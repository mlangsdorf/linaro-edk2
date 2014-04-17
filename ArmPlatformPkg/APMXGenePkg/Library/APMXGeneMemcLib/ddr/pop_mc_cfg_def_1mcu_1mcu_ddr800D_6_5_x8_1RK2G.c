/**
 * APM X-Gene DDR3 controller code
 *
 * Copyright (c) 2013, AppliedMicro Corp. All rights reserved.
 * All rights reserved. Josh Robinson <jrobinson@apm.com>.
 *
 * This program and the accompanying materials
 * are licensed and made available under the terms and conditions of the BSD License
 * which accompanies this distribution.  The full text of the license may be found at
 * http://opensource.org/licenses/bsd-license.php
 *
 * THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
 * WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.
 *
 * This general setup file. The init is attached to the
 * apm_memc structure. These setup generic values for MC initialization.
 * Typically these values are over-ridden as needed 
 *
 **/

#ifdef APM_SIM
#include "apm_ddr_sdram.h"
#elif defined(APM_VBIOS)
#include "common.h"
#include <stdio.h>
#include <apm_ddr_sdram.h>
#elif defined(APM_TIANOCORE)
#include "apm_ddr_sdram.h"
#else
#define CONFIG_2G
#include <asm/arch/apm_ddr_sdram.h>
#endif

#include "ddr_mcu.h"
#include "ddr_lib.h"

int pop_mc_cfg_def_1mcu_1mcu_ddr800D_6_5_x8_1RK2G(void *ptr)
{
	unsigned int err = 0;
	struct apm_memc *memc = (struct apm_memc *)ptr;
	struct apm_mcu *mcu;
	unsigned int iia;

	debug
	    ("DRAM: pop_mc_cfg_def_1mcu_1mcu_ddr800D_6_5_x8_1RK2G initialization\n");

	for (iia = 0; iia < CONFIG_SYS_NUM_DDR_CTLRS; iia++) {
		mcu = (struct apm_mcu *)&memc->mcu[iia];

		mcu->mcu_params.dimm_type = UDIMM;
		mcu->mcu_params.rc_en = (mcu->mcu_params.dimm_type == RDIMM
					 || mcu->mcu_params.dimm_type == RSODIMM
					 || mcu->mcu_params.dimm_type ==
					 LRDIMM) ? 1 : 0;
		mcu->mcu_params.speed = 800;
		mcu->mcu_params.speed_desired = 800;
		// mcu->mcu_params.ranksperslot[3]; // ?? 
		mcu->mcu_params.ECCenable = 0;
		mcu->mcu_params.cl = 11;
		mcu->mcu_params.t_cwl = (mcu->phy_params.en_2T_adj_incr_latency) ? 10 : 9;	/* CL  minus one */
		mcu->mcu_params.t_crl = (mcu->phy_params.en_2T_adj_incr_latency) ? 11 : 10;	/* CWL minus one */
		// NOTE: en_2T_adj_cmd_addr adds +1 to CL/CWL for Mcu-PHY but NOT Dimm!!!

		// Mcu PLL settings 
#if USE_KCTC_PLL_VALS
		mcu->mcu_params.pllctl0_odiv = 3;
		mcu->mcu_params.pllctl0_fbdiv = 0x7F;	// 127;
		mcu->mcu_params.pllctl0_idiv = 3;
#else
		mcu->mcu_params.pllctl0_odiv = 3;
		mcu->mcu_params.pllctl0_fbdiv = 0xC0;	// 192;
		mcu->mcu_params.pllctl0_idiv = 5;
#endif

		/* MRS 0-4 Mode register setting */
		mcu->mcu_params.mode_reg[0] = 0x1520;	// CASL=6   
		// tWR =15ns / tCK 2.5ns  => 6 for MR0
		mcu->mcu_params.mode_reg[1] = 0x8 | DIMM_MR1_RTTNOM_DIC;
		mcu->mcu_params.mode_reg[2] = 0x0 | DIMM_MR2_RTTWR;
		mcu->mcu_params.mode_reg[3] = 0;

#ifdef APM_RTL_SIM
		mcu->mcu_params.clks200us = 0xC8;
		mcu->mcu_params.clks500us = 0x1F4;
		mcu->mcu_params.clks6us = 0x1902;
#else
		mcu->mcu_params.clks200us = 0x13F00;	//max 0x3_FFFF 200us in Mcu clock for 200us
		mcu->mcu_params.clks500us = 0x3FF00;	//max 0x_FFFF
		mcu->mcu_params.clks6us = 0x07F0;	//max 0x0_aFFF
#endif

		mcu->mcu_params.clkstxpr = 0x131;
		mcu->mcu_params.clkstmrd = 0x4;
		mcu->mcu_params.clkstmod = 0x11;
		mcu->mcu_params.clkstzqc_zqs = 0x80;
		mcu->mcu_params.clkstzqc_zql = 0x2FF;

		mcu->mcu_params.bank_actpre = 7 + 3;
		mcu->mcu_params.bank_rdpre = 1 + 5;
		mcu->mcu_params.bank_wrpre = 7 + 3;
		mcu->mcu_params.bank_preact = 2;	//
		mcu->mcu_params.bank_actact = 9;
		mcu->mcu_params.bank_rdaact = 4 + 3;
		mcu->mcu_params.bank_wraact = 10;
		mcu->mcu_params.bank_actrd = 2 + 3;
		mcu->mcu_params.bank_actwr = 2 + 3;
		mcu->mcu_params.bank_actrda = 5 + 3;
		mcu->mcu_params.bank_actwra = 1 + 5;

		mcu->mcu_params.rank_actact = 1 + 1;
		mcu->mcu_params.rank_rdrd = 1;
		mcu->mcu_params.rank_wrwr = 1;
		mcu->mcu_params.rank_rdwr = 4 + 1;
		mcu->mcu_params.rank_wrrd = 6 + 1;
		mcu->mcu_params.rank_actfaw = 7;
		mcu->mcu_params.sys_rdrd = 4 + 2;
		mcu->mcu_params.sys_wrwr = 4 + 2;
		mcu->mcu_params.sys_rdwr = 5 + 2;
		mcu->mcu_params.sys_wrrd = 6 + 2;

		mcu->mcu_params.rank_refactref = 72;
		mcu->mcu_params.rank_refint = 1300;
		mcu->mcu_params.rank_ref_burst_cnt = 4;

		mcu->mcu_params.zqcctl_enable = 1;
		mcu->mcu_params.zqcctl_interval = 0x8000007F;

		mcu->mcu_params.zqcdly = 15;

		mcu->mcu_params.rank_size[0] = 0x2;
		mcu->mcu_params.rank_base_high[0] = 0x8;
		mcu->mcu_params.rank_mask_high[0] = 0x3FF8;
		if (mcu->phy_tr_dly.rank_mask == 0x3) {
			mcu->mcu_params.rank_size[1] = 0x2;
			mcu->mcu_params.rank_base_high[1] = 0x10;
			mcu->mcu_params.rank_mask_high[1] = 0x3FF8;
		}

		mcu->mcu_params.rank_srxnodll = 383;
		mcu->mcu_params.rank_srxdll = 512;
		mcu->mcu_params.rank_ckemin = 6;
		mcu->mcu_params.rank_pdxnodll = 3;
		mcu->mcu_params.rank_pdxdll = 10;
		mcu->mcu_params.rank_rdpde = 15;
		mcu->mcu_params.rank_wrpde = 15;
		mcu->mcu_params.rank_wrapde = 16;
		mcu->mcu_params.rank_odtl = 3;

		// PHY 
		mcu->phy_params.en_phy_dll_cal = 0;	// PHY parameters
		mcu->phy_params.dll_cal_lo_freq = 1;
		mcu->phy_params.WL = (mcu->mcu_params.t_cwl) + 1;
		mcu->phy_params.RL = (mcu->mcu_params.t_crl) + 1;
	}

	return err;
}				// populate_mc_default_parms
