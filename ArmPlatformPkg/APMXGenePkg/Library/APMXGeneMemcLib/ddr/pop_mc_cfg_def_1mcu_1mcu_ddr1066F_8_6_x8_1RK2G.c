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
#else //using UBOOT
#include "common.h"
#include <asm/arch/apm_ddr_sdram.h>
#endif

#include "ddr_mcu.h"
#include "ddr_lib.h"

int pop_mc_cfg_def_1mcu_1mcu_ddr1066F_8_6_x8_1RK2G(void *ptr)
{
	unsigned int err = 0;
	struct apm_memc *memc = (struct apm_memc *)ptr;
	struct apm_mcu *mcu;
	unsigned int iia, jjb;

	debug
	    ("DRAM: pop_mc_cfg_def_1mcu_1mcu_ddr1066F_8_6_x8_1RK2G initialization\n");

	/* Initialize DDR structure */

	for (iia = 0; iia < CONFIG_SYS_NUM_DDR_CTLRS; iia++) {
		mcu = (struct apm_mcu *)&memc->mcu[iia];

		mcu->mcu_params.dimm_type = UDIMM;
		mcu->mcu_params.rc_en = (mcu->mcu_params.dimm_type == RDIMM
					 || mcu->mcu_params.dimm_type == RSODIMM
					 || mcu->mcu_params.dimm_type ==
					 LRDIMM) ? 1 : 0;
		mcu->mcu_params.speed = 1066;
		mcu->mcu_params.speed_desired = 1066;
		// mcu->mcu_params.ranksperslot[3]; 
		mcu->mcu_params.cl = 8;
		mcu->mcu_params.t_cwl = (mcu->phy_params.en_2T_adj_incr_latency) ? 6 : 5;	/* CL  minus one */
		mcu->mcu_params.t_crl = (mcu->phy_params.en_2T_adj_incr_latency) ? 8 : 7;	/* CWL minus one */
		// NOTE: en_2T_adj_cmd_addr adds +1 to CL/CWL for Mcu-PHY but NOT Dimm!!!

		// Mcu PLL settings 
#if USE_KCTC_PLL_VALS
		mcu->mcu_params.pllctl0_odiv = 1;
		mcu->mcu_params.pllctl0_fbdiv = 0xA9;	// 169;    // period 1876 ps
		mcu->mcu_params.pllctl0_idiv = 7;
#else
		mcu->mcu_params.pllctl0_odiv = 1;
		mcu->mcu_params.pllctl0_fbdiv = 0x80;	// period 1876 ps
		mcu->mcu_params.pllctl0_idiv = 5;
#endif

		/* MRS 0-4 Mode register setting */
		mcu->mcu_params.mode_reg[0] = 0x940;
		// tWR =15ns / tCK 1.88ns  => 8 for MR0
		mcu->mcu_params.mode_reg[1] = 0x0 | DIMM_MR1_RTTNOM_DIC;
		mcu->mcu_params.mode_reg[2] = 0x008 | DIMM_MR2_RTTWR;
		mcu->mcu_params.mode_reg[3] = 0x0;

#ifdef APM_RTL_SIM
		mcu->mcu_params.clks200us = 0xC8;
		mcu->mcu_params.clks500us = 0x1F4;
		mcu->mcu_params.clks6us = 0x1902;
#else
		mcu->mcu_params.clks200us = 0x34800;	// 0x3FFFF 200us in Mcu clock for 200us
		mcu->mcu_params.clks500us = 0x72400;	// 0x7FFFF max
		mcu->mcu_params.clks6us = 0x1F02;	// 0x01FFF  12:0 ;
#endif

		mcu->mcu_params.clkstxpr = 0x1FF;
		mcu->mcu_params.clkstmrd = 0x4;
		mcu->mcu_params.clkstmod = 0x11;
		mcu->mcu_params.clkstzqc_zqs = 0x80;
		mcu->mcu_params.clkstzqc_zql = 0x2FF;

		mcu->mcu_params.bank_actpre = 9 + 3;
		mcu->mcu_params.bank_rdpre = 1 + 3;
		mcu->mcu_params.bank_wrpre = 8 + 3;
		mcu->mcu_params.bank_preact = 3 + 3;
		mcu->mcu_params.bank_actact = 12;
		mcu->mcu_params.bank_rdaact = 5 + 3;
		mcu->mcu_params.bank_wraact = 11 + 3;
		mcu->mcu_params.bank_actrd = 3 + 3;
		mcu->mcu_params.bank_actwr = 3 + 3;
		mcu->mcu_params.bank_actrda = 7 + 3;
		mcu->mcu_params.bank_actwra = 0 + 3;

		mcu->mcu_params.rank_actact = 1 + 3;
		mcu->mcu_params.rank_rdrd = 1;
		mcu->mcu_params.rank_wrwr = 1;
		mcu->mcu_params.rank_rdwr = 4 + 2;
		mcu->mcu_params.rank_wrrd = 6 + 2;
		mcu->mcu_params.rank_actfaw = 6 + 2;
		mcu->mcu_params.sys_rdrd = 4 + 2;
		mcu->mcu_params.sys_wrwr = 4 + 2;
		mcu->mcu_params.sys_rdwr = 5 + 2;
		mcu->mcu_params.sys_wrrd = 3 + 2;

		mcu->mcu_params.rank_refactref = 93;
		mcu->mcu_params.rank_refint = 1500;
		mcu->mcu_params.rank_ref_burst_cnt = 4;

		mcu->mcu_params.zqcctl_enable = 1;
		mcu->mcu_params.zqcctl_interval = 0x7F;

		mcu->mcu_params.zqcdly = 15;

		for (jjb = 0; jjb < MCU_SUPPORTED_RANKS; jjb++) {
			mcu->mcu_params.rank_size[jjb] = 0x7;
			mcu->mcu_params.rank_config[jjb] = 0x1;
			mcu->mcu_params.rank_hash[jjb] = 0x0;
			mcu->mcu_params.rank_base_low[jjb] = 0x0;
			mcu->mcu_params.rank_base_high[jjb] = 0x8 + 0x8 * jjb;
			mcu->mcu_params.rank_mask_low[jjb] = 0x0;
			mcu->mcu_params.rank_mask_high[jjb] = 0x3FF8;
		}
		mcu->mcu_params.rank_size[0] = 0x2;
		mcu->mcu_params.rank_base_high[0] = 0x8;
		mcu->mcu_params.rank_mask_high[0] = 0x3FF8;

		mcu->mcu_params.rank_srxnodll = 383;
		mcu->mcu_params.rank_srxdll = 512;
		mcu->mcu_params.rank_ckemin = 6;
		mcu->mcu_params.rank_pdxnodll = 3;
		mcu->mcu_params.rank_pdxdll = 10;
		mcu->mcu_params.rank_rdpde = 21;
		mcu->mcu_params.rank_wrpde = 21;
		mcu->mcu_params.rank_wrapde = 22;
		mcu->mcu_params.rank_odtl = 5;

		// PHY 
		mcu->phy_params.en_phy_dll_cal = 0;
		mcu->phy_params.dll_cal_lo_freq = 1;
		mcu->phy_params.WL = (mcu->mcu_params.t_cwl) + 1;
		mcu->phy_params.RL = (mcu->mcu_params.t_crl) + 1;
	}

	return err;
}				// populate_mc_default_parms
