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

#ifndef __APM_QM_ACCESS_H__
#define __APM_QM_ACCESS_H__

#ifndef APM_XGENE
#include <common.h>
#include <config.h>
#include <malloc.h>
#else
#include <Library/DebugLib.h>
#include <Library/BaseLib.h>
#include <Library/BaseMemoryLib.h>
#include <Library/MemoryAllocationLib.h>
typedef UINT8 u8;
typedef UINT16 u16;
typedef UINT32 u32;
typedef UINT64 u64;
#endif

#undef CONFIG_NOT_COHERENT_QM

#define memset(dest,ch,count)             SetMem(dest,(UINTN)(count),(UINT8)(ch))
#define printf          info
#define malloc AllocateZeroPool
#define free FreePool


#define info(arg...) DEBUG ((EFI_D_INFO,## arg))

/* Enabled debug macros put here */
#define QM_DBG_ERR_CHK
#define QM_PRINT_ENABLE
#undef QMCORE_PRINT_ENABLE
#undef DQM_DBG
#undef DQM_DBG_WR
#undef DQM_DBG_RD
#undef QM_DBG_STATE

#ifdef DQM_DBG
#define QM_DBG(x, ...)  printf(x, ##__VA_ARGS__)
#else
#define QM_DBG(x, ...)
#endif

#ifdef DQM_DBG2
#define QM_DBG2(x, ...)  printf(x, ##__VA_ARGS__)
#else
#define QM_DBG2(x, ...)
#endif

#ifdef QM_PRINT_ENABLE
#define QM_PRINT(x, ...)  printf(x, ##__VA_ARGS__)
#else
#define QM_PRINT(x, ...)
#endif

#ifdef QMCORE_PRINT_ENABLE
#define QMCORE_PRINT(x, ...)  printf(x, ##__VA_ARGS__)
#else
#define QMCORE_PRINT(x, ...)
#endif

#ifdef QM_DBG_ERR_CHK
#define QM_ERR_CHK(x, ...)  printf(x, ##__VA_ARGS__)
#define QM_ERR_CHK_DUMP(hdr, fmt, ...)
#else
#define QM_ERR_CHK(x, ...)
#define QM_ERR_CHK_DUMP(hdr, fmt, ...)
#endif

#ifdef DQM_DBG_WR
#define QMWRITE_PRINT(x, ...)  printf(x, ##__VA_ARGS__)
#else
#define QMWRITE_PRINT(x, ...)
#endif

#ifdef DQM_DBG_RD
#define QMREAD_PRINT(x, ...)  printf(x, ##__VA_ARGS__)
#else
#define QMREAD_PRINT(x, ...)
#endif

#ifdef QM_DBG_STATE
#define QM_STATE_DBG(x, ...)  printf(x, ##__VA_ARGS__)
#else
#define QM_STATE_DBG(x, ...)
#endif

#define MEMALLOC malloc
#define MEMFREE  free

/* dummy virt to phys for u-boot */
#define virt_to_phys(x) 	((u64) (unsigned long) (x))
#define phys_to_virt(x) 	((void *) (unsigned long) (x))
#ifdef CONFIG_ARCH_MSLIM
#define CONFIG_NOT_COHERENT_QM
#define VIRT_TO_PHYS(x)	mslim_pa_to_iof_axi(virt_to_phys(x))
#define PHYS_TO_VIRT(x)	phys_to_virt(mslim_iof_axi_to_pa(x))
#else
#define VIRT_TO_PHYS(x) virt_to_phys(x)
#define PHYS_TO_VIRT(x) phys_to_virt(x)
#endif

/* Disble Reporting Errors to Error Queue */
#undef APM_QM_ERROR_Q_ENABLE

/* Compile QM module for boot loader */
#define BOOTLOADER

#define CONFIG_APM_QM_ALTERNATE_ENQUEUE
#define CONFIG_APM_QM_ALTERNATE_DEQUEUE

#if !defined(CONFIG_APM_QM_ALTERNATE_ENQUEUE) || !defined(CONFIG_APM_QM_ALTERNATE_DEQUEUE)
/** 
 * QM mailbox locations
 *
 * OCM Address: 	PADDR: 0xeffffc000ULL 
 *              	VADDR: 0x90004000
 * MemQ Address: 	PADDR: CONFIG_SYS_PHY_MB_BASE
 *               	VADDR: CONFIG_SYS_MB_BASE
 * CPU FAM Address:	PADDR: 0x400000000ULL 
 *              	VADDR: 0x40000000
 * DDR Address:		PADDR: 0x000000000ULL
 *                      VADDR: 0x00000000
 * For DDR, it can be non-cachable, cachable, or coherent.
 *
 * NOTE: For AMP to work correctly, the QM mailbox address musts be at a 
 *       fixed location and accessible by all cores. See apm_qm_access.h.
 *
 */
#undef CONFIG_QM_MAILBOX_MEMQ
#define CONFIG_QM_MAILBOX_DDR 

#if defined(CONFIG_QM_MAILBOX_MEMQ)
#define QM_MAILBOX_PADDR	CONFIG_SYS_PHY_MB_BASE
#define QM_MAILBOX_VADDR	CONFIG_SYS_MB_BASE
#define CONFIG_QM_MAILBOX_TYPE	QM_MAILBOX_NONCACHEABLE
#elif defined(CONFIG_QM_MAILBOX_OCM)
#define QM_MAILBOX_PADDR	0x000000000ULL
#define QM_MAILBOX_VADDR	0x00000000
#define CONFIG_QM_MAILBOX_TYPE	QM_MAILBOX_NONCACHEABLE
#define MAX_MAILBOXS		8
#else 
#define QM_MAILBOX_PADDR	0x000000000ULL
#define QM_MAILBOX_VADDR	0x00000000
/*#define CONFIG_QM_MAILBOX_TYPE	QM_MAILBOX_COHERENT*/
#define CONFIG_QM_MAILBOX_TYPE	QM_MAILBOX_NONCACHEABLE
#endif 
#endif

#ifdef inline
#undef inline
#endif
/* QM raw register read/write routine */
inline int apm_qm_wr32(u32 qm_ip, u32 offset, u32 data);
inline int apm_qm_rd32(u32 qm_ip, u32 offset, u32 *data);
int apm_qm_init_mbox(u32 qm_ip);
int apm_qm_init(u32 qm_ip, int stage);
void QM_INVALIDATE_MB(u32 qm_ip, void *start, void *stop);
void QM_FLUSH_MB(u32 qm_ip, void *start, void *stop);

#endif /* __APM_QM_ACCESS_H__ */
