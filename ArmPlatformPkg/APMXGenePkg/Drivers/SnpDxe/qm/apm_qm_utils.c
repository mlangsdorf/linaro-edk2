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
#include <misc/xgene/qm/apm_qm_core.h>
#include <misc/xgene/qm/apm_qm_utils.h>
#include <misc/xgene/qm/apm_qm_access.h>
#else
#include "apm_qm_core.h"
#include "apm_qm_utils.h"
#include "apm_qm_access.h"

#define DDR_INFO
#ifdef DDR_INFO
#define info(arg...) DEBUG ((EFI_D_INFO,## arg))
#else
#define info(arg...)
#endif
#undef QM_PRINT
#define QM_PRINT info
#undef QMCORE_PRINT
#define QMCORE_PRINT info
#endif

void dump_qstate(struct apm_qm_qstate *qstate)
{
	QM_PRINT("\nQUEUE STATE DUMP\n");

	if (qstate->ip_blk >= IP_BLK_QM0 && qstate->ip_blk <= IP_BLK_QM2)
		QM_PRINT("\nThis queue belongs to: QM%d\n", qstate->ip_blk);
	else if (qstate->ip_blk == IP_BLK_QML)
		QM_PRINT("\nThis queue belongs to: QM lite\n");
	else
		QM_PRINT("\nThis queue belongs to: Invalid IP blk\n");

	if (qstate->valid)
		QM_PRINT("This queue is: Valid\n");
	else
		QM_PRINT("This queue is: Invalid\n");

	QM_PRINT("Queue ID: %d\n", qstate->q_id);
	QM_PRINT("Assigned mailbox ID: %d\n", qstate->mb_id);
	QM_PRINT("Belongs to slave ID: %d\n", qstate->slave_id);
	QM_PRINT("Belongs to Prefetch Buffer: 0x%x\n", qstate->pbn);

	switch(qstate->q_type) {
	case(P_QUEUE):
		QM_PRINT("This queue is: Physical queue\n");
		break;
	case(FREE_POOL):
		QM_PRINT("This queue is: Free queue\n");
		break;
	case(V_QUEUE):
		QM_PRINT("This queue is: Virtual queue\n");
		break;
	default:
		QM_PRINT("This queue is: Invalid queue\n");
		break;
	}

	switch(qstate->q_size) {
	case(SIZE_512B):
		QM_PRINT("Queue size: 512 Bytes\n");
		break;
	case(SIZE_2KB):
		QM_PRINT("Queue size: 2 KB\n");
		break;
	case(SIZE_16KB):
		QM_PRINT("Queue size: 16 KB\n");
		break;
	case(SIZE_64KB):
		QM_PRINT("Queue size: 64 KB\n");
		break;
	case(SIZE_512KB):
		QM_PRINT("Queue size: 512 KB\n");
		break;
	default:
		QM_PRINT("Queue size: Invalid\n");
		break;
	}

	QM_PRINT("Queue Physical start address: 0x%llx\n", (unsigned long long)(qstate->q_start_addr << 8));
	QM_PRINT("Queue Virtual start address: 0x%p\n", phys_to_virt(qstate->q_start_addr << 8));

	QM_PRINT("Number of message in queue: %d\n", qstate->nummsgs);
	QM_PRINT("Number of dma_msg in queue: %d\n", qstate->dma_nummsgs);
	QM_PRINT("Current region ID of the queue: %d\n", qstate->rid);
	QM_PRINT("Number SW message in queue: %d\n", qstate->msg_stat);

	if (qstate->direction == DIR_EGRESS)
		QM_PRINT("This queue is used in: Egress direction\n");
	else if (qstate->direction == DIR_INGRESS)
		QM_PRINT("This queue is used in: Ingress direction\n");
	else
		QM_PRINT("This queue is used in: Invalid direction\n");

	QM_PRINT("Config SAB Enable for this queue: %d\n", qstate->cfgsaben);
	QM_PRINT("Config CPU Notify for this queue: %d\n", qstate->cpu_notify);
}

void apm_qm_msg_decode(struct apm_qm_msg32 msg)
{
#if 0	//TODO
	struct apm_qm_msg16 *msg16 = &(msg.msg16);
	struct apm_qm_msg_up16 *msg_up16 = &msg.msgup16;

	QM_PRINT(" FPQNum=0x%x\n", msg16->FPQNum);
	QM_PRINT(" Rv2=0x%x\n", msg16->Rv2);
	QM_PRINT(" ELErr=0x%x\n", msg16->ELErr);
	QM_PRINT(" LEI=0x%x\n", msg16->LEI);
	QM_PRINT(" NV=0x%x\n", msg16->NV);

	QM_PRINT(" LL=0x%x\n", msg16->LL);
	QM_PRINT(" PB=0x%x\n", msg16->PB);
	QM_PRINT(" HB=0x%x\n", msg16->HB);
	QM_PRINT(" Rv=0x%x\n", msg16->Rv);
	QM_PRINT(" IN=0x%x\n", msg16->In);
	QM_PRINT(" RType=0x%x\n", msg16->RType);
	QM_PRINT(" LErr=0x%x\n", msg16->LErr);
	QM_PRINT(" HL=0x%x\n", msg16->HL);
	QM_PRINT(" DataAddr=0x%llx\n", (u64)msg16->DataAddr);
	QM_PRINT(" Rv6=0x%x\n", msg16->Rv6);
	QM_PRINT(" BufDataLen=0x%x\n", msg16->BufDataLen);
	QM_PRINT(" C=0x%x\n", msg16->C);


	QM_PRINT(" H0Info_msb=0x%llx\n", (u64)msg_up16->H0Info_msb);
	QM_PRINT(" TotDataLengthLinkListLSBs=0x%x\n", msg_up16->TotDataLengthLinkListLSBs);
	QM_PRINT(" Rv1=0x%x\n", msg_up16->Rv1);
	QM_PRINT(" DR=0x%x\n", msg_up16->DR);
	QM_PRINT(" Rv0=0x%x\n", msg_up16->Rv0);
	QM_PRINT(" HR=0x%x\n", msg_up16->HR);
	QM_PRINT(" H0Info_lsb=0x%llx\n", (u64)msg_up16->H0Info_lsb);
	QM_PRINT(" H0Enq_Num=0x%x\n", msg_up16->H0Enq_Num);
	QM_PRINT(" H0FPSel=0x%x\n", msg_up16->H0FPSel);
#endif
}

int apm_qm_rx_msg_util(u32 qm_ip, int qid, int mbid)
{
	struct apm_qm_msg_desc msg_desc;
	struct apm_qm_msg32 msg;
	u8 *temp_msg = NULL;

	msg_desc.msg = &msg;
	temp_msg = (u8 *) msg_desc.msg;
	memset(&msg, 0, sizeof(msg));
	msg_desc.qm_ip_blk = qm_ip;
	msg_desc.qid = qid;
	msg_desc.mb_id = mbid;
	msg_desc.is_msg16 = 0;	

#ifdef CONFIG_APM_QM_ALTERNATE_DEQUEUE
	apm_qml_pull_msg(&msg_desc);
#else
	if (qm_ip >= IP_BLK_QM0 && qm_ip <= IP_BLK_QM2)
		apm_qm_pull_msg(&msg_desc);
	else
		apm_qml_pull_msg(&msg_desc);
#endif
	QM_PRINT("READ MSG: %x\n", *(u32 *)temp_msg);
	temp_msg+=4;
	QM_PRINT("READ MSG: %x\n", *(u32 *)temp_msg);
	temp_msg+=4;
	QM_PRINT("READ MSG: %x\n", *(u32 *)temp_msg);
	temp_msg+=4;
	QM_PRINT("READ MSG: %x\n", *(u32 *)temp_msg);
	apm_qm_msg_decode(msg);
	return 0;
}

int apm_qm_send_msg_util(u32 qm_ip, int qid, int mbid, struct apm_qm_msg64 *msg64)
{
	struct apm_qm_msg_desc msg_desc;
	struct apm_qm_msg32 msg32;
	struct apm_qm_msg16 *msg16;
	static u32 UserInfo = 0;

	if (msg64 == NULL) {
		memset(&msg32, 0, sizeof(msg32));

		/* prepare dummy message to send */
		msg16 = &(msg32.msg16);
		msg16->UserInfo = (++UserInfo);
		msg16->BufDataLen = 3;
		msg16->DataAddr = 0x0d00ffff;

		msg_desc.msg = &msg32;
	} else {
		msg_desc.msg = msg64;
	}

	msg_desc.qm_ip_blk = qm_ip;
	msg_desc.qid = qid;
	msg_desc.mb_id = mbid;

#ifdef CONFIG_APM_QM_ALTERNATE_DEQUEUE
	apm_qml_push_msg(&msg_desc);
#else
	if (qm_ip >= IP_BLK_QM0 && qm_ip <= IP_BLK_QM2)
		apm_qm_push_msg(&msg_desc);
	else
		apm_qml_push_msg(&msg_desc);
#endif

	return 0;
}

int apm_qm_dealloc_buf_util(u32 qm_ip, int qid, int mbid)
{
	struct apm_qm_msg_desc msg_desc;
	struct apm_qm_msg16 msg;

	memset(&msg, 0, sizeof(msg));

	/* prepare dummy message to send */
	msg.BufDataLen = 3;
	msg.DataAddr = 0x0d00ffff;
	msg.FPQNum = qid;

	msg_desc.qm_ip_blk = qm_ip;
	msg_desc.qid = qid;
	msg_desc.mb_id = mbid;
	msg_desc.msg = &msg;

#ifdef CONFIG_APM_QM_ALTERNATE_ENQUEUE
	apm_qml_fp_dealloc_buf(&msg_desc);
#else
	apm_qm_fp_dealloc_buf(&msg_desc);
#endif

	return 0;
}

int apm_qm_alloc_buf_util(u32 qm_ip, int qid, int mbid)
{
	struct apm_qm_msg_desc msg_desc;
	struct apm_qm_msg16 msg;

	msg_desc.msg = &msg;

	memset(&msg, 0, sizeof(msg));

	/* prepare dummy message to send */
	msg.BufDataLen = 3;
	msg.DataAddr = 0x0d00ffff;
	msg.FPQNum = qid;

	msg_desc.qm_ip_blk = qm_ip;
	msg_desc.qid = qid;
	msg_desc.mb_id = mbid;
	msg_desc.msg = &msg;

#ifdef CONFIG_APM_QM_ALTERNATE_DEQUEUE
	apm_qml_pull_msg(&msg_desc);
#else
	apm_qm_fp_alloc_buf(&msg_desc);
#endif

	QM_PRINT("msg.DataAddr: %llx\n", (unsigned long long)msg.DataAddr);
	QM_PRINT("msg.FPQNum: %x\n", msg.FPQNum);

	return 0;
}
