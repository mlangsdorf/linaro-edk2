/**
 * Copyright (c) 2014, AppliedMicro Corp. All rights reserved.
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

#include "phy-xgene.h"
#include "phy-xgene-port.h"

int xgene_is_preA3(void)
{
	#define EFUSE0_SHADOW_VERSION_SHIFT     28
	#define EFUSE0_SHADOW_VERSION_MASK      0xF
	volatile void *efuse = (volatile void *) 0x1054A000ULL;
	u32 efuse0;

	efuse0 = (readl(efuse) >> EFUSE0_SHADOW_VERSION_SHIFT)
			& EFUSE0_SHADOW_VERSION_MASK;
	switch (efuse0) {
	case 0x00: /* Not marked */
		return 1;
	case 0x01: /* A2 */
		return 1;
	case 0x02: /* A3 */
		return 0;
	case 0x03: /* B0 */
		return 0;
	default:   /* Unknown */
		return 0;
	}
}
