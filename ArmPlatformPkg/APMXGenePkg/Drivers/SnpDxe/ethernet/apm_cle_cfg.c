/**
 * Copyright (c) 2013, AppliedMicro Corp. All rights reserved.
 *
 * This program and the accompanying materials
 * are licensed and made available under the terms and conditions of the BSD License
 * which accompanies this distribution.  The full text of the license may be found at
 * http://opensource.org/licenses/bsd-license.php
 *
 * THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
 * WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.
 *
 **/

#include "apm_enet_access.h"
#ifndef APM_XGENE
#include <misc/xgene/qm/apm_qm_core.h>
#include <misc/xgene/cle/apm_preclass_data.h>
#include <misc/xgene/cle/apm_cle_mgr.h>
#else
#include <netinet/in.h>
#include "../qm/apm_qm_core.h"
#include "../classifier/apm_preclass_data.h"
#include "../classifier/apm_cle_mgr.h"
#endif

#define CLE_DB_INDEX		0

static struct ptree_kn kn = {0, DBPTR_ALLOC(CLE_DB_INDEX)};
static struct apm_cle_dbptr dbptr;
static struct apm_ptree_config ptree[MAX_ENET_PORTS];
static u8 enet_macaddr[MAX_ENET_PORTS][8] = {{0}};

static struct ptree_branch branch[] = {
	{      0, 0xFFFF,  EQT, PTREE_ALLOC(0), EW_BRANCH(2),  2, 1, JMP_REL, JMP_FW },	/* Broadcast MACAddr byte [0:1] */
	{ 0xffff,      0,  EQT, PTREE_ALLOC(1), EW_BRANCH(0),  0, 0, JMP_REL, JMP_BW },	/* Jump to check EthernetN MACAddr [0:1] */
	{      0, 0xFFFF,  EQT, PTREE_ALLOC(0), EW_BRANCH(4),  2, 1, JMP_REL, JMP_FW },	/* Broadcast MACAddr byte [2:3] */
	{ 0xffff,      0,  EQT, PTREE_ALLOC(1), EW_BRANCH(0),  2, 0, JMP_REL, JMP_BW },	/* Jump to check EthernetN MACAddr [0:1] */
	{      0, 0xFFFF,  EQT, PTREE_ALLOC(0), EW_BRANCH(6),  8, 1, JMP_REL, JMP_FW },	/* Broadcast MACAddr byte [4:5] */
	{ 0xffff,      0,  EQT, PTREE_ALLOC(1), EW_BRANCH(0),  4, 0, JMP_REL, JMP_BW },	/* Jump to check EthernetN MACAddr [0:1] */
#if defined(ALLOW_BROADCAST_ONLY_ARP)   /* (0x0806 == Ethernet Packet's EtherType field) */
	{      0, 0x0806,  EQT, PTREE_ALLOC(2), EW_BRANCH(0),  0, 1,       0,      0 },	/* Broadcast Ethertype ARP */
#elif defined(ALLOW_BROADCAST_UPTO_ARP) /* (0x0806 >= Ethernet Packet's EtherType field) */
	{      0, 0x0806,GTEQT, PTREE_ALLOC(2), EW_BRANCH(0),  0, 1,       0,      0 },	/* Broadcast Ethertype 0 to ARP (0x0806) */
#elif defined(ALLOW_BROADCAST_UPTO_VLAN)/* (0x8100 >= Ethernet Packet's EtherType field */
	{      0, 0x8100,GTEQT, PTREE_ALLOC(2), EW_BRANCH(0),  0, 1,       0,      0 },	/* Broadcast Ethertype 0 to VLAN (0x8100) */
#else /* ALLOW_BROADCAST_ANY_ETHERTYPE */
	{ 0xffff,      0,  EQT, PTREE_ALLOC(2), EW_BRANCH(0),  0, 1,       0,      0 },	/* No check for Ethertype */
#endif
	{ 0xffff,      0, NEQT,              0,            0,  0, 0,       0,      0 },	/* Not a Broadcast Ethertype ARP so drop */


	{      0, 0x0000,  EQT, PTREE_ALLOC(1), EW_BRANCH(2),  2, 1, JMP_REL, JMP_FW },	/* EthernetN MACAddr byte [0:1] */
	{ 0xffff,      0, NEQT,              0,            0,  0, 0,       0,      0 },	/* Not our EthernetN MACAddr [0:1] so drop */
	{      0, 0x0000,  EQT, PTREE_ALLOC(1), EW_BRANCH(4),  2, 1, JMP_REL, JMP_FW },	/* EthernetN MACAddr byte [2:3] */
	{ 0xffff,      0, NEQT,              0,            0,  0, 0,       0,      0 },	/* Not our EthernetN MACAddr [2:3] so drop */
	{      0, 0x0000,  EQT, PTREE_ALLOC(1), EW_BRANCH(6),  8, 1, JMP_REL, JMP_FW },	/* EthernetN MACAddr byte [4:5] */
	{ 0xffff,      0, NEQT,              0,            0,  0, 0,       0,      0 },	/* Not our EthernetN MACAddr [4:5] so drop */
	{ 0xffff,      0,  EQT, PTREE_ALLOC(2), EW_BRANCH(0),  0, 1,       0,      0 },	/* No check for Ethertype */
	{ 0xffff,      0, NEQT,              0,            0,  0, 0,       0,      0 },	/* Not our EthernetN Ethertype so drop */

	{ 0xffff,      0,  EQT, PTREE_ALLOC(3), KEY_INDEX(0),  0, 0,       0,      0 },	/* Last Node allowing all of the above */
};

static struct ptree_dn dn[] = {
	{ START_NODE,	DBPTR_DROP(0), AVL_SEARCH(NO_BYTE), 0, 0, 0, 8, &branch[0] },	/* Allow BCast MAC with ARP */
	{ INTERIM_NODE,	DBPTR_DROP(0), AVL_SEARCH(NO_BYTE), 0, 0, 0, 8, &branch[8] },	/* Allow our EthernetN MACAddr */
	{ LAST_NODE,	DBPTR_DROP(0), AVL_SEARCH(NO_BYTE), 0, 0, 0, 1, &branch[16] },	/* Last Node */
};

static struct ptree_node node[] = {
	{ PTREE_ALLOC(0), EWDN, 0, (struct ptree_dn*)&dn[0] },
	{ PTREE_ALLOC(1), EWDN, 0, (struct ptree_dn*)&dn[1] },
	{ PTREE_ALLOC(2), EWDN, 0, (struct ptree_dn*)&dn[2] },
	{ PTREE_ALLOC(3),   KN, 0,    (struct ptree_kn*)&kn },
};

int apm_preclass_init(u8 port_id, struct eth_queue_ids *eth_q)
{
	int rc;
	struct apm_ptree_config *ptree_config = &ptree[port_id];

	memset(&enet_macaddr[port_id][0], 0, 8);
	memset(ptree_config, 0, sizeof(*ptree_config));

	ptree_config->default_result = DEFAULT_DBPTR;
	ptree_config->start_parser = 1;

	memset(&dbptr, 0, sizeof(dbptr));
	memset(&kn, 0, sizeof(kn));

	PCLS_DBG("Create Preclassifier DB entries for Ping Tree port %d\n",
			port_id);

	dbptr.index = DBPTR_ALLOC(CLE_DB_INDEX);
	dbptr.dstqid = eth_q->rx_qid | DST_QM_IP(eth_q->qm_ip);
	dbptr.fpsel  = eth_q->rx_fp_pbn - 0x20;

	kn.result_pointer = DBPTR_ALLOC(CLE_DB_INDEX);

	PCLS_DBG("Create Patricia Tree Nodes for Ping Tree. dstqid=0x%x, fpsel=0x%x\n",
			dbptr.dstqid, dbptr.fpsel);
	if ((rc = apm_ptree_alloc(port_id, ARRAY_SIZE(node), 1, node, &dbptr,
					ptree_config)) != APM_RC_OK) {
		PCLS_ERR("Preclass init error %d \n", rc);
		return rc;
	}

	PCLS_DBG("Switch Tree for port %d with default ptree\n", port_id);
	if ((rc = apm_set_sys_ptree_config(port_id, ptree_config) != APM_RC_OK)) {
		PCLS_ERR("Preclass Switch port %d Tree error %d \n",
				port_id, rc);
		return rc;
	}

	return rc;
}

void apm_preclass_update_mac(u8 port_id, u8 *macaddr)
{
	int i;
	struct ptree_branch pbranch;

	if (memcmp(&enet_macaddr[port_id][0], macaddr, 6) == 0)
		return;

	memcpy(&enet_macaddr[port_id][0], macaddr, 6);

	for (i = 0; i < 3; i++) {
		pbranch.mask = 0;
		pbranch.data = ntohs(*(u16 *)&macaddr[i * 2]);
		pbranch.operation = EQT;
		apm_set_ptree_node_branch(port_id,
				ptree[port_id].start_node_ptr + 1,
				0, (i * 2), &pbranch, SET_BRANCH_MDO);
	}
}
