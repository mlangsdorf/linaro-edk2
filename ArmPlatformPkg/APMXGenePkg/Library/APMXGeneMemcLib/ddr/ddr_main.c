/**
 * APM X-Gene DDR3 controller code
 *
 * Copyright (c) 2013, AppliedMicro Corp. All rights reserved.
 * All rights reserved. Feng Kan <fkan@apm.com>.
 *
 * This program and the accompanying materials
 * are licensed and made available under the terms and conditions of the BSD License
 * which accompanies this distribution.  The full text of the license may be found at
 * http://opensource.org/licenses/bsd-license.php
 *
 * THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
 * WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.
 *
 * This is the main init function file. The init is attached to the
 * apm_memc structure. These are the top level init function used
 * to initialize the system's ddr controllers. 
 *
 **/

#if DDRLIB_DEBUGON
#define DEBUG
#define DEBUG_REGMOD
#else
#undef DEBUG
#undef DEBUG_REGMOD
#endif

#if defined(APM_SIM)
#include "apm_ddr_sdram.h"
#elif defined(APM_VBIOS)
#include <common.h>
#include <stdio.h>
#include <apm_ddr_sdram.h>
#include <ddr_driver.h>
#elif defined(APM_TIANOCORE)
#include "apm_ddr_sdram.h"
#else /* U-Boot */
#include <common.h>
#include <command.h>
#include <asm/io.h>
#include <asm/arch/apm_ddr_sdram.h>
#include "config.h"
#endif

#ifdef APM_VBIOS

#define APM_VBIOS_LPRINTF(msg, ...) lprintf(7, msg, ##__VA_ARGS__)
#define APM_VBIOS_LPRINTF_CHK(msg, id) \
                do {    \
                    if (mcu->enabled) lprintf(7, msg, id); \
                } while(0)
#define APM_VBIOS_RETURN(e, msg, ...)     \
                do {    \
                    if(e) {   \
                        lprintf(4, msg, ##__VA_ARGS__);    \
                        return (unsigned int)e;     \
                    }   \
                   } while(0)

#else

#define APM_VBIOS_LPRINTF(msg, ...)
#define APM_VBIOS_LPRINTF_CHK(msg, id)
#define APM_VBIOS_RETURN(e, msg, ...)
#endif

#include "ddr_lib.h"
#include "kc_phy_util_reg_flds.h"

/* 
 * Initialize up to 2 Mcb and 4 Mcu
 */
int ddr_sys_setup(void *ptr, unsigned int flag)
{
	unsigned int err = 0;
	struct apm_memc *memc = (struct apm_memc *)ptr;
	struct apm_mcu *mcu;
	unsigned int iia;

	debug("DRAM: memc setup\n");

	/* Initialize DDR structure */
	memc->p_mcb_reset = memc_dummy_fn;
	memc->p_mcu_reset = memc_dummy_fn;
	memc->p_mc_pwr_ok = mcu_assert_mc_pwr_ok;
	memc->p_memsys_unreset = memsys_unreset;
	memc->p_mem_test_init = memc_dummy_fn;
	memc->p_addressmap = memc_addr_cfg;
#ifdef APM_VBIOS
	memc->p_tlb_map = vbios_ddr_tlb_map;
#else
	memc->p_tlb_map = memc_dummy_fn;
#endif
	for (iia = 0; iia < CONFIG_SYS_NUM_DDR_CTLRS; iia++) {
		mcu = (struct apm_mcu *)&memc->mcu[iia];
		mcu->id = iia;

//#if defined(APM_VBIOS)
//              mcu->enabled = (MCU_ENABLE_MASK >> iia) & 0x1;
//#endif
//#if defined(APM_SIM) || defined(APM_VBIOS)
//              mcu->mcu_params.speed_desired = MC_DIMM_SPEED;
//              mcu->mcu_params.ECCscheme = MC_ECC_SCHEME;
//#endif
		mcu->mcb_id = iia / 2;	//Mcb0->mcu0/1 :: Mcb1->mcu2/3
		mcu->base = PCP_RB_MCU_BASE + iia * PCP_RB_MCU_OFFSET;
		mcu->phy_addr = mcu->base;
		mcu->csw_base = PCP_RB_CSW_BASE;

		mcu->mcb_base = (iia < 2) ? PCP_RB_MCB_BASE :
		    (PCP_RB_MCB_BASE + PCP_RB_MCB_OFFSET);

		mcu->mcu_rd = mcu_read_reg;
		mcu->mcu_wr = mcu_write_reg;
		mcu->mcu_rmw = mcu_regmod;
		mcu->phy_rd = phy_read_reg;
		mcu->phy_wr = phy_write_reg;
		mcu->mcb_rd = mcb_read_reg;
		mcu->mcb_wr = mcb_write_reg;
		mcu->csw_rd = csw_read_reg;
		mcu->csw_wr = csw_write_reg;

		mcu->prbs_test = 0;
		mcu->bist_test = 0;
		mcu->p_spd_init = memc_dummy_fn;
		mcu->p_timing_config = memc_dummy_fn;
		mcu->p_csr_config = memc_dummy_fn;
		mcu->p_pre_init = memc_dummy_fn;
		mcu->p_phy_setup = memc_dummy_fn;
		mcu->p_phy_pre_init = memc_dummy_fn;
		mcu->p_post_init = memc_dummy_fn;
		mcu->p_phy_post_init = memc_dummy_fn;
		mcu->p_prbs_test = memc_dummy_fn;
		mcu->p_dimm_post_init = memc_dummy_fn;
		mcu->p_phy_calib = memc_dummy_fn;
		mcu->p_bist_test = memc_dummy_fn;
		mcu->p_post_train_setup = memc_dummy_fn;
		mcu->p_meminitdone = memc_dummy_fn;
		mcu->p_phy_retrain = memc_dummy_fn;

		mcu->p_spd_init =
		    (SKIP_SPD_INIT) ? memc_dummy_fn : ddr_spd_init;
		mcu->p_timing_config = (SKIP_SPD_INIT
					|| SKIP_TIMING_CONFIG) ?
		    memc_dummy_fn : mcu_timing_config;

		mcu->p_csr_config = mcu_csr_config22;
		mcu->p_pre_init = mcu_pre_init;
		mcu->p_phy_setup = mcu_kc_phy_setup_tc;
		mcu->p_phy_pre_init = memc_dummy_fn;	// Moved after MC_POWER_OK
		mcu->p_phy_post_init = mcu_post_assert_mc_pwr_tc;
		mcu->p_post_init = mcu_post_init;

		mcu->p_dimm_post_init = dimm_mcu_fsm_init;
		mcu->p_phy_calib = calib_pevm_seperate_steps;
		mcu->p_post_train_setup = mcu_post_train_setup;
		mcu->p_meminitdone = mcu_en_traffic_mem_init_done;

	}

	memc->p_mem_test_init = memc_dummy_fn;

	/* Setup apm_memc with generic values */
	populate_mc_default_parms(memc);
	APM_MARKERN(0x800000);
	APM_MARKERN_WRITE32(OCM_C0_TEST_PRGS_ADDR, 0x800000);

	return err;
}

int ddr_sys_spd_calc(void *ptr, unsigned int flag)
{
	unsigned int err = 0;
	struct apm_memc *memc = (struct apm_memc *)ptr;
	struct apm_mcu *mcu;
	unsigned int iia, ecc_en;
	ecc_en = 0;

	debug("DRAM: SPD discovery and timing calc\n");

#ifdef APM_VBIOS
	unsigned int spd_mcu_enable = 0;
#endif
	/*
	 * SPD init & setup for bringup
	 */
	for (iia = 0; iia < CONFIG_SYS_NUM_DDR_CTLRS; iia++) {
		mcu = (struct apm_mcu *)&(memc->mcu[iia]);
#ifdef APM_VBIOS
		if (gp_vbios_ddr_config->g_ddr_skipSPD)
			continue;
#endif
		/* SPD read & timing parameter generation */
		APM_VBIOS_LPRINTF_CHK
		    ("\n------- MCU[%d] - SPD read & DIMM config parameter generation --------\n",
		     iia);
		err |= mcu->p_spd_init(mcu);
		APM_MARKERN(0x801000);
		APM_MARKERN_WRITE32(OCM_C0_TEST_PRGS_ADDR, 0x801000);
#ifdef APM_VBIOS
		spd_mcu_enable |= (mcu->enabled) << iia;
#endif
	}
#ifdef APM_VBIOS

	if (spd_mcu_enable != gp_vbios_ddr_config->g_ddr_mcu_en) {
		lprintf(8,
			"\n\n****** SPD-MCU enable ? [Org: 0x%x new: 0x%x] ***** \n\n",
			gp_vbios_ddr_config->g_ddr_mcu_en, spd_mcu_enable);
	}
	gp_vbios_ddr_config->g_ddr_mcu_en = spd_mcu_enable;
	if (gp_vbios_ddr_config->g_ddr_onlySPD)
		return (unsigned int)err;
#endif
	for (iia = 0; iia < CONFIG_SYS_NUM_DDR_CTLRS; iia++) {
		mcu = (struct apm_mcu *)&(memc->mcu[iia]);
		/* DDRlib structure fillup & corsscheck spd vs test-requirements */
		APM_VBIOS_LPRINTF_CHK
		    ("\n------- MCU[%d] - Timing parameter calculaiton --------\n",
		     iia);
		err |= mcu->p_timing_config(mcu);
		APM_MARKERN(0x802000);
		APM_MARKERN_WRITE32(OCM_C0_TEST_PRGS_ADDR, 0x802000);
		if (mcu->enabled)
			ecc_en |= ((mcu->mcu_params.ECCscheme != 0)
				   && mcu->mcu_params.ECCenable) ? 1 : 0;
	}

#if !(defined(APM_SIM))
	if (ecc_en) {
		memc->p_mem_test_init = memc_ecc_init_en;
	}
#endif

	for (iia = 0; iia < CONFIG_SYS_NUM_DDR_CTLRS; iia++) {
		// Set retrain if indicated
		mcu = (struct apm_mcu *)&memc->mcu[iia];
		if (mcu->phy_params.pevm_retrain_en != 0) {
			mcu->p_phy_retrain = retrain_pevm_sep_steps;
		}
	}

	return err;
}

int ddr_sys_init(void *ptr, unsigned int flag)
{
	unsigned int err = 0;
	struct apm_memc *memc = (struct apm_memc *)ptr;
	struct apm_mcu *mcu;
	unsigned int iia;

	debug("DRAM: system initialization this time\n");

	/* 
	 * Top Level MCU/PHY-PLL turn on and Unreset  memory sub-system 
	 */
	APM_VBIOS_LPRINTF
	    ("\n------- Top Level MCU/PHY-PLL turn on and Unreset memory sub-system --------\n");
	err += memc->p_memsys_unreset(memc);
	APM_MARKERN(0x802FFFF);
	APM_VBIOS_RETURN(err, "\nMemory sub-system Unreset ERROR [%d]\n", err);
	/*
	 * Memory controller pre setup/initialization 
	 */
	for (iia = 0; iia < CONFIG_SYS_NUM_DDR_CTLRS; iia++) {
		mcu = (struct apm_mcu *)&(memc->mcu[iia]);
		/* MCU CSR setup */
		APM_VBIOS_LPRINTF_CHK
		    ("\n------- MCU[%d] - CSR setup --------\n", iia);
		err += mcu->p_csr_config(mcu);
		APM_MARKERN(0x803000);
		APM_MARKERN_WRITE32(OCM_C0_TEST_PRGS_ADDR, 0x803000);

		/* MCU pre power ok initialization */
		APM_VBIOS_LPRINTF_CHK("\n------- MCU[%d] - Pre-Init --------\n",
				      iia);
		err += mcu->p_pre_init(mcu);
		APM_MARKERN(0x804000);
		APM_MARKERN_WRITE32(OCM_C0_TEST_PRGS_ADDR, 0x804000);
	}
	APM_VBIOS_RETURN(err, "\nPre-Init  ERROR [%d]\n", err);

	APM_VBIOS_LPRINTF("\n------- MCU Address Map Config --------\n");
	err += memc->p_addressmap(memc);
	APM_VBIOS_RETURN(err, "\nAddress Map ERROR [%d]\n", err);

	APM_VBIOS_LPRINTF("\n------- DDR mem-space TLB Setup --------\n");
	err += memc->p_tlb_map(memc);
	APM_VBIOS_RETURN(err, "\nTLB Map ERROR [%d]\n", err);
	/* 
	 * Assert DDR_MC_POWER_OK since  MCU have common pin.  
	 */
	APM_VBIOS_LPRINTF("\n------- Assert DDR_MC_POWER_OK --------\n");
	err += memc->p_mc_pwr_ok(mcu);
	APM_MARKERN(0x804ffff);
	APM_MARKERN_WRITE32(OCM_C0_TEST_PRGS_ADDR, 0x804ffff);

	/*
	 * MCU post power of initialization 
	 */
	for (iia = 0; iia < CONFIG_SYS_NUM_DDR_CTLRS; iia++) {
		mcu = (struct apm_mcu *)&memc->mcu[iia];
		APM_VBIOS_LPRINTF_CHK
		    ("\n------- MCU[%d] - Post-Init --------\n", iia);
		err += mcu->p_post_init(mcu);
		APM_MARKERN(0x805000);
		APM_MARKERN_WRITE32(OCM_C0_TEST_PRGS_ADDR, 0x805000);
	}
	APM_VBIOS_RETURN(err, "\nPost-Init ERROR [%d]\n", err);
	/*
	 * MCU-BIST 
	 */
	for (iia = 0; iia < CONFIG_SYS_NUM_DDR_CTLRS; iia++) {
		mcu = (struct apm_mcu *)&memc->mcu[iia];
#ifdef APM_VBIOS
		if (mcu->bist_test)
			lprintf(7, "\n------- MCU[%d] - BIST test --------\n",
				iia);
		else
			continue;
#endif
		err += mcu->p_bist_test(mcu);
		APM_MARKERN(0x806000);
		APM_MARKERN_WRITE32(OCM_C0_TEST_PRGS_ADDR, 0x806000);
	}
	APM_VBIOS_RETURN(err, "\nBIST ERROR [%d]\n", err);

	/*
	 * MCU- Poll InitDone 
	 */
	for (iia = 0; iia < CONFIG_SYS_NUM_DDR_CTLRS; iia++) {
		mcu = (struct apm_mcu *)&memc->mcu[iia];
		APM_VBIOS_LPRINTF_CHK
		    ("\n------- MCU[%d] - Post Train Setup --------\n", iia);
		err += mcu->p_post_train_setup(mcu);
		APM_MARKERN(0x807000);
		APM_MARKERN_WRITE32(OCM_C0_TEST_PRGS_ADDR, 0x807000);
		APM_VBIOS_LPRINTF_CHK
		    ("\n------- MCU[%d] - Poll for Done --------\n", iia);
		err += mcu->p_meminitdone(mcu);
		APM_MARKERN(0x808000);
		APM_MARKERN_WRITE32(OCM_C0_TEST_PRGS_ADDR, 0x808000);
	}
	APM_VBIOS_RETURN(err, "\nPost-Train / Init-Done ERROR [%d]\n", err);

	/*
	 * MEMC - test memory or initialize with ECC syndrome and enable ECC 
	 */
	APM_VBIOS_LPRINTF("\n------- Start DDR ECCinit --------\n");
	err += memc->p_mem_test_init(memc);
	APM_VBIOS_RETURN(err, "ECCinit ERROR [%d]\n", err);

	/*
	 * MCU- Poll InitDone 
	 */
	for (iia = 0; iia < CONFIG_SYS_NUM_DDR_CTLRS; iia++) {
		mcu = (struct apm_mcu *)&memc->mcu[iia];
#ifdef APM_VBIOS
		if (mcu->phy_params.pevm_retrain_en != 0)
			lprintf(7, "\n------- MCU[%d] - Re-Train --------\n",
				iia);
#endif
		err += mcu->p_phy_retrain(mcu);
	}
	APM_VBIOS_RETURN(err, "Re-Train ERROR [%d]\n", err);
	debug("DRAM: memc setup DONE ......\n");
	return err;
}
