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
#endif

void dump_qstate(struct apm_qm_qstate *qstate);
int apm_qm_rx_msg_util(u32 qm_ip, int qid, int mbid);
int apm_qm_send_msg_util(u32 qm_ip, int qid, int mbid, struct apm_qm_msg64 *msg64);
int apm_qm_dealloc_buf_util(u32 qm_ip, int qid, int mbid);
int apm_qm_alloc_buf_util(u32 qm_ip, int qid, int mbid);
