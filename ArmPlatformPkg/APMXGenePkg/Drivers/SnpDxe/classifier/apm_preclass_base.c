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

#ifndef APM_XGENE
#include <misc/xgene/cle/apm_preclass_data.h>
#include <misc/xgene/cle/apm_preclass_base.h>
#else
//#include <stddef.h>
//#include <stdlib.h>
//#include <stdio.h>
//#include <string.h>
#include <Library/IoLib.h>
#include <Library/DebugLib.h>
#include <Library/BaseMemoryLib.h>
#define readl           MmioRead32
#define writel(v, a)    MmioWrite32((a), (v))
#include "apm_preclass_data.h"
#include "apm_preclass_base.h"
#endif

int apm_preclass_ptram_read(u32 port, u8 node_index, u32 *node_value)
{
	int i, rc = APM_RC_OK;
	u32 command_done;
	u32 counter_for_timeout = 0;
	u32 cmd;
	u32 addr;
	u32 cid = PID2CID[port];

#ifdef CLE_DEBUG
	if (node_value == NULL) {
		PCLS_DBG("Null node_value pointer \n");
		return APM_RC_INVALID_PARM;
	}
#endif

	addr = (node_index | IND_ADDR_PT_RAM);
	PCLS_DBG("node_index[%d] and addr[0X%08X] \n", node_index, addr);

	/* Write the offset in DCR address register */
	rc |= apm_gbl_cle_wr32(cid, INDADDR_ADDR, addr);

	/* Invoke read command */
	cmd = READ_F2_WR(1);
	PCLS_DBG("Starting PT Ram Read, cmd [0X%x] \n", cmd);
	rc |= apm_gbl_cle_wr32(cid, INDCMD_ADDR, cmd);

	/* Poll for command done */
	do {
		rc |= apm_gbl_cle_rd32(cid, INDCMD_STATUS_ADDR,
				       &command_done);
	} while((!(command_done & READ_DONE_MASK)) &&
		(counter_for_timeout++ < APM_CLE_ITER));

	if (counter_for_timeout > APM_CLE_ITER) {
		PCLS_ERR("Read command not done after waiting for "
			 "%d iteration \n", APM_CLE_ITER);
		return APM_RC_FATAL;
	} else {
		/* Read the ptree data in the dataram 0-15 register */
		CLE_NODE_DBG("%s: node_index[%d] \n", __func__, node_index);
		for (i = 0; i < REGS_PER_PTREE_NODE; i++) {
			rc |= apm_gbl_cle_rd32(cid, DATA_RAM0_ADDR + (i*4),
						(node_value+i));
			CLE_NODE_DBG("0X%08X ", *(node_value+i));
		}
		CLE_NODE_DBG("\n");
	}

	return rc;
}

int apm_preclass_ptram_write(u32 port, u8 node_index, u32 *node_value)
{
	int i, rc = APM_RC_OK;
	u32 command_done;
	u32 counter_for_timeout = 0;
	u32 cmd;
	u32 addr;
	u32 cid = PID2CID[port];

#ifdef CLE_DEBUG
	if (node_value == NULL) {
		PCLS_DBG("Null node_value pointer \n");
		return APM_RC_INVALID_PARM;
	}
#endif

	/* Write the offset in DCR */
	addr = (node_index | IND_ADDR_PT_RAM);
	PCLS_DBG("node_index[%d] and addr[0X%08X] \n", node_index, addr);

	rc |= apm_gbl_cle_wr32(cid, INDADDR_ADDR, addr);

	/* Write the ptree data in the dataram 0-15 register */
	CLE_NODE_DBG("%s: node_index[%d] \n", __func__, node_index);
	for (i = 0; i < REGS_PER_PTREE_NODE; i++) {
		CLE_NODE_DBG("0X%08X ", *(node_value+i));
		rc =  apm_gbl_cle_wr32(cid, DATA_RAM0_ADDR + (i*4),
					*(node_value+i));
	}
	CLE_NODE_DBG("\n");

	/* Invoke write command */
	cmd = WRITE_F2_WR(1);	
	PCLS_DBG("Starting PT Ram Write, cmd [0X%x] \n", cmd);
	rc |= apm_gbl_cle_wr32(cid, INDCMD_ADDR, cmd);

	/* Poll for command done */
	do {
		rc |= apm_gbl_cle_rd32(cid, INDCMD_STATUS_ADDR, &command_done);
	} while((!(command_done & WRITE_DONE_MASK)) && \
			(counter_for_timeout++ < APM_CLE_ITER));

	if (counter_for_timeout > APM_CLE_ITER) {
		PCLS_ERR("Write command not done after waiting for "
			 "%d iterations \n", APM_CLE_ITER);
		return APM_RC_FATAL;
	}

	return rc;
}

#ifdef PTREE_MANAGER
int apm_preclass_pktram_read(u32 port, u32 *data_hi, u32 *data_lo)
{
	int rc = APM_RC_OK;
	u32 command_done;
	u32 counter_for_timeout = 0;
	u32 cmd;
	u32 addr;
	u32 cid = PID2CID[port];

#ifdef CLE_DEBUG
	if (data_lo == NULL) {
		PCLS_DBG("Null data_lo pointer \n");
		return APM_RC_INVALID_PARM;
	}
	if (data_hi == NULL) {
		PCLS_DBG("Null data_hi pointer \n");
		return APM_RC_INVALID_PARM;
	}
#endif 

	addr = ((2 << 30) | IND_ADDR_PKT_RAM_0);
	/* Write the offset in DCR address register */
	rc |= apm_gbl_cle_wr32(cid, INDADDR_ADDR, addr);

	/* Invoke read command */
	cmd = READ_F2_WR(1);
	PCLS_DBG("Starting PACKET Ram Read, cmd [0X%x] \n", cmd);
	rc |= apm_gbl_cle_wr32(cid, INDCMD_ADDR, cmd);

	/* Poll for command done */
	do {
		rc |= apm_gbl_cle_rd32(cid, INDCMD_STATUS_ADDR, &command_done);
	} while((!(command_done & READ_DONE_MASK)) && \
				(counter_for_timeout++ < APM_CLE_ITER));

	if (counter_for_timeout > APM_CLE_ITER) {
		PCLS_ERR("Read command not done after waiting for "
			 "%d iterations \n", APM_CLE_ITER);
		return APM_RC_FATAL;
	} else {
		
		rc |= apm_gbl_cle_rd32(cid, DATA_RAM15_ADDR, data_lo);
	}
	return rc;
}

int apm_preclass_pktram_write(u32 port, u32 data_hi, u32 data_lo)
{
	int rc = APM_RC_OK;
	u32 command_done;
	u32 counter_for_timeout = 0;
	u32 cmd;
	u32 addr;
	u32 cid = PID2CID[port];

	/* Write the offset in DCR address register */
	addr = ((2 << 30) | IND_ADDR_PKT_RAM_0);
	rc |= apm_gbl_cle_wr32(cid, INDADDR_ADDR, addr);
	
	rc |= apm_gbl_cle_wr32(cid, DATA_RAM15_ADDR, data_lo);

	/* Invoke write command */
	cmd = WRITE_F2_WR(1);	
	PCLS_DBG("Starting PACKET Ram Write, cmd [0X%x] \n", cmd);
	rc |= apm_gbl_cle_wr32(cid, INDCMD_ADDR, cmd);

	/* Poll for command done */
	do {
		rc |= apm_gbl_cle_rd32(cid, INDCMD_STATUS_ADDR, &command_done);
	} while((!(command_done & WRITE_DONE_MASK)) && \
				(counter_for_timeout++ < APM_CLE_ITER));

	if (counter_for_timeout > APM_CLE_ITER) {
		PCLS_ERR("Write command not done after waiting for "
			 "%d iterations \n", APM_CLE_ITER);
		return APM_RC_FATAL;
	}
	return (rc);
}

int apm_preclass_cldb_read(u32 port, u16 db_index, u32 *data)
{
	int i, rc = APM_RC_OK;
	u32 command_done = 0;
	u32 counter_for_timeout = 0;
	u32 cmd = 0;
	u32 addr = 0;
	u32 cid = PID2CID[port];

#ifdef CLE_DEBUG
	if (data == NULL) {
		PCLS_DBG("Null data pointer \n");
		return APM_RC_INVALID_PARM;
	}
#endif 
	
	/* Write the offset in DCR address register */
	addr = (db_index | IND_ADDR_DB_RAM);
	rc |= apm_gbl_cle_wr32(cid, INDADDR_ADDR, addr);
	
	/* Invoke read command */
	cmd = READ_F2_WR(1);
	PCLS_DBG("Starting DB Ram Read, cmd [0X%x] \n", cmd);
	rc |= apm_gbl_cle_wr32(cid, INDCMD_ADDR, cmd);
	
	/* Poll for command done */
	do {
		rc |= apm_gbl_cle_rd32(cid, INDCMD_STATUS_ADDR, &command_done);
	} while((!(command_done & READ_DONE_MASK)) &&
		(counter_for_timeout++ < APM_CLE_ITER));
	
	if (counter_for_timeout > APM_CLE_ITER) {
		PCLS_ERR("Read command not done after waiting for "
			"%d iterations \n", APM_CLE_ITER);
		return APM_RC_FATAL;
	} else {
		/* Read the DB entry [172:0] in the data ram 0-5 register */
		CLE_NODE_DBG("%s: db_index[%d] \n", __func__, db_index);
		for (i = 0; i < REGS_PER_DB; i++) {
			rc |= apm_gbl_cle_rd32(cid, (DATA_RAM5_ADDR - (i * 4)),
						(data + i));
			CLE_NODE_DBG("0X%08X ", *(data+i));
		}
		CLE_NODE_DBG("\n");
	}
	return (rc);
}
#endif

int apm_preclass_cldb_write(u32 port, u16 db_index, u32 *data)
{
	int i, rc = APM_RC_OK;
	u32 command_done = 0;
	u32 counter_for_timeout = 0;
	u32 cmd = 0;
	u32 addr = 0;	
	u32 cid = PID2CID[port];

	/* Write the offset in DCR address register */
	addr = (db_index | IND_ADDR_DB_RAM);
	rc |= apm_gbl_cle_wr32(cid, INDADDR_ADDR, addr);

	/* Write the DB entry [172:0] in the data ram 0-5 register */
	CLE_NODE_DBG("%s: node_index[%d] \n", __func__, db_index);
	for (i = 0; i < REGS_PER_DB; i++) {
		CLE_NODE_DBG("0X%08X ", *(data+i));
		rc |= apm_gbl_cle_wr32(cid, (DATA_RAM0_ADDR + (i * 4)),
					*(data + i));
	}
	CLE_NODE_DBG("\n");

	/* Invoke write command */
	cmd = WRITE_F2_WR(1);
	PCLS_DBG("Starting DB Ram Write, cmd [0X%x] \n", cmd);
	rc |= apm_gbl_cle_wr32(cid, INDCMD_ADDR, cmd);

	/* Poll for command done */
	do {
		rc |= apm_gbl_cle_rd32(cid, INDCMD_STATUS_ADDR, &command_done);
	} while((!(command_done & WRITE_DONE_MASK)) &&
		(counter_for_timeout++ < APM_CLE_ITER));

	if (counter_for_timeout > APM_CLE_ITER) {
		PCLS_ERR("Write command not done after waiting for"
			"%d iterations \n", APM_CLE_ITER);
		return APM_RC_FATAL;
	}
	return (rc);
}
