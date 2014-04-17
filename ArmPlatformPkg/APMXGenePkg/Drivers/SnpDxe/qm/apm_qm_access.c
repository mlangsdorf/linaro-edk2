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
#include <common.h>
#include <asm/io.h>
#include <misc/xgene/qm/apm_qm_access.h>
#include <misc/xgene/qm/apm_qm_core.h>
#include <misc/xgene/qm/apm_qm_csr.h>

DECLARE_GLOBAL_DATA_PTR;
#else
#include "../mustang.h"
#include "apm_qm_access.h"
#include "apm_qm_core.h"
#include "apm_qm_csr.h"
#endif

struct apm_qm_device *qm_dev[MAX_QM_DEV] = {0};

/* Global queue configuration table */
struct apm_qm_qstate mb_cfg_pqs[0] = { };

/* QM raw register read/write routine */
inline int apm_qm_wr32(u32 qm_ip, u32 offset, u32 data)
{
	//tianocore void *addr = (u8 *) QM_DEV(qm_ip)qm_csr_vaddr + offset;
	//TODO u32 addr = QM_DEV(qm_ip)qm_csr_vaddr + offset;
	u64 addr = QM_DEV(qm_ip)qm_csr_vaddr + offset;
#ifdef QM_DEBUG
	if (offset > CSR_PPC_SAB7_ADDR) {
		QM_ERR_CHK("Invalid offset in QM reg write %x\n", offset);
		return -1;
	}
#endif

	QMWRITE_PRINT("Write addr 0x%p data 0x%08x\n", addr, data);
	writel(data, addr);

	return 0;
}

inline int apm_qm_rd32(u32 qm_ip, u32 offset, u32 *data)
{
	//tianocore void *addr = (u8 *) QM_DEV(qm_ip)qm_csr_vaddr + offset;
	//TODO u32 addr = QM_DEV(qm_ip)qm_csr_vaddr + offset;
	u64 addr = QM_DEV(qm_ip)qm_csr_vaddr + offset;
#ifdef QM_DEBUG
	if (offset > CSR_PPC_SAB7_ADDR) {
		QM_ERR_CHK("Invalid offset in QM reg read %x\n", offset);
		return -1;
	}
#endif

	*data = readl(addr);
	QMREAD_PRINT("Read addr 0x%p data %08X\n", addr, *data);

	return 0;
}

#ifndef CONFIG_APM_QM_SKIP_MAILBOX_INIT
int apm_qm_init_mbox(u32 qm_ip)
{
	QM_DEV(qm_ip)qm_mailbox_type = CONFIG_QM_MAILBOX_TYPE;
	QM_DEV(qm_ip)qm_mailbox_paddr = QM_MAILBOX_PADDR;
	QM_DEV(qm_ip)qm_mailbox_vaddr = (void *) QM_MAILBOX_VADDR;
	QM_DEV(qm_ip)qm_enq_mbox_size = (ENQUE_MAIL_BOXES * TOTAL_SLOTS_32BYTE_MSG * 32);	/* WQ msg size for Enq is 32 bytes */
	QM_DEV(qm_ip)qm_dq_mbox_size = (DQ_MAIL_BOXES * TOTAL_SLOTS_32BYTE_MSG * 32);	/* WQ msg size for Dq is 32 bytes */
	QM_DEV(qm_ip)qm_fp_mbox_size = (FP_MAIL_BOXES * TOTAL_SLOTS_16BYTE_MSG * 16);	/* FQ msg size for Fp is 16 bytes */

#if !defined(CONFIG_QM_MAILBOX_MEMQ) && defined(CONFIG_MP)
	/* NOTE: For AMP to work correctly with Ethernet, the QM mailboxes
	 *       addresses must be a fixed location. Therefore, IO memory
	 *       must be used.
	 *       For AMP domain protection to work correctly, QM mailboxes
	 *       must located in MemQ 
	 */ 
	if (getenv("AMP") == NULL && !apm86xxx_is_dp_mode())
		goto done_amp;
	if (gd->shmem_size == 0) {
		QM_PRINT("\nWARNING: AMP does not support QM Mailbox "
			"located in MemQ\n");
		return -1;
	}

	if (!apm86xxx_is_dp_mode()) {
		/* Read the DDR size from Memory Queue controller and 
		   determine QM Mailbox location. */
		QM_DEV(qm_ip)qm_mailbox_paddr = (~in32(CONFIG_SYS_DDRC_BASE +
			0x00000004) + 1) & 0xFFFF;
		QM_DEV(qm_ip)qm_mailbox_paddr <<= 20;
		QM_DEV(qm_ip)qm_mailbox_paddr -= 16*1024;
		QM_DEV(qm_ip)qm_mailbox_vaddr = phys_to_virt(QM_DEV(qm_ip)qm_mailbox_paddr); 
		/* Program a TLB for QM Mailboxes */
		program_tlb(QM_DEV(qm_ip)qm_mailbox_paddr, (u32) QM_DEV(qm_ip)qm_mailbox_vaddr, 
			16*1024, AC_R|AC_W|AC_X|SA_I|SA_G);
	} else {
		/* Domain Protection: Use MemQ Mailbox phy address in MemQ */
		QM_DEV(qm_ip)qm_mailbox_paddr = CONFIG_SYS_PHY_MB_BASE;
		QM_DEV(qm_ip)qm_mailbox_vaddr = (void *) CONFIG_SYS_MB_BASE;
		QM_DEV(qm_ip)qm_mailbox_type = QM_MAILBOX_NONCACHEABLE;
	}

done_amp:
#endif
	if (QM_DEV(qm_ip)qm_mailbox_paddr == 0x0000000000ULL) {
		QM_DEV(qm_ip)qm_mailbox_vaddr = MEMALLOC(QM_DEV(qm_ip)qm_enq_mbox_size + 
			QM_DEV(qm_ip)qm_dq_mbox_size + QM_DEV(qm_ip)qm_fp_mbox_size + 
			65536);
		if (QM_DEV(qm_ip)qm_mailbox_vaddr == NULL) {
			QM_PRINT("Unable to allocate memory for mailbox\n");
			return -1;
		}
		QM_DEV(qm_ip)qm_mailbox_vaddr = (void *) ((((unsigned long) QM_DEV(qm_ip)qm_mailbox_vaddr) 
			+ (65536 - 1)) & ~(65536 - 1));
		QM_DEV(qm_ip)qm_mailbox_paddr = virt_to_phys(QM_DEV(qm_ip)qm_mailbox_vaddr);
	}

	QM_DEV(qm_ip)qm_enq_mbox_paddr = QM_DEV(qm_ip)qm_mailbox_paddr;
	QM_DEV(qm_ip)qm_enq_mbox_vaddr = QM_DEV(qm_ip)qm_mailbox_vaddr;
	QM_DEV(qm_ip)qm_dq_mbox_paddr = QM_DEV(qm_ip)qm_enq_mbox_paddr + QM_DEV(qm_ip)qm_enq_mbox_size;
	QM_DEV(qm_ip)qm_dq_mbox_vaddr = (u8 *) QM_DEV(qm_ip)qm_enq_mbox_vaddr + QM_DEV(qm_ip)qm_enq_mbox_size;
	QM_DEV(qm_ip)qm_fp_mbox_paddr = QM_DEV(qm_ip)qm_dq_mbox_paddr + QM_DEV(qm_ip)qm_dq_mbox_size;
	QM_DEV(qm_ip)qm_fp_mbox_vaddr = (u8 *) QM_DEV(qm_ip)qm_dq_mbox_vaddr + QM_DEV(qm_ip)qm_dq_mbox_size;

	QM_DBG("QM alloc mbox\n");
	apm_qm_alloc_mbox(qm_ip);

	apm_qm_set_enq_mbox_addr(qm_ip,
		QM_DEV(qm_ip)qm_mailbox_type == QM_MAILBOX_NONCACHEABLE ? 0 : 1,
		QM_DEV(qm_ip)qm_enq_mbox_paddr);
	apm_qm_set_dq_mbox_addr(qm_ip,
		QM_DEV(qm_ip)qm_mailbox_type == QM_MAILBOX_NONCACHEABLE ? 0 : 1,
		QM_DEV(qm_ip)qm_dq_mbox_paddr);
	apm_qm_set_fp_mbox_addr(qm_ip,
		QM_DEV(qm_ip)qm_mailbox_type == QM_MAILBOX_NONCACHEABLE ? 0 : 1,
		QM_DEV(qm_ip)qm_fp_mbox_paddr);

	return 0;
}
#endif

void QM_INVALIDATE_MB(u32 qm_ip, void *start, void *stop)
{
#if 0
	if (QM_DEV(qm_ip)qm_mailbox_type & (QM_MAILBOX_CACHEABLE | QM_MAILBOX_IOCOHERENT))
		invalidate_dcache_range((unsigned long) start, 
			(unsigned long) stop);
#endif
}

void QM_FLUSH_MB(u32 qm_ip, void *start, void *stop)
{
#if 0
	if (QM_DEV(qm_ip)qm_mailbox_type & (QM_MAILBOX_CACHEABLE | QM_MAILBOX_IOCOHERENT))
		flush_dcache_range((unsigned long) start, 
			(unsigned long) stop);
#endif
}

int apm_qm_init(u32 qm_ip, int stage)
{
	int rc;

	if (qm_ip < IP_BLK_QM0 || qm_ip > IP_BLK_QML) {
		QM_PRINT("\nInvalid QM_IP %d\n", qm_ip);
		return -1;
	}

	if (qm_dev[qm_ip] == NULL) {
		qm_dev[qm_ip] = MEMALLOC(sizeof(struct apm_qm_device));
		memset(qm_dev[qm_ip], 0, sizeof(struct apm_qm_device));
		QM_DEV(qm_ip)id = qm_ip;
	}

	if (stage == 0)
		goto stage_1;

	/* Check if already initialize */
	if (QM_DEV(qm_ip)ip_pbn_wq_msk[IP_CPU0]) {
		QM_PRINT("QM init stage %d skipped\n", stage);
		return 0;	
	}

	if (stage == 2)
		goto stage_2;

stage_1:
	QM_DBG("QM init stage 1\n");
	switch (qm_ip) {
	case IP_BLK_QM0:
		QM_DEV(IP_BLK_QM0)qm_csr_paddr = CONFIG_SYS_QM0_CSR_BASE;
		QM_DEV(IP_BLK_QM0)qm_csr_vaddr = CONFIG_SYS_QM0_CSR_BASE;
		QM_DEV(IP_BLK_QM0)qm_fabric_paddr = CONFIG_SYS_QM0_FABRIC_BASE;
		QM_DEV(IP_BLK_QM0)qm_fabric_vaddr = CONFIG_SYS_QM0_FABRIC_BASE;
		break;
	case IP_BLK_QM1:
		QM_DEV(IP_BLK_QM1)qm_csr_paddr = CONFIG_SYS_QM1_CSR_BASE;
		QM_DEV(IP_BLK_QM1)qm_csr_vaddr = CONFIG_SYS_QM1_CSR_BASE;
		QM_DEV(IP_BLK_QM1)qm_fabric_paddr = CONFIG_SYS_QM1_FABRIC_BASE;
		QM_DEV(IP_BLK_QM1)qm_fabric_vaddr = CONFIG_SYS_QM1_FABRIC_BASE;
		break;
	case IP_BLK_QM2:
		QM_DEV(IP_BLK_QM2)qm_csr_paddr = CONFIG_SYS_QM2_CSR_BASE;
		QM_DEV(IP_BLK_QM2)qm_csr_vaddr = CONFIG_SYS_QM2_CSR_BASE;
		QM_DEV(IP_BLK_QM2)qm_fabric_paddr = CONFIG_SYS_QM2_FABRIC_BASE;
		QM_DEV(IP_BLK_QM2)qm_fabric_vaddr = CONFIG_SYS_QM2_FABRIC_BASE;
		break;
	case IP_BLK_QML:
		QM_DEV(IP_BLK_QML)qm_csr_paddr = CONFIG_SYS_QML_CSR_BASE;
		QM_DEV(IP_BLK_QML)qm_csr_vaddr = CONFIG_SYS_QML_CSR_BASE;
		QM_DEV(IP_BLK_QML)qm_fabric_paddr = CONFIG_SYS_QML_FABRIC_BASE;
		QM_DEV(IP_BLK_QML)qm_fabric_vaddr = CONFIG_SYS_QML_FABRIC_BASE;
		break;
	}

	rc = apm_qm_ip_init(qm_ip);

	if (rc)
		QM_PRINT("ERROR: failed to reset QM error %d\n", rc);	

	return rc;

stage_2:
	QM_DBG("QM init stage 2\n");
#ifdef CONFIG_MP
	/* For AMP Systems, we are partitioning cle resoures */
	if (getenv("AMP") != NULL) {		
		/* NOTE: We need to clear all queue state assigned to 
		 *       this core. We should also patch up the DTS for 
		 *       AMP accordingly.
		 */
		if (apm88xxxx_cpuid() == 0) {
			apm_qm_set_qid(qm_ip, 0, QM_START_QID_CORE0, 
				QM_END_QID_CORE0, QM_END_QID_CORE0);
			apm_qm_set_mboxes(qm_ip, 8, 0);
		} else {
			apm_qm_set_qid(qm_ip, QM_START_QID_CORE1, QM_START_QID_CORE1, 
				QM_END_QID_CORE1, QM_END_QID_CORE1);
			apm_qm_set_mboxes(qm_ip, 8, 8);
		}
	} else 
#endif
	{
		apm_qm_set_qid(qm_ip, 0, QM_START_QID_CORE0, QM_AVL_QUEUES, 
			QM_AVL_QUEUES);
		if (qm_ip != IP_BLK_QML)
			apm_qm_set_mboxes(qm_ip, 8, 2);	//TODO from 2
	}

	apm_qm_set_smp(1);	/* For U-Boot, CPU0 initialize QM only */
	apm_qm_set_noqml(0);	/* QM lite is always available */

#ifndef CONFIG_APM_QM_SKIP_MAILBOX_INIT
	/* Initialize QM mailboxes */
	if (qm_ip != IP_BLK_QML) {
		QM_DBG("QM init mboxs\n");
		if ((rc = apm_qm_init_mbox(qm_ip)) != 0)
			return rc;
	}
#endif

	QM_DBG("QM init queue\n");
	apm_qm_init_queue(qm_ip, 0);
	return 0;
}
