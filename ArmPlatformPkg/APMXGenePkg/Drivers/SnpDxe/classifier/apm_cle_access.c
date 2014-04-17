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
#include <asm/io.h>
#else
#include "apm_cle_access.h"
#include "apm_preclass_data.h"
//#include <asm/io.h>
#endif

u64 apm_class_base_addr_p[MAX_CLE_ENGINE];
u64 apm_class_base_addr[MAX_CLE_ENGINE];

int apm_gbl_cle_rd32(u32 cid, u32 reg_offset, u32  *value)
{
	u64 addr;

#ifdef CLE_DBG	   
	if (value == NULL) {
		PCLS_DBG("Error: Null value pointer in calling %s \n",
			__FUNCTION__);
		return APM_RC_INVALID_PARM;
	}
#endif
	addr = apm_class_base_addr[cid] + reg_offset;
	*value = readl(addr);

	PCLS_DBG("CLE CSR Read at addr 0x%0llX value 0x%08X \n", (unsigned long long)addr, *value);
	return APM_RC_OK;
}

int apm_gbl_cle_wr32(u32 cid, u32 reg_offset, u32 value)
{
	u64 addr;

	addr = apm_class_base_addr[cid] + reg_offset;

	PCLS_DBG("CLE CSR Write at addr 0x%0llX value 0x%08X \n", (unsigned long long)addr, value);
	writel(value, addr);
	return APM_RC_OK;
}
