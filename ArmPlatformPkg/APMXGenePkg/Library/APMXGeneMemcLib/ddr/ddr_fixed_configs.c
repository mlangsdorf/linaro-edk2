/**
 * APM X-Gene DDR3 controller code
 *
 * Copyright (c) 2013, AppliedMicro Corp. All rights reserved.
 * All rights reserved. Feng Kan <fkan@apm.com>
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

#if DDRLIB_DEBUGON
#define DEBUG
#define DEBUG_REGMOD
#endif

#ifdef APM_SIM
#include "apm_ddr_sdram.h"
#elif defined(APM_VBIOS)
#include <common.h>
#include <stdio.h>
#include <apm_ddr_sdram.h>

unsigned int g_ddr_wrlvl_min_smpl = 0x20;
unsigned int g_ddr_wrlvl_smpl_per_dly = 6;
#elif defined(APM_TIANOCORE)
#include "apm_ddr_sdram.h"
#else
#include <common.h>
#include <command.h>
#include <asm/io.h>
#include <asm/arch/apm_ddr_sdram.h>
#include "config.h"
#endif

#include "ddr_mcu.h"
#include "ddr_lib.h"
#include "kc_phy_util_reg_flds.h"

//======================================================================
//======================================================================
int populate_mc_default_parms(void *ptr)
{
	unsigned int err = 0;
	struct apm_memc *memc = (struct apm_memc *)ptr;
	struct apm_mcu *mcu;
	unsigned int iia, jjb, speed;
	debug("DRAM: Default MC paramters before SPD Init\n");

	/* Initialize DDR structure */
	memc->desired_dual_mcb = DESIRED_DUAL_MCB;
	memc->desired_mcb_intrlv = DESIRED_MCB_INTRLV;

	memc->full_addr = 1;

	init_phy_tr_dly_vals(&memc->mcu[0]);
	init_phy_tr_dly_vals(&memc->mcu[1]);
	init_phy_tr_dly_vals(&memc->mcu[2]);
	init_phy_tr_dly_vals(&memc->mcu[3]);

	for (iia = 0; iia < CONFIG_SYS_NUM_DDR_CTLRS; iia++) {
		mcu = (struct apm_mcu *)&memc->mcu[iia];

		mcu->mcu_params.dimm_type = UDIMM;
		mcu->mcu_params.rc_en = (mcu->mcu_params.dimm_type == RDIMM
					 || mcu->mcu_params.dimm_type == RSODIMM
					 || mcu->mcu_params.dimm_type ==
					 LRDIMM) ? 1 : 0;
		mcu->mcu_params.speed = mcu->mcu_params.speed_desired;
		mcu->mcu_params.ECCenable = mcu->mcu_params.ECCscheme ? 1 : 0;
		mcu->mcu_params.burst_len = 8;	// Mcu only does BL8
		mcu->mcu_params.minranksize =
		    (unsigned long long)2 *1024 * 1024 * 1024;
		mcu->mcu_params.activeslots = 1;
		// Slot cfg
		for (jjb = 0; jjb < CONFIG_SYS_DIMM_SLOTS_PER_CTLR; jjb++) {
			mcu->mcu_params.ranksperslot[jjb] = 0;
		}

		mcu->mcu_params.ranksperslot[0] =
		    (DIMM_RANK_MASK == 0x3) ? 2 : 1;

		// Mcu PLL settings 
		mcu->mcu_params.pllctl0_ssen = 0;
		mcu->mcu_params.pllctl0_vstep = 0;
		mcu->mcu_params.pllctl0_ss_mod = 0;
		mcu->mcu_params.pllctl0_odiv = 1;
		mcu->mcu_params.pllctl0_fbdiv = 0xA0;
		mcu->mcu_params.pllctl0_idiv = 5;
		mcu->mcu_params.pllctl1_tm_ctrl = 0;
		mcu->mcu_params.pllctl1_pdn = 0;
		mcu->mcu_params.pllctl1_bypass = 0;
		mcu->mcu_params.single_clock_mode = 0;

		mcu->mcu_params.rttnom =
		    getRttNomfromMR1(DIMM_MR1_RTTNOM_U1R_DIC);
		mcu->mcu_params.rttwr = (DIMM_MR2_RTTWR) & 0x3;
		switch (mcu->mcu_params.rttnom) {
		case 1:
			mcu->mcu_params.rttnom_wrlvl = mcu->mcu_params.rttnom;
			break;
		case 2:
			mcu->mcu_params.rttnom_wrlvl = mcu->mcu_params.rttnom;
			break;
		case 3:
			mcu->mcu_params.rttnom_wrlvl = mcu->mcu_params.rttnom;
			break;
		case 4:
			mcu->mcu_params.rttnom_wrlvl = 3;
			break;
		case 5:
			mcu->mcu_params.rttnom_wrlvl = 3;
			break;
		default:
			mcu->mcu_params.rttnom_wrlvl = 2;
			break;
		}
		mcu->mcu_params.rank_mask_disable_rttnom = 0;

#ifdef APM_RTL_SIM
		mcu->mcu_params.clks200us = 0xC8;
		mcu->mcu_params.clks500us = 0x1F4;
		mcu->mcu_params.clks6us = 0x1902;
#else
		mcu->mcu_params.clks200us = 0x5F000;	// 200us in Mcu clock for 200us
		mcu->mcu_params.clks500us = 0xAF000;
		mcu->mcu_params.clks6us = 0x1F02;	//28Jan13 - wrong values - 12:0 cannot fit- 0x2002;
#endif

		mcu->mcu_params.clkstxpr = 0x1FF;
		mcu->mcu_params.clkstmrd = 0x4;
		mcu->mcu_params.clkstmod = 0x11;
		mcu->mcu_params.clkstzqc_zqs = 0x80;
		mcu->mcu_params.clkstzqc_zql = 0x2FF;

		// Note: See Storm ODT Table (bchase)
		mcu->mcu_params.rank_wr_odt[0] = 0x5;
		mcu->mcu_params.rank_wr_odt[1] = 0x6;
		mcu->mcu_params.rank_wr_odt[2] = 0x5;
		mcu->mcu_params.rank_wr_odt[3] = 0x9;

		mcu->mcu_params.rank_wr_odt[4] = 0x5;
		mcu->mcu_params.rank_wr_odt[5] = 0x6;
		mcu->mcu_params.rank_wr_odt[6] = 0x5;
		mcu->mcu_params.rank_wr_odt[7] = 0x9;

		mcu->mcu_params.rank_rd_odt[0] = 0x4;
		mcu->mcu_params.rank_rd_odt[1] = 0x4;
		mcu->mcu_params.rank_rd_odt[2] = 0x1;
		mcu->mcu_params.rank_rd_odt[3] = 0x1;

		mcu->mcu_params.rank_rd_odt[4] = 0x4;
		mcu->mcu_params.rank_rd_odt[5] = 0x4;
		mcu->mcu_params.rank_rd_odt[6] = 0x1;
		mcu->mcu_params.rank_rd_odt[7] = 0x1;

		mcu->mcu_params.hpweight = 8;
		mcu->mcu_params.lpweight = 8;
		mcu->mcu_params.wpweight = 96;
		mcu->mcu_params.maxinterval = 1024;
		mcu->mcu_params.quantumsize = 1;
		mcu->mcu_params.agethres_hp = 2;
		mcu->mcu_params.agethres_lp = 2;
		mcu->mcu_params.agethres_wp = 2;
		mcu->mcu_params.page_mode = 1;
		mcu->mcu_params.by4_mode = 0;
		mcu->mcu_params.desired_rank_hash_en = DESIRED_RANK_HASHEN;
		mcu->mcu_params.desired_rank_hash = DESIRED_RANK_HASH;

		mcu->mcu_params.mirror_ctrl = DIMM_ADDR_MIRROR_CTRL;
		mcu->mcu_params.fast_cpu_enable = 1;

		mcu->mcu_params.rank_refactref = 200;
		mcu->mcu_params.rank_refint = 800;
		mcu->mcu_params.rank_ref_burst_cnt = 4;

		/* By default, turn on rank interleave */
		mcu->mcu_params.desired_rank_intrlv  = DESIRED_RANK_INTRLV;

		for (jjb = 0; jjb < MCU_SUPPORTED_RANKS; jjb++) {
			mcu->mcu_params.rank_size[jjb] = 0x7;
			mcu->mcu_params.rank_config[jjb] = 0x1;
			mcu->mcu_params.rank_hash[jjb] = 0x5;
			mcu->mcu_params.rank_base_low[jjb] = 0x0;
			mcu->mcu_params.rank_base_high[jjb] = 0x8 + 0x8 * jjb;
			mcu->mcu_params.rank_mask_low[jjb] = 0x0;
			mcu->mcu_params.rank_mask_high[jjb] = 0x3FF8;
		}
		mcu->mcu_params.rank_size[0] = 0x2;
		mcu->mcu_params.rank_base_high[0] = 0x8;
		mcu->mcu_params.rank_mask_high[0] = 0x3FF8;

		mcu->mcu_params.zqcctl_enable = 1;
		mcu->mcu_params.zqcctl_interval = 0x8000007F;
		mcu->mcu_params.zqcdly = 15;
		mcu->mcu_params.scrub_ctrl = 0;
		mcu->mcu_params.glb_err_ctrl = 0x10000;
		mcu->mcu_params.sleep_ctrl = 0;
		mcu->mcu_params.lsleep_ctrl = 0;
		mcu->mcu_params.dsleep_ctrl = 0;
		mcu->mcu_params.phy_pm_ctl = 0;
		mcu->mcu_params.sram_sleep_ctrl = 0;
		mcu->mcu_params.sram_rmw_ctrl = 0;

		mcu->mcu_params.tWRLVL_WW = 0x7;
		mcu->mcu_params.tRDLVL_RR = 0xF;
		mcu->phy_params.twrlvl_ww = 0xD;
		// PHY 
		mcu->phy_params.phy_train_mode = 2;
		mcu->phy_params.cfg_parity_oe = 0;
		mcu->phy_params.pevm_retrain_en = PHY_PEVM_RETRAIN_EN;

		mcu->phy_params.en_phy_dll_cal = 0;	// PHY parameters
		mcu->phy_params.dll_cal_lo_freq = 0;
		mcu->phy_params.phy_disable_pullup = KCPHY_DISABLE_PULLUP;
		mcu->phy_params.phy_short_gt_preamble_en =
		    KCPHY_SHORT_GT_PREAMBLE_EN;
		mcu->phy_params.phy_short_gt_preamble_val =
		    KCPHY_SHORT_GT_PREAMBLE_VAL;

		mcu->phy_params.phy_dis_up_54_58_5C = PHY_DIS_UP_54_58_5C;
		mcu->phy_params.init_val_cmd_addr_dly_54_58 =
		    PHY_INIT_VAL_CMD_ADDR_DELAY_54_58;
		mcu->phy_params.init_val_ctl_dly_5C = PHY_INIT_VAL_CTL_DELAY_5C;
		mcu->phy_params.en_posttr_2T_adj_cmd_addr_dly =
		    PHY_EN_POSTTR_2T_ADJ_CMD_ADDR;
		mcu->phy_params.en_2T_adj_incr_latency = 0;
		mcu->phy_params.posttr_val_2T_cmd_addr_dly =
		    PHY_POSTTR_ADJ_VAL_2T_CMD_ADDR_DELAY;

		mcu->phy_params.cfg_macro_en_val = (mcu->mcu_params.ECCenable) ?
		    KCPHY_CFG_MACRO_ENABLE_VAL : (KCPHY_CFG_MACRO_ENABLE_VAL &
						  KCPHY_CFG_MACRO_NOECC_MASK);
		mcu->phy_params.prbs_dm_status_mask = KCPHY_PRBS_DM_STATUS_MASK;

		mcu->phy_params.TRCD = 16;
		mcu->phy_params.TMOD = 16;
		mcu->phy_params.TMRD = 4;
		mcu->phy_params.TRP = 14;
		mcu->phy_params.TWLMRD = 40;
		mcu->phy_params.TWRD = 9;

#if defined(APM_SIM) || defined(APM_VBIOS)
		mcu->phy_params.zqcal_code = PHY_ZQCAL_CODE_VALUE;
		mcu->phy_params.bit_dq_stren = 0x7 & KCPHY_BIT_DQ_STREN;
		mcu->phy_params.bit_ad_stren = 0x7 & KCPHY_BIT_AD_STREN;
		mcu->phy_params.bit_cmd_stren = 0x7 & KCPHY_BIT_CMD_STREN;
		mcu->phy_params.bit_ctl_stren = 0x7 & KCPHY_BIT_CTL_STREN;
		mcu->phy_params.bit_clk_stren = 0x7 & KCPHY_BIT_CLK_STREN;

		mcu->phy_params.bit_dq_slew = 0x3 & KCPHY_BIT_DQ_SLEW;
		mcu->phy_params.bit_ad_slew = 0x3 & KCPHY_BIT_AD_SLEW;
		mcu->phy_params.bit_cmd_slew = 0x3 & KCPHY_BIT_CMD_SLEW;
		mcu->phy_params.bit_ctl_slew = 0x3 & KCPHY_BIT_CTL_SLEW;
		mcu->phy_params.bit_clk_slew = 0x3 & KCPHY_BIT_CLK_SLEW;
#endif
		mcu->phy_params.bit_odt_stren = 0x7 & KCPHY_BIT_ODT_STREN;

		// Training
		mcu->phy_tr_dly.rank_mask = DIMM_RANK_MASK;
		mcu->phy_tr_dly.phy_wrcal_rank_mask = DIMM_RANK_MASK;
		mcu->phy_tr_dly.sw_wrcal_rank_mask = 0x0;
		mcu->phy_tr_dly.rddeskew_rank_mask = mcu->phy_tr_dly.rank_mask &
		    DIMM_DESKEW_RANK_MASK;
		mcu->phy_tr_dly.wrdeskew_rank_mask = 0;

#ifdef APM_VBIOS
		mcu->phy_tr_dly.wrlvl_smpl_per_dly = g_ddr_wrlvl_smpl_per_dly;
#else
		mcu->phy_tr_dly.wrlvl_smpl_per_dly =
		    KCPHY_PEVM_WRLVL_SMPL_PER_DLY;
#endif
		mcu->phy_tr_dly.gtlvl_smpl_per_dly =
		    KCPHY_PEVM_GTLVL_SMPL_PER_DLY;
		mcu->phy_tr_dly.rdlvl_smpl_per_dly =
		    KCPHY_PEVM_RDLVL_SMPL_PER_DLY;

#if KCPHY_PEVM_STSIZE_3
		mcu->phy_tr_dly.wrlvl_dly_stsize = 3U;	/*7:0 */
		mcu->phy_tr_dly.rdlvl_dly_stsize = 1U;	/*7:0 */
		mcu->phy_tr_dly.gtlvl_dly_stsize = 3U;	/*7:0 */
#else
#if KCPHY_PEVM_STSIZE_2
		mcu->phy_tr_dly.wrlvl_dly_stsize = 2U;	/*7:0 */
		mcu->phy_tr_dly.rdlvl_dly_stsize = 1U;	/*7:0 */
		mcu->phy_tr_dly.gtlvl_dly_stsize = 2U;	/*7:0 */
#else
		mcu->phy_tr_dly.wrlvl_dly_stsize = 1U;	/*7:0 */
		mcu->phy_tr_dly.rdlvl_dly_stsize = 1U;	/*7:0 */
		mcu->phy_tr_dly.gtlvl_dly_stsize = 1U;	/*7:0 */
#endif
#endif

#ifdef APM_VBIOS
		mcu->phy_tr_dly.wrlvl_min_smpl = g_ddr_wrlvl_min_smpl;	/*7:0 */
#else
		mcu->phy_tr_dly.wrlvl_min_smpl = KCPHY_PEVM_WRLVL_MIN_SMPLS;	/*7:0 */
#endif
		mcu->phy_tr_dly.gtlvl_min_smpl = KCPHY_PEVM_GTLVL_MIN_SMPLS;	/*7:0 */

		mcu->phy_tr_dly.wrlvl_max_delay_limit = 0x3F0U;	// 0x3FF
		mcu->phy_tr_dly.gtlvl_max_delay_limit = 0x7FCU;
		mcu->phy_tr_dly.rdlvl_max_delay_limit = 0x180U;	// 0x2FF
		mcu->phy_tr_dly.wrcal_max_delay_limit = 0x3FCU;
		mcu->phy_tr_dly.cfg_gate_retrain_val = 0x80U;

		mcu->phy_params.cfg_cs_en = mcu->phy_tr_dly.rank_mask;
		mcu->phy_params.cfg_ck_en = 0xF;
		mcu->phy_params.cfg_odt_en = 0x3F;
		mcu->phy_params.cfg_cke_en = 0x3F;
	}

	// memory region
	memc->memspace.num_mem_regions = 1;
	memc->memspace.str_addr[0] = 0x80000000;
	memc->memspace.end_addr[0] = 0xFFFFFFFF;
	memc->memspace.str_addr[1] = 0x0;
	memc->memspace.end_addr[1] = 0x0;
	memc->memspace.str_addr[2] = 0x0;
	memc->memspace.end_addr[2] = 0x0;
	memc->memspace.str_addr[3] = 0x0;
	memc->memspace.end_addr[3] = 0x0;

	// load default speed ratings - same for all Mcu
	speed = memc->mcu[0].mcu_params.speed_desired;
	debug(" Mcu[%1d] Speed=%d  for default\n", mcu->id, speed);
	if (speed >= 1866) {
		err += pop_mc_cfg_def_1mcu_1mcu_ddr1600J_x8_1RK2G(ptr);
	} else if (speed >= 1600) {
		err += pop_mc_cfg_def_1mcu_1mcu_ddr1600J_x8_1RK2G(ptr);
	} else if (speed >= 1550) {
		err += pop_mc_cfg_def_1mcu_1mcu_ddr1550J_x8_1RK2G(ptr);
	} else if (speed >= 1333) {
		err += pop_mc_cfg_def_1mcu_1mcu_ddr1333H_9_7_x8_1RK2G(ptr);
	} else if (speed >= 1066) {
		err += pop_mc_cfg_def_1mcu_1mcu_ddr1066F_8_6_x8_1RK2G(ptr);
	}
	// TBD if needed else if (speed < 800) { err += pop_mc_cfg_def_1mcu_1mcu_ddr400D_6_5_x8_1RK1G(ptr); }
	else {
		err += pop_mc_cfg_def_1mcu_1mcu_ddr800D_6_5_x8_1RK2G(ptr);
	}
	return err;
}				// populate_mc_default_parms

//======================================================================
//======================================================================

int fixed_mcu_config(void *ptr)
{
	struct apm_mcu *mcu = (struct apm_mcu *)ptr;

	/*
	 * We can call other init functions here
	 * any other combinations
	 */
	return mcu_csr_config22(mcu);
}

//======================================================================
//======================================================================

int mcu_csr_config(void *ptr)
{
	return mcu_csr_config22(ptr);
}

//======================================================================
//======================================================================

int mcu_csr_config22(void *ptr)
{
	struct apm_mcu *mcu = (struct apm_mcu *)ptr;
	mcu_param_t *p = &mcu->mcu_params;
	unsigned int i, offset;

	if (!(mcu->enabled))
		return 0;
	debug(" ENTRY: %s > \n", __FUNCTION__);
	//debug(" [mcu@0x%x mp@0x%x] \n", (unsigned int)ptr,  (unsigned int)p);

	mcu->mcu_wr(mcu, MCU_REG_HPWEIGHT, p->hpweight);
	mcu->mcu_wr(mcu, MCU_REG_LPWEIGHT, p->lpweight);
	mcu->mcu_wr(mcu, MCU_REG_WPWEIGHT, p->wpweight);
	mcu->mcu_wr(mcu, MCU_REG_MAXINTERVAL, p->maxinterval);
	mcu->mcu_wr(mcu, MCU_REG_QUANTUMSIZE, p->quantumsize);
	mcu->mcu_wr(mcu, MCU_REG_AGETHRESH_HP, p->agethres_hp);
	mcu->mcu_wr(mcu, MCU_REG_AGETHRESH_LP, p->agethres_lp);
	mcu->mcu_wr(mcu, MCU_REG_AGETHRESH_WP, p->agethres_wp);
	mcu->mcu_wr(mcu, MCU_REG_PAGE_MODE, p->page_mode);
	mcu->mcu_wr(mcu, MCU_REG_HASH_CTL, p->hash_enable);
	mcu->mcu_wr(mcu, MCU_REG_DIMM_ADDR_MIRROR_CTL, p->mirror_ctrl);
	mcu->mcu_wr(mcu, MCU_REG_FAST_CPU_ENABLE, p->fast_cpu_enable);

	/*
	 * RANK programming
	 */
	for (i = 0; i < MCU_SUPPORTED_RANKS; i++) {
		offset = i * 0x40;
		mcu->mcu_wr(mcu, MCU_REG_RANK_0_SIZE + offset,
			    (p->rank_size[i]));
		mcu->mcu_wr(mcu, MCU_REG_RANK_0_CONFIG + offset,
			    (p->rank_config[i]));
		mcu->mcu_wr(mcu, MCU_REG_RANK_0_BASE + offset,
			    ((((p->rank_base_low[i]) & 0x7U) << 16)
			     | ((p->rank_base_high[i]) & 0x3FFFU)));
		mcu->mcu_wr(mcu, MCU_REG_RANK_0_MASK + offset,
			    ((((p->rank_mask_low[i]) & 0x7U) << 16)
			     | ((p->rank_mask_high[i]) & 0x3FFFU)));
		mcu->mcu_wr(mcu, MCU_REG_RANK_0_HASH_SIZE + offset,
			    (p->rank_hash[i]));
	}

	mcu->mcu_wr(mcu, MCU_REG_BY4_MODE, p->by4_mode);
	// JHR do not use 3/15/13 mcu->mcu_wr(mcu, MCU_REG_DDR_CLKDISABLE,
	//          (~(mcu->phy_tr_dly.rank_mask)));
	mcu->mcu_wr(mcu, MCU_REG_MCUZQCCTL,
		    (((p->zqcctl_enable & 0x1) << 31) | (p->zqcctl_interval &
							 0x7FFFFFFF)));
	mcu->mcu_wr(mcu, MCU_REG_MCUZQCDLY, p->zqcdly);

	/*
	 * Do Not program  MCU_REG_DDR_INIT_SEQ here
	 */

	mcu->mcu_wr(mcu, MCU_REG_BANK_ACTPRE, p->bank_actpre);
	mcu->mcu_wr(mcu, MCU_REG_BANK_RDPRE, p->bank_rdpre);
	mcu->mcu_wr(mcu, MCU_REG_BANK_WRPRE, p->bank_wrpre);
	mcu->mcu_wr(mcu, MCU_REG_BANK_PREACT, p->bank_preact);
	mcu->mcu_wr(mcu, MCU_REG_BANK_ACTACT, p->bank_actact);
	mcu->mcu_wr(mcu, MCU_REG_BANK_RDAACT, p->bank_rdaact);
	mcu->mcu_wr(mcu, MCU_REG_BANK_WRAACT, p->bank_wraact);
	mcu->mcu_wr(mcu, MCU_REG_BANK_ACTRD, p->bank_actrd);
	mcu->mcu_wr(mcu, MCU_REG_BANK_ACTWR, p->bank_actwr);
	mcu->mcu_wr(mcu, MCU_REG_BANK_ACTRDA, p->bank_actrda);
	mcu->mcu_wr(mcu, MCU_REG_BANK_ACTWRA, p->bank_actwra);

	mcu->mcu_wr(mcu, MCU_REG_RANK_ACTACT, p->rank_actact);
	mcu->mcu_wr(mcu, MCU_REG_RANK_RDRD, p->rank_rdrd);
	mcu->mcu_wr(mcu, MCU_REG_RANK_WRWR, p->rank_wrwr);
	mcu->mcu_wr(mcu, MCU_REG_RANK_RDWR, p->rank_rdwr);
	mcu->mcu_wr(mcu, MCU_REG_RANK_WRRD, p->rank_wrrd);
	mcu->mcu_wr(mcu, MCU_REG_RANK_ACTFAW, p->rank_actfaw);

	mcu->mcu_wr(mcu, MCU_REG_SYS_RDRD, p->sys_rdrd);
	mcu->mcu_wr(mcu, MCU_REG_SYS_WRWR, p->sys_wrwr);
	mcu->mcu_wr(mcu, MCU_REG_SYS_RDWR, p->sys_rdwr);
	mcu->mcu_wr(mcu, MCU_REG_SYS_WRRD, p->sys_wrrd);

	mcu->mcu_wr(mcu, MCU_REG_RANK_REFACTREF, p->rank_refactref);
	mcu->mcu_wr(mcu, MCU_REG_REFINT, p->rank_refint);
	mcu->mcu_wr(mcu, MCU_REG_REFRESH_BURST_CNT, p->rank_ref_burst_cnt);

	mcu->mcu_wr(mcu, MCU_REG_RC0A, p->rca[0]);
	mcu->mcu_wr(mcu, MCU_REG_RC0B, p->rcb[0]);
	mcu->mcu_wr(mcu, MCU_REG_RC1A, p->rca[1]);
	mcu->mcu_wr(mcu, MCU_REG_RC1B, p->rcb[1]);
	mcu->mcu_wr(mcu, MCU_REG_RC2A, p->rca[2]);
	mcu->mcu_wr(mcu, MCU_REG_RC2B, p->rcb[2]);
	mcu->mcu_wr(mcu, MCU_REG_RC3A, p->rca[3]);
	mcu->mcu_wr(mcu, MCU_REG_RC3B, p->rcb[3]);

	mcu->mcu_wr(mcu, MCU_REG_T_WR_LATENCY, p->t_cwl);
	mcu->mcu_wr(mcu, MCU_REG_T_RD_LATENCY, p->t_crl);
	// debug("INFO: MCU-%1d   t_WL=%2d t_RL=%2d \n", mcu->id, p->t_cwl,p->t_crl);

	mcu->mcu_wr(mcu, MCU_REG_CLKS200US, p->clks200us);
	mcu->mcu_wr(mcu, MCU_REG_CLKS500US, p->clks500us);
	mcu->mcu_wr(mcu, MCU_REG_CLKSTXPR, p->clkstxpr);
	mcu->mcu_wr(mcu, MCU_REG_CLKSTMRD, p->clkstmrd);
	mcu->mcu_wr(mcu, MCU_REG_CLKSTMOD, p->clkstmod);
	mcu->mcu_wr(mcu, MCU_REG_CLKSTZQC, (((p->clkstzqc_zqs & 0xFFF) << 12)
					    | (p->clkstzqc_zql & 0xFFF)));
	mcu->mcu_wr(mcu, MCU_REG_CLKS6US, p->clks6us);

	mcu->mcu_wr(mcu, MCU_REG_RDODTTABLO, (((p->rank_rd_odt[3] & 0xFF) << 24)
					      | ((p->rank_rd_odt[2] & 0xFF) <<
						 16)
					      | ((p->rank_rd_odt[1] & 0xFF) <<
						 8)
					      | ((p->rank_rd_odt[0] & 0xFF))));
	mcu->mcu_wr(mcu, MCU_REG_WRODTTABLO, (((p->rank_wr_odt[3] & 0xFF) << 24)
					      | ((p->rank_wr_odt[2] & 0xFF) <<
						 16)
					      | ((p->rank_wr_odt[1] & 0xFF) <<
						 8)
					      | ((p->rank_wr_odt[0] & 0xFF))));

	mcu->mcu_wr(mcu, MCU_REG_RDODTTABHI, (((p->rank_rd_odt[7] & 0xFF) << 24)
					      | ((p->rank_rd_odt[6] & 0xFF) <<
						 16)
					      | ((p->rank_rd_odt[5] & 0xFF) <<
						 8)
					      | ((p->rank_rd_odt[4] & 0xFF))));
	mcu->mcu_wr(mcu, MCU_REG_WRODTTABHI, (((p->rank_wr_odt[7] & 0xFF) << 24)
					      | ((p->rank_wr_odt[6] & 0xFF) <<
						 16)
					      | ((p->rank_wr_odt[5] & 0xFF) <<
						 8)
					      | ((p->rank_wr_odt[4] & 0xFF))));

	/*
	 * MR programming
	 */
	offset = 0;
	for (i = 0; i < 4; i++) {
		mcu->mcu_wr(mcu, MCU_REG_MRS_0_VALUE + offset, p->mode_reg[i]);
		offset += 4;
		debug("INFO: MCU-%1d   MR%1d val=0x%04X \n", mcu->id, i,
		      p->mode_reg[i]);
	}

	// CSR Status RO  MCU_REG_SCRUB_ADDR_LO
	// CSR Status RO  MCU_REG_SCRUB_ADDR_HI
	// post cfg step  mcu->mcu_wr(mcu, MCU_REG_SCRUB_CTL, p->scrub_ctrl);
	// post cfg step  mcu->mcu_wr(mcu, MCU_REG_SCRUB_START_ADDR_LO, p->scrub_start);
	// post cfg step  mcu->mcu_wr(mcu, MCU_REG_SCRUB_START_ADDR_HI, (p->scrub_start >> 31) );
	// post cfg step  mcu->mcu_wr(mcu, MCU_REG_SCRUB_END_ADDR_LO, p->scrub_end);
	// post cfg step  mcu->mcu_wr(mcu, MCU_REG_SCRUB_END_ADDR_HI, (p->scrub_end >> 31) );

	// post cfg step  mcu->mcu_wr(mcu, MCU_REG_MCUGECR, p->glb_err_ctrl);

	// post cfg step  mcu->mcu_wr(mcu, MCU_REG_MCULSCTL, p->lsleep_ctrl);
	// post cfg step  mcu->mcu_wr(mcu, MCU_REG_MCUDSCTL, p->dsleep_ctrl);
	// post cfg step  mcu->mcu_wr(mcu, MCU_REG_MCUSLEEPCTL, p->sleep_ctrl);

	mcu->mcu_wr(mcu, MCU_REG_RANK_SRXNODLL, p->rank_srxnodll);
	mcu->mcu_wr(mcu, MCU_REG_RANK_SRXDLL, p->rank_srxdll);
	mcu->mcu_wr(mcu, MCU_REG_RANK_CKEMIN, p->rank_ckemin);
	mcu->mcu_wr(mcu, MCU_REG_RANK_PDXNODLL, p->rank_pdxnodll);
	mcu->mcu_wr(mcu, MCU_REG_RANK_PDXDLL, p->rank_pdxdll);
	mcu->mcu_wr(mcu, MCU_REG_RANK_RDPDE, p->rank_rdpde);
	mcu->mcu_wr(mcu, MCU_REG_RANK_WRPDE, p->rank_wrpde);
	mcu->mcu_wr(mcu, MCU_REG_RANK_WRAPDE, p->rank_wrapde);
	mcu->mcu_wr(mcu, MCU_REG_RANK_ODTL, p->rank_odtl);

	// Status CSR RO mcu->mcu_wr(mcu, MCU_REG_MCUSLEEPSTS, 0);
	// post cfg step  mcu->mcu_wr(mcu, MCU_REG_RAMSLEEPCTL, p->sram_sleep_ctrl);
	// JHR do not enable unless needed  mcu->mcu_wr(mcu, MCU_REG_RAMRWMCTL, p->sram_rmw_ctrl);

	mcu->mcu_wr(mcu, MCU_CPU_REG0_PQDEBUGCTL, 0x800);

	debug(" EXIT: %s < \n", __FUNCTION__);
	return 0;
}

//======================================================================
//======================================================================

int mcu_post_train_setup(void *ptr)
{
	struct apm_mcu *mcu = (struct apm_mcu *)ptr;
	mcu_param_t *p = &mcu->mcu_params;
	phy_param_t *p_phy = &mcu->phy_params;

	if (!(mcu->enabled))
		return 0;
	debug(" ENTRY: %s > \n", __FUNCTION__);

	// turn on some settings after training
	mcu->mcu_wr(mcu, MCU_REG_SCRUB_CTL, p->scrub_ctrl);
	mcu->mcu_wr(mcu, MCU_REG_SCRUB_START_ADDR_LO, p->scrub_start);
	mcu->mcu_wr(mcu, MCU_REG_SCRUB_START_ADDR_HI, (p->scrub_start >> 31));
	mcu->mcu_wr(mcu, MCU_REG_SCRUB_END_ADDR_LO, p->scrub_end);
	mcu->mcu_wr(mcu, MCU_REG_SCRUB_END_ADDR_HI, (p->scrub_end >> 31));
	mcu->mcu_wr(mcu, MCU_REG_MCUGECR, p->glb_err_ctrl);
	mcu->mcu_wr(mcu, MCU_REG_MCULSCTL, p->lsleep_ctrl);
	mcu->mcu_wr(mcu, MCU_REG_MCUDSCTL, p->dsleep_ctrl);
	mcu->mcu_wr(mcu, MCU_REG_MCUSLEEPCTL, p->sleep_ctrl);
	mcu->mcu_wr(mcu, MCU_REG_RAMSLEEPCTL, p->sram_sleep_ctrl);

	// PHY change AD/CMD delay for 2T timing
	if (p_phy->en_posttr_2T_adj_cmd_addr_dly) {
		phy_rf_write_cfg_cmd_delay(ptr,
					   p_phy->posttr_val_2T_cmd_addr_dly);
		phy_rf_write_cfg_ad_delay(ptr,
					  p_phy->posttr_val_2T_cmd_addr_dly);

	}
	// PHY - enable retraining
	//if (p_phy->pevm_retrain_en) {
	//    mcu->phy_wr(mcu, PHY_REG_CFG_RETRAIN_ENABLE, 0x5);
	//}

	debug(" EXIT: %s < \n", __FUNCTION__);
	return 0;
}

//======================================================================
//======================================================================

