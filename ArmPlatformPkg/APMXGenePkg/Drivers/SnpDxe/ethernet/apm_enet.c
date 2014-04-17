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

#include "../mustang.h"
#include "apm_enet_access.h"
#ifndef APM_XGENE
#include <asm/io.h>
#include <malloc.h>
#include <watchdog.h>
#endif
#include "apm_enet_mac.h"
#include "apm_xgenet_mac.h"
#include "apm_enet_misc.h"
#include "apm_enet_csr.h"
#ifndef APM_XGENE
#include <misc/xgene/cle/apm_preclass_data.h>
#include <misc/xgene/qm/apm_qm_core.h>
#else
#include "../classifier/apm_preclass_data.h"
#include "../qm/apm_qm_core.h"
#include "../qm/apm_qm_utils.h"
#endif

#define malloc AllocateZeroPool
#if defined(CONFIG_MII) || defined(CONFIG_CMD_MII)
#include <miiphy.h>
#endif

#ifdef CONFIG_CMD_I2C
#include <i2c.h>
#define SPFF_I2C_BUS    1
#define SPFF_I2C_CH_ADDR     0x71
#define SPFF_I2C_OUT0_ADDR   0x26 /* XG0, XG1 laser control */
#define SPFF_I2C_OUT1_ADDR   0x27 /* XG2, XG3 */
#define IN_OFFSET  0
#define OUT_OFFSET 1
#define CONFIG_OFFSET 3
u32 sfp_addr[4] = {SPFF_I2C_OUT0_ADDR, SPFF_I2C_OUT0_ADDR,
                   SPFF_I2C_OUT1_ADDR, SPFF_I2C_OUT1_ADDR};
u32 sfp_abs[4] = {0x20, 0x2, 0x20, 0x2};
u32 sfp_laser_on[4] = {0xef, 0xfe, 0xef, 0xfe};
u32 sfp_laser_off[4] = {0xff, 0xff, 0xff, 0xff};
#endif

#undef PCM_LOOPBACK
#ifndef APM_XGENE
DECLARE_GLOBAL_DATA_PTR;
#endif

#if !defined(CONFIG_NET_MULTI)
struct eth_device *emac0_dev;
#endif
struct eth_device *emac_dev[MAX_ENET_PORTS];

static u32 eth_count = 0;
char eth_port[20];
//int gdev_autoneg_done[MAX_ENET_PORTS];

// TODO:  move to common
#define APM_ENET01_BASE_ADDRESS		(CONFIG_SYS_ETH01_CSR_BASE)
#define APM_ENET01_GBL_BASE_ADDRESS	(APM_ENET01_BASE_ADDRESS)
#define APM_ENET0_BASE_ADDRESS		(APM_ENET01_BASE_ADDRESS)
#define APM_XGENET0_BASE_ADDRESS	(CONFIG_SYS_XGE0_CSR_BASE)
#define APM_XGENET0_GBL_BASE_ADDRESS	(APM_XGENET0_BASE_ADDRESS)
#define APM_ENET4_BASE_ADDRESS		(CONFIG_SYS_ETH4_CSR_BASE)
#define APM_ENET4_GBL_BASE_ADDRESS	(APM_ENET4_BASE_ADDRESS)

/* All SGMII use  MENET MII Bus to talk to external PHY */
#define APM_ENET_MII_BASE_ADDRESS	(APM_ENET4_BASE_ADDRESS)

#define APM_GLBL_DIAG_OFFSET		0x7000

#define APM_CLE01_GBL_BASE_ADDR		(CONFIG_SYS_CLE01_CSR_BASE)
#define APM_CLE_XG0_GBL_BASE_ADDR	(CONFIG_SYS_XGC0_CSR_BASE)
#define APM_CLE4_GBL_BASE_ADDR	        (CONFIG_SYS_CLE4_CSR_BASE)

/* Ethernet raw register write routine */
inline int apm_enet_wr32(void *addr, u32 data)
{
	ENET_REG_WR("Write addr 0x%p data 0x%08X\n", addr, data);
	writel(data, (u64)addr);
	return 0;
}

/* Ethernet raw register read routine */
inline int apm_enet_rd32(void *addr, u32 *data)
{
	ENET_REG_RD("Read addr 0x%p ", addr);
	*data = readl((u64)addr);
	ENET_REG_RD("data 0x%08X\n", *data);
	return 0;
}

#ifdef DEBUG_HEXDUMP
static int putshex(u8 *buf, int len)
{
	int i;
	
	for (i = 0; i < len; i++) {
		if (i == 0) {
			printf("%02X", buf[i]);
		} else {
			if ((i % 32) == 0)
				printf("\n%02X", buf[i]);
			else if ((i % 4) == 0)
				printf(" %02X", buf[i]);
			else
				printf("%02X", buf[i]);
		}
	}
	printf("\n");
	return 0;
}
#endif

u64 PADDR(void *ptr)
{
	u64 paddress = 0x000000000ULL; /* Macro for DDR less than 4 GB */
	paddress |= (unsigned long) ptr;
	return paddress;
}

int apm_eth_macaddr_check(struct eth_device *dev)
{
#if 0

	struct apm_enet_dev *priv_dev = dev->priv;
	struct apm_data_priv *priv = &priv_dev->priv;
	char mac_addr[16];
	int rc = APM_RC_OK;

	if (strcmp(dev->name, "eth0"))
		sprintf(mac_addr, "%saddr", dev->name);
	else
		strcpy(mac_addr, "ethaddr");

	if (!eth_getenv_enetaddr(mac_addr, dev->enetaddr)) {
		printf("ERROR: %s: %s variable not set for port %d !\n",
			dev->name, mac_addr, priv->port);
		rc = APM_RC_ERROR;
	}
#else
	int rc = 0;
#endif
	return rc;
}

/* This will be called by application, not running in interrupt context */
int apm_eth_tx(struct eth_device *dev, volatile void *ptr, int len)
{
	struct enet_frame *ef_ptr;
	struct apm_enet_dev *priv_dev;
	struct apm_qm_msg_desc tx_msg_desc;
	struct apm_qm_msg_desc rx_msg_desc;
	struct apm_qm_msg32 msg;
	struct apm_qm_msg16 *msg16 = &(msg.msg16);
	struct apm_qm_msg_up16 *msg_up16 = &msg.msgup16;
	u16 data_len;
	int rc;
	u64 phy;
	int poll;
	u32 qm_ip;

	memset(&msg, 0, sizeof(msg));
	priv_dev = dev->priv;
	qm_ip = priv_dev->qm_ip;

	ef_ptr = (struct enet_frame *) ptr;

	/* Copy mac address into frame buffer */
	memcpy(ef_ptr->source_addr, dev->enetaddr, ENET_ADDR_LENGTH);

	// FIXME: TX_DATA_LEN_MASK = 0xFFF ok ?
	data_len = (len & TX_DATA_LEN_MASK);

	/* Prepare the Msg to send out the packet */
	ENET_DEBUG_TX("Tx Pkt VADDR 0x%p len %d\n", ef_ptr, data_len);
	ENET_TXHEXDUMP((u8*) ef_ptr, data_len);

	msg16->BufDataLen = (data_len < 60) ? 60 : data_len;
	phy               = PADDR(ef_ptr);
	msg16->DataAddr   = phy;
	msg16->C          = apm_qm_coherent();

	/* For Receiving completion message */
	msg_up16->H0Enq_Num = priv_dev->queues.comp_qid | DST_QM_IP(qm_ip);
	tx_msg_desc.qm_ip_blk = qm_ip;
	tx_msg_desc.qid = priv_dev->queues.tx_qid;
	tx_msg_desc.msg = &msg;

	ENET_DEBUG_TX("Enqueue QM msg QID %d len %d\n",
		tx_msg_desc.qid, msg16->BufDataLen);
        ENET_TXHEXDUMP((u8*) &msg, 32);

#ifdef CONFIG_APM_QM_ALTERNATE_ENQUEUE
	if ((rc = apm_qml_push_msg(&tx_msg_desc)) != APM_RC_OK) {
		printf("Error in Packet Transmit \n");
		return -1;
	}
#else
	if (qm_ip == IP_BLK_QML) {
		if ((rc = apm_qml_push_msg(&tx_msg_desc)) != APM_RC_OK) {
			printf("Error in Packet Transmit \n");
			return -1;
		}
	} else {
		if ((rc = apm_qm_push_msg(&tx_msg_desc)) != APM_RC_OK) {
			printf("Error in Packet Transmit \n");
			return -1;
		}
	}
#endif

	/* Check for completion message to make sure transmit succeeded */
	memset(&msg, 0, sizeof(msg));
	rx_msg_desc.qm_ip_blk = qm_ip;
	rx_msg_desc.msg = &msg;
	rx_msg_desc.qid = priv_dev->queues.comp_qid;
	rx_msg_desc.mb_id = priv_dev->queues.comp_mb;
	rx_msg_desc.is_msg16 = 0;

	ENET_DEBUG_TX("Checking completion msg QID %d mailbox %d\n",
		rx_msg_desc.qid, rx_msg_desc.mb_id);
	poll = 0;
	while (poll++ < 10) {
#ifdef CONFIG_APM_QM_ALTERNATE_DEQUEUE
		rc = apm_qml_pull_msg(&rx_msg_desc);
#else
		if (qm_ip == IP_BLK_QML)
			rc = apm_qml_pull_msg(&rx_msg_desc);
		else
			rc = apm_qm_pull_msg(&rx_msg_desc);
#endif
		if (rc == APM_RC_OK)
			break;
		/* Wait a while so we receive completion msg */
		udelay(500);
	}

	if (poll >= 10) {
#if 0	//
		struct apm_qm_qstate qstate = {0};
		u32 qcnt;

		for (qcnt = QM_START_QID_CORE0 ; qcnt < (QM_START_QID_CORE0 + 4); qcnt++) { 
			u32 val;
			memset(&qstate, 0, sizeof(qstate)) ;
			//memset(&msg, 0, sizeof(msg));
			apm_qm_qstate_rd(qm_ip, qcnt, &qstate);
			dump_qstate(&qstate);
			val = apm_qm_pb_get(qm_ip, qstate.slave_id, qstate.pbn);
			ENET_DEBUG("QM PBN 0x%08X\n", val);
		}
#endif
		printf("Time out completion msg QID %d mailbox %d\n",
				rx_msg_desc.qid, rx_msg_desc.mb_id);
	} else	{
		ENET_DEBUG_TX("Received completion msg QID %d mailbox %d\n",
				rx_msg_desc.qid, rx_msg_desc.mb_id);
#ifdef DEBUG_HEXDUMP
		printf("Completion message dump:: \n");
		putshex((u8 *)&msg,  sizeof(struct apm_qm_msg32));
#endif	
	}

	return rc;
}

static int dealloc_rx_msg(struct apm_enet_dev *priv_dev, struct apm_qm_msg32 *msg)
{
	struct apm_qm_msg_desc fp_msg_desc;
	struct apm_qm_msg16 fp_msg;
	struct apm_qm_msg16 *msg16 = &msg->msg16;
	u32 qm_ip = priv_dev->qm_ip;
	int rc;

	ENET_DEBUG_RX("Dealloc the Buff to FP \n");
	memset(&fp_msg, 0, sizeof(fp_msg));

	/* Common fields  */
	fp_msg.BufDataLen = BUF_LEN_2K;
	fp_msg.FPQNum = priv_dev->queues.rx_fp_qid | DST_QM_IP(qm_ip);
	fp_msg.DataAddr = msg16->DataAddr;
	fp_msg.C = apm_qm_coherent();

	fp_msg_desc.qid = priv_dev->queues.rx_fp_qid;
	fp_msg_desc.msg = &fp_msg;
	fp_msg_desc.qm_ip_blk = qm_ip;

#ifdef CONFIG_APM_QM_ALTERNATE_ENQUEUE
	rc = apm_qml_fp_dealloc_buf(&fp_msg_desc);
#else
	if (qm_ip == IP_BLK_QML)
		rc = apm_qml_fp_dealloc_buf(&fp_msg_desc);
	else
		rc = apm_qm_fp_dealloc_buf(&fp_msg_desc);
#endif
	if (rc != APM_RC_OK)
		printf("Can not de-allocate buffer to QM\n");
	return rc;
}

/*
 * return size of buffer received, or zero for error
 */
static int get_rx_msg(struct eth_device *dev, struct apm_qm_msg32 *msg)
{
	struct apm_enet_dev *priv_dev = dev->priv;
	struct apm_data_priv *priv = &priv_dev->priv;
	struct apm_qm_msg_desc rx_msg_desc;
	struct apm_qm_msg16 *msg16 = &msg->msg16;
	u32 qm_ip = priv_dev->qm_ip;
	int rc;
	u8 LErr;

	memset(msg, 0, sizeof(msg));
	rx_msg_desc.qm_ip_blk = qm_ip;
	rx_msg_desc.msg = msg;
	rx_msg_desc.qid = priv_dev->queues.rx_qid;
	rx_msg_desc.mb_id = priv_dev->queues.rx_mbid;
	rx_msg_desc.is_msg16 = 0;

	/* Get the Pkts if any */
#ifdef CONFIG_APM_QM_ALTERNATE_DEQUEUE
	rc = apm_qml_pull_msg(&rx_msg_desc);
#else
	if (qm_ip == IP_BLK_QML)
		rc = apm_qml_pull_msg(&rx_msg_desc);
	else
		rc = apm_qm_pull_msg(&rx_msg_desc);
#endif
	if (rc != 0)
		return 0;

	if (msg16->LErr)
		ENET_DEBUG_RX("Rcvd LErr 0x%02x\n", msg16->LErr);
	if (msg16->ELErr)
		ENET_DEBUG_RX("Rcvd ELErr 0x%02x\n", msg16->ELErr);
	LErr = msg16->LErr;
	LErr |= (u8) msg16->ELErr << 3;
	if (LErr) {
#if defined(BYPASS_CLE)
		if (LErr == 0x10 || LErr == 0x11)
			return 0;
#endif		
		ENET_DEBUG_ERR("Rcvd LErr 0x%02x ELErr 0x%02x\n", msg16->LErr, msg16->ELErr);
		apm_enet_parse_error(LErr, 1, rx_msg_desc.qid);
		if (priv->phy_mode == PHY_MODE_SGMII) {
			apm_enet_serdes_reset(priv);
			apm_enet_autoneg(priv, 1);
		}
		if (msg16->FPQNum & 0x3ff) /* 10-bit */
			dealloc_rx_msg(priv_dev, msg);

		return 0;
	}
	return msg16->BufDataLen & TX_DATA_LEN_MASK;
}


/* Deliver received packets to higher layers */
int apm_eth_rx(struct eth_device *dev, VOID *Buffer, UINTN *BufferSize)
{
	static int msg_buf_len = 0;
	struct apm_enet_dev *priv_dev;
	struct apm_qm_msg32 msg;
	struct apm_qm_msg16 *msg16 = &msg.msg16;
	u16 data_len;
	u64 pkt_ptr = 0UL;
	UINTN orig_size;

	priv_dev = dev->priv;

	orig_size = *BufferSize;

	if (!msg_buf_len) {
		msg_buf_len = get_rx_msg(dev, &msg);
		if (msg_buf_len == 0) {
			*BufferSize = 0;
			return APM_RC_OK;
		}
	}

	/* Pass the Packet to Higher Layer for processing */
	data_len = msg_buf_len;
	pkt_ptr = (u64) (msg16->DataAddr);

	*BufferSize = data_len;
	if (data_len > orig_size)
		return APM_RC_OK;

	msg_buf_len = 0;

	ENET_DEBUG_RX("Rcvd Pkt of Len[%d] Passing it to Higher UP\n", data_len);
#ifdef DEBUG_HEXDUMP
	printf("Message Dump:: \n");
	putshex((u8 *)&msg,  sizeof(struct apm_qm_msg32));
	printf("Packet Dump:: \n");
	putshex((u8 *)(u64)msg16->DataAddr, data_len);
#endif
	//NetReceive((uchar*)pkt_ptr, data_len);
	*BufferSize = data_len;
	memcpy(Buffer, (void*) pkt_ptr, data_len);
	ENET_DEBUG_RX("pkt_ptr = 0x%llx, data_len = 0x%x\n", pkt_ptr, data_len);
#ifdef DEBUG_HEXDUMP
	putshex((u8 *)Buffer, data_len);
#endif
	dealloc_rx_msg(priv_dev, &msg);

	return APM_RC_OK;
}

static void apm_eth_halt(struct eth_device *dev)
{
	struct apm_enet_dev *priv_dev = dev->priv;
	struct apm_data_priv *priv = &priv_dev->priv;

	// FIXME:  why skipping 10G ports ?
#if defined(PCM_LOOPBACK)
	if (priv->port < XGENET_0 || priv->port > XGENET_3)
		return;
#endif
	/* Disable MAC */
	apm_enet_mac_rx_state(priv, 0);
	apm_enet_mac_tx_state(priv, 0);
}

static int apm_eth_init(struct eth_device *dev)
{
	struct apm_enet_dev *priv_dev;
	struct apm_data_priv *priv;
	int rc;

	priv_dev = dev->priv;
	priv = &priv_dev->priv;

	ENET_DEBUG("Initialize index:%d\n", dev->index);

	if ((rc = apm_eth_macaddr_check(dev)) != APM_RC_OK)
		goto _ret;

#ifndef BYPASS_CLE
	apm_preclass_update_mac(priv->port, dev->enetaddr);
#endif
	/* Check link mode */
	apm_enet_get_link_status(priv);

	apm_gmac_init(priv, dev->enetaddr, priv->speed, ENET_MAX_MTU_ALIGNED, 1);
	/* Enable MAC */
	apm_enet_mac_rx_state(priv, 1);
	apm_enet_mac_tx_state(priv, 1);

_ret:
	return rc;
}

#ifdef CONFIG_APM88XXXX_XGENET
int apm_ethx_init(struct eth_device *dev, bd_t *bis)
{
	struct apm_enet_dev *priv_dev;
	struct apm_data_priv *priv;
	int rc;

	priv_dev = dev->priv;
	priv     = &priv_dev->priv;

	ENET_DEBUG("XG Initialize %s\n", dev->name);

	if ((rc = apm_eth_macaddr_check(dev)) != APM_RC_OK)
		goto _ret;

#ifndef BYPASS_CLE
	apm_preclass_update_mac(priv->port, dev->enetaddr);
#endif

	rc = apm_xgmac_init( priv, dev->enetaddr, 10000, ENET_MAX_MTU_ALIGNED, 1 );
	/* Enable MAC */
	apm_enet_mac_rx_state(priv, 1);
	apm_enet_mac_tx_state(priv, 1);

_ret: 
	return rc;
}
#endif

// FIXME: what are the following two defines ?  are they required ?
#if defined(CONFIG_MII) || defined(CONFIG_CMD_MII)
int apm_eth_miiphy_read(const char *devname, unsigned char addr, unsigned char reg,
			unsigned short *value)
{
	int ret;
	u32 data;
#if !defined(CONFIG_NET_MULTI)
	struct eth_device *dev = emac0_dev;
#else	
	struct eth_device *dev = eth_get_dev_by_name(devname);
#endif	
	struct apm_enet_dev *priv_dev = NULL;

	if (!dev)
		return -1;

	priv_dev = dev->priv;

	ret = apm_genericmiiphy_read(&priv_dev->priv, addr, reg, &data);
	if (ret == 0)
		*value = (unsigned short)(0x0000ffff & data);

	return ret;
}

int apm_eth_miiphy_write(const char *devname, unsigned char addr, unsigned char reg,
			 unsigned short value)
{
	u32 data = (0x0000ffff & (u32)value);
#if !defined(CONFIG_NET_MULTI)
	struct eth_device *dev = emac0_dev;
#else	
	struct eth_device *dev = eth_get_dev_by_name(devname);
#endif	
	struct apm_enet_dev *priv_dev = NULL;

	if (!dev)
		return -1;

	priv_dev = dev->priv;

	return apm_genericmiiphy_write(&priv_dev->priv, addr, reg, data);
}
#endif

int apm_eth_fp_init(struct apm_enet_dev *priv_dev)
{
	int i, rc = APM_RC_OK;
	unsigned char *fp_buf_array;
	struct apm_qm_msg_desc fp_msg_desc;
	struct apm_qm_msg16 msg;
	u32 qm_ip = priv_dev->qm_ip;

	ENET_DEBUG("Allocate memory for buffers \n" );
	// FIXME: can we make it simple ?
	fp_buf_array = malloc(64 + (NO_RX_BUFF * ENET_MAX_MTU_ALIGNED));
	if (!fp_buf_array) {
		printf("Cannot allocate eth_rx_buf_list \n");
		rc = APM_RC_ERROR;
		goto _ret;
	}
	fp_buf_array = (void *)(((unsigned long)fp_buf_array + 15) & ~0xf);
	// FIXME: does it initiatize the new aligned array ?
	memset(fp_buf_array, 0, NO_RX_BUFF * ENET_MAX_MTU_ALIGNED);

	memset(&msg, 0, sizeof(msg));
	fp_msg_desc.msg = &msg;

	/* Common fields */
	msg.BufDataLen = BUF_LEN_2K;	 /* 2K buffer size */
	msg.FPQNum = priv_dev->queues.rx_fp_qid | DST_QM_IP(qm_ip);

	fp_msg_desc.qid = priv_dev->queues.rx_fp_qid;
	fp_msg_desc.mb_id = 0;
	fp_msg_desc.msg = &msg;
	fp_msg_desc.qm_ip_blk = qm_ip;

	for (i = 0; i < NO_RX_BUFF; i++) {
		/* Assign addresses as per configuration */
		msg.DataAddr = PADDR(fp_buf_array + i * ENET_MAX_MTU_ALIGNED);
		msg.C = apm_qm_coherent();

#ifdef CONFIG_APM_QM_ALTERNATE_ENQUEUE
		apm_qml_fp_dealloc_buf(&fp_msg_desc);
#else
		if (qm_ip == IP_BLK_QML)
			apm_qml_fp_dealloc_buf(&fp_msg_desc);
		else
			apm_qm_fp_dealloc_buf(&fp_msg_desc);
#endif
	}

_ret:
	return rc;
}

// FIXME: hide pbn related functionality from ethernet driver, let qm handle this
int apm_eth_pbn_clr(struct apm_enet_dev *priv_dev, int slave_id, int pbn)
{
#ifdef PBN_CLEAR_SUPPORT
	int no_buf;
	u32 word0;
	u32 word1;
	u32 word2;
	u32 word3;
	u32 val;
	int pbn_enabled;
	u32 qm_ip = priv_dev->qm_ip;

	ENET_DEBUG("Draining pbn %d\n", pbn);

	/* Disable queue pre-fetch buffer to not push message */
	val = apm_qm_pb_get(qm_ip, slave_id, pbn);
	pbn_enabled = val & (1 << 21);
	val &= ~(1 << 21);	/* Disable pre-fetch buffer pushing */
	apm_qm_pb_set(qm_ip, slave_id, pbn | (1 << 31), val);

	/* Wait for any in-service to finish */
	do {
		val = apm_qm_pb_get(qm_ip, slave_id, pbn);
	} while (val & (1 << 30));	

	if (pbn < 0x20) {
		/* Non-free pool queue */
		apm_enet_write(&priv_dev->priv, BLOCK_ETH_QMI,
				ENET_CFGSSQMIWQRESET_ADDR, 1 << pbn);
		do {
			apm_enet_read(&priv_dev->priv, BLOCK_ETH_QMI,
					ENET_CFGSSQMIWQRESET_ADDR, &val);
		} while (val & (1 << pbn));
	} else {
		/* Now drain the ETH pre-fetch free pool buffer */
		no_buf = apm_enet_get_pb_cnt(&priv_dev->priv, pbn - 0x20);
		udelay(1000);
		/* Setup QM side to match to avoid QM error interrupt */
		val = apm_qm_pb_get(qm_ip, slave_id, pbn);
		val &= ~0xFF;
		val |= ((no_buf + 1) & 0xFF);
		apm_qm_pb_set(qm_ip, slave_id, pbn | (1 << 31), val);
		ENET_DEBUG("Draining pbn %d count %d\n", pbn, no_buf);
		while (no_buf > 0)  {
			apm_enet_qmi_read_pb_msg(&priv_dev->priv, pbn,
						0, 0, &word3);
			apm_enet_qmi_read_pb_msg(&priv_dev->priv, pbn,
						1, 0, &word2);
			apm_enet_qmi_read_pb_msg(&priv_dev->priv, pbn,
						2, 0, &word1);
			apm_enet_qmi_pop_pb_msg(&priv_dev->priv, pbn,
						3, 1, &word0);
			no_buf = apm_enet_get_pb_cnt(&priv_dev->priv, pbn - 0x20);
			udelay(1000);
		}
	}

	/* Clear PBN on the QM side */
	apm_qm_pb_clr(qm_ip, slave_id, pbn);

	if (pbn_enabled) {
		val = apm_qm_pb_get(qm_ip, slave_id, pbn);
		val |= 1 << 21;
		apm_qm_pb_set(qm_ip, slave_id, pbn, val);
		ENET_DEBUG("QM PBN 0x%08X\n", val);
	}
#endif
	return 0;
}

// FIXME: code will be cleaned up after QM changes
int apm_eth_qm_init(struct apm_enet_dev *priv_dev)
{
	static struct apm_qm_qstate *enet_qstates = NULL;
	struct apm_qm_qstate *cur_qstate = NULL;
	struct apm_qm_qstate *tmp_qstate = NULL;
	int qcnt = 4;
	struct apm_qm_qalloc eth_qalloc = {0};
	int err = 0;
	u16 hw_port_id = IP_ETH0 + priv_dev->priv.port;
	u32 qm_ip = priv_dev->qm_ip;

	priv_dev->queues.qm_ip = qm_ip;
	/* allocate queue state memory if not done so already */
	if (enet_qstates == NULL) {
		enet_qstates = malloc(qcnt * sizeof(struct apm_qm_qstate));
		if (enet_qstates == NULL) {
			printf("Couldn't allocate memory for Enet"
			       "queues state\n");
			return -1;
		}
	}
	memset(enet_qstates, 0, qcnt * sizeof(struct apm_qm_qstate));
	cur_qstate = enet_qstates;

	/* Allocate egress work queue from CPU0 to ETH0 */
	eth_qalloc.qstates = cur_qstate;
	eth_qalloc.qm_ip_blk = qm_ip;
	eth_qalloc.ip_blk = hw_port_id;
	eth_qalloc.cpu_id = CORE0;
	eth_qalloc.q_type = P_QUEUE;
	eth_qalloc.q_count = 1;
	eth_qalloc.direction = DIR_EGRESS;
	eth_qalloc.qsize = SIZE_2KB;
	eth_qalloc.thr_set = 1;
	eth_qalloc.qaddr = 0; /* Dynamically allocated */	
	if ((err = apm_qm_alloc_q(&eth_qalloc)) != 0) {
		printf("Error allocating two egress work queues for ETH0\n");
		return -1;
	}	
	priv_dev->queues.tx_qid = cur_qstate->q_id;
	/* Clear Ethernet and QM PBN */
	apm_eth_pbn_clr(priv_dev, cur_qstate->slave_id, cur_qstate->pbn);
	cur_qstate++;

	/* Allocate one ingress queue for Eth0 to CPU0 normal work queue */
	eth_qalloc.qstates = cur_qstate;
	eth_qalloc.direction = DIR_INGRESS;	
	if ((err = apm_qm_alloc_q(&eth_qalloc)) != 0) {
		printf("Error allocating ingress queues for ETH to CPU0\n");
		return -1;
	}
	priv_dev->queues.rx_qid = cur_qstate->q_id;
	priv_dev->queues.rx_mbid = cur_qstate->mb_id;
	/* Clear PBN on the QM side */
	apm_eth_pbn_clr(priv_dev, cur_qstate->slave_id, cur_qstate->pbn);
	cur_qstate++;

	/* Get completion queue info for Ethx to CPU0 */
	tmp_qstate = apm_qm_get_compl_queue(qm_ip);
	memcpy(cur_qstate, tmp_qstate, sizeof(struct apm_qm_qstate));
	priv_dev->queues.comp_qid = cur_qstate->q_id;
	priv_dev->queues.comp_mb = cur_qstate->mb_id;
	cur_qstate++;

	/* Allocate free pool for ETH0 from CPU0 */
	eth_qalloc.qstates = cur_qstate;
	eth_qalloc.q_type = FREE_POOL;
	eth_qalloc.direction = DIR_EGRESS;
	if ((err = apm_qm_alloc_q(&eth_qalloc)) != 0) {
		printf("Error allocating free pool for CPU0\n");
		return -1;
	}
	priv_dev->queues.rx_fp_qid = cur_qstate->q_id;
	priv_dev->queues.rx_fp_pbn = cur_qstate->pbn;
	priv_dev->queues.rx_fp_mbid = cur_qstate->mb_id;
	/* Clear PBN on the Ethernet side */	
	apm_eth_pbn_clr(priv_dev, cur_qstate->slave_id, cur_qstate->pbn);

	ENET_DEBUG("RX QID %d, RX MB %d, TX QID %d, CQID %d, "
		"CMB %d, FP QID %d, FP PBN %d\n",
		priv_dev->queues.rx_qid, priv_dev->queues.rx_mbid,
		priv_dev->queues.tx_qid, priv_dev->queues.comp_qid,
		priv_dev->queues.comp_mb, priv_dev->queues.rx_fp_qid,
		priv_dev->queues.rx_fp_pbn);
#if 0
	for (qcnt = QM_START_QID_CORE0; qcnt < (QM_START_QID_CORE0 + 4); qcnt++) {
		struct apm_qm_qstate qstate = {0};
		u32 val;
		apm_qm_qstate_rd(qm_ip, qcnt, &qstate);
		dump_qstate(&qstate);
		val = apm_qm_pb_get(qm_ip, qstate.slave_id, qstate.pbn);
		ENET_DEBUG("QM PBN 0x%08X\n", val);
	}
#endif


	return err;
}

/* Turn on laser for port */
void apm_xg_laser_on(u32 port)
{
#ifdef CONFIG_CMD_I2C	/* TODO move this to XG */
	u8  i2c_data;
	u32 p = port - XGENET_0;
	u8 data;

	i2c_set_bus_num(SPFF_I2C_BUS);  /* Set to bus 1 */
	/* Select channel 1 */
	i2c_data = 0x1;
	i2c_write(SPFF_I2C_CH_ADDR, OUT_OFFSET, 1, &i2c_data, sizeof(i2c_data));
	/* Set config */
	i2c_data = 0xee;
	i2c_write(sfp_addr[p], CONFIG_OFFSET, 1, &i2c_data, sizeof(i2c_data));

	i2c_read(sfp_addr[p], IN_OFFSET, 1, &i2c_data, sizeof(i2c_data));

	if (p & 1) {
		if (i2c_data & sfp_abs[p])
			data = sfp_laser_off[p];
		else
			data = sfp_laser_on[p];

		if (i2c_data & sfp_abs[p - 1])
			data &= sfp_laser_off[p - 1];
		else
			data &= sfp_laser_on[p - 1];
	} else {
		if (i2c_data & sfp_abs[p])
			data = sfp_laser_off[p];
		else
			data = sfp_laser_on[p];

		if (i2c_data & sfp_abs[p + 1])
			data &= sfp_laser_off[p + 1];
		else
			data &= sfp_laser_on[p + 1];
	}
	i2c_data = data;
	i2c_write(sfp_addr[p], OUT_OFFSET, 1, &i2c_data, sizeof(i2c_data));
#endif
}

int apm_eth_device_setup(u8 port, u32 phy_addr, u32 phy_mode,
	      void *port_base_addr, void *gbl_base_addr, void *mii_base_addr,
	      u8 *apm_mac_addr)
{
	struct eth_device *dev;
	struct apm_enet_dev *priv_dev;
	struct apm_data_priv *priv;
	int rc = APM_RC_ERROR;

	/* Allocate device structure */
	dev = (struct eth_device *) malloc(sizeof(struct eth_device));
	if (!dev) {
		printf("Error: Failed to allocate eth_device %d\n", (int)port);
		goto _ret;
	}
	memset(dev, 0, sizeof(*dev));	

	/* Allocate device private structure */
	priv_dev = (struct apm_enet_dev *) malloc(sizeof(struct apm_enet_dev));
	if (!priv_dev) {
		printf("Error: Failed to allocate apm_enet_dev %d\n", (int)port);
		goto _ret;
	}
	memset(priv_dev, 0, sizeof(*priv_dev));
	priv = &priv_dev->priv;

	/* Initialize device function pointers */
	dev->priv = (void *) priv_dev;
	dev->send = apm_eth_tx;
	dev->recv = apm_eth_rx;
	dev->halt = apm_eth_halt;
	dev->next = NULL;
	dev->index = port;

        ENET_DEBUG("apm_eth_device_setup  MAC: %2x:%2x:%2x:%2x:%2x:%x !!!",
                   apm_mac_addr[0], apm_mac_addr[1], apm_mac_addr[2],
                   apm_mac_addr[3], apm_mac_addr[4], apm_mac_addr[5]);

#if 0	//TODO
	/* Setup the ethernet name */
	sprintf(dev->name, "eth%d", eth_count);

	if (eth_count)
		sprintf(mac_addr, "eth%daddr", eth_count);
	else
		strcpy(mac_addr, "ethaddr");
#else
	memcpy(dev->enetaddr, apm_mac_addr, 6);
#endif

#if defined(CONFIG_SGMII_STD_ALONE) && defined(CONFIG_ORION)
	priv->std_alone = (port == ENET_1 || port == ENET_3) ? 1 : 0;
#else
	priv->std_alone = 0;
#endif
#if defined(CONFIG_SGMII_MAC_TO_MAC) && defined(CONFIG_MCDIVITT)
	priv->mac_to_mac = 1;
	priv->desired_speed = 1000;
#else
	priv->mac_to_mac = 0;
	priv->desired_speed = 0;
#endif
#if defined(CONFIG_SGMII_PHYLESS) && defined(CONFIG_LYNX)
	priv->phyless = 1;
#else
	priv->phyless = 0;
#endif
#if defined(CONFIG_SGMII_FORCE_SERDES_RESET) && (defined(CONFIG_MCDIVITT) || defined(CONFIG_LYNX))
	priv->force_serdes_reset = 1;
#else
	priv->force_serdes_reset = 0;
#endif

	/* Initialize device function pointers */
	switch (port) {
#ifdef CONFIG_APM88XXXX_XGENET
	case XGENET_0:
	case XGENET_1:
	case XGENET_2:
	case XGENET_3:
		/* 10G interface is used */
		apm_xgenet_init_priv(priv, port_base_addr, gbl_base_addr, mii_base_addr);
		/* Initialize device function pointers */
		dev->init = apm_ethx_init;
		break;
#endif
	default:
		/* 1G interface is used */
		apm_enet_init_priv(priv, port_base_addr, gbl_base_addr, mii_base_addr);
		/* Initialize device function pointers */
		dev->init = apm_eth_init;
		break;
	}

	priv->phy_addr = phy_addr;
	priv->phy_mode = phy_mode;
	priv->port = port;
	apm_enet_port_reset(priv, phy_mode);

	/* Derive qm_ip & setup IP */
	switch (port) {
	case XGENET_0:
	case XGENET_1:
		priv_dev->qm_ip = IP_BLK_QM0;
		break;
	case ENET_0:
	case ENET_1:
	case ENET_2:
	case ENET_3:
		priv_dev->qm_ip = IP_BLK_QM1;
		break;
	case XGENET_2:
	case XGENET_3:
		priv_dev->qm_ip = IP_BLK_QM2;
		break;
	case MENET:
		priv_dev->qm_ip = IP_BLK_QML;
		break;
	}

	/* QM queue configuration */
	if ((rc = apm_eth_qm_init(priv_dev)) != 0) {
		printf("Error in QM configuration\n");
		goto _ret;
	}

	/* Allocate buffers in free pool */
	if ((rc = apm_eth_fp_init(priv_dev)) != APM_RC_OK) {
		printf("Error in Free Pool Configure\n");
		goto _ret;
	}

	/* Configure classifier */
#ifdef BYPASS_CLE
	apm_enet_cle_bypass(priv,
		(priv_dev->queues.rx_qid | DST_QM_IP(priv_dev->qm_ip)),
		priv_dev->queues.rx_fp_pbn-0x20);
#else
	/* Initialize preclass tree */
	if ((rc = apm_preclass_init(port, &priv_dev->queues)) != APM_RC_OK)
		goto _ret;
#endif
	/* Initialize MAC */
	apm_enet_mac_init(priv, dev->enetaddr, SPEED_1000, ENET_MAX_MTU_ALIGNED, 1);

	/* Ensure port is halted */
	apm_eth_halt(dev);

	/* Register ethernet device */
#if defined(CONFIG_NET_MULTI)
	//TODO eth_register(dev);
	emac_dev[0] = dev;
	ENET_DEBUG("apm_eth_device_setup dev=%p\n", dev);
#else
	emac0_dev = dev;
#endif

	/* Register MII PHY read/write operations */
#if defined(CONFIG_MII) || defined(CONFIG_CMD_MII)
	if (priv->phy_mode != PHY_MODE_XGMII)
		miiphy_register(dev->name, apm_eth_miiphy_read, apm_eth_miiphy_write);
#endif
	eth_port[2*eth_count] = 0x30 + port;
	rc = APM_RC_OK;

_ret:
	eth_count++;
	return rc;
}

/* Ethernet Subsystem Initialization */
#ifdef APM_XGENE /* TODO */
int apm_eth_initialize(u8 *mac_addr)
#else
int apm_eth_initialize(bd_t *bis)
#endif
{
	u8  phy_mode[MAX_ENET_PORTS];
	u32 phy_addr[MAX_ENET_PORTS];
	int i, rc = 0;
#if 0	//TODO
	char s[32], *c, *t;
	char *phymode, *phyid;
#endif
	memset(phy_mode, 0, sizeof(phy_mode));
	memset(phy_addr, 0, sizeof(phy_addr));
	memset(eth_port, 0, sizeof(eth_port));

	for (i = ENET_0; i < MAX_ENET_PORTS - 1; i++)
		eth_port[(2*i) + 1] = ':';

	/* Setup classifier */
	apm_cle_system_id = CORE_0;
	apm_cle_systems = 1;

#if 1
	/* Initialize RGMII interface */
	phy_mode[MENET] = PHY_MODE_RGMII;
#if 0	//TODO
	phyid = getenv("rgmii_phyid");
	if (phyid) {
		phy_addr[MENET] = simple_strtol(phyid, NULL, 16);
	} else {
		phy_addr[MENET] = 3;
		setenv("rgmii_phyid", "3");
	}
#else
	phy_addr[MENET] = 2;
#endif

	/* Initialize Queue Mgmt for RGMII: TBD remove two calls */
	if ((rc = apm_qm_init(IP_BLK_QML, 1)) != 0)
		return rc;

	if ((rc = apm_qm_init(IP_BLK_QML, 2)) != 0)
		return rc;

	apm_class_base_addr[CLE_LITE] = APM_CLE4_GBL_BASE_ADDR;

	if ((rc = apm_eth_device_setup(MENET, phy_addr[MENET], phy_mode[MENET],
					(void *)APM_ENET4_BASE_ADDRESS,
					(void *)APM_ENET4_GBL_BASE_ADDRESS,
					(void *)APM_ENET4_BASE_ADDRESS,
					mac_addr))) {
		return rc;
	}
#endif

#if 0
	/* Initialize SATA based SGMII interfaces  */
	/* Get modes of SATA/SGMII Port 0, 1, 2 & 3 */
	phymode = getenv("sata_enet");
	if (phymode) {
		strncpy(s, phymode, sizeof(s));
		c = s;
		t = s;

		for (i = ENET_0; i <= ENET_3; i++) {
			for (; *c != ':' && *c != '\0'; c++);

			if (*c == ':')
				*c++ = '\0';

			if (*t == 'e' || *t == 'E')
				phy_mode[i] = PHY_MODE_SGMII;

			t = c;
		}
	} else {
#if !defined(CONFIG_MCDIVITT) && !defined(CONFIG_LYNX)
		/* Set default modes of SATA/SGMII Port 0, 1, 2 & 3 */
		phy_mode[ENET_0] = PHY_MODE_SGMII;
#endif
	}

	/* Get phyid of SATA/SGMII Port 0, 1, 2 & 3 */
	phyid = getenv("sgmii_phyid");
	if (phyid) {
		strncpy(s, phyid, sizeof(s));
		c = s;
		t = s;

		for (i = ENET_0; i <= ENET_3; i++) {
			for (; *c != ':' && *c != '\0'; c++);

			if (*c == ':')
				*c++ = '\0';

			if (*t)
				phy_addr[i] = simple_strtol(t, NULL, 16);

			t = c;
		}
	} else {
		/* Set default phyid of SATA/SGMII Port 0, 1, 2 & 3 */
		phy_addr[ENET_0] = 4;
		setenv("sgmii_phyid", "4:::");
	}
#endif

#if 0	//TODO
	phy_mode[ENET_0] = PHY_MODE_SGMII;
	phy_addr[ENET_0] = 0x11;
	if ((rc = apm_qm_init(IP_BLK_QM, 1)) != 0)
		return rc;

	if ((rc = apm_qm_init(IP_BLK_QM, 2)) != 0)
		return rc;

	apm_class_base_addr[CLE_0] = APM_CLE01_GBL_BASE_ADDR;
	if (phy_mode[ENET_0] == PHY_MODE_SGMII) {
		/* Initialize Eth0 */
		if ((rc = apm_eth_device_setup(ENET_0, phy_addr[ENET_0], phy_mode[ENET_0],
						(void *)APM_ENET0_BASE_ADDRESS,
						(void *)APM_ENET01_GBL_BASE_ADDRESS,
						(void *)APM_ENET_MII_BASE_ADDRESS))) {
			return rc;
		}
	}
#endif
#if 0
	/* Initialize XFI based interfaces  */
	/* Get modes of XFI Port 0, 1, 2 & 3 */
	phymode = getenv("enet_mode");
	if (phymode) {
		strncpy(s, phymode, sizeof(s));
		c = s;
		t = s;

		for (i = XGENET_0; i <= XGENET_3; i++) {
			for (; *c != ':' && *c != '\0'; c++);

			if (*c == ':')
				*c++ = '\0';

			if (*t == 'x' || *t == 'X')
				phy_mode[i] = PHY_MODE_XGMII;
			else if (*t == 's' || *t == 'S')
				phy_mode[i] = PHY_MODE_SGMII;

			t = c;
		}
	} else {
		/* Set default modes of XFI Port 0, 1, 2 & 3 */
		phy_mode[XGENET_0] = PHY_MODE_XGMII;
		setenv("enet_mode", "x:::");
	}

	/* Get phyid of XFI Port 0, 1, 2 & 3 */
	phyid = getenv("xgmii_phyid");
	if (phyid) {
		strncpy(s, phyid, sizeof(s));
		c = s;
		t = s;

		for (i = XGENET_0; i <= XGENET_3; i++) {
			for (; *c != ':' && *c != '\0'; c++);

			if (*c == ':')
				*c++ = '\0';

			if (*t)
				phy_addr[i] = simple_strtol(t, NULL, 16);

			t = c;
		}
	} else {
		/* Set default phyid of XFI Port 0, 1, 2 & 3 */
		setenv("xgmii_phyid", ":::");
	}

	if ((rc = apm_qm_init(IP_BLK_QM0, 1)) != 0)
		return rc;

	if ((rc = apm_qm_init(IP_BLK_QM0, 2)) != 0)
		return rc;

	apm_class_base_addr[XGCLE_0] = APM_CLE_XG0_GBL_BASE_ADDR;
	if (phy_mode[XGENET_0] != PHY_MODE_NONE) {
		/* Initialize XGENET 0 */
		if ((rc = apm_eth_device_setup(XGENET_0, phy_addr[XGENET_0], 
						phy_mode[XGENET_0],
						(void *)APM_XGENET0_BASE_ADDRESS,
						(void *)APM_XGENET0_GBL_BASE_ADDRESS,
						(void *)APM_ENET_MII_BASE_ADDRESS))) {
			return rc;
		}
	if (phy_mode[XGENET_0] == PHY_MODE_XGMII)
		apm_xg_laser_on(XGENET_0);
	}

	setenv("eth_port", eth_port);
#endif
	return 0;
}

#if !defined(CONFIG_NET_MULTI)
void eth_halt(void)
{
	if (emac0_dev) {
		apm_eth_halt(emac0_dev);
		free(emac0_dev);
		emac0_dev = NULL;
	}
}

int eth_init(bd_t *bis)
{
	apm_eth_initialize(bis);
	if (emac0_dev) {
		return apm_eth_init(emac0_dev, bis);
	} else {
		printf("ERROR: ethaddr not set!\n");
		return -1;
	}
	return 0;
}

int eth_send(volatile void *packet, int length)
{
	return apm_eth_tx(emac0_dev, packet, length);
}

int eth_rx(void)
{
	return apm_eth_rx(emac0_dev);
}
#endif /* !defined(CONFIG_NET_MULTI) */
