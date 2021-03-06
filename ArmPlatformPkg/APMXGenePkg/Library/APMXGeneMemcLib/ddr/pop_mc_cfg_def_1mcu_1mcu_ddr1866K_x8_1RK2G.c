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
 * This general setup file. The init is attached to the
 * apm_memc structure. These setup generic values for MC initialization.
 * Typically these values are over-ridden as needed 
 *
 **/

#ifdef APM_SIM

#include "apm_ddr_sdram.h"

#else //! APM_SIM

#include "common.h"

#ifdef APM_VBIOS
#include <apm_ddr_sdram.h>

#else //using UBOOT

#include <asm/arch/apm_ddr_sdram.h>

#endif
#endif

#include "ddr_mcu.h"
#include "ddr_lib.h"

int pop_mc_cfg_def_1mcu_1mcu_ddr1866K_x8_1RK2G(void *ptr)
{
	unsigned int err = 0;
	struct apm_memc *memc = (struct apm_memc *)ptr;
	struct apm_mcu *mcu;
	unsigned int iia, jjb;

	// margins to add to DDR3 MCU TIMING PARAMS
	unsigned int margin_0 = 1;
	unsigned int margin_1 = 2;

	debug
	    ("DRAM: pop_mc_cfg_def_1mcu_1mcu_ddr1866K_x8_1RK2G initialization\n");

	/* Initialize DDR structure */

	for (iia = 0; iia < CONFIG_SYS_NUM_DDR_CTLRS; iia++) {
		mcu = (struct apm_mcu *)&memc->mcu[iia];

		mcu->mcu_params.dimm_type = UDIMM;
		mcu->mcu_params.rc_en = (mcu->mcu_params.dimm_type == RDIMM
					 || mcu->mcu_params.dimm_type == RSODIMM
					 || mcu->mcu_params.dimm_type ==
					 LRDIMM) ? 1 : 0;
		mcu->mcu_params.speed = 1866;	// 1866 MHz or DFI freq 800MHz
		mcu->mcu_params.speed_desired = 1866;
		// mcu->mcu_params.ranksperslot[3]; 
		mcu->mcu_params.cl = 11;
		// 1866K_11_8
		mcu->mcu_params.t_crl = (mcu->phy_params.en_2T_adj_incr_latency) ? 11 : 10;	/* CL minus one */
		mcu->mcu_params.t_cwl = (mcu->phy_params.en_2T_adj_incr_latency) ? 9 : 8;	/* CWL  minus one */
		// NOTE: en_2T_adj_cmd_addr adds +1 to CL/CWL for Mcu-PHY but NOT Dimm!!!

		// Mcu PLL settings 
#if USE_KCTC_PLL_VALS
		mcu->mcu_params.pllctl0_odiv = 0x1;
		mcu->mcu_params.pllctl0_fbdiv = 0x7F;	// 127;  // KC value
		mcu->mcu_params.pllctl0_idiv = 3;
#else
		mcu->mcu_params.pllctl0_odiv = 0x0;
		mcu->mcu_params.pllctl0_fbdiv = 112;
		mcu->mcu_params.pllctl0_idiv = 0x5;
#endif

		/* MRS 0-4 Mode register setting */
		mcu->mcu_params.mode_reg[0] = 0xF70;
		// tWR =15ns / tCK 1.25ns  => 12 for MR0
		//D70;  // JHR 0xD60 rl 10
		mcu->mcu_params.mode_reg[1] = 0x0 | DIMM_MR1_RTTNOM_DIC;
		mcu->mcu_params.mode_reg[2] = 0x020 | DIMM_MR2_RTTWR;
		mcu->mcu_params.mode_reg[3] = 0;

#ifdef APM_RTL_SIM
		mcu->mcu_params.clks200us = 0xC8;
		mcu->mcu_params.clks500us = 0x1F4;
		mcu->mcu_params.clks6us = 0x1902;
#else
		mcu->mcu_params.clks200us = 0x3ffff;	//max 0x3_FFFF 200us in Mcu clock for 200us
		mcu->mcu_params.clks500us = 0x7ffff;	//max 0x7_FFFF
		mcu->mcu_params.clks6us = 0x1902;	//max 0x0_1FFF
#endif

		mcu->mcu_params.clkstxpr = 0x131;
		mcu->mcu_params.clkstmrd = 0x4;
		mcu->mcu_params.clkstmod = 0x11;
		mcu->mcu_params.clkstzqc_zqs = 0x80;
		mcu->mcu_params.clkstzqc_zql = 0x2FF;

		mcu->mcu_params.bank_actpre = 15 + (2 * margin_1);
		mcu->mcu_params.bank_rdpre = 3 + margin_1;
		mcu->mcu_params.bank_wrpre = 13 + margin_1;
		mcu->mcu_params.bank_preact = 5 + margin_0;
		mcu->mcu_params.bank_actact = 21 + (margin_1 + margin_0);
		mcu->mcu_params.bank_rdaact = 9 + (margin_1 + margin_0);
		mcu->mcu_params.bank_wraact = 19 + (margin_1 + margin_0);
		mcu->mcu_params.bank_actrd = 5 + margin_1;
		mcu->mcu_params.bank_actwr = 5 + margin_1;
		mcu->mcu_params.bank_actrda = 11 + margin_1;
		mcu->mcu_params.bank_actwra = 1 + margin_1;

		mcu->mcu_params.rank_actact = 2 + margin_0;
		mcu->mcu_params.rank_rdrd = 1 + margin_0;
		mcu->mcu_params.rank_wrwr = 1 + margin_0;
		mcu->mcu_params.rank_rdwr = 3 + margin_0;
		mcu->mcu_params.rank_wrrd = 10 + margin_0;
		mcu->mcu_params.rank_actfaw = 12 + (4 * margin_0);
		mcu->mcu_params.sys_rdrd = 4;
		mcu->mcu_params.sys_wrwr = 4;
		mcu->mcu_params.sys_rdwr = 5;
		mcu->mcu_params.sys_wrrd = 3;

		mcu->mcu_params.rank_refactref = 116;
		mcu->mcu_params.rank_refint = 2500;
		mcu->mcu_params.rank_ref_burst_cnt = 4;

		mcu->mcu_params.zqcctl_enable = 1;
		mcu->mcu_params.zqcctl_interval = 0x80000003;

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
		mcu->mcu_params.rank_pdxnodll = 7;
		mcu->mcu_params.rank_pdxdll = 26;
		mcu->mcu_params.rank_rdpde = 35;
		mcu->mcu_params.rank_wrpde = 50;
		mcu->mcu_params.rank_wrapde = 50;
		mcu->mcu_params.rank_odtl = 6;

		// PHY 
#ifdef APM_RTL_SIM
		mcu->phy_params.en_phy_dll_cal = 0;	// PHY parameters
#else
		mcu->phy_params.en_phy_dll_cal = 1;
#endif
		mcu->phy_params.dll_cal_lo_freq = 0;
		mcu->phy_params.WL = (mcu->mcu_params.t_cwl) + 1;
		mcu->phy_params.RL = (mcu->mcu_params.t_crl) + 1;
	}
	return err;
}				// populate_mc_default_parms
