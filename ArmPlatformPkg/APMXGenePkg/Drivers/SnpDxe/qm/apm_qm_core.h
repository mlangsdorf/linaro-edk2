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

#ifndef __APM_QM_CORE_H__
#define __APM_QM_CORE_H__
#ifndef APM_XGENE
#include <misc/xgene/qm/apm_qm_access.h>
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
#undef SIZE_2KB
#undef SIZE_16KB
#undef SIZE_64KB
#undef SIZE_512KB
#include "apm_qm_access.h"
#endif

#define memcpy(dest,source,count)         CopyMem(dest,source,(UINTN)(count))
//#define memset(dest,ch,count)             SetMem(dest,(UINTN)(count),(UINT8)(ch))


/* NOTE: Update qm_cfg_ip in apm/qm/linux/apm_qm_cfg.h accordingly */
enum apm_qm_ip {
	IP_BLK_QM0,
	IP_BLK_QM1,
	IP_BLK_QM2,
	IP_BLK_QML,
	MAX_QM_DEV,
};

/* Common qm_cfg_ip */
#define IP_BLK_QM IP_BLK_QM1

/* Destination QM, 2 MSb in work queue, dstqid */
#define DST_QM_IP(n)		(n << 10)

#define QM_BASE_ADDR		QM_DEV(qm_ip)qm_fabric_vaddr
#define QBASE_ADDR_QID_MASK	6
#define MAX_CPU_CORES		2

#define CPU_FP_MB_PBN_OFFSET	0x20

#define QM_B_ADDR_QID(x) 	((void *) ((unsigned long) QM_BASE_ADDR | (x << QBASE_ADDR_QID_MASK)))
#define QM_ENQ_B_ADDR_QID(x)	(((unsigned long) QM_BASE_ADDR | (x << QBASE_ADDR_QID_MASK) | 0x2C))
#define DEC_OFFSET		0x3c
#define QM_B_ADDR_DEC	 	((void *) ((unsigned long) QM_BASE_ADDR | DEC_OFFSET))
#define CPU_SLAVE_ID		0xF
#define SLAVE_ID_SHIFT		6
#define CPU_SLAVE_SHIFT		14
#define DEC_PBN_SHIFT		8
#define QM_DEC_MSG_VAL(pbn, dec) ((CPU_SLAVE_ID << CPU_SLAVE_SHIFT) | (pbn << DEC_PBN_SHIFT) | dec)

/* QM lite queues */
#define WQ_SZ_32B     		1

#define APM_QM_MBID_SHIFT	10
#define APM_QM_SLOTID_SHIFT	2

#define TOTAL_SLOTS		256
#define TOTAL_SLOTS_16BYTE_MSG	256
#define TOTAL_SLOTS_32BYTE_MSG	256
#define TOTAL_SLOTS_64BYTE_MSG	128

#define SIZE_64_MSG		3
#define SIZE_32_MSG		2
#define SIZE_16_MSG		1

#ifndef MAX_MAILBOXS
#define MAX_MAILBOXS		32
#endif
#define ENQUE_MAIL_BOXES	MAX_MAILBOXS
#define DQ_MAIL_BOXES		MAX_MAILBOXS
#define FP_MAIL_BOXES		MAX_MAILBOXS

#if defined(CONFIG_APM_QM_ALTERNATE_ENQUEUE) && defined(CONFIG_APM_QM_ALTERNATE_DEQUEUE)
#define CONFIG_APM_QM_SKIP_MAILBOX_INIT
#else
/* Use bit for easy bit-wise test */
#if !defined(QM_MAILBOX_COHERENT)
#define QM_MAILBOX_COHERENT	0x0001
#define QM_MAILBOX_IOCOHERENT	0x0002
#define QM_MAILBOX_CACHEABLE	0x0004
#define QM_MAILBOX_NONCACHEABLE	0x0008
#endif
#endif

enum apm_qm_rtype {
	APM_QM_NON_RTYPE = 0,
	APM_QM_ETH_RTYPE,
	APM_QM_SEC_RTYPE,
	APM_QM_DMA_RTYPE,
	APM_QM_CLASS_RTYPE,
	APM_QM_VENET_RTYPE,
	APM_QM_CPU_RTYPE,
	APM_QM_WOL_RTYPE,
	APM_QM_LRO_RTYPE,
	APM_QM_UNUSE5_RTYPE,
	APM_QM_UNUSE4_RTYPE,
	APM_QM_UNUSE3_RTYPE,
	APM_QM_UNUSE2_RTYPE,
	APM_QM_UNUSE1_RTYPE,
	APM_QM_UNUSE0_RTYPE,
	MB_INVALID_RTYPE
};

#define EMPTY_SLOT_INDEX	7
#define EMPTY_SLOT		0x22222222

#define APM_QM_MAX_RTYPE	64

#define CORE0			0
#define CORE1			1
#define MAX_CORES		2

#define QM_MAX_QUEUES		256
#define QM_QID_MASK             0xFF

/*  QML Queues used by Enet and SlimPRO for WoL */
#define DSLEEP_ENET_TX_Q    	252	/* SlimPRO work queue for WoL */
#define DSLEEP_ENET_RX_FP_Q 	253	/* SlimPRO free pool queue for WoL */
#define DSLEEP_ENET_RX_Q    	254	/* Ethernet work queue for WoL */
#define DSLEEP_ENET_RX_FQ_TO_DDR 251	/* Intermediate queue in WoL for lossless */

#define DSLEEP_ENET_RX_FP_PBN	0x30	/* ETH PBN 0x30 reserved for WoL */
#define DSLEEP_ENET_RX_FQ_TO_DDR_PBN 0x31 /* ETH PBN 0x31 reserved for WoL lossless */

#define QM_RSV_UNCONFIG_COMP_Q	250
#define QM_RSV_UNCONFIG_FUTURE	249

#define QM_RSV_QUEUES		8	/* Reserved Qs 249 to 254, 0 and 255 */
#define QM_AVL_QUEUES		(QM_MAX_QUEUES - QM_RSV_QUEUES)	/* Available Qs */

/* For AMP Core 0 */
#ifndef APM_XGENE
#define QM_START_QID_CORE0	0
#else
#define QM_START_QID_CORE0	0	//TODO from 4

#endif
#define QM_END_QID_CORE0	((QM_AVL_QUEUES / 2) - 1)

/* For AMP Core 1 */
#define QM_START_QID_CORE1	(QM_AVL_QUEUES / 2)
#define QM_END_QID_CORE1	(QM_AVL_QUEUES - 1)

#define MAX_DELAY_CNT   	10000

#define DIR_INGRESS		0
#define DIR_EGRESS		1

#define ENABLE_VQ		1
#define DRR_CREDIT_GRAN		4500

enum apm_qm_arb_type {
	NO_ARB,
	SP_ARB,
	DRR_ARB,
	AVB_ARB,
};

/* QM/QM-lite queues start at 0x1000 offset*/
#define QMI_ETH_IPP_INGRESS_FP_ADDR	0x00401000
#define QMI_ETH_IPP_INGRESS_WQ_ADDR	0x00401200
#define QMI_ETH_IPP_EGRESS_WQ_ADDR      0x00401400
#define QMI_ETH_IPP_FREE_POOL_ADDR	0x00401600

/* QM return codes */
#define QM_ERR				-1
#define QM_OK				0

/* Check for mailbox available before writing msg */
#define CONFIG_MB_CHECK_TX_MSG

#define QM_MSYNC

/* Prefetch buffer slave ids */
/* NOTE: Update qm_cfg_slave_id in apm/qm/linux/apm_qm_cfg.h accordingly */
enum apm_qm_slave_id {
	PB_SLAVE_ID_ETH_BLK0,
	PB_SLAVE_ID_ETH_BLK1,
	PB_SLAVE_ID_RES2,
	PB_SLAVE_ID_DMA,
	PB_SLAVE_ID_CTX,
	PB_SLAVE_ID_SEC,
	PB_SLAVE_ID_CLASS,
	PB_SLAVE_ID_MSLIM,
	PB_SLAVE_ID_RES8,
	PB_SLAVE_ID_RES9,
	PB_SLAVE_ID_RESA,
	PB_SLAVE_ID_RESB,
	PB_SLAVE_ID_RESC,
	PB_SLAVE_ID_RESD,
	PB_SLAVE_ID_IPP,
	PB_SLAVE_ID_CPU,
	MAX_SLAVES,
};

/* Common Prefetch buffer slave ids */
#define PB_SLAVE_ID_ETH0 PB_SLAVE_ID_ETH_BLK0
#define PB_SLAVE_ID_ETH1 PB_SLAVE_ID_ETH_BLK0
#define PB_SLAVE_ID_ETH2 PB_SLAVE_ID_ETH_BLK1
#define PB_SLAVE_ID_ETH3 PB_SLAVE_ID_ETH_BLK1
#define PB_SLAVE_ID_XGE0 PB_SLAVE_ID_ETH_BLK0
#define PB_SLAVE_ID_XGE1 PB_SLAVE_ID_ETH_BLK1
#define PB_SLAVE_ID_XGE2 PB_SLAVE_ID_ETH_BLK0
#define PB_SLAVE_ID_XGE3 PB_SLAVE_ID_ETH_BLK1
#define PB_SLAVE_ID_ETH4 PB_SLAVE_ID_ETH_BLK0

/* NOTE: Update qm_cfg_dev_ip in apm/qm/linux/apm_qm_cfg.h accordingly */
enum apm_qm_dev_ip {
	IP_CPU0,
	IP_CPU1,
	IP_CPU2,
	IP_CPU3,
	IP_CPU4,
	IP_CPU5,
	IP_CPU6,
	IP_CPU7,
	IP_ETH0,
	IP_ETH1,
	IP_ETH2,
	IP_ETH3,
	IP_XGE0,
	IP_XGE1,
	IP_XGE2,
	IP_XGE3,
	IP_ETH4,
	IP_DMA,
	IP_CTX,
	IP_SEC,
	IP_CLASS,
	IP_MSLIM,
	IP_IPP,
	IP_MAX,
};

enum apm_qm_qtype {
	QUEUE_DISABLED,
	P_QUEUE,
	FREE_POOL,
	V_QUEUE,
};

enum apm_qm_msg_size {
	MSG_16B,
	MSG_32B,
	MSG_64B
};

enum apm_qm_fp_mode {
	MSG_NO_CHANGE,
	ROUND_ADDR,
	REDUCE_LEN,
	CHANGE_LEN
};

enum apm_qm_qsize {
	SIZE_512B,
	SIZE_2KB,
	SIZE_16KB,
	SIZE_64KB,
	SIZE_512KB,
};

enum apm_qm_notify_cpu {
	NO_NOTIFY,
	NOTIFY_CPU0,
	NOTIFY_CPU1,
	NOTIFY_BOTH,
};

/* LErr(3b) Decoding */
enum apm_qm_lerr {
	QM_NO_ERR,
	QM_MSG_SIZE_ERR,
	QM_HOP_COUNT_ERR,
	QM_VQ_ENQ_ERR,
	QM_DISABLEDQ_ENQ_ERR,
	QM_Q_OVERFLOW_ERR,
	QM_ENQUEUE_ERR,
	QM_DEQUEUE_ERR,
};

/* Userinfo encodings for LERR code 6 */

/* err[2:0] Encoding */
#define QM_AXI_READ_ERR             0  /* AXI error on read from CPU mailbox */
#define QM_AXI_ENQ_VQ_ERR           3  /* Alternate enq cmd to a VQ */
#define QM_AXI_ENQ_DQ_ERR           4  /* Alternate enq cmd to a Disabled Q */
#define QM_AXI_ENQ_OVERFLOWQ_ERR    5  /* Alternate enq cmd overfills a Q  */

/* cmd_acr_enq_err[1:0] Encoding  */
enum apm_qm_enq_err {
	QM_NO_AXI_ERR,
	QM_AXI_SLAVE_ERR,  /* AXI slave error on CPU mailbox read   */
	QM_AXI_DECODE_ERR, /* AXI decode error on CPU mailbox read  */
};

/* Userinfo encodings for LERR code 7 */
#define QM_CHILD_VQ_ERR  6     /* VQ was assigned as a child of another VQ  */
#define QM_DEQUEUE_DQ    7     /* dequeue was requested from a disabled PQ */

/*
 * @struct  apm_qm_raw_qstate
 * @brief   This structure represents raw queue state (pq or fp or vq)
 **
 */
struct apm_qm_raw_qstate {
	u32 w0;
	u32 w1;
	u32 w2;
	u32 w3;
	u32 w4;
};

/*
 * @struct  apm_qm_vqstate
 * @brief   This structure represents virtual queue state (vq)
 */
struct apm_qm_vqstate {
	/* word 0 159:128 */
	u32 resv1               : 11;
	u32 cfgqtype            : 2; /* queue type, refer mb_q_type */
	u32 cfgselthrsh         : 3; /*  associated threshold set */
	u32 q0_sel              : 10;
	u32 q0reqvld            : 1;
	u32 q0txallowed         : 1;
	u32 q0selarb            : 2;
	u32 q1_sel_2b           : 2; /* b129:128   split 2/8 */

	/* word 1 127:96 */
	u32 q1_sel_8b           : 8; /* b127:120   split 2/8 */
	u32 q1reqvld            : 1;
	u32 q1txallowed         : 1;
	u32 q1selarb            : 2;
	u32 q2_sel              : 10; /* q2_sel_3b */
	u32 q2reqvld            : 1;
	u32 q2txallowed         : 1;
	u32 q2selarb            : 2;
	u32 q3_sel_6b           : 6; /* b101:96    split 6/4 */

	/* word 2 95:64 */
	u32 q3_sel_4b           : 4;  /* b95:92    split 6/4 */
	u32 q3reqvld            : 1;  /* b91 */
	u32 q3txallowed         : 1;
	u32 q3selarb            : 2;
	u32 q4_sel              : 10; /* b87:78 */
	u32 q4reqvld            : 1;
	u32 q4txallowed         : 1;  /* b76 */
	u32 q4selarb            : 2;  /* b75:74 */
	u32 q5_sel              : 10; /* b73:64 */

	/* word 3 63:32 */
	u32 q5reqvld            : 1;
	u32 q5txallowed         : 1;
	u32 q5selarb            : 2;
	u32 q6_sel              : 10; /* b59:50 */
	u32 q6reqvld            : 1;
	u32 q6txallowed         : 1;
	u32 q6selarb            : 2;
	u32 q7_sel              : 10; /* b45:36 */
	u32 q7reqvld            : 1;
	u32 q7txallowed         : 1;
	u32 q7selarb            : 2;

	/* word 4 31:0 */
	u32 rid                 : 3; /* current region id of queue fill level */
	u32 cpu_notify          : 8; /* see mb_notify_cpu  */
	u32 cfgcrid             : 1; /* critical rid config */
	u32 cfgnotifyqne        : 1; /* enable queue not empty interrupt */
	u32 cfgsaben            : 1; /* enable SAB broadcasting */
	u32 nummsg              : 18;
};

/*
 * @struct  apm_qm_pqstate
 * @brief   This structure represents physical queue state (pq or fp)
 */
struct apm_qm_pqstate {
	/* word 0 31:0 */
	u32 resize_qid          : 10;
	u32 resize_start        : 1;
	u32 resize_done         : 1;
	u32 cfgtmvqen           : 1; /* enable pq to belong to vq */
	u32 cfgtmvq             : 10; /* parent vq */
	u32 cfgsaben            : 1; /* enable SAB broadcasting */
	u32 cpu_notify          : 8; /* cfgcpusab */

	u32 cfgnotifyqne        : 1; /* enable queue not empty interrupt */
	u32 nummsg              : 16;
	u32 headptr             : 15;

	u32 cfgcrid             : 1;
	u32 rid                 : 3;
	u32 qcoherent           : 1;
	u64 cfgstartaddr        : 34;	// 27/7 split

	u32 vc_chanctl          : 2;
	u32 vc_chanid           : 2;
	u32 slot_pending        : 6;
#undef L3_STASHING
	u32 stashing            : 1;
	u32 reserved_0          : 1;
	u32 cfgacceptlerr       : 1;
	u32 fp_mode             : 3; /* free pool mode */
	u32 cfgqsize            : 3; /* queue size, see mb_q_size */
	u32 qstatelock          : 1;
	u32 cfgRecombBuf        : 1;
	u32 cfgRecombBufTimeout : 7; // 4/3 split

	u32 cfgselthrsh         : 3; /*  associated threshold set */
	u32 resv2               : 13;
	u32 cfgqtype            : 2; /* queue type, refer mb_q_type */
	u32 resv1               : 11;
}__attribute__ ((packed));

/*
 * @struct  apm_qm_qstate
 * @brief   This structure represents per queue state database
 */
struct apm_qm_qstate {
	u8 ip_blk;		/**< which ip block this queue belongs to (QM or QM light) */
	u8 valid;		/**< 1 if configured else 0 */
	u16 q_id;		/**< queue id */
	u8 mb_id;		/**< mailbox id, used for ingress only */
	u8 slave_id;		/**< prefetch mgr slave id */
	u8 pbn;			/**< prefetch buffer number */
	u8 q_type;		/**< queue type, see mb_q_type */
	u8 msg_size;		/**< message size supported for this queue */
	u8 vqen;		/**< Virtual Queue enable/disable */
	u32 parent_vqid; 	/**< parent qid, if this pq belongs to any vq */
	u8 cpu_notify; 		/**<
0: Notification not required by CPU,
1: Notify CPU 0 only,
2: Notify CPU 1 only,
3: Notify both CPUs */
	u8 q_size; 		/**< 0: 2KB, 1: 16KB, 2: 64KB, 3: 512KB */
	u64 q_start_addr; 	/**< 28 bit, 256 byte aligned  start addr */
	u8 fp_mode; 		/**< handle addr and len of buf, refer
				  mb_fp_mode
0: No modification to message,
1: Round the start address down to an address
boundary consistant with the size of the buf
2: Reduce the BufDataLen field according to
BufSize - DataAddr(LSBs).
3: Change the BufDataLen field to indicate the
BufSize (zero it out to indicate the maximum
value). */
	u8 thr_set;		/**< configured threshold set (one of eight thresholds) */
	u32 nummsgs;		/**< Number of messages in the queue */
	u8 rid;			/**< Current region ID of the queue */
	u8 q_not_empty_intr;	/**< Enable/disable queue not empty interrupt */
	u8 direction;		/**< 0: ingress, 1: egress */
	u8 cfgsaben;		/**< Enable broadcasting of information on sab bus */
	u8 src_ip_blk;		/**< Requested by IP block */
	u8 cpu_id;		/**< Destination IP block */
	u8 pq_sel[8];           /**< PQs to be added to VQ */
	u8 q_sel_arb[8]; 	/**< For VQ only, select queue arbitration policy:
0: This queue is not enabled for dequeue
1: strict priority
2: WRR priority
3: AVB arbitration */
	u8 shape_rate[8];	/**< Shaping rate in case of AVB ARB,
				  Weight for DRR ARB and not used
				  for SP ARB */
	u8 *startptr;		/**< For alternative enqueue */
	u8 *tailptr;
	u8 *headptr;
	u8 *endptr;

	u32 msg_stat;		/**< Statistic for enqueue or dequeue */
	u32 pending_dealloc;	/**< Pending de-allocate msg to send for FP */
	u32 pending_compl;	/**< Pending de-allocate msg to send for completion message */
	u32 qml_cpu_pbn_cfg;	/**< Configure QM-Lite CPU PBN */
	u32 dma_nummsgs;	/**< Number of messages in the queue */
	struct apm_qm_raw_qstate *dma;
};

/* QM messages */

/*
 * @struct  apm_qm_msg16
 * @brief   This structure represents 16 byte QM message format
 */
struct apm_qm_msg16 {
	u32 UserInfo;

	u32 FPQNum      : 12; /* 12 + Rv(2) */
	u32 Rv2         : 2;
	u32 ELErr       : 2;
	u32 LEI         : 2;
	u32 NV          : 1;
	u32 LL          : 1;
	u32 PB          : 1;
	u32 HB          : 1;
	u32 Rv          : 1;
	u32 In          : 1;
	u32 RType       : 4;
	u32 LErr        : 3;
	u32 HL          : 1;

	u64 DataAddr    : 42; /* 32/10 split */
	u32 Rv6         : 6;
	u32 BufDataLen  : 15;
	u32 C           : 1;
}__attribute__ ((packed));

/*
 * @struct  apm_qm_msg_up16
 * @brief   This structure represents upper 16 byte portion of 32 byte of QM message format
 */
struct apm_qm_msg_up16 {
	u64 H0Info_msb  : 48;
	u32 TotDataLengthLinkListLSBs : 12;
	u32 Rv1         : 1;
	u32 DR          : 1;
	u32 Rv0         : 1;
	u32 HR          : 1;

	u64 H0Info_lsb  : 48;
	u32 H0Enq_Num   : 12;
	u32 H0FPSel     : 4;
}__attribute__ ((packed));

/*
 * @struct  apm_qm_msg_ext8
 * @brief   This structure represents 8 byte portion of QM extended (64B)
 *	    message format
 *
 */
struct apm_qm_msg_ext8 {
	u64 NxtDataAddr         :42;
	u32 Rv2                 :2;
	u32 NxtFPQNum           :4;
	u32 NxtBufDataLength    :15;
	u32 Rv1                 :1;
}__attribute__ ((packed));

/*
 * @struct  apm_qm_msg_ll8
 * @brief   This structure represents 8 byte Link list portion of QM extended (64B)
 *	    message format
 *
 */
struct apm_qm_msg_ll8 {
	u64 NxtDataPtr          :42;
	u32 Rv2                 :2;
	u32 NxtFPQNum           :4;
	u8  NxtLinkListength;
	u8  TotDataLengthLinkListMSBs;
}__attribute__ ((packed));

/*
 * @struct  apm_qm_msg32
 * @brief   This structure represents 32 byte QM message format
 */
struct apm_qm_msg32 {
	struct apm_qm_msg16 msg16;
	struct apm_qm_msg_up16 msgup16;
}__attribute__ ((packed));

/*
 * @struct  apm_qm_msg_ext32
 * @brief   This structure represents 32 byte of QM extended (64B)
 *	    message format
 */
struct apm_qm_msg_ext32 {
	struct apm_qm_msg_ext8 msg8_2;
	struct apm_qm_msg_ext8 msg8_1;
	union {
		struct apm_qm_msg_ext8 msg8_4;
		struct apm_qm_msg_ll8 msg8_ll;
	};
	struct apm_qm_msg_ext8 msg8_3;
}__attribute__ ((packed));

/*
 * @struct  apm_qm_msg64
 * @brief   This structure represents 64 byte QM message format
 */
struct apm_qm_msg64 {
	struct apm_qm_msg32 msg32_1;
	struct apm_qm_msg_ext32 msg32_2;
}__attribute__ ((packed));

/*
 * @struct  apm_qm_mailbox_ctxt
 * @brief   This structure contains mailbox context information
 */
struct apm_qm_mailbox_ctxt {
	/* Variable used for dequeue */
	struct apm_qm_msg32 *cur_ptr;
	struct apm_qm_msg32 *first_ptr;
	struct apm_qm_msg32 *last_ptr;

	/* Variable used for enqueue */
	u16 slot;
	u16 total_slot;
	u16 last_slot;
	u16 unuse_for_align;
} __attribute__ ((packed));

/*
 * @struct  apm_qm_mailbox
 * @brief   This structure represents a work queue mailbox
 */
struct apm_qm_mailbox {
	struct apm_qm_msg32 mailslots[TOTAL_SLOTS_32BYTE_MSG];
};

struct apm_qm_fp_mailbox_ctxt {
	/* Variable used for dequeue */
	struct apm_qm_msg16 *cur_ptr;
	struct apm_qm_msg16 *first_ptr;
	struct apm_qm_msg16 *last_ptr;

	/* Variable used for enqueue */
	u16 slot;
	u16 total_slot;
	u16 last_slot;
	u16 unuse_for_align;
} __attribute__ ((packed));

/*
 * @struct  apm_qm_fp_mailbox
 * @brief   This structure represents a free pool mailbox
 */
struct apm_qm_fp_mailbox {
	struct apm_qm_msg16 mailslots[TOTAL_SLOTS_16BYTE_MSG];
};

/*
 * @struct  apm_qm_msg_desc
 * @brief   This structure represents a QM msg descriptor
 */
struct apm_qm_msg_desc {
	u32 qm_ip_blk;
	u32 qid : 16; 	  /**< destination QID to send message to */
	u32 mb_id : 8; 	  /**< mailbox id to push/pull this message to/from */
	u32 is_msg16 : 8; /**< set this to get 1st 16 bytes message */
	void *msg;	  /**< Pointer to message */
} __attribute__ ((packed));

/* QM callback function type */
typedef int (*apm_qm_msg_fn_ptr) (struct apm_qm_msg_desc *msg_desc);

/*
 * @struct  apm_qm_qalloc
 * @brief   This structure contains info about allocating queues for IP blocks
 */
struct apm_qm_qalloc {
	u8 qm_ip_blk;		/**< refer enum apm_qm_ip */
	u8 ip_blk;		/**< Requesting (source) IP block */
	u8 cpu_id;		/**< Destination IP block */
	u8 q_type;		/**< 0: PQ, 1: VQ, 2: FP */
	u32 q_count;		/**< Number of queues to allocate */
	u8 vqen; 		/**< Enable this PQ to be part of the VQ */
	u32 parent_vq;		/**< If need to attach VQ to PQs, provide VQ */
	u8 direction;		/**< 0: Ingress, 1: Egress */
	u32 qaddr;		/**< Start Address of queue */
	u8 qsize;		/**< Size of queue to be created */
	u8 thr_set;		/**< Queue threshold set to be used */
	u8 en_fill_chk;		/**< Enable queue fill check on this queue */
	u8 q_sel_arb[8];        /**< Arbitration mechanism for VQ */
	u8 pq_sel[8];           /**< PQs to be added to VQ */
	u8 shape_rate[8];       /**< Shaping rate in case of AVB ARB,
				  Weight for DRR ARB and not used
				  for SP ARB */
	struct apm_qm_qstate *qstates;	/**< Store queue states here */
	u32 qml_cpu_pbn_cfg;	/**< Configure QM-Lite CPU PBN */
};

struct apm_qm_device {
	/* QM/QML CSR address for all QMTM i.e. QMTM0, QMTM1, QMTM2, & QMTM3/QMLite */
	u64 qm_csr_paddr;
	//void *qm_csr_vaddr;
	u64 qm_csr_vaddr;
	u64 qm_fabric_paddr;
	//void *qm_fabric_vaddr;
	u64 qm_fabric_vaddr;

	/* iPP-QML CSR address for QMTM3/QMLite only */
	u64 qml_ipp_csr_paddr;
	void *qml_ipp_csr_vaddr;

	/* Mailbox address */
	u64 qm_mailbox_paddr;
	void *qm_mailbox_vaddr;
	u32 qm_mailbox_type;
	u64 qm_enq_mbox_paddr;
	void *qm_enq_mbox_vaddr;
	u32 qm_enq_mbox_size;
	u64 qm_dq_mbox_paddr;
	void *qm_dq_mbox_vaddr;
	u32 qm_dq_mbox_size;
	u64 qm_fp_mbox_paddr;
	void *qm_fp_mbox_vaddr;
	u32 qm_fp_mbox_size;
#ifdef CONFIG_ARCH_MSLIM
	void *cop_axi_vaddr;
	u32 cop_axi_paddr;
	void *cop_csr_vaddr;
	u32 cop_csr_paddr;
#endif
	/* enqueue for work queue and free pool */
	struct apm_qm_mailbox_ctxt mb_enq_mbox_ctxt[ENQUE_MAIL_BOXES];
	/* dequeue for work queue (pq or vq) */
	struct apm_qm_mailbox_ctxt mb_dq_mbox_ctxt[DQ_MAIL_BOXES];
	/* dequeue for free pool */
	struct apm_qm_fp_mailbox_ctxt mb_fp_mbox_ctxt[FP_MAIL_BOXES];

	/* pointer to maibox for enqueue for work queue and free pool */
	struct apm_qm_mailbox *enq_mboxes;
	/* pointer to maibox for dequeue for work queue (pq or vq) */
	struct apm_qm_mailbox *dq_mboxes;
	/* pointer to maibox for dequeue for free pool */
	struct apm_qm_fp_mailbox *fp_mboxes;

	u32 id;		/* qm_ip - IP_BLK_QM0, IP_BLK_QM1, IP_BLK_QM2 or IP_BLK_QML */
	u32 err_qid;	/* Updated in apm_qm_init_errq */
	u32 max_qid;
	u32 max_clr_qid;
	u32 first_qid;
	u32 start_qid;
	u32 start_mboxes;
	u32 max_mboxes;

#define IDX 0
#define MBX 1
#define IRQ 2
	u32 id_mb_irq_map[MAX_MAILBOXS][3];
	u32 sab_irq;
	u32 err_irq;

	/* QM message callback function table */
	apm_qm_msg_fn_ptr qm_cb_fn_table[APM_QM_MAX_RTYPE];
	apm_qm_msg_fn_ptr qm_mailbox_fn_table[MAX_MAILBOXS];

	/* QM message tasklet function table */
	struct apm_qm_mb_tasklet *apm_qm_mb_tasklet_table[MAX_MAILBOXS];

	/* Queue to mailbox and mailbox to queue mappings */
	u32 q_to_mb[QM_MAX_QUEUES];	/* for outbound */
	u32 mb_to_q[MAX_MAILBOXS];	/* for inbound */
	u16 ib_mbox_used[MAX_MAILBOXS];	/* Flag indicates mail box used already */
	u32 ib_mb_pending_chk[MAX_MAILBOXS]; /* # check where message pending */
	u32 pbn_valid[QM_MAX_QUEUES];
	u32 free_qid[QM_MAX_QUEUES/32]; /* Available QID */
	int free_qid_idx;		/* Slot for next available QID */
	u32 dq_fp_ip_to_mb[MAX_SLAVES];  /* Mailbox used to deq msg from IP blk (FQ) */
	u32 ip_pbn_wq_msk[IP_MAX]; 	/* Bit mask indicates available WQ PBN */
	u32 ip_pbn_wq_act[IP_MAX]; 	/* Bit mask indicates in use WQ PBN */
	u32 ip_pbn_fq_msk[IP_MAX]; 	/* Bit mask indicates available FP PBN */
	u32 ip_pbn_fq_act[IP_MAX]; 	/* Bit mask indicates in use FP PBN */

	struct apm_qm_qstate *queue_states;
	struct apm_qm_qstate *comp_qstate;
	struct apm_qm_raw_qstate *q_raw_states;
	struct clk *clk;
};

#ifdef BOOTLOADER
extern struct apm_qm_device *qm_dev[MAX_QM_DEV];
#define QM_DEV(x) qm_dev[x]->
#else
extern struct apm_qm_device qm_dev[MAX_QM_DEV];
#define QM_DEV(x) qm_dev[x].
#endif

/* API declarations */

/**
 * @brief   Determine whether QM is coherent
 * @param   None
 * @return  1 if QM is coherent else 0
 */
static inline int apm_qm_coherent(void)
{
#if !defined(CONFIG_NOT_COHERENT_QM)
	return 1;
#else
	return 0;
#endif
}

/**
 * @brief   Decode buffer length from BufDataLen
 * @param   bufdatalen Encoded buffer data length field
 * @return  Decoded value of buffer length
 */
static inline u16 apm_qm_decode_buflen(u16 bufdatalen)
{
	switch (bufdatalen & 0x7000) {
		case 0x7000:
			return 0x100;
		case 0x6000:
			return 0x400;
		case 0x5000:
			return 0x800;
		case 0x4000:
			return 0x1000;
		default:
			return 0x4000;
	};
}

/**
 * @brief   Decode data length from BufDataLen
 * @param   bufdatalen Encoded buffer data length field
 * @return  Decoded value of data length
 */
static inline u32 apm_qm_decode_datalen(u16 bufdatalen)
{
	switch (bufdatalen & 0x7000) {
		case 0x7000:
			return bufdatalen & 0xFF ? bufdatalen & 0xFF : 0x100;
		case 0x6000:
			return bufdatalen & 0x3FF ? bufdatalen & 0x3FF : 0x400;
		case 0x5000:
			return bufdatalen & 0x7FF ? bufdatalen & 0x7FF : 0x800;
		case 0x4000:
			return bufdatalen & 0xFFF ? bufdatalen & 0xFFF : 0x1000;
		default:
			return bufdatalen & 0x3FFF ? bufdatalen & 0x3FFF : 0x4000;
	};
}

/**
 * @brief   Decrement datalen in BufDataLen
 * @param   Encoded value of buffer data length field
 * @param   Less data from datalen
 * @param   Update datalen with original datalen
 * @return  Encoded value of buffer data length field
 */
static inline u16 apm_qm_less_bufdatalen(u16 bufdatalen, u16 less, u32 *datalen)
{
	u16 mask;
	u16 final_datalen;

	switch ((bufdatalen >> 12) & 0x7) {
		case 7:
			mask = 0xFF;
			break;
		case 6:
			mask = 0x3FF;
			break;
		case 5:
			mask = 0x7FF;
			break;
		case 4:
			mask = 0xFFF;
			break;
		default:
			mask = 0x3FFF;
			break;
	};

	final_datalen = *datalen = (bufdatalen & mask) ? (bufdatalen & mask) : (mask + 1);
	final_datalen = (final_datalen > less) ? (final_datalen - less) : 0;
	bufdatalen = (bufdatalen & ~mask) | final_datalen;

	return bufdatalen;
}

/**
 * @brief   Encode buffer length and data length to BufDataLen
 * @param   len Data length or Buffer length
 * @return  Encoded value of buffer data length field
 */
static inline u16 apm_qm_encode_bufdatalen(u32 len)
{
	if (len <= 0x100) {
		return (0x7 << 12) | (len & 0xFF);
	} else if (len <= 0x400) {
		return (0x6 << 12) | (len & 0x3FF);
	} else if (len <= 0x800) {
		return (0x5 << 12) | (len & 0x7FF);
	} else if (len <= 0x1000) {
		return (0x4 << 12) | (len & 0xFFF);
	} else if (len < 0x4000) {
		return len & 0x3FFF;
	} else {
		return 0;
	}
}

/**
 * @brief   Encode data length to BufDataLen assuming maximum buffer size
 * @param   len Data length
 * @return  Encoded value of buffer data length field
 */
static inline u16 apm_qm_encode_datalen(u32 len)
{
	return len & 0x3FFF;
}

/**
 * @brief   Check if next buffer data length field is valid.
 * @param   nxtbufdatalen Next buffer data length field of a Extended Message
 * @return  0 - success or -1 - failure
 */
static inline int apm_qm_nxtbufdatalen_is_valid(u16 nxtbufdatalen)
{
	return nxtbufdatalen == 0x7800 ? 0 : 1;
}

/**
 * @brief   Initialize QM IP
 * @param   qm_ip - IP_BLK_QM0, IP_BLK_QM1, IP_BLK_QM2 or IP_BLK_QML
 * @return  0 - success or -1 - failure
 */
int apm_qm_ip_init(u32 qm_ip);
void apm_qm_ip_shutdown(u32 qm_ip);

/**
 * @brief   Initialize Error Q
 * @param   qm_ip - IP_BLK_QM0, IP_BLK_QM1 or IP_BLK_QM2
 * 	    CPU ID to which error Q will interrupt
 * @return  0 - success or -1 - failure
 */
int apm_qm_init_errq(u32 qm_ip, u32 cpu_id);

/**
 * @brief   Initialize QM HW block
 * @param   qm_ip - IP_BLK_QM0, IP_BLK_QM1, IP_BLK_QM2 or IP_BLK_QML
 *	    no_of_queues Number of queues to initialize
 * @return  0 - success or -1 - failure
 */
int apm_qm_init_queue(u32 qm_ip, u32 no_of_queues);

/**
 * @brief   Free QM qstates
 * @param   qm_ip - IP_BLK_QM0, IP_BLK_QM1, IP_BLK_QM2 or IP_BLK_QML
 * @return  0 - success or -1 - failure
 */
int apm_qm_free_qstates(u32 qm_ip);

/**
 * @brief   Return the current qstate configuration without talking to QM HW
 * @param   qm_ip - IP_BLK_QM0, IP_BLK_QM1, IP_BLK_QM2 or IP_BLK_QML
 * 	    q_num Queue number
 * 	    qstate Pointer to queue state structure for this queue
 * @return  0 - success or -1 - failure
 */
int apm_qm_qstate_rd_cfg(u32 qm_ip, u32 q_num, struct apm_qm_qstate *qstate);

/**
 * @brief   Reads the state of the given queue number from QM
 * @param   qm_ip - IP_BLK_QM0, IP_BLK_QM1, IP_BLK_QM2 or IP_BLK_QML
 * 	    q_num Queue number
 *          qstate Pointer to queue state structure for this queue
 * @return  0 - success or -1 - failure
 */
int apm_qm_qstate_rd(u32 qm_ip, u32 q_num, struct apm_qm_qstate *qstate);

/**
 * @brief   Writes the state of the given queue number to QM
 * @param   qstate Pointer to queue state structure for this queue
 * @return  0 - success or -1 - failure
 */
int apm_qm_qstate_wr(struct apm_qm_qstate *qstate);

/**
 * @brief   Frees qstate->qaddr, invalidate qstate and deletes queue in the hw
 * @param   qm_ip - IP_BLK_QM0, IP_BLK_QM1, IP_BLK_QM2 or IP_BLK_QML
 * 	    q_num Queue number
 * @return  0 - success or -1 - failure
 */
int apm_qm_delete_queue(u32 qm_ip, u32 q_num);

/**
 * @brief   Reads the state of the given queue number from QM in RAW format
 * @param   qm_ip - IP_BLK_QM0, IP_BLK_QM1, IP_BLK_QM2 or IP_BLK_QML
 * 	    q_num Queue number to read the state for
 *          raw_qstate Pointer to queue state structure for this queue
 * @return  0 - success or -1 - failure
 */
int apm_qm_raw_qstate_rd(u32 qm_ip, u32 q_num, struct apm_qm_raw_qstate *raw_q);

/**
 * @brief   Writes the state of the given queue number in QM in RAW format
 * @param   qm_ip - IP_BLK_QM0, IP_BLK_QM1, IP_BLK_QM2 or IP_BLK_QML
 * 	    q_num Queue number to write the state for
 *          raw_qstate Pointer to queue state structure for this queue
 * @return  0 - success or -1 - failure
 */
int apm_qm_raw_qstate_wr(u32 qm_ip, u32 q_num, struct apm_qm_raw_qstate *raw_q);

/**
 * @brief   Enqueues (Pushes) the message to mailbox on given QML queue
 * @param   msg_desc Descriptor of the message to push
 * @return  0 - success or -1 - failure
 */
int apm_qml_push_msg(struct apm_qm_msg_desc *msg_desc);

/**
 * @brief   Enqueues (Pushes) the message to mailbox on given QM queue
 * @param   msg_desc Descriptor of the message to push
 * @return  0 - success or -1 - failure
 */
int apm_qm_push_msg(struct apm_qm_msg_desc *msg_desc);

/**
 * @brief   Gives the userinfo from completion queue
 * @param   qm_ip - IP_BLK_QM0, IP_BLK_QM1 or IP_BLK_QM2
 * 	    mb_id Mailbox ID
 * @return  userinfo - success or -1 - failure
 */
u32 apm_qm_pull_comp_msg(u32 qm_ip, u32 mb_id);

/**
 * @brief   Gives the userinfo from completion queue but notify QM in batch
 * @param   qm_ip - IP_BLK_QM0, IP_BLK_QM1 or IP_BLK_QM2
 * 	    mb_id Mailbox ID
 * @return  userinfo - success or -1 - failure
 */
u32 apm_qm_pull_comp_msg2(u32 qm_ip, u32 mb_id);


/**
 * @brief   Gives the userinfo from completion queue
 * @param   qm_ip - IP_BLK_QM0, IP_BLK_QM1 or IP_BLK_QM2
 * 	    mb_id Mailbox ID
 * @return  userinfo - success or -1 - failure
 */
int apm_qml_pull_comp_msg(u32 qm_ip, u32 qid);

/**
 * @brief   Explicit notify QM if any pending decrement due to batch notify
 * @param   qm_ip - IP_BLK_QM0, IP_BLK_QM1 or IP_BLK_QM2
 * 	    mb_id Mailbox ID
 * @return  userinfo - success or -1 - failure
 */
int apm_qm_pull_comp_flush(u32 qm_ip, u32 mb_id);

/**
 * @brief   Dequeues (Pulls) the message from mailbox on given queue
 * @param   msg_desc Descriptor of the message to pull
 * @return  0 - success or -1 - failure
 */
int apm_qm_pull_msg(struct apm_qm_msg_desc *msg_desc);

/**
 * @brief   Deallocates buffer to given QML buffer pool
 * @param   msg_desc Descriptor of the msg (containing buffer to deallocate)
 * @return  0 - success or -1 - failure
 * NOTE: This function can be routed to alternative enqueue version or non-
 *       alternative enqueue version depends if alternative enqueue is
 *       enabled or not.
 */
int apm_qml_fp_dealloc_buf(struct apm_qm_msg_desc *msg_desc);

/**
 * @brief   Deallocates buffer to given buffer pool
 * @param   msg_desc Descriptor of the msg (containing buffer to deallocate)
 * @return  0 - success or -1 - failure
 */
int apm_qm_fp_dealloc_buf(struct apm_qm_msg_desc *msg_desc);

/**
 * @brief   Explicit notify QM if any pending decrement due to batch notify
 * @param   qm_ip - IP_BLK_QM0, IP_BLK_QM1 or IP_BLK_QM2
 * 	    mb_id Mailbox ID
 * @return  0 - success or -1 - failure
 */
int apm_qm_fp_dealloc_flush(u32 qm_ip, u32 qid);

/**
 * @brief   Allocate buffer to given buffer pool
 * @param   msg_desc Descriptor of the msg (containing buffer to allocate)
 * @return  0 - success or -1 - failure
 */
int apm_qm_fp_alloc_buf(struct apm_qm_msg_desc *msg_desc);

/**
 * @brief   Dequeues (Pulls) the message from QML queue
 * @param   msg Descriptor of the message to pull
 * @return  0 - success or -1 - failure
 */
int apm_qml_pull_msg(struct apm_qm_msg_desc *msg_desc);

/**
 * @brief   Unregister QM callback function for given RTYPE
 * @param   qm_ip - IP_BLK_QM0, IP_BLK_QM1 or IP_BLK_QM2
 * 	    rtype RTYPE for which to register callback
 * @return  0 - success or -1 - failure
 */
int apm_qm_msg_rx_unregister(u32 qm_ip, u32 rtype);

/**
 * @brief   Register QM callback function for given RTYPE
 * @param   qm_ip - IP_BLK_QM0, IP_BLK_QM1 or IP_BLK_QM2
 * 	    rtype RTYPE for which to register callback
 *	    fn_ptr Callback function pointer
 * @return  0 - success or -1 - failure
 */
int apm_qm_msg_rx_register(u32 qm_ip, u32 rtype, apm_qm_msg_fn_ptr fn_ptr);

/**
 * @brief   Unregister direct QM callback function for given Mail box
 * @param   qm_ip - IP_BLK_QM0, IP_BLK_QM1 or IP_BLK_QM2
 * 	    mbidx Mailbox index
 * @return  0 - success or -1 - failure
 */
int apm_qm_mailbox_rx_unregister(u32 qm_ip, u32 mbidx);

/**
 * @brief   Register direct QM callback function for given Mail box
 * @param   qm_ip - IP_BLK_QM0, IP_BLK_QM1 or IP_BLK_QM2
 * @param   mbidx Mailbox index
 * @param   fn_ptr Callback function pointer
 * @return  0 - success or -1 - failure
 */
int apm_qm_mailbox_rx_register(u32 qm_ip, u32 mbidx, apm_qm_msg_fn_ptr fn_ptr);

/**
 * @brief   Parse the exact for the Error Message received on Errro Queue
 * @param   err_msg_desc - Descriptor of the Error msg
 * @return  None
 */
void apm_qm_parse_error(struct apm_qm_msg_desc *err_msg_desc);

/**
 * @brief   Return queues to given IP blocks
 * @param   qm_ip - IP_BLK_QM0, IP_BLK_QM1 or IP_BLK_QM2
 * @param   qalloc Structure filled up with queue allocation information for QM driver
 * @return  0 - success or -1 - failure
 */
int apm_qm_alloc_q(struct apm_qm_qalloc *qalloc);

int apm_qm_free_q(struct apm_qm_qstate *qstate);

/**
 * @brief   Return Virtual queue to given IP blocks
 * @param   qalloc Structure filled up with queue allocation information
 *		for QM driver
 * @return  0 - success or -1 - failure
 */
int apm_qm_alloc_vq(struct apm_qm_qalloc *qalloc, u32 qid);

/**
 * @brief   Return completion queue for current CPU
 * @param   qm_ip - IP_BLK_QM0, IP_BLK_QM1 or IP_BLK_QM2
 * @return  0 - success or -1 - failure
 */
struct apm_qm_qstate *apm_qm_get_compl_queue(u32 qm_ip);

/**
 * @brief   Return completion queue size for ip block
 * @param   qm_ip - IP_BLK_QM0, IP_BLK_QM1, IP_BLK_QM2 or IP_BLK_QML
 * @return  actual size in bytes
 */
u32 apm_qm_get_compl_queue_size(u32 qm_ip);

/**
 * @brief   Configure prefetch buffer table
 * @param   qm_ip - IP_BLK_QM0, IP_BLK_QM1, IP_BLK_QM2 or IP_BLK_QML
 *	    slv_id PBN Slave ID
 *	    pbn prefetch buffer number to configure
 *	    qnum Queue number to configure PBN for
 *	    is_fp Is it free queue or not
 * @return  None
 */
int apm_qm_pb_config(u32 qm_ip, u32 slv_id, u32 pbn, u32 qnum, u8 is_fp, u8 is_vq);

u32 apm_qm_pb_get(u32 qm_ip, u32 slv_id, u32 pbn);
u32 apm_qm_pb_set(u32 qm_ip, u32 slv_id, u32 pbn, u32 pbn_buf);
int apm_qm_pb_disable(u32 qm_ip, u32 slv_id, u32 pbn, u32 qnum);
int apm_qm_pb_overwrite(u32 qm_ip, u32 slv_id, u32 pbn, u32 qnum, u8 is_fp);
u32 apm_qm_pb_get(u32 qm_ip, u32 slv_id, u32 pbn);
int apm_qm_pb_clr(u32 qm_ip, u32 slv_id, u32 pbn);
int apm_qm_enq_stats_setqid(u32 qm_ip, u32 qid);
u32 apm_qm_enq_stats_getqid(u32 qm_ip);
u32 apm_qm_enq_stats_value(u32 qm_ip);
int apm_qm_deq_stats_setqid(u32 qm_ip, u32 qid);
u32 apm_qm_deq_stats_getqid(u32 qm_ip);
u32 apm_qm_deq_stats_value(u32 qm_ip);
void apm_qm_set_enq_mbox_addr(u32 qm_ip, u32 coherent, u64 paddr);
void apm_qm_set_dq_mbox_addr(u32 qm_ip, u32 coherent, u64 paddr);
void apm_qm_set_fp_mbox_addr(u32 qm_ip, u32 coherent, u64 paddr);
int apm_qm_alloc_mbox(u32 qm_ip);
int apm_qm_cstate_rd(u32 qm_ip, u32 qid, u32 * cstate);
int apm_qm_cstate_wr(u32 qm_ip, u32 qid, u32 cstate[2]);
int apm_qm_get_vq(u32 qm_ip, u32 ip_blk);
int apm_qm_alt_enqueue_enable(void);
int apm_qm_irq_err(u32 qm_ip);

int apm_qm_is_pbn_valid(u32 qm_ip, u32 qid);
void apm_qm_clr_pbn_valid(u32 qm_ip, u32 qid);
int apm_qm_mb2qid(u32 qm_ip, u32 mb);
int apm_qm_qid2mb(u32 qm_ip, u32 qid);

void apm_qm_set_mboxes(u32 qm_ip, u32 maxboxes, u32 startboxes);
u32 apm_qm_get_start_mboxes(u32 qm_ip);
u32 apm_qm_get_max_mboxes(u32 qm_ip);
void apm_qm_set_qid(u32 qm_ip, u32 fqid, u32 sqid, u32 maxqid, u32 maxclrqid);
u32 apm_qm_get_first_qid(u32 qm_ip);
u32 apm_qm_get_start_qid(u32 qm_ip);
u32 apm_qm_get_max_qid(u32 qm_ip);
u32 apm_qm_get_max_clr_qid(u32 qm_ip);
void apm_qm_set_smp(u8 is_smp);
u8 apm_qm_get_smp(void);
void apm_qm_set_noqml(u8 is_noqml);
u8 apm_qm_get_noqml(void);
void apm_qm_msg_not_empty_intr_coal_set(u32 qm_ip, u32 tap);
int apm_qm_mbox_set_coal(u32 qm_ip, u32 mbox_id, u32 tap);
int apm_qm_get_slave_id(u32 ip_blk);

/* Mailbox SoftIRQ Context */
struct apm_qm_mb_tasklet {
	u32 qm_ip_blk;
	u32 mailbox;
	u32 queue;
	u32 core;
	void *ctx;
	void *tasklet;	/* OS specific structure */
};

int apm_qm_mb_tasklet_unregister(u32 qm_ip, struct apm_qm_mb_tasklet *handler);
int apm_qm_mb_tasklet_register(u32 qm_ip, u32 mailbox, u32 queue, u32 core, void *ctx,
		void (*func)(unsigned long));
int apm_qm_indirect_access_lock(int lock);
int apm_qm_enable_hwirq(u32 qm_ip);
void apm_qm_disable_hwirq(u32 qm_ip);
int apm_qm_update_tm_timer(u32 qm_ip, u32 val);

#endif /* __APM_QM_CORE_H__ */
