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
#include <asm/io.h>
#include <misc/xgene/qm/apm_qm_core.h>
#include <misc/xgene/qm/apm_qm_csr.h>
#ifdef CONFIG_ARCH_MSLIM
#include <asm/hardware/mslim-iof-map.h>
#endif
#else	/* UEFI */
//#include <Library/DebugLib.h>
//#include <Library/BaseMemoryLib.h>


#undef SIZE_2KB
#undef SIZE_16KB
#undef SIZE_64KB
#undef SIZE_512KB

#include "apm_qm_core.h"
#include "apm_qm_csr.h"

#define QM_INFO
#ifdef QM_INFO
#define info(arg...) DEBUG ((EFI_D_INFO,## arg))
#else
#define info(arg...)
#endif

#if 0
#undef QM_PRINT
#define QM_PRINT info
#undef QMCORE_PRINT
#define QMCORE_PRINT info
#endif
#endif

struct qm_core_info {
	u8 is_smp;
	u8 is_noqml;
} qm_cinfo;

/* global queue configuration table */
extern struct apm_qm_qstate mb_cfg_pqs[];

#ifdef CONFIG_APM_QM_QUEUE_LOCATION
static u64   mem_paddr = QM_QUEUE_PADDR;
static void *mem_vaddr = (void *)QM_QUEUE_VADDR;
#endif
static u32 ip_to_slave_id[IP_MAX];		/* IP block to slave ID mapping */
static u32 qml_cpu_pbn_qnum = 0xffffffff;

int apm_qm_is_pbn_valid(u32 qm_ip, u32 qid)
{
	return QM_DEV(qm_ip)pbn_valid[qid];
}

void apm_qm_clr_pbn_valid(u32 qm_ip, u32 qid)
{
	QM_DEV(qm_ip)pbn_valid[qid] = 0;
}

int apm_qm_mb2qid(u32 qm_ip, u32 mb)
{
	return QM_DEV(qm_ip)mb_to_q[mb];
}

int apm_qm_qid2mb(u32 qm_ip, u32 qid)
{
	return QM_DEV(qm_ip)q_to_mb[qid];
}

void apm_qm_set_qid(u32 qm_ip, u32 fqid, u32 sqid, u32 maxqid, u32 maxclrqid)
{
	QM_DEV(qm_ip)first_qid = fqid;
	QM_DEV(qm_ip)start_qid = sqid;
	QM_DEV(qm_ip)max_qid = maxqid;
	QM_DEV(qm_ip)max_clr_qid = maxclrqid;
}

u32 apm_qm_get_max_qid(u32 qm_ip)
{
	return QM_DEV(qm_ip)max_qid;
}

u32 apm_qm_get_max_clr_qid(u32 qm_ip)
{
	return QM_DEV(qm_ip)max_clr_qid;
}

u32 apm_qm_get_first_qid(u32 qm_ip)
{
	return QM_DEV(qm_ip)first_qid;
}

u32 apm_qm_get_start_qid(u32 qm_ip)
{
	return QM_DEV(qm_ip)start_qid;
}

void apm_qm_set_mboxes(u32 qm_ip, u32 maxboxes, u32 startboxes)
{
	QM_DEV(qm_ip)max_mboxes = maxboxes;
	QM_DEV(qm_ip)start_mboxes = startboxes;
}

u32 apm_qm_get_max_mboxes(u32 qm_ip)
{
	return QM_DEV(qm_ip)max_mboxes;
}

u32 apm_qm_get_start_mboxes(u32 qm_ip)
{
	return QM_DEV(qm_ip)start_mboxes;
}

void apm_qm_set_smp(u8 is_smp)
{
	qm_cinfo.is_smp = is_smp;
}

u8 apm_qm_get_smp(void)
{
	return qm_cinfo.is_smp;
}

void apm_qm_set_noqml(u8 is_noqml)
{
	qm_cinfo.is_noqml = is_noqml;
}

u8 apm_qm_get_noqml(void)
{
	return qm_cinfo.is_noqml;
}

void apm_qml_cpu_pbn_qnum(u32 qnum)
{
	if (qml_cpu_pbn_qnum == 0xffffffff) {
		apm_qm_wr32(IP_BLK_QML, CSR_QM_MBOX_NE_INT_MODE_ADDR,
			MBOX_0_NOT_EMPTY_MASK);
		qml_cpu_pbn_qnum = qnum;
		QM_DEV(IP_BLK_QML)mb_to_q[0] = qnum;
		QM_DBG("Configuring QML CPU PBN 0 for QID %d\n", qnum);
	}
}

void apm_qml_free_cpu_pbn_qnum(u32 qnum)
{
	if (qml_cpu_pbn_qnum != 0xffffffff) {
		apm_qm_wr32(IP_BLK_QML, CSR_QM_MBOX_NE_INT_MODE_ADDR,
			CSR_QM_MBOX_NE_INT_MODE_DEFAULT);
		qml_cpu_pbn_qnum = 0xffffffff;
		QM_DEV(IP_BLK_QML)mb_to_q[0] = 0;
		QM_DBG("Freeing QML CPU PBN 0 for QID %d\n", qnum);
	}
}

static int __apm_qm_dp_enabled(void)
{
	/*return apm88xxxx_is_dp_mode();*/
	return 0;
}

static int __apm_qm_pb_cmd(u32 qm_ip, u32 pbm_addr, u32 *buf, int read)
{	
	int rc = 0;

	if (qm_ip == IP_BLK_QML) {
		u32 slv_id = SLVID_PBN_RD(pbm_addr) >> SLAVE_ID_SHIFT;
		u32 pbn = SLVID_PBN_RD(pbm_addr) & 0x03F;

		if (slv_id == PB_SLAVE_ID_CPU && pbn != 0) {
			QM_DBG("Skipping __apm_qm_pb_cmd for qm_ip=IP_BLK_QML "
				"& slv_id=PB_SLAVE_ID_CPU & pbn=%d\n", pbn);
			return 0;
		}
	}

	if (!__apm_qm_dp_enabled()) {
		u32 overwrite = pbm_addr & 0x80000000;
		apm_qm_wr32(qm_ip, CSR_PBM_ADDR, pbm_addr & ~0x80000000);
		QMCORE_PRINT("Write addr 0x%08x data 0x%08x\n", CSR_PBM_ADDR, pbm_addr & ~0x80000000);
		apm_qm_rd32(qm_ip, CSR_PBM_ADDR, &pbm_addr); /* Force barrier */
		QMCORE_PRINT("Read  addr 0x%08x data 0x%08x\n", CSR_PBM_ADDR, pbm_addr);
		if (read) {
			apm_qm_rd32(qm_ip, CSR_PBM_BUF_RD_ADDR, buf);
			QMCORE_PRINT("Read  addr 0x%08x data 0x%08x\n", CSR_PBM_BUF_RD_ADDR, *buf);
		} else {
			if (overwrite) {
				apm_qm_wr32(qm_ip, CSR_PBM_ADDR, pbm_addr | 0x80000000);
				QMCORE_PRINT("Write addr 0x%08x data 0x%08x\n", CSR_PBM_ADDR, pbm_addr | 0x80000000);
			}
			if (qm_ip == IP_BLK_QM0 || qm_ip == IP_BLK_QM2)
				*buf |= 0x80000000;
			apm_qm_wr32(qm_ip, CSR_PBM_BUF_WR_ADDR, *buf);
			QMCORE_PRINT("Write addr 0x%08x data 0x%08x\n", CSR_PBM_BUF_WR_ADDR, *buf);
		}
#if 0
	} else {
		/* Read/Write via SlimPRO interface */
		rc = apm88xxxx_dp_qm(IPP_DP_CMD_QM_PB, IPP_DP_RES_QM, read, 
			pbm_addr, buf);
		if (rc != 0) {
			QM_DBG("QM PB cmd failed error %d\n", rc);
#if defined(DQM_DBG)
		} else {
			if (!read) {
				u32 tmp;
				rc = apm88xxxx_dp_qm(IPP_DP_CMD_QM_PB, IPP_DP_RES_QM, 
					1, pbm_addr, &tmp);
				if (rc != 0)
					QM_DBG("QM PB cmd failed error %d\n", rc);
				else if ((tmp & 0x3FFFF) != (*buf & 0x3FFFF))
					QM_DBG("QM PB cmd failed data mismatch "
						"0x%08X != 0x%08X\n", *buf, tmp);				
			}
#endif
		}
#endif
	}
	return rc;
}

static int __apm_qm_qstate_cmd(u32 qm_ip, u32 qid, struct apm_qm_raw_qstate *buf, int read)
{
	int rc = 0;

	if (!__apm_qm_dp_enabled()) {
		apm_qm_wr32(qm_ip, CSR_QSTATE_ADDR, qid);
		apm_qm_rd32(qm_ip, CSR_QSTATE_ADDR, &qid); /* Force barrier */
		if (!read) {
			apm_qm_wr32(qm_ip, CSR_QSTATE_WR_0_ADDR, buf->w0);
			apm_qm_wr32(qm_ip, CSR_QSTATE_WR_1_ADDR, buf->w1);
			apm_qm_wr32(qm_ip, CSR_QSTATE_WR_2_ADDR, buf->w2);
			apm_qm_wr32(qm_ip, CSR_QSTATE_WR_3_ADDR, buf->w3);
			apm_qm_wr32(qm_ip, CSR_QSTATE_WR_4_ADDR, buf->w4);
		}
		apm_qm_rd32(qm_ip, CSR_QSTATE_RD_0_ADDR, &buf->w0);
		apm_qm_rd32(qm_ip, CSR_QSTATE_RD_1_ADDR, &buf->w1); 
		apm_qm_rd32(qm_ip, CSR_QSTATE_RD_2_ADDR, &buf->w2); 
		apm_qm_rd32(qm_ip, CSR_QSTATE_RD_3_ADDR, &buf->w3); 
		apm_qm_rd32(qm_ip, CSR_QSTATE_RD_4_ADDR, &buf->w4); 
#if 0
	} else {
		/* Read/Write via SlimPRO interface */
		QM_DBG("QM QState %s QID %d\n", read ? "RD" : "WR", qid);
		rc = apm88xxxx_dp_qm(IPP_DP_CMD_QM_QSTATE, IPP_DP_RES_QM, read, 
			qid, (u32 *)buf);
		if (rc != 0) {
			QM_DBG("QM QState cmd failed error %d\n", rc);
#if defined(DQM_DBG)
		} else {
			if (!read) {
				u32 tmp[5];
				rc = apm88xxxx_dp_qm(IPP_DP_CMD_QM_QSTATE, 
					IPP_DP_RES_QM, 1, qid, tmp);
				if (rc != 0) {
					QM_DBG("QM QState cmd failed error %d\n", rc);
				} else if (memcmp(tmp, (u32 *)buf, 5*4) != 0) {
					QM_DBG("QM QState cmd failed data mismatch\n");				
				}
			}
#endif
		}
#endif
	}

	return rc;
}

static int __apm_qm_cstate_cmd(u32 qm_ip, u32 qid, u32 *buf, int read)
{
	int rc = 0;

	if (!__apm_qm_dp_enabled()) {
		apm_qm_wr32(qm_ip, CSR_QSTATE_ADDR, qid);
		apm_qm_rd32(qm_ip, CSR_QSTATE_ADDR, &qid); /* Force barrier */
		if (!read) {
			apm_qm_wr32(qm_ip, CSR_CSTATE_WR_0_ADDR, buf[0]);
			apm_qm_wr32(qm_ip, CSR_CSTATE_WR_1_ADDR, buf[1]);
		}
		apm_qm_rd32(qm_ip, CSR_CSTATE_RD_0_ADDR, &buf[0]);
		apm_qm_rd32(qm_ip, CSR_CSTATE_RD_1_ADDR, &buf[1]); 
#if 0
	} else {
		/* Read/Write via SlimPRO interface */
		rc = apm88xxxx_dp_qm(IPP_DP_CMD_QM_CSTATE, IPP_DP_RES_QM, read,
			qid, buf);
		if (rc != 0) {
			QM_DBG("QM CState cmd failed error %d\n", rc);
		} else {
#if defined(DQM_DBG)
			if (!read) {
				u32 tmp[2];
				rc = apm88xxxx_dp_qm(IPP_DP_CMD_QM_CSTATE, 
					IPP_DP_RES_QM, 1, qid, tmp);
				if (rc != 0)
					QM_DBG("QM CState cmd failed error %d\n", rc);
				else if (memcmp(tmp, buf, 2*4) != 0)
					QM_DBG("QM CState cmd failed data mismatch\n");				
			}
#endif
		}
#endif
	}
	return rc;
}

u32 apm_qm_pb_get(u32 qm_ip, u32 slv_id, u32 pbn)
{
	u32 pbn_buf = 0;
	u32 val = (slv_id << SLAVE_ID_SHIFT) | pbn;

	apm_qm_indirect_access_lock(1);
	__apm_qm_pb_cmd(qm_ip, val, &pbn_buf, 1);
	apm_qm_indirect_access_lock(0);
	QM_DBG("PBN RD Addr: 0x%08X val: 0x%08X\n", val, pbn_buf);

	return pbn_buf;
}

u32 apm_qm_pb_set(u32 qm_ip, u32 slv_id, u32 pbn, u32 pbn_buf)
{
	u32 val = (slv_id << SLAVE_ID_SHIFT) | pbn;

	if (qm_ip == IP_BLK_QML && slv_id == PB_SLAVE_ID_CPU) {
		u32 qnum = CORRESPONDING_QNUM_RD(pbn_buf);

		if (pbn != 0 || qnum != qml_cpu_pbn_qnum) {
			QM_DBG("Skipping set for IP_BLK_QML "
				"slv_id = PB_SLAVE_ID_CPU pbn = %d "
				"qnum = %d\n", /*__func__, */ pbn, qnum);
			return 0;
		}
	}

	QM_DBG("PBN WR Addr: 0x%08X val: 0x%08X\n", val, pbn_buf);
	apm_qm_indirect_access_lock(1);
	__apm_qm_pb_cmd(qm_ip, val, &pbn_buf, 0);
	apm_qm_indirect_access_lock(0);

	return pbn_buf;
}

int apm_qm_pb_disable(u32 qm_ip, u32 slv_id, u32 pbn, u32 qnum)
{
	u32 pbn_buf = 0;
	u32 val = (1 << 31) | (slv_id << SLAVE_ID_SHIFT) | pbn;

	if (qm_ip == IP_BLK_QML && slv_id == PB_SLAVE_ID_CPU) {
		if (pbn != 0 || qnum != qml_cpu_pbn_qnum) {
			QM_DBG("Skipping disable for IP_BLK_QML "
				"slv_id = PB_SLAVE_ID_CPU pbn = %d "
				"qnum = %d\n", /*__func__, */ pbn, qnum);
			return 0;
		}
	}

	QM_DBG("PBN WR Addr: 0x%08X val: %x\n", val, pbn_buf);
	apm_qm_indirect_access_lock(1);
	__apm_qm_pb_cmd(qm_ip, val, &pbn_buf, 0);
	apm_qm_indirect_access_lock(0);
	QM_DEV(qm_ip)pbn_valid[qnum] = 0;

	return 0;
}

int apm_qm_pb_clr(u32 qm_ip, u32 slv_id, u32 pbn)
{
	u32 val = (slv_id << SLAVE_ID_SHIFT) | pbn;
	u32 pbn_val;
	int enabled;

	if (qm_ip == IP_BLK_QML && slv_id == PB_SLAVE_ID_CPU && pbn != 0) {
		QM_DBG("Skipping clr for IP_BLK_QML "
			"slv_id = PB_SLAVE_ID_CPU pbn = %d\n",
			/*__func__, */ pbn);
		return 0;
	}

	apm_qm_indirect_access_lock(1);
	__apm_qm_pb_cmd(qm_ip, val, &pbn_val, 1);
	/* Check if clear required? */
	if (!(pbn_val & (0x0000000F | 0x00038000))) {
		apm_qm_indirect_access_lock(0);
		return 0;
	}
	/* Disable first */
	enabled = pbn_val & (1 << 21);
	pbn_val &= ~(1 << 21);
	__apm_qm_pb_cmd(qm_ip, val, &pbn_val, 0);
	/* Clear it out next */
	val |= (1 << 31);
	pbn_val &= ~0x0000000F;	/* Clear num msgs in buffer */
	pbn_val &= ~0x00038000;	/* Clear slot number */
	__apm_qm_pb_cmd(qm_ip, val, &pbn_val, 0);
	/* Re-enable it */
	if (enabled) {
		pbn_val |= (1 << 21);
		__apm_qm_pb_cmd(qm_ip, val, &pbn_val, 0);
	}
	QM_DBG("PBN WR Addr: 0x%08X val: %x\n", val, pbn_val);
	apm_qm_indirect_access_lock(0);
	return 0;
}

int apm_qm_pb_overwrite(u32 qm_ip, u32 slv_id, u32 pbn, u32 qnum, u8 is_fp)
{
	u32 pbn_buf = 0;
	u32 val = (1 << 31) | (slv_id << SLAVE_ID_SHIFT) | pbn;

	if (qm_ip == IP_BLK_QML && slv_id == PB_SLAVE_ID_CPU) {
		if (pbn != 0 || qnum != qml_cpu_pbn_qnum) {
			QM_DBG("Skipping overwrite for IP_BLK_QML "
				"slv_id = PB_SLAVE_ID_CPU pbn = %d "
				"qnum = %d\n", /*__func__, */ pbn, qnum);
			return 0;
		}
	}

	pbn_buf |= ((qnum << 9) | (is_fp << 20) | (1 << 21) | 0x4);
	QM_DBG("PBN WR Addr: 0x%08X val: 0x%08X\n", val, pbn_buf);
	apm_qm_indirect_access_lock(1);
	__apm_qm_pb_cmd(qm_ip, val, &pbn_buf, 0);
	apm_qm_indirect_access_lock(0);
	QM_DEV(qm_ip)pbn_valid[qnum] = 1;

	return 0;
}

int apm_qm_pb_config(u32 qm_ip, u32 slv_id, u32 pbn, u32 qnum, u8 is_fp, u8 is_vq)
{
	u32 pbn_buf = 0;
	u32 val = (slv_id << SLAVE_ID_SHIFT) | pbn;

	if (qm_ip == IP_BLK_QML && slv_id == PB_SLAVE_ID_CPU) {
		if (pbn != 0 || qnum != qml_cpu_pbn_qnum) {
			QM_DBG("Skipping config for IP_BLK_QML "
				"slv_id = PB_SLAVE_ID_CPU pbn = %d "
				"qnum = %d\n", /*__func__, */ pbn, qnum);
			return 0;
		}
	}

	pbn_buf |= ((qnum << 9) | (is_fp << 20) | (is_vq << 19) | (1 << 21));
	QM_DBG("Configure PBN WR Addr: 0x%08X val: 0x%08X\n", val, pbn_buf);
	apm_qm_indirect_access_lock(1);
	__apm_qm_pb_cmd(qm_ip, val, &pbn_buf, 0);
	apm_qm_indirect_access_lock(0);
	QM_DEV(qm_ip)pbn_valid[qnum] = 1;
	return 0;
}

int apm_qm_pb_cfg_rd(u32 qm_ip, u32 slv_id, u32 pbn, u32 *pbn_val)
{
	u32 val = (slv_id << SLAVE_ID_SHIFT) | pbn;

	apm_qm_indirect_access_lock(1);
	__apm_qm_pb_cmd(qm_ip, val, pbn_val, 1);
	apm_qm_indirect_access_lock(0);
	QM_DBG("Configure PBN RD Addr: 0x%08X val: 0x%08X\n", val, *pbn_val);

	return 0;
}

int apm_qm_enq_stats_setqid(u32 qm_ip, u32 qid)
{
	u32 val = 0x0;

	apm_qm_rd32(qm_ip, CSR_QM_STATS_CFG_ADDR, &val);
	val = QID_ENQ_COUNTER_SET(val, qid);
	if (!__apm_qm_dp_enabled())
		apm_qm_wr32(qm_ip, CSR_QM_STATS_CFG_ADDR, val);
#if 0
	else    /* Write via SlimPRO interface */
		apm88xxxx_dp_cfg(IPP_DP_CMD_REG_WR, IPP_DP_RES_QM, 0, 
			CSR_QM_STATS_CFG_ADDR, val);
#endif
	return 0;
}

u32 apm_qm_enq_stats_getqid(u32 qm_ip)
{
	u32 val = 0x0;
	apm_qm_rd32(qm_ip, CSR_QM_STATS_CFG_ADDR, &val);
	return QID_ENQ_COUNTER_RD(val);
}

u32 apm_qm_enq_stats_value(u32 qm_ip)
{
	u32 val = 0x0;

	apm_qm_rd32(qm_ip, CSR_ENQ_STATISTICS_ADDR, &val);
	return val;
}

int apm_qm_deq_stats_setqid(u32 qm_ip, u32 qid)
{
	u32 val = 0x0;

	apm_qm_rd32(qm_ip, CSR_QM_STATS_CFG_ADDR, &val);
	val = QID_DEQ_COUNTER_SET(val, qid);
	if (!__apm_qm_dp_enabled())
		apm_qm_wr32(qm_ip, CSR_QM_STATS_CFG_ADDR, val);
#if 0
	else    /* Write via SlimPRO interface */
		apm88xxxx_dp_cfg(IPP_DP_CMD_REG_WR, IPP_DP_RES_QM, 0, 
			CSR_QM_STATS_CFG_ADDR, val);	
#endif
	return 0;
}

u32 apm_qm_deq_stats_getqid(u32 qm_ip)
{
	u32 val = 0x0;

	apm_qm_rd32(qm_ip, CSR_QM_STATS_CFG_ADDR, &val);
	return QID_DEQ_COUNTER_RD(val);
}

u32 apm_qm_deq_stats_value(u32 qm_ip)
{
	u32 val = 0x0;

	apm_qm_rd32(qm_ip, CSR_DEQ_STATISTICS_ADDR, &val);
	return val;
}

int apm_qm_raw_qstate_rd(u32 qm_ip, u32 q_num, struct apm_qm_raw_qstate *raw_q)
{
	int rc = 0;
	u32 queue_id = 0;

	if (q_num < 0 || q_num > 255) {
		QM_PRINT("Queue number is not valid\n");
		return -1;
	}

	queue_id = QNUMBER_SET(queue_id, q_num);
	apm_qm_indirect_access_lock(1);
	__apm_qm_qstate_cmd(qm_ip, queue_id, raw_q, 1);
	QM_STATE_DBG("QState RD QID %d 0x%08X 0x%08X 0x%08X 0x%08X 0x%08X\n",
		queue_id, 
		raw_q->w0, raw_q->w1, raw_q->w2, raw_q->w3, raw_q->w4);
	apm_qm_indirect_access_lock(0);

	return rc;
}

int apm_qm_get_qstate_msgcnt(u32 qm_ip, u32 qid, u32 *count)
{
	u32 qaddr;
	struct apm_qm_raw_qstate val;

	qaddr = QNUMBER_WR(qid);
	apm_qm_indirect_access_lock(1);
	__apm_qm_qstate_cmd(qm_ip, qaddr, &val, 1);
	apm_qm_indirect_access_lock(0);
	*count = val.w3 & 0xFFFF;
	return 0;
}

int apm_qm_qstate_rd_cfg(u32 qm_ip, u32 q_num, struct apm_qm_qstate *qstate)
{
	if (q_num < 0 || q_num > QM_MAX_QUEUES)
		return -1;

	memcpy(qstate, &QM_DEV(qm_ip)queue_states[q_num], sizeof (struct apm_qm_qstate));	
	return 0;
}

int apm_qm_qstate_rd(u32 qm_ip, u32 q_num, struct apm_qm_qstate *qstate)
{
	int rc = 0;
	struct apm_qm_pqstate pq;
	struct apm_qm_qstate *q_sw_state = &QM_DEV(qm_ip)queue_states[q_num];

	if ((!q_sw_state->valid) || (q_sw_state->q_type == QUEUE_DISABLED)) {
		QM_PRINT("Queue config is not valid\n");
		return -1;
	}

	if (q_num < 0 || q_num > 255) {
		QM_PRINT("Queue number is not valid\n");
		return -1;
	}

	rc = apm_qm_raw_qstate_rd(qm_ip, q_num, (struct apm_qm_raw_qstate *) &pq);
	if (rc) {
		return rc;
	}

	/* fill info from sw state */
	memcpy(qstate, q_sw_state, sizeof (struct apm_qm_qstate));	
	
	if (qm_ip == IP_BLK_QML &&
			q_sw_state->slave_id == PB_SLAVE_ID_CPU &&
			q_sw_state->qml_cpu_pbn_cfg) {
		qstate->qml_cpu_pbn_cfg = q_sw_state->qml_cpu_pbn_cfg;
	} else {
		qstate->qml_cpu_pbn_cfg = 0;
	}

	/* fill infor from hw state */
	qstate->q_type = pq.cfgqtype; 
	qstate->thr_set = pq.cfgselthrsh; 
	qstate->fp_mode = pq.fp_mode; 
	qstate->q_size = pq.cfgqsize;
	qstate->q_start_addr = pq.cfgstartaddr;
	qstate->nummsgs = pq.nummsg;
	qstate->rid = pq.rid;
	qstate->cfgsaben = pq.cfgsaben;
	qstate->cpu_notify = pq.cpu_notify;
	qstate->dma_nummsgs = (readl((UINTN)&qstate->dma->w1) & 0x1fffe) >> 1;

	return rc;
}

int apm_qm_raw_qstate_wr(u32 qm_blk_id, u32 q_num,
		struct apm_qm_raw_qstate *raw_q)
{
	u32 queue_id = 0;

	if (q_num < 0 || q_num > 255) {
		QM_PRINT("Queue ID %d not valid in cfg write\n", q_num);
		return -1;
	}

	/* write queue number */
	queue_id = QNUMBER_SET(queue_id, q_num);
	apm_qm_indirect_access_lock(1);
	__apm_qm_qstate_cmd(qm_blk_id, queue_id, raw_q, 0);
	QM_STATE_DBG("QState WR QID %d 0x%08X 0x%08X 0x%08X 0x%08X 0x%08X\n", 
		queue_id, 
		raw_q->w0, raw_q->w1, raw_q->w2, raw_q->w3, raw_q->w4);
	apm_qm_indirect_access_lock(0);

	return 0;
}

int apm_qm_cpu2domain(void)
{
	int cpuid = 0;

	switch (cpuid) {
	case 0:
	default:
		return 0x02;
	case 1:
		return 0x03;
	}
}

int apm_qm_cpu2domain_allowed(void)
{
	int cpuid = 0;

	switch (cpuid) {
	case 0:
	default:
		return 0x04;
	case 1:
		return 0x08;
	}
}


int apm_qm_delete_queue(u32 qm_ip, u32 qnum)
{
	int rc=0;
	struct apm_qm_raw_qstate pq;

	if (qnum < 0 || qnum > QM_MAX_QUEUES-1) {
		QM_PRINT("Queue number not valid in delete queue: 0x%x\n", qnum);
		rc = -1;
		goto _ret;
	}

	if (qm_ip < IP_BLK_QM0 || qm_ip > IP_BLK_QML) {
		QM_PRINT("Invalid Block ID in cfg write: %d\n", qm_ip);
		rc = -1;
		goto _ret;
	}

	if (QM_DEV(qm_ip)queue_states[qnum].valid) {
#ifndef CONFIG_APM_QM_QUEUE_LOCATION
		/* free qaddr */
		MEMFREE((void *)QM_DEV(qm_ip)queue_states[qnum].startptr);
#endif
		apm_qm_free_q(&QM_DEV(qm_ip)queue_states[qnum]);

		/* invalidate qstate */
#if !defined(BOOTLOADER)
	       	memset(&QM_DEV(qm_ip)q_raw_states[qnum], 0, sizeof(struct apm_qm_raw_qstate));
#endif
	       	memset(&QM_DEV(qm_ip)queue_states[qnum], 0, sizeof(struct apm_qm_qstate));

		/* delete queue in hardware */
		memset(&pq, 0, sizeof(pq));
		rc = apm_qm_raw_qstate_wr(qm_ip, qnum, &pq);
	}

_ret:
	return rc;
}



int apm_qm_qstate_wr(struct apm_qm_qstate *qstate)
{
	struct apm_qm_pqstate pq;
	int rc = 0;
	u8 *qaddr = NULL;
	u32 q_size = 0;
	u64 qaddr_phy;
	u32 mem_size;
	int q_num = qstate->q_id;
	u32 qm_ip = qstate->ip_blk;

	memset(&pq, 0, sizeof(pq));

	if (q_num < 0 || q_num > 255) {
		QM_PRINT("Queue number not valid in cfg write: 0x%x\n", q_num);
		return -1;
	}

	if ((!qstate->valid) || (qstate->q_type == QUEUE_DISABLED)) {
		QM_PRINT("Queue config not valid in cfg write\n");
		return -1;
	}

	if (qm_ip < IP_BLK_QM0 || qm_ip > IP_BLK_QML) {
		QM_PRINT("Invalid Block ID in cfg write: %d\n", qm_ip);
		return -1;
	}

	if (qm_ip != IP_BLK_QML) {
		if (qstate->direction) { /* egress direction */
			QM_DBG("For QM_IP %d using MB %d PBN %d queue %d IP %d slave %d "
				"in EGRESS\n", 
				qm_ip, qstate->mb_id, qstate->pbn, q_num, 
				qstate->src_ip_blk, qstate->slave_id);
			QM_DEV(qm_ip)q_to_mb[q_num] = qstate->mb_id;
		} else if (qstate->slave_id == PB_SLAVE_ID_CPU && 
			   qstate->q_type == FREE_POOL) {
			QM_DBG("For QM_IP %d using MB %d PBN %d queue %d IP %d slave %d "
				"in Free Pool CPU\n", 
				qm_ip, qstate->mb_id, qstate->pbn, q_num,
				qstate->src_ip_blk, qstate->slave_id);
			QM_DEV(qm_ip)q_to_mb[q_num] = qstate->mb_id;
			QM_DEV(qm_ip)mb_to_q[qstate->mb_id] = q_num;
		} else {
			QM_DBG("For QM_IP %d using MB %d PBN %d queue %d IP %d slave %d "
				"in INGRESS\n", 
				qm_ip, qstate->mb_id, qstate->pbn, q_num,
				qstate->src_ip_blk, qstate->slave_id);
			if (qstate->vqen == ENABLE_VQ) {
				QM_DEV(qm_ip)mb_to_q[qstate->mb_id] = qstate->parent_vqid;
			} else {
				QM_DEV(qm_ip)mb_to_q[qstate->mb_id] = q_num;
			}
		}
	}

#if 0
	/* Configure domain protection field */
	if (__apm_qm_dp_enabled()) {
		pq.queue_dom = apm_qm_cpu2domain();
		pq.allowed_dom = apm_qm_cpu2domain_allowed();
		pq.not_insert_dom = 0;
	} else {
		pq.queue_dom = 0x0;
		pq.allowed_dom = 0xF;
		pq.not_insert_dom = 0x1;
	}
#endif
#ifdef QM_RECOMBINATION_BUFFER
	if (qstate->src_ip_blk >= IP_XGE0 && qstate->src_ip_blk <= IP_XGE3) {
		pq.cfgRecombBuf = 1;
		pq.cfgRecombBufTimeout = 0x7f;
	}
#endif
	pq.cfgqtype = qstate->q_type;
	pq.cfgselthrsh = qstate->thr_set;
	pq.cfgqsize = qstate->q_size; 
	pq.fp_mode = qstate->fp_mode;
	/* Ethernet can generate LError for fragment packet (checksum error),
	   we must allow the queue to accept message with non-zero LErr. */
	pq.cfgacceptlerr = 1;
	switch (qstate->q_size) {
	case SIZE_512B:
		q_size = 512;
		break;
	case SIZE_2KB:
		q_size = 2 * 1024;
		break;
	case SIZE_16KB:
		q_size = 16 * 1024;
		break;
	case SIZE_64KB:
		q_size = 64 * 1024;
		break;
	case SIZE_512KB:
		q_size = 512 * 1024;
		break;
	default:
		QM_PRINT("Invalid queue size cfg write %d\n", qstate->q_size);
		return -1;
	}

	/* if its a free queue, ask QM to set len to 0 when dealloc */
	if (qstate->q_type == FREE_POOL)
		pq.fp_mode = 0x3;	/* FIXME, replace with enum once tested */

	if (qstate->q_start_addr != 0) { /* QM queues statically & dynamically allocated to reside in DRAM */
		switch(qstate->q_type) {
		case FREE_POOL:
			qaddr_phy = QMI_ETH_IPP_INGRESS_FP_ADDR;
			break;
		case P_QUEUE:
			if(qstate->direction) /* Egress */
				qaddr_phy = QMI_ETH_IPP_EGRESS_WQ_ADDR;
			else
				qaddr_phy = QMI_ETH_IPP_INGRESS_WQ_ADDR;
			break;
		default:
			QM_PRINT("Invalid queue type in QM/QML queue config\n");
			return -1;
		}

		qstate->q_start_addr = qaddr_phy >> 8; /* 256 byte aligned */
	} else { /* QM queues dynamically allocated to reside in DDR */
		int i, msg_len = 0;

		mem_size = q_size;
#ifdef CONFIG_APM_QM_QUEUE_LOCATION
		qaddr = mem_vaddr;
		mem_vaddr += mem_size;
		qaddr_phy = mem_paddr;
		mem_paddr += mem_size;
#else /* CONFIG_APM_QM_QUEUE_LOCATION */
#if defined(BOOTLOADER)
		mem_size = q_size + 512;
#endif
		qaddr = (u8 *)MEMALLOC(mem_size);

		if (qaddr == NULL) {
			QM_PRINT("Could not allocate memory for queue\n");
			return -1;
		}
#if defined(BOOTLOADER)
		/* queue addresses 256 byte aligned */
		qaddr = qaddr + 256;
		qaddr = (u8 *)((u64)qaddr & 0xFFFFFFFFFFFFFF00ULL);
#endif
		qaddr_phy = (u64)VIRT_TO_PHYS(qaddr);
#endif /* CONFIG_APM_QM_QUEUE_LOCATION */
		/* 256 byte aligned */
		qstate->q_start_addr = (u32)(qaddr_phy >> 8);
		qstate->startptr = qaddr;
		qstate->tailptr = qaddr;
		qstate->headptr = qaddr;
		qstate->endptr = qaddr + q_size;
		if (qstate->q_type == FREE_POOL)
			msg_len = 16;
		else
			msg_len = 32;
		for (i = 0; i < q_size; i+= msg_len) {
			memset(&qstate->startptr[i], 0, msg_len);
#if defined(CONFIG_MSLIM) || defined(CONFIG_ARCH_MSLIM)
			if (qstate->direction == DIR_EGRESS) {
#else
			if (qstate->direction == DIR_INGRESS) {
#endif
				((u32 *)qstate->startptr)[(i / 4) + EMPTY_SLOT_INDEX] = EMPTY_SLOT;
			}
		}

		QMCORE_PRINT("Queue PAddr 0x%llx VAddr 0x%p QAddr 0x%llx\n",
			(u64)qaddr_phy, qstate->startptr,
			(u64)qstate->q_start_addr);
	}

	pq.qcoherent = apm_qm_coherent();
	pq.cfgstartaddr = qstate->q_start_addr;
	pq.cpu_notify = qstate->cpu_notify; 
	pq.cfgnotifyqne = qstate->q_not_empty_intr; 
	pq.cfgsaben = qstate->cfgsaben;
	if (qstate->q_type == P_QUEUE) {
		pq.cfgtmvq = qstate->parent_vqid; 
		pq.cfgtmvqen = qstate->vqen; 
	}
#ifdef L3_STASHING
	pq.stashing = 1;
#endif

	QMCORE_PRINT("QM_IP %d QID %d cfgqtype %d cfgselthrsh %d cfgqsize %d fp_mode %d\n",
		qm_ip, q_num, pq.cfgqtype, pq.cfgselthrsh, pq.cfgqsize, pq.fp_mode);
	QMCORE_PRINT("QM_IP %d QID %d cfgacceptlerr %d cfgstartaddr 0x%llx cpu_notify %d\n",
		qm_ip, q_num, pq.cfgacceptlerr, (unsigned long long)pq.cfgstartaddr, pq.cpu_notify);
	QMCORE_PRINT("QM_IP %d QID %d cfgnotifyqne %d cfgsaben %d cfgtmvq %d cfgtmvqen %d\n",
		qm_ip, q_num, pq.cfgnotifyqne, pq.cfgsaben, pq.cfgtmvq, pq.cfgtmvqen);

	rc = apm_qm_raw_qstate_wr(qm_ip, 
			q_num, (struct apm_qm_raw_qstate *) &pq);
	if (rc) {
		return rc;
	}

	/* copy software queue state */
	memcpy(&QM_DEV(qm_ip)queue_states[qstate->q_id], qstate, 
			sizeof(struct apm_qm_qstate));
	QM_DEV(qm_ip)queue_states[qstate->q_id].dma = (struct apm_qm_raw_qstate *)
		QM_DEV(qm_ip)qm_fabric_vaddr + (qstate->q_id << 6);
	QM_DEV(qm_ip)queue_states[qstate->q_id].msg_stat = 0;

	return rc;
}

int apm_qm_cstate_wr(u32 qm_ip, u32 qid, u32 cstate[2])
{
	u32 queue_id = 0;
	int rc = 0;

	if (qid < 0 || qid > 255) {
		QM_PRINT("Queue number not valid in cfg write: 0x%x\n", qid);
		return -1;
	}

	/* write queue number */
	queue_id = QNUMBER_SET(queue_id, qid);
	QM_DBG("CState WR QID %d 0x%08X 0x%08X\n", 
			queue_id, cstate[0], cstate[1]);
	apm_qm_indirect_access_lock(1);
	__apm_qm_cstate_cmd(qm_ip, queue_id, cstate, 0);
	apm_qm_indirect_access_lock(0);

	return rc;
}

int apm_qm_cstate_rd(u32 qm_ip, u32 qid, u32 * cstate)
{
	u32 queue_id = 0;
	int rc = 0;

	if (qid < 0 || qid > 255) {
		QM_PRINT("Queue number not valid in cfg write: 0x%x\n", qid);
		return -1;
	}

	/* write queue number */
	queue_id = QNUMBER_SET(queue_id, qid);
	apm_qm_indirect_access_lock(1);
	__apm_qm_cstate_cmd(qm_ip, queue_id, cstate, 1);
	QM_DBG("CState RD QID %d 0x%08X 0x%08X\n", 
		queue_id, cstate[0], cstate[1]);
	apm_qm_indirect_access_lock(0);

	return rc;
}

int apm_qm_vqstate_wr(struct apm_qm_qstate *qstate)
{
	struct apm_qm_vqstate vq;
	int rc = 0, q_num = qstate->q_id, i;
	u32 cstate[2] = {0};
	u32 qm_ip = qstate->ip_blk;

	memset(&vq, 0, sizeof(vq));

	if (q_num < 0 || q_num > 255) {
		QM_PRINT("Queue number not valid in cfg write: 0x%x\n", q_num);
		return -1;
	}

	if ((!qstate->valid) || (qstate->q_type != V_QUEUE)) {
		QM_PRINT("Virtual queue config not valid in cfg write\n");
		return -1;
	}

	if (qm_ip < IP_BLK_QM0 || qm_ip > IP_BLK_QM2) {
		QM_PRINT("Invalid Block ID in cfg write for VQ: %d\n",
				qm_ip);
		return -1;
	}

	vq.cfgqtype = qstate->q_type;
	vq.cfgselthrsh = qstate->thr_set;
	vq.q0_sel = qstate->pq_sel[0];
	vq.q0selarb = qstate->q_sel_arb[0];
	if (qstate->q_sel_arb[0] == DRR_ARB)
		vq.q0txallowed = 1;
	vq.q1_sel_2b = qstate->pq_sel[1] >> 8;
	vq.q1_sel_8b = qstate->pq_sel[1] & 0xff;
	vq.q1selarb = qstate->q_sel_arb[1];
	if (qstate->q_sel_arb[1] == DRR_ARB)
		vq.q1txallowed = 1;
	vq.q2_sel = qstate->pq_sel[2];
	vq.q2selarb = qstate->q_sel_arb[2];
	if (qstate->q_sel_arb[2] == DRR_ARB)
		vq.q2txallowed = 1;
	vq.q3_sel_6b = qstate->pq_sel[3];
	vq.q3_sel_4b = qstate->pq_sel[3];
	vq.q3selarb = qstate->q_sel_arb[3];
	if (qstate->q_sel_arb[3] == DRR_ARB)
		vq.q3txallowed = 1;
	vq.q4_sel = qstate->pq_sel[4];
	vq.q4selarb = qstate->q_sel_arb[4];
	vq.q5_sel = qstate->pq_sel[5];
	vq.q5selarb = qstate->q_sel_arb[5];
	if (qstate->q_sel_arb[5] == DRR_ARB)
		vq.q5txallowed = 1;
	vq.q6_sel = qstate->pq_sel[6];
	vq.q6selarb = qstate->q_sel_arb[6];
	if (qstate->q_sel_arb[6] == DRR_ARB)
		vq.q6txallowed = 1;
	vq.q7_sel = qstate->pq_sel[7];
	vq.q7selarb = qstate->q_sel_arb[7];
	if (qstate->q_sel_arb[7] == DRR_ARB)
		vq.q7txallowed = 1;
	vq.cpu_notify = qstate->cpu_notify; 
	vq.cfgnotifyqne = qstate->q_not_empty_intr;

#if 0
	/* Configure domain protection field. For VQ, allow for all and 
	   use the original message domain */
	vq.allowed_dom = 0xF;
#endif

	rc = apm_qm_raw_qstate_wr(qm_ip, 
			q_num, (struct apm_qm_raw_qstate *)&vq);
	if (rc) {
		return rc;
	}

	/* copy software queue state */
	memcpy(&QM_DEV(qm_ip)queue_states[qstate->q_id], qstate,
			sizeof (struct apm_qm_qstate));

	if (qstate->q_sel_arb[0] == SP_ARB)
		goto exit;

	/* Update Credit Ram State for each of PQ */
	for (i = 0; i < 8; i++) {
		QM_DBG("q_sel_arb[%d] = %d, pq_sel[%d] = %d rate/weight[%d] = %d \n",
			i, qstate->q_sel_arb[i],i,  qstate->pq_sel[i], i, qstate->shape_rate[i]);
		if (qstate->q_sel_arb[i] == DRR_ARB) {
			u32 credit = qstate->shape_rate[i] * DRR_CREDIT_GRAN;
			cstate[0] = credit >> 10;
			cstate[1] = ((credit & 0X3FF) << 22) |
				(credit & 0X3FFFFF );
			QM_DBG("Credit: %d \n", credit);
			QM_DBG("Writing Cstate for pq_sel[%d]:%d - cstate[0]:0x%x, cstate[1]:0x%x \n", i, qstate->pq_sel[i], cstate[0], cstate[1]);
		} else if (qstate->q_sel_arb[i] == AVB_ARB) {
			u32 slope = qstate->shape_rate[i];
			cstate[0] |= slope >> 4 ;
			cstate[1] |= (slope & 0xf) << 28;
			QM_DBG("Writing Cstate for pq_sel[%d]:%d - cstate[0]:0x%x, cstate[1]:0x%x \n", i, qstate->pq_sel[i], cstate[0], cstate[1]);
		} else {
			continue;
		}
		apm_qm_cstate_wr(qm_ip, qstate->pq_sel[i], cstate);
		cstate[0] = cstate[1] = 0;
	}

	/* Update Credit Ram State for each of PQ */
	apm_qm_cstate_wr(qm_ip, qstate->q_id, cstate);

exit:	
	return rc;
}

static int apm_qm_config_qstate(u32 no_of_queues)
{
	struct apm_qm_qstate *qstate;
	int i, is_fp = 0, rc = 0, is_vq;
	/*static int config_done = 0;*/

	/*if (config_done)*/ /*skip for now*/
		return rc;

	/*config_done = 1;*/
	QM_DBG("Configure static queues: %d\n", no_of_queues);
	/* configure QM */
	for (i = 0; i < no_of_queues; i++) {
		qstate = &mb_cfg_pqs[i];
		if (qstate->ip_blk == IP_BLK_QML && qm_cinfo.is_noqml) {
			/* Skip QM Lite configuration if hardware not 
			   available */
			continue;
		}
		if ((rc = apm_qm_qstate_wr(qstate)) != 0) {
			QM_PRINT("Error in queue configuration error %d\n", 
				rc);
			break;
		} 
		is_fp = ((qstate->q_type == FREE_POOL) ? 1 : 0);
		is_vq = ((qstate->q_type == V_QUEUE) ? 1 : 0);
		apm_qm_pb_config(qstate->ip_blk, qstate->slave_id, qstate->pbn, 
			qstate->q_id, is_fp, is_vq);
	}

	return rc;
}

static void apm_qm_slave_id_map_init(void)
{
	int i;
	static int config_done = 0;

	if (config_done)
		return;

	config_done = 1;

	/* initialize mailbox assignments */
	for (i = IP_CPU0; i < IP_MAX; i++) {
		switch(i) {
		case IP_ETH0:
		case IP_ETH1:
		case IP_XGE0:
		case IP_XGE2:
		case IP_ETH4:
			ip_to_slave_id[i] = PB_SLAVE_ID_ETH_BLK0;
			break;
		case IP_ETH2:
		case IP_ETH3:
		case IP_XGE1:
		case IP_XGE3:
			ip_to_slave_id[i] = PB_SLAVE_ID_ETH_BLK1;
			break;
		case IP_DMA:
			ip_to_slave_id[i] = PB_SLAVE_ID_DMA;
			break;
		case IP_CTX:
			ip_to_slave_id[i] = PB_SLAVE_ID_CTX;
			break;
		case IP_SEC:
			ip_to_slave_id[i] = PB_SLAVE_ID_SEC;
			break;
		case IP_CLASS:
			ip_to_slave_id[i] = PB_SLAVE_ID_CLASS;
			break;
		case IP_MSLIM:
			ip_to_slave_id[i] = PB_SLAVE_ID_MSLIM;
			break;
		case IP_IPP:
			ip_to_slave_id[i] = PB_SLAVE_ID_IPP;
			break;
		case IP_CPU0:
		case IP_CPU1:
		case IP_CPU2:
		case IP_CPU3:
		case IP_CPU4:
		case IP_CPU5:
		case IP_CPU6:
		case IP_CPU7:
			ip_to_slave_id[i] = PB_SLAVE_ID_CPU;
			break;
		}
	}
}

static void apm_qm_pbn_init(u32 qm_ip)
{
	memset(QM_DEV(qm_ip)ip_pbn_wq_msk, 0, sizeof(QM_DEV(qm_ip)ip_pbn_wq_msk));
	memset(QM_DEV(qm_ip)ip_pbn_wq_act, 0, sizeof(QM_DEV(qm_ip)ip_pbn_wq_act));
	memset(QM_DEV(qm_ip)ip_pbn_fq_msk, 0, sizeof(QM_DEV(qm_ip)ip_pbn_fq_msk));
	memset(QM_DEV(qm_ip)ip_pbn_fq_act, 0, sizeof(QM_DEV(qm_ip)ip_pbn_fq_act));

	if (qm_ip == IP_BLK_QM) {
		/* ETH 0 PBN */
		QM_DEV(qm_ip)ip_pbn_wq_msk[IP_ETH0] = 0x000000FF;
		QM_DEV(qm_ip)ip_pbn_fq_msk[IP_ETH0] = 0x000000FF;

		/* ETH 1 PBN */
		QM_DEV(qm_ip)ip_pbn_wq_msk[IP_ETH1] = 0x0000FF00;	/* 0x10 is for QM-lite */
		QM_DEV(qm_ip)ip_pbn_fq_msk[IP_ETH1] = 0x0000FF00;	/* 0x30 and 0x31 for QM-lite */

		/* ETH 2 PBN */
		QM_DEV(qm_ip)ip_pbn_wq_msk[IP_ETH2] = 0x000000FF;
		QM_DEV(qm_ip)ip_pbn_fq_msk[IP_ETH2] = 0x000000FF;

		/* ETH 3 PBN */
		QM_DEV(qm_ip)ip_pbn_wq_msk[IP_ETH3] = 0x0000FF00;	/* 0x10 is for QM-lite */
		QM_DEV(qm_ip)ip_pbn_fq_msk[IP_ETH3] = 0x0000FF00;	/* 0x30 and 0x31 for QM-lite */

		/* DMA PBN */
		QM_DEV(qm_ip)ip_pbn_wq_msk[IP_DMA] = 0x0000000F;	
		QM_DEV(qm_ip)ip_pbn_fq_msk[IP_DMA] = 0x000000FF;

		/* SEC PBN */
		QM_DEV(qm_ip)ip_pbn_wq_msk[IP_SEC] = 0x00000003;
		QM_DEV(qm_ip)ip_pbn_fq_msk[IP_SEC] = 0x000000FF;	

		/* CLE PBN */
		QM_DEV(qm_ip)ip_pbn_wq_msk[IP_CLASS] = 0x0000000F;
		QM_DEV(qm_ip)ip_pbn_fq_msk[IP_CLASS] = 0x000000FF;
	}

	if (qm_ip == IP_BLK_QM0) {
		/* XGE 0 PBN */
		QM_DEV(qm_ip)ip_pbn_wq_msk[IP_XGE0] = 0x000000FF;
		QM_DEV(qm_ip)ip_pbn_fq_msk[IP_XGE0] = 0x000000FF;

		/* XGE 1 PBN */
		QM_DEV(qm_ip)ip_pbn_wq_msk[IP_XGE1] = 0x000000FF;
		QM_DEV(qm_ip)ip_pbn_fq_msk[IP_XGE1] = 0x000000FF;
	}

	if (qm_ip == IP_BLK_QM2) {
		/* XGE 2 PBN */
		QM_DEV(qm_ip)ip_pbn_wq_msk[IP_XGE2] = 0x000000FF;
		QM_DEV(qm_ip)ip_pbn_fq_msk[IP_XGE2] = 0x000000FF;

		/* XGE 3 PBN */
		QM_DEV(qm_ip)ip_pbn_wq_msk[IP_XGE3] = 0x000000FF;
		QM_DEV(qm_ip)ip_pbn_fq_msk[IP_XGE3] = 0x000000FF;
	}

	if (qm_ip == IP_BLK_QML) {
		/* ETH 4 PBN */
		QM_DEV(qm_ip)ip_pbn_wq_msk[IP_ETH4] = 0x0000000F;
		QM_DEV(qm_ip)ip_pbn_fq_msk[IP_ETH4] = 0x0000000F;

		/* MSLIM PBN */
		QM_DEV(qm_ip)ip_pbn_wq_msk[IP_MSLIM] = 0x00000001;
		QM_DEV(qm_ip)ip_pbn_fq_msk[IP_MSLIM] = 0x00000001;

		/* SlimPRO PBN */
		QM_DEV(qm_ip)ip_pbn_wq_msk[IP_IPP] = 0x00000003;
		QM_DEV(qm_ip)ip_pbn_fq_msk[IP_IPP] = 0x00000003;

		/* CPU0-7 PBN as shared */
		QM_DEV(qm_ip)ip_pbn_wq_msk[IP_CPU0] = 0x00000001;	
		QM_DEV(qm_ip)ip_pbn_fq_msk[IP_CPU0] = 0x00000001;
	} else {
		/* CTX PBN */
		QM_DEV(qm_ip)ip_pbn_wq_msk[IP_CTX] = 0x000001FF;	
		QM_DEV(qm_ip)ip_pbn_fq_msk[IP_CTX] = 0x00000003;

		/* MSLIM PBN */
		QM_DEV(qm_ip)ip_pbn_wq_msk[IP_MSLIM] = 0x0000FFFF;
		QM_DEV(qm_ip)ip_pbn_fq_msk[IP_MSLIM] = 0x0000FFFF;

		/* SlimPRO PBN */
		QM_DEV(qm_ip)ip_pbn_wq_msk[IP_IPP] = 0x0000003F;		/* Work QID 0x1 for QM-lite */
		QM_DEV(qm_ip)ip_pbn_fq_msk[IP_IPP] = 0x000000FF;		/* Free PBN 0x28 for QM-lite */

		/* CPU0-7 PBN as shared */
		QM_DEV(qm_ip)ip_pbn_wq_msk[IP_CPU0] = 0xFFFFFFFF;	
		QM_DEV(qm_ip)ip_pbn_fq_msk[IP_CPU0] = 0xFFFFFFFF;
	}
}

int apm_qm_get_slave_id(u32 ip_blk)
{
	if (ip_blk < IP_CPU0 && ip_blk >= IP_MAX)
		return -1;

	return ip_to_slave_id[ip_blk];
}

int apm_qm_get_ib_mb(u32 qm_ip, u32 cpux, u32 ip_blk)
{
	int idx;

#ifdef CONFIG_APM_QM_ALTERNATE_DEQUEUE
	u32 data;
#endif
	int found = 0;

	if (qm_ip == IP_BLK_QML) {
		QM_DBG("Skipping Inbound Mailbox Configuration for "
			"qm_ip=IP_BLK_QML\n");
		return 0;
	}

	for (idx = QM_DEV(qm_ip)start_mboxes;
		idx < QM_DEV(qm_ip)start_mboxes + QM_DEV(qm_ip)max_mboxes;
		idx++) { 
		/* Check if this slot is in use */
		if (!QM_DEV(qm_ip)ib_mbox_used[idx]) {
			/* If empty lets use it */
			QM_DEV(qm_ip)ib_mbox_used[idx] = ip_blk | 0x8000;
#ifdef CONFIG_APM_QM_ALTERNATE_DEQUEUE
			apm_qm_rd32(qm_ip, CSR_QM_MBOX_NE_INT_MODE_ADDR,
				&data);
			data |= (1 << (31 - idx));
			apm_qm_wr32(qm_ip, CSR_QM_MBOX_NE_INT_MODE_ADDR,
				data);
#endif
			found = 1;
			break;
		}
	}

	if (!found)
		QM_DBG("Error: Inbound mailbox slots all taken\n");
	return idx;
}

int apm_qm_get_ib_pbn(u32 qm_ip, u32 cpux, u32 ip_blk, u32 ibmbox)
{
	if (qm_ip == IP_BLK_QML) {
		QM_DBG("Skipping Inbound PBN Configuration for "
			"qm_ip=IP_BLK_QML\n");
		return 0;
	}

	/* PBN is same as mail box */
	if (QM_DEV(qm_ip)ip_pbn_wq_msk[IP_CPU0] & (1 << ibmbox)) {
		if (!(QM_DEV(qm_ip)ip_pbn_wq_act[IP_CPU0] & (1 << ibmbox))) {
			QM_DEV(qm_ip)ip_pbn_wq_act[IP_CPU0] |= (1 << ibmbox);
			return ibmbox;
		}
	}

	/* Out of CPU PBN */
	QM_ERR_CHK("Out of CPU QM PBN for CPU %d IP %d\n", cpux, ip_blk);
	return -1;
}

int apm_qm_free_ib_pbn(u32 qm_ip, u32 cpux, u32 ip_blk, u32 ibmbox)
{
	if (qm_ip == IP_BLK_QML) {
		QM_DBG("Skipping Inbound PBN Free for "
			"qm_ip=IP_BLK_QML\n");
		return 0;
	}

	/* PBN is same as mail box */
	if (QM_DEV(qm_ip)ip_pbn_wq_msk[IP_CPU0] & (1 << ibmbox)) {
		if (QM_DEV(qm_ip)ip_pbn_wq_act[IP_CPU0] & (1 << ibmbox)) {
			QM_DEV(qm_ip)ip_pbn_wq_act[IP_CPU0] &= ~(1 << ibmbox);
			return 0;
		}
	}
	return -1;
}

int apm_qm_get_fp_pbn(u32 qm_ip, u32 cpux, u32 ip_blk)
{
	int i;

	/* FP PBN for CPU are shared */
	if (ip_blk >= IP_CPU0 && ip_blk <= IP_CPU7)
		ip_blk = IP_CPU0;

	/* Search for a free PBN for this IP block */
	for (i = 0; i <= 31; i++) {	//TODO from 1
		if (QM_DEV(qm_ip)ip_pbn_fq_msk[ip_blk] & (1 << i) &&
			!(QM_DEV(qm_ip)ip_pbn_fq_act[ip_blk] & (1 << i))) {
			/* We found a free PBN */
			QM_DEV(qm_ip)ip_pbn_fq_act[ip_blk] |= (1 << i);
			return i + 0x20;
		}
	}
	/* Out of PBN */
	QM_ERR_CHK("Out of QM FP PBN for CPU %d IP %d\n", cpux, ip_blk);
	return -1;
}

int apm_qm_free_fp_pbn(u32 qm_ip, u32 ip_blk, u32 pbn)
{
	int pbn_bit = pbn - 0x20;

	/* FP PBN for CPU are shared */
	if (ip_blk == IP_CPU1)
		ip_blk = IP_CPU0;

	if (QM_DEV(qm_ip)ip_pbn_fq_msk[ip_blk] & (1 << pbn_bit)) {
		QM_DEV(qm_ip)ip_pbn_fq_act[ip_blk] &= ~(1 << pbn_bit);
		return 0;
	} else {
		return -1;
	}
}

int apm_qm_get_ob_mb(u32 qm_ip, u32 cpux, u32 ip_blk, u32 is_fp)
{
	static u32 dma_wq_cnt = 0, dma_fp_cnt = 0;

	switch (ip_blk) {
	case IP_ETH0:
	case IP_ETH2:
	case IP_XGE0:
	case IP_XGE2:
	case IP_CLASS:
	case IP_CPU0:
	case IP_CPU4:
		return (cpux * 4) + (2 * is_fp) + 0;
	case IP_ETH1:
	case IP_ETH3:
	case IP_XGE1:
	case IP_XGE3:
	case IP_SEC:
	case IP_CPU1:
	case IP_CPU5:
		return (cpux * 4) + (2 * is_fp) + 1;
	case IP_MSLIM:
	case IP_CPU2:
	case IP_CPU6:
		return (cpux * 4) - (2 * is_fp) + 2;
	case IP_CTX:
	case IP_IPP:
	case IP_CPU3:
	case IP_CPU7:
		return (cpux * 4) - (2 * is_fp) + 3;
	case IP_DMA:
		if (is_fp)
			return (cpux * 4) + ((dma_wq_cnt++) % 4);
		else
			return (cpux * 4) + ((dma_fp_cnt++) % 4);
	default:
		return (cpux * 4);
	}
}

int apm_qm_get_ob_pbn(u32 qm_ip, u32 cpux, u32 ip_blk)
{
	int i;

	/* PBN for CPU are shared */
	if (ip_blk >= IP_CPU0 && ip_blk <= IP_CPU7)
		ip_blk = IP_CPU0;

	/* Search for a free PBN for this IP block */
	for (i = 0; i <= 31; i++) {	//TODO from 1
		if (QM_DEV(qm_ip)ip_pbn_wq_msk[ip_blk] & (1 << i) &&
			!(QM_DEV(qm_ip)ip_pbn_wq_act[ip_blk] & (1 << i))) {
			/* We found a PBN */
			QM_DEV(qm_ip)ip_pbn_wq_act[ip_blk] |= (1 << i);
			return i;
		}
	}
	/* Out of PBN */
	QM_ERR_CHK("Out of QM PBN for CPU %d IP %d\n", cpux, ip_blk);
	return -1;
}

int apm_qm_free_ob_pbn(u32 qm_ip, u32 cpux, u32 ip_blk, u32 pbn)
{
	/* PBN for CPU are shared */
	if (ip_blk >= IP_CPU0 && ip_blk <= IP_CPU7)
		ip_blk = IP_CPU0;

	if (QM_DEV(qm_ip)ip_pbn_wq_msk[ip_blk] & (1 << pbn))
		QM_DEV(qm_ip)ip_pbn_wq_act[ip_blk] &= ~(1 << pbn);
	return 0;
}

#ifndef CONFIG_APM_QM_SKIP_MAILBOX_INIT
void apm_qm_set_enq_mbox_addr(u32 qm_ip, u32 coherent, u64 paddr)
{
	u32 data = 0;
	/*u32 reg;*/

	if (coherent)
		data = 0x80000000;

	data |= (u32)(paddr >> 16);
	apm_qm_wr32(qm_ip, CSR_ENQ_BASE_0_ADDR, data);
	QMCORE_PRINT("qm_ip %d enq_mbox_addr 0x%llx data %08x\n",
		qm_ip, (unsigned long long)paddr, data);

	if (ENQUE_MAIL_BOXES > 8) {
		data += 1;      /* (8 * 256 * 32 = 65536 = 0x10000) */
		apm_qm_wr32(qm_ip, CSR_ENQ_BASE_1_ADDR, data);
	}

	if (ENQUE_MAIL_BOXES > 16) {
		data += 1;
		apm_qm_wr32(qm_ip, CSR_ENQ_BASE_2_ADDR, data);
	}

	if (ENQUE_MAIL_BOXES > 24) {
		data += 1;
		apm_qm_wr32(qm_ip, CSR_ENQ_BASE_3_ADDR, data);
	}
}

void apm_qm_set_dq_mbox_addr(u32 qm_ip, u32 coherent, u64 paddr)
{
	u32 data = 0;
	/*u32 reg;*/

	if (coherent)
		data = 0x80000000;

	data |= (u32)(paddr >> 16);
	apm_qm_wr32(qm_ip, CSR_PROC_MBOX_BASE_0_ADDR, data); /*CSR_PROC_MBOX_BASE */
	QMCORE_PRINT("qm_ip %d dq_mbox_addr 0x%llx data %08x\n",
		qm_ip, (unsigned long long)paddr, data);

	if (DQ_MAIL_BOXES > 8) {
		data += 1;
		apm_qm_wr32(qm_ip, CSR_PROC_MBOX_BASE_1_ADDR, data);
	}

	if (DQ_MAIL_BOXES > 16) {
		data += 1;
		apm_qm_wr32(qm_ip, CSR_PROC_MBOX_BASE_2_ADDR, data);
	}

	if (DQ_MAIL_BOXES > 24) {
		data += 1;
		apm_qm_wr32(qm_ip, CSR_PROC_MBOX_BASE_3_ADDR, data);
	}
}

void apm_qm_set_fp_mbox_addr(u32 qm_ip, u32 coherent, u64 paddr)
{
	u32 data = 0;
	/*u32 reg;*/

	if (coherent)
		data = 0x80000000;

	data |= (u32)(paddr >> 15);
	apm_qm_wr32(qm_ip, CSR_PROC_FPOOL_BASE_0_ADDR, data);
	QMCORE_PRINT("qm_ip %d fp_mbox_addr 0x%llx data %08x\n",
		qm_ip, (unsigned long long)paddr, data);

	if (FP_MAIL_BOXES > 8) {
		data += 1;
		apm_qm_wr32(qm_ip, CSR_PROC_FPOOL_BASE_1_ADDR, data);
	}

	if (FP_MAIL_BOXES > 16) {
		data += 1;
		apm_qm_wr32(qm_ip, CSR_PROC_FPOOL_BASE_2_ADDR, data);
	}

	if (FP_MAIL_BOXES > 24) {
		data += 1;
		apm_qm_wr32(qm_ip, CSR_PROC_FPOOL_BASE_3_ADDR, data);
	}
}

int apm_qm_alloc_mbox(u32 qm_ip)
{
	struct apm_qm_msg32 *mb_slot_ptr;
	struct apm_qm_msg32 *cur_slot_ptr;
	u32 *slot_ptr;
	u32 j;
	u32 i;

	QM_DBG("%s Enq:0x%llx Dq:0x%llx Fp:0x%llx\n", __func__,
		(unsigned long long)QM_DEV(qm_ip)qm_enq_mbox_paddr,
		(unsigned long long)QM_DEV(qm_ip)qm_dq_mbox_paddr,
		(unsigned long long)QM_DEV(qm_ip)qm_fp_mbox_paddr);

	QM_DEV(qm_ip)enq_mboxes = (struct apm_qm_mailbox *) QM_DEV(qm_ip)qm_enq_mbox_vaddr;
	QM_DEV(qm_ip)dq_mboxes = (struct apm_qm_mailbox *) QM_DEV(qm_ip)qm_dq_mbox_vaddr;
	QM_DEV(qm_ip)fp_mboxes = (struct apm_qm_fp_mailbox *) QM_DEV(qm_ip)qm_fp_mbox_vaddr;

	/* assign invalid RType to all slots in all mailboxes */
	for (i = QM_DEV(qm_ip)start_mboxes; 
			i < QM_DEV(qm_ip)start_mboxes + QM_DEV(qm_ip)max_mboxes; i++) { 
		/* for all mailboxes */
		mb_slot_ptr = (struct apm_qm_msg32 *) &QM_DEV(qm_ip)dq_mboxes[i];
		/* for all slots in given mailbox */ 
		for (j = 0; j < TOTAL_SLOTS_32BYTE_MSG; j++) { 
			cur_slot_ptr = mb_slot_ptr + j;
			QM_INVALIDATE_MB(qm_ip, cur_slot_ptr, 
					(u8 *) (cur_slot_ptr + 1)); 
			slot_ptr = (u32 *) cur_slot_ptr;
			slot_ptr[EMPTY_SLOT_INDEX] = EMPTY_SLOT; /* Initially all slots are empty */
			QM_FLUSH_MB(qm_ip, cur_slot_ptr, 
					(u8 *) (cur_slot_ptr + 1));
		}
	}

	/*configure enqeue mailboxes */
	for (i = 0; i < ENQUE_MAIL_BOXES; i++) {
		QM_DEV(qm_ip)mb_enq_mbox_ctxt[i].first_ptr = &QM_DEV(qm_ip)enq_mboxes[i].mailslots[0];
		QM_DEV(qm_ip)mb_enq_mbox_ctxt[i].last_ptr = &QM_DEV(qm_ip)enq_mboxes[i].mailslots[TOTAL_SLOTS_32BYTE_MSG-1];
		QM_DEV(qm_ip)mb_enq_mbox_ctxt[i].cur_ptr = QM_DEV(qm_ip)mb_enq_mbox_ctxt[i].first_ptr;
		QM_DEV(qm_ip)mb_enq_mbox_ctxt[i].slot = 0;
		QM_DEV(qm_ip)mb_enq_mbox_ctxt[i].last_slot = TOTAL_SLOTS_32BYTE_MSG - 1;
		QM_DEV(qm_ip)mb_enq_mbox_ctxt[i].total_slot = TOTAL_SLOTS_32BYTE_MSG;
	}

	/* configure work queue dequeue mailboxes */
	for (i = 0; i < DQ_MAIL_BOXES; i++) {
		QM_DEV(qm_ip)mb_dq_mbox_ctxt[i].first_ptr = &QM_DEV(qm_ip)dq_mboxes[i].mailslots[0];
		QM_DEV(qm_ip)mb_dq_mbox_ctxt[i].last_ptr = &QM_DEV(qm_ip)dq_mboxes[i].mailslots[TOTAL_SLOTS_32BYTE_MSG-1];
		QM_DEV(qm_ip)mb_dq_mbox_ctxt[i].cur_ptr = QM_DEV(qm_ip)mb_dq_mbox_ctxt[i].first_ptr; 
		QM_DEV(qm_ip)mb_dq_mbox_ctxt[i].slot = 0;
		QM_DEV(qm_ip)mb_dq_mbox_ctxt[i].last_slot = TOTAL_SLOTS_32BYTE_MSG - 1;
		QM_DEV(qm_ip)mb_dq_mbox_ctxt[i].total_slot = TOTAL_SLOTS_32BYTE_MSG;
	}

	/* configure free queue dequeue mailboxes */
	for (i = 0; i < FP_MAIL_BOXES; i++) {
		QM_DEV(qm_ip)mb_fp_mbox_ctxt[i].first_ptr = &QM_DEV(qm_ip)fp_mboxes[i].mailslots[0];
		QM_DEV(qm_ip)mb_fp_mbox_ctxt[i].last_ptr = &QM_DEV(qm_ip)fp_mboxes[i].mailslots[TOTAL_SLOTS_16BYTE_MSG-1];
		QM_DEV(qm_ip)mb_fp_mbox_ctxt[i].cur_ptr = QM_DEV(qm_ip)mb_fp_mbox_ctxt[i].first_ptr; 
		QM_DEV(qm_ip)mb_fp_mbox_ctxt[i].slot = 0;
		QM_DEV(qm_ip)mb_fp_mbox_ctxt[i].last_slot = TOTAL_SLOTS_16BYTE_MSG - 1;
		QM_DEV(qm_ip)mb_fp_mbox_ctxt[i].total_slot = TOTAL_SLOTS_16BYTE_MSG;
	}

	/* initialize mailbox assignments */
	for (i = 0; i < MAX_SLAVES; i++) {
		QM_DEV(qm_ip)dq_fp_ip_to_mb[i] = i;
	}

	return 0;
}
#endif

int apm_qm_mailbox_rx_unregister(u32 qm_ip, u32 mbidx)
{
	if (mbidx > MAX_MAILBOXS) 
		return -1;
	QM_DEV(qm_ip)qm_mailbox_fn_table[mbidx] = NULL;
	return 0;
}

int apm_qm_mailbox_rx_register(u32 qm_ip, u32 mbidx, apm_qm_msg_fn_ptr fn_ptr)
{
	if (mbidx > MAX_MAILBOXS || fn_ptr == NULL) 
		return -1;
	else if (QM_DEV(qm_ip)qm_mailbox_fn_table[mbidx] != NULL)
		return -1;

	QM_DEV(qm_ip)qm_mailbox_fn_table[mbidx] = fn_ptr;
	return 0;
}

int apm_qm_msg_rx_unregister(u32 qm_ip, u32 rtype)
{
	if (rtype >= APM_QM_MAX_RTYPE) {
		QM_PRINT("Unsupported rtype number %d\n", rtype);
		return -1;
	} else if (QM_DEV(qm_ip)qm_cb_fn_table[rtype] == NULL) {
		QM_PRINT("RType never registered before%d\n", rtype);
		return -1;
	}

	QM_DEV(qm_ip)qm_cb_fn_table[rtype] = NULL;

	return 0;
}

int apm_qm_msg_rx_register(u32 qm_ip, u32 rtype, apm_qm_msg_fn_ptr fn_ptr)
{
	if (rtype >= APM_QM_MAX_RTYPE) {
		QM_PRINT("Unsupported rtype number %d\n", rtype);
		return -1;
	} else if (fn_ptr == NULL) {
		QM_PRINT("fn_ptr can't be NULL in QM callback register\n");
		return -1;
	} else if (QM_DEV(qm_ip)qm_cb_fn_table[rtype] != NULL) {
		QM_PRINT("rtype [%d] already registered.\n",rtype);
		return -1;
	}

	/* register call back */
	QM_DEV(qm_ip)qm_cb_fn_table[rtype] = fn_ptr;

	return 0;
}

int apm_qm_qid_id_init(u32 qm_ip, u32 sqid, u32 eqid)
{
	if (QM_DEV(qm_ip)start_qid < 0 || QM_DEV(qm_ip)max_qid > QM_MAX_QUEUES-1) {
	       	QM_PRINT("QID range too large\n");
		goto _ret;
	}

	memset(QM_DEV(qm_ip)free_qid, 0, sizeof(QM_DEV(qm_ip)free_qid));

_ret:
	return 0;
}

/* check for the first available free_qid bit position and set it to 1 */
int apm_qm_qid_get(u32 qm_ip)
{
	u32 idx;

	for (idx = QM_DEV(qm_ip)start_qid; idx < QM_DEV(qm_ip)max_qid; idx++) {
		if ((QM_DEV(qm_ip)free_qid[idx / 32] & (1 << (idx % 32))) == 0) {
			QM_DEV(qm_ip)free_qid[idx / 32] |= (1 << (idx % 32));
			return idx;
		}
	}

	QM_PRINT("Out of QID\n");
	return -1;
}

/* set the free_qid bit to 0 */
int apm_qm_qid_free(u32 qm_ip, u32 qid)
{
	QM_DEV(qm_ip)free_qid[qid / 32] &= ~(1 << (qid % 32));

	return 0;
}

int apm_qm_init_errq(u32 qm_ip, u32 cpux)
{
	int rc = 0;
	u32 val;
#ifdef APM_QM_ERROR_Q_ENABLE
	struct apm_qm_qstate qstate;

	QM_DBG("Configure QM error queue\n");
#endif

#ifdef APM_QM_ERROR_Q_ENABLE
	/* program threshold set 1 and all hysteresis */
	apm_qm_wr32(qm_ip, CSR_THRESHOLD0_SET1_ADDR, 100);
	apm_qm_wr32(qm_ip, CSR_THRESHOLD1_SET1_ADDR, 200);
	apm_qm_wr32(qm_ip, CSR_HYSTERESIS_ADDR, 0xFFFFFFFF);

	/* create error queue */
	memset(&qstate, 0, sizeof(qstate));	
	qstate.src_ip_blk = IP_CPU0 + cpux;
	qstate.ip_blk = qm_ip;
	qstate.cpu_id = cpux;
	qstate.valid = 1;
	qstate.q_id = apm_qm_qid_get(qm_ip);
	qstate.mb_id = apm_qm_get_ib_mb(qm_ip, cpux, cpux);
	qstate.pbn = apm_qm_get_ib_pbn(qm_ip, cpux, cpux, qstate.mb_id);
#if defined(CONFIG_MSLIM) || defined(CONFIG_ARCH_MSLIM)
	qstate.slave_id = PB_SLAVE_ID_MSLIM;
	qstate.direction = DIR_EGRESS;
#else
	qstate.slave_id = PB_SLAVE_ID_CPU;
	qstate.direction = DIR_INGRESS;
#endif
	qstate.q_type = P_QUEUE;
	qstate.msg_size = MSG_32B;
	qstate.q_size = SIZE_2KB;
	qstate.thr_set = 1;
	if ((rc = apm_qm_qstate_wr(&qstate)) != 0) {
		QM_PRINT("Unable to configure Error queue state for CPU %d "
			"error %d\n", cpux, rc);
		return rc;
	} 
	if ((rc = apm_qm_pb_config(qstate.ip_blk, qstate.slave_id,
			qstate.pbn, qstate.q_id, 0, 0)) != 0) {
		QM_PRINT("Unable to configure Error queue PBN for CPU %d "
			"error %d\n", cpux, rc);
		return rc;
	}
	/* Also reset the slot and num message in PBN */
	/*apm_qm_pb_clr(qstate.ip_blk, qstate.slave_id, qstate.pbn);*/

	QM_DEV(qm_ip)err_qid = qstate.q_id;
#endif

	/* Enable QPcore and assign error queue */
	val = 0;
	val = QM_ENABLE_SET(val, 1);
	apm_qm_wr32(qm_ip, CSR_QM_CONFIG_ADDR, val);	

#ifdef APM_QM_ERROR_Q_ENABLE
	val = 0;
	val = UNEXPECTED_EN_SET(val, 1);
	val = UNEXPECTED_QID_SET(val, QM_DEV(qm_ip)err_qid);
	val = EXPECTED_EN_SET(val, 1);
	val = EXPECTED_QID_SET(val, QM_DEV(qm_ip)err_qid);
	apm_qm_wr32(qm_ip, CSR_ERRQ_ADDR, val);
#endif

	return rc;
}

static int apm_qm_create_compl_queue(u32 qm_ip, u32 desc_size)
{
	int rc = 0;
	struct apm_qm_qstate qstate;

	QM_DBG("Creating CPU0 completion queue for all DEV in QM%d\n", qm_ip);
	memset(&qstate, 0, sizeof(qstate));
	qstate.q_id = apm_qm_qid_get(qm_ip);

	if (qstate.q_id < 0) {
		QM_PRINT("Out of QID for QM %d\n", qm_ip);
		return -1;
	}

	qstate.src_ip_blk = IP_CPU0;
	qstate.ip_blk = qm_ip;
	qstate.cpu_id = IP_CPU0;
	qstate.valid = 1;
	qstate.mb_id = apm_qm_get_ib_mb(qm_ip, IP_CPU0, IP_CPU0);
#if defined(CONFIG_MSLIM) || defined(CONFIG_ARCH_MSLIM)
	qstate.slave_id = PB_SLAVE_ID_MSLIM;
	qstate.direction = DIR_EGRESS;
#else
	qstate.slave_id = PB_SLAVE_ID_CPU;
#endif
	qstate.pbn = apm_qm_get_ib_pbn(qm_ip, IP_CPU0, IP_CPU0, qstate.mb_id);
	qstate.q_type = P_QUEUE;
	qstate.msg_size = MSG_32B;
	qstate.q_size = desc_size;
	qstate.thr_set = 1;

	if ((rc = apm_qm_qstate_wr(&qstate)) != 0) {
		QM_PRINT("Unable to configure completion queue state for QM %d "
			"error %d\n", qm_ip, rc);
		return rc;
	} 

	if ((rc = apm_qm_pb_config(qstate.ip_blk, qstate.slave_id,
			qstate.pbn, qstate.q_id, 0, 0)) != 0) {
		QM_PRINT("Unable to configure completion queue PBN for QM %d "
			"error %d\n", qm_ip, rc);
		return rc;
	}
	/* Also reset the slot and num message in PBN */
	/*apm_qm_pb_clr(qstate.ip_blk, qstate.slave_id, qstate.pbn);*/

	QM_DEV(qm_ip)comp_qstate = &QM_DEV(qm_ip)queue_states[qstate.q_id];
	return 0;
}

int apm_qm_queue_clr(u32 qm_ip, u32 sqid, u32 eqid)
{
	struct apm_qm_raw_qstate raw_qstate;
	/*struct apm_qm_pqstate *pq;*/
	int i;

	memset(&raw_qstate, 0, sizeof(struct apm_qm_raw_qstate));

#if 0
	pq = (struct apm_qm_pqstate *) &raw_qstate;
	/* Configure domain protection field */
	pq->queue_dom = 0x0;
	pq->allowed_dom = 0xF;
	pq->not_insert_dom = 0x1;
#endif
	for (i = sqid; i < eqid; i++) {
		apm_qm_raw_qstate_wr(qm_ip, i, &raw_qstate);
	}
	return 0;
}

int apm_qm_init_queue(u32 qm_ip, u32 no_of_queues)
{
	u32 i;
	int rc = 0;

	/* QM INIT */
#ifdef CONFIG_APM_QM_QUEUE_LOCATION
	if (mem_vaddr == NULL) {
		mem_vaddr = ioremap_nocache(mem_paddr, 0x80000);
		QM_DBG("OCM Buffer PADDR: 0x%llx  VADDR: 0x%p\n",
			mem_paddr, mem_vaddr);
	}
#endif
#if !defined(BOOTLOADER)
	QM_DEV(qm_ip)q_raw_states = MEMALLOC(QM_MAX_QUEUES * sizeof(struct apm_qm_raw_qstate));
	memset(QM_DEV(qm_ip)q_raw_states, 0, QM_MAX_QUEUES * sizeof(struct apm_qm_raw_qstate));
#endif
	QM_DEV(qm_ip)queue_states = MEMALLOC(QM_MAX_QUEUES * sizeof(struct apm_qm_qstate));
	memset(QM_DEV(qm_ip)queue_states, 0, QM_MAX_QUEUES * sizeof(struct apm_qm_qstate));

	for (i = 0; i < QM_MAX_QUEUES; i++) {
		QM_DEV(qm_ip)queue_states[i].q_id = i;
		QM_DEV(qm_ip)pbn_valid[i] = 0;
		QM_DEV(qm_ip)q_to_mb[i] = 0;
	}
	for (i = 0; i < MAX_MAILBOXS; i++) {
		QM_DEV(qm_ip)mb_to_q[i] = 0;
		QM_DEV(qm_ip)ib_mbox_used[i] = 0;
		QM_DEV(qm_ip)ib_mb_pending_chk[i] = 0;		
	}

	apm_qm_slave_id_map_init();
	/* Clear all HW queue state in case they were not de-activated */
	apm_qm_queue_clr(qm_ip, QM_DEV(qm_ip)first_qid, QM_DEV(qm_ip)max_clr_qid);

	apm_qm_qid_id_init(qm_ip, QM_DEV(qm_ip)start_qid, QM_DEV(qm_ip)max_qid);
	apm_qm_pbn_init(qm_ip);

	/* configure static queue descriptors (mainly QM-lite queues) */
	if ((rc = apm_qm_config_qstate(no_of_queues)) != 0) {
		QM_PRINT("Error in config static queue database\n");
		return rc;
	}

	/* Enable QPcore and assign error queue from Core 0 */
	if (qm_cinfo.is_smp)
		if ((rc = apm_qm_init_errq(qm_ip, 0)) != 0)
			QM_PRINT("Error in apm_qm_init_errq\n");

	rc |= apm_qm_create_compl_queue(qm_ip, SIZE_2KB);

	return rc;
}


/* free all the qstates, called only from QM driver */
int apm_qm_free_qstates(u32 qm_ip)
{
	u32 qnum;
	int rc=0;
	struct apm_qm_raw_qstate pq;

	for (qnum=0 ; qnum < QM_MAX_QUEUES ; qnum++) {
		if (QM_DEV(qm_ip)queue_states[qnum].valid) {
			QM_PRINT("WARNING: Freeing up qm_ip: %d, queue: %d\n", qm_ip, qnum);

#ifndef CONFIG_APM_QM_QUEUE_LOCATION
			/* free qaddr */
			MEMFREE((void *)QM_DEV(qm_ip)queue_states[qnum].startptr);
#endif

			/* delete queue in hardware */
			memset(&pq, 0, sizeof(pq));
			rc = apm_qm_raw_qstate_wr(qm_ip, qnum, &pq);
		}
	}

#if !defined(BOOTLOADER)
	MEMFREE((void *)QM_DEV(qm_ip)q_raw_states);
#endif
	MEMFREE((void *)QM_DEV(qm_ip)queue_states);

	return rc;
}


struct apm_qm_qstate *apm_qm_get_compl_queue(u32 qm_ip)
{
	return QM_DEV(qm_ip)comp_qstate;
}

u32 apm_qm_get_compl_queue_size(u32 qm_ip)
{
	u32 q_size = 0;
	struct apm_qm_qstate *compl_queue = apm_qm_get_compl_queue(qm_ip);

	switch (compl_queue->q_size) {
	case SIZE_512B:
		q_size = 512;
		break;
	case SIZE_2KB:
		q_size = 2 * 1024;
		break;
	case SIZE_16KB:
		q_size = 16 * 1024;
		break;
	case SIZE_64KB:
		q_size = 64 * 1024;
		break;
	case SIZE_512KB:
		q_size = 512 * 1024;
		break;
	}
	return q_size;
}

int apm_qm_alloc_q(struct apm_qm_qalloc *qalloc)
{
	int rc = 0, is_fp = 0;
	struct apm_qm_qstate *qstate = qalloc->qstates;
	int i, qid;
	u32 qm_ip = qalloc->qm_ip_blk;

	/* configure queue state */
	for (i = 0; i < qalloc->q_count; i++) {
		qid = apm_qm_qid_get(qm_ip);
		if (qid < 0) {
			QM_PRINT("Not enough queues available\n");
			return -1;
		}

		qstate->src_ip_blk = qalloc->ip_blk;
		qstate->ip_blk = qm_ip;
		qstate->cpu_id = qalloc->cpu_id;
		qstate->valid = 1;
		qstate->q_type = qalloc->q_type;
		qstate->q_start_addr = qalloc->qaddr;
		qstate->q_size = qalloc->qsize;
		qstate->thr_set = qalloc->thr_set;
		qstate->direction = qalloc->direction;
		qstate->q_id = qid;
		qstate->parent_vqid = qalloc->parent_vq;
		if (qalloc->vqen == ENABLE_VQ) {
			qstate->vqen = qalloc->vqen;
			qstate->parent_vqid = qalloc->parent_vq;
		}
#ifdef QM_DEBUG
		if (qstate->vqen)
			QM_PRINT("Parent VQID %d\n", qstate->parent_vqid);
#endif

		/* mailbox assignment */
		if (qalloc->direction) { /* Egress direction */
#if defined(CONFIG_MSLIM) || defined(CONFIG_ARCH_MSLIM)
			if (qstate->src_ip_blk == IP_MSLIM)
				qstate->mb_id = apm_qm_get_ib_mb(qm_ip, qalloc->cpu_id, 0);
			else
#endif
			qstate->mb_id = apm_qm_get_ob_mb(qm_ip, qalloc->cpu_id, 
				qalloc->ip_blk,
				qalloc->q_type == FREE_POOL);
			if (qstate->vqen != ENABLE_VQ) 
				qstate->slave_id = apm_qm_get_slave_id(qalloc->ip_blk);
		} else { /* Ingress direction */
			qstate->mb_id = apm_qm_get_ib_mb(qm_ip, qalloc->cpu_id, 
				qalloc->ip_blk);		
			if (qstate->vqen != ENABLE_VQ)
				qstate->slave_id = PB_SLAVE_ID_CPU;
		}

		/* Prefetch buffer number assignment */
		if (qalloc->q_type == FREE_POOL) {
			qstate->pbn = apm_qm_get_fp_pbn(qm_ip, qalloc->cpu_id,
				qalloc->ip_blk);			
			is_fp = 1;
		} else if (qstate->vqen != ENABLE_VQ) {
			if (qalloc->direction) /* Egress direction */
#if defined(CONFIG_MSLIM) || defined(CONFIG_ARCH_MSLIM)
				if (qstate->src_ip_blk == IP_MSLIM)
					qstate->pbn = apm_qm_get_ib_pbn(qm_ip, qalloc->cpu_id,
						qalloc->ip_blk, qstate->mb_id);
				else					
#endif
				qstate->pbn = apm_qm_get_ob_pbn(qm_ip,
					qalloc->cpu_id, qalloc->ip_blk);

			else /* PBN is same as MB */
				qstate->pbn = apm_qm_get_ib_pbn(qm_ip,
					qalloc->cpu_id, qalloc->ip_blk,
					qstate->mb_id);
		}

		/* CPU is enqueuing and wants to check fill status interrupt */
		if (qalloc->direction && qalloc->en_fill_chk) {
			qstate->cpu_notify = qalloc->cpu_id + 1; /* trigger interrupt to this CPU */
			qstate->cfgsaben = 1;
		}

		if (qm_ip == IP_BLK_QML && qstate->slave_id == PB_SLAVE_ID_CPU &&
			qalloc->qml_cpu_pbn_cfg) {
			qstate->qml_cpu_pbn_cfg = qalloc->qml_cpu_pbn_cfg;
			apm_qml_cpu_pbn_qnum(qstate->q_id);
		}

		if ((rc = apm_qm_qstate_wr(qstate)) != 0) {
			QM_PRINT("Unable to write queue state error %d\n", rc);
			break;
		}

		QMCORE_PRINT("PQueue configuration\n");
		QMCORE_PRINT("    IP blk: %d\n", qstate->ip_blk);
		QMCORE_PRINT("  Slave ID: %d\n", qstate->slave_id);
		QMCORE_PRINT("       PBN: %d\n", qstate->pbn);
		QMCORE_PRINT("  Queue ID: %d\n", qstate->q_id);
		QMCORE_PRINT("     MB ID: %d\n", qstate->mb_id);
		QMCORE_PRINT("Queue Type: %d\n", qstate->q_type);

		if ((rc = apm_qm_pb_config(qstate->ip_blk, qstate->slave_id,
				qstate->pbn, qstate->q_id, is_fp, 0)) != 0) {
			QM_PRINT("Unable to write PBN error %d\n", rc);
			break;
		}

		qstate++;
	}

	return rc;
}

int apm_qm_free_q(struct apm_qm_qstate *qstate)
{
       	u32 qm_ip, qid, mbid, cpu_id, ip_blk, pbn;
	u8 qtype;
	u32 data;

	qm_ip = qstate->ip_blk;
	qid   = qstate->q_id;
	mbid  = qstate->mb_id;
	cpu_id = qstate->cpu_id;
	ip_blk = qstate->src_ip_blk;
	qtype  = qstate->q_type;
	pbn   = qstate->pbn;

	apm_qm_qid_free(qm_ip, qid);

	/* Ingress direction */
       	if (!qstate->direction) {
		QM_DEV(qm_ip)ib_mbox_used[mbid] = 0;
#ifdef CONFIG_APM_QM_ALTERNATE_DEQUEUE
	       	apm_qm_rd32(qm_ip, CSR_QM_MBOX_NE_INT_MODE_ADDR, &data);
	       	data &= ~(1U << (31 - mbid));
	       	apm_qm_wr32(qm_ip, CSR_QM_MBOX_NE_INT_MODE_ADDR, data);
#endif
	}

	/* Free up Prefetch buffer number assignment */
	if (qtype == FREE_POOL) {
		apm_qm_free_fp_pbn(qm_ip, ip_blk, pbn);
	} else if (qstate->vqen != ENABLE_VQ) {
		if (qstate->direction) /* Egress direction */
			apm_qm_free_ob_pbn(qm_ip, cpu_id, ip_blk, pbn);
		else /* PBN is same as MB */
		       	apm_qm_free_ib_pbn(qm_ip, cpu_id, ip_blk, mbid);
	}

	if (qm_ip == IP_BLK_QML && qstate->slave_id == PB_SLAVE_ID_CPU &&
		qstate->qml_cpu_pbn_cfg) {
		apm_qml_free_cpu_pbn_qnum(qid);
	}

	return 0;
}

int apm_qm_get_vq(u32 qm_ip, u32 ip_blk)
{
	int qid = apm_qm_qid_get(qm_ip);

	if (qid < 0) {
		QM_PRINT("QM virtual queue id not available\n");
		return -1;
	}
	return qid;
}

int apm_qm_alloc_vq(struct apm_qm_qalloc *qalloc, u32 qid)
{
	struct apm_qm_qstate *qstate = qalloc->qstates;
	int rc = 0, j, is_fp = 0;
	u32 qm_ip = qalloc->qm_ip_blk;

	if (qid > QM_DEV(qm_ip)max_qid || qalloc->q_count != 1) {
		QM_PRINT("QM virtual queue not available\n");
		return -1;
	} else if (qalloc->q_type != V_QUEUE) {
		QM_PRINT("Invalid parameter for VQ config\n");
		return -1;
	}

	/* configure queue state */
	qstate->src_ip_blk = qalloc->ip_blk;
	qstate->ip_blk = qm_ip;
	qstate->cpu_id = qalloc->cpu_id;
	qstate->valid = 1;
	qstate->q_type = qalloc->q_type;
	qstate->q_start_addr = qalloc->qaddr;
	qstate->q_size = qalloc->qsize;
	qstate->thr_set = qalloc->thr_set;
	qstate->direction = qalloc->direction;
	qstate->q_id = qid;
	qstate->parent_vqid = qalloc->parent_vq;
	qstate->vqen = qalloc->vqen;

	memcpy(qstate->pq_sel, qalloc->pq_sel, sizeof(qstate->pq_sel));
	memcpy(qstate->q_sel_arb, qalloc->q_sel_arb, 
		sizeof(qstate->q_sel_arb));
	memcpy(qstate->shape_rate, qalloc->shape_rate,
		sizeof(qstate->shape_rate));

	/* mailbox assignment */
	if (qalloc->direction) { /* Egress direction */
		qstate->mb_id = apm_qm_get_ob_mb(qm_ip, qalloc->cpu_id, 
			qalloc->ip_blk,	
			qalloc->q_type == FREE_POOL);
		qstate->slave_id = apm_qm_get_slave_id(qalloc->ip_blk);
	} else { /* Ingress direction */
		qstate->mb_id = apm_qm_get_ib_mb(qm_ip, qalloc->cpu_id,
			qalloc->ip_blk);	
		qstate->slave_id = PB_SLAVE_ID_CPU;
	}

	/* Prefetch buffer number assignment */
	if (qalloc->q_type == FREE_POOL) {
		qstate->pbn = apm_qm_get_fp_pbn(qm_ip, qalloc->cpu_id, 
			qalloc->ip_blk);
		is_fp = 1;
	} else {
		if (qalloc->direction) /* Egress direction */
			qstate->pbn = apm_qm_get_ob_pbn(qm_ip,
				qalloc->cpu_id, qalloc->ip_blk);
		else
			qstate->pbn = apm_qm_get_ib_pbn(qm_ip,
				qalloc->cpu_id, qalloc->ip_blk,
				qstate->mb_id);
	}

	if ((rc = apm_qm_vqstate_wr(qstate)) != 0) {
		QM_PRINT("Error in queue configuration\n");
		return rc;
	}

	QMCORE_PRINT("Virtual Queue configuration\n");
	QMCORE_PRINT("    IP blk: %d\n", qstate->ip_blk);
	QMCORE_PRINT("  Slave ID: %d\n", qstate->slave_id);
	QMCORE_PRINT("       PBN: %d\n", qstate->pbn);
	QMCORE_PRINT("  Queue ID: %d\n", qstate->q_id);
	QMCORE_PRINT("     MB ID: %d\n", qstate->mb_id);
	QMCORE_PRINT("Queue Type: %d\n", qstate->q_type);

	for (j = 0; j < 8; j++)
		QMCORE_PRINT("PQ_SEL[%d] %d Q_SEL_ARB[%d] %d RATE[%d] %d\n",
			j, qstate->pq_sel[j], j, qstate->q_sel_arb[j], 
			j, qstate->shape_rate[j]);

	if ((rc = apm_qm_pb_config(qstate->ip_blk, qstate->slave_id,
			qstate->pbn, qstate->q_id, is_fp, 1)) != 0) {
		QM_PRINT("Unable to configure virtual queue PBN error %d\n", 
			rc);
		return rc;
	}
	return rc;
}

#ifndef CONFIG_APM_QM_ALTERNATE_DEQUEUE
inline u32 apm_qm_pull_comp_msg(u32 qm_ip, u32 mb_id)
{
	/* NOTE: This function had been optimized. If you change anything,
	   re-test via IPv4 forwarding with 64B message */
	struct apm_qm_msg16 *msg16;
	u32 *slot_ptr;
	u32 uinfo;
	int NV; 

	slot_ptr = (u32 *) QM_DEV(qm_ip)mb_dq_mbox_ctxt[mb_id].cur_ptr; 
	QM_INVALIDATE_MB(qm_ip, (void *) slot_ptr, (u8 *) slot_ptr + 32); 

	/* Check signature to determine if slot has a valid message */
	if (slot_ptr[EMPTY_SLOT_INDEX] == EMPTY_SLOT) 
		return 0;

	msg16 = (struct apm_qm_msg16 *) slot_ptr;
	NV = msg16->NV;
	uinfo = msg16->UserInfo;

	QM_DBG2("Completion QM msg mailbox %d slot 0x%p\n", 
		mb_id, QM_DEV(qm_ip)mb_dq_mbox_ctxt[mb_id].cur_ptr);

	/* Mark slot empty */
	slot_ptr[EMPTY_SLOT_INDEX] = EMPTY_SLOT;
	QM_FLUSH_MB(qm_ip, (void *) slot_ptr, (u8 *) slot_ptr + 16); 

	/* Update queue statistic */
#if defined(DQM_DBG) 
	++QM_DEV(qm_ip)queue_states[QM_DEV(qm_ip)mb_to_q[mb_id]].msg_stat;
#endif
	/* Move pointer to next slot. */
	if (QM_DEV(qm_ip)mb_dq_mbox_ctxt[mb_id].cur_ptr == QM_DEV(qm_ip)mb_dq_mbox_ctxt[mb_id].last_ptr)
		QM_DEV(qm_ip)mb_dq_mbox_ctxt[mb_id].cur_ptr = 
			QM_DEV(qm_ip)mb_dq_mbox_ctxt[mb_id].first_ptr;
	else
		QM_DEV(qm_ip)mb_dq_mbox_ctxt[mb_id].cur_ptr++;

	if (!NV) {
		/* Tell QM to move to next slot */
		writel(QM_DEC_MSG_VAL(mb_id, 1), QM_B_ADDR_DEC);
	} else {
		/* For 64B message, clean the 2nd half slot */
		slot_ptr = (u32 *) QM_DEV(qm_ip)mb_dq_mbox_ctxt[mb_id].cur_ptr;
		QM_INVALIDATE_MB(qm_ip, (void *) slot_ptr, (u8 *) slot_ptr + 32);
		slot_ptr[EMPTY_SLOT_INDEX] = EMPTY_SLOT;
		QM_FLUSH_MB(qm_ip, (void *) slot_ptr, (u8 *) slot_ptr + 16); 

		/* Move pointer to next slot */
		if (QM_DEV(qm_ip)mb_dq_mbox_ctxt[mb_id].cur_ptr == 
				QM_DEV(qm_ip)mb_dq_mbox_ctxt[mb_id].last_ptr)
			QM_DEV(qm_ip)mb_dq_mbox_ctxt[mb_id].cur_ptr = 
				QM_DEV(qm_ip)mb_dq_mbox_ctxt[mb_id].first_ptr;
		else
			QM_DEV(qm_ip)mb_dq_mbox_ctxt[mb_id].cur_ptr++;

		/* Tell QM to move to next slot */
		writel(QM_DEC_MSG_VAL(mb_id, 2), QM_B_ADDR_DEC);
	}

	return uinfo;
}

#define APM_QM_PENDING_COMPL		4
inline u32 apm_qm_pull_comp_msg2(u32 qm_ip, u32 mb_id)
{
	/* NOTE: This function had been optimized. If you change anything,
	   re-test via IPv4 forwarding with 64B message */
	struct apm_qm_msg16 *msg16;
	u32 *slot_ptr;
	u32 uinfo;
	int NV; 

	slot_ptr = (u32 *) QM_DEV(qm_ip)mb_dq_mbox_ctxt[mb_id].cur_ptr;
	QM_INVALIDATE_MB(qm_ip, (void *) slot_ptr, (u8 *) slot_ptr + 32); 

	/* Check signature to determine if slot has a valid message */
	if (slot_ptr[EMPTY_SLOT_INDEX] == EMPTY_SLOT) 
		return 0;

	msg16 = (struct apm_qm_msg16 *) slot_ptr;
	NV = msg16->NV;
	uinfo = msg16->UserInfo;

	QM_DBG2("Completion QM msg mailbox %d slot 0x%p\n", 
		mb_id, QM_DEV(qm_ip)mb_dq_mbox_ctxt[mb_id].cur_ptr);

	/* Mark slot empty */
	slot_ptr[EMPTY_SLOT_INDEX] = EMPTY_SLOT;
	QM_FLUSH_MB(qm_ip, (void *) slot_ptr, (u8 *) slot_ptr + 16); 

	/* Update queue statistic */
#if defined(DQM_DBG) 
	++QM_DEV(qm_ip)queue_states[QM_DEV(qm_ip)mb_to_q[mb_id]].msg_stat;
#endif
	/* Move pointer to next slot */
	if (QM_DEV(qm_ip)mb_dq_mbox_ctxt[mb_id].cur_ptr == QM_DEV(qm_ip)mb_dq_mbox_ctxt[mb_id].last_ptr)
		QM_DEV(qm_ip)mb_dq_mbox_ctxt[mb_id].cur_ptr = 
			QM_DEV(qm_ip)mb_dq_mbox_ctxt[mb_id].first_ptr;
	else
		QM_DEV(qm_ip)mb_dq_mbox_ctxt[mb_id].cur_ptr++;

	if (!NV) {
		/* Tell QM to move to next slot */
		QM_DEV(qm_ip)queue_states[QM_DEV(qm_ip)mb_to_q[mb_id]].pending_compl++;
	} else {
		/* For 64B message, clean the 2nd half slot */
		slot_ptr = (u32 *) QM_DEV(qm_ip)mb_dq_mbox_ctxt[mb_id].cur_ptr;
		QM_INVALIDATE_MB(qm_ip, (void *) slot_ptr, (u8 *) slot_ptr + 32);
		slot_ptr[EMPTY_SLOT_INDEX] = EMPTY_SLOT;
		QM_FLUSH_MB(qm_ip, (void *) slot_ptr, (u8 *) slot_ptr + 16); 

		/* Move pointer to next slot */
		if (QM_DEV(qm_ip)mb_dq_mbox_ctxt[mb_id].cur_ptr == 
				QM_DEV(qm_ip)mb_dq_mbox_ctxt[mb_id].last_ptr)
			QM_DEV(qm_ip)mb_dq_mbox_ctxt[mb_id].cur_ptr = 
				QM_DEV(qm_ip)mb_dq_mbox_ctxt[mb_id].first_ptr;
		else
			QM_DEV(qm_ip)mb_dq_mbox_ctxt[mb_id].cur_ptr++;

		QM_DEV(qm_ip)queue_states[QM_DEV(qm_ip)mb_to_q[mb_id]].pending_compl += 2;
	}
	if (QM_DEV(qm_ip)queue_states[QM_DEV(qm_ip)mb_to_q[mb_id]].pending_compl >= 
			APM_QM_PENDING_COMPL) {
		/* Tell QM to move to next slot */
		writel(QM_DEC_MSG_VAL(mb_id, APM_QM_PENDING_COMPL), QM_B_ADDR_DEC);
		QM_DEV(qm_ip)queue_states[QM_DEV(qm_ip)mb_to_q[mb_id]].pending_compl -= 
			APM_QM_PENDING_COMPL;
	}
	return uinfo;
}

int apm_qm_pull_comp_flush(u32 qm_ip, u32 mb_id)
{
	struct apm_qm_qstate *qstate = &QM_DEV(qm_ip)queue_states[QM_DEV(qm_ip)mb_to_q[mb_id]];

	while (qstate->pending_compl) {
		if (qstate->pending_compl < APM_QM_PENDING_COMPL) {
			writel(QM_DEC_MSG_VAL(mb_id, qstate->pending_compl), QM_B_ADDR_DEC);
			qstate->pending_compl = 0;
			return 0;
		} else {
			writel(QM_DEC_MSG_VAL(mb_id, APM_QM_PENDING_COMPL), QM_B_ADDR_DEC);
			qstate->pending_compl -= APM_QM_PENDING_COMPL;
		}
	}
	return 0;
}

int apm_qm_pull_msg(struct apm_qm_msg_desc *msg_desc)
{
	/* NOTE: This function had been optimized. If you change anything,
	   re-test via IPv4 forwarding with 64B message */
	u32 qm_ip = msg_desc->qm_ip_blk;
	u8 mb_id = msg_desc->mb_id;
	volatile u32 *slot_ptr;
	u32 *temp;

	slot_ptr = (u32 *) QM_DEV(qm_ip)mb_dq_mbox_ctxt[mb_id].cur_ptr;
	QM_INVALIDATE_MB(qm_ip, (void *) slot_ptr, (u8 *) slot_ptr + 32); 

	/* Check if slot has a message */
	if (slot_ptr[EMPTY_SLOT_INDEX] == EMPTY_SLOT)
		return -1;	

	/* Copy out the message */
	temp = (u32 *) msg_desc->msg;
	if (msg_desc->is_msg16) {
		memcpy(temp, (const void*)slot_ptr, 16);
	} else {
		memcpy(temp, (const void*)slot_ptr, 32);
	}

	QM_DBG2("Pull QM msg mailbox %d slot 0x%p\n", 
		mb_id, QM_DEV(qm_ip)mb_dq_mbox_ctxt[mb_id].cur_ptr);

	/* Move pointer to next slot */
	if (QM_DEV(qm_ip)mb_dq_mbox_ctxt[mb_id].cur_ptr == QM_DEV(qm_ip)mb_dq_mbox_ctxt[mb_id].last_ptr)
		QM_DEV(qm_ip)mb_dq_mbox_ctxt[mb_id].cur_ptr = 
			QM_DEV(qm_ip)mb_dq_mbox_ctxt[mb_id].first_ptr;
	else
		QM_DEV(qm_ip)mb_dq_mbox_ctxt[mb_id].cur_ptr++;

	/* Mark slot empty */
	slot_ptr[EMPTY_SLOT_INDEX] = EMPTY_SLOT;
	QM_FLUSH_MB(qm_ip, (void *) slot_ptr, (u8 *) slot_ptr + 16);

	/* Update queue statistic */
#if defined(DQM_DBG) 
	++QM_DEV(qm_ip)queue_states[QM_DEV(qm_ip)mb_to_q[mb_id]].msg_stat;
#endif	
	/* Do not remove this statement as this variable is cached in L2 and
	   more efficient than the NV test in next statement. */
	if (msg_desc->is_msg16) {
		/* Tell QM to move to next slot */
		writel(QM_DEC_MSG_VAL(mb_id, 1), QM_B_ADDR_DEC);
		return 0;
	}

	if (!((struct apm_qm_msg16 *) msg_desc->msg)->NV) {		
		/* Tell QM to move to next slot */		
		writel(QM_DEC_MSG_VAL(mb_id, 1), QM_B_ADDR_DEC);
	} else {	
		/* For 64B message, read out 2nd half slot */
		slot_ptr = (u32 *) QM_DEV(qm_ip)mb_dq_mbox_ctxt[mb_id].cur_ptr;
		QM_INVALIDATE_MB(qm_ip, (void *) slot_ptr, (u8 *) slot_ptr + 32); 

		temp += 8;
		memcpy(temp, (const void*)slot_ptr, 32);

		/* Move pointer to next slot */
		if (QM_DEV(qm_ip)mb_dq_mbox_ctxt[mb_id].cur_ptr == 
				QM_DEV(qm_ip)mb_dq_mbox_ctxt[mb_id].last_ptr)
			QM_DEV(qm_ip)mb_dq_mbox_ctxt[mb_id].cur_ptr =
				QM_DEV(qm_ip)mb_dq_mbox_ctxt[mb_id].first_ptr;
		else
			QM_DEV(qm_ip)mb_dq_mbox_ctxt[mb_id].cur_ptr++;

		/* Mark 2nd slot empty */
		slot_ptr[EMPTY_SLOT_INDEX] = EMPTY_SLOT;
		QM_FLUSH_MB(qm_ip, (void *) slot_ptr, (u8 *) slot_ptr + 16);

		/* Tell QM to move to next slot */		
		writel(QM_DEC_MSG_VAL(mb_id, 2), QM_B_ADDR_DEC);
	}
	return 0;
}

int apm_qm_fp_alloc_buf(struct apm_qm_msg_desc *msg_desc)
{
	/* NOTE: This function had been optimized. If you change anything,
	   re-test via IPv4 forwarding with 64B message */
	u32 qm_ip = msg_desc->qm_ip_blk;
	u8 mb_id = msg_desc->mb_id;
	volatile u32 *slot_ptr;
	u32 *temp;
	u8 pbn = mb_id + CPU_FP_MB_PBN_OFFSET;

	slot_ptr = (u32 *) QM_DEV(qm_ip)mb_fp_mbox_ctxt[mb_id].cur_ptr;
	QM_INVALIDATE_MB(qm_ip, (void *) slot_ptr, (u8 *) slot_ptr + 16); 

	/* Make sure there is a message to read */
	if (slot_ptr[EMPTY_SLOT_INDEX] == EMPTY_SLOT) {
		/* message slot is empty */
		QM_DBG2("No msg to dequeue from free pool queue %d\n", 
			msg_desc->qid);
		return -1;
	}

	/* read message from the current slot */
	temp = (u32 *) msg_desc->msg;
	memcpy(temp, (const void *)slot_ptr, 16);

	/* Move to next slot */
	if (QM_DEV(qm_ip)mb_fp_mbox_ctxt[msg_desc->mb_id].cur_ptr == 
			QM_DEV(qm_ip)mb_fp_mbox_ctxt[msg_desc->mb_id].last_ptr)
		QM_DEV(qm_ip)mb_fp_mbox_ctxt[msg_desc->mb_id].cur_ptr = 
			QM_DEV(qm_ip)mb_fp_mbox_ctxt[msg_desc->mb_id].first_ptr;
	else
		QM_DEV(qm_ip)mb_fp_mbox_ctxt[msg_desc->mb_id].cur_ptr++;

	/* Clear slot marker */
	slot_ptr[EMPTY_SLOT_INDEX] = EMPTY_SLOT;
	QM_FLUSH_MB(qm_ip, (void *) slot_ptr, (u8 *) slot_ptr + 16);

	/* Decrement number of messages in this slave id and PBN */
	writel(QM_DEC_MSG_VAL(pbn, 1), QM_B_ADDR_DEC);

	return 0;
}
#endif

int apm_qml_push_msg(struct apm_qm_msg_desc *msg_desc)
{
	/* NOTE: This function had been optimized. If you change anything,
	   re-test via IPv4 forwarding with 64B message */
	u32 qm_ip = msg_desc->qm_ip_blk;
	struct apm_qm_msg16 *msg16 = (struct apm_qm_msg16 *) msg_desc->msg;
	u8 qid = msg_desc->qid;
	u8 *tailptr = QM_DEV(qm_ip)queue_states[qid].tailptr;
	struct apm_qm_qstate *qstate = &QM_DEV(qm_ip)queue_states[qid];
	u32 *temp;

	/* Write message at tail pointer of the queue descriptor */
	temp = (u32 *) msg_desc->msg;
	memcpy(tailptr, temp, 32);
	QM_FLUSH_MB(qm_ip, tailptr, tailptr + 32);
	//TODO
	QM_DBG("Push QM msg queue %d pointer 0x%p %dB, fabric 0x%x\n", 
		qid, tailptr, msg16->NV ? 64 : 32, QM_ENQ_B_ADDR_QID(qid));

	/* Adjust tail pointer.
	   This version is more efficient than have else statement. */
	qstate->tailptr += 32;
	if (qstate->tailptr == qstate->endptr) 
		qstate->tailptr = qstate->startptr;

	/* Update queue statistic */
#if defined(DQM_DBG) 
	++qstate->msg_stat;
#endif	

	if (!msg16->NV) {
		/* Tell QM we read out 32B */
		QM_MSYNC
		writel(1, QM_ENQ_B_ADDR_QID(qid));
	} else {
		/* For 64B message, write out remaining */
		tailptr = qstate->tailptr;

		/* Write remaining message at tail pointer */
		temp += 8;
		memcpy(tailptr, temp, 32);
		QM_FLUSH_MB(qm_ip, tailptr, tailptr + 32);

		/* Adjust tail pointer.
		   This version is more efficient than have else statement. */
		qstate->tailptr += 32;
		if (qstate->tailptr == qstate->endptr) 
			qstate->tailptr = qstate->startptr;

		/* Tell QM we wrote 64 byte message */
		QM_MSYNC
		writel(2, QM_ENQ_B_ADDR_QID(qid));
	}

	return 0;
}

#ifndef CONFIG_APM_QM_ALTERNATE_ENQUEUE
int apm_qm_push_msg(struct apm_qm_msg_desc *msg_desc)
{
	/* NOTE: This function had been optimized. If you change anything,
	   re-test via IPv4 forwarding with 64B message */
	u32 qm_ip = msg_desc->qm_ip_blk;
	volatile u32 *slot_ptr;
	u32 *temp;
	u32 mb_desc, cur_slot, init_slot;
	u8 mb_id = QM_DEV(qm_ip)q_to_mb[msg_desc->qid];
#if defined (CONFIG_MB_CHECK_TX_MSG)
	int wait_required;
#endif
	volatile struct apm_qm_msg32 *mb_slot_ptr;
	struct apm_qm_msg32 *msg = (struct apm_qm_msg32 *) msg_desc->msg;

	temp = (u32 *) msg_desc->msg;
	cur_slot = QM_DEV(qm_ip)mb_enq_mbox_ctxt[mb_id].slot;
	QM_DBG2("Push QM msg queue %d mailbox %d slot %d\n",
		msg_desc->qid, mb_id, cur_slot);

#ifdef CONFIG_MB_CHECK_TX_MSG
	if (msg->msg16.NV &&
		cur_slot == QM_DEV(qm_ip)mb_enq_mbox_ctxt[mb_id].last_slot)
		wait_required = 1;
	else
		wait_required = 0;

	if (cur_slot == 0 || wait_required) {
		static u32 enq_csr_lookup[16] = {
			CSR_ENQ_STATUS_0_ADDR, CSR_ENQ_STATUS_1_ADDR, CSR_ENQ_STATUS_2_ADDR, CSR_ENQ_STATUS_3_ADDR,
			CSR_ENQ_STATUS_4_ADDR, CSR_ENQ_STATUS_5_ADDR, CSR_ENQ_STATUS_6_ADDR, CSR_ENQ_STATUS_7_ADDR,
			CSR_ENQ_STATUS_8_ADDR, CSR_ENQ_STATUS_9_ADDR, CSR_ENQ_STATUS_10_ADDR, CSR_ENQ_STATUS_11_ADDR,
			CSR_ENQ_STATUS_12_ADDR, CSR_ENQ_STATUS_13_ADDR, CSR_ENQ_STATUS_14_ADDR, CSR_ENQ_STATUS_15_ADDR };
		static u32 st_byte_lookup[2] = {    /* mailbox 0 is at b[31:16] */
			16, 0
		};
		static u32 st_bit_lookup[16] = {
			15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0
		};
		/* check mailbox status after enq */
		u32 val, status_byte;
		while (1) {
			apm_qm_rd32(qm_ip, enq_csr_lookup[mb_id / 2], &val);
			status_byte = val >> st_byte_lookup[mb_id % 2];
			if (!((status_byte >> st_bit_lookup[cur_slot / 16]) & 0x1))
				break;
		}
	}
#endif

	init_slot = cur_slot;
	mb_slot_ptr = (struct apm_qm_msg32 *) &QM_DEV(qm_ip)enq_mboxes[mb_id];
	mb_slot_ptr += cur_slot;
	slot_ptr = (u32 *) mb_slot_ptr;

	/* write message in the current slot */
	slot_ptr[0] = temp[0];
	slot_ptr[1] = temp[1];
	slot_ptr[2] = temp[2];
	slot_ptr[3] = temp[3];
	slot_ptr[4] = temp[4];
	slot_ptr[5] = temp[5];
	slot_ptr[6] = temp[6];
	slot_ptr[7] = temp[7];
	QM_FLUSH_MB(qm_ip, (void *) slot_ptr, (u8 *) slot_ptr + 32);

	/* adjust current slot.
	   This version is more efficient than have else statement. */
	QM_DEV(qm_ip)mb_enq_mbox_ctxt[mb_id].slot++;
	if (QM_DEV(qm_ip)mb_enq_mbox_ctxt[mb_id].slot == QM_DEV(qm_ip)mb_enq_mbox_ctxt[mb_id].total_slot)
		QM_DEV(qm_ip)mb_enq_mbox_ctxt[mb_id].slot = 0;

	/* prepare qm base address to write to */
	if (!msg->msg16.NV) {
		/* prepare data to write to qm base address */
		mb_desc = (mb_id << APM_QM_MBID_SHIFT) | 
			(init_slot << APM_QM_SLOTID_SHIFT) | 
			SIZE_32_MSG;
	} else {
		cur_slot = QM_DEV(qm_ip)mb_enq_mbox_ctxt[mb_id].slot;
		mb_slot_ptr = (struct apm_qm_msg32 *) &QM_DEV(qm_ip)enq_mboxes[mb_id];
		mb_slot_ptr += cur_slot;
		slot_ptr = (u32 *) mb_slot_ptr;

		/* adjust current slot .
		   This version is more efficient than have else statement. */
		QM_DEV(qm_ip)mb_enq_mbox_ctxt[mb_id].slot++;
		if (QM_DEV(qm_ip)mb_enq_mbox_ctxt[mb_id].slot == 
				QM_DEV(qm_ip)mb_enq_mbox_ctxt[mb_id].total_slot)
			QM_DEV(qm_ip)mb_enq_mbox_ctxt[mb_id].slot = 0;

		/* write remaining 32 byte message in the next slot */
		slot_ptr[0] = temp[8];
		slot_ptr[1] = temp[9];
		slot_ptr[2] = temp[10];
		slot_ptr[3] = temp[11];
		slot_ptr[4] = temp[12];
		slot_ptr[5] = temp[13];
		slot_ptr[6] = temp[14];
		slot_ptr[7] = temp[15];
		QM_FLUSH_MB(qm_ip, (void *) slot_ptr, (u8 *) slot_ptr + 32);

		/* prepare data to write to qm base address */
		mb_desc = (mb_id << APM_QM_MBID_SHIFT) | 
			(init_slot << APM_QM_SLOTID_SHIFT) | 
			SIZE_64_MSG;
	}

	/* Update queue statistic */
#if defined(DQM_DBG) 
	++QM_DEV(qm_ip)queue_states[msg_desc->qid].msg_stat;
#endif	
	/* Tell QM */
	QM_MSYNC
	writel(mb_desc, (u32 *) QM_B_ADDR_QID(msg_desc->qid));
	return 0;
}

int apm_qm_fp_dealloc_buf(struct apm_qm_msg_desc *msg_desc)
{
	/* NOTE: This function had been optimized. If you change anything,
	   re-test via IPv4 forwarding with 64B message */
	u32 qm_ip = msg_desc->qm_ip_blk;
	volatile u32 *slot_ptr;
	u32 *temp;
	u32 mb_desc = 0;
	volatile struct apm_qm_msg32 *mb_slot_ptr;
	u8 mb_id = QM_DEV(qm_ip)q_to_mb[msg_desc->qid];

	temp = (u32 *) msg_desc->msg;

	mb_slot_ptr = (struct apm_qm_msg32 *) &QM_DEV(qm_ip)enq_mboxes[mb_id];
	mb_slot_ptr += QM_DEV(qm_ip)mb_enq_mbox_ctxt[mb_id].slot;
	slot_ptr = (u32 *) mb_slot_ptr;

#ifdef CONFIG_MB_CHECK_TX_MSG
	if (QM_DEV(qm_ip)mb_enq_mbox_ctxt[mb_id].slot == 0) {
		static u32 enq_csr_lookup[16] = {
			CSR_ENQ_STATUS_0_ADDR, CSR_ENQ_STATUS_1_ADDR, CSR_ENQ_STATUS_2_ADDR, CSR_ENQ_STATUS_3_ADDR,
			CSR_ENQ_STATUS_4_ADDR, CSR_ENQ_STATUS_5_ADDR, CSR_ENQ_STATUS_6_ADDR, CSR_ENQ_STATUS_7_ADDR,
			CSR_ENQ_STATUS_8_ADDR, CSR_ENQ_STATUS_9_ADDR, CSR_ENQ_STATUS_10_ADDR, CSR_ENQ_STATUS_11_ADDR,
			CSR_ENQ_STATUS_12_ADDR, CSR_ENQ_STATUS_13_ADDR, CSR_ENQ_STATUS_14_ADDR, CSR_ENQ_STATUS_15_ADDR
		};	
		static u32 st_byte_lookup[2] = {    /* mailbox 0 @  b[31:16], slot 0 @ bit 15, This is 16-bits */
			16, 0
		};
		/* check mailbox status after enq */
		u32 val, status_byte;
		/* wait for QM to be done reading the message from mailbox */
		while (1) {   /* */
			apm_qm_rd32(qm_ip, enq_csr_lookup[mb_id / 2], &val);
			status_byte = val >> st_byte_lookup[mb_id % 2];
			if (!(status_byte &  (0x1 << 15)))
				break;
		}
	}
#endif
	/* write message in the current slot */
	slot_ptr[0] = temp[0];
	slot_ptr[1] = temp[1];
	slot_ptr[2] = temp[2];
	slot_ptr[3] = temp[3];
	QM_FLUSH_MB(qm_ip, (void *) slot_ptr, (u8 *) slot_ptr + 16);

	QM_DBG2("Dealloc QM msg queue %d mailbox %d slot %d\n",
			msg_desc->qid, mb_id, QM_DEV(qm_ip)mb_enq_mbox_ctxt[mb_id].slot);

	/* prepare data to write to qm base address */
	mb_desc = (mb_id << APM_QM_MBID_SHIFT) | 
		(QM_DEV(qm_ip)mb_enq_mbox_ctxt[mb_id].slot << APM_QM_SLOTID_SHIFT) |
		SIZE_16_MSG;
	/* Move pointer to next slot.
	   This version is more efficient than have else statement. */
	QM_DEV(qm_ip)mb_enq_mbox_ctxt[mb_id].slot++;
	if (QM_DEV(qm_ip)mb_enq_mbox_ctxt[mb_id].slot == QM_DEV(qm_ip)mb_enq_mbox_ctxt[mb_id].total_slot)
		QM_DEV(qm_ip)mb_enq_mbox_ctxt[mb_id].slot = 0;

	/* Tell QM */
	QM_MSYNC
	writel(mb_desc, (u32 *) QM_B_ADDR_QID(msg_desc->qid));

	return 0;
}

int apm_qm_fp_dealloc_flush(u32 qm_ip, u32 qid)
{
	return 0;
}
#endif

int apm_qml_fp_dealloc_buf(struct apm_qm_msg_desc *msg_desc)
{
#if 0
	volatile u32 *slot_ptr;
	u32 *temp;
	u32 mb_desc = 0;
	u8 mb_id = apm_qm_get_ib_mb(IP_BLK_QML, 0, IP_MAX);	/* IP_MAX for default */
	volatile struct apm_qm_msg32 *mb_slot_ptr;

	/* Check if QML hardware available */
	if (qm_cinfo.is_noqml)
		return -1;

	temp = (u32 *) msg_desc->msg;

	mb_slot_ptr = (struct apm_qm_msg32 *) &QM_DEV(IP_BLK_QML)enq_mboxes[mb_id];
	mb_slot_ptr += QM_DEV(IP_BLK_QML)mb_enq_mbox_ctxt[mb_id].slot;
	slot_ptr = (u32 *) mb_slot_ptr;

	/* write message in the current slot */
	*slot_ptr++ = *temp++; *slot_ptr++ = *temp++;
	*slot_ptr++ = *temp++; *slot_ptr++ = *temp++;

	/* prepare data to write to qm base address */
	mb_desc = (mb_id << APM_QM_MBID_SHIFT) | 
		(QM_DEV(IP_BLK_QML)mb_enq_mbox_ctxt[mb_id].slot << APM_QM_SLOTID_SHIFT) |
		SIZE_16_MSG;
	QM_DEV(IP_BLK_QML)mb_enq_mbox_ctxt[mb_id].slot++;
	if (QM_DEV(IP_BLK_QML)mb_enq_mbox_ctxt[mb_id].slot == QM_DEV(IP_BLK_QML)mb_enq_mbox_ctxt[mb_id].total_slot)
		QM_DEV(IP_BLK_QML)mb_enq_mbox_ctxt[mb_id].slot = 0;

	QM_MSYNC
	writel(mb_desc, (u32 *)QM_B_ADDR_QID(msg_desc->qid));
#else
	/* NOTE: This function had been optimized. If you change anything,
	   re-test via IPv4 forwarding with 64B message */
	u32 qm_ip = msg_desc->qm_ip_blk;
	u8 qid = msg_desc->qid;
	void *tailptr = QM_DEV(qm_ip)queue_states[qid].tailptr;
	struct apm_qm_qstate *qstate = &QM_DEV(qm_ip)queue_states[qid];
	struct apm_qm_msg16 *msg16 = (struct apm_qm_msg16 *) msg_desc->msg;

	/* Write message at tail pointer. */
	memcpy(tailptr, msg16, 16);
	QM_FLUSH_MB(qm_ip, tailptr, (u8 *) tailptr + 16);

	QM_DBG2("Dealloc QM msg queue %d pointer 0x%p %dB\n", 
		qid, tailptr, msg16->NV ? 64 : 32);

	/* Adjust tail pointer.
	   This version is more efficient than have else statement. */
	qstate->tailptr += 16;
	if (qstate->tailptr == qstate->endptr) 
		qstate->tailptr = qstate->startptr;

	/* Tell QM we wrote 32B */
#ifdef CONFIG_APM_QM_FP_DEALLOC_CACHE
	/*
	 * This section causes a cache hit and slow down the 
	 * mb enq, so need to find a better mechanism
	 */
#define APM_QM_FP_DEALLOC_CACHE		6
	if (++qstate->pending_dealloc >= APM_QM_FP_DEALLOC_CACHE) {	
		QM_MSYNC
		writel(APM_QM_FP_DEALLOC_CACHE, QM_ENQ_B_ADDR_QID(qid));
		qstate->pending_dealloc -= APM_QM_FP_DEALLOC_CACHE;
	}
#else
	writel(1, QM_ENQ_B_ADDR_QID(qid));
#endif
#endif
	return 0;
}

int apm_qml_fp_dealloc_flush(u32 qm_ip, u32 qid)
{
	struct apm_qm_qstate *qstate = &QM_DEV(qm_ip)queue_states[qid];

	if (qstate->pending_dealloc) {	
		QM_MSYNC
		writel(qstate->pending_dealloc, QM_ENQ_B_ADDR_QID(qid));
		qstate->pending_dealloc = 0;
		QM_MSYNC
	}
	return 0;
}

int apm_qml_pull_msg(struct apm_qm_msg_desc *msg_desc)
{
	u32 *temp;
/*	u32 cnt = 0, val = 0;	*/
	u32 qid;
	u8 *headptr;
	u32 qm_ip;

	qm_ip = msg_desc->qm_ip_blk;
	qid = msg_desc->qid;

	QM_DBG("apm_qml_pull_msg qm_ip: %d\tqid: %d\n", /*__func__,*/ qm_ip, qid);

	/* check for message available */
#if 0  /* For Mailbox interface only */
	while (1) {
		apm_qm_rd32(qm_ip, CSR_QM_MBOX_NE_ADDR, &val);

		if (QUEUE_NOT_EMPTY_RD(val)) {
			QM_DBG("qml: Found a message in mailbox 0\n");
			break;
		}
		if (cnt++ > MAX_DELAY_CNT) {
			QM_DBG("qml: Not found any message in mailbox0\n");
			return -1;
		}
	}

	/* make sure to read message from work queue of CPU */
	headptr = QM_DEV(qm_ip)queue_states[qid].headptr;

#else  /* For non-mailbox interface only */

	/* make sure to read message from work queue of CPU */
	headptr = QM_DEV(qm_ip)queue_states[qid].headptr;
	temp = (u32 *)headptr;
	if (temp[EMPTY_SLOT_INDEX] == EMPTY_SLOT) {
		QM_DBG("qml: Not found any message in qm_ip %d qid %d @0x%p\n", qm_ip, qid, headptr);
		return -1;
	}
	QM_DBG("qml: Found a message in mailbox 0\n");
#endif

	/* message is available, read it */
	temp = (u32 *) msg_desc->msg;
	temp[0] = ((u32 *)headptr)[0];
	temp[1] = ((u32 *)headptr)[1];
	temp[2] = ((u32 *)headptr)[2];
	temp[3] = ((u32 *)headptr)[3];
	temp[4] = ((u32 *)headptr)[4];
	temp[5] = ((u32 *)headptr)[5];
	temp[6] = ((u32 *)headptr)[6];
	temp[7] = ((u32 *)headptr)[7];
	QM_FLUSH_MB(qm_ip, headptr, headptr + 32);

	((u32 *)headptr)[EMPTY_SLOT_INDEX] = EMPTY_SLOT;

	/* Adjust tail pointer */
	QM_DEV(qm_ip)queue_states[qid].headptr += 32;
	if (QM_DEV(qm_ip)queue_states[qid].headptr == QM_DEV(qm_ip)queue_states[qid].endptr)
		QM_DEV(qm_ip)queue_states[qid].headptr = QM_DEV(qm_ip)queue_states[qid].startptr;

	/* Tell QM Lite number messages read in*/
	QM_MSYNC
	//writel((0x10000 - 1), (u32 *) QM_ENQ_B_ADDR_QID(qid));
	writel((0xFFFFFFFF), QM_ENQ_B_ADDR_QID(qid));
	return 0;
}


int apm_qml_pull_comp_msg(u32 qm_ip, u32 qid)
{
	u32 *temp;
	u32 uinfo;
	u8 *headptr;
	struct apm_qm_msg16 *msg16;
	u8 NV;

	/* Check signature to determine if slot has a valid message */
	headptr = QM_DEV(qm_ip)queue_states[qid].headptr;
	temp = (u32 *)headptr;
	if (temp[EMPTY_SLOT_INDEX] == EMPTY_SLOT) {
		QM_DBG("qml comp: Not found any message in qm_ip %d qid %d\n", qm_ip, qid);
		return 0;
	}
	QM_DBG("qml: Found a message in mailbox 0\n");

	QM_FLUSH_MB(qm_ip, headptr, headptr + 32);

	msg16 = (struct apm_qm_msg16 *) headptr;
	uinfo = msg16->UserInfo;
	NV = msg16->NV;

	((u32 *)headptr)[EMPTY_SLOT_INDEX] = EMPTY_SLOT;

	/* Adjust tail pointer */
	QM_DEV(qm_ip)queue_states[qid].headptr += 32;
	if (QM_DEV(qm_ip)queue_states[qid].headptr == QM_DEV(qm_ip)queue_states[qid].endptr)
		QM_DEV(qm_ip)queue_states[qid].headptr = QM_DEV(qm_ip)queue_states[qid].startptr;

	if (!NV) {
		/* Tell QM Lite number messages read in*/
		QM_MSYNC
		writel((0xFFFFFFFF), QM_ENQ_B_ADDR_QID(qid));
	} else {
		/* For 64B message, clean the 2nd half slot */
		((u32 *)QM_DEV(qm_ip)queue_states[qid].headptr)[EMPTY_SLOT_INDEX] = EMPTY_SLOT;

		/* Adjust tail pointer */
		QM_DEV(qm_ip)queue_states[qid].headptr += 32;
		if (QM_DEV(qm_ip)queue_states[qid].headptr == QM_DEV(qm_ip)queue_states[qid].endptr)
			QM_DEV(qm_ip)queue_states[qid].headptr = QM_DEV(qm_ip)queue_states[qid].startptr;

		/* Tell QM Lite number messages read in*/
		QM_MSYNC
		writel((0xFFFFFFFE), QM_ENQ_B_ADDR_QID(qid));
	}

	return uinfo;
}

/*
 * Parse the exact for the Error Message received on Error Queue
 *
 */
void apm_qm_parse_error(struct apm_qm_msg_desc *err_msg_desc)
{
	struct apm_qm_msg32 *msg = (struct apm_qm_msg32 *) err_msg_desc->msg;
	struct apm_qm_msg16 *msg16 = &msg->msg16;
#ifdef QM_DBG_ERR_CHK
	u8 err = 0, cmd_acr_enq_err = 0, cmd_acr_enq_qid = 0, deq_slot_num = 0;
	u16 deq_slvid_pbn = 0;
#endif

	QM_ERR_CHK("QM Error LErr[%d] for Qid[%d] \n",
		msg16->LErr, err_msg_desc->qid);

	switch(msg16->LErr) {
	case QM_MSG_SIZE_ERR:
		QM_ERR_CHK("Msg Size Error for Enqueue on Queue %d \n",
			err_msg_desc->qid);
		break;
	case QM_HOP_COUNT_ERR:
		QM_ERR_CHK("Hop count error. QM received a message with"
			"a hop count of 3 for Queue %d \n",
			err_msg_desc->qid);
		break;
	case QM_VQ_ENQ_ERR:
		QM_ERR_CHK("Enqueue on Virtual Queue %d \n",
			err_msg_desc->qid);
		break;
	case QM_DISABLEDQ_ENQ_ERR:
		QM_ERR_CHK("Enqueue on disabled Queue %d \n",
			err_msg_desc->qid);
		break;
	case QM_Q_OVERFLOW_ERR:
		QM_ERR_CHK("Queue %d overflow, message send to"
			"Error Queue \n",
			err_msg_desc->qid);
		break;
#ifdef QM_DBG_ERR_CHK
	case QM_ENQUEUE_ERR:
		cmd_acr_enq_qid = (msg16->UserInfo & QM_QID_MASK);
		cmd_acr_enq_err = ((msg16->UserInfo >> 22) & 0X2);
		err = ((msg16->UserInfo >> 29) & 0X7);
		QM_ERR_CHK("Enqueue Erro on Qid[%d]\n", cmd_acr_enq_qid);
		switch(err) {
		case QM_AXI_READ_ERR:
			QM_ERR_CHK("AXI error on read from CPU "
				"mailbox: Qid[%d]\n",
				cmd_acr_enq_qid);
			break;
		case QM_AXI_ENQ_VQ_ERR:
			QM_ERR_CHK("Alternate Enqueue Command to a"
				"Virtual Queue: Qid[%d]\n",
				cmd_acr_enq_qid);
			break;
		case QM_AXI_ENQ_DQ_ERR:
			QM_ERR_CHK("Alternate Enqueue Command to a"
				"Disabled Queue: Qid[%d]\n",
				cmd_acr_enq_qid);
			break;
		case QM_AXI_ENQ_OVERFLOWQ_ERR:
			QM_ERR_CHK("Alternate Enqueue Command "
				"overfills Queue: Qid[%d]\n",
				cmd_acr_enq_qid);
			break;
		}
		if (cmd_acr_enq_err == QM_AXI_SLAVE_ERR)
			QM_ERR_CHK("AXI slave error on CPU mailbox"
				"read: Qid[%d]\n",
				cmd_acr_enq_qid);
		else if (cmd_acr_enq_err == QM_AXI_SLAVE_ERR)
			QM_ERR_CHK("AXI decode error on CPU mailbox"
				"read: Qid[%d]\n",
				cmd_acr_enq_qid);
		break;
	case QM_DEQUEUE_ERR:
		err = ((msg16->UserInfo >> 29) & 0X7);
		deq_slvid_pbn = ((msg16->UserInfo >> 3) & 0XFF3);
		deq_slot_num = (msg16->UserInfo & 0x7);
		QM_ERR_CHK("Dequeue Error for deq_slot_num :%d and \n"
			"deq_slvid_pbn: %d",
			deq_slot_num, deq_slvid_pbn);
		if (err ==  QM_CHILD_VQ_ERR)
			QM_ERR_CHK("VQ was assigned as a child of another"
				"VQ, deq_slot_num :%d and \n"
				"deq_slvid_pbn: %d",
				deq_slot_num, deq_slvid_pbn);
		else if (err == QM_DEQUEUE_DQ)
			QM_ERR_CHK("A dequeue was requested from a"
				"disabled PQ, deq_slot_num :%d and \n"
				"deq_slvid_pbn: %d",
				deq_slot_num, deq_slvid_pbn);
		break;
#else
	case QM_ENQUEUE_ERR:
	case QM_DEQUEUE_ERR:
		break;
#endif
	default:
		QM_ERR_CHK("Unknown Error \n");
		break;
	}
	return;
}

int apm_qm_alt_enqueue_enable(void)
{
#if defined(CONFIG_APM_QM_ALTERNATE_ENQUEUE)
	return 1;
#else
	return 0;
#endif	 
}

int apm_qm_alt_dequeue_enable(void)
{
#if defined(CONFIG_APM_QM_ALTERNATE_DEQUEUE)
	return 1;
#else
	return 0;
#endif	 
}


int apm_qm_irq_err(u32 qm_ip)
{
	struct apm_qm_raw_qstate qinfo;	
	u32 status;
	u32 pbm_err;
	u32 msgrd_err;	

	apm_qm_rd32(qm_ip, QM_INTERRUPT_ADDR, &status);
	QM_ERR_CHK("QM error interrupt status 0x%08X\n", status);
	apm_qm_rd32(qm_ip, CSR_PBM_ERRINF_ADDR, &pbm_err);
	QM_ERR_CHK("QM CSR PBM ERRINF (0x%X) value 0x%08X\n", 
		CSR_PBM_ERRINF_ADDR, pbm_err);
	apm_qm_rd32(qm_ip, CSR_MSGRD_ERRINF_ADDR, &msgrd_err);
	QM_ERR_CHK("QM CSR MSGRD ERRINF (0x%X) value 0x%08X\n", 
		CSR_MSGRD_ERRINF_ADDR, msgrd_err);

	QM_ERR_CHK("DEQ QID %d\n", QID_RD(msgrd_err));
	apm_qm_raw_qstate_rd(qm_ip, QID_RD(msgrd_err), &qinfo);
	QM_ERR_CHK_DUMP("QSTATE ", &qinfo, sizeof(qinfo));

	QM_ERR_CHK("ENQ QID %d\n", ACR_QID_RD(msgrd_err));
	apm_qm_raw_qstate_rd(qm_ip, ACR_QID_RD(msgrd_err), &qinfo);
	QM_ERR_CHK_DUMP("QSTATE ", &qinfo, sizeof(qinfo));

#if 0
	if (qm_ip != IP_BLK_QML) {
		int i;

		for (i = 0; i < DQ_MAIL_BOXES; i++) {
			u32 val;
			apm_qm_indirect_access_lock(1);
			__apm_qm_pb_cmd(qm_ip, 
				(PB_SLAVE_ID_CPU << 6) | i, &val, 1); 
			apm_qm_indirect_access_lock(0);
			QM_ERR_CHK("QM CSR 0x10 mailbox %d value 0x%08X slot %d\n", 
				i, val, QM_DEV(qm_ip)mb_dq_mbox_ctxt[i].slot);
		}
	}
#endif

	apm_qm_wr32(qm_ip, QM_INTERRUPT_ADDR, status);	
	return 0;
}

#define MAX_COAL_TAP 0x7
#define MIN_COAL_TAP 0x0

/* This will programe CSR_PBM_COAL's qne_ctick_sel bits which sets a 
 * tap selects for queue not empty interrupt. 
 */
void apm_qm_msg_not_empty_intr_coal_set(u32 qm_ip, u32 tap)
{
	u32 val;

	apm_qm_indirect_access_lock(1);
	apm_qm_rd32(qm_ip, CSR_PBM_COAL_ADDR, &val);
	val |= QNE_CTICK_SEL_WR(tap);
	if (!__apm_qm_dp_enabled())
		apm_qm_wr32(qm_ip, CSR_PBM_COAL_ADDR, val);
#if 0
	else
		apm88xxxx_dp_cfg(IPP_DP_CMD_REG_WR, IPP_DP_RES_QM, 0, 
				CSR_PBM_COAL_ADDR, val);	
#endif
	/* Reback to force barrier */
	apm_qm_rd32(qm_ip, CSR_PBM_COAL_ADDR, &val);
	apm_qm_indirect_access_lock(0);
}

/* If tap is zero then coalescence is off */
int apm_qm_mbox_set_coal(u32 qm_ip, u32 mbox_id, u32 tap)
{
	u32 val, offset;

	if (tap > MAX_COAL_TAP || tap < MIN_COAL_TAP)
		return -1;

	apm_qm_indirect_access_lock(1);
	if (mbox_id <= 7)
		offset = 0;	
	else if (((mbox_id >= 8) && (mbox_id <= 15)))
		offset = 4;
	else if (((mbox_id >= 16) && (mbox_id <= 23)))
		offset = 8;
	else
		offset = 12;
	apm_qm_rd32(qm_ip, CSR_PBM_CTICK0_ADDR + offset, &val);

	switch (mbox_id) {
	case 0:
	case 8:
	case 16:
	case 24:
		val = MBOX00_SET(val, tap);
		break;
	case 1:
	case 9:
	case 17:
	case 25:
		val = MBOX10_SET(val, tap);
		break;
	case 2:
	case 10:
	case 18:
	case 26:
		val = MBOX20_SET(val, tap);
		break;
	case 3:
	case 11:
	case 19:
	case 27:
		val = MBOX30_SET(val, tap);
		break;
	case 4:
	case 12:
	case 20:
	case 28:
		val = MBOX40_SET(val, tap);
		break;
	case 5:
	case 13:
	case 21:
	case 29:
		val = MBOX50_SET(val, tap);
		break;
	case 6:
	case 14:
	case 22:
	case 30:
		val = MBOX60_SET(val, tap);
		break;
	case 7:
	case 15:
	case 23:
	case 31:
		val = MBOX70_SET(val, tap);
		break;
	default:
		apm_qm_indirect_access_lock(0);
		QM_ERR_CHK("%s: Wrong mail box id: %d\n", __func__, mbox_id);
		return -1;
	}
	if (!__apm_qm_dp_enabled()) {
		apm_qm_wr32(qm_ip, CSR_PBM_CTICK0_ADDR + offset, val);
#if 0
	} else {
		if (mbox_id <= 7)
			apm88xxxx_dp_cfg(IPP_DP_CMD_REG_WR, IPP_DP_RES_QM, 0, 
				CSR_PBM_CTICK0_ADDR, val);
		else
			apm88xxxx_dp_cfg(IPP_DP_CMD_REG_WR, IPP_DP_RES_QM, 0, 
				CSR_PBM_CTICK1_ADDR, val);
#endif
	}
	/* Reback to force barrier */
	apm_qm_rd32(qm_ip, CSR_PBM_CTICK0_ADDR + offset, &val);
	apm_qm_indirect_access_lock(0);

	return 0;
}

int __apm_qm_indirect_access_lock(int lock)
{
	return 0;
}
int apm_qm_indirect_access_lock(int lock)
	__attribute((weak, alias("__apm_qm_indirect_access_lock")));

void apm_qm_disable_hwirq(u32 qm_ip)
{
	u32 mask;

	mask = PBM_DEC_ERRORMASK_MASK
		| ACR_FIFO_CRITICALMASK_MASK
		| QUEUE_NOT_EMPTYMASK_MASK
		| DEQ_AXI_ERRORMASK_MASK
		| QPCORE_ACR_ERRORMASK_MASK;

	if (!__apm_qm_dp_enabled())
		apm_qm_wr32(qm_ip, QM_INTERRUPTMASK_ADDR, mask);
}



int apm_qm_enable_hwirq(u32 qm_ip)
{
	u32 mask;

	mask = ~(PBM_DEC_ERRORMASK_MASK
		| ACR_FIFO_CRITICALMASK_MASK
		| QUEUE_NOT_EMPTYMASK_MASK
		| DEQ_AXI_ERRORMASK_MASK
		| QPCORE_ACR_ERRORMASK_MASK
		);

	if (!__apm_qm_dp_enabled())
		apm_qm_wr32(qm_ip, QM_INTERRUPTMASK_ADDR, mask);
#if 0
	else
		apm88xxxx_dp_cfg(IPP_DP_CMD_REG_WR, IPP_DP_RES_QM, 0, 
				QM_INTERRUPTMASK_ADDR, msk);
#endif
	return 0;	
}

int apm_qm_update_tm_timer(u32 qm_ip, u32 val)
{ 
	if (!__apm_qm_dp_enabled())
		apm_qm_wr32(qm_ip, CSR_CU_TIMER_ADDR, val);
#if 0
	else
		apm88xxxx_dp_cfg(IPP_DP_CMD_REG_WR, IPP_DP_RES_QM, 0, 
				CSR_CU_TIMER_ADDR, val);
#endif
	return 0;	
}

int apm_qm_ip_init(u32 qm_ip)
{
	u32 rdata;
	int mwait = 0; 

	apm_qm_wr32(qm_ip, QM_CLKRST_CSR_BASE_ADDR_OFFSET + QM_CLKEN_ADDR, 0x3);
	apm_qm_wr32(qm_ip, QM_CLKRST_CSR_BASE_ADDR_OFFSET + QM_SRST_ADDR, 0);
	apm_qm_wr32(qm_ip, QM_GLBL_DIAG_CSR_BASE_ADDR_OFFSET + QM_CFG_MEM_RAM_SHUTDOWN_ADDR, 0);
	do {
		apm_qm_rd32(qm_ip, QM_GLBL_DIAG_CSR_BASE_ADDR_OFFSET + QM_CFG_MEM_RAM_SHUTDOWN_ADDR, &rdata);
		if (mwait++ >= 1000)
			return -1;
	} while (rdata == 0xffffffff);

	switch (qm_ip) {
	case IP_BLK_QM0:
	case IP_BLK_QM2:
#ifdef QM_RECOMBINATION_BUFFER
		apm_qm_rd32(qm_ip, CSR_RECOMB_CTRL_0_ADDR, &rdata);
		rdata = RECOMB_EN0_SET(rdata, 1);
		apm_qm_wr32(qm_ip, CSR_RECOMB_CTRL_0_ADDR, rdata);
#endif
		break;
	case IP_BLK_QML:
		//SLIMPRO uses pbn0 and pbn1 while cop, abd cpu each use pbn0
		apm_qm_wr32(IP_BLK_QML, CSR_QMLITE_PBN_MAP_0_ADDR, 0x00000000);
	}

	return 0;
}

void apm_qm_ip_shutdown(u32 qm_ip)
{
	u32 val;

	val = QM_RESET_WR(1) | CSR_RESET_WR(1);
	apm_qm_wr32(qm_ip, QM_CLKRST_CSR_BASE_ADDR_OFFSET + QM_SRST_ADDR, val);

	val = QM_CLKEN_WR(0) | CSR_CLKEN_WR(0);
	apm_qm_wr32(qm_ip, QM_CLKRST_CSR_BASE_ADDR_OFFSET + QM_CLKEN_ADDR, val);
}
