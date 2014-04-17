/**
 * APM X-Gene DDR3 controller
 *
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

#undef CONFIG_CMD_STORM_DDR
#if defined(APM_SIM)
#include "apm_ddr_sdram.h"
#include "ddr_lib.h"
#include "ddr_mcu.h"
#include "ddr_spd.h"

#elif defined(APM_VBIOS)

#include <common.h>
#include <stdio.h>
#include <apm_ddr_sdram.h>
#include "ddr_lib.h"
#include "ddr_mcu.h"
#include "ddr_spd.h"

#elif defined(APM_TIANOCORE)

#include <apm_ddr_sdram.h>
#include "ddr_lib.h"
#include "ddr_mcu.h"
#include "ddr_spd.h"

#else

#include <common.h>
#include <command.h>
#include <i2c.h>
#include <asm/io.h>
#include <asm/arch/apm_ddr_sdram.h>
#include <asm/arch/apm88xxxx_scu.h>
#include <asm/arch/apm_ipp_csr.h>
#include "config.h"

DECLARE_GLOBAL_DATA_PTR;
#endif

#ifdef APM_SIM

#define CONFIG_BOARD_TYPE_MUSTANG	1
#define CONFIG_BOARD_TYPE_BLACKBIRD	0

int dram_hw_init(void)
{
	struct apm_memc ddr;
	unsigned int err = 0;
	unsigned int iia;
	unsigned int board_type = 0;
	unsigned char muxaddr = 1;

	/*
	 * Lets do a simple board detection here first
	 * Need to figure out if it is black bird or mustang
	 */
	if (i2c_write(0x70, 0, 1, &muxaddr, 1)) {
		debug("DRAM: Mustang Board detected.\n");
		board_type = CONFIG_BOARD_TYPE_MUSTANG;
	} else {
		debug("DRAM: Blackbird Board detected.\n");
		board_type = CONFIG_BOARD_TYPE_BLACKBIRD;
	}

	ddr.p_setup = ddr_sys_setup;
	ddr.p_spdcal = ddr_sys_spd_calc;
	ddr.p_init = ddr_sys_init;

	debug("DRAM: ");
	for (iia = 0; iia < CONFIG_SYS_NUM_DDR_CTLRS; iia++) {
		/*
		 * We enable here for now, let SPD discovery
		 * determine what can come up
		 */
		if (board_type == CONFIG_BOARD_TYPE_BLACKBIRD)
			ddr.mcu[iia].enabled = 1;
		else {
			if (iia % 2 == 0)
				ddr.mcu[iia].enabled = 1;
			else
				ddr.mcu[iia].enabled = 0;
		}
		/*
		 * Fill out SPD information right here
		 */
		if (board_type == CONFIG_BOARD_TYPE_BLACKBIRD) {
			ddr.mcu[iia].spd_mux = 0x70;
			ddr.mcu[iia].spd_mux_addr = 1 << iia;
			ddr.mcu[iia].spd_addr[0] = 0x54;
			ddr.mcu[iia].spd_addr[1] = 0x55;
		} else {
			ddr.mcu[iia].spd_mux = 0;
			ddr.mcu[iia].spd_mux_addr = 0;
			ddr.mcu[iia].spd_addr[0] = 0;
			ddr.mcu[iia].spd_addr[1] = 0;
			if (ddr.mcu[iia].enabled)
				ddr.mcu[iia].spd_addr[0] = 0x54 + iia + 1;
		}
	}
#if APM_DISABLE_MCU123
	ddr.mcu[0].enabled = 1;
	ddr.mcu[1].enabled = 0;
	ddr.mcu[2].enabled = 0;
	ddr.mcu[3].enabled = 0;
#else
#if APM_DISABLE_MCU13
	ddr.mcu[0].enabled = 1;
	ddr.mcu[1].enabled = 0;
	ddr.mcu[2].enabled = 1;
	ddr.mcu[3].enabled = 0;
#endif
#endif

	/* Setup Data Struct & functions */
	err += ddr.p_setup(&ddr, 0);
	for (iia = 0; iia < CONFIG_SYS_NUM_DDR_CTLRS; iia++) {
		ddr.mcu[iia].mcu_params.ECCenable = 1;
	}

	/* Discover SPD and Dimm params etc */
	err += ddr.p_spdcal(&ddr, 0);

	/* Memory controller initialization */
	err += ddr.p_init(&ddr, 0);

	/* Save copy of memory regions for Pcp tests etc */
	// gp_apm_ddrlib_MEMSPACE = &(ddr.memspace);

	return err;
}

#else
#ifdef APM_VBIOS

/* Global vars - not for Uboot */
unsigned int g_apm_ddrlib_MCU_ENABLE_MASK = MCU_ENABLE_MASK;
unsigned int g_apm_ddrlib_DESIRED_DUAL_MCB = DESIRED_DUAL_MCB;
unsigned int g_apm_ddrlib_DESIRED_MCB_INTRLV = DESIRED_MCB_INTRLV;
unsigned int g_apm_ddrlib_DESIRED_DUAL_MCU = DESIRED_DUAL_MCU;
unsigned int g_apm_ddrlib_DESIRED_MCU_INTRLV = DESIRED_MCU_INTRLV;
unsigned int g_apm_ddrlib_MCU_SPEC_READ = MCU_SPEC_READ;

unsigned int g_apm_ddrlib_skipSPDInit = SKIP_SPD_INIT;
unsigned int g_apm_ddrlib_skipTimingConfig = SKIP_TIMING_CONFIG;
unsigned int g_apm_ddrlib_DIMM_SPEED = MC_DIMM_SPEED;
unsigned int g_apm_ddrlib_EN_ECC_SCHEME = MC_ECC_SCHEME;

unsigned int g_apm_ddrlib_BIST_TEST_VAL = BIST_TEST_NUMBER;

unsigned int g_apm_ddrlib_DIMM_MIRROR_CTRL = DIMM_ADDR_MIRROR_CTRL;

unsigned int g_apm_ddrlib_DIMM_MR0 = 0;
/* DIMM_MR1_RTTNOM_DIC {0x0 0x44 }  */
unsigned int g_apm_ddrlib_DIMM_MR1 = 0;

/* DIMM_MR2_RTTWR {0x0  0x200  0x400}*/
unsigned int g_apm_ddrlib_DIMM_MR2 = 0;

unsigned int g_apm_ddrlib_DIMM_RANK_MASK = DIMM_RANK_MASK;
unsigned int g_apm_ddrlib_DIMM_DESKEW_RANK_MASK = DIMM_DESKEW_RANK_MASK;
unsigned int g_apm_ddrlib_PHY_PEVM_RETRAIN_EN = PHY_PEVM_RETRAIN_EN;
unsigned int g_apm_ddrlib_PHY_ZQCAL_CODE_VALUE = PHY_ZQCAL_CODE_VALUE;
unsigned int g_apm_ddrlib_PHY_CFG_MACRO_EN_VAL = KCPHY_CFG_MACRO_ENABLE_VAL;
unsigned int g_apm_ddrlib_PHY_PRBS_DM_STATUS_MASK = KCPHY_PRBS_DM_STATUS_MASK;

unsigned int g_apm_ddrlib_KCPHY_BIT_DQ_STREN = KCPHY_BIT_DQ_STREN;
unsigned int g_apm_ddrlib_KCPHY_BIT_AD_STREN = KCPHY_BIT_AD_STREN;
unsigned int g_apm_ddrlib_KCPHY_BIT_CMD_STREN = KCPHY_BIT_CMD_STREN;
unsigned int g_apm_ddrlib_KCPHY_BIT_CTL_STREN = KCPHY_BIT_CTL_STREN;
unsigned int g_apm_ddrlib_KCPHY_BIT_CLK_STREN = KCPHY_BIT_CLK_STREN;
unsigned int g_apm_ddrlib_KCPHY_BIT_ODT_STREN = KCPHY_BIT_ODT_STREN;
unsigned int g_apm_ddrlib_KCPHY_BIT_DQ_SLEW = KCPHY_BIT_DQ_SLEW;
unsigned int g_apm_ddrlib_KCPHY_BIT_AD_SLEW = KCPHY_BIT_AD_SLEW;
unsigned int g_apm_ddrlib_KCPHY_BIT_CMD_SLEW = KCPHY_BIT_CMD_SLEW;
unsigned int g_apm_ddrlib_KCPHY_BIT_CTL_SLEW = KCPHY_BIT_CTL_SLEW;
unsigned int g_apm_ddrlib_KCPHY_BIT_CLK_SLEW = KCPHY_BIT_CLK_SLEW;

unsigned int g_apm_ddrlib_PHY_DIS_UP_54_58_5C = PHY_DIS_UP_54_58_5C;
unsigned int g_apm_ddrlib_PHY_INIT_VAL_CMD_ADDR_DELAY_54_58 =
    PHY_INIT_VAL_CMD_ADDR_DELAY_54_58;
unsigned int g_apm_ddrlib_PHY_INIT_VAL_CTL_DELAY_5C = PHY_INIT_VAL_CTL_DELAY_5C;
unsigned int g_apm_ddrlib_PHY_EN_POSTTR_2T_ADJ_CMD_ADDR =
    PHY_EN_POSTTR_2T_ADJ_CMD_ADDR;
unsigned int g_apm_ddrlib_PHY_POSTTR_ADJ_VAL_2T_CMD_ADDR_DELAY =
    PHY_POSTTR_ADJ_VAL_2T_CMD_ADDR_DELAY;

unsigned int g_apm_ddrlib_KCPHY_DISABLE_PULLUP = KCPHY_DISABLE_PULLUP;

#else //  UBOOT
#define CONFIG_BOARD_TYPE_MUSTANG	1
#define CONFIG_BOARD_TYPE_BLACKBIRD	0

void ddr_dimm_config(struct apm_memc *memc)
{
	unsigned int iia, mcu_mask = 0;

	memc->mcb_intrlv = memc->desired_mcb_intrlv;
	memc->dual_mcb = memc->mcb_intrlv;
	for (iia = 0; iia < CONFIG_SYS_NUM_DDR_CTLRS; iia++) {
		mcu_mask |= memc->mcu[iia].enabled << iia;
		/* user's desired rank interleave config */
		memc->mcu[iia].mcu_params.desired_rank_intrlv =
			getenv_ulong("DDRRANKINTLV", 10, 1);
		/* user's desired rank has config */
		memc->mcu[iia].mcu_params.desired_rank_hash_en =
			getenv_ulong("DDRRANKHASHEN", 10, 0);
		/* rank hash size:
 		 * 0:64K - 1:128K - 2:256K - 3:512K - 4:1M - 5:2M
		 */
		memc->mcu[iia].mcu_params.desired_rank_hash =
			getenv_ulong("DDRRANKHASH", 10, 4);
	}

	/*
	 * Setup MCB and Interleave Mode
	 */
	memc->mcb[0].dual_mcu = 0;
	memc->mcb[0].mcu_intrlv = 0;
	memc->mcb[1].dual_mcu = 0;
	memc->mcb[1].mcu_intrlv = 0;
	switch (mcu_mask) {
	case 0x5:
		if (!memc->mcb_intrlv) {
			memc->mcu[2].enabled = 0;
		}
		memc->mcu[1].enabled = 0;
		memc->mcu[3].enabled = 0;
		break;
	case 0x4:
		/*
		 * No interleave, so shut off other ports
		 */
		memc->mcb_intrlv = 0;
		memc->dual_mcb = 1;
		memc->mcu[0].enabled = 0;
		memc->mcu[1].enabled = 0;
		memc->mcu[3].enabled = 0;
		break;
	case 0x8:
		/*
		 * No interleave, so shut off other ports
		 */
		memc->mcb_intrlv = 0;
		memc->dual_mcb = 1;
		memc->mcb[1].dual_mcu = 1;
		memc->mcu[0].enabled = 0;
		memc->mcu[1].enabled = 0;
		memc->mcu[2].enabled = 0;
		break;
	case 0x2:
		/*
		 * No interleave, so shut off other ports
		 */
		memc->mcb_intrlv = 0;
		memc->dual_mcb = 0;
		memc->mcb[0].dual_mcu = 1;
		memc->mcu[0].enabled = 0;
		memc->mcu[2].enabled = 0;
		memc->mcu[3].enabled = 0;
		break;
	case 0x1:
		/*
		 * No interleave, so shut off other ports
		 */
		memc->mcb_intrlv = 0;
		memc->dual_mcb = 0;
		memc->mcu[1].enabled = 0;
		memc->mcu[2].enabled = 0;
		memc->mcu[3].enabled = 0;
		break;
	case 0x3:
		/*
		 * No interleave, so shut off other ports
		 */
		memc->mcb_intrlv = 0;
		memc->dual_mcb = 0;
		memc->mcb[0].dual_mcu = 1;
		memc->mcb[1].dual_mcu = 1;
		memc->mcb[0].mcu_intrlv = 1;
		memc->mcb[1].mcu_intrlv = 1;
		memc->mcu[0].enabled = 1;
		memc->mcu[1].enabled = 1;
		memc->mcu[2].enabled = 0;
		memc->mcu[3].enabled = 0;
		break;
	case 0xC:
		/*
		 * No interleave, so shut off other ports
		 */
		memc->mcb_intrlv = 0;
		memc->dual_mcb = 1;
		memc->mcb[0].dual_mcu = 0;
		memc->mcb[1].dual_mcu = 1;
		memc->mcb[0].mcu_intrlv = 0;
		memc->mcb[1].mcu_intrlv = 1;
		memc->mcu[0].enabled = 0;
		memc->mcu[1].enabled = 0;
		break;
	case 0xf:
		/*
		 * No interleave, so shut off other ports
		 */
		memc->mcb_intrlv = 1;
		memc->mcb[0].mcu_intrlv = 1;
		memc->mcb[1].mcu_intrlv = 1;
		memc->mcb[0].dual_mcu = 1;
		memc->mcb[1].dual_mcu = 1;
		memc->dual_mcb = 1;
		break;
	default:
		printf("\nInvalid DDR configuration.\n");
		printf("MCU mask: %x\n", mcu_mask);
		while (1) ;
		break;
	}
}

void mustang_board_ddr_cfg(struct apm_memc *pmemc)
{
	unsigned int i;
	unsigned int val;
	unsigned long long base = CONFIG_SYS_SCU_BASE + APM_MPA_REG_OFFSET;

	/* Enable SPD access: GPIO_DS16 = 1 */
	val = readl(base + MPA_GPIO_SEL_HI_ADDR);
	val &= ~0x00000003;
	writel(val, base + MPA_GPIO_SEL_HI_ADDR);
	val = readl(base + MPA_GPIO_OE_ADDR);
	val |= 0x00010000;
	writel(val, base + MPA_GPIO_OE_ADDR);
	val = readl(base + MPA_GPIO_OUT_ADDR);
	val |= 0x00010000;
	writel(val, base + MPA_GPIO_OUT_ADDR);

	pmemc->mcu[0].enabled = 1;
	pmemc->mcu[1].enabled = 0;
	pmemc->mcu[2].enabled = 1;
	pmemc->mcu[3].enabled = 0;

	for (i = 0; i < CONFIG_SYS_NUM_DDR_CTLRS; i++) {
		/*
		 * Setup SPD I2C configuration
		 */
		pmemc->mcu[i].spd_mux = 0;
		pmemc->mcu[i].spd_mux_addr = 0;
		pmemc->mcu[i].spd_addr[0] = 0;
		pmemc->mcu[i].spd_addr[1] = 0;
		if (pmemc->mcu[i].enabled)
			pmemc->mcu[i].spd_addr[0] = (i == 0) ? 0x54 : 0x57;

		/*
		 * Set user drive strength and slew rate
		 */
		pmemc->mcu[i].phy_params.bit_dq_stren = 6;
		pmemc->mcu[i].phy_params.bit_ad_stren = 4;
		pmemc->mcu[i].phy_params.bit_cmd_stren = 4;
		pmemc->mcu[i].phy_params.bit_ctl_stren = 4;
		pmemc->mcu[i].phy_params.bit_clk_stren = 6;

		pmemc->mcu[i].phy_params.bit_dq_slew = 2;
		pmemc->mcu[i].phy_params.bit_ad_slew = 1;
		pmemc->mcu[i].phy_params.bit_cmd_slew = 1;
		pmemc->mcu[i].phy_params.bit_ctl_slew = 1;
		pmemc->mcu[i].phy_params.bit_clk_slew = 1;

		pmemc->mcu[i].phy_params.zqcal_code = (i == 0) ? 0xa2f : 0xa2f;

		pmemc->mcu[i].phy_tr_dly.fix_gtlvl_flg = 0;
		pmemc->mcu[i].phy_tr_dly.fix_rdlvl_flg = 0;
		pmemc->mcu[i].phy_tr_dly.fix_wrlvl_flg = 0;
	}
}

void blackbird_board_ddr_cfg(struct apm_memc *pmemc)
{
	unsigned int i, j;

	for (i = 0; i < CONFIG_SYS_NUM_DDR_CTLRS; i++) {

		pmemc->mcu[i].enabled = 1;

		/*
		 * Setup SPD I2C configuration
		 */
		pmemc->mcu[i].spd_mux = 0x70;
		pmemc->mcu[i].spd_mux_addr = 1 << i;
		pmemc->mcu[i].spd_addr[0] = 0x54;
		pmemc->mcu[i].spd_addr[1] = 0x55;

		/*
		 * Set user drive strength and slew rate
		 */
		pmemc->mcu[i].phy_params.bit_dq_stren = 6;
		pmemc->mcu[i].phy_params.bit_ad_stren = 4;
		pmemc->mcu[i].phy_params.bit_cmd_stren = 4;
		pmemc->mcu[i].phy_params.bit_ctl_stren = 4;
		pmemc->mcu[i].phy_params.bit_clk_stren = 6;

		pmemc->mcu[i].phy_params.bit_dq_slew = 2;
		pmemc->mcu[i].phy_params.bit_ad_slew = 1;
		pmemc->mcu[i].phy_params.bit_cmd_slew = 1;
		pmemc->mcu[i].phy_params.bit_ctl_slew = 1;
		pmemc->mcu[i].phy_params.bit_clk_slew = 1;

		pmemc->mcu[i].phy_params.zqcal_code = (i == 0) ? 0xa2f : 0xa2f;

		pmemc->mcu[i].phy_tr_dly.fix_gtlvl_flg = 0;
		pmemc->mcu[i].phy_tr_dly.fix_rdlvl_flg = 0;
		pmemc->mcu[i].phy_tr_dly.fix_wrlvl_flg = 0;

		if (pmemc->mcu[i].phy_tr_dly.fix_gtlvl_flg) {
			for (j = 0; j < 2; j++) {
				pmemc->mcu[i].phy_tr_dly.rank_dly[j].
					fix_gt_lvl[0] = 0x5a0;
				pmemc->mcu[i].phy_tr_dly.rank_dly[j].
					fix_gt_lvl[1] = 0x5a0;
				pmemc->mcu[i].phy_tr_dly.rank_dly[j].
					fix_gt_lvl[2] = 0x5a0;
				pmemc->mcu[i].phy_tr_dly.rank_dly[j].
					fix_gt_lvl[3] = 0x5a0;
				pmemc->mcu[i].phy_tr_dly.rank_dly[j].
					fix_gt_lvl[4] = 0x5a0;
				pmemc->mcu[i].phy_tr_dly.rank_dly[j].
					fix_gt_lvl[5] = 0x5a0;
				pmemc->mcu[i].phy_tr_dly.rank_dly[j].
					fix_gt_lvl[6] = 0x5a0;
				pmemc->mcu[i].phy_tr_dly.rank_dly[j].
					fix_gt_lvl[7] = 0x5a0;
				pmemc->mcu[i].phy_tr_dly.rank_dly[j].
					fix_gt_lvl[8] = 0x5a0;
				pmemc->mcu[i].phy_tr_dly.rank_dly[j].
					fix_gt_lvl[9] = 0x618;
				pmemc->mcu[i].phy_tr_dly.rank_dly[j].
					fix_gt_lvl[10] = 0x618;
				pmemc->mcu[i].phy_tr_dly.rank_dly[j].
					fix_gt_lvl[11] = 0x670;
				pmemc->mcu[i].phy_tr_dly.rank_dly[j].
					fix_gt_lvl[12] = 0x670;
				pmemc->mcu[i].phy_tr_dly.rank_dly[j].
					fix_gt_lvl[13] = 0x670;
				pmemc->mcu[i].phy_tr_dly.rank_dly[j].
					fix_gt_lvl[14] = 0x670;
				pmemc->mcu[i].phy_tr_dly.rank_dly[j].
					fix_gt_lvl[15] = 0x670;
				pmemc->mcu[i].phy_tr_dly.rank_dly[j].
					fix_gt_lvl[16] = 0x670;
				pmemc->mcu[i].phy_tr_dly.rank_dly[j].
					fix_gt_lvl[17] = 0x670;
			}
		}
	}
}

void dram_board_init(struct apm_memc *pmemc)
{
	unsigned char muxaddr = 1;
	unsigned int i;

	/*
	 * Lets do a simple board detection here first
	 * Need to figure out if it is black bird or mustang
	 */
	if (i2c_read(0x70, 0, 1, &muxaddr, 1)) {
		debug("DRAM: Mustang Board detected.\n");
		mustang_board_ddr_cfg(pmemc);
	} else {
		debug("DRAM: Blackbird Board detected.\n");
		blackbird_board_ddr_cfg(pmemc);
	}

	pmemc->p_setup = ddr_sys_setup;
	pmemc->p_spdcal = ddr_sys_spd_calc;
	pmemc->p_init = ddr_sys_init;

	pmemc->desired_mcb_intrlv = getenv_ulong("DDRMCBINTLV", 10, 1);
	pmemc->desired_dual_mcb = pmemc->desired_mcb_intrlv;
	pmemc->full_addr = 1;	/* 1: 42 bit mode */

	/* Enable SPEC read always */
	pmemc->mcb[0].spec_read = getenv_ulong("DDRSPEC", 10, 1);
	pmemc->mcb[1].spec_read = getenv_ulong("DDRSPEC", 10, 1);

	for (i = 0; i < CONFIG_SYS_NUM_DDR_CTLRS; i++) {
		pmemc->mcu[i].mcu_params.speed_desired =
			getenv_ulong("DDRSPEED", 10, 1600);
		/* rd2wr - wr2rd - margin0 - margin 1 - rd2rd - wr2wr */
		pmemc->mcu[i].mcu_params.tmargin =
			getenv_ulong("DDRMARGIN", 16, 0x110000);
#if !defined(CONFIG_OCM_U_BOOT)
		pmemc->mcu[i].mcu_params.ECCscheme =
			getenv_ulong("DDRECC", 10, 3);
#else
		pmemc->mcu[i].mcu_params.ECCscheme =
			getenv_ulong("DDRECC", 10, 0);
#endif
		pmemc->mcu[i].mcu_params.ECCenable =
			pmemc->mcu[i].mcu_params.ECCscheme ? 1 : 0;
	}
}

void check_valid_interleave_mode_config (struct apm_memc *memc)
{
	unsigned int i;
	int first_dimm = -1;
	int rnk_err = 0;

	for (i = 0; i < CONFIG_SYS_NUM_DDR_CTLRS; i++) {
		if(memc->mcu[i].enabled){
			/* Detect the first populated DIMM */
			if (first_dimm < 0) {
				first_dimm = i;
				continue;
			}
			/* Invalid number of rank or rank size */
			rnk_err = (memc->mcu[i].dimm_params[0].n_ranks !=
					memc->mcu[first_dimm].dimm_params[0].n_ranks)? 1 : 0;
			rnk_err += (memc->mcu[i].dimm_params[0].rank_density !=
					memc->mcu[first_dimm].dimm_params[0].rank_density)? 1 : 0;
			if (rnk_err > 0) {
				printf(" ## DRAM Interleave mode ERROR:"
						" please install identical DIMMs and REBOOT ##\n");
				while(1);
			}
		}
	}
}


static int apm88xxx_chip_revision(void)
{
#define EFUSE0_SHADOW_VERSION_SHIFT     28
#define EFUSE0_SHADOW_VERSION_MASK      0xF
#define SCU_JTAG0                       0x17000004
#define EFUSE0_SHADOW_ADDR_ABS          0x1054a000
  volatile u32 *addr;
  addr = (u32 *)EFUSE0_SHADOW_ADDR_ABS;

  u32 val = (*(addr) >> EFUSE0_SHADOW_VERSION_SHIFT)
              & EFUSE0_SHADOW_VERSION_MASK;
  switch (val){
  case 0x00:
    addr = (u32 *)SCU_JTAG0;
    return (*addr & 0x10000000)? 2: 1;
  case 0x01:
    return 2;
  case 0x02:
    return 3;
  }
  return 0;
}


int dram_hw_init(unsigned long long *ddrbase, unsigned long long *ddrsize)
{
	struct apm_memc ddr;
	unsigned int err = 0;
	unsigned int i;
	unsigned int spd_err = 0;
	unsigned int mcu_mask = 0;
	unsigned char muxaddr = 1;

	printf("DRAM: ");

	/* Init the apm_memc structure */
        memset(&ddr, 0, sizeof(struct apm_memc));

	/*
	 * Do some board related DDR structure setup
	 */
	dram_board_init(&ddr);

	/* Setup Data Struct & functions */
	err += ddr.p_setup(&ddr, 0);

	/*Discover SPD and Dimm params etc */
	spd_err = ddr.p_spdcal(&ddr, 0);

	/* For Black Bird 2 channels or 4 channels 2 ranks support upto 1550Mhz */
	if (apm88xxx_chip_revision() == 1 && !i2c_read(0x70, 0, 1, &muxaddr, 1)) {
		for (i = 0; i < CONFIG_SYS_NUM_DDR_CTLRS; i++) {
			mcu_mask |= ddr.mcu[i].enabled << i;
		}
		switch (mcu_mask) {
		case 0x3:
		case 0x5:
		case 0xC:
		case 0xF:
			if ((ddr.mcu[0].dimm_params[0].n_ranks == 2) &&
				(ddr.mcu[0].mcu_params.speed_desired >= 1600)) {
				for (i = 0; i < CONFIG_SYS_NUM_DDR_CTLRS; i++) {
					ddr.mcu[i].mcu_params.speed_desired = 1550;
				}
				spd_err = ddr.p_spdcal(&ddr, 0);
			}
			break;
		}
	}

	/*
	 * Setup interleave mode
	 */
	ddr_dimm_config(&ddr);

	/* Check if MCB/MCU interleave mode DIMM configuration is valid */
	if (ddr.mcb_intrlv || ddr.mcb[0].mcu_intrlv || ddr.mcb[1].mcu_intrlv)
		check_valid_interleave_mode_config(&ddr);

	/* Memory controller initialization */
	err += ddr.p_init(&ddr, 0);

	{
	unsigned long ram_size = 0;
	for (i = 0; i < 5; i++) {
#if !defined(APM_TIANOCORE)
		gd->ram_start = ddr.memspace.str_addr[0];
		gd->ram_size =
		    (ddr.memspace.end_addr[0] - ddr.memspace.str_addr[0]) + 1;
		ram_size = gd->ram_size;
#else
		ram_size = (ddr.memspace.end_addr[0] - ddr.memspace.str_addr[0]) + 1;
#endif
		if (ram_size > 0x100000)
			break;
	}
	print_size(ram_size, "");
	*ddrsize = ram_size;
	}
	printf(" @ %dMHz\n", ddr.mcu[0].mcu_params.speed);
	if (spd_err & 0x2)
		printf("Warning: SPD checksum incorrect.\n");

 	return err;
}

#ifdef CONFIG_CMD_STORM_DDR
int do_ddr_tp(struct apm_memc *memc, cmd_tbl_t * cmdtp, int flag, int argc,
	      char *argv[])
{
	unsigned char i;
	struct apm_mcu *mcu;
	unsigned int mtb_ps;
	generic_spd_eeprom_t *spd;
	dimm_params_t *pdimm;

	printf("\nDDR Timing Parameters\n");
	for (i = 0; i < 4; i++) {

		if (memc->mcu[i].enabled == 0)
			continue;

		mcu = &memc->mcu[0];

		spd = &mcu->spd_info[0];
		pdimm = &mcu->dimm_params[0];
		printf("\tDIMM Capacity (%d ranks): total 0x%llx\n",
		       pdimm->n_ranks, pdimm->capacity);

		switch (spd->module_type & 0xf) {
		case 0x01:		/* RDIMM */
		case 0x05:		/* Mini-RDIMM */
			printf("\tRegister DIMM detected: Type 0x%X\n",
			      spd->module_type & 0xf);
			break;
		case 0x0B:		/* LRDIMM */
			printf("\tLRDIMM detected: Type 0x%X\n",
			       spd->module_type & 0xf);
			break;
		case 0x02:		/* UDIMM */
		case 0x03:		/* SO-DIMM */
		case 0x04:		/* Micro-DIMM */
		case 0x06:		/* Mini-UDIMM */
			printf("\tUnbuffered DIMM detected: Type 0x%X\n",
			      spd->module_type & 0xf);
			break;

		default:
			printf("\tUnknown dimm_type: 0x%02X\n",
			       spd->module_type);
			return 1;
		}

		printf("\tAddressing: Row: %d Col: %d Bank: %d\n",
		       pdimm->n_row_addr, pdimm->n_col_addr,
		       pdimm->n_banks_per_sdram_device);

		mtb_ps = (spd->mtb_dividend * 1000) / spd->mtb_divisor;
		printf("\tMTB(ps): %d\n", mtb_ps);

		pdimm->tCKmin_X_ps = (spd->tCK_min * mtb_ps);
		printf("\tCK min(ps): %d (min-supported by DIMM)\n",
		       pdimm->tCKmin_X_ps);

		pdimm->caslat_X =
		    ((spd->caslat_msb << 8) | spd->caslat_lsb) << 4;
		printf("\tSPD CAS Latency: 0x%4x\n", pdimm->caslat_X);

		pdimm->tAA_ps = spd->tAA_min * mtb_ps;
		printf("\tAA min(ps): %d\n", pdimm->tAA_ps);

		pdimm->tWR_ps = spd->tWR_min * mtb_ps;
		printf("\tWR min(ps): %d\n", pdimm->tWR_ps);

		pdimm->tRCD_ps = spd->tRCD_min * mtb_ps;
		printf("\tRCD min(ps): %d\n", pdimm->tRCD_ps);

		pdimm->tRRD_ps = spd->tRRD_min * mtb_ps;
		printf("\tRRD min(ps): %d\n", pdimm->tRRD_ps);

		pdimm->tRP_ps = spd->tRP_min * mtb_ps;
		printf("\tRP min(ps): %d\n", pdimm->tRP_ps);

		pdimm->tRAS_ps =
		    (((spd->tRAS_tRC_ext & 0xf) << 8) | spd->tRAS_min_lsb)
		    * mtb_ps;
		printf("\tRAS min(ps): %d\n", pdimm->tRAS_ps);

		pdimm->tRC_ps =
		    (((spd->tRAS_tRC_ext & 0xf0) << 4) | spd->tRC_min_lsb)
		    * mtb_ps;
		printf("\tRC min(ps): %d\n", pdimm->tRC_ps);

		pdimm->tRFC_ps = ((spd->tRFC_min_msb << 8) | spd->tRFC_min_lsb)
		    * mtb_ps;
		printf("\tRFC min(ps): %d\n", pdimm->tRFC_ps);

		pdimm->tWTR_ps = spd->tWTR_min * mtb_ps;
		printf("\tWTR (ps): %d\n", pdimm->tWTR_ps);

		pdimm->tRTP_ps = spd->tRTP_min * mtb_ps;
		printf("\tRTP (ps): %d\n", pdimm->tRTP_ps);

		pdimm->refresh_rate_ps = (7800U * 8 * mtb_ps);	// div by tclks is done while calculating actual ref-int for CSR
		printf("\tREF-INT (ps): %d\n", pdimm->refresh_rate_ps);

		pdimm->tFAW_ps = (((spd->tFAW_msb & 0xf) << 8) | spd->tFAW_min)
		    * mtb_ps;
		printf("\tFAW (ps): %d\n", pdimm->tFAW_ps);
		printf("\n");

		break;
	}
	return 0;
}

int do_ddr_spd(struct apm_memc *memc, cmd_tbl_t * cmdtp, int flag, int argc,
	       char *argv[])
{
	unsigned char *ptr = 0;
	unsigned char *spd = 0;
	unsigned char i, j;
	struct apm_mcu *mcu;

	printf("\nDDR SPD Configuration\n");
	for (i = 0; i < 4; i++) {

		if (memc->mcu[i].enabled == 0)
			continue;

		for (j = 0; j < 2; j++) {
			mcu = &memc->mcu[i];
			if (!(mcu->mcu_params.activeslots & (1 << j)))
				continue;

			printf("MCU %d Slot %d:\n", i, j);

			spd = (unsigned char *)&memc->mcu[i].spd_info[j];

			ptr = ((spd_eeprom_t *) spd)->mpart;
			printf("\tDIMM Vendor : 0x%X%X\n",
			       ((spd_eeprom_t *) spd)->dmid_lsb,
			       ((spd_eeprom_t *) spd)->dmid_msb);
			printf("\tDIMM Part : ");
			printf("%c", *ptr++);
			for (i = 0; i < 18; i++)
				printf("%c", *ptr++);
			printf("\n\t");
			switch (((spd_eeprom_t *) spd)->module_type & 0xf) {
			case 0x01:		/* RDIMM */
				printf("RDIMM: ");
				break;
			case 0x05:		/* Mini-RDIMM */
				printf("Mini-RDIMM: ");
				break;
			case 0x02:		/* UDIMM */
				printf("UDIMM: ");
				break;
			case 0x03:		/* SO-DIMM */
				printf("SODIMM: ");
				break;
			case 0x04:		/* Micro-DIMM */
				printf("Micro-DIMM: ");
				break;
			case 0x06:		/* Mini-UDIMM */
				printf("Mini-UDIMM ");
				break;
			case 0x0B:		/* LRDIMM */
				printf("LRDIMM: ");
				break;
			default:
				printf("Unknown DIMM: ");
				break;
			}
			printf("%ldMB/rank\n",
			       compute_ranksize((spd_eeprom_t *) spd) / (1024 *
									 1024));
			printf("\tRanks:%d\n", mcu->dimm_params[j].n_ranks);
			printf("\tMirrored Dimm: %s\n",
			       mcu->dimm_params[j].
			       mirrored_dimm ? "yes" : "no");
			printf("\n");
		}
	}
	return 0;
}

int do_ddr_cmd(cmd_tbl_t *cmdtp, int flag, int argc, char *argv[])
{
	static struct apm_memc ddr;

	if (argc < 2) {
		cmd_usage(cmdtp);
		return 1;
	}

	if (ddr.p_setup == NULL) {
		dram_board_init(&ddr);
		ddr.p_setup(&ddr, 0);
		ddr.p_spdcal(&ddr, 0);
	}

	if (!strncmp(argv[1], "sp", 2))
		return do_ddr_spd(&ddr, cmdtp, flag, argc, argv);

	if (!strncmp(argv[1], "tp", 2))
		return do_ddr_tp(&ddr, cmdtp, flag, argc, argv);

	return 0;
}

U_BOOT_CMD(ddr, 2, 0, do_ddr_cmd,
	"DDR sub-system commands\n",
	"ddr status 	- read DDR status\n"
	"ddr tp 	- read DDR Timing Parameters\n"
	"ddr spd 	- read DDR SPD information\n"
	   "ddr cal 	- read DDR calibration results\n" "\n");
#endif

#endif
#endif

