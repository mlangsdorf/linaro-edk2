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

#ifndef __APM_ENET_MISC_H_
#define __APM_ENET_MISC_H_

#include "apm_enet_common.h"
#ifdef INT_SUPPORT
#include <linux/irqreturn.h>
#endif

int apm_enet_parse_error(u8 LErr, u8 HC, int qid);
void apm_enet_unmask_int(struct apm_data_priv *priv);
int apm_enet_enable_link_intr(struct apm_data_priv *priv, int enable);
void apm_enet_qmi_pop_pb_msg(struct apm_data_priv *priv, u32 pbn,
				u32 addroffset, u32 last, u32 *msg);
void apm_enet_qmi_read_pb_msg(struct apm_data_priv *priv, u32 pbn,
				u32 addroffset, u32 last, u32 *msg);
int apm_enet_get_pb_cnt(struct apm_data_priv *priv, int pbn);

#ifdef INT_SUPPORT
irqreturn_t apm_enet_qmi_err_irq(int irq, void *dev_instance);
irqreturn_t apm_enet_mac_err_irq(int irq, void *dev_instance);
irqreturn_t apm_enet_err_irq(int irq, void *dev_instance);
#endif

#endif /* __APM_ENET_MISC_H_ */
