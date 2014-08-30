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

#ifndef _APM_QM_CSR_H__
#define _APM_QM_CSR_H__

#ifndef CONFIG_STORM
#define CONFIG_STORM
#endif
#if defined(CONFIG_STORM)
/* For APM88xxxx */

/*	Global Base Address	*/
#define QM0_CSR_BASE_ADDR			0x01f600000ULL
#define QM1_CSR_BASE_ADDR			0x01f200000ULL
#define QM2_CSR_BASE_ADDR			0x01f700000ULL
#define QML_CSR_BASE_ADDR			0x017030000ULL

/*    Address QM_CSR Registers */
#define CSR_IPBRR_ADDR                                               0x00000000
#define CSR_IPBRR_DEFAULT                                            0x00000070
#define CSR_QM_CONFIG_ADDR                                           0x00000004
#define CSR_QM_CONFIG_DEFAULT                                        0x00000000
#define CSR_PBM_ADDR                                                 0x00000008
#define CSR_PBM_DEFAULT                                              0x00000000
#define CSR_PBM_BUF_WR_ADDR                                          0x0000000c
#define CSR_PBM_BUF_WR_DEFAULT                                       0x00000000
#define CSR_PBM_BUF_RD_ADDR                                          0x00000010
#define CSR_PBM_BUF_RD_DEFAULT                                       0x00000000
#define CSR_PBM_COAL_ADDR                                            0x00000014
#define CSR_PBM_COAL_DEFAULT                                         0x00000109
#define CSR_PBM_CTICK0_ADDR                                          0x00000018
#define CSR_PBM_CTICK0_DEFAULT                                       0x00000000
#define CSR_PBM_CTICK1_ADDR                                          0x0000001c
#define CSR_PBM_CTICK1_DEFAULT                                       0x00000000
#define CSR_PBM_CTICK2_ADDR                                          0x00000020
#define CSR_PBM_CTICK2_DEFAULT                                       0x00000000
#define CSR_PBM_CTICK3_ADDR                                          0x00000024
#define CSR_PBM_CTICK3_DEFAULT                                       0x00000000
#define CSR_THRESHOLD0_SET0_ADDR                                     0x00000028
#define CSR_THRESHOLD0_SET0_DEFAULT                                  0x00000000
#define CSR_THRESHOLD1_SET0_ADDR                                     0x0000002c
#define CSR_THRESHOLD1_SET0_DEFAULT                                  0x00000000
#define CSR_THRESHOLD0_SET1_ADDR                                     0x00000030
#define CSR_THRESHOLD0_SET1_DEFAULT                                  0x00000000
#define CSR_THRESHOLD1_SET1_ADDR                                     0x00000034
#define CSR_THRESHOLD1_SET1_DEFAULT                                  0x00000000
#define CSR_THRESHOLD0_SET2_ADDR                                     0x00000038
#define CSR_THRESHOLD0_SET2_DEFAULT                                  0x00000000
#define CSR_THRESHOLD1_SET2_ADDR                                     0x0000003c
#define CSR_THRESHOLD1_SET2_DEFAULT                                  0x00000000
#define CSR_THRESHOLD0_SET3_ADDR                                     0x00000040
#define CSR_THRESHOLD0_SET3_DEFAULT                                  0x00000000
#define CSR_THRESHOLD1_SET3_ADDR                                     0x00000044
#define CSR_THRESHOLD1_SET3_DEFAULT                                  0x00000000
#define CSR_THRESHOLD0_SET4_ADDR                                     0x00000048
#define CSR_THRESHOLD0_SET4_DEFAULT                                  0x00000000
#define CSR_THRESHOLD1_SET4_ADDR                                     0x0000004c
#define CSR_THRESHOLD1_SET4_DEFAULT                                  0x00000000
#define CSR_THRESHOLD0_SET5_ADDR                                     0x00000050
#define CSR_THRESHOLD0_SET5_DEFAULT                                  0x00000000
#define CSR_THRESHOLD1_SET5_ADDR                                     0x00000054
#define CSR_THRESHOLD1_SET5_DEFAULT                                  0x00000000
#define CSR_THRESHOLD0_SET6_ADDR                                     0x00000058
#define CSR_THRESHOLD0_SET6_DEFAULT                                  0x00000000
#define CSR_THRESHOLD1_SET6_ADDR                                     0x0000005c
#define CSR_THRESHOLD1_SET6_DEFAULT                                  0x00000000
#define CSR_THRESHOLD0_SET7_ADDR                                     0x00000060
#define CSR_THRESHOLD0_SET7_DEFAULT                                  0x00000000
#define CSR_THRESHOLD1_SET7_ADDR                                     0x00000064
#define CSR_THRESHOLD1_SET7_DEFAULT                                  0x00000000
#define CSR_HYSTERESIS_ADDR                                          0x00000068
#define CSR_HYSTERESIS_DEFAULT                                       0x00000000
#define CSR_QSTATE_ADDR                                              0x0000006c
#define CSR_QSTATE_DEFAULT                                           0x00000000
#define CSR_QSTATE_WR_0_ADDR                                         0x00000070
#define CSR_QSTATE_WR_0_DEFAULT                                      0x00000000
#define CSR_QSTATE_WR_1_ADDR                                         0x00000074
#define CSR_QSTATE_WR_1_DEFAULT                                      0x00000000
#define CSR_QSTATE_WR_2_ADDR                                         0x00000078
#define CSR_QSTATE_WR_2_DEFAULT                                      0x00000000
#define CSR_QSTATE_WR_3_ADDR                                         0x0000007c
#define CSR_QSTATE_WR_3_DEFAULT                                      0x00000000
#define CSR_QSTATE_WR_4_ADDR                                         0x00000080
#define CSR_QSTATE_WR_4_DEFAULT                                      0x00000000
#define CSR_QSTATE_RD_0_ADDR                                         0x00000084
#define CSR_QSTATE_RD_0_DEFAULT                                      0x00000000
#define CSR_QSTATE_RD_1_ADDR                                         0x00000088
#define CSR_QSTATE_RD_1_DEFAULT                                      0x00000000
#define CSR_QSTATE_RD_2_ADDR                                         0x0000008c
#define CSR_QSTATE_RD_2_DEFAULT                                      0x00000000
#define CSR_QSTATE_RD_3_ADDR                                         0x00000090
#define CSR_QSTATE_RD_3_DEFAULT                                      0x00000000
#define CSR_QSTATE_RD_4_ADDR                                         0x00000094
#define CSR_QSTATE_RD_4_DEFAULT                                      0x00000000
#define CSR_CSTATE_WR_0_ADDR                                         0x0000009c
#define CSR_CSTATE_WR_0_DEFAULT                                      0x00000000
#define CSR_CSTATE_WR_1_ADDR                                         0x000000a0
#define CSR_CSTATE_WR_1_DEFAULT                                      0x00000000
#define CSR_CSTATE_RD_0_ADDR                                         0x000000a4
#define CSR_CSTATE_RD_0_DEFAULT                                      0x00000000
#define CSR_CSTATE_RD_1_ADDR                                         0x000000a8
#define CSR_CSTATE_RD_1_DEFAULT                                      0x00000000
#define CSR_CU_TIMER_ADDR                                            0x000000ac
#define CSR_CU_TIMER_DEFAULT                                         0x00000000
#define CSR_PROC_MBOX_BASE_0_ADDR                                    0x000000b0
#define CSR_PROC_MBOX_BASE_0_DEFAULT                                 0x00000000
#define CSR_PROC_MBOX_BASE_1_ADDR                                    0x000000b4
#define CSR_PROC_MBOX_BASE_1_DEFAULT                                 0x00000000
#define CSR_PROC_MBOX_BASE_2_ADDR                                    0x000000b8
#define CSR_PROC_MBOX_BASE_2_DEFAULT                                 0x00000000
#define CSR_PROC_MBOX_BASE_3_ADDR                                    0x000000bc
#define CSR_PROC_MBOX_BASE_3_DEFAULT                                 0x00000000
#define CSR_PROC_FPOOL_BASE_0_ADDR                                   0x000000c0
#define CSR_PROC_FPOOL_BASE_0_DEFAULT                                0x00000000
#define CSR_PROC_FPOOL_BASE_1_ADDR                                   0x000000c4
#define CSR_PROC_FPOOL_BASE_1_DEFAULT                                0x00000000
#define CSR_PROC_FPOOL_BASE_2_ADDR                                   0x000000c8
#define CSR_PROC_FPOOL_BASE_2_DEFAULT                                0x00000000
#define CSR_PROC_FPOOL_BASE_3_ADDR                                   0x000000cc
#define CSR_PROC_FPOOL_BASE_3_DEFAULT                                0x00000000
#define CSR_ENQ_BASE_0_ADDR                                          0x000000d4
#define CSR_ENQ_BASE_0_DEFAULT                                       0x00000000
#define CSR_ENQ_BASE_1_ADDR                                          0x000000d8
#define CSR_ENQ_BASE_1_DEFAULT                                       0x00000000
#define CSR_ENQ_BASE_2_ADDR                                          0x000000dc
#define CSR_ENQ_BASE_2_DEFAULT                                       0x00000000
#define CSR_ENQ_BASE_3_ADDR                                          0x000000e0
#define CSR_ENQ_BASE_3_DEFAULT                                       0x00000000
#define CSR_ENQ_STATUS_0_ADDR                                        0x000000e4
#define CSR_ENQ_STATUS_0_DEFAULT                                     0x00000000
#define CSR_ENQ_STATUS_1_ADDR                                        0x000000e8
#define CSR_ENQ_STATUS_1_DEFAULT                                     0x00000000
#define CSR_ENQ_STATUS_2_ADDR                                        0x000000ec
#define CSR_ENQ_STATUS_2_DEFAULT                                     0x00000000
#define CSR_ENQ_STATUS_3_ADDR                                        0x000000f0
#define CSR_ENQ_STATUS_3_DEFAULT                                     0x00000000
#define CSR_ENQ_STATUS_4_ADDR                                        0x000000f4
#define CSR_ENQ_STATUS_4_DEFAULT                                     0x00000000
#define CSR_ENQ_STATUS_5_ADDR                                        0x000000f8
#define CSR_ENQ_STATUS_5_DEFAULT                                     0x00000000
#define CSR_ENQ_STATUS_6_ADDR                                        0x000000fc
#define CSR_ENQ_STATUS_6_DEFAULT                                     0x00000000
#define CSR_ENQ_STATUS_7_ADDR                                        0x00000100
#define CSR_ENQ_STATUS_7_DEFAULT                                     0x00000000
#define CSR_ENQ_STATUS_8_ADDR                                        0x00000104
#define CSR_ENQ_STATUS_8_DEFAULT                                     0x00000000
#define CSR_ENQ_STATUS_9_ADDR                                        0x00000108
#define CSR_ENQ_STATUS_9_DEFAULT                                     0x00000000
#define CSR_ENQ_STATUS_10_ADDR                                       0x0000010c
#define CSR_ENQ_STATUS_10_DEFAULT                                    0x00000000
#define CSR_ENQ_STATUS_11_ADDR                                       0x00000110
#define CSR_ENQ_STATUS_11_DEFAULT                                    0x00000000
#define CSR_ENQ_STATUS_12_ADDR                                       0x00000114
#define CSR_ENQ_STATUS_12_DEFAULT                                    0x00000000
#define CSR_ENQ_STATUS_13_ADDR                                       0x00000118
#define CSR_ENQ_STATUS_13_DEFAULT                                    0x00000000
#define CSR_ENQ_STATUS_14_ADDR                                       0x0000011c
#define CSR_ENQ_STATUS_14_DEFAULT                                    0x00000000
#define CSR_ENQ_STATUS_15_ADDR                                       0x00000120
#define CSR_ENQ_STATUS_15_DEFAULT                                    0x00000000
#define QM_INTERRUPT_ADDR                                            0x00000124
#define QM_INTERRUPT_DEFAULT                                         0x00000000
#define QM_INTERRUPTMASK_ADDR                                        0x00000128
#define QM_SAB_QNE_INTERRUPT_ADDR                                    0x0000012c
#define QM_SAB_QNE_INTERRUPT_DEFAULT                                 0x00000000
#define QM_SAB_QNE_INTERRUPTMASK_ADDR                                0x00000130
#define CSR_PBM_ERRINF_ADDR                                          0x00000134
#define CSR_PBM_ERRINF_DEFAULT                                       0x00000000
#define CSR_MSGRD_ERRINF_ADDR                                        0x00000138
#define CSR_MSGRD_ERRINF_DEFAULT                                     0x00000000
#define CSR_QM_SAB_PROC0_ADDR                                        0x0000013c
#define CSR_QM_SAB_PROC0_DEFAULT                                     0x00000000
#define CSR_QM_SAB_PROC0MASK_ADDR                                    0x00000140
#define CSR_QM_SAB_PROC1_ADDR                                        0x00000144
#define CSR_QM_SAB_PROC1_DEFAULT                                     0x00000000
#define CSR_QM_SAB_PROC1MASK_ADDR                                    0x00000148
#define CSR_QM_SAB_PROC2_ADDR                                        0x0000014c
#define CSR_QM_SAB_PROC2_DEFAULT                                     0x00000000
#define CSR_QM_SAB_PROC2MASK_ADDR                                    0x00000150
#define CSR_QM_SAB_PROC3_ADDR                                        0x00000154
#define CSR_QM_SAB_PROC3_DEFAULT                                     0x00000000
#define CSR_QM_SAB_PROC3MASK_ADDR                                    0x00000158
#define CSR_QM_SAB_PROC4_ADDR                                        0x0000015c
#define CSR_QM_SAB_PROC4_DEFAULT                                     0x00000000
#define CSR_QM_SAB_PROC4MASK_ADDR                                    0x00000160
#define CSR_QM_SAB_PROC5_ADDR                                        0x00000164
#define CSR_QM_SAB_PROC5_DEFAULT                                     0x00000000
#define CSR_QM_SAB_PROC5MASK_ADDR                                    0x00000168
#define CSR_QM_SAB_PROC6_ADDR                                        0x0000016c
#define CSR_QM_SAB_PROC6_DEFAULT                                     0x00000000
#define CSR_QM_SAB_PROC6MASK_ADDR                                    0x00000170
#define CSR_QM_SAB_PROC7_ADDR                                        0x00000174
#define CSR_QM_SAB_PROC7_DEFAULT                                     0x00000000
#define CSR_QM_SAB_PROC7MASK_ADDR                                    0x00000178
#define CSR_QM_MBOX_NE_INT_MODE_ADDR                                 0x0000017c
#define CSR_QM_MBOX_NE_INT_MODE_DEFAULT                              0x00000000
#define CSR_QM_MBOX_NE_ADDR                                          0x00000180
#define CSR_QM_MBOX_NE_DEFAULT                                       0x00000000
#define CSR_PROC_SAB0_ADDR                                           0x00000184
#define CSR_PROC_SAB0_DEFAULT                                        0x00000000
#define CSR_PROC_SAB1_ADDR                                           0x00000188
#define CSR_PROC_SAB1_DEFAULT                                        0x00000000
#define CSR_PROC_SAB2_ADDR                                           0x0000018c
#define CSR_PROC_SAB2_DEFAULT                                        0x00000000
#define CSR_PROC_SAB3_ADDR                                           0x00000190
#define CSR_PROC_SAB3_DEFAULT                                        0x00000000
#define CSR_PROC_SAB4_ADDR                                           0x00000194
#define CSR_PROC_SAB4_DEFAULT                                        0x00000000
#define CSR_PROC_SAB5_ADDR                                           0x00000198
#define CSR_PROC_SAB5_DEFAULT                                        0x00000000
#define CSR_PROC_SAB6_ADDR                                           0x0000019c
#define CSR_PROC_SAB6_DEFAULT                                        0x00000000
#define CSR_PROC_SAB7_ADDR                                           0x000001a0
#define CSR_PROC_SAB7_DEFAULT                                        0x00000000
#define CSR_PROC_SAB8_ADDR                                           0x000001a4
#define CSR_PROC_SAB8_DEFAULT                                        0x00000000
#define CSR_PROC_SAB9_ADDR                                           0x000001a8
#define CSR_PROC_SAB9_DEFAULT                                        0x00000000
#define CSR_PROC_SAB10_ADDR                                          0x000001ac
#define CSR_PROC_SAB10_DEFAULT                                       0x00000000
#define CSR_PROC_SAB11_ADDR                                          0x000001b0
#define CSR_PROC_SAB11_DEFAULT                                       0x00000000
#define CSR_PROC_SAB12_ADDR                                          0x000001b4
#define CSR_PROC_SAB12_DEFAULT                                       0x00000000
#define CSR_PROC_SAB13_ADDR                                          0x000001b8
#define CSR_PROC_SAB13_DEFAULT                                       0x00000000
#define CSR_PROC_SAB14_ADDR                                          0x000001bc
#define CSR_PROC_SAB14_DEFAULT                                       0x00000000
#define CSR_PROC_SAB15_ADDR                                          0x000001c0
#define CSR_PROC_SAB15_DEFAULT                                       0x00000000
#define CSR_PROC_SAB16_ADDR                                          0x000001c4
#define CSR_PROC_SAB16_DEFAULT                                       0x00000000
#define CSR_PROC_SAB17_ADDR                                          0x000001c8
#define CSR_PROC_SAB17_DEFAULT                                       0x00000000
#define CSR_PROC_SAB18_ADDR                                          0x000001cc
#define CSR_PROC_SAB18_DEFAULT                                       0x00000000
#define CSR_PROC_SAB19_ADDR                                          0x000001d0
#define CSR_PROC_SAB19_DEFAULT                                       0x00000000
#define CSR_PROC_SAB20_ADDR                                          0x000001d4
#define CSR_PROC_SAB20_DEFAULT                                       0x00000000
#define CSR_PROC_SAB21_ADDR                                          0x000001d8
#define CSR_PROC_SAB21_DEFAULT                                       0x00000000
#define CSR_PROC_SAB22_ADDR                                          0x000001dc
#define CSR_PROC_SAB22_DEFAULT                                       0x00000000
#define CSR_PROC_SAB23_ADDR                                          0x000001e0
#define CSR_PROC_SAB23_DEFAULT                                       0x00000000
#define CSR_PROC_SAB24_ADDR                                          0x000001e4
#define CSR_PROC_SAB24_DEFAULT                                       0x00000000
#define CSR_PROC_SAB25_ADDR                                          0x000001e8
#define CSR_PROC_SAB25_DEFAULT                                       0x00000000
#define CSR_PROC_SAB26_ADDR                                          0x000001ec
#define CSR_PROC_SAB26_DEFAULT                                       0x00000000
#define CSR_PROC_SAB27_ADDR                                          0x000001f0
#define CSR_PROC_SAB27_DEFAULT                                       0x00000000
#define CSR_PROC_SAB28_ADDR                                          0x000001f4
#define CSR_PROC_SAB28_DEFAULT                                       0x00000000
#define CSR_PROC_SAB29_ADDR                                          0x000001f8
#define CSR_PROC_SAB29_DEFAULT                                       0x00000000
#define CSR_PROC_SAB30_ADDR                                          0x000001fc
#define CSR_PROC_SAB30_DEFAULT                                       0x00000000
#define CSR_PROC_SAB31_ADDR                                          0x00000200
#define CSR_PROC_SAB31_DEFAULT                                       0x00000000
#define CSR_QM_STATS_CFG_ADDR                                        0x00000204
#define CSR_QM_STATS_CFG_DEFAULT                                     0x00000000
#define CSR_ENQ_STATISTICS_ADDR                                      0x00000208
#define CSR_ENQ_STATISTICS_DEFAULT                                   0x00000000
#define CSR_DEQ_STATISTICS_ADDR                                      0x0000020c
#define CSR_DEQ_STATISTICS_DEFAULT                                   0x00000000
#define CSR_FIFO_STATUS_ADDR                                         0x00000210
#define CSR_FIFO_STATUS_DEFAULT                                      0x00000000
#define CSR_ACR_FIFO_CTRL_ADDR                                       0x00000214
#define CSR_ACR_FIFO_CTRL_DEFAULT                                    0xc0e08020
#define CSR_ERRQ_ADDR                                                0x00000218
#define CSR_ERRQ_DEFAULT                                             0x00000000
#define CSR_QM_RAM_MARGIN_ADDR                                       0x0000021c
#define CSR_QM_RAM_MARGIN_DEFAULT                                    0x00000000
#define CSR_QM_TESTINT0_ADDR                                         0x00000220
#define CSR_QM_TESTINT0_DEFAULT                                      0x00000000
#define CSR_QM_TESTINT1_ADDR                                         0x00000224
#define CSR_QM_TESTINT1_DEFAULT                                      0x00000000
#define CSR_QMLITE_PBN_MAP_0_ADDR                                    0x00000228
#define CSR_QMLITE_PBN_MAP_0_DEFAULT                                 0x00000000
#define CSR_QMLITE_PBN_MAP_1_ADDR                                    0x0000022c
#define CSR_QMLITE_PBN_MAP_1_DEFAULT                                 0x00000000
#define CSR_RECOMB_CTRL_0_ADDR                                       0x00000230
#define CSR_RECOMB_CTRL_0_DEFAULT                                    0x00000104
#define CSR_RECOMB_CTRL_1_ADDR                                       0x00000234
#define CSR_RECOMB_CTRL_1_DEFAULT                                    0x02080208
#define CSR_RECOMB_CTRL_2_ADDR                                       0x00000238
#define CSR_RECOMB_CTRL_2_DEFAULT                                    0x80202020
#define CSR_QM_RECOMB_RAM_MARGIN_ADDR                                0x00000240
#define CSR_QM_RECOMB_RAM_MARGIN_DEFAULT                             0x00000000
#define CSR_RECOMB_STS_0_ADDR                                        0x00000244
#define CSR_RECOMB_STS_0_DEFAULT                                     0x000001ff
#define CSR_RECOMB_STS_1_ADDR                                        0x00000248
#define CSR_RECOMB_STS_1_DEFAULT                                     0xffffffff
#define CSR_RECOMB_STS_2_ADDR                                        0x0000024c
#define CSR_RECOMB_STS_2_DEFAULT                                     0xffffffff
#define RECOMB_INTERRUPT_ADDR                                        0x00000250
#define RECOMB_INTERRUPT_DEFAULT                                     0x00000000
#define RECOMB_INTERRUPTMASK_ADDR                                    0x00000254
#define CSR_DEQ_CTRL_0_ADDR                                          0x00000258
#define CSR_DEQ_CTRL_0_DEFAULT                                       0x00000007
#define CSR_MPIC_CTRL_0_ADDR                                         0x0000025c
#define CSR_MPIC_CTRL_0_DEFAULT                                      0x00000001
#define CSR_MISC_CTRL_0_ADDR                                         0x00000260
#define CSR_MISC_CTRL_0_DEFAULT                                      0x00000000
#define PBM_DIAGDATA_CTRL_0_ADDR                                     0x00000264
#define PBM_DIAGDATA_CTRL_0_DEFAULT                                  0x00000000

/*	Register csr_ipbrr	*/ 
/*	 Fields revno	 */
#define QM_REVNO_WIDTH                                                   2
#define QM_REVNO_SHIFT                                                  14
#define QM_REVNO_MASK                                           0x0000c000
#define QM_REVNO_RD(src)                        (((src) & 0x0000c000)>>14)
#define QM_REVNO_SET(dst,src) \
                      (((dst) & ~0x0000c000) | (((u32)(src)<<14) & 0x0000c000))
/*	 Fields busid	 */
#define QM_BUSID_WIDTH                                                   2
#define QM_BUSID_SHIFT                                                  12
#define QM_BUSID_MASK                                           0x00003000
#define QM_BUSID_RD(src)                        (((src) & 0x00003000)>>12)
#define QM_BUSID_SET(dst,src) \
                      (((dst) & ~0x00003000) | (((u32)(src)<<12) & 0x00003000))
/*	 Fields deviceid	 */
#define QM_DEVICEID_WIDTH                                               12
#define QM_DEVICEID_SHIFT                                                0
#define QM_DEVICEID_MASK                                        0x00000fff
#define QM_DEVICEID_RD(src)                         (((src) & 0x00000fff))
#define QM_DEVICEID_SET(dst,src) \
                          (((dst) & ~0x00000fff) | (((u32)(src)) & 0x00000fff))

/*	Register csr_qm_config	*/ 
/*	 Fields enable	 */
#define QM_ENABLE_WIDTH                                                  1
#define QM_ENABLE_SHIFT                                                 31
#define QM_ENABLE_MASK                                          0x80000000
#define QM_ENABLE_RD(src)                       (((src) & 0x80000000)>>31)
#define QM_ENABLE_WR(src)                  (((u32)(src)<<31) & 0x80000000)
#define QM_ENABLE_SET(dst,src) \
                      (((dst) & ~0x80000000) | (((u32)(src)<<31) & 0x80000000))
/*	 Fields erq_ovr_protect	 */
#define ERQ_OVR_PROTECT_WIDTH                                                 1
#define ERQ_OVR_PROTECT_SHIFT                                                30
#define ERQ_OVR_PROTECT_MASK                                         0x40000000
#define ERQ_OVR_PROTECT_RD(src)                      (((src) & 0x40000000)>>30)
#define ERQ_OVR_PROTECT_WR(src)                 (((u32)(src)<<30) & 0x40000000)
#define ERQ_OVR_PROTECT_SET(dst,src) \
                      (((dst) & ~0x40000000) | (((u32)(src)<<30) & 0x40000000))
/*	 Fields mbox_enq_status_toggle_mode	 */
#define QM_MBOX_ENQ_STATUS_TOGGLE_MODE_WIDTH                             1
#define QM_MBOX_ENQ_STATUS_TOGGLE_MODE_SHIFT                            29
#define QM_MBOX_ENQ_STATUS_TOGGLE_MODE_MASK                     0x20000000
#define QM_MBOX_ENQ_STATUS_TOGGLE_MODE_RD(src)  (((src) & 0x20000000)>>29)
#define QM_MBOX_ENQ_STATUS_TOGGLE_MODE_WR(src) \
                                                (((u32)(src)<<29) & 0x20000000)
#define QM_MBOX_ENQ_STATUS_TOGGLE_MODE_SET(dst,src) \
                      (((dst) & ~0x20000000) | (((u32)(src)<<29) & 0x20000000))

/*	Register csr_pbm	*/ 
/*	 Fields overwrite	 */
#define OVERWRITE_WIDTH                                                       1
#define OVERWRITE_SHIFT                                                      31
#define OVERWRITE_MASK                                               0x80000000
#define OVERWRITE_RD(src)                            (((src) & 0x80000000)>>31)
#define OVERWRITE_WR(src)                       (((u32)(src)<<31) & 0x80000000)
#define OVERWRITE_SET(dst,src) \
                      (((dst) & ~0x80000000) | (((u32)(src)<<31) & 0x80000000))
/*	 Fields slvid_pbn	 */
#define SLVID_PBN_WIDTH                                                      10
#define SLVID_PBN_SHIFT                                                       0
#define SLVID_PBN_MASK                                               0x000003ff
#define SLVID_PBN_RD(src)                                (((src) & 0x000003ff))
#define SLVID_PBN_WR(src)                           (((u32)(src)) & 0x000003ff)
#define SLVID_PBN_SET(dst,src) \
                          (((dst) & ~0x000003ff) | (((u32)(src)) & 0x000003ff))

/*	Register csr_pbm_buf_wr	*/ 
/*	 Fields pb_size	 */
#define PB_SIZE_WIDTH                                                         1
#define PB_SIZE_SHIFT                                                        31
#define PB_SIZE_MASK                                                 0x80000000
#define PB_SIZE_RD(src)                              (((src) & 0x80000000)>>31)
#define PB_SIZE_WR(src)                         (((u32)(src)<<31) & 0x80000000)
#define PB_SIZE_SET(dst,src) \
                      (((dst) & ~0x80000000) | (((u32)(src)<<31) & 0x80000000))
/*	 Fields in_service_clr	 */
#define IN_SERVICE_CLR_WIDTH                                                  1
#define IN_SERVICE_CLR_SHIFT                                                 30
#define IN_SERVICE_CLR_MASK                                          0x40000000
#define IN_SERVICE_CLR_RD(src)                       (((src) & 0x40000000)>>30)
#define IN_SERVICE_CLR_WR(src)                  (((u32)(src)<<30) & 0x40000000)
#define IN_SERVICE_CLR_SET(dst,src) \
                      (((dst) & ~0x40000000) | (((u32)(src)<<30) & 0x40000000))
/*	 Fields data	 */
#define DATA_WIDTH                                                           30
#define DATA_SHIFT                                                            0
#define DATA_MASK                                                    0x3fffffff
#define DATA_RD(src)                                     (((src) & 0x3fffffff))
#define DATA_WR(src)                                (((u32)(src)) & 0x3fffffff)
#define DATA_SET(dst,src) \
                          (((dst) & ~0x3fffffff) | (((u32)(src)) & 0x3fffffff))

/*	Register csr_pbm_buf_rd	*/ 
/*	 Fields pb_size	 */
#define PB_SIZE_F1_WIDTH                                                      1
#define PB_SIZE_F1_SHIFT                                                     31
#define PB_SIZE_F1_MASK                                              0x80000000
#define PB_SIZE_F1_RD(src)                           (((src) & 0x80000000)>>31)
#define PB_SIZE_F1_SET(dst,src) \
                      (((dst) & ~0x80000000) | (((u32)(src)<<31) & 0x80000000))
/*	 Fields pb_in_service	 */
#define PB_IN_SERVICE_WIDTH                                                   1
#define PB_IN_SERVICE_SHIFT                                                  30
#define PB_IN_SERVICE_MASK                                           0x40000000
#define PB_IN_SERVICE_RD(src)                        (((src) & 0x40000000)>>30)
#define PB_IN_SERVICE_SET(dst,src) \
                      (((dst) & ~0x40000000) | (((u32)(src)<<30) & 0x40000000))
/*	 Fields slot_num	 */
#define SLOT_NUM_WIDTH                                                        8
#define SLOT_NUM_SHIFT                                                       22
#define SLOT_NUM_MASK                                                0x3fc00000
#define SLOT_NUM_RD(src)                             (((src) & 0x3fc00000)>>22)
#define SLOT_NUM_SET(dst,src) \
                      (((dst) & ~0x3fc00000) | (((u32)(src)<<22) & 0x3fc00000))
/*	 Fields prefetch_buf_en	 */
#define PREFETCH_BUF_EN_WIDTH                                                 1
#define PREFETCH_BUF_EN_SHIFT                                                21
#define PREFETCH_BUF_EN_MASK                                         0x00200000
#define PREFETCH_BUF_EN_RD(src)                      (((src) & 0x00200000)>>21)
#define PREFETCH_BUF_EN_SET(dst,src) \
                      (((dst) & ~0x00200000) | (((u32)(src)<<21) & 0x00200000))
/*	 Fields is_free_pool	 */
#define IS_FREE_POOL_WIDTH                                                    1
#define IS_FREE_POOL_SHIFT                                                   20
#define IS_FREE_POOL_MASK                                            0x00100000
#define IS_FREE_POOL_RD(src)                         (((src) & 0x00100000)>>20)
#define IS_FREE_POOL_SET(dst,src) \
                      (((dst) & ~0x00100000) | (((u32)(src)<<20) & 0x00100000))
/*	 Fields tlvq	 */
#define TLVQ_WIDTH                                                            1
#define TLVQ_SHIFT                                                           19
#define TLVQ_MASK                                                    0x00080000
#define TLVQ_RD(src)                                 (((src) & 0x00080000)>>19)
#define TLVQ_SET(dst,src) \
                      (((dst) & ~0x00080000) | (((u32)(src)<<19) & 0x00080000))
/*	 Fields corresponding_qnum	 */
#define CORRESPONDING_QNUM_WIDTH                                             10
#define CORRESPONDING_QNUM_SHIFT                                              9
#define CORRESPONDING_QNUM_MASK                                      0x0007fe00
#define CORRESPONDING_QNUM_RD(src)                    (((src) & 0x0007fe00)>>9)
#define CORRESPONDING_QNUM_SET(dst,src) \
                       (((dst) & ~0x0007fe00) | (((u32)(src)<<9) & 0x0007fe00))
/*	 Fields num_msgs_in_buf	 */
#define NUM_MSGS_IN_BUF_WIDTH                                                 9
#define NUM_MSGS_IN_BUF_SHIFT                                                 0
#define NUM_MSGS_IN_BUF_MASK                                         0x000001ff
#define NUM_MSGS_IN_BUF_RD(src)                          (((src) & 0x000001ff))
#define NUM_MSGS_IN_BUF_SET(dst,src) \
                          (((dst) & ~0x000001ff) | (((u32)(src)) & 0x000001ff))

/*	Register csr_pbm_coal	*/ 
/*	 Fields qne_ctick_sel	 */
#define QNE_CTICK_SEL_WIDTH                                                   3
#define QNE_CTICK_SEL_SHIFT                                                  28
#define QNE_CTICK_SEL_MASK                                           0x70000000
#define QNE_CTICK_SEL_RD(src)                        (((src) & 0x70000000)>>28)
#define QNE_CTICK_SEL_WR(src)                   (((u32)(src)<<28) & 0x70000000)
#define QNE_CTICK_SEL_SET(dst,src) \
                      (((dst) & ~0x70000000) | (((u32)(src)<<28) & 0x70000000))
/*	 Fields observe_ctick_7	 */
#define OBSERVE_CTICK_7_WIDTH                                                 1
#define OBSERVE_CTICK_7_SHIFT                                                27
#define OBSERVE_CTICK_7_MASK                                         0x08000000
#define OBSERVE_CTICK_7_RD(src)                      (((src) & 0x08000000)>>27)
#define OBSERVE_CTICK_7_SET(dst,src) \
                      (((dst) & ~0x08000000) | (((u32)(src)<<27) & 0x08000000))
/*	 Fields count_range	 */
#define COUNT_RANGE_WIDTH                                                    16
#define COUNT_RANGE_SHIFT                                                     0
#define COUNT_RANGE_MASK                                             0x0000ffff
#define COUNT_RANGE_RD(src)                              (((src) & 0x0000ffff))
#define COUNT_RANGE_WR(src)                         (((u32)(src)) & 0x0000ffff)
#define COUNT_RANGE_SET(dst,src) \
                          (((dst) & ~0x0000ffff) | (((u32)(src)) & 0x0000ffff))

/*	Register csr_pbm_ctick0	*/ 
/*	 Fields mbox0	 */
#define MBOX00_WIDTH                                                          3
#define MBOX00_SHIFT                                                         28
#define MBOX00_MASK                                                  0x70000000
#define MBOX00_RD(src)                               (((src) & 0x70000000)>>28)
#define MBOX00_WR(src)                          (((u32)(src)<<28) & 0x70000000)
#define MBOX00_SET(dst,src) \
                      (((dst) & ~0x70000000) | (((u32)(src)<<28) & 0x70000000))
/*	 Fields mbox1	 */
#define MBOX10_WIDTH                                                          3
#define MBOX10_SHIFT                                                         24
#define MBOX10_MASK                                                  0x07000000
#define MBOX10_RD(src)                               (((src) & 0x07000000)>>24)
#define MBOX10_WR(src)                          (((u32)(src)<<24) & 0x07000000)
#define MBOX10_SET(dst,src) \
                      (((dst) & ~0x07000000) | (((u32)(src)<<24) & 0x07000000))
/*	 Fields mbox2	 */
#define MBOX20_WIDTH                                                          3
#define MBOX20_SHIFT                                                         20
#define MBOX20_MASK                                                  0x00700000
#define MBOX20_RD(src)                               (((src) & 0x00700000)>>20)
#define MBOX20_WR(src)                          (((u32)(src)<<20) & 0x00700000)
#define MBOX20_SET(dst,src) \
                      (((dst) & ~0x00700000) | (((u32)(src)<<20) & 0x00700000))
/*	 Fields mbox3	 */
#define MBOX30_WIDTH                                                          3
#define MBOX30_SHIFT                                                         16
#define MBOX30_MASK                                                  0x00070000
#define MBOX30_RD(src)                               (((src) & 0x00070000)>>16)
#define MBOX30_WR(src)                          (((u32)(src)<<16) & 0x00070000)
#define MBOX30_SET(dst,src) \
                      (((dst) & ~0x00070000) | (((u32)(src)<<16) & 0x00070000))
/*	 Fields mbox4	 */
#define MBOX40_WIDTH                                                          3
#define MBOX40_SHIFT                                                         12
#define MBOX40_MASK                                                  0x00007000
#define MBOX40_RD(src)                               (((src) & 0x00007000)>>12)
#define MBOX40_WR(src)                          (((u32)(src)<<12) & 0x00007000)
#define MBOX40_SET(dst,src) \
                      (((dst) & ~0x00007000) | (((u32)(src)<<12) & 0x00007000))
/*	 Fields mbox5	 */
#define MBOX50_WIDTH                                                          3
#define MBOX50_SHIFT                                                          8
#define MBOX50_MASK                                                  0x00000700
#define MBOX50_RD(src)                                (((src) & 0x00000700)>>8)
#define MBOX50_WR(src)                           (((u32)(src)<<8) & 0x00000700)
#define MBOX50_SET(dst,src) \
                       (((dst) & ~0x00000700) | (((u32)(src)<<8) & 0x00000700))
/*	 Fields mbox6	 */
#define MBOX60_WIDTH                                                          3
#define MBOX60_SHIFT                                                          4
#define MBOX60_MASK                                                  0x00000070
#define MBOX60_RD(src)                                (((src) & 0x00000070)>>4)
#define MBOX60_WR(src)                           (((u32)(src)<<4) & 0x00000070)
#define MBOX60_SET(dst,src) \
                       (((dst) & ~0x00000070) | (((u32)(src)<<4) & 0x00000070))
/*	 Fields mbox7	 */
#define MBOX70_WIDTH                                                          3
#define MBOX70_SHIFT                                                          0
#define MBOX70_MASK                                                  0x00000007
#define MBOX70_RD(src)                                   (((src) & 0x00000007))
#define MBOX70_WR(src)                              (((u32)(src)) & 0x00000007)
#define MBOX70_SET(dst,src) \
                          (((dst) & ~0x00000007) | (((u32)(src)) & 0x00000007))

/*	Register csr_pbm_ctick1	*/ 
/*	 Fields mbox8	 */
#define MBOX81_WIDTH                                                          3
#define MBOX81_SHIFT                                                         28
#define MBOX81_MASK                                                  0x70000000
#define MBOX81_RD(src)                               (((src) & 0x70000000)>>28)
#define MBOX81_WR(src)                          (((u32)(src)<<28) & 0x70000000)
#define MBOX81_SET(dst,src) \
                      (((dst) & ~0x70000000) | (((u32)(src)<<28) & 0x70000000))
/*	 Fields mbox9	 */
#define MBOX91_WIDTH                                                          3
#define MBOX91_SHIFT                                                         24
#define MBOX91_MASK                                                  0x07000000
#define MBOX91_RD(src)                               (((src) & 0x07000000)>>24)
#define MBOX91_WR(src)                          (((u32)(src)<<24) & 0x07000000)
#define MBOX91_SET(dst,src) \
                      (((dst) & ~0x07000000) | (((u32)(src)<<24) & 0x07000000))
/*	 Fields mbox10	 */
#define MBOX101_WIDTH                                                         3
#define MBOX101_SHIFT                                                        20
#define MBOX101_MASK                                                 0x00700000
#define MBOX101_RD(src)                              (((src) & 0x00700000)>>20)
#define MBOX101_WR(src)                         (((u32)(src)<<20) & 0x00700000)
#define MBOX101_SET(dst,src) \
                      (((dst) & ~0x00700000) | (((u32)(src)<<20) & 0x00700000))
/*	 Fields mbox11	 */
#define MBOX111_WIDTH                                                         3
#define MBOX111_SHIFT                                                        16
#define MBOX111_MASK                                                 0x00070000
#define MBOX111_RD(src)                              (((src) & 0x00070000)>>16)
#define MBOX111_WR(src)                         (((u32)(src)<<16) & 0x00070000)
#define MBOX111_SET(dst,src) \
                      (((dst) & ~0x00070000) | (((u32)(src)<<16) & 0x00070000))
/*	 Fields mbox12	 */
#define MBOX121_WIDTH                                                         3
#define MBOX121_SHIFT                                                        12
#define MBOX121_MASK                                                 0x00007000
#define MBOX121_RD(src)                              (((src) & 0x00007000)>>12)
#define MBOX121_WR(src)                         (((u32)(src)<<12) & 0x00007000)
#define MBOX121_SET(dst,src) \
                      (((dst) & ~0x00007000) | (((u32)(src)<<12) & 0x00007000))
/*	 Fields mbox13	 */
#define MBOX131_WIDTH                                                         3
#define MBOX131_SHIFT                                                         8
#define MBOX131_MASK                                                 0x00000700
#define MBOX131_RD(src)                               (((src) & 0x00000700)>>8)
#define MBOX131_WR(src)                          (((u32)(src)<<8) & 0x00000700)
#define MBOX131_SET(dst,src) \
                       (((dst) & ~0x00000700) | (((u32)(src)<<8) & 0x00000700))
/*	 Fields mbox14	 */
#define MBOX141_WIDTH                                                         3
#define MBOX141_SHIFT                                                         4
#define MBOX141_MASK                                                 0x00000070
#define MBOX141_RD(src)                               (((src) & 0x00000070)>>4)
#define MBOX141_WR(src)                          (((u32)(src)<<4) & 0x00000070)
#define MBOX141_SET(dst,src) \
                       (((dst) & ~0x00000070) | (((u32)(src)<<4) & 0x00000070))
/*	 Fields mbox15	 */
#define MBOX151_WIDTH                                                         3
#define MBOX151_SHIFT                                                         0
#define MBOX151_MASK                                                 0x00000007
#define MBOX151_RD(src)                                  (((src) & 0x00000007))
#define MBOX151_WR(src)                             (((u32)(src)) & 0x00000007)
#define MBOX151_SET(dst,src) \
                          (((dst) & ~0x00000007) | (((u32)(src)) & 0x00000007))

/*	Register csr_pbm_ctick2	*/ 
/*	 Fields mbox16	 */
#define MBOX162_WIDTH                                                         3
#define MBOX162_SHIFT                                                        28
#define MBOX162_MASK                                                 0x70000000
#define MBOX162_RD(src)                              (((src) & 0x70000000)>>28)
#define MBOX162_WR(src)                         (((u32)(src)<<28) & 0x70000000)
#define MBOX162_SET(dst,src) \
                      (((dst) & ~0x70000000) | (((u32)(src)<<28) & 0x70000000))
/*	 Fields mbox17	 */
#define MBOX172_WIDTH                                                         3
#define MBOX172_SHIFT                                                        24
#define MBOX172_MASK                                                 0x07000000
#define MBOX172_RD(src)                              (((src) & 0x07000000)>>24)
#define MBOX172_WR(src)                         (((u32)(src)<<24) & 0x07000000)
#define MBOX172_SET(dst,src) \
                      (((dst) & ~0x07000000) | (((u32)(src)<<24) & 0x07000000))
/*	 Fields mbox18	 */
#define MBOX182_WIDTH                                                         3
#define MBOX182_SHIFT                                                        20
#define MBOX182_MASK                                                 0x00700000
#define MBOX182_RD(src)                              (((src) & 0x00700000)>>20)
#define MBOX182_WR(src)                         (((u32)(src)<<20) & 0x00700000)
#define MBOX182_SET(dst,src) \
                      (((dst) & ~0x00700000) | (((u32)(src)<<20) & 0x00700000))
/*	 Fields mbox19	 */
#define MBOX192_WIDTH                                                         3
#define MBOX192_SHIFT                                                        16
#define MBOX192_MASK                                                 0x00070000
#define MBOX192_RD(src)                              (((src) & 0x00070000)>>16)
#define MBOX192_WR(src)                         (((u32)(src)<<16) & 0x00070000)
#define MBOX192_SET(dst,src) \
                      (((dst) & ~0x00070000) | (((u32)(src)<<16) & 0x00070000))
/*	 Fields mbox20	 */
#define MBOX202_WIDTH                                                         3
#define MBOX202_SHIFT                                                        12
#define MBOX202_MASK                                                 0x00007000
#define MBOX202_RD(src)                              (((src) & 0x00007000)>>12)
#define MBOX202_WR(src)                         (((u32)(src)<<12) & 0x00007000)
#define MBOX202_SET(dst,src) \
                      (((dst) & ~0x00007000) | (((u32)(src)<<12) & 0x00007000))
/*	 Fields mbox21	 */
#define MBOX212_WIDTH                                                         3
#define MBOX212_SHIFT                                                         8
#define MBOX212_MASK                                                 0x00000700
#define MBOX212_RD(src)                               (((src) & 0x00000700)>>8)
#define MBOX212_WR(src)                          (((u32)(src)<<8) & 0x00000700)
#define MBOX212_SET(dst,src) \
                       (((dst) & ~0x00000700) | (((u32)(src)<<8) & 0x00000700))
/*	 Fields mbox22	 */
#define MBOX222_WIDTH                                                         3
#define MBOX222_SHIFT                                                         4
#define MBOX222_MASK                                                 0x00000070
#define MBOX222_RD(src)                               (((src) & 0x00000070)>>4)
#define MBOX222_WR(src)                          (((u32)(src)<<4) & 0x00000070)
#define MBOX222_SET(dst,src) \
                       (((dst) & ~0x00000070) | (((u32)(src)<<4) & 0x00000070))
/*	 Fields mbox23	 */
#define MBOX232_WIDTH                                                         3
#define MBOX232_SHIFT                                                         0
#define MBOX232_MASK                                                 0x00000007
#define MBOX232_RD(src)                                  (((src) & 0x00000007))
#define MBOX232_WR(src)                             (((u32)(src)) & 0x00000007)
#define MBOX232_SET(dst,src) \
                          (((dst) & ~0x00000007) | (((u32)(src)) & 0x00000007))

/*	Register csr_pbm_ctick3	*/ 
/*	 Fields mbox24	 */
#define MBOX243_WIDTH                                                         3
#define MBOX243_SHIFT                                                        28
#define MBOX243_MASK                                                 0x70000000
#define MBOX243_RD(src)                              (((src) & 0x70000000)>>28)
#define MBOX243_WR(src)                         (((u32)(src)<<28) & 0x70000000)
#define MBOX243_SET(dst,src) \
                      (((dst) & ~0x70000000) | (((u32)(src)<<28) & 0x70000000))
/*	 Fields mbox25	 */
#define MBOX253_WIDTH                                                         3
#define MBOX253_SHIFT                                                        24
#define MBOX253_MASK                                                 0x07000000
#define MBOX253_RD(src)                              (((src) & 0x07000000)>>24)
#define MBOX253_WR(src)                         (((u32)(src)<<24) & 0x07000000)
#define MBOX253_SET(dst,src) \
                      (((dst) & ~0x07000000) | (((u32)(src)<<24) & 0x07000000))
/*	 Fields mbox26	 */
#define MBOX263_WIDTH                                                         3
#define MBOX263_SHIFT                                                        20
#define MBOX263_MASK                                                 0x00700000
#define MBOX263_RD(src)                              (((src) & 0x00700000)>>20)
#define MBOX263_WR(src)                         (((u32)(src)<<20) & 0x00700000)
#define MBOX263_SET(dst,src) \
                      (((dst) & ~0x00700000) | (((u32)(src)<<20) & 0x00700000))
/*	 Fields mbox27	 */
#define MBOX273_WIDTH                                                         3
#define MBOX273_SHIFT                                                        16
#define MBOX273_MASK                                                 0x00070000
#define MBOX273_RD(src)                              (((src) & 0x00070000)>>16)
#define MBOX273_WR(src)                         (((u32)(src)<<16) & 0x00070000)
#define MBOX273_SET(dst,src) \
                      (((dst) & ~0x00070000) | (((u32)(src)<<16) & 0x00070000))
/*	 Fields mbox28	 */
#define MBOX283_WIDTH                                                         3
#define MBOX283_SHIFT                                                        12
#define MBOX283_MASK                                                 0x00007000
#define MBOX283_RD(src)                              (((src) & 0x00007000)>>12)
#define MBOX283_WR(src)                         (((u32)(src)<<12) & 0x00007000)
#define MBOX283_SET(dst,src) \
                      (((dst) & ~0x00007000) | (((u32)(src)<<12) & 0x00007000))
/*	 Fields mbox29	 */
#define MBOX293_WIDTH                                                         3
#define MBOX293_SHIFT                                                         8
#define MBOX293_MASK                                                 0x00000700
#define MBOX293_RD(src)                               (((src) & 0x00000700)>>8)
#define MBOX293_WR(src)                          (((u32)(src)<<8) & 0x00000700)
#define MBOX293_SET(dst,src) \
                       (((dst) & ~0x00000700) | (((u32)(src)<<8) & 0x00000700))
/*	 Fields mbox30	 */
#define MBOX303_WIDTH                                                         3
#define MBOX303_SHIFT                                                         4
#define MBOX303_MASK                                                 0x00000070
#define MBOX303_RD(src)                               (((src) & 0x00000070)>>4)
#define MBOX303_WR(src)                          (((u32)(src)<<4) & 0x00000070)
#define MBOX303_SET(dst,src) \
                       (((dst) & ~0x00000070) | (((u32)(src)<<4) & 0x00000070))
/*	 Fields mbox31	 */
#define MBOX313_WIDTH                                                         3
#define MBOX313_SHIFT                                                         0
#define MBOX313_MASK                                                 0x00000007
#define MBOX313_RD(src)                                  (((src) & 0x00000007))
#define MBOX313_WR(src)                             (((u32)(src)) & 0x00000007)
#define MBOX313_SET(dst,src) \
                          (((dst) & ~0x00000007) | (((u32)(src)) & 0x00000007))

/*	Register csr_threshold0_set0	*/ 
/*	 Fields thr0	 */
#define THR00_WIDTH                                                          18
#define THR00_SHIFT                                                           0
#define THR00_MASK                                                   0x0003ffff
#define THR00_RD(src)                                    (((src) & 0x0003ffff))
#define THR00_WR(src)                               (((u32)(src)) & 0x0003ffff)
#define THR00_SET(dst,src) \
                          (((dst) & ~0x0003ffff) | (((u32)(src)) & 0x0003ffff))

/*	Register csr_threshold1_set0	*/ 
/*	 Fields thr1	 */
#define THR10_WIDTH                                                          18
#define THR10_SHIFT                                                           0
#define THR10_MASK                                                   0x0003ffff
#define THR10_RD(src)                                    (((src) & 0x0003ffff))
#define THR10_WR(src)                               (((u32)(src)) & 0x0003ffff)
#define THR10_SET(dst,src) \
                          (((dst) & ~0x0003ffff) | (((u32)(src)) & 0x0003ffff))

/*	Register csr_threshold0_set1	*/ 
/*	 Fields thr0	 */
#define THR01_WIDTH                                                          18
#define THR01_SHIFT                                                           0
#define THR01_MASK                                                   0x0003ffff
#define THR01_RD(src)                                    (((src) & 0x0003ffff))
#define THR01_WR(src)                               (((u32)(src)) & 0x0003ffff)
#define THR01_SET(dst,src) \
                          (((dst) & ~0x0003ffff) | (((u32)(src)) & 0x0003ffff))

/*	Register csr_threshold1_set1	*/ 
/*	 Fields thr1	 */
#define THR11_WIDTH                                                          18
#define THR11_SHIFT                                                           0
#define THR11_MASK                                                   0x0003ffff
#define THR11_RD(src)                                    (((src) & 0x0003ffff))
#define THR11_WR(src)                               (((u32)(src)) & 0x0003ffff)
#define THR11_SET(dst,src) \
                          (((dst) & ~0x0003ffff) | (((u32)(src)) & 0x0003ffff))

/*	Register csr_threshold0_set2	*/ 
/*	 Fields thr0	 */
#define THR02_WIDTH                                                          18
#define THR02_SHIFT                                                           0
#define THR02_MASK                                                   0x0003ffff
#define THR02_RD(src)                                    (((src) & 0x0003ffff))
#define THR02_WR(src)                               (((u32)(src)) & 0x0003ffff)
#define THR02_SET(dst,src) \
                          (((dst) & ~0x0003ffff) | (((u32)(src)) & 0x0003ffff))

/*	Register csr_threshold1_set2	*/ 
/*	 Fields thr1	 */
#define THR12_WIDTH                                                          18
#define THR12_SHIFT                                                           0
#define THR12_MASK                                                   0x0003ffff
#define THR12_RD(src)                                    (((src) & 0x0003ffff))
#define THR12_WR(src)                               (((u32)(src)) & 0x0003ffff)
#define THR12_SET(dst,src) \
                          (((dst) & ~0x0003ffff) | (((u32)(src)) & 0x0003ffff))

/*	Register csr_threshold0_set3	*/ 
/*	 Fields thr0	 */
#define THR03_WIDTH                                                          18
#define THR03_SHIFT                                                           0
#define THR03_MASK                                                   0x0003ffff
#define THR03_RD(src)                                    (((src) & 0x0003ffff))
#define THR03_WR(src)                               (((u32)(src)) & 0x0003ffff)
#define THR03_SET(dst,src) \
                          (((dst) & ~0x0003ffff) | (((u32)(src)) & 0x0003ffff))

/*	Register csr_threshold1_set3	*/ 
/*	 Fields thr1	 */
#define THR13_WIDTH                                                          18
#define THR13_SHIFT                                                           0
#define THR13_MASK                                                   0x0003ffff
#define THR13_RD(src)                                    (((src) & 0x0003ffff))
#define THR13_WR(src)                               (((u32)(src)) & 0x0003ffff)
#define THR13_SET(dst,src) \
                          (((dst) & ~0x0003ffff) | (((u32)(src)) & 0x0003ffff))

/*	Register csr_threshold0_set4	*/ 
/*	 Fields thr0	 */
#define THR04_WIDTH                                                          18
#define THR04_SHIFT                                                           0
#define THR04_MASK                                                   0x0003ffff
#define THR04_RD(src)                                    (((src) & 0x0003ffff))
#define THR04_WR(src)                               (((u32)(src)) & 0x0003ffff)
#define THR04_SET(dst,src) \
                          (((dst) & ~0x0003ffff) | (((u32)(src)) & 0x0003ffff))

/*	Register csr_threshold1_set4	*/ 
/*	 Fields thr1	 */
#define THR14_WIDTH                                                          18
#define THR14_SHIFT                                                           0
#define THR14_MASK                                                   0x0003ffff
#define THR14_RD(src)                                    (((src) & 0x0003ffff))
#define THR14_WR(src)                               (((u32)(src)) & 0x0003ffff)
#define THR14_SET(dst,src) \
                          (((dst) & ~0x0003ffff) | (((u32)(src)) & 0x0003ffff))

/*	Register csr_threshold0_set5	*/ 
/*	 Fields thr0	 */
#define THR05_WIDTH                                                          18
#define THR05_SHIFT                                                           0
#define THR05_MASK                                                   0x0003ffff
#define THR05_RD(src)                                    (((src) & 0x0003ffff))
#define THR05_WR(src)                               (((u32)(src)) & 0x0003ffff)
#define THR05_SET(dst,src) \
                          (((dst) & ~0x0003ffff) | (((u32)(src)) & 0x0003ffff))

/*	Register csr_threshold1_set5	*/ 
/*	 Fields thr1	 */
#define THR15_WIDTH                                                          18
#define THR15_SHIFT                                                           0
#define THR15_MASK                                                   0x0003ffff
#define THR15_RD(src)                                    (((src) & 0x0003ffff))
#define THR15_WR(src)                               (((u32)(src)) & 0x0003ffff)
#define THR15_SET(dst,src) \
                          (((dst) & ~0x0003ffff) | (((u32)(src)) & 0x0003ffff))

/*	Register csr_threshold0_set6	*/ 
/*	 Fields thr0	 */
#define THR06_WIDTH                                                          18
#define THR06_SHIFT                                                           0
#define THR06_MASK                                                   0x0003ffff
#define THR06_RD(src)                                    (((src) & 0x0003ffff))
#define THR06_WR(src)                               (((u32)(src)) & 0x0003ffff)
#define THR06_SET(dst,src) \
                          (((dst) & ~0x0003ffff) | (((u32)(src)) & 0x0003ffff))

/*	Register csr_threshold1_set6	*/ 
/*	 Fields thr1	 */
#define THR16_WIDTH                                                          18
#define THR16_SHIFT                                                           0
#define THR16_MASK                                                   0x0003ffff
#define THR16_RD(src)                                    (((src) & 0x0003ffff))
#define THR16_WR(src)                               (((u32)(src)) & 0x0003ffff)
#define THR16_SET(dst,src) \
                          (((dst) & ~0x0003ffff) | (((u32)(src)) & 0x0003ffff))

/*	Register csr_threshold0_set7	*/ 
/*	 Fields thr0	 */
#define THR07_WIDTH                                                          18
#define THR07_SHIFT                                                           0
#define THR07_MASK                                                   0x0003ffff
#define THR07_RD(src)                                    (((src) & 0x0003ffff))
#define THR07_WR(src)                               (((u32)(src)) & 0x0003ffff)
#define THR07_SET(dst,src) \
                          (((dst) & ~0x0003ffff) | (((u32)(src)) & 0x0003ffff))

/*	Register csr_threshold1_set7	*/ 
/*	 Fields thr1	 */
#define THR17_WIDTH                                                          18
#define THR17_SHIFT                                                           0
#define THR17_MASK                                                   0x0003ffff
#define THR17_RD(src)                                    (((src) & 0x0003ffff))
#define THR17_WR(src)                               (((u32)(src)) & 0x0003ffff)
#define THR17_SET(dst,src) \
                          (((dst) & ~0x0003ffff) | (((u32)(src)) & 0x0003ffff))

/*	Register csr_hysteresis	*/ 
/*	 Fields set0_hyst	 */
#define SET0_HYST_WIDTH                                                       4
#define SET0_HYST_SHIFT                                                      28
#define SET0_HYST_MASK                                               0xf0000000
#define SET0_HYST_RD(src)                            (((src) & 0xf0000000)>>28)
#define SET0_HYST_WR(src)                       (((u32)(src)<<28) & 0xf0000000)
#define SET0_HYST_SET(dst,src) \
                      (((dst) & ~0xf0000000) | (((u32)(src)<<28) & 0xf0000000))
/*	 Fields set1_hyst	 */
#define SET1_HYST_WIDTH                                                       4
#define SET1_HYST_SHIFT                                                      24
#define SET1_HYST_MASK                                               0x0f000000
#define SET1_HYST_RD(src)                            (((src) & 0x0f000000)>>24)
#define SET1_HYST_WR(src)                       (((u32)(src)<<24) & 0x0f000000)
#define SET1_HYST_SET(dst,src) \
                      (((dst) & ~0x0f000000) | (((u32)(src)<<24) & 0x0f000000))
/*	 Fields set2_hyst	 */
#define SET2_HYST_WIDTH                                                       4
#define SET2_HYST_SHIFT                                                      20
#define SET2_HYST_MASK                                               0x00f00000
#define SET2_HYST_RD(src)                            (((src) & 0x00f00000)>>20)
#define SET2_HYST_WR(src)                       (((u32)(src)<<20) & 0x00f00000)
#define SET2_HYST_SET(dst,src) \
                      (((dst) & ~0x00f00000) | (((u32)(src)<<20) & 0x00f00000))
/*	 Fields set3_hyst	 */
#define SET3_HYST_WIDTH                                                       4
#define SET3_HYST_SHIFT                                                      16
#define SET3_HYST_MASK                                               0x000f0000
#define SET3_HYST_RD(src)                            (((src) & 0x000f0000)>>16)
#define SET3_HYST_WR(src)                       (((u32)(src)<<16) & 0x000f0000)
#define SET3_HYST_SET(dst,src) \
                      (((dst) & ~0x000f0000) | (((u32)(src)<<16) & 0x000f0000))
/*	 Fields set4_hyst	 */
#define SET4_HYST_WIDTH                                                       4
#define SET4_HYST_SHIFT                                                      12
#define SET4_HYST_MASK                                               0x0000f000
#define SET4_HYST_RD(src)                            (((src) & 0x0000f000)>>12)
#define SET4_HYST_WR(src)                       (((u32)(src)<<12) & 0x0000f000)
#define SET4_HYST_SET(dst,src) \
                      (((dst) & ~0x0000f000) | (((u32)(src)<<12) & 0x0000f000))
/*	 Fields set5_hyst	 */
#define SET5_HYST_WIDTH                                                       4
#define SET5_HYST_SHIFT                                                       8
#define SET5_HYST_MASK                                               0x00000f00
#define SET5_HYST_RD(src)                             (((src) & 0x00000f00)>>8)
#define SET5_HYST_WR(src)                        (((u32)(src)<<8) & 0x00000f00)
#define SET5_HYST_SET(dst,src) \
                       (((dst) & ~0x00000f00) | (((u32)(src)<<8) & 0x00000f00))
/*	 Fields set6_hyst	 */
#define SET6_HYST_WIDTH                                                       4
#define SET6_HYST_SHIFT                                                       4
#define SET6_HYST_MASK                                               0x000000f0
#define SET6_HYST_RD(src)                             (((src) & 0x000000f0)>>4)
#define SET6_HYST_WR(src)                        (((u32)(src)<<4) & 0x000000f0)
#define SET6_HYST_SET(dst,src) \
                       (((dst) & ~0x000000f0) | (((u32)(src)<<4) & 0x000000f0))
/*	 Fields set7_hyst	 */
#define SET7_HYST_WIDTH                                                       4
#define SET7_HYST_SHIFT                                                       0
#define SET7_HYST_MASK                                               0x0000000f
#define SET7_HYST_RD(src)                                (((src) & 0x0000000f))
#define SET7_HYST_WR(src)                           (((u32)(src)) & 0x0000000f)
#define SET7_HYST_SET(dst,src) \
                          (((dst) & ~0x0000000f) | (((u32)(src)) & 0x0000000f))

/*	Register csr_qstate	*/ 
/*	 Fields qnumber	 */
#define QNUMBER_WIDTH                                                        10
#define QNUMBER_SHIFT                                                         0
#define QNUMBER_MASK                                                 0x000003ff
#define QNUMBER_RD(src)                                  (((src) & 0x000003ff))
#define QNUMBER_WR(src)                             (((u32)(src)) & 0x000003ff)
#define QNUMBER_SET(dst,src) \
                          (((dst) & ~0x000003ff) | (((u32)(src)) & 0x000003ff))

/*	Register csr_qstate_wr_0	*/ 
/*	 Fields data	 */
#define DATA0_WIDTH                                                          32
#define DATA0_SHIFT                                                           0
#define DATA0_MASK                                                   0xffffffff
#define DATA0_RD(src)                                    (((src) & 0xffffffff))
#define DATA0_WR(src)                               (((u32)(src)) & 0xffffffff)
#define DATA0_SET(dst,src) \
                          (((dst) & ~0xffffffff) | (((u32)(src)) & 0xffffffff))

/*	Register csr_qstate_wr_1	*/ 
/*	 Fields data	 */
#define DATA1_WIDTH                                                          32
#define DATA1_SHIFT                                                           0
#define DATA1_MASK                                                   0xffffffff
#define DATA1_RD(src)                                    (((src) & 0xffffffff))
#define DATA1_WR(src)                               (((u32)(src)) & 0xffffffff)
#define DATA1_SET(dst,src) \
                          (((dst) & ~0xffffffff) | (((u32)(src)) & 0xffffffff))

/*	Register csr_qstate_wr_2	*/ 
/*	 Fields data	 */
#define DATA2_WIDTH                                                          32
#define DATA2_SHIFT                                                           0
#define DATA2_MASK                                                   0xffffffff
#define DATA2_RD(src)                                    (((src) & 0xffffffff))
#define DATA2_WR(src)                               (((u32)(src)) & 0xffffffff)
#define DATA2_SET(dst,src) \
                          (((dst) & ~0xffffffff) | (((u32)(src)) & 0xffffffff))

/*	Register csr_qstate_wr_3	*/ 
/*	 Fields data	 */
#define DATA3_WIDTH                                                          32
#define DATA3_SHIFT                                                           0
#define DATA3_MASK                                                   0xffffffff
#define DATA3_RD(src)                                    (((src) & 0xffffffff))
#define DATA3_WR(src)                               (((u32)(src)) & 0xffffffff)
#define DATA3_SET(dst,src) \
                          (((dst) & ~0xffffffff) | (((u32)(src)) & 0xffffffff))

/*	Register csr_qstate_wr_4	*/ 
/*	 Fields data	 */
#define QM_DATA4_WIDTH                                                       21
#define QM_DATA4_SHIFT                                                        0
#define QM_DATA4_MASK                                                0x001fffff
#define QM_DATA4_RD(src)                                 (((src) & 0x001fffff))
#define QM_DATA4_WR(src)                            (((u32)(src)) & 0x001fffff)
#define QM_DATA4_SET(dst,src) \
                          (((dst) & ~0x001fffff) | (((u32)(src)) & 0x001fffff))

/*	Register csr_qstate_rd_0	*/ 
/*	 Fields data	 */
#define DATA0_F1_WIDTH                                                       32
#define DATA0_F1_SHIFT                                                        0
#define DATA0_F1_MASK                                                0xffffffff
#define DATA0_F1_RD(src)                                 (((src) & 0xffffffff))
#define DATA0_F1_SET(dst,src) \
                          (((dst) & ~0xffffffff) | (((u32)(src)) & 0xffffffff))

/*	Register csr_qstate_rd_1	*/ 
/*	 Fields data	 */
#define DATA1_F1_WIDTH                                                       32
#define DATA1_F1_SHIFT                                                        0
#define DATA1_F1_MASK                                                0xffffffff
#define DATA1_F1_RD(src)                                 (((src) & 0xffffffff))
#define DATA1_F1_SET(dst,src) \
                          (((dst) & ~0xffffffff) | (((u32)(src)) & 0xffffffff))

/*	Register csr_qstate_rd_2	*/ 
/*	 Fields data	 */
#define DATA2_F1_WIDTH                                                       32
#define DATA2_F1_SHIFT                                                        0
#define DATA2_F1_MASK                                                0xffffffff
#define DATA2_F1_RD(src)                                 (((src) & 0xffffffff))
#define DATA2_F1_SET(dst,src) \
                          (((dst) & ~0xffffffff) | (((u32)(src)) & 0xffffffff))

/*	Register csr_qstate_rd_3	*/ 
/*	 Fields data	 */
#define DATA3_F1_WIDTH                                                       32
#define DATA3_F1_SHIFT                                                        0
#define DATA3_F1_MASK                                                0xffffffff
#define DATA3_F1_RD(src)                                 (((src) & 0xffffffff))
#define DATA3_F1_SET(dst,src) \
                          (((dst) & ~0xffffffff) | (((u32)(src)) & 0xffffffff))

/*	Register csr_qstate_rd_4	*/ 
/*	 Fields data	 */
#define QM_DATA4_F1_WIDTH                                                    21
#define QM_DATA4_F1_SHIFT                                                     0
#define QM_DATA4_F1_MASK                                             0x001fffff
#define QM_DATA4_F1_RD(src)                              (((src) & 0x001fffff))
#define QM_DATA4_F1_SET(dst,src) \
                          (((dst) & ~0x001fffff) | (((u32)(src)) & 0x001fffff))

/*	Register csr_cstate_wr_0	*/ 
/*	 Fields data	 */
#define DATA0_F2_WIDTH                                                       32
#define DATA0_F2_SHIFT                                                        0
#define DATA0_F2_MASK                                                0xffffffff
#define DATA0_F2_RD(src)                                 (((src) & 0xffffffff))
#define DATA0_F2_WR(src)                            (((u32)(src)) & 0xffffffff)
#define DATA0_F2_SET(dst,src) \
                          (((dst) & ~0xffffffff) | (((u32)(src)) & 0xffffffff))

/*	Register csr_cstate_wr_1	*/ 
/*	 Fields data	 */
#define DATA1_F2_WIDTH                                                       15
#define DATA1_F2_SHIFT                                                        0
#define DATA1_F2_MASK                                                0x00007fff
#define DATA1_F2_RD(src)                                 (((src) & 0x00007fff))
#define DATA1_F2_WR(src)                            (((u32)(src)) & 0x00007fff)
#define DATA1_F2_SET(dst,src) \
                          (((dst) & ~0x00007fff) | (((u32)(src)) & 0x00007fff))

/*	Register csr_cstate_rd_0	*/ 
/*	 Fields data	 */
#define DATA0_F3_WIDTH                                                       32
#define DATA0_F3_SHIFT                                                        0
#define DATA0_F3_MASK                                                0xffffffff
#define DATA0_F3_RD(src)                                 (((src) & 0xffffffff))
#define DATA0_F3_SET(dst,src) \
                          (((dst) & ~0xffffffff) | (((u32)(src)) & 0xffffffff))

/*	Register csr_cstate_rd_1	*/ 
/*	 Fields data	 */
#define DATA1_F3_WIDTH                                                       15
#define DATA1_F3_SHIFT                                                        0
#define DATA1_F3_MASK                                                0x00007fff
#define DATA1_F3_RD(src)                                 (((src) & 0x00007fff))
#define DATA1_F3_SET(dst,src) \
                          (((dst) & ~0x00007fff) | (((u32)(src)) & 0x00007fff))

/*	Register csr_cu_timer	*/ 
/*	 Fields init	 */
#define INIT_WIDTH                                                           20
#define INIT_SHIFT                                                            0
#define INIT_MASK                                                    0x000fffff
#define INIT_RD(src)                                     (((src) & 0x000fffff))
#define INIT_WR(src)                                (((u32)(src)) & 0x000fffff)
#define INIT_SET(dst,src) \
                          (((dst) & ~0x000fffff) | (((u32)(src)) & 0x000fffff))

/*	Register csr_proc_mbox_base_0	*/ 
/*	 Fields coherent	 */
#define COHERENT0_WIDTH                                                       1
#define COHERENT0_SHIFT                                                      31
#define COHERENT0_MASK                                               0x80000000
#define COHERENT0_RD(src)                            (((src) & 0x80000000)>>31)
#define COHERENT0_WR(src)                       (((u32)(src)<<31) & 0x80000000)
#define COHERENT0_SET(dst,src) \
                      (((dst) & ~0x80000000) | (((u32)(src)<<31) & 0x80000000))
/*	 Fields vc	 */
#define VC0_WIDTH                                                             2
#define VC0_SHIFT                                                            29
#define VC0_MASK                                                     0x60000000
#define VC0_RD(src)                                  (((src) & 0x60000000)>>29)
#define VC0_WR(src)                             (((u32)(src)<<29) & 0x60000000)
#define VC0_SET(dst,src) \
                      (((dst) & ~0x60000000) | (((u32)(src)<<29) & 0x60000000))
/*	 Fields stashing	 */
#define STASHING0_WIDTH                                                       1
#define STASHING0_SHIFT                                                      28
#define STASHING0_MASK                                               0x10000000
#define STASHING0_RD(src)                            (((src) & 0x10000000)>>28)
#define STASHING0_WR(src)                       (((u32)(src)<<28) & 0x10000000)
#define STASHING0_SET(dst,src) \
                      (((dst) & ~0x10000000) | (((u32)(src)<<28) & 0x10000000))
/*	 Fields addr	 */
#define QM_ADDR0_WIDTH                                                  26
#define QM_ADDR0_SHIFT                                                   0
#define QM_ADDR0_MASK                                           0x03ffffff
#define QM_ADDR0_RD(src)                            (((src) & 0x03ffffff))
#define QM_ADDR0_WR(src)                       (((u32)(src)) & 0x03ffffff)
#define QM_ADDR0_SET(dst,src) \
                          (((dst) & ~0x03ffffff) | (((u32)(src)) & 0x03ffffff))

/*	Register csr_proc_mbox_base_1	*/ 
/*	 Fields coherent	 */
#define COHERENT1_WIDTH                                                       1
#define COHERENT1_SHIFT                                                      31
#define COHERENT1_MASK                                               0x80000000
#define COHERENT1_RD(src)                            (((src) & 0x80000000)>>31)
#define COHERENT1_WR(src)                       (((u32)(src)<<31) & 0x80000000)
#define COHERENT1_SET(dst,src) \
                      (((dst) & ~0x80000000) | (((u32)(src)<<31) & 0x80000000))
/*	 Fields vc	 */
#define VC1_WIDTH                                                             2
#define VC1_SHIFT                                                            29
#define VC1_MASK                                                     0x60000000
#define VC1_RD(src)                                  (((src) & 0x60000000)>>29)
#define VC1_WR(src)                             (((u32)(src)<<29) & 0x60000000)
#define VC1_SET(dst,src) \
                      (((dst) & ~0x60000000) | (((u32)(src)<<29) & 0x60000000))
/*	 Fields stashing	 */
#define STASHING1_WIDTH                                                       1
#define STASHING1_SHIFT                                                      28
#define STASHING1_MASK                                               0x10000000
#define STASHING1_RD(src)                            (((src) & 0x10000000)>>28)
#define STASHING1_WR(src)                       (((u32)(src)<<28) & 0x10000000)
#define STASHING1_SET(dst,src) \
                      (((dst) & ~0x10000000) | (((u32)(src)<<28) & 0x10000000))
/*	 Fields addr	 */
#define QM_ADDR1_WIDTH                                                  26
#define QM_ADDR1_SHIFT                                                   0
#define QM_ADDR1_MASK                                           0x03ffffff
#define QM_ADDR1_RD(src)                            (((src) & 0x03ffffff))
#define QM_ADDR1_WR(src)                       (((u32)(src)) & 0x03ffffff)
#define QM_ADDR1_SET(dst,src) \
                          (((dst) & ~0x03ffffff) | (((u32)(src)) & 0x03ffffff))

/*	Register csr_proc_mbox_base_2	*/ 
/*	 Fields coherent	 */
#define COHERENT2_WIDTH                                                       1
#define COHERENT2_SHIFT                                                      31
#define COHERENT2_MASK                                               0x80000000
#define COHERENT2_RD(src)                            (((src) & 0x80000000)>>31)
#define COHERENT2_WR(src)                       (((u32)(src)<<31) & 0x80000000)
#define COHERENT2_SET(dst,src) \
                      (((dst) & ~0x80000000) | (((u32)(src)<<31) & 0x80000000))
/*	 Fields vc	 */
#define VC2_WIDTH                                                             2
#define VC2_SHIFT                                                            29
#define VC2_MASK                                                     0x60000000
#define VC2_RD(src)                                  (((src) & 0x60000000)>>29)
#define VC2_WR(src)                             (((u32)(src)<<29) & 0x60000000)
#define VC2_SET(dst,src) \
                      (((dst) & ~0x60000000) | (((u32)(src)<<29) & 0x60000000))
/*	 Fields stashing	 */
#define STASHING2_WIDTH                                                       1
#define STASHING2_SHIFT                                                      28
#define STASHING2_MASK                                               0x10000000
#define STASHING2_RD(src)                            (((src) & 0x10000000)>>28)
#define STASHING2_WR(src)                       (((u32)(src)<<28) & 0x10000000)
#define STASHING2_SET(dst,src) \
                      (((dst) & ~0x10000000) | (((u32)(src)<<28) & 0x10000000))
/*	 Fields addr	 */
#define QM_ADDR2_WIDTH                                                  26
#define QM_ADDR2_SHIFT                                                   0
#define QM_ADDR2_MASK                                           0x03ffffff
#define QM_ADDR2_RD(src)                            (((src) & 0x03ffffff))
#define QM_ADDR2_WR(src)                       (((u32)(src)) & 0x03ffffff)
#define QM_ADDR2_SET(dst,src) \
                          (((dst) & ~0x03ffffff) | (((u32)(src)) & 0x03ffffff))

/*	Register csr_proc_mbox_base_3	*/ 
/*	 Fields coherent	 */
#define COHERENT3_WIDTH                                                       1
#define COHERENT3_SHIFT                                                      31
#define COHERENT3_MASK                                               0x80000000
#define COHERENT3_RD(src)                            (((src) & 0x80000000)>>31)
#define COHERENT3_WR(src)                       (((u32)(src)<<31) & 0x80000000)
#define COHERENT3_SET(dst,src) \
                      (((dst) & ~0x80000000) | (((u32)(src)<<31) & 0x80000000))
/*	 Fields vc	 */
#define VC3_WIDTH                                                             2
#define VC3_SHIFT                                                            29
#define VC3_MASK                                                     0x60000000
#define VC3_RD(src)                                  (((src) & 0x60000000)>>29)
#define VC3_WR(src)                             (((u32)(src)<<29) & 0x60000000)
#define VC3_SET(dst,src) \
                      (((dst) & ~0x60000000) | (((u32)(src)<<29) & 0x60000000))
/*	 Fields stashing	 */
#define STASHING3_WIDTH                                                       1
#define STASHING3_SHIFT                                                      28
#define STASHING3_MASK                                               0x10000000
#define STASHING3_RD(src)                            (((src) & 0x10000000)>>28)
#define STASHING3_WR(src)                       (((u32)(src)<<28) & 0x10000000)
#define STASHING3_SET(dst,src) \
                      (((dst) & ~0x10000000) | (((u32)(src)<<28) & 0x10000000))
/*	 Fields addr	 */
#define QM_ADDR3_WIDTH                                                  26
#define QM_ADDR3_SHIFT                                                   0
#define QM_ADDR3_MASK                                           0x03ffffff
#define QM_ADDR3_RD(src)                            (((src) & 0x03ffffff))
#define QM_ADDR3_WR(src)                       (((u32)(src)) & 0x03ffffff)
#define QM_ADDR3_SET(dst,src) \
                          (((dst) & ~0x03ffffff) | (((u32)(src)) & 0x03ffffff))

/*	Register csr_proc_fpool_base_0	*/ 
/*	 Fields coherent	 */
#define COHERENT0_F1_WIDTH                                                    1
#define COHERENT0_F1_SHIFT                                                   31
#define COHERENT0_F1_MASK                                            0x80000000
#define COHERENT0_F1_RD(src)                         (((src) & 0x80000000)>>31)
#define COHERENT0_F1_WR(src)                    (((u32)(src)<<31) & 0x80000000)
#define COHERENT0_F1_SET(dst,src) \
                      (((dst) & ~0x80000000) | (((u32)(src)<<31) & 0x80000000))
/*	 Fields vc	 */
#define VC0_F1_WIDTH                                                          2
#define VC0_F1_SHIFT                                                         29
#define VC0_F1_MASK                                                  0x60000000
#define VC0_F1_RD(src)                               (((src) & 0x60000000)>>29)
#define VC0_F1_WR(src)                          (((u32)(src)<<29) & 0x60000000)
#define VC0_F1_SET(dst,src) \
                      (((dst) & ~0x60000000) | (((u32)(src)<<29) & 0x60000000))
/*	 Fields stashing	 */
#define STASHING0_F1_WIDTH                                                    1
#define STASHING0_F1_SHIFT                                                   28
#define STASHING0_F1_MASK                                            0x10000000
#define STASHING0_F1_RD(src)                         (((src) & 0x10000000)>>28)
#define STASHING0_F1_WR(src)                    (((u32)(src)<<28) & 0x10000000)
#define STASHING0_F1_SET(dst,src) \
                      (((dst) & ~0x10000000) | (((u32)(src)<<28) & 0x10000000))
/*	 Fields addr	 */
#define QM_ADDR0_F1_WIDTH                                               27
#define QM_ADDR0_F1_SHIFT                                                0
#define QM_ADDR0_F1_MASK                                        0x07ffffff
#define QM_ADDR0_F1_RD(src)                         (((src) & 0x07ffffff))
#define QM_ADDR0_F1_WR(src)                    (((u32)(src)) & 0x07ffffff)
#define QM_ADDR0_F1_SET(dst,src) \
                          (((dst) & ~0x07ffffff) | (((u32)(src)) & 0x07ffffff))

/*	Register csr_proc_fpool_base_1	*/ 
/*	 Fields coherent	 */
#define COHERENT1_F1_WIDTH                                                    1
#define COHERENT1_F1_SHIFT                                                   31
#define COHERENT1_F1_MASK                                            0x80000000
#define COHERENT1_F1_RD(src)                         (((src) & 0x80000000)>>31)
#define COHERENT1_F1_WR(src)                    (((u32)(src)<<31) & 0x80000000)
#define COHERENT1_F1_SET(dst,src) \
                      (((dst) & ~0x80000000) | (((u32)(src)<<31) & 0x80000000))
/*	 Fields vc	 */
#define VC1_F1_WIDTH                                                          2
#define VC1_F1_SHIFT                                                         29
#define VC1_F1_MASK                                                  0x60000000
#define VC1_F1_RD(src)                               (((src) & 0x60000000)>>29)
#define VC1_F1_WR(src)                          (((u32)(src)<<29) & 0x60000000)
#define VC1_F1_SET(dst,src) \
                      (((dst) & ~0x60000000) | (((u32)(src)<<29) & 0x60000000))
/*	 Fields stashing	 */
#define STASHING1_F1_WIDTH                                                    1
#define STASHING1_F1_SHIFT                                                   28
#define STASHING1_F1_MASK                                            0x10000000
#define STASHING1_F1_RD(src)                         (((src) & 0x10000000)>>28)
#define STASHING1_F1_WR(src)                    (((u32)(src)<<28) & 0x10000000)
#define STASHING1_F1_SET(dst,src) \
                      (((dst) & ~0x10000000) | (((u32)(src)<<28) & 0x10000000))
/*	 Fields addr	 */
#define QM_ADDR1_F1_WIDTH                                               27
#define QM_ADDR1_F1_SHIFT                                                0
#define QM_ADDR1_F1_MASK                                        0x07ffffff
#define QM_ADDR1_F1_RD(src)                         (((src) & 0x07ffffff))
#define QM_ADDR1_F1_WR(src)                    (((u32)(src)) & 0x07ffffff)
#define QM_ADDR1_F1_SET(dst,src) \
                          (((dst) & ~0x07ffffff) | (((u32)(src)) & 0x07ffffff))

/*	Register csr_proc_fpool_base_2	*/ 
/*	 Fields coherent	 */
#define COHERENT2_F1_WIDTH                                                    1
#define COHERENT2_F1_SHIFT                                                   31
#define COHERENT2_F1_MASK                                            0x80000000
#define COHERENT2_F1_RD(src)                         (((src) & 0x80000000)>>31)
#define COHERENT2_F1_WR(src)                    (((u32)(src)<<31) & 0x80000000)
#define COHERENT2_F1_SET(dst,src) \
                      (((dst) & ~0x80000000) | (((u32)(src)<<31) & 0x80000000))
/*	 Fields vc	 */
#define VC2_F1_WIDTH                                                          2
#define VC2_F1_SHIFT                                                         29
#define VC2_F1_MASK                                                  0x60000000
#define VC2_F1_RD(src)                               (((src) & 0x60000000)>>29)
#define VC2_F1_WR(src)                          (((u32)(src)<<29) & 0x60000000)
#define VC2_F1_SET(dst,src) \
                      (((dst) & ~0x60000000) | (((u32)(src)<<29) & 0x60000000))
/*	 Fields stashing	 */
#define STASHING2_F1_WIDTH                                                    1
#define STASHING2_F1_SHIFT                                                   28
#define STASHING2_F1_MASK                                            0x10000000
#define STASHING2_F1_RD(src)                         (((src) & 0x10000000)>>28)
#define STASHING2_F1_WR(src)                    (((u32)(src)<<28) & 0x10000000)
#define STASHING2_F1_SET(dst,src) \
                      (((dst) & ~0x10000000) | (((u32)(src)<<28) & 0x10000000))
/*	 Fields addr	 */
#define QM_ADDR2_F1_WIDTH                                               27
#define QM_ADDR2_F1_SHIFT                                                0
#define QM_ADDR2_F1_MASK                                        0x07ffffff
#define QM_ADDR2_F1_RD(src)                         (((src) & 0x07ffffff))
#define QM_ADDR2_F1_WR(src)                    (((u32)(src)) & 0x07ffffff)
#define QM_ADDR2_F1_SET(dst,src) \
                          (((dst) & ~0x07ffffff) | (((u32)(src)) & 0x07ffffff))

/*	Register csr_proc_fpool_base_3	*/ 
/*	 Fields coherent	 */
#define COHERENT3_F1_WIDTH                                                    1
#define COHERENT3_F1_SHIFT                                                   31
#define COHERENT3_F1_MASK                                            0x80000000
#define COHERENT3_F1_RD(src)                         (((src) & 0x80000000)>>31)
#define COHERENT3_F1_WR(src)                    (((u32)(src)<<31) & 0x80000000)
#define COHERENT3_F1_SET(dst,src) \
                      (((dst) & ~0x80000000) | (((u32)(src)<<31) & 0x80000000))
/*	 Fields vc	 */
#define VC3_F1_WIDTH                                                          2
#define VC3_F1_SHIFT                                                         29
#define VC3_F1_MASK                                                  0x60000000
#define VC3_F1_RD(src)                               (((src) & 0x60000000)>>29)
#define VC3_F1_WR(src)                          (((u32)(src)<<29) & 0x60000000)
#define VC3_F1_SET(dst,src) \
                      (((dst) & ~0x60000000) | (((u32)(src)<<29) & 0x60000000))
/*	 Fields stashing	 */
#define STASHING3_F1_WIDTH                                                    1
#define STASHING3_F1_SHIFT                                                   28
#define STASHING3_F1_MASK                                            0x10000000
#define STASHING3_F1_RD(src)                         (((src) & 0x10000000)>>28)
#define STASHING3_F1_WR(src)                    (((u32)(src)<<28) & 0x10000000)
#define STASHING3_F1_SET(dst,src) \
                      (((dst) & ~0x10000000) | (((u32)(src)<<28) & 0x10000000))
/*	 Fields addr	 */
#define QM_ADDR3_F1_WIDTH                                               27
#define QM_ADDR3_F1_SHIFT                                                0
#define QM_ADDR3_F1_MASK                                        0x07ffffff
#define QM_ADDR3_F1_RD(src)                         (((src) & 0x07ffffff))
#define QM_ADDR3_F1_WR(src)                    (((u32)(src)) & 0x07ffffff)
#define QM_ADDR3_F1_SET(dst,src) \
                          (((dst) & ~0x07ffffff) | (((u32)(src)) & 0x07ffffff))

/*	Register csr_enq_base_0	*/ 
/*	 Fields coherent	 */
#define COHERENT0_F2_WIDTH                                                    1
#define COHERENT0_F2_SHIFT                                                   31
#define COHERENT0_F2_MASK                                            0x80000000
#define COHERENT0_F2_RD(src)                         (((src) & 0x80000000)>>31)
#define COHERENT0_F2_WR(src)                    (((u32)(src)<<31) & 0x80000000)
#define COHERENT0_F2_SET(dst,src) \
                      (((dst) & ~0x80000000) | (((u32)(src)<<31) & 0x80000000))
/*	 Fields vc	 */
#define VC0_F2_WIDTH                                                          2
#define VC0_F2_SHIFT                                                         29
#define VC0_F2_MASK                                                  0x60000000
#define VC0_F2_RD(src)                               (((src) & 0x60000000)>>29)
#define VC0_F2_WR(src)                          (((u32)(src)<<29) & 0x60000000)
#define VC0_F2_SET(dst,src) \
                      (((dst) & ~0x60000000) | (((u32)(src)<<29) & 0x60000000))
/*	 Fields stashing	 */
#define STASHING0_F2_WIDTH                                                    1
#define STASHING0_F2_SHIFT                                                   28
#define STASHING0_F2_MASK                                            0x10000000
#define STASHING0_F2_RD(src)                         (((src) & 0x10000000)>>28)
#define STASHING0_F2_WR(src)                    (((u32)(src)<<28) & 0x10000000)
#define STASHING0_F2_SET(dst,src) \
                      (((dst) & ~0x10000000) | (((u32)(src)<<28) & 0x10000000))
/*	 Fields addr	 */
#define QM_ADDR0_F2_WIDTH                                               26
#define QM_ADDR0_F2_SHIFT                                                0
#define QM_ADDR0_F2_MASK                                        0x03ffffff
#define QM_ADDR0_F2_RD(src)                         (((src) & 0x03ffffff))
#define QM_ADDR0_F2_WR(src)                    (((u32)(src)) & 0x03ffffff)
#define QM_ADDR0_F2_SET(dst,src) \
                          (((dst) & ~0x03ffffff) | (((u32)(src)) & 0x03ffffff))

/*	Register csr_enq_base_1	*/ 
/*	 Fields coherent	 */
#define COHERENT1_F2_WIDTH                                                    1
#define COHERENT1_F2_SHIFT                                                   31
#define COHERENT1_F2_MASK                                            0x80000000
#define COHERENT1_F2_RD(src)                         (((src) & 0x80000000)>>31)
#define COHERENT1_F2_WR(src)                    (((u32)(src)<<31) & 0x80000000)
#define COHERENT1_F2_SET(dst,src) \
                      (((dst) & ~0x80000000) | (((u32)(src)<<31) & 0x80000000))
/*	 Fields vc	 */
#define VC1_F2_WIDTH                                                          2
#define VC1_F2_SHIFT                                                         29
#define VC1_F2_MASK                                                  0x60000000
#define VC1_F2_RD(src)                               (((src) & 0x60000000)>>29)
#define VC1_F2_WR(src)                          (((u32)(src)<<29) & 0x60000000)
#define VC1_F2_SET(dst,src) \
                      (((dst) & ~0x60000000) | (((u32)(src)<<29) & 0x60000000))
/*	 Fields stashing	 */
#define STASHING1_F2_WIDTH                                                    1
#define STASHING1_F2_SHIFT                                                   28
#define STASHING1_F2_MASK                                            0x10000000
#define STASHING1_F2_RD(src)                         (((src) & 0x10000000)>>28)
#define STASHING1_F2_WR(src)                    (((u32)(src)<<28) & 0x10000000)
#define STASHING1_F2_SET(dst,src) \
                      (((dst) & ~0x10000000) | (((u32)(src)<<28) & 0x10000000))
/*	 Fields addr	 */
#define QM_ADDR1_F2_WIDTH                                               26
#define QM_ADDR1_F2_SHIFT                                                0
#define QM_ADDR1_F2_MASK                                        0x03ffffff
#define QM_ADDR1_F2_RD(src)                         (((src) & 0x03ffffff))
#define QM_ADDR1_F2_WR(src)                    (((u32)(src)) & 0x03ffffff)
#define QM_ADDR1_F2_SET(dst,src) \
                          (((dst) & ~0x03ffffff) | (((u32)(src)) & 0x03ffffff))

/*	Register csr_enq_base_2	*/ 
/*	 Fields coherent	 */
#define COHERENT2_F2_WIDTH                                                    1
#define COHERENT2_F2_SHIFT                                                   31
#define COHERENT2_F2_MASK                                            0x80000000
#define COHERENT2_F2_RD(src)                         (((src) & 0x80000000)>>31)
#define COHERENT2_F2_WR(src)                    (((u32)(src)<<31) & 0x80000000)
#define COHERENT2_F2_SET(dst,src) \
                      (((dst) & ~0x80000000) | (((u32)(src)<<31) & 0x80000000))
/*	 Fields vc	 */
#define VC2_F2_WIDTH                                                          2
#define VC2_F2_SHIFT                                                         29
#define VC2_F2_MASK                                                  0x60000000
#define VC2_F2_RD(src)                               (((src) & 0x60000000)>>29)
#define VC2_F2_WR(src)                          (((u32)(src)<<29) & 0x60000000)
#define VC2_F2_SET(dst,src) \
                      (((dst) & ~0x60000000) | (((u32)(src)<<29) & 0x60000000))
/*	 Fields stashing	 */
#define STASHING2_F2_WIDTH                                                    1
#define STASHING2_F2_SHIFT                                                   28
#define STASHING2_F2_MASK                                            0x10000000
#define STASHING2_F2_RD(src)                         (((src) & 0x10000000)>>28)
#define STASHING2_F2_WR(src)                    (((u32)(src)<<28) & 0x10000000)
#define STASHING2_F2_SET(dst,src) \
                      (((dst) & ~0x10000000) | (((u32)(src)<<28) & 0x10000000))
/*	 Fields addr	 */
#define QM_ADDR2_F2_WIDTH                                               26
#define QM_ADDR2_F2_SHIFT                                                0
#define QM_ADDR2_F2_MASK                                        0x03ffffff
#define QM_ADDR2_F2_RD(src)                         (((src) & 0x03ffffff))
#define QM_ADDR2_F2_WR(src)                    (((u32)(src)) & 0x03ffffff)
#define QM_ADDR2_F2_SET(dst,src) \
                          (((dst) & ~0x03ffffff) | (((u32)(src)) & 0x03ffffff))

/*	Register csr_enq_base_3	*/ 
/*	 Fields coherent	 */
#define COHERENT3_F2_WIDTH                                                    1
#define COHERENT3_F2_SHIFT                                                   31
#define COHERENT3_F2_MASK                                            0x80000000
#define COHERENT3_F2_RD(src)                         (((src) & 0x80000000)>>31)
#define COHERENT3_F2_WR(src)                    (((u32)(src)<<31) & 0x80000000)
#define COHERENT3_F2_SET(dst,src) \
                      (((dst) & ~0x80000000) | (((u32)(src)<<31) & 0x80000000))
/*	 Fields vc	 */
#define VC3_F2_WIDTH                                                          2
#define VC3_F2_SHIFT                                                         29
#define VC3_F2_MASK                                                  0x60000000
#define VC3_F2_RD(src)                               (((src) & 0x60000000)>>29)
#define VC3_F2_WR(src)                          (((u32)(src)<<29) & 0x60000000)
#define VC3_F2_SET(dst,src) \
                      (((dst) & ~0x60000000) | (((u32)(src)<<29) & 0x60000000))
/*	 Fields stashing	 */
#define STASHING3_F2_WIDTH                                                    1
#define STASHING3_F2_SHIFT                                                   28
#define STASHING3_F2_MASK                                            0x10000000
#define STASHING3_F2_RD(src)                         (((src) & 0x10000000)>>28)
#define STASHING3_F2_WR(src)                    (((u32)(src)<<28) & 0x10000000)
#define STASHING3_F2_SET(dst,src) \
                      (((dst) & ~0x10000000) | (((u32)(src)<<28) & 0x10000000))
/*	 Fields addr	 */
#define QM_ADDR3_F2_WIDTH                                               26
#define QM_ADDR3_F2_SHIFT                                                0
#define QM_ADDR3_F2_MASK                                        0x03ffffff
#define QM_ADDR3_F2_RD(src)                         (((src) & 0x03ffffff))
#define QM_ADDR3_F2_WR(src)                    (((u32)(src)) & 0x03ffffff)
#define QM_ADDR3_F2_SET(dst,src) \
                          (((dst) & ~0x03ffffff) | (((u32)(src)) & 0x03ffffff))

/*	Register csr_enq_status_0	*/ 
/*	 Fields mbox_0_15	 */
#define MBOX_0_150_WIDTH                                                      1
#define MBOX_0_150_SHIFT                                                     31
#define MBOX_0_150_MASK                                              0x80000000
#define MBOX_0_150_RD(src)                           (((src) & 0x80000000)>>31)
#define MBOX_0_150_SET(dst,src) \
                      (((dst) & ~0x80000000) | (((u32)(src)<<31) & 0x80000000))
/*	 Fields mbox_0_14	 */
#define MBOX_0_140_WIDTH                                                      1
#define MBOX_0_140_SHIFT                                                     30
#define MBOX_0_140_MASK                                              0x40000000
#define MBOX_0_140_RD(src)                           (((src) & 0x40000000)>>30)
#define MBOX_0_140_SET(dst,src) \
                      (((dst) & ~0x40000000) | (((u32)(src)<<30) & 0x40000000))
/*	 Fields mbox_0_13	 */
#define MBOX_0_130_WIDTH                                                      1
#define MBOX_0_130_SHIFT                                                     29
#define MBOX_0_130_MASK                                              0x20000000
#define MBOX_0_130_RD(src)                           (((src) & 0x20000000)>>29)
#define MBOX_0_130_SET(dst,src) \
                      (((dst) & ~0x20000000) | (((u32)(src)<<29) & 0x20000000))
/*	 Fields mbox_0_12	 */
#define MBOX_0_120_WIDTH                                                      1
#define MBOX_0_120_SHIFT                                                     28
#define MBOX_0_120_MASK                                              0x10000000
#define MBOX_0_120_RD(src)                           (((src) & 0x10000000)>>28)
#define MBOX_0_120_SET(dst,src) \
                      (((dst) & ~0x10000000) | (((u32)(src)<<28) & 0x10000000))
/*	 Fields mbox_0_11	 */
#define MBOX_0_110_WIDTH                                                      1
#define MBOX_0_110_SHIFT                                                     27
#define MBOX_0_110_MASK                                              0x08000000
#define MBOX_0_110_RD(src)                           (((src) & 0x08000000)>>27)
#define MBOX_0_110_SET(dst,src) \
                      (((dst) & ~0x08000000) | (((u32)(src)<<27) & 0x08000000))
/*	 Fields mbox_0_10	 */
#define MBOX_0_100_WIDTH                                                      1
#define MBOX_0_100_SHIFT                                                     26
#define MBOX_0_100_MASK                                              0x04000000
#define MBOX_0_100_RD(src)                           (((src) & 0x04000000)>>26)
#define MBOX_0_100_SET(dst,src) \
                      (((dst) & ~0x04000000) | (((u32)(src)<<26) & 0x04000000))
/*	 Fields mbox_0_9	 */
#define MBOX_0_90_WIDTH                                                       1
#define MBOX_0_90_SHIFT                                                      25
#define MBOX_0_90_MASK                                               0x02000000
#define MBOX_0_90_RD(src)                            (((src) & 0x02000000)>>25)
#define MBOX_0_90_SET(dst,src) \
                      (((dst) & ~0x02000000) | (((u32)(src)<<25) & 0x02000000))
/*	 Fields mbox_0_8	 */
#define MBOX_0_80_WIDTH                                                       1
#define MBOX_0_80_SHIFT                                                      24
#define MBOX_0_80_MASK                                               0x01000000
#define MBOX_0_80_RD(src)                            (((src) & 0x01000000)>>24)
#define MBOX_0_80_SET(dst,src) \
                      (((dst) & ~0x01000000) | (((u32)(src)<<24) & 0x01000000))
/*	 Fields mbox_0_7	 */
#define MBOX_0_70_WIDTH                                                       1
#define MBOX_0_70_SHIFT                                                      23
#define MBOX_0_70_MASK                                               0x00800000
#define MBOX_0_70_RD(src)                            (((src) & 0x00800000)>>23)
#define MBOX_0_70_SET(dst,src) \
                      (((dst) & ~0x00800000) | (((u32)(src)<<23) & 0x00800000))
/*	 Fields mbox_0_6	 */
#define MBOX_0_60_WIDTH                                                       1
#define MBOX_0_60_SHIFT                                                      22
#define MBOX_0_60_MASK                                               0x00400000
#define MBOX_0_60_RD(src)                            (((src) & 0x00400000)>>22)
#define MBOX_0_60_SET(dst,src) \
                      (((dst) & ~0x00400000) | (((u32)(src)<<22) & 0x00400000))
/*	 Fields mbox_0_5	 */
#define MBOX_0_50_WIDTH                                                       1
#define MBOX_0_50_SHIFT                                                      21
#define MBOX_0_50_MASK                                               0x00200000
#define MBOX_0_50_RD(src)                            (((src) & 0x00200000)>>21)
#define MBOX_0_50_SET(dst,src) \
                      (((dst) & ~0x00200000) | (((u32)(src)<<21) & 0x00200000))
/*	 Fields mbox_0_4	 */
#define MBOX_0_40_WIDTH                                                       1
#define MBOX_0_40_SHIFT                                                      20
#define MBOX_0_40_MASK                                               0x00100000
#define MBOX_0_40_RD(src)                            (((src) & 0x00100000)>>20)
#define MBOX_0_40_SET(dst,src) \
                      (((dst) & ~0x00100000) | (((u32)(src)<<20) & 0x00100000))
/*	 Fields mbox_0_3	 */
#define MBOX_0_30_WIDTH                                                       1
#define MBOX_0_30_SHIFT                                                      19
#define MBOX_0_30_MASK                                               0x00080000
#define MBOX_0_30_RD(src)                            (((src) & 0x00080000)>>19)
#define MBOX_0_30_SET(dst,src) \
                      (((dst) & ~0x00080000) | (((u32)(src)<<19) & 0x00080000))
/*	 Fields mbox_0_2	 */
#define MBOX_0_20_WIDTH                                                       1
#define MBOX_0_20_SHIFT                                                      18
#define MBOX_0_20_MASK                                               0x00040000
#define MBOX_0_20_RD(src)                            (((src) & 0x00040000)>>18)
#define MBOX_0_20_SET(dst,src) \
                      (((dst) & ~0x00040000) | (((u32)(src)<<18) & 0x00040000))
/*	 Fields mbox_0_1	 */
#define MBOX_0_10_WIDTH                                                       1
#define MBOX_0_10_SHIFT                                                      17
#define MBOX_0_10_MASK                                               0x00020000
#define MBOX_0_10_RD(src)                            (((src) & 0x00020000)>>17)
#define MBOX_0_10_SET(dst,src) \
                      (((dst) & ~0x00020000) | (((u32)(src)<<17) & 0x00020000))
/*	 Fields mbox_0_0	 */
#define MBOX_0_00_WIDTH                                                       1
#define MBOX_0_00_SHIFT                                                      16
#define MBOX_0_00_MASK                                               0x00010000
#define MBOX_0_00_RD(src)                            (((src) & 0x00010000)>>16)
#define MBOX_0_00_SET(dst,src) \
                      (((dst) & ~0x00010000) | (((u32)(src)<<16) & 0x00010000))
/*	 Fields mbox_1_15	 */
#define MBOX_1_150_WIDTH                                                      1
#define MBOX_1_150_SHIFT                                                     15
#define MBOX_1_150_MASK                                              0x00008000
#define MBOX_1_150_RD(src)                           (((src) & 0x00008000)>>15)
#define MBOX_1_150_SET(dst,src) \
                      (((dst) & ~0x00008000) | (((u32)(src)<<15) & 0x00008000))
/*	 Fields mbox_1_14	 */
#define MBOX_1_140_WIDTH                                                      1
#define MBOX_1_140_SHIFT                                                     14
#define MBOX_1_140_MASK                                              0x00004000
#define MBOX_1_140_RD(src)                           (((src) & 0x00004000)>>14)
#define MBOX_1_140_SET(dst,src) \
                      (((dst) & ~0x00004000) | (((u32)(src)<<14) & 0x00004000))
/*	 Fields mbox_1_13	 */
#define MBOX_1_130_WIDTH                                                      1
#define MBOX_1_130_SHIFT                                                     13
#define MBOX_1_130_MASK                                              0x00002000
#define MBOX_1_130_RD(src)                           (((src) & 0x00002000)>>13)
#define MBOX_1_130_SET(dst,src) \
                      (((dst) & ~0x00002000) | (((u32)(src)<<13) & 0x00002000))
/*	 Fields mbox_1_12	 */
#define MBOX_1_120_WIDTH                                                      1
#define MBOX_1_120_SHIFT                                                     12
#define MBOX_1_120_MASK                                              0x00001000
#define MBOX_1_120_RD(src)                           (((src) & 0x00001000)>>12)
#define MBOX_1_120_SET(dst,src) \
                      (((dst) & ~0x00001000) | (((u32)(src)<<12) & 0x00001000))
/*	 Fields mbox_1_11	 */
#define MBOX_1_110_WIDTH                                                      1
#define MBOX_1_110_SHIFT                                                     11
#define MBOX_1_110_MASK                                              0x00000800
#define MBOX_1_110_RD(src)                           (((src) & 0x00000800)>>11)
#define MBOX_1_110_SET(dst,src) \
                      (((dst) & ~0x00000800) | (((u32)(src)<<11) & 0x00000800))
/*	 Fields mbox_1_10	 */
#define MBOX_1_100_WIDTH                                                      1
#define MBOX_1_100_SHIFT                                                     10
#define MBOX_1_100_MASK                                              0x00000400
#define MBOX_1_100_RD(src)                           (((src) & 0x00000400)>>10)
#define MBOX_1_100_SET(dst,src) \
                      (((dst) & ~0x00000400) | (((u32)(src)<<10) & 0x00000400))
/*	 Fields mbox_1_9	 */
#define MBOX_1_90_WIDTH                                                       1
#define MBOX_1_90_SHIFT                                                       9
#define MBOX_1_90_MASK                                               0x00000200
#define MBOX_1_90_RD(src)                             (((src) & 0x00000200)>>9)
#define MBOX_1_90_SET(dst,src) \
                       (((dst) & ~0x00000200) | (((u32)(src)<<9) & 0x00000200))
/*	 Fields mbox_1_8	 */
#define MBOX_1_80_WIDTH                                                       1
#define MBOX_1_80_SHIFT                                                       8
#define MBOX_1_80_MASK                                               0x00000100
#define MBOX_1_80_RD(src)                             (((src) & 0x00000100)>>8)
#define MBOX_1_80_SET(dst,src) \
                       (((dst) & ~0x00000100) | (((u32)(src)<<8) & 0x00000100))
/*	 Fields mbox_1_7	 */
#define MBOX_1_70_WIDTH                                                       1
#define MBOX_1_70_SHIFT                                                       7
#define MBOX_1_70_MASK                                               0x00000080
#define MBOX_1_70_RD(src)                             (((src) & 0x00000080)>>7)
#define MBOX_1_70_SET(dst,src) \
                       (((dst) & ~0x00000080) | (((u32)(src)<<7) & 0x00000080))
/*	 Fields mbox_1_6	 */
#define MBOX_1_60_WIDTH                                                       1
#define MBOX_1_60_SHIFT                                                       6
#define MBOX_1_60_MASK                                               0x00000040
#define MBOX_1_60_RD(src)                             (((src) & 0x00000040)>>6)
#define MBOX_1_60_SET(dst,src) \
                       (((dst) & ~0x00000040) | (((u32)(src)<<6) & 0x00000040))
/*	 Fields mbox_1_5	 */
#define MBOX_1_50_WIDTH                                                       1
#define MBOX_1_50_SHIFT                                                       5
#define MBOX_1_50_MASK                                               0x00000020
#define MBOX_1_50_RD(src)                             (((src) & 0x00000020)>>5)
#define MBOX_1_50_SET(dst,src) \
                       (((dst) & ~0x00000020) | (((u32)(src)<<5) & 0x00000020))
/*	 Fields mbox_1_4	 */
#define MBOX_1_40_WIDTH                                                       1
#define MBOX_1_40_SHIFT                                                       4
#define MBOX_1_40_MASK                                               0x00000010
#define MBOX_1_40_RD(src)                             (((src) & 0x00000010)>>4)
#define MBOX_1_40_SET(dst,src) \
                       (((dst) & ~0x00000010) | (((u32)(src)<<4) & 0x00000010))
/*	 Fields mbox_1_3	 */
#define MBOX_1_30_WIDTH                                                       1
#define MBOX_1_30_SHIFT                                                       3
#define MBOX_1_30_MASK                                               0x00000008
#define MBOX_1_30_RD(src)                             (((src) & 0x00000008)>>3)
#define MBOX_1_30_SET(dst,src) \
                       (((dst) & ~0x00000008) | (((u32)(src)<<3) & 0x00000008))
/*	 Fields mbox_1_2	 */
#define MBOX_1_20_WIDTH                                                       1
#define MBOX_1_20_SHIFT                                                       2
#define MBOX_1_20_MASK                                               0x00000004
#define MBOX_1_20_RD(src)                             (((src) & 0x00000004)>>2)
#define MBOX_1_20_SET(dst,src) \
                       (((dst) & ~0x00000004) | (((u32)(src)<<2) & 0x00000004))
/*	 Fields mbox_1_1	 */
#define MBOX_1_10_WIDTH                                                       1
#define MBOX_1_10_SHIFT                                                       1
#define MBOX_1_10_MASK                                               0x00000002
#define MBOX_1_10_RD(src)                             (((src) & 0x00000002)>>1)
#define MBOX_1_10_SET(dst,src) \
                       (((dst) & ~0x00000002) | (((u32)(src)<<1) & 0x00000002))
/*	 Fields mbox_1_0	 */
#define MBOX_1_00_WIDTH                                                       1
#define MBOX_1_00_SHIFT                                                       0
#define MBOX_1_00_MASK                                               0x00000001
#define MBOX_1_00_RD(src)                                (((src) & 0x00000001))
#define MBOX_1_00_SET(dst,src) \
                          (((dst) & ~0x00000001) | (((u32)(src)) & 0x00000001))

/*	Register csr_enq_status_1	*/ 
/*	 Fields mbox_2_15	 */
#define MBOX_2_151_WIDTH                                                      1
#define MBOX_2_151_SHIFT                                                     31
#define MBOX_2_151_MASK                                              0x80000000
#define MBOX_2_151_RD(src)                           (((src) & 0x80000000)>>31)
#define MBOX_2_151_SET(dst,src) \
                      (((dst) & ~0x80000000) | (((u32)(src)<<31) & 0x80000000))
/*	 Fields mbox_2_14	 */
#define MBOX_2_141_WIDTH                                                      1
#define MBOX_2_141_SHIFT                                                     30
#define MBOX_2_141_MASK                                              0x40000000
#define MBOX_2_141_RD(src)                           (((src) & 0x40000000)>>30)
#define MBOX_2_141_SET(dst,src) \
                      (((dst) & ~0x40000000) | (((u32)(src)<<30) & 0x40000000))
/*	 Fields mbox_2_13	 */
#define MBOX_2_131_WIDTH                                                      1
#define MBOX_2_131_SHIFT                                                     29
#define MBOX_2_131_MASK                                              0x20000000
#define MBOX_2_131_RD(src)                           (((src) & 0x20000000)>>29)
#define MBOX_2_131_SET(dst,src) \
                      (((dst) & ~0x20000000) | (((u32)(src)<<29) & 0x20000000))
/*	 Fields mbox_2_12	 */
#define MBOX_2_121_WIDTH                                                      1
#define MBOX_2_121_SHIFT                                                     28
#define MBOX_2_121_MASK                                              0x10000000
#define MBOX_2_121_RD(src)                           (((src) & 0x10000000)>>28)
#define MBOX_2_121_SET(dst,src) \
                      (((dst) & ~0x10000000) | (((u32)(src)<<28) & 0x10000000))
/*	 Fields mbox_2_11	 */
#define MBOX_2_111_WIDTH                                                      1
#define MBOX_2_111_SHIFT                                                     27
#define MBOX_2_111_MASK                                              0x08000000
#define MBOX_2_111_RD(src)                           (((src) & 0x08000000)>>27)
#define MBOX_2_111_SET(dst,src) \
                      (((dst) & ~0x08000000) | (((u32)(src)<<27) & 0x08000000))
/*	 Fields mbox_2_10	 */
#define MBOX_2_101_WIDTH                                                      1
#define MBOX_2_101_SHIFT                                                     26
#define MBOX_2_101_MASK                                              0x04000000
#define MBOX_2_101_RD(src)                           (((src) & 0x04000000)>>26)
#define MBOX_2_101_SET(dst,src) \
                      (((dst) & ~0x04000000) | (((u32)(src)<<26) & 0x04000000))
/*	 Fields mbox_2_9	 */
#define MBOX_2_91_WIDTH                                                       1
#define MBOX_2_91_SHIFT                                                      25
#define MBOX_2_91_MASK                                               0x02000000
#define MBOX_2_91_RD(src)                            (((src) & 0x02000000)>>25)
#define MBOX_2_91_SET(dst,src) \
                      (((dst) & ~0x02000000) | (((u32)(src)<<25) & 0x02000000))
/*	 Fields mbox_2_8	 */
#define MBOX_2_81_WIDTH                                                       1
#define MBOX_2_81_SHIFT                                                      24
#define MBOX_2_81_MASK                                               0x01000000
#define MBOX_2_81_RD(src)                            (((src) & 0x01000000)>>24)
#define MBOX_2_81_SET(dst,src) \
                      (((dst) & ~0x01000000) | (((u32)(src)<<24) & 0x01000000))
/*	 Fields mbox_2_7	 */
#define MBOX_2_71_WIDTH                                                       1
#define MBOX_2_71_SHIFT                                                      23
#define MBOX_2_71_MASK                                               0x00800000
#define MBOX_2_71_RD(src)                            (((src) & 0x00800000)>>23)
#define MBOX_2_71_SET(dst,src) \
                      (((dst) & ~0x00800000) | (((u32)(src)<<23) & 0x00800000))
/*	 Fields mbox_2_6	 */
#define MBOX_2_61_WIDTH                                                       1
#define MBOX_2_61_SHIFT                                                      22
#define MBOX_2_61_MASK                                               0x00400000
#define MBOX_2_61_RD(src)                            (((src) & 0x00400000)>>22)
#define MBOX_2_61_SET(dst,src) \
                      (((dst) & ~0x00400000) | (((u32)(src)<<22) & 0x00400000))
/*	 Fields mbox_2_5	 */
#define MBOX_2_51_WIDTH                                                       1
#define MBOX_2_51_SHIFT                                                      21
#define MBOX_2_51_MASK                                               0x00200000
#define MBOX_2_51_RD(src)                            (((src) & 0x00200000)>>21)
#define MBOX_2_51_SET(dst,src) \
                      (((dst) & ~0x00200000) | (((u32)(src)<<21) & 0x00200000))
/*	 Fields mbox_2_4	 */
#define MBOX_2_41_WIDTH                                                       1
#define MBOX_2_41_SHIFT                                                      20
#define MBOX_2_41_MASK                                               0x00100000
#define MBOX_2_41_RD(src)                            (((src) & 0x00100000)>>20)
#define MBOX_2_41_SET(dst,src) \
                      (((dst) & ~0x00100000) | (((u32)(src)<<20) & 0x00100000))
/*	 Fields mbox_2_3	 */
#define MBOX_2_31_WIDTH                                                       1
#define MBOX_2_31_SHIFT                                                      19
#define MBOX_2_31_MASK                                               0x00080000
#define MBOX_2_31_RD(src)                            (((src) & 0x00080000)>>19)
#define MBOX_2_31_SET(dst,src) \
                      (((dst) & ~0x00080000) | (((u32)(src)<<19) & 0x00080000))
/*	 Fields mbox_2_2	 */
#define MBOX_2_21_WIDTH                                                       1
#define MBOX_2_21_SHIFT                                                      18
#define MBOX_2_21_MASK                                               0x00040000
#define MBOX_2_21_RD(src)                            (((src) & 0x00040000)>>18)
#define MBOX_2_21_SET(dst,src) \
                      (((dst) & ~0x00040000) | (((u32)(src)<<18) & 0x00040000))
/*	 Fields mbox_2_1	 */
#define MBOX_2_11_WIDTH                                                       1
#define MBOX_2_11_SHIFT                                                      17
#define MBOX_2_11_MASK                                               0x00020000
#define MBOX_2_11_RD(src)                            (((src) & 0x00020000)>>17)
#define MBOX_2_11_SET(dst,src) \
                      (((dst) & ~0x00020000) | (((u32)(src)<<17) & 0x00020000))
/*	 Fields mbox_2_0	 */
#define MBOX_2_01_WIDTH                                                       1
#define MBOX_2_01_SHIFT                                                      16
#define MBOX_2_01_MASK                                               0x00010000
#define MBOX_2_01_RD(src)                            (((src) & 0x00010000)>>16)
#define MBOX_2_01_SET(dst,src) \
                      (((dst) & ~0x00010000) | (((u32)(src)<<16) & 0x00010000))
/*	 Fields mbox_3_15	 */
#define MBOX_3_151_WIDTH                                                      1
#define MBOX_3_151_SHIFT                                                     15
#define MBOX_3_151_MASK                                              0x00008000
#define MBOX_3_151_RD(src)                           (((src) & 0x00008000)>>15)
#define MBOX_3_151_SET(dst,src) \
                      (((dst) & ~0x00008000) | (((u32)(src)<<15) & 0x00008000))
/*	 Fields mbox_3_14	 */
#define MBOX_3_141_WIDTH                                                      1
#define MBOX_3_141_SHIFT                                                     14
#define MBOX_3_141_MASK                                              0x00004000
#define MBOX_3_141_RD(src)                           (((src) & 0x00004000)>>14)
#define MBOX_3_141_SET(dst,src) \
                      (((dst) & ~0x00004000) | (((u32)(src)<<14) & 0x00004000))
/*	 Fields mbox_3_13	 */
#define MBOX_3_131_WIDTH                                                      1
#define MBOX_3_131_SHIFT                                                     13
#define MBOX_3_131_MASK                                              0x00002000
#define MBOX_3_131_RD(src)                           (((src) & 0x00002000)>>13)
#define MBOX_3_131_SET(dst,src) \
                      (((dst) & ~0x00002000) | (((u32)(src)<<13) & 0x00002000))
/*	 Fields mbox_3_12	 */
#define MBOX_3_121_WIDTH                                                      1
#define MBOX_3_121_SHIFT                                                     12
#define MBOX_3_121_MASK                                              0x00001000
#define MBOX_3_121_RD(src)                           (((src) & 0x00001000)>>12)
#define MBOX_3_121_SET(dst,src) \
                      (((dst) & ~0x00001000) | (((u32)(src)<<12) & 0x00001000))
/*	 Fields mbox_3_11	 */
#define MBOX_3_111_WIDTH                                                      1
#define MBOX_3_111_SHIFT                                                     11
#define MBOX_3_111_MASK                                              0x00000800
#define MBOX_3_111_RD(src)                           (((src) & 0x00000800)>>11)
#define MBOX_3_111_SET(dst,src) \
                      (((dst) & ~0x00000800) | (((u32)(src)<<11) & 0x00000800))
/*	 Fields mbox_3_10	 */
#define MBOX_3_101_WIDTH                                                      1
#define MBOX_3_101_SHIFT                                                     10
#define MBOX_3_101_MASK                                              0x00000400
#define MBOX_3_101_RD(src)                           (((src) & 0x00000400)>>10)
#define MBOX_3_101_SET(dst,src) \
                      (((dst) & ~0x00000400) | (((u32)(src)<<10) & 0x00000400))
/*	 Fields mbox_3_9	 */
#define MBOX_3_91_WIDTH                                                       1
#define MBOX_3_91_SHIFT                                                       9
#define MBOX_3_91_MASK                                               0x00000200
#define MBOX_3_91_RD(src)                             (((src) & 0x00000200)>>9)
#define MBOX_3_91_SET(dst,src) \
                       (((dst) & ~0x00000200) | (((u32)(src)<<9) & 0x00000200))
/*	 Fields mbox_3_8	 */
#define MBOX_3_81_WIDTH                                                       1
#define MBOX_3_81_SHIFT                                                       8
#define MBOX_3_81_MASK                                               0x00000100
#define MBOX_3_81_RD(src)                             (((src) & 0x00000100)>>8)
#define MBOX_3_81_SET(dst,src) \
                       (((dst) & ~0x00000100) | (((u32)(src)<<8) & 0x00000100))
/*	 Fields mbox_3_7	 */
#define MBOX_3_71_WIDTH                                                       1
#define MBOX_3_71_SHIFT                                                       7
#define MBOX_3_71_MASK                                               0x00000080
#define MBOX_3_71_RD(src)                             (((src) & 0x00000080)>>7)
#define MBOX_3_71_SET(dst,src) \
                       (((dst) & ~0x00000080) | (((u32)(src)<<7) & 0x00000080))
/*	 Fields mbox_3_6	 */
#define MBOX_3_61_WIDTH                                                       1
#define MBOX_3_61_SHIFT                                                       6
#define MBOX_3_61_MASK                                               0x00000040
#define MBOX_3_61_RD(src)                             (((src) & 0x00000040)>>6)
#define MBOX_3_61_SET(dst,src) \
                       (((dst) & ~0x00000040) | (((u32)(src)<<6) & 0x00000040))
/*	 Fields mbox_3_5	 */
#define MBOX_3_51_WIDTH                                                       1
#define MBOX_3_51_SHIFT                                                       5
#define MBOX_3_51_MASK                                               0x00000020
#define MBOX_3_51_RD(src)                             (((src) & 0x00000020)>>5)
#define MBOX_3_51_SET(dst,src) \
                       (((dst) & ~0x00000020) | (((u32)(src)<<5) & 0x00000020))
/*	 Fields mbox_3_4	 */
#define MBOX_3_41_WIDTH                                                       1
#define MBOX_3_41_SHIFT                                                       4
#define MBOX_3_41_MASK                                               0x00000010
#define MBOX_3_41_RD(src)                             (((src) & 0x00000010)>>4)
#define MBOX_3_41_SET(dst,src) \
                       (((dst) & ~0x00000010) | (((u32)(src)<<4) & 0x00000010))
/*	 Fields mbox_3_3	 */
#define MBOX_3_31_WIDTH                                                       1
#define MBOX_3_31_SHIFT                                                       3
#define MBOX_3_31_MASK                                               0x00000008
#define MBOX_3_31_RD(src)                             (((src) & 0x00000008)>>3)
#define MBOX_3_31_SET(dst,src) \
                       (((dst) & ~0x00000008) | (((u32)(src)<<3) & 0x00000008))
/*	 Fields mbox_3_2	 */
#define MBOX_3_21_WIDTH                                                       1
#define MBOX_3_21_SHIFT                                                       2
#define MBOX_3_21_MASK                                               0x00000004
#define MBOX_3_21_RD(src)                             (((src) & 0x00000004)>>2)
#define MBOX_3_21_SET(dst,src) \
                       (((dst) & ~0x00000004) | (((u32)(src)<<2) & 0x00000004))
/*	 Fields mbox_3_1	 */
#define MBOX_3_11_WIDTH                                                       1
#define MBOX_3_11_SHIFT                                                       1
#define MBOX_3_11_MASK                                               0x00000002
#define MBOX_3_11_RD(src)                             (((src) & 0x00000002)>>1)
#define MBOX_3_11_SET(dst,src) \
                       (((dst) & ~0x00000002) | (((u32)(src)<<1) & 0x00000002))
/*	 Fields mbox_3_0	 */
#define MBOX_3_01_WIDTH                                                       1
#define MBOX_3_01_SHIFT                                                       0
#define MBOX_3_01_MASK                                               0x00000001
#define MBOX_3_01_RD(src)                                (((src) & 0x00000001))
#define MBOX_3_01_SET(dst,src) \
                          (((dst) & ~0x00000001) | (((u32)(src)) & 0x00000001))

/*	Register csr_enq_status_2	*/ 
/*	 Fields mbox_4_15	 */
#define MBOX_4_152_WIDTH                                                      1
#define MBOX_4_152_SHIFT                                                     31
#define MBOX_4_152_MASK                                              0x80000000
#define MBOX_4_152_RD(src)                           (((src) & 0x80000000)>>31)
#define MBOX_4_152_SET(dst,src) \
                      (((dst) & ~0x80000000) | (((u32)(src)<<31) & 0x80000000))
/*	 Fields mbox_4_14	 */
#define MBOX_4_142_WIDTH                                                      1
#define MBOX_4_142_SHIFT                                                     30
#define MBOX_4_142_MASK                                              0x40000000
#define MBOX_4_142_RD(src)                           (((src) & 0x40000000)>>30)
#define MBOX_4_142_SET(dst,src) \
                      (((dst) & ~0x40000000) | (((u32)(src)<<30) & 0x40000000))
/*	 Fields mbox_4_13	 */
#define MBOX_4_132_WIDTH                                                      1
#define MBOX_4_132_SHIFT                                                     29
#define MBOX_4_132_MASK                                              0x20000000
#define MBOX_4_132_RD(src)                           (((src) & 0x20000000)>>29)
#define MBOX_4_132_SET(dst,src) \
                      (((dst) & ~0x20000000) | (((u32)(src)<<29) & 0x20000000))
/*	 Fields mbox_4_12	 */
#define MBOX_4_122_WIDTH                                                      1
#define MBOX_4_122_SHIFT                                                     28
#define MBOX_4_122_MASK                                              0x10000000
#define MBOX_4_122_RD(src)                           (((src) & 0x10000000)>>28)
#define MBOX_4_122_SET(dst,src) \
                      (((dst) & ~0x10000000) | (((u32)(src)<<28) & 0x10000000))
/*	 Fields mbox_4_11	 */
#define MBOX_4_112_WIDTH                                                      1
#define MBOX_4_112_SHIFT                                                     27
#define MBOX_4_112_MASK                                              0x08000000
#define MBOX_4_112_RD(src)                           (((src) & 0x08000000)>>27)
#define MBOX_4_112_SET(dst,src) \
                      (((dst) & ~0x08000000) | (((u32)(src)<<27) & 0x08000000))
/*	 Fields mbox_4_10	 */
#define MBOX_4_102_WIDTH                                                      1
#define MBOX_4_102_SHIFT                                                     26
#define MBOX_4_102_MASK                                              0x04000000
#define MBOX_4_102_RD(src)                           (((src) & 0x04000000)>>26)
#define MBOX_4_102_SET(dst,src) \
                      (((dst) & ~0x04000000) | (((u32)(src)<<26) & 0x04000000))
/*	 Fields mbox_4_9	 */
#define MBOX_4_92_WIDTH                                                       1
#define MBOX_4_92_SHIFT                                                      25
#define MBOX_4_92_MASK                                               0x02000000
#define MBOX_4_92_RD(src)                            (((src) & 0x02000000)>>25)
#define MBOX_4_92_SET(dst,src) \
                      (((dst) & ~0x02000000) | (((u32)(src)<<25) & 0x02000000))
/*	 Fields mbox_4_8	 */
#define MBOX_4_82_WIDTH                                                       1
#define MBOX_4_82_SHIFT                                                      24
#define MBOX_4_82_MASK                                               0x01000000
#define MBOX_4_82_RD(src)                            (((src) & 0x01000000)>>24)
#define MBOX_4_82_SET(dst,src) \
                      (((dst) & ~0x01000000) | (((u32)(src)<<24) & 0x01000000))
/*	 Fields mbox_4_7	 */
#define MBOX_4_72_WIDTH                                                       1
#define MBOX_4_72_SHIFT                                                      23
#define MBOX_4_72_MASK                                               0x00800000
#define MBOX_4_72_RD(src)                            (((src) & 0x00800000)>>23)
#define MBOX_4_72_SET(dst,src) \
                      (((dst) & ~0x00800000) | (((u32)(src)<<23) & 0x00800000))
/*	 Fields mbox_4_6	 */
#define MBOX_4_62_WIDTH                                                       1
#define MBOX_4_62_SHIFT                                                      22
#define MBOX_4_62_MASK                                               0x00400000
#define MBOX_4_62_RD(src)                            (((src) & 0x00400000)>>22)
#define MBOX_4_62_SET(dst,src) \
                      (((dst) & ~0x00400000) | (((u32)(src)<<22) & 0x00400000))
/*	 Fields mbox_4_5	 */
#define MBOX_4_52_WIDTH                                                       1
#define MBOX_4_52_SHIFT                                                      21
#define MBOX_4_52_MASK                                               0x00200000
#define MBOX_4_52_RD(src)                            (((src) & 0x00200000)>>21)
#define MBOX_4_52_SET(dst,src) \
                      (((dst) & ~0x00200000) | (((u32)(src)<<21) & 0x00200000))
/*	 Fields mbox_4_4	 */
#define MBOX_4_42_WIDTH                                                       1
#define MBOX_4_42_SHIFT                                                      20
#define MBOX_4_42_MASK                                               0x00100000
#define MBOX_4_42_RD(src)                            (((src) & 0x00100000)>>20)
#define MBOX_4_42_SET(dst,src) \
                      (((dst) & ~0x00100000) | (((u32)(src)<<20) & 0x00100000))
/*	 Fields mbox_4_3	 */
#define MBOX_4_32_WIDTH                                                       1
#define MBOX_4_32_SHIFT                                                      19
#define MBOX_4_32_MASK                                               0x00080000
#define MBOX_4_32_RD(src)                            (((src) & 0x00080000)>>19)
#define MBOX_4_32_SET(dst,src) \
                      (((dst) & ~0x00080000) | (((u32)(src)<<19) & 0x00080000))
/*	 Fields mbox_4_2	 */
#define MBOX_4_22_WIDTH                                                       1
#define MBOX_4_22_SHIFT                                                      18
#define MBOX_4_22_MASK                                               0x00040000
#define MBOX_4_22_RD(src)                            (((src) & 0x00040000)>>18)
#define MBOX_4_22_SET(dst,src) \
                      (((dst) & ~0x00040000) | (((u32)(src)<<18) & 0x00040000))
/*	 Fields mbox_4_1	 */
#define MBOX_4_12_WIDTH                                                       1
#define MBOX_4_12_SHIFT                                                      17
#define MBOX_4_12_MASK                                               0x00020000
#define MBOX_4_12_RD(src)                            (((src) & 0x00020000)>>17)
#define MBOX_4_12_SET(dst,src) \
                      (((dst) & ~0x00020000) | (((u32)(src)<<17) & 0x00020000))
/*	 Fields mbox_4_0	 */
#define MBOX_4_02_WIDTH                                                       1
#define MBOX_4_02_SHIFT                                                      16
#define MBOX_4_02_MASK                                               0x00010000
#define MBOX_4_02_RD(src)                            (((src) & 0x00010000)>>16)
#define MBOX_4_02_SET(dst,src) \
                      (((dst) & ~0x00010000) | (((u32)(src)<<16) & 0x00010000))
/*	 Fields mbox_5_15	 */
#define MBOX_5_152_WIDTH                                                      1
#define MBOX_5_152_SHIFT                                                     15
#define MBOX_5_152_MASK                                              0x00008000
#define MBOX_5_152_RD(src)                           (((src) & 0x00008000)>>15)
#define MBOX_5_152_SET(dst,src) \
                      (((dst) & ~0x00008000) | (((u32)(src)<<15) & 0x00008000))
/*	 Fields mbox_5_14	 */
#define MBOX_5_142_WIDTH                                                      1
#define MBOX_5_142_SHIFT                                                     14
#define MBOX_5_142_MASK                                              0x00004000
#define MBOX_5_142_RD(src)                           (((src) & 0x00004000)>>14)
#define MBOX_5_142_SET(dst,src) \
                      (((dst) & ~0x00004000) | (((u32)(src)<<14) & 0x00004000))
/*	 Fields mbox_5_13	 */
#define MBOX_5_132_WIDTH                                                      1
#define MBOX_5_132_SHIFT                                                     13
#define MBOX_5_132_MASK                                              0x00002000
#define MBOX_5_132_RD(src)                           (((src) & 0x00002000)>>13)
#define MBOX_5_132_SET(dst,src) \
                      (((dst) & ~0x00002000) | (((u32)(src)<<13) & 0x00002000))
/*	 Fields mbox_5_12	 */
#define MBOX_5_122_WIDTH                                                      1
#define MBOX_5_122_SHIFT                                                     12
#define MBOX_5_122_MASK                                              0x00001000
#define MBOX_5_122_RD(src)                           (((src) & 0x00001000)>>12)
#define MBOX_5_122_SET(dst,src) \
                      (((dst) & ~0x00001000) | (((u32)(src)<<12) & 0x00001000))
/*	 Fields mbox_5_11	 */
#define MBOX_5_112_WIDTH                                                      1
#define MBOX_5_112_SHIFT                                                     11
#define MBOX_5_112_MASK                                              0x00000800
#define MBOX_5_112_RD(src)                           (((src) & 0x00000800)>>11)
#define MBOX_5_112_SET(dst,src) \
                      (((dst) & ~0x00000800) | (((u32)(src)<<11) & 0x00000800))
/*	 Fields mbox_5_10	 */
#define MBOX_5_102_WIDTH                                                      1
#define MBOX_5_102_SHIFT                                                     10
#define MBOX_5_102_MASK                                              0x00000400
#define MBOX_5_102_RD(src)                           (((src) & 0x00000400)>>10)
#define MBOX_5_102_SET(dst,src) \
                      (((dst) & ~0x00000400) | (((u32)(src)<<10) & 0x00000400))
/*	 Fields mbox_5_9	 */
#define MBOX_5_92_WIDTH                                                       1
#define MBOX_5_92_SHIFT                                                       9
#define MBOX_5_92_MASK                                               0x00000200
#define MBOX_5_92_RD(src)                             (((src) & 0x00000200)>>9)
#define MBOX_5_92_SET(dst,src) \
                       (((dst) & ~0x00000200) | (((u32)(src)<<9) & 0x00000200))
/*	 Fields mbox_5_8	 */
#define MBOX_5_82_WIDTH                                                       1
#define MBOX_5_82_SHIFT                                                       8
#define MBOX_5_82_MASK                                               0x00000100
#define MBOX_5_82_RD(src)                             (((src) & 0x00000100)>>8)
#define MBOX_5_82_SET(dst,src) \
                       (((dst) & ~0x00000100) | (((u32)(src)<<8) & 0x00000100))
/*	 Fields mbox_5_7	 */
#define MBOX_5_72_WIDTH                                                       1
#define MBOX_5_72_SHIFT                                                       7
#define MBOX_5_72_MASK                                               0x00000080
#define MBOX_5_72_RD(src)                             (((src) & 0x00000080)>>7)
#define MBOX_5_72_SET(dst,src) \
                       (((dst) & ~0x00000080) | (((u32)(src)<<7) & 0x00000080))
/*	 Fields mbox_5_6	 */
#define MBOX_5_62_WIDTH                                                       1
#define MBOX_5_62_SHIFT                                                       6
#define MBOX_5_62_MASK                                               0x00000040
#define MBOX_5_62_RD(src)                             (((src) & 0x00000040)>>6)
#define MBOX_5_62_SET(dst,src) \
                       (((dst) & ~0x00000040) | (((u32)(src)<<6) & 0x00000040))
/*	 Fields mbox_5_5	 */
#define MBOX_5_52_WIDTH                                                       1
#define MBOX_5_52_SHIFT                                                       5
#define MBOX_5_52_MASK                                               0x00000020
#define MBOX_5_52_RD(src)                             (((src) & 0x00000020)>>5)
#define MBOX_5_52_SET(dst,src) \
                       (((dst) & ~0x00000020) | (((u32)(src)<<5) & 0x00000020))
/*	 Fields mbox_5_4	 */
#define MBOX_5_42_WIDTH                                                       1
#define MBOX_5_42_SHIFT                                                       4
#define MBOX_5_42_MASK                                               0x00000010
#define MBOX_5_42_RD(src)                             (((src) & 0x00000010)>>4)
#define MBOX_5_42_SET(dst,src) \
                       (((dst) & ~0x00000010) | (((u32)(src)<<4) & 0x00000010))
/*	 Fields mbox_5_3	 */
#define MBOX_5_32_WIDTH                                                       1
#define MBOX_5_32_SHIFT                                                       3
#define MBOX_5_32_MASK                                               0x00000008
#define MBOX_5_32_RD(src)                             (((src) & 0x00000008)>>3)
#define MBOX_5_32_SET(dst,src) \
                       (((dst) & ~0x00000008) | (((u32)(src)<<3) & 0x00000008))
/*	 Fields mbox_5_2	 */
#define MBOX_5_22_WIDTH                                                       1
#define MBOX_5_22_SHIFT                                                       2
#define MBOX_5_22_MASK                                               0x00000004
#define MBOX_5_22_RD(src)                             (((src) & 0x00000004)>>2)
#define MBOX_5_22_SET(dst,src) \
                       (((dst) & ~0x00000004) | (((u32)(src)<<2) & 0x00000004))
/*	 Fields mbox_5_1	 */
#define MBOX_5_12_WIDTH                                                       1
#define MBOX_5_12_SHIFT                                                       1
#define MBOX_5_12_MASK                                               0x00000002
#define MBOX_5_12_RD(src)                             (((src) & 0x00000002)>>1)
#define MBOX_5_12_SET(dst,src) \
                       (((dst) & ~0x00000002) | (((u32)(src)<<1) & 0x00000002))
/*	 Fields mbox_5_0	 */
#define MBOX_5_02_WIDTH                                                       1
#define MBOX_5_02_SHIFT                                                       0
#define MBOX_5_02_MASK                                               0x00000001
#define MBOX_5_02_RD(src)                                (((src) & 0x00000001))
#define MBOX_5_02_SET(dst,src) \
                          (((dst) & ~0x00000001) | (((u32)(src)) & 0x00000001))

/*	Register csr_enq_status_3	*/ 
/*	 Fields mbox_6_15	 */
#define MBOX_6_153_WIDTH                                                      1
#define MBOX_6_153_SHIFT                                                     31
#define MBOX_6_153_MASK                                              0x80000000
#define MBOX_6_153_RD(src)                           (((src) & 0x80000000)>>31)
#define MBOX_6_153_SET(dst,src) \
                      (((dst) & ~0x80000000) | (((u32)(src)<<31) & 0x80000000))
/*	 Fields mbox_6_14	 */
#define MBOX_6_143_WIDTH                                                      1
#define MBOX_6_143_SHIFT                                                     30
#define MBOX_6_143_MASK                                              0x40000000
#define MBOX_6_143_RD(src)                           (((src) & 0x40000000)>>30)
#define MBOX_6_143_SET(dst,src) \
                      (((dst) & ~0x40000000) | (((u32)(src)<<30) & 0x40000000))
/*	 Fields mbox_6_13	 */
#define MBOX_6_133_WIDTH                                                      1
#define MBOX_6_133_SHIFT                                                     29
#define MBOX_6_133_MASK                                              0x20000000
#define MBOX_6_133_RD(src)                           (((src) & 0x20000000)>>29)
#define MBOX_6_133_SET(dst,src) \
                      (((dst) & ~0x20000000) | (((u32)(src)<<29) & 0x20000000))
/*	 Fields mbox_6_12	 */
#define MBOX_6_123_WIDTH                                                      1
#define MBOX_6_123_SHIFT                                                     28
#define MBOX_6_123_MASK                                              0x10000000
#define MBOX_6_123_RD(src)                           (((src) & 0x10000000)>>28)
#define MBOX_6_123_SET(dst,src) \
                      (((dst) & ~0x10000000) | (((u32)(src)<<28) & 0x10000000))
/*	 Fields mbox_6_11	 */
#define MBOX_6_113_WIDTH                                                      1
#define MBOX_6_113_SHIFT                                                     27
#define MBOX_6_113_MASK                                              0x08000000
#define MBOX_6_113_RD(src)                           (((src) & 0x08000000)>>27)
#define MBOX_6_113_SET(dst,src) \
                      (((dst) & ~0x08000000) | (((u32)(src)<<27) & 0x08000000))
/*	 Fields mbox_6_10	 */
#define MBOX_6_103_WIDTH                                                      1
#define MBOX_6_103_SHIFT                                                     26
#define MBOX_6_103_MASK                                              0x04000000
#define MBOX_6_103_RD(src)                           (((src) & 0x04000000)>>26)
#define MBOX_6_103_SET(dst,src) \
                      (((dst) & ~0x04000000) | (((u32)(src)<<26) & 0x04000000))
/*	 Fields mbox_6_9	 */
#define MBOX_6_93_WIDTH                                                       1
#define MBOX_6_93_SHIFT                                                      25
#define MBOX_6_93_MASK                                               0x02000000
#define MBOX_6_93_RD(src)                            (((src) & 0x02000000)>>25)
#define MBOX_6_93_SET(dst,src) \
                      (((dst) & ~0x02000000) | (((u32)(src)<<25) & 0x02000000))
/*	 Fields mbox_6_8	 */
#define MBOX_6_83_WIDTH                                                       1
#define MBOX_6_83_SHIFT                                                      24
#define MBOX_6_83_MASK                                               0x01000000
#define MBOX_6_83_RD(src)                            (((src) & 0x01000000)>>24)
#define MBOX_6_83_SET(dst,src) \
                      (((dst) & ~0x01000000) | (((u32)(src)<<24) & 0x01000000))
/*	 Fields mbox_6_7	 */
#define MBOX_6_73_WIDTH                                                       1
#define MBOX_6_73_SHIFT                                                      23
#define MBOX_6_73_MASK                                               0x00800000
#define MBOX_6_73_RD(src)                            (((src) & 0x00800000)>>23)
#define MBOX_6_73_SET(dst,src) \
                      (((dst) & ~0x00800000) | (((u32)(src)<<23) & 0x00800000))
/*	 Fields mbox_6_6	 */
#define MBOX_6_63_WIDTH                                                       1
#define MBOX_6_63_SHIFT                                                      22
#define MBOX_6_63_MASK                                               0x00400000
#define MBOX_6_63_RD(src)                            (((src) & 0x00400000)>>22)
#define MBOX_6_63_SET(dst,src) \
                      (((dst) & ~0x00400000) | (((u32)(src)<<22) & 0x00400000))
/*	 Fields mbox_6_5	 */
#define MBOX_6_53_WIDTH                                                       1
#define MBOX_6_53_SHIFT                                                      21
#define MBOX_6_53_MASK                                               0x00200000
#define MBOX_6_53_RD(src)                            (((src) & 0x00200000)>>21)
#define MBOX_6_53_SET(dst,src) \
                      (((dst) & ~0x00200000) | (((u32)(src)<<21) & 0x00200000))
/*	 Fields mbox_6_4	 */
#define MBOX_6_43_WIDTH                                                       1
#define MBOX_6_43_SHIFT                                                      20
#define MBOX_6_43_MASK                                               0x00100000
#define MBOX_6_43_RD(src)                            (((src) & 0x00100000)>>20)
#define MBOX_6_43_SET(dst,src) \
                      (((dst) & ~0x00100000) | (((u32)(src)<<20) & 0x00100000))
/*	 Fields mbox_6_3	 */
#define MBOX_6_33_WIDTH                                                       1
#define MBOX_6_33_SHIFT                                                      19
#define MBOX_6_33_MASK                                               0x00080000
#define MBOX_6_33_RD(src)                            (((src) & 0x00080000)>>19)
#define MBOX_6_33_SET(dst,src) \
                      (((dst) & ~0x00080000) | (((u32)(src)<<19) & 0x00080000))
/*	 Fields mbox_6_2	 */
#define MBOX_6_23_WIDTH                                                       1
#define MBOX_6_23_SHIFT                                                      18
#define MBOX_6_23_MASK                                               0x00040000
#define MBOX_6_23_RD(src)                            (((src) & 0x00040000)>>18)
#define MBOX_6_23_SET(dst,src) \
                      (((dst) & ~0x00040000) | (((u32)(src)<<18) & 0x00040000))
/*	 Fields mbox_6_1	 */
#define MBOX_6_13_WIDTH                                                       1
#define MBOX_6_13_SHIFT                                                      17
#define MBOX_6_13_MASK                                               0x00020000
#define MBOX_6_13_RD(src)                            (((src) & 0x00020000)>>17)
#define MBOX_6_13_SET(dst,src) \
                      (((dst) & ~0x00020000) | (((u32)(src)<<17) & 0x00020000))
/*	 Fields mbox_6_0	 */
#define MBOX_6_03_WIDTH                                                       1
#define MBOX_6_03_SHIFT                                                      16
#define MBOX_6_03_MASK                                               0x00010000
#define MBOX_6_03_RD(src)                            (((src) & 0x00010000)>>16)
#define MBOX_6_03_SET(dst,src) \
                      (((dst) & ~0x00010000) | (((u32)(src)<<16) & 0x00010000))
/*	 Fields mbox_7_15	 */
#define MBOX_7_153_WIDTH                                                      1
#define MBOX_7_153_SHIFT                                                     15
#define MBOX_7_153_MASK                                              0x00008000
#define MBOX_7_153_RD(src)                           (((src) & 0x00008000)>>15)
#define MBOX_7_153_SET(dst,src) \
                      (((dst) & ~0x00008000) | (((u32)(src)<<15) & 0x00008000))
/*	 Fields mbox_7_14	 */
#define MBOX_7_143_WIDTH                                                      1
#define MBOX_7_143_SHIFT                                                     14
#define MBOX_7_143_MASK                                              0x00004000
#define MBOX_7_143_RD(src)                           (((src) & 0x00004000)>>14)
#define MBOX_7_143_SET(dst,src) \
                      (((dst) & ~0x00004000) | (((u32)(src)<<14) & 0x00004000))
/*	 Fields mbox_7_13	 */
#define MBOX_7_133_WIDTH                                                      1
#define MBOX_7_133_SHIFT                                                     13
#define MBOX_7_133_MASK                                              0x00002000
#define MBOX_7_133_RD(src)                           (((src) & 0x00002000)>>13)
#define MBOX_7_133_SET(dst,src) \
                      (((dst) & ~0x00002000) | (((u32)(src)<<13) & 0x00002000))
/*	 Fields mbox_7_12	 */
#define MBOX_7_123_WIDTH                                                      1
#define MBOX_7_123_SHIFT                                                     12
#define MBOX_7_123_MASK                                              0x00001000
#define MBOX_7_123_RD(src)                           (((src) & 0x00001000)>>12)
#define MBOX_7_123_SET(dst,src) \
                      (((dst) & ~0x00001000) | (((u32)(src)<<12) & 0x00001000))
/*	 Fields mbox_7_11	 */
#define MBOX_7_113_WIDTH                                                      1
#define MBOX_7_113_SHIFT                                                     11
#define MBOX_7_113_MASK                                              0x00000800
#define MBOX_7_113_RD(src)                           (((src) & 0x00000800)>>11)
#define MBOX_7_113_SET(dst,src) \
                      (((dst) & ~0x00000800) | (((u32)(src)<<11) & 0x00000800))
/*	 Fields mbox_7_10	 */
#define MBOX_7_103_WIDTH                                                      1
#define MBOX_7_103_SHIFT                                                     10
#define MBOX_7_103_MASK                                              0x00000400
#define MBOX_7_103_RD(src)                           (((src) & 0x00000400)>>10)
#define MBOX_7_103_SET(dst,src) \
                      (((dst) & ~0x00000400) | (((u32)(src)<<10) & 0x00000400))
/*	 Fields mbox_7_9	 */
#define MBOX_7_93_WIDTH                                                       1
#define MBOX_7_93_SHIFT                                                       9
#define MBOX_7_93_MASK                                               0x00000200
#define MBOX_7_93_RD(src)                             (((src) & 0x00000200)>>9)
#define MBOX_7_93_SET(dst,src) \
                       (((dst) & ~0x00000200) | (((u32)(src)<<9) & 0x00000200))
/*	 Fields mbox_7_8	 */
#define MBOX_7_83_WIDTH                                                       1
#define MBOX_7_83_SHIFT                                                       8
#define MBOX_7_83_MASK                                               0x00000100
#define MBOX_7_83_RD(src)                             (((src) & 0x00000100)>>8)
#define MBOX_7_83_SET(dst,src) \
                       (((dst) & ~0x00000100) | (((u32)(src)<<8) & 0x00000100))
/*	 Fields mbox_7_7	 */
#define MBOX_7_73_WIDTH                                                       1
#define MBOX_7_73_SHIFT                                                       7
#define MBOX_7_73_MASK                                               0x00000080
#define MBOX_7_73_RD(src)                             (((src) & 0x00000080)>>7)
#define MBOX_7_73_SET(dst,src) \
                       (((dst) & ~0x00000080) | (((u32)(src)<<7) & 0x00000080))
/*	 Fields mbox_7_6	 */
#define MBOX_7_63_WIDTH                                                       1
#define MBOX_7_63_SHIFT                                                       6
#define MBOX_7_63_MASK                                               0x00000040
#define MBOX_7_63_RD(src)                             (((src) & 0x00000040)>>6)
#define MBOX_7_63_SET(dst,src) \
                       (((dst) & ~0x00000040) | (((u32)(src)<<6) & 0x00000040))
/*	 Fields mbox_7_5	 */
#define MBOX_7_53_WIDTH                                                       1
#define MBOX_7_53_SHIFT                                                       5
#define MBOX_7_53_MASK                                               0x00000020
#define MBOX_7_53_RD(src)                             (((src) & 0x00000020)>>5)
#define MBOX_7_53_SET(dst,src) \
                       (((dst) & ~0x00000020) | (((u32)(src)<<5) & 0x00000020))
/*	 Fields mbox_7_4	 */
#define MBOX_7_43_WIDTH                                                       1
#define MBOX_7_43_SHIFT                                                       4
#define MBOX_7_43_MASK                                               0x00000010
#define MBOX_7_43_RD(src)                             (((src) & 0x00000010)>>4)
#define MBOX_7_43_SET(dst,src) \
                       (((dst) & ~0x00000010) | (((u32)(src)<<4) & 0x00000010))
/*	 Fields mbox_7_3	 */
#define MBOX_7_33_WIDTH                                                       1
#define MBOX_7_33_SHIFT                                                       3
#define MBOX_7_33_MASK                                               0x00000008
#define MBOX_7_33_RD(src)                             (((src) & 0x00000008)>>3)
#define MBOX_7_33_SET(dst,src) \
                       (((dst) & ~0x00000008) | (((u32)(src)<<3) & 0x00000008))
/*	 Fields mbox_7_2	 */
#define MBOX_7_23_WIDTH                                                       1
#define MBOX_7_23_SHIFT                                                       2
#define MBOX_7_23_MASK                                               0x00000004
#define MBOX_7_23_RD(src)                             (((src) & 0x00000004)>>2)
#define MBOX_7_23_SET(dst,src) \
                       (((dst) & ~0x00000004) | (((u32)(src)<<2) & 0x00000004))
/*	 Fields mbox_7_1	 */
#define MBOX_7_13_WIDTH                                                       1
#define MBOX_7_13_SHIFT                                                       1
#define MBOX_7_13_MASK                                               0x00000002
#define MBOX_7_13_RD(src)                             (((src) & 0x00000002)>>1)
#define MBOX_7_13_SET(dst,src) \
                       (((dst) & ~0x00000002) | (((u32)(src)<<1) & 0x00000002))
/*	 Fields mbox_7_0	 */
#define MBOX_7_03_WIDTH                                                       1
#define MBOX_7_03_SHIFT                                                       0
#define MBOX_7_03_MASK                                               0x00000001
#define MBOX_7_03_RD(src)                                (((src) & 0x00000001))
#define MBOX_7_03_SET(dst,src) \
                          (((dst) & ~0x00000001) | (((u32)(src)) & 0x00000001))

/*	Register csr_enq_status_4	*/ 
/*	 Fields mbox_8_15	 */
#define MBOX_8_154_WIDTH                                                      1
#define MBOX_8_154_SHIFT                                                     31
#define MBOX_8_154_MASK                                              0x80000000
#define MBOX_8_154_RD(src)                           (((src) & 0x80000000)>>31)
#define MBOX_8_154_SET(dst,src) \
                      (((dst) & ~0x80000000) | (((u32)(src)<<31) & 0x80000000))
/*	 Fields mbox_8_14	 */
#define MBOX_8_144_WIDTH                                                      1
#define MBOX_8_144_SHIFT                                                     30
#define MBOX_8_144_MASK                                              0x40000000
#define MBOX_8_144_RD(src)                           (((src) & 0x40000000)>>30)
#define MBOX_8_144_SET(dst,src) \
                      (((dst) & ~0x40000000) | (((u32)(src)<<30) & 0x40000000))
/*	 Fields mbox_8_13	 */
#define MBOX_8_134_WIDTH                                                      1
#define MBOX_8_134_SHIFT                                                     29
#define MBOX_8_134_MASK                                              0x20000000
#define MBOX_8_134_RD(src)                           (((src) & 0x20000000)>>29)
#define MBOX_8_134_SET(dst,src) \
                      (((dst) & ~0x20000000) | (((u32)(src)<<29) & 0x20000000))
/*	 Fields mbox_8_12	 */
#define MBOX_8_124_WIDTH                                                      1
#define MBOX_8_124_SHIFT                                                     28
#define MBOX_8_124_MASK                                              0x10000000
#define MBOX_8_124_RD(src)                           (((src) & 0x10000000)>>28)
#define MBOX_8_124_SET(dst,src) \
                      (((dst) & ~0x10000000) | (((u32)(src)<<28) & 0x10000000))
/*	 Fields mbox_8_11	 */
#define MBOX_8_114_WIDTH                                                      1
#define MBOX_8_114_SHIFT                                                     27
#define MBOX_8_114_MASK                                              0x08000000
#define MBOX_8_114_RD(src)                           (((src) & 0x08000000)>>27)
#define MBOX_8_114_SET(dst,src) \
                      (((dst) & ~0x08000000) | (((u32)(src)<<27) & 0x08000000))
/*	 Fields mbox_8_10	 */
#define MBOX_8_104_WIDTH                                                      1
#define MBOX_8_104_SHIFT                                                     26
#define MBOX_8_104_MASK                                              0x04000000
#define MBOX_8_104_RD(src)                           (((src) & 0x04000000)>>26)
#define MBOX_8_104_SET(dst,src) \
                      (((dst) & ~0x04000000) | (((u32)(src)<<26) & 0x04000000))
/*	 Fields mbox_8_9	 */
#define MBOX_8_94_WIDTH                                                       1
#define MBOX_8_94_SHIFT                                                      25
#define MBOX_8_94_MASK                                               0x02000000
#define MBOX_8_94_RD(src)                            (((src) & 0x02000000)>>25)
#define MBOX_8_94_SET(dst,src) \
                      (((dst) & ~0x02000000) | (((u32)(src)<<25) & 0x02000000))
/*	 Fields mbox_8_8	 */
#define MBOX_8_84_WIDTH                                                       1
#define MBOX_8_84_SHIFT                                                      24
#define MBOX_8_84_MASK                                               0x01000000
#define MBOX_8_84_RD(src)                            (((src) & 0x01000000)>>24)
#define MBOX_8_84_SET(dst,src) \
                      (((dst) & ~0x01000000) | (((u32)(src)<<24) & 0x01000000))
/*	 Fields mbox_8_7	 */
#define MBOX_8_74_WIDTH                                                       1
#define MBOX_8_74_SHIFT                                                      23
#define MBOX_8_74_MASK                                               0x00800000
#define MBOX_8_74_RD(src)                            (((src) & 0x00800000)>>23)
#define MBOX_8_74_SET(dst,src) \
                      (((dst) & ~0x00800000) | (((u32)(src)<<23) & 0x00800000))
/*	 Fields mbox_8_6	 */
#define MBOX_8_64_WIDTH                                                       1
#define MBOX_8_64_SHIFT                                                      22
#define MBOX_8_64_MASK                                               0x00400000
#define MBOX_8_64_RD(src)                            (((src) & 0x00400000)>>22)
#define MBOX_8_64_SET(dst,src) \
                      (((dst) & ~0x00400000) | (((u32)(src)<<22) & 0x00400000))
/*	 Fields mbox_8_5	 */
#define MBOX_8_54_WIDTH                                                       1
#define MBOX_8_54_SHIFT                                                      21
#define MBOX_8_54_MASK                                               0x00200000
#define MBOX_8_54_RD(src)                            (((src) & 0x00200000)>>21)
#define MBOX_8_54_SET(dst,src) \
                      (((dst) & ~0x00200000) | (((u32)(src)<<21) & 0x00200000))
/*	 Fields mbox_8_4	 */
#define MBOX_8_44_WIDTH                                                       1
#define MBOX_8_44_SHIFT                                                      20
#define MBOX_8_44_MASK                                               0x00100000
#define MBOX_8_44_RD(src)                            (((src) & 0x00100000)>>20)
#define MBOX_8_44_SET(dst,src) \
                      (((dst) & ~0x00100000) | (((u32)(src)<<20) & 0x00100000))
/*	 Fields mbox_8_3	 */
#define MBOX_8_34_WIDTH                                                       1
#define MBOX_8_34_SHIFT                                                      19
#define MBOX_8_34_MASK                                               0x00080000
#define MBOX_8_34_RD(src)                            (((src) & 0x00080000)>>19)
#define MBOX_8_34_SET(dst,src) \
                      (((dst) & ~0x00080000) | (((u32)(src)<<19) & 0x00080000))
/*	 Fields mbox_8_2	 */
#define MBOX_8_24_WIDTH                                                       1
#define MBOX_8_24_SHIFT                                                      18
#define MBOX_8_24_MASK                                               0x00040000
#define MBOX_8_24_RD(src)                            (((src) & 0x00040000)>>18)
#define MBOX_8_24_SET(dst,src) \
                      (((dst) & ~0x00040000) | (((u32)(src)<<18) & 0x00040000))
/*	 Fields mbox_8_1	 */
#define MBOX_8_14_WIDTH                                                       1
#define MBOX_8_14_SHIFT                                                      17
#define MBOX_8_14_MASK                                               0x00020000
#define MBOX_8_14_RD(src)                            (((src) & 0x00020000)>>17)
#define MBOX_8_14_SET(dst,src) \
                      (((dst) & ~0x00020000) | (((u32)(src)<<17) & 0x00020000))
/*	 Fields mbox_8_0	 */
#define MBOX_8_04_WIDTH                                                       1
#define MBOX_8_04_SHIFT                                                      16
#define MBOX_8_04_MASK                                               0x00010000
#define MBOX_8_04_RD(src)                            (((src) & 0x00010000)>>16)
#define MBOX_8_04_SET(dst,src) \
                      (((dst) & ~0x00010000) | (((u32)(src)<<16) & 0x00010000))
/*	 Fields mbox_9_15	 */
#define MBOX_9_154_WIDTH                                                      1
#define MBOX_9_154_SHIFT                                                     15
#define MBOX_9_154_MASK                                              0x00008000
#define MBOX_9_154_RD(src)                           (((src) & 0x00008000)>>15)
#define MBOX_9_154_SET(dst,src) \
                      (((dst) & ~0x00008000) | (((u32)(src)<<15) & 0x00008000))
/*	 Fields mbox_9_14	 */
#define MBOX_9_144_WIDTH                                                      1
#define MBOX_9_144_SHIFT                                                     14
#define MBOX_9_144_MASK                                              0x00004000
#define MBOX_9_144_RD(src)                           (((src) & 0x00004000)>>14)
#define MBOX_9_144_SET(dst,src) \
                      (((dst) & ~0x00004000) | (((u32)(src)<<14) & 0x00004000))
/*	 Fields mbox_9_13	 */
#define MBOX_9_134_WIDTH                                                      1
#define MBOX_9_134_SHIFT                                                     13
#define MBOX_9_134_MASK                                              0x00002000
#define MBOX_9_134_RD(src)                           (((src) & 0x00002000)>>13)
#define MBOX_9_134_SET(dst,src) \
                      (((dst) & ~0x00002000) | (((u32)(src)<<13) & 0x00002000))
/*	 Fields mbox_9_12	 */
#define MBOX_9_124_WIDTH                                                      1
#define MBOX_9_124_SHIFT                                                     12
#define MBOX_9_124_MASK                                              0x00001000
#define MBOX_9_124_RD(src)                           (((src) & 0x00001000)>>12)
#define MBOX_9_124_SET(dst,src) \
                      (((dst) & ~0x00001000) | (((u32)(src)<<12) & 0x00001000))
/*	 Fields mbox_9_11	 */
#define MBOX_9_114_WIDTH                                                      1
#define MBOX_9_114_SHIFT                                                     11
#define MBOX_9_114_MASK                                              0x00000800
#define MBOX_9_114_RD(src)                           (((src) & 0x00000800)>>11)
#define MBOX_9_114_SET(dst,src) \
                      (((dst) & ~0x00000800) | (((u32)(src)<<11) & 0x00000800))
/*	 Fields mbox_9_10	 */
#define MBOX_9_104_WIDTH                                                      1
#define MBOX_9_104_SHIFT                                                     10
#define MBOX_9_104_MASK                                              0x00000400
#define MBOX_9_104_RD(src)                           (((src) & 0x00000400)>>10)
#define MBOX_9_104_SET(dst,src) \
                      (((dst) & ~0x00000400) | (((u32)(src)<<10) & 0x00000400))
/*	 Fields mbox_9_9	 */
#define MBOX_9_94_WIDTH                                                       1
#define MBOX_9_94_SHIFT                                                       9
#define MBOX_9_94_MASK                                               0x00000200
#define MBOX_9_94_RD(src)                             (((src) & 0x00000200)>>9)
#define MBOX_9_94_SET(dst,src) \
                       (((dst) & ~0x00000200) | (((u32)(src)<<9) & 0x00000200))
/*	 Fields mbox_9_8	 */
#define MBOX_9_84_WIDTH                                                       1
#define MBOX_9_84_SHIFT                                                       8
#define MBOX_9_84_MASK                                               0x00000100
#define MBOX_9_84_RD(src)                             (((src) & 0x00000100)>>8)
#define MBOX_9_84_SET(dst,src) \
                       (((dst) & ~0x00000100) | (((u32)(src)<<8) & 0x00000100))
/*	 Fields mbox_9_7	 */
#define MBOX_9_74_WIDTH                                                       1
#define MBOX_9_74_SHIFT                                                       7
#define MBOX_9_74_MASK                                               0x00000080
#define MBOX_9_74_RD(src)                             (((src) & 0x00000080)>>7)
#define MBOX_9_74_SET(dst,src) \
                       (((dst) & ~0x00000080) | (((u32)(src)<<7) & 0x00000080))
/*	 Fields mbox_9_6	 */
#define MBOX_9_64_WIDTH                                                       1
#define MBOX_9_64_SHIFT                                                       6
#define MBOX_9_64_MASK                                               0x00000040
#define MBOX_9_64_RD(src)                             (((src) & 0x00000040)>>6)
#define MBOX_9_64_SET(dst,src) \
                       (((dst) & ~0x00000040) | (((u32)(src)<<6) & 0x00000040))
/*	 Fields mbox_9_5	 */
#define MBOX_9_54_WIDTH                                                       1
#define MBOX_9_54_SHIFT                                                       5
#define MBOX_9_54_MASK                                               0x00000020
#define MBOX_9_54_RD(src)                             (((src) & 0x00000020)>>5)
#define MBOX_9_54_SET(dst,src) \
                       (((dst) & ~0x00000020) | (((u32)(src)<<5) & 0x00000020))
/*	 Fields mbox_9_4	 */
#define MBOX_9_44_WIDTH                                                       1
#define MBOX_9_44_SHIFT                                                       4
#define MBOX_9_44_MASK                                               0x00000010
#define MBOX_9_44_RD(src)                             (((src) & 0x00000010)>>4)
#define MBOX_9_44_SET(dst,src) \
                       (((dst) & ~0x00000010) | (((u32)(src)<<4) & 0x00000010))
/*	 Fields mbox_9_3	 */
#define MBOX_9_34_WIDTH                                                       1
#define MBOX_9_34_SHIFT                                                       3
#define MBOX_9_34_MASK                                               0x00000008
#define MBOX_9_34_RD(src)                             (((src) & 0x00000008)>>3)
#define MBOX_9_34_SET(dst,src) \
                       (((dst) & ~0x00000008) | (((u32)(src)<<3) & 0x00000008))
/*	 Fields mbox_9_2	 */
#define MBOX_9_24_WIDTH                                                       1
#define MBOX_9_24_SHIFT                                                       2
#define MBOX_9_24_MASK                                               0x00000004
#define MBOX_9_24_RD(src)                             (((src) & 0x00000004)>>2)
#define MBOX_9_24_SET(dst,src) \
                       (((dst) & ~0x00000004) | (((u32)(src)<<2) & 0x00000004))
/*	 Fields mbox_9_1	 */
#define MBOX_9_14_WIDTH                                                       1
#define MBOX_9_14_SHIFT                                                       1
#define MBOX_9_14_MASK                                               0x00000002
#define MBOX_9_14_RD(src)                             (((src) & 0x00000002)>>1)
#define MBOX_9_14_SET(dst,src) \
                       (((dst) & ~0x00000002) | (((u32)(src)<<1) & 0x00000002))
/*	 Fields mbox_9_0	 */
#define MBOX_9_04_WIDTH                                                       1
#define MBOX_9_04_SHIFT                                                       0
#define MBOX_9_04_MASK                                               0x00000001
#define MBOX_9_04_RD(src)                                (((src) & 0x00000001))
#define MBOX_9_04_SET(dst,src) \
                          (((dst) & ~0x00000001) | (((u32)(src)) & 0x00000001))

/*	Register csr_enq_status_5	*/ 
/*	 Fields mbox_10_15	 */
#define MBOX_10_155_WIDTH                                                     1
#define MBOX_10_155_SHIFT                                                    31
#define MBOX_10_155_MASK                                             0x80000000
#define MBOX_10_155_RD(src)                          (((src) & 0x80000000)>>31)
#define MBOX_10_155_SET(dst,src) \
                      (((dst) & ~0x80000000) | (((u32)(src)<<31) & 0x80000000))
/*	 Fields mbox_10_14	 */
#define MBOX_10_145_WIDTH                                                     1
#define MBOX_10_145_SHIFT                                                    30
#define MBOX_10_145_MASK                                             0x40000000
#define MBOX_10_145_RD(src)                          (((src) & 0x40000000)>>30)
#define MBOX_10_145_SET(dst,src) \
                      (((dst) & ~0x40000000) | (((u32)(src)<<30) & 0x40000000))
/*	 Fields mbox_10_13	 */
#define MBOX_10_135_WIDTH                                                     1
#define MBOX_10_135_SHIFT                                                    29
#define MBOX_10_135_MASK                                             0x20000000
#define MBOX_10_135_RD(src)                          (((src) & 0x20000000)>>29)
#define MBOX_10_135_SET(dst,src) \
                      (((dst) & ~0x20000000) | (((u32)(src)<<29) & 0x20000000))
/*	 Fields mbox_10_12	 */
#define MBOX_10_125_WIDTH                                                     1
#define MBOX_10_125_SHIFT                                                    28
#define MBOX_10_125_MASK                                             0x10000000
#define MBOX_10_125_RD(src)                          (((src) & 0x10000000)>>28)
#define MBOX_10_125_SET(dst,src) \
                      (((dst) & ~0x10000000) | (((u32)(src)<<28) & 0x10000000))
/*	 Fields mbox_10_11	 */
#define MBOX_10_115_WIDTH                                                     1
#define MBOX_10_115_SHIFT                                                    27
#define MBOX_10_115_MASK                                             0x08000000
#define MBOX_10_115_RD(src)                          (((src) & 0x08000000)>>27)
#define MBOX_10_115_SET(dst,src) \
                      (((dst) & ~0x08000000) | (((u32)(src)<<27) & 0x08000000))
/*	 Fields mbox_10_10	 */
#define MBOX_10_105_WIDTH                                                     1
#define MBOX_10_105_SHIFT                                                    26
#define MBOX_10_105_MASK                                             0x04000000
#define MBOX_10_105_RD(src)                          (((src) & 0x04000000)>>26)
#define MBOX_10_105_SET(dst,src) \
                      (((dst) & ~0x04000000) | (((u32)(src)<<26) & 0x04000000))
/*	 Fields mbox_10_9	 */
#define MBOX_10_95_WIDTH                                                      1
#define MBOX_10_95_SHIFT                                                     25
#define MBOX_10_95_MASK                                              0x02000000
#define MBOX_10_95_RD(src)                           (((src) & 0x02000000)>>25)
#define MBOX_10_95_SET(dst,src) \
                      (((dst) & ~0x02000000) | (((u32)(src)<<25) & 0x02000000))
/*	 Fields mbox_10_8	 */
#define MBOX_10_85_WIDTH                                                      1
#define MBOX_10_85_SHIFT                                                     24
#define MBOX_10_85_MASK                                              0x01000000
#define MBOX_10_85_RD(src)                           (((src) & 0x01000000)>>24)
#define MBOX_10_85_SET(dst,src) \
                      (((dst) & ~0x01000000) | (((u32)(src)<<24) & 0x01000000))
/*	 Fields mbox_10_7	 */
#define MBOX_10_75_WIDTH                                                      1
#define MBOX_10_75_SHIFT                                                     23
#define MBOX_10_75_MASK                                              0x00800000
#define MBOX_10_75_RD(src)                           (((src) & 0x00800000)>>23)
#define MBOX_10_75_SET(dst,src) \
                      (((dst) & ~0x00800000) | (((u32)(src)<<23) & 0x00800000))
/*	 Fields mbox_10_6	 */
#define MBOX_10_65_WIDTH                                                      1
#define MBOX_10_65_SHIFT                                                     22
#define MBOX_10_65_MASK                                              0x00400000
#define MBOX_10_65_RD(src)                           (((src) & 0x00400000)>>22)
#define MBOX_10_65_SET(dst,src) \
                      (((dst) & ~0x00400000) | (((u32)(src)<<22) & 0x00400000))
/*	 Fields mbox_10_5	 */
#define MBOX_10_55_WIDTH                                                      1
#define MBOX_10_55_SHIFT                                                     21
#define MBOX_10_55_MASK                                              0x00200000
#define MBOX_10_55_RD(src)                           (((src) & 0x00200000)>>21)
#define MBOX_10_55_SET(dst,src) \
                      (((dst) & ~0x00200000) | (((u32)(src)<<21) & 0x00200000))
/*	 Fields mbox_10_4	 */
#define MBOX_10_45_WIDTH                                                      1
#define MBOX_10_45_SHIFT                                                     20
#define MBOX_10_45_MASK                                              0x00100000
#define MBOX_10_45_RD(src)                           (((src) & 0x00100000)>>20)
#define MBOX_10_45_SET(dst,src) \
                      (((dst) & ~0x00100000) | (((u32)(src)<<20) & 0x00100000))
/*	 Fields mbox_10_3	 */
#define MBOX_10_35_WIDTH                                                      1
#define MBOX_10_35_SHIFT                                                     19
#define MBOX_10_35_MASK                                              0x00080000
#define MBOX_10_35_RD(src)                           (((src) & 0x00080000)>>19)
#define MBOX_10_35_SET(dst,src) \
                      (((dst) & ~0x00080000) | (((u32)(src)<<19) & 0x00080000))
/*	 Fields mbox_10_2	 */
#define MBOX_10_25_WIDTH                                                      1
#define MBOX_10_25_SHIFT                                                     18
#define MBOX_10_25_MASK                                              0x00040000
#define MBOX_10_25_RD(src)                           (((src) & 0x00040000)>>18)
#define MBOX_10_25_SET(dst,src) \
                      (((dst) & ~0x00040000) | (((u32)(src)<<18) & 0x00040000))
/*	 Fields mbox_10_1	 */
#define MBOX_10_15_WIDTH                                                      1
#define MBOX_10_15_SHIFT                                                     17
#define MBOX_10_15_MASK                                              0x00020000
#define MBOX_10_15_RD(src)                           (((src) & 0x00020000)>>17)
#define MBOX_10_15_SET(dst,src) \
                      (((dst) & ~0x00020000) | (((u32)(src)<<17) & 0x00020000))
/*	 Fields mbox_10_0	 */
#define MBOX_10_05_WIDTH                                                      1
#define MBOX_10_05_SHIFT                                                     16
#define MBOX_10_05_MASK                                              0x00010000
#define MBOX_10_05_RD(src)                           (((src) & 0x00010000)>>16)
#define MBOX_10_05_SET(dst,src) \
                      (((dst) & ~0x00010000) | (((u32)(src)<<16) & 0x00010000))
/*	 Fields mbox_11_15	 */
#define MBOX_11_155_WIDTH                                                     1
#define MBOX_11_155_SHIFT                                                    15
#define MBOX_11_155_MASK                                             0x00008000
#define MBOX_11_155_RD(src)                          (((src) & 0x00008000)>>15)
#define MBOX_11_155_SET(dst,src) \
                      (((dst) & ~0x00008000) | (((u32)(src)<<15) & 0x00008000))
/*	 Fields mbox_11_14	 */
#define MBOX_11_145_WIDTH                                                     1
#define MBOX_11_145_SHIFT                                                    14
#define MBOX_11_145_MASK                                             0x00004000
#define MBOX_11_145_RD(src)                          (((src) & 0x00004000)>>14)
#define MBOX_11_145_SET(dst,src) \
                      (((dst) & ~0x00004000) | (((u32)(src)<<14) & 0x00004000))
/*	 Fields mbox_11_13	 */
#define MBOX_11_135_WIDTH                                                     1
#define MBOX_11_135_SHIFT                                                    13
#define MBOX_11_135_MASK                                             0x00002000
#define MBOX_11_135_RD(src)                          (((src) & 0x00002000)>>13)
#define MBOX_11_135_SET(dst,src) \
                      (((dst) & ~0x00002000) | (((u32)(src)<<13) & 0x00002000))
/*	 Fields mbox_11_12	 */
#define MBOX_11_125_WIDTH                                                     1
#define MBOX_11_125_SHIFT                                                    12
#define MBOX_11_125_MASK                                             0x00001000
#define MBOX_11_125_RD(src)                          (((src) & 0x00001000)>>12)
#define MBOX_11_125_SET(dst,src) \
                      (((dst) & ~0x00001000) | (((u32)(src)<<12) & 0x00001000))
/*	 Fields mbox_11_11	 */
#define MBOX_11_115_WIDTH                                                     1
#define MBOX_11_115_SHIFT                                                    11
#define MBOX_11_115_MASK                                             0x00000800
#define MBOX_11_115_RD(src)                          (((src) & 0x00000800)>>11)
#define MBOX_11_115_SET(dst,src) \
                      (((dst) & ~0x00000800) | (((u32)(src)<<11) & 0x00000800))
/*	 Fields mbox_11_10	 */
#define MBOX_11_105_WIDTH                                                     1
#define MBOX_11_105_SHIFT                                                    10
#define MBOX_11_105_MASK                                             0x00000400
#define MBOX_11_105_RD(src)                          (((src) & 0x00000400)>>10)
#define MBOX_11_105_SET(dst,src) \
                      (((dst) & ~0x00000400) | (((u32)(src)<<10) & 0x00000400))
/*	 Fields mbox_11_9	 */
#define MBOX_11_95_WIDTH                                                      1
#define MBOX_11_95_SHIFT                                                      9
#define MBOX_11_95_MASK                                              0x00000200
#define MBOX_11_95_RD(src)                            (((src) & 0x00000200)>>9)
#define MBOX_11_95_SET(dst,src) \
                       (((dst) & ~0x00000200) | (((u32)(src)<<9) & 0x00000200))
/*	 Fields mbox_11_8	 */
#define MBOX_11_85_WIDTH                                                      1
#define MBOX_11_85_SHIFT                                                      8
#define MBOX_11_85_MASK                                              0x00000100
#define MBOX_11_85_RD(src)                            (((src) & 0x00000100)>>8)
#define MBOX_11_85_SET(dst,src) \
                       (((dst) & ~0x00000100) | (((u32)(src)<<8) & 0x00000100))
/*	 Fields mbox_11_7	 */
#define MBOX_11_75_WIDTH                                                      1
#define MBOX_11_75_SHIFT                                                      7
#define MBOX_11_75_MASK                                              0x00000080
#define MBOX_11_75_RD(src)                            (((src) & 0x00000080)>>7)
#define MBOX_11_75_SET(dst,src) \
                       (((dst) & ~0x00000080) | (((u32)(src)<<7) & 0x00000080))
/*	 Fields mbox_11_6	 */
#define MBOX_11_65_WIDTH                                                      1
#define MBOX_11_65_SHIFT                                                      6
#define MBOX_11_65_MASK                                              0x00000040
#define MBOX_11_65_RD(src)                            (((src) & 0x00000040)>>6)
#define MBOX_11_65_SET(dst,src) \
                       (((dst) & ~0x00000040) | (((u32)(src)<<6) & 0x00000040))
/*	 Fields mbox_11_5	 */
#define MBOX_11_55_WIDTH                                                      1
#define MBOX_11_55_SHIFT                                                      5
#define MBOX_11_55_MASK                                              0x00000020
#define MBOX_11_55_RD(src)                            (((src) & 0x00000020)>>5)
#define MBOX_11_55_SET(dst,src) \
                       (((dst) & ~0x00000020) | (((u32)(src)<<5) & 0x00000020))
/*	 Fields mbox_11_4	 */
#define MBOX_11_45_WIDTH                                                      1
#define MBOX_11_45_SHIFT                                                      4
#define MBOX_11_45_MASK                                              0x00000010
#define MBOX_11_45_RD(src)                            (((src) & 0x00000010)>>4)
#define MBOX_11_45_SET(dst,src) \
                       (((dst) & ~0x00000010) | (((u32)(src)<<4) & 0x00000010))
/*	 Fields mbox_11_3	 */
#define MBOX_11_35_WIDTH                                                      1
#define MBOX_11_35_SHIFT                                                      3
#define MBOX_11_35_MASK                                              0x00000008
#define MBOX_11_35_RD(src)                            (((src) & 0x00000008)>>3)
#define MBOX_11_35_SET(dst,src) \
                       (((dst) & ~0x00000008) | (((u32)(src)<<3) & 0x00000008))
/*	 Fields mbox_11_2	 */
#define MBOX_11_25_WIDTH                                                      1
#define MBOX_11_25_SHIFT                                                      2
#define MBOX_11_25_MASK                                              0x00000004
#define MBOX_11_25_RD(src)                            (((src) & 0x00000004)>>2)
#define MBOX_11_25_SET(dst,src) \
                       (((dst) & ~0x00000004) | (((u32)(src)<<2) & 0x00000004))
/*	 Fields mbox_11_1	 */
#define MBOX_11_15_WIDTH                                                      1
#define MBOX_11_15_SHIFT                                                      1
#define MBOX_11_15_MASK                                              0x00000002
#define MBOX_11_15_RD(src)                            (((src) & 0x00000002)>>1)
#define MBOX_11_15_SET(dst,src) \
                       (((dst) & ~0x00000002) | (((u32)(src)<<1) & 0x00000002))
/*	 Fields mbox_11_0	 */
#define MBOX_11_05_WIDTH                                                      1
#define MBOX_11_05_SHIFT                                                      0
#define MBOX_11_05_MASK                                              0x00000001
#define MBOX_11_05_RD(src)                               (((src) & 0x00000001))
#define MBOX_11_05_SET(dst,src) \
                          (((dst) & ~0x00000001) | (((u32)(src)) & 0x00000001))

/*	Register csr_enq_status_6	*/ 
/*	 Fields mbox_12_15	 */
#define MBOX_12_156_WIDTH                                                     1
#define MBOX_12_156_SHIFT                                                    31
#define MBOX_12_156_MASK                                             0x80000000
#define MBOX_12_156_RD(src)                          (((src) & 0x80000000)>>31)
#define MBOX_12_156_SET(dst,src) \
                      (((dst) & ~0x80000000) | (((u32)(src)<<31) & 0x80000000))
/*	 Fields mbox_12_14	 */
#define MBOX_12_146_WIDTH                                                     1
#define MBOX_12_146_SHIFT                                                    30
#define MBOX_12_146_MASK                                             0x40000000
#define MBOX_12_146_RD(src)                          (((src) & 0x40000000)>>30)
#define MBOX_12_146_SET(dst,src) \
                      (((dst) & ~0x40000000) | (((u32)(src)<<30) & 0x40000000))
/*	 Fields mbox_12_13	 */
#define MBOX_12_136_WIDTH                                                     1
#define MBOX_12_136_SHIFT                                                    29
#define MBOX_12_136_MASK                                             0x20000000
#define MBOX_12_136_RD(src)                          (((src) & 0x20000000)>>29)
#define MBOX_12_136_SET(dst,src) \
                      (((dst) & ~0x20000000) | (((u32)(src)<<29) & 0x20000000))
/*	 Fields mbox_12_12	 */
#define MBOX_12_126_WIDTH                                                     1
#define MBOX_12_126_SHIFT                                                    28
#define MBOX_12_126_MASK                                             0x10000000
#define MBOX_12_126_RD(src)                          (((src) & 0x10000000)>>28)
#define MBOX_12_126_SET(dst,src) \
                      (((dst) & ~0x10000000) | (((u32)(src)<<28) & 0x10000000))
/*	 Fields mbox_12_11	 */
#define MBOX_12_116_WIDTH                                                     1
#define MBOX_12_116_SHIFT                                                    27
#define MBOX_12_116_MASK                                             0x08000000
#define MBOX_12_116_RD(src)                          (((src) & 0x08000000)>>27)
#define MBOX_12_116_SET(dst,src) \
                      (((dst) & ~0x08000000) | (((u32)(src)<<27) & 0x08000000))
/*	 Fields mbox_12_10	 */
#define MBOX_12_106_WIDTH                                                     1
#define MBOX_12_106_SHIFT                                                    26
#define MBOX_12_106_MASK                                             0x04000000
#define MBOX_12_106_RD(src)                          (((src) & 0x04000000)>>26)
#define MBOX_12_106_SET(dst,src) \
                      (((dst) & ~0x04000000) | (((u32)(src)<<26) & 0x04000000))
/*	 Fields mbox_12_9	 */
#define MBOX_12_96_WIDTH                                                      1
#define MBOX_12_96_SHIFT                                                     25
#define MBOX_12_96_MASK                                              0x02000000
#define MBOX_12_96_RD(src)                           (((src) & 0x02000000)>>25)
#define MBOX_12_96_SET(dst,src) \
                      (((dst) & ~0x02000000) | (((u32)(src)<<25) & 0x02000000))
/*	 Fields mbox_12_8	 */
#define MBOX_12_86_WIDTH                                                      1
#define MBOX_12_86_SHIFT                                                     24
#define MBOX_12_86_MASK                                              0x01000000
#define MBOX_12_86_RD(src)                           (((src) & 0x01000000)>>24)
#define MBOX_12_86_SET(dst,src) \
                      (((dst) & ~0x01000000) | (((u32)(src)<<24) & 0x01000000))
/*	 Fields mbox_12_7	 */
#define MBOX_12_76_WIDTH                                                      1
#define MBOX_12_76_SHIFT                                                     23
#define MBOX_12_76_MASK                                              0x00800000
#define MBOX_12_76_RD(src)                           (((src) & 0x00800000)>>23)
#define MBOX_12_76_SET(dst,src) \
                      (((dst) & ~0x00800000) | (((u32)(src)<<23) & 0x00800000))
/*	 Fields mbox_12_6	 */
#define MBOX_12_66_WIDTH                                                      1
#define MBOX_12_66_SHIFT                                                     22
#define MBOX_12_66_MASK                                              0x00400000
#define MBOX_12_66_RD(src)                           (((src) & 0x00400000)>>22)
#define MBOX_12_66_SET(dst,src) \
                      (((dst) & ~0x00400000) | (((u32)(src)<<22) & 0x00400000))
/*	 Fields mbox_12_5	 */
#define MBOX_12_56_WIDTH                                                      1
#define MBOX_12_56_SHIFT                                                     21
#define MBOX_12_56_MASK                                              0x00200000
#define MBOX_12_56_RD(src)                           (((src) & 0x00200000)>>21)
#define MBOX_12_56_SET(dst,src) \
                      (((dst) & ~0x00200000) | (((u32)(src)<<21) & 0x00200000))
/*	 Fields mbox_12_4	 */
#define MBOX_12_46_WIDTH                                                      1
#define MBOX_12_46_SHIFT                                                     20
#define MBOX_12_46_MASK                                              0x00100000
#define MBOX_12_46_RD(src)                           (((src) & 0x00100000)>>20)
#define MBOX_12_46_SET(dst,src) \
                      (((dst) & ~0x00100000) | (((u32)(src)<<20) & 0x00100000))
/*	 Fields mbox_12_3	 */
#define MBOX_12_36_WIDTH                                                      1
#define MBOX_12_36_SHIFT                                                     19
#define MBOX_12_36_MASK                                              0x00080000
#define MBOX_12_36_RD(src)                           (((src) & 0x00080000)>>19)
#define MBOX_12_36_SET(dst,src) \
                      (((dst) & ~0x00080000) | (((u32)(src)<<19) & 0x00080000))
/*	 Fields mbox_12_2	 */
#define MBOX_12_26_WIDTH                                                      1
#define MBOX_12_26_SHIFT                                                     18
#define MBOX_12_26_MASK                                              0x00040000
#define MBOX_12_26_RD(src)                           (((src) & 0x00040000)>>18)
#define MBOX_12_26_SET(dst,src) \
                      (((dst) & ~0x00040000) | (((u32)(src)<<18) & 0x00040000))
/*	 Fields mbox_12_1	 */
#define MBOX_12_16_WIDTH                                                      1
#define MBOX_12_16_SHIFT                                                     17
#define MBOX_12_16_MASK                                              0x00020000
#define MBOX_12_16_RD(src)                           (((src) & 0x00020000)>>17)
#define MBOX_12_16_SET(dst,src) \
                      (((dst) & ~0x00020000) | (((u32)(src)<<17) & 0x00020000))
/*	 Fields mbox_12_0	 */
#define MBOX_12_06_WIDTH                                                      1
#define MBOX_12_06_SHIFT                                                     16
#define MBOX_12_06_MASK                                              0x00010000
#define MBOX_12_06_RD(src)                           (((src) & 0x00010000)>>16)
#define MBOX_12_06_SET(dst,src) \
                      (((dst) & ~0x00010000) | (((u32)(src)<<16) & 0x00010000))
/*	 Fields mbox_13_15	 */
#define MBOX_13_156_WIDTH                                                     1
#define MBOX_13_156_SHIFT                                                    15
#define MBOX_13_156_MASK                                             0x00008000
#define MBOX_13_156_RD(src)                          (((src) & 0x00008000)>>15)
#define MBOX_13_156_SET(dst,src) \
                      (((dst) & ~0x00008000) | (((u32)(src)<<15) & 0x00008000))
/*	 Fields mbox_13_14	 */
#define MBOX_13_146_WIDTH                                                     1
#define MBOX_13_146_SHIFT                                                    14
#define MBOX_13_146_MASK                                             0x00004000
#define MBOX_13_146_RD(src)                          (((src) & 0x00004000)>>14)
#define MBOX_13_146_SET(dst,src) \
                      (((dst) & ~0x00004000) | (((u32)(src)<<14) & 0x00004000))
/*	 Fields mbox_13_13	 */
#define MBOX_13_136_WIDTH                                                     1
#define MBOX_13_136_SHIFT                                                    13
#define MBOX_13_136_MASK                                             0x00002000
#define MBOX_13_136_RD(src)                          (((src) & 0x00002000)>>13)
#define MBOX_13_136_SET(dst,src) \
                      (((dst) & ~0x00002000) | (((u32)(src)<<13) & 0x00002000))
/*	 Fields mbox_13_12	 */
#define MBOX_13_126_WIDTH                                                     1
#define MBOX_13_126_SHIFT                                                    12
#define MBOX_13_126_MASK                                             0x00001000
#define MBOX_13_126_RD(src)                          (((src) & 0x00001000)>>12)
#define MBOX_13_126_SET(dst,src) \
                      (((dst) & ~0x00001000) | (((u32)(src)<<12) & 0x00001000))
/*	 Fields mbox_13_11	 */
#define MBOX_13_116_WIDTH                                                     1
#define MBOX_13_116_SHIFT                                                    11
#define MBOX_13_116_MASK                                             0x00000800
#define MBOX_13_116_RD(src)                          (((src) & 0x00000800)>>11)
#define MBOX_13_116_SET(dst,src) \
                      (((dst) & ~0x00000800) | (((u32)(src)<<11) & 0x00000800))
/*	 Fields mbox_13_10	 */
#define MBOX_13_106_WIDTH                                                     1
#define MBOX_13_106_SHIFT                                                    10
#define MBOX_13_106_MASK                                             0x00000400
#define MBOX_13_106_RD(src)                          (((src) & 0x00000400)>>10)
#define MBOX_13_106_SET(dst,src) \
                      (((dst) & ~0x00000400) | (((u32)(src)<<10) & 0x00000400))
/*	 Fields mbox_13_9	 */
#define MBOX_13_96_WIDTH                                                      1
#define MBOX_13_96_SHIFT                                                      9
#define MBOX_13_96_MASK                                              0x00000200
#define MBOX_13_96_RD(src)                            (((src) & 0x00000200)>>9)
#define MBOX_13_96_SET(dst,src) \
                       (((dst) & ~0x00000200) | (((u32)(src)<<9) & 0x00000200))
/*	 Fields mbox_13_8	 */
#define MBOX_13_86_WIDTH                                                      1
#define MBOX_13_86_SHIFT                                                      8
#define MBOX_13_86_MASK                                              0x00000100
#define MBOX_13_86_RD(src)                            (((src) & 0x00000100)>>8)
#define MBOX_13_86_SET(dst,src) \
                       (((dst) & ~0x00000100) | (((u32)(src)<<8) & 0x00000100))
/*	 Fields mbox_13_7	 */
#define MBOX_13_76_WIDTH                                                      1
#define MBOX_13_76_SHIFT                                                      7
#define MBOX_13_76_MASK                                              0x00000080
#define MBOX_13_76_RD(src)                            (((src) & 0x00000080)>>7)
#define MBOX_13_76_SET(dst,src) \
                       (((dst) & ~0x00000080) | (((u32)(src)<<7) & 0x00000080))
/*	 Fields mbox_13_6	 */
#define MBOX_13_66_WIDTH                                                      1
#define MBOX_13_66_SHIFT                                                      6
#define MBOX_13_66_MASK                                              0x00000040
#define MBOX_13_66_RD(src)                            (((src) & 0x00000040)>>6)
#define MBOX_13_66_SET(dst,src) \
                       (((dst) & ~0x00000040) | (((u32)(src)<<6) & 0x00000040))
/*	 Fields mbox_13_5	 */
#define MBOX_13_56_WIDTH                                                      1
#define MBOX_13_56_SHIFT                                                      5
#define MBOX_13_56_MASK                                              0x00000020
#define MBOX_13_56_RD(src)                            (((src) & 0x00000020)>>5)
#define MBOX_13_56_SET(dst,src) \
                       (((dst) & ~0x00000020) | (((u32)(src)<<5) & 0x00000020))
/*	 Fields mbox_13_4	 */
#define MBOX_13_46_WIDTH                                                      1
#define MBOX_13_46_SHIFT                                                      4
#define MBOX_13_46_MASK                                              0x00000010
#define MBOX_13_46_RD(src)                            (((src) & 0x00000010)>>4)
#define MBOX_13_46_SET(dst,src) \
                       (((dst) & ~0x00000010) | (((u32)(src)<<4) & 0x00000010))
/*	 Fields mbox_13_3	 */
#define MBOX_13_36_WIDTH                                                      1
#define MBOX_13_36_SHIFT                                                      3
#define MBOX_13_36_MASK                                              0x00000008
#define MBOX_13_36_RD(src)                            (((src) & 0x00000008)>>3)
#define MBOX_13_36_SET(dst,src) \
                       (((dst) & ~0x00000008) | (((u32)(src)<<3) & 0x00000008))
/*	 Fields mbox_13_2	 */
#define MBOX_13_26_WIDTH                                                      1
#define MBOX_13_26_SHIFT                                                      2
#define MBOX_13_26_MASK                                              0x00000004
#define MBOX_13_26_RD(src)                            (((src) & 0x00000004)>>2)
#define MBOX_13_26_SET(dst,src) \
                       (((dst) & ~0x00000004) | (((u32)(src)<<2) & 0x00000004))
/*	 Fields mbox_13_1	 */
#define MBOX_13_16_WIDTH                                                      1
#define MBOX_13_16_SHIFT                                                      1
#define MBOX_13_16_MASK                                              0x00000002
#define MBOX_13_16_RD(src)                            (((src) & 0x00000002)>>1)
#define MBOX_13_16_SET(dst,src) \
                       (((dst) & ~0x00000002) | (((u32)(src)<<1) & 0x00000002))
/*	 Fields mbox_13_0	 */
#define MBOX_13_06_WIDTH                                                      1
#define MBOX_13_06_SHIFT                                                      0
#define MBOX_13_06_MASK                                              0x00000001
#define MBOX_13_06_RD(src)                               (((src) & 0x00000001))
#define MBOX_13_06_SET(dst,src) \
                          (((dst) & ~0x00000001) | (((u32)(src)) & 0x00000001))

/*	Register csr_enq_status_7	*/ 
/*	 Fields mbox_14_15	 */
#define MBOX_14_157_WIDTH                                                     1
#define MBOX_14_157_SHIFT                                                    31
#define MBOX_14_157_MASK                                             0x80000000
#define MBOX_14_157_RD(src)                          (((src) & 0x80000000)>>31)
#define MBOX_14_157_SET(dst,src) \
                      (((dst) & ~0x80000000) | (((u32)(src)<<31) & 0x80000000))
/*	 Fields mbox_14_14	 */
#define MBOX_14_147_WIDTH                                                     1
#define MBOX_14_147_SHIFT                                                    30
#define MBOX_14_147_MASK                                             0x40000000
#define MBOX_14_147_RD(src)                          (((src) & 0x40000000)>>30)
#define MBOX_14_147_SET(dst,src) \
                      (((dst) & ~0x40000000) | (((u32)(src)<<30) & 0x40000000))
/*	 Fields mbox_14_13	 */
#define MBOX_14_137_WIDTH                                                     1
#define MBOX_14_137_SHIFT                                                    29
#define MBOX_14_137_MASK                                             0x20000000
#define MBOX_14_137_RD(src)                          (((src) & 0x20000000)>>29)
#define MBOX_14_137_SET(dst,src) \
                      (((dst) & ~0x20000000) | (((u32)(src)<<29) & 0x20000000))
/*	 Fields mbox_14_12	 */
#define MBOX_14_127_WIDTH                                                     1
#define MBOX_14_127_SHIFT                                                    28
#define MBOX_14_127_MASK                                             0x10000000
#define MBOX_14_127_RD(src)                          (((src) & 0x10000000)>>28)
#define MBOX_14_127_SET(dst,src) \
                      (((dst) & ~0x10000000) | (((u32)(src)<<28) & 0x10000000))
/*	 Fields mbox_14_11	 */
#define MBOX_14_117_WIDTH                                                     1
#define MBOX_14_117_SHIFT                                                    27
#define MBOX_14_117_MASK                                             0x08000000
#define MBOX_14_117_RD(src)                          (((src) & 0x08000000)>>27)
#define MBOX_14_117_SET(dst,src) \
                      (((dst) & ~0x08000000) | (((u32)(src)<<27) & 0x08000000))
/*	 Fields mbox_14_10	 */
#define MBOX_14_107_WIDTH                                                     1
#define MBOX_14_107_SHIFT                                                    26
#define MBOX_14_107_MASK                                             0x04000000
#define MBOX_14_107_RD(src)                          (((src) & 0x04000000)>>26)
#define MBOX_14_107_SET(dst,src) \
                      (((dst) & ~0x04000000) | (((u32)(src)<<26) & 0x04000000))
/*	 Fields mbox_14_9	 */
#define MBOX_14_97_WIDTH                                                      1
#define MBOX_14_97_SHIFT                                                     25
#define MBOX_14_97_MASK                                              0x02000000
#define MBOX_14_97_RD(src)                           (((src) & 0x02000000)>>25)
#define MBOX_14_97_SET(dst,src) \
                      (((dst) & ~0x02000000) | (((u32)(src)<<25) & 0x02000000))
/*	 Fields mbox_14_8	 */
#define MBOX_14_87_WIDTH                                                      1
#define MBOX_14_87_SHIFT                                                     24
#define MBOX_14_87_MASK                                              0x01000000
#define MBOX_14_87_RD(src)                           (((src) & 0x01000000)>>24)
#define MBOX_14_87_SET(dst,src) \
                      (((dst) & ~0x01000000) | (((u32)(src)<<24) & 0x01000000))
/*	 Fields mbox_14_7	 */
#define MBOX_14_77_WIDTH                                                      1
#define MBOX_14_77_SHIFT                                                     23
#define MBOX_14_77_MASK                                              0x00800000
#define MBOX_14_77_RD(src)                           (((src) & 0x00800000)>>23)
#define MBOX_14_77_SET(dst,src) \
                      (((dst) & ~0x00800000) | (((u32)(src)<<23) & 0x00800000))
/*	 Fields mbox_14_6	 */
#define MBOX_14_67_WIDTH                                                      1
#define MBOX_14_67_SHIFT                                                     22
#define MBOX_14_67_MASK                                              0x00400000
#define MBOX_14_67_RD(src)                           (((src) & 0x00400000)>>22)
#define MBOX_14_67_SET(dst,src) \
                      (((dst) & ~0x00400000) | (((u32)(src)<<22) & 0x00400000))
/*	 Fields mbox_14_5	 */
#define MBOX_14_57_WIDTH                                                      1
#define MBOX_14_57_SHIFT                                                     21
#define MBOX_14_57_MASK                                              0x00200000
#define MBOX_14_57_RD(src)                           (((src) & 0x00200000)>>21)
#define MBOX_14_57_SET(dst,src) \
                      (((dst) & ~0x00200000) | (((u32)(src)<<21) & 0x00200000))
/*	 Fields mbox_14_4	 */
#define MBOX_14_47_WIDTH                                                      1
#define MBOX_14_47_SHIFT                                                     20
#define MBOX_14_47_MASK                                              0x00100000
#define MBOX_14_47_RD(src)                           (((src) & 0x00100000)>>20)
#define MBOX_14_47_SET(dst,src) \
                      (((dst) & ~0x00100000) | (((u32)(src)<<20) & 0x00100000))
/*	 Fields mbox_14_3	 */
#define MBOX_14_37_WIDTH                                                      1
#define MBOX_14_37_SHIFT                                                     19
#define MBOX_14_37_MASK                                              0x00080000
#define MBOX_14_37_RD(src)                           (((src) & 0x00080000)>>19)
#define MBOX_14_37_SET(dst,src) \
                      (((dst) & ~0x00080000) | (((u32)(src)<<19) & 0x00080000))
/*	 Fields mbox_14_2	 */
#define MBOX_14_27_WIDTH                                                      1
#define MBOX_14_27_SHIFT                                                     18
#define MBOX_14_27_MASK                                              0x00040000
#define MBOX_14_27_RD(src)                           (((src) & 0x00040000)>>18)
#define MBOX_14_27_SET(dst,src) \
                      (((dst) & ~0x00040000) | (((u32)(src)<<18) & 0x00040000))
/*	 Fields mbox_14_1	 */
#define MBOX_14_17_WIDTH                                                      1
#define MBOX_14_17_SHIFT                                                     17
#define MBOX_14_17_MASK                                              0x00020000
#define MBOX_14_17_RD(src)                           (((src) & 0x00020000)>>17)
#define MBOX_14_17_SET(dst,src) \
                      (((dst) & ~0x00020000) | (((u32)(src)<<17) & 0x00020000))
/*	 Fields mbox_14_0	 */
#define MBOX_14_07_WIDTH                                                      1
#define MBOX_14_07_SHIFT                                                     16
#define MBOX_14_07_MASK                                              0x00010000
#define MBOX_14_07_RD(src)                           (((src) & 0x00010000)>>16)
#define MBOX_14_07_SET(dst,src) \
                      (((dst) & ~0x00010000) | (((u32)(src)<<16) & 0x00010000))
/*	 Fields mbox_15_15	 */
#define MBOX_15_157_WIDTH                                                     1
#define MBOX_15_157_SHIFT                                                    15
#define MBOX_15_157_MASK                                             0x00008000
#define MBOX_15_157_RD(src)                          (((src) & 0x00008000)>>15)
#define MBOX_15_157_SET(dst,src) \
                      (((dst) & ~0x00008000) | (((u32)(src)<<15) & 0x00008000))
/*	 Fields mbox_15_14	 */
#define MBOX_15_147_WIDTH                                                     1
#define MBOX_15_147_SHIFT                                                    14
#define MBOX_15_147_MASK                                             0x00004000
#define MBOX_15_147_RD(src)                          (((src) & 0x00004000)>>14)
#define MBOX_15_147_SET(dst,src) \
                      (((dst) & ~0x00004000) | (((u32)(src)<<14) & 0x00004000))
/*	 Fields mbox_15_13	 */
#define MBOX_15_137_WIDTH                                                     1
#define MBOX_15_137_SHIFT                                                    13
#define MBOX_15_137_MASK                                             0x00002000
#define MBOX_15_137_RD(src)                          (((src) & 0x00002000)>>13)
#define MBOX_15_137_SET(dst,src) \
                      (((dst) & ~0x00002000) | (((u32)(src)<<13) & 0x00002000))
/*	 Fields mbox_15_12	 */
#define MBOX_15_127_WIDTH                                                     1
#define MBOX_15_127_SHIFT                                                    12
#define MBOX_15_127_MASK                                             0x00001000
#define MBOX_15_127_RD(src)                          (((src) & 0x00001000)>>12)
#define MBOX_15_127_SET(dst,src) \
                      (((dst) & ~0x00001000) | (((u32)(src)<<12) & 0x00001000))
/*	 Fields mbox_15_11	 */
#define MBOX_15_117_WIDTH                                                     1
#define MBOX_15_117_SHIFT                                                    11
#define MBOX_15_117_MASK                                             0x00000800
#define MBOX_15_117_RD(src)                          (((src) & 0x00000800)>>11)
#define MBOX_15_117_SET(dst,src) \
                      (((dst) & ~0x00000800) | (((u32)(src)<<11) & 0x00000800))
/*	 Fields mbox_15_10	 */
#define MBOX_15_107_WIDTH                                                     1
#define MBOX_15_107_SHIFT                                                    10
#define MBOX_15_107_MASK                                             0x00000400
#define MBOX_15_107_RD(src)                          (((src) & 0x00000400)>>10)
#define MBOX_15_107_SET(dst,src) \
                      (((dst) & ~0x00000400) | (((u32)(src)<<10) & 0x00000400))
/*	 Fields mbox_15_9	 */
#define MBOX_15_97_WIDTH                                                      1
#define MBOX_15_97_SHIFT                                                      9
#define MBOX_15_97_MASK                                              0x00000200
#define MBOX_15_97_RD(src)                            (((src) & 0x00000200)>>9)
#define MBOX_15_97_SET(dst,src) \
                       (((dst) & ~0x00000200) | (((u32)(src)<<9) & 0x00000200))
/*	 Fields mbox_15_8	 */
#define MBOX_15_87_WIDTH                                                      1
#define MBOX_15_87_SHIFT                                                      8
#define MBOX_15_87_MASK                                              0x00000100
#define MBOX_15_87_RD(src)                            (((src) & 0x00000100)>>8)
#define MBOX_15_87_SET(dst,src) \
                       (((dst) & ~0x00000100) | (((u32)(src)<<8) & 0x00000100))
/*	 Fields mbox_15_7	 */
#define MBOX_15_77_WIDTH                                                      1
#define MBOX_15_77_SHIFT                                                      7
#define MBOX_15_77_MASK                                              0x00000080
#define MBOX_15_77_RD(src)                            (((src) & 0x00000080)>>7)
#define MBOX_15_77_SET(dst,src) \
                       (((dst) & ~0x00000080) | (((u32)(src)<<7) & 0x00000080))
/*	 Fields mbox_15_6	 */
#define MBOX_15_67_WIDTH                                                      1
#define MBOX_15_67_SHIFT                                                      6
#define MBOX_15_67_MASK                                              0x00000040
#define MBOX_15_67_RD(src)                            (((src) & 0x00000040)>>6)
#define MBOX_15_67_SET(dst,src) \
                       (((dst) & ~0x00000040) | (((u32)(src)<<6) & 0x00000040))
/*	 Fields mbox_15_5	 */
#define MBOX_15_57_WIDTH                                                      1
#define MBOX_15_57_SHIFT                                                      5
#define MBOX_15_57_MASK                                              0x00000020
#define MBOX_15_57_RD(src)                            (((src) & 0x00000020)>>5)
#define MBOX_15_57_SET(dst,src) \
                       (((dst) & ~0x00000020) | (((u32)(src)<<5) & 0x00000020))
/*	 Fields mbox_15_4	 */
#define MBOX_15_47_WIDTH                                                      1
#define MBOX_15_47_SHIFT                                                      4
#define MBOX_15_47_MASK                                              0x00000010
#define MBOX_15_47_RD(src)                            (((src) & 0x00000010)>>4)
#define MBOX_15_47_SET(dst,src) \
                       (((dst) & ~0x00000010) | (((u32)(src)<<4) & 0x00000010))
/*	 Fields mbox_15_3	 */
#define MBOX_15_37_WIDTH                                                      1
#define MBOX_15_37_SHIFT                                                      3
#define MBOX_15_37_MASK                                              0x00000008
#define MBOX_15_37_RD(src)                            (((src) & 0x00000008)>>3)
#define MBOX_15_37_SET(dst,src) \
                       (((dst) & ~0x00000008) | (((u32)(src)<<3) & 0x00000008))
/*	 Fields mbox_15_2	 */
#define MBOX_15_27_WIDTH                                                      1
#define MBOX_15_27_SHIFT                                                      2
#define MBOX_15_27_MASK                                              0x00000004
#define MBOX_15_27_RD(src)                            (((src) & 0x00000004)>>2)
#define MBOX_15_27_SET(dst,src) \
                       (((dst) & ~0x00000004) | (((u32)(src)<<2) & 0x00000004))
/*	 Fields mbox_15_1	 */
#define MBOX_15_17_WIDTH                                                      1
#define MBOX_15_17_SHIFT                                                      1
#define MBOX_15_17_MASK                                              0x00000002
#define MBOX_15_17_RD(src)                            (((src) & 0x00000002)>>1)
#define MBOX_15_17_SET(dst,src) \
                       (((dst) & ~0x00000002) | (((u32)(src)<<1) & 0x00000002))
/*	 Fields mbox_15_0	 */
#define MBOX_15_07_WIDTH                                                      1
#define MBOX_15_07_SHIFT                                                      0
#define MBOX_15_07_MASK                                              0x00000001
#define MBOX_15_07_RD(src)                               (((src) & 0x00000001))
#define MBOX_15_07_SET(dst,src) \
                          (((dst) & ~0x00000001) | (((u32)(src)) & 0x00000001))

/*	Register csr_enq_status_8	*/ 
/*	 Fields mbox_16_15	 */
#define MBOX_16_158_WIDTH                                                     1
#define MBOX_16_158_SHIFT                                                    31
#define MBOX_16_158_MASK                                             0x80000000
#define MBOX_16_158_RD(src)                          (((src) & 0x80000000)>>31)
#define MBOX_16_158_SET(dst,src) \
                      (((dst) & ~0x80000000) | (((u32)(src)<<31) & 0x80000000))
/*	 Fields mbox_16_14	 */
#define MBOX_16_148_WIDTH                                                     1
#define MBOX_16_148_SHIFT                                                    30
#define MBOX_16_148_MASK                                             0x40000000
#define MBOX_16_148_RD(src)                          (((src) & 0x40000000)>>30)
#define MBOX_16_148_SET(dst,src) \
                      (((dst) & ~0x40000000) | (((u32)(src)<<30) & 0x40000000))
/*	 Fields mbox_16_13	 */
#define MBOX_16_138_WIDTH                                                     1
#define MBOX_16_138_SHIFT                                                    29
#define MBOX_16_138_MASK                                             0x20000000
#define MBOX_16_138_RD(src)                          (((src) & 0x20000000)>>29)
#define MBOX_16_138_SET(dst,src) \
                      (((dst) & ~0x20000000) | (((u32)(src)<<29) & 0x20000000))
/*	 Fields mbox_16_12	 */
#define MBOX_16_128_WIDTH                                                     1
#define MBOX_16_128_SHIFT                                                    28
#define MBOX_16_128_MASK                                             0x10000000
#define MBOX_16_128_RD(src)                          (((src) & 0x10000000)>>28)
#define MBOX_16_128_SET(dst,src) \
                      (((dst) & ~0x10000000) | (((u32)(src)<<28) & 0x10000000))
/*	 Fields mbox_16_11	 */
#define MBOX_16_118_WIDTH                                                     1
#define MBOX_16_118_SHIFT                                                    27
#define MBOX_16_118_MASK                                             0x08000000
#define MBOX_16_118_RD(src)                          (((src) & 0x08000000)>>27)
#define MBOX_16_118_SET(dst,src) \
                      (((dst) & ~0x08000000) | (((u32)(src)<<27) & 0x08000000))
/*	 Fields mbox_16_10	 */
#define MBOX_16_108_WIDTH                                                     1
#define MBOX_16_108_SHIFT                                                    26
#define MBOX_16_108_MASK                                             0x04000000
#define MBOX_16_108_RD(src)                          (((src) & 0x04000000)>>26)
#define MBOX_16_108_SET(dst,src) \
                      (((dst) & ~0x04000000) | (((u32)(src)<<26) & 0x04000000))
/*	 Fields mbox_16_9	 */
#define MBOX_16_98_WIDTH                                                      1
#define MBOX_16_98_SHIFT                                                     25
#define MBOX_16_98_MASK                                              0x02000000
#define MBOX_16_98_RD(src)                           (((src) & 0x02000000)>>25)
#define MBOX_16_98_SET(dst,src) \
                      (((dst) & ~0x02000000) | (((u32)(src)<<25) & 0x02000000))
/*	 Fields mbox_16_8	 */
#define MBOX_16_88_WIDTH                                                      1
#define MBOX_16_88_SHIFT                                                     24
#define MBOX_16_88_MASK                                              0x01000000
#define MBOX_16_88_RD(src)                           (((src) & 0x01000000)>>24)
#define MBOX_16_88_SET(dst,src) \
                      (((dst) & ~0x01000000) | (((u32)(src)<<24) & 0x01000000))
/*	 Fields mbox_16_7	 */
#define MBOX_16_78_WIDTH                                                      1
#define MBOX_16_78_SHIFT                                                     23
#define MBOX_16_78_MASK                                              0x00800000
#define MBOX_16_78_RD(src)                           (((src) & 0x00800000)>>23)
#define MBOX_16_78_SET(dst,src) \
                      (((dst) & ~0x00800000) | (((u32)(src)<<23) & 0x00800000))
/*	 Fields mbox_16_6	 */
#define MBOX_16_68_WIDTH                                                      1
#define MBOX_16_68_SHIFT                                                     22
#define MBOX_16_68_MASK                                              0x00400000
#define MBOX_16_68_RD(src)                           (((src) & 0x00400000)>>22)
#define MBOX_16_68_SET(dst,src) \
                      (((dst) & ~0x00400000) | (((u32)(src)<<22) & 0x00400000))
/*	 Fields mbox_16_5	 */
#define MBOX_16_58_WIDTH                                                      1
#define MBOX_16_58_SHIFT                                                     21
#define MBOX_16_58_MASK                                              0x00200000
#define MBOX_16_58_RD(src)                           (((src) & 0x00200000)>>21)
#define MBOX_16_58_SET(dst,src) \
                      (((dst) & ~0x00200000) | (((u32)(src)<<21) & 0x00200000))
/*	 Fields mbox_16_4	 */
#define MBOX_16_48_WIDTH                                                      1
#define MBOX_16_48_SHIFT                                                     20
#define MBOX_16_48_MASK                                              0x00100000
#define MBOX_16_48_RD(src)                           (((src) & 0x00100000)>>20)
#define MBOX_16_48_SET(dst,src) \
                      (((dst) & ~0x00100000) | (((u32)(src)<<20) & 0x00100000))
/*	 Fields mbox_16_3	 */
#define MBOX_16_38_WIDTH                                                      1
#define MBOX_16_38_SHIFT                                                     19
#define MBOX_16_38_MASK                                              0x00080000
#define MBOX_16_38_RD(src)                           (((src) & 0x00080000)>>19)
#define MBOX_16_38_SET(dst,src) \
                      (((dst) & ~0x00080000) | (((u32)(src)<<19) & 0x00080000))
/*	 Fields mbox_16_2	 */
#define MBOX_16_28_WIDTH                                                      1
#define MBOX_16_28_SHIFT                                                     18
#define MBOX_16_28_MASK                                              0x00040000
#define MBOX_16_28_RD(src)                           (((src) & 0x00040000)>>18)
#define MBOX_16_28_SET(dst,src) \
                      (((dst) & ~0x00040000) | (((u32)(src)<<18) & 0x00040000))
/*	 Fields mbox_16_1	 */
#define MBOX_16_18_WIDTH                                                      1
#define MBOX_16_18_SHIFT                                                     17
#define MBOX_16_18_MASK                                              0x00020000
#define MBOX_16_18_RD(src)                           (((src) & 0x00020000)>>17)
#define MBOX_16_18_SET(dst,src) \
                      (((dst) & ~0x00020000) | (((u32)(src)<<17) & 0x00020000))
/*	 Fields mbox_16_0	 */
#define MBOX_16_08_WIDTH                                                      1
#define MBOX_16_08_SHIFT                                                     16
#define MBOX_16_08_MASK                                              0x00010000
#define MBOX_16_08_RD(src)                           (((src) & 0x00010000)>>16)
#define MBOX_16_08_SET(dst,src) \
                      (((dst) & ~0x00010000) | (((u32)(src)<<16) & 0x00010000))
/*	 Fields mbox_17_15	 */
#define MBOX_17_158_WIDTH                                                     1
#define MBOX_17_158_SHIFT                                                    15
#define MBOX_17_158_MASK                                             0x00008000
#define MBOX_17_158_RD(src)                          (((src) & 0x00008000)>>15)
#define MBOX_17_158_SET(dst,src) \
                      (((dst) & ~0x00008000) | (((u32)(src)<<15) & 0x00008000))
/*	 Fields mbox_17_14	 */
#define MBOX_17_148_WIDTH                                                     1
#define MBOX_17_148_SHIFT                                                    14
#define MBOX_17_148_MASK                                             0x00004000
#define MBOX_17_148_RD(src)                          (((src) & 0x00004000)>>14)
#define MBOX_17_148_SET(dst,src) \
                      (((dst) & ~0x00004000) | (((u32)(src)<<14) & 0x00004000))
/*	 Fields mbox_17_13	 */
#define MBOX_17_138_WIDTH                                                     1
#define MBOX_17_138_SHIFT                                                    13
#define MBOX_17_138_MASK                                             0x00002000
#define MBOX_17_138_RD(src)                          (((src) & 0x00002000)>>13)
#define MBOX_17_138_SET(dst,src) \
                      (((dst) & ~0x00002000) | (((u32)(src)<<13) & 0x00002000))
/*	 Fields mbox_17_12	 */
#define MBOX_17_128_WIDTH                                                     1
#define MBOX_17_128_SHIFT                                                    12
#define MBOX_17_128_MASK                                             0x00001000
#define MBOX_17_128_RD(src)                          (((src) & 0x00001000)>>12)
#define MBOX_17_128_SET(dst,src) \
                      (((dst) & ~0x00001000) | (((u32)(src)<<12) & 0x00001000))
/*	 Fields mbox_17_11	 */
#define MBOX_17_118_WIDTH                                                     1
#define MBOX_17_118_SHIFT                                                    11
#define MBOX_17_118_MASK                                             0x00000800
#define MBOX_17_118_RD(src)                          (((src) & 0x00000800)>>11)
#define MBOX_17_118_SET(dst,src) \
                      (((dst) & ~0x00000800) | (((u32)(src)<<11) & 0x00000800))
/*	 Fields mbox_17_10	 */
#define MBOX_17_108_WIDTH                                                     1
#define MBOX_17_108_SHIFT                                                    10
#define MBOX_17_108_MASK                                             0x00000400
#define MBOX_17_108_RD(src)                          (((src) & 0x00000400)>>10)
#define MBOX_17_108_SET(dst,src) \
                      (((dst) & ~0x00000400) | (((u32)(src)<<10) & 0x00000400))
/*	 Fields mbox_17_9	 */
#define MBOX_17_98_WIDTH                                                      1
#define MBOX_17_98_SHIFT                                                      9
#define MBOX_17_98_MASK                                              0x00000200
#define MBOX_17_98_RD(src)                            (((src) & 0x00000200)>>9)
#define MBOX_17_98_SET(dst,src) \
                       (((dst) & ~0x00000200) | (((u32)(src)<<9) & 0x00000200))
/*	 Fields mbox_17_8	 */
#define MBOX_17_88_WIDTH                                                      1
#define MBOX_17_88_SHIFT                                                      8
#define MBOX_17_88_MASK                                              0x00000100
#define MBOX_17_88_RD(src)                            (((src) & 0x00000100)>>8)
#define MBOX_17_88_SET(dst,src) \
                       (((dst) & ~0x00000100) | (((u32)(src)<<8) & 0x00000100))
/*	 Fields mbox_17_7	 */
#define MBOX_17_78_WIDTH                                                      1
#define MBOX_17_78_SHIFT                                                      7
#define MBOX_17_78_MASK                                              0x00000080
#define MBOX_17_78_RD(src)                            (((src) & 0x00000080)>>7)
#define MBOX_17_78_SET(dst,src) \
                       (((dst) & ~0x00000080) | (((u32)(src)<<7) & 0x00000080))
/*	 Fields mbox_17_6	 */
#define MBOX_17_68_WIDTH                                                      1
#define MBOX_17_68_SHIFT                                                      6
#define MBOX_17_68_MASK                                              0x00000040
#define MBOX_17_68_RD(src)                            (((src) & 0x00000040)>>6)
#define MBOX_17_68_SET(dst,src) \
                       (((dst) & ~0x00000040) | (((u32)(src)<<6) & 0x00000040))
/*	 Fields mbox_17_5	 */
#define MBOX_17_58_WIDTH                                                      1
#define MBOX_17_58_SHIFT                                                      5
#define MBOX_17_58_MASK                                              0x00000020
#define MBOX_17_58_RD(src)                            (((src) & 0x00000020)>>5)
#define MBOX_17_58_SET(dst,src) \
                       (((dst) & ~0x00000020) | (((u32)(src)<<5) & 0x00000020))
/*	 Fields mbox_17_4	 */
#define MBOX_17_48_WIDTH                                                      1
#define MBOX_17_48_SHIFT                                                      4
#define MBOX_17_48_MASK                                              0x00000010
#define MBOX_17_48_RD(src)                            (((src) & 0x00000010)>>4)
#define MBOX_17_48_SET(dst,src) \
                       (((dst) & ~0x00000010) | (((u32)(src)<<4) & 0x00000010))
/*	 Fields mbox_17_3	 */
#define MBOX_17_38_WIDTH                                                      1
#define MBOX_17_38_SHIFT                                                      3
#define MBOX_17_38_MASK                                              0x00000008
#define MBOX_17_38_RD(src)                            (((src) & 0x00000008)>>3)
#define MBOX_17_38_SET(dst,src) \
                       (((dst) & ~0x00000008) | (((u32)(src)<<3) & 0x00000008))
/*	 Fields mbox_17_2	 */
#define MBOX_17_28_WIDTH                                                      1
#define MBOX_17_28_SHIFT                                                      2
#define MBOX_17_28_MASK                                              0x00000004
#define MBOX_17_28_RD(src)                            (((src) & 0x00000004)>>2)
#define MBOX_17_28_SET(dst,src) \
                       (((dst) & ~0x00000004) | (((u32)(src)<<2) & 0x00000004))
/*	 Fields mbox_17_1	 */
#define MBOX_17_18_WIDTH                                                      1
#define MBOX_17_18_SHIFT                                                      1
#define MBOX_17_18_MASK                                              0x00000002
#define MBOX_17_18_RD(src)                            (((src) & 0x00000002)>>1)
#define MBOX_17_18_SET(dst,src) \
                       (((dst) & ~0x00000002) | (((u32)(src)<<1) & 0x00000002))
/*	 Fields mbox_17_0	 */
#define MBOX_17_08_WIDTH                                                      1
#define MBOX_17_08_SHIFT                                                      0
#define MBOX_17_08_MASK                                              0x00000001
#define MBOX_17_08_RD(src)                               (((src) & 0x00000001))
#define MBOX_17_08_SET(dst,src) \
                          (((dst) & ~0x00000001) | (((u32)(src)) & 0x00000001))

/*	Register csr_enq_status_9	*/ 
/*	 Fields mbox_18_15	 */
#define MBOX_18_159_WIDTH                                                     1
#define MBOX_18_159_SHIFT                                                    31
#define MBOX_18_159_MASK                                             0x80000000
#define MBOX_18_159_RD(src)                          (((src) & 0x80000000)>>31)
#define MBOX_18_159_SET(dst,src) \
                      (((dst) & ~0x80000000) | (((u32)(src)<<31) & 0x80000000))
/*	 Fields mbox_18_14	 */
#define MBOX_18_149_WIDTH                                                     1
#define MBOX_18_149_SHIFT                                                    30
#define MBOX_18_149_MASK                                             0x40000000
#define MBOX_18_149_RD(src)                          (((src) & 0x40000000)>>30)
#define MBOX_18_149_SET(dst,src) \
                      (((dst) & ~0x40000000) | (((u32)(src)<<30) & 0x40000000))
/*	 Fields mbox_18_13	 */
#define MBOX_18_139_WIDTH                                                     1
#define MBOX_18_139_SHIFT                                                    29
#define MBOX_18_139_MASK                                             0x20000000
#define MBOX_18_139_RD(src)                          (((src) & 0x20000000)>>29)
#define MBOX_18_139_SET(dst,src) \
                      (((dst) & ~0x20000000) | (((u32)(src)<<29) & 0x20000000))
/*	 Fields mbox_18_12	 */
#define MBOX_18_129_WIDTH                                                     1
#define MBOX_18_129_SHIFT                                                    28
#define MBOX_18_129_MASK                                             0x10000000
#define MBOX_18_129_RD(src)                          (((src) & 0x10000000)>>28)
#define MBOX_18_129_SET(dst,src) \
                      (((dst) & ~0x10000000) | (((u32)(src)<<28) & 0x10000000))
/*	 Fields mbox_18_11	 */
#define MBOX_18_119_WIDTH                                                     1
#define MBOX_18_119_SHIFT                                                    27
#define MBOX_18_119_MASK                                             0x08000000
#define MBOX_18_119_RD(src)                          (((src) & 0x08000000)>>27)
#define MBOX_18_119_SET(dst,src) \
                      (((dst) & ~0x08000000) | (((u32)(src)<<27) & 0x08000000))
/*	 Fields mbox_18_10	 */
#define MBOX_18_109_WIDTH                                                     1
#define MBOX_18_109_SHIFT                                                    26
#define MBOX_18_109_MASK                                             0x04000000
#define MBOX_18_109_RD(src)                          (((src) & 0x04000000)>>26)
#define MBOX_18_109_SET(dst,src) \
                      (((dst) & ~0x04000000) | (((u32)(src)<<26) & 0x04000000))
/*	 Fields mbox_18_9	 */
#define MBOX_18_99_WIDTH                                                      1
#define MBOX_18_99_SHIFT                                                     25
#define MBOX_18_99_MASK                                              0x02000000
#define MBOX_18_99_RD(src)                           (((src) & 0x02000000)>>25)
#define MBOX_18_99_SET(dst,src) \
                      (((dst) & ~0x02000000) | (((u32)(src)<<25) & 0x02000000))
/*	 Fields mbox_18_8	 */
#define MBOX_18_89_WIDTH                                                      1
#define MBOX_18_89_SHIFT                                                     24
#define MBOX_18_89_MASK                                              0x01000000
#define MBOX_18_89_RD(src)                           (((src) & 0x01000000)>>24)
#define MBOX_18_89_SET(dst,src) \
                      (((dst) & ~0x01000000) | (((u32)(src)<<24) & 0x01000000))
/*	 Fields mbox_18_7	 */
#define MBOX_18_79_WIDTH                                                      1
#define MBOX_18_79_SHIFT                                                     23
#define MBOX_18_79_MASK                                              0x00800000
#define MBOX_18_79_RD(src)                           (((src) & 0x00800000)>>23)
#define MBOX_18_79_SET(dst,src) \
                      (((dst) & ~0x00800000) | (((u32)(src)<<23) & 0x00800000))
/*	 Fields mbox_18_6	 */
#define MBOX_18_69_WIDTH                                                      1
#define MBOX_18_69_SHIFT                                                     22
#define MBOX_18_69_MASK                                              0x00400000
#define MBOX_18_69_RD(src)                           (((src) & 0x00400000)>>22)
#define MBOX_18_69_SET(dst,src) \
                      (((dst) & ~0x00400000) | (((u32)(src)<<22) & 0x00400000))
/*	 Fields mbox_18_5	 */
#define MBOX_18_59_WIDTH                                                      1
#define MBOX_18_59_SHIFT                                                     21
#define MBOX_18_59_MASK                                              0x00200000
#define MBOX_18_59_RD(src)                           (((src) & 0x00200000)>>21)
#define MBOX_18_59_SET(dst,src) \
                      (((dst) & ~0x00200000) | (((u32)(src)<<21) & 0x00200000))
/*	 Fields mbox_18_4	 */
#define MBOX_18_49_WIDTH                                                      1
#define MBOX_18_49_SHIFT                                                     20
#define MBOX_18_49_MASK                                              0x00100000
#define MBOX_18_49_RD(src)                           (((src) & 0x00100000)>>20)
#define MBOX_18_49_SET(dst,src) \
                      (((dst) & ~0x00100000) | (((u32)(src)<<20) & 0x00100000))
/*	 Fields mbox_18_3	 */
#define MBOX_18_39_WIDTH                                                      1
#define MBOX_18_39_SHIFT                                                     19
#define MBOX_18_39_MASK                                              0x00080000
#define MBOX_18_39_RD(src)                           (((src) & 0x00080000)>>19)
#define MBOX_18_39_SET(dst,src) \
                      (((dst) & ~0x00080000) | (((u32)(src)<<19) & 0x00080000))
/*	 Fields mbox_18_2	 */
#define MBOX_18_29_WIDTH                                                      1
#define MBOX_18_29_SHIFT                                                     18
#define MBOX_18_29_MASK                                              0x00040000
#define MBOX_18_29_RD(src)                           (((src) & 0x00040000)>>18)
#define MBOX_18_29_SET(dst,src) \
                      (((dst) & ~0x00040000) | (((u32)(src)<<18) & 0x00040000))
/*	 Fields mbox_18_1	 */
#define MBOX_18_19_WIDTH                                                      1
#define MBOX_18_19_SHIFT                                                     17
#define MBOX_18_19_MASK                                              0x00020000
#define MBOX_18_19_RD(src)                           (((src) & 0x00020000)>>17)
#define MBOX_18_19_SET(dst,src) \
                      (((dst) & ~0x00020000) | (((u32)(src)<<17) & 0x00020000))
/*	 Fields mbox_18_0	 */
#define MBOX_18_09_WIDTH                                                      1
#define MBOX_18_09_SHIFT                                                     16
#define MBOX_18_09_MASK                                              0x00010000
#define MBOX_18_09_RD(src)                           (((src) & 0x00010000)>>16)
#define MBOX_18_09_SET(dst,src) \
                      (((dst) & ~0x00010000) | (((u32)(src)<<16) & 0x00010000))
/*	 Fields mbox_19_15	 */
#define MBOX_19_159_WIDTH                                                     1
#define MBOX_19_159_SHIFT                                                    15
#define MBOX_19_159_MASK                                             0x00008000
#define MBOX_19_159_RD(src)                          (((src) & 0x00008000)>>15)
#define MBOX_19_159_SET(dst,src) \
                      (((dst) & ~0x00008000) | (((u32)(src)<<15) & 0x00008000))
/*	 Fields mbox_19_14	 */
#define MBOX_19_149_WIDTH                                                     1
#define MBOX_19_149_SHIFT                                                    14
#define MBOX_19_149_MASK                                             0x00004000
#define MBOX_19_149_RD(src)                          (((src) & 0x00004000)>>14)
#define MBOX_19_149_SET(dst,src) \
                      (((dst) & ~0x00004000) | (((u32)(src)<<14) & 0x00004000))
/*	 Fields mbox_19_13	 */
#define MBOX_19_139_WIDTH                                                     1
#define MBOX_19_139_SHIFT                                                    13
#define MBOX_19_139_MASK                                             0x00002000
#define MBOX_19_139_RD(src)                          (((src) & 0x00002000)>>13)
#define MBOX_19_139_SET(dst,src) \
                      (((dst) & ~0x00002000) | (((u32)(src)<<13) & 0x00002000))
/*	 Fields mbox_19_12	 */
#define MBOX_19_129_WIDTH                                                     1
#define MBOX_19_129_SHIFT                                                    12
#define MBOX_19_129_MASK                                             0x00001000
#define MBOX_19_129_RD(src)                          (((src) & 0x00001000)>>12)
#define MBOX_19_129_SET(dst,src) \
                      (((dst) & ~0x00001000) | (((u32)(src)<<12) & 0x00001000))
/*	 Fields mbox_19_11	 */
#define MBOX_19_119_WIDTH                                                     1
#define MBOX_19_119_SHIFT                                                    11
#define MBOX_19_119_MASK                                             0x00000800
#define MBOX_19_119_RD(src)                          (((src) & 0x00000800)>>11)
#define MBOX_19_119_SET(dst,src) \
                      (((dst) & ~0x00000800) | (((u32)(src)<<11) & 0x00000800))
/*	 Fields mbox_19_10	 */
#define MBOX_19_109_WIDTH                                                     1
#define MBOX_19_109_SHIFT                                                    10
#define MBOX_19_109_MASK                                             0x00000400
#define MBOX_19_109_RD(src)                          (((src) & 0x00000400)>>10)
#define MBOX_19_109_SET(dst,src) \
                      (((dst) & ~0x00000400) | (((u32)(src)<<10) & 0x00000400))
/*	 Fields mbox_19_9	 */
#define MBOX_19_99_WIDTH                                                      1
#define MBOX_19_99_SHIFT                                                      9
#define MBOX_19_99_MASK                                              0x00000200
#define MBOX_19_99_RD(src)                            (((src) & 0x00000200)>>9)
#define MBOX_19_99_SET(dst,src) \
                       (((dst) & ~0x00000200) | (((u32)(src)<<9) & 0x00000200))
/*	 Fields mbox_19_8	 */
#define MBOX_19_89_WIDTH                                                      1
#define MBOX_19_89_SHIFT                                                      8
#define MBOX_19_89_MASK                                              0x00000100
#define MBOX_19_89_RD(src)                            (((src) & 0x00000100)>>8)
#define MBOX_19_89_SET(dst,src) \
                       (((dst) & ~0x00000100) | (((u32)(src)<<8) & 0x00000100))
/*	 Fields mbox_19_7	 */
#define MBOX_19_79_WIDTH                                                      1
#define MBOX_19_79_SHIFT                                                      7
#define MBOX_19_79_MASK                                              0x00000080
#define MBOX_19_79_RD(src)                            (((src) & 0x00000080)>>7)
#define MBOX_19_79_SET(dst,src) \
                       (((dst) & ~0x00000080) | (((u32)(src)<<7) & 0x00000080))
/*	 Fields mbox_19_6	 */
#define MBOX_19_69_WIDTH                                                      1
#define MBOX_19_69_SHIFT                                                      6
#define MBOX_19_69_MASK                                              0x00000040
#define MBOX_19_69_RD(src)                            (((src) & 0x00000040)>>6)
#define MBOX_19_69_SET(dst,src) \
                       (((dst) & ~0x00000040) | (((u32)(src)<<6) & 0x00000040))
/*	 Fields mbox_19_5	 */
#define MBOX_19_59_WIDTH                                                      1
#define MBOX_19_59_SHIFT                                                      5
#define MBOX_19_59_MASK                                              0x00000020
#define MBOX_19_59_RD(src)                            (((src) & 0x00000020)>>5)
#define MBOX_19_59_SET(dst,src) \
                       (((dst) & ~0x00000020) | (((u32)(src)<<5) & 0x00000020))
/*	 Fields mbox_19_4	 */
#define MBOX_19_49_WIDTH                                                      1
#define MBOX_19_49_SHIFT                                                      4
#define MBOX_19_49_MASK                                              0x00000010
#define MBOX_19_49_RD(src)                            (((src) & 0x00000010)>>4)
#define MBOX_19_49_SET(dst,src) \
                       (((dst) & ~0x00000010) | (((u32)(src)<<4) & 0x00000010))
/*	 Fields mbox_19_3	 */
#define MBOX_19_39_WIDTH                                                      1
#define MBOX_19_39_SHIFT                                                      3
#define MBOX_19_39_MASK                                              0x00000008
#define MBOX_19_39_RD(src)                            (((src) & 0x00000008)>>3)
#define MBOX_19_39_SET(dst,src) \
                       (((dst) & ~0x00000008) | (((u32)(src)<<3) & 0x00000008))
/*	 Fields mbox_19_2	 */
#define MBOX_19_29_WIDTH                                                      1
#define MBOX_19_29_SHIFT                                                      2
#define MBOX_19_29_MASK                                              0x00000004
#define MBOX_19_29_RD(src)                            (((src) & 0x00000004)>>2)
#define MBOX_19_29_SET(dst,src) \
                       (((dst) & ~0x00000004) | (((u32)(src)<<2) & 0x00000004))
/*	 Fields mbox_19_1	 */
#define MBOX_19_19_WIDTH                                                      1
#define MBOX_19_19_SHIFT                                                      1
#define MBOX_19_19_MASK                                              0x00000002
#define MBOX_19_19_RD(src)                            (((src) & 0x00000002)>>1)
#define MBOX_19_19_SET(dst,src) \
                       (((dst) & ~0x00000002) | (((u32)(src)<<1) & 0x00000002))
/*	 Fields mbox_19_0	 */
#define MBOX_19_09_WIDTH                                                      1
#define MBOX_19_09_SHIFT                                                      0
#define MBOX_19_09_MASK                                              0x00000001
#define MBOX_19_09_RD(src)                               (((src) & 0x00000001))
#define MBOX_19_09_SET(dst,src) \
                          (((dst) & ~0x00000001) | (((u32)(src)) & 0x00000001))

/*	Register csr_enq_status_10	*/ 
/*	 Fields mbox_20_15	 */
#define MBOX_20_150_WIDTH                                                     1
#define MBOX_20_150_SHIFT                                                    31
#define MBOX_20_150_MASK                                             0x80000000
#define MBOX_20_150_RD(src)                          (((src) & 0x80000000)>>31)
#define MBOX_20_150_SET(dst,src) \
                      (((dst) & ~0x80000000) | (((u32)(src)<<31) & 0x80000000))
/*	 Fields mbox_20_14	 */
#define MBOX_20_140_WIDTH                                                     1
#define MBOX_20_140_SHIFT                                                    30
#define MBOX_20_140_MASK                                             0x40000000
#define MBOX_20_140_RD(src)                          (((src) & 0x40000000)>>30)
#define MBOX_20_140_SET(dst,src) \
                      (((dst) & ~0x40000000) | (((u32)(src)<<30) & 0x40000000))
/*	 Fields mbox_20_13	 */
#define MBOX_20_130_WIDTH                                                     1
#define MBOX_20_130_SHIFT                                                    29
#define MBOX_20_130_MASK                                             0x20000000
#define MBOX_20_130_RD(src)                          (((src) & 0x20000000)>>29)
#define MBOX_20_130_SET(dst,src) \
                      (((dst) & ~0x20000000) | (((u32)(src)<<29) & 0x20000000))
/*	 Fields mbox_20_12	 */
#define MBOX_20_120_WIDTH                                                     1
#define MBOX_20_120_SHIFT                                                    28
#define MBOX_20_120_MASK                                             0x10000000
#define MBOX_20_120_RD(src)                          (((src) & 0x10000000)>>28)
#define MBOX_20_120_SET(dst,src) \
                      (((dst) & ~0x10000000) | (((u32)(src)<<28) & 0x10000000))
/*	 Fields mbox_20_11	 */
#define MBOX_20_110_WIDTH                                                     1
#define MBOX_20_110_SHIFT                                                    27
#define MBOX_20_110_MASK                                             0x08000000
#define MBOX_20_110_RD(src)                          (((src) & 0x08000000)>>27)
#define MBOX_20_110_SET(dst,src) \
                      (((dst) & ~0x08000000) | (((u32)(src)<<27) & 0x08000000))
/*	 Fields mbox_20_10	 */
#define MBOX_20_100_WIDTH                                                     1
#define MBOX_20_100_SHIFT                                                    26
#define MBOX_20_100_MASK                                             0x04000000
#define MBOX_20_100_RD(src)                          (((src) & 0x04000000)>>26)
#define MBOX_20_100_SET(dst,src) \
                      (((dst) & ~0x04000000) | (((u32)(src)<<26) & 0x04000000))
/*	 Fields mbox_20_9	 */
#define MBOX_20_90_WIDTH                                                      1
#define MBOX_20_90_SHIFT                                                     25
#define MBOX_20_90_MASK                                              0x02000000
#define MBOX_20_90_RD(src)                           (((src) & 0x02000000)>>25)
#define MBOX_20_90_SET(dst,src) \
                      (((dst) & ~0x02000000) | (((u32)(src)<<25) & 0x02000000))
/*	 Fields mbox_20_8	 */
#define MBOX_20_80_WIDTH                                                      1
#define MBOX_20_80_SHIFT                                                     24
#define MBOX_20_80_MASK                                              0x01000000
#define MBOX_20_80_RD(src)                           (((src) & 0x01000000)>>24)
#define MBOX_20_80_SET(dst,src) \
                      (((dst) & ~0x01000000) | (((u32)(src)<<24) & 0x01000000))
/*	 Fields mbox_20_7	 */
#define MBOX_20_70_WIDTH                                                      1
#define MBOX_20_70_SHIFT                                                     23
#define MBOX_20_70_MASK                                              0x00800000
#define MBOX_20_70_RD(src)                           (((src) & 0x00800000)>>23)
#define MBOX_20_70_SET(dst,src) \
                      (((dst) & ~0x00800000) | (((u32)(src)<<23) & 0x00800000))
/*	 Fields mbox_20_6	 */
#define MBOX_20_60_WIDTH                                                      1
#define MBOX_20_60_SHIFT                                                     22
#define MBOX_20_60_MASK                                              0x00400000
#define MBOX_20_60_RD(src)                           (((src) & 0x00400000)>>22)
#define MBOX_20_60_SET(dst,src) \
                      (((dst) & ~0x00400000) | (((u32)(src)<<22) & 0x00400000))
/*	 Fields mbox_20_5	 */
#define MBOX_20_50_WIDTH                                                      1
#define MBOX_20_50_SHIFT                                                     21
#define MBOX_20_50_MASK                                              0x00200000
#define MBOX_20_50_RD(src)                           (((src) & 0x00200000)>>21)
#define MBOX_20_50_SET(dst,src) \
                      (((dst) & ~0x00200000) | (((u32)(src)<<21) & 0x00200000))
/*	 Fields mbox_20_4	 */
#define MBOX_20_40_WIDTH                                                      1
#define MBOX_20_40_SHIFT                                                     20
#define MBOX_20_40_MASK                                              0x00100000
#define MBOX_20_40_RD(src)                           (((src) & 0x00100000)>>20)
#define MBOX_20_40_SET(dst,src) \
                      (((dst) & ~0x00100000) | (((u32)(src)<<20) & 0x00100000))
/*	 Fields mbox_20_3	 */
#define MBOX_20_30_WIDTH                                                      1
#define MBOX_20_30_SHIFT                                                     19
#define MBOX_20_30_MASK                                              0x00080000
#define MBOX_20_30_RD(src)                           (((src) & 0x00080000)>>19)
#define MBOX_20_30_SET(dst,src) \
                      (((dst) & ~0x00080000) | (((u32)(src)<<19) & 0x00080000))
/*	 Fields mbox_20_2	 */
#define MBOX_20_20_WIDTH                                                      1
#define MBOX_20_20_SHIFT                                                     18
#define MBOX_20_20_MASK                                              0x00040000
#define MBOX_20_20_RD(src)                           (((src) & 0x00040000)>>18)
#define MBOX_20_20_SET(dst,src) \
                      (((dst) & ~0x00040000) | (((u32)(src)<<18) & 0x00040000))
/*	 Fields mbox_20_1	 */
#define MBOX_20_10_WIDTH                                                      1
#define MBOX_20_10_SHIFT                                                     17
#define MBOX_20_10_MASK                                              0x00020000
#define MBOX_20_10_RD(src)                           (((src) & 0x00020000)>>17)
#define MBOX_20_10_SET(dst,src) \
                      (((dst) & ~0x00020000) | (((u32)(src)<<17) & 0x00020000))
/*	 Fields mbox_20_0	 */
#define MBOX_20_00_WIDTH                                                      1
#define MBOX_20_00_SHIFT                                                     16
#define MBOX_20_00_MASK                                              0x00010000
#define MBOX_20_00_RD(src)                           (((src) & 0x00010000)>>16)
#define MBOX_20_00_SET(dst,src) \
                      (((dst) & ~0x00010000) | (((u32)(src)<<16) & 0x00010000))
/*	 Fields mbox_21_15	 */
#define MBOX_21_150_WIDTH                                                     1
#define MBOX_21_150_SHIFT                                                    15
#define MBOX_21_150_MASK                                             0x00008000
#define MBOX_21_150_RD(src)                          (((src) & 0x00008000)>>15)
#define MBOX_21_150_SET(dst,src) \
                      (((dst) & ~0x00008000) | (((u32)(src)<<15) & 0x00008000))
/*	 Fields mbox_21_14	 */
#define MBOX_21_140_WIDTH                                                     1
#define MBOX_21_140_SHIFT                                                    14
#define MBOX_21_140_MASK                                             0x00004000
#define MBOX_21_140_RD(src)                          (((src) & 0x00004000)>>14)
#define MBOX_21_140_SET(dst,src) \
                      (((dst) & ~0x00004000) | (((u32)(src)<<14) & 0x00004000))
/*	 Fields mbox_21_13	 */
#define MBOX_21_130_WIDTH                                                     1
#define MBOX_21_130_SHIFT                                                    13
#define MBOX_21_130_MASK                                             0x00002000
#define MBOX_21_130_RD(src)                          (((src) & 0x00002000)>>13)
#define MBOX_21_130_SET(dst,src) \
                      (((dst) & ~0x00002000) | (((u32)(src)<<13) & 0x00002000))
/*	 Fields mbox_21_12	 */
#define MBOX_21_120_WIDTH                                                     1
#define MBOX_21_120_SHIFT                                                    12
#define MBOX_21_120_MASK                                             0x00001000
#define MBOX_21_120_RD(src)                          (((src) & 0x00001000)>>12)
#define MBOX_21_120_SET(dst,src) \
                      (((dst) & ~0x00001000) | (((u32)(src)<<12) & 0x00001000))
/*	 Fields mbox_21_11	 */
#define MBOX_21_110_WIDTH                                                     1
#define MBOX_21_110_SHIFT                                                    11
#define MBOX_21_110_MASK                                             0x00000800
#define MBOX_21_110_RD(src)                          (((src) & 0x00000800)>>11)
#define MBOX_21_110_SET(dst,src) \
                      (((dst) & ~0x00000800) | (((u32)(src)<<11) & 0x00000800))
/*	 Fields mbox_21_10	 */
#define MBOX_21_100_WIDTH                                                     1
#define MBOX_21_100_SHIFT                                                    10
#define MBOX_21_100_MASK                                             0x00000400
#define MBOX_21_100_RD(src)                          (((src) & 0x00000400)>>10)
#define MBOX_21_100_SET(dst,src) \
                      (((dst) & ~0x00000400) | (((u32)(src)<<10) & 0x00000400))
/*	 Fields mbox_21_9	 */
#define MBOX_21_90_WIDTH                                                      1
#define MBOX_21_90_SHIFT                                                      9
#define MBOX_21_90_MASK                                              0x00000200
#define MBOX_21_90_RD(src)                            (((src) & 0x00000200)>>9)
#define MBOX_21_90_SET(dst,src) \
                       (((dst) & ~0x00000200) | (((u32)(src)<<9) & 0x00000200))
/*	 Fields mbox_21_8	 */
#define MBOX_21_80_WIDTH                                                      1
#define MBOX_21_80_SHIFT                                                      8
#define MBOX_21_80_MASK                                              0x00000100
#define MBOX_21_80_RD(src)                            (((src) & 0x00000100)>>8)
#define MBOX_21_80_SET(dst,src) \
                       (((dst) & ~0x00000100) | (((u32)(src)<<8) & 0x00000100))
/*	 Fields mbox_21_7	 */
#define MBOX_21_70_WIDTH                                                      1
#define MBOX_21_70_SHIFT                                                      7
#define MBOX_21_70_MASK                                              0x00000080
#define MBOX_21_70_RD(src)                            (((src) & 0x00000080)>>7)
#define MBOX_21_70_SET(dst,src) \
                       (((dst) & ~0x00000080) | (((u32)(src)<<7) & 0x00000080))
/*	 Fields mbox_21_6	 */
#define MBOX_21_60_WIDTH                                                      1
#define MBOX_21_60_SHIFT                                                      6
#define MBOX_21_60_MASK                                              0x00000040
#define MBOX_21_60_RD(src)                            (((src) & 0x00000040)>>6)
#define MBOX_21_60_SET(dst,src) \
                       (((dst) & ~0x00000040) | (((u32)(src)<<6) & 0x00000040))
/*	 Fields mbox_21_5	 */
#define MBOX_21_50_WIDTH                                                      1
#define MBOX_21_50_SHIFT                                                      5
#define MBOX_21_50_MASK                                              0x00000020
#define MBOX_21_50_RD(src)                            (((src) & 0x00000020)>>5)
#define MBOX_21_50_SET(dst,src) \
                       (((dst) & ~0x00000020) | (((u32)(src)<<5) & 0x00000020))
/*	 Fields mbox_21_4	 */
#define MBOX_21_40_WIDTH                                                      1
#define MBOX_21_40_SHIFT                                                      4
#define MBOX_21_40_MASK                                              0x00000010
#define MBOX_21_40_RD(src)                            (((src) & 0x00000010)>>4)
#define MBOX_21_40_SET(dst,src) \
                       (((dst) & ~0x00000010) | (((u32)(src)<<4) & 0x00000010))
/*	 Fields mbox_21_3	 */
#define MBOX_21_30_WIDTH                                                      1
#define MBOX_21_30_SHIFT                                                      3
#define MBOX_21_30_MASK                                              0x00000008
#define MBOX_21_30_RD(src)                            (((src) & 0x00000008)>>3)
#define MBOX_21_30_SET(dst,src) \
                       (((dst) & ~0x00000008) | (((u32)(src)<<3) & 0x00000008))
/*	 Fields mbox_21_2	 */
#define MBOX_21_20_WIDTH                                                      1
#define MBOX_21_20_SHIFT                                                      2
#define MBOX_21_20_MASK                                              0x00000004
#define MBOX_21_20_RD(src)                            (((src) & 0x00000004)>>2)
#define MBOX_21_20_SET(dst,src) \
                       (((dst) & ~0x00000004) | (((u32)(src)<<2) & 0x00000004))
/*	 Fields mbox_21_1	 */
#define MBOX_21_10_WIDTH                                                      1
#define MBOX_21_10_SHIFT                                                      1
#define MBOX_21_10_MASK                                              0x00000002
#define MBOX_21_10_RD(src)                            (((src) & 0x00000002)>>1)
#define MBOX_21_10_SET(dst,src) \
                       (((dst) & ~0x00000002) | (((u32)(src)<<1) & 0x00000002))
/*	 Fields mbox_21_0	 */
#define MBOX_21_00_WIDTH                                                      1
#define MBOX_21_00_SHIFT                                                      0
#define MBOX_21_00_MASK                                              0x00000001
#define MBOX_21_00_RD(src)                               (((src) & 0x00000001))
#define MBOX_21_00_SET(dst,src) \
                          (((dst) & ~0x00000001) | (((u32)(src)) & 0x00000001))

/*	Register csr_enq_status_11	*/ 
/*	 Fields mbox_22_15	 */
#define MBOX_22_151_WIDTH                                                     1
#define MBOX_22_151_SHIFT                                                    31
#define MBOX_22_151_MASK                                             0x80000000
#define MBOX_22_151_RD(src)                          (((src) & 0x80000000)>>31)
#define MBOX_22_151_SET(dst,src) \
                      (((dst) & ~0x80000000) | (((u32)(src)<<31) & 0x80000000))
/*	 Fields mbox_22_14	 */
#define MBOX_22_141_WIDTH                                                     1
#define MBOX_22_141_SHIFT                                                    30
#define MBOX_22_141_MASK                                             0x40000000
#define MBOX_22_141_RD(src)                          (((src) & 0x40000000)>>30)
#define MBOX_22_141_SET(dst,src) \
                      (((dst) & ~0x40000000) | (((u32)(src)<<30) & 0x40000000))
/*	 Fields mbox_22_13	 */
#define MBOX_22_131_WIDTH                                                     1
#define MBOX_22_131_SHIFT                                                    29
#define MBOX_22_131_MASK                                             0x20000000
#define MBOX_22_131_RD(src)                          (((src) & 0x20000000)>>29)
#define MBOX_22_131_SET(dst,src) \
                      (((dst) & ~0x20000000) | (((u32)(src)<<29) & 0x20000000))
/*	 Fields mbox_22_12	 */
#define MBOX_22_121_WIDTH                                                     1
#define MBOX_22_121_SHIFT                                                    28
#define MBOX_22_121_MASK                                             0x10000000
#define MBOX_22_121_RD(src)                          (((src) & 0x10000000)>>28)
#define MBOX_22_121_SET(dst,src) \
                      (((dst) & ~0x10000000) | (((u32)(src)<<28) & 0x10000000))
/*	 Fields mbox_22_11	 */
#define MBOX_22_111_WIDTH                                                     1
#define MBOX_22_111_SHIFT                                                    27
#define MBOX_22_111_MASK                                             0x08000000
#define MBOX_22_111_RD(src)                          (((src) & 0x08000000)>>27)
#define MBOX_22_111_SET(dst,src) \
                      (((dst) & ~0x08000000) | (((u32)(src)<<27) & 0x08000000))
/*	 Fields mbox_22_10	 */
#define MBOX_22_101_WIDTH                                                     1
#define MBOX_22_101_SHIFT                                                    26
#define MBOX_22_101_MASK                                             0x04000000
#define MBOX_22_101_RD(src)                          (((src) & 0x04000000)>>26)
#define MBOX_22_101_SET(dst,src) \
                      (((dst) & ~0x04000000) | (((u32)(src)<<26) & 0x04000000))
/*	 Fields mbox_22_9	 */
#define MBOX_22_91_WIDTH                                                      1
#define MBOX_22_91_SHIFT                                                     25
#define MBOX_22_91_MASK                                              0x02000000
#define MBOX_22_91_RD(src)                           (((src) & 0x02000000)>>25)
#define MBOX_22_91_SET(dst,src) \
                      (((dst) & ~0x02000000) | (((u32)(src)<<25) & 0x02000000))
/*	 Fields mbox_22_8	 */
#define MBOX_22_81_WIDTH                                                      1
#define MBOX_22_81_SHIFT                                                     24
#define MBOX_22_81_MASK                                              0x01000000
#define MBOX_22_81_RD(src)                           (((src) & 0x01000000)>>24)
#define MBOX_22_81_SET(dst,src) \
                      (((dst) & ~0x01000000) | (((u32)(src)<<24) & 0x01000000))
/*	 Fields mbox_22_7	 */
#define MBOX_22_71_WIDTH                                                      1
#define MBOX_22_71_SHIFT                                                     23
#define MBOX_22_71_MASK                                              0x00800000
#define MBOX_22_71_RD(src)                           (((src) & 0x00800000)>>23)
#define MBOX_22_71_SET(dst,src) \
                      (((dst) & ~0x00800000) | (((u32)(src)<<23) & 0x00800000))
/*	 Fields mbox_22_6	 */
#define MBOX_22_61_WIDTH                                                      1
#define MBOX_22_61_SHIFT                                                     22
#define MBOX_22_61_MASK                                              0x00400000
#define MBOX_22_61_RD(src)                           (((src) & 0x00400000)>>22)
#define MBOX_22_61_SET(dst,src) \
                      (((dst) & ~0x00400000) | (((u32)(src)<<22) & 0x00400000))
/*	 Fields mbox_22_5	 */
#define MBOX_22_51_WIDTH                                                      1
#define MBOX_22_51_SHIFT                                                     21
#define MBOX_22_51_MASK                                              0x00200000
#define MBOX_22_51_RD(src)                           (((src) & 0x00200000)>>21)
#define MBOX_22_51_SET(dst,src) \
                      (((dst) & ~0x00200000) | (((u32)(src)<<21) & 0x00200000))
/*	 Fields mbox_22_4	 */
#define MBOX_22_41_WIDTH                                                      1
#define MBOX_22_41_SHIFT                                                     20
#define MBOX_22_41_MASK                                              0x00100000
#define MBOX_22_41_RD(src)                           (((src) & 0x00100000)>>20)
#define MBOX_22_41_SET(dst,src) \
                      (((dst) & ~0x00100000) | (((u32)(src)<<20) & 0x00100000))
/*	 Fields mbox_22_3	 */
#define MBOX_22_31_WIDTH                                                      1
#define MBOX_22_31_SHIFT                                                     19
#define MBOX_22_31_MASK                                              0x00080000
#define MBOX_22_31_RD(src)                           (((src) & 0x00080000)>>19)
#define MBOX_22_31_SET(dst,src) \
                      (((dst) & ~0x00080000) | (((u32)(src)<<19) & 0x00080000))
/*	 Fields mbox_22_2	 */
#define MBOX_22_21_WIDTH                                                      1
#define MBOX_22_21_SHIFT                                                     18
#define MBOX_22_21_MASK                                              0x00040000
#define MBOX_22_21_RD(src)                           (((src) & 0x00040000)>>18)
#define MBOX_22_21_SET(dst,src) \
                      (((dst) & ~0x00040000) | (((u32)(src)<<18) & 0x00040000))
/*	 Fields mbox_22_1	 */
#define MBOX_22_11_WIDTH                                                      1
#define MBOX_22_11_SHIFT                                                     17
#define MBOX_22_11_MASK                                              0x00020000
#define MBOX_22_11_RD(src)                           (((src) & 0x00020000)>>17)
#define MBOX_22_11_SET(dst,src) \
                      (((dst) & ~0x00020000) | (((u32)(src)<<17) & 0x00020000))
/*	 Fields mbox_22_0	 */
#define MBOX_22_01_WIDTH                                                      1
#define MBOX_22_01_SHIFT                                                     16
#define MBOX_22_01_MASK                                              0x00010000
#define MBOX_22_01_RD(src)                           (((src) & 0x00010000)>>16)
#define MBOX_22_01_SET(dst,src) \
                      (((dst) & ~0x00010000) | (((u32)(src)<<16) & 0x00010000))
/*	 Fields mbox_23_15	 */
#define MBOX_23_151_WIDTH                                                     1
#define MBOX_23_151_SHIFT                                                    15
#define MBOX_23_151_MASK                                             0x00008000
#define MBOX_23_151_RD(src)                          (((src) & 0x00008000)>>15)
#define MBOX_23_151_SET(dst,src) \
                      (((dst) & ~0x00008000) | (((u32)(src)<<15) & 0x00008000))
/*	 Fields mbox_23_14	 */
#define MBOX_23_141_WIDTH                                                     1
#define MBOX_23_141_SHIFT                                                    14
#define MBOX_23_141_MASK                                             0x00004000
#define MBOX_23_141_RD(src)                          (((src) & 0x00004000)>>14)
#define MBOX_23_141_SET(dst,src) \
                      (((dst) & ~0x00004000) | (((u32)(src)<<14) & 0x00004000))
/*	 Fields mbox_23_13	 */
#define MBOX_23_131_WIDTH                                                     1
#define MBOX_23_131_SHIFT                                                    13
#define MBOX_23_131_MASK                                             0x00002000
#define MBOX_23_131_RD(src)                          (((src) & 0x00002000)>>13)
#define MBOX_23_131_SET(dst,src) \
                      (((dst) & ~0x00002000) | (((u32)(src)<<13) & 0x00002000))
/*	 Fields mbox_23_12	 */
#define MBOX_23_121_WIDTH                                                     1
#define MBOX_23_121_SHIFT                                                    12
#define MBOX_23_121_MASK                                             0x00001000
#define MBOX_23_121_RD(src)                          (((src) & 0x00001000)>>12)
#define MBOX_23_121_SET(dst,src) \
                      (((dst) & ~0x00001000) | (((u32)(src)<<12) & 0x00001000))
/*	 Fields mbox_23_11	 */
#define MBOX_23_111_WIDTH                                                     1
#define MBOX_23_111_SHIFT                                                    11
#define MBOX_23_111_MASK                                             0x00000800
#define MBOX_23_111_RD(src)                          (((src) & 0x00000800)>>11)
#define MBOX_23_111_SET(dst,src) \
                      (((dst) & ~0x00000800) | (((u32)(src)<<11) & 0x00000800))
/*	 Fields mbox_23_10	 */
#define MBOX_23_101_WIDTH                                                     1
#define MBOX_23_101_SHIFT                                                    10
#define MBOX_23_101_MASK                                             0x00000400
#define MBOX_23_101_RD(src)                          (((src) & 0x00000400)>>10)
#define MBOX_23_101_SET(dst,src) \
                      (((dst) & ~0x00000400) | (((u32)(src)<<10) & 0x00000400))
/*	 Fields mbox_23_9	 */
#define MBOX_23_91_WIDTH                                                      1
#define MBOX_23_91_SHIFT                                                      9
#define MBOX_23_91_MASK                                              0x00000200
#define MBOX_23_91_RD(src)                            (((src) & 0x00000200)>>9)
#define MBOX_23_91_SET(dst,src) \
                       (((dst) & ~0x00000200) | (((u32)(src)<<9) & 0x00000200))
/*	 Fields mbox_23_8	 */
#define MBOX_23_81_WIDTH                                                      1
#define MBOX_23_81_SHIFT                                                      8
#define MBOX_23_81_MASK                                              0x00000100
#define MBOX_23_81_RD(src)                            (((src) & 0x00000100)>>8)
#define MBOX_23_81_SET(dst,src) \
                       (((dst) & ~0x00000100) | (((u32)(src)<<8) & 0x00000100))
/*	 Fields mbox_23_7	 */
#define MBOX_23_71_WIDTH                                                      1
#define MBOX_23_71_SHIFT                                                      7
#define MBOX_23_71_MASK                                              0x00000080
#define MBOX_23_71_RD(src)                            (((src) & 0x00000080)>>7)
#define MBOX_23_71_SET(dst,src) \
                       (((dst) & ~0x00000080) | (((u32)(src)<<7) & 0x00000080))
/*	 Fields mbox_23_6	 */
#define MBOX_23_61_WIDTH                                                      1
#define MBOX_23_61_SHIFT                                                      6
#define MBOX_23_61_MASK                                              0x00000040
#define MBOX_23_61_RD(src)                            (((src) & 0x00000040)>>6)
#define MBOX_23_61_SET(dst,src) \
                       (((dst) & ~0x00000040) | (((u32)(src)<<6) & 0x00000040))
/*	 Fields mbox_23_5	 */
#define MBOX_23_51_WIDTH                                                      1
#define MBOX_23_51_SHIFT                                                      5
#define MBOX_23_51_MASK                                              0x00000020
#define MBOX_23_51_RD(src)                            (((src) & 0x00000020)>>5)
#define MBOX_23_51_SET(dst,src) \
                       (((dst) & ~0x00000020) | (((u32)(src)<<5) & 0x00000020))
/*	 Fields mbox_23_4	 */
#define MBOX_23_41_WIDTH                                                      1
#define MBOX_23_41_SHIFT                                                      4
#define MBOX_23_41_MASK                                              0x00000010
#define MBOX_23_41_RD(src)                            (((src) & 0x00000010)>>4)
#define MBOX_23_41_SET(dst,src) \
                       (((dst) & ~0x00000010) | (((u32)(src)<<4) & 0x00000010))
/*	 Fields mbox_23_3	 */
#define MBOX_23_31_WIDTH                                                      1
#define MBOX_23_31_SHIFT                                                      3
#define MBOX_23_31_MASK                                              0x00000008
#define MBOX_23_31_RD(src)                            (((src) & 0x00000008)>>3)
#define MBOX_23_31_SET(dst,src) \
                       (((dst) & ~0x00000008) | (((u32)(src)<<3) & 0x00000008))
/*	 Fields mbox_23_2	 */
#define MBOX_23_21_WIDTH                                                      1
#define MBOX_23_21_SHIFT                                                      2
#define MBOX_23_21_MASK                                              0x00000004
#define MBOX_23_21_RD(src)                            (((src) & 0x00000004)>>2)
#define MBOX_23_21_SET(dst,src) \
                       (((dst) & ~0x00000004) | (((u32)(src)<<2) & 0x00000004))
/*	 Fields mbox_23_1	 */
#define MBOX_23_11_WIDTH                                                      1
#define MBOX_23_11_SHIFT                                                      1
#define MBOX_23_11_MASK                                              0x00000002
#define MBOX_23_11_RD(src)                            (((src) & 0x00000002)>>1)
#define MBOX_23_11_SET(dst,src) \
                       (((dst) & ~0x00000002) | (((u32)(src)<<1) & 0x00000002))
/*	 Fields mbox_23_0	 */
#define MBOX_23_01_WIDTH                                                      1
#define MBOX_23_01_SHIFT                                                      0
#define MBOX_23_01_MASK                                              0x00000001
#define MBOX_23_01_RD(src)                               (((src) & 0x00000001))
#define MBOX_23_01_SET(dst,src) \
                          (((dst) & ~0x00000001) | (((u32)(src)) & 0x00000001))

/*	Register csr_enq_status_12	*/ 
/*	 Fields mbox_24_15	 */
#define MBOX_24_152_WIDTH                                                     1
#define MBOX_24_152_SHIFT                                                    31
#define MBOX_24_152_MASK                                             0x80000000
#define MBOX_24_152_RD(src)                          (((src) & 0x80000000)>>31)
#define MBOX_24_152_SET(dst,src) \
                      (((dst) & ~0x80000000) | (((u32)(src)<<31) & 0x80000000))
/*	 Fields mbox_24_14	 */
#define MBOX_24_142_WIDTH                                                     1
#define MBOX_24_142_SHIFT                                                    30
#define MBOX_24_142_MASK                                             0x40000000
#define MBOX_24_142_RD(src)                          (((src) & 0x40000000)>>30)
#define MBOX_24_142_SET(dst,src) \
                      (((dst) & ~0x40000000) | (((u32)(src)<<30) & 0x40000000))
/*	 Fields mbox_24_13	 */
#define MBOX_24_132_WIDTH                                                     1
#define MBOX_24_132_SHIFT                                                    29
#define MBOX_24_132_MASK                                             0x20000000
#define MBOX_24_132_RD(src)                          (((src) & 0x20000000)>>29)
#define MBOX_24_132_SET(dst,src) \
                      (((dst) & ~0x20000000) | (((u32)(src)<<29) & 0x20000000))
/*	 Fields mbox_24_12	 */
#define MBOX_24_122_WIDTH                                                     1
#define MBOX_24_122_SHIFT                                                    28
#define MBOX_24_122_MASK                                             0x10000000
#define MBOX_24_122_RD(src)                          (((src) & 0x10000000)>>28)
#define MBOX_24_122_SET(dst,src) \
                      (((dst) & ~0x10000000) | (((u32)(src)<<28) & 0x10000000))
/*	 Fields mbox_24_11	 */
#define MBOX_24_112_WIDTH                                                     1
#define MBOX_24_112_SHIFT                                                    27
#define MBOX_24_112_MASK                                             0x08000000
#define MBOX_24_112_RD(src)                          (((src) & 0x08000000)>>27)
#define MBOX_24_112_SET(dst,src) \
                      (((dst) & ~0x08000000) | (((u32)(src)<<27) & 0x08000000))
/*	 Fields mbox_24_10	 */
#define MBOX_24_102_WIDTH                                                     1
#define MBOX_24_102_SHIFT                                                    26
#define MBOX_24_102_MASK                                             0x04000000
#define MBOX_24_102_RD(src)                          (((src) & 0x04000000)>>26)
#define MBOX_24_102_SET(dst,src) \
                      (((dst) & ~0x04000000) | (((u32)(src)<<26) & 0x04000000))
/*	 Fields mbox_24_9	 */
#define MBOX_24_92_WIDTH                                                      1
#define MBOX_24_92_SHIFT                                                     25
#define MBOX_24_92_MASK                                              0x02000000
#define MBOX_24_92_RD(src)                           (((src) & 0x02000000)>>25)
#define MBOX_24_92_SET(dst,src) \
                      (((dst) & ~0x02000000) | (((u32)(src)<<25) & 0x02000000))
/*	 Fields mbox_24_8	 */
#define MBOX_24_82_WIDTH                                                      1
#define MBOX_24_82_SHIFT                                                     24
#define MBOX_24_82_MASK                                              0x01000000
#define MBOX_24_82_RD(src)                           (((src) & 0x01000000)>>24)
#define MBOX_24_82_SET(dst,src) \
                      (((dst) & ~0x01000000) | (((u32)(src)<<24) & 0x01000000))
/*	 Fields mbox_24_7	 */
#define MBOX_24_72_WIDTH                                                      1
#define MBOX_24_72_SHIFT                                                     23
#define MBOX_24_72_MASK                                              0x00800000
#define MBOX_24_72_RD(src)                           (((src) & 0x00800000)>>23)
#define MBOX_24_72_SET(dst,src) \
                      (((dst) & ~0x00800000) | (((u32)(src)<<23) & 0x00800000))
/*	 Fields mbox_24_6	 */
#define MBOX_24_62_WIDTH                                                      1
#define MBOX_24_62_SHIFT                                                     22
#define MBOX_24_62_MASK                                              0x00400000
#define MBOX_24_62_RD(src)                           (((src) & 0x00400000)>>22)
#define MBOX_24_62_SET(dst,src) \
                      (((dst) & ~0x00400000) | (((u32)(src)<<22) & 0x00400000))
/*	 Fields mbox_24_5	 */
#define MBOX_24_52_WIDTH                                                      1
#define MBOX_24_52_SHIFT                                                     21
#define MBOX_24_52_MASK                                              0x00200000
#define MBOX_24_52_RD(src)                           (((src) & 0x00200000)>>21)
#define MBOX_24_52_SET(dst,src) \
                      (((dst) & ~0x00200000) | (((u32)(src)<<21) & 0x00200000))
/*	 Fields mbox_24_4	 */
#define MBOX_24_42_WIDTH                                                      1
#define MBOX_24_42_SHIFT                                                     20
#define MBOX_24_42_MASK                                              0x00100000
#define MBOX_24_42_RD(src)                           (((src) & 0x00100000)>>20)
#define MBOX_24_42_SET(dst,src) \
                      (((dst) & ~0x00100000) | (((u32)(src)<<20) & 0x00100000))
/*	 Fields mbox_24_3	 */
#define MBOX_24_32_WIDTH                                                      1
#define MBOX_24_32_SHIFT                                                     19
#define MBOX_24_32_MASK                                              0x00080000
#define MBOX_24_32_RD(src)                           (((src) & 0x00080000)>>19)
#define MBOX_24_32_SET(dst,src) \
                      (((dst) & ~0x00080000) | (((u32)(src)<<19) & 0x00080000))
/*	 Fields mbox_24_2	 */
#define MBOX_24_22_WIDTH                                                      1
#define MBOX_24_22_SHIFT                                                     18
#define MBOX_24_22_MASK                                              0x00040000
#define MBOX_24_22_RD(src)                           (((src) & 0x00040000)>>18)
#define MBOX_24_22_SET(dst,src) \
                      (((dst) & ~0x00040000) | (((u32)(src)<<18) & 0x00040000))
/*	 Fields mbox_24_1	 */
#define MBOX_24_12_WIDTH                                                      1
#define MBOX_24_12_SHIFT                                                     17
#define MBOX_24_12_MASK                                              0x00020000
#define MBOX_24_12_RD(src)                           (((src) & 0x00020000)>>17)
#define MBOX_24_12_SET(dst,src) \
                      (((dst) & ~0x00020000) | (((u32)(src)<<17) & 0x00020000))
/*	 Fields mbox_24_0	 */
#define MBOX_24_02_WIDTH                                                      1
#define MBOX_24_02_SHIFT                                                     16
#define MBOX_24_02_MASK                                              0x00010000
#define MBOX_24_02_RD(src)                           (((src) & 0x00010000)>>16)
#define MBOX_24_02_SET(dst,src) \
                      (((dst) & ~0x00010000) | (((u32)(src)<<16) & 0x00010000))
/*	 Fields mbox_25_15	 */
#define MBOX_25_152_WIDTH                                                     1
#define MBOX_25_152_SHIFT                                                    15
#define MBOX_25_152_MASK                                             0x00008000
#define MBOX_25_152_RD(src)                          (((src) & 0x00008000)>>15)
#define MBOX_25_152_SET(dst,src) \
                      (((dst) & ~0x00008000) | (((u32)(src)<<15) & 0x00008000))
/*	 Fields mbox_25_14	 */
#define MBOX_25_142_WIDTH                                                     1
#define MBOX_25_142_SHIFT                                                    14
#define MBOX_25_142_MASK                                             0x00004000
#define MBOX_25_142_RD(src)                          (((src) & 0x00004000)>>14)
#define MBOX_25_142_SET(dst,src) \
                      (((dst) & ~0x00004000) | (((u32)(src)<<14) & 0x00004000))
/*	 Fields mbox_25_13	 */
#define MBOX_25_132_WIDTH                                                     1
#define MBOX_25_132_SHIFT                                                    13
#define MBOX_25_132_MASK                                             0x00002000
#define MBOX_25_132_RD(src)                          (((src) & 0x00002000)>>13)
#define MBOX_25_132_SET(dst,src) \
                      (((dst) & ~0x00002000) | (((u32)(src)<<13) & 0x00002000))
/*	 Fields mbox_25_12	 */
#define MBOX_25_122_WIDTH                                                     1
#define MBOX_25_122_SHIFT                                                    12
#define MBOX_25_122_MASK                                             0x00001000
#define MBOX_25_122_RD(src)                          (((src) & 0x00001000)>>12)
#define MBOX_25_122_SET(dst,src) \
                      (((dst) & ~0x00001000) | (((u32)(src)<<12) & 0x00001000))
/*	 Fields mbox_25_11	 */
#define MBOX_25_112_WIDTH                                                     1
#define MBOX_25_112_SHIFT                                                    11
#define MBOX_25_112_MASK                                             0x00000800
#define MBOX_25_112_RD(src)                          (((src) & 0x00000800)>>11)
#define MBOX_25_112_SET(dst,src) \
                      (((dst) & ~0x00000800) | (((u32)(src)<<11) & 0x00000800))
/*	 Fields mbox_25_10	 */
#define MBOX_25_102_WIDTH                                                     1
#define MBOX_25_102_SHIFT                                                    10
#define MBOX_25_102_MASK                                             0x00000400
#define MBOX_25_102_RD(src)                          (((src) & 0x00000400)>>10)
#define MBOX_25_102_SET(dst,src) \
                      (((dst) & ~0x00000400) | (((u32)(src)<<10) & 0x00000400))
/*	 Fields mbox_25_9	 */
#define MBOX_25_92_WIDTH                                                      1
#define MBOX_25_92_SHIFT                                                      9
#define MBOX_25_92_MASK                                              0x00000200
#define MBOX_25_92_RD(src)                            (((src) & 0x00000200)>>9)
#define MBOX_25_92_SET(dst,src) \
                       (((dst) & ~0x00000200) | (((u32)(src)<<9) & 0x00000200))
/*	 Fields mbox_25_8	 */
#define MBOX_25_82_WIDTH                                                      1
#define MBOX_25_82_SHIFT                                                      8
#define MBOX_25_82_MASK                                              0x00000100
#define MBOX_25_82_RD(src)                            (((src) & 0x00000100)>>8)
#define MBOX_25_82_SET(dst,src) \
                       (((dst) & ~0x00000100) | (((u32)(src)<<8) & 0x00000100))
/*	 Fields mbox_25_7	 */
#define MBOX_25_72_WIDTH                                                      1
#define MBOX_25_72_SHIFT                                                      7
#define MBOX_25_72_MASK                                              0x00000080
#define MBOX_25_72_RD(src)                            (((src) & 0x00000080)>>7)
#define MBOX_25_72_SET(dst,src) \
                       (((dst) & ~0x00000080) | (((u32)(src)<<7) & 0x00000080))
/*	 Fields mbox_25_6	 */
#define MBOX_25_62_WIDTH                                                      1
#define MBOX_25_62_SHIFT                                                      6
#define MBOX_25_62_MASK                                              0x00000040
#define MBOX_25_62_RD(src)                            (((src) & 0x00000040)>>6)
#define MBOX_25_62_SET(dst,src) \
                       (((dst) & ~0x00000040) | (((u32)(src)<<6) & 0x00000040))
/*	 Fields mbox_25_5	 */
#define MBOX_25_52_WIDTH                                                      1
#define MBOX_25_52_SHIFT                                                      5
#define MBOX_25_52_MASK                                              0x00000020
#define MBOX_25_52_RD(src)                            (((src) & 0x00000020)>>5)
#define MBOX_25_52_SET(dst,src) \
                       (((dst) & ~0x00000020) | (((u32)(src)<<5) & 0x00000020))
/*	 Fields mbox_25_4	 */
#define MBOX_25_42_WIDTH                                                      1
#define MBOX_25_42_SHIFT                                                      4
#define MBOX_25_42_MASK                                              0x00000010
#define MBOX_25_42_RD(src)                            (((src) & 0x00000010)>>4)
#define MBOX_25_42_SET(dst,src) \
                       (((dst) & ~0x00000010) | (((u32)(src)<<4) & 0x00000010))
/*	 Fields mbox_25_3	 */
#define MBOX_25_32_WIDTH                                                      1
#define MBOX_25_32_SHIFT                                                      3
#define MBOX_25_32_MASK                                              0x00000008
#define MBOX_25_32_RD(src)                            (((src) & 0x00000008)>>3)
#define MBOX_25_32_SET(dst,src) \
                       (((dst) & ~0x00000008) | (((u32)(src)<<3) & 0x00000008))
/*	 Fields mbox_25_2	 */
#define MBOX_25_22_WIDTH                                                      1
#define MBOX_25_22_SHIFT                                                      2
#define MBOX_25_22_MASK                                              0x00000004
#define MBOX_25_22_RD(src)                            (((src) & 0x00000004)>>2)
#define MBOX_25_22_SET(dst,src) \
                       (((dst) & ~0x00000004) | (((u32)(src)<<2) & 0x00000004))
/*	 Fields mbox_25_1	 */
#define MBOX_25_12_WIDTH                                                      1
#define MBOX_25_12_SHIFT                                                      1
#define MBOX_25_12_MASK                                              0x00000002
#define MBOX_25_12_RD(src)                            (((src) & 0x00000002)>>1)
#define MBOX_25_12_SET(dst,src) \
                       (((dst) & ~0x00000002) | (((u32)(src)<<1) & 0x00000002))
/*	 Fields mbox_25_0	 */
#define MBOX_25_02_WIDTH                                                      1
#define MBOX_25_02_SHIFT                                                      0
#define MBOX_25_02_MASK                                              0x00000001
#define MBOX_25_02_RD(src)                               (((src) & 0x00000001))
#define MBOX_25_02_SET(dst,src) \
                          (((dst) & ~0x00000001) | (((u32)(src)) & 0x00000001))

/*	Register csr_enq_status_13	*/ 
/*	 Fields mbox_26_15	 */
#define MBOX_26_153_WIDTH                                                     1
#define MBOX_26_153_SHIFT                                                    31
#define MBOX_26_153_MASK                                             0x80000000
#define MBOX_26_153_RD(src)                          (((src) & 0x80000000)>>31)
#define MBOX_26_153_SET(dst,src) \
                      (((dst) & ~0x80000000) | (((u32)(src)<<31) & 0x80000000))
/*	 Fields mbox_26_14	 */
#define MBOX_26_143_WIDTH                                                     1
#define MBOX_26_143_SHIFT                                                    30
#define MBOX_26_143_MASK                                             0x40000000
#define MBOX_26_143_RD(src)                          (((src) & 0x40000000)>>30)
#define MBOX_26_143_SET(dst,src) \
                      (((dst) & ~0x40000000) | (((u32)(src)<<30) & 0x40000000))
/*	 Fields mbox_26_13	 */
#define MBOX_26_133_WIDTH                                                     1
#define MBOX_26_133_SHIFT                                                    29
#define MBOX_26_133_MASK                                             0x20000000
#define MBOX_26_133_RD(src)                          (((src) & 0x20000000)>>29)
#define MBOX_26_133_SET(dst,src) \
                      (((dst) & ~0x20000000) | (((u32)(src)<<29) & 0x20000000))
/*	 Fields mbox_26_12	 */
#define MBOX_26_123_WIDTH                                                     1
#define MBOX_26_123_SHIFT                                                    28
#define MBOX_26_123_MASK                                             0x10000000
#define MBOX_26_123_RD(src)                          (((src) & 0x10000000)>>28)
#define MBOX_26_123_SET(dst,src) \
                      (((dst) & ~0x10000000) | (((u32)(src)<<28) & 0x10000000))
/*	 Fields mbox_26_11	 */
#define MBOX_26_113_WIDTH                                                     1
#define MBOX_26_113_SHIFT                                                    27
#define MBOX_26_113_MASK                                             0x08000000
#define MBOX_26_113_RD(src)                          (((src) & 0x08000000)>>27)
#define MBOX_26_113_SET(dst,src) \
                      (((dst) & ~0x08000000) | (((u32)(src)<<27) & 0x08000000))
/*	 Fields mbox_26_10	 */
#define MBOX_26_103_WIDTH                                                     1
#define MBOX_26_103_SHIFT                                                    26
#define MBOX_26_103_MASK                                             0x04000000
#define MBOX_26_103_RD(src)                          (((src) & 0x04000000)>>26)
#define MBOX_26_103_SET(dst,src) \
                      (((dst) & ~0x04000000) | (((u32)(src)<<26) & 0x04000000))
/*	 Fields mbox_26_9	 */
#define MBOX_26_93_WIDTH                                                      1
#define MBOX_26_93_SHIFT                                                     25
#define MBOX_26_93_MASK                                              0x02000000
#define MBOX_26_93_RD(src)                           (((src) & 0x02000000)>>25)
#define MBOX_26_93_SET(dst,src) \
                      (((dst) & ~0x02000000) | (((u32)(src)<<25) & 0x02000000))
/*	 Fields mbox_26_8	 */
#define MBOX_26_83_WIDTH                                                      1
#define MBOX_26_83_SHIFT                                                     24
#define MBOX_26_83_MASK                                              0x01000000
#define MBOX_26_83_RD(src)                           (((src) & 0x01000000)>>24)
#define MBOX_26_83_SET(dst,src) \
                      (((dst) & ~0x01000000) | (((u32)(src)<<24) & 0x01000000))
/*	 Fields mbox_26_7	 */
#define MBOX_26_73_WIDTH                                                      1
#define MBOX_26_73_SHIFT                                                     23
#define MBOX_26_73_MASK                                              0x00800000
#define MBOX_26_73_RD(src)                           (((src) & 0x00800000)>>23)
#define MBOX_26_73_SET(dst,src) \
                      (((dst) & ~0x00800000) | (((u32)(src)<<23) & 0x00800000))
/*	 Fields mbox_26_6	 */
#define MBOX_26_63_WIDTH                                                      1
#define MBOX_26_63_SHIFT                                                     22
#define MBOX_26_63_MASK                                              0x00400000
#define MBOX_26_63_RD(src)                           (((src) & 0x00400000)>>22)
#define MBOX_26_63_SET(dst,src) \
                      (((dst) & ~0x00400000) | (((u32)(src)<<22) & 0x00400000))
/*	 Fields mbox_26_5	 */
#define MBOX_26_53_WIDTH                                                      1
#define MBOX_26_53_SHIFT                                                     21
#define MBOX_26_53_MASK                                              0x00200000
#define MBOX_26_53_RD(src)                           (((src) & 0x00200000)>>21)
#define MBOX_26_53_SET(dst,src) \
                      (((dst) & ~0x00200000) | (((u32)(src)<<21) & 0x00200000))
/*	 Fields mbox_26_4	 */
#define MBOX_26_43_WIDTH                                                      1
#define MBOX_26_43_SHIFT                                                     20
#define MBOX_26_43_MASK                                              0x00100000
#define MBOX_26_43_RD(src)                           (((src) & 0x00100000)>>20)
#define MBOX_26_43_SET(dst,src) \
                      (((dst) & ~0x00100000) | (((u32)(src)<<20) & 0x00100000))
/*	 Fields mbox_26_3	 */
#define MBOX_26_33_WIDTH                                                      1
#define MBOX_26_33_SHIFT                                                     19
#define MBOX_26_33_MASK                                              0x00080000
#define MBOX_26_33_RD(src)                           (((src) & 0x00080000)>>19)
#define MBOX_26_33_SET(dst,src) \
                      (((dst) & ~0x00080000) | (((u32)(src)<<19) & 0x00080000))
/*	 Fields mbox_26_2	 */
#define MBOX_26_23_WIDTH                                                      1
#define MBOX_26_23_SHIFT                                                     18
#define MBOX_26_23_MASK                                              0x00040000
#define MBOX_26_23_RD(src)                           (((src) & 0x00040000)>>18)
#define MBOX_26_23_SET(dst,src) \
                      (((dst) & ~0x00040000) | (((u32)(src)<<18) & 0x00040000))
/*	 Fields mbox_26_1	 */
#define MBOX_26_13_WIDTH                                                      1
#define MBOX_26_13_SHIFT                                                     17
#define MBOX_26_13_MASK                                              0x00020000
#define MBOX_26_13_RD(src)                           (((src) & 0x00020000)>>17)
#define MBOX_26_13_SET(dst,src) \
                      (((dst) & ~0x00020000) | (((u32)(src)<<17) & 0x00020000))
/*	 Fields mbox_26_0	 */
#define MBOX_26_03_WIDTH                                                      1
#define MBOX_26_03_SHIFT                                                     16
#define MBOX_26_03_MASK                                              0x00010000
#define MBOX_26_03_RD(src)                           (((src) & 0x00010000)>>16)
#define MBOX_26_03_SET(dst,src) \
                      (((dst) & ~0x00010000) | (((u32)(src)<<16) & 0x00010000))
/*	 Fields mbox_27_15	 */
#define MBOX_27_153_WIDTH                                                     1
#define MBOX_27_153_SHIFT                                                    15
#define MBOX_27_153_MASK                                             0x00008000
#define MBOX_27_153_RD(src)                          (((src) & 0x00008000)>>15)
#define MBOX_27_153_SET(dst,src) \
                      (((dst) & ~0x00008000) | (((u32)(src)<<15) & 0x00008000))
/*	 Fields mbox_27_14	 */
#define MBOX_27_143_WIDTH                                                     1
#define MBOX_27_143_SHIFT                                                    14
#define MBOX_27_143_MASK                                             0x00004000
#define MBOX_27_143_RD(src)                          (((src) & 0x00004000)>>14)
#define MBOX_27_143_SET(dst,src) \
                      (((dst) & ~0x00004000) | (((u32)(src)<<14) & 0x00004000))
/*	 Fields mbox_27_13	 */
#define MBOX_27_133_WIDTH                                                     1
#define MBOX_27_133_SHIFT                                                    13
#define MBOX_27_133_MASK                                             0x00002000
#define MBOX_27_133_RD(src)                          (((src) & 0x00002000)>>13)
#define MBOX_27_133_SET(dst,src) \
                      (((dst) & ~0x00002000) | (((u32)(src)<<13) & 0x00002000))
/*	 Fields mbox_27_12	 */
#define MBOX_27_123_WIDTH                                                     1
#define MBOX_27_123_SHIFT                                                    12
#define MBOX_27_123_MASK                                             0x00001000
#define MBOX_27_123_RD(src)                          (((src) & 0x00001000)>>12)
#define MBOX_27_123_SET(dst,src) \
                      (((dst) & ~0x00001000) | (((u32)(src)<<12) & 0x00001000))
/*	 Fields mbox_27_11	 */
#define MBOX_27_113_WIDTH                                                     1
#define MBOX_27_113_SHIFT                                                    11
#define MBOX_27_113_MASK                                             0x00000800
#define MBOX_27_113_RD(src)                          (((src) & 0x00000800)>>11)
#define MBOX_27_113_SET(dst,src) \
                      (((dst) & ~0x00000800) | (((u32)(src)<<11) & 0x00000800))
/*	 Fields mbox_27_10	 */
#define MBOX_27_103_WIDTH                                                     1
#define MBOX_27_103_SHIFT                                                    10
#define MBOX_27_103_MASK                                             0x00000400
#define MBOX_27_103_RD(src)                          (((src) & 0x00000400)>>10)
#define MBOX_27_103_SET(dst,src) \
                      (((dst) & ~0x00000400) | (((u32)(src)<<10) & 0x00000400))
/*	 Fields mbox_27_9	 */
#define MBOX_27_93_WIDTH                                                      1
#define MBOX_27_93_SHIFT                                                      9
#define MBOX_27_93_MASK                                              0x00000200
#define MBOX_27_93_RD(src)                            (((src) & 0x00000200)>>9)
#define MBOX_27_93_SET(dst,src) \
                       (((dst) & ~0x00000200) | (((u32)(src)<<9) & 0x00000200))
/*	 Fields mbox_27_8	 */
#define MBOX_27_83_WIDTH                                                      1
#define MBOX_27_83_SHIFT                                                      8
#define MBOX_27_83_MASK                                              0x00000100
#define MBOX_27_83_RD(src)                            (((src) & 0x00000100)>>8)
#define MBOX_27_83_SET(dst,src) \
                       (((dst) & ~0x00000100) | (((u32)(src)<<8) & 0x00000100))
/*	 Fields mbox_27_7	 */
#define MBOX_27_73_WIDTH                                                      1
#define MBOX_27_73_SHIFT                                                      7
#define MBOX_27_73_MASK                                              0x00000080
#define MBOX_27_73_RD(src)                            (((src) & 0x00000080)>>7)
#define MBOX_27_73_SET(dst,src) \
                       (((dst) & ~0x00000080) | (((u32)(src)<<7) & 0x00000080))
/*	 Fields mbox_27_6	 */
#define MBOX_27_63_WIDTH                                                      1
#define MBOX_27_63_SHIFT                                                      6
#define MBOX_27_63_MASK                                              0x00000040
#define MBOX_27_63_RD(src)                            (((src) & 0x00000040)>>6)
#define MBOX_27_63_SET(dst,src) \
                       (((dst) & ~0x00000040) | (((u32)(src)<<6) & 0x00000040))
/*	 Fields mbox_27_5	 */
#define MBOX_27_53_WIDTH                                                      1
#define MBOX_27_53_SHIFT                                                      5
#define MBOX_27_53_MASK                                              0x00000020
#define MBOX_27_53_RD(src)                            (((src) & 0x00000020)>>5)
#define MBOX_27_53_SET(dst,src) \
                       (((dst) & ~0x00000020) | (((u32)(src)<<5) & 0x00000020))
/*	 Fields mbox_27_4	 */
#define MBOX_27_43_WIDTH                                                      1
#define MBOX_27_43_SHIFT                                                      4
#define MBOX_27_43_MASK                                              0x00000010
#define MBOX_27_43_RD(src)                            (((src) & 0x00000010)>>4)
#define MBOX_27_43_SET(dst,src) \
                       (((dst) & ~0x00000010) | (((u32)(src)<<4) & 0x00000010))
/*	 Fields mbox_27_3	 */
#define MBOX_27_33_WIDTH                                                      1
#define MBOX_27_33_SHIFT                                                      3
#define MBOX_27_33_MASK                                              0x00000008
#define MBOX_27_33_RD(src)                            (((src) & 0x00000008)>>3)
#define MBOX_27_33_SET(dst,src) \
                       (((dst) & ~0x00000008) | (((u32)(src)<<3) & 0x00000008))
/*	 Fields mbox_27_2	 */
#define MBOX_27_23_WIDTH                                                      1
#define MBOX_27_23_SHIFT                                                      2
#define MBOX_27_23_MASK                                              0x00000004
#define MBOX_27_23_RD(src)                            (((src) & 0x00000004)>>2)
#define MBOX_27_23_SET(dst,src) \
                       (((dst) & ~0x00000004) | (((u32)(src)<<2) & 0x00000004))
/*	 Fields mbox_27_1	 */
#define MBOX_27_13_WIDTH                                                      1
#define MBOX_27_13_SHIFT                                                      1
#define MBOX_27_13_MASK                                              0x00000002
#define MBOX_27_13_RD(src)                            (((src) & 0x00000002)>>1)
#define MBOX_27_13_SET(dst,src) \
                       (((dst) & ~0x00000002) | (((u32)(src)<<1) & 0x00000002))
/*	 Fields mbox_27_0	 */
#define MBOX_27_03_WIDTH                                                      1
#define MBOX_27_03_SHIFT                                                      0
#define MBOX_27_03_MASK                                              0x00000001
#define MBOX_27_03_RD(src)                               (((src) & 0x00000001))
#define MBOX_27_03_SET(dst,src) \
                          (((dst) & ~0x00000001) | (((u32)(src)) & 0x00000001))

/*	Register csr_enq_status_14	*/ 
/*	 Fields mbox_28_15	 */
#define MBOX_28_154_WIDTH                                                     1
#define MBOX_28_154_SHIFT                                                    31
#define MBOX_28_154_MASK                                             0x80000000
#define MBOX_28_154_RD(src)                          (((src) & 0x80000000)>>31)
#define MBOX_28_154_SET(dst,src) \
                      (((dst) & ~0x80000000) | (((u32)(src)<<31) & 0x80000000))
/*	 Fields mbox_28_14	 */
#define MBOX_28_144_WIDTH                                                     1
#define MBOX_28_144_SHIFT                                                    30
#define MBOX_28_144_MASK                                             0x40000000
#define MBOX_28_144_RD(src)                          (((src) & 0x40000000)>>30)
#define MBOX_28_144_SET(dst,src) \
                      (((dst) & ~0x40000000) | (((u32)(src)<<30) & 0x40000000))
/*	 Fields mbox_28_13	 */
#define MBOX_28_134_WIDTH                                                     1
#define MBOX_28_134_SHIFT                                                    29
#define MBOX_28_134_MASK                                             0x20000000
#define MBOX_28_134_RD(src)                          (((src) & 0x20000000)>>29)
#define MBOX_28_134_SET(dst,src) \
                      (((dst) & ~0x20000000) | (((u32)(src)<<29) & 0x20000000))
/*	 Fields mbox_28_12	 */
#define MBOX_28_124_WIDTH                                                     1
#define MBOX_28_124_SHIFT                                                    28
#define MBOX_28_124_MASK                                             0x10000000
#define MBOX_28_124_RD(src)                          (((src) & 0x10000000)>>28)
#define MBOX_28_124_SET(dst,src) \
                      (((dst) & ~0x10000000) | (((u32)(src)<<28) & 0x10000000))
/*	 Fields mbox_28_11	 */
#define MBOX_28_114_WIDTH                                                     1
#define MBOX_28_114_SHIFT                                                    27
#define MBOX_28_114_MASK                                             0x08000000
#define MBOX_28_114_RD(src)                          (((src) & 0x08000000)>>27)
#define MBOX_28_114_SET(dst,src) \
                      (((dst) & ~0x08000000) | (((u32)(src)<<27) & 0x08000000))
/*	 Fields mbox_28_10	 */
#define MBOX_28_104_WIDTH                                                     1
#define MBOX_28_104_SHIFT                                                    26
#define MBOX_28_104_MASK                                             0x04000000
#define MBOX_28_104_RD(src)                          (((src) & 0x04000000)>>26)
#define MBOX_28_104_SET(dst,src) \
                      (((dst) & ~0x04000000) | (((u32)(src)<<26) & 0x04000000))
/*	 Fields mbox_28_9	 */
#define MBOX_28_94_WIDTH                                                      1
#define MBOX_28_94_SHIFT                                                     25
#define MBOX_28_94_MASK                                              0x02000000
#define MBOX_28_94_RD(src)                           (((src) & 0x02000000)>>25)
#define MBOX_28_94_SET(dst,src) \
                      (((dst) & ~0x02000000) | (((u32)(src)<<25) & 0x02000000))
/*	 Fields mbox_28_8	 */
#define MBOX_28_84_WIDTH                                                      1
#define MBOX_28_84_SHIFT                                                     24
#define MBOX_28_84_MASK                                              0x01000000
#define MBOX_28_84_RD(src)                           (((src) & 0x01000000)>>24)
#define MBOX_28_84_SET(dst,src) \
                      (((dst) & ~0x01000000) | (((u32)(src)<<24) & 0x01000000))
/*	 Fields mbox_28_7	 */
#define MBOX_28_74_WIDTH                                                      1
#define MBOX_28_74_SHIFT                                                     23
#define MBOX_28_74_MASK                                              0x00800000
#define MBOX_28_74_RD(src)                           (((src) & 0x00800000)>>23)
#define MBOX_28_74_SET(dst,src) \
                      (((dst) & ~0x00800000) | (((u32)(src)<<23) & 0x00800000))
/*	 Fields mbox_28_6	 */
#define MBOX_28_64_WIDTH                                                      1
#define MBOX_28_64_SHIFT                                                     22
#define MBOX_28_64_MASK                                              0x00400000
#define MBOX_28_64_RD(src)                           (((src) & 0x00400000)>>22)
#define MBOX_28_64_SET(dst,src) \
                      (((dst) & ~0x00400000) | (((u32)(src)<<22) & 0x00400000))
/*	 Fields mbox_28_5	 */
#define MBOX_28_54_WIDTH                                                      1
#define MBOX_28_54_SHIFT                                                     21
#define MBOX_28_54_MASK                                              0x00200000
#define MBOX_28_54_RD(src)                           (((src) & 0x00200000)>>21)
#define MBOX_28_54_SET(dst,src) \
                      (((dst) & ~0x00200000) | (((u32)(src)<<21) & 0x00200000))
/*	 Fields mbox_28_4	 */
#define MBOX_28_44_WIDTH                                                      1
#define MBOX_28_44_SHIFT                                                     20
#define MBOX_28_44_MASK                                              0x00100000
#define MBOX_28_44_RD(src)                           (((src) & 0x00100000)>>20)
#define MBOX_28_44_SET(dst,src) \
                      (((dst) & ~0x00100000) | (((u32)(src)<<20) & 0x00100000))
/*	 Fields mbox_28_3	 */
#define MBOX_28_34_WIDTH                                                      1
#define MBOX_28_34_SHIFT                                                     19
#define MBOX_28_34_MASK                                              0x00080000
#define MBOX_28_34_RD(src)                           (((src) & 0x00080000)>>19)
#define MBOX_28_34_SET(dst,src) \
                      (((dst) & ~0x00080000) | (((u32)(src)<<19) & 0x00080000))
/*	 Fields mbox_28_2	 */
#define MBOX_28_24_WIDTH                                                      1
#define MBOX_28_24_SHIFT                                                     18
#define MBOX_28_24_MASK                                              0x00040000
#define MBOX_28_24_RD(src)                           (((src) & 0x00040000)>>18)
#define MBOX_28_24_SET(dst,src) \
                      (((dst) & ~0x00040000) | (((u32)(src)<<18) & 0x00040000))
/*	 Fields mbox_28_1	 */
#define MBOX_28_14_WIDTH                                                      1
#define MBOX_28_14_SHIFT                                                     17
#define MBOX_28_14_MASK                                              0x00020000
#define MBOX_28_14_RD(src)                           (((src) & 0x00020000)>>17)
#define MBOX_28_14_SET(dst,src) \
                      (((dst) & ~0x00020000) | (((u32)(src)<<17) & 0x00020000))
/*	 Fields mbox_28_0	 */
#define MBOX_28_04_WIDTH                                                      1
#define MBOX_28_04_SHIFT                                                     16
#define MBOX_28_04_MASK                                              0x00010000
#define MBOX_28_04_RD(src)                           (((src) & 0x00010000)>>16)
#define MBOX_28_04_SET(dst,src) \
                      (((dst) & ~0x00010000) | (((u32)(src)<<16) & 0x00010000))
/*	 Fields mbox_29_15	 */
#define MBOX_29_154_WIDTH                                                     1
#define MBOX_29_154_SHIFT                                                    15
#define MBOX_29_154_MASK                                             0x00008000
#define MBOX_29_154_RD(src)                          (((src) & 0x00008000)>>15)
#define MBOX_29_154_SET(dst,src) \
                      (((dst) & ~0x00008000) | (((u32)(src)<<15) & 0x00008000))
/*	 Fields mbox_29_14	 */
#define MBOX_29_144_WIDTH                                                     1
#define MBOX_29_144_SHIFT                                                    14
#define MBOX_29_144_MASK                                             0x00004000
#define MBOX_29_144_RD(src)                          (((src) & 0x00004000)>>14)
#define MBOX_29_144_SET(dst,src) \
                      (((dst) & ~0x00004000) | (((u32)(src)<<14) & 0x00004000))
/*	 Fields mbox_29_13	 */
#define MBOX_29_134_WIDTH                                                     1
#define MBOX_29_134_SHIFT                                                    13
#define MBOX_29_134_MASK                                             0x00002000
#define MBOX_29_134_RD(src)                          (((src) & 0x00002000)>>13)
#define MBOX_29_134_SET(dst,src) \
                      (((dst) & ~0x00002000) | (((u32)(src)<<13) & 0x00002000))
/*	 Fields mbox_29_12	 */
#define MBOX_29_124_WIDTH                                                     1
#define MBOX_29_124_SHIFT                                                    12
#define MBOX_29_124_MASK                                             0x00001000
#define MBOX_29_124_RD(src)                          (((src) & 0x00001000)>>12)
#define MBOX_29_124_SET(dst,src) \
                      (((dst) & ~0x00001000) | (((u32)(src)<<12) & 0x00001000))
/*	 Fields mbox_29_11	 */
#define MBOX_29_114_WIDTH                                                     1
#define MBOX_29_114_SHIFT                                                    11
#define MBOX_29_114_MASK                                             0x00000800
#define MBOX_29_114_RD(src)                          (((src) & 0x00000800)>>11)
#define MBOX_29_114_SET(dst,src) \
                      (((dst) & ~0x00000800) | (((u32)(src)<<11) & 0x00000800))
/*	 Fields mbox_29_10	 */
#define MBOX_29_104_WIDTH                                                     1
#define MBOX_29_104_SHIFT                                                    10
#define MBOX_29_104_MASK                                             0x00000400
#define MBOX_29_104_RD(src)                          (((src) & 0x00000400)>>10)
#define MBOX_29_104_SET(dst,src) \
                      (((dst) & ~0x00000400) | (((u32)(src)<<10) & 0x00000400))
/*	 Fields mbox_29_9	 */
#define MBOX_29_94_WIDTH                                                      1
#define MBOX_29_94_SHIFT                                                      9
#define MBOX_29_94_MASK                                              0x00000200
#define MBOX_29_94_RD(src)                            (((src) & 0x00000200)>>9)
#define MBOX_29_94_SET(dst,src) \
                       (((dst) & ~0x00000200) | (((u32)(src)<<9) & 0x00000200))
/*	 Fields mbox_29_8	 */
#define MBOX_29_84_WIDTH                                                      1
#define MBOX_29_84_SHIFT                                                      8
#define MBOX_29_84_MASK                                              0x00000100
#define MBOX_29_84_RD(src)                            (((src) & 0x00000100)>>8)
#define MBOX_29_84_SET(dst,src) \
                       (((dst) & ~0x00000100) | (((u32)(src)<<8) & 0x00000100))
/*	 Fields mbox_29_7	 */
#define MBOX_29_74_WIDTH                                                      1
#define MBOX_29_74_SHIFT                                                      7
#define MBOX_29_74_MASK                                              0x00000080
#define MBOX_29_74_RD(src)                            (((src) & 0x00000080)>>7)
#define MBOX_29_74_SET(dst,src) \
                       (((dst) & ~0x00000080) | (((u32)(src)<<7) & 0x00000080))
/*	 Fields mbox_29_6	 */
#define MBOX_29_64_WIDTH                                                      1
#define MBOX_29_64_SHIFT                                                      6
#define MBOX_29_64_MASK                                              0x00000040
#define MBOX_29_64_RD(src)                            (((src) & 0x00000040)>>6)
#define MBOX_29_64_SET(dst,src) \
                       (((dst) & ~0x00000040) | (((u32)(src)<<6) & 0x00000040))
/*	 Fields mbox_29_5	 */
#define MBOX_29_54_WIDTH                                                      1
#define MBOX_29_54_SHIFT                                                      5
#define MBOX_29_54_MASK                                              0x00000020
#define MBOX_29_54_RD(src)                            (((src) & 0x00000020)>>5)
#define MBOX_29_54_SET(dst,src) \
                       (((dst) & ~0x00000020) | (((u32)(src)<<5) & 0x00000020))
/*	 Fields mbox_29_4	 */
#define MBOX_29_44_WIDTH                                                      1
#define MBOX_29_44_SHIFT                                                      4
#define MBOX_29_44_MASK                                              0x00000010
#define MBOX_29_44_RD(src)                            (((src) & 0x00000010)>>4)
#define MBOX_29_44_SET(dst,src) \
                       (((dst) & ~0x00000010) | (((u32)(src)<<4) & 0x00000010))
/*	 Fields mbox_29_3	 */
#define MBOX_29_34_WIDTH                                                      1
#define MBOX_29_34_SHIFT                                                      3
#define MBOX_29_34_MASK                                              0x00000008
#define MBOX_29_34_RD(src)                            (((src) & 0x00000008)>>3)
#define MBOX_29_34_SET(dst,src) \
                       (((dst) & ~0x00000008) | (((u32)(src)<<3) & 0x00000008))
/*	 Fields mbox_29_2	 */
#define MBOX_29_24_WIDTH                                                      1
#define MBOX_29_24_SHIFT                                                      2
#define MBOX_29_24_MASK                                              0x00000004
#define MBOX_29_24_RD(src)                            (((src) & 0x00000004)>>2)
#define MBOX_29_24_SET(dst,src) \
                       (((dst) & ~0x00000004) | (((u32)(src)<<2) & 0x00000004))
/*	 Fields mbox_29_1	 */
#define MBOX_29_14_WIDTH                                                      1
#define MBOX_29_14_SHIFT                                                      1
#define MBOX_29_14_MASK                                              0x00000002
#define MBOX_29_14_RD(src)                            (((src) & 0x00000002)>>1)
#define MBOX_29_14_SET(dst,src) \
                       (((dst) & ~0x00000002) | (((u32)(src)<<1) & 0x00000002))
/*	 Fields mbox_29_0	 */
#define MBOX_29_04_WIDTH                                                      1
#define MBOX_29_04_SHIFT                                                      0
#define MBOX_29_04_MASK                                              0x00000001
#define MBOX_29_04_RD(src)                               (((src) & 0x00000001))
#define MBOX_29_04_SET(dst,src) \
                          (((dst) & ~0x00000001) | (((u32)(src)) & 0x00000001))

/*	Register csr_enq_status_15	*/ 
/*	 Fields mbox_30_15	 */
#define MBOX_30_155_WIDTH                                                     1
#define MBOX_30_155_SHIFT                                                    31
#define MBOX_30_155_MASK                                             0x80000000
#define MBOX_30_155_RD(src)                          (((src) & 0x80000000)>>31)
#define MBOX_30_155_SET(dst,src) \
                      (((dst) & ~0x80000000) | (((u32)(src)<<31) & 0x80000000))
/*	 Fields mbox_30_14	 */
#define MBOX_30_145_WIDTH                                                     1
#define MBOX_30_145_SHIFT                                                    30
#define MBOX_30_145_MASK                                             0x40000000
#define MBOX_30_145_RD(src)                          (((src) & 0x40000000)>>30)
#define MBOX_30_145_SET(dst,src) \
                      (((dst) & ~0x40000000) | (((u32)(src)<<30) & 0x40000000))
/*	 Fields mbox_30_13	 */
#define MBOX_30_135_WIDTH                                                     1
#define MBOX_30_135_SHIFT                                                    29
#define MBOX_30_135_MASK                                             0x20000000
#define MBOX_30_135_RD(src)                          (((src) & 0x20000000)>>29)
#define MBOX_30_135_SET(dst,src) \
                      (((dst) & ~0x20000000) | (((u32)(src)<<29) & 0x20000000))
/*	 Fields mbox_30_12	 */
#define MBOX_30_125_WIDTH                                                     1
#define MBOX_30_125_SHIFT                                                    28
#define MBOX_30_125_MASK                                             0x10000000
#define MBOX_30_125_RD(src)                          (((src) & 0x10000000)>>28)
#define MBOX_30_125_SET(dst,src) \
                      (((dst) & ~0x10000000) | (((u32)(src)<<28) & 0x10000000))
/*	 Fields mbox_30_11	 */
#define MBOX_30_115_WIDTH                                                     1
#define MBOX_30_115_SHIFT                                                    27
#define MBOX_30_115_MASK                                             0x08000000
#define MBOX_30_115_RD(src)                          (((src) & 0x08000000)>>27)
#define MBOX_30_115_SET(dst,src) \
                      (((dst) & ~0x08000000) | (((u32)(src)<<27) & 0x08000000))
/*	 Fields mbox_30_10	 */
#define MBOX_30_105_WIDTH                                                     1
#define MBOX_30_105_SHIFT                                                    26
#define MBOX_30_105_MASK                                             0x04000000
#define MBOX_30_105_RD(src)                          (((src) & 0x04000000)>>26)
#define MBOX_30_105_SET(dst,src) \
                      (((dst) & ~0x04000000) | (((u32)(src)<<26) & 0x04000000))
/*	 Fields mbox_30_9	 */
#define MBOX_30_95_WIDTH                                                      1
#define MBOX_30_95_SHIFT                                                     25
#define MBOX_30_95_MASK                                              0x02000000
#define MBOX_30_95_RD(src)                           (((src) & 0x02000000)>>25)
#define MBOX_30_95_SET(dst,src) \
                      (((dst) & ~0x02000000) | (((u32)(src)<<25) & 0x02000000))
/*	 Fields mbox_30_8	 */
#define MBOX_30_85_WIDTH                                                      1
#define MBOX_30_85_SHIFT                                                     24
#define MBOX_30_85_MASK                                              0x01000000
#define MBOX_30_85_RD(src)                           (((src) & 0x01000000)>>24)
#define MBOX_30_85_SET(dst,src) \
                      (((dst) & ~0x01000000) | (((u32)(src)<<24) & 0x01000000))
/*	 Fields mbox_30_7	 */
#define MBOX_30_75_WIDTH                                                      1
#define MBOX_30_75_SHIFT                                                     23
#define MBOX_30_75_MASK                                              0x00800000
#define MBOX_30_75_RD(src)                           (((src) & 0x00800000)>>23)
#define MBOX_30_75_SET(dst,src) \
                      (((dst) & ~0x00800000) | (((u32)(src)<<23) & 0x00800000))
/*	 Fields mbox_30_6	 */
#define MBOX_30_65_WIDTH                                                      1
#define MBOX_30_65_SHIFT                                                     22
#define MBOX_30_65_MASK                                              0x00400000
#define MBOX_30_65_RD(src)                           (((src) & 0x00400000)>>22)
#define MBOX_30_65_SET(dst,src) \
                      (((dst) & ~0x00400000) | (((u32)(src)<<22) & 0x00400000))
/*	 Fields mbox_30_5	 */
#define MBOX_30_55_WIDTH                                                      1
#define MBOX_30_55_SHIFT                                                     21
#define MBOX_30_55_MASK                                              0x00200000
#define MBOX_30_55_RD(src)                           (((src) & 0x00200000)>>21)
#define MBOX_30_55_SET(dst,src) \
                      (((dst) & ~0x00200000) | (((u32)(src)<<21) & 0x00200000))
/*	 Fields mbox_30_4	 */
#define MBOX_30_45_WIDTH                                                      1
#define MBOX_30_45_SHIFT                                                     20
#define MBOX_30_45_MASK                                              0x00100000
#define MBOX_30_45_RD(src)                           (((src) & 0x00100000)>>20)
#define MBOX_30_45_SET(dst,src) \
                      (((dst) & ~0x00100000) | (((u32)(src)<<20) & 0x00100000))
/*	 Fields mbox_30_3	 */
#define MBOX_30_35_WIDTH                                                      1
#define MBOX_30_35_SHIFT                                                     19
#define MBOX_30_35_MASK                                              0x00080000
#define MBOX_30_35_RD(src)                           (((src) & 0x00080000)>>19)
#define MBOX_30_35_SET(dst,src) \
                      (((dst) & ~0x00080000) | (((u32)(src)<<19) & 0x00080000))
/*	 Fields mbox_30_2	 */
#define MBOX_30_25_WIDTH                                                      1
#define MBOX_30_25_SHIFT                                                     18
#define MBOX_30_25_MASK                                              0x00040000
#define MBOX_30_25_RD(src)                           (((src) & 0x00040000)>>18)
#define MBOX_30_25_SET(dst,src) \
                      (((dst) & ~0x00040000) | (((u32)(src)<<18) & 0x00040000))
/*	 Fields mbox_30_1	 */
#define MBOX_30_15_WIDTH                                                      1
#define MBOX_30_15_SHIFT                                                     17
#define MBOX_30_15_MASK                                              0x00020000
#define MBOX_30_15_RD(src)                           (((src) & 0x00020000)>>17)
#define MBOX_30_15_SET(dst,src) \
                      (((dst) & ~0x00020000) | (((u32)(src)<<17) & 0x00020000))
/*	 Fields mbox_30_0	 */
#define MBOX_30_05_WIDTH                                                      1
#define MBOX_30_05_SHIFT                                                     16
#define MBOX_30_05_MASK                                              0x00010000
#define MBOX_30_05_RD(src)                           (((src) & 0x00010000)>>16)
#define MBOX_30_05_SET(dst,src) \
                      (((dst) & ~0x00010000) | (((u32)(src)<<16) & 0x00010000))
/*	 Fields mbox_31_15	 */
#define MBOX_31_155_WIDTH                                                     1
#define MBOX_31_155_SHIFT                                                    15
#define MBOX_31_155_MASK                                             0x00008000
#define MBOX_31_155_RD(src)                          (((src) & 0x00008000)>>15)
#define MBOX_31_155_SET(dst,src) \
                      (((dst) & ~0x00008000) | (((u32)(src)<<15) & 0x00008000))
/*	 Fields mbox_31_14	 */
#define MBOX_31_145_WIDTH                                                     1
#define MBOX_31_145_SHIFT                                                    14
#define MBOX_31_145_MASK                                             0x00004000
#define MBOX_31_145_RD(src)                          (((src) & 0x00004000)>>14)
#define MBOX_31_145_SET(dst,src) \
                      (((dst) & ~0x00004000) | (((u32)(src)<<14) & 0x00004000))
/*	 Fields mbox_31_13	 */
#define MBOX_31_135_WIDTH                                                     1
#define MBOX_31_135_SHIFT                                                    13
#define MBOX_31_135_MASK                                             0x00002000
#define MBOX_31_135_RD(src)                          (((src) & 0x00002000)>>13)
#define MBOX_31_135_SET(dst,src) \
                      (((dst) & ~0x00002000) | (((u32)(src)<<13) & 0x00002000))
/*	 Fields mbox_31_12	 */
#define MBOX_31_125_WIDTH                                                     1
#define MBOX_31_125_SHIFT                                                    12
#define MBOX_31_125_MASK                                             0x00001000
#define MBOX_31_125_RD(src)                          (((src) & 0x00001000)>>12)
#define MBOX_31_125_SET(dst,src) \
                      (((dst) & ~0x00001000) | (((u32)(src)<<12) & 0x00001000))
/*	 Fields mbox_31_11	 */
#define MBOX_31_115_WIDTH                                                     1
#define MBOX_31_115_SHIFT                                                    11
#define MBOX_31_115_MASK                                             0x00000800
#define MBOX_31_115_RD(src)                          (((src) & 0x00000800)>>11)
#define MBOX_31_115_SET(dst,src) \
                      (((dst) & ~0x00000800) | (((u32)(src)<<11) & 0x00000800))
/*	 Fields mbox_31_10	 */
#define MBOX_31_105_WIDTH                                                     1
#define MBOX_31_105_SHIFT                                                    10
#define MBOX_31_105_MASK                                             0x00000400
#define MBOX_31_105_RD(src)                          (((src) & 0x00000400)>>10)
#define MBOX_31_105_SET(dst,src) \
                      (((dst) & ~0x00000400) | (((u32)(src)<<10) & 0x00000400))
/*	 Fields mbox_31_9	 */
#define MBOX_31_95_WIDTH                                                      1
#define MBOX_31_95_SHIFT                                                      9
#define MBOX_31_95_MASK                                              0x00000200
#define MBOX_31_95_RD(src)                            (((src) & 0x00000200)>>9)
#define MBOX_31_95_SET(dst,src) \
                       (((dst) & ~0x00000200) | (((u32)(src)<<9) & 0x00000200))
/*	 Fields mbox_31_8	 */
#define MBOX_31_85_WIDTH                                                      1
#define MBOX_31_85_SHIFT                                                      8
#define MBOX_31_85_MASK                                              0x00000100
#define MBOX_31_85_RD(src)                            (((src) & 0x00000100)>>8)
#define MBOX_31_85_SET(dst,src) \
                       (((dst) & ~0x00000100) | (((u32)(src)<<8) & 0x00000100))
/*	 Fields mbox_31_7	 */
#define MBOX_31_75_WIDTH                                                      1
#define MBOX_31_75_SHIFT                                                      7
#define MBOX_31_75_MASK                                              0x00000080
#define MBOX_31_75_RD(src)                            (((src) & 0x00000080)>>7)
#define MBOX_31_75_SET(dst,src) \
                       (((dst) & ~0x00000080) | (((u32)(src)<<7) & 0x00000080))
/*	 Fields mbox_31_6	 */
#define MBOX_31_65_WIDTH                                                      1
#define MBOX_31_65_SHIFT                                                      6
#define MBOX_31_65_MASK                                              0x00000040
#define MBOX_31_65_RD(src)                            (((src) & 0x00000040)>>6)
#define MBOX_31_65_SET(dst,src) \
                       (((dst) & ~0x00000040) | (((u32)(src)<<6) & 0x00000040))
/*	 Fields mbox_31_5	 */
#define MBOX_31_55_WIDTH                                                      1
#define MBOX_31_55_SHIFT                                                      5
#define MBOX_31_55_MASK                                              0x00000020
#define MBOX_31_55_RD(src)                            (((src) & 0x00000020)>>5)
#define MBOX_31_55_SET(dst,src) \
                       (((dst) & ~0x00000020) | (((u32)(src)<<5) & 0x00000020))
/*	 Fields mbox_31_4	 */
#define MBOX_31_45_WIDTH                                                      1
#define MBOX_31_45_SHIFT                                                      4
#define MBOX_31_45_MASK                                              0x00000010
#define MBOX_31_45_RD(src)                            (((src) & 0x00000010)>>4)
#define MBOX_31_45_SET(dst,src) \
                       (((dst) & ~0x00000010) | (((u32)(src)<<4) & 0x00000010))
/*	 Fields mbox_31_3	 */
#define MBOX_31_35_WIDTH                                                      1
#define MBOX_31_35_SHIFT                                                      3
#define MBOX_31_35_MASK                                              0x00000008
#define MBOX_31_35_RD(src)                            (((src) & 0x00000008)>>3)
#define MBOX_31_35_SET(dst,src) \
                       (((dst) & ~0x00000008) | (((u32)(src)<<3) & 0x00000008))
/*	 Fields mbox_31_2	 */
#define MBOX_31_25_WIDTH                                                      1
#define MBOX_31_25_SHIFT                                                      2
#define MBOX_31_25_MASK                                              0x00000004
#define MBOX_31_25_RD(src)                            (((src) & 0x00000004)>>2)
#define MBOX_31_25_SET(dst,src) \
                       (((dst) & ~0x00000004) | (((u32)(src)<<2) & 0x00000004))
/*	 Fields mbox_31_1	 */
#define MBOX_31_15_WIDTH                                                      1
#define MBOX_31_15_SHIFT                                                      1
#define MBOX_31_15_MASK                                              0x00000002
#define MBOX_31_15_RD(src)                            (((src) & 0x00000002)>>1)
#define MBOX_31_15_SET(dst,src) \
                       (((dst) & ~0x00000002) | (((u32)(src)<<1) & 0x00000002))
/*	 Fields mbox_31_0	 */
#define MBOX_31_05_WIDTH                                                      1
#define MBOX_31_05_SHIFT                                                      0
#define MBOX_31_05_MASK                                              0x00000001
#define MBOX_31_05_RD(src)                               (((src) & 0x00000001))
#define MBOX_31_05_SET(dst,src) \
                          (((dst) & ~0x00000001) | (((u32)(src)) & 0x00000001))

/*	Register qm_INT	*/ 
/*	 Fields queue_not_empty	 */
#define QUEUE_NOT_EMPTY_WIDTH                                                 1
#define QUEUE_NOT_EMPTY_SHIFT                                                31
#define QUEUE_NOT_EMPTY_MASK                                         0x80000000
#define QUEUE_NOT_EMPTY_RD(src)                      (((src) & 0x80000000)>>31)
#define QUEUE_NOT_EMPTY_WR(src)                 (((u32)(src)<<31) & 0x80000000)
#define QUEUE_NOT_EMPTY_SET(dst,src) \
                      (((dst) & ~0x80000000) | (((u32)(src)<<31) & 0x80000000))
/*	 Fields acr_fifo_critical	 */
#define ACR_FIFO_CRITICAL_WIDTH                                               1
#define ACR_FIFO_CRITICAL_SHIFT                                               3
#define ACR_FIFO_CRITICAL_MASK                                       0x00000008
#define ACR_FIFO_CRITICAL_RD(src)                     (((src) & 0x00000008)>>3)
#define ACR_FIFO_CRITICAL_WR(src)                (((u32)(src)<<3) & 0x00000008)
#define ACR_FIFO_CRITICAL_SET(dst,src) \
                       (((dst) & ~0x00000008) | (((u32)(src)<<3) & 0x00000008))
/*	 Fields qpcore_acr_error	 */
#define QPCORE_ACR_ERROR_WIDTH                                                1
#define QPCORE_ACR_ERROR_SHIFT                                                2
#define QPCORE_ACR_ERROR_MASK                                        0x00000004
#define QPCORE_ACR_ERROR_RD(src)                      (((src) & 0x00000004)>>2)
#define QPCORE_ACR_ERROR_WR(src)                 (((u32)(src)<<2) & 0x00000004)
#define QPCORE_ACR_ERROR_SET(dst,src) \
                       (((dst) & ~0x00000004) | (((u32)(src)<<2) & 0x00000004))
/*	 Fields deq_axi_error	 */
#define DEQ_AXI_ERROR_WIDTH                                                   1
#define DEQ_AXI_ERROR_SHIFT                                                   1
#define DEQ_AXI_ERROR_MASK                                           0x00000002
#define DEQ_AXI_ERROR_RD(src)                         (((src) & 0x00000002)>>1)
#define DEQ_AXI_ERROR_WR(src)                    (((u32)(src)<<1) & 0x00000002)
#define DEQ_AXI_ERROR_SET(dst,src) \
                       (((dst) & ~0x00000002) | (((u32)(src)<<1) & 0x00000002))
/*	 Fields pbm_dec_error	 */
#define PBM_DEC_ERROR_WIDTH                                                   1
#define PBM_DEC_ERROR_SHIFT                                                   0
#define PBM_DEC_ERROR_MASK                                           0x00000001
#define PBM_DEC_ERROR_RD(src)                            (((src) & 0x00000001))
#define PBM_DEC_ERROR_WR(src)                       (((u32)(src)) & 0x00000001)
#define PBM_DEC_ERROR_SET(dst,src) \
                          (((dst) & ~0x00000001) | (((u32)(src)) & 0x00000001))

/*	Register qm_interruptMask	*/
/*    Mask Register Fields queue_not_emptyMask    */
#define QUEUE_NOT_EMPTYMASK_WIDTH                                             1
#define QUEUE_NOT_EMPTYMASK_SHIFT                                            31
#define QUEUE_NOT_EMPTYMASK_MASK                                     0x80000000
#define QUEUE_NOT_EMPTYMASK_RD(src)                  (((src) & 0x80000000)>>31)
#define QUEUE_NOT_EMPTYMASK_WR(src)             (((u32)(src)<<31) & 0x80000000)
#define QUEUE_NOT_EMPTYMASK_SET(dst,src) \
                      (((dst) & ~0x80000000) | (((u32)(src)<<31) & 0x80000000))
/*    Mask Register Fields acr_fifo_criticalMask    */
#define ACR_FIFO_CRITICALMASK_WIDTH                                           1
#define ACR_FIFO_CRITICALMASK_SHIFT                                           3
#define ACR_FIFO_CRITICALMASK_MASK                                   0x00000008
#define ACR_FIFO_CRITICALMASK_RD(src)                 (((src) & 0x00000008)>>3)
#define ACR_FIFO_CRITICALMASK_WR(src)            (((u32)(src)<<3) & 0x00000008)
#define ACR_FIFO_CRITICALMASK_SET(dst,src) \
                       (((dst) & ~0x00000008) | (((u32)(src)<<3) & 0x00000008))
/*    Mask Register Fields qpcore_acr_errorMask    */
#define QPCORE_ACR_ERRORMASK_WIDTH                                            1
#define QPCORE_ACR_ERRORMASK_SHIFT                                            2
#define QPCORE_ACR_ERRORMASK_MASK                                    0x00000004
#define QPCORE_ACR_ERRORMASK_RD(src)                  (((src) & 0x00000004)>>2)
#define QPCORE_ACR_ERRORMASK_WR(src)             (((u32)(src)<<2) & 0x00000004)
#define QPCORE_ACR_ERRORMASK_SET(dst,src) \
                       (((dst) & ~0x00000004) | (((u32)(src)<<2) & 0x00000004))
/*    Mask Register Fields deq_axi_errorMask    */
#define DEQ_AXI_ERRORMASK_WIDTH                                               1
#define DEQ_AXI_ERRORMASK_SHIFT                                               1
#define DEQ_AXI_ERRORMASK_MASK                                       0x00000002
#define DEQ_AXI_ERRORMASK_RD(src)                     (((src) & 0x00000002)>>1)
#define DEQ_AXI_ERRORMASK_WR(src)                (((u32)(src)<<1) & 0x00000002)
#define DEQ_AXI_ERRORMASK_SET(dst,src) \
                       (((dst) & ~0x00000002) | (((u32)(src)<<1) & 0x00000002))
/*    Mask Register Fields pbm_dec_errorMask    */
#define PBM_DEC_ERRORMASK_WIDTH                                               1
#define PBM_DEC_ERRORMASK_SHIFT                                               0
#define PBM_DEC_ERRORMASK_MASK                                       0x00000001
#define PBM_DEC_ERRORMASK_RD(src)                        (((src) & 0x00000001))
#define PBM_DEC_ERRORMASK_WR(src)                   (((u32)(src)) & 0x00000001)
#define PBM_DEC_ERRORMASK_SET(dst,src) \
                          (((dst) & ~0x00000001) | (((u32)(src)) & 0x00000001))

/*	Register qm_SAB_qne_INT	*/ 
/*	 Fields interrupting_csr	 */
#define INTERRUPTING_CSR_WIDTH                                               32
#define INTERRUPTING_CSR_SHIFT                                                0
#define INTERRUPTING_CSR_MASK                                        0xffffffff
#define INTERRUPTING_CSR_RD(src)                         (((src) & 0xffffffff))
#define INTERRUPTING_CSR_WR(src)                    (((u32)(src)) & 0xffffffff)
#define INTERRUPTING_CSR_SET(dst,src) \
                          (((dst) & ~0xffffffff) | (((u32)(src)) & 0xffffffff))

/*	Register qm_SAB_qne_interruptMask	*/
/*    Mask Register Fields interrupting_csrMask    */
#define INTERRUPTING_CSRMASK_WIDTH                                           32
#define INTERRUPTING_CSRMASK_SHIFT                                            0
#define INTERRUPTING_CSRMASK_MASK                                    0xffffffff
#define INTERRUPTING_CSRMASK_RD(src)                     (((src) & 0xffffffff))
#define INTERRUPTING_CSRMASK_WR(src)                (((u32)(src)) & 0xffffffff)
#define INTERRUPTING_CSRMASK_SET(dst,src) \
                          (((dst) & ~0xffffffff) | (((u32)(src)) & 0xffffffff))

/*	Register csr_pbm_errinf	*/ 
/*	 Fields pbm_config_err	 */
#define PBM_CONFIG_ERR_WIDTH                                                  1
#define PBM_CONFIG_ERR_SHIFT                                                 17
#define PBM_CONFIG_ERR_MASK                                          0x00020000
#define PBM_CONFIG_ERR_RD(src)                       (((src) & 0x00020000)>>17)
#define PBM_CONFIG_ERR_SET(dst,src) \
                      (((dst) & ~0x00020000) | (((u32)(src)<<17) & 0x00020000))
/*	 Fields pbm_decrement_err	 */
#define PBM_DECREMENT_ERR_WIDTH                                               1
#define PBM_DECREMENT_ERR_SHIFT                                              16
#define PBM_DECREMENT_ERR_MASK                                       0x00010000
#define PBM_DECREMENT_ERR_RD(src)                    (((src) & 0x00010000)>>16)
#define PBM_DECREMENT_ERR_SET(dst,src) \
                      (((dst) & ~0x00010000) | (((u32)(src)<<16) & 0x00010000))
/*	 Fields slave_id	 */
#define SLAVE_ID_WIDTH                                                        4
#define SLAVE_ID_SHIFT                                                        6
#define SLAVE_ID_MASK                                                0x000003c0
#define SLAVE_ID_RD(src)                              (((src) & 0x000003c0)>>6)
#define SLAVE_ID_SET(dst,src) \
                       (((dst) & ~0x000003c0) | (((u32)(src)<<6) & 0x000003c0))
/*	 Fields PB_number	 */
#define PB_NUMBER_WIDTH                                                       6
#define PB_NUMBER_SHIFT                                                       0
#define PB_NUMBER_MASK                                               0x0000003f
#define PB_NUMBER_RD(src)                                (((src) & 0x0000003f))
#define PB_NUMBER_SET(dst,src) \
                          (((dst) & ~0x0000003f) | (((u32)(src)) & 0x0000003f))

/*	Register csr_msgrd_errinf	*/ 
/*	 Fields qpcore_was_disabled	 */
#define QPCORE_WAS_DISABLED_WIDTH                                             1
#define QPCORE_WAS_DISABLED_SHIFT                                            27
#define QPCORE_WAS_DISABLED_MASK                                     0x08000000
#define QPCORE_WAS_DISABLED_RD(src)                  (((src) & 0x08000000)>>27)
#define QPCORE_WAS_DISABLED_SET(dst,src) \
                      (((dst) & ~0x08000000) | (((u32)(src)<<27) & 0x08000000))
/*	 Fields drop_code	 */
#define DROP_CODE_WIDTH                                                       3
#define DROP_CODE_SHIFT                                                      24
#define DROP_CODE_MASK                                               0x07000000
#define DROP_CODE_RD(src)                            (((src) & 0x07000000)>>24)
#define DROP_CODE_SET(dst,src) \
                      (((dst) & ~0x07000000) | (((u32)(src)<<24) & 0x07000000))
/*	 Fields acr_qid	 */
#define ACR_QID_WIDTH                                                        10
#define ACR_QID_SHIFT                                                        14
#define ACR_QID_MASK                                                 0x00ffc000
#define ACR_QID_RD(src)                              (((src) & 0x00ffc000)>>14)
#define ACR_QID_SET(dst,src) \
                      (((dst) & ~0x00ffc000) | (((u32)(src)<<14) & 0x00ffc000))
/*	 Fields response_code	 */
#define RESPONSE_CODE_WIDTH                                                   2
#define RESPONSE_CODE_SHIFT                                                  10
#define RESPONSE_CODE_MASK                                           0x00000c00
#define RESPONSE_CODE_RD(src)                        (((src) & 0x00000c00)>>10)
#define RESPONSE_CODE_SET(dst,src) \
                      (((dst) & ~0x00000c00) | (((u32)(src)<<10) & 0x00000c00))
/*	 Fields qid	 */
#define QID_WIDTH                                                            10
#define QID_SHIFT                                                             0
#define QID_MASK                                                     0x000003ff
#define QID_RD(src)                                      (((src) & 0x000003ff))
#define QID_SET(dst,src) (((dst) & ~0x000003ff) | (((u32)(src)) & 0x000003ff))

/*	Register csr_qm_sab_proc0	*/ 
/*	 Fields interrupting_csr	 */
#define INTERRUPTING_CSR0_WIDTH                                              32
#define INTERRUPTING_CSR0_SHIFT                                               0
#define INTERRUPTING_CSR0_MASK                                       0xffffffff
#define INTERRUPTING_CSR0_RD(src)                        (((src) & 0xffffffff))
#define INTERRUPTING_CSR0_WR(src)                   (((u32)(src)) & 0xffffffff)
#define INTERRUPTING_CSR0_SET(dst,src) \
                          (((dst) & ~0xffffffff) | (((u32)(src)) & 0xffffffff))

/*	Register csr_qm_sab_proc0Mask	*/
/*    Mask Register Fields interrupting_csrMask    */
#define INTERRUPTING_CSRMASK_F1_WIDTH                                        32
#define INTERRUPTING_CSRMASK_F1_SHIFT                                         0
#define INTERRUPTING_CSRMASK_F1_MASK                                 0xffffffff
#define INTERRUPTING_CSRMASK_F1_RD(src)                  (((src) & 0xffffffff))
#define INTERRUPTING_CSRMASK_F1_WR(src)             (((u32)(src)) & 0xffffffff)
#define INTERRUPTING_CSRMASK_F1_SET(dst,src) \
                          (((dst) & ~0xffffffff) | (((u32)(src)) & 0xffffffff))

/*	Register csr_qm_sab_proc1	*/ 
/*	 Fields interrupting_csr	 */
#define INTERRUPTING_CSR1_WIDTH                                              32
#define INTERRUPTING_CSR1_SHIFT                                               0
#define INTERRUPTING_CSR1_MASK                                       0xffffffff
#define INTERRUPTING_CSR1_RD(src)                        (((src) & 0xffffffff))
#define INTERRUPTING_CSR1_WR(src)                   (((u32)(src)) & 0xffffffff)
#define INTERRUPTING_CSR1_SET(dst,src) \
                          (((dst) & ~0xffffffff) | (((u32)(src)) & 0xffffffff))

/*	Register csr_qm_sab_proc1Mask	*/
/*    Mask Register Fields interrupting_csrMask    */
#define INTERRUPTING_CSRMASK_F2_WIDTH                                        32
#define INTERRUPTING_CSRMASK_F2_SHIFT                                         0
#define INTERRUPTING_CSRMASK_F2_MASK                                 0xffffffff
#define INTERRUPTING_CSRMASK_F2_RD(src)                  (((src) & 0xffffffff))
#define INTERRUPTING_CSRMASK_F2_WR(src)             (((u32)(src)) & 0xffffffff)
#define INTERRUPTING_CSRMASK_F2_SET(dst,src) \
                          (((dst) & ~0xffffffff) | (((u32)(src)) & 0xffffffff))

/*	Register csr_qm_sab_proc2	*/ 
/*	 Fields interrupting_csr	 */
#define INTERRUPTING_CSR2_WIDTH                                              32
#define INTERRUPTING_CSR2_SHIFT                                               0
#define INTERRUPTING_CSR2_MASK                                       0xffffffff
#define INTERRUPTING_CSR2_RD(src)                        (((src) & 0xffffffff))
#define INTERRUPTING_CSR2_WR(src)                   (((u32)(src)) & 0xffffffff)
#define INTERRUPTING_CSR2_SET(dst,src) \
                          (((dst) & ~0xffffffff) | (((u32)(src)) & 0xffffffff))

/*	Register csr_qm_sab_proc2Mask	*/
/*    Mask Register Fields interrupting_csrMask    */
#define INTERRUPTING_CSRMASK_F3_WIDTH                                        32
#define INTERRUPTING_CSRMASK_F3_SHIFT                                         0
#define INTERRUPTING_CSRMASK_F3_MASK                                 0xffffffff
#define INTERRUPTING_CSRMASK_F3_RD(src)                  (((src) & 0xffffffff))
#define INTERRUPTING_CSRMASK_F3_WR(src)             (((u32)(src)) & 0xffffffff)
#define INTERRUPTING_CSRMASK_F3_SET(dst,src) \
                          (((dst) & ~0xffffffff) | (((u32)(src)) & 0xffffffff))

/*	Register csr_qm_sab_proc3	*/ 
/*	 Fields interrupting_csr	 */
#define INTERRUPTING_CSR3_WIDTH                                              32
#define INTERRUPTING_CSR3_SHIFT                                               0
#define INTERRUPTING_CSR3_MASK                                       0xffffffff
#define INTERRUPTING_CSR3_RD(src)                        (((src) & 0xffffffff))
#define INTERRUPTING_CSR3_WR(src)                   (((u32)(src)) & 0xffffffff)
#define INTERRUPTING_CSR3_SET(dst,src) \
                          (((dst) & ~0xffffffff) | (((u32)(src)) & 0xffffffff))

/*	Register csr_qm_sab_proc3Mask	*/
/*    Mask Register Fields interrupting_csrMask    */
#define INTERRUPTING_CSRMASK_F4_WIDTH                                        32
#define INTERRUPTING_CSRMASK_F4_SHIFT                                         0
#define INTERRUPTING_CSRMASK_F4_MASK                                 0xffffffff
#define INTERRUPTING_CSRMASK_F4_RD(src)                  (((src) & 0xffffffff))
#define INTERRUPTING_CSRMASK_F4_WR(src)             (((u32)(src)) & 0xffffffff)
#define INTERRUPTING_CSRMASK_F4_SET(dst,src) \
                          (((dst) & ~0xffffffff) | (((u32)(src)) & 0xffffffff))

/*	Register csr_qm_sab_proc4	*/ 
/*	 Fields interrupting_csr	 */
#define INTERRUPTING_CSR4_WIDTH                                              32
#define INTERRUPTING_CSR4_SHIFT                                               0
#define INTERRUPTING_CSR4_MASK                                       0xffffffff
#define INTERRUPTING_CSR4_RD(src)                        (((src) & 0xffffffff))
#define INTERRUPTING_CSR4_WR(src)                   (((u32)(src)) & 0xffffffff)
#define INTERRUPTING_CSR4_SET(dst,src) \
                          (((dst) & ~0xffffffff) | (((u32)(src)) & 0xffffffff))

/*	Register csr_qm_sab_proc4Mask	*/
/*    Mask Register Fields interrupting_csrMask    */
#define INTERRUPTING_CSRMASK_F5_WIDTH                                        32
#define INTERRUPTING_CSRMASK_F5_SHIFT                                         0
#define INTERRUPTING_CSRMASK_F5_MASK                                 0xffffffff
#define INTERRUPTING_CSRMASK_F5_RD(src)                  (((src) & 0xffffffff))
#define INTERRUPTING_CSRMASK_F5_WR(src)             (((u32)(src)) & 0xffffffff)
#define INTERRUPTING_CSRMASK_F5_SET(dst,src) \
                          (((dst) & ~0xffffffff) | (((u32)(src)) & 0xffffffff))

/*	Register csr_qm_sab_proc5	*/ 
/*	 Fields interrupting_csr	 */
#define INTERRUPTING_CSR5_WIDTH                                              32
#define INTERRUPTING_CSR5_SHIFT                                               0
#define INTERRUPTING_CSR5_MASK                                       0xffffffff
#define INTERRUPTING_CSR5_RD(src)                        (((src) & 0xffffffff))
#define INTERRUPTING_CSR5_WR(src)                   (((u32)(src)) & 0xffffffff)
#define INTERRUPTING_CSR5_SET(dst,src) \
                          (((dst) & ~0xffffffff) | (((u32)(src)) & 0xffffffff))

/*	Register csr_qm_sab_proc5Mask	*/
/*    Mask Register Fields interrupting_csrMask    */
#define INTERRUPTING_CSRMASK_F6_WIDTH                                        32
#define INTERRUPTING_CSRMASK_F6_SHIFT                                         0
#define INTERRUPTING_CSRMASK_F6_MASK                                 0xffffffff
#define INTERRUPTING_CSRMASK_F6_RD(src)                  (((src) & 0xffffffff))
#define INTERRUPTING_CSRMASK_F6_WR(src)             (((u32)(src)) & 0xffffffff)
#define INTERRUPTING_CSRMASK_F6_SET(dst,src) \
                          (((dst) & ~0xffffffff) | (((u32)(src)) & 0xffffffff))

/*	Register csr_qm_sab_proc6	*/ 
/*	 Fields interrupting_csr	 */
#define INTERRUPTING_CSR6_WIDTH                                              32
#define INTERRUPTING_CSR6_SHIFT                                               0
#define INTERRUPTING_CSR6_MASK                                       0xffffffff
#define INTERRUPTING_CSR6_RD(src)                        (((src) & 0xffffffff))
#define INTERRUPTING_CSR6_WR(src)                   (((u32)(src)) & 0xffffffff)
#define INTERRUPTING_CSR6_SET(dst,src) \
                          (((dst) & ~0xffffffff) | (((u32)(src)) & 0xffffffff))

/*	Register csr_qm_sab_proc6Mask	*/
/*    Mask Register Fields interrupting_csrMask    */
#define INTERRUPTING_CSRMASK_F7_WIDTH                                        32
#define INTERRUPTING_CSRMASK_F7_SHIFT                                         0
#define INTERRUPTING_CSRMASK_F7_MASK                                 0xffffffff
#define INTERRUPTING_CSRMASK_F7_RD(src)                  (((src) & 0xffffffff))
#define INTERRUPTING_CSRMASK_F7_WR(src)             (((u32)(src)) & 0xffffffff)
#define INTERRUPTING_CSRMASK_F7_SET(dst,src) \
                          (((dst) & ~0xffffffff) | (((u32)(src)) & 0xffffffff))

/*	Register csr_qm_sab_proc7	*/ 
/*	 Fields interrupting_csr	 */
#define INTERRUPTING_CSR7_WIDTH                                              32
#define INTERRUPTING_CSR7_SHIFT                                               0
#define INTERRUPTING_CSR7_MASK                                       0xffffffff
#define INTERRUPTING_CSR7_RD(src)                        (((src) & 0xffffffff))
#define INTERRUPTING_CSR7_WR(src)                   (((u32)(src)) & 0xffffffff)
#define INTERRUPTING_CSR7_SET(dst,src) \
                          (((dst) & ~0xffffffff) | (((u32)(src)) & 0xffffffff))

/*	Register csr_qm_sab_proc7Mask	*/
/*    Mask Register Fields interrupting_csrMask    */
#define INTERRUPTING_CSRMASK_F8_WIDTH                                        32
#define INTERRUPTING_CSRMASK_F8_SHIFT                                         0
#define INTERRUPTING_CSRMASK_F8_MASK                                 0xffffffff
#define INTERRUPTING_CSRMASK_F8_RD(src)                  (((src) & 0xffffffff))
#define INTERRUPTING_CSRMASK_F8_WR(src)             (((u32)(src)) & 0xffffffff)
#define INTERRUPTING_CSRMASK_F8_SET(dst,src) \
                          (((dst) & ~0xffffffff) | (((u32)(src)) & 0xffffffff))

/*	Register csr_qm_mbox_ne_int_mode	*/ 
/*	 Fields mbox_0_31	 */
#define MBOX_0_31_WIDTH                                                      32
#define MBOX_0_31_SHIFT                                                       0
#define MBOX_0_31_MASK                                               0xffffffff
#define MBOX_0_31_RD(src)                                (((src) & 0xffffffff))
#define MBOX_0_31_WR(src)                           (((u32)(src)) & 0xffffffff)
#define MBOX_0_31_SET(dst,src) \
                          (((dst) & ~0xffffffff) | (((u32)(src)) & 0xffffffff))

/*	Register csr_qm_mbox_ne	*/ 
/*	 Fields mbox_0_not_empty	 */
#define MBOX_0_NOT_EMPTY_WIDTH                                                1
#define MBOX_0_NOT_EMPTY_SHIFT                                               31
#define MBOX_0_NOT_EMPTY_MASK                                        0x80000000
#define MBOX_0_NOT_EMPTY_RD(src)                     (((src) & 0x80000000)>>31)
#define MBOX_0_NOT_EMPTY_SET(dst,src) \
                      (((dst) & ~0x80000000) | (((u32)(src)<<31) & 0x80000000))
/*	 Fields mbox_1_not_empty	 */
#define MBOX_1_NOT_EMPTY_WIDTH                                                1
#define MBOX_1_NOT_EMPTY_SHIFT                                               30
#define MBOX_1_NOT_EMPTY_MASK                                        0x40000000
#define MBOX_1_NOT_EMPTY_RD(src)                     (((src) & 0x40000000)>>30)
#define MBOX_1_NOT_EMPTY_SET(dst,src) \
                      (((dst) & ~0x40000000) | (((u32)(src)<<30) & 0x40000000))
/*	 Fields mbox_2_not_empty	 */
#define MBOX_2_NOT_EMPTY_WIDTH                                                1
#define MBOX_2_NOT_EMPTY_SHIFT                                               29
#define MBOX_2_NOT_EMPTY_MASK                                        0x20000000
#define MBOX_2_NOT_EMPTY_RD(src)                     (((src) & 0x20000000)>>29)
#define MBOX_2_NOT_EMPTY_SET(dst,src) \
                      (((dst) & ~0x20000000) | (((u32)(src)<<29) & 0x20000000))
/*	 Fields mbox_3_not_empty	 */
#define MBOX_3_NOT_EMPTY_WIDTH                                                1
#define MBOX_3_NOT_EMPTY_SHIFT                                               28
#define MBOX_3_NOT_EMPTY_MASK                                        0x10000000
#define MBOX_3_NOT_EMPTY_RD(src)                     (((src) & 0x10000000)>>28)
#define MBOX_3_NOT_EMPTY_SET(dst,src) \
                      (((dst) & ~0x10000000) | (((u32)(src)<<28) & 0x10000000))
/*	 Fields mbox_4_not_empty	 */
#define MBOX_4_NOT_EMPTY_WIDTH                                                1
#define MBOX_4_NOT_EMPTY_SHIFT                                               27
#define MBOX_4_NOT_EMPTY_MASK                                        0x08000000
#define MBOX_4_NOT_EMPTY_RD(src)                     (((src) & 0x08000000)>>27)
#define MBOX_4_NOT_EMPTY_SET(dst,src) \
                      (((dst) & ~0x08000000) | (((u32)(src)<<27) & 0x08000000))
/*	 Fields mbox_5_not_empty	 */
#define MBOX_5_NOT_EMPTY_WIDTH                                                1
#define MBOX_5_NOT_EMPTY_SHIFT                                               26
#define MBOX_5_NOT_EMPTY_MASK                                        0x04000000
#define MBOX_5_NOT_EMPTY_RD(src)                     (((src) & 0x04000000)>>26)
#define MBOX_5_NOT_EMPTY_SET(dst,src) \
                      (((dst) & ~0x04000000) | (((u32)(src)<<26) & 0x04000000))
/*	 Fields mbox_6_not_empty	 */
#define MBOX_6_NOT_EMPTY_WIDTH                                                1
#define MBOX_6_NOT_EMPTY_SHIFT                                               25
#define MBOX_6_NOT_EMPTY_MASK                                        0x02000000
#define MBOX_6_NOT_EMPTY_RD(src)                     (((src) & 0x02000000)>>25)
#define MBOX_6_NOT_EMPTY_SET(dst,src) \
                      (((dst) & ~0x02000000) | (((u32)(src)<<25) & 0x02000000))
/*	 Fields mbox_7_not_empty	 */
#define MBOX_7_NOT_EMPTY_WIDTH                                                1
#define MBOX_7_NOT_EMPTY_SHIFT                                               24
#define MBOX_7_NOT_EMPTY_MASK                                        0x01000000
#define MBOX_7_NOT_EMPTY_RD(src)                     (((src) & 0x01000000)>>24)
#define MBOX_7_NOT_EMPTY_SET(dst,src) \
                      (((dst) & ~0x01000000) | (((u32)(src)<<24) & 0x01000000))
/*	 Fields mbox_8_not_empty	 */
#define MBOX_8_NOT_EMPTY_WIDTH                                                1
#define MBOX_8_NOT_EMPTY_SHIFT                                               23
#define MBOX_8_NOT_EMPTY_MASK                                        0x00800000
#define MBOX_8_NOT_EMPTY_RD(src)                     (((src) & 0x00800000)>>23)
#define MBOX_8_NOT_EMPTY_SET(dst,src) \
                      (((dst) & ~0x00800000) | (((u32)(src)<<23) & 0x00800000))
/*	 Fields mbox_9_not_empty	 */
#define MBOX_9_NOT_EMPTY_WIDTH                                                1
#define MBOX_9_NOT_EMPTY_SHIFT                                               22
#define MBOX_9_NOT_EMPTY_MASK                                        0x00400000
#define MBOX_9_NOT_EMPTY_RD(src)                     (((src) & 0x00400000)>>22)
#define MBOX_9_NOT_EMPTY_SET(dst,src) \
                      (((dst) & ~0x00400000) | (((u32)(src)<<22) & 0x00400000))
/*	 Fields mbox_10_not_empty	 */
#define MBOX_10_NOT_EMPTY_WIDTH                                               1
#define MBOX_10_NOT_EMPTY_SHIFT                                              21
#define MBOX_10_NOT_EMPTY_MASK                                       0x00200000
#define MBOX_10_NOT_EMPTY_RD(src)                    (((src) & 0x00200000)>>21)
#define MBOX_10_NOT_EMPTY_SET(dst,src) \
                      (((dst) & ~0x00200000) | (((u32)(src)<<21) & 0x00200000))
/*	 Fields mbox_11_not_empty	 */
#define MBOX_11_NOT_EMPTY_WIDTH                                               1
#define MBOX_11_NOT_EMPTY_SHIFT                                              20
#define MBOX_11_NOT_EMPTY_MASK                                       0x00100000
#define MBOX_11_NOT_EMPTY_RD(src)                    (((src) & 0x00100000)>>20)
#define MBOX_11_NOT_EMPTY_SET(dst,src) \
                      (((dst) & ~0x00100000) | (((u32)(src)<<20) & 0x00100000))
/*	 Fields mbox_12_not_empty	 */
#define MBOX_12_NOT_EMPTY_WIDTH                                               1
#define MBOX_12_NOT_EMPTY_SHIFT                                              19
#define MBOX_12_NOT_EMPTY_MASK                                       0x00080000
#define MBOX_12_NOT_EMPTY_RD(src)                    (((src) & 0x00080000)>>19)
#define MBOX_12_NOT_EMPTY_SET(dst,src) \
                      (((dst) & ~0x00080000) | (((u32)(src)<<19) & 0x00080000))
/*	 Fields mbox_13_not_empty	 */
#define MBOX_13_NOT_EMPTY_WIDTH                                               1
#define MBOX_13_NOT_EMPTY_SHIFT                                              18
#define MBOX_13_NOT_EMPTY_MASK                                       0x00040000
#define MBOX_13_NOT_EMPTY_RD(src)                    (((src) & 0x00040000)>>18)
#define MBOX_13_NOT_EMPTY_SET(dst,src) \
                      (((dst) & ~0x00040000) | (((u32)(src)<<18) & 0x00040000))
/*	 Fields mbox_14_not_empty	 */
#define MBOX_14_NOT_EMPTY_WIDTH                                               1
#define MBOX_14_NOT_EMPTY_SHIFT                                              17
#define MBOX_14_NOT_EMPTY_MASK                                       0x00020000
#define MBOX_14_NOT_EMPTY_RD(src)                    (((src) & 0x00020000)>>17)
#define MBOX_14_NOT_EMPTY_SET(dst,src) \
                      (((dst) & ~0x00020000) | (((u32)(src)<<17) & 0x00020000))
/*	 Fields mbox_15_not_empty	 */
#define MBOX_15_NOT_EMPTY_WIDTH                                               1
#define MBOX_15_NOT_EMPTY_SHIFT                                              16
#define MBOX_15_NOT_EMPTY_MASK                                       0x00010000
#define MBOX_15_NOT_EMPTY_RD(src)                    (((src) & 0x00010000)>>16)
#define MBOX_15_NOT_EMPTY_SET(dst,src) \
                      (((dst) & ~0x00010000) | (((u32)(src)<<16) & 0x00010000))
/*	 Fields mbox_16_not_empty	 */
#define MBOX_16_NOT_EMPTY_WIDTH                                               1
#define MBOX_16_NOT_EMPTY_SHIFT                                              15
#define MBOX_16_NOT_EMPTY_MASK                                       0x00008000
#define MBOX_16_NOT_EMPTY_RD(src)                    (((src) & 0x00008000)>>15)
#define MBOX_16_NOT_EMPTY_SET(dst,src) \
                      (((dst) & ~0x00008000) | (((u32)(src)<<15) & 0x00008000))
/*	 Fields mbox_17_not_empty	 */
#define MBOX_17_NOT_EMPTY_WIDTH                                               1
#define MBOX_17_NOT_EMPTY_SHIFT                                              14
#define MBOX_17_NOT_EMPTY_MASK                                       0x00004000
#define MBOX_17_NOT_EMPTY_RD(src)                    (((src) & 0x00004000)>>14)
#define MBOX_17_NOT_EMPTY_SET(dst,src) \
                      (((dst) & ~0x00004000) | (((u32)(src)<<14) & 0x00004000))
/*	 Fields mbox_18_not_empty	 */
#define MBOX_18_NOT_EMPTY_WIDTH                                               1
#define MBOX_18_NOT_EMPTY_SHIFT                                              13
#define MBOX_18_NOT_EMPTY_MASK                                       0x00002000
#define MBOX_18_NOT_EMPTY_RD(src)                    (((src) & 0x00002000)>>13)
#define MBOX_18_NOT_EMPTY_SET(dst,src) \
                      (((dst) & ~0x00002000) | (((u32)(src)<<13) & 0x00002000))
/*	 Fields mbox_19_not_empty	 */
#define MBOX_19_NOT_EMPTY_WIDTH                                               1
#define MBOX_19_NOT_EMPTY_SHIFT                                              12
#define MBOX_19_NOT_EMPTY_MASK                                       0x00001000
#define MBOX_19_NOT_EMPTY_RD(src)                    (((src) & 0x00001000)>>12)
#define MBOX_19_NOT_EMPTY_SET(dst,src) \
                      (((dst) & ~0x00001000) | (((u32)(src)<<12) & 0x00001000))
/*	 Fields mbox_20_not_empty	 */
#define MBOX_20_NOT_EMPTY_WIDTH                                               1
#define MBOX_20_NOT_EMPTY_SHIFT                                              11
#define MBOX_20_NOT_EMPTY_MASK                                       0x00000800
#define MBOX_20_NOT_EMPTY_RD(src)                    (((src) & 0x00000800)>>11)
#define MBOX_20_NOT_EMPTY_SET(dst,src) \
                      (((dst) & ~0x00000800) | (((u32)(src)<<11) & 0x00000800))
/*	 Fields mbox_21_not_empty	 */
#define MBOX_21_NOT_EMPTY_WIDTH                                               1
#define MBOX_21_NOT_EMPTY_SHIFT                                              10
#define MBOX_21_NOT_EMPTY_MASK                                       0x00000400
#define MBOX_21_NOT_EMPTY_RD(src)                    (((src) & 0x00000400)>>10)
#define MBOX_21_NOT_EMPTY_SET(dst,src) \
                      (((dst) & ~0x00000400) | (((u32)(src)<<10) & 0x00000400))
/*	 Fields mbox_22_not_empty	 */
#define MBOX_22_NOT_EMPTY_WIDTH                                               1
#define MBOX_22_NOT_EMPTY_SHIFT                                               9
#define MBOX_22_NOT_EMPTY_MASK                                       0x00000200
#define MBOX_22_NOT_EMPTY_RD(src)                     (((src) & 0x00000200)>>9)
#define MBOX_22_NOT_EMPTY_SET(dst,src) \
                       (((dst) & ~0x00000200) | (((u32)(src)<<9) & 0x00000200))
/*	 Fields mbox_23_not_empty	 */
#define MBOX_23_NOT_EMPTY_WIDTH                                               1
#define MBOX_23_NOT_EMPTY_SHIFT                                               8
#define MBOX_23_NOT_EMPTY_MASK                                       0x00000100
#define MBOX_23_NOT_EMPTY_RD(src)                     (((src) & 0x00000100)>>8)
#define MBOX_23_NOT_EMPTY_SET(dst,src) \
                       (((dst) & ~0x00000100) | (((u32)(src)<<8) & 0x00000100))
/*	 Fields mbox_24_not_empty	 */
#define MBOX_24_NOT_EMPTY_WIDTH                                               1
#define MBOX_24_NOT_EMPTY_SHIFT                                               7
#define MBOX_24_NOT_EMPTY_MASK                                       0x00000080
#define MBOX_24_NOT_EMPTY_RD(src)                     (((src) & 0x00000080)>>7)
#define MBOX_24_NOT_EMPTY_SET(dst,src) \
                       (((dst) & ~0x00000080) | (((u32)(src)<<7) & 0x00000080))
/*	 Fields mbox_25_not_empty	 */
#define MBOX_25_NOT_EMPTY_WIDTH                                               1
#define MBOX_25_NOT_EMPTY_SHIFT                                               6
#define MBOX_25_NOT_EMPTY_MASK                                       0x00000040
#define MBOX_25_NOT_EMPTY_RD(src)                     (((src) & 0x00000040)>>6)
#define MBOX_25_NOT_EMPTY_SET(dst,src) \
                       (((dst) & ~0x00000040) | (((u32)(src)<<6) & 0x00000040))
/*	 Fields mbox_26_not_empty	 */
#define MBOX_26_NOT_EMPTY_WIDTH                                               1
#define MBOX_26_NOT_EMPTY_SHIFT                                               5
#define MBOX_26_NOT_EMPTY_MASK                                       0x00000020
#define MBOX_26_NOT_EMPTY_RD(src)                     (((src) & 0x00000020)>>5)
#define MBOX_26_NOT_EMPTY_SET(dst,src) \
                       (((dst) & ~0x00000020) | (((u32)(src)<<5) & 0x00000020))
/*	 Fields mbox_27_not_empty	 */
#define MBOX_27_NOT_EMPTY_WIDTH                                               1
#define MBOX_27_NOT_EMPTY_SHIFT                                               4
#define MBOX_27_NOT_EMPTY_MASK                                       0x00000010
#define MBOX_27_NOT_EMPTY_RD(src)                     (((src) & 0x00000010)>>4)
#define MBOX_27_NOT_EMPTY_SET(dst,src) \
                       (((dst) & ~0x00000010) | (((u32)(src)<<4) & 0x00000010))
/*	 Fields mbox_28_not_empty	 */
#define MBOX_28_NOT_EMPTY_WIDTH                                               1
#define MBOX_28_NOT_EMPTY_SHIFT                                               3
#define MBOX_28_NOT_EMPTY_MASK                                       0x00000008
#define MBOX_28_NOT_EMPTY_RD(src)                     (((src) & 0x00000008)>>3)
#define MBOX_28_NOT_EMPTY_SET(dst,src) \
                       (((dst) & ~0x00000008) | (((u32)(src)<<3) & 0x00000008))
/*	 Fields mbox_29_not_empty	 */
#define MBOX_29_NOT_EMPTY_WIDTH                                               1
#define MBOX_29_NOT_EMPTY_SHIFT                                               2
#define MBOX_29_NOT_EMPTY_MASK                                       0x00000004
#define MBOX_29_NOT_EMPTY_RD(src)                     (((src) & 0x00000004)>>2)
#define MBOX_29_NOT_EMPTY_SET(dst,src) \
                       (((dst) & ~0x00000004) | (((u32)(src)<<2) & 0x00000004))
/*	 Fields mbox_30_not_empty	 */
#define MBOX_30_NOT_EMPTY_WIDTH                                               1
#define MBOX_30_NOT_EMPTY_SHIFT                                               1
#define MBOX_30_NOT_EMPTY_MASK                                       0x00000002
#define MBOX_30_NOT_EMPTY_RD(src)                     (((src) & 0x00000002)>>1)
#define MBOX_30_NOT_EMPTY_SET(dst,src) \
                       (((dst) & ~0x00000002) | (((u32)(src)<<1) & 0x00000002))
/*	 Fields mbox_31_not_empty	 */
#define MBOX_31_NOT_EMPTY_WIDTH                                               1
#define MBOX_31_NOT_EMPTY_SHIFT                                               0
#define MBOX_31_NOT_EMPTY_MASK                                       0x00000001
#define MBOX_31_NOT_EMPTY_RD(src)                        (((src) & 0x00000001))
#define MBOX_31_NOT_EMPTY_SET(dst,src) \
                          (((dst) & ~0x00000001) | (((u32)(src)) & 0x00000001))

/*	Register csr_proc_sab0	*/ 
/*	 Fields queue_critical	 */
#define QUEUE_CRITICAL0_WIDTH                                                32
#define QUEUE_CRITICAL0_SHIFT                                                 0
#define QUEUE_CRITICAL0_MASK                                         0xffffffff
#define QUEUE_CRITICAL0_RD(src)                          (((src) & 0xffffffff))
#define QUEUE_CRITICAL0_SET(dst,src) \
                          (((dst) & ~0xffffffff) | (((u32)(src)) & 0xffffffff))

/*	Register csr_proc_sab1	*/ 
/*	 Fields queue_critical	 */
#define QUEUE_CRITICAL1_WIDTH                                                32
#define QUEUE_CRITICAL1_SHIFT                                                 0
#define QUEUE_CRITICAL1_MASK                                         0xffffffff
#define QUEUE_CRITICAL1_RD(src)                          (((src) & 0xffffffff))
#define QUEUE_CRITICAL1_SET(dst,src) \
                          (((dst) & ~0xffffffff) | (((u32)(src)) & 0xffffffff))

/*	Register csr_proc_sab2	*/ 
/*	 Fields queue_critical	 */
#define QUEUE_CRITICAL2_WIDTH                                                32
#define QUEUE_CRITICAL2_SHIFT                                                 0
#define QUEUE_CRITICAL2_MASK                                         0xffffffff
#define QUEUE_CRITICAL2_RD(src)                          (((src) & 0xffffffff))
#define QUEUE_CRITICAL2_SET(dst,src) \
                          (((dst) & ~0xffffffff) | (((u32)(src)) & 0xffffffff))

/*	Register csr_proc_sab3	*/ 
/*	 Fields queue_critical	 */
#define QUEUE_CRITICAL3_WIDTH                                                32
#define QUEUE_CRITICAL3_SHIFT                                                 0
#define QUEUE_CRITICAL3_MASK                                         0xffffffff
#define QUEUE_CRITICAL3_RD(src)                          (((src) & 0xffffffff))
#define QUEUE_CRITICAL3_SET(dst,src) \
                          (((dst) & ~0xffffffff) | (((u32)(src)) & 0xffffffff))

/*	Register csr_proc_sab4	*/ 
/*	 Fields queue_critical	 */
#define QUEUE_CRITICAL4_WIDTH                                                32
#define QUEUE_CRITICAL4_SHIFT                                                 0
#define QUEUE_CRITICAL4_MASK                                         0xffffffff
#define QUEUE_CRITICAL4_RD(src)                          (((src) & 0xffffffff))
#define QUEUE_CRITICAL4_SET(dst,src) \
                          (((dst) & ~0xffffffff) | (((u32)(src)) & 0xffffffff))

/*	Register csr_proc_sab5	*/ 
/*	 Fields queue_critical	 */
#define QUEUE_CRITICAL5_WIDTH                                                32
#define QUEUE_CRITICAL5_SHIFT                                                 0
#define QUEUE_CRITICAL5_MASK                                         0xffffffff
#define QUEUE_CRITICAL5_RD(src)                          (((src) & 0xffffffff))
#define QUEUE_CRITICAL5_SET(dst,src) \
                          (((dst) & ~0xffffffff) | (((u32)(src)) & 0xffffffff))

/*	Register csr_proc_sab6	*/ 
/*	 Fields queue_critical	 */
#define QUEUE_CRITICAL6_WIDTH                                                32
#define QUEUE_CRITICAL6_SHIFT                                                 0
#define QUEUE_CRITICAL6_MASK                                         0xffffffff
#define QUEUE_CRITICAL6_RD(src)                          (((src) & 0xffffffff))
#define QUEUE_CRITICAL6_SET(dst,src) \
                          (((dst) & ~0xffffffff) | (((u32)(src)) & 0xffffffff))

/*	Register csr_proc_sab7	*/ 
/*	 Fields queue_critical	 */
#define QUEUE_CRITICAL7_WIDTH                                                32
#define QUEUE_CRITICAL7_SHIFT                                                 0
#define QUEUE_CRITICAL7_MASK                                         0xffffffff
#define QUEUE_CRITICAL7_RD(src)                          (((src) & 0xffffffff))
#define QUEUE_CRITICAL7_SET(dst,src) \
                          (((dst) & ~0xffffffff) | (((u32)(src)) & 0xffffffff))

/*	Register csr_proc_sab8	*/ 
/*	 Fields queue_critical	 */
#define QUEUE_CRITICAL8_WIDTH                                                32
#define QUEUE_CRITICAL8_SHIFT                                                 0
#define QUEUE_CRITICAL8_MASK                                         0xffffffff
#define QUEUE_CRITICAL8_RD(src)                          (((src) & 0xffffffff))
#define QUEUE_CRITICAL8_SET(dst,src) \
                          (((dst) & ~0xffffffff) | (((u32)(src)) & 0xffffffff))

/*	Register csr_proc_sab9	*/ 
/*	 Fields queue_critical	 */
#define QUEUE_CRITICAL9_WIDTH                                                32
#define QUEUE_CRITICAL9_SHIFT                                                 0
#define QUEUE_CRITICAL9_MASK                                         0xffffffff
#define QUEUE_CRITICAL9_RD(src)                          (((src) & 0xffffffff))
#define QUEUE_CRITICAL9_SET(dst,src) \
                          (((dst) & ~0xffffffff) | (((u32)(src)) & 0xffffffff))

/*	Register csr_proc_sab10	*/ 
/*	 Fields queue_critical	 */
#define QUEUE_CRITICAL0_F1_WIDTH                                             32
#define QUEUE_CRITICAL0_F1_SHIFT                                              0
#define QUEUE_CRITICAL0_F1_MASK                                      0xffffffff
#define QUEUE_CRITICAL0_F1_RD(src)                       (((src) & 0xffffffff))
#define QUEUE_CRITICAL0_F1_SET(dst,src) \
                          (((dst) & ~0xffffffff) | (((u32)(src)) & 0xffffffff))

/*	Register csr_proc_sab11	*/ 
/*	 Fields queue_critical	 */
#define QUEUE_CRITICAL1_F1_WIDTH                                             32
#define QUEUE_CRITICAL1_F1_SHIFT                                              0
#define QUEUE_CRITICAL1_F1_MASK                                      0xffffffff
#define QUEUE_CRITICAL1_F1_RD(src)                       (((src) & 0xffffffff))
#define QUEUE_CRITICAL1_F1_SET(dst,src) \
                          (((dst) & ~0xffffffff) | (((u32)(src)) & 0xffffffff))

/*	Register csr_proc_sab12	*/ 
/*	 Fields queue_critical	 */
#define QUEUE_CRITICAL2_F1_WIDTH                                             32
#define QUEUE_CRITICAL2_F1_SHIFT                                              0
#define QUEUE_CRITICAL2_F1_MASK                                      0xffffffff
#define QUEUE_CRITICAL2_F1_RD(src)                       (((src) & 0xffffffff))
#define QUEUE_CRITICAL2_F1_SET(dst,src) \
                          (((dst) & ~0xffffffff) | (((u32)(src)) & 0xffffffff))

/*	Register csr_proc_sab13	*/ 
/*	 Fields queue_critical	 */
#define QUEUE_CRITICAL3_F1_WIDTH                                             32
#define QUEUE_CRITICAL3_F1_SHIFT                                              0
#define QUEUE_CRITICAL3_F1_MASK                                      0xffffffff
#define QUEUE_CRITICAL3_F1_RD(src)                       (((src) & 0xffffffff))
#define QUEUE_CRITICAL3_F1_SET(dst,src) \
                          (((dst) & ~0xffffffff) | (((u32)(src)) & 0xffffffff))

/*	Register csr_proc_sab14	*/ 
/*	 Fields queue_critical	 */
#define QUEUE_CRITICAL4_F1_WIDTH                                             32
#define QUEUE_CRITICAL4_F1_SHIFT                                              0
#define QUEUE_CRITICAL4_F1_MASK                                      0xffffffff
#define QUEUE_CRITICAL4_F1_RD(src)                       (((src) & 0xffffffff))
#define QUEUE_CRITICAL4_F1_SET(dst,src) \
                          (((dst) & ~0xffffffff) | (((u32)(src)) & 0xffffffff))

/*	Register csr_proc_sab15	*/ 
/*	 Fields queue_critical	 */
#define QUEUE_CRITICAL5_F1_WIDTH                                             32
#define QUEUE_CRITICAL5_F1_SHIFT                                              0
#define QUEUE_CRITICAL5_F1_MASK                                      0xffffffff
#define QUEUE_CRITICAL5_F1_RD(src)                       (((src) & 0xffffffff))
#define QUEUE_CRITICAL5_F1_SET(dst,src) \
                          (((dst) & ~0xffffffff) | (((u32)(src)) & 0xffffffff))

/*	Register csr_proc_sab16	*/ 
/*	 Fields queue_critical	 */
#define QUEUE_CRITICAL6_F1_WIDTH                                             32
#define QUEUE_CRITICAL6_F1_SHIFT                                              0
#define QUEUE_CRITICAL6_F1_MASK                                      0xffffffff
#define QUEUE_CRITICAL6_F1_RD(src)                       (((src) & 0xffffffff))
#define QUEUE_CRITICAL6_F1_SET(dst,src) \
                          (((dst) & ~0xffffffff) | (((u32)(src)) & 0xffffffff))

/*	Register csr_proc_sab17	*/ 
/*	 Fields queue_critical	 */
#define QUEUE_CRITICAL7_F1_WIDTH                                             32
#define QUEUE_CRITICAL7_F1_SHIFT                                              0
#define QUEUE_CRITICAL7_F1_MASK                                      0xffffffff
#define QUEUE_CRITICAL7_F1_RD(src)                       (((src) & 0xffffffff))
#define QUEUE_CRITICAL7_F1_SET(dst,src) \
                          (((dst) & ~0xffffffff) | (((u32)(src)) & 0xffffffff))

/*	Register csr_proc_sab18	*/ 
/*	 Fields queue_critical	 */
#define QUEUE_CRITICAL8_F1_WIDTH                                             32
#define QUEUE_CRITICAL8_F1_SHIFT                                              0
#define QUEUE_CRITICAL8_F1_MASK                                      0xffffffff
#define QUEUE_CRITICAL8_F1_RD(src)                       (((src) & 0xffffffff))
#define QUEUE_CRITICAL8_F1_SET(dst,src) \
                          (((dst) & ~0xffffffff) | (((u32)(src)) & 0xffffffff))

/*	Register csr_proc_sab19	*/ 
/*	 Fields queue_critical	 */
#define QUEUE_CRITICAL9_F1_WIDTH                                             32
#define QUEUE_CRITICAL9_F1_SHIFT                                              0
#define QUEUE_CRITICAL9_F1_MASK                                      0xffffffff
#define QUEUE_CRITICAL9_F1_RD(src)                       (((src) & 0xffffffff))
#define QUEUE_CRITICAL9_F1_SET(dst,src) \
                          (((dst) & ~0xffffffff) | (((u32)(src)) & 0xffffffff))

/*	Register csr_proc_sab20	*/ 
/*	 Fields queue_critical	 */
#define QUEUE_CRITICAL0_F2_WIDTH                                             32
#define QUEUE_CRITICAL0_F2_SHIFT                                              0
#define QUEUE_CRITICAL0_F2_MASK                                      0xffffffff
#define QUEUE_CRITICAL0_F2_RD(src)                       (((src) & 0xffffffff))
#define QUEUE_CRITICAL0_F2_SET(dst,src) \
                          (((dst) & ~0xffffffff) | (((u32)(src)) & 0xffffffff))

/*	Register csr_proc_sab21	*/ 
/*	 Fields queue_critical	 */
#define QUEUE_CRITICAL1_F2_WIDTH                                             32
#define QUEUE_CRITICAL1_F2_SHIFT                                              0
#define QUEUE_CRITICAL1_F2_MASK                                      0xffffffff
#define QUEUE_CRITICAL1_F2_RD(src)                       (((src) & 0xffffffff))
#define QUEUE_CRITICAL1_F2_SET(dst,src) \
                          (((dst) & ~0xffffffff) | (((u32)(src)) & 0xffffffff))

/*	Register csr_proc_sab22	*/ 
/*	 Fields queue_critical	 */
#define QUEUE_CRITICAL2_F2_WIDTH                                             32
#define QUEUE_CRITICAL2_F2_SHIFT                                              0
#define QUEUE_CRITICAL2_F2_MASK                                      0xffffffff
#define QUEUE_CRITICAL2_F2_RD(src)                       (((src) & 0xffffffff))
#define QUEUE_CRITICAL2_F2_SET(dst,src) \
                          (((dst) & ~0xffffffff) | (((u32)(src)) & 0xffffffff))

/*	Register csr_proc_sab23	*/ 
/*	 Fields queue_critical	 */
#define QUEUE_CRITICAL3_F2_WIDTH                                             32
#define QUEUE_CRITICAL3_F2_SHIFT                                              0
#define QUEUE_CRITICAL3_F2_MASK                                      0xffffffff
#define QUEUE_CRITICAL3_F2_RD(src)                       (((src) & 0xffffffff))
#define QUEUE_CRITICAL3_F2_SET(dst,src) \
                          (((dst) & ~0xffffffff) | (((u32)(src)) & 0xffffffff))

/*	Register csr_proc_sab24	*/ 
/*	 Fields queue_critical	 */
#define QUEUE_CRITICAL4_F2_WIDTH                                             32
#define QUEUE_CRITICAL4_F2_SHIFT                                              0
#define QUEUE_CRITICAL4_F2_MASK                                      0xffffffff
#define QUEUE_CRITICAL4_F2_RD(src)                       (((src) & 0xffffffff))
#define QUEUE_CRITICAL4_F2_SET(dst,src) \
                          (((dst) & ~0xffffffff) | (((u32)(src)) & 0xffffffff))

/*	Register csr_proc_sab25	*/ 
/*	 Fields queue_critical	 */
#define QUEUE_CRITICAL5_F2_WIDTH                                             32
#define QUEUE_CRITICAL5_F2_SHIFT                                              0
#define QUEUE_CRITICAL5_F2_MASK                                      0xffffffff
#define QUEUE_CRITICAL5_F2_RD(src)                       (((src) & 0xffffffff))
#define QUEUE_CRITICAL5_F2_SET(dst,src) \
                          (((dst) & ~0xffffffff) | (((u32)(src)) & 0xffffffff))

/*	Register csr_proc_sab26	*/ 
/*	 Fields queue_critical	 */
#define QUEUE_CRITICAL6_F2_WIDTH                                             32
#define QUEUE_CRITICAL6_F2_SHIFT                                              0
#define QUEUE_CRITICAL6_F2_MASK                                      0xffffffff
#define QUEUE_CRITICAL6_F2_RD(src)                       (((src) & 0xffffffff))
#define QUEUE_CRITICAL6_F2_SET(dst,src) \
                          (((dst) & ~0xffffffff) | (((u32)(src)) & 0xffffffff))

/*	Register csr_proc_sab27	*/ 
/*	 Fields queue_critical	 */
#define QUEUE_CRITICAL7_F2_WIDTH                                             32
#define QUEUE_CRITICAL7_F2_SHIFT                                              0
#define QUEUE_CRITICAL7_F2_MASK                                      0xffffffff
#define QUEUE_CRITICAL7_F2_RD(src)                       (((src) & 0xffffffff))
#define QUEUE_CRITICAL7_F2_SET(dst,src) \
                          (((dst) & ~0xffffffff) | (((u32)(src)) & 0xffffffff))

/*	Register csr_proc_sab28	*/ 
/*	 Fields queue_critical	 */
#define QUEUE_CRITICAL8_F2_WIDTH                                             32
#define QUEUE_CRITICAL8_F2_SHIFT                                              0
#define QUEUE_CRITICAL8_F2_MASK                                      0xffffffff
#define QUEUE_CRITICAL8_F2_RD(src)                       (((src) & 0xffffffff))
#define QUEUE_CRITICAL8_F2_SET(dst,src) \
                          (((dst) & ~0xffffffff) | (((u32)(src)) & 0xffffffff))

/*	Register csr_proc_sab29	*/ 
/*	 Fields queue_critical	 */
#define QUEUE_CRITICAL9_F2_WIDTH                                             32
#define QUEUE_CRITICAL9_F2_SHIFT                                              0
#define QUEUE_CRITICAL9_F2_MASK                                      0xffffffff
#define QUEUE_CRITICAL9_F2_RD(src)                       (((src) & 0xffffffff))
#define QUEUE_CRITICAL9_F2_SET(dst,src) \
                          (((dst) & ~0xffffffff) | (((u32)(src)) & 0xffffffff))

/*	Register csr_proc_sab30	*/ 
/*	 Fields queue_critical	 */
#define QUEUE_CRITICAL0_F3_WIDTH                                             32
#define QUEUE_CRITICAL0_F3_SHIFT                                              0
#define QUEUE_CRITICAL0_F3_MASK                                      0xffffffff
#define QUEUE_CRITICAL0_F3_RD(src)                       (((src) & 0xffffffff))
#define QUEUE_CRITICAL0_F3_SET(dst,src) \
                          (((dst) & ~0xffffffff) | (((u32)(src)) & 0xffffffff))

/*	Register csr_proc_sab31	*/ 
/*	 Fields queue_critical	 */
#define QUEUE_CRITICAL1_F3_WIDTH                                             32
#define QUEUE_CRITICAL1_F3_SHIFT                                              0
#define QUEUE_CRITICAL1_F3_MASK                                      0xffffffff
#define QUEUE_CRITICAL1_F3_RD(src)                       (((src) & 0xffffffff))
#define QUEUE_CRITICAL1_F3_SET(dst,src) \
                          (((dst) & ~0xffffffff) | (((u32)(src)) & 0xffffffff))

/*	Register csr_qm_stats_cfg	*/ 
/*	 Fields qid_enq_counter	 */
#define QID_ENQ_COUNTER_WIDTH                                                10
#define QID_ENQ_COUNTER_SHIFT                                                16
#define QID_ENQ_COUNTER_MASK                                         0x03ff0000
#define QID_ENQ_COUNTER_RD(src)                      (((src) & 0x03ff0000)>>16)
#define QID_ENQ_COUNTER_WR(src)                 (((u32)(src)<<16) & 0x03ff0000)
#define QID_ENQ_COUNTER_SET(dst,src) \
                      (((dst) & ~0x03ff0000) | (((u32)(src)<<16) & 0x03ff0000))
/*	 Fields qid_deq_counter	 */
#define QID_DEQ_COUNTER_WIDTH                                                10
#define QID_DEQ_COUNTER_SHIFT                                                 0
#define QID_DEQ_COUNTER_MASK                                         0x000003ff
#define QID_DEQ_COUNTER_RD(src)                          (((src) & 0x000003ff))
#define QID_DEQ_COUNTER_WR(src)                     (((u32)(src)) & 0x000003ff)
#define QID_DEQ_COUNTER_SET(dst,src) \
                          (((dst) & ~0x000003ff) | (((u32)(src)) & 0x000003ff))

/*	Register csr_enq_statistics	*/ 
/*	 Fields enq_count	 */
#define ENQ_COUNT_WIDTH                                                      32
#define ENQ_COUNT_SHIFT                                                       0
#define ENQ_COUNT_MASK                                               0xffffffff
#define ENQ_COUNT_RD(src)                                (((src) & 0xffffffff))
#define ENQ_COUNT_SET(dst,src) \
                          (((dst) & ~0xffffffff) | (((u32)(src)) & 0xffffffff))

/*	Register csr_deq_statistics	*/ 
/*	 Fields deq_count	 */
#define DEQ_COUNT_WIDTH                                                      32
#define DEQ_COUNT_SHIFT                                                       0
#define DEQ_COUNT_MASK                                               0xffffffff
#define DEQ_COUNT_RD(src)                                (((src) & 0xffffffff))
#define DEQ_COUNT_SET(dst,src) \
                          (((dst) & ~0xffffffff) | (((u32)(src)) & 0xffffffff))

/*	Register csr_fifo_status	*/ 
/*	 Fields csr_epoch_overrun	 */
#define CSR_EPOCH_OVERRUN_WIDTH                                               1
#define CSR_EPOCH_OVERRUN_SHIFT                                              31
#define CSR_EPOCH_OVERRUN_MASK                                       0x80000000
#define CSR_EPOCH_OVERRUN_RD(src)                    (((src) & 0x80000000)>>31)
#define CSR_EPOCH_OVERRUN_SET(dst,src) \
                      (((dst) & ~0x80000000) | (((u32)(src)<<31) & 0x80000000))
/*	 Fields csr_cut_busy	 */
#define CSR_CUT_BUSY_WIDTH                                                    1
#define CSR_CUT_BUSY_SHIFT                                                   30
#define CSR_CUT_BUSY_MASK                                            0x40000000
#define CSR_CUT_BUSY_RD(src)                         (((src) & 0x40000000)>>30)
#define CSR_CUT_BUSY_SET(dst,src) \
                      (((dst) & ~0x40000000) | (((u32)(src)<<30) & 0x40000000))
/*	 Fields csr_cut_toggle	 */
#define CSR_CUT_TOGGLE_WIDTH                                                  1
#define CSR_CUT_TOGGLE_SHIFT                                                 29
#define CSR_CUT_TOGGLE_MASK                                          0x20000000
#define CSR_CUT_TOGGLE_RD(src)                       (((src) & 0x20000000)>>29)
#define CSR_CUT_TOGGLE_SET(dst,src) \
                      (((dst) & ~0x20000000) | (((u32)(src)<<29) & 0x20000000))
/*	 Fields csr_qpcore_active_process	 */
#define CSR_QPCORE_ACTIVE_PROCESS_WIDTH                                       5
#define CSR_QPCORE_ACTIVE_PROCESS_SHIFT                                      22
#define CSR_QPCORE_ACTIVE_PROCESS_MASK                               0x07c00000
#define CSR_QPCORE_ACTIVE_PROCESS_RD(src)            (((src) & 0x07c00000)>>22)
#define CSR_QPCORE_ACTIVE_PROCESS_SET(dst,src) \
                      (((dst) & ~0x07c00000) | (((u32)(src)<<22) & 0x07c00000))
/*	 Fields csr_msgrd_fifo_stat	 */
#define CSR_MSGRD_FIFO_STAT_WIDTH                                             7
#define CSR_MSGRD_FIFO_STAT_SHIFT                                            12
#define CSR_MSGRD_FIFO_STAT_MASK                                     0x0007f000
#define CSR_MSGRD_FIFO_STAT_RD(src)                  (((src) & 0x0007f000)>>12)
#define CSR_MSGRD_FIFO_STAT_SET(dst,src) \
                      (((dst) & ~0x0007f000) | (((u32)(src)<<12) & 0x0007f000))
/*	 Fields csr_acr_mstr_cmd_level	 */
#define CSR_ACR_MSTR_CMD_LEVEL_WIDTH                                          4
#define CSR_ACR_MSTR_CMD_LEVEL_SHIFT                                          8
#define CSR_ACR_MSTR_CMD_LEVEL_MASK                                  0x00000f00
#define CSR_ACR_MSTR_CMD_LEVEL_RD(src)                (((src) & 0x00000f00)>>8)
#define CSR_ACR_MSTR_CMD_LEVEL_SET(dst,src) \
                       (((dst) & ~0x00000f00) | (((u32)(src)<<8) & 0x00000f00))
/*	 Fields csr_acr_allocated	 */
#define CSR_ACR_ALLOCATED_WIDTH                                               8
#define CSR_ACR_ALLOCATED_SHIFT                                               0
#define CSR_ACR_ALLOCATED_MASK                                       0x000000ff
#define CSR_ACR_ALLOCATED_RD(src)                        (((src) & 0x000000ff))
#define CSR_ACR_ALLOCATED_SET(dst,src) \
                          (((dst) & ~0x000000ff) | (((u32)(src)) & 0x000000ff))

/*	Register csr_acr_fifo_ctrl	*/ 
/*	 Fields critical_level	 */
#define CRITICAL_LEVEL_WIDTH                                                  4
#define CRITICAL_LEVEL_SHIFT                                                 28
#define CRITICAL_LEVEL_MASK                                          0xf0000000
#define CRITICAL_LEVEL_RD(src)                       (((src) & 0xf0000000)>>28)
#define CRITICAL_LEVEL_WR(src)                  (((u32)(src)<<28) & 0xf0000000)
#define CRITICAL_LEVEL_SET(dst,src) \
                      (((dst) & ~0xf0000000) | (((u32)(src)<<28) & 0xf0000000))
/*	 Fields critical_test	 */
#define CRITICAL_TEST_WIDTH                                                   1
#define CRITICAL_TEST_SHIFT                                                  24
#define CRITICAL_TEST_MASK                                           0x01000000
#define CRITICAL_TEST_RD(src)                        (((src) & 0x01000000)>>24)
#define CRITICAL_TEST_WR(src)                   (((u32)(src)<<24) & 0x01000000)
#define CRITICAL_TEST_SET(dst,src) \
                      (((dst) & ~0x01000000) | (((u32)(src)<<24) & 0x01000000))
/*	 Fields max_level	 */
#define MAX_LEVEL_WIDTH                                                       8
#define MAX_LEVEL_SHIFT                                                      16
#define MAX_LEVEL_MASK                                               0x00ff0000
#define MAX_LEVEL_RD(src)                            (((src) & 0x00ff0000)>>16)
#define MAX_LEVEL_WR(src)                       (((u32)(src)<<16) & 0x00ff0000)
#define MAX_LEVEL_SET(dst,src) \
                      (((dst) & ~0x00ff0000) | (((u32)(src)<<16) & 0x00ff0000))
/*	 Fields qmi_hold_enable	 */
#define QMI_HOLD_ENABLE_WIDTH                                                 1
#define QMI_HOLD_ENABLE_SHIFT                                                15
#define QMI_HOLD_ENABLE_MASK                                         0x00008000
#define QMI_HOLD_ENABLE_RD(src)                      (((src) & 0x00008000)>>15)
#define QMI_HOLD_ENABLE_WR(src)                 (((u32)(src)<<15) & 0x00008000)
#define QMI_HOLD_ENABLE_SET(dst,src) \
                      (((dst) & ~0x00008000) | (((u32)(src)<<15) & 0x00008000))
/*	 Fields qmi_hold_level	 */
#define QMI_HOLD_LEVEL_WIDTH                                                  8
#define QMI_HOLD_LEVEL_SHIFT                                                  0
#define QMI_HOLD_LEVEL_MASK                                          0x000000ff
#define QMI_HOLD_LEVEL_RD(src)                           (((src) & 0x000000ff))
#define QMI_HOLD_LEVEL_WR(src)                      (((u32)(src)) & 0x000000ff)
#define QMI_HOLD_LEVEL_SET(dst,src) \
                          (((dst) & ~0x000000ff) | (((u32)(src)) & 0x000000ff))

/*	Register csr_errq	*/ 
/*	 Fields unexpected_en	 */
#define UNEXPECTED_EN_WIDTH                                                   1
#define UNEXPECTED_EN_SHIFT                                                  31
#define UNEXPECTED_EN_MASK                                           0x80000000
#define UNEXPECTED_EN_RD(src)                        (((src) & 0x80000000)>>31)
#define UNEXPECTED_EN_WR(src)                   (((u32)(src)<<31) & 0x80000000)
#define UNEXPECTED_EN_SET(dst,src) \
                      (((dst) & ~0x80000000) | (((u32)(src)<<31) & 0x80000000))
/*	 Fields unexpected_qid	 */
#define UNEXPECTED_QID_WIDTH                                                 10
#define UNEXPECTED_QID_SHIFT                                                 16
#define UNEXPECTED_QID_MASK                                          0x03ff0000
#define UNEXPECTED_QID_RD(src)                       (((src) & 0x03ff0000)>>16)
#define UNEXPECTED_QID_WR(src)                  (((u32)(src)<<16) & 0x03ff0000)
#define UNEXPECTED_QID_SET(dst,src) \
                      (((dst) & ~0x03ff0000) | (((u32)(src)<<16) & 0x03ff0000))
/*	 Fields expected_en	 */
#define EXPECTED_EN_WIDTH                                                     1
#define EXPECTED_EN_SHIFT                                                    15
#define EXPECTED_EN_MASK                                             0x00008000
#define EXPECTED_EN_RD(src)                          (((src) & 0x00008000)>>15)
#define EXPECTED_EN_WR(src)                     (((u32)(src)<<15) & 0x00008000)
#define EXPECTED_EN_SET(dst,src) \
                      (((dst) & ~0x00008000) | (((u32)(src)<<15) & 0x00008000))
/*	 Fields expected_qid	 */
#define EXPECTED_QID_WIDTH                                                   10
#define EXPECTED_QID_SHIFT                                                    0
#define EXPECTED_QID_MASK                                            0x000003ff
#define EXPECTED_QID_RD(src)                             (((src) & 0x000003ff))
#define EXPECTED_QID_WR(src)                        (((u32)(src)) & 0x000003ff)
#define EXPECTED_QID_SET(dst,src) \
                          (((dst) & ~0x000003ff) | (((u32)(src)) & 0x000003ff))

/*	Register csr_qm_ram_margin	*/ 
/*	 Fields recomb_rmea	 */
#define RECOMB_RMEA_WIDTH                                                     1
#define RECOMB_RMEA_SHIFT                                                    29
#define RECOMB_RMEA_MASK                                             0x20000000
#define RECOMB_RMEA_RD(src)                          (((src) & 0x20000000)>>29)
#define RECOMB_RMEA_WR(src)                     (((u32)(src)<<29) & 0x20000000)
#define RECOMB_RMEA_SET(dst,src) \
                      (((dst) & ~0x20000000) | (((u32)(src)<<29) & 0x20000000))
/*	 Fields recomb_rmeb	 */
#define RECOMB_RMEB_WIDTH                                                     1
#define RECOMB_RMEB_SHIFT                                                    28
#define RECOMB_RMEB_MASK                                             0x10000000
#define RECOMB_RMEB_RD(src)                          (((src) & 0x10000000)>>28)
#define RECOMB_RMEB_WR(src)                     (((u32)(src)<<28) & 0x10000000)
#define RECOMB_RMEB_SET(dst,src) \
                      (((dst) & ~0x10000000) | (((u32)(src)<<28) & 0x10000000))
/*	 Fields recomb_rma	 */
#define RECOMB_RMA_WIDTH                                                      2
#define RECOMB_RMA_SHIFT                                                     26
#define RECOMB_RMA_MASK                                              0x0c000000
#define RECOMB_RMA_RD(src)                           (((src) & 0x0c000000)>>26)
#define RECOMB_RMA_WR(src)                      (((u32)(src)<<26) & 0x0c000000)
#define RECOMB_RMA_SET(dst,src) \
                      (((dst) & ~0x0c000000) | (((u32)(src)<<26) & 0x0c000000))
/*	 Fields recomb_rmb	 */
#define RECOMB_RMB_WIDTH                                                      2
#define RECOMB_RMB_SHIFT                                                     24
#define RECOMB_RMB_MASK                                              0x03000000
#define RECOMB_RMB_RD(src)                           (((src) & 0x03000000)>>24)
#define RECOMB_RMB_WR(src)                      (((u32)(src)<<24) & 0x03000000)
#define RECOMB_RMB_SET(dst,src) \
                      (((dst) & ~0x03000000) | (((u32)(src)<<24) & 0x03000000))
/*	 Fields acr_rmea	 */
#define ACR_RMEA_WIDTH                                                        1
#define ACR_RMEA_SHIFT                                                       21
#define ACR_RMEA_MASK                                                0x00200000
#define ACR_RMEA_RD(src)                             (((src) & 0x00200000)>>21)
#define ACR_RMEA_WR(src)                        (((u32)(src)<<21) & 0x00200000)
#define ACR_RMEA_SET(dst,src) \
                      (((dst) & ~0x00200000) | (((u32)(src)<<21) & 0x00200000))
/*	 Fields acr_rmeb	 */
#define ACR_RMEB_WIDTH                                                        1
#define ACR_RMEB_SHIFT                                                       20
#define ACR_RMEB_MASK                                                0x00100000
#define ACR_RMEB_RD(src)                             (((src) & 0x00100000)>>20)
#define ACR_RMEB_WR(src)                        (((u32)(src)<<20) & 0x00100000)
#define ACR_RMEB_SET(dst,src) \
                      (((dst) & ~0x00100000) | (((u32)(src)<<20) & 0x00100000))
/*	 Fields acr_rma	 */
#define ACR_RMA_WIDTH                                                         2
#define ACR_RMA_SHIFT                                                        18
#define ACR_RMA_MASK                                                 0x000c0000
#define ACR_RMA_RD(src)                              (((src) & 0x000c0000)>>18)
#define ACR_RMA_WR(src)                         (((u32)(src)<<18) & 0x000c0000)
#define ACR_RMA_SET(dst,src) \
                      (((dst) & ~0x000c0000) | (((u32)(src)<<18) & 0x000c0000))
/*	 Fields acr_rmb	 */
#define ACR_RMB_WIDTH                                                         2
#define ACR_RMB_SHIFT                                                        16
#define ACR_RMB_MASK                                                 0x00030000
#define ACR_RMB_RD(src)                              (((src) & 0x00030000)>>16)
#define ACR_RMB_WR(src)                         (((u32)(src)<<16) & 0x00030000)
#define ACR_RMB_SET(dst,src) \
                      (((dst) & ~0x00030000) | (((u32)(src)<<16) & 0x00030000))
/*	 Fields qstate_rmea	 */
#define QSTATE_RMEA_WIDTH                                                     1
#define QSTATE_RMEA_SHIFT                                                    13
#define QSTATE_RMEA_MASK                                             0x00002000
#define QSTATE_RMEA_RD(src)                          (((src) & 0x00002000)>>13)
#define QSTATE_RMEA_WR(src)                     (((u32)(src)<<13) & 0x00002000)
#define QSTATE_RMEA_SET(dst,src) \
                      (((dst) & ~0x00002000) | (((u32)(src)<<13) & 0x00002000))
/*	 Fields qstate_rmeb	 */
#define QSTATE_RMEB_WIDTH                                                     1
#define QSTATE_RMEB_SHIFT                                                    12
#define QSTATE_RMEB_MASK                                             0x00001000
#define QSTATE_RMEB_RD(src)                          (((src) & 0x00001000)>>12)
#define QSTATE_RMEB_WR(src)                     (((u32)(src)<<12) & 0x00001000)
#define QSTATE_RMEB_SET(dst,src) \
                      (((dst) & ~0x00001000) | (((u32)(src)<<12) & 0x00001000))
/*	 Fields qstate_rma	 */
#define QSTATE_RMA_WIDTH                                                      2
#define QSTATE_RMA_SHIFT                                                     10
#define QSTATE_RMA_MASK                                              0x00000c00
#define QSTATE_RMA_RD(src)                           (((src) & 0x00000c00)>>10)
#define QSTATE_RMA_WR(src)                      (((u32)(src)<<10) & 0x00000c00)
#define QSTATE_RMA_SET(dst,src) \
                      (((dst) & ~0x00000c00) | (((u32)(src)<<10) & 0x00000c00))
/*	 Fields qstate_rmb	 */
#define QSTATE_RMB_WIDTH                                                      2
#define QSTATE_RMB_SHIFT                                                      8
#define QSTATE_RMB_MASK                                              0x00000300
#define QSTATE_RMB_RD(src)                            (((src) & 0x00000300)>>8)
#define QSTATE_RMB_WR(src)                       (((u32)(src)<<8) & 0x00000300)
#define QSTATE_RMB_SET(dst,src) \
                       (((dst) & ~0x00000300) | (((u32)(src)<<8) & 0x00000300))
/*	 Fields cstate_rmea	 */
#define CSTATE_RMEA_WIDTH                                                     1
#define CSTATE_RMEA_SHIFT                                                     5
#define CSTATE_RMEA_MASK                                             0x00000020
#define CSTATE_RMEA_RD(src)                           (((src) & 0x00000020)>>5)
#define CSTATE_RMEA_WR(src)                      (((u32)(src)<<5) & 0x00000020)
#define CSTATE_RMEA_SET(dst,src) \
                       (((dst) & ~0x00000020) | (((u32)(src)<<5) & 0x00000020))
/*	 Fields cstate_rmeb	 */
#define CSTATE_RMEB_WIDTH                                                     1
#define CSTATE_RMEB_SHIFT                                                     4
#define CSTATE_RMEB_MASK                                             0x00000010
#define CSTATE_RMEB_RD(src)                           (((src) & 0x00000010)>>4)
#define CSTATE_RMEB_WR(src)                      (((u32)(src)<<4) & 0x00000010)
#define CSTATE_RMEB_SET(dst,src) \
                       (((dst) & ~0x00000010) | (((u32)(src)<<4) & 0x00000010))
/*	 Fields cstate_rma	 */
#define CSTATE_RMA_WIDTH                                                      2
#define CSTATE_RMA_SHIFT                                                      2
#define CSTATE_RMA_MASK                                              0x0000000c
#define CSTATE_RMA_RD(src)                            (((src) & 0x0000000c)>>2)
#define CSTATE_RMA_WR(src)                       (((u32)(src)<<2) & 0x0000000c)
#define CSTATE_RMA_SET(dst,src) \
                       (((dst) & ~0x0000000c) | (((u32)(src)<<2) & 0x0000000c))
/*	 Fields cstate_rmb	 */
#define CSTATE_RMB_WIDTH                                                      2
#define CSTATE_RMB_SHIFT                                                      0
#define CSTATE_RMB_MASK                                              0x00000003
#define CSTATE_RMB_RD(src)                               (((src) & 0x00000003))
#define CSTATE_RMB_WR(src)                          (((u32)(src)) & 0x00000003)
#define CSTATE_RMB_SET(dst,src) \
                          (((dst) & ~0x00000003) | (((u32)(src)) & 0x00000003))

/*	Register csr_qm_testint0	*/ 
/*	 Fields mbox	 */
#define MBOX0_WIDTH                                                          32
#define MBOX0_SHIFT                                                           0
#define MBOX0_MASK                                                   0xffffffff
#define MBOX0_RD(src)                                    (((src) & 0xffffffff))
#define MBOX0_WR(src)                               (((u32)(src)) & 0xffffffff)
#define MBOX0_SET(dst,src) \
                          (((dst) & ~0xffffffff) | (((u32)(src)) & 0xffffffff))

/*	Register csr_qm_testint1	*/ 
/*	 Fields sab_proc7	 */
#define SAB_PROC71_WIDTH                                                      1
#define SAB_PROC71_SHIFT                                                     31
#define SAB_PROC71_MASK                                              0x80000000
#define SAB_PROC71_RD(src)                           (((src) & 0x80000000)>>31)
#define SAB_PROC71_WR(src)                      (((u32)(src)<<31) & 0x80000000)
#define SAB_PROC71_SET(dst,src) \
                      (((dst) & ~0x80000000) | (((u32)(src)<<31) & 0x80000000))
/*	 Fields sab_proc6	 */
#define SAB_PROC61_WIDTH                                                      1
#define SAB_PROC61_SHIFT                                                     30
#define SAB_PROC61_MASK                                              0x40000000
#define SAB_PROC61_RD(src)                           (((src) & 0x40000000)>>30)
#define SAB_PROC61_WR(src)                      (((u32)(src)<<30) & 0x40000000)
#define SAB_PROC61_SET(dst,src) \
                      (((dst) & ~0x40000000) | (((u32)(src)<<30) & 0x40000000))
/*	 Fields sab_proc5	 */
#define SAB_PROC51_WIDTH                                                      1
#define SAB_PROC51_SHIFT                                                     29
#define SAB_PROC51_MASK                                              0x20000000
#define SAB_PROC51_RD(src)                           (((src) & 0x20000000)>>29)
#define SAB_PROC51_WR(src)                      (((u32)(src)<<29) & 0x20000000)
#define SAB_PROC51_SET(dst,src) \
                      (((dst) & ~0x20000000) | (((u32)(src)<<29) & 0x20000000))
/*	 Fields sab_proc4	 */
#define SAB_PROC41_WIDTH                                                      1
#define SAB_PROC41_SHIFT                                                     28
#define SAB_PROC41_MASK                                              0x10000000
#define SAB_PROC41_RD(src)                           (((src) & 0x10000000)>>28)
#define SAB_PROC41_WR(src)                      (((u32)(src)<<28) & 0x10000000)
#define SAB_PROC41_SET(dst,src) \
                      (((dst) & ~0x10000000) | (((u32)(src)<<28) & 0x10000000))
/*	 Fields sab_proc3	 */
#define SAB_PROC31_WIDTH                                                      1
#define SAB_PROC31_SHIFT                                                     27
#define SAB_PROC31_MASK                                              0x08000000
#define SAB_PROC31_RD(src)                           (((src) & 0x08000000)>>27)
#define SAB_PROC31_WR(src)                      (((u32)(src)<<27) & 0x08000000)
#define SAB_PROC31_SET(dst,src) \
                      (((dst) & ~0x08000000) | (((u32)(src)<<27) & 0x08000000))
/*	 Fields sab_proc2	 */
#define SAB_PROC21_WIDTH                                                      1
#define SAB_PROC21_SHIFT                                                     26
#define SAB_PROC21_MASK                                              0x04000000
#define SAB_PROC21_RD(src)                           (((src) & 0x04000000)>>26)
#define SAB_PROC21_WR(src)                      (((u32)(src)<<26) & 0x04000000)
#define SAB_PROC21_SET(dst,src) \
                      (((dst) & ~0x04000000) | (((u32)(src)<<26) & 0x04000000))
/*	 Fields sab_proc1	 */
#define SAB_PROC11_WIDTH                                                      1
#define SAB_PROC11_SHIFT                                                     25
#define SAB_PROC11_MASK                                              0x02000000
#define SAB_PROC11_RD(src)                           (((src) & 0x02000000)>>25)
#define SAB_PROC11_WR(src)                      (((u32)(src)<<25) & 0x02000000)
#define SAB_PROC11_SET(dst,src) \
                      (((dst) & ~0x02000000) | (((u32)(src)<<25) & 0x02000000))
/*	 Fields sab_proc0	 */
#define SAB_PROC01_WIDTH                                                      1
#define SAB_PROC01_SHIFT                                                     24
#define SAB_PROC01_MASK                                              0x01000000
#define SAB_PROC01_RD(src)                           (((src) & 0x01000000)>>24)
#define SAB_PROC01_WR(src)                      (((u32)(src)<<24) & 0x01000000)
#define SAB_PROC01_SET(dst,src) \
                      (((dst) & ~0x01000000) | (((u32)(src)<<24) & 0x01000000))
/*	 Fields qm_int	 */
#define QM_INT1_WIDTH                                                         1
#define QM_INT1_SHIFT                                                        20
#define QM_INT1_MASK                                                 0x00100000
#define QM_INT1_RD(src)                              (((src) & 0x00100000)>>20)
#define QM_INT1_WR(src)                         (((u32)(src)<<20) & 0x00100000)
#define QM_INT1_SET(dst,src) \
                      (((dst) & ~0x00100000) | (((u32)(src)<<20) & 0x00100000))
/*	 Fields ecc_sec	 */
#define ECC_SEC1_WIDTH                                                        6
#define ECC_SEC1_SHIFT                                                       10
#define ECC_SEC1_MASK                                                0x0000fc00
#define ECC_SEC1_RD(src)                             (((src) & 0x0000fc00)>>10)
#define ECC_SEC1_WR(src)                        (((u32)(src)<<10) & 0x0000fc00)
#define ECC_SEC1_SET(dst,src) \
                      (((dst) & ~0x0000fc00) | (((u32)(src)<<10) & 0x0000fc00))
/*	 Fields ecc_ded	 */
#define ECC_DED1_WIDTH                                                        6
#define ECC_DED1_SHIFT                                                        0
#define ECC_DED1_MASK                                                0x0000003f
#define ECC_DED1_RD(src)                                 (((src) & 0x0000003f))
#define ECC_DED1_WR(src)                            (((u32)(src)) & 0x0000003f)
#define ECC_DED1_SET(dst,src) \
                          (((dst) & ~0x0000003f) | (((u32)(src)) & 0x0000003f))

/*	Register csr_qmlite_pbn_map_0	*/ 
/*	 Fields slimpro_fpq0_mbox	 */
#define SLIMPRO_FPQ0_MBOX0_WIDTH                                              5
#define SLIMPRO_FPQ0_MBOX0_SHIFT                                             25
#define SLIMPRO_FPQ0_MBOX0_MASK                                      0x3e000000
#define SLIMPRO_FPQ0_MBOX0_RD(src)                   (((src) & 0x3e000000)>>25)
#define SLIMPRO_FPQ0_MBOX0_WR(src)              (((u32)(src)<<25) & 0x3e000000)
#define SLIMPRO_FPQ0_MBOX0_SET(dst,src) \
                      (((dst) & ~0x3e000000) | (((u32)(src)<<25) & 0x3e000000))
/*	 Fields slimpro_wq0_mbox	 */
#define SLIMPRO_WQ0_MBOX0_WIDTH                                               5
#define SLIMPRO_WQ0_MBOX0_SHIFT                                              20
#define SLIMPRO_WQ0_MBOX0_MASK                                       0x01f00000
#define SLIMPRO_WQ0_MBOX0_RD(src)                    (((src) & 0x01f00000)>>20)
#define SLIMPRO_WQ0_MBOX0_WR(src)               (((u32)(src)<<20) & 0x01f00000)
#define SLIMPRO_WQ0_MBOX0_SET(dst,src) \
                      (((dst) & ~0x01f00000) | (((u32)(src)<<20) & 0x01f00000))
/*	 Fields cop_fpq_mbox	 */
#define COP_FPQ_MBOX0_WIDTH                                                   5
#define COP_FPQ_MBOX0_SHIFT                                                  15
#define COP_FPQ_MBOX0_MASK                                           0x000f8000
#define COP_FPQ_MBOX0_RD(src)                        (((src) & 0x000f8000)>>15)
#define COP_FPQ_MBOX0_WR(src)                   (((u32)(src)<<15) & 0x000f8000)
#define COP_FPQ_MBOX0_SET(dst,src) \
                      (((dst) & ~0x000f8000) | (((u32)(src)<<15) & 0x000f8000))
/*	 Fields cop_wq_mbox	 */
#define COP_WQ_MBOX0_WIDTH                                                    5
#define COP_WQ_MBOX0_SHIFT                                                   10
#define COP_WQ_MBOX0_MASK                                            0x00007c00
#define COP_WQ_MBOX0_RD(src)                         (((src) & 0x00007c00)>>10)
#define COP_WQ_MBOX0_WR(src)                    (((u32)(src)<<10) & 0x00007c00)
#define COP_WQ_MBOX0_SET(dst,src) \
                      (((dst) & ~0x00007c00) | (((u32)(src)<<10) & 0x00007c00))
/*	 Fields cpu_fpq_mbox	 */
#define CPU_FPQ_MBOX0_WIDTH                                                   5
#define CPU_FPQ_MBOX0_SHIFT                                                   5
#define CPU_FPQ_MBOX0_MASK                                           0x000003e0
#define CPU_FPQ_MBOX0_RD(src)                         (((src) & 0x000003e0)>>5)
#define CPU_FPQ_MBOX0_WR(src)                    (((u32)(src)<<5) & 0x000003e0)
#define CPU_FPQ_MBOX0_SET(dst,src) \
                       (((dst) & ~0x000003e0) | (((u32)(src)<<5) & 0x000003e0))
/*	 Fields cpu_wq_mbox	 */
#define CPU_WQ_MBOX0_WIDTH                                                    5
#define CPU_WQ_MBOX0_SHIFT                                                    0
#define CPU_WQ_MBOX0_MASK                                            0x0000001f
#define CPU_WQ_MBOX0_RD(src)                             (((src) & 0x0000001f))
#define CPU_WQ_MBOX0_WR(src)                        (((u32)(src)) & 0x0000001f)
#define CPU_WQ_MBOX0_SET(dst,src) \
                          (((dst) & ~0x0000001f) | (((u32)(src)) & 0x0000001f))

/*	Register csr_qmlite_pbn_map_1	*/ 
/*	 Fields slimpro_fpq1_mbox	 */
#define SLIMPRO_FPQ1_MBOX1_WIDTH                                              5
#define SLIMPRO_FPQ1_MBOX1_SHIFT                                              5
#define SLIMPRO_FPQ1_MBOX1_MASK                                      0x000003e0
#define SLIMPRO_FPQ1_MBOX1_RD(src)                    (((src) & 0x000003e0)>>5)
#define SLIMPRO_FPQ1_MBOX1_WR(src)               (((u32)(src)<<5) & 0x000003e0)
#define SLIMPRO_FPQ1_MBOX1_SET(dst,src) \
                       (((dst) & ~0x000003e0) | (((u32)(src)<<5) & 0x000003e0))
/*	 Fields slimpro_wq1_mbox	 */
#define SLIMPRO_WQ1_MBOX1_WIDTH                                               5
#define SLIMPRO_WQ1_MBOX1_SHIFT                                               0
#define SLIMPRO_WQ1_MBOX1_MASK                                       0x0000001f
#define SLIMPRO_WQ1_MBOX1_RD(src)                        (((src) & 0x0000001f))
#define SLIMPRO_WQ1_MBOX1_WR(src)                   (((u32)(src)) & 0x0000001f)
#define SLIMPRO_WQ1_MBOX1_SET(dst,src) \
                          (((dst) & ~0x0000001f) | (((u32)(src)) & 0x0000001f))

/*	Register csr_recomb_ctrl_0	*/ 
/*	 Fields force_eviction_cstate_address	 */
#define FORCE_EVICTION_CSTATE_ADDRESS0_WIDTH                                  6
#define FORCE_EVICTION_CSTATE_ADDRESS0_SHIFT                                 12
#define FORCE_EVICTION_CSTATE_ADDRESS0_MASK                          0x0003f000
#define FORCE_EVICTION_CSTATE_ADDRESS0_RD(src)       (((src) & 0x0003f000)>>12)
#define FORCE_EVICTION_CSTATE_ADDRESS0_WR(src)  (((u32)(src)<<12) & 0x0003f000)
#define FORCE_EVICTION_CSTATE_ADDRESS0_SET(dst,src) \
                      (((dst) & ~0x0003f000) | (((u32)(src)<<12) & 0x0003f000))
/*	 Fields prescale_cntr	 */
#define PRESCALE_CNTR0_WIDTH                                                  2
#define PRESCALE_CNTR0_SHIFT                                                  8
#define PRESCALE_CNTR0_MASK                                          0x00000300
#define PRESCALE_CNTR0_RD(src)                        (((src) & 0x00000300)>>8)
#define PRESCALE_CNTR0_WR(src)                   (((u32)(src)<<8) & 0x00000300)
#define PRESCALE_CNTR0_SET(dst,src) \
                       (((dst) & ~0x00000300) | (((u32)(src)<<8) & 0x00000300))
/*	 Fields force_eviction_cstate	 */
#define FORCE_EVICTION_CSTATE0_WIDTH                                          1
#define FORCE_EVICTION_CSTATE0_SHIFT                                          3
#define FORCE_EVICTION_CSTATE0_MASK                                  0x00000008
#define FORCE_EVICTION_CSTATE0_RD(src)                (((src) & 0x00000008)>>3)
#define FORCE_EVICTION_CSTATE0_WR(src)           (((u32)(src)<<3) & 0x00000008)
#define FORCE_EVICTION_CSTATE0_SET(dst,src) \
                       (((dst) & ~0x00000008) | (((u32)(src)<<3) & 0x00000008))
/*	 Fields qidsb_resp_collapse_en	 */
#define QIDSB_RESP_COLLAPSE_EN0_WIDTH                                         1
#define QIDSB_RESP_COLLAPSE_EN0_SHIFT                                         2
#define QIDSB_RESP_COLLAPSE_EN0_MASK                                 0x00000004
#define QIDSB_RESP_COLLAPSE_EN0_RD(src)               (((src) & 0x00000004)>>2)
#define QIDSB_RESP_COLLAPSE_EN0_WR(src)          (((u32)(src)<<2) & 0x00000004)
#define QIDSB_RESP_COLLAPSE_EN0_SET(dst,src) \
                       (((dst) & ~0x00000004) | (((u32)(src)<<2) & 0x00000004))
/*	 Fields force_eviction	 */
#define FORCE_EVICTION0_WIDTH                                                 1
#define FORCE_EVICTION0_SHIFT                                                 1
#define FORCE_EVICTION0_MASK                                         0x00000002
#define FORCE_EVICTION0_RD(src)                       (((src) & 0x00000002)>>1)
#define FORCE_EVICTION0_WR(src)                  (((u32)(src)<<1) & 0x00000002)
#define FORCE_EVICTION0_SET(dst,src) \
                       (((dst) & ~0x00000002) | (((u32)(src)<<1) & 0x00000002))
/*	 Fields recomb_en	 */
#define RECOMB_EN0_WIDTH                                                      1
#define RECOMB_EN0_SHIFT                                                      0
#define RECOMB_EN0_MASK                                              0x00000001
#define RECOMB_EN0_RD(src)                               (((src) & 0x00000001))
#define RECOMB_EN0_WR(src)                          (((u32)(src)) & 0x00000001)
#define RECOMB_EN0_SET(dst,src) \
                          (((dst) & ~0x00000001) | (((u32)(src)) & 0x00000001))

/*	Register csr_recomb_ctrl_1	*/ 
/*	 Fields amareq_afifo_thresh	 */
#define AMAREQ_AFIFO_THRESH1_WIDTH                                            2
#define AMAREQ_AFIFO_THRESH1_SHIFT                                           24
#define AMAREQ_AFIFO_THRESH1_MASK                                    0x03000000
#define AMAREQ_AFIFO_THRESH1_RD(src)                 (((src) & 0x03000000)>>24)
#define AMAREQ_AFIFO_THRESH1_WR(src)            (((u32)(src)<<24) & 0x03000000)
#define AMAREQ_AFIFO_THRESH1_SET(dst,src) \
                      (((dst) & ~0x03000000) | (((u32)(src)<<24) & 0x03000000))
/*	 Fields amareq_dfifo_thresh	 */
#define AMAREQ_DFIFO_THRESH1_WIDTH                                            4
#define AMAREQ_DFIFO_THRESH1_SHIFT                                           16
#define AMAREQ_DFIFO_THRESH1_MASK                                    0x000f0000
#define AMAREQ_DFIFO_THRESH1_RD(src)                 (((src) & 0x000f0000)>>16)
#define AMAREQ_DFIFO_THRESH1_WR(src)            (((u32)(src)<<16) & 0x000f0000)
#define AMAREQ_DFIFO_THRESH1_SET(dst,src) \
                      (((dst) & ~0x000f0000) | (((u32)(src)<<16) & 0x000f0000))
/*	 Fields wctrl_afifo_thresh	 */
#define WCTRL_AFIFO_THRESH1_WIDTH                                             2
#define WCTRL_AFIFO_THRESH1_SHIFT                                             8
#define WCTRL_AFIFO_THRESH1_MASK                                     0x00000300
#define WCTRL_AFIFO_THRESH1_RD(src)                   (((src) & 0x00000300)>>8)
#define WCTRL_AFIFO_THRESH1_WR(src)              (((u32)(src)<<8) & 0x00000300)
#define WCTRL_AFIFO_THRESH1_SET(dst,src) \
                       (((dst) & ~0x00000300) | (((u32)(src)<<8) & 0x00000300))
/*	 Fields wctrl_dfifo_thresh	 */
#define WCTRL_DFIFO_THRESH1_WIDTH                                             4
#define WCTRL_DFIFO_THRESH1_SHIFT                                             0
#define WCTRL_DFIFO_THRESH1_MASK                                     0x0000000f
#define WCTRL_DFIFO_THRESH1_RD(src)                      (((src) & 0x0000000f))
#define WCTRL_DFIFO_THRESH1_WR(src)                 (((u32)(src)) & 0x0000000f)
#define WCTRL_DFIFO_THRESH1_SET(dst,src) \
                          (((dst) & ~0x0000000f) | (((u32)(src)) & 0x0000000f))

/*	Register csr_recomb_ctrl_2	*/ 
/*	 Fields bresp_brespfifo_thresh	 */
#define BRESP_BRESPFIFO_THRESH2_WIDTH                                         8
#define BRESP_BRESPFIFO_THRESH2_SHIFT                                        24
#define BRESP_BRESPFIFO_THRESH2_MASK                                 0xff000000
#define BRESP_BRESPFIFO_THRESH2_RD(src)              (((src) & 0xff000000)>>24)
#define BRESP_BRESPFIFO_THRESH2_WR(src)         (((u32)(src)<<24) & 0xff000000)
#define BRESP_BRESPFIFO_THRESH2_SET(dst,src) \
                      (((dst) & ~0xff000000) | (((u32)(src)<<24) & 0xff000000))
/*	 Fields bresp_vc0bfifo_thresh	 */
#define BRESP_VC0BFIFO_THRESH2_WIDTH                                          6
#define BRESP_VC0BFIFO_THRESH2_SHIFT                                         16
#define BRESP_VC0BFIFO_THRESH2_MASK                                  0x003f0000
#define BRESP_VC0BFIFO_THRESH2_RD(src)               (((src) & 0x003f0000)>>16)
#define BRESP_VC0BFIFO_THRESH2_WR(src)          (((u32)(src)<<16) & 0x003f0000)
#define BRESP_VC0BFIFO_THRESH2_SET(dst,src) \
                      (((dst) & ~0x003f0000) | (((u32)(src)<<16) & 0x003f0000))
/*	 Fields bresp_vc1bfifo_thresh	 */
#define BRESP_VC1BFIFO_THRESH2_WIDTH                                          6
#define BRESP_VC1BFIFO_THRESH2_SHIFT                                          8
#define BRESP_VC1BFIFO_THRESH2_MASK                                  0x00003f00
#define BRESP_VC1BFIFO_THRESH2_RD(src)                (((src) & 0x00003f00)>>8)
#define BRESP_VC1BFIFO_THRESH2_WR(src)           (((u32)(src)<<8) & 0x00003f00)
#define BRESP_VC1BFIFO_THRESH2_SET(dst,src) \
                       (((dst) & ~0x00003f00) | (((u32)(src)<<8) & 0x00003f00))
/*	 Fields bresp_vc2bfifo_thresh	 */
#define BRESP_VC2BFIFO_THRESH2_WIDTH                                          6
#define BRESP_VC2BFIFO_THRESH2_SHIFT                                          0
#define BRESP_VC2BFIFO_THRESH2_MASK                                  0x0000003f
#define BRESP_VC2BFIFO_THRESH2_RD(src)                   (((src) & 0x0000003f))
#define BRESP_VC2BFIFO_THRESH2_WR(src)              (((u32)(src)) & 0x0000003f)
#define BRESP_VC2BFIFO_THRESH2_SET(dst,src) \
                          (((dst) & ~0x0000003f) | (((u32)(src)) & 0x0000003f))

/*	Register csr_qm_recomb_ram_margin	*/ 
/*	 Fields qidsbmem_rmea	 */
#define QIDSBMEM_RMEA_WIDTH                                                   1
#define QIDSBMEM_RMEA_SHIFT                                                  13
#define QIDSBMEM_RMEA_MASK                                           0x00002000
#define QIDSBMEM_RMEA_RD(src)                        (((src) & 0x00002000)>>13)
#define QIDSBMEM_RMEA_WR(src)                   (((u32)(src)<<13) & 0x00002000)
#define QIDSBMEM_RMEA_SET(dst,src) \
                      (((dst) & ~0x00002000) | (((u32)(src)<<13) & 0x00002000))
/*	 Fields qidsbmem_rmeb	 */
#define QIDSBMEM_RMEB_WIDTH                                                   1
#define QIDSBMEM_RMEB_SHIFT                                                  12
#define QIDSBMEM_RMEB_MASK                                           0x00001000
#define QIDSBMEM_RMEB_RD(src)                        (((src) & 0x00001000)>>12)
#define QIDSBMEM_RMEB_WR(src)                   (((u32)(src)<<12) & 0x00001000)
#define QIDSBMEM_RMEB_SET(dst,src) \
                      (((dst) & ~0x00001000) | (((u32)(src)<<12) & 0x00001000))
/*	 Fields qidsbmem_rma	 */
#define QIDSBMEM_RMA_WIDTH                                                    2
#define QIDSBMEM_RMA_SHIFT                                                   10
#define QIDSBMEM_RMA_MASK                                            0x00000c00
#define QIDSBMEM_RMA_RD(src)                         (((src) & 0x00000c00)>>10)
#define QIDSBMEM_RMA_WR(src)                    (((u32)(src)<<10) & 0x00000c00)
#define QIDSBMEM_RMA_SET(dst,src) \
                      (((dst) & ~0x00000c00) | (((u32)(src)<<10) & 0x00000c00))
/*	 Fields qidsbmem_rmb	 */
#define QIDSBMEM_RMB_WIDTH                                                    2
#define QIDSBMEM_RMB_SHIFT                                                    8
#define QIDSBMEM_RMB_MASK                                            0x00000300
#define QIDSBMEM_RMB_RD(src)                          (((src) & 0x00000300)>>8)
#define QIDSBMEM_RMB_WR(src)                     (((u32)(src)<<8) & 0x00000300)
#define QIDSBMEM_RMB_SET(dst,src) \
                       (((dst) & ~0x00000300) | (((u32)(src)<<8) & 0x00000300))
/*	 Fields cmem_rmea	 */
#define CMEM_RMEA_WIDTH                                                       1
#define CMEM_RMEA_SHIFT                                                       5
#define CMEM_RMEA_MASK                                               0x00000020
#define CMEM_RMEA_RD(src)                             (((src) & 0x00000020)>>5)
#define CMEM_RMEA_WR(src)                        (((u32)(src)<<5) & 0x00000020)
#define CMEM_RMEA_SET(dst,src) \
                       (((dst) & ~0x00000020) | (((u32)(src)<<5) & 0x00000020))
/*	 Fields cmem_rmeb	 */
#define CMEM_RMEB_WIDTH                                                       1
#define CMEM_RMEB_SHIFT                                                       4
#define CMEM_RMEB_MASK                                               0x00000010
#define CMEM_RMEB_RD(src)                             (((src) & 0x00000010)>>4)
#define CMEM_RMEB_WR(src)                        (((u32)(src)<<4) & 0x00000010)
#define CMEM_RMEB_SET(dst,src) \
                       (((dst) & ~0x00000010) | (((u32)(src)<<4) & 0x00000010))
/*	 Fields cmem_rma	 */
#define CMEM_RMA_WIDTH                                                        2
#define CMEM_RMA_SHIFT                                                        2
#define CMEM_RMA_MASK                                                0x0000000c
#define CMEM_RMA_RD(src)                              (((src) & 0x0000000c)>>2)
#define CMEM_RMA_WR(src)                         (((u32)(src)<<2) & 0x0000000c)
#define CMEM_RMA_SET(dst,src) \
                       (((dst) & ~0x0000000c) | (((u32)(src)<<2) & 0x0000000c))
/*	 Fields cmem_rmb	 */
#define CMEM_RMB_WIDTH                                                        2
#define CMEM_RMB_SHIFT                                                        0
#define CMEM_RMB_MASK                                                0x00000003
#define CMEM_RMB_RD(src)                                 (((src) & 0x00000003))
#define CMEM_RMB_WR(src)                            (((u32)(src)) & 0x00000003)
#define CMEM_RMB_SET(dst,src) \
                          (((dst) & ~0x00000003) | (((u32)(src)) & 0x00000003))

/*	Register csr_recomb_sts_0	*/ 
/*	 Fields cstate_empty	 */
#define CSTATE_EMPTY0_WIDTH                                                   1
#define CSTATE_EMPTY0_SHIFT                                                   8
#define CSTATE_EMPTY0_MASK                                           0x00000100
#define CSTATE_EMPTY0_RD(src)                         (((src) & 0x00000100)>>8)
#define CSTATE_EMPTY0_SET(dst,src) \
                       (((dst) & ~0x00000100) | (((u32)(src)<<8) & 0x00000100))
/*	 Fields amareq_afifo_empty	 */
#define AMAREQ_AFIFO_EMPTY0_WIDTH                                             1
#define AMAREQ_AFIFO_EMPTY0_SHIFT                                             7
#define AMAREQ_AFIFO_EMPTY0_MASK                                     0x00000080
#define AMAREQ_AFIFO_EMPTY0_RD(src)                   (((src) & 0x00000080)>>7)
#define AMAREQ_AFIFO_EMPTY0_SET(dst,src) \
                       (((dst) & ~0x00000080) | (((u32)(src)<<7) & 0x00000080))
/*	 Fields amareq_dfifo_empty	 */
#define AMAREQ_DFIFO_EMPTY0_WIDTH                                             1
#define AMAREQ_DFIFO_EMPTY0_SHIFT                                             6
#define AMAREQ_DFIFO_EMPTY0_MASK                                     0x00000040
#define AMAREQ_DFIFO_EMPTY0_RD(src)                   (((src) & 0x00000040)>>6)
#define AMAREQ_DFIFO_EMPTY0_SET(dst,src) \
                       (((dst) & ~0x00000040) | (((u32)(src)<<6) & 0x00000040))
/*	 Fields bresp_brespfifo_empty	 */
#define BRESP_BRESPFIFO_EMPTY0_WIDTH                                          1
#define BRESP_BRESPFIFO_EMPTY0_SHIFT                                          5
#define BRESP_BRESPFIFO_EMPTY0_MASK                                  0x00000020
#define BRESP_BRESPFIFO_EMPTY0_RD(src)                (((src) & 0x00000020)>>5)
#define BRESP_BRESPFIFO_EMPTY0_SET(dst,src) \
                       (((dst) & ~0x00000020) | (((u32)(src)<<5) & 0x00000020))
/*	 Fields bresp_vc0bfifo_empty	 */
#define BRESP_VC0BFIFO_EMPTY0_WIDTH                                           1
#define BRESP_VC0BFIFO_EMPTY0_SHIFT                                           4
#define BRESP_VC0BFIFO_EMPTY0_MASK                                   0x00000010
#define BRESP_VC0BFIFO_EMPTY0_RD(src)                 (((src) & 0x00000010)>>4)
#define BRESP_VC0BFIFO_EMPTY0_SET(dst,src) \
                       (((dst) & ~0x00000010) | (((u32)(src)<<4) & 0x00000010))
/*	 Fields bresp_vc1bfifo_empty	 */
#define BRESP_VC1BFIFO_EMPTY0_WIDTH                                           1
#define BRESP_VC1BFIFO_EMPTY0_SHIFT                                           3
#define BRESP_VC1BFIFO_EMPTY0_MASK                                   0x00000008
#define BRESP_VC1BFIFO_EMPTY0_RD(src)                 (((src) & 0x00000008)>>3)
#define BRESP_VC1BFIFO_EMPTY0_SET(dst,src) \
                       (((dst) & ~0x00000008) | (((u32)(src)<<3) & 0x00000008))
/*	 Fields bresp_vc2bfifo_empty	 */
#define BRESP_VC2BFIFO_EMPTY0_WIDTH                                           1
#define BRESP_VC2BFIFO_EMPTY0_SHIFT                                           2
#define BRESP_VC2BFIFO_EMPTY0_MASK                                   0x00000004
#define BRESP_VC2BFIFO_EMPTY0_RD(src)                 (((src) & 0x00000004)>>2)
#define BRESP_VC2BFIFO_EMPTY0_SET(dst,src) \
                       (((dst) & ~0x00000004) | (((u32)(src)<<2) & 0x00000004))
/*	 Fields wctrl_afifo_empty	 */
#define WCTRL_AFIFO_EMPTY0_WIDTH                                              1
#define WCTRL_AFIFO_EMPTY0_SHIFT                                              1
#define WCTRL_AFIFO_EMPTY0_MASK                                      0x00000002
#define WCTRL_AFIFO_EMPTY0_RD(src)                    (((src) & 0x00000002)>>1)
#define WCTRL_AFIFO_EMPTY0_SET(dst,src) \
                       (((dst) & ~0x00000002) | (((u32)(src)<<1) & 0x00000002))
/*	 Fields wctrl_dfifo_empty	 */
#define WCTRL_DFIFO_EMPTY0_WIDTH                                              1
#define WCTRL_DFIFO_EMPTY0_SHIFT                                              0
#define WCTRL_DFIFO_EMPTY0_MASK                                      0x00000001
#define WCTRL_DFIFO_EMPTY0_RD(src)                       (((src) & 0x00000001))
#define WCTRL_DFIFO_EMPTY0_SET(dst,src) \
                          (((dst) & ~0x00000001) | (((u32)(src)) & 0x00000001))

/*	Register csr_recomb_sts_1	*/ 
/*	 Fields cstate_empty	 */
#define CSTATE_EMPTY1_WIDTH                                                  32
#define CSTATE_EMPTY1_SHIFT                                                   0
#define CSTATE_EMPTY1_MASK                                           0xffffffff
#define CSTATE_EMPTY1_RD(src)                            (((src) & 0xffffffff))
#define CSTATE_EMPTY1_SET(dst,src) \
                          (((dst) & ~0xffffffff) | (((u32)(src)) & 0xffffffff))

/*	Register csr_recomb_sts_2	*/ 
/*	 Fields cstate_empty	 */
#define CSTATE_EMPTY2_WIDTH                                                  32
#define CSTATE_EMPTY2_SHIFT                                                   0
#define CSTATE_EMPTY2_MASK                                           0xffffffff
#define CSTATE_EMPTY2_RD(src)                            (((src) & 0xffffffff))
#define CSTATE_EMPTY2_SET(dst,src) \
                          (((dst) & ~0xffffffff) | (((u32)(src)) & 0xffffffff))

/*	Register recomb_INT	*/ 
/*	 Fields amareq_afifo_overfl_intr	 */
#define AMAREQ_AFIFO_OVERFL_INTR_WIDTH                                        1
#define AMAREQ_AFIFO_OVERFL_INTR_SHIFT                                       15
#define AMAREQ_AFIFO_OVERFL_INTR_MASK                                0x00008000
#define AMAREQ_AFIFO_OVERFL_INTR_RD(src)             (((src) & 0x00008000)>>15)
#define AMAREQ_AFIFO_OVERFL_INTR_WR(src)        (((u32)(src)<<15) & 0x00008000)
#define AMAREQ_AFIFO_OVERFL_INTR_SET(dst,src) \
                      (((dst) & ~0x00008000) | (((u32)(src)<<15) & 0x00008000))
/*	 Fields amareq_afifo_underfl_intr	 */
#define AMAREQ_AFIFO_UNDERFL_INTR_WIDTH                                       1
#define AMAREQ_AFIFO_UNDERFL_INTR_SHIFT                                      14
#define AMAREQ_AFIFO_UNDERFL_INTR_MASK                               0x00004000
#define AMAREQ_AFIFO_UNDERFL_INTR_RD(src)            (((src) & 0x00004000)>>14)
#define AMAREQ_AFIFO_UNDERFL_INTR_WR(src)       (((u32)(src)<<14) & 0x00004000)
#define AMAREQ_AFIFO_UNDERFL_INTR_SET(dst,src) \
                      (((dst) & ~0x00004000) | (((u32)(src)<<14) & 0x00004000))
/*	 Fields amareq_dfifo_overfl_intr	 */
#define AMAREQ_DFIFO_OVERFL_INTR_WIDTH                                        1
#define AMAREQ_DFIFO_OVERFL_INTR_SHIFT                                       13
#define AMAREQ_DFIFO_OVERFL_INTR_MASK                                0x00002000
#define AMAREQ_DFIFO_OVERFL_INTR_RD(src)             (((src) & 0x00002000)>>13)
#define AMAREQ_DFIFO_OVERFL_INTR_WR(src)        (((u32)(src)<<13) & 0x00002000)
#define AMAREQ_DFIFO_OVERFL_INTR_SET(dst,src) \
                      (((dst) & ~0x00002000) | (((u32)(src)<<13) & 0x00002000))
/*	 Fields amareq_dfifo_underfl_intr	 */
#define AMAREQ_DFIFO_UNDERFL_INTR_WIDTH                                       1
#define AMAREQ_DFIFO_UNDERFL_INTR_SHIFT                                      12
#define AMAREQ_DFIFO_UNDERFL_INTR_MASK                               0x00001000
#define AMAREQ_DFIFO_UNDERFL_INTR_RD(src)            (((src) & 0x00001000)>>12)
#define AMAREQ_DFIFO_UNDERFL_INTR_WR(src)       (((u32)(src)<<12) & 0x00001000)
#define AMAREQ_DFIFO_UNDERFL_INTR_SET(dst,src) \
                      (((dst) & ~0x00001000) | (((u32)(src)<<12) & 0x00001000))
/*	 Fields bresp_brespfifo_overfl_intr	 */
#define BRESP_BRESPFIFO_OVERFL_INTR_WIDTH                                     1
#define BRESP_BRESPFIFO_OVERFL_INTR_SHIFT                                    11
#define BRESP_BRESPFIFO_OVERFL_INTR_MASK                             0x00000800
#define BRESP_BRESPFIFO_OVERFL_INTR_RD(src)          (((src) & 0x00000800)>>11)
#define BRESP_BRESPFIFO_OVERFL_INTR_WR(src)     (((u32)(src)<<11) & 0x00000800)
#define BRESP_BRESPFIFO_OVERFL_INTR_SET(dst,src) \
                      (((dst) & ~0x00000800) | (((u32)(src)<<11) & 0x00000800))
/*	 Fields bresp_brespfifo_underfl_intr	 */
#define BRESP_BRESPFIFO_UNDERFL_INTR_WIDTH                                    1
#define BRESP_BRESPFIFO_UNDERFL_INTR_SHIFT                                   10
#define BRESP_BRESPFIFO_UNDERFL_INTR_MASK                            0x00000400
#define BRESP_BRESPFIFO_UNDERFL_INTR_RD(src)         (((src) & 0x00000400)>>10)
#define BRESP_BRESPFIFO_UNDERFL_INTR_WR(src)    (((u32)(src)<<10) & 0x00000400)
#define BRESP_BRESPFIFO_UNDERFL_INTR_SET(dst,src) \
                      (((dst) & ~0x00000400) | (((u32)(src)<<10) & 0x00000400))
/*	 Fields bresp_vc0bfifo_overfl_intr	 */
#define BRESP_VC0BFIFO_OVERFL_INTR_WIDTH                                      1
#define BRESP_VC0BFIFO_OVERFL_INTR_SHIFT                                      9
#define BRESP_VC0BFIFO_OVERFL_INTR_MASK                              0x00000200
#define BRESP_VC0BFIFO_OVERFL_INTR_RD(src)            (((src) & 0x00000200)>>9)
#define BRESP_VC0BFIFO_OVERFL_INTR_WR(src)       (((u32)(src)<<9) & 0x00000200)
#define BRESP_VC0BFIFO_OVERFL_INTR_SET(dst,src) \
                       (((dst) & ~0x00000200) | (((u32)(src)<<9) & 0x00000200))
/*	 Fields bresp_vc0bfifo_underfl_intr	 */
#define BRESP_VC0BFIFO_UNDERFL_INTR_WIDTH                                     1
#define BRESP_VC0BFIFO_UNDERFL_INTR_SHIFT                                     8
#define BRESP_VC0BFIFO_UNDERFL_INTR_MASK                             0x00000100
#define BRESP_VC0BFIFO_UNDERFL_INTR_RD(src)           (((src) & 0x00000100)>>8)
#define BRESP_VC0BFIFO_UNDERFL_INTR_WR(src)      (((u32)(src)<<8) & 0x00000100)
#define BRESP_VC0BFIFO_UNDERFL_INTR_SET(dst,src) \
                       (((dst) & ~0x00000100) | (((u32)(src)<<8) & 0x00000100))
/*	 Fields bresp_vc1bfifo_overfl_intr	 */
#define BRESP_VC1BFIFO_OVERFL_INTR_WIDTH                                      1
#define BRESP_VC1BFIFO_OVERFL_INTR_SHIFT                                      7
#define BRESP_VC1BFIFO_OVERFL_INTR_MASK                              0x00000080
#define BRESP_VC1BFIFO_OVERFL_INTR_RD(src)            (((src) & 0x00000080)>>7)
#define BRESP_VC1BFIFO_OVERFL_INTR_WR(src)       (((u32)(src)<<7) & 0x00000080)
#define BRESP_VC1BFIFO_OVERFL_INTR_SET(dst,src) \
                       (((dst) & ~0x00000080) | (((u32)(src)<<7) & 0x00000080))
/*	 Fields bresp_vc1bfifo_underfl_intr	 */
#define BRESP_VC1BFIFO_UNDERFL_INTR_WIDTH                                     1
#define BRESP_VC1BFIFO_UNDERFL_INTR_SHIFT                                     6
#define BRESP_VC1BFIFO_UNDERFL_INTR_MASK                             0x00000040
#define BRESP_VC1BFIFO_UNDERFL_INTR_RD(src)           (((src) & 0x00000040)>>6)
#define BRESP_VC1BFIFO_UNDERFL_INTR_WR(src)      (((u32)(src)<<6) & 0x00000040)
#define BRESP_VC1BFIFO_UNDERFL_INTR_SET(dst,src) \
                       (((dst) & ~0x00000040) | (((u32)(src)<<6) & 0x00000040))
/*	 Fields bresp_vc2bfifo_overfl_intr	 */
#define BRESP_VC2BFIFO_OVERFL_INTR_WIDTH                                      1
#define BRESP_VC2BFIFO_OVERFL_INTR_SHIFT                                      5
#define BRESP_VC2BFIFO_OVERFL_INTR_MASK                              0x00000020
#define BRESP_VC2BFIFO_OVERFL_INTR_RD(src)            (((src) & 0x00000020)>>5)
#define BRESP_VC2BFIFO_OVERFL_INTR_WR(src)       (((u32)(src)<<5) & 0x00000020)
#define BRESP_VC2BFIFO_OVERFL_INTR_SET(dst,src) \
                       (((dst) & ~0x00000020) | (((u32)(src)<<5) & 0x00000020))
/*	 Fields bresp_vc2bfifo_underfl_intr	 */
#define BRESP_VC2BFIFO_UNDERFL_INTR_WIDTH                                     1
#define BRESP_VC2BFIFO_UNDERFL_INTR_SHIFT                                     4
#define BRESP_VC2BFIFO_UNDERFL_INTR_MASK                             0x00000010
#define BRESP_VC2BFIFO_UNDERFL_INTR_RD(src)           (((src) & 0x00000010)>>4)
#define BRESP_VC2BFIFO_UNDERFL_INTR_WR(src)      (((u32)(src)<<4) & 0x00000010)
#define BRESP_VC2BFIFO_UNDERFL_INTR_SET(dst,src) \
                       (((dst) & ~0x00000010) | (((u32)(src)<<4) & 0x00000010))
/*	 Fields wctrl_afifo_overfl_intr	 */
#define WCTRL_AFIFO_OVERFL_INTR_WIDTH                                         1
#define WCTRL_AFIFO_OVERFL_INTR_SHIFT                                         3
#define WCTRL_AFIFO_OVERFL_INTR_MASK                                 0x00000008
#define WCTRL_AFIFO_OVERFL_INTR_RD(src)               (((src) & 0x00000008)>>3)
#define WCTRL_AFIFO_OVERFL_INTR_WR(src)          (((u32)(src)<<3) & 0x00000008)
#define WCTRL_AFIFO_OVERFL_INTR_SET(dst,src) \
                       (((dst) & ~0x00000008) | (((u32)(src)<<3) & 0x00000008))
/*	 Fields wctrl_afifo_underfl_intr	 */
#define WCTRL_AFIFO_UNDERFL_INTR_WIDTH                                        1
#define WCTRL_AFIFO_UNDERFL_INTR_SHIFT                                        2
#define WCTRL_AFIFO_UNDERFL_INTR_MASK                                0x00000004
#define WCTRL_AFIFO_UNDERFL_INTR_RD(src)              (((src) & 0x00000004)>>2)
#define WCTRL_AFIFO_UNDERFL_INTR_WR(src)         (((u32)(src)<<2) & 0x00000004)
#define WCTRL_AFIFO_UNDERFL_INTR_SET(dst,src) \
                       (((dst) & ~0x00000004) | (((u32)(src)<<2) & 0x00000004))
/*	 Fields wctrl_dfifo_overfl_intr	 */
#define WCTRL_DFIFO_OVERFL_INTR_WIDTH                                         1
#define WCTRL_DFIFO_OVERFL_INTR_SHIFT                                         1
#define WCTRL_DFIFO_OVERFL_INTR_MASK                                 0x00000002
#define WCTRL_DFIFO_OVERFL_INTR_RD(src)               (((src) & 0x00000002)>>1)
#define WCTRL_DFIFO_OVERFL_INTR_WR(src)          (((u32)(src)<<1) & 0x00000002)
#define WCTRL_DFIFO_OVERFL_INTR_SET(dst,src) \
                       (((dst) & ~0x00000002) | (((u32)(src)<<1) & 0x00000002))
/*	 Fields wctrl_dfifo_underfl_intr	 */
#define WCTRL_DFIFO_UNDERFL_INTR_WIDTH                                        1
#define WCTRL_DFIFO_UNDERFL_INTR_SHIFT                                        0
#define WCTRL_DFIFO_UNDERFL_INTR_MASK                                0x00000001
#define WCTRL_DFIFO_UNDERFL_INTR_RD(src)                 (((src) & 0x00000001))
#define WCTRL_DFIFO_UNDERFL_INTR_WR(src)            (((u32)(src)) & 0x00000001)
#define WCTRL_DFIFO_UNDERFL_INTR_SET(dst,src) \
                          (((dst) & ~0x00000001) | (((u32)(src)) & 0x00000001))

/*	Register recomb_interruptMask	*/
/*    Mask Register Fields amareq_afifo_overfl_intrMask    */
#define AMAREQ_AFIFO_OVERFL_INTRMASK_WIDTH                                    1
#define AMAREQ_AFIFO_OVERFL_INTRMASK_SHIFT                                   15
#define AMAREQ_AFIFO_OVERFL_INTRMASK_MASK                            0x00008000
#define AMAREQ_AFIFO_OVERFL_INTRMASK_RD(src)         (((src) & 0x00008000)>>15)
#define AMAREQ_AFIFO_OVERFL_INTRMASK_WR(src)    (((u32)(src)<<15) & 0x00008000)
#define AMAREQ_AFIFO_OVERFL_INTRMASK_SET(dst,src) \
                      (((dst) & ~0x00008000) | (((u32)(src)<<15) & 0x00008000))
/*    Mask Register Fields amareq_afifo_underfl_intrMask    */
#define AMAREQ_AFIFO_UNDERFL_INTRMASK_WIDTH                                   1
#define AMAREQ_AFIFO_UNDERFL_INTRMASK_SHIFT                                  14
#define AMAREQ_AFIFO_UNDERFL_INTRMASK_MASK                           0x00004000
#define AMAREQ_AFIFO_UNDERFL_INTRMASK_RD(src)        (((src) & 0x00004000)>>14)
#define AMAREQ_AFIFO_UNDERFL_INTRMASK_WR(src)   (((u32)(src)<<14) & 0x00004000)
#define AMAREQ_AFIFO_UNDERFL_INTRMASK_SET(dst,src) \
                      (((dst) & ~0x00004000) | (((u32)(src)<<14) & 0x00004000))
/*    Mask Register Fields amareq_dfifo_overfl_intrMask    */
#define AMAREQ_DFIFO_OVERFL_INTRMASK_WIDTH                                    1
#define AMAREQ_DFIFO_OVERFL_INTRMASK_SHIFT                                   13
#define AMAREQ_DFIFO_OVERFL_INTRMASK_MASK                            0x00002000
#define AMAREQ_DFIFO_OVERFL_INTRMASK_RD(src)         (((src) & 0x00002000)>>13)
#define AMAREQ_DFIFO_OVERFL_INTRMASK_WR(src)    (((u32)(src)<<13) & 0x00002000)
#define AMAREQ_DFIFO_OVERFL_INTRMASK_SET(dst,src) \
                      (((dst) & ~0x00002000) | (((u32)(src)<<13) & 0x00002000))
/*    Mask Register Fields amareq_dfifo_underfl_intrMask    */
#define AMAREQ_DFIFO_UNDERFL_INTRMASK_WIDTH                                   1
#define AMAREQ_DFIFO_UNDERFL_INTRMASK_SHIFT                                  12
#define AMAREQ_DFIFO_UNDERFL_INTRMASK_MASK                           0x00001000
#define AMAREQ_DFIFO_UNDERFL_INTRMASK_RD(src)        (((src) & 0x00001000)>>12)
#define AMAREQ_DFIFO_UNDERFL_INTRMASK_WR(src)   (((u32)(src)<<12) & 0x00001000)
#define AMAREQ_DFIFO_UNDERFL_INTRMASK_SET(dst,src) \
                      (((dst) & ~0x00001000) | (((u32)(src)<<12) & 0x00001000))
/*    Mask Register Fields bresp_brespfifo_overfl_intrMask    */
#define BRESP_BRESPFIFO_OVERFL_INTRMASK_WIDTH                                 1
#define BRESP_BRESPFIFO_OVERFL_INTRMASK_SHIFT                                11
#define BRESP_BRESPFIFO_OVERFL_INTRMASK_MASK                         0x00000800
#define BRESP_BRESPFIFO_OVERFL_INTRMASK_RD(src)      (((src) & 0x00000800)>>11)
#define BRESP_BRESPFIFO_OVERFL_INTRMASK_WR(src) \
                                                (((u32)(src)<<11) & 0x00000800)
#define BRESP_BRESPFIFO_OVERFL_INTRMASK_SET(dst,src) \
                      (((dst) & ~0x00000800) | (((u32)(src)<<11) & 0x00000800))
/*    Mask Register Fields bresp_brespfifo_underfl_intrMask    */
#define BRESP_BRESPFIFO_UNDERFL_INTRMASK_WIDTH                                1
#define BRESP_BRESPFIFO_UNDERFL_INTRMASK_SHIFT                               10
#define BRESP_BRESPFIFO_UNDERFL_INTRMASK_MASK                        0x00000400
#define BRESP_BRESPFIFO_UNDERFL_INTRMASK_RD(src)     (((src) & 0x00000400)>>10)
#define BRESP_BRESPFIFO_UNDERFL_INTRMASK_WR(src) \
                                                (((u32)(src)<<10) & 0x00000400)
#define BRESP_BRESPFIFO_UNDERFL_INTRMASK_SET(dst,src) \
                      (((dst) & ~0x00000400) | (((u32)(src)<<10) & 0x00000400))
/*    Mask Register Fields bresp_vc0bfifo_overfl_intrMask    */
#define BRESP_VC0BFIFO_OVERFL_INTRMASK_WIDTH                                  1
#define BRESP_VC0BFIFO_OVERFL_INTRMASK_SHIFT                                  9
#define BRESP_VC0BFIFO_OVERFL_INTRMASK_MASK                          0x00000200
#define BRESP_VC0BFIFO_OVERFL_INTRMASK_RD(src)        (((src) & 0x00000200)>>9)
#define BRESP_VC0BFIFO_OVERFL_INTRMASK_WR(src)   (((u32)(src)<<9) & 0x00000200)
#define BRESP_VC0BFIFO_OVERFL_INTRMASK_SET(dst,src) \
                       (((dst) & ~0x00000200) | (((u32)(src)<<9) & 0x00000200))
/*    Mask Register Fields bresp_vc0bfifo_underfl_intrMask    */
#define BRESP_VC0BFIFO_UNDERFL_INTRMASK_WIDTH                                 1
#define BRESP_VC0BFIFO_UNDERFL_INTRMASK_SHIFT                                 8
#define BRESP_VC0BFIFO_UNDERFL_INTRMASK_MASK                         0x00000100
#define BRESP_VC0BFIFO_UNDERFL_INTRMASK_RD(src)       (((src) & 0x00000100)>>8)
#define BRESP_VC0BFIFO_UNDERFL_INTRMASK_WR(src)  (((u32)(src)<<8) & 0x00000100)
#define BRESP_VC0BFIFO_UNDERFL_INTRMASK_SET(dst,src) \
                       (((dst) & ~0x00000100) | (((u32)(src)<<8) & 0x00000100))
/*    Mask Register Fields bresp_vc1bfifo_overfl_intrMask    */
#define BRESP_VC1BFIFO_OVERFL_INTRMASK_WIDTH                                  1
#define BRESP_VC1BFIFO_OVERFL_INTRMASK_SHIFT                                  7
#define BRESP_VC1BFIFO_OVERFL_INTRMASK_MASK                          0x00000080
#define BRESP_VC1BFIFO_OVERFL_INTRMASK_RD(src)        (((src) & 0x00000080)>>7)
#define BRESP_VC1BFIFO_OVERFL_INTRMASK_WR(src)   (((u32)(src)<<7) & 0x00000080)
#define BRESP_VC1BFIFO_OVERFL_INTRMASK_SET(dst,src) \
                       (((dst) & ~0x00000080) | (((u32)(src)<<7) & 0x00000080))
/*    Mask Register Fields bresp_vc1bfifo_underfl_intrMask    */
#define BRESP_VC1BFIFO_UNDERFL_INTRMASK_WIDTH                                 1
#define BRESP_VC1BFIFO_UNDERFL_INTRMASK_SHIFT                                 6
#define BRESP_VC1BFIFO_UNDERFL_INTRMASK_MASK                         0x00000040
#define BRESP_VC1BFIFO_UNDERFL_INTRMASK_RD(src)       (((src) & 0x00000040)>>6)
#define BRESP_VC1BFIFO_UNDERFL_INTRMASK_WR(src)  (((u32)(src)<<6) & 0x00000040)
#define BRESP_VC1BFIFO_UNDERFL_INTRMASK_SET(dst,src) \
                       (((dst) & ~0x00000040) | (((u32)(src)<<6) & 0x00000040))
/*    Mask Register Fields bresp_vc2bfifo_overfl_intrMask    */
#define BRESP_VC2BFIFO_OVERFL_INTRMASK_WIDTH                                  1
#define BRESP_VC2BFIFO_OVERFL_INTRMASK_SHIFT                                  5
#define BRESP_VC2BFIFO_OVERFL_INTRMASK_MASK                          0x00000020
#define BRESP_VC2BFIFO_OVERFL_INTRMASK_RD(src)        (((src) & 0x00000020)>>5)
#define BRESP_VC2BFIFO_OVERFL_INTRMASK_WR(src)   (((u32)(src)<<5) & 0x00000020)
#define BRESP_VC2BFIFO_OVERFL_INTRMASK_SET(dst,src) \
                       (((dst) & ~0x00000020) | (((u32)(src)<<5) & 0x00000020))
/*    Mask Register Fields bresp_vc2bfifo_underfl_intrMask    */
#define BRESP_VC2BFIFO_UNDERFL_INTRMASK_WIDTH                                 1
#define BRESP_VC2BFIFO_UNDERFL_INTRMASK_SHIFT                                 4
#define BRESP_VC2BFIFO_UNDERFL_INTRMASK_MASK                         0x00000010
#define BRESP_VC2BFIFO_UNDERFL_INTRMASK_RD(src)       (((src) & 0x00000010)>>4)
#define BRESP_VC2BFIFO_UNDERFL_INTRMASK_WR(src)  (((u32)(src)<<4) & 0x00000010)
#define BRESP_VC2BFIFO_UNDERFL_INTRMASK_SET(dst,src) \
                       (((dst) & ~0x00000010) | (((u32)(src)<<4) & 0x00000010))
/*    Mask Register Fields wctrl_afifo_overfl_intrMask    */
#define WCTRL_AFIFO_OVERFL_INTRMASK_WIDTH                                     1
#define WCTRL_AFIFO_OVERFL_INTRMASK_SHIFT                                     3
#define WCTRL_AFIFO_OVERFL_INTRMASK_MASK                             0x00000008
#define WCTRL_AFIFO_OVERFL_INTRMASK_RD(src)           (((src) & 0x00000008)>>3)
#define WCTRL_AFIFO_OVERFL_INTRMASK_WR(src)      (((u32)(src)<<3) & 0x00000008)
#define WCTRL_AFIFO_OVERFL_INTRMASK_SET(dst,src) \
                       (((dst) & ~0x00000008) | (((u32)(src)<<3) & 0x00000008))
/*    Mask Register Fields wctrl_afifo_underfl_intrMask    */
#define WCTRL_AFIFO_UNDERFL_INTRMASK_WIDTH                                    1
#define WCTRL_AFIFO_UNDERFL_INTRMASK_SHIFT                                    2
#define WCTRL_AFIFO_UNDERFL_INTRMASK_MASK                            0x00000004
#define WCTRL_AFIFO_UNDERFL_INTRMASK_RD(src)          (((src) & 0x00000004)>>2)
#define WCTRL_AFIFO_UNDERFL_INTRMASK_WR(src)     (((u32)(src)<<2) & 0x00000004)
#define WCTRL_AFIFO_UNDERFL_INTRMASK_SET(dst,src) \
                       (((dst) & ~0x00000004) | (((u32)(src)<<2) & 0x00000004))
/*    Mask Register Fields wctrl_dfifo_overfl_intrMask    */
#define WCTRL_DFIFO_OVERFL_INTRMASK_WIDTH                                     1
#define WCTRL_DFIFO_OVERFL_INTRMASK_SHIFT                                     1
#define WCTRL_DFIFO_OVERFL_INTRMASK_MASK                             0x00000002
#define WCTRL_DFIFO_OVERFL_INTRMASK_RD(src)           (((src) & 0x00000002)>>1)
#define WCTRL_DFIFO_OVERFL_INTRMASK_WR(src)      (((u32)(src)<<1) & 0x00000002)
#define WCTRL_DFIFO_OVERFL_INTRMASK_SET(dst,src) \
                       (((dst) & ~0x00000002) | (((u32)(src)<<1) & 0x00000002))
/*    Mask Register Fields wctrl_dfifo_underfl_intrMask    */
#define WCTRL_DFIFO_UNDERFL_INTRMASK_WIDTH                                    1
#define WCTRL_DFIFO_UNDERFL_INTRMASK_SHIFT                                    0
#define WCTRL_DFIFO_UNDERFL_INTRMASK_MASK                            0x00000001
#define WCTRL_DFIFO_UNDERFL_INTRMASK_RD(src)             (((src) & 0x00000001))
#define WCTRL_DFIFO_UNDERFL_INTRMASK_WR(src)        (((u32)(src)) & 0x00000001)
#define WCTRL_DFIFO_UNDERFL_INTRMASK_SET(dst,src) \
                          (((dst) & ~0x00000001) | (((u32)(src)) & 0x00000001))

/*	Register csr_deq_ctrl_0	*/ 
/*	 Fields dis_256mbox	 */
#define DIS_256MBOX0_WIDTH                                                    1
#define DIS_256MBOX0_SHIFT                                                    2
#define DIS_256MBOX0_MASK                                            0x00000004
#define DIS_256MBOX0_RD(src)                          (((src) & 0x00000004)>>2)
#define DIS_256MBOX0_WR(src)                     (((u32)(src)<<2) & 0x00000004)
#define DIS_256MBOX0_SET(dst,src) \
                       (((dst) & ~0x00000004) | (((u32)(src)<<2) & 0x00000004))
/*	 Fields dis_4msg_push	 */
#define DIS_4MSG_PUSH0_WIDTH                                                  1
#define DIS_4MSG_PUSH0_SHIFT                                                  1
#define DIS_4MSG_PUSH0_MASK                                          0x00000002
#define DIS_4MSG_PUSH0_RD(src)                        (((src) & 0x00000002)>>1)
#define DIS_4MSG_PUSH0_WR(src)                   (((u32)(src)<<1) & 0x00000002)
#define DIS_4MSG_PUSH0_SET(dst,src) \
                       (((dst) & ~0x00000002) | (((u32)(src)<<1) & 0x00000002))
/*	 Fields dis_half_64b_push	 */
#define DIS_HALF_64B_PUSH0_WIDTH                                              1
#define DIS_HALF_64B_PUSH0_SHIFT                                              0
#define DIS_HALF_64B_PUSH0_MASK                                      0x00000001
#define DIS_HALF_64B_PUSH0_RD(src)                       (((src) & 0x00000001))
#define DIS_HALF_64B_PUSH0_WR(src)                  (((u32)(src)) & 0x00000001)
#define DIS_HALF_64B_PUSH0_SET(dst,src) \
                          (((dst) & ~0x00000001) | (((u32)(src)) & 0x00000001))

/*	Register csr_mpic_ctrl_0	*/ 
/*	 Fields dis_irq2wr	 */
#define DIS_IRQ2WR0_WIDTH                                                     1
#define DIS_IRQ2WR0_SHIFT                                                     0
#define DIS_IRQ2WR0_MASK                                             0x00000001
#define DIS_IRQ2WR0_RD(src)                              (((src) & 0x00000001))
#define DIS_IRQ2WR0_WR(src)                         (((u32)(src)) & 0x00000001)
#define DIS_IRQ2WR0_SET(dst,src) \
                          (((dst) & ~0x00000001) | (((u32)(src)) & 0x00000001))

/*	Register csr_misc_ctrl_0	*/ 
/*	 Fields sab_en_override	 */
#define SAB_EN_OVERRIDE0_WIDTH                                                1
#define SAB_EN_OVERRIDE0_SHIFT                                                4
#define SAB_EN_OVERRIDE0_MASK                                        0x00000010
#define SAB_EN_OVERRIDE0_RD(src)                      (((src) & 0x00000010)>>4)
#define SAB_EN_OVERRIDE0_WR(src)                 (((u32)(src)<<4) & 0x00000010)
#define SAB_EN_OVERRIDE0_SET(dst,src) \
                       (((dst) & ~0x00000010) | (((u32)(src)<<4) & 0x00000010))
/*	 Fields qmi_hold_hyst	 */
#define QMI_HOLD_HYST0_WIDTH                                                  4
#define QMI_HOLD_HYST0_SHIFT                                                  0
#define QMI_HOLD_HYST0_MASK                                          0x0000000f
#define QMI_HOLD_HYST0_RD(src)                           (((src) & 0x0000000f))
#define QMI_HOLD_HYST0_WR(src)                      (((u32)(src)) & 0x0000000f)
#define QMI_HOLD_HYST0_SET(dst,src) \
                          (((dst) & ~0x0000000f) | (((u32)(src)) & 0x0000000f))

/*	Register pbm_diagdata_ctrl_0	*/ 
/*	 Fields sel	 */
#define QM_SEL0_WIDTH                                                    8
#define QM_SEL0_SHIFT                                                    0
#define QM_SEL0_MASK                                            0x000000ff
#define QM_SEL0_RD(src)                             (((src) & 0x000000ff))
#define QM_SEL0_WR(src)                        (((u32)(src)) & 0x000000ff)
#define QM_SEL0_SET(dst,src) \
                          (((dst) & ~0x000000ff) | (((u32)(src)) & 0x000000ff))

/*	Global Base Address	*/
#define QM_CLKRST_CSR_BASE_ADDR			0x01f20c000ULL
#define QM_CLKRST_CSR_BASE_ADDR_OFFSET			0xc000

/*    Address QM_CLKRST_CSR  Registers */
#define QM_SRST_ADDR                                                 0x00000200
#define QM_SRST_DEFAULT                                              0x00000003
#define QM_CLKEN_ADDR                                                0x00000208
#define QM_CLKEN_DEFAULT                                             0x00000000

/*	Register qm_srst	*/ 
/*	 Fields qm_reset	 */
#define QM_RESET_WIDTH                                                        1
#define QM_RESET_SHIFT                                                        1
#define QM_RESET_MASK                                                0x00000002
#define QM_RESET_RD(src)                              (((src) & 0x00000002)>>1)
#define QM_RESET_WR(src)                         (((u32)(src)<<1) & 0x00000002)
#define QM_RESET_SET(dst,src) \
                       (((dst) & ~0x00000002) | (((u32)(src)<<1) & 0x00000002))
/*	 Fields csr_reset	 */
#define CSR_RESET_WIDTH                                                       1
#define CSR_RESET_SHIFT                                                       0
#define CSR_RESET_MASK                                               0x00000001
#define CSR_RESET_RD(src)                                (((src) & 0x00000001))
#define CSR_RESET_WR(src)                           (((u32)(src)) & 0x00000001)
#define CSR_RESET_SET(dst,src) \
                          (((dst) & ~0x00000001) | (((u32)(src)) & 0x00000001))

/*	Register qm_clken	*/ 
/*	 Fields qm_clken	 */
#define QM_CLKEN_WIDTH                                                        1
#define QM_CLKEN_SHIFT                                                        1
#define QM_CLKEN_MASK                                                0x00000002
#define QM_CLKEN_RD(src)                              (((src) & 0x00000002)>>1)
#define QM_CLKEN_WR(src)                         (((u32)(src)<<1) & 0x00000002)
#define QM_CLKEN_SET(dst,src) \
                       (((dst) & ~0x00000002) | (((u32)(src)<<1) & 0x00000002))
/*	 Fields csr_clken	 */
#define CSR_CLKEN_WIDTH                                                       1
#define CSR_CLKEN_SHIFT                                                       0
#define CSR_CLKEN_MASK                                               0x00000001
#define CSR_CLKEN_RD(src)                                (((src) & 0x00000001))
#define CSR_CLKEN_WR(src)                           (((u32)(src)) & 0x00000001)
#define CSR_CLKEN_SET(dst,src) \
                          (((dst) & ~0x00000001) | (((u32)(src)) & 0x00000001))

/*	Global Base Address	*/
#define QM_GLBL_DIAG_CSR_BASE_ADDR			0x01f20d000ULL
#define QM_GLBL_DIAG_CSR_BASE_ADDR_OFFSET			0xd000

/*    Address GLBL_DIAG_CSR  Registers */
#define QM_CFG_DIAG_SEL_ADDR                                    0x00000000
#define QM_CFG_DIAG_SEL_DEFAULT                                 0x00000000
#define QM_CFG_READ_BW_LAT_ADDR_MASK_ADDR                       0x00000004
#define QM_CFG_READ_BW_LAT_ADDR_MASK_DEFAULT                    0x00000000
#define QM_CFG_READ_BW_LAT_ADDR_PAT_ADDR                        0x00000008
#define QM_CFG_READ_BW_LAT_ADDR_PAT_DEFAULT                     0xffffffff
#define QM_CFG_WRITE_BW_LAT_ADDR_MASK_ADDR                      0x0000000c
#define QM_CFG_WRITE_BW_LAT_ADDR_MASK_DEFAULT                   0x00000000
#define QM_CFG_WRITE_BW_LAT_ADDR_PAT_ADDR                       0x00000010
#define QM_CFG_WRITE_BW_LAT_ADDR_PAT_DEFAULT                    0xffffffff
#define QM_CFG_DIAG_START_STOP_ADDR                             0x00000014
#define QM_CFG_DIAG_START_STOP_DEFAULT                          0x000003ff
#define QM_CFG_BW_MSTR_STOP_CNT_ADDR                            0x00000018
#define QM_CFG_BW_MSTR_STOP_CNT_DEFAULT                         0x00040004
#define QM_CFG_BW_SLV_STOP_CNT_ADDR                             0x0000001c
#define QM_CFG_BW_SLV_STOP_CNT_DEFAULT                          0x00040004
#define QM_STS_READ_LATENCY_OUTPUT_ADDR                         0x00000020
#define QM_STS_READ_LATENCY_OUTPUT_DEFAULT                      0x00000000
#define QM_STS_AXI_MRD_BW_CLK_CNT_ADDR                          0x00000024
#define QM_STS_AXI_MRD_BW_CLK_CNT_DEFAULT                       0x00000000
#define QM_STS_AXI_MRD_BW_BYTE_CNT_ADDR                         0x00000028
#define QM_STS_AXI_MRD_BW_BYTE_CNT_DEFAULT                      0x00000000
#define QM_STS_AXI_MWR_BW_CLK_CNT_ADDR                          0x0000002c
#define QM_STS_AXI_MWR_BW_CLK_CNT_DEFAULT                       0x00000000
#define QM_STS_AXI_MWR_BW_BYTE_CNT_ADDR                         0x00000030
#define QM_STS_AXI_MWR_BW_BYTE_CNT_DEFAULT                      0x00000000
#define QM_STS_AXI_SRD_BW_CLK_CNT_ADDR                          0x00000034
#define QM_STS_AXI_SRD_BW_CLK_CNT_DEFAULT                       0x00000000
#define QM_STS_AXI_SRD_BW_BYTE_CNT_ADDR                         0x00000038
#define QM_STS_AXI_SRD_BW_BYTE_CNT_DEFAULT                      0x00000000
#define QM_STS_AXI_SWR_BW_CLK_CNT_ADDR                          0x0000003c
#define QM_STS_AXI_SWR_BW_CLK_CNT_DEFAULT                       0x00000000
#define QM_STS_AXI_SWR_BW_BYTE_CNT_ADDR                         0x00000040
#define QM_STS_AXI_SWR_BW_BYTE_CNT_DEFAULT                      0x00000000
#define QM_CFG_DBG_TRIG_CTRL_ADDR                               0x00000044
#define QM_CFG_DBG_TRIG_CTRL_DEFAULT                            0x00000000
#define QM_CFG_DBG_PAT_REG_0_ADDR                               0x00000048
#define QM_CFG_DBG_PAT_REG_0_DEFAULT                            0x00000000
#define QM_CFG_DBG_PAT_MASK_REG_0_ADDR                          0x0000004c
#define QM_CFG_DBG_PAT_MASK_REG_0_DEFAULT                       0x00000000
#define QM_CFG_DBG_PAT_REG_1_ADDR                               0x00000050
#define QM_CFG_DBG_PAT_REG_1_DEFAULT                            0x00000000
#define QM_CFG_DBG_PAT_MASK_REG_1_ADDR                          0x00000054
#define QM_CFG_DBG_PAT_MASK_REG_1_DEFAULT                       0x00000000
#define QM_DBG_TRIG_OUT_ADDR                                    0x00000058
#define QM_DBG_TRIG_OUT_DEFAULT                                 0x00000000
#define QM_DBG_TRIG_INT_ADDR                                    0x0000005c
#define QM_DBG_TRIG_INT_DEFAULT                                 0x00000000
#define QM_DBG_TRIG_INTMASK_ADDR                                0x00000060
#define QM_INTR_STS_ADDR                                        0x00000064
#define QM_INTR_STS_DEFAULT                                     0x00000000
#define QM_CFG_MEM_ECC_BYPASS_ADDR                              0x00000068
#define QM_CFG_MEM_ECC_BYPASS_DEFAULT                           0x00000000
#define QM_CFG_MEM_PWRDN_DIS_ADDR                               0x0000006c
#define QM_CFG_MEM_PWRDN_DIS_DEFAULT                            0x00000000
#define QM_CFG_MEM_RAM_SHUTDOWN_ADDR                            0x00000070
#define QM_CFG_MEM_RAM_SHUTDOWN_DEFAULT                         0xffffffff
#define QM_BLOCK_MEM_RDY_ADDR                                   0x00000074
#define QM_BLOCK_MEM_RDY_DEFAULT                                0xffffffff
#define QM_STS_READ_LATENCY_TOT_READ_REQS_ADDR                  0x0000008c
#define QM_STS_READ_LATENCY_TOT_READ_REQS_DEFAULT               0x00000000
#define QM_CFG_LT_MSTR_STOP_CNT_ADDR                            0x00000090
#define QM_CFG_LT_MSTR_STOP_CNT_DEFAULT                         0x00040000
#define QM_CFG_BW_SRD_TRIG_CAP_ADDR                             0x000000a0
#define QM_CFG_BW_SRD_TRIG_CAP_DEFAULT                          0x00000000
#define QM_CFG_BW_SWR_TRIG_CAP_ADDR                             0x000000a4
#define QM_CFG_BW_SWR_TRIG_CAP_DEFAULT                          0x00000000
#define QM_CFG_BW_MRD_TRIG_CAP_ADDR                             0x000000a8
#define QM_CFG_BW_MRD_TRIG_CAP_DEFAULT                          0x00000000
#define QM_CFG_BW_MWR_TRIG_CAP_ADDR                             0x000000ac
#define QM_CFG_BW_MWR_TRIG_CAP_DEFAULT                          0x00000000
#define QM_CFG_LT_MRD_TRIG_CAP_ADDR                             0x000000b0
#define QM_CFG_LT_MRD_TRIG_CAP_DEFAULT                          0x00000000
#define QM_DBG_BLOCK_AXI_ADDR                                   0x000000b4
#define QM_DBG_BLOCK_AXI_DEFAULT                                0x00000000
#define QM_DBG_BLOCK_NON_AXI_ADDR                               0x000000b8
#define QM_DBG_BLOCK_NON_AXI_DEFAULT                            0x00000000
#define QM_DBG_AXI_SHIM_OUT_ADDR                                0x000000bc
#define QM_DBG_AXI_SHIM_OUT_DEFAULT                             0x00000000

/*	Register CFG_DIAG_SEL	*/ 
/*	 Fields CFG_SHIM_BLK_DBUS_MUX_SELECT	 */
#define QM_CFG_SHIM_BLK_DBUS_MUX_SELECT_WIDTH                            1
#define QM_CFG_SHIM_BLK_DBUS_MUX_SELECT_SHIFT                           12
#define QM_CFG_SHIM_BLK_DBUS_MUX_SELECT_MASK                    0x00001000
#define QM_CFG_SHIM_BLK_DBUS_MUX_SELECT_RD(src) \
                                                    (((src) & 0x00001000)>>12)
#define QM_CFG_SHIM_BLK_DBUS_MUX_SELECT_WR(src) \
                                                (((u32)(src)<<12) & 0x00001000)
#define QM_CFG_SHIM_BLK_DBUS_MUX_SELECT_SET(dst,src) \
                      (((dst) & ~0x00001000) | (((u32)(src)<<12) & 0x00001000))
/*	 Fields CFG_AXI_NON_AXI_MUX_SELECT	 */
#define QM_CFG_AXI_NON_AXI_MUX_SELECT_WIDTH                              1
#define QM_CFG_AXI_NON_AXI_MUX_SELECT_SHIFT                             11
#define QM_CFG_AXI_NON_AXI_MUX_SELECT_MASK                      0x00000800
#define QM_CFG_AXI_NON_AXI_MUX_SELECT_RD(src)   (((src) & 0x00000800)>>11)
#define QM_CFG_AXI_NON_AXI_MUX_SELECT_WR(src) \
                                                (((u32)(src)<<11) & 0x00000800)
#define QM_CFG_AXI_NON_AXI_MUX_SELECT_SET(dst,src) \
                      (((dst) & ~0x00000800) | (((u32)(src)<<11) & 0x00000800))
/*	 Fields CFG_MUX_SELECTOR	 */
#define QM_CFG_MUX_SELECTOR_WIDTH                                       11
#define QM_CFG_MUX_SELECTOR_SHIFT                                        0
#define QM_CFG_MUX_SELECTOR_MASK                                0x000007ff
#define QM_CFG_MUX_SELECTOR_RD(src)                 (((src) & 0x000007ff))
#define QM_CFG_MUX_SELECTOR_WR(src)            (((u32)(src)) & 0x000007ff)
#define QM_CFG_MUX_SELECTOR_SET(dst,src) \
                          (((dst) & ~0x000007ff) | (((u32)(src)) & 0x000007ff))

/*	Register CFG_READ_BW_LAT_ADDR_MASK	*/ 
/*	 Fields READ_ADDR_MASK	 */
#define QM_READ_ADDR_MASK_WIDTH                                         32
#define QM_READ_ADDR_MASK_SHIFT                                          0
#define QM_READ_ADDR_MASK_MASK                                  0xffffffff
#define QM_READ_ADDR_MASK_RD(src)                   (((src) & 0xffffffff))
#define QM_READ_ADDR_MASK_WR(src)              (((u32)(src)) & 0xffffffff)
#define QM_READ_ADDR_MASK_SET(dst,src) \
                          (((dst) & ~0xffffffff) | (((u32)(src)) & 0xffffffff))

/*	Register CFG_READ_BW_LAT_ADDR_PAT	*/ 
/*	 Fields READ_ADDR_PAT	 */
#define QM_READ_ADDR_PAT_WIDTH                                          32
#define QM_READ_ADDR_PAT_SHIFT                                           0
#define QM_READ_ADDR_PAT_MASK                                   0xffffffff
#define QM_READ_ADDR_PAT_RD(src)                    (((src) & 0xffffffff))
#define QM_READ_ADDR_PAT_WR(src)               (((u32)(src)) & 0xffffffff)
#define QM_READ_ADDR_PAT_SET(dst,src) \
                          (((dst) & ~0xffffffff) | (((u32)(src)) & 0xffffffff))

/*	Register CFG_WRITE_BW_LAT_ADDR_MASK	*/ 
/*	 Fields WRITE_ADDR_MASK	 */
#define QM_WRITE_ADDR_MASK_WIDTH                                        32
#define QM_WRITE_ADDR_MASK_SHIFT                                         0
#define QM_WRITE_ADDR_MASK_MASK                                 0xffffffff
#define QM_WRITE_ADDR_MASK_RD(src)                  (((src) & 0xffffffff))
#define QM_WRITE_ADDR_MASK_WR(src)             (((u32)(src)) & 0xffffffff)
#define QM_WRITE_ADDR_MASK_SET(dst,src) \
                          (((dst) & ~0xffffffff) | (((u32)(src)) & 0xffffffff))

/*	Register CFG_WRITE_BW_LAT_ADDR_PAT	*/ 
/*	 Fields WRITE_ADDR_PAT	 */
#define QM_WRITE_ADDR_PAT_WIDTH                                         32
#define QM_WRITE_ADDR_PAT_SHIFT                                          0
#define QM_WRITE_ADDR_PAT_MASK                                  0xffffffff
#define QM_WRITE_ADDR_PAT_RD(src)                   (((src) & 0xffffffff))
#define QM_WRITE_ADDR_PAT_WR(src)              (((u32)(src)) & 0xffffffff)
#define QM_WRITE_ADDR_PAT_SET(dst,src) \
                          (((dst) & ~0xffffffff) | (((u32)(src)) & 0xffffffff))

/*	Register CFG_DIAG_START_STOP	*/ 
/*	 Fields CTRL_AddCap_MRD_LT	 */
#define QM_CTRL_ADDCAP_MRD_LT_WIDTH                                      1
#define QM_CTRL_ADDCAP_MRD_LT_SHIFT                                      9
#define QM_CTRL_ADDCAP_MRD_LT_MASK                              0x00000200
#define QM_CTRL_ADDCAP_MRD_LT_RD(src)            (((src) & 0x00000200)>>9)
#define QM_CTRL_ADDCAP_MRD_LT_WR(src)       (((u32)(src)<<9) & 0x00000200)
#define QM_CTRL_ADDCAP_MRD_LT_SET(dst,src) \
                       (((dst) & ~0x00000200) | (((u32)(src)<<9) & 0x00000200))
/*	 Fields CTRL_AddCap_SRD_BW	 */
#define QM_CTRL_ADDCAP_SRD_BW_WIDTH                                      1
#define QM_CTRL_ADDCAP_SRD_BW_SHIFT                                      8
#define QM_CTRL_ADDCAP_SRD_BW_MASK                              0x00000100
#define QM_CTRL_ADDCAP_SRD_BW_RD(src)            (((src) & 0x00000100)>>8)
#define QM_CTRL_ADDCAP_SRD_BW_WR(src)       (((u32)(src)<<8) & 0x00000100)
#define QM_CTRL_ADDCAP_SRD_BW_SET(dst,src) \
                       (((dst) & ~0x00000100) | (((u32)(src)<<8) & 0x00000100))
/*	 Fields CTRL_AddCap_MRD_BW	 */
#define QM_CTRL_ADDCAP_MRD_BW_WIDTH                                      1
#define QM_CTRL_ADDCAP_MRD_BW_SHIFT                                      7
#define QM_CTRL_ADDCAP_MRD_BW_MASK                              0x00000080
#define QM_CTRL_ADDCAP_MRD_BW_RD(src)            (((src) & 0x00000080)>>7)
#define QM_CTRL_ADDCAP_MRD_BW_WR(src)       (((u32)(src)<<7) & 0x00000080)
#define QM_CTRL_ADDCAP_MRD_BW_SET(dst,src) \
                       (((dst) & ~0x00000080) | (((u32)(src)<<7) & 0x00000080))
/*	 Fields CTRL_AddCap_SWR_BW	 */
#define QM_CTRL_ADDCAP_SWR_BW_WIDTH                                      1
#define QM_CTRL_ADDCAP_SWR_BW_SHIFT                                      6
#define QM_CTRL_ADDCAP_SWR_BW_MASK                              0x00000040
#define QM_CTRL_ADDCAP_SWR_BW_RD(src)            (((src) & 0x00000040)>>6)
#define QM_CTRL_ADDCAP_SWR_BW_WR(src)       (((u32)(src)<<6) & 0x00000040)
#define QM_CTRL_ADDCAP_SWR_BW_SET(dst,src) \
                       (((dst) & ~0x00000040) | (((u32)(src)<<6) & 0x00000040))
/*	 Fields CTRL_AddCap_MWR_BW	 */
#define QM_CTRL_ADDCAP_MWR_BW_WIDTH                                      1
#define QM_CTRL_ADDCAP_MWR_BW_SHIFT                                      5
#define QM_CTRL_ADDCAP_MWR_BW_MASK                              0x00000020
#define QM_CTRL_ADDCAP_MWR_BW_RD(src)            (((src) & 0x00000020)>>5)
#define QM_CTRL_ADDCAP_MWR_BW_WR(src)       (((u32)(src)<<5) & 0x00000020)
#define QM_CTRL_ADDCAP_MWR_BW_SET(dst,src) \
                       (((dst) & ~0x00000020) | (((u32)(src)<<5) & 0x00000020))
/*	 Fields START_MRD_LT	 */
#define QM_START_MRD_LT_WIDTH                                            1
#define QM_START_MRD_LT_SHIFT                                            4
#define QM_START_MRD_LT_MASK                                    0x00000010
#define QM_START_MRD_LT_RD(src)                  (((src) & 0x00000010)>>4)
#define QM_START_MRD_LT_WR(src)             (((u32)(src)<<4) & 0x00000010)
#define QM_START_MRD_LT_SET(dst,src) \
                       (((dst) & ~0x00000010) | (((u32)(src)<<4) & 0x00000010))
/*	 Fields START_SRD_BW	 */
#define QM_START_SRD_BW_WIDTH                                            1
#define QM_START_SRD_BW_SHIFT                                            3
#define QM_START_SRD_BW_MASK                                    0x00000008
#define QM_START_SRD_BW_RD(src)                  (((src) & 0x00000008)>>3)
#define QM_START_SRD_BW_WR(src)             (((u32)(src)<<3) & 0x00000008)
#define QM_START_SRD_BW_SET(dst,src) \
                       (((dst) & ~0x00000008) | (((u32)(src)<<3) & 0x00000008))
/*	 Fields START_MRD_BW	 */
#define QM_START_MRD_BW_WIDTH                                            1
#define QM_START_MRD_BW_SHIFT                                            2
#define QM_START_MRD_BW_MASK                                    0x00000004
#define QM_START_MRD_BW_RD(src)                  (((src) & 0x00000004)>>2)
#define QM_START_MRD_BW_WR(src)             (((u32)(src)<<2) & 0x00000004)
#define QM_START_MRD_BW_SET(dst,src) \
                       (((dst) & ~0x00000004) | (((u32)(src)<<2) & 0x00000004))
/*	 Fields START_SWR_BW	 */
#define QM_START_SWR_BW_WIDTH                                            1
#define QM_START_SWR_BW_SHIFT                                            1
#define QM_START_SWR_BW_MASK                                    0x00000002
#define QM_START_SWR_BW_RD(src)                  (((src) & 0x00000002)>>1)
#define QM_START_SWR_BW_WR(src)             (((u32)(src)<<1) & 0x00000002)
#define QM_START_SWR_BW_SET(dst,src) \
                       (((dst) & ~0x00000002) | (((u32)(src)<<1) & 0x00000002))
/*	 Fields START_MWR_BW	 */
#define QM_START_MWR_BW_WIDTH                                            1
#define QM_START_MWR_BW_SHIFT                                            0
#define QM_START_MWR_BW_MASK                                    0x00000001
#define QM_START_MWR_BW_RD(src)                     (((src) & 0x00000001))
#define QM_START_MWR_BW_WR(src)                (((u32)(src)) & 0x00000001)
#define QM_START_MWR_BW_SET(dst,src) \
                          (((dst) & ~0x00000001) | (((u32)(src)) & 0x00000001))

/*	Register CFG_BW_MSTR_STOP_CNT	*/ 
/*	 Fields MSTR_STOP_RD_CNT	 */
#define QM_MSTR_STOP_RD_CNT_WIDTH                                       16
#define QM_MSTR_STOP_RD_CNT_SHIFT                                       16
#define QM_MSTR_STOP_RD_CNT_MASK                                0xffff0000
#define QM_MSTR_STOP_RD_CNT_RD(src)             (((src) & 0xffff0000)>>16)
#define QM_MSTR_STOP_RD_CNT_WR(src)        (((u32)(src)<<16) & 0xffff0000)
#define QM_MSTR_STOP_RD_CNT_SET(dst,src) \
                      (((dst) & ~0xffff0000) | (((u32)(src)<<16) & 0xffff0000))
/*	 Fields MSTR_STOP_WR_CNT	 */
#define QM_MSTR_STOP_WR_CNT_WIDTH                                       16
#define QM_MSTR_STOP_WR_CNT_SHIFT                                        0
#define QM_MSTR_STOP_WR_CNT_MASK                                0x0000ffff
#define QM_MSTR_STOP_WR_CNT_RD(src)                 (((src) & 0x0000ffff))
#define QM_MSTR_STOP_WR_CNT_WR(src)            (((u32)(src)) & 0x0000ffff)
#define QM_MSTR_STOP_WR_CNT_SET(dst,src) \
                          (((dst) & ~0x0000ffff) | (((u32)(src)) & 0x0000ffff))

/*	Register CFG_BW_SLV_STOP_CNT	*/ 
/*	 Fields SLV_STOP_RD_CNT	 */
#define QM_SLV_STOP_RD_CNT_WIDTH                                        16
#define QM_SLV_STOP_RD_CNT_SHIFT                                        16
#define QM_SLV_STOP_RD_CNT_MASK                                 0xffff0000
#define QM_SLV_STOP_RD_CNT_RD(src)              (((src) & 0xffff0000)>>16)
#define QM_SLV_STOP_RD_CNT_WR(src)         (((u32)(src)<<16) & 0xffff0000)
#define QM_SLV_STOP_RD_CNT_SET(dst,src) \
                      (((dst) & ~0xffff0000) | (((u32)(src)<<16) & 0xffff0000))
/*	 Fields SLV_STOP_WR_CNT	 */
#define QM_SLV_STOP_WR_CNT_WIDTH                                        16
#define QM_SLV_STOP_WR_CNT_SHIFT                                         0
#define QM_SLV_STOP_WR_CNT_MASK                                 0x0000ffff
#define QM_SLV_STOP_WR_CNT_RD(src)                  (((src) & 0x0000ffff))
#define QM_SLV_STOP_WR_CNT_WR(src)             (((u32)(src)) & 0x0000ffff)
#define QM_SLV_STOP_WR_CNT_SET(dst,src) \
                          (((dst) & ~0x0000ffff) | (((u32)(src)) & 0x0000ffff))

/*	Register STS_READ_LATENCY_OUTPUT	*/ 
/*	 Fields READ_TOT	 */
#define QM_READ_TOT_WIDTH                                               22
#define QM_READ_TOT_SHIFT                                                0
#define QM_READ_TOT_MASK                                        0x003fffff
#define QM_READ_TOT_RD(src)                         (((src) & 0x003fffff))
#define QM_READ_TOT_SET(dst,src) \
                          (((dst) & ~0x003fffff) | (((u32)(src)) & 0x003fffff))

/*	Register STS_AXI_MRD_BW_CLK_CNT	*/ 
/*	 Fields MSTR_READ_BW_CLK_CNT	 */
#define QM_MSTR_READ_BW_CLK_CNT_WIDTH                                   32
#define QM_MSTR_READ_BW_CLK_CNT_SHIFT                                    0
#define QM_MSTR_READ_BW_CLK_CNT_MASK                            0xffffffff
#define QM_MSTR_READ_BW_CLK_CNT_RD(src)             (((src) & 0xffffffff))
#define QM_MSTR_READ_BW_CLK_CNT_SET(dst,src) \
                          (((dst) & ~0xffffffff) | (((u32)(src)) & 0xffffffff))

/*	Register STS_AXI_MRD_BW_BYTE_CNT	*/ 
/*	 Fields MSTR_READ_BW_BYTE_CNT	 */
#define QM_MSTR_READ_BW_BYTE_CNT_WIDTH                                  32
#define QM_MSTR_READ_BW_BYTE_CNT_SHIFT                                   0
#define QM_MSTR_READ_BW_BYTE_CNT_MASK                           0xffffffff
#define QM_MSTR_READ_BW_BYTE_CNT_RD(src)            (((src) & 0xffffffff))
#define QM_MSTR_READ_BW_BYTE_CNT_SET(dst,src) \
                          (((dst) & ~0xffffffff) | (((u32)(src)) & 0xffffffff))

/*	Register STS_AXI_MWR_BW_CLK_CNT	*/ 
/*	 Fields MSTR_WRITE_BW_CLK_CNT	 */
#define QM_MSTR_WRITE_BW_CLK_CNT_WIDTH                                  32
#define QM_MSTR_WRITE_BW_CLK_CNT_SHIFT                                   0
#define QM_MSTR_WRITE_BW_CLK_CNT_MASK                           0xffffffff
#define QM_MSTR_WRITE_BW_CLK_CNT_RD(src)            (((src) & 0xffffffff))
#define QM_MSTR_WRITE_BW_CLK_CNT_SET(dst,src) \
                          (((dst) & ~0xffffffff) | (((u32)(src)) & 0xffffffff))

/*	Register STS_AXI_MWR_BW_BYTE_CNT	*/ 
/*	 Fields MSTR_WRITE_BW_BYTE_CNT	 */
#define QM_MSTR_WRITE_BW_BYTE_CNT_WIDTH                                 32
#define QM_MSTR_WRITE_BW_BYTE_CNT_SHIFT                                  0
#define QM_MSTR_WRITE_BW_BYTE_CNT_MASK                          0xffffffff
#define QM_MSTR_WRITE_BW_BYTE_CNT_RD(src)           (((src) & 0xffffffff))
#define QM_MSTR_WRITE_BW_BYTE_CNT_SET(dst,src) \
                          (((dst) & ~0xffffffff) | (((u32)(src)) & 0xffffffff))

/*	Register STS_AXI_SRD_BW_CLK_CNT	*/ 
/*	 Fields SLV_READ_BW_CLK_CNT	 */
#define QM_SLV_READ_BW_CLK_CNT_WIDTH                                    32
#define QM_SLV_READ_BW_CLK_CNT_SHIFT                                     0
#define QM_SLV_READ_BW_CLK_CNT_MASK                             0xffffffff
#define QM_SLV_READ_BW_CLK_CNT_RD(src)              (((src) & 0xffffffff))
#define QM_SLV_READ_BW_CLK_CNT_SET(dst,src) \
                          (((dst) & ~0xffffffff) | (((u32)(src)) & 0xffffffff))

/*	Register STS_AXI_SRD_BW_BYTE_CNT	*/ 
/*	 Fields SLV_READ_BW_BYTE_CNT	 */
#define QM_SLV_READ_BW_BYTE_CNT_WIDTH                                   32
#define QM_SLV_READ_BW_BYTE_CNT_SHIFT                                    0
#define QM_SLV_READ_BW_BYTE_CNT_MASK                            0xffffffff
#define QM_SLV_READ_BW_BYTE_CNT_RD(src)             (((src) & 0xffffffff))
#define QM_SLV_READ_BW_BYTE_CNT_SET(dst,src) \
                          (((dst) & ~0xffffffff) | (((u32)(src)) & 0xffffffff))

/*	Register STS_AXI_SWR_BW_CLK_CNT	*/ 
/*	 Fields SLV_WRITE_BW_CLK_CNT	 */
#define QM_SLV_WRITE_BW_CLK_CNT_WIDTH                                   32
#define QM_SLV_WRITE_BW_CLK_CNT_SHIFT                                    0
#define QM_SLV_WRITE_BW_CLK_CNT_MASK                            0xffffffff
#define QM_SLV_WRITE_BW_CLK_CNT_RD(src)             (((src) & 0xffffffff))
#define QM_SLV_WRITE_BW_CLK_CNT_SET(dst,src) \
                          (((dst) & ~0xffffffff) | (((u32)(src)) & 0xffffffff))

/*	Register STS_AXI_SWR_BW_BYTE_CNT	*/ 
/*	 Fields SLV_WRITE_BW_BYTE_CNT	 */
#define QM_SLV_WRITE_BW_BYTE_CNT_WIDTH                                  32
#define QM_SLV_WRITE_BW_BYTE_CNT_SHIFT                                   0
#define QM_SLV_WRITE_BW_BYTE_CNT_MASK                           0xffffffff
#define QM_SLV_WRITE_BW_BYTE_CNT_RD(src)            (((src) & 0xffffffff))
#define QM_SLV_WRITE_BW_BYTE_CNT_SET(dst,src) \
                          (((dst) & ~0xffffffff) | (((u32)(src)) & 0xffffffff))

/*	Register CFG_DBG_TRIG_CTRL	*/ 
/*	 Fields TRIG_EN_OUT_CTRL	 */
#define QM_TRIG_EN_OUT_CTRL_WIDTH                                        1
#define QM_TRIG_EN_OUT_CTRL_SHIFT                                        5
#define QM_TRIG_EN_OUT_CTRL_MASK                                0x00000020
#define QM_TRIG_EN_OUT_CTRL_RD(src)              (((src) & 0x00000020)>>5)
#define QM_TRIG_EN_OUT_CTRL_WR(src)         (((u32)(src)<<5) & 0x00000020)
#define QM_TRIG_EN_OUT_CTRL_SET(dst,src) \
                       (((dst) & ~0x00000020) | (((u32)(src)<<5) & 0x00000020))
/*	 Fields TRIG_EN	 */
#define QM_TRIG_EN_WIDTH                                                 1
#define QM_TRIG_EN_SHIFT                                                 4
#define QM_TRIG_EN_MASK                                         0x00000010
#define QM_TRIG_EN_RD(src)                       (((src) & 0x00000010)>>4)
#define QM_TRIG_EN_WR(src)                  (((u32)(src)<<4) & 0x00000010)
#define QM_TRIG_EN_SET(dst,src) \
                       (((dst) & ~0x00000010) | (((u32)(src)<<4) & 0x00000010))
/*	 Fields AND_E	 */
#define QM_AND_E_WIDTH                                                   2
#define QM_AND_E_SHIFT                                                   2
#define QM_AND_E_MASK                                           0x0000000c
#define QM_AND_E_RD(src)                         (((src) & 0x0000000c)>>2)
#define QM_AND_E_WR(src)                    (((u32)(src)<<2) & 0x0000000c)
#define QM_AND_E_SET(dst,src) \
                       (((dst) & ~0x0000000c) | (((u32)(src)<<2) & 0x0000000c))
/*	 Fields OR_E	 */
#define QM_OR_E_WIDTH                                                    2
#define QM_OR_E_SHIFT                                                    0
#define QM_OR_E_MASK                                            0x00000003
#define QM_OR_E_RD(src)                             (((src) & 0x00000003))
#define QM_OR_E_WR(src)                        (((u32)(src)) & 0x00000003)
#define QM_OR_E_SET(dst,src) \
                          (((dst) & ~0x00000003) | (((u32)(src)) & 0x00000003))

/*	Register CFG_DBG_PAT_REG_0	*/ 
/*	 Fields PATTERN	 */
#define QM_PATTERN0_WIDTH                                               32
#define QM_PATTERN0_SHIFT                                                0
#define QM_PATTERN0_MASK                                        0xffffffff
#define QM_PATTERN0_RD(src)                         (((src) & 0xffffffff))
#define QM_PATTERN0_WR(src)                    (((u32)(src)) & 0xffffffff)
#define QM_PATTERN0_SET(dst,src) \
                          (((dst) & ~0xffffffff) | (((u32)(src)) & 0xffffffff))

/*	Register CFG_DBG_PAT_MASK_REG_0	*/ 
/*	 Fields PAT_MASK	 */
#define QM_PAT_MASK0_WIDTH                                              32
#define QM_PAT_MASK0_SHIFT                                               0
#define QM_PAT_MASK0_MASK                                       0xffffffff
#define QM_PAT_MASK0_RD(src)                        (((src) & 0xffffffff))
#define QM_PAT_MASK0_WR(src)                   (((u32)(src)) & 0xffffffff)
#define QM_PAT_MASK0_SET(dst,src) \
                          (((dst) & ~0xffffffff) | (((u32)(src)) & 0xffffffff))

/*	Register CFG_DBG_PAT_REG_1	*/ 
/*	 Fields PATTERN	 */
#define QM_PATTERN1_WIDTH                                               32
#define QM_PATTERN1_SHIFT                                                0
#define QM_PATTERN1_MASK                                        0xffffffff
#define QM_PATTERN1_RD(src)                         (((src) & 0xffffffff))
#define QM_PATTERN1_WR(src)                    (((u32)(src)) & 0xffffffff)
#define QM_PATTERN1_SET(dst,src) \
                          (((dst) & ~0xffffffff) | (((u32)(src)) & 0xffffffff))

/*	Register CFG_DBG_PAT_MASK_REG_1	*/ 
/*	 Fields PAT_MASK	 */
#define QM_PAT_MASK1_WIDTH                                              32
#define QM_PAT_MASK1_SHIFT                                               0
#define QM_PAT_MASK1_MASK                                       0xffffffff
#define QM_PAT_MASK1_RD(src)                        (((src) & 0xffffffff))
#define QM_PAT_MASK1_WR(src)                   (((u32)(src)) & 0xffffffff)
#define QM_PAT_MASK1_SET(dst,src) \
                          (((dst) & ~0xffffffff) | (((u32)(src)) & 0xffffffff))

/*	Register DBG_TRIG_OUT	*/ 
/*	 Fields DBG_OUT	 */
#define QM_DBG_OUT_WIDTH                                                32
#define QM_DBG_OUT_SHIFT                                                 0
#define QM_DBG_OUT_MASK                                         0xffffffff
#define QM_DBG_OUT_RD(src)                          (((src) & 0xffffffff))
#define QM_DBG_OUT_SET(dst,src) \
                          (((dst) & ~0xffffffff) | (((u32)(src)) & 0xffffffff))

/*	Register DBG_TRIG_INT	*/ 
/*	 Fields DBG_INT	 */
#define QM_DBG_INT_WIDTH                                                 1
#define QM_DBG_INT_SHIFT                                                 0
#define QM_DBG_INT_MASK                                         0x00000001
#define QM_DBG_INT_RD(src)                          (((src) & 0x00000001))
#define QM_DBG_INT_WR(src)                     (((u32)(src)) & 0x00000001)
#define QM_DBG_INT_SET(dst,src) \
                          (((dst) & ~0x00000001) | (((u32)(src)) & 0x00000001))

/*	Register DBG_TRIG_INTMask	*/
/*    Mask Register Fields DBG_INTMask    */
#define QM_DBG_INTMASK_WIDTH                                             1
#define QM_DBG_INTMASK_SHIFT                                             0
#define QM_DBG_INTMASK_MASK                                     0x00000001
#define QM_DBG_INTMASK_RD(src)                      (((src) & 0x00000001))
#define QM_DBG_INTMASK_WR(src)                 (((u32)(src)) & 0x00000001)
#define QM_DBG_INTMASK_SET(dst,src) \
                          (((dst) & ~0x00000001) | (((u32)(src)) & 0x00000001))

/*	Register INTR_STS	*/ 
/*	 Fields DIAGMOD_INT	 */
#define QM_DIAGMOD_INT_WIDTH                                             1
#define QM_DIAGMOD_INT_SHIFT                                             1
#define QM_DIAGMOD_INT_MASK                                     0x00000002
#define QM_DIAGMOD_INT_RD(src)                   (((src) & 0x00000002)>>1)
#define QM_DIAGMOD_INT_SET(dst,src) \
                       (((dst) & ~0x00000002) | (((u32)(src)<<1) & 0x00000002))
/*	 Fields ERRMOD_INT	 */
#define QM_ERRMOD_INT_WIDTH                                              1
#define QM_ERRMOD_INT_SHIFT                                              0
#define QM_ERRMOD_INT_MASK                                      0x00000001
#define QM_ERRMOD_INT_RD(src)                       (((src) & 0x00000001))
#define QM_ERRMOD_INT_SET(dst,src) \
                          (((dst) & ~0x00000001) | (((u32)(src)) & 0x00000001))

/*	Register CFG_MEM_ECC_BYPASS	*/ 
/*	 Fields CFG_ECC_BYPASS	 */
#define QM_CFG_ECC_BYPASS_WIDTH                                         16
#define QM_CFG_ECC_BYPASS_SHIFT                                          0
#define QM_CFG_ECC_BYPASS_MASK                                  0x0000ffff
#define QM_CFG_ECC_BYPASS_RD(src)                   (((src) & 0x0000ffff))
#define QM_CFG_ECC_BYPASS_WR(src)              (((u32)(src)) & 0x0000ffff)
#define QM_CFG_ECC_BYPASS_SET(dst,src) \
                          (((dst) & ~0x0000ffff) | (((u32)(src)) & 0x0000ffff))

/*	Register CFG_MEM_PWRDN_DIS	*/ 
/*	 Fields CFG_ECC_PWRDN_DIS	 */
#define QM_CFG_ECC_PWRDN_DIS_WIDTH                                      16
#define QM_CFG_ECC_PWRDN_DIS_SHIFT                                      16
#define QM_CFG_ECC_PWRDN_DIS_MASK                               0xffff0000
#define QM_CFG_ECC_PWRDN_DIS_RD(src)            (((src) & 0xffff0000)>>16)
#define QM_CFG_ECC_PWRDN_DIS_WR(src)       (((u32)(src)<<16) & 0xffff0000)
#define QM_CFG_ECC_PWRDN_DIS_SET(dst,src) \
                      (((dst) & ~0xffff0000) | (((u32)(src)<<16) & 0xffff0000))
/*	 Fields CFG_PWRDN_DIS	 */
#define QM_CFG_PWRDN_DIS_WIDTH                                          16
#define QM_CFG_PWRDN_DIS_SHIFT                                           0
#define QM_CFG_PWRDN_DIS_MASK                                   0x0000ffff
#define QM_CFG_PWRDN_DIS_RD(src)                    (((src) & 0x0000ffff))
#define QM_CFG_PWRDN_DIS_WR(src)               (((u32)(src)) & 0x0000ffff)
#define QM_CFG_PWRDN_DIS_SET(dst,src) \
                          (((dst) & ~0x0000ffff) | (((u32)(src)) & 0x0000ffff))

/*	Register CFG_MEM_RAM_SHUTDOWN	*/ 
/*	 Fields CFG_RAM_SHUTDOWN_EN	 */
#define QM_CFG_RAM_SHUTDOWN_EN_WIDTH                                    32
#define QM_CFG_RAM_SHUTDOWN_EN_SHIFT                                     0
#define QM_CFG_RAM_SHUTDOWN_EN_MASK                             0xffffffff
#define QM_CFG_RAM_SHUTDOWN_EN_RD(src)              (((src) & 0xffffffff))
#define QM_CFG_RAM_SHUTDOWN_EN_WR(src)         (((u32)(src)) & 0xffffffff)
#define QM_CFG_RAM_SHUTDOWN_EN_SET(dst,src) \
                          (((dst) & ~0xffffffff) | (((u32)(src)) & 0xffffffff))

/*	Register BLOCK_MEM_RDY	*/ 
/*	 Fields MEM_RDY	 */
#define QM_MEM_RDY_WIDTH                                                32
#define QM_MEM_RDY_SHIFT                                                 0
#define QM_MEM_RDY_MASK                                         0xffffffff
#define QM_MEM_RDY_RD(src)                          (((src) & 0xffffffff))
#define QM_MEM_RDY_SET(dst,src) \
                          (((dst) & ~0xffffffff) | (((u32)(src)) & 0xffffffff))

/*	Register STS_READ_LATENCY_TOT_READ_REQS	*/ 
/*	 Fields TOT_READS	 */
#define QM_TOT_READS_WIDTH                                              16
#define QM_TOT_READS_SHIFT                                              16
#define QM_TOT_READS_MASK                                       0xffff0000
#define QM_TOT_READS_RD(src)                    (((src) & 0xffff0000)>>16)
#define QM_TOT_READS_SET(dst,src) \
                      (((dst) & ~0xffff0000) | (((u32)(src)<<16) & 0xffff0000))

/*	Register CFG_LT_MSTR_STOP_CNT	*/ 
/*	 Fields MSTR_LT_STOP_CNT	 */
#define QM_MSTR_LT_STOP_CNT_WIDTH                                       16
#define QM_MSTR_LT_STOP_CNT_SHIFT                                       16
#define QM_MSTR_LT_STOP_CNT_MASK                                0xffff0000
#define QM_MSTR_LT_STOP_CNT_RD(src)             (((src) & 0xffff0000)>>16)
#define QM_MSTR_LT_STOP_CNT_WR(src)        (((u32)(src)<<16) & 0xffff0000)
#define QM_MSTR_LT_STOP_CNT_SET(dst,src) \
                      (((dst) & ~0xffff0000) | (((u32)(src)<<16) & 0xffff0000))

/*	Register CFG_BW_SRD_TRIG_CAP	*/ 
/*	 Fields CAP_ADD_BWSRD	 */
#define QM_CAP_ADD_BWSRD_WIDTH                                          32
#define QM_CAP_ADD_BWSRD_SHIFT                                           0
#define QM_CAP_ADD_BWSRD_MASK                                   0xffffffff
#define QM_CAP_ADD_BWSRD_RD(src)                    (((src) & 0xffffffff))
#define QM_CAP_ADD_BWSRD_SET(dst,src) \
                          (((dst) & ~0xffffffff) | (((u32)(src)) & 0xffffffff))

/*	Register CFG_BW_SWR_TRIG_CAP	*/ 
/*	 Fields CAP_ADD_BWSWR	 */
#define QM_CAP_ADD_BWSWR_WIDTH                                          32
#define QM_CAP_ADD_BWSWR_SHIFT                                           0
#define QM_CAP_ADD_BWSWR_MASK                                   0xffffffff
#define QM_CAP_ADD_BWSWR_RD(src)                    (((src) & 0xffffffff))
#define QM_CAP_ADD_BWSWR_SET(dst,src) \
                          (((dst) & ~0xffffffff) | (((u32)(src)) & 0xffffffff))

/*	Register CFG_BW_MRD_TRIG_CAP	*/ 
/*	 Fields CAP_ADD_BWMRD	 */
#define QM_CAP_ADD_BWMRD_WIDTH                                          32
#define QM_CAP_ADD_BWMRD_SHIFT                                           0
#define QM_CAP_ADD_BWMRD_MASK                                   0xffffffff
#define QM_CAP_ADD_BWMRD_RD(src)                    (((src) & 0xffffffff))
#define QM_CAP_ADD_BWMRD_SET(dst,src) \
                          (((dst) & ~0xffffffff) | (((u32)(src)) & 0xffffffff))

/*	Register CFG_BW_MWR_TRIG_CAP	*/ 
/*	 Fields CAP_ADD_BWMWR	 */
#define QM_CAP_ADD_BWMWR_WIDTH                                          32
#define QM_CAP_ADD_BWMWR_SHIFT                                           0
#define QM_CAP_ADD_BWMWR_MASK                                   0xffffffff
#define QM_CAP_ADD_BWMWR_RD(src)                    (((src) & 0xffffffff))
#define QM_CAP_ADD_BWMWR_SET(dst,src) \
                          (((dst) & ~0xffffffff) | (((u32)(src)) & 0xffffffff))

/*	Register CFG_LT_MRD_TRIG_CAP	*/ 
/*	 Fields CAP_ADD_LTMRD	 */
#define QM_CAP_ADD_LTMRD_WIDTH                                          32
#define QM_CAP_ADD_LTMRD_SHIFT                                           0
#define QM_CAP_ADD_LTMRD_MASK                                   0xffffffff
#define QM_CAP_ADD_LTMRD_RD(src)                    (((src) & 0xffffffff))
#define QM_CAP_ADD_LTMRD_SET(dst,src) \
                          (((dst) & ~0xffffffff) | (((u32)(src)) & 0xffffffff))

/*	Register DBG_BLOCK_AXI	*/ 
/*	 Fields DBG_BUS_BLOCK_AXI	 */
#define QM_DBG_BUS_BLOCK_AXI_WIDTH                                      32
#define QM_DBG_BUS_BLOCK_AXI_SHIFT                                       0
#define QM_DBG_BUS_BLOCK_AXI_MASK                               0xffffffff
#define QM_DBG_BUS_BLOCK_AXI_RD(src)                (((src) & 0xffffffff))
#define QM_DBG_BUS_BLOCK_AXI_SET(dst,src) \
                          (((dst) & ~0xffffffff) | (((u32)(src)) & 0xffffffff))

/*	Register DBG_BLOCK_NON_AXI	*/ 
/*	 Fields DBG_BUS_BLOCK_NON_AXI	 */
#define QM_DBG_BUS_BLOCK_NON_AXI_WIDTH                                  32
#define QM_DBG_BUS_BLOCK_NON_AXI_SHIFT                                   0
#define QM_DBG_BUS_BLOCK_NON_AXI_MASK                           0xffffffff
#define QM_DBG_BUS_BLOCK_NON_AXI_RD(src)            (((src) & 0xffffffff))
#define QM_DBG_BUS_BLOCK_NON_AXI_SET(dst,src) \
                          (((dst) & ~0xffffffff) | (((u32)(src)) & 0xffffffff))

/*	Register DBG_AXI_SHIM_OUT	*/ 
/*	 Fields DBG_BUS_SHIM	 */
#define QM_DBG_BUS_SHIM_WIDTH                                           32
#define QM_DBG_BUS_SHIM_SHIFT                                            0
#define QM_DBG_BUS_SHIM_MASK                                    0xffffffff
#define QM_DBG_BUS_SHIM_RD(src)                     (((src) & 0xffffffff))
#define QM_DBG_BUS_SHIM_SET(dst,src) \
                          (((dst) & ~0xffffffff) | (((u32)(src)) & 0xffffffff))

/*	Global Base Address	*/
#define GLBL_ERR_CSR_BASE_ADDR			0x01f20d800ULL
#define GLBL_ERR_CSR_BASE_ADDR_OFFSET			0xd800

/*    Address GLBL_ERR_CSR  Registers */
#define GLBL_ERR_STS_ADDR                                            0x00000800
#define GLBL_ERR_STS_DEFAULT                                         0x00000000
#define GLBL_SEC_ERRL_ADDR                                           0x00000810
#define GLBL_SEC_ERRL_DEFAULT                                        0x00000000
#define GLBL_SEC_ERRLMASK_ADDR                                       0x00000814
#define GLBL_SEC_ERRH_ADDR                                           0x00000818
#define GLBL_SEC_ERRH_DEFAULT                                        0x00000000
#define GLBL_SEC_ERRHMASK_ADDR                                       0x0000081c
#define GLBL_MSEC_ERRL_ADDR                                          0x00000820
#define GLBL_MSEC_ERRL_DEFAULT                                       0x00000000
#define GLBL_MSEC_ERRLMASK_ADDR                                      0x00000824
#define GLBL_MSEC_ERRH_ADDR                                          0x00000828
#define GLBL_MSEC_ERRH_DEFAULT                                       0x00000000
#define GLBL_MSEC_ERRHMASK_ADDR                                      0x0000082c
#define GLBL_DED_ERRL_ADDR                                           0x00000830
#define GLBL_DED_ERRL_DEFAULT                                        0x00000000
#define GLBL_DED_ERRLMASK_ADDR                                       0x00000834
#define GLBL_DED_ERRH_ADDR                                           0x00000838
#define GLBL_DED_ERRH_DEFAULT                                        0x00000000
#define GLBL_DED_ERRHMASK_ADDR                                       0x0000083c
#define GLBL_MDED_ERRL_ADDR                                          0x00000840
#define GLBL_MDED_ERRL_DEFAULT                                       0x00000000
#define GLBL_MDED_ERRLMASK_ADDR                                      0x00000844
#define GLBL_MDED_ERRH_ADDR                                          0x00000848
#define GLBL_MDED_ERRH_DEFAULT                                       0x00000000
#define GLBL_MDED_ERRHMASK_ADDR                                      0x0000084c
#define GLBL_MERR_ADDR_ADDR                                          0x00000850
#define GLBL_MERR_ADDR_DEFAULT                                       0x00000000
#define GLBL_MERR_REQINFO_ADDR                                       0x00000854
#define GLBL_MERR_REQINFO_DEFAULT                                    0x00000000
#define GLBL_TRANS_ERR_ADDR                                          0x00000860
#define GLBL_TRANS_ERR_DEFAULT                                       0x00000000
#define GLBL_TRANS_ERRMASK_ADDR                                      0x00000864
#define GLBL_WDERR_ADDR_ADDR                                         0x00000870
#define GLBL_WDERR_ADDR_DEFAULT                                      0x00000000
#define GLBL_WDERR_REQINFO_ADDR                                      0x00000874
#define GLBL_WDERR_REQINFO_DEFAULT                                   0x00000000
#define GLBL_DEVERR_ADDR_ADDR                                        0x00000878
#define GLBL_DEVERR_ADDR_DEFAULT                                     0x00000000
#define GLBL_DEVERR_REQINFO_ADDR                                     0x0000087c
#define GLBL_DEVERR_REQINFO_DEFAULT                                  0x00000000
#define GLBL_SEC_ERRL_ALS_ADDR                                       0x00000880
#define GLBL_SEC_ERRL_ALS_DEFAULT                                    0x00000000
#define GLBL_SEC_ERRH_ALS_ADDR                                       0x00000884
#define GLBL_SEC_ERRH_ALS_DEFAULT                                    0x00000000
#define GLBL_DED_ERRL_ALS_ADDR                                       0x00000888
#define GLBL_DED_ERRL_ALS_DEFAULT                                    0x00000000
#define GLBL_DED_ERRH_ALS_ADDR                                       0x0000088c
#define GLBL_DED_ERRH_ALS_DEFAULT                                    0x00000000
#define GLBL_TRANS_ERR_ALS_ADDR                                      0x00000890
#define GLBL_TRANS_ERR_ALS_DEFAULT                                   0x00000000

/*	Register GLBL_ERR_STS	*/ 
/*	 Fields SHIM_ERR	 */
#define SHIM_ERR_WIDTH                                                        1
#define SHIM_ERR_SHIFT                                                        5
#define SHIM_ERR_MASK                                                0x00000020
#define SHIM_ERR_RD(src)                              (((src) & 0x00000020)>>5)
#define SHIM_ERR_SET(dst,src) \
                       (((dst) & ~0x00000020) | (((u32)(src)<<5) & 0x00000020))
/*	 Fields TRANS_ERR	 */
#define TRANS_ERR_WIDTH                                                       1
#define TRANS_ERR_SHIFT                                                       4
#define TRANS_ERR_MASK                                               0x00000010
#define TRANS_ERR_RD(src)                             (((src) & 0x00000010)>>4)
#define TRANS_ERR_SET(dst,src) \
                       (((dst) & ~0x00000010) | (((u32)(src)<<4) & 0x00000010))
/*	 Fields MDED_ERR	 */
#define MDED_ERR_WIDTH                                                        1
#define MDED_ERR_SHIFT                                                        3
#define MDED_ERR_MASK                                                0x00000008
#define MDED_ERR_RD(src)                              (((src) & 0x00000008)>>3)
#define MDED_ERR_SET(dst,src) \
                       (((dst) & ~0x00000008) | (((u32)(src)<<3) & 0x00000008))
/*	 Fields DED_ERR	 */
#define DED_ERR_WIDTH                                                         1
#define DED_ERR_SHIFT                                                         2
#define DED_ERR_MASK                                                 0x00000004
#define DED_ERR_RD(src)                               (((src) & 0x00000004)>>2)
#define DED_ERR_SET(dst,src) \
                       (((dst) & ~0x00000004) | (((u32)(src)<<2) & 0x00000004))
/*	 Fields MSEC_ERR	 */
#define MSEC_ERR_WIDTH                                                        1
#define MSEC_ERR_SHIFT                                                        1
#define MSEC_ERR_MASK                                                0x00000002
#define MSEC_ERR_RD(src)                              (((src) & 0x00000002)>>1)
#define MSEC_ERR_SET(dst,src) \
                       (((dst) & ~0x00000002) | (((u32)(src)<<1) & 0x00000002))
/*	 Fields SEC_ERR	 */
#define SEC_ERR_WIDTH                                                         1
#define SEC_ERR_SHIFT                                                         0
#define SEC_ERR_MASK                                                 0x00000001
#define SEC_ERR_RD(src)                                  (((src) & 0x00000001))
#define SEC_ERR_SET(dst,src) \
                          (((dst) & ~0x00000001) | (((u32)(src)) & 0x00000001))

/*	Register GLBL_SEC_ERRL	*/ 
/*	 Fields SEC31	 */
#define SEC31_WIDTH                                                           1
#define SEC31_SHIFT                                                          31
#define SEC31_MASK                                                   0x80000000
#define SEC31_RD(src)                                (((src) & 0x80000000)>>31)
#define SEC31_WR(src)                           (((u32)(src)<<31) & 0x80000000)
#define SEC31_SET(dst,src) \
                      (((dst) & ~0x80000000) | (((u32)(src)<<31) & 0x80000000))
/*	 Fields SEC30	 */
#define SEC30_WIDTH                                                           1
#define SEC30_SHIFT                                                          30
#define SEC30_MASK                                                   0x40000000
#define SEC30_RD(src)                                (((src) & 0x40000000)>>30)
#define SEC30_WR(src)                           (((u32)(src)<<30) & 0x40000000)
#define SEC30_SET(dst,src) \
                      (((dst) & ~0x40000000) | (((u32)(src)<<30) & 0x40000000))
/*	 Fields SEC29	 */
#define SEC29_WIDTH                                                           1
#define SEC29_SHIFT                                                          29
#define SEC29_MASK                                                   0x20000000
#define SEC29_RD(src)                                (((src) & 0x20000000)>>29)
#define SEC29_WR(src)                           (((u32)(src)<<29) & 0x20000000)
#define SEC29_SET(dst,src) \
                      (((dst) & ~0x20000000) | (((u32)(src)<<29) & 0x20000000))
/*	 Fields SEC28	 */
#define SEC28_WIDTH                                                           1
#define SEC28_SHIFT                                                          28
#define SEC28_MASK                                                   0x10000000
#define SEC28_RD(src)                                (((src) & 0x10000000)>>28)
#define SEC28_WR(src)                           (((u32)(src)<<28) & 0x10000000)
#define SEC28_SET(dst,src) \
                      (((dst) & ~0x10000000) | (((u32)(src)<<28) & 0x10000000))
/*	 Fields SEC27	 */
#define SEC27_WIDTH                                                           1
#define SEC27_SHIFT                                                          27
#define SEC27_MASK                                                   0x08000000
#define SEC27_RD(src)                                (((src) & 0x08000000)>>27)
#define SEC27_WR(src)                           (((u32)(src)<<27) & 0x08000000)
#define SEC27_SET(dst,src) \
                      (((dst) & ~0x08000000) | (((u32)(src)<<27) & 0x08000000))
/*	 Fields SEC26	 */
#define SEC26_WIDTH                                                           1
#define SEC26_SHIFT                                                          26
#define SEC26_MASK                                                   0x04000000
#define SEC26_RD(src)                                (((src) & 0x04000000)>>26)
#define SEC26_WR(src)                           (((u32)(src)<<26) & 0x04000000)
#define SEC26_SET(dst,src) \
                      (((dst) & ~0x04000000) | (((u32)(src)<<26) & 0x04000000))
/*	 Fields SEC25	 */
#define SEC25_WIDTH                                                           1
#define SEC25_SHIFT                                                          25
#define SEC25_MASK                                                   0x02000000
#define SEC25_RD(src)                                (((src) & 0x02000000)>>25)
#define SEC25_WR(src)                           (((u32)(src)<<25) & 0x02000000)
#define SEC25_SET(dst,src) \
                      (((dst) & ~0x02000000) | (((u32)(src)<<25) & 0x02000000))
/*	 Fields SEC24	 */
#define SEC24_WIDTH                                                           1
#define SEC24_SHIFT                                                          24
#define SEC24_MASK                                                   0x01000000
#define SEC24_RD(src)                                (((src) & 0x01000000)>>24)
#define SEC24_WR(src)                           (((u32)(src)<<24) & 0x01000000)
#define SEC24_SET(dst,src) \
                      (((dst) & ~0x01000000) | (((u32)(src)<<24) & 0x01000000))
/*	 Fields SEC23	 */
#define SEC23_WIDTH                                                           1
#define SEC23_SHIFT                                                          23
#define SEC23_MASK                                                   0x00800000
#define SEC23_RD(src)                                (((src) & 0x00800000)>>23)
#define SEC23_WR(src)                           (((u32)(src)<<23) & 0x00800000)
#define SEC23_SET(dst,src) \
                      (((dst) & ~0x00800000) | (((u32)(src)<<23) & 0x00800000))
/*	 Fields SEC22	 */
#define SEC22_WIDTH                                                           1
#define SEC22_SHIFT                                                          22
#define SEC22_MASK                                                   0x00400000
#define SEC22_RD(src)                                (((src) & 0x00400000)>>22)
#define SEC22_WR(src)                           (((u32)(src)<<22) & 0x00400000)
#define SEC22_SET(dst,src) \
                      (((dst) & ~0x00400000) | (((u32)(src)<<22) & 0x00400000))
/*	 Fields SEC21	 */
#define SEC21_WIDTH                                                           1
#define SEC21_SHIFT                                                          21
#define SEC21_MASK                                                   0x00200000
#define SEC21_RD(src)                                (((src) & 0x00200000)>>21)
#define SEC21_WR(src)                           (((u32)(src)<<21) & 0x00200000)
#define SEC21_SET(dst,src) \
                      (((dst) & ~0x00200000) | (((u32)(src)<<21) & 0x00200000))
/*	 Fields SEC20	 */
#define SEC20_WIDTH                                                           1
#define SEC20_SHIFT                                                          20
#define SEC20_MASK                                                   0x00100000
#define SEC20_RD(src)                                (((src) & 0x00100000)>>20)
#define SEC20_WR(src)                           (((u32)(src)<<20) & 0x00100000)
#define SEC20_SET(dst,src) \
                      (((dst) & ~0x00100000) | (((u32)(src)<<20) & 0x00100000))
/*	 Fields SEC19	 */
#define SEC19_WIDTH                                                           1
#define SEC19_SHIFT                                                          19
#define SEC19_MASK                                                   0x00080000
#define SEC19_RD(src)                                (((src) & 0x00080000)>>19)
#define SEC19_WR(src)                           (((u32)(src)<<19) & 0x00080000)
#define SEC19_SET(dst,src) \
                      (((dst) & ~0x00080000) | (((u32)(src)<<19) & 0x00080000))
/*	 Fields SEC18	 */
#define SEC18_WIDTH                                                           1
#define SEC18_SHIFT                                                          18
#define SEC18_MASK                                                   0x00040000
#define SEC18_RD(src)                                (((src) & 0x00040000)>>18)
#define SEC18_WR(src)                           (((u32)(src)<<18) & 0x00040000)
#define SEC18_SET(dst,src) \
                      (((dst) & ~0x00040000) | (((u32)(src)<<18) & 0x00040000))
/*	 Fields SEC17	 */
#define SEC17_WIDTH                                                           1
#define SEC17_SHIFT                                                          17
#define SEC17_MASK                                                   0x00020000
#define SEC17_RD(src)                                (((src) & 0x00020000)>>17)
#define SEC17_WR(src)                           (((u32)(src)<<17) & 0x00020000)
#define SEC17_SET(dst,src) \
                      (((dst) & ~0x00020000) | (((u32)(src)<<17) & 0x00020000))
/*	 Fields SEC16	 */
#define SEC16_WIDTH                                                           1
#define SEC16_SHIFT                                                          16
#define SEC16_MASK                                                   0x00010000
#define SEC16_RD(src)                                (((src) & 0x00010000)>>16)
#define SEC16_WR(src)                           (((u32)(src)<<16) & 0x00010000)
#define SEC16_SET(dst,src) \
                      (((dst) & ~0x00010000) | (((u32)(src)<<16) & 0x00010000))
/*	 Fields SEC15	 */
#define SEC15_WIDTH                                                           1
#define SEC15_SHIFT                                                          15
#define SEC15_MASK                                                   0x00008000
#define SEC15_RD(src)                                (((src) & 0x00008000)>>15)
#define SEC15_WR(src)                           (((u32)(src)<<15) & 0x00008000)
#define SEC15_SET(dst,src) \
                      (((dst) & ~0x00008000) | (((u32)(src)<<15) & 0x00008000))
/*	 Fields SEC14	 */
#define SEC14_WIDTH                                                           1
#define SEC14_SHIFT                                                          14
#define SEC14_MASK                                                   0x00004000
#define SEC14_RD(src)                                (((src) & 0x00004000)>>14)
#define SEC14_WR(src)                           (((u32)(src)<<14) & 0x00004000)
#define SEC14_SET(dst,src) \
                      (((dst) & ~0x00004000) | (((u32)(src)<<14) & 0x00004000))
/*	 Fields SEC13	 */
#define SEC13_WIDTH                                                           1
#define SEC13_SHIFT                                                          13
#define SEC13_MASK                                                   0x00002000
#define SEC13_RD(src)                                (((src) & 0x00002000)>>13)
#define SEC13_WR(src)                           (((u32)(src)<<13) & 0x00002000)
#define SEC13_SET(dst,src) \
                      (((dst) & ~0x00002000) | (((u32)(src)<<13) & 0x00002000))
/*	 Fields SEC12	 */
#define SEC12_WIDTH                                                           1
#define SEC12_SHIFT                                                          12
#define SEC12_MASK                                                   0x00001000
#define SEC12_RD(src)                                (((src) & 0x00001000)>>12)
#define SEC12_WR(src)                           (((u32)(src)<<12) & 0x00001000)
#define SEC12_SET(dst,src) \
                      (((dst) & ~0x00001000) | (((u32)(src)<<12) & 0x00001000))
/*	 Fields SEC11	 */
#define SEC11_WIDTH                                                           1
#define SEC11_SHIFT                                                          11
#define SEC11_MASK                                                   0x00000800
#define SEC11_RD(src)                                (((src) & 0x00000800)>>11)
#define SEC11_WR(src)                           (((u32)(src)<<11) & 0x00000800)
#define SEC11_SET(dst,src) \
                      (((dst) & ~0x00000800) | (((u32)(src)<<11) & 0x00000800))
/*	 Fields SEC10	 */
#define SEC10_WIDTH                                                           1
#define SEC10_SHIFT                                                          10
#define SEC10_MASK                                                   0x00000400
#define SEC10_RD(src)                                (((src) & 0x00000400)>>10)
#define SEC10_WR(src)                           (((u32)(src)<<10) & 0x00000400)
#define SEC10_SET(dst,src) \
                      (((dst) & ~0x00000400) | (((u32)(src)<<10) & 0x00000400))
/*	 Fields SEC9	 */
#define SEC9_WIDTH                                                            1
#define SEC9_SHIFT                                                            9
#define SEC9_MASK                                                    0x00000200
#define SEC9_RD(src)                                  (((src) & 0x00000200)>>9)
#define SEC9_WR(src)                             (((u32)(src)<<9) & 0x00000200)
#define SEC9_SET(dst,src) \
                       (((dst) & ~0x00000200) | (((u32)(src)<<9) & 0x00000200))
/*	 Fields SEC8	 */
#define SEC8_WIDTH                                                            1
#define SEC8_SHIFT                                                            8
#define SEC8_MASK                                                    0x00000100
#define SEC8_RD(src)                                  (((src) & 0x00000100)>>8)
#define SEC8_WR(src)                             (((u32)(src)<<8) & 0x00000100)
#define SEC8_SET(dst,src) \
                       (((dst) & ~0x00000100) | (((u32)(src)<<8) & 0x00000100))
/*	 Fields SEC7	 */
#define SEC7_WIDTH                                                            1
#define SEC7_SHIFT                                                            7
#define SEC7_MASK                                                    0x00000080
#define SEC7_RD(src)                                  (((src) & 0x00000080)>>7)
#define SEC7_WR(src)                             (((u32)(src)<<7) & 0x00000080)
#define SEC7_SET(dst,src) \
                       (((dst) & ~0x00000080) | (((u32)(src)<<7) & 0x00000080))
/*	 Fields SEC6	 */
#define SEC6_WIDTH                                                            1
#define SEC6_SHIFT                                                            6
#define SEC6_MASK                                                    0x00000040
#define SEC6_RD(src)                                  (((src) & 0x00000040)>>6)
#define SEC6_WR(src)                             (((u32)(src)<<6) & 0x00000040)
#define SEC6_SET(dst,src) \
                       (((dst) & ~0x00000040) | (((u32)(src)<<6) & 0x00000040))
/*	 Fields SEC5	 */
#define SEC5_WIDTH                                                            1
#define SEC5_SHIFT                                                            5
#define SEC5_MASK                                                    0x00000020
#define SEC5_RD(src)                                  (((src) & 0x00000020)>>5)
#define SEC5_WR(src)                             (((u32)(src)<<5) & 0x00000020)
#define SEC5_SET(dst,src) \
                       (((dst) & ~0x00000020) | (((u32)(src)<<5) & 0x00000020))
/*	 Fields SEC4	 */
#define SEC4_WIDTH                                                            1
#define SEC4_SHIFT                                                            4
#define SEC4_MASK                                                    0x00000010
#define SEC4_RD(src)                                  (((src) & 0x00000010)>>4)
#define SEC4_WR(src)                             (((u32)(src)<<4) & 0x00000010)
#define SEC4_SET(dst,src) \
                       (((dst) & ~0x00000010) | (((u32)(src)<<4) & 0x00000010))
/*	 Fields SEC3	 */
#define SEC3_WIDTH                                                            1
#define SEC3_SHIFT                                                            3
#define SEC3_MASK                                                    0x00000008
#define SEC3_RD(src)                                  (((src) & 0x00000008)>>3)
#define SEC3_WR(src)                             (((u32)(src)<<3) & 0x00000008)
#define SEC3_SET(dst,src) \
                       (((dst) & ~0x00000008) | (((u32)(src)<<3) & 0x00000008))
/*	 Fields SEC2	 */
#define SEC2_WIDTH                                                            1
#define SEC2_SHIFT                                                            2
#define SEC2_MASK                                                    0x00000004
#define SEC2_RD(src)                                  (((src) & 0x00000004)>>2)
#define SEC2_WR(src)                             (((u32)(src)<<2) & 0x00000004)
#define SEC2_SET(dst,src) \
                       (((dst) & ~0x00000004) | (((u32)(src)<<2) & 0x00000004))
/*	 Fields SEC1	 */
#define SEC1_WIDTH                                                            1
#define SEC1_SHIFT                                                            1
#define SEC1_MASK                                                    0x00000002
#define SEC1_RD(src)                                  (((src) & 0x00000002)>>1)
#define SEC1_WR(src)                             (((u32)(src)<<1) & 0x00000002)
#define SEC1_SET(dst,src) \
                       (((dst) & ~0x00000002) | (((u32)(src)<<1) & 0x00000002))
/*	 Fields SEC0	 */
#define SEC0_WIDTH                                                            1
#define SEC0_SHIFT                                                            0
#define SEC0_MASK                                                    0x00000001
#define SEC0_RD(src)                                     (((src) & 0x00000001))
#define SEC0_WR(src)                                (((u32)(src)) & 0x00000001)
#define SEC0_SET(dst,src) \
                          (((dst) & ~0x00000001) | (((u32)(src)) & 0x00000001))

/*	Register GLBL_SEC_ERRLMask	*/
/*    Mask Register Fields SEC31Mask    */
#define SEC31MASK_WIDTH                                                       1
#define SEC31MASK_SHIFT                                                      31
#define SEC31MASK_MASK                                               0x80000000
#define SEC31MASK_RD(src)                            (((src) & 0x80000000)>>31)
#define SEC31MASK_WR(src)                       (((u32)(src)<<31) & 0x80000000)
#define SEC31MASK_SET(dst,src) \
                      (((dst) & ~0x80000000) | (((u32)(src)<<31) & 0x80000000))
/*    Mask Register Fields SEC30Mask    */
#define SEC30MASK_WIDTH                                                       1
#define SEC30MASK_SHIFT                                                      30
#define SEC30MASK_MASK                                               0x40000000
#define SEC30MASK_RD(src)                            (((src) & 0x40000000)>>30)
#define SEC30MASK_WR(src)                       (((u32)(src)<<30) & 0x40000000)
#define SEC30MASK_SET(dst,src) \
                      (((dst) & ~0x40000000) | (((u32)(src)<<30) & 0x40000000))
/*    Mask Register Fields SEC29Mask    */
#define SEC29MASK_WIDTH                                                       1
#define SEC29MASK_SHIFT                                                      29
#define SEC29MASK_MASK                                               0x20000000
#define SEC29MASK_RD(src)                            (((src) & 0x20000000)>>29)
#define SEC29MASK_WR(src)                       (((u32)(src)<<29) & 0x20000000)
#define SEC29MASK_SET(dst,src) \
                      (((dst) & ~0x20000000) | (((u32)(src)<<29) & 0x20000000))
/*    Mask Register Fields SEC28Mask    */
#define SEC28MASK_WIDTH                                                       1
#define SEC28MASK_SHIFT                                                      28
#define SEC28MASK_MASK                                               0x10000000
#define SEC28MASK_RD(src)                            (((src) & 0x10000000)>>28)
#define SEC28MASK_WR(src)                       (((u32)(src)<<28) & 0x10000000)
#define SEC28MASK_SET(dst,src) \
                      (((dst) & ~0x10000000) | (((u32)(src)<<28) & 0x10000000))
/*    Mask Register Fields SEC27Mask    */
#define SEC27MASK_WIDTH                                                       1
#define SEC27MASK_SHIFT                                                      27
#define SEC27MASK_MASK                                               0x08000000
#define SEC27MASK_RD(src)                            (((src) & 0x08000000)>>27)
#define SEC27MASK_WR(src)                       (((u32)(src)<<27) & 0x08000000)
#define SEC27MASK_SET(dst,src) \
                      (((dst) & ~0x08000000) | (((u32)(src)<<27) & 0x08000000))
/*    Mask Register Fields SEC26Mask    */
#define SEC26MASK_WIDTH                                                       1
#define SEC26MASK_SHIFT                                                      26
#define SEC26MASK_MASK                                               0x04000000
#define SEC26MASK_RD(src)                            (((src) & 0x04000000)>>26)
#define SEC26MASK_WR(src)                       (((u32)(src)<<26) & 0x04000000)
#define SEC26MASK_SET(dst,src) \
                      (((dst) & ~0x04000000) | (((u32)(src)<<26) & 0x04000000))
/*    Mask Register Fields SEC25Mask    */
#define SEC25MASK_WIDTH                                                       1
#define SEC25MASK_SHIFT                                                      25
#define SEC25MASK_MASK                                               0x02000000
#define SEC25MASK_RD(src)                            (((src) & 0x02000000)>>25)
#define SEC25MASK_WR(src)                       (((u32)(src)<<25) & 0x02000000)
#define SEC25MASK_SET(dst,src) \
                      (((dst) & ~0x02000000) | (((u32)(src)<<25) & 0x02000000))
/*    Mask Register Fields SEC24Mask    */
#define SEC24MASK_WIDTH                                                       1
#define SEC24MASK_SHIFT                                                      24
#define SEC24MASK_MASK                                               0x01000000
#define SEC24MASK_RD(src)                            (((src) & 0x01000000)>>24)
#define SEC24MASK_WR(src)                       (((u32)(src)<<24) & 0x01000000)
#define SEC24MASK_SET(dst,src) \
                      (((dst) & ~0x01000000) | (((u32)(src)<<24) & 0x01000000))
/*    Mask Register Fields SEC23Mask    */
#define SEC23MASK_WIDTH                                                       1
#define SEC23MASK_SHIFT                                                      23
#define SEC23MASK_MASK                                               0x00800000
#define SEC23MASK_RD(src)                            (((src) & 0x00800000)>>23)
#define SEC23MASK_WR(src)                       (((u32)(src)<<23) & 0x00800000)
#define SEC23MASK_SET(dst,src) \
                      (((dst) & ~0x00800000) | (((u32)(src)<<23) & 0x00800000))
/*    Mask Register Fields SEC22Mask    */
#define SEC22MASK_WIDTH                                                       1
#define SEC22MASK_SHIFT                                                      22
#define SEC22MASK_MASK                                               0x00400000
#define SEC22MASK_RD(src)                            (((src) & 0x00400000)>>22)
#define SEC22MASK_WR(src)                       (((u32)(src)<<22) & 0x00400000)
#define SEC22MASK_SET(dst,src) \
                      (((dst) & ~0x00400000) | (((u32)(src)<<22) & 0x00400000))
/*    Mask Register Fields SEC21Mask    */
#define SEC21MASK_WIDTH                                                       1
#define SEC21MASK_SHIFT                                                      21
#define SEC21MASK_MASK                                               0x00200000
#define SEC21MASK_RD(src)                            (((src) & 0x00200000)>>21)
#define SEC21MASK_WR(src)                       (((u32)(src)<<21) & 0x00200000)
#define SEC21MASK_SET(dst,src) \
                      (((dst) & ~0x00200000) | (((u32)(src)<<21) & 0x00200000))
/*    Mask Register Fields SEC20Mask    */
#define SEC20MASK_WIDTH                                                       1
#define SEC20MASK_SHIFT                                                      20
#define SEC20MASK_MASK                                               0x00100000
#define SEC20MASK_RD(src)                            (((src) & 0x00100000)>>20)
#define SEC20MASK_WR(src)                       (((u32)(src)<<20) & 0x00100000)
#define SEC20MASK_SET(dst,src) \
                      (((dst) & ~0x00100000) | (((u32)(src)<<20) & 0x00100000))
/*    Mask Register Fields SEC19Mask    */
#define SEC19MASK_WIDTH                                                       1
#define SEC19MASK_SHIFT                                                      19
#define SEC19MASK_MASK                                               0x00080000
#define SEC19MASK_RD(src)                            (((src) & 0x00080000)>>19)
#define SEC19MASK_WR(src)                       (((u32)(src)<<19) & 0x00080000)
#define SEC19MASK_SET(dst,src) \
                      (((dst) & ~0x00080000) | (((u32)(src)<<19) & 0x00080000))
/*    Mask Register Fields SEC18Mask    */
#define SEC18MASK_WIDTH                                                       1
#define SEC18MASK_SHIFT                                                      18
#define SEC18MASK_MASK                                               0x00040000
#define SEC18MASK_RD(src)                            (((src) & 0x00040000)>>18)
#define SEC18MASK_WR(src)                       (((u32)(src)<<18) & 0x00040000)
#define SEC18MASK_SET(dst,src) \
                      (((dst) & ~0x00040000) | (((u32)(src)<<18) & 0x00040000))
/*    Mask Register Fields SEC17Mask    */
#define SEC17MASK_WIDTH                                                       1
#define SEC17MASK_SHIFT                                                      17
#define SEC17MASK_MASK                                               0x00020000
#define SEC17MASK_RD(src)                            (((src) & 0x00020000)>>17)
#define SEC17MASK_WR(src)                       (((u32)(src)<<17) & 0x00020000)
#define SEC17MASK_SET(dst,src) \
                      (((dst) & ~0x00020000) | (((u32)(src)<<17) & 0x00020000))
/*    Mask Register Fields SEC16Mask    */
#define SEC16MASK_WIDTH                                                       1
#define SEC16MASK_SHIFT                                                      16
#define SEC16MASK_MASK                                               0x00010000
#define SEC16MASK_RD(src)                            (((src) & 0x00010000)>>16)
#define SEC16MASK_WR(src)                       (((u32)(src)<<16) & 0x00010000)
#define SEC16MASK_SET(dst,src) \
                      (((dst) & ~0x00010000) | (((u32)(src)<<16) & 0x00010000))
/*    Mask Register Fields SEC15Mask    */
#define SEC15MASK_WIDTH                                                       1
#define SEC15MASK_SHIFT                                                      15
#define SEC15MASK_MASK                                               0x00008000
#define SEC15MASK_RD(src)                            (((src) & 0x00008000)>>15)
#define SEC15MASK_WR(src)                       (((u32)(src)<<15) & 0x00008000)
#define SEC15MASK_SET(dst,src) \
                      (((dst) & ~0x00008000) | (((u32)(src)<<15) & 0x00008000))
/*    Mask Register Fields SEC14Mask    */
#define SEC14MASK_WIDTH                                                       1
#define SEC14MASK_SHIFT                                                      14
#define SEC14MASK_MASK                                               0x00004000
#define SEC14MASK_RD(src)                            (((src) & 0x00004000)>>14)
#define SEC14MASK_WR(src)                       (((u32)(src)<<14) & 0x00004000)
#define SEC14MASK_SET(dst,src) \
                      (((dst) & ~0x00004000) | (((u32)(src)<<14) & 0x00004000))
/*    Mask Register Fields SEC13Mask    */
#define SEC13MASK_WIDTH                                                       1
#define SEC13MASK_SHIFT                                                      13
#define SEC13MASK_MASK                                               0x00002000
#define SEC13MASK_RD(src)                            (((src) & 0x00002000)>>13)
#define SEC13MASK_WR(src)                       (((u32)(src)<<13) & 0x00002000)
#define SEC13MASK_SET(dst,src) \
                      (((dst) & ~0x00002000) | (((u32)(src)<<13) & 0x00002000))
/*    Mask Register Fields SEC12Mask    */
#define SEC12MASK_WIDTH                                                       1
#define SEC12MASK_SHIFT                                                      12
#define SEC12MASK_MASK                                               0x00001000
#define SEC12MASK_RD(src)                            (((src) & 0x00001000)>>12)
#define SEC12MASK_WR(src)                       (((u32)(src)<<12) & 0x00001000)
#define SEC12MASK_SET(dst,src) \
                      (((dst) & ~0x00001000) | (((u32)(src)<<12) & 0x00001000))
/*    Mask Register Fields SEC11Mask    */
#define SEC11MASK_WIDTH                                                       1
#define SEC11MASK_SHIFT                                                      11
#define SEC11MASK_MASK                                               0x00000800
#define SEC11MASK_RD(src)                            (((src) & 0x00000800)>>11)
#define SEC11MASK_WR(src)                       (((u32)(src)<<11) & 0x00000800)
#define SEC11MASK_SET(dst,src) \
                      (((dst) & ~0x00000800) | (((u32)(src)<<11) & 0x00000800))
/*    Mask Register Fields SEC10Mask    */
#define SEC10MASK_WIDTH                                                       1
#define SEC10MASK_SHIFT                                                      10
#define SEC10MASK_MASK                                               0x00000400
#define SEC10MASK_RD(src)                            (((src) & 0x00000400)>>10)
#define SEC10MASK_WR(src)                       (((u32)(src)<<10) & 0x00000400)
#define SEC10MASK_SET(dst,src) \
                      (((dst) & ~0x00000400) | (((u32)(src)<<10) & 0x00000400))
/*    Mask Register Fields SEC9Mask    */
#define SEC9MASK_WIDTH                                                        1
#define SEC9MASK_SHIFT                                                        9
#define SEC9MASK_MASK                                                0x00000200
#define SEC9MASK_RD(src)                              (((src) & 0x00000200)>>9)
#define SEC9MASK_WR(src)                         (((u32)(src)<<9) & 0x00000200)
#define SEC9MASK_SET(dst,src) \
                       (((dst) & ~0x00000200) | (((u32)(src)<<9) & 0x00000200))
/*    Mask Register Fields SEC8Mask    */
#define SEC8MASK_WIDTH                                                        1
#define SEC8MASK_SHIFT                                                        8
#define SEC8MASK_MASK                                                0x00000100
#define SEC8MASK_RD(src)                              (((src) & 0x00000100)>>8)
#define SEC8MASK_WR(src)                         (((u32)(src)<<8) & 0x00000100)
#define SEC8MASK_SET(dst,src) \
                       (((dst) & ~0x00000100) | (((u32)(src)<<8) & 0x00000100))
/*    Mask Register Fields SEC7Mask    */
#define SEC7MASK_WIDTH                                                        1
#define SEC7MASK_SHIFT                                                        7
#define SEC7MASK_MASK                                                0x00000080
#define SEC7MASK_RD(src)                              (((src) & 0x00000080)>>7)
#define SEC7MASK_WR(src)                         (((u32)(src)<<7) & 0x00000080)
#define SEC7MASK_SET(dst,src) \
                       (((dst) & ~0x00000080) | (((u32)(src)<<7) & 0x00000080))
/*    Mask Register Fields SEC6Mask    */
#define SEC6MASK_WIDTH                                                        1
#define SEC6MASK_SHIFT                                                        6
#define SEC6MASK_MASK                                                0x00000040
#define SEC6MASK_RD(src)                              (((src) & 0x00000040)>>6)
#define SEC6MASK_WR(src)                         (((u32)(src)<<6) & 0x00000040)
#define SEC6MASK_SET(dst,src) \
                       (((dst) & ~0x00000040) | (((u32)(src)<<6) & 0x00000040))
/*    Mask Register Fields SEC5Mask    */
#define SEC5MASK_WIDTH                                                        1
#define SEC5MASK_SHIFT                                                        5
#define SEC5MASK_MASK                                                0x00000020
#define SEC5MASK_RD(src)                              (((src) & 0x00000020)>>5)
#define SEC5MASK_WR(src)                         (((u32)(src)<<5) & 0x00000020)
#define SEC5MASK_SET(dst,src) \
                       (((dst) & ~0x00000020) | (((u32)(src)<<5) & 0x00000020))
/*    Mask Register Fields SEC4Mask    */
#define SEC4MASK_WIDTH                                                        1
#define SEC4MASK_SHIFT                                                        4
#define SEC4MASK_MASK                                                0x00000010
#define SEC4MASK_RD(src)                              (((src) & 0x00000010)>>4)
#define SEC4MASK_WR(src)                         (((u32)(src)<<4) & 0x00000010)
#define SEC4MASK_SET(dst,src) \
                       (((dst) & ~0x00000010) | (((u32)(src)<<4) & 0x00000010))
/*    Mask Register Fields SEC3Mask    */
#define SEC3MASK_WIDTH                                                        1
#define SEC3MASK_SHIFT                                                        3
#define SEC3MASK_MASK                                                0x00000008
#define SEC3MASK_RD(src)                              (((src) & 0x00000008)>>3)
#define SEC3MASK_WR(src)                         (((u32)(src)<<3) & 0x00000008)
#define SEC3MASK_SET(dst,src) \
                       (((dst) & ~0x00000008) | (((u32)(src)<<3) & 0x00000008))
/*    Mask Register Fields SEC2Mask    */
#define SEC2MASK_WIDTH                                                        1
#define SEC2MASK_SHIFT                                                        2
#define SEC2MASK_MASK                                                0x00000004
#define SEC2MASK_RD(src)                              (((src) & 0x00000004)>>2)
#define SEC2MASK_WR(src)                         (((u32)(src)<<2) & 0x00000004)
#define SEC2MASK_SET(dst,src) \
                       (((dst) & ~0x00000004) | (((u32)(src)<<2) & 0x00000004))
/*    Mask Register Fields SEC1Mask    */
#define SEC1MASK_WIDTH                                                        1
#define SEC1MASK_SHIFT                                                        1
#define SEC1MASK_MASK                                                0x00000002
#define SEC1MASK_RD(src)                              (((src) & 0x00000002)>>1)
#define SEC1MASK_WR(src)                         (((u32)(src)<<1) & 0x00000002)
#define SEC1MASK_SET(dst,src) \
                       (((dst) & ~0x00000002) | (((u32)(src)<<1) & 0x00000002))
/*    Mask Register Fields SEC0Mask    */
#define SEC0MASK_WIDTH                                                        1
#define SEC0MASK_SHIFT                                                        0
#define SEC0MASK_MASK                                                0x00000001
#define SEC0MASK_RD(src)                                 (((src) & 0x00000001))
#define SEC0MASK_WR(src)                            (((u32)(src)) & 0x00000001)
#define SEC0MASK_SET(dst,src) \
                          (((dst) & ~0x00000001) | (((u32)(src)) & 0x00000001))

/*	Register GLBL_SEC_ERRH	*/ 
/*	 Fields SEC31	 */
#define SEC31_F1_WIDTH                                                        1
#define SEC31_F1_SHIFT                                                       31
#define SEC31_F1_MASK                                                0x80000000
#define SEC31_F1_RD(src)                             (((src) & 0x80000000)>>31)
#define SEC31_F1_WR(src)                        (((u32)(src)<<31) & 0x80000000)
#define SEC31_F1_SET(dst,src) \
                      (((dst) & ~0x80000000) | (((u32)(src)<<31) & 0x80000000))
/*	 Fields SEC30	 */
#define SEC30_F1_WIDTH                                                        1
#define SEC30_F1_SHIFT                                                       30
#define SEC30_F1_MASK                                                0x40000000
#define SEC30_F1_RD(src)                             (((src) & 0x40000000)>>30)
#define SEC30_F1_WR(src)                        (((u32)(src)<<30) & 0x40000000)
#define SEC30_F1_SET(dst,src) \
                      (((dst) & ~0x40000000) | (((u32)(src)<<30) & 0x40000000))
/*	 Fields SEC29	 */
#define SEC29_F1_WIDTH                                                        1
#define SEC29_F1_SHIFT                                                       29
#define SEC29_F1_MASK                                                0x20000000
#define SEC29_F1_RD(src)                             (((src) & 0x20000000)>>29)
#define SEC29_F1_WR(src)                        (((u32)(src)<<29) & 0x20000000)
#define SEC29_F1_SET(dst,src) \
                      (((dst) & ~0x20000000) | (((u32)(src)<<29) & 0x20000000))
/*	 Fields SEC28	 */
#define SEC28_F1_WIDTH                                                        1
#define SEC28_F1_SHIFT                                                       28
#define SEC28_F1_MASK                                                0x10000000
#define SEC28_F1_RD(src)                             (((src) & 0x10000000)>>28)
#define SEC28_F1_WR(src)                        (((u32)(src)<<28) & 0x10000000)
#define SEC28_F1_SET(dst,src) \
                      (((dst) & ~0x10000000) | (((u32)(src)<<28) & 0x10000000))
/*	 Fields SEC27	 */
#define SEC27_F1_WIDTH                                                        1
#define SEC27_F1_SHIFT                                                       27
#define SEC27_F1_MASK                                                0x08000000
#define SEC27_F1_RD(src)                             (((src) & 0x08000000)>>27)
#define SEC27_F1_WR(src)                        (((u32)(src)<<27) & 0x08000000)
#define SEC27_F1_SET(dst,src) \
                      (((dst) & ~0x08000000) | (((u32)(src)<<27) & 0x08000000))
/*	 Fields SEC26	 */
#define SEC26_F1_WIDTH                                                        1
#define SEC26_F1_SHIFT                                                       26
#define SEC26_F1_MASK                                                0x04000000
#define SEC26_F1_RD(src)                             (((src) & 0x04000000)>>26)
#define SEC26_F1_WR(src)                        (((u32)(src)<<26) & 0x04000000)
#define SEC26_F1_SET(dst,src) \
                      (((dst) & ~0x04000000) | (((u32)(src)<<26) & 0x04000000))
/*	 Fields SEC25	 */
#define SEC25_F1_WIDTH                                                        1
#define SEC25_F1_SHIFT                                                       25
#define SEC25_F1_MASK                                                0x02000000
#define SEC25_F1_RD(src)                             (((src) & 0x02000000)>>25)
#define SEC25_F1_WR(src)                        (((u32)(src)<<25) & 0x02000000)
#define SEC25_F1_SET(dst,src) \
                      (((dst) & ~0x02000000) | (((u32)(src)<<25) & 0x02000000))
/*	 Fields SEC24	 */
#define SEC24_F1_WIDTH                                                        1
#define SEC24_F1_SHIFT                                                       24
#define SEC24_F1_MASK                                                0x01000000
#define SEC24_F1_RD(src)                             (((src) & 0x01000000)>>24)
#define SEC24_F1_WR(src)                        (((u32)(src)<<24) & 0x01000000)
#define SEC24_F1_SET(dst,src) \
                      (((dst) & ~0x01000000) | (((u32)(src)<<24) & 0x01000000))
/*	 Fields SEC23	 */
#define SEC23_F1_WIDTH                                                        1
#define SEC23_F1_SHIFT                                                       23
#define SEC23_F1_MASK                                                0x00800000
#define SEC23_F1_RD(src)                             (((src) & 0x00800000)>>23)
#define SEC23_F1_WR(src)                        (((u32)(src)<<23) & 0x00800000)
#define SEC23_F1_SET(dst,src) \
                      (((dst) & ~0x00800000) | (((u32)(src)<<23) & 0x00800000))
/*	 Fields SEC22	 */
#define SEC22_F1_WIDTH                                                        1
#define SEC22_F1_SHIFT                                                       22
#define SEC22_F1_MASK                                                0x00400000
#define SEC22_F1_RD(src)                             (((src) & 0x00400000)>>22)
#define SEC22_F1_WR(src)                        (((u32)(src)<<22) & 0x00400000)
#define SEC22_F1_SET(dst,src) \
                      (((dst) & ~0x00400000) | (((u32)(src)<<22) & 0x00400000))
/*	 Fields SEC21	 */
#define SEC21_F1_WIDTH                                                        1
#define SEC21_F1_SHIFT                                                       21
#define SEC21_F1_MASK                                                0x00200000
#define SEC21_F1_RD(src)                             (((src) & 0x00200000)>>21)
#define SEC21_F1_WR(src)                        (((u32)(src)<<21) & 0x00200000)
#define SEC21_F1_SET(dst,src) \
                      (((dst) & ~0x00200000) | (((u32)(src)<<21) & 0x00200000))
/*	 Fields SEC20	 */
#define SEC20_F1_WIDTH                                                        1
#define SEC20_F1_SHIFT                                                       20
#define SEC20_F1_MASK                                                0x00100000
#define SEC20_F1_RD(src)                             (((src) & 0x00100000)>>20)
#define SEC20_F1_WR(src)                        (((u32)(src)<<20) & 0x00100000)
#define SEC20_F1_SET(dst,src) \
                      (((dst) & ~0x00100000) | (((u32)(src)<<20) & 0x00100000))
/*	 Fields SEC19	 */
#define SEC19_F1_WIDTH                                                        1
#define SEC19_F1_SHIFT                                                       19
#define SEC19_F1_MASK                                                0x00080000
#define SEC19_F1_RD(src)                             (((src) & 0x00080000)>>19)
#define SEC19_F1_WR(src)                        (((u32)(src)<<19) & 0x00080000)
#define SEC19_F1_SET(dst,src) \
                      (((dst) & ~0x00080000) | (((u32)(src)<<19) & 0x00080000))
/*	 Fields SEC18	 */
#define SEC18_F1_WIDTH                                                        1
#define SEC18_F1_SHIFT                                                       18
#define SEC18_F1_MASK                                                0x00040000
#define SEC18_F1_RD(src)                             (((src) & 0x00040000)>>18)
#define SEC18_F1_WR(src)                        (((u32)(src)<<18) & 0x00040000)
#define SEC18_F1_SET(dst,src) \
                      (((dst) & ~0x00040000) | (((u32)(src)<<18) & 0x00040000))
/*	 Fields SEC17	 */
#define SEC17_F1_WIDTH                                                        1
#define SEC17_F1_SHIFT                                                       17
#define SEC17_F1_MASK                                                0x00020000
#define SEC17_F1_RD(src)                             (((src) & 0x00020000)>>17)
#define SEC17_F1_WR(src)                        (((u32)(src)<<17) & 0x00020000)
#define SEC17_F1_SET(dst,src) \
                      (((dst) & ~0x00020000) | (((u32)(src)<<17) & 0x00020000))
/*	 Fields SEC16	 */
#define SEC16_F1_WIDTH                                                        1
#define SEC16_F1_SHIFT                                                       16
#define SEC16_F1_MASK                                                0x00010000
#define SEC16_F1_RD(src)                             (((src) & 0x00010000)>>16)
#define SEC16_F1_WR(src)                        (((u32)(src)<<16) & 0x00010000)
#define SEC16_F1_SET(dst,src) \
                      (((dst) & ~0x00010000) | (((u32)(src)<<16) & 0x00010000))
/*	 Fields SEC15	 */
#define SEC15_F1_WIDTH                                                        1
#define SEC15_F1_SHIFT                                                       15
#define SEC15_F1_MASK                                                0x00008000
#define SEC15_F1_RD(src)                             (((src) & 0x00008000)>>15)
#define SEC15_F1_WR(src)                        (((u32)(src)<<15) & 0x00008000)
#define SEC15_F1_SET(dst,src) \
                      (((dst) & ~0x00008000) | (((u32)(src)<<15) & 0x00008000))
/*	 Fields SEC14	 */
#define SEC14_F1_WIDTH                                                        1
#define SEC14_F1_SHIFT                                                       14
#define SEC14_F1_MASK                                                0x00004000
#define SEC14_F1_RD(src)                             (((src) & 0x00004000)>>14)
#define SEC14_F1_WR(src)                        (((u32)(src)<<14) & 0x00004000)
#define SEC14_F1_SET(dst,src) \
                      (((dst) & ~0x00004000) | (((u32)(src)<<14) & 0x00004000))
/*	 Fields SEC13	 */
#define SEC13_F1_WIDTH                                                        1
#define SEC13_F1_SHIFT                                                       13
#define SEC13_F1_MASK                                                0x00002000
#define SEC13_F1_RD(src)                             (((src) & 0x00002000)>>13)
#define SEC13_F1_WR(src)                        (((u32)(src)<<13) & 0x00002000)
#define SEC13_F1_SET(dst,src) \
                      (((dst) & ~0x00002000) | (((u32)(src)<<13) & 0x00002000))
/*	 Fields SEC12	 */
#define SEC12_F1_WIDTH                                                        1
#define SEC12_F1_SHIFT                                                       12
#define SEC12_F1_MASK                                                0x00001000
#define SEC12_F1_RD(src)                             (((src) & 0x00001000)>>12)
#define SEC12_F1_WR(src)                        (((u32)(src)<<12) & 0x00001000)
#define SEC12_F1_SET(dst,src) \
                      (((dst) & ~0x00001000) | (((u32)(src)<<12) & 0x00001000))
/*	 Fields SEC11	 */
#define SEC11_F1_WIDTH                                                        1
#define SEC11_F1_SHIFT                                                       11
#define SEC11_F1_MASK                                                0x00000800
#define SEC11_F1_RD(src)                             (((src) & 0x00000800)>>11)
#define SEC11_F1_WR(src)                        (((u32)(src)<<11) & 0x00000800)
#define SEC11_F1_SET(dst,src) \
                      (((dst) & ~0x00000800) | (((u32)(src)<<11) & 0x00000800))
/*	 Fields SEC10	 */
#define SEC10_F1_WIDTH                                                        1
#define SEC10_F1_SHIFT                                                       10
#define SEC10_F1_MASK                                                0x00000400
#define SEC10_F1_RD(src)                             (((src) & 0x00000400)>>10)
#define SEC10_F1_WR(src)                        (((u32)(src)<<10) & 0x00000400)
#define SEC10_F1_SET(dst,src) \
                      (((dst) & ~0x00000400) | (((u32)(src)<<10) & 0x00000400))
/*	 Fields SEC9	 */
#define SEC9_F1_WIDTH                                                         1
#define SEC9_F1_SHIFT                                                         9
#define SEC9_F1_MASK                                                 0x00000200
#define SEC9_F1_RD(src)                               (((src) & 0x00000200)>>9)
#define SEC9_F1_WR(src)                          (((u32)(src)<<9) & 0x00000200)
#define SEC9_F1_SET(dst,src) \
                       (((dst) & ~0x00000200) | (((u32)(src)<<9) & 0x00000200))
/*	 Fields SEC8	 */
#define SEC8_F1_WIDTH                                                         1
#define SEC8_F1_SHIFT                                                         8
#define SEC8_F1_MASK                                                 0x00000100
#define SEC8_F1_RD(src)                               (((src) & 0x00000100)>>8)
#define SEC8_F1_WR(src)                          (((u32)(src)<<8) & 0x00000100)
#define SEC8_F1_SET(dst,src) \
                       (((dst) & ~0x00000100) | (((u32)(src)<<8) & 0x00000100))
/*	 Fields SEC7	 */
#define SEC7_F1_WIDTH                                                         1
#define SEC7_F1_SHIFT                                                         7
#define SEC7_F1_MASK                                                 0x00000080
#define SEC7_F1_RD(src)                               (((src) & 0x00000080)>>7)
#define SEC7_F1_WR(src)                          (((u32)(src)<<7) & 0x00000080)
#define SEC7_F1_SET(dst,src) \
                       (((dst) & ~0x00000080) | (((u32)(src)<<7) & 0x00000080))
/*	 Fields SEC6	 */
#define SEC6_F1_WIDTH                                                         1
#define SEC6_F1_SHIFT                                                         6
#define SEC6_F1_MASK                                                 0x00000040
#define SEC6_F1_RD(src)                               (((src) & 0x00000040)>>6)
#define SEC6_F1_WR(src)                          (((u32)(src)<<6) & 0x00000040)
#define SEC6_F1_SET(dst,src) \
                       (((dst) & ~0x00000040) | (((u32)(src)<<6) & 0x00000040))
/*	 Fields SEC5	 */
#define SEC5_F1_WIDTH                                                         1
#define SEC5_F1_SHIFT                                                         5
#define SEC5_F1_MASK                                                 0x00000020
#define SEC5_F1_RD(src)                               (((src) & 0x00000020)>>5)
#define SEC5_F1_WR(src)                          (((u32)(src)<<5) & 0x00000020)
#define SEC5_F1_SET(dst,src) \
                       (((dst) & ~0x00000020) | (((u32)(src)<<5) & 0x00000020))
/*	 Fields SEC4	 */
#define SEC4_F1_WIDTH                                                         1
#define SEC4_F1_SHIFT                                                         4
#define SEC4_F1_MASK                                                 0x00000010
#define SEC4_F1_RD(src)                               (((src) & 0x00000010)>>4)
#define SEC4_F1_WR(src)                          (((u32)(src)<<4) & 0x00000010)
#define SEC4_F1_SET(dst,src) \
                       (((dst) & ~0x00000010) | (((u32)(src)<<4) & 0x00000010))
/*	 Fields SEC3	 */
#define SEC3_F1_WIDTH                                                         1
#define SEC3_F1_SHIFT                                                         3
#define SEC3_F1_MASK                                                 0x00000008
#define SEC3_F1_RD(src)                               (((src) & 0x00000008)>>3)
#define SEC3_F1_WR(src)                          (((u32)(src)<<3) & 0x00000008)
#define SEC3_F1_SET(dst,src) \
                       (((dst) & ~0x00000008) | (((u32)(src)<<3) & 0x00000008))
/*	 Fields SEC2	 */
#define SEC2_F1_WIDTH                                                         1
#define SEC2_F1_SHIFT                                                         2
#define SEC2_F1_MASK                                                 0x00000004
#define SEC2_F1_RD(src)                               (((src) & 0x00000004)>>2)
#define SEC2_F1_WR(src)                          (((u32)(src)<<2) & 0x00000004)
#define SEC2_F1_SET(dst,src) \
                       (((dst) & ~0x00000004) | (((u32)(src)<<2) & 0x00000004))
/*	 Fields SEC1	 */
#define SEC1_F1_WIDTH                                                         1
#define SEC1_F1_SHIFT                                                         1
#define SEC1_F1_MASK                                                 0x00000002
#define SEC1_F1_RD(src)                               (((src) & 0x00000002)>>1)
#define SEC1_F1_WR(src)                          (((u32)(src)<<1) & 0x00000002)
#define SEC1_F1_SET(dst,src) \
                       (((dst) & ~0x00000002) | (((u32)(src)<<1) & 0x00000002))
/*	 Fields SEC0	 */
#define SEC0_F1_WIDTH                                                         1
#define SEC0_F1_SHIFT                                                         0
#define SEC0_F1_MASK                                                 0x00000001
#define SEC0_F1_RD(src)                                  (((src) & 0x00000001))
#define SEC0_F1_WR(src)                             (((u32)(src)) & 0x00000001)
#define SEC0_F1_SET(dst,src) \
                          (((dst) & ~0x00000001) | (((u32)(src)) & 0x00000001))

/*	Register GLBL_SEC_ERRHMask	*/
/*    Mask Register Fields SEC31Mask    */
#define SEC31MASK_F1_WIDTH                                                    1
#define SEC31MASK_F1_SHIFT                                                   31
#define SEC31MASK_F1_MASK                                            0x80000000
#define SEC31MASK_F1_RD(src)                         (((src) & 0x80000000)>>31)
#define SEC31MASK_F1_WR(src)                    (((u32)(src)<<31) & 0x80000000)
#define SEC31MASK_F1_SET(dst,src) \
                      (((dst) & ~0x80000000) | (((u32)(src)<<31) & 0x80000000))
/*    Mask Register Fields SEC30Mask    */
#define SEC30MASK_F1_WIDTH                                                    1
#define SEC30MASK_F1_SHIFT                                                   30
#define SEC30MASK_F1_MASK                                            0x40000000
#define SEC30MASK_F1_RD(src)                         (((src) & 0x40000000)>>30)
#define SEC30MASK_F1_WR(src)                    (((u32)(src)<<30) & 0x40000000)
#define SEC30MASK_F1_SET(dst,src) \
                      (((dst) & ~0x40000000) | (((u32)(src)<<30) & 0x40000000))
/*    Mask Register Fields SEC29Mask    */
#define SEC29MASK_F1_WIDTH                                                    1
#define SEC29MASK_F1_SHIFT                                                   29
#define SEC29MASK_F1_MASK                                            0x20000000
#define SEC29MASK_F1_RD(src)                         (((src) & 0x20000000)>>29)
#define SEC29MASK_F1_WR(src)                    (((u32)(src)<<29) & 0x20000000)
#define SEC29MASK_F1_SET(dst,src) \
                      (((dst) & ~0x20000000) | (((u32)(src)<<29) & 0x20000000))
/*    Mask Register Fields SEC28Mask    */
#define SEC28MASK_F1_WIDTH                                                    1
#define SEC28MASK_F1_SHIFT                                                   28
#define SEC28MASK_F1_MASK                                            0x10000000
#define SEC28MASK_F1_RD(src)                         (((src) & 0x10000000)>>28)
#define SEC28MASK_F1_WR(src)                    (((u32)(src)<<28) & 0x10000000)
#define SEC28MASK_F1_SET(dst,src) \
                      (((dst) & ~0x10000000) | (((u32)(src)<<28) & 0x10000000))
/*    Mask Register Fields SEC27Mask    */
#define SEC27MASK_F1_WIDTH                                                    1
#define SEC27MASK_F1_SHIFT                                                   27
#define SEC27MASK_F1_MASK                                            0x08000000
#define SEC27MASK_F1_RD(src)                         (((src) & 0x08000000)>>27)
#define SEC27MASK_F1_WR(src)                    (((u32)(src)<<27) & 0x08000000)
#define SEC27MASK_F1_SET(dst,src) \
                      (((dst) & ~0x08000000) | (((u32)(src)<<27) & 0x08000000))
/*    Mask Register Fields SEC26Mask    */
#define SEC26MASK_F1_WIDTH                                                    1
#define SEC26MASK_F1_SHIFT                                                   26
#define SEC26MASK_F1_MASK                                            0x04000000
#define SEC26MASK_F1_RD(src)                         (((src) & 0x04000000)>>26)
#define SEC26MASK_F1_WR(src)                    (((u32)(src)<<26) & 0x04000000)
#define SEC26MASK_F1_SET(dst,src) \
                      (((dst) & ~0x04000000) | (((u32)(src)<<26) & 0x04000000))
/*    Mask Register Fields SEC25Mask    */
#define SEC25MASK_F1_WIDTH                                                    1
#define SEC25MASK_F1_SHIFT                                                   25
#define SEC25MASK_F1_MASK                                            0x02000000
#define SEC25MASK_F1_RD(src)                         (((src) & 0x02000000)>>25)
#define SEC25MASK_F1_WR(src)                    (((u32)(src)<<25) & 0x02000000)
#define SEC25MASK_F1_SET(dst,src) \
                      (((dst) & ~0x02000000) | (((u32)(src)<<25) & 0x02000000))
/*    Mask Register Fields SEC24Mask    */
#define SEC24MASK_F1_WIDTH                                                    1
#define SEC24MASK_F1_SHIFT                                                   24
#define SEC24MASK_F1_MASK                                            0x01000000
#define SEC24MASK_F1_RD(src)                         (((src) & 0x01000000)>>24)
#define SEC24MASK_F1_WR(src)                    (((u32)(src)<<24) & 0x01000000)
#define SEC24MASK_F1_SET(dst,src) \
                      (((dst) & ~0x01000000) | (((u32)(src)<<24) & 0x01000000))
/*    Mask Register Fields SEC23Mask    */
#define SEC23MASK_F1_WIDTH                                                    1
#define SEC23MASK_F1_SHIFT                                                   23
#define SEC23MASK_F1_MASK                                            0x00800000
#define SEC23MASK_F1_RD(src)                         (((src) & 0x00800000)>>23)
#define SEC23MASK_F1_WR(src)                    (((u32)(src)<<23) & 0x00800000)
#define SEC23MASK_F1_SET(dst,src) \
                      (((dst) & ~0x00800000) | (((u32)(src)<<23) & 0x00800000))
/*    Mask Register Fields SEC22Mask    */
#define SEC22MASK_F1_WIDTH                                                    1
#define SEC22MASK_F1_SHIFT                                                   22
#define SEC22MASK_F1_MASK                                            0x00400000
#define SEC22MASK_F1_RD(src)                         (((src) & 0x00400000)>>22)
#define SEC22MASK_F1_WR(src)                    (((u32)(src)<<22) & 0x00400000)
#define SEC22MASK_F1_SET(dst,src) \
                      (((dst) & ~0x00400000) | (((u32)(src)<<22) & 0x00400000))
/*    Mask Register Fields SEC21Mask    */
#define SEC21MASK_F1_WIDTH                                                    1
#define SEC21MASK_F1_SHIFT                                                   21
#define SEC21MASK_F1_MASK                                            0x00200000
#define SEC21MASK_F1_RD(src)                         (((src) & 0x00200000)>>21)
#define SEC21MASK_F1_WR(src)                    (((u32)(src)<<21) & 0x00200000)
#define SEC21MASK_F1_SET(dst,src) \
                      (((dst) & ~0x00200000) | (((u32)(src)<<21) & 0x00200000))
/*    Mask Register Fields SEC20Mask    */
#define SEC20MASK_F1_WIDTH                                                    1
#define SEC20MASK_F1_SHIFT                                                   20
#define SEC20MASK_F1_MASK                                            0x00100000
#define SEC20MASK_F1_RD(src)                         (((src) & 0x00100000)>>20)
#define SEC20MASK_F1_WR(src)                    (((u32)(src)<<20) & 0x00100000)
#define SEC20MASK_F1_SET(dst,src) \
                      (((dst) & ~0x00100000) | (((u32)(src)<<20) & 0x00100000))
/*    Mask Register Fields SEC19Mask    */
#define SEC19MASK_F1_WIDTH                                                    1
#define SEC19MASK_F1_SHIFT                                                   19
#define SEC19MASK_F1_MASK                                            0x00080000
#define SEC19MASK_F1_RD(src)                         (((src) & 0x00080000)>>19)
#define SEC19MASK_F1_WR(src)                    (((u32)(src)<<19) & 0x00080000)
#define SEC19MASK_F1_SET(dst,src) \
                      (((dst) & ~0x00080000) | (((u32)(src)<<19) & 0x00080000))
/*    Mask Register Fields SEC18Mask    */
#define SEC18MASK_F1_WIDTH                                                    1
#define SEC18MASK_F1_SHIFT                                                   18
#define SEC18MASK_F1_MASK                                            0x00040000
#define SEC18MASK_F1_RD(src)                         (((src) & 0x00040000)>>18)
#define SEC18MASK_F1_WR(src)                    (((u32)(src)<<18) & 0x00040000)
#define SEC18MASK_F1_SET(dst,src) \
                      (((dst) & ~0x00040000) | (((u32)(src)<<18) & 0x00040000))
/*    Mask Register Fields SEC17Mask    */
#define SEC17MASK_F1_WIDTH                                                    1
#define SEC17MASK_F1_SHIFT                                                   17
#define SEC17MASK_F1_MASK                                            0x00020000
#define SEC17MASK_F1_RD(src)                         (((src) & 0x00020000)>>17)
#define SEC17MASK_F1_WR(src)                    (((u32)(src)<<17) & 0x00020000)
#define SEC17MASK_F1_SET(dst,src) \
                      (((dst) & ~0x00020000) | (((u32)(src)<<17) & 0x00020000))
/*    Mask Register Fields SEC16Mask    */
#define SEC16MASK_F1_WIDTH                                                    1
#define SEC16MASK_F1_SHIFT                                                   16
#define SEC16MASK_F1_MASK                                            0x00010000
#define SEC16MASK_F1_RD(src)                         (((src) & 0x00010000)>>16)
#define SEC16MASK_F1_WR(src)                    (((u32)(src)<<16) & 0x00010000)
#define SEC16MASK_F1_SET(dst,src) \
                      (((dst) & ~0x00010000) | (((u32)(src)<<16) & 0x00010000))
/*    Mask Register Fields SEC15Mask    */
#define SEC15MASK_F1_WIDTH                                                    1
#define SEC15MASK_F1_SHIFT                                                   15
#define SEC15MASK_F1_MASK                                            0x00008000
#define SEC15MASK_F1_RD(src)                         (((src) & 0x00008000)>>15)
#define SEC15MASK_F1_WR(src)                    (((u32)(src)<<15) & 0x00008000)
#define SEC15MASK_F1_SET(dst,src) \
                      (((dst) & ~0x00008000) | (((u32)(src)<<15) & 0x00008000))
/*    Mask Register Fields SEC14Mask    */
#define SEC14MASK_F1_WIDTH                                                    1
#define SEC14MASK_F1_SHIFT                                                   14
#define SEC14MASK_F1_MASK                                            0x00004000
#define SEC14MASK_F1_RD(src)                         (((src) & 0x00004000)>>14)
#define SEC14MASK_F1_WR(src)                    (((u32)(src)<<14) & 0x00004000)
#define SEC14MASK_F1_SET(dst,src) \
                      (((dst) & ~0x00004000) | (((u32)(src)<<14) & 0x00004000))
/*    Mask Register Fields SEC13Mask    */
#define SEC13MASK_F1_WIDTH                                                    1
#define SEC13MASK_F1_SHIFT                                                   13
#define SEC13MASK_F1_MASK                                            0x00002000
#define SEC13MASK_F1_RD(src)                         (((src) & 0x00002000)>>13)
#define SEC13MASK_F1_WR(src)                    (((u32)(src)<<13) & 0x00002000)
#define SEC13MASK_F1_SET(dst,src) \
                      (((dst) & ~0x00002000) | (((u32)(src)<<13) & 0x00002000))
/*    Mask Register Fields SEC12Mask    */
#define SEC12MASK_F1_WIDTH                                                    1
#define SEC12MASK_F1_SHIFT                                                   12
#define SEC12MASK_F1_MASK                                            0x00001000
#define SEC12MASK_F1_RD(src)                         (((src) & 0x00001000)>>12)
#define SEC12MASK_F1_WR(src)                    (((u32)(src)<<12) & 0x00001000)
#define SEC12MASK_F1_SET(dst,src) \
                      (((dst) & ~0x00001000) | (((u32)(src)<<12) & 0x00001000))
/*    Mask Register Fields SEC11Mask    */
#define SEC11MASK_F1_WIDTH                                                    1
#define SEC11MASK_F1_SHIFT                                                   11
#define SEC11MASK_F1_MASK                                            0x00000800
#define SEC11MASK_F1_RD(src)                         (((src) & 0x00000800)>>11)
#define SEC11MASK_F1_WR(src)                    (((u32)(src)<<11) & 0x00000800)
#define SEC11MASK_F1_SET(dst,src) \
                      (((dst) & ~0x00000800) | (((u32)(src)<<11) & 0x00000800))
/*    Mask Register Fields SEC10Mask    */
#define SEC10MASK_F1_WIDTH                                                    1
#define SEC10MASK_F1_SHIFT                                                   10
#define SEC10MASK_F1_MASK                                            0x00000400
#define SEC10MASK_F1_RD(src)                         (((src) & 0x00000400)>>10)
#define SEC10MASK_F1_WR(src)                    (((u32)(src)<<10) & 0x00000400)
#define SEC10MASK_F1_SET(dst,src) \
                      (((dst) & ~0x00000400) | (((u32)(src)<<10) & 0x00000400))
/*    Mask Register Fields SEC9Mask    */
#define SEC9MASK_F1_WIDTH                                                     1
#define SEC9MASK_F1_SHIFT                                                     9
#define SEC9MASK_F1_MASK                                             0x00000200
#define SEC9MASK_F1_RD(src)                           (((src) & 0x00000200)>>9)
#define SEC9MASK_F1_WR(src)                      (((u32)(src)<<9) & 0x00000200)
#define SEC9MASK_F1_SET(dst,src) \
                       (((dst) & ~0x00000200) | (((u32)(src)<<9) & 0x00000200))
/*    Mask Register Fields SEC8Mask    */
#define SEC8MASK_F1_WIDTH                                                     1
#define SEC8MASK_F1_SHIFT                                                     8
#define SEC8MASK_F1_MASK                                             0x00000100
#define SEC8MASK_F1_RD(src)                           (((src) & 0x00000100)>>8)
#define SEC8MASK_F1_WR(src)                      (((u32)(src)<<8) & 0x00000100)
#define SEC8MASK_F1_SET(dst,src) \
                       (((dst) & ~0x00000100) | (((u32)(src)<<8) & 0x00000100))
/*    Mask Register Fields SEC7Mask    */
#define SEC7MASK_F1_WIDTH                                                     1
#define SEC7MASK_F1_SHIFT                                                     7
#define SEC7MASK_F1_MASK                                             0x00000080
#define SEC7MASK_F1_RD(src)                           (((src) & 0x00000080)>>7)
#define SEC7MASK_F1_WR(src)                      (((u32)(src)<<7) & 0x00000080)
#define SEC7MASK_F1_SET(dst,src) \
                       (((dst) & ~0x00000080) | (((u32)(src)<<7) & 0x00000080))
/*    Mask Register Fields SEC6Mask    */
#define SEC6MASK_F1_WIDTH                                                     1
#define SEC6MASK_F1_SHIFT                                                     6
#define SEC6MASK_F1_MASK                                             0x00000040
#define SEC6MASK_F1_RD(src)                           (((src) & 0x00000040)>>6)
#define SEC6MASK_F1_WR(src)                      (((u32)(src)<<6) & 0x00000040)
#define SEC6MASK_F1_SET(dst,src) \
                       (((dst) & ~0x00000040) | (((u32)(src)<<6) & 0x00000040))
/*    Mask Register Fields SEC5Mask    */
#define SEC5MASK_F1_WIDTH                                                     1
#define SEC5MASK_F1_SHIFT                                                     5
#define SEC5MASK_F1_MASK                                             0x00000020
#define SEC5MASK_F1_RD(src)                           (((src) & 0x00000020)>>5)
#define SEC5MASK_F1_WR(src)                      (((u32)(src)<<5) & 0x00000020)
#define SEC5MASK_F1_SET(dst,src) \
                       (((dst) & ~0x00000020) | (((u32)(src)<<5) & 0x00000020))
/*    Mask Register Fields SEC4Mask    */
#define SEC4MASK_F1_WIDTH                                                     1
#define SEC4MASK_F1_SHIFT                                                     4
#define SEC4MASK_F1_MASK                                             0x00000010
#define SEC4MASK_F1_RD(src)                           (((src) & 0x00000010)>>4)
#define SEC4MASK_F1_WR(src)                      (((u32)(src)<<4) & 0x00000010)
#define SEC4MASK_F1_SET(dst,src) \
                       (((dst) & ~0x00000010) | (((u32)(src)<<4) & 0x00000010))
/*    Mask Register Fields SEC3Mask    */
#define SEC3MASK_F1_WIDTH                                                     1
#define SEC3MASK_F1_SHIFT                                                     3
#define SEC3MASK_F1_MASK                                             0x00000008
#define SEC3MASK_F1_RD(src)                           (((src) & 0x00000008)>>3)
#define SEC3MASK_F1_WR(src)                      (((u32)(src)<<3) & 0x00000008)
#define SEC3MASK_F1_SET(dst,src) \
                       (((dst) & ~0x00000008) | (((u32)(src)<<3) & 0x00000008))
/*    Mask Register Fields SEC2Mask    */
#define SEC2MASK_F1_WIDTH                                                     1
#define SEC2MASK_F1_SHIFT                                                     2
#define SEC2MASK_F1_MASK                                             0x00000004
#define SEC2MASK_F1_RD(src)                           (((src) & 0x00000004)>>2)
#define SEC2MASK_F1_WR(src)                      (((u32)(src)<<2) & 0x00000004)
#define SEC2MASK_F1_SET(dst,src) \
                       (((dst) & ~0x00000004) | (((u32)(src)<<2) & 0x00000004))
/*    Mask Register Fields SEC1Mask    */
#define SEC1MASK_F1_WIDTH                                                     1
#define SEC1MASK_F1_SHIFT                                                     1
#define SEC1MASK_F1_MASK                                             0x00000002
#define SEC1MASK_F1_RD(src)                           (((src) & 0x00000002)>>1)
#define SEC1MASK_F1_WR(src)                      (((u32)(src)<<1) & 0x00000002)
#define SEC1MASK_F1_SET(dst,src) \
                       (((dst) & ~0x00000002) | (((u32)(src)<<1) & 0x00000002))
/*    Mask Register Fields SEC0Mask    */
#define SEC0MASK_F1_WIDTH                                                     1
#define SEC0MASK_F1_SHIFT                                                     0
#define SEC0MASK_F1_MASK                                             0x00000001
#define SEC0MASK_F1_RD(src)                              (((src) & 0x00000001))
#define SEC0MASK_F1_WR(src)                         (((u32)(src)) & 0x00000001)
#define SEC0MASK_F1_SET(dst,src) \
                          (((dst) & ~0x00000001) | (((u32)(src)) & 0x00000001))

/*	Register GLBL_MSEC_ERRL	*/ 
/*	 Fields MSEC31	 */
#define MSEC31_WIDTH                                                          1
#define MSEC31_SHIFT                                                         31
#define MSEC31_MASK                                                  0x80000000
#define MSEC31_RD(src)                               (((src) & 0x80000000)>>31)
#define MSEC31_WR(src)                          (((u32)(src)<<31) & 0x80000000)
#define MSEC31_SET(dst,src) \
                      (((dst) & ~0x80000000) | (((u32)(src)<<31) & 0x80000000))
/*	 Fields MSEC30	 */
#define MSEC30_WIDTH                                                          1
#define MSEC30_SHIFT                                                         30
#define MSEC30_MASK                                                  0x40000000
#define MSEC30_RD(src)                               (((src) & 0x40000000)>>30)
#define MSEC30_WR(src)                          (((u32)(src)<<30) & 0x40000000)
#define MSEC30_SET(dst,src) \
                      (((dst) & ~0x40000000) | (((u32)(src)<<30) & 0x40000000))
/*	 Fields MSEC29	 */
#define MSEC29_WIDTH                                                          1
#define MSEC29_SHIFT                                                         29
#define MSEC29_MASK                                                  0x20000000
#define MSEC29_RD(src)                               (((src) & 0x20000000)>>29)
#define MSEC29_WR(src)                          (((u32)(src)<<29) & 0x20000000)
#define MSEC29_SET(dst,src) \
                      (((dst) & ~0x20000000) | (((u32)(src)<<29) & 0x20000000))
/*	 Fields MSEC28	 */
#define MSEC28_WIDTH                                                          1
#define MSEC28_SHIFT                                                         28
#define MSEC28_MASK                                                  0x10000000
#define MSEC28_RD(src)                               (((src) & 0x10000000)>>28)
#define MSEC28_WR(src)                          (((u32)(src)<<28) & 0x10000000)
#define MSEC28_SET(dst,src) \
                      (((dst) & ~0x10000000) | (((u32)(src)<<28) & 0x10000000))
/*	 Fields MSEC27	 */
#define MSEC27_WIDTH                                                          1
#define MSEC27_SHIFT                                                         27
#define MSEC27_MASK                                                  0x08000000
#define MSEC27_RD(src)                               (((src) & 0x08000000)>>27)
#define MSEC27_WR(src)                          (((u32)(src)<<27) & 0x08000000)
#define MSEC27_SET(dst,src) \
                      (((dst) & ~0x08000000) | (((u32)(src)<<27) & 0x08000000))
/*	 Fields MSEC26	 */
#define MSEC26_WIDTH                                                          1
#define MSEC26_SHIFT                                                         26
#define MSEC26_MASK                                                  0x04000000
#define MSEC26_RD(src)                               (((src) & 0x04000000)>>26)
#define MSEC26_WR(src)                          (((u32)(src)<<26) & 0x04000000)
#define MSEC26_SET(dst,src) \
                      (((dst) & ~0x04000000) | (((u32)(src)<<26) & 0x04000000))
/*	 Fields MSEC25	 */
#define MSEC25_WIDTH                                                          1
#define MSEC25_SHIFT                                                         25
#define MSEC25_MASK                                                  0x02000000
#define MSEC25_RD(src)                               (((src) & 0x02000000)>>25)
#define MSEC25_WR(src)                          (((u32)(src)<<25) & 0x02000000)
#define MSEC25_SET(dst,src) \
                      (((dst) & ~0x02000000) | (((u32)(src)<<25) & 0x02000000))
/*	 Fields MSEC24	 */
#define MSEC24_WIDTH                                                          1
#define MSEC24_SHIFT                                                         24
#define MSEC24_MASK                                                  0x01000000
#define MSEC24_RD(src)                               (((src) & 0x01000000)>>24)
#define MSEC24_WR(src)                          (((u32)(src)<<24) & 0x01000000)
#define MSEC24_SET(dst,src) \
                      (((dst) & ~0x01000000) | (((u32)(src)<<24) & 0x01000000))
/*	 Fields MSEC23	 */
#define MSEC23_WIDTH                                                          1
#define MSEC23_SHIFT                                                         23
#define MSEC23_MASK                                                  0x00800000
#define MSEC23_RD(src)                               (((src) & 0x00800000)>>23)
#define MSEC23_WR(src)                          (((u32)(src)<<23) & 0x00800000)
#define MSEC23_SET(dst,src) \
                      (((dst) & ~0x00800000) | (((u32)(src)<<23) & 0x00800000))
/*	 Fields MSEC22	 */
#define MSEC22_WIDTH                                                          1
#define MSEC22_SHIFT                                                         22
#define MSEC22_MASK                                                  0x00400000
#define MSEC22_RD(src)                               (((src) & 0x00400000)>>22)
#define MSEC22_WR(src)                          (((u32)(src)<<22) & 0x00400000)
#define MSEC22_SET(dst,src) \
                      (((dst) & ~0x00400000) | (((u32)(src)<<22) & 0x00400000))
/*	 Fields MSEC21	 */
#define MSEC21_WIDTH                                                          1
#define MSEC21_SHIFT                                                         21
#define MSEC21_MASK                                                  0x00200000
#define MSEC21_RD(src)                               (((src) & 0x00200000)>>21)
#define MSEC21_WR(src)                          (((u32)(src)<<21) & 0x00200000)
#define MSEC21_SET(dst,src) \
                      (((dst) & ~0x00200000) | (((u32)(src)<<21) & 0x00200000))
/*	 Fields MSEC20	 */
#define MSEC20_WIDTH                                                          1
#define MSEC20_SHIFT                                                         20
#define MSEC20_MASK                                                  0x00100000
#define MSEC20_RD(src)                               (((src) & 0x00100000)>>20)
#define MSEC20_WR(src)                          (((u32)(src)<<20) & 0x00100000)
#define MSEC20_SET(dst,src) \
                      (((dst) & ~0x00100000) | (((u32)(src)<<20) & 0x00100000))
/*	 Fields MSEC19	 */
#define MSEC19_WIDTH                                                          1
#define MSEC19_SHIFT                                                         19
#define MSEC19_MASK                                                  0x00080000
#define MSEC19_RD(src)                               (((src) & 0x00080000)>>19)
#define MSEC19_WR(src)                          (((u32)(src)<<19) & 0x00080000)
#define MSEC19_SET(dst,src) \
                      (((dst) & ~0x00080000) | (((u32)(src)<<19) & 0x00080000))
/*	 Fields MSEC18	 */
#define MSEC18_WIDTH                                                          1
#define MSEC18_SHIFT                                                         18
#define MSEC18_MASK                                                  0x00040000
#define MSEC18_RD(src)                               (((src) & 0x00040000)>>18)
#define MSEC18_WR(src)                          (((u32)(src)<<18) & 0x00040000)
#define MSEC18_SET(dst,src) \
                      (((dst) & ~0x00040000) | (((u32)(src)<<18) & 0x00040000))
/*	 Fields MSEC17	 */
#define MSEC17_WIDTH                                                          1
#define MSEC17_SHIFT                                                         17
#define MSEC17_MASK                                                  0x00020000
#define MSEC17_RD(src)                               (((src) & 0x00020000)>>17)
#define MSEC17_WR(src)                          (((u32)(src)<<17) & 0x00020000)
#define MSEC17_SET(dst,src) \
                      (((dst) & ~0x00020000) | (((u32)(src)<<17) & 0x00020000))
/*	 Fields MSEC16	 */
#define MSEC16_WIDTH                                                          1
#define MSEC16_SHIFT                                                         16
#define MSEC16_MASK                                                  0x00010000
#define MSEC16_RD(src)                               (((src) & 0x00010000)>>16)
#define MSEC16_WR(src)                          (((u32)(src)<<16) & 0x00010000)
#define MSEC16_SET(dst,src) \
                      (((dst) & ~0x00010000) | (((u32)(src)<<16) & 0x00010000))
/*	 Fields MSEC15	 */
#define MSEC15_WIDTH                                                          1
#define MSEC15_SHIFT                                                         15
#define MSEC15_MASK                                                  0x00008000
#define MSEC15_RD(src)                               (((src) & 0x00008000)>>15)
#define MSEC15_WR(src)                          (((u32)(src)<<15) & 0x00008000)
#define MSEC15_SET(dst,src) \
                      (((dst) & ~0x00008000) | (((u32)(src)<<15) & 0x00008000))
/*	 Fields MSEC14	 */
#define MSEC14_WIDTH                                                          1
#define MSEC14_SHIFT                                                         14
#define MSEC14_MASK                                                  0x00004000
#define MSEC14_RD(src)                               (((src) & 0x00004000)>>14)
#define MSEC14_WR(src)                          (((u32)(src)<<14) & 0x00004000)
#define MSEC14_SET(dst,src) \
                      (((dst) & ~0x00004000) | (((u32)(src)<<14) & 0x00004000))
/*	 Fields MSEC13	 */
#define MSEC13_WIDTH                                                          1
#define MSEC13_SHIFT                                                         13
#define MSEC13_MASK                                                  0x00002000
#define MSEC13_RD(src)                               (((src) & 0x00002000)>>13)
#define MSEC13_WR(src)                          (((u32)(src)<<13) & 0x00002000)
#define MSEC13_SET(dst,src) \
                      (((dst) & ~0x00002000) | (((u32)(src)<<13) & 0x00002000))
/*	 Fields MSEC12	 */
#define MSEC12_WIDTH                                                          1
#define MSEC12_SHIFT                                                         12
#define MSEC12_MASK                                                  0x00001000
#define MSEC12_RD(src)                               (((src) & 0x00001000)>>12)
#define MSEC12_WR(src)                          (((u32)(src)<<12) & 0x00001000)
#define MSEC12_SET(dst,src) \
                      (((dst) & ~0x00001000) | (((u32)(src)<<12) & 0x00001000))
/*	 Fields MSEC11	 */
#define MSEC11_WIDTH                                                          1
#define MSEC11_SHIFT                                                         11
#define MSEC11_MASK                                                  0x00000800
#define MSEC11_RD(src)                               (((src) & 0x00000800)>>11)
#define MSEC11_WR(src)                          (((u32)(src)<<11) & 0x00000800)
#define MSEC11_SET(dst,src) \
                      (((dst) & ~0x00000800) | (((u32)(src)<<11) & 0x00000800))
/*	 Fields MSEC10	 */
#define MSEC10_WIDTH                                                          1
#define MSEC10_SHIFT                                                         10
#define MSEC10_MASK                                                  0x00000400
#define MSEC10_RD(src)                               (((src) & 0x00000400)>>10)
#define MSEC10_WR(src)                          (((u32)(src)<<10) & 0x00000400)
#define MSEC10_SET(dst,src) \
                      (((dst) & ~0x00000400) | (((u32)(src)<<10) & 0x00000400))
/*	 Fields MSEC9	 */
#define MSEC9_WIDTH                                                           1
#define MSEC9_SHIFT                                                           9
#define MSEC9_MASK                                                   0x00000200
#define MSEC9_RD(src)                                 (((src) & 0x00000200)>>9)
#define MSEC9_WR(src)                            (((u32)(src)<<9) & 0x00000200)
#define MSEC9_SET(dst,src) \
                       (((dst) & ~0x00000200) | (((u32)(src)<<9) & 0x00000200))
/*	 Fields MSEC8	 */
#define MSEC8_WIDTH                                                           1
#define MSEC8_SHIFT                                                           8
#define MSEC8_MASK                                                   0x00000100
#define MSEC8_RD(src)                                 (((src) & 0x00000100)>>8)
#define MSEC8_WR(src)                            (((u32)(src)<<8) & 0x00000100)
#define MSEC8_SET(dst,src) \
                       (((dst) & ~0x00000100) | (((u32)(src)<<8) & 0x00000100))
/*	 Fields MSEC7	 */
#define MSEC7_WIDTH                                                           1
#define MSEC7_SHIFT                                                           7
#define MSEC7_MASK                                                   0x00000080
#define MSEC7_RD(src)                                 (((src) & 0x00000080)>>7)
#define MSEC7_WR(src)                            (((u32)(src)<<7) & 0x00000080)
#define MSEC7_SET(dst,src) \
                       (((dst) & ~0x00000080) | (((u32)(src)<<7) & 0x00000080))
/*	 Fields MSEC6	 */
#define MSEC6_WIDTH                                                           1
#define MSEC6_SHIFT                                                           6
#define MSEC6_MASK                                                   0x00000040
#define MSEC6_RD(src)                                 (((src) & 0x00000040)>>6)
#define MSEC6_WR(src)                            (((u32)(src)<<6) & 0x00000040)
#define MSEC6_SET(dst,src) \
                       (((dst) & ~0x00000040) | (((u32)(src)<<6) & 0x00000040))
/*	 Fields MSEC5	 */
#define MSEC5_WIDTH                                                           1
#define MSEC5_SHIFT                                                           5
#define MSEC5_MASK                                                   0x00000020
#define MSEC5_RD(src)                                 (((src) & 0x00000020)>>5)
#define MSEC5_WR(src)                            (((u32)(src)<<5) & 0x00000020)
#define MSEC5_SET(dst,src) \
                       (((dst) & ~0x00000020) | (((u32)(src)<<5) & 0x00000020))
/*	 Fields MSEC4	 */
#define MSEC4_WIDTH                                                           1
#define MSEC4_SHIFT                                                           4
#define MSEC4_MASK                                                   0x00000010
#define MSEC4_RD(src)                                 (((src) & 0x00000010)>>4)
#define MSEC4_WR(src)                            (((u32)(src)<<4) & 0x00000010)
#define MSEC4_SET(dst,src) \
                       (((dst) & ~0x00000010) | (((u32)(src)<<4) & 0x00000010))
/*	 Fields MSEC3	 */
#define MSEC3_WIDTH                                                           1
#define MSEC3_SHIFT                                                           3
#define MSEC3_MASK                                                   0x00000008
#define MSEC3_RD(src)                                 (((src) & 0x00000008)>>3)
#define MSEC3_WR(src)                            (((u32)(src)<<3) & 0x00000008)
#define MSEC3_SET(dst,src) \
                       (((dst) & ~0x00000008) | (((u32)(src)<<3) & 0x00000008))
/*	 Fields MSEC2	 */
#define MSEC2_WIDTH                                                           1
#define MSEC2_SHIFT                                                           2
#define MSEC2_MASK                                                   0x00000004
#define MSEC2_RD(src)                                 (((src) & 0x00000004)>>2)
#define MSEC2_WR(src)                            (((u32)(src)<<2) & 0x00000004)
#define MSEC2_SET(dst,src) \
                       (((dst) & ~0x00000004) | (((u32)(src)<<2) & 0x00000004))
/*	 Fields MSEC1	 */
#define MSEC1_WIDTH                                                           1
#define MSEC1_SHIFT                                                           1
#define MSEC1_MASK                                                   0x00000002
#define MSEC1_RD(src)                                 (((src) & 0x00000002)>>1)
#define MSEC1_WR(src)                            (((u32)(src)<<1) & 0x00000002)
#define MSEC1_SET(dst,src) \
                       (((dst) & ~0x00000002) | (((u32)(src)<<1) & 0x00000002))
/*	 Fields MSEC0	 */
#define MSEC0_WIDTH                                                           1
#define MSEC0_SHIFT                                                           0
#define MSEC0_MASK                                                   0x00000001
#define MSEC0_RD(src)                                    (((src) & 0x00000001))
#define MSEC0_WR(src)                               (((u32)(src)) & 0x00000001)
#define MSEC0_SET(dst,src) \
                          (((dst) & ~0x00000001) | (((u32)(src)) & 0x00000001))

/*	Register GLBL_MSEC_ERRLMask	*/
/*    Mask Register Fields MSEC31Mask    */
#define MSEC31MASK_WIDTH                                                      1
#define MSEC31MASK_SHIFT                                                     31
#define MSEC31MASK_MASK                                              0x80000000
#define MSEC31MASK_RD(src)                           (((src) & 0x80000000)>>31)
#define MSEC31MASK_WR(src)                      (((u32)(src)<<31) & 0x80000000)
#define MSEC31MASK_SET(dst,src) \
                      (((dst) & ~0x80000000) | (((u32)(src)<<31) & 0x80000000))
/*    Mask Register Fields MSEC30Mask    */
#define MSEC30MASK_WIDTH                                                      1
#define MSEC30MASK_SHIFT                                                     30
#define MSEC30MASK_MASK                                              0x40000000
#define MSEC30MASK_RD(src)                           (((src) & 0x40000000)>>30)
#define MSEC30MASK_WR(src)                      (((u32)(src)<<30) & 0x40000000)
#define MSEC30MASK_SET(dst,src) \
                      (((dst) & ~0x40000000) | (((u32)(src)<<30) & 0x40000000))
/*    Mask Register Fields MSEC29Mask    */
#define MSEC29MASK_WIDTH                                                      1
#define MSEC29MASK_SHIFT                                                     29
#define MSEC29MASK_MASK                                              0x20000000
#define MSEC29MASK_RD(src)                           (((src) & 0x20000000)>>29)
#define MSEC29MASK_WR(src)                      (((u32)(src)<<29) & 0x20000000)
#define MSEC29MASK_SET(dst,src) \
                      (((dst) & ~0x20000000) | (((u32)(src)<<29) & 0x20000000))
/*    Mask Register Fields MSEC28Mask    */
#define MSEC28MASK_WIDTH                                                      1
#define MSEC28MASK_SHIFT                                                     28
#define MSEC28MASK_MASK                                              0x10000000
#define MSEC28MASK_RD(src)                           (((src) & 0x10000000)>>28)
#define MSEC28MASK_WR(src)                      (((u32)(src)<<28) & 0x10000000)
#define MSEC28MASK_SET(dst,src) \
                      (((dst) & ~0x10000000) | (((u32)(src)<<28) & 0x10000000))
/*    Mask Register Fields MSEC27Mask    */
#define MSEC27MASK_WIDTH                                                      1
#define MSEC27MASK_SHIFT                                                     27
#define MSEC27MASK_MASK                                              0x08000000
#define MSEC27MASK_RD(src)                           (((src) & 0x08000000)>>27)
#define MSEC27MASK_WR(src)                      (((u32)(src)<<27) & 0x08000000)
#define MSEC27MASK_SET(dst,src) \
                      (((dst) & ~0x08000000) | (((u32)(src)<<27) & 0x08000000))
/*    Mask Register Fields MSEC26Mask    */
#define MSEC26MASK_WIDTH                                                      1
#define MSEC26MASK_SHIFT                                                     26
#define MSEC26MASK_MASK                                              0x04000000
#define MSEC26MASK_RD(src)                           (((src) & 0x04000000)>>26)
#define MSEC26MASK_WR(src)                      (((u32)(src)<<26) & 0x04000000)
#define MSEC26MASK_SET(dst,src) \
                      (((dst) & ~0x04000000) | (((u32)(src)<<26) & 0x04000000))
/*    Mask Register Fields MSEC25Mask    */
#define MSEC25MASK_WIDTH                                                      1
#define MSEC25MASK_SHIFT                                                     25
#define MSEC25MASK_MASK                                              0x02000000
#define MSEC25MASK_RD(src)                           (((src) & 0x02000000)>>25)
#define MSEC25MASK_WR(src)                      (((u32)(src)<<25) & 0x02000000)
#define MSEC25MASK_SET(dst,src) \
                      (((dst) & ~0x02000000) | (((u32)(src)<<25) & 0x02000000))
/*    Mask Register Fields MSEC24Mask    */
#define MSEC24MASK_WIDTH                                                      1
#define MSEC24MASK_SHIFT                                                     24
#define MSEC24MASK_MASK                                              0x01000000
#define MSEC24MASK_RD(src)                           (((src) & 0x01000000)>>24)
#define MSEC24MASK_WR(src)                      (((u32)(src)<<24) & 0x01000000)
#define MSEC24MASK_SET(dst,src) \
                      (((dst) & ~0x01000000) | (((u32)(src)<<24) & 0x01000000))
/*    Mask Register Fields MSEC23Mask    */
#define MSEC23MASK_WIDTH                                                      1
#define MSEC23MASK_SHIFT                                                     23
#define MSEC23MASK_MASK                                              0x00800000
#define MSEC23MASK_RD(src)                           (((src) & 0x00800000)>>23)
#define MSEC23MASK_WR(src)                      (((u32)(src)<<23) & 0x00800000)
#define MSEC23MASK_SET(dst,src) \
                      (((dst) & ~0x00800000) | (((u32)(src)<<23) & 0x00800000))
/*    Mask Register Fields MSEC22Mask    */
#define MSEC22MASK_WIDTH                                                      1
#define MSEC22MASK_SHIFT                                                     22
#define MSEC22MASK_MASK                                              0x00400000
#define MSEC22MASK_RD(src)                           (((src) & 0x00400000)>>22)
#define MSEC22MASK_WR(src)                      (((u32)(src)<<22) & 0x00400000)
#define MSEC22MASK_SET(dst,src) \
                      (((dst) & ~0x00400000) | (((u32)(src)<<22) & 0x00400000))
/*    Mask Register Fields MSEC21Mask    */
#define MSEC21MASK_WIDTH                                                      1
#define MSEC21MASK_SHIFT                                                     21
#define MSEC21MASK_MASK                                              0x00200000
#define MSEC21MASK_RD(src)                           (((src) & 0x00200000)>>21)
#define MSEC21MASK_WR(src)                      (((u32)(src)<<21) & 0x00200000)
#define MSEC21MASK_SET(dst,src) \
                      (((dst) & ~0x00200000) | (((u32)(src)<<21) & 0x00200000))
/*    Mask Register Fields MSEC20Mask    */
#define MSEC20MASK_WIDTH                                                      1
#define MSEC20MASK_SHIFT                                                     20
#define MSEC20MASK_MASK                                              0x00100000
#define MSEC20MASK_RD(src)                           (((src) & 0x00100000)>>20)
#define MSEC20MASK_WR(src)                      (((u32)(src)<<20) & 0x00100000)
#define MSEC20MASK_SET(dst,src) \
                      (((dst) & ~0x00100000) | (((u32)(src)<<20) & 0x00100000))
/*    Mask Register Fields MSEC19Mask    */
#define MSEC19MASK_WIDTH                                                      1
#define MSEC19MASK_SHIFT                                                     19
#define MSEC19MASK_MASK                                              0x00080000
#define MSEC19MASK_RD(src)                           (((src) & 0x00080000)>>19)
#define MSEC19MASK_WR(src)                      (((u32)(src)<<19) & 0x00080000)
#define MSEC19MASK_SET(dst,src) \
                      (((dst) & ~0x00080000) | (((u32)(src)<<19) & 0x00080000))
/*    Mask Register Fields MSEC18Mask    */
#define MSEC18MASK_WIDTH                                                      1
#define MSEC18MASK_SHIFT                                                     18
#define MSEC18MASK_MASK                                              0x00040000
#define MSEC18MASK_RD(src)                           (((src) & 0x00040000)>>18)
#define MSEC18MASK_WR(src)                      (((u32)(src)<<18) & 0x00040000)
#define MSEC18MASK_SET(dst,src) \
                      (((dst) & ~0x00040000) | (((u32)(src)<<18) & 0x00040000))
/*    Mask Register Fields MSEC17Mask    */
#define MSEC17MASK_WIDTH                                                      1
#define MSEC17MASK_SHIFT                                                     17
#define MSEC17MASK_MASK                                              0x00020000
#define MSEC17MASK_RD(src)                           (((src) & 0x00020000)>>17)
#define MSEC17MASK_WR(src)                      (((u32)(src)<<17) & 0x00020000)
#define MSEC17MASK_SET(dst,src) \
                      (((dst) & ~0x00020000) | (((u32)(src)<<17) & 0x00020000))
/*    Mask Register Fields MSEC16Mask    */
#define MSEC16MASK_WIDTH                                                      1
#define MSEC16MASK_SHIFT                                                     16
#define MSEC16MASK_MASK                                              0x00010000
#define MSEC16MASK_RD(src)                           (((src) & 0x00010000)>>16)
#define MSEC16MASK_WR(src)                      (((u32)(src)<<16) & 0x00010000)
#define MSEC16MASK_SET(dst,src) \
                      (((dst) & ~0x00010000) | (((u32)(src)<<16) & 0x00010000))
/*    Mask Register Fields MSEC15Mask    */
#define MSEC15MASK_WIDTH                                                      1
#define MSEC15MASK_SHIFT                                                     15
#define MSEC15MASK_MASK                                              0x00008000
#define MSEC15MASK_RD(src)                           (((src) & 0x00008000)>>15)
#define MSEC15MASK_WR(src)                      (((u32)(src)<<15) & 0x00008000)
#define MSEC15MASK_SET(dst,src) \
                      (((dst) & ~0x00008000) | (((u32)(src)<<15) & 0x00008000))
/*    Mask Register Fields MSEC14Mask    */
#define MSEC14MASK_WIDTH                                                      1
#define MSEC14MASK_SHIFT                                                     14
#define MSEC14MASK_MASK                                              0x00004000
#define MSEC14MASK_RD(src)                           (((src) & 0x00004000)>>14)
#define MSEC14MASK_WR(src)                      (((u32)(src)<<14) & 0x00004000)
#define MSEC14MASK_SET(dst,src) \
                      (((dst) & ~0x00004000) | (((u32)(src)<<14) & 0x00004000))
/*    Mask Register Fields MSEC13Mask    */
#define MSEC13MASK_WIDTH                                                      1
#define MSEC13MASK_SHIFT                                                     13
#define MSEC13MASK_MASK                                              0x00002000
#define MSEC13MASK_RD(src)                           (((src) & 0x00002000)>>13)
#define MSEC13MASK_WR(src)                      (((u32)(src)<<13) & 0x00002000)
#define MSEC13MASK_SET(dst,src) \
                      (((dst) & ~0x00002000) | (((u32)(src)<<13) & 0x00002000))
/*    Mask Register Fields MSEC12Mask    */
#define MSEC12MASK_WIDTH                                                      1
#define MSEC12MASK_SHIFT                                                     12
#define MSEC12MASK_MASK                                              0x00001000
#define MSEC12MASK_RD(src)                           (((src) & 0x00001000)>>12)
#define MSEC12MASK_WR(src)                      (((u32)(src)<<12) & 0x00001000)
#define MSEC12MASK_SET(dst,src) \
                      (((dst) & ~0x00001000) | (((u32)(src)<<12) & 0x00001000))
/*    Mask Register Fields MSEC11Mask    */
#define MSEC11MASK_WIDTH                                                      1
#define MSEC11MASK_SHIFT                                                     11
#define MSEC11MASK_MASK                                              0x00000800
#define MSEC11MASK_RD(src)                           (((src) & 0x00000800)>>11)
#define MSEC11MASK_WR(src)                      (((u32)(src)<<11) & 0x00000800)
#define MSEC11MASK_SET(dst,src) \
                      (((dst) & ~0x00000800) | (((u32)(src)<<11) & 0x00000800))
/*    Mask Register Fields MSEC10Mask    */
#define MSEC10MASK_WIDTH                                                      1
#define MSEC10MASK_SHIFT                                                     10
#define MSEC10MASK_MASK                                              0x00000400
#define MSEC10MASK_RD(src)                           (((src) & 0x00000400)>>10)
#define MSEC10MASK_WR(src)                      (((u32)(src)<<10) & 0x00000400)
#define MSEC10MASK_SET(dst,src) \
                      (((dst) & ~0x00000400) | (((u32)(src)<<10) & 0x00000400))
/*    Mask Register Fields MSEC9Mask    */
#define MSEC9MASK_WIDTH                                                       1
#define MSEC9MASK_SHIFT                                                       9
#define MSEC9MASK_MASK                                               0x00000200
#define MSEC9MASK_RD(src)                             (((src) & 0x00000200)>>9)
#define MSEC9MASK_WR(src)                        (((u32)(src)<<9) & 0x00000200)
#define MSEC9MASK_SET(dst,src) \
                       (((dst) & ~0x00000200) | (((u32)(src)<<9) & 0x00000200))
/*    Mask Register Fields MSEC8Mask    */
#define MSEC8MASK_WIDTH                                                       1
#define MSEC8MASK_SHIFT                                                       8
#define MSEC8MASK_MASK                                               0x00000100
#define MSEC8MASK_RD(src)                             (((src) & 0x00000100)>>8)
#define MSEC8MASK_WR(src)                        (((u32)(src)<<8) & 0x00000100)
#define MSEC8MASK_SET(dst,src) \
                       (((dst) & ~0x00000100) | (((u32)(src)<<8) & 0x00000100))
/*    Mask Register Fields MSEC7Mask    */
#define MSEC7MASK_WIDTH                                                       1
#define MSEC7MASK_SHIFT                                                       7
#define MSEC7MASK_MASK                                               0x00000080
#define MSEC7MASK_RD(src)                             (((src) & 0x00000080)>>7)
#define MSEC7MASK_WR(src)                        (((u32)(src)<<7) & 0x00000080)
#define MSEC7MASK_SET(dst,src) \
                       (((dst) & ~0x00000080) | (((u32)(src)<<7) & 0x00000080))
/*    Mask Register Fields MSEC6Mask    */
#define MSEC6MASK_WIDTH                                                       1
#define MSEC6MASK_SHIFT                                                       6
#define MSEC6MASK_MASK                                               0x00000040
#define MSEC6MASK_RD(src)                             (((src) & 0x00000040)>>6)
#define MSEC6MASK_WR(src)                        (((u32)(src)<<6) & 0x00000040)
#define MSEC6MASK_SET(dst,src) \
                       (((dst) & ~0x00000040) | (((u32)(src)<<6) & 0x00000040))
/*    Mask Register Fields MSEC5Mask    */
#define MSEC5MASK_WIDTH                                                       1
#define MSEC5MASK_SHIFT                                                       5
#define MSEC5MASK_MASK                                               0x00000020
#define MSEC5MASK_RD(src)                             (((src) & 0x00000020)>>5)
#define MSEC5MASK_WR(src)                        (((u32)(src)<<5) & 0x00000020)
#define MSEC5MASK_SET(dst,src) \
                       (((dst) & ~0x00000020) | (((u32)(src)<<5) & 0x00000020))
/*    Mask Register Fields MSEC4Mask    */
#define MSEC4MASK_WIDTH                                                       1
#define MSEC4MASK_SHIFT                                                       4
#define MSEC4MASK_MASK                                               0x00000010
#define MSEC4MASK_RD(src)                             (((src) & 0x00000010)>>4)
#define MSEC4MASK_WR(src)                        (((u32)(src)<<4) & 0x00000010)
#define MSEC4MASK_SET(dst,src) \
                       (((dst) & ~0x00000010) | (((u32)(src)<<4) & 0x00000010))
/*    Mask Register Fields MSEC3Mask    */
#define MSEC3MASK_WIDTH                                                       1
#define MSEC3MASK_SHIFT                                                       3
#define MSEC3MASK_MASK                                               0x00000008
#define MSEC3MASK_RD(src)                             (((src) & 0x00000008)>>3)
#define MSEC3MASK_WR(src)                        (((u32)(src)<<3) & 0x00000008)
#define MSEC3MASK_SET(dst,src) \
                       (((dst) & ~0x00000008) | (((u32)(src)<<3) & 0x00000008))
/*    Mask Register Fields MSEC2Mask    */
#define MSEC2MASK_WIDTH                                                       1
#define MSEC2MASK_SHIFT                                                       2
#define MSEC2MASK_MASK                                               0x00000004
#define MSEC2MASK_RD(src)                             (((src) & 0x00000004)>>2)
#define MSEC2MASK_WR(src)                        (((u32)(src)<<2) & 0x00000004)
#define MSEC2MASK_SET(dst,src) \
                       (((dst) & ~0x00000004) | (((u32)(src)<<2) & 0x00000004))
/*    Mask Register Fields MSEC1Mask    */
#define MSEC1MASK_WIDTH                                                       1
#define MSEC1MASK_SHIFT                                                       1
#define MSEC1MASK_MASK                                               0x00000002
#define MSEC1MASK_RD(src)                             (((src) & 0x00000002)>>1)
#define MSEC1MASK_WR(src)                        (((u32)(src)<<1) & 0x00000002)
#define MSEC1MASK_SET(dst,src) \
                       (((dst) & ~0x00000002) | (((u32)(src)<<1) & 0x00000002))
/*    Mask Register Fields MSEC0Mask    */
#define MSEC0MASK_WIDTH                                                       1
#define MSEC0MASK_SHIFT                                                       0
#define MSEC0MASK_MASK                                               0x00000001
#define MSEC0MASK_RD(src)                                (((src) & 0x00000001))
#define MSEC0MASK_WR(src)                           (((u32)(src)) & 0x00000001)
#define MSEC0MASK_SET(dst,src) \
                          (((dst) & ~0x00000001) | (((u32)(src)) & 0x00000001))

/*	Register GLBL_MSEC_ERRH	*/ 
/*	 Fields MSEC63	 */
#define MSEC63_WIDTH                                                          1
#define MSEC63_SHIFT                                                         31
#define MSEC63_MASK                                                  0x80000000
#define MSEC63_RD(src)                               (((src) & 0x80000000)>>31)
#define MSEC63_WR(src)                          (((u32)(src)<<31) & 0x80000000)
#define MSEC63_SET(dst,src) \
                      (((dst) & ~0x80000000) | (((u32)(src)<<31) & 0x80000000))
/*	 Fields MSEC62	 */
#define MSEC62_WIDTH                                                          1
#define MSEC62_SHIFT                                                         30
#define MSEC62_MASK                                                  0x40000000
#define MSEC62_RD(src)                               (((src) & 0x40000000)>>30)
#define MSEC62_WR(src)                          (((u32)(src)<<30) & 0x40000000)
#define MSEC62_SET(dst,src) \
                      (((dst) & ~0x40000000) | (((u32)(src)<<30) & 0x40000000))
/*	 Fields MSEC61	 */
#define MSEC61_WIDTH                                                          1
#define MSEC61_SHIFT                                                         29
#define MSEC61_MASK                                                  0x20000000
#define MSEC61_RD(src)                               (((src) & 0x20000000)>>29)
#define MSEC61_WR(src)                          (((u32)(src)<<29) & 0x20000000)
#define MSEC61_SET(dst,src) \
                      (((dst) & ~0x20000000) | (((u32)(src)<<29) & 0x20000000))
/*	 Fields MSEC60	 */
#define MSEC60_WIDTH                                                          1
#define MSEC60_SHIFT                                                         28
#define MSEC60_MASK                                                  0x10000000
#define MSEC60_RD(src)                               (((src) & 0x10000000)>>28)
#define MSEC60_WR(src)                          (((u32)(src)<<28) & 0x10000000)
#define MSEC60_SET(dst,src) \
                      (((dst) & ~0x10000000) | (((u32)(src)<<28) & 0x10000000))
/*	 Fields MSEC59	 */
#define MSEC59_WIDTH                                                          1
#define MSEC59_SHIFT                                                         27
#define MSEC59_MASK                                                  0x08000000
#define MSEC59_RD(src)                               (((src) & 0x08000000)>>27)
#define MSEC59_WR(src)                          (((u32)(src)<<27) & 0x08000000)
#define MSEC59_SET(dst,src) \
                      (((dst) & ~0x08000000) | (((u32)(src)<<27) & 0x08000000))
/*	 Fields MSEC58	 */
#define MSEC58_WIDTH                                                          1
#define MSEC58_SHIFT                                                         26
#define MSEC58_MASK                                                  0x04000000
#define MSEC58_RD(src)                               (((src) & 0x04000000)>>26)
#define MSEC58_WR(src)                          (((u32)(src)<<26) & 0x04000000)
#define MSEC58_SET(dst,src) \
                      (((dst) & ~0x04000000) | (((u32)(src)<<26) & 0x04000000))
/*	 Fields MSEC57	 */
#define MSEC57_WIDTH                                                          1
#define MSEC57_SHIFT                                                         25
#define MSEC57_MASK                                                  0x02000000
#define MSEC57_RD(src)                               (((src) & 0x02000000)>>25)
#define MSEC57_WR(src)                          (((u32)(src)<<25) & 0x02000000)
#define MSEC57_SET(dst,src) \
                      (((dst) & ~0x02000000) | (((u32)(src)<<25) & 0x02000000))
/*	 Fields MSEC56	 */
#define MSEC56_WIDTH                                                          1
#define MSEC56_SHIFT                                                         24
#define MSEC56_MASK                                                  0x01000000
#define MSEC56_RD(src)                               (((src) & 0x01000000)>>24)
#define MSEC56_WR(src)                          (((u32)(src)<<24) & 0x01000000)
#define MSEC56_SET(dst,src) \
                      (((dst) & ~0x01000000) | (((u32)(src)<<24) & 0x01000000))
/*	 Fields MSEC55	 */
#define MSEC55_WIDTH                                                          1
#define MSEC55_SHIFT                                                         23
#define MSEC55_MASK                                                  0x00800000
#define MSEC55_RD(src)                               (((src) & 0x00800000)>>23)
#define MSEC55_WR(src)                          (((u32)(src)<<23) & 0x00800000)
#define MSEC55_SET(dst,src) \
                      (((dst) & ~0x00800000) | (((u32)(src)<<23) & 0x00800000))
/*	 Fields MSEC54	 */
#define MSEC54_WIDTH                                                          1
#define MSEC54_SHIFT                                                         22
#define MSEC54_MASK                                                  0x00400000
#define MSEC54_RD(src)                               (((src) & 0x00400000)>>22)
#define MSEC54_WR(src)                          (((u32)(src)<<22) & 0x00400000)
#define MSEC54_SET(dst,src) \
                      (((dst) & ~0x00400000) | (((u32)(src)<<22) & 0x00400000))
/*	 Fields MSEC53	 */
#define MSEC53_WIDTH                                                          1
#define MSEC53_SHIFT                                                         21
#define MSEC53_MASK                                                  0x00200000
#define MSEC53_RD(src)                               (((src) & 0x00200000)>>21)
#define MSEC53_WR(src)                          (((u32)(src)<<21) & 0x00200000)
#define MSEC53_SET(dst,src) \
                      (((dst) & ~0x00200000) | (((u32)(src)<<21) & 0x00200000))
/*	 Fields MSEC52	 */
#define MSEC52_WIDTH                                                          1
#define MSEC52_SHIFT                                                         20
#define MSEC52_MASK                                                  0x00100000
#define MSEC52_RD(src)                               (((src) & 0x00100000)>>20)
#define MSEC52_WR(src)                          (((u32)(src)<<20) & 0x00100000)
#define MSEC52_SET(dst,src) \
                      (((dst) & ~0x00100000) | (((u32)(src)<<20) & 0x00100000))
/*	 Fields MSEC51	 */
#define MSEC51_WIDTH                                                          1
#define MSEC51_SHIFT                                                         19
#define MSEC51_MASK                                                  0x00080000
#define MSEC51_RD(src)                               (((src) & 0x00080000)>>19)
#define MSEC51_WR(src)                          (((u32)(src)<<19) & 0x00080000)
#define MSEC51_SET(dst,src) \
                      (((dst) & ~0x00080000) | (((u32)(src)<<19) & 0x00080000))
/*	 Fields MSEC50	 */
#define MSEC50_WIDTH                                                          1
#define MSEC50_SHIFT                                                         18
#define MSEC50_MASK                                                  0x00040000
#define MSEC50_RD(src)                               (((src) & 0x00040000)>>18)
#define MSEC50_WR(src)                          (((u32)(src)<<18) & 0x00040000)
#define MSEC50_SET(dst,src) \
                      (((dst) & ~0x00040000) | (((u32)(src)<<18) & 0x00040000))
/*	 Fields MSEC49	 */
#define MSEC49_WIDTH                                                          1
#define MSEC49_SHIFT                                                         17
#define MSEC49_MASK                                                  0x00020000
#define MSEC49_RD(src)                               (((src) & 0x00020000)>>17)
#define MSEC49_WR(src)                          (((u32)(src)<<17) & 0x00020000)
#define MSEC49_SET(dst,src) \
                      (((dst) & ~0x00020000) | (((u32)(src)<<17) & 0x00020000))
/*	 Fields MSEC48	 */
#define MSEC48_WIDTH                                                          1
#define MSEC48_SHIFT                                                         16
#define MSEC48_MASK                                                  0x00010000
#define MSEC48_RD(src)                               (((src) & 0x00010000)>>16)
#define MSEC48_WR(src)                          (((u32)(src)<<16) & 0x00010000)
#define MSEC48_SET(dst,src) \
                      (((dst) & ~0x00010000) | (((u32)(src)<<16) & 0x00010000))
/*	 Fields MSEC47	 */
#define MSEC47_WIDTH                                                          1
#define MSEC47_SHIFT                                                         15
#define MSEC47_MASK                                                  0x00008000
#define MSEC47_RD(src)                               (((src) & 0x00008000)>>15)
#define MSEC47_WR(src)                          (((u32)(src)<<15) & 0x00008000)
#define MSEC47_SET(dst,src) \
                      (((dst) & ~0x00008000) | (((u32)(src)<<15) & 0x00008000))
/*	 Fields MSEC46	 */
#define MSEC46_WIDTH                                                          1
#define MSEC46_SHIFT                                                         14
#define MSEC46_MASK                                                  0x00004000
#define MSEC46_RD(src)                               (((src) & 0x00004000)>>14)
#define MSEC46_WR(src)                          (((u32)(src)<<14) & 0x00004000)
#define MSEC46_SET(dst,src) \
                      (((dst) & ~0x00004000) | (((u32)(src)<<14) & 0x00004000))
/*	 Fields MSEC45	 */
#define MSEC45_WIDTH                                                          1
#define MSEC45_SHIFT                                                         13
#define MSEC45_MASK                                                  0x00002000
#define MSEC45_RD(src)                               (((src) & 0x00002000)>>13)
#define MSEC45_WR(src)                          (((u32)(src)<<13) & 0x00002000)
#define MSEC45_SET(dst,src) \
                      (((dst) & ~0x00002000) | (((u32)(src)<<13) & 0x00002000))
/*	 Fields MSEC44	 */
#define MSEC44_WIDTH                                                          1
#define MSEC44_SHIFT                                                         12
#define MSEC44_MASK                                                  0x00001000
#define MSEC44_RD(src)                               (((src) & 0x00001000)>>12)
#define MSEC44_WR(src)                          (((u32)(src)<<12) & 0x00001000)
#define MSEC44_SET(dst,src) \
                      (((dst) & ~0x00001000) | (((u32)(src)<<12) & 0x00001000))
/*	 Fields MSEC43	 */
#define MSEC43_WIDTH                                                          1
#define MSEC43_SHIFT                                                         11
#define MSEC43_MASK                                                  0x00000800
#define MSEC43_RD(src)                               (((src) & 0x00000800)>>11)
#define MSEC43_WR(src)                          (((u32)(src)<<11) & 0x00000800)
#define MSEC43_SET(dst,src) \
                      (((dst) & ~0x00000800) | (((u32)(src)<<11) & 0x00000800))
/*	 Fields MSEC42	 */
#define MSEC42_WIDTH                                                          1
#define MSEC42_SHIFT                                                         10
#define MSEC42_MASK                                                  0x00000400
#define MSEC42_RD(src)                               (((src) & 0x00000400)>>10)
#define MSEC42_WR(src)                          (((u32)(src)<<10) & 0x00000400)
#define MSEC42_SET(dst,src) \
                      (((dst) & ~0x00000400) | (((u32)(src)<<10) & 0x00000400))
/*	 Fields MSEC41	 */
#define MSEC41_WIDTH                                                          1
#define MSEC41_SHIFT                                                          9
#define MSEC41_MASK                                                  0x00000200
#define MSEC41_RD(src)                                (((src) & 0x00000200)>>9)
#define MSEC41_WR(src)                           (((u32)(src)<<9) & 0x00000200)
#define MSEC41_SET(dst,src) \
                       (((dst) & ~0x00000200) | (((u32)(src)<<9) & 0x00000200))
/*	 Fields MSEC40	 */
#define MSEC40_WIDTH                                                          1
#define MSEC40_SHIFT                                                          8
#define MSEC40_MASK                                                  0x00000100
#define MSEC40_RD(src)                                (((src) & 0x00000100)>>8)
#define MSEC40_WR(src)                           (((u32)(src)<<8) & 0x00000100)
#define MSEC40_SET(dst,src) \
                       (((dst) & ~0x00000100) | (((u32)(src)<<8) & 0x00000100))
/*	 Fields MSEC39	 */
#define MSEC39_WIDTH                                                          1
#define MSEC39_SHIFT                                                          7
#define MSEC39_MASK                                                  0x00000080
#define MSEC39_RD(src)                                (((src) & 0x00000080)>>7)
#define MSEC39_WR(src)                           (((u32)(src)<<7) & 0x00000080)
#define MSEC39_SET(dst,src) \
                       (((dst) & ~0x00000080) | (((u32)(src)<<7) & 0x00000080))
/*	 Fields MSEC38	 */
#define MSEC38_WIDTH                                                          1
#define MSEC38_SHIFT                                                          6
#define MSEC38_MASK                                                  0x00000040
#define MSEC38_RD(src)                                (((src) & 0x00000040)>>6)
#define MSEC38_WR(src)                           (((u32)(src)<<6) & 0x00000040)
#define MSEC38_SET(dst,src) \
                       (((dst) & ~0x00000040) | (((u32)(src)<<6) & 0x00000040))
/*	 Fields MSEC37	 */
#define MSEC37_WIDTH                                                          1
#define MSEC37_SHIFT                                                          5
#define MSEC37_MASK                                                  0x00000020
#define MSEC37_RD(src)                                (((src) & 0x00000020)>>5)
#define MSEC37_WR(src)                           (((u32)(src)<<5) & 0x00000020)
#define MSEC37_SET(dst,src) \
                       (((dst) & ~0x00000020) | (((u32)(src)<<5) & 0x00000020))
/*	 Fields MSEC36	 */
#define MSEC36_WIDTH                                                          1
#define MSEC36_SHIFT                                                          4
#define MSEC36_MASK                                                  0x00000010
#define MSEC36_RD(src)                                (((src) & 0x00000010)>>4)
#define MSEC36_WR(src)                           (((u32)(src)<<4) & 0x00000010)
#define MSEC36_SET(dst,src) \
                       (((dst) & ~0x00000010) | (((u32)(src)<<4) & 0x00000010))
/*	 Fields MSEC35	 */
#define MSEC35_WIDTH                                                          1
#define MSEC35_SHIFT                                                          3
#define MSEC35_MASK                                                  0x00000008
#define MSEC35_RD(src)                                (((src) & 0x00000008)>>3)
#define MSEC35_WR(src)                           (((u32)(src)<<3) & 0x00000008)
#define MSEC35_SET(dst,src) \
                       (((dst) & ~0x00000008) | (((u32)(src)<<3) & 0x00000008))
/*	 Fields MSEC34	 */
#define MSEC34_WIDTH                                                          1
#define MSEC34_SHIFT                                                          2
#define MSEC34_MASK                                                  0x00000004
#define MSEC34_RD(src)                                (((src) & 0x00000004)>>2)
#define MSEC34_WR(src)                           (((u32)(src)<<2) & 0x00000004)
#define MSEC34_SET(dst,src) \
                       (((dst) & ~0x00000004) | (((u32)(src)<<2) & 0x00000004))
/*	 Fields MSEC33	 */
#define MSEC33_WIDTH                                                          1
#define MSEC33_SHIFT                                                          1
#define MSEC33_MASK                                                  0x00000002
#define MSEC33_RD(src)                                (((src) & 0x00000002)>>1)
#define MSEC33_WR(src)                           (((u32)(src)<<1) & 0x00000002)
#define MSEC33_SET(dst,src) \
                       (((dst) & ~0x00000002) | (((u32)(src)<<1) & 0x00000002))
/*	 Fields MSEC32	 */
#define MSEC32_WIDTH                                                          1
#define MSEC32_SHIFT                                                          0
#define MSEC32_MASK                                                  0x00000001
#define MSEC32_RD(src)                                   (((src) & 0x00000001))
#define MSEC32_WR(src)                              (((u32)(src)) & 0x00000001)
#define MSEC32_SET(dst,src) \
                          (((dst) & ~0x00000001) | (((u32)(src)) & 0x00000001))

/*	Register GLBL_MSEC_ERRHMask	*/
/*    Mask Register Fields MSEC63Mask    */
#define MSEC63MASK_WIDTH                                                      1
#define MSEC63MASK_SHIFT                                                     31
#define MSEC63MASK_MASK                                              0x80000000
#define MSEC63MASK_RD(src)                           (((src) & 0x80000000)>>31)
#define MSEC63MASK_WR(src)                      (((u32)(src)<<31) & 0x80000000)
#define MSEC63MASK_SET(dst,src) \
                      (((dst) & ~0x80000000) | (((u32)(src)<<31) & 0x80000000))
/*    Mask Register Fields MSEC62Mask    */
#define MSEC62MASK_WIDTH                                                      1
#define MSEC62MASK_SHIFT                                                     30
#define MSEC62MASK_MASK                                              0x40000000
#define MSEC62MASK_RD(src)                           (((src) & 0x40000000)>>30)
#define MSEC62MASK_WR(src)                      (((u32)(src)<<30) & 0x40000000)
#define MSEC62MASK_SET(dst,src) \
                      (((dst) & ~0x40000000) | (((u32)(src)<<30) & 0x40000000))
/*    Mask Register Fields MSEC61Mask    */
#define MSEC61MASK_WIDTH                                                      1
#define MSEC61MASK_SHIFT                                                     29
#define MSEC61MASK_MASK                                              0x20000000
#define MSEC61MASK_RD(src)                           (((src) & 0x20000000)>>29)
#define MSEC61MASK_WR(src)                      (((u32)(src)<<29) & 0x20000000)
#define MSEC61MASK_SET(dst,src) \
                      (((dst) & ~0x20000000) | (((u32)(src)<<29) & 0x20000000))
/*    Mask Register Fields MSEC60Mask    */
#define MSEC60MASK_WIDTH                                                      1
#define MSEC60MASK_SHIFT                                                     28
#define MSEC60MASK_MASK                                              0x10000000
#define MSEC60MASK_RD(src)                           (((src) & 0x10000000)>>28)
#define MSEC60MASK_WR(src)                      (((u32)(src)<<28) & 0x10000000)
#define MSEC60MASK_SET(dst,src) \
                      (((dst) & ~0x10000000) | (((u32)(src)<<28) & 0x10000000))
/*    Mask Register Fields MSEC59Mask    */
#define MSEC59MASK_WIDTH                                                      1
#define MSEC59MASK_SHIFT                                                     27
#define MSEC59MASK_MASK                                              0x08000000
#define MSEC59MASK_RD(src)                           (((src) & 0x08000000)>>27)
#define MSEC59MASK_WR(src)                      (((u32)(src)<<27) & 0x08000000)
#define MSEC59MASK_SET(dst,src) \
                      (((dst) & ~0x08000000) | (((u32)(src)<<27) & 0x08000000))
/*    Mask Register Fields MSEC58Mask    */
#define MSEC58MASK_WIDTH                                                      1
#define MSEC58MASK_SHIFT                                                     26
#define MSEC58MASK_MASK                                              0x04000000
#define MSEC58MASK_RD(src)                           (((src) & 0x04000000)>>26)
#define MSEC58MASK_WR(src)                      (((u32)(src)<<26) & 0x04000000)
#define MSEC58MASK_SET(dst,src) \
                      (((dst) & ~0x04000000) | (((u32)(src)<<26) & 0x04000000))
/*    Mask Register Fields MSEC57Mask    */
#define MSEC57MASK_WIDTH                                                      1
#define MSEC57MASK_SHIFT                                                     25
#define MSEC57MASK_MASK                                              0x02000000
#define MSEC57MASK_RD(src)                           (((src) & 0x02000000)>>25)
#define MSEC57MASK_WR(src)                      (((u32)(src)<<25) & 0x02000000)
#define MSEC57MASK_SET(dst,src) \
                      (((dst) & ~0x02000000) | (((u32)(src)<<25) & 0x02000000))
/*    Mask Register Fields MSEC56Mask    */
#define MSEC56MASK_WIDTH                                                      1
#define MSEC56MASK_SHIFT                                                     24
#define MSEC56MASK_MASK                                              0x01000000
#define MSEC56MASK_RD(src)                           (((src) & 0x01000000)>>24)
#define MSEC56MASK_WR(src)                      (((u32)(src)<<24) & 0x01000000)
#define MSEC56MASK_SET(dst,src) \
                      (((dst) & ~0x01000000) | (((u32)(src)<<24) & 0x01000000))
/*    Mask Register Fields MSEC55Mask    */
#define MSEC55MASK_WIDTH                                                      1
#define MSEC55MASK_SHIFT                                                     23
#define MSEC55MASK_MASK                                              0x00800000
#define MSEC55MASK_RD(src)                           (((src) & 0x00800000)>>23)
#define MSEC55MASK_WR(src)                      (((u32)(src)<<23) & 0x00800000)
#define MSEC55MASK_SET(dst,src) \
                      (((dst) & ~0x00800000) | (((u32)(src)<<23) & 0x00800000))
/*    Mask Register Fields MSEC54Mask    */
#define MSEC54MASK_WIDTH                                                      1
#define MSEC54MASK_SHIFT                                                     22
#define MSEC54MASK_MASK                                              0x00400000
#define MSEC54MASK_RD(src)                           (((src) & 0x00400000)>>22)
#define MSEC54MASK_WR(src)                      (((u32)(src)<<22) & 0x00400000)
#define MSEC54MASK_SET(dst,src) \
                      (((dst) & ~0x00400000) | (((u32)(src)<<22) & 0x00400000))
/*    Mask Register Fields MSEC53Mask    */
#define MSEC53MASK_WIDTH                                                      1
#define MSEC53MASK_SHIFT                                                     21
#define MSEC53MASK_MASK                                              0x00200000
#define MSEC53MASK_RD(src)                           (((src) & 0x00200000)>>21)
#define MSEC53MASK_WR(src)                      (((u32)(src)<<21) & 0x00200000)
#define MSEC53MASK_SET(dst,src) \
                      (((dst) & ~0x00200000) | (((u32)(src)<<21) & 0x00200000))
/*    Mask Register Fields MSEC52Mask    */
#define MSEC52MASK_WIDTH                                                      1
#define MSEC52MASK_SHIFT                                                     20
#define MSEC52MASK_MASK                                              0x00100000
#define MSEC52MASK_RD(src)                           (((src) & 0x00100000)>>20)
#define MSEC52MASK_WR(src)                      (((u32)(src)<<20) & 0x00100000)
#define MSEC52MASK_SET(dst,src) \
                      (((dst) & ~0x00100000) | (((u32)(src)<<20) & 0x00100000))
/*    Mask Register Fields MSEC51Mask    */
#define MSEC51MASK_WIDTH                                                      1
#define MSEC51MASK_SHIFT                                                     19
#define MSEC51MASK_MASK                                              0x00080000
#define MSEC51MASK_RD(src)                           (((src) & 0x00080000)>>19)
#define MSEC51MASK_WR(src)                      (((u32)(src)<<19) & 0x00080000)
#define MSEC51MASK_SET(dst,src) \
                      (((dst) & ~0x00080000) | (((u32)(src)<<19) & 0x00080000))
/*    Mask Register Fields MSEC50Mask    */
#define MSEC50MASK_WIDTH                                                      1
#define MSEC50MASK_SHIFT                                                     18
#define MSEC50MASK_MASK                                              0x00040000
#define MSEC50MASK_RD(src)                           (((src) & 0x00040000)>>18)
#define MSEC50MASK_WR(src)                      (((u32)(src)<<18) & 0x00040000)
#define MSEC50MASK_SET(dst,src) \
                      (((dst) & ~0x00040000) | (((u32)(src)<<18) & 0x00040000))
/*    Mask Register Fields MSEC49Mask    */
#define MSEC49MASK_WIDTH                                                      1
#define MSEC49MASK_SHIFT                                                     17
#define MSEC49MASK_MASK                                              0x00020000
#define MSEC49MASK_RD(src)                           (((src) & 0x00020000)>>17)
#define MSEC49MASK_WR(src)                      (((u32)(src)<<17) & 0x00020000)
#define MSEC49MASK_SET(dst,src) \
                      (((dst) & ~0x00020000) | (((u32)(src)<<17) & 0x00020000))
/*    Mask Register Fields MSEC48Mask    */
#define MSEC48MASK_WIDTH                                                      1
#define MSEC48MASK_SHIFT                                                     16
#define MSEC48MASK_MASK                                              0x00010000
#define MSEC48MASK_RD(src)                           (((src) & 0x00010000)>>16)
#define MSEC48MASK_WR(src)                      (((u32)(src)<<16) & 0x00010000)
#define MSEC48MASK_SET(dst,src) \
                      (((dst) & ~0x00010000) | (((u32)(src)<<16) & 0x00010000))
/*    Mask Register Fields MSEC47Mask    */
#define MSEC47MASK_WIDTH                                                      1
#define MSEC47MASK_SHIFT                                                     15
#define MSEC47MASK_MASK                                              0x00008000
#define MSEC47MASK_RD(src)                           (((src) & 0x00008000)>>15)
#define MSEC47MASK_WR(src)                      (((u32)(src)<<15) & 0x00008000)
#define MSEC47MASK_SET(dst,src) \
                      (((dst) & ~0x00008000) | (((u32)(src)<<15) & 0x00008000))
/*    Mask Register Fields MSEC46Mask    */
#define MSEC46MASK_WIDTH                                                      1
#define MSEC46MASK_SHIFT                                                     14
#define MSEC46MASK_MASK                                              0x00004000
#define MSEC46MASK_RD(src)                           (((src) & 0x00004000)>>14)
#define MSEC46MASK_WR(src)                      (((u32)(src)<<14) & 0x00004000)
#define MSEC46MASK_SET(dst,src) \
                      (((dst) & ~0x00004000) | (((u32)(src)<<14) & 0x00004000))
/*    Mask Register Fields MSEC45Mask    */
#define MSEC45MASK_WIDTH                                                      1
#define MSEC45MASK_SHIFT                                                     13
#define MSEC45MASK_MASK                                              0x00002000
#define MSEC45MASK_RD(src)                           (((src) & 0x00002000)>>13)
#define MSEC45MASK_WR(src)                      (((u32)(src)<<13) & 0x00002000)
#define MSEC45MASK_SET(dst,src) \
                      (((dst) & ~0x00002000) | (((u32)(src)<<13) & 0x00002000))
/*    Mask Register Fields MSEC44Mask    */
#define MSEC44MASK_WIDTH                                                      1
#define MSEC44MASK_SHIFT                                                     12
#define MSEC44MASK_MASK                                              0x00001000
#define MSEC44MASK_RD(src)                           (((src) & 0x00001000)>>12)
#define MSEC44MASK_WR(src)                      (((u32)(src)<<12) & 0x00001000)
#define MSEC44MASK_SET(dst,src) \
                      (((dst) & ~0x00001000) | (((u32)(src)<<12) & 0x00001000))
/*    Mask Register Fields MSEC43Mask    */
#define MSEC43MASK_WIDTH                                                      1
#define MSEC43MASK_SHIFT                                                     11
#define MSEC43MASK_MASK                                              0x00000800
#define MSEC43MASK_RD(src)                           (((src) & 0x00000800)>>11)
#define MSEC43MASK_WR(src)                      (((u32)(src)<<11) & 0x00000800)
#define MSEC43MASK_SET(dst,src) \
                      (((dst) & ~0x00000800) | (((u32)(src)<<11) & 0x00000800))
/*    Mask Register Fields MSEC42Mask    */
#define MSEC42MASK_WIDTH                                                      1
#define MSEC42MASK_SHIFT                                                     10
#define MSEC42MASK_MASK                                              0x00000400
#define MSEC42MASK_RD(src)                           (((src) & 0x00000400)>>10)
#define MSEC42MASK_WR(src)                      (((u32)(src)<<10) & 0x00000400)
#define MSEC42MASK_SET(dst,src) \
                      (((dst) & ~0x00000400) | (((u32)(src)<<10) & 0x00000400))
/*    Mask Register Fields MSEC41Mask    */
#define MSEC41MASK_WIDTH                                                      1
#define MSEC41MASK_SHIFT                                                      9
#define MSEC41MASK_MASK                                              0x00000200
#define MSEC41MASK_RD(src)                            (((src) & 0x00000200)>>9)
#define MSEC41MASK_WR(src)                       (((u32)(src)<<9) & 0x00000200)
#define MSEC41MASK_SET(dst,src) \
                       (((dst) & ~0x00000200) | (((u32)(src)<<9) & 0x00000200))
/*    Mask Register Fields MSEC40Mask    */
#define MSEC40MASK_WIDTH                                                      1
#define MSEC40MASK_SHIFT                                                      8
#define MSEC40MASK_MASK                                              0x00000100
#define MSEC40MASK_RD(src)                            (((src) & 0x00000100)>>8)
#define MSEC40MASK_WR(src)                       (((u32)(src)<<8) & 0x00000100)
#define MSEC40MASK_SET(dst,src) \
                       (((dst) & ~0x00000100) | (((u32)(src)<<8) & 0x00000100))
/*    Mask Register Fields MSEC39Mask    */
#define MSEC39MASK_WIDTH                                                      1
#define MSEC39MASK_SHIFT                                                      7
#define MSEC39MASK_MASK                                              0x00000080
#define MSEC39MASK_RD(src)                            (((src) & 0x00000080)>>7)
#define MSEC39MASK_WR(src)                       (((u32)(src)<<7) & 0x00000080)
#define MSEC39MASK_SET(dst,src) \
                       (((dst) & ~0x00000080) | (((u32)(src)<<7) & 0x00000080))
/*    Mask Register Fields MSEC38Mask    */
#define MSEC38MASK_WIDTH                                                      1
#define MSEC38MASK_SHIFT                                                      6
#define MSEC38MASK_MASK                                              0x00000040
#define MSEC38MASK_RD(src)                            (((src) & 0x00000040)>>6)
#define MSEC38MASK_WR(src)                       (((u32)(src)<<6) & 0x00000040)
#define MSEC38MASK_SET(dst,src) \
                       (((dst) & ~0x00000040) | (((u32)(src)<<6) & 0x00000040))
/*    Mask Register Fields MSEC37Mask    */
#define MSEC37MASK_WIDTH                                                      1
#define MSEC37MASK_SHIFT                                                      5
#define MSEC37MASK_MASK                                              0x00000020
#define MSEC37MASK_RD(src)                            (((src) & 0x00000020)>>5)
#define MSEC37MASK_WR(src)                       (((u32)(src)<<5) & 0x00000020)
#define MSEC37MASK_SET(dst,src) \
                       (((dst) & ~0x00000020) | (((u32)(src)<<5) & 0x00000020))
/*    Mask Register Fields MSEC36Mask    */
#define MSEC36MASK_WIDTH                                                      1
#define MSEC36MASK_SHIFT                                                      4
#define MSEC36MASK_MASK                                              0x00000010
#define MSEC36MASK_RD(src)                            (((src) & 0x00000010)>>4)
#define MSEC36MASK_WR(src)                       (((u32)(src)<<4) & 0x00000010)
#define MSEC36MASK_SET(dst,src) \
                       (((dst) & ~0x00000010) | (((u32)(src)<<4) & 0x00000010))
/*    Mask Register Fields MSEC35Mask    */
#define MSEC35MASK_WIDTH                                                      1
#define MSEC35MASK_SHIFT                                                      3
#define MSEC35MASK_MASK                                              0x00000008
#define MSEC35MASK_RD(src)                            (((src) & 0x00000008)>>3)
#define MSEC35MASK_WR(src)                       (((u32)(src)<<3) & 0x00000008)
#define MSEC35MASK_SET(dst,src) \
                       (((dst) & ~0x00000008) | (((u32)(src)<<3) & 0x00000008))
/*    Mask Register Fields MSEC34Mask    */
#define MSEC34MASK_WIDTH                                                      1
#define MSEC34MASK_SHIFT                                                      2
#define MSEC34MASK_MASK                                              0x00000004
#define MSEC34MASK_RD(src)                            (((src) & 0x00000004)>>2)
#define MSEC34MASK_WR(src)                       (((u32)(src)<<2) & 0x00000004)
#define MSEC34MASK_SET(dst,src) \
                       (((dst) & ~0x00000004) | (((u32)(src)<<2) & 0x00000004))
/*    Mask Register Fields MSEC33Mask    */
#define MSEC33MASK_WIDTH                                                      1
#define MSEC33MASK_SHIFT                                                      1
#define MSEC33MASK_MASK                                              0x00000002
#define MSEC33MASK_RD(src)                            (((src) & 0x00000002)>>1)
#define MSEC33MASK_WR(src)                       (((u32)(src)<<1) & 0x00000002)
#define MSEC33MASK_SET(dst,src) \
                       (((dst) & ~0x00000002) | (((u32)(src)<<1) & 0x00000002))
/*    Mask Register Fields MSEC32Mask    */
#define MSEC32MASK_WIDTH                                                      1
#define MSEC32MASK_SHIFT                                                      0
#define MSEC32MASK_MASK                                              0x00000001
#define MSEC32MASK_RD(src)                               (((src) & 0x00000001))
#define MSEC32MASK_WR(src)                          (((u32)(src)) & 0x00000001)
#define MSEC32MASK_SET(dst,src) \
                          (((dst) & ~0x00000001) | (((u32)(src)) & 0x00000001))

/*	Register GLBL_DED_ERRL	*/ 
/*	 Fields DED31	 */
#define DED31_WIDTH                                                           1
#define DED31_SHIFT                                                          31
#define DED31_MASK                                                   0x80000000
#define DED31_RD(src)                                (((src) & 0x80000000)>>31)
#define DED31_WR(src)                           (((u32)(src)<<31) & 0x80000000)
#define DED31_SET(dst,src) \
                      (((dst) & ~0x80000000) | (((u32)(src)<<31) & 0x80000000))
/*	 Fields DED30	 */
#define DED30_WIDTH                                                           1
#define DED30_SHIFT                                                          30
#define DED30_MASK                                                   0x40000000
#define DED30_RD(src)                                (((src) & 0x40000000)>>30)
#define DED30_WR(src)                           (((u32)(src)<<30) & 0x40000000)
#define DED30_SET(dst,src) \
                      (((dst) & ~0x40000000) | (((u32)(src)<<30) & 0x40000000))
/*	 Fields DED29	 */
#define DED29_WIDTH                                                           1
#define DED29_SHIFT                                                          29
#define DED29_MASK                                                   0x20000000
#define DED29_RD(src)                                (((src) & 0x20000000)>>29)
#define DED29_WR(src)                           (((u32)(src)<<29) & 0x20000000)
#define DED29_SET(dst,src) \
                      (((dst) & ~0x20000000) | (((u32)(src)<<29) & 0x20000000))
/*	 Fields DED28	 */
#define DED28_WIDTH                                                           1
#define DED28_SHIFT                                                          28
#define DED28_MASK                                                   0x10000000
#define DED28_RD(src)                                (((src) & 0x10000000)>>28)
#define DED28_WR(src)                           (((u32)(src)<<28) & 0x10000000)
#define DED28_SET(dst,src) \
                      (((dst) & ~0x10000000) | (((u32)(src)<<28) & 0x10000000))
/*	 Fields DED27	 */
#define DED27_WIDTH                                                           1
#define DED27_SHIFT                                                          27
#define DED27_MASK                                                   0x08000000
#define DED27_RD(src)                                (((src) & 0x08000000)>>27)
#define DED27_WR(src)                           (((u32)(src)<<27) & 0x08000000)
#define DED27_SET(dst,src) \
                      (((dst) & ~0x08000000) | (((u32)(src)<<27) & 0x08000000))
/*	 Fields DED26	 */
#define DED26_WIDTH                                                           1
#define DED26_SHIFT                                                          26
#define DED26_MASK                                                   0x04000000
#define DED26_RD(src)                                (((src) & 0x04000000)>>26)
#define DED26_WR(src)                           (((u32)(src)<<26) & 0x04000000)
#define DED26_SET(dst,src) \
                      (((dst) & ~0x04000000) | (((u32)(src)<<26) & 0x04000000))
/*	 Fields DED25	 */
#define DED25_WIDTH                                                           1
#define DED25_SHIFT                                                          25
#define DED25_MASK                                                   0x02000000
#define DED25_RD(src)                                (((src) & 0x02000000)>>25)
#define DED25_WR(src)                           (((u32)(src)<<25) & 0x02000000)
#define DED25_SET(dst,src) \
                      (((dst) & ~0x02000000) | (((u32)(src)<<25) & 0x02000000))
/*	 Fields DED24	 */
#define DED24_WIDTH                                                           1
#define DED24_SHIFT                                                          24
#define DED24_MASK                                                   0x01000000
#define DED24_RD(src)                                (((src) & 0x01000000)>>24)
#define DED24_WR(src)                           (((u32)(src)<<24) & 0x01000000)
#define DED24_SET(dst,src) \
                      (((dst) & ~0x01000000) | (((u32)(src)<<24) & 0x01000000))
/*	 Fields DED23	 */
#define DED23_WIDTH                                                           1
#define DED23_SHIFT                                                          23
#define DED23_MASK                                                   0x00800000
#define DED23_RD(src)                                (((src) & 0x00800000)>>23)
#define DED23_WR(src)                           (((u32)(src)<<23) & 0x00800000)
#define DED23_SET(dst,src) \
                      (((dst) & ~0x00800000) | (((u32)(src)<<23) & 0x00800000))
/*	 Fields DED22	 */
#define DED22_WIDTH                                                           1
#define DED22_SHIFT                                                          22
#define DED22_MASK                                                   0x00400000
#define DED22_RD(src)                                (((src) & 0x00400000)>>22)
#define DED22_WR(src)                           (((u32)(src)<<22) & 0x00400000)
#define DED22_SET(dst,src) \
                      (((dst) & ~0x00400000) | (((u32)(src)<<22) & 0x00400000))
/*	 Fields DED21	 */
#define DED21_WIDTH                                                           1
#define DED21_SHIFT                                                          21
#define DED21_MASK                                                   0x00200000
#define DED21_RD(src)                                (((src) & 0x00200000)>>21)
#define DED21_WR(src)                           (((u32)(src)<<21) & 0x00200000)
#define DED21_SET(dst,src) \
                      (((dst) & ~0x00200000) | (((u32)(src)<<21) & 0x00200000))
/*	 Fields DED20	 */
#define DED20_WIDTH                                                           1
#define DED20_SHIFT                                                          20
#define DED20_MASK                                                   0x00100000
#define DED20_RD(src)                                (((src) & 0x00100000)>>20)
#define DED20_WR(src)                           (((u32)(src)<<20) & 0x00100000)
#define DED20_SET(dst,src) \
                      (((dst) & ~0x00100000) | (((u32)(src)<<20) & 0x00100000))
/*	 Fields DED19	 */
#define DED19_WIDTH                                                           1
#define DED19_SHIFT                                                          19
#define DED19_MASK                                                   0x00080000
#define DED19_RD(src)                                (((src) & 0x00080000)>>19)
#define DED19_WR(src)                           (((u32)(src)<<19) & 0x00080000)
#define DED19_SET(dst,src) \
                      (((dst) & ~0x00080000) | (((u32)(src)<<19) & 0x00080000))
/*	 Fields DED18	 */
#define DED18_WIDTH                                                           1
#define DED18_SHIFT                                                          18
#define DED18_MASK                                                   0x00040000
#define DED18_RD(src)                                (((src) & 0x00040000)>>18)
#define DED18_WR(src)                           (((u32)(src)<<18) & 0x00040000)
#define DED18_SET(dst,src) \
                      (((dst) & ~0x00040000) | (((u32)(src)<<18) & 0x00040000))
/*	 Fields DED17	 */
#define DED17_WIDTH                                                           1
#define DED17_SHIFT                                                          17
#define DED17_MASK                                                   0x00020000
#define DED17_RD(src)                                (((src) & 0x00020000)>>17)
#define DED17_WR(src)                           (((u32)(src)<<17) & 0x00020000)
#define DED17_SET(dst,src) \
                      (((dst) & ~0x00020000) | (((u32)(src)<<17) & 0x00020000))
/*	 Fields DED16	 */
#define DED16_WIDTH                                                           1
#define DED16_SHIFT                                                          16
#define DED16_MASK                                                   0x00010000
#define DED16_RD(src)                                (((src) & 0x00010000)>>16)
#define DED16_WR(src)                           (((u32)(src)<<16) & 0x00010000)
#define DED16_SET(dst,src) \
                      (((dst) & ~0x00010000) | (((u32)(src)<<16) & 0x00010000))
/*	 Fields DED15	 */
#define DED15_WIDTH                                                           1
#define DED15_SHIFT                                                          15
#define DED15_MASK                                                   0x00008000
#define DED15_RD(src)                                (((src) & 0x00008000)>>15)
#define DED15_WR(src)                           (((u32)(src)<<15) & 0x00008000)
#define DED15_SET(dst,src) \
                      (((dst) & ~0x00008000) | (((u32)(src)<<15) & 0x00008000))
/*	 Fields DED14	 */
#define DED14_WIDTH                                                           1
#define DED14_SHIFT                                                          14
#define DED14_MASK                                                   0x00004000
#define DED14_RD(src)                                (((src) & 0x00004000)>>14)
#define DED14_WR(src)                           (((u32)(src)<<14) & 0x00004000)
#define DED14_SET(dst,src) \
                      (((dst) & ~0x00004000) | (((u32)(src)<<14) & 0x00004000))
/*	 Fields DED13	 */
#define DED13_WIDTH                                                           1
#define DED13_SHIFT                                                          13
#define DED13_MASK                                                   0x00002000
#define DED13_RD(src)                                (((src) & 0x00002000)>>13)
#define DED13_WR(src)                           (((u32)(src)<<13) & 0x00002000)
#define DED13_SET(dst,src) \
                      (((dst) & ~0x00002000) | (((u32)(src)<<13) & 0x00002000))
/*	 Fields DED12	 */
#define DED12_WIDTH                                                           1
#define DED12_SHIFT                                                          12
#define DED12_MASK                                                   0x00001000
#define DED12_RD(src)                                (((src) & 0x00001000)>>12)
#define DED12_WR(src)                           (((u32)(src)<<12) & 0x00001000)
#define DED12_SET(dst,src) \
                      (((dst) & ~0x00001000) | (((u32)(src)<<12) & 0x00001000))
/*	 Fields DED11	 */
#define DED11_WIDTH                                                           1
#define DED11_SHIFT                                                          11
#define DED11_MASK                                                   0x00000800
#define DED11_RD(src)                                (((src) & 0x00000800)>>11)
#define DED11_WR(src)                           (((u32)(src)<<11) & 0x00000800)
#define DED11_SET(dst,src) \
                      (((dst) & ~0x00000800) | (((u32)(src)<<11) & 0x00000800))
/*	 Fields DED10	 */
#define DED10_WIDTH                                                           1
#define DED10_SHIFT                                                          10
#define DED10_MASK                                                   0x00000400
#define DED10_RD(src)                                (((src) & 0x00000400)>>10)
#define DED10_WR(src)                           (((u32)(src)<<10) & 0x00000400)
#define DED10_SET(dst,src) \
                      (((dst) & ~0x00000400) | (((u32)(src)<<10) & 0x00000400))
/*	 Fields DED9	 */
#define DED9_WIDTH                                                            1
#define DED9_SHIFT                                                            9
#define DED9_MASK                                                    0x00000200
#define DED9_RD(src)                                  (((src) & 0x00000200)>>9)
#define DED9_WR(src)                             (((u32)(src)<<9) & 0x00000200)
#define DED9_SET(dst,src) \
                       (((dst) & ~0x00000200) | (((u32)(src)<<9) & 0x00000200))
/*	 Fields DED8	 */
#define DED8_WIDTH                                                            1
#define DED8_SHIFT                                                            8
#define DED8_MASK                                                    0x00000100
#define DED8_RD(src)                                  (((src) & 0x00000100)>>8)
#define DED8_WR(src)                             (((u32)(src)<<8) & 0x00000100)
#define DED8_SET(dst,src) \
                       (((dst) & ~0x00000100) | (((u32)(src)<<8) & 0x00000100))
/*	 Fields DED7	 */
#define DED7_WIDTH                                                            1
#define DED7_SHIFT                                                            7
#define DED7_MASK                                                    0x00000080
#define DED7_RD(src)                                  (((src) & 0x00000080)>>7)
#define DED7_WR(src)                             (((u32)(src)<<7) & 0x00000080)
#define DED7_SET(dst,src) \
                       (((dst) & ~0x00000080) | (((u32)(src)<<7) & 0x00000080))
/*	 Fields DED6	 */
#define DED6_WIDTH                                                            1
#define DED6_SHIFT                                                            6
#define DED6_MASK                                                    0x00000040
#define DED6_RD(src)                                  (((src) & 0x00000040)>>6)
#define DED6_WR(src)                             (((u32)(src)<<6) & 0x00000040)
#define DED6_SET(dst,src) \
                       (((dst) & ~0x00000040) | (((u32)(src)<<6) & 0x00000040))
/*	 Fields DED5	 */
#define DED5_WIDTH                                                            1
#define DED5_SHIFT                                                            5
#define DED5_MASK                                                    0x00000020
#define DED5_RD(src)                                  (((src) & 0x00000020)>>5)
#define DED5_WR(src)                             (((u32)(src)<<5) & 0x00000020)
#define DED5_SET(dst,src) \
                       (((dst) & ~0x00000020) | (((u32)(src)<<5) & 0x00000020))
/*	 Fields DED4	 */
#define DED4_WIDTH                                                            1
#define DED4_SHIFT                                                            4
#define DED4_MASK                                                    0x00000010
#define DED4_RD(src)                                  (((src) & 0x00000010)>>4)
#define DED4_WR(src)                             (((u32)(src)<<4) & 0x00000010)
#define DED4_SET(dst,src) \
                       (((dst) & ~0x00000010) | (((u32)(src)<<4) & 0x00000010))
/*	 Fields DED3	 */
#define DED3_WIDTH                                                            1
#define DED3_SHIFT                                                            3
#define DED3_MASK                                                    0x00000008
#define DED3_RD(src)                                  (((src) & 0x00000008)>>3)
#define DED3_WR(src)                             (((u32)(src)<<3) & 0x00000008)
#define DED3_SET(dst,src) \
                       (((dst) & ~0x00000008) | (((u32)(src)<<3) & 0x00000008))
/*	 Fields DED2	 */
#define DED2_WIDTH                                                            1
#define DED2_SHIFT                                                            2
#define DED2_MASK                                                    0x00000004
#define DED2_RD(src)                                  (((src) & 0x00000004)>>2)
#define DED2_WR(src)                             (((u32)(src)<<2) & 0x00000004)
#define DED2_SET(dst,src) \
                       (((dst) & ~0x00000004) | (((u32)(src)<<2) & 0x00000004))
/*	 Fields DED1	 */
#define DED1_WIDTH                                                            1
#define DED1_SHIFT                                                            1
#define DED1_MASK                                                    0x00000002
#define DED1_RD(src)                                  (((src) & 0x00000002)>>1)
#define DED1_WR(src)                             (((u32)(src)<<1) & 0x00000002)
#define DED1_SET(dst,src) \
                       (((dst) & ~0x00000002) | (((u32)(src)<<1) & 0x00000002))
/*	 Fields DED0	 */
#define DED0_WIDTH                                                            1
#define DED0_SHIFT                                                            0
#define DED0_MASK                                                    0x00000001
#define DED0_RD(src)                                     (((src) & 0x00000001))
#define DED0_WR(src)                                (((u32)(src)) & 0x00000001)
#define DED0_SET(dst,src) \
                          (((dst) & ~0x00000001) | (((u32)(src)) & 0x00000001))

/*	Register GLBL_DED_ERRLMask	*/
/*    Mask Register Fields DED31Mask    */
#define DED31MASK_WIDTH                                                       1
#define DED31MASK_SHIFT                                                      31
#define DED31MASK_MASK                                               0x80000000
#define DED31MASK_RD(src)                            (((src) & 0x80000000)>>31)
#define DED31MASK_WR(src)                       (((u32)(src)<<31) & 0x80000000)
#define DED31MASK_SET(dst,src) \
                      (((dst) & ~0x80000000) | (((u32)(src)<<31) & 0x80000000))
/*    Mask Register Fields DED30Mask    */
#define DED30MASK_WIDTH                                                       1
#define DED30MASK_SHIFT                                                      30
#define DED30MASK_MASK                                               0x40000000
#define DED30MASK_RD(src)                            (((src) & 0x40000000)>>30)
#define DED30MASK_WR(src)                       (((u32)(src)<<30) & 0x40000000)
#define DED30MASK_SET(dst,src) \
                      (((dst) & ~0x40000000) | (((u32)(src)<<30) & 0x40000000))
/*    Mask Register Fields DED29Mask    */
#define DED29MASK_WIDTH                                                       1
#define DED29MASK_SHIFT                                                      29
#define DED29MASK_MASK                                               0x20000000
#define DED29MASK_RD(src)                            (((src) & 0x20000000)>>29)
#define DED29MASK_WR(src)                       (((u32)(src)<<29) & 0x20000000)
#define DED29MASK_SET(dst,src) \
                      (((dst) & ~0x20000000) | (((u32)(src)<<29) & 0x20000000))
/*    Mask Register Fields DED28Mask    */
#define DED28MASK_WIDTH                                                       1
#define DED28MASK_SHIFT                                                      28
#define DED28MASK_MASK                                               0x10000000
#define DED28MASK_RD(src)                            (((src) & 0x10000000)>>28)
#define DED28MASK_WR(src)                       (((u32)(src)<<28) & 0x10000000)
#define DED28MASK_SET(dst,src) \
                      (((dst) & ~0x10000000) | (((u32)(src)<<28) & 0x10000000))
/*    Mask Register Fields DED27Mask    */
#define DED27MASK_WIDTH                                                       1
#define DED27MASK_SHIFT                                                      27
#define DED27MASK_MASK                                               0x08000000
#define DED27MASK_RD(src)                            (((src) & 0x08000000)>>27)
#define DED27MASK_WR(src)                       (((u32)(src)<<27) & 0x08000000)
#define DED27MASK_SET(dst,src) \
                      (((dst) & ~0x08000000) | (((u32)(src)<<27) & 0x08000000))
/*    Mask Register Fields DED26Mask    */
#define DED26MASK_WIDTH                                                       1
#define DED26MASK_SHIFT                                                      26
#define DED26MASK_MASK                                               0x04000000
#define DED26MASK_RD(src)                            (((src) & 0x04000000)>>26)
#define DED26MASK_WR(src)                       (((u32)(src)<<26) & 0x04000000)
#define DED26MASK_SET(dst,src) \
                      (((dst) & ~0x04000000) | (((u32)(src)<<26) & 0x04000000))
/*    Mask Register Fields DED25Mask    */
#define DED25MASK_WIDTH                                                       1
#define DED25MASK_SHIFT                                                      25
#define DED25MASK_MASK                                               0x02000000
#define DED25MASK_RD(src)                            (((src) & 0x02000000)>>25)
#define DED25MASK_WR(src)                       (((u32)(src)<<25) & 0x02000000)
#define DED25MASK_SET(dst,src) \
                      (((dst) & ~0x02000000) | (((u32)(src)<<25) & 0x02000000))
/*    Mask Register Fields DED24Mask    */
#define DED24MASK_WIDTH                                                       1
#define DED24MASK_SHIFT                                                      24
#define DED24MASK_MASK                                               0x01000000
#define DED24MASK_RD(src)                            (((src) & 0x01000000)>>24)
#define DED24MASK_WR(src)                       (((u32)(src)<<24) & 0x01000000)
#define DED24MASK_SET(dst,src) \
                      (((dst) & ~0x01000000) | (((u32)(src)<<24) & 0x01000000))
/*    Mask Register Fields DED23Mask    */
#define DED23MASK_WIDTH                                                       1
#define DED23MASK_SHIFT                                                      23
#define DED23MASK_MASK                                               0x00800000
#define DED23MASK_RD(src)                            (((src) & 0x00800000)>>23)
#define DED23MASK_WR(src)                       (((u32)(src)<<23) & 0x00800000)
#define DED23MASK_SET(dst,src) \
                      (((dst) & ~0x00800000) | (((u32)(src)<<23) & 0x00800000))
/*    Mask Register Fields DED22Mask    */
#define DED22MASK_WIDTH                                                       1
#define DED22MASK_SHIFT                                                      22
#define DED22MASK_MASK                                               0x00400000
#define DED22MASK_RD(src)                            (((src) & 0x00400000)>>22)
#define DED22MASK_WR(src)                       (((u32)(src)<<22) & 0x00400000)
#define DED22MASK_SET(dst,src) \
                      (((dst) & ~0x00400000) | (((u32)(src)<<22) & 0x00400000))
/*    Mask Register Fields DED21Mask    */
#define DED21MASK_WIDTH                                                       1
#define DED21MASK_SHIFT                                                      21
#define DED21MASK_MASK                                               0x00200000
#define DED21MASK_RD(src)                            (((src) & 0x00200000)>>21)
#define DED21MASK_WR(src)                       (((u32)(src)<<21) & 0x00200000)
#define DED21MASK_SET(dst,src) \
                      (((dst) & ~0x00200000) | (((u32)(src)<<21) & 0x00200000))
/*    Mask Register Fields DED20Mask    */
#define DED20MASK_WIDTH                                                       1
#define DED20MASK_SHIFT                                                      20
#define DED20MASK_MASK                                               0x00100000
#define DED20MASK_RD(src)                            (((src) & 0x00100000)>>20)
#define DED20MASK_WR(src)                       (((u32)(src)<<20) & 0x00100000)
#define DED20MASK_SET(dst,src) \
                      (((dst) & ~0x00100000) | (((u32)(src)<<20) & 0x00100000))
/*    Mask Register Fields DED19Mask    */
#define DED19MASK_WIDTH                                                       1
#define DED19MASK_SHIFT                                                      19
#define DED19MASK_MASK                                               0x00080000
#define DED19MASK_RD(src)                            (((src) & 0x00080000)>>19)
#define DED19MASK_WR(src)                       (((u32)(src)<<19) & 0x00080000)
#define DED19MASK_SET(dst,src) \
                      (((dst) & ~0x00080000) | (((u32)(src)<<19) & 0x00080000))
/*    Mask Register Fields DED18Mask    */
#define DED18MASK_WIDTH                                                       1
#define DED18MASK_SHIFT                                                      18
#define DED18MASK_MASK                                               0x00040000
#define DED18MASK_RD(src)                            (((src) & 0x00040000)>>18)
#define DED18MASK_WR(src)                       (((u32)(src)<<18) & 0x00040000)
#define DED18MASK_SET(dst,src) \
                      (((dst) & ~0x00040000) | (((u32)(src)<<18) & 0x00040000))
/*    Mask Register Fields DED17Mask    */
#define DED17MASK_WIDTH                                                       1
#define DED17MASK_SHIFT                                                      17
#define DED17MASK_MASK                                               0x00020000
#define DED17MASK_RD(src)                            (((src) & 0x00020000)>>17)
#define DED17MASK_WR(src)                       (((u32)(src)<<17) & 0x00020000)
#define DED17MASK_SET(dst,src) \
                      (((dst) & ~0x00020000) | (((u32)(src)<<17) & 0x00020000))
/*    Mask Register Fields DED16Mask    */
#define DED16MASK_WIDTH                                                       1
#define DED16MASK_SHIFT                                                      16
#define DED16MASK_MASK                                               0x00010000
#define DED16MASK_RD(src)                            (((src) & 0x00010000)>>16)
#define DED16MASK_WR(src)                       (((u32)(src)<<16) & 0x00010000)
#define DED16MASK_SET(dst,src) \
                      (((dst) & ~0x00010000) | (((u32)(src)<<16) & 0x00010000))
/*    Mask Register Fields DED15Mask    */
#define DED15MASK_WIDTH                                                       1
#define DED15MASK_SHIFT                                                      15
#define DED15MASK_MASK                                               0x00008000
#define DED15MASK_RD(src)                            (((src) & 0x00008000)>>15)
#define DED15MASK_WR(src)                       (((u32)(src)<<15) & 0x00008000)
#define DED15MASK_SET(dst,src) \
                      (((dst) & ~0x00008000) | (((u32)(src)<<15) & 0x00008000))
/*    Mask Register Fields DED14Mask    */
#define DED14MASK_WIDTH                                                       1
#define DED14MASK_SHIFT                                                      14
#define DED14MASK_MASK                                               0x00004000
#define DED14MASK_RD(src)                            (((src) & 0x00004000)>>14)
#define DED14MASK_WR(src)                       (((u32)(src)<<14) & 0x00004000)
#define DED14MASK_SET(dst,src) \
                      (((dst) & ~0x00004000) | (((u32)(src)<<14) & 0x00004000))
/*    Mask Register Fields DED13Mask    */
#define DED13MASK_WIDTH                                                       1
#define DED13MASK_SHIFT                                                      13
#define DED13MASK_MASK                                               0x00002000
#define DED13MASK_RD(src)                            (((src) & 0x00002000)>>13)
#define DED13MASK_WR(src)                       (((u32)(src)<<13) & 0x00002000)
#define DED13MASK_SET(dst,src) \
                      (((dst) & ~0x00002000) | (((u32)(src)<<13) & 0x00002000))
/*    Mask Register Fields DED12Mask    */
#define DED12MASK_WIDTH                                                       1
#define DED12MASK_SHIFT                                                      12
#define DED12MASK_MASK                                               0x00001000
#define DED12MASK_RD(src)                            (((src) & 0x00001000)>>12)
#define DED12MASK_WR(src)                       (((u32)(src)<<12) & 0x00001000)
#define DED12MASK_SET(dst,src) \
                      (((dst) & ~0x00001000) | (((u32)(src)<<12) & 0x00001000))
/*    Mask Register Fields DED11Mask    */
#define DED11MASK_WIDTH                                                       1
#define DED11MASK_SHIFT                                                      11
#define DED11MASK_MASK                                               0x00000800
#define DED11MASK_RD(src)                            (((src) & 0x00000800)>>11)
#define DED11MASK_WR(src)                       (((u32)(src)<<11) & 0x00000800)
#define DED11MASK_SET(dst,src) \
                      (((dst) & ~0x00000800) | (((u32)(src)<<11) & 0x00000800))
/*    Mask Register Fields DED10Mask    */
#define DED10MASK_WIDTH                                                       1
#define DED10MASK_SHIFT                                                      10
#define DED10MASK_MASK                                               0x00000400
#define DED10MASK_RD(src)                            (((src) & 0x00000400)>>10)
#define DED10MASK_WR(src)                       (((u32)(src)<<10) & 0x00000400)
#define DED10MASK_SET(dst,src) \
                      (((dst) & ~0x00000400) | (((u32)(src)<<10) & 0x00000400))
/*    Mask Register Fields DED9Mask    */
#define DED9MASK_WIDTH                                                        1
#define DED9MASK_SHIFT                                                        9
#define DED9MASK_MASK                                                0x00000200
#define DED9MASK_RD(src)                              (((src) & 0x00000200)>>9)
#define DED9MASK_WR(src)                         (((u32)(src)<<9) & 0x00000200)
#define DED9MASK_SET(dst,src) \
                       (((dst) & ~0x00000200) | (((u32)(src)<<9) & 0x00000200))
/*    Mask Register Fields DED8Mask    */
#define DED8MASK_WIDTH                                                        1
#define DED8MASK_SHIFT                                                        8
#define DED8MASK_MASK                                                0x00000100
#define DED8MASK_RD(src)                              (((src) & 0x00000100)>>8)
#define DED8MASK_WR(src)                         (((u32)(src)<<8) & 0x00000100)
#define DED8MASK_SET(dst,src) \
                       (((dst) & ~0x00000100) | (((u32)(src)<<8) & 0x00000100))
/*    Mask Register Fields DED7Mask    */
#define DED7MASK_WIDTH                                                        1
#define DED7MASK_SHIFT                                                        7
#define DED7MASK_MASK                                                0x00000080
#define DED7MASK_RD(src)                              (((src) & 0x00000080)>>7)
#define DED7MASK_WR(src)                         (((u32)(src)<<7) & 0x00000080)
#define DED7MASK_SET(dst,src) \
                       (((dst) & ~0x00000080) | (((u32)(src)<<7) & 0x00000080))
/*    Mask Register Fields DED6Mask    */
#define DED6MASK_WIDTH                                                        1
#define DED6MASK_SHIFT                                                        6
#define DED6MASK_MASK                                                0x00000040
#define DED6MASK_RD(src)                              (((src) & 0x00000040)>>6)
#define DED6MASK_WR(src)                         (((u32)(src)<<6) & 0x00000040)
#define DED6MASK_SET(dst,src) \
                       (((dst) & ~0x00000040) | (((u32)(src)<<6) & 0x00000040))
/*    Mask Register Fields DED5Mask    */
#define DED5MASK_WIDTH                                                        1
#define DED5MASK_SHIFT                                                        5
#define DED5MASK_MASK                                                0x00000020
#define DED5MASK_RD(src)                              (((src) & 0x00000020)>>5)
#define DED5MASK_WR(src)                         (((u32)(src)<<5) & 0x00000020)
#define DED5MASK_SET(dst,src) \
                       (((dst) & ~0x00000020) | (((u32)(src)<<5) & 0x00000020))
/*    Mask Register Fields DED4Mask    */
#define DED4MASK_WIDTH                                                        1
#define DED4MASK_SHIFT                                                        4
#define DED4MASK_MASK                                                0x00000010
#define DED4MASK_RD(src)                              (((src) & 0x00000010)>>4)
#define DED4MASK_WR(src)                         (((u32)(src)<<4) & 0x00000010)
#define DED4MASK_SET(dst,src) \
                       (((dst) & ~0x00000010) | (((u32)(src)<<4) & 0x00000010))
/*    Mask Register Fields DED3Mask    */
#define DED3MASK_WIDTH                                                        1
#define DED3MASK_SHIFT                                                        3
#define DED3MASK_MASK                                                0x00000008
#define DED3MASK_RD(src)                              (((src) & 0x00000008)>>3)
#define DED3MASK_WR(src)                         (((u32)(src)<<3) & 0x00000008)
#define DED3MASK_SET(dst,src) \
                       (((dst) & ~0x00000008) | (((u32)(src)<<3) & 0x00000008))
/*    Mask Register Fields DED2Mask    */
#define DED2MASK_WIDTH                                                        1
#define DED2MASK_SHIFT                                                        2
#define DED2MASK_MASK                                                0x00000004
#define DED2MASK_RD(src)                              (((src) & 0x00000004)>>2)
#define DED2MASK_WR(src)                         (((u32)(src)<<2) & 0x00000004)
#define DED2MASK_SET(dst,src) \
                       (((dst) & ~0x00000004) | (((u32)(src)<<2) & 0x00000004))
/*    Mask Register Fields DED1Mask    */
#define DED1MASK_WIDTH                                                        1
#define DED1MASK_SHIFT                                                        1
#define DED1MASK_MASK                                                0x00000002
#define DED1MASK_RD(src)                              (((src) & 0x00000002)>>1)
#define DED1MASK_WR(src)                         (((u32)(src)<<1) & 0x00000002)
#define DED1MASK_SET(dst,src) \
                       (((dst) & ~0x00000002) | (((u32)(src)<<1) & 0x00000002))
/*    Mask Register Fields DED0Mask    */
#define DED0MASK_WIDTH                                                        1
#define DED0MASK_SHIFT                                                        0
#define DED0MASK_MASK                                                0x00000001
#define DED0MASK_RD(src)                                 (((src) & 0x00000001))
#define DED0MASK_WR(src)                            (((u32)(src)) & 0x00000001)
#define DED0MASK_SET(dst,src) \
                          (((dst) & ~0x00000001) | (((u32)(src)) & 0x00000001))

/*	Register GLBL_DED_ERRH	*/ 
/*	 Fields DED63	 */
#define DED63_WIDTH                                                           1
#define DED63_SHIFT                                                          31
#define DED63_MASK                                                   0x80000000
#define DED63_RD(src)                                (((src) & 0x80000000)>>31)
#define DED63_WR(src)                           (((u32)(src)<<31) & 0x80000000)
#define DED63_SET(dst,src) \
                      (((dst) & ~0x80000000) | (((u32)(src)<<31) & 0x80000000))
/*	 Fields DED62	 */
#define DED62_WIDTH                                                           1
#define DED62_SHIFT                                                          30
#define DED62_MASK                                                   0x40000000
#define DED62_RD(src)                                (((src) & 0x40000000)>>30)
#define DED62_WR(src)                           (((u32)(src)<<30) & 0x40000000)
#define DED62_SET(dst,src) \
                      (((dst) & ~0x40000000) | (((u32)(src)<<30) & 0x40000000))
/*	 Fields DED61	 */
#define DED61_WIDTH                                                           1
#define DED61_SHIFT                                                          29
#define DED61_MASK                                                   0x20000000
#define DED61_RD(src)                                (((src) & 0x20000000)>>29)
#define DED61_WR(src)                           (((u32)(src)<<29) & 0x20000000)
#define DED61_SET(dst,src) \
                      (((dst) & ~0x20000000) | (((u32)(src)<<29) & 0x20000000))
/*	 Fields DED60	 */
#define DED60_WIDTH                                                           1
#define DED60_SHIFT                                                          28
#define DED60_MASK                                                   0x10000000
#define DED60_RD(src)                                (((src) & 0x10000000)>>28)
#define DED60_WR(src)                           (((u32)(src)<<28) & 0x10000000)
#define DED60_SET(dst,src) \
                      (((dst) & ~0x10000000) | (((u32)(src)<<28) & 0x10000000))
/*	 Fields DED59	 */
#define DED59_WIDTH                                                           1
#define DED59_SHIFT                                                          27
#define DED59_MASK                                                   0x08000000
#define DED59_RD(src)                                (((src) & 0x08000000)>>27)
#define DED59_WR(src)                           (((u32)(src)<<27) & 0x08000000)
#define DED59_SET(dst,src) \
                      (((dst) & ~0x08000000) | (((u32)(src)<<27) & 0x08000000))
/*	 Fields DED58	 */
#define DED58_WIDTH                                                           1
#define DED58_SHIFT                                                          26
#define DED58_MASK                                                   0x04000000
#define DED58_RD(src)                                (((src) & 0x04000000)>>26)
#define DED58_WR(src)                           (((u32)(src)<<26) & 0x04000000)
#define DED58_SET(dst,src) \
                      (((dst) & ~0x04000000) | (((u32)(src)<<26) & 0x04000000))
/*	 Fields DED57	 */
#define DED57_WIDTH                                                           1
#define DED57_SHIFT                                                          25
#define DED57_MASK                                                   0x02000000
#define DED57_RD(src)                                (((src) & 0x02000000)>>25)
#define DED57_WR(src)                           (((u32)(src)<<25) & 0x02000000)
#define DED57_SET(dst,src) \
                      (((dst) & ~0x02000000) | (((u32)(src)<<25) & 0x02000000))
/*	 Fields DED56	 */
#define DED56_WIDTH                                                           1
#define DED56_SHIFT                                                          24
#define DED56_MASK                                                   0x01000000
#define DED56_RD(src)                                (((src) & 0x01000000)>>24)
#define DED56_WR(src)                           (((u32)(src)<<24) & 0x01000000)
#define DED56_SET(dst,src) \
                      (((dst) & ~0x01000000) | (((u32)(src)<<24) & 0x01000000))
/*	 Fields DED55	 */
#define DED55_WIDTH                                                           1
#define DED55_SHIFT                                                          23
#define DED55_MASK                                                   0x00800000
#define DED55_RD(src)                                (((src) & 0x00800000)>>23)
#define DED55_WR(src)                           (((u32)(src)<<23) & 0x00800000)
#define DED55_SET(dst,src) \
                      (((dst) & ~0x00800000) | (((u32)(src)<<23) & 0x00800000))
/*	 Fields DED54	 */
#define DED54_WIDTH                                                           1
#define DED54_SHIFT                                                          22
#define DED54_MASK                                                   0x00400000
#define DED54_RD(src)                                (((src) & 0x00400000)>>22)
#define DED54_WR(src)                           (((u32)(src)<<22) & 0x00400000)
#define DED54_SET(dst,src) \
                      (((dst) & ~0x00400000) | (((u32)(src)<<22) & 0x00400000))
/*	 Fields DED53	 */
#define DED53_WIDTH                                                           1
#define DED53_SHIFT                                                          21
#define DED53_MASK                                                   0x00200000
#define DED53_RD(src)                                (((src) & 0x00200000)>>21)
#define DED53_WR(src)                           (((u32)(src)<<21) & 0x00200000)
#define DED53_SET(dst,src) \
                      (((dst) & ~0x00200000) | (((u32)(src)<<21) & 0x00200000))
/*	 Fields DED52	 */
#define DED52_WIDTH                                                           1
#define DED52_SHIFT                                                          20
#define DED52_MASK                                                   0x00100000
#define DED52_RD(src)                                (((src) & 0x00100000)>>20)
#define DED52_WR(src)                           (((u32)(src)<<20) & 0x00100000)
#define DED52_SET(dst,src) \
                      (((dst) & ~0x00100000) | (((u32)(src)<<20) & 0x00100000))
/*	 Fields DED51	 */
#define DED51_WIDTH                                                           1
#define DED51_SHIFT                                                          19
#define DED51_MASK                                                   0x00080000
#define DED51_RD(src)                                (((src) & 0x00080000)>>19)
#define DED51_WR(src)                           (((u32)(src)<<19) & 0x00080000)
#define DED51_SET(dst,src) \
                      (((dst) & ~0x00080000) | (((u32)(src)<<19) & 0x00080000))
/*	 Fields DED50	 */
#define DED50_WIDTH                                                           1
#define DED50_SHIFT                                                          18
#define DED50_MASK                                                   0x00040000
#define DED50_RD(src)                                (((src) & 0x00040000)>>18)
#define DED50_WR(src)                           (((u32)(src)<<18) & 0x00040000)
#define DED50_SET(dst,src) \
                      (((dst) & ~0x00040000) | (((u32)(src)<<18) & 0x00040000))
/*	 Fields DED49	 */
#define DED49_WIDTH                                                           1
#define DED49_SHIFT                                                          17
#define DED49_MASK                                                   0x00020000
#define DED49_RD(src)                                (((src) & 0x00020000)>>17)
#define DED49_WR(src)                           (((u32)(src)<<17) & 0x00020000)
#define DED49_SET(dst,src) \
                      (((dst) & ~0x00020000) | (((u32)(src)<<17) & 0x00020000))
/*	 Fields DED48	 */
#define DED48_WIDTH                                                           1
#define DED48_SHIFT                                                          16
#define DED48_MASK                                                   0x00010000
#define DED48_RD(src)                                (((src) & 0x00010000)>>16)
#define DED48_WR(src)                           (((u32)(src)<<16) & 0x00010000)
#define DED48_SET(dst,src) \
                      (((dst) & ~0x00010000) | (((u32)(src)<<16) & 0x00010000))
/*	 Fields DED47	 */
#define DED47_WIDTH                                                           1
#define DED47_SHIFT                                                          15
#define DED47_MASK                                                   0x00008000
#define DED47_RD(src)                                (((src) & 0x00008000)>>15)
#define DED47_WR(src)                           (((u32)(src)<<15) & 0x00008000)
#define DED47_SET(dst,src) \
                      (((dst) & ~0x00008000) | (((u32)(src)<<15) & 0x00008000))
/*	 Fields DED46	 */
#define DED46_WIDTH                                                           1
#define DED46_SHIFT                                                          14
#define DED46_MASK                                                   0x00004000
#define DED46_RD(src)                                (((src) & 0x00004000)>>14)
#define DED46_WR(src)                           (((u32)(src)<<14) & 0x00004000)
#define DED46_SET(dst,src) \
                      (((dst) & ~0x00004000) | (((u32)(src)<<14) & 0x00004000))
/*	 Fields DED45	 */
#define DED45_WIDTH                                                           1
#define DED45_SHIFT                                                          13
#define DED45_MASK                                                   0x00002000
#define DED45_RD(src)                                (((src) & 0x00002000)>>13)
#define DED45_WR(src)                           (((u32)(src)<<13) & 0x00002000)
#define DED45_SET(dst,src) \
                      (((dst) & ~0x00002000) | (((u32)(src)<<13) & 0x00002000))
/*	 Fields DED44	 */
#define DED44_WIDTH                                                           1
#define DED44_SHIFT                                                          12
#define DED44_MASK                                                   0x00001000
#define DED44_RD(src)                                (((src) & 0x00001000)>>12)
#define DED44_WR(src)                           (((u32)(src)<<12) & 0x00001000)
#define DED44_SET(dst,src) \
                      (((dst) & ~0x00001000) | (((u32)(src)<<12) & 0x00001000))
/*	 Fields DED43	 */
#define DED43_WIDTH                                                           1
#define DED43_SHIFT                                                          11
#define DED43_MASK                                                   0x00000800
#define DED43_RD(src)                                (((src) & 0x00000800)>>11)
#define DED43_WR(src)                           (((u32)(src)<<11) & 0x00000800)
#define DED43_SET(dst,src) \
                      (((dst) & ~0x00000800) | (((u32)(src)<<11) & 0x00000800))
/*	 Fields DED42	 */
#define DED42_WIDTH                                                           1
#define DED42_SHIFT                                                          10
#define DED42_MASK                                                   0x00000400
#define DED42_RD(src)                                (((src) & 0x00000400)>>10)
#define DED42_WR(src)                           (((u32)(src)<<10) & 0x00000400)
#define DED42_SET(dst,src) \
                      (((dst) & ~0x00000400) | (((u32)(src)<<10) & 0x00000400))
/*	 Fields DED41	 */
#define DED41_WIDTH                                                           1
#define DED41_SHIFT                                                           9
#define DED41_MASK                                                   0x00000200
#define DED41_RD(src)                                 (((src) & 0x00000200)>>9)
#define DED41_WR(src)                            (((u32)(src)<<9) & 0x00000200)
#define DED41_SET(dst,src) \
                       (((dst) & ~0x00000200) | (((u32)(src)<<9) & 0x00000200))
/*	 Fields DED40	 */
#define DED40_WIDTH                                                           1
#define DED40_SHIFT                                                           8
#define DED40_MASK                                                   0x00000100
#define DED40_RD(src)                                 (((src) & 0x00000100)>>8)
#define DED40_WR(src)                            (((u32)(src)<<8) & 0x00000100)
#define DED40_SET(dst,src) \
                       (((dst) & ~0x00000100) | (((u32)(src)<<8) & 0x00000100))
/*	 Fields DED39	 */
#define DED39_WIDTH                                                           1
#define DED39_SHIFT                                                           7
#define DED39_MASK                                                   0x00000080
#define DED39_RD(src)                                 (((src) & 0x00000080)>>7)
#define DED39_WR(src)                            (((u32)(src)<<7) & 0x00000080)
#define DED39_SET(dst,src) \
                       (((dst) & ~0x00000080) | (((u32)(src)<<7) & 0x00000080))
/*	 Fields DED38	 */
#define DED38_WIDTH                                                           1
#define DED38_SHIFT                                                           6
#define DED38_MASK                                                   0x00000040
#define DED38_RD(src)                                 (((src) & 0x00000040)>>6)
#define DED38_WR(src)                            (((u32)(src)<<6) & 0x00000040)
#define DED38_SET(dst,src) \
                       (((dst) & ~0x00000040) | (((u32)(src)<<6) & 0x00000040))
/*	 Fields DED37	 */
#define DED37_WIDTH                                                           1
#define DED37_SHIFT                                                           5
#define DED37_MASK                                                   0x00000020
#define DED37_RD(src)                                 (((src) & 0x00000020)>>5)
#define DED37_WR(src)                            (((u32)(src)<<5) & 0x00000020)
#define DED37_SET(dst,src) \
                       (((dst) & ~0x00000020) | (((u32)(src)<<5) & 0x00000020))
/*	 Fields DED36	 */
#define DED36_WIDTH                                                           1
#define DED36_SHIFT                                                           4
#define DED36_MASK                                                   0x00000010
#define DED36_RD(src)                                 (((src) & 0x00000010)>>4)
#define DED36_WR(src)                            (((u32)(src)<<4) & 0x00000010)
#define DED36_SET(dst,src) \
                       (((dst) & ~0x00000010) | (((u32)(src)<<4) & 0x00000010))
/*	 Fields DED35	 */
#define DED35_WIDTH                                                           1
#define DED35_SHIFT                                                           3
#define DED35_MASK                                                   0x00000008
#define DED35_RD(src)                                 (((src) & 0x00000008)>>3)
#define DED35_WR(src)                            (((u32)(src)<<3) & 0x00000008)
#define DED35_SET(dst,src) \
                       (((dst) & ~0x00000008) | (((u32)(src)<<3) & 0x00000008))
/*	 Fields DED34	 */
#define DED34_WIDTH                                                           1
#define DED34_SHIFT                                                           2
#define DED34_MASK                                                   0x00000004
#define DED34_RD(src)                                 (((src) & 0x00000004)>>2)
#define DED34_WR(src)                            (((u32)(src)<<2) & 0x00000004)
#define DED34_SET(dst,src) \
                       (((dst) & ~0x00000004) | (((u32)(src)<<2) & 0x00000004))
/*	 Fields DED33	 */
#define DED33_WIDTH                                                           1
#define DED33_SHIFT                                                           1
#define DED33_MASK                                                   0x00000002
#define DED33_RD(src)                                 (((src) & 0x00000002)>>1)
#define DED33_WR(src)                            (((u32)(src)<<1) & 0x00000002)
#define DED33_SET(dst,src) \
                       (((dst) & ~0x00000002) | (((u32)(src)<<1) & 0x00000002))
/*	 Fields DED32	 */
#define DED32_WIDTH                                                           1
#define DED32_SHIFT                                                           0
#define DED32_MASK                                                   0x00000001
#define DED32_RD(src)                                    (((src) & 0x00000001))
#define DED32_WR(src)                               (((u32)(src)) & 0x00000001)
#define DED32_SET(dst,src) \
                          (((dst) & ~0x00000001) | (((u32)(src)) & 0x00000001))

/*	Register GLBL_DED_ERRHMask	*/
/*    Mask Register Fields DED63Mask    */
#define DED63MASK_WIDTH                                                       1
#define DED63MASK_SHIFT                                                      31
#define DED63MASK_MASK                                               0x80000000
#define DED63MASK_RD(src)                            (((src) & 0x80000000)>>31)
#define DED63MASK_WR(src)                       (((u32)(src)<<31) & 0x80000000)
#define DED63MASK_SET(dst,src) \
                      (((dst) & ~0x80000000) | (((u32)(src)<<31) & 0x80000000))
/*    Mask Register Fields DED62Mask    */
#define DED62MASK_WIDTH                                                       1
#define DED62MASK_SHIFT                                                      30
#define DED62MASK_MASK                                               0x40000000
#define DED62MASK_RD(src)                            (((src) & 0x40000000)>>30)
#define DED62MASK_WR(src)                       (((u32)(src)<<30) & 0x40000000)
#define DED62MASK_SET(dst,src) \
                      (((dst) & ~0x40000000) | (((u32)(src)<<30) & 0x40000000))
/*    Mask Register Fields DED61Mask    */
#define DED61MASK_WIDTH                                                       1
#define DED61MASK_SHIFT                                                      29
#define DED61MASK_MASK                                               0x20000000
#define DED61MASK_RD(src)                            (((src) & 0x20000000)>>29)
#define DED61MASK_WR(src)                       (((u32)(src)<<29) & 0x20000000)
#define DED61MASK_SET(dst,src) \
                      (((dst) & ~0x20000000) | (((u32)(src)<<29) & 0x20000000))
/*    Mask Register Fields DED60Mask    */
#define DED60MASK_WIDTH                                                       1
#define DED60MASK_SHIFT                                                      28
#define DED60MASK_MASK                                               0x10000000
#define DED60MASK_RD(src)                            (((src) & 0x10000000)>>28)
#define DED60MASK_WR(src)                       (((u32)(src)<<28) & 0x10000000)
#define DED60MASK_SET(dst,src) \
                      (((dst) & ~0x10000000) | (((u32)(src)<<28) & 0x10000000))
/*    Mask Register Fields DED59Mask    */
#define DED59MASK_WIDTH                                                       1
#define DED59MASK_SHIFT                                                      27
#define DED59MASK_MASK                                               0x08000000
#define DED59MASK_RD(src)                            (((src) & 0x08000000)>>27)
#define DED59MASK_WR(src)                       (((u32)(src)<<27) & 0x08000000)
#define DED59MASK_SET(dst,src) \
                      (((dst) & ~0x08000000) | (((u32)(src)<<27) & 0x08000000))
/*    Mask Register Fields DED58Mask    */
#define DED58MASK_WIDTH                                                       1
#define DED58MASK_SHIFT                                                      26
#define DED58MASK_MASK                                               0x04000000
#define DED58MASK_RD(src)                            (((src) & 0x04000000)>>26)
#define DED58MASK_WR(src)                       (((u32)(src)<<26) & 0x04000000)
#define DED58MASK_SET(dst,src) \
                      (((dst) & ~0x04000000) | (((u32)(src)<<26) & 0x04000000))
/*    Mask Register Fields DED57Mask    */
#define DED57MASK_WIDTH                                                       1
#define DED57MASK_SHIFT                                                      25
#define DED57MASK_MASK                                               0x02000000
#define DED57MASK_RD(src)                            (((src) & 0x02000000)>>25)
#define DED57MASK_WR(src)                       (((u32)(src)<<25) & 0x02000000)
#define DED57MASK_SET(dst,src) \
                      (((dst) & ~0x02000000) | (((u32)(src)<<25) & 0x02000000))
/*    Mask Register Fields DED56Mask    */
#define DED56MASK_WIDTH                                                       1
#define DED56MASK_SHIFT                                                      24
#define DED56MASK_MASK                                               0x01000000
#define DED56MASK_RD(src)                            (((src) & 0x01000000)>>24)
#define DED56MASK_WR(src)                       (((u32)(src)<<24) & 0x01000000)
#define DED56MASK_SET(dst,src) \
                      (((dst) & ~0x01000000) | (((u32)(src)<<24) & 0x01000000))
/*    Mask Register Fields DED55Mask    */
#define DED55MASK_WIDTH                                                       1
#define DED55MASK_SHIFT                                                      23
#define DED55MASK_MASK                                               0x00800000
#define DED55MASK_RD(src)                            (((src) & 0x00800000)>>23)
#define DED55MASK_WR(src)                       (((u32)(src)<<23) & 0x00800000)
#define DED55MASK_SET(dst,src) \
                      (((dst) & ~0x00800000) | (((u32)(src)<<23) & 0x00800000))
/*    Mask Register Fields DED54Mask    */
#define DED54MASK_WIDTH                                                       1
#define DED54MASK_SHIFT                                                      22
#define DED54MASK_MASK                                               0x00400000
#define DED54MASK_RD(src)                            (((src) & 0x00400000)>>22)
#define DED54MASK_WR(src)                       (((u32)(src)<<22) & 0x00400000)
#define DED54MASK_SET(dst,src) \
                      (((dst) & ~0x00400000) | (((u32)(src)<<22) & 0x00400000))
/*    Mask Register Fields DED53Mask    */
#define DED53MASK_WIDTH                                                       1
#define DED53MASK_SHIFT                                                      21
#define DED53MASK_MASK                                               0x00200000
#define DED53MASK_RD(src)                            (((src) & 0x00200000)>>21)
#define DED53MASK_WR(src)                       (((u32)(src)<<21) & 0x00200000)
#define DED53MASK_SET(dst,src) \
                      (((dst) & ~0x00200000) | (((u32)(src)<<21) & 0x00200000))
/*    Mask Register Fields DED52Mask    */
#define DED52MASK_WIDTH                                                       1
#define DED52MASK_SHIFT                                                      20
#define DED52MASK_MASK                                               0x00100000
#define DED52MASK_RD(src)                            (((src) & 0x00100000)>>20)
#define DED52MASK_WR(src)                       (((u32)(src)<<20) & 0x00100000)
#define DED52MASK_SET(dst,src) \
                      (((dst) & ~0x00100000) | (((u32)(src)<<20) & 0x00100000))
/*    Mask Register Fields DED51Mask    */
#define DED51MASK_WIDTH                                                       1
#define DED51MASK_SHIFT                                                      19
#define DED51MASK_MASK                                               0x00080000
#define DED51MASK_RD(src)                            (((src) & 0x00080000)>>19)
#define DED51MASK_WR(src)                       (((u32)(src)<<19) & 0x00080000)
#define DED51MASK_SET(dst,src) \
                      (((dst) & ~0x00080000) | (((u32)(src)<<19) & 0x00080000))
/*    Mask Register Fields DED50Mask    */
#define DED50MASK_WIDTH                                                       1
#define DED50MASK_SHIFT                                                      18
#define DED50MASK_MASK                                               0x00040000
#define DED50MASK_RD(src)                            (((src) & 0x00040000)>>18)
#define DED50MASK_WR(src)                       (((u32)(src)<<18) & 0x00040000)
#define DED50MASK_SET(dst,src) \
                      (((dst) & ~0x00040000) | (((u32)(src)<<18) & 0x00040000))
/*    Mask Register Fields DED49Mask    */
#define DED49MASK_WIDTH                                                       1
#define DED49MASK_SHIFT                                                      17
#define DED49MASK_MASK                                               0x00020000
#define DED49MASK_RD(src)                            (((src) & 0x00020000)>>17)
#define DED49MASK_WR(src)                       (((u32)(src)<<17) & 0x00020000)
#define DED49MASK_SET(dst,src) \
                      (((dst) & ~0x00020000) | (((u32)(src)<<17) & 0x00020000))
/*    Mask Register Fields DED48Mask    */
#define DED48MASK_WIDTH                                                       1
#define DED48MASK_SHIFT                                                      16
#define DED48MASK_MASK                                               0x00010000
#define DED48MASK_RD(src)                            (((src) & 0x00010000)>>16)
#define DED48MASK_WR(src)                       (((u32)(src)<<16) & 0x00010000)
#define DED48MASK_SET(dst,src) \
                      (((dst) & ~0x00010000) | (((u32)(src)<<16) & 0x00010000))
/*    Mask Register Fields DED47Mask    */
#define DED47MASK_WIDTH                                                       1
#define DED47MASK_SHIFT                                                      15
#define DED47MASK_MASK                                               0x00008000
#define DED47MASK_RD(src)                            (((src) & 0x00008000)>>15)
#define DED47MASK_WR(src)                       (((u32)(src)<<15) & 0x00008000)
#define DED47MASK_SET(dst,src) \
                      (((dst) & ~0x00008000) | (((u32)(src)<<15) & 0x00008000))
/*    Mask Register Fields DED46Mask    */
#define DED46MASK_WIDTH                                                       1
#define DED46MASK_SHIFT                                                      14
#define DED46MASK_MASK                                               0x00004000
#define DED46MASK_RD(src)                            (((src) & 0x00004000)>>14)
#define DED46MASK_WR(src)                       (((u32)(src)<<14) & 0x00004000)
#define DED46MASK_SET(dst,src) \
                      (((dst) & ~0x00004000) | (((u32)(src)<<14) & 0x00004000))
/*    Mask Register Fields DED45Mask    */
#define DED45MASK_WIDTH                                                       1
#define DED45MASK_SHIFT                                                      13
#define DED45MASK_MASK                                               0x00002000
#define DED45MASK_RD(src)                            (((src) & 0x00002000)>>13)
#define DED45MASK_WR(src)                       (((u32)(src)<<13) & 0x00002000)
#define DED45MASK_SET(dst,src) \
                      (((dst) & ~0x00002000) | (((u32)(src)<<13) & 0x00002000))
/*    Mask Register Fields DED44Mask    */
#define DED44MASK_WIDTH                                                       1
#define DED44MASK_SHIFT                                                      12
#define DED44MASK_MASK                                               0x00001000
#define DED44MASK_RD(src)                            (((src) & 0x00001000)>>12)
#define DED44MASK_WR(src)                       (((u32)(src)<<12) & 0x00001000)
#define DED44MASK_SET(dst,src) \
                      (((dst) & ~0x00001000) | (((u32)(src)<<12) & 0x00001000))
/*    Mask Register Fields DED43Mask    */
#define DED43MASK_WIDTH                                                       1
#define DED43MASK_SHIFT                                                      11
#define DED43MASK_MASK                                               0x00000800
#define DED43MASK_RD(src)                            (((src) & 0x00000800)>>11)
#define DED43MASK_WR(src)                       (((u32)(src)<<11) & 0x00000800)
#define DED43MASK_SET(dst,src) \
                      (((dst) & ~0x00000800) | (((u32)(src)<<11) & 0x00000800))
/*    Mask Register Fields DED42Mask    */
#define DED42MASK_WIDTH                                                       1
#define DED42MASK_SHIFT                                                      10
#define DED42MASK_MASK                                               0x00000400
#define DED42MASK_RD(src)                            (((src) & 0x00000400)>>10)
#define DED42MASK_WR(src)                       (((u32)(src)<<10) & 0x00000400)
#define DED42MASK_SET(dst,src) \
                      (((dst) & ~0x00000400) | (((u32)(src)<<10) & 0x00000400))
/*    Mask Register Fields DED41Mask    */
#define DED41MASK_WIDTH                                                       1
#define DED41MASK_SHIFT                                                       9
#define DED41MASK_MASK                                               0x00000200
#define DED41MASK_RD(src)                             (((src) & 0x00000200)>>9)
#define DED41MASK_WR(src)                        (((u32)(src)<<9) & 0x00000200)
#define DED41MASK_SET(dst,src) \
                       (((dst) & ~0x00000200) | (((u32)(src)<<9) & 0x00000200))
/*    Mask Register Fields DED40Mask    */
#define DED40MASK_WIDTH                                                       1
#define DED40MASK_SHIFT                                                       8
#define DED40MASK_MASK                                               0x00000100
#define DED40MASK_RD(src)                             (((src) & 0x00000100)>>8)
#define DED40MASK_WR(src)                        (((u32)(src)<<8) & 0x00000100)
#define DED40MASK_SET(dst,src) \
                       (((dst) & ~0x00000100) | (((u32)(src)<<8) & 0x00000100))
/*    Mask Register Fields DED39Mask    */
#define DED39MASK_WIDTH                                                       1
#define DED39MASK_SHIFT                                                       7
#define DED39MASK_MASK                                               0x00000080
#define DED39MASK_RD(src)                             (((src) & 0x00000080)>>7)
#define DED39MASK_WR(src)                        (((u32)(src)<<7) & 0x00000080)
#define DED39MASK_SET(dst,src) \
                       (((dst) & ~0x00000080) | (((u32)(src)<<7) & 0x00000080))
/*    Mask Register Fields DED38Mask    */
#define DED38MASK_WIDTH                                                       1
#define DED38MASK_SHIFT                                                       6
#define DED38MASK_MASK                                               0x00000040
#define DED38MASK_RD(src)                             (((src) & 0x00000040)>>6)
#define DED38MASK_WR(src)                        (((u32)(src)<<6) & 0x00000040)
#define DED38MASK_SET(dst,src) \
                       (((dst) & ~0x00000040) | (((u32)(src)<<6) & 0x00000040))
/*    Mask Register Fields DED37Mask    */
#define DED37MASK_WIDTH                                                       1
#define DED37MASK_SHIFT                                                       5
#define DED37MASK_MASK                                               0x00000020
#define DED37MASK_RD(src)                             (((src) & 0x00000020)>>5)
#define DED37MASK_WR(src)                        (((u32)(src)<<5) & 0x00000020)
#define DED37MASK_SET(dst,src) \
                       (((dst) & ~0x00000020) | (((u32)(src)<<5) & 0x00000020))
/*    Mask Register Fields DED36Mask    */
#define DED36MASK_WIDTH                                                       1
#define DED36MASK_SHIFT                                                       4
#define DED36MASK_MASK                                               0x00000010
#define DED36MASK_RD(src)                             (((src) & 0x00000010)>>4)
#define DED36MASK_WR(src)                        (((u32)(src)<<4) & 0x00000010)
#define DED36MASK_SET(dst,src) \
                       (((dst) & ~0x00000010) | (((u32)(src)<<4) & 0x00000010))
/*    Mask Register Fields DED35Mask    */
#define DED35MASK_WIDTH                                                       1
#define DED35MASK_SHIFT                                                       3
#define DED35MASK_MASK                                               0x00000008
#define DED35MASK_RD(src)                             (((src) & 0x00000008)>>3)
#define DED35MASK_WR(src)                        (((u32)(src)<<3) & 0x00000008)
#define DED35MASK_SET(dst,src) \
                       (((dst) & ~0x00000008) | (((u32)(src)<<3) & 0x00000008))
/*    Mask Register Fields DED34Mask    */
#define DED34MASK_WIDTH                                                       1
#define DED34MASK_SHIFT                                                       2
#define DED34MASK_MASK                                               0x00000004
#define DED34MASK_RD(src)                             (((src) & 0x00000004)>>2)
#define DED34MASK_WR(src)                        (((u32)(src)<<2) & 0x00000004)
#define DED34MASK_SET(dst,src) \
                       (((dst) & ~0x00000004) | (((u32)(src)<<2) & 0x00000004))
/*    Mask Register Fields DED33Mask    */
#define DED33MASK_WIDTH                                                       1
#define DED33MASK_SHIFT                                                       1
#define DED33MASK_MASK                                               0x00000002
#define DED33MASK_RD(src)                             (((src) & 0x00000002)>>1)
#define DED33MASK_WR(src)                        (((u32)(src)<<1) & 0x00000002)
#define DED33MASK_SET(dst,src) \
                       (((dst) & ~0x00000002) | (((u32)(src)<<1) & 0x00000002))
/*    Mask Register Fields DED32Mask    */
#define DED32MASK_WIDTH                                                       1
#define DED32MASK_SHIFT                                                       0
#define DED32MASK_MASK                                               0x00000001
#define DED32MASK_RD(src)                                (((src) & 0x00000001))
#define DED32MASK_WR(src)                           (((u32)(src)) & 0x00000001)
#define DED32MASK_SET(dst,src) \
                          (((dst) & ~0x00000001) | (((u32)(src)) & 0x00000001))

/*	Register GLBL_MDED_ERRL	*/ 
/*	 Fields MDED31	 */
#define MDED31_WIDTH                                                          1
#define MDED31_SHIFT                                                         31
#define MDED31_MASK                                                  0x80000000
#define MDED31_RD(src)                               (((src) & 0x80000000)>>31)
#define MDED31_WR(src)                          (((u32)(src)<<31) & 0x80000000)
#define MDED31_SET(dst,src) \
                      (((dst) & ~0x80000000) | (((u32)(src)<<31) & 0x80000000))
/*	 Fields MDED30	 */
#define MDED30_WIDTH                                                          1
#define MDED30_SHIFT                                                         30
#define MDED30_MASK                                                  0x40000000
#define MDED30_RD(src)                               (((src) & 0x40000000)>>30)
#define MDED30_WR(src)                          (((u32)(src)<<30) & 0x40000000)
#define MDED30_SET(dst,src) \
                      (((dst) & ~0x40000000) | (((u32)(src)<<30) & 0x40000000))
/*	 Fields MDED29	 */
#define MDED29_WIDTH                                                          1
#define MDED29_SHIFT                                                         29
#define MDED29_MASK                                                  0x20000000
#define MDED29_RD(src)                               (((src) & 0x20000000)>>29)
#define MDED29_WR(src)                          (((u32)(src)<<29) & 0x20000000)
#define MDED29_SET(dst,src) \
                      (((dst) & ~0x20000000) | (((u32)(src)<<29) & 0x20000000))
/*	 Fields MDED28	 */
#define MDED28_WIDTH                                                          1
#define MDED28_SHIFT                                                         28
#define MDED28_MASK                                                  0x10000000
#define MDED28_RD(src)                               (((src) & 0x10000000)>>28)
#define MDED28_WR(src)                          (((u32)(src)<<28) & 0x10000000)
#define MDED28_SET(dst,src) \
                      (((dst) & ~0x10000000) | (((u32)(src)<<28) & 0x10000000))
/*	 Fields MDED27	 */
#define MDED27_WIDTH                                                          1
#define MDED27_SHIFT                                                         27
#define MDED27_MASK                                                  0x08000000
#define MDED27_RD(src)                               (((src) & 0x08000000)>>27)
#define MDED27_WR(src)                          (((u32)(src)<<27) & 0x08000000)
#define MDED27_SET(dst,src) \
                      (((dst) & ~0x08000000) | (((u32)(src)<<27) & 0x08000000))
/*	 Fields MDED26	 */
#define MDED26_WIDTH                                                          1
#define MDED26_SHIFT                                                         26
#define MDED26_MASK                                                  0x04000000
#define MDED26_RD(src)                               (((src) & 0x04000000)>>26)
#define MDED26_WR(src)                          (((u32)(src)<<26) & 0x04000000)
#define MDED26_SET(dst,src) \
                      (((dst) & ~0x04000000) | (((u32)(src)<<26) & 0x04000000))
/*	 Fields MDED25	 */
#define MDED25_WIDTH                                                          1
#define MDED25_SHIFT                                                         25
#define MDED25_MASK                                                  0x02000000
#define MDED25_RD(src)                               (((src) & 0x02000000)>>25)
#define MDED25_WR(src)                          (((u32)(src)<<25) & 0x02000000)
#define MDED25_SET(dst,src) \
                      (((dst) & ~0x02000000) | (((u32)(src)<<25) & 0x02000000))
/*	 Fields MDED24	 */
#define MDED24_WIDTH                                                          1
#define MDED24_SHIFT                                                         24
#define MDED24_MASK                                                  0x01000000
#define MDED24_RD(src)                               (((src) & 0x01000000)>>24)
#define MDED24_WR(src)                          (((u32)(src)<<24) & 0x01000000)
#define MDED24_SET(dst,src) \
                      (((dst) & ~0x01000000) | (((u32)(src)<<24) & 0x01000000))
/*	 Fields MDED23	 */
#define MDED23_WIDTH                                                          1
#define MDED23_SHIFT                                                         23
#define MDED23_MASK                                                  0x00800000
#define MDED23_RD(src)                               (((src) & 0x00800000)>>23)
#define MDED23_WR(src)                          (((u32)(src)<<23) & 0x00800000)
#define MDED23_SET(dst,src) \
                      (((dst) & ~0x00800000) | (((u32)(src)<<23) & 0x00800000))
/*	 Fields MDED22	 */
#define MDED22_WIDTH                                                          1
#define MDED22_SHIFT                                                         22
#define MDED22_MASK                                                  0x00400000
#define MDED22_RD(src)                               (((src) & 0x00400000)>>22)
#define MDED22_WR(src)                          (((u32)(src)<<22) & 0x00400000)
#define MDED22_SET(dst,src) \
                      (((dst) & ~0x00400000) | (((u32)(src)<<22) & 0x00400000))
/*	 Fields MDED21	 */
#define MDED21_WIDTH                                                          1
#define MDED21_SHIFT                                                         21
#define MDED21_MASK                                                  0x00200000
#define MDED21_RD(src)                               (((src) & 0x00200000)>>21)
#define MDED21_WR(src)                          (((u32)(src)<<21) & 0x00200000)
#define MDED21_SET(dst,src) \
                      (((dst) & ~0x00200000) | (((u32)(src)<<21) & 0x00200000))
/*	 Fields MDED20	 */
#define MDED20_WIDTH                                                          1
#define MDED20_SHIFT                                                         20
#define MDED20_MASK                                                  0x00100000
#define MDED20_RD(src)                               (((src) & 0x00100000)>>20)
#define MDED20_WR(src)                          (((u32)(src)<<20) & 0x00100000)
#define MDED20_SET(dst,src) \
                      (((dst) & ~0x00100000) | (((u32)(src)<<20) & 0x00100000))
/*	 Fields MDED19	 */
#define MDED19_WIDTH                                                          1
#define MDED19_SHIFT                                                         19
#define MDED19_MASK                                                  0x00080000
#define MDED19_RD(src)                               (((src) & 0x00080000)>>19)
#define MDED19_WR(src)                          (((u32)(src)<<19) & 0x00080000)
#define MDED19_SET(dst,src) \
                      (((dst) & ~0x00080000) | (((u32)(src)<<19) & 0x00080000))
/*	 Fields MDED18	 */
#define MDED18_WIDTH                                                          1
#define MDED18_SHIFT                                                         18
#define MDED18_MASK                                                  0x00040000
#define MDED18_RD(src)                               (((src) & 0x00040000)>>18)
#define MDED18_WR(src)                          (((u32)(src)<<18) & 0x00040000)
#define MDED18_SET(dst,src) \
                      (((dst) & ~0x00040000) | (((u32)(src)<<18) & 0x00040000))
/*	 Fields MDED17	 */
#define MDED17_WIDTH                                                          1
#define MDED17_SHIFT                                                         17
#define MDED17_MASK                                                  0x00020000
#define MDED17_RD(src)                               (((src) & 0x00020000)>>17)
#define MDED17_WR(src)                          (((u32)(src)<<17) & 0x00020000)
#define MDED17_SET(dst,src) \
                      (((dst) & ~0x00020000) | (((u32)(src)<<17) & 0x00020000))
/*	 Fields MDED16	 */
#define MDED16_WIDTH                                                          1
#define MDED16_SHIFT                                                         16
#define MDED16_MASK                                                  0x00010000
#define MDED16_RD(src)                               (((src) & 0x00010000)>>16)
#define MDED16_WR(src)                          (((u32)(src)<<16) & 0x00010000)
#define MDED16_SET(dst,src) \
                      (((dst) & ~0x00010000) | (((u32)(src)<<16) & 0x00010000))
/*	 Fields MDED15	 */
#define MDED15_WIDTH                                                          1
#define MDED15_SHIFT                                                         15
#define MDED15_MASK                                                  0x00008000
#define MDED15_RD(src)                               (((src) & 0x00008000)>>15)
#define MDED15_WR(src)                          (((u32)(src)<<15) & 0x00008000)
#define MDED15_SET(dst,src) \
                      (((dst) & ~0x00008000) | (((u32)(src)<<15) & 0x00008000))
/*	 Fields MDED14	 */
#define MDED14_WIDTH                                                          1
#define MDED14_SHIFT                                                         14
#define MDED14_MASK                                                  0x00004000
#define MDED14_RD(src)                               (((src) & 0x00004000)>>14)
#define MDED14_WR(src)                          (((u32)(src)<<14) & 0x00004000)
#define MDED14_SET(dst,src) \
                      (((dst) & ~0x00004000) | (((u32)(src)<<14) & 0x00004000))
/*	 Fields MDED13	 */
#define MDED13_WIDTH                                                          1
#define MDED13_SHIFT                                                         13
#define MDED13_MASK                                                  0x00002000
#define MDED13_RD(src)                               (((src) & 0x00002000)>>13)
#define MDED13_WR(src)                          (((u32)(src)<<13) & 0x00002000)
#define MDED13_SET(dst,src) \
                      (((dst) & ~0x00002000) | (((u32)(src)<<13) & 0x00002000))
/*	 Fields MDED12	 */
#define MDED12_WIDTH                                                          1
#define MDED12_SHIFT                                                         12
#define MDED12_MASK                                                  0x00001000
#define MDED12_RD(src)                               (((src) & 0x00001000)>>12)
#define MDED12_WR(src)                          (((u32)(src)<<12) & 0x00001000)
#define MDED12_SET(dst,src) \
                      (((dst) & ~0x00001000) | (((u32)(src)<<12) & 0x00001000))
/*	 Fields MDED11	 */
#define MDED11_WIDTH                                                          1
#define MDED11_SHIFT                                                         11
#define MDED11_MASK                                                  0x00000800
#define MDED11_RD(src)                               (((src) & 0x00000800)>>11)
#define MDED11_WR(src)                          (((u32)(src)<<11) & 0x00000800)
#define MDED11_SET(dst,src) \
                      (((dst) & ~0x00000800) | (((u32)(src)<<11) & 0x00000800))
/*	 Fields MDED10	 */
#define MDED10_WIDTH                                                          1
#define MDED10_SHIFT                                                         10
#define MDED10_MASK                                                  0x00000400
#define MDED10_RD(src)                               (((src) & 0x00000400)>>10)
#define MDED10_WR(src)                          (((u32)(src)<<10) & 0x00000400)
#define MDED10_SET(dst,src) \
                      (((dst) & ~0x00000400) | (((u32)(src)<<10) & 0x00000400))
/*	 Fields MDED9	 */
#define MDED9_WIDTH                                                           1
#define MDED9_SHIFT                                                           9
#define MDED9_MASK                                                   0x00000200
#define MDED9_RD(src)                                 (((src) & 0x00000200)>>9)
#define MDED9_WR(src)                            (((u32)(src)<<9) & 0x00000200)
#define MDED9_SET(dst,src) \
                       (((dst) & ~0x00000200) | (((u32)(src)<<9) & 0x00000200))
/*	 Fields MDED8	 */
#define MDED8_WIDTH                                                           1
#define MDED8_SHIFT                                                           8
#define MDED8_MASK                                                   0x00000100
#define MDED8_RD(src)                                 (((src) & 0x00000100)>>8)
#define MDED8_WR(src)                            (((u32)(src)<<8) & 0x00000100)
#define MDED8_SET(dst,src) \
                       (((dst) & ~0x00000100) | (((u32)(src)<<8) & 0x00000100))
/*	 Fields MDED7	 */
#define MDED7_WIDTH                                                           1
#define MDED7_SHIFT                                                           7
#define MDED7_MASK                                                   0x00000080
#define MDED7_RD(src)                                 (((src) & 0x00000080)>>7)
#define MDED7_WR(src)                            (((u32)(src)<<7) & 0x00000080)
#define MDED7_SET(dst,src) \
                       (((dst) & ~0x00000080) | (((u32)(src)<<7) & 0x00000080))
/*	 Fields MDED6	 */
#define MDED6_WIDTH                                                           1
#define MDED6_SHIFT                                                           6
#define MDED6_MASK                                                   0x00000040
#define MDED6_RD(src)                                 (((src) & 0x00000040)>>6)
#define MDED6_WR(src)                            (((u32)(src)<<6) & 0x00000040)
#define MDED6_SET(dst,src) \
                       (((dst) & ~0x00000040) | (((u32)(src)<<6) & 0x00000040))
/*	 Fields MDED5	 */
#define MDED5_WIDTH                                                           1
#define MDED5_SHIFT                                                           5
#define MDED5_MASK                                                   0x00000020
#define MDED5_RD(src)                                 (((src) & 0x00000020)>>5)
#define MDED5_WR(src)                            (((u32)(src)<<5) & 0x00000020)
#define MDED5_SET(dst,src) \
                       (((dst) & ~0x00000020) | (((u32)(src)<<5) & 0x00000020))
/*	 Fields MDED4	 */
#define MDED4_WIDTH                                                           1
#define MDED4_SHIFT                                                           4
#define MDED4_MASK                                                   0x00000010
#define MDED4_RD(src)                                 (((src) & 0x00000010)>>4)
#define MDED4_WR(src)                            (((u32)(src)<<4) & 0x00000010)
#define MDED4_SET(dst,src) \
                       (((dst) & ~0x00000010) | (((u32)(src)<<4) & 0x00000010))
/*	 Fields MDED3	 */
#define MDED3_WIDTH                                                           1
#define MDED3_SHIFT                                                           3
#define MDED3_MASK                                                   0x00000008
#define MDED3_RD(src)                                 (((src) & 0x00000008)>>3)
#define MDED3_WR(src)                            (((u32)(src)<<3) & 0x00000008)
#define MDED3_SET(dst,src) \
                       (((dst) & ~0x00000008) | (((u32)(src)<<3) & 0x00000008))
/*	 Fields MDED2	 */
#define MDED2_WIDTH                                                           1
#define MDED2_SHIFT                                                           2
#define MDED2_MASK                                                   0x00000004
#define MDED2_RD(src)                                 (((src) & 0x00000004)>>2)
#define MDED2_WR(src)                            (((u32)(src)<<2) & 0x00000004)
#define MDED2_SET(dst,src) \
                       (((dst) & ~0x00000004) | (((u32)(src)<<2) & 0x00000004))
/*	 Fields MDED1	 */
#define MDED1_WIDTH                                                           1
#define MDED1_SHIFT                                                           1
#define MDED1_MASK                                                   0x00000002
#define MDED1_RD(src)                                 (((src) & 0x00000002)>>1)
#define MDED1_WR(src)                            (((u32)(src)<<1) & 0x00000002)
#define MDED1_SET(dst,src) \
                       (((dst) & ~0x00000002) | (((u32)(src)<<1) & 0x00000002))
/*	 Fields MDED0	 */
#define MDED0_WIDTH                                                           1
#define MDED0_SHIFT                                                           0
#define MDED0_MASK                                                   0x00000001
#define MDED0_RD(src)                                    (((src) & 0x00000001))
#define MDED0_WR(src)                               (((u32)(src)) & 0x00000001)
#define MDED0_SET(dst,src) \
                          (((dst) & ~0x00000001) | (((u32)(src)) & 0x00000001))

/*	Register GLBL_MDED_ERRLMask	*/
/*    Mask Register Fields MDED31Mask    */
#define MDED31MASK_WIDTH                                                      1
#define MDED31MASK_SHIFT                                                     31
#define MDED31MASK_MASK                                              0x80000000
#define MDED31MASK_RD(src)                           (((src) & 0x80000000)>>31)
#define MDED31MASK_WR(src)                      (((u32)(src)<<31) & 0x80000000)
#define MDED31MASK_SET(dst,src) \
                      (((dst) & ~0x80000000) | (((u32)(src)<<31) & 0x80000000))
/*    Mask Register Fields MDED30Mask    */
#define MDED30MASK_WIDTH                                                      1
#define MDED30MASK_SHIFT                                                     30
#define MDED30MASK_MASK                                              0x40000000
#define MDED30MASK_RD(src)                           (((src) & 0x40000000)>>30)
#define MDED30MASK_WR(src)                      (((u32)(src)<<30) & 0x40000000)
#define MDED30MASK_SET(dst,src) \
                      (((dst) & ~0x40000000) | (((u32)(src)<<30) & 0x40000000))
/*    Mask Register Fields MDED29Mask    */
#define MDED29MASK_WIDTH                                                      1
#define MDED29MASK_SHIFT                                                     29
#define MDED29MASK_MASK                                              0x20000000
#define MDED29MASK_RD(src)                           (((src) & 0x20000000)>>29)
#define MDED29MASK_WR(src)                      (((u32)(src)<<29) & 0x20000000)
#define MDED29MASK_SET(dst,src) \
                      (((dst) & ~0x20000000) | (((u32)(src)<<29) & 0x20000000))
/*    Mask Register Fields MDED28Mask    */
#define MDED28MASK_WIDTH                                                      1
#define MDED28MASK_SHIFT                                                     28
#define MDED28MASK_MASK                                              0x10000000
#define MDED28MASK_RD(src)                           (((src) & 0x10000000)>>28)
#define MDED28MASK_WR(src)                      (((u32)(src)<<28) & 0x10000000)
#define MDED28MASK_SET(dst,src) \
                      (((dst) & ~0x10000000) | (((u32)(src)<<28) & 0x10000000))
/*    Mask Register Fields MDED27Mask    */
#define MDED27MASK_WIDTH                                                      1
#define MDED27MASK_SHIFT                                                     27
#define MDED27MASK_MASK                                              0x08000000
#define MDED27MASK_RD(src)                           (((src) & 0x08000000)>>27)
#define MDED27MASK_WR(src)                      (((u32)(src)<<27) & 0x08000000)
#define MDED27MASK_SET(dst,src) \
                      (((dst) & ~0x08000000) | (((u32)(src)<<27) & 0x08000000))
/*    Mask Register Fields MDED26Mask    */
#define MDED26MASK_WIDTH                                                      1
#define MDED26MASK_SHIFT                                                     26
#define MDED26MASK_MASK                                              0x04000000
#define MDED26MASK_RD(src)                           (((src) & 0x04000000)>>26)
#define MDED26MASK_WR(src)                      (((u32)(src)<<26) & 0x04000000)
#define MDED26MASK_SET(dst,src) \
                      (((dst) & ~0x04000000) | (((u32)(src)<<26) & 0x04000000))
/*    Mask Register Fields MDED25Mask    */
#define MDED25MASK_WIDTH                                                      1
#define MDED25MASK_SHIFT                                                     25
#define MDED25MASK_MASK                                              0x02000000
#define MDED25MASK_RD(src)                           (((src) & 0x02000000)>>25)
#define MDED25MASK_WR(src)                      (((u32)(src)<<25) & 0x02000000)
#define MDED25MASK_SET(dst,src) \
                      (((dst) & ~0x02000000) | (((u32)(src)<<25) & 0x02000000))
/*    Mask Register Fields MDED24Mask    */
#define MDED24MASK_WIDTH                                                      1
#define MDED24MASK_SHIFT                                                     24
#define MDED24MASK_MASK                                              0x01000000
#define MDED24MASK_RD(src)                           (((src) & 0x01000000)>>24)
#define MDED24MASK_WR(src)                      (((u32)(src)<<24) & 0x01000000)
#define MDED24MASK_SET(dst,src) \
                      (((dst) & ~0x01000000) | (((u32)(src)<<24) & 0x01000000))
/*    Mask Register Fields MDED23Mask    */
#define MDED23MASK_WIDTH                                                      1
#define MDED23MASK_SHIFT                                                     23
#define MDED23MASK_MASK                                              0x00800000
#define MDED23MASK_RD(src)                           (((src) & 0x00800000)>>23)
#define MDED23MASK_WR(src)                      (((u32)(src)<<23) & 0x00800000)
#define MDED23MASK_SET(dst,src) \
                      (((dst) & ~0x00800000) | (((u32)(src)<<23) & 0x00800000))
/*    Mask Register Fields MDED22Mask    */
#define MDED22MASK_WIDTH                                                      1
#define MDED22MASK_SHIFT                                                     22
#define MDED22MASK_MASK                                              0x00400000
#define MDED22MASK_RD(src)                           (((src) & 0x00400000)>>22)
#define MDED22MASK_WR(src)                      (((u32)(src)<<22) & 0x00400000)
#define MDED22MASK_SET(dst,src) \
                      (((dst) & ~0x00400000) | (((u32)(src)<<22) & 0x00400000))
/*    Mask Register Fields MDED21Mask    */
#define MDED21MASK_WIDTH                                                      1
#define MDED21MASK_SHIFT                                                     21
#define MDED21MASK_MASK                                              0x00200000
#define MDED21MASK_RD(src)                           (((src) & 0x00200000)>>21)
#define MDED21MASK_WR(src)                      (((u32)(src)<<21) & 0x00200000)
#define MDED21MASK_SET(dst,src) \
                      (((dst) & ~0x00200000) | (((u32)(src)<<21) & 0x00200000))
/*    Mask Register Fields MDED20Mask    */
#define MDED20MASK_WIDTH                                                      1
#define MDED20MASK_SHIFT                                                     20
#define MDED20MASK_MASK                                              0x00100000
#define MDED20MASK_RD(src)                           (((src) & 0x00100000)>>20)
#define MDED20MASK_WR(src)                      (((u32)(src)<<20) & 0x00100000)
#define MDED20MASK_SET(dst,src) \
                      (((dst) & ~0x00100000) | (((u32)(src)<<20) & 0x00100000))
/*    Mask Register Fields MDED19Mask    */
#define MDED19MASK_WIDTH                                                      1
#define MDED19MASK_SHIFT                                                     19
#define MDED19MASK_MASK                                              0x00080000
#define MDED19MASK_RD(src)                           (((src) & 0x00080000)>>19)
#define MDED19MASK_WR(src)                      (((u32)(src)<<19) & 0x00080000)
#define MDED19MASK_SET(dst,src) \
                      (((dst) & ~0x00080000) | (((u32)(src)<<19) & 0x00080000))
/*    Mask Register Fields MDED18Mask    */
#define MDED18MASK_WIDTH                                                      1
#define MDED18MASK_SHIFT                                                     18
#define MDED18MASK_MASK                                              0x00040000
#define MDED18MASK_RD(src)                           (((src) & 0x00040000)>>18)
#define MDED18MASK_WR(src)                      (((u32)(src)<<18) & 0x00040000)
#define MDED18MASK_SET(dst,src) \
                      (((dst) & ~0x00040000) | (((u32)(src)<<18) & 0x00040000))
/*    Mask Register Fields MDED17Mask    */
#define MDED17MASK_WIDTH                                                      1
#define MDED17MASK_SHIFT                                                     17
#define MDED17MASK_MASK                                              0x00020000
#define MDED17MASK_RD(src)                           (((src) & 0x00020000)>>17)
#define MDED17MASK_WR(src)                      (((u32)(src)<<17) & 0x00020000)
#define MDED17MASK_SET(dst,src) \
                      (((dst) & ~0x00020000) | (((u32)(src)<<17) & 0x00020000))
/*    Mask Register Fields MDED16Mask    */
#define MDED16MASK_WIDTH                                                      1
#define MDED16MASK_SHIFT                                                     16
#define MDED16MASK_MASK                                              0x00010000
#define MDED16MASK_RD(src)                           (((src) & 0x00010000)>>16)
#define MDED16MASK_WR(src)                      (((u32)(src)<<16) & 0x00010000)
#define MDED16MASK_SET(dst,src) \
                      (((dst) & ~0x00010000) | (((u32)(src)<<16) & 0x00010000))
/*    Mask Register Fields MDED15Mask    */
#define MDED15MASK_WIDTH                                                      1
#define MDED15MASK_SHIFT                                                     15
#define MDED15MASK_MASK                                              0x00008000
#define MDED15MASK_RD(src)                           (((src) & 0x00008000)>>15)
#define MDED15MASK_WR(src)                      (((u32)(src)<<15) & 0x00008000)
#define MDED15MASK_SET(dst,src) \
                      (((dst) & ~0x00008000) | (((u32)(src)<<15) & 0x00008000))
/*    Mask Register Fields MDED14Mask    */
#define MDED14MASK_WIDTH                                                      1
#define MDED14MASK_SHIFT                                                     14
#define MDED14MASK_MASK                                              0x00004000
#define MDED14MASK_RD(src)                           (((src) & 0x00004000)>>14)
#define MDED14MASK_WR(src)                      (((u32)(src)<<14) & 0x00004000)
#define MDED14MASK_SET(dst,src) \
                      (((dst) & ~0x00004000) | (((u32)(src)<<14) & 0x00004000))
/*    Mask Register Fields MDED13Mask    */
#define MDED13MASK_WIDTH                                                      1
#define MDED13MASK_SHIFT                                                     13
#define MDED13MASK_MASK                                              0x00002000
#define MDED13MASK_RD(src)                           (((src) & 0x00002000)>>13)
#define MDED13MASK_WR(src)                      (((u32)(src)<<13) & 0x00002000)
#define MDED13MASK_SET(dst,src) \
                      (((dst) & ~0x00002000) | (((u32)(src)<<13) & 0x00002000))
/*    Mask Register Fields MDED12Mask    */
#define MDED12MASK_WIDTH                                                      1
#define MDED12MASK_SHIFT                                                     12
#define MDED12MASK_MASK                                              0x00001000
#define MDED12MASK_RD(src)                           (((src) & 0x00001000)>>12)
#define MDED12MASK_WR(src)                      (((u32)(src)<<12) & 0x00001000)
#define MDED12MASK_SET(dst,src) \
                      (((dst) & ~0x00001000) | (((u32)(src)<<12) & 0x00001000))
/*    Mask Register Fields MDED11Mask    */
#define MDED11MASK_WIDTH                                                      1
#define MDED11MASK_SHIFT                                                     11
#define MDED11MASK_MASK                                              0x00000800
#define MDED11MASK_RD(src)                           (((src) & 0x00000800)>>11)
#define MDED11MASK_WR(src)                      (((u32)(src)<<11) & 0x00000800)
#define MDED11MASK_SET(dst,src) \
                      (((dst) & ~0x00000800) | (((u32)(src)<<11) & 0x00000800))
/*    Mask Register Fields MDED10Mask    */
#define MDED10MASK_WIDTH                                                      1
#define MDED10MASK_SHIFT                                                     10
#define MDED10MASK_MASK                                              0x00000400
#define MDED10MASK_RD(src)                           (((src) & 0x00000400)>>10)
#define MDED10MASK_WR(src)                      (((u32)(src)<<10) & 0x00000400)
#define MDED10MASK_SET(dst,src) \
                      (((dst) & ~0x00000400) | (((u32)(src)<<10) & 0x00000400))
/*    Mask Register Fields MDED9Mask    */
#define MDED9MASK_WIDTH                                                       1
#define MDED9MASK_SHIFT                                                       9
#define MDED9MASK_MASK                                               0x00000200
#define MDED9MASK_RD(src)                             (((src) & 0x00000200)>>9)
#define MDED9MASK_WR(src)                        (((u32)(src)<<9) & 0x00000200)
#define MDED9MASK_SET(dst,src) \
                       (((dst) & ~0x00000200) | (((u32)(src)<<9) & 0x00000200))
/*    Mask Register Fields MDED8Mask    */
#define MDED8MASK_WIDTH                                                       1
#define MDED8MASK_SHIFT                                                       8
#define MDED8MASK_MASK                                               0x00000100
#define MDED8MASK_RD(src)                             (((src) & 0x00000100)>>8)
#define MDED8MASK_WR(src)                        (((u32)(src)<<8) & 0x00000100)
#define MDED8MASK_SET(dst,src) \
                       (((dst) & ~0x00000100) | (((u32)(src)<<8) & 0x00000100))
/*    Mask Register Fields MDED7Mask    */
#define MDED7MASK_WIDTH                                                       1
#define MDED7MASK_SHIFT                                                       7
#define MDED7MASK_MASK                                               0x00000080
#define MDED7MASK_RD(src)                             (((src) & 0x00000080)>>7)
#define MDED7MASK_WR(src)                        (((u32)(src)<<7) & 0x00000080)
#define MDED7MASK_SET(dst,src) \
                       (((dst) & ~0x00000080) | (((u32)(src)<<7) & 0x00000080))
/*    Mask Register Fields MDED6Mask    */
#define MDED6MASK_WIDTH                                                       1
#define MDED6MASK_SHIFT                                                       6
#define MDED6MASK_MASK                                               0x00000040
#define MDED6MASK_RD(src)                             (((src) & 0x00000040)>>6)
#define MDED6MASK_WR(src)                        (((u32)(src)<<6) & 0x00000040)
#define MDED6MASK_SET(dst,src) \
                       (((dst) & ~0x00000040) | (((u32)(src)<<6) & 0x00000040))
/*    Mask Register Fields MDED5Mask    */
#define MDED5MASK_WIDTH                                                       1
#define MDED5MASK_SHIFT                                                       5
#define MDED5MASK_MASK                                               0x00000020
#define MDED5MASK_RD(src)                             (((src) & 0x00000020)>>5)
#define MDED5MASK_WR(src)                        (((u32)(src)<<5) & 0x00000020)
#define MDED5MASK_SET(dst,src) \
                       (((dst) & ~0x00000020) | (((u32)(src)<<5) & 0x00000020))
/*    Mask Register Fields MDED4Mask    */
#define MDED4MASK_WIDTH                                                       1
#define MDED4MASK_SHIFT                                                       4
#define MDED4MASK_MASK                                               0x00000010
#define MDED4MASK_RD(src)                             (((src) & 0x00000010)>>4)
#define MDED4MASK_WR(src)                        (((u32)(src)<<4) & 0x00000010)
#define MDED4MASK_SET(dst,src) \
                       (((dst) & ~0x00000010) | (((u32)(src)<<4) & 0x00000010))
/*    Mask Register Fields MDED3Mask    */
#define MDED3MASK_WIDTH                                                       1
#define MDED3MASK_SHIFT                                                       3
#define MDED3MASK_MASK                                               0x00000008
#define MDED3MASK_RD(src)                             (((src) & 0x00000008)>>3)
#define MDED3MASK_WR(src)                        (((u32)(src)<<3) & 0x00000008)
#define MDED3MASK_SET(dst,src) \
                       (((dst) & ~0x00000008) | (((u32)(src)<<3) & 0x00000008))
/*    Mask Register Fields MDED2Mask    */
#define MDED2MASK_WIDTH                                                       1
#define MDED2MASK_SHIFT                                                       2
#define MDED2MASK_MASK                                               0x00000004
#define MDED2MASK_RD(src)                             (((src) & 0x00000004)>>2)
#define MDED2MASK_WR(src)                        (((u32)(src)<<2) & 0x00000004)
#define MDED2MASK_SET(dst,src) \
                       (((dst) & ~0x00000004) | (((u32)(src)<<2) & 0x00000004))
/*    Mask Register Fields MDED1Mask    */
#define MDED1MASK_WIDTH                                                       1
#define MDED1MASK_SHIFT                                                       1
#define MDED1MASK_MASK                                               0x00000002
#define MDED1MASK_RD(src)                             (((src) & 0x00000002)>>1)
#define MDED1MASK_WR(src)                        (((u32)(src)<<1) & 0x00000002)
#define MDED1MASK_SET(dst,src) \
                       (((dst) & ~0x00000002) | (((u32)(src)<<1) & 0x00000002))
/*    Mask Register Fields MDED0Mask    */
#define MDED0MASK_WIDTH                                                       1
#define MDED0MASK_SHIFT                                                       0
#define MDED0MASK_MASK                                               0x00000001
#define MDED0MASK_RD(src)                                (((src) & 0x00000001))
#define MDED0MASK_WR(src)                           (((u32)(src)) & 0x00000001)
#define MDED0MASK_SET(dst,src) \
                          (((dst) & ~0x00000001) | (((u32)(src)) & 0x00000001))

/*	Register GLBL_MDED_ERRH	*/ 
/*	 Fields MDED63	 */
#define MDED63_WIDTH                                                          1
#define MDED63_SHIFT                                                         31
#define MDED63_MASK                                                  0x80000000
#define MDED63_RD(src)                               (((src) & 0x80000000)>>31)
#define MDED63_WR(src)                          (((u32)(src)<<31) & 0x80000000)
#define MDED63_SET(dst,src) \
                      (((dst) & ~0x80000000) | (((u32)(src)<<31) & 0x80000000))
/*	 Fields MDED62	 */
#define MDED62_WIDTH                                                          1
#define MDED62_SHIFT                                                         30
#define MDED62_MASK                                                  0x40000000
#define MDED62_RD(src)                               (((src) & 0x40000000)>>30)
#define MDED62_WR(src)                          (((u32)(src)<<30) & 0x40000000)
#define MDED62_SET(dst,src) \
                      (((dst) & ~0x40000000) | (((u32)(src)<<30) & 0x40000000))
/*	 Fields MDED61	 */
#define MDED61_WIDTH                                                          1
#define MDED61_SHIFT                                                         29
#define MDED61_MASK                                                  0x20000000
#define MDED61_RD(src)                               (((src) & 0x20000000)>>29)
#define MDED61_WR(src)                          (((u32)(src)<<29) & 0x20000000)
#define MDED61_SET(dst,src) \
                      (((dst) & ~0x20000000) | (((u32)(src)<<29) & 0x20000000))
/*	 Fields MDED60	 */
#define MDED60_WIDTH                                                          1
#define MDED60_SHIFT                                                         28
#define MDED60_MASK                                                  0x10000000
#define MDED60_RD(src)                               (((src) & 0x10000000)>>28)
#define MDED60_WR(src)                          (((u32)(src)<<28) & 0x10000000)
#define MDED60_SET(dst,src) \
                      (((dst) & ~0x10000000) | (((u32)(src)<<28) & 0x10000000))
/*	 Fields MDED59	 */
#define MDED59_WIDTH                                                          1
#define MDED59_SHIFT                                                         27
#define MDED59_MASK                                                  0x08000000
#define MDED59_RD(src)                               (((src) & 0x08000000)>>27)
#define MDED59_WR(src)                          (((u32)(src)<<27) & 0x08000000)
#define MDED59_SET(dst,src) \
                      (((dst) & ~0x08000000) | (((u32)(src)<<27) & 0x08000000))
/*	 Fields MDED58	 */
#define MDED58_WIDTH                                                          1
#define MDED58_SHIFT                                                         26
#define MDED58_MASK                                                  0x04000000
#define MDED58_RD(src)                               (((src) & 0x04000000)>>26)
#define MDED58_WR(src)                          (((u32)(src)<<26) & 0x04000000)
#define MDED58_SET(dst,src) \
                      (((dst) & ~0x04000000) | (((u32)(src)<<26) & 0x04000000))
/*	 Fields MDED57	 */
#define MDED57_WIDTH                                                          1
#define MDED57_SHIFT                                                         25
#define MDED57_MASK                                                  0x02000000
#define MDED57_RD(src)                               (((src) & 0x02000000)>>25)
#define MDED57_WR(src)                          (((u32)(src)<<25) & 0x02000000)
#define MDED57_SET(dst,src) \
                      (((dst) & ~0x02000000) | (((u32)(src)<<25) & 0x02000000))
/*	 Fields MDED56	 */
#define MDED56_WIDTH                                                          1
#define MDED56_SHIFT                                                         24
#define MDED56_MASK                                                  0x01000000
#define MDED56_RD(src)                               (((src) & 0x01000000)>>24)
#define MDED56_WR(src)                          (((u32)(src)<<24) & 0x01000000)
#define MDED56_SET(dst,src) \
                      (((dst) & ~0x01000000) | (((u32)(src)<<24) & 0x01000000))
/*	 Fields MDED55	 */
#define MDED55_WIDTH                                                          1
#define MDED55_SHIFT                                                         23
#define MDED55_MASK                                                  0x00800000
#define MDED55_RD(src)                               (((src) & 0x00800000)>>23)
#define MDED55_WR(src)                          (((u32)(src)<<23) & 0x00800000)
#define MDED55_SET(dst,src) \
                      (((dst) & ~0x00800000) | (((u32)(src)<<23) & 0x00800000))
/*	 Fields MDED54	 */
#define MDED54_WIDTH                                                          1
#define MDED54_SHIFT                                                         22
#define MDED54_MASK                                                  0x00400000
#define MDED54_RD(src)                               (((src) & 0x00400000)>>22)
#define MDED54_WR(src)                          (((u32)(src)<<22) & 0x00400000)
#define MDED54_SET(dst,src) \
                      (((dst) & ~0x00400000) | (((u32)(src)<<22) & 0x00400000))
/*	 Fields MDED53	 */
#define MDED53_WIDTH                                                          1
#define MDED53_SHIFT                                                         21
#define MDED53_MASK                                                  0x00200000
#define MDED53_RD(src)                               (((src) & 0x00200000)>>21)
#define MDED53_WR(src)                          (((u32)(src)<<21) & 0x00200000)
#define MDED53_SET(dst,src) \
                      (((dst) & ~0x00200000) | (((u32)(src)<<21) & 0x00200000))
/*	 Fields MDED52	 */
#define MDED52_WIDTH                                                          1
#define MDED52_SHIFT                                                         20
#define MDED52_MASK                                                  0x00100000
#define MDED52_RD(src)                               (((src) & 0x00100000)>>20)
#define MDED52_WR(src)                          (((u32)(src)<<20) & 0x00100000)
#define MDED52_SET(dst,src) \
                      (((dst) & ~0x00100000) | (((u32)(src)<<20) & 0x00100000))
/*	 Fields MDED51	 */
#define MDED51_WIDTH                                                          1
#define MDED51_SHIFT                                                         19
#define MDED51_MASK                                                  0x00080000
#define MDED51_RD(src)                               (((src) & 0x00080000)>>19)
#define MDED51_WR(src)                          (((u32)(src)<<19) & 0x00080000)
#define MDED51_SET(dst,src) \
                      (((dst) & ~0x00080000) | (((u32)(src)<<19) & 0x00080000))
/*	 Fields MDED50	 */
#define MDED50_WIDTH                                                          1
#define MDED50_SHIFT                                                         18
#define MDED50_MASK                                                  0x00040000
#define MDED50_RD(src)                               (((src) & 0x00040000)>>18)
#define MDED50_WR(src)                          (((u32)(src)<<18) & 0x00040000)
#define MDED50_SET(dst,src) \
                      (((dst) & ~0x00040000) | (((u32)(src)<<18) & 0x00040000))
/*	 Fields MDED49	 */
#define MDED49_WIDTH                                                          1
#define MDED49_SHIFT                                                         17
#define MDED49_MASK                                                  0x00020000
#define MDED49_RD(src)                               (((src) & 0x00020000)>>17)
#define MDED49_WR(src)                          (((u32)(src)<<17) & 0x00020000)
#define MDED49_SET(dst,src) \
                      (((dst) & ~0x00020000) | (((u32)(src)<<17) & 0x00020000))
/*	 Fields MDED48	 */
#define MDED48_WIDTH                                                          1
#define MDED48_SHIFT                                                         16
#define MDED48_MASK                                                  0x00010000
#define MDED48_RD(src)                               (((src) & 0x00010000)>>16)
#define MDED48_WR(src)                          (((u32)(src)<<16) & 0x00010000)
#define MDED48_SET(dst,src) \
                      (((dst) & ~0x00010000) | (((u32)(src)<<16) & 0x00010000))
/*	 Fields MDED47	 */
#define MDED47_WIDTH                                                          1
#define MDED47_SHIFT                                                         15
#define MDED47_MASK                                                  0x00008000
#define MDED47_RD(src)                               (((src) & 0x00008000)>>15)
#define MDED47_WR(src)                          (((u32)(src)<<15) & 0x00008000)
#define MDED47_SET(dst,src) \
                      (((dst) & ~0x00008000) | (((u32)(src)<<15) & 0x00008000))
/*	 Fields MDED46	 */
#define MDED46_WIDTH                                                          1
#define MDED46_SHIFT                                                         14
#define MDED46_MASK                                                  0x00004000
#define MDED46_RD(src)                               (((src) & 0x00004000)>>14)
#define MDED46_WR(src)                          (((u32)(src)<<14) & 0x00004000)
#define MDED46_SET(dst,src) \
                      (((dst) & ~0x00004000) | (((u32)(src)<<14) & 0x00004000))
/*	 Fields MDED45	 */
#define MDED45_WIDTH                                                          1
#define MDED45_SHIFT                                                         13
#define MDED45_MASK                                                  0x00002000
#define MDED45_RD(src)                               (((src) & 0x00002000)>>13)
#define MDED45_WR(src)                          (((u32)(src)<<13) & 0x00002000)
#define MDED45_SET(dst,src) \
                      (((dst) & ~0x00002000) | (((u32)(src)<<13) & 0x00002000))
/*	 Fields MDED44	 */
#define MDED44_WIDTH                                                          1
#define MDED44_SHIFT                                                         12
#define MDED44_MASK                                                  0x00001000
#define MDED44_RD(src)                               (((src) & 0x00001000)>>12)
#define MDED44_WR(src)                          (((u32)(src)<<12) & 0x00001000)
#define MDED44_SET(dst,src) \
                      (((dst) & ~0x00001000) | (((u32)(src)<<12) & 0x00001000))
/*	 Fields MDED43	 */
#define MDED43_WIDTH                                                          1
#define MDED43_SHIFT                                                         11
#define MDED43_MASK                                                  0x00000800
#define MDED43_RD(src)                               (((src) & 0x00000800)>>11)
#define MDED43_WR(src)                          (((u32)(src)<<11) & 0x00000800)
#define MDED43_SET(dst,src) \
                      (((dst) & ~0x00000800) | (((u32)(src)<<11) & 0x00000800))
/*	 Fields MDED42	 */
#define MDED42_WIDTH                                                          1
#define MDED42_SHIFT                                                         10
#define MDED42_MASK                                                  0x00000400
#define MDED42_RD(src)                               (((src) & 0x00000400)>>10)
#define MDED42_WR(src)                          (((u32)(src)<<10) & 0x00000400)
#define MDED42_SET(dst,src) \
                      (((dst) & ~0x00000400) | (((u32)(src)<<10) & 0x00000400))
/*	 Fields MDED41	 */
#define MDED41_WIDTH                                                          1
#define MDED41_SHIFT                                                          9
#define MDED41_MASK                                                  0x00000200
#define MDED41_RD(src)                                (((src) & 0x00000200)>>9)
#define MDED41_WR(src)                           (((u32)(src)<<9) & 0x00000200)
#define MDED41_SET(dst,src) \
                       (((dst) & ~0x00000200) | (((u32)(src)<<9) & 0x00000200))
/*	 Fields MDED40	 */
#define MDED40_WIDTH                                                          1
#define MDED40_SHIFT                                                          8
#define MDED40_MASK                                                  0x00000100
#define MDED40_RD(src)                                (((src) & 0x00000100)>>8)
#define MDED40_WR(src)                           (((u32)(src)<<8) & 0x00000100)
#define MDED40_SET(dst,src) \
                       (((dst) & ~0x00000100) | (((u32)(src)<<8) & 0x00000100))
/*	 Fields MDED39	 */
#define MDED39_WIDTH                                                          1
#define MDED39_SHIFT                                                          7
#define MDED39_MASK                                                  0x00000080
#define MDED39_RD(src)                                (((src) & 0x00000080)>>7)
#define MDED39_WR(src)                           (((u32)(src)<<7) & 0x00000080)
#define MDED39_SET(dst,src) \
                       (((dst) & ~0x00000080) | (((u32)(src)<<7) & 0x00000080))
/*	 Fields MDED38	 */
#define MDED38_WIDTH                                                          1
#define MDED38_SHIFT                                                          6
#define MDED38_MASK                                                  0x00000040
#define MDED38_RD(src)                                (((src) & 0x00000040)>>6)
#define MDED38_WR(src)                           (((u32)(src)<<6) & 0x00000040)
#define MDED38_SET(dst,src) \
                       (((dst) & ~0x00000040) | (((u32)(src)<<6) & 0x00000040))
/*	 Fields MDED37	 */
#define MDED37_WIDTH                                                          1
#define MDED37_SHIFT                                                          5
#define MDED37_MASK                                                  0x00000020
#define MDED37_RD(src)                                (((src) & 0x00000020)>>5)
#define MDED37_WR(src)                           (((u32)(src)<<5) & 0x00000020)
#define MDED37_SET(dst,src) \
                       (((dst) & ~0x00000020) | (((u32)(src)<<5) & 0x00000020))
/*	 Fields MDED36	 */
#define MDED36_WIDTH                                                          1
#define MDED36_SHIFT                                                          4
#define MDED36_MASK                                                  0x00000010
#define MDED36_RD(src)                                (((src) & 0x00000010)>>4)
#define MDED36_WR(src)                           (((u32)(src)<<4) & 0x00000010)
#define MDED36_SET(dst,src) \
                       (((dst) & ~0x00000010) | (((u32)(src)<<4) & 0x00000010))
/*	 Fields MDED35	 */
#define MDED35_WIDTH                                                          1
#define MDED35_SHIFT                                                          3
#define MDED35_MASK                                                  0x00000008
#define MDED35_RD(src)                                (((src) & 0x00000008)>>3)
#define MDED35_WR(src)                           (((u32)(src)<<3) & 0x00000008)
#define MDED35_SET(dst,src) \
                       (((dst) & ~0x00000008) | (((u32)(src)<<3) & 0x00000008))
/*	 Fields MDED34	 */
#define MDED34_WIDTH                                                          1
#define MDED34_SHIFT                                                          2
#define MDED34_MASK                                                  0x00000004
#define MDED34_RD(src)                                (((src) & 0x00000004)>>2)
#define MDED34_WR(src)                           (((u32)(src)<<2) & 0x00000004)
#define MDED34_SET(dst,src) \
                       (((dst) & ~0x00000004) | (((u32)(src)<<2) & 0x00000004))
/*	 Fields MDED33	 */
#define MDED33_WIDTH                                                          1
#define MDED33_SHIFT                                                          1
#define MDED33_MASK                                                  0x00000002
#define MDED33_RD(src)                                (((src) & 0x00000002)>>1)
#define MDED33_WR(src)                           (((u32)(src)<<1) & 0x00000002)
#define MDED33_SET(dst,src) \
                       (((dst) & ~0x00000002) | (((u32)(src)<<1) & 0x00000002))
/*	 Fields MDED32	 */
#define MDED32_WIDTH                                                          1
#define MDED32_SHIFT                                                          0
#define MDED32_MASK                                                  0x00000001
#define MDED32_RD(src)                                   (((src) & 0x00000001))
#define MDED32_WR(src)                              (((u32)(src)) & 0x00000001)
#define MDED32_SET(dst,src) \
                          (((dst) & ~0x00000001) | (((u32)(src)) & 0x00000001))

/*	Register GLBL_MDED_ERRHMask	*/
/*    Mask Register Fields MDED63Mask    */
#define MDED63MASK_WIDTH                                                      1
#define MDED63MASK_SHIFT                                                     31
#define MDED63MASK_MASK                                              0x80000000
#define MDED63MASK_RD(src)                           (((src) & 0x80000000)>>31)
#define MDED63MASK_WR(src)                      (((u32)(src)<<31) & 0x80000000)
#define MDED63MASK_SET(dst,src) \
                      (((dst) & ~0x80000000) | (((u32)(src)<<31) & 0x80000000))
/*    Mask Register Fields MDED62Mask    */
#define MDED62MASK_WIDTH                                                      1
#define MDED62MASK_SHIFT                                                     30
#define MDED62MASK_MASK                                              0x40000000
#define MDED62MASK_RD(src)                           (((src) & 0x40000000)>>30)
#define MDED62MASK_WR(src)                      (((u32)(src)<<30) & 0x40000000)
#define MDED62MASK_SET(dst,src) \
                      (((dst) & ~0x40000000) | (((u32)(src)<<30) & 0x40000000))
/*    Mask Register Fields MDED61Mask    */
#define MDED61MASK_WIDTH                                                      1
#define MDED61MASK_SHIFT                                                     29
#define MDED61MASK_MASK                                              0x20000000
#define MDED61MASK_RD(src)                           (((src) & 0x20000000)>>29)
#define MDED61MASK_WR(src)                      (((u32)(src)<<29) & 0x20000000)
#define MDED61MASK_SET(dst,src) \
                      (((dst) & ~0x20000000) | (((u32)(src)<<29) & 0x20000000))
/*    Mask Register Fields MDED60Mask    */
#define MDED60MASK_WIDTH                                                      1
#define MDED60MASK_SHIFT                                                     28
#define MDED60MASK_MASK                                              0x10000000
#define MDED60MASK_RD(src)                           (((src) & 0x10000000)>>28)
#define MDED60MASK_WR(src)                      (((u32)(src)<<28) & 0x10000000)
#define MDED60MASK_SET(dst,src) \
                      (((dst) & ~0x10000000) | (((u32)(src)<<28) & 0x10000000))
/*    Mask Register Fields MDED59Mask    */
#define MDED59MASK_WIDTH                                                      1
#define MDED59MASK_SHIFT                                                     27
#define MDED59MASK_MASK                                              0x08000000
#define MDED59MASK_RD(src)                           (((src) & 0x08000000)>>27)
#define MDED59MASK_WR(src)                      (((u32)(src)<<27) & 0x08000000)
#define MDED59MASK_SET(dst,src) \
                      (((dst) & ~0x08000000) | (((u32)(src)<<27) & 0x08000000))
/*    Mask Register Fields MDED58Mask    */
#define MDED58MASK_WIDTH                                                      1
#define MDED58MASK_SHIFT                                                     26
#define MDED58MASK_MASK                                              0x04000000
#define MDED58MASK_RD(src)                           (((src) & 0x04000000)>>26)
#define MDED58MASK_WR(src)                      (((u32)(src)<<26) & 0x04000000)
#define MDED58MASK_SET(dst,src) \
                      (((dst) & ~0x04000000) | (((u32)(src)<<26) & 0x04000000))
/*    Mask Register Fields MDED57Mask    */
#define MDED57MASK_WIDTH                                                      1
#define MDED57MASK_SHIFT                                                     25
#define MDED57MASK_MASK                                              0x02000000
#define MDED57MASK_RD(src)                           (((src) & 0x02000000)>>25)
#define MDED57MASK_WR(src)                      (((u32)(src)<<25) & 0x02000000)
#define MDED57MASK_SET(dst,src) \
                      (((dst) & ~0x02000000) | (((u32)(src)<<25) & 0x02000000))
/*    Mask Register Fields MDED56Mask    */
#define MDED56MASK_WIDTH                                                      1
#define MDED56MASK_SHIFT                                                     24
#define MDED56MASK_MASK                                              0x01000000
#define MDED56MASK_RD(src)                           (((src) & 0x01000000)>>24)
#define MDED56MASK_WR(src)                      (((u32)(src)<<24) & 0x01000000)
#define MDED56MASK_SET(dst,src) \
                      (((dst) & ~0x01000000) | (((u32)(src)<<24) & 0x01000000))
/*    Mask Register Fields MDED55Mask    */
#define MDED55MASK_WIDTH                                                      1
#define MDED55MASK_SHIFT                                                     23
#define MDED55MASK_MASK                                              0x00800000
#define MDED55MASK_RD(src)                           (((src) & 0x00800000)>>23)
#define MDED55MASK_WR(src)                      (((u32)(src)<<23) & 0x00800000)
#define MDED55MASK_SET(dst,src) \
                      (((dst) & ~0x00800000) | (((u32)(src)<<23) & 0x00800000))
/*    Mask Register Fields MDED54Mask    */
#define MDED54MASK_WIDTH                                                      1
#define MDED54MASK_SHIFT                                                     22
#define MDED54MASK_MASK                                              0x00400000
#define MDED54MASK_RD(src)                           (((src) & 0x00400000)>>22)
#define MDED54MASK_WR(src)                      (((u32)(src)<<22) & 0x00400000)
#define MDED54MASK_SET(dst,src) \
                      (((dst) & ~0x00400000) | (((u32)(src)<<22) & 0x00400000))
/*    Mask Register Fields MDED53Mask    */
#define MDED53MASK_WIDTH                                                      1
#define MDED53MASK_SHIFT                                                     21
#define MDED53MASK_MASK                                              0x00200000
#define MDED53MASK_RD(src)                           (((src) & 0x00200000)>>21)
#define MDED53MASK_WR(src)                      (((u32)(src)<<21) & 0x00200000)
#define MDED53MASK_SET(dst,src) \
                      (((dst) & ~0x00200000) | (((u32)(src)<<21) & 0x00200000))
/*    Mask Register Fields MDED52Mask    */
#define MDED52MASK_WIDTH                                                      1
#define MDED52MASK_SHIFT                                                     20
#define MDED52MASK_MASK                                              0x00100000
#define MDED52MASK_RD(src)                           (((src) & 0x00100000)>>20)
#define MDED52MASK_WR(src)                      (((u32)(src)<<20) & 0x00100000)
#define MDED52MASK_SET(dst,src) \
                      (((dst) & ~0x00100000) | (((u32)(src)<<20) & 0x00100000))
/*    Mask Register Fields MDED51Mask    */
#define MDED51MASK_WIDTH                                                      1
#define MDED51MASK_SHIFT                                                     19
#define MDED51MASK_MASK                                              0x00080000
#define MDED51MASK_RD(src)                           (((src) & 0x00080000)>>19)
#define MDED51MASK_WR(src)                      (((u32)(src)<<19) & 0x00080000)
#define MDED51MASK_SET(dst,src) \
                      (((dst) & ~0x00080000) | (((u32)(src)<<19) & 0x00080000))
/*    Mask Register Fields MDED50Mask    */
#define MDED50MASK_WIDTH                                                      1
#define MDED50MASK_SHIFT                                                     18
#define MDED50MASK_MASK                                              0x00040000
#define MDED50MASK_RD(src)                           (((src) & 0x00040000)>>18)
#define MDED50MASK_WR(src)                      (((u32)(src)<<18) & 0x00040000)
#define MDED50MASK_SET(dst,src) \
                      (((dst) & ~0x00040000) | (((u32)(src)<<18) & 0x00040000))
/*    Mask Register Fields MDED49Mask    */
#define MDED49MASK_WIDTH                                                      1
#define MDED49MASK_SHIFT                                                     17
#define MDED49MASK_MASK                                              0x00020000
#define MDED49MASK_RD(src)                           (((src) & 0x00020000)>>17)
#define MDED49MASK_WR(src)                      (((u32)(src)<<17) & 0x00020000)
#define MDED49MASK_SET(dst,src) \
                      (((dst) & ~0x00020000) | (((u32)(src)<<17) & 0x00020000))
/*    Mask Register Fields MDED48Mask    */
#define MDED48MASK_WIDTH                                                      1
#define MDED48MASK_SHIFT                                                     16
#define MDED48MASK_MASK                                              0x00010000
#define MDED48MASK_RD(src)                           (((src) & 0x00010000)>>16)
#define MDED48MASK_WR(src)                      (((u32)(src)<<16) & 0x00010000)
#define MDED48MASK_SET(dst,src) \
                      (((dst) & ~0x00010000) | (((u32)(src)<<16) & 0x00010000))
/*    Mask Register Fields MDED47Mask    */
#define MDED47MASK_WIDTH                                                      1
#define MDED47MASK_SHIFT                                                     15
#define MDED47MASK_MASK                                              0x00008000
#define MDED47MASK_RD(src)                           (((src) & 0x00008000)>>15)
#define MDED47MASK_WR(src)                      (((u32)(src)<<15) & 0x00008000)
#define MDED47MASK_SET(dst,src) \
                      (((dst) & ~0x00008000) | (((u32)(src)<<15) & 0x00008000))
/*    Mask Register Fields MDED46Mask    */
#define MDED46MASK_WIDTH                                                      1
#define MDED46MASK_SHIFT                                                     14
#define MDED46MASK_MASK                                              0x00004000
#define MDED46MASK_RD(src)                           (((src) & 0x00004000)>>14)
#define MDED46MASK_WR(src)                      (((u32)(src)<<14) & 0x00004000)
#define MDED46MASK_SET(dst,src) \
                      (((dst) & ~0x00004000) | (((u32)(src)<<14) & 0x00004000))
/*    Mask Register Fields MDED45Mask    */
#define MDED45MASK_WIDTH                                                      1
#define MDED45MASK_SHIFT                                                     13
#define MDED45MASK_MASK                                              0x00002000
#define MDED45MASK_RD(src)                           (((src) & 0x00002000)>>13)
#define MDED45MASK_WR(src)                      (((u32)(src)<<13) & 0x00002000)
#define MDED45MASK_SET(dst,src) \
                      (((dst) & ~0x00002000) | (((u32)(src)<<13) & 0x00002000))
/*    Mask Register Fields MDED44Mask    */
#define MDED44MASK_WIDTH                                                      1
#define MDED44MASK_SHIFT                                                     12
#define MDED44MASK_MASK                                              0x00001000
#define MDED44MASK_RD(src)                           (((src) & 0x00001000)>>12)
#define MDED44MASK_WR(src)                      (((u32)(src)<<12) & 0x00001000)
#define MDED44MASK_SET(dst,src) \
                      (((dst) & ~0x00001000) | (((u32)(src)<<12) & 0x00001000))
/*    Mask Register Fields MDED43Mask    */
#define MDED43MASK_WIDTH                                                      1
#define MDED43MASK_SHIFT                                                     11
#define MDED43MASK_MASK                                              0x00000800
#define MDED43MASK_RD(src)                           (((src) & 0x00000800)>>11)
#define MDED43MASK_WR(src)                      (((u32)(src)<<11) & 0x00000800)
#define MDED43MASK_SET(dst,src) \
                      (((dst) & ~0x00000800) | (((u32)(src)<<11) & 0x00000800))
/*    Mask Register Fields MDED42Mask    */
#define MDED42MASK_WIDTH                                                      1
#define MDED42MASK_SHIFT                                                     10
#define MDED42MASK_MASK                                              0x00000400
#define MDED42MASK_RD(src)                           (((src) & 0x00000400)>>10)
#define MDED42MASK_WR(src)                      (((u32)(src)<<10) & 0x00000400)
#define MDED42MASK_SET(dst,src) \
                      (((dst) & ~0x00000400) | (((u32)(src)<<10) & 0x00000400))
/*    Mask Register Fields MDED41Mask    */
#define MDED41MASK_WIDTH                                                      1
#define MDED41MASK_SHIFT                                                      9
#define MDED41MASK_MASK                                              0x00000200
#define MDED41MASK_RD(src)                            (((src) & 0x00000200)>>9)
#define MDED41MASK_WR(src)                       (((u32)(src)<<9) & 0x00000200)
#define MDED41MASK_SET(dst,src) \
                       (((dst) & ~0x00000200) | (((u32)(src)<<9) & 0x00000200))
/*    Mask Register Fields MDED40Mask    */
#define MDED40MASK_WIDTH                                                      1
#define MDED40MASK_SHIFT                                                      8
#define MDED40MASK_MASK                                              0x00000100
#define MDED40MASK_RD(src)                            (((src) & 0x00000100)>>8)
#define MDED40MASK_WR(src)                       (((u32)(src)<<8) & 0x00000100)
#define MDED40MASK_SET(dst,src) \
                       (((dst) & ~0x00000100) | (((u32)(src)<<8) & 0x00000100))
/*    Mask Register Fields MDED39Mask    */
#define MDED39MASK_WIDTH                                                      1
#define MDED39MASK_SHIFT                                                      7
#define MDED39MASK_MASK                                              0x00000080
#define MDED39MASK_RD(src)                            (((src) & 0x00000080)>>7)
#define MDED39MASK_WR(src)                       (((u32)(src)<<7) & 0x00000080)
#define MDED39MASK_SET(dst,src) \
                       (((dst) & ~0x00000080) | (((u32)(src)<<7) & 0x00000080))
/*    Mask Register Fields MDED38Mask    */
#define MDED38MASK_WIDTH                                                      1
#define MDED38MASK_SHIFT                                                      6
#define MDED38MASK_MASK                                              0x00000040
#define MDED38MASK_RD(src)                            (((src) & 0x00000040)>>6)
#define MDED38MASK_WR(src)                       (((u32)(src)<<6) & 0x00000040)
#define MDED38MASK_SET(dst,src) \
                       (((dst) & ~0x00000040) | (((u32)(src)<<6) & 0x00000040))
/*    Mask Register Fields MDED37Mask    */
#define MDED37MASK_WIDTH                                                      1
#define MDED37MASK_SHIFT                                                      5
#define MDED37MASK_MASK                                              0x00000020
#define MDED37MASK_RD(src)                            (((src) & 0x00000020)>>5)
#define MDED37MASK_WR(src)                       (((u32)(src)<<5) & 0x00000020)
#define MDED37MASK_SET(dst,src) \
                       (((dst) & ~0x00000020) | (((u32)(src)<<5) & 0x00000020))
/*    Mask Register Fields MDED36Mask    */
#define MDED36MASK_WIDTH                                                      1
#define MDED36MASK_SHIFT                                                      4
#define MDED36MASK_MASK                                              0x00000010
#define MDED36MASK_RD(src)                            (((src) & 0x00000010)>>4)
#define MDED36MASK_WR(src)                       (((u32)(src)<<4) & 0x00000010)
#define MDED36MASK_SET(dst,src) \
                       (((dst) & ~0x00000010) | (((u32)(src)<<4) & 0x00000010))
/*    Mask Register Fields MDED35Mask    */
#define MDED35MASK_WIDTH                                                      1
#define MDED35MASK_SHIFT                                                      3
#define MDED35MASK_MASK                                              0x00000008
#define MDED35MASK_RD(src)                            (((src) & 0x00000008)>>3)
#define MDED35MASK_WR(src)                       (((u32)(src)<<3) & 0x00000008)
#define MDED35MASK_SET(dst,src) \
                       (((dst) & ~0x00000008) | (((u32)(src)<<3) & 0x00000008))
/*    Mask Register Fields MDED34Mask    */
#define MDED34MASK_WIDTH                                                      1
#define MDED34MASK_SHIFT                                                      2
#define MDED34MASK_MASK                                              0x00000004
#define MDED34MASK_RD(src)                            (((src) & 0x00000004)>>2)
#define MDED34MASK_WR(src)                       (((u32)(src)<<2) & 0x00000004)
#define MDED34MASK_SET(dst,src) \
                       (((dst) & ~0x00000004) | (((u32)(src)<<2) & 0x00000004))
/*    Mask Register Fields MDED33Mask    */
#define MDED33MASK_WIDTH                                                      1
#define MDED33MASK_SHIFT                                                      1
#define MDED33MASK_MASK                                              0x00000002
#define MDED33MASK_RD(src)                            (((src) & 0x00000002)>>1)
#define MDED33MASK_WR(src)                       (((u32)(src)<<1) & 0x00000002)
#define MDED33MASK_SET(dst,src) \
                       (((dst) & ~0x00000002) | (((u32)(src)<<1) & 0x00000002))
/*    Mask Register Fields MDED32Mask    */
#define MDED32MASK_WIDTH                                                      1
#define MDED32MASK_SHIFT                                                      0
#define MDED32MASK_MASK                                              0x00000001
#define MDED32MASK_RD(src)                               (((src) & 0x00000001))
#define MDED32MASK_WR(src)                          (((u32)(src)) & 0x00000001)
#define MDED32MASK_SET(dst,src) \
                          (((dst) & ~0x00000001) | (((u32)(src)) & 0x00000001))

/*	Register GLBL_MERR_ADDR	*/ 
/*	 Fields ERRADDRL	 */
#define ERRADDRL_WIDTH                                                       32
#define ERRADDRL_SHIFT                                                        0
#define ERRADDRL_MASK                                                0xffffffff
#define ERRADDRL_RD(src)                                 (((src) & 0xffffffff))
#define ERRADDRL_WR(src)                            (((u32)(src)) & 0xffffffff)
#define ERRADDRL_SET(dst,src) \
                          (((dst) & ~0xffffffff) | (((u32)(src)) & 0xffffffff))

/*	Register GLBL_MERR_REQINFO	*/ 
/*	 Fields ERRADDRH	 */
#define ERRADDRH_WIDTH                                                       10
#define ERRADDRH_SHIFT                                                       22
#define ERRADDRH_MASK                                                0xffc00000
#define ERRADDRH_RD(src)                             (((src) & 0xffc00000)>>22)
#define ERRADDRH_WR(src)                        (((u32)(src)<<22) & 0xffc00000)
#define ERRADDRH_SET(dst,src) \
                      (((dst) & ~0xffc00000) | (((u32)(src)<<22) & 0xffc00000))
/*	 Fields MSTRID	 */
#define MSTRID_WIDTH                                                          6
#define MSTRID_SHIFT                                                         16
#define MSTRID_MASK                                                  0x003f0000
#define MSTRID_RD(src)                               (((src) & 0x003f0000)>>16)
#define MSTRID_WR(src)                          (((u32)(src)<<16) & 0x003f0000)
#define MSTRID_SET(dst,src) \
                      (((dst) & ~0x003f0000) | (((u32)(src)<<16) & 0x003f0000))
/*	 Fields AUXINFO	 */
#define AUXINFO_WIDTH                                                         6
#define AUXINFO_SHIFT                                                        10
#define AUXINFO_MASK                                                 0x0000fc00
#define AUXINFO_RD(src)                              (((src) & 0x0000fc00)>>10)
#define AUXINFO_WR(src)                         (((u32)(src)<<10) & 0x0000fc00)
#define AUXINFO_SET(dst,src) \
                      (((dst) & ~0x0000fc00) | (((u32)(src)<<10) & 0x0000fc00))
/*	 Fields REQLEN	 */
#define REQLEN_WIDTH                                                          2
#define REQLEN_SHIFT                                                          4
#define REQLEN_MASK                                                  0x00000030
#define REQLEN_RD(src)                                (((src) & 0x00000030)>>4)
#define REQLEN_WR(src)                           (((u32)(src)<<4) & 0x00000030)
#define REQLEN_SET(dst,src) \
                       (((dst) & ~0x00000030) | (((u32)(src)<<4) & 0x00000030))
/*	 Fields REQSIZE	 */
#define REQSIZE_WIDTH                                                         3
#define REQSIZE_SHIFT                                                         1
#define REQSIZE_MASK                                                 0x0000000e
#define REQSIZE_RD(src)                               (((src) & 0x0000000e)>>1)
#define REQSIZE_WR(src)                          (((u32)(src)<<1) & 0x0000000e)
#define REQSIZE_SET(dst,src) \
                       (((dst) & ~0x0000000e) | (((u32)(src)<<1) & 0x0000000e))
/*	 Fields REQTYPE	 */
#define REQTYPE_WIDTH                                                         1
#define REQTYPE_SHIFT                                                         0
#define REQTYPE_MASK                                                 0x00000001
#define REQTYPE_RD(src)                                  (((src) & 0x00000001))
#define REQTYPE_WR(src)                             (((u32)(src)) & 0x00000001)
#define REQTYPE_SET(dst,src) \
                          (((dst) & ~0x00000001) | (((u32)(src)) & 0x00000001))

/*	Register GLBL_TRANS_ERR	*/ 
/*	 Fields MSWRPOISON	 */
#define MSWRPOISON_WIDTH                                                      1
#define MSWRPOISON_SHIFT                                                     12
#define MSWRPOISON_MASK                                              0x00001000
#define MSWRPOISON_RD(src)                           (((src) & 0x00001000)>>12)
#define MSWRPOISON_WR(src)                      (((u32)(src)<<12) & 0x00001000)
#define MSWRPOISON_SET(dst,src) \
                      (((dst) & ~0x00001000) | (((u32)(src)<<12) & 0x00001000))
/*	 Fields SWRPOISON	 */
#define SWRPOISON_WIDTH                                                       1
#define SWRPOISON_SHIFT                                                      11
#define SWRPOISON_MASK                                               0x00000800
#define SWRPOISON_RD(src)                            (((src) & 0x00000800)>>11)
#define SWRPOISON_WR(src)                       (((u32)(src)<<11) & 0x00000800)
#define SWRPOISON_SET(dst,src) \
                      (((dst) & ~0x00000800) | (((u32)(src)<<11) & 0x00000800))
/*	 Fields SWRDYTMO	 */
#define SWRDYTMO_WIDTH                                                        1
#define SWRDYTMO_SHIFT                                                       10
#define SWRDYTMO_MASK                                                0x00000400
#define SWRDYTMO_RD(src)                             (((src) & 0x00000400)>>10)
#define SWRDYTMO_WR(src)                        (((u32)(src)<<10) & 0x00000400)
#define SWRDYTMO_SET(dst,src) \
                      (((dst) & ~0x00000400) | (((u32)(src)<<10) & 0x00000400))
/*	 Fields SWRESPTMO	 */
#define SWRESPTMO_WIDTH                                                       1
#define SWRESPTMO_SHIFT                                                       9
#define SWRESPTMO_MASK                                               0x00000200
#define SWRESPTMO_RD(src)                             (((src) & 0x00000200)>>9)
#define SWRESPTMO_WR(src)                        (((u32)(src)<<9) & 0x00000200)
#define SWRESPTMO_SET(dst,src) \
                       (((dst) & ~0x00000200) | (((u32)(src)<<9) & 0x00000200))
/*	 Fields MSWRERR	 */
#define MSWRERR_WIDTH                                                         1
#define MSWRERR_SHIFT                                                         8
#define MSWRERR_MASK                                                 0x00000100
#define MSWRERR_RD(src)                               (((src) & 0x00000100)>>8)
#define MSWRERR_WR(src)                          (((u32)(src)<<8) & 0x00000100)
#define MSWRERR_SET(dst,src) \
                       (((dst) & ~0x00000100) | (((u32)(src)<<8) & 0x00000100))
/*	 Fields SWRERR	 */
#define SWRERR_WIDTH                                                          1
#define SWRERR_SHIFT                                                          7
#define SWRERR_MASK                                                  0x00000080
#define SWRERR_RD(src)                                (((src) & 0x00000080)>>7)
#define SWRERR_WR(src)                           (((u32)(src)<<7) & 0x00000080)
#define SWRERR_SET(dst,src) \
                       (((dst) & ~0x00000080) | (((u32)(src)<<7) & 0x00000080))
/*	 Fields SRRDYTMO	 */
#define SRRDYTMO_WIDTH                                                        1
#define SRRDYTMO_SHIFT                                                        3
#define SRRDYTMO_MASK                                                0x00000008
#define SRRDYTMO_RD(src)                              (((src) & 0x00000008)>>3)
#define SRRDYTMO_WR(src)                         (((u32)(src)<<3) & 0x00000008)
#define SRRDYTMO_SET(dst,src) \
                       (((dst) & ~0x00000008) | (((u32)(src)<<3) & 0x00000008))
/*	 Fields SRRESPTMO	 */
#define SRRESPTMO_WIDTH                                                       1
#define SRRESPTMO_SHIFT                                                       2
#define SRRESPTMO_MASK                                               0x00000004
#define SRRESPTMO_RD(src)                             (((src) & 0x00000004)>>2)
#define SRRESPTMO_WR(src)                        (((u32)(src)<<2) & 0x00000004)
#define SRRESPTMO_SET(dst,src) \
                       (((dst) & ~0x00000004) | (((u32)(src)<<2) & 0x00000004))
/*	 Fields MSRDERR	 */
#define MSRDERR_WIDTH                                                         1
#define MSRDERR_SHIFT                                                         1
#define MSRDERR_MASK                                                 0x00000002
#define MSRDERR_RD(src)                               (((src) & 0x00000002)>>1)
#define MSRDERR_WR(src)                          (((u32)(src)<<1) & 0x00000002)
#define MSRDERR_SET(dst,src) \
                       (((dst) & ~0x00000002) | (((u32)(src)<<1) & 0x00000002))
/*	 Fields SRDERR	 */
#define SRDERR_WIDTH                                                          1
#define SRDERR_SHIFT                                                          0
#define SRDERR_MASK                                                  0x00000001
#define SRDERR_RD(src)                                   (((src) & 0x00000001))
#define SRDERR_WR(src)                              (((u32)(src)) & 0x00000001)
#define SRDERR_SET(dst,src) \
                          (((dst) & ~0x00000001) | (((u32)(src)) & 0x00000001))

/*	Register GLBL_TRANS_ERRMask	*/
/*    Mask Register Fields MSWRPOISONMask    */
#define MSWRPOISONMASK_WIDTH                                                  1
#define MSWRPOISONMASK_SHIFT                                                 12
#define MSWRPOISONMASK_MASK                                          0x00001000
#define MSWRPOISONMASK_RD(src)                       (((src) & 0x00001000)>>12)
#define MSWRPOISONMASK_WR(src)                  (((u32)(src)<<12) & 0x00001000)
#define MSWRPOISONMASK_SET(dst,src) \
                      (((dst) & ~0x00001000) | (((u32)(src)<<12) & 0x00001000))
/*    Mask Register Fields SWRPOISONMask    */
#define SWRPOISONMASK_WIDTH                                                   1
#define SWRPOISONMASK_SHIFT                                                  11
#define SWRPOISONMASK_MASK                                           0x00000800
#define SWRPOISONMASK_RD(src)                        (((src) & 0x00000800)>>11)
#define SWRPOISONMASK_WR(src)                   (((u32)(src)<<11) & 0x00000800)
#define SWRPOISONMASK_SET(dst,src) \
                      (((dst) & ~0x00000800) | (((u32)(src)<<11) & 0x00000800))
/*    Mask Register Fields SWRDYTMOMask    */
#define SWRDYTMOMASK_WIDTH                                                    1
#define SWRDYTMOMASK_SHIFT                                                   10
#define SWRDYTMOMASK_MASK                                            0x00000400
#define SWRDYTMOMASK_RD(src)                         (((src) & 0x00000400)>>10)
#define SWRDYTMOMASK_WR(src)                    (((u32)(src)<<10) & 0x00000400)
#define SWRDYTMOMASK_SET(dst,src) \
                      (((dst) & ~0x00000400) | (((u32)(src)<<10) & 0x00000400))
/*    Mask Register Fields SWRESPTMOMask    */
#define SWRESPTMOMASK_WIDTH                                                   1
#define SWRESPTMOMASK_SHIFT                                                   9
#define SWRESPTMOMASK_MASK                                           0x00000200
#define SWRESPTMOMASK_RD(src)                         (((src) & 0x00000200)>>9)
#define SWRESPTMOMASK_WR(src)                    (((u32)(src)<<9) & 0x00000200)
#define SWRESPTMOMASK_SET(dst,src) \
                       (((dst) & ~0x00000200) | (((u32)(src)<<9) & 0x00000200))
/*    Mask Register Fields MSWRERRMask    */
#define MSWRERRMASK_WIDTH                                                     1
#define MSWRERRMASK_SHIFT                                                     8
#define MSWRERRMASK_MASK                                             0x00000100
#define MSWRERRMASK_RD(src)                           (((src) & 0x00000100)>>8)
#define MSWRERRMASK_WR(src)                      (((u32)(src)<<8) & 0x00000100)
#define MSWRERRMASK_SET(dst,src) \
                       (((dst) & ~0x00000100) | (((u32)(src)<<8) & 0x00000100))
/*    Mask Register Fields SWRERRMask    */
#define SWRERRMASK_WIDTH                                                      1
#define SWRERRMASK_SHIFT                                                      7
#define SWRERRMASK_MASK                                              0x00000080
#define SWRERRMASK_RD(src)                            (((src) & 0x00000080)>>7)
#define SWRERRMASK_WR(src)                       (((u32)(src)<<7) & 0x00000080)
#define SWRERRMASK_SET(dst,src) \
                       (((dst) & ~0x00000080) | (((u32)(src)<<7) & 0x00000080))
/*    Mask Register Fields SRRDYTMOMask    */
#define SRRDYTMOMASK_WIDTH                                                    1
#define SRRDYTMOMASK_SHIFT                                                    3
#define SRRDYTMOMASK_MASK                                            0x00000008
#define SRRDYTMOMASK_RD(src)                          (((src) & 0x00000008)>>3)
#define SRRDYTMOMASK_WR(src)                     (((u32)(src)<<3) & 0x00000008)
#define SRRDYTMOMASK_SET(dst,src) \
                       (((dst) & ~0x00000008) | (((u32)(src)<<3) & 0x00000008))
/*    Mask Register Fields SRRESPTMOMask    */
#define SRRESPTMOMASK_WIDTH                                                   1
#define SRRESPTMOMASK_SHIFT                                                   2
#define SRRESPTMOMASK_MASK                                           0x00000004
#define SRRESPTMOMASK_RD(src)                         (((src) & 0x00000004)>>2)
#define SRRESPTMOMASK_WR(src)                    (((u32)(src)<<2) & 0x00000004)
#define SRRESPTMOMASK_SET(dst,src) \
                       (((dst) & ~0x00000004) | (((u32)(src)<<2) & 0x00000004))
/*    Mask Register Fields MSRDERRMask    */
#define MSRDERRMASK_WIDTH                                                     1
#define MSRDERRMASK_SHIFT                                                     1
#define MSRDERRMASK_MASK                                             0x00000002
#define MSRDERRMASK_RD(src)                           (((src) & 0x00000002)>>1)
#define MSRDERRMASK_WR(src)                      (((u32)(src)<<1) & 0x00000002)
#define MSRDERRMASK_SET(dst,src) \
                       (((dst) & ~0x00000002) | (((u32)(src)<<1) & 0x00000002))
/*    Mask Register Fields SRDERRMask    */
#define SRDERRMASK_WIDTH                                                      1
#define SRDERRMASK_SHIFT                                                      0
#define SRDERRMASK_MASK                                              0x00000001
#define SRDERRMASK_RD(src)                               (((src) & 0x00000001))
#define SRDERRMASK_WR(src)                          (((u32)(src)) & 0x00000001)
#define SRDERRMASK_SET(dst,src) \
                          (((dst) & ~0x00000001) | (((u32)(src)) & 0x00000001))

/*	Register GLBL_WDERR_ADDR	*/ 
/*	 Fields ERRADDRL	 */
#define ERRADDRL_F1_WIDTH                                                    32
#define ERRADDRL_F1_SHIFT                                                     0
#define ERRADDRL_F1_MASK                                             0xffffffff
#define ERRADDRL_F1_RD(src)                              (((src) & 0xffffffff))
#define ERRADDRL_F1_WR(src)                         (((u32)(src)) & 0xffffffff)
#define ERRADDRL_F1_SET(dst,src) \
                          (((dst) & ~0xffffffff) | (((u32)(src)) & 0xffffffff))

/*	Register GLBL_WDERR_REQINFO	*/ 
/*	 Fields ERRADDRH	 */
#define ERRADDRH_F1_WIDTH                                                    10
#define ERRADDRH_F1_SHIFT                                                    22
#define ERRADDRH_F1_MASK                                             0xffc00000
#define ERRADDRH_F1_RD(src)                          (((src) & 0xffc00000)>>22)
#define ERRADDRH_F1_WR(src)                     (((u32)(src)<<22) & 0xffc00000)
#define ERRADDRH_F1_SET(dst,src) \
                      (((dst) & ~0xffc00000) | (((u32)(src)<<22) & 0xffc00000))
/*	 Fields MSTRID	 */
#define MSTRID_F1_WIDTH                                                       6
#define MSTRID_F1_SHIFT                                                      16
#define MSTRID_F1_MASK                                               0x003f0000
#define MSTRID_F1_RD(src)                            (((src) & 0x003f0000)>>16)
#define MSTRID_F1_WR(src)                       (((u32)(src)<<16) & 0x003f0000)
#define MSTRID_F1_SET(dst,src) \
                      (((dst) & ~0x003f0000) | (((u32)(src)<<16) & 0x003f0000))
/*	 Fields AUXINFO	 */
#define AUXINFO_F1_WIDTH                                                      6
#define AUXINFO_F1_SHIFT                                                     10
#define AUXINFO_F1_MASK                                              0x0000fc00
#define AUXINFO_F1_RD(src)                           (((src) & 0x0000fc00)>>10)
#define AUXINFO_F1_WR(src)                      (((u32)(src)<<10) & 0x0000fc00)
#define AUXINFO_F1_SET(dst,src) \
                      (((dst) & ~0x0000fc00) | (((u32)(src)<<10) & 0x0000fc00))
/*	 Fields REQLEN	 */
#define REQLEN_F1_WIDTH                                                       2
#define REQLEN_F1_SHIFT                                                       4
#define REQLEN_F1_MASK                                               0x00000030
#define REQLEN_F1_RD(src)                             (((src) & 0x00000030)>>4)
#define REQLEN_F1_WR(src)                        (((u32)(src)<<4) & 0x00000030)
#define REQLEN_F1_SET(dst,src) \
                       (((dst) & ~0x00000030) | (((u32)(src)<<4) & 0x00000030))
/*	 Fields REQSIZE	 */
#define REQSIZE_F1_WIDTH                                                      3
#define REQSIZE_F1_SHIFT                                                      1
#define REQSIZE_F1_MASK                                              0x0000000e
#define REQSIZE_F1_RD(src)                            (((src) & 0x0000000e)>>1)
#define REQSIZE_F1_WR(src)                       (((u32)(src)<<1) & 0x0000000e)
#define REQSIZE_F1_SET(dst,src) \
                       (((dst) & ~0x0000000e) | (((u32)(src)<<1) & 0x0000000e))

/*	Register GLBL_DEVERR_ADDR	*/ 
/*	 Fields ERRADDRL	 */
#define ERRADDRL_F2_WIDTH                                                    32
#define ERRADDRL_F2_SHIFT                                                     0
#define ERRADDRL_F2_MASK                                             0xffffffff
#define ERRADDRL_F2_RD(src)                              (((src) & 0xffffffff))
#define ERRADDRL_F2_WR(src)                         (((u32)(src)) & 0xffffffff)
#define ERRADDRL_F2_SET(dst,src) \
                          (((dst) & ~0xffffffff) | (((u32)(src)) & 0xffffffff))

/*	Register GLBL_DEVERR_REQINFO	*/ 
/*	 Fields ERRADDRH	 */
#define ERRADDRH_F2_WIDTH                                                    10
#define ERRADDRH_F2_SHIFT                                                    22
#define ERRADDRH_F2_MASK                                             0xffc00000
#define ERRADDRH_F2_RD(src)                          (((src) & 0xffc00000)>>22)
#define ERRADDRH_F2_WR(src)                     (((u32)(src)<<22) & 0xffc00000)
#define ERRADDRH_F2_SET(dst,src) \
                      (((dst) & ~0xffc00000) | (((u32)(src)<<22) & 0xffc00000))
/*	 Fields MSTRID	 */
#define MSTRID_F2_WIDTH                                                       6
#define MSTRID_F2_SHIFT                                                      16
#define MSTRID_F2_MASK                                               0x003f0000
#define MSTRID_F2_RD(src)                            (((src) & 0x003f0000)>>16)
#define MSTRID_F2_WR(src)                       (((u32)(src)<<16) & 0x003f0000)
#define MSTRID_F2_SET(dst,src) \
                      (((dst) & ~0x003f0000) | (((u32)(src)<<16) & 0x003f0000))
/*	 Fields AUXINFO	 */
#define AUXINFO_F2_WIDTH                                                      6
#define AUXINFO_F2_SHIFT                                                     10
#define AUXINFO_F2_MASK                                              0x0000fc00
#define AUXINFO_F2_RD(src)                           (((src) & 0x0000fc00)>>10)
#define AUXINFO_F2_WR(src)                      (((u32)(src)<<10) & 0x0000fc00)
#define AUXINFO_F2_SET(dst,src) \
                      (((dst) & ~0x0000fc00) | (((u32)(src)<<10) & 0x0000fc00))
/*	 Fields REQLEN	 */
#define REQLEN_F2_WIDTH                                                       2
#define REQLEN_F2_SHIFT                                                       4
#define REQLEN_F2_MASK                                               0x00000030
#define REQLEN_F2_RD(src)                             (((src) & 0x00000030)>>4)
#define REQLEN_F2_WR(src)                        (((u32)(src)<<4) & 0x00000030)
#define REQLEN_F2_SET(dst,src) \
                       (((dst) & ~0x00000030) | (((u32)(src)<<4) & 0x00000030))
/*	 Fields REQSIZE	 */
#define REQSIZE_F2_WIDTH                                                      3
#define REQSIZE_F2_SHIFT                                                      1
#define REQSIZE_F2_MASK                                              0x0000000e
#define REQSIZE_F2_RD(src)                            (((src) & 0x0000000e)>>1)
#define REQSIZE_F2_WR(src)                       (((u32)(src)<<1) & 0x0000000e)
#define REQSIZE_F2_SET(dst,src) \
                       (((dst) & ~0x0000000e) | (((u32)(src)<<1) & 0x0000000e))
/*	 Fields REQTYPE	 */
#define REQTYPE_F1_WIDTH                                                      1
#define REQTYPE_F1_SHIFT                                                      0
#define REQTYPE_F1_MASK                                              0x00000001
#define REQTYPE_F1_RD(src)                               (((src) & 0x00000001))
#define REQTYPE_F1_WR(src)                          (((u32)(src)) & 0x00000001)
#define REQTYPE_F1_SET(dst,src) \
                          (((dst) & ~0x00000001) | (((u32)(src)) & 0x00000001))

/*	Register GLBL_SEC_ERRL_ALS	*/ 
/*	 Fields SEC	 */
#define SEC_WIDTH                                                            32
#define SEC_SHIFT                                                             0
#define SEC_MASK                                                     0xffffffff
#define SEC_RD(src)                                      (((src) & 0xffffffff))
#define SEC_WR(src)                                 (((u32)(src)) & 0xffffffff)
#define SEC_SET(dst,src) (((dst) & ~0xffffffff) | (((u32)(src)) & 0xffffffff))

/*	Register GLBL_SEC_ERRH_ALS	*/ 
/*	 Fields SEC	 */
#define SEC_F1_WIDTH                                                         32
#define SEC_F1_SHIFT                                                          0
#define SEC_F1_MASK                                                  0xffffffff
#define SEC_F1_RD(src)                                   (((src) & 0xffffffff))
#define SEC_F1_WR(src)                              (((u32)(src)) & 0xffffffff)
#define SEC_F1_SET(dst,src) \
                          (((dst) & ~0xffffffff) | (((u32)(src)) & 0xffffffff))

/*	Register GLBL_DED_ERRL_ALS	*/ 
/*	 Fields DED	 */
#define DED_WIDTH                                                            32
#define DED_SHIFT                                                             0
#define DED_MASK                                                     0xffffffff
#define DED_RD(src)                                      (((src) & 0xffffffff))
#define DED_WR(src)                                 (((u32)(src)) & 0xffffffff)
#define DED_SET(dst,src) (((dst) & ~0xffffffff) | (((u32)(src)) & 0xffffffff))

/*	Register GLBL_DED_ERRH_ALS	*/ 
/*	 Fields DED	 */
#define DED_F1_WIDTH                                                         32
#define DED_F1_SHIFT                                                          0
#define DED_F1_MASK                                                  0xffffffff
#define DED_F1_RD(src)                                   (((src) & 0xffffffff))
#define DED_F1_WR(src)                              (((u32)(src)) & 0xffffffff)
#define DED_F1_SET(dst,src) \
                          (((dst) & ~0xffffffff) | (((u32)(src)) & 0xffffffff))

/*	Register GLBL_TRANS_ERR_ALS	*/ 
/*	 Fields SWRPOISON	 */
#define SWRPOISON_F1_WIDTH                                                    1
#define SWRPOISON_F1_SHIFT                                                   11
#define SWRPOISON_F1_MASK                                            0x00000800
#define SWRPOISON_F1_RD(src)                         (((src) & 0x00000800)>>11)
#define SWRPOISON_F1_WR(src)                    (((u32)(src)<<11) & 0x00000800)
#define SWRPOISON_F1_SET(dst,src) \
                      (((dst) & ~0x00000800) | (((u32)(src)<<11) & 0x00000800))
/*	 Fields SWRDYTMO	 */
#define SWRDYTMO_F1_WIDTH                                                     1
#define SWRDYTMO_F1_SHIFT                                                    10
#define SWRDYTMO_F1_MASK                                             0x00000400
#define SWRDYTMO_F1_RD(src)                          (((src) & 0x00000400)>>10)
#define SWRDYTMO_F1_WR(src)                     (((u32)(src)<<10) & 0x00000400)
#define SWRDYTMO_F1_SET(dst,src) \
                      (((dst) & ~0x00000400) | (((u32)(src)<<10) & 0x00000400))
/*	 Fields SWRESPTMO	 */
#define SWRESPTMO_F1_WIDTH                                                    1
#define SWRESPTMO_F1_SHIFT                                                    9
#define SWRESPTMO_F1_MASK                                            0x00000200
#define SWRESPTMO_F1_RD(src)                          (((src) & 0x00000200)>>9)
#define SWRESPTMO_F1_WR(src)                     (((u32)(src)<<9) & 0x00000200)
#define SWRESPTMO_F1_SET(dst,src) \
                       (((dst) & ~0x00000200) | (((u32)(src)<<9) & 0x00000200))
/*	 Fields SWRERR	 */
#define SWRERR_F1_WIDTH                                                       1
#define SWRERR_F1_SHIFT                                                       7
#define SWRERR_F1_MASK                                               0x00000080
#define SWRERR_F1_RD(src)                             (((src) & 0x00000080)>>7)
#define SWRERR_F1_WR(src)                        (((u32)(src)<<7) & 0x00000080)
#define SWRERR_F1_SET(dst,src) \
                       (((dst) & ~0x00000080) | (((u32)(src)<<7) & 0x00000080))
/*	 Fields SRRDYTMO	 */
#define SRRDYTMO_F1_WIDTH                                                     1
#define SRRDYTMO_F1_SHIFT                                                     3
#define SRRDYTMO_F1_MASK                                             0x00000008
#define SRRDYTMO_F1_RD(src)                           (((src) & 0x00000008)>>3)
#define SRRDYTMO_F1_WR(src)                      (((u32)(src)<<3) & 0x00000008)
#define SRRDYTMO_F1_SET(dst,src) \
                       (((dst) & ~0x00000008) | (((u32)(src)<<3) & 0x00000008))
/*	 Fields SRRESPTMO	 */
#define SRRESPTMO_F1_WIDTH                                                    1
#define SRRESPTMO_F1_SHIFT                                                    2
#define SRRESPTMO_F1_MASK                                            0x00000004
#define SRRESPTMO_F1_RD(src)                          (((src) & 0x00000004)>>2)
#define SRRESPTMO_F1_WR(src)                     (((u32)(src)<<2) & 0x00000004)
#define SRRESPTMO_F1_SET(dst,src) \
                       (((dst) & ~0x00000004) | (((u32)(src)<<2) & 0x00000004))
/*	 Fields SRDERR	 */
#define SRDERR_F1_WIDTH                                                       1
#define SRDERR_F1_SHIFT                                                       0
#define SRDERR_F1_MASK                                               0x00000001
#define SRDERR_F1_RD(src)                                (((src) & 0x00000001))
#define SRDERR_F1_WR(src)                           (((u32)(src)) & 0x00000001)
#define SRDERR_F1_SET(dst,src) \
                          (((dst) & ~0x00000001) | (((u32)(src)) & 0x00000001))

/*	Global Base Address	*/
#define SLAVE_SHIM_CSR_BASE_ADDR			0x01f20e000ULL
#define SLAVE_SHIM_CSR_BASE_ADDR_OFFSET			0xe000

/*    Address SLAVE_SHIM_CSR  Registers */
#define CFG_SLV_RESP_TMO_CNTR_ADDR                                   0x00000004
#define CFG_SLV_RESP_TMO_CNTR_DEFAULT                                0x0000ffff
#define CFG_SLV_READY_TMO_CNTR_ADDR                                  0x00000008
#define CFG_SLV_READY_TMO_CNTR_DEFAULT                               0x0004ffff
#define INT_SLV_TMO_ADDR                                             0x0000000c
#define INT_SLV_TMO_DEFAULT                                          0x00000000
#define INT_SLV_TMOMASK_ADDR                                         0x00000010
#define CFG_AMA_MODE_ADDR                                            0x00000014
#define CFG_AMA_MODE_DEFAULT                                         0x00000000
#define CFG_SLV_CSR_TMO_CNTR_ADDR                                    0x00000018
#define CFG_SLV_CSR_TMO_CNTR_DEFAULT                                 0x0000ffff
#define CFG_MASK_DEV_ERR_RESP_ADDR                                   0x0000001c
#define CFG_MASK_DEV_ERR_RESP_DEFAULT                                0x00000000

/*	Register CFG_SLV_RESP_TMO_CNTR	*/ 
/*	 Fields CFG_CSR_POISON	 */
#define CFG_CSR_POISON_WIDTH                                                  1
#define CFG_CSR_POISON_SHIFT                                                 17
#define CFG_CSR_POISON_MASK                                          0x00020000
#define CFG_CSR_POISON_RD(src)                       (((src) & 0x00020000)>>17)
#define CFG_CSR_POISON_WR(src)                  (((u32)(src)<<17) & 0x00020000)
#define CFG_CSR_POISON_SET(dst,src) \
                      (((dst) & ~0x00020000) | (((u32)(src)<<17) & 0x00020000))
/*	 Fields CSR_ERR_RESP_EN	 */
#define CSR_ERR_RESP_EN_WIDTH                                                 1
#define CSR_ERR_RESP_EN_SHIFT                                                16
#define CSR_ERR_RESP_EN_MASK                                         0x00010000
#define CSR_ERR_RESP_EN_RD(src)                      (((src) & 0x00010000)>>16)
#define CSR_ERR_RESP_EN_WR(src)                 (((u32)(src)<<16) & 0x00010000)
#define CSR_ERR_RESP_EN_SET(dst,src) \
                      (((dst) & ~0x00010000) | (((u32)(src)<<16) & 0x00010000))
/*	 Fields CFG_CSR_RESP_TMO	 */
#define CFG_CSR_RESP_TMO_WIDTH                                               16
#define CFG_CSR_RESP_TMO_SHIFT                                                0
#define CFG_CSR_RESP_TMO_MASK                                        0x0000ffff
#define CFG_CSR_RESP_TMO_RD(src)                         (((src) & 0x0000ffff))
#define CFG_CSR_RESP_TMO_WR(src)                    (((u32)(src)) & 0x0000ffff)
#define CFG_CSR_RESP_TMO_SET(dst,src) \
                          (((dst) & ~0x0000ffff) | (((u32)(src)) & 0x0000ffff))

/*	Register CFG_SLV_READY_TMO_CNTR	*/ 
/*	 Fields CFG_CSR_READY_TMO	 */
#define CFG_CSR_READY_TMO_WIDTH                                              32
#define CFG_CSR_READY_TMO_SHIFT                                               0
#define CFG_CSR_READY_TMO_MASK                                       0xffffffff
#define CFG_CSR_READY_TMO_RD(src)                        (((src) & 0xffffffff))
#define CFG_CSR_READY_TMO_WR(src)                   (((u32)(src)) & 0xffffffff)
#define CFG_CSR_READY_TMO_SET(dst,src) \
                          (((dst) & ~0xffffffff) | (((u32)(src)) & 0xffffffff))

/*	Register INT_SLV_TMO	*/ 
/*	 Fields STS_CSR_TMO	 */
#define STS_CSR_TMO_WIDTH                                                     1
#define STS_CSR_TMO_SHIFT                                                     4
#define STS_CSR_TMO_MASK                                             0x00000010
#define STS_CSR_TMO_RD(src)                           (((src) & 0x00000010)>>4)
#define STS_CSR_TMO_WR(src)                      (((u32)(src)<<4) & 0x00000010)
#define STS_CSR_TMO_SET(dst,src) \
                       (((dst) & ~0x00000010) | (((u32)(src)<<4) & 0x00000010))
/*	 Fields STS_ARREADY_TMO	 */
#define STS_ARREADY_TMO_WIDTH                                                 1
#define STS_ARREADY_TMO_SHIFT                                                 3
#define STS_ARREADY_TMO_MASK                                         0x00000008
#define STS_ARREADY_TMO_RD(src)                       (((src) & 0x00000008)>>3)
#define STS_ARREADY_TMO_WR(src)                  (((u32)(src)<<3) & 0x00000008)
#define STS_ARREADY_TMO_SET(dst,src) \
                       (((dst) & ~0x00000008) | (((u32)(src)<<3) & 0x00000008))
/*	 Fields STS_RVALID_TMO	 */
#define STS_RVALID_TMO_WIDTH                                                  1
#define STS_RVALID_TMO_SHIFT                                                  2
#define STS_RVALID_TMO_MASK                                          0x00000004
#define STS_RVALID_TMO_RD(src)                        (((src) & 0x00000004)>>2)
#define STS_RVALID_TMO_WR(src)                   (((u32)(src)<<2) & 0x00000004)
#define STS_RVALID_TMO_SET(dst,src) \
                       (((dst) & ~0x00000004) | (((u32)(src)<<2) & 0x00000004))
/*	 Fields STS_AWREADY_TMO	 */
#define STS_AWREADY_TMO_WIDTH                                                 1
#define STS_AWREADY_TMO_SHIFT                                                 1
#define STS_AWREADY_TMO_MASK                                         0x00000002
#define STS_AWREADY_TMO_RD(src)                       (((src) & 0x00000002)>>1)
#define STS_AWREADY_TMO_WR(src)                  (((u32)(src)<<1) & 0x00000002)
#define STS_AWREADY_TMO_SET(dst,src) \
                       (((dst) & ~0x00000002) | (((u32)(src)<<1) & 0x00000002))
/*	 Fields STS_BVALID_TMO	 */
#define STS_BVALID_TMO_WIDTH                                                  1
#define STS_BVALID_TMO_SHIFT                                                  0
#define STS_BVALID_TMO_MASK                                          0x00000001
#define STS_BVALID_TMO_RD(src)                           (((src) & 0x00000001))
#define STS_BVALID_TMO_WR(src)                      (((u32)(src)) & 0x00000001)
#define STS_BVALID_TMO_SET(dst,src) \
                          (((dst) & ~0x00000001) | (((u32)(src)) & 0x00000001))

/*	Register INT_SLV_TMOMask	*/
/*    Mask Register Fields STS_CSR_TMOMask    */
#define STS_CSR_TMOMASK_WIDTH                                                 1
#define STS_CSR_TMOMASK_SHIFT                                                 4
#define STS_CSR_TMOMASK_MASK                                         0x00000010
#define STS_CSR_TMOMASK_RD(src)                       (((src) & 0x00000010)>>4)
#define STS_CSR_TMOMASK_WR(src)                  (((u32)(src)<<4) & 0x00000010)
#define STS_CSR_TMOMASK_SET(dst,src) \
                       (((dst) & ~0x00000010) | (((u32)(src)<<4) & 0x00000010))
/*    Mask Register Fields STS_ARREADY_TMOMask    */
#define STS_ARREADY_TMOMASK_WIDTH                                             1
#define STS_ARREADY_TMOMASK_SHIFT                                             3
#define STS_ARREADY_TMOMASK_MASK                                     0x00000008
#define STS_ARREADY_TMOMASK_RD(src)                   (((src) & 0x00000008)>>3)
#define STS_ARREADY_TMOMASK_WR(src)              (((u32)(src)<<3) & 0x00000008)
#define STS_ARREADY_TMOMASK_SET(dst,src) \
                       (((dst) & ~0x00000008) | (((u32)(src)<<3) & 0x00000008))
/*    Mask Register Fields STS_RVALID_TMOMask    */
#define STS_RVALID_TMOMASK_WIDTH                                              1
#define STS_RVALID_TMOMASK_SHIFT                                              2
#define STS_RVALID_TMOMASK_MASK                                      0x00000004
#define STS_RVALID_TMOMASK_RD(src)                    (((src) & 0x00000004)>>2)
#define STS_RVALID_TMOMASK_WR(src)               (((u32)(src)<<2) & 0x00000004)
#define STS_RVALID_TMOMASK_SET(dst,src) \
                       (((dst) & ~0x00000004) | (((u32)(src)<<2) & 0x00000004))
/*    Mask Register Fields STS_AWREADY_TMOMask    */
#define STS_AWREADY_TMOMASK_WIDTH                                             1
#define STS_AWREADY_TMOMASK_SHIFT                                             1
#define STS_AWREADY_TMOMASK_MASK                                     0x00000002
#define STS_AWREADY_TMOMASK_RD(src)                   (((src) & 0x00000002)>>1)
#define STS_AWREADY_TMOMASK_WR(src)              (((u32)(src)<<1) & 0x00000002)
#define STS_AWREADY_TMOMASK_SET(dst,src) \
                       (((dst) & ~0x00000002) | (((u32)(src)<<1) & 0x00000002))
/*    Mask Register Fields STS_BVALID_TMOMask    */
#define STS_BVALID_TMOMASK_WIDTH                                              1
#define STS_BVALID_TMOMASK_SHIFT                                              0
#define STS_BVALID_TMOMASK_MASK                                      0x00000001
#define STS_BVALID_TMOMASK_RD(src)                       (((src) & 0x00000001))
#define STS_BVALID_TMOMASK_WR(src)                  (((u32)(src)) & 0x00000001)
#define STS_BVALID_TMOMASK_SET(dst,src) \
                          (((dst) & ~0x00000001) | (((u32)(src)) & 0x00000001))

/*	Register CFG_AMA_MODE	*/ 
/*	 Fields CFG_RD2WR_EN	 */
#define CFG_RD2WR_EN_WIDTH                                                    1
#define CFG_RD2WR_EN_SHIFT                                                    1
#define CFG_RD2WR_EN_MASK                                            0x00000002
#define CFG_RD2WR_EN_RD(src)                          (((src) & 0x00000002)>>1)
#define CFG_RD2WR_EN_WR(src)                     (((u32)(src)<<1) & 0x00000002)
#define CFG_RD2WR_EN_SET(dst,src) \
                       (((dst) & ~0x00000002) | (((u32)(src)<<1) & 0x00000002))
/*	 Fields CFG_AMA_MODE	 */
#define QM_CFG_AMA_MODE_WIDTH                                            1
#define QM_CFG_AMA_MODE_SHIFT                                            0
#define QM_CFG_AMA_MODE_MASK                                    0x00000001
#define QM_CFG_AMA_MODE_RD(src)                     (((src) & 0x00000001))
#define QM_CFG_AMA_MODE_WR(src)                (((u32)(src)) & 0x00000001)
#define QM_CFG_AMA_MODE_SET(dst,src) \
                          (((dst) & ~0x00000001) | (((u32)(src)) & 0x00000001))

/*	Register CFG_SLV_CSR_TMO_CNTR	*/ 
/*	 Fields CFG_CSR_TMO	 */
#define CFG_CSR_TMO_WIDTH                                                    16
#define CFG_CSR_TMO_SHIFT                                                     0
#define CFG_CSR_TMO_MASK                                             0x0000ffff
#define CFG_CSR_TMO_RD(src)                              (((src) & 0x0000ffff))
#define CFG_CSR_TMO_WR(src)                         (((u32)(src)) & 0x0000ffff)
#define CFG_CSR_TMO_SET(dst,src) \
                          (((dst) & ~0x0000ffff) | (((u32)(src)) & 0x0000ffff))

/*	Register CFG_MASK_DEV_ERR_RESP	*/ 
/*	 Fields MASK_DEV_ERR_RESP	 */
#define MASK_DEV_ERR_RESP_WIDTH                                               1
#define MASK_DEV_ERR_RESP_SHIFT                                               0
#define MASK_DEV_ERR_RESP_MASK                                       0x00000001
#define MASK_DEV_ERR_RESP_RD(src)                        (((src) & 0x00000001))
#define MASK_DEV_ERR_RESP_WR(src)                   (((u32)(src)) & 0x00000001)
#define MASK_DEV_ERR_RESP_SET(dst,src) \
                          (((dst) & ~0x00000001) | (((u32)(src)) & 0x00000001))

/*	Global Base Address	*/
#define QM_MASTER_SHIM_CSR_BASE_ADDR			0x01f20f000ULL
#define QM_MASTER_SHIM_CSR_BASE_ADDR_OFFSET			0xf000

/*    Address MASTER_SHIM_CSR  Registers */
#define CFG_MST_IOB_SEL_ADDR                                         0x00000004
#define CFG_MST_IOB_SEL_DEFAULT                                      0x00000002
#define CFG_VC0_PREFETCH_ADDR                                        0x00000008
#define CFG_VC0_PREFETCH_DEFAULT                                     0x00000004
#define CFG_VC1_PREFETCH_ADDR                                        0x0000000c
#define CFG_VC1_PREFETCH_DEFAULT                                     0x00000004
#define CFG_VC2_PREFETCH_ADDR                                        0x00000010
#define CFG_VC2_PREFETCH_DEFAULT                                     0x00000004
#define VC0_TOKEN_USED_ADDR                                          0x00000014
#define VC0_TOKEN_USED_DEFAULT                                       0x00000000
#define VC1_TOKEN_USED_ADDR                                          0x00000018
#define VC1_TOKEN_USED_DEFAULT                                       0x00000000
#define VC2_TOKEN_USED_ADDR                                          0x0000001c
#define VC2_TOKEN_USED_DEFAULT                                       0x00000000
#define VC0_TOKEN_REQ_ADDR                                           0x00000020
#define VC0_TOKEN_REQ_DEFAULT                                        0x00000000
#define VC1_TOKEN_REQ_ADDR                                           0x00000024
#define VC1_TOKEN_REQ_DEFAULT                                        0x00000000
#define VC2_TOKEN_REQ_ADDR                                           0x00000028
#define VC2_TOKEN_REQ_DEFAULT                                        0x00000000

/*	Register CFG_MST_IOB_SEL	*/ 
/*	 Fields CFG_VC_BYPASS	 */
#define CFG_VC_BYPASS_WIDTH                                                   1
#define CFG_VC_BYPASS_SHIFT                                                   1
#define CFG_VC_BYPASS_MASK                                           0x00000002
#define CFG_VC_BYPASS_RD(src)                         (((src) & 0x00000002)>>1)
#define CFG_VC_BYPASS_WR(src)                    (((u32)(src)<<1) & 0x00000002)
#define CFG_VC_BYPASS_SET(dst,src) \
                       (((dst) & ~0x00000002) | (((u32)(src)<<1) & 0x00000002))
/*	 Fields CFG_MST_IOB_SEL	 */
#define CFG_MST_IOB_SEL_WIDTH                                                 1
#define CFG_MST_IOB_SEL_SHIFT                                                 0
#define CFG_MST_IOB_SEL_MASK                                         0x00000001
#define CFG_MST_IOB_SEL_RD(src)                          (((src) & 0x00000001))
#define CFG_MST_IOB_SEL_WR(src)                     (((u32)(src)) & 0x00000001)
#define CFG_MST_IOB_SEL_SET(dst,src) \
                          (((dst) & ~0x00000001) | (((u32)(src)) & 0x00000001))

/*	Register CFG_VC0_PREFETCH	*/ 
/*	 Fields CFG_VC0_PREFETCH_CNT	 */
#define CFG_VC0_PREFETCH_CNT_WIDTH                                            4
#define CFG_VC0_PREFETCH_CNT_SHIFT                                            0
#define CFG_VC0_PREFETCH_CNT_MASK                                    0x0000000f
#define CFG_VC0_PREFETCH_CNT_RD(src)                     (((src) & 0x0000000f))
#define CFG_VC0_PREFETCH_CNT_WR(src)                (((u32)(src)) & 0x0000000f)
#define CFG_VC0_PREFETCH_CNT_SET(dst,src) \
                          (((dst) & ~0x0000000f) | (((u32)(src)) & 0x0000000f))

/*	Register CFG_VC1_PREFETCH	*/ 
/*	 Fields CFG_VC1_PREFETCH_CNT	 */
#define CFG_VC1_PREFETCH_CNT_WIDTH                                            4
#define CFG_VC1_PREFETCH_CNT_SHIFT                                            0
#define CFG_VC1_PREFETCH_CNT_MASK                                    0x0000000f
#define CFG_VC1_PREFETCH_CNT_RD(src)                     (((src) & 0x0000000f))
#define CFG_VC1_PREFETCH_CNT_WR(src)                (((u32)(src)) & 0x0000000f)
#define CFG_VC1_PREFETCH_CNT_SET(dst,src) \
                          (((dst) & ~0x0000000f) | (((u32)(src)) & 0x0000000f))

/*	Register CFG_VC2_PREFETCH	*/ 
/*	 Fields CFG_VC2_PREFETCH_CNT	 */
#define CFG_VC2_PREFETCH_CNT_WIDTH                                            4
#define CFG_VC2_PREFETCH_CNT_SHIFT                                            0
#define CFG_VC2_PREFETCH_CNT_MASK                                    0x0000000f
#define CFG_VC2_PREFETCH_CNT_RD(src)                     (((src) & 0x0000000f))
#define CFG_VC2_PREFETCH_CNT_WR(src)                (((u32)(src)) & 0x0000000f)
#define CFG_VC2_PREFETCH_CNT_SET(dst,src) \
                          (((dst) & ~0x0000000f) | (((u32)(src)) & 0x0000000f))

/*	Register VC0_TOKEN_USED	*/ 
/*	 Fields VC0_TOKEN_USED	 */
#define VC0_TOKEN_USED_WIDTH                                                 32
#define VC0_TOKEN_USED_SHIFT                                                  0
#define VC0_TOKEN_USED_MASK                                          0xffffffff
#define VC0_TOKEN_USED_RD(src)                           (((src) & 0xffffffff))
#define VC0_TOKEN_USED_SET(dst,src) \
                          (((dst) & ~0xffffffff) | (((u32)(src)) & 0xffffffff))

/*	Register VC1_TOKEN_USED	*/ 
/*	 Fields VC1_TOKEN_USED	 */
#define VC1_TOKEN_USED_WIDTH                                                 32
#define VC1_TOKEN_USED_SHIFT                                                  0
#define VC1_TOKEN_USED_MASK                                          0xffffffff
#define VC1_TOKEN_USED_RD(src)                           (((src) & 0xffffffff))
#define VC1_TOKEN_USED_SET(dst,src) \
                          (((dst) & ~0xffffffff) | (((u32)(src)) & 0xffffffff))

/*	Register VC2_TOKEN_USED	*/ 
/*	 Fields VC2_TOKEN_USED	 */
#define VC2_TOKEN_USED_WIDTH                                                 32
#define VC2_TOKEN_USED_SHIFT                                                  0
#define VC2_TOKEN_USED_MASK                                          0xffffffff
#define VC2_TOKEN_USED_RD(src)                           (((src) & 0xffffffff))
#define VC2_TOKEN_USED_SET(dst,src) \
                          (((dst) & ~0xffffffff) | (((u32)(src)) & 0xffffffff))

/*	Register VC0_TOKEN_REQ	*/ 
/*	 Fields VC0_TOKEN_REQ	 */
#define VC0_TOKEN_REQ_WIDTH                                                  32
#define VC0_TOKEN_REQ_SHIFT                                                   0
#define VC0_TOKEN_REQ_MASK                                           0xffffffff
#define VC0_TOKEN_REQ_RD(src)                            (((src) & 0xffffffff))
#define VC0_TOKEN_REQ_SET(dst,src) \
                          (((dst) & ~0xffffffff) | (((u32)(src)) & 0xffffffff))

/*	Register VC1_TOKEN_REQ	*/ 
/*	 Fields VC1_TOKEN_REQ	 */
#define VC1_TOKEN_REQ_WIDTH                                                  32
#define VC1_TOKEN_REQ_SHIFT                                                   0
#define VC1_TOKEN_REQ_MASK                                           0xffffffff
#define VC1_TOKEN_REQ_RD(src)                            (((src) & 0xffffffff))
#define VC1_TOKEN_REQ_SET(dst,src) \
                          (((dst) & ~0xffffffff) | (((u32)(src)) & 0xffffffff))

/*	Register VC2_TOKEN_REQ	*/ 
/*	 Fields VC2_TOKEN_REQ	 */
#define VC2_TOKEN_REQ_WIDTH                                                  32
#define VC2_TOKEN_REQ_SHIFT                                                   0
#define VC2_TOKEN_REQ_MASK                                           0xffffffff
#define VC2_TOKEN_REQ_RD(src)                            (((src) & 0xffffffff))
#define VC2_TOKEN_REQ_SET(dst,src) \
                          (((dst) & ~0xffffffff) | (((u32)(src)) & 0xffffffff))
	
#endif /* CONFIG_STORM */

#endif /* _APM_QM_CSR_H__ */
