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
#elif defined(APM_TIANOCORE)
#include "apm_ddr_sdram.h"
#else
#include <command.h>
#include <asm/io.h>
#include <asm/arch/apm_ddr_sdram.h>
#include "config.h"
#endif

#include "ddr_mcu.h"
#include "ddr_lib.h"
#include "kc_phy_util_reg_flds.h"

/******************************************************************************
 *     Mcu_RESET FSM tasks
 *****************************************************************************/

int mcu_reset_status_poll(void *p, unsigned int status, unsigned int mask,
			  unsigned int flag)
{
	// Same as SV code: rb_mcu_request_seq_base.svh:: task mcu_CSR_reset_status_poll
	// POLL MCU Reset status (RO) csr for FSM state , errors mem_init_done etc
	unsigned int done, rddata;
	struct apm_mcu *mcu = (struct apm_mcu *)p;

	debug(" ENTRY: %s > \n", __FUNCTION__);
	debug("MCU[%d] - mcu_reset_status_poll\n", mcu->id);
	done = 0;
	do {
		rddata = mcu->mcu_rd(mcu, MCU_REG_DDR_INIT_STATUS);
		if (flag == POLL_EQUAL) {
			if ((rddata & mask) == (status & mask))
				done = 1;
			else
				DELAY(1);
		} else if (flag == POLL_LESS) {
			if ((rddata & mask) <= (status & mask))
				done = 1;
			else
				DELAY(1);
		} else if (flag == POLL_GREATER) {
			if ((rddata & mask) >= (status & mask))
				done = 1;
			else
				DELAY(1);
		}
#ifdef CONFIG_VHP
		done = 1;
#endif

	} while (done == 0);
	return rddata;
}

//======================================================================

int mcu_init_done_poll(void *p)
{
	unsigned int status, mask;
	status = mask = 1;

	return (mcu_reset_status_poll(p, status, mask, POLL_EQUAL));
}

//======================================================================

void mcu_reset_FSM_poll(void *p, unsigned int status, unsigned int flag)
{
	unsigned int mask;
	struct apm_mcu __attribute__ ((unused)) * mcu = (struct apm_mcu *)p;
	status = (status & 0x7F) << 24;
	mask = 0x7F000000;
	debug
	    ("MCU[%d] mcu_reset_status_poll >>> status:0x%X mask=0x%X flag=0x%X\n",
	     mcu->id, status, mask, flag);
	mcu_reset_status_poll(p, status, mask, flag);
}

/******************************************************************************
 *     Mcu - Dimm Initialization Sub Tasks
 *****************************************************************************/

void mcu_wr_statechk(struct apm_mcu *mcu, unsigned int reg, unsigned int val)
{
	mcu_reset_FSM_poll(mcu, MCU_RESET_FSM_stRESTART, POLL_EQUAL);
	mcu->mcu_wr(mcu, reg, val);
}

//======================================================================

int mcu_pre_assert_mc_pwr(void *ptr)
{
	unsigned int reg;
	struct apm_mcu *mcu = (struct apm_mcu *)ptr;
	/*
	 * DFI reset
	 */
	reg = mcu->mcu_rd(mcu, MCU_REG_DFI_INIT_CTL);
	reg &= 0xFFFFFFFB;	// ~(0x1 << MCU_DFI_INIT_CTL_DFI_RESET_RNG)
	mcu->mcu_wr(mcu, MCU_REG_DFI_INIT_CTL, reg);

	/*
	 * PHY PBRS & TR reset
	 */
#if 0
	reg = mcu->phy_rd(mcu, CFG_PHY_SRST);
	reg &= 0xFFFFFFFC;
	mcu->phy_wr(mcu, CFG_PHY_SRST, reg);
#else
	phy_rf_write_cfg_prbs_srst(mcu, 0x0);	// KC PHY R20 requirement
	phy_rf_write_cfg_tr_srst(mcu, 0x0);	// KC PHY R20 requirement
#endif
	return 0;
}

//======================================================================

int mcu_post_assert_mc_pwr(void *ptr)
{
	unsigned int reg;
	struct apm_mcu *mcu = (struct apm_mcu *)ptr;
	/*
	 * Start DFI initialization
	 */
	reg = mcu->mcu_rd(mcu, MCU_REG_DFI_INIT_CTL);
	if (1 == ((reg >> MCU_DFI_INIT_CTL_DFI_RESET_RNG) & 0x1)) {
		// DFI RESET still asserted - turn off
		mcu_pre_assert_mc_pwr(mcu);
	}
	// Toggle signal  dfi_init_start to PHY
	reg |= 0x00000001;	// (0x1 << MCU_DFI_INIT_CTL_INIT_START_RNG)
	mcu->mcu_wr(mcu, MCU_REG_DFI_INIT_CTL, reg);
	reg &= 0xFFFFFFFE;
	mcu->mcu_wr(mcu, MCU_REG_DFI_INIT_CTL, reg);

	/*
	 * Wait for Signal dfi_init_complete from PHY
	 */
	do {
		reg = mcu->mcu_rd(mcu, MCU_REG_DFI_INIT_STS);
#ifdef CONFIG_VHP
		reg = 1;
#endif
	} while ((reg & 0x1) == 0);

	return 0;
}				// mcu_post_assert_mc_pwr

//======================================================================

int mcu_post_assert_mc_pwr_tc(void *ptr)
{
	unsigned int reg;
	struct apm_mcu *mcu = (struct apm_mcu *)ptr;

	/* 
	 * Note: TestChip does: MC_POWER_OK -> dfi_init_start -> dfi_reset (deassert)
	 */

	DELAYP(2);
	/*
	 * DFI reset
	 */
	reg = mcu->mcu_rd(mcu, MCU_REG_DFI_INIT_CTL);
	reg &= 0xFFFFFFFB;	// ~(0x1 << MCU_DFI_INIT_CTL_DFI_RESET_RNG)
	mcu->mcu_wr(mcu, MCU_REG_DFI_INIT_CTL, reg);

	/* 
	 * Start DFI initialization
	 */
	DELAYP(1);
	reg = mcu->mcu_rd(mcu, MCU_REG_DFI_INIT_CTL);
	if (1 == ((reg >> MCU_DFI_INIT_CTL_DFI_RESET_RNG) & 0x1)) {
		// DFI RESET still asserted - turn off
		mcu_pre_assert_mc_pwr(mcu);
	}
	// Toggle signal  dfi_init_start to PHY
	reg |= 0x00000001;	// (0x1 << MCU_DFI_INIT_CTL_INIT_START_RNG)
	mcu->mcu_wr(mcu, MCU_REG_DFI_INIT_CTL, reg);
	reg &= 0xFFFFFFFE;
	mcu->mcu_wr(mcu, MCU_REG_DFI_INIT_CTL, reg);

	// Wait for Signal dfi_init_complete from PHY
	do {
		reg = mcu->mcu_rd(mcu, MCU_REG_DFI_INIT_STS);
#ifdef CONFIG_VHP
		reg = 1;
#endif
	} while ((reg & 0x1) == 0);

	return 0;
}				// mcu_post_assert_mc_pwr_tc

//======================================================================

int mcu_pre_init(void *ptr)
{
	struct apm_mcu *mcu = (struct apm_mcu *)ptr;

	if (!mcu->enabled)
		return 0;

	/*
	 * Reset CKE
	 */
	mcu_reset_FSM_poll(mcu, MCU_RESET_FSM_stRESTART, POLL_EQUAL);
	// JHR 1/28 mcu->mcu_wr(mcu, MCU_REG_SWISS_RSTCKE, 0x80000000);

	mcu->p_phy_setup(ptr);

	/*
	 * Pre DDR_MC_POWER_OK phy init
	 */
	mcu->p_phy_pre_init(ptr);	// mcu_pre_assert_mc_pwr(mcu);
	return 0;
}

//======================================================================

int mcu_post_init(void *ptr)
{
	int err = 0;
    struct apm_mcu *mcu = (struct apm_mcu *)ptr;
	if (!mcu->enabled)
		return 0;
	/*
	 * Post assert MC power ok
	 */
	err += mcu->p_phy_post_init(ptr);	// mcu_post_assert_mc_pwr(mcu);
	err += mcu->p_prbs_test(ptr);
	err += mcu->p_dimm_post_init(ptr);
	err += mcu->p_phy_calib(ptr);
	return err;
}

//======================================================================
//======================================================================
//======================================================================

int phy_sw_adj_ctrlupdate(void *ptr)
{
	int unsigned fsm_init_seq = 0;
	int unsigned fsm_init_ctl = 0;
	struct apm_mcu *mcu = (struct apm_mcu *)ptr;
	unsigned int rddata = 0;
	unsigned int poszq;
	unsigned int negzq;
	unsigned int posgood, neggood;

	if (!mcu->enabled) {
		return 0;
	}

	/*
	 * Setup initialization control
	 */
	mcu_reset_FSM_poll(mcu, MCU_RESET_FSM_stRESTART, POLL_EQUAL);
	// Write FSM delay values - should be done is csr config
	rddata = mcu->mcu_rd(mcu, MCU_REG_DDR_INIT_SEQ);
	rddata = (rddata >> MCU_DDR_INIT_SEQ_SETMEMINITDONE_RNG) & 0x1U;
	fsm_init_seq = (1U << MCU_DDR_INIT_SEQ_CTLUPDATE_RNG) | (rddata);

	fsm_init_ctl =
	    (0x1U << MCU_DDR_INIT_CTL_CALIBGO_RNG) |
	    ((0x4U & 0xFU) << MCU_DDR_INIT_CTL_RCWAIT_RNG) |
	    ((0x1U & 0x7U) << MCU_DDR_INIT_CTL_REFRESHCNT_RNG);

	mcu->mcu_wr(mcu, MCU_REG_DDR_INIT_SEQ, fsm_init_seq);
	mcu->mcu_wr(mcu, MCU_REG_DDR_INIT_CTL, fsm_init_ctl);	// Kick off FSM - initializing

	mcu_reset_FSM_poll(mcu, MCU_RESET_FSM_stRESTART, POLL_EQUAL);

	// Read PHY ZQ cal code after first Phy Ctrl Update
	rddata = mcu->phy_rd(mcu, PHY_REG_CFG_ZQ_CAL_CODE);
	debug("MCU-PHY %d: INFO: ZQ Cal Code: 0x%0x\n", mcu->id, rddata);
	poszq = rddata & 0x3FU;
	negzq = (rddata >> 6) & 0x3FU;
	posgood = 0;		// ((poszq > 0x24) && (poszq < 0x38)) ? 1 : 0;
	neggood = 0;		// ((negzq > 0x24) && (negzq < 0x38)) ? 1 : 0;

	if (posgood & neggood) {	// ZQ good
	} else if (posgood) {
		// PHY ZQ broken - copy positive into negative
		rddata = poszq | (poszq << 6);
	} else if (neggood) {
		rddata = negzq | (negzq << 6);
	} else {
		rddata = PHY_ZQCAL_CODE_VALUE;
	}			// Both bad
	mcu->phy_wr(mcu, PHY_REG_CFG_ZQ_CAL_CODE, rddata);
	debug("MCU-PHY %d: INFO: ZQ Cal Code: wrote back 0x%0x\n", mcu->id,
	      rddata);
	rddata = mcu->phy_rd(mcu, PHY_REG_CFG_ZQ_CAL_CODE);
	debug("MCU-PHY %d: INFO: ZQ Cal Code: 0x%0x\n", mcu->id, rddata);
	return 0;
}				// phy_sw_adj_ctrlupdate

//======================================================================

int dimm_mcu_fsm_init(void *ptr)
{
	int unsigned fsm_init_seq = 0;
	int unsigned fsm_init_ctl = 0;
	struct apm_mcu *mcu = (struct apm_mcu *)ptr;
	unsigned int __attribute__ ((unused)) rddata = 0;

	if (!mcu->enabled) {
		return 0;
	}

	/*
	 * Setup initialization control
	 */
	fsm_init_ctl =
	    (0x1U << MCU_DDR_INIT_CTL_CALIBGO_RNG) |
	    ((0x4U & 0xFU) << MCU_DDR_INIT_CTL_RCWAIT_RNG) |
	    ((0x3U & 0x7U) << MCU_DDR_INIT_CTL_REFRESHCNT_RNG);

	// Write FSM delay values - should be done is csr config

	// // Read PHY ZQ cal code after first Phy Ctrl Update
	rddata = phy_read_reg(mcu, PHY_REG_CFG_ZQ_CAL_CODE);
	debug("MCU-PHY %d: INFO: ZQ Cal Code: 0x%0x\n", mcu->id, rddata);

	mcu_reset_FSM_poll(mcu, MCU_RESET_FSM_stRESTART, POLL_EQUAL);

	fsm_init_seq = (1 << MCU_DDR_INIT_SEQ_CLK200ENAB_RNG) | (1 << MCU_DDR_INIT_SEQ_CLK500ENAB_RNG) | (1 << MCU_DDR_INIT_SEQ_TXPRENAB_RNG) | ((mcu->mcu_params.rc_en & 0x1) << MCU_DDR_INIT_SEQ_RCENAB_RNG) |	/*rdimm only */
	    (1 << MCU_DDR_INIT_SEQ_MRENAB_RNG) |
	    (1 << MCU_DDR_INIT_SEQ_ZQCLENAB_RNG) |
	    (DO_INIT_SEQ_CTLUPDATE << MCU_DDR_INIT_SEQ_CTLUPDATE_RNG);

	mcu->mcu_wr(mcu, MCU_REG_DDR_INIT_SEQ, fsm_init_seq);
	mcu->mcu_wr(mcu, MCU_REG_DDR_INIT_CTL, fsm_init_ctl);	// Kick off FSM - initializing

	DELAY(600);
	mcu_reset_FSM_poll(mcu, MCU_RESET_FSM_stRESTART, POLL_EQUAL);

	if (PHY_EN_SW_CTL_UP_ZQ) {
		rddata = phy_sw_adj_ctrlupdate(ptr);
	}

	return 0;
}				// dimm_mcu_fsm_init

//======================================================================
//======================================================================

int mcu_bist_test(void *ptr, int chk_cnt,
		  unsigned int rankA,
		  unsigned int rankB,
		  unsigned int rd2wrgap,
		  unsigned int wr2rdgap,
		  unsigned int wr2wrgap,
		  unsigned int rd2rdgap,
		  unsigned int dtype, unsigned int row, unsigned int col)
{
	// BIST test routine, and check X times, finish BIST
	// return error cnt
	struct apm_mcu *mcu = (struct apm_mcu *)ptr;
	int unsigned fsm_init_seq = 0;
	int unsigned fsm_init_ctl = 0;
	int unsigned ia, foo, status, bctrl;
	int errcnt = 0;
	if (!mcu->enabled) {
		return 0;
	}
	mcu_reset_FSM_poll(mcu, MCU_RESET_FSM_stRESTART, POLL_EQUAL);

	foo = phy_read_reg(mcu, PHY_REG_CFG_ZQ_CAL_CODE);	// read to check 0x44
	debug("MCU-Phy %d: INFO   CFG_ZQ_CAL_CODE=0x%0X\n", mcu->id, foo);
	foo = phy_read_reg(mcu, PHY_REG_CFG_DELAY_FROM_RD_EN);

	debug("MCU-Phy %d: INFO  ########################################\n",
	      mcu->id);
#if APM_SIM
#else
	debug
	    ("MCU-Phy %d: INFO  Bist Test:  rnk(%d/%d) row=0x%4X col=0x%4X cnt=%d\n",
	     mcu->id, rankA, rankB, row, col, chk_cnt);
	debug
	    ("MCU-Phy %d: INFO  Start    :  Rd2Wr=%2d Wr2Rd=%2d Wr2Wr=%2d Rd2Rd=%2d \n",
	     mcu->id, rd2wrgap, wr2rdgap, wr2wrgap, rd2rdgap);
#endif
	//debug("MCU-Phy %d: INFO  ########################################\n", mcu->id);

	switch (dtype) {
	case 1:{
			mcu->mcu_wr(mcu, (MCU_REG_BISTWRDATA0), 0x12345678);
			mcu->mcu_wr(mcu, (MCU_REG_BISTWRDATA0 + (0x4 * 1)),
				    0x9ABCDEF0);
			mcu->mcu_wr(mcu, (MCU_REG_BISTWRDATA0 + (0x4 * 2)),
				    0x33557799);
			mcu->mcu_wr(mcu, (MCU_REG_BISTWRDATA0 + (0x4 * 3)),
				    0x44220066);
			mcu->mcu_wr(mcu, (MCU_REG_BISTWRDATA0 + (0x4 * 4)),
				    0xBBCCAA33);
			break;
		}
	case 0:{		// Constant data for scope
			for (ia = 0; ia < 5; ia++) {
				mcu->mcu_wr(mcu,
					    (MCU_REG_BISTWRDATA0 + (0x4 * ia)),
					    0xAAAAAAAA);
			}
			break;
		}
	default:{
			break;
		}
	}

	mcu->mcu_wr(mcu, MCU_REG_BISTROWCOL,
		    (((row & 0xFFFF) << 16) | (col & 0xFFFF)));
	bctrl = ((rd2wrgap & 0x1F) << 27) | ((wr2rdgap & 0x1F) << 22) | ((wr2wrgap & 0xF) << 18) | ((rd2rdgap & 0xF) << 14) | ((rankA & 0x7) << 11) | ((rankB & 0x7) << 8) | ((rankA & 0x7) << 5) | ((rankB & 0x7) << 2) | 0x3;	// Wr & Rd on
	mcu->mcu_wr(mcu, MCU_REG_BISTCTLSTS, bctrl);
	/* MCU_REG_BISTCTLSTS 
	   31:27 R/W RD2WRGap BIST delay btwn Rd -> Wr
	   26:22 R/W WR2RDGap BIST delay btwn Wr -> Rd
	   21:18 R/W WR2WRGap BIST delay btwn Wr -> Wr
	   17:14 R/W RD2RDGap BIST delay btwn Rd -> Rd
	   13:11 R/W WR0Rank  Select Wr #0 rank
	   10:8  R/W WR1Rank  Select Wr #1 rank
	   7:5   R/W RD0Rank  Select Rd #0 rank
	   4:2   R/W RD1Rank  Select Rd #1 rank
	   1     R/W DoWR     Enable Wr
	   0     R/W DoRD     Enable Rd
	 */

	fsm_init_seq =
	    (1U << MCU_DDR_INIT_SEQ_BISTENAB_RNG) |
	    (DO_INIT_SEQ_CTLUPDATE << MCU_DDR_INIT_SEQ_CTLUPDATE_RNG);
	fsm_init_ctl =
	    (0x1U << MCU_DDR_INIT_CTL_CALIBGO_RNG) | ((0x4U & 0xFU) <<
						      MCU_DDR_INIT_CTL_RCWAIT_RNG)
	    | ((0x1U & 0x7U) << MCU_DDR_INIT_CTL_REFRESHCNT_RNG);
	mcu->mcu_wr(mcu, MCU_REG_DDR_INIT_SEQ, fsm_init_seq);
	mcu->mcu_wr(mcu, MCU_REG_DDR_INIT_CTL, fsm_init_ctl);	// Kick off FSM

	// Check that in BIST state - GONZO if fails 1000 times then Mcu hung!!!
	for (ia = 0; ia < 1000; ia++) {
		// `define MCU_RSTSTS_ICST_RNG         30:24
		foo = mcu->mcu_rd(mcu, MCU_REG_DDR_INIT_STATUS);
		status = (foo >> 24) & 0x7F;
		if ((status >= MCU_RESET_FSM_stBISTACT)
		    && (status <= MCU_RESET_FSM_stBISTCOMPARE)) {
			//debug("Bist Test mcu_Reset FSM doing bist operations (0x%08X)\n",foo);
			break;
		}
	}
	for (ia = 0; ia < chk_cnt; ia++) {
		if ((foo >> MCU_RSTSTS_BISTERR_RNG) & 0x1) {
			debug
			    ("ERROR Bist Test  failed in chk loop (%d of %d)",
			     (ia + 1), chk_cnt);
			debug(" (0x%08X)\n", foo);
			errcnt++;
			break;
		}
		//else { debug("INFO Bist Test good in chk loop (%d of %d) (0x%08X)\n",(ia+1),chk_cnt,foo);  }
		foo = mcu->mcu_rd(mcu, MCU_REG_DDR_INIT_STATUS);
	}
	// Done in any case
	fsm_init_seq =
	    (0U << MCU_DDR_INIT_SEQ_BISTENAB_RNG) |
	    (DO_INIT_SEQ_CTLUPDATE << MCU_DDR_INIT_SEQ_CTLUPDATE_RNG);
	mcu->mcu_wr(mcu, MCU_REG_DDR_INIT_SEQ, fsm_init_seq);

	mcu_reset_FSM_poll(mcu, MCU_RESET_FSM_stRESTART, POLL_EQUAL);

	debug("MCU-Phy %d: INFO  ########################################\n",
	      mcu->id);
	foo = mcu->mcu_rd(mcu, MCU_REG_DDR_INIT_STATUS);
	if ((foo >> MCU_RSTSTS_BISTERR_RNG) & 0x1) {
		debug
		    ("ERROR Bist Test  failed at end (err=%d  DDR_INIT_STATUS=0x%08X) ... done\n",
		     errcnt, foo);
		errcnt++;
	} else {
		debug
		    ("INFO  Bist Test  good at end   (err%d  DDR_INIT_STATUS==0x%08X) ... done\n",
		     errcnt, foo);
	}
	//debug("MCU-Phy %d: INFO  ########################################\n", mcu->id);
	return (errcnt);
}				// mcu_bist_test

//======================================================================
//======================================================================

int mcu_bist_check_in_prog(void *ptr)
{
	// BIST existing Bist running in progress
	// return error cnt
	struct apm_mcu *mcu = (struct apm_mcu *)ptr;
	int unsigned foo, ist, retst;
	int errcnt = 0;
	if (!mcu->enabled) {
		return 0;
	}
	// Check that in BIST state and Bist is 
	// `define MCU_RSTSTS_ICST_RNG         30:24
	foo = mcu->mcu_rd(mcu, MCU_REG_DDR_INIT_STATUS);
	ist = (foo >> 24) & 0x7F;
	retst = (foo >> 16) & 0xFF;
	if (((ist >= MCU_RESET_FSM_stBISTCHK)
	     && (ist <= MCU_RESET_FSM_stBISTCOMPARE))
	    ||
	    (((ist == MCU_RESET_FSM_stWAIT) || (ist == MCU_RESET_FSM_stWAITNOP))
	     && ((retst >= MCU_RESET_FSM_stBISTCHK)
		 && (retst <= MCU_RESET_FSM_stBISTCOMPARE)))) {

		if ((foo >> MCU_RSTSTS_BISTERR_RNG) & 0x1) {
			errcnt++;
		}
		// else okay
	} else {
		errcnt++;
		debug
		    ("MCU[%d]: ERROR mcu_bist_check_in_prog() Bist not running! st=%08X\n",
		     mcu->id, foo);
	}
	return (errcnt);
}

//======================================================================
//======================================================================

int mcu_en_traffic_mem_init_done(void *ptr)
{
	// After all config, init, training, bist, etc
	// Enable traffic to flow to Dimms
	struct apm_mcu *mcu = (struct apm_mcu *)ptr;
	int unsigned fsm_init_seq = 0;
	int unsigned fsm_init_ctl = 0;

	debug(" ENTRY: %s > \n", __FUNCTION__);
	if (!mcu->enabled) {
		return 0;
	}
	debug("MCU[%d] - mcu_en_traffic_mem_init_done\n", mcu->id);

	mcu_reset_FSM_poll(mcu, MCU_RESET_FSM_stRESTART, POLL_EQUAL);

	fsm_init_seq =
	    (1U << MCU_DDR_INIT_SEQ_ZQCLENAB_RNG) |
	    (DO_INIT_SEQ_CTLUPDATE <<
	     MCU_DDR_INIT_SEQ_CTLUPDATE_RNG) | (1U <<
						MCU_DDR_INIT_SEQ_SETMEMINITDONE_RNG);
	fsm_init_ctl =
	    (0x1U << MCU_DDR_INIT_CTL_CALIBGO_RNG) | ((0x4U & 0xFU) <<
						      MCU_DDR_INIT_CTL_RCWAIT_RNG)
	    | ((0x1U & 0x7U) << MCU_DDR_INIT_CTL_REFRESHCNT_RNG);
	mcu->mcu_wr(mcu, MCU_REG_DDR_INIT_SEQ, fsm_init_seq);
	mcu->mcu_wr(mcu, MCU_REG_DDR_INIT_CTL, fsm_init_ctl);	// Kick off FSM
	// Wait for traffic to flow
	mcu_init_done_poll(mcu);

	return 0;
}				// mcu_en_traffic_mem_init_done

//======================================================================
//======================================================================

#if defined(APM_SIM) || defined(APM_VBIOS)
int mcu_en_traffic_mem_test1_raj(void *ptr)
{
	// After all config, init, training, bist, etc
	// Enable traffic to flow to Dimms
	struct apm_mcu *mcu = (struct apm_mcu *)ptr;
	int unsigned fsm_init_seq = 0;
	int unsigned fsm_init_ctl = 0;
	if (!mcu->enabled) {
		return 0;
	}
	mcu_reset_FSM_poll(mcu, MCU_RESET_FSM_stRESTART, POLL_EQUAL);

	fsm_init_seq =
	    (1U << MCU_DDR_INIT_SEQ_ZQCLENAB_RNG) |
	    (DO_INIT_SEQ_CTLUPDATE <<
	     MCU_DDR_INIT_SEQ_CTLUPDATE_RNG) | (1U <<
						MCU_DDR_INIT_SEQ_SETMEMINITDONE_RNG);
	fsm_init_ctl =
	    (0x1U << MCU_DDR_INIT_CTL_CALIBGO_RNG) | ((0x4U & 0xFU) <<
						      MCU_DDR_INIT_CTL_RCWAIT_RNG)
	    | ((0x1U & 0x7U) << MCU_DDR_INIT_CTL_REFRESHCNT_RNG);
	mcu->mcu_wr(mcu, MCU_REG_DDR_INIT_SEQ, fsm_init_seq);
	mcu->mcu_wr(mcu, MCU_REG_DDR_INIT_CTL, fsm_init_ctl);	// Kick off FSM
	// Wait for traffic to flow
	mcu_init_done_poll(mcu);

	// return mem_test1_raj(0xF); // JHR 2/22 
	return mem_test_kc1(0xF);
}				// mcu_en_traffic_mem_test1_raj
#endif
//======================================================================
//======================================================================

int mcu_en_bist_init_config(void *ptr,
			    unsigned int rank0,
			    unsigned int rank1, unsigned int turnon)
{
	/*
	 * After all config, init, training, etc
	 * Prevents traffic from CSW to dimms
	 * Sets up Mcu BIST engine 
	 *    no checking done here. must be done by user.
	 * rank0 & rank1 can be set to same or diff ranks
	 *   uses corresponding mcu delays
	 * turnon - enables bist and exit 
	 - otherwise user can enable after init
	 */
	struct apm_mcu *mcu = (struct apm_mcu *)ptr;
	int unsigned fsm_init_seq = 0;
	int unsigned fsm_init_ctl = 0;
	int unsigned ia, bctrl;
	unsigned int __attribute__ ((unused)) foo;

	if (!mcu->enabled) {
		return 0;
	}
	mcu_reset_FSM_poll(mcu, MCU_RESET_FSM_stRESTART, POLL_EQUAL);

	foo = phy_read_reg(mcu, PHY_REG_CFG_ZQ_CAL_CODE);	// read to check 0x44
	debug("MCU-Phy %d: INFO   CFG_ZQ_CAL_CODE=0x%0X\n", mcu->id, foo);

	for (ia = 0; ia < 5; ia++) {
		mcu->mcu_wr(mcu, (MCU_REG_BISTWRDATA0 + (0x4 * ia)),
			    (0xF5A97C0 | (ia + 3)));
	}
	if ((rank0 & 0x7) == (rank1 & 0x7)) {
		bctrl = ((mcu->mcu_params.rank_rdwr & 0x1F) << 27) |
		    ((mcu->mcu_params.rank_wrrd & 0x1F) << 22) |
		    ((mcu->mcu_params.rank_wrwr & 0xF) << 18) |
		    ((mcu->mcu_params.rank_rdrd & 0xF) << 14) |
		    ((rank0 & 0x7) << 11) |
		    ((rank0 & 0x7) << 8) |
		    ((rank0 & 0x7) << 5) | ((rank0 & 0x7) << 2) | 0x3;
	} else {
		bctrl = ((mcu->mcu_params.sys_rdwr & 0x1F) << 27) |
		    ((mcu->mcu_params.sys_wrrd & 0x1F) << 22) |
		    ((mcu->mcu_params.sys_wrwr & 0xF) << 18) |
		    ((mcu->mcu_params.sys_rdrd & 0xF) << 14) |
		    ((rank0 & 0x7) << 11) |
		    ((rank1 & 0x7) << 8) |
		    ((rank0 & 0x7) << 5) | ((rank1 & 0x7) << 2) | 0x3;
	}
	mcu->mcu_wr(mcu, MCU_REG_BISTROWCOL, 0x012301F0);
	mcu->mcu_wr(mcu, MCU_REG_BISTCTLSTS, bctrl);

	fsm_init_seq =
	    (1U << MCU_DDR_INIT_SEQ_ZQCLENAB_RNG) |
	    (1U << MCU_DDR_INIT_SEQ_BISTENAB_RNG) |
	    (DO_INIT_SEQ_CTLUPDATE <<
	     MCU_DDR_INIT_SEQ_CTLUPDATE_RNG) | (0U <<
						MCU_DDR_INIT_SEQ_SETMEMINITDONE_RNG);
	fsm_init_ctl =
	    ((turnon & 0x1U) << MCU_DDR_INIT_CTL_CALIBGO_RNG) |
	    ((0x4U & 0xFU) << MCU_DDR_INIT_CTL_RCWAIT_RNG) |
	    ((0x1U & 0x7U) << MCU_DDR_INIT_CTL_REFRESHCNT_RNG);
	mcu->mcu_wr(mcu, MCU_REG_DDR_INIT_SEQ, fsm_init_seq);
	mcu->mcu_wr(mcu, MCU_REG_DDR_INIT_CTL, fsm_init_ctl);	// Kick off FSM
	return 0;
}				// mcu_en_bist_init_done

//======================================================================

int mcu_en_bist_init_done_R0(void *ptr)
{
	/* Turn on BIST to rank 0 only
	 */

	return mcu_en_bist_init_config(ptr, 0, 0, 1);
}				// mcu_en_bist_init_done

int mcu_en_bist_init_done_R1(void *ptr)
{
	/* Turn on BIST to rank 1 only
	 */
	return mcu_en_bist_init_config(ptr, 1, 1, 1);
}				// mcu_en_bist_init_done

int mcu_en_bist_init_done_R01(void *ptr)
{
	/* Turn on BIST to rank 0 & 1
	 */
	return mcu_en_bist_init_config(ptr, 0, 1, 1);
}				// mcu_en_bist_init_done

//======================================================================
//======================================================================

int mcu_bist_walk_one_row_test(void *ptr)
{
	// After all config, init, training, bist, etc
	// Should get around Phy bug by writing memory 
	// offset Col address by 2
	struct apm_mcu *mcu = (struct apm_mcu *)ptr;
	int unsigned fsm_init_seq = 0;
	int unsigned fsm_init_ctl = 0;
	int unsigned ia;
	unsigned int __attribute__ ((unused)) foo;

	if (!mcu->enabled) {
		return 0;
	}
	mcu_reset_FSM_poll(mcu, MCU_RESET_FSM_stRESTART, POLL_EQUAL);

	foo = phy_read_reg(mcu, PHY_REG_CFG_ZQ_CAL_CODE);	//just read it to check 0x44
	debug("MCU-Phy %d: INFO   CFG_ZQ_CAL_CODE=0x%0X\n", mcu->id, foo);

	//for (ia = 0; ia < 5; ia++) {
	mcu->mcu_wr(mcu, (MCU_REG_BISTWRDATA0 + (0x4 * 0)), 0xEEDDCCBB);
	mcu->mcu_wr(mcu, (MCU_REG_BISTWRDATA0 + (0x4 * 1)), 0xAA998877);
	mcu->mcu_wr(mcu, (MCU_REG_BISTWRDATA0 + (0x4 * 2)), 0x66554433);
	mcu->mcu_wr(mcu, (MCU_REG_BISTWRDATA0 + (0x4 * 3)), 0x221100FF);
	mcu->mcu_wr(mcu, (MCU_REG_BISTWRDATA0 + (0x4 * 4)), 0x12345678);
	//}

	mcu->mcu_wr(mcu, MCU_REG_BISTROWCOL, 0x00000000);
	mcu->mcu_wr(mcu, MCU_REG_BISTCTLSTS, 0xFFFFC002);
	mcu->mcu_wr(mcu, MCU_REG_WRODTTABLO, 0x00000001);

	fsm_init_seq =
	    (1U << MCU_DDR_INIT_SEQ_ZQCLENAB_RNG) |
	    (1U << MCU_DDR_INIT_SEQ_BISTENAB_RNG) |
	    (DO_INIT_SEQ_CTLUPDATE <<
	     MCU_DDR_INIT_SEQ_CTLUPDATE_RNG) | (1U <<
						MCU_DDR_INIT_SEQ_SETMEMINITDONE_RNG);
	fsm_init_ctl =
	    (0x1U << MCU_DDR_INIT_CTL_CALIBGO_RNG) | ((0x4U & 0xFU) <<
						      MCU_DDR_INIT_CTL_RCWAIT_RNG)
	    | ((0x1U & 0x7U) << MCU_DDR_INIT_CTL_REFRESHCNT_RNG);
	mcu->mcu_wr(mcu, MCU_REG_DDR_INIT_SEQ, fsm_init_seq);
	mcu->mcu_wr(mcu, MCU_REG_DDR_INIT_CTL, fsm_init_ctl);	// Kick off FSM
	// Trigger BIST Automatically

	for (ia = 0; ia < 0x100; ia = ia + 2) {
		mcu->mcu_wr(mcu, MCU_REG_BISTROWCOL, (0x00000000 + ia));
	}

	// Turn off Bist and enable traffic
	fsm_init_seq =
	    (1U << MCU_DDR_INIT_SEQ_ZQCLENAB_RNG) |
	    (0U << MCU_DDR_INIT_SEQ_BISTENAB_RNG) |
	    (DO_INIT_SEQ_CTLUPDATE <<
	     MCU_DDR_INIT_SEQ_CTLUPDATE_RNG) | (0U <<
						MCU_DDR_INIT_SEQ_SETMEMINITDONE_RNG);
	mcu->mcu_wr(mcu, MCU_REG_DDR_INIT_SEQ, fsm_init_seq);
	return 0;
}				// mcu_bist_walk_one_row_test

//======================================================================
//======================================================================

int mcu_bist_chk_b2b_test(void *ptr)
{
	// After all config, init, training, 
	// Run BIST routine, and check X times, finish BIST then,
	// Enable traffic to flow to Dimms
	struct apm_mcu *mcu = (struct apm_mcu *)ptr;
	int unsigned fsm_init_seq = 0;
	int unsigned fsm_init_ctl = 0;
	int unsigned en_rdfifo_rst;
	unsigned int __attribute__ ((unused)) foo;

	int errcnt = 0;
	if (!mcu->enabled) {
		return 0;
	}
	if (mcu->mcu_params.by4_mode == 0) {
		if ((mcu->phy_params.cfg_macro_en_val !=
		     KCPHY_CFG_MACRO_x8_MASK)) {
			return 0;
		}
	} else {
		if ((mcu->phy_params.cfg_macro_en_val !=
		     KCPHY_CFG_MACRO_x4_MASK)) {
			return 0;
		}
	}
	en_rdfifo_rst = 1;
	/*            Bist test    chkcnt,rnkA,rnkB,rd2wr,wr2rd,wr2wr,rd2rd,dtype,row,   col */
	errcnt +=
	    mcu_bist_test(ptr, 4, 0, 0, 0xB, 0xB, 0x8, 0x8, 1, 0x122, 0x78);
	if (en_rdfifo_rst) {
		mcu_phy_rdfifo_reset(ptr);
	}
	errcnt +=
	    mcu_bist_test(ptr, 4, 0, 0, 0xB, 0xB, 0x6, 0x6, 1, 0x123, 0x78);
	if (en_rdfifo_rst) {
		mcu_phy_rdfifo_reset(ptr);
	}
	errcnt +=
	    mcu_bist_test(ptr, 4, 0, 0, 0xB, 0xB, 0x4, 0x4, 1, 0x124, 0x78);
	if (en_rdfifo_rst) {
		mcu_phy_rdfifo_reset(ptr);
	}
	errcnt +=
	    mcu_bist_test(ptr, 4, 0, 0, 0xB, 0xB, 0x3, 0x3, 1, 0x125, 0x78);
	if (en_rdfifo_rst) {
		mcu_phy_rdfifo_reset(ptr);
	}
	errcnt +=
	    mcu_bist_test(ptr, 4, 0, 0, 0xB, 0xB, 0x3, 0x2, 1, 0x126, 0x78);
	if (en_rdfifo_rst) {
		mcu_phy_rdfifo_reset(ptr);
	}
	errcnt +=
	    mcu_bist_test(ptr, 4, 0, 0, 0xB, 0xB, 0x2, 0x2, 1, 0x127, 0x78);
	if (en_rdfifo_rst) {
		mcu_phy_rdfifo_reset(ptr);
	}
	errcnt +=
	    mcu_bist_test(ptr, 4, 0, 0, 0xB, 0xB, 0x1, 0x2, 1, 0x128, 0x78);
	if (en_rdfifo_rst) {
		mcu_phy_rdfifo_reset(ptr);
	}
	errcnt +=
	    mcu_bist_test(ptr, 4, 0, 0, 0xB, 0xB, 0x1, 0x1, 1, 0x129, 0x78);

	errcnt +=
	    mcu_bist_test(ptr, 4, 0, 0, 0xB, 0xB, 0x7, 0x7, 1, 0x12A, 0x78);

	mcu_reset_FSM_poll(mcu, MCU_RESET_FSM_stRESTART, POLL_EQUAL);

	foo = phy_read_reg(mcu, PHY_REG_CFG_ZQ_CAL_CODE);	// read to check 0x44
	debug("MCU-Phy %d: INFO   CFG_ZQ_CAL_CODE=0x%0X\n", mcu->id, foo);

	fsm_init_seq =
	    (DO_INIT_SEQ_CTLUPDATE <<
	     MCU_DDR_INIT_SEQ_CTLUPDATE_RNG) | (0U <<
						MCU_DDR_INIT_SEQ_SETMEMINITDONE_RNG);
	fsm_init_ctl =
	    (0x1U << MCU_DDR_INIT_CTL_CALIBGO_RNG) | ((0x4U & 0xFU) <<
						      MCU_DDR_INIT_CTL_RCWAIT_RNG)
	    | ((0x1U & 0x7U) << MCU_DDR_INIT_CTL_REFRESHCNT_RNG);
	mcu->mcu_wr(mcu, MCU_REG_DDR_INIT_SEQ, fsm_init_seq);
	mcu->mcu_wr(mcu, MCU_REG_DDR_INIT_CTL, fsm_init_ctl);	// Kick off FSM

	return (errcnt);
}				// mcu_bist_chk_b2b_test

//======================================================================
//======================================================================

int mcu_bist_shmoo_test(void *ptr)
{
	// After all config, init, training, 
	// Run BIST routine, and check X times, finish BIST then,
	// Enable traffic to flow to Dimms
	struct apm_mcu *mcu = (struct apm_mcu *)ptr;
	int unsigned fsm_init_seq = 0;
	int unsigned fsm_init_ctl = 0;
	int unsigned row, col, en_rdfifo_rst;
	unsigned int __attribute__ ((unused)) foo;
	int ia, jb, kc, ld;
	int errcnt = 0;

	if (!mcu->enabled) {
		return 0;
	}
	if (mcu->mcu_params.by4_mode == 0) {
		if ((mcu->phy_params.cfg_macro_en_val !=
		     KCPHY_CFG_MACRO_x8_MASK)) {
			return 0;
		}
	} else {
		if ((mcu->phy_params.cfg_macro_en_val !=
		     KCPHY_CFG_MACRO_x4_MASK)) {
			return 0;
		}
	}
	en_rdfifo_rst = 1;
	row = 0x20;
	col = 0x10;
	for (ia = mcu->mcu_params.rank_rdwr; ia < 12; ia = ia + 2) {
		for (jb = mcu->mcu_params.rank_wrrd; jb < 10; jb = jb + 2) {
			for (kc = 0x4; kc > 1; kc--) {
				for (ld = 0x4; ld > 1; ld--) {
					/*            Bist test    chkcnt,rnkA,rnkB,rd2wr,wr2rd,wr2wr,rd2rd,dtype,row, col */
					errcnt +=
					    mcu_bist_test(ptr, 4, 0, 0, ia, jb,
							  kc, ld, 1, row, col);
					if (en_rdfifo_rst) {
						mcu_phy_rdfifo_reset(ptr);
					}
					row += 0x1;
				}
				col += 0x8;
			}
		}
	}

	mcu_reset_FSM_poll(mcu, MCU_RESET_FSM_stRESTART, POLL_EQUAL);

	foo = phy_read_reg(mcu, PHY_REG_CFG_ZQ_CAL_CODE);	// read to check 0x44
	debug("MCU-Phy %d: INFO   CFG_ZQ_CAL_CODE=0x%0X\n", mcu->id, foo);

	fsm_init_seq =
	    (DO_INIT_SEQ_CTLUPDATE <<
	     MCU_DDR_INIT_SEQ_CTLUPDATE_RNG) | (0U <<
						MCU_DDR_INIT_SEQ_SETMEMINITDONE_RNG);
	fsm_init_ctl =
	    (0x1U << MCU_DDR_INIT_CTL_CALIBGO_RNG) | ((0x4U & 0xFU) <<
						      MCU_DDR_INIT_CTL_RCWAIT_RNG)
	    | ((0x1U & 0x7U) << MCU_DDR_INIT_CTL_REFRESHCNT_RNG);
	mcu->mcu_wr(mcu, MCU_REG_DDR_INIT_SEQ, fsm_init_seq);
	mcu->mcu_wr(mcu, MCU_REG_DDR_INIT_CTL, fsm_init_ctl);	// Kick off FSM
	return (errcnt);
}				// mcu_bist_shmoo_test

//======================================================================
//======================================================================

int mcu_bist_chk_b2b_multi_rank_test(void *ptr)
{
	// After all config, init, training, 
	// Run BIST routine, and check X times, finish BIST then,
	// Enable traffic to flow to Dimms
	struct apm_mcu *mcu = (struct apm_mcu *)ptr;
	int unsigned fsm_init_seq = 0;
	int unsigned fsm_init_ctl = 0;
	int unsigned en_rdfifo_rst;
	unsigned int __attribute__ ((unused)) foo;
	int unsigned rnk0, rnk1;
	int unsigned rd2wr, wr2rd, rd2rd, wr2wr;

	int errcnt = 0;
	if (!mcu->enabled) {
		return 0;
	}
	if (mcu->mcu_params.by4_mode == 0) {
		if ((mcu->phy_params.cfg_macro_en_val !=
		     KCPHY_CFG_MACRO_x8_MASK)) {
			return 0;
		}
	} else {
		if ((mcu->phy_params.cfg_macro_en_val !=
		     KCPHY_CFG_MACRO_x4_MASK)) {
			return 0;
		}
	}

	en_rdfifo_rst = 1;
	rnk0 = 0;
	rnk1 = 1;
	rd2wr = mcu->mcu_params.sys_rdwr;
	wr2rd = mcu->mcu_params.sys_wrrd;
	rd2rd = mcu->mcu_params.sys_rdrd;
	wr2wr = mcu->mcu_params.sys_wrwr;

	/*            Bist test   chkcnt,rnkA, rnkB, rd2wr, wr2rd, wr2wr, rd2rd,dtype,row,   col */
	errcnt +=
	    mcu_bist_test(ptr, 4, rnk0, rnk1, rd2wr, wr2rd, wr2wr, rd2rd, 1,
			  0x111, 0x78);
	if (en_rdfifo_rst) {
		mcu_phy_rdfifo_reset(ptr);
	}
	errcnt +=
	    mcu_bist_test(ptr, 4, rnk0, rnk1, rd2wr, wr2rd, wr2wr, ++rd2rd, 1,
			  0x112, 0x78);
	if (en_rdfifo_rst) {
		mcu_phy_rdfifo_reset(ptr);
	}
	errcnt +=
	    mcu_bist_test(ptr, 4, rnk0, rnk1, rd2wr, wr2rd, ++wr2wr, rd2rd, 1,
			  0x113, 0x78);
	if (en_rdfifo_rst) {
		mcu_phy_rdfifo_reset(ptr);
	}
	errcnt +=
	    mcu_bist_test(ptr, 4, rnk0, rnk1, rd2wr, ++wr2rd, wr2wr, rd2rd, 1,
			  0x114, 0x78);
	if (en_rdfifo_rst) {
		mcu_phy_rdfifo_reset(ptr);
	}
	errcnt +=
	    mcu_bist_test(ptr, 4, rnk0, rnk1, ++rd2wr, wr2rd, wr2wr, rd2rd, 1,
			  0x115, 0x78);
	if (en_rdfifo_rst) {
		mcu_phy_rdfifo_reset(ptr);
	}
	errcnt +=
	    mcu_bist_test(ptr, 4, rnk0, rnk1, rd2wr, wr2rd, wr2wr, ++rd2rd, 1,
			  0x116, 0x78);
	if (en_rdfifo_rst) {
		mcu_phy_rdfifo_reset(ptr);
	}
	errcnt +=
	    mcu_bist_test(ptr, 4, rnk0, rnk1, rd2wr, wr2rd, ++wr2wr, rd2rd, 1,
			  0x117, 0x78);
	if (en_rdfifo_rst) {
		mcu_phy_rdfifo_reset(ptr);
	}
	errcnt +=
	    mcu_bist_test(ptr, 4, rnk0, rnk1, rd2wr, ++wr2rd, wr2wr, rd2rd, 1,
			  0x118, 0x78);
	if (en_rdfifo_rst) {
		mcu_phy_rdfifo_reset(ptr);
	}
	errcnt +=
	    mcu_bist_test(ptr, 4, rnk0, rnk1, ++rd2wr, wr2rd, wr2wr, rd2rd, 1,
			  0x119, 0x78);
	if (en_rdfifo_rst) {
		mcu_phy_rdfifo_reset(ptr);
	}
	// Same Rank 
	rd2wr = mcu->mcu_params.rank_rdwr;
	wr2rd = mcu->mcu_params.rank_wrrd;
	rd2rd = mcu->mcu_params.rank_rdrd;
	wr2wr = mcu->mcu_params.rank_wrwr;

	errcnt +=
	    mcu_bist_test(ptr, 4, rnk0, rnk0, rd2wr, wr2rd, wr2wr, rd2rd, 1,
			  0x120, 0x78);
	if (en_rdfifo_rst) {
		mcu_phy_rdfifo_reset(ptr);
	}
	errcnt +=
	    mcu_bist_test(ptr, 4, rnk1, rnk1, rd2wr, wr2rd, wr2wr, rd2rd, 1,
			  0x121, 0x78);
	if (en_rdfifo_rst) {
		mcu_phy_rdfifo_reset(ptr);
	}

	mcu_reset_FSM_poll(mcu, MCU_RESET_FSM_stRESTART, POLL_EQUAL);

	foo = phy_read_reg(mcu, PHY_REG_CFG_ZQ_CAL_CODE);	// read to check 0x44
	debug("MCU-Phy %d: INFO   CFG_ZQ_CAL_CODE=0x%0X\n", mcu->id, foo);

	fsm_init_seq =
	    (DO_INIT_SEQ_CTLUPDATE <<
	     MCU_DDR_INIT_SEQ_CTLUPDATE_RNG) | (0U <<
						MCU_DDR_INIT_SEQ_SETMEMINITDONE_RNG);
	fsm_init_ctl =
	    (0x1U << MCU_DDR_INIT_CTL_CALIBGO_RNG) | ((0x4U & 0xFU) <<
						      MCU_DDR_INIT_CTL_RCWAIT_RNG)
	    | ((0x1U & 0x7U) << MCU_DDR_INIT_CTL_REFRESHCNT_RNG);
	mcu->mcu_wr(mcu, MCU_REG_DDR_INIT_SEQ, fsm_init_seq);
	mcu->mcu_wr(mcu, MCU_REG_DDR_INIT_CTL, fsm_init_ctl);	// Kick off FSM

	return (errcnt);
}				// mcu_bist_chk_b2b_multi_rank_test

//======================================================================
//======================================================================
//======================================================================
// Setup Memory for turning on ECC
//======================================================================

int memc_ecc_init_en(void *ptr)
{
	struct apm_memc *memc = (struct apm_memc *)ptr;
	struct apm_mcu *mcu;
	unsigned int iia, mcugecr[CONFIG_SYS_NUM_DDR_CTLRS],
	    scrubctl[CONFIG_SYS_NUM_DDR_CTLRS];
	unsigned int errcnt = 0;
	unsigned long long *addr_ptr;
	unsigned long long data2;

	debug
	    ("INFO: ECC initialization of ddr space starting...memc_ecc_init_en()\n");
	// Use global var to see which of three setups to use
	// check config - disable reporting (should be off)
	for (iia = 0; iia < CONFIG_SYS_NUM_DDR_CTLRS; iia++) {
		mcu = (struct apm_mcu *)&memc->mcu[iia];
		if (!(mcu->enabled))
			continue;
		if ((mcu->mcu_params.ECCenable == 0)	// ||
		    //(((mcu->mcu_params.glb_err_ctrl >> 7) & 0x1) == 0)
		    ) {
			continue;
		}
		// Turn off ECC IRQ & counting
		mcugecr[iia] = mcu->mcu_rd(mcu, MCU_REG_MCUGECR);
		if ((((mcugecr[iia] >> 7) & 0x1) == 1) ||
		    (((mcugecr[iia] >> 2) & 0x1) == 1) ||
		    (((mcugecr[iia]) & 0x1) == 1)) {
			mcu->mcu_wr(mcu, MCU_REG_MCUGECR,
				    (mcugecr[iia] & 0xFFFFFF7AU));
		}
		// Disable Demand Scrub - ?? needed
		scrubctl[iia] = mcu->mcu_rd(mcu, MCU_REG_SCRUB_CTL);
		if (((scrubctl[iia] >> 1) & 0x1) == 1) {
			mcu->mcu_wr(mcu, MCU_REG_SCRUB_CTL,
				    (scrubctl[iia] & 0xFFFFFFFDU));
		}
	}

	// Initialize ECC syndrom by partial write into each 64B location
#if !(defined(APM_SIM) || defined(APM_VBIOS))
	printf(" ECC init ................");
	printf("\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b");
#endif
	data2 = 0;

	for (iia = 0; iia < memc->memspace.num_mem_regions; iia++) {
		addr_ptr = (unsigned long long *)(memc->memspace.str_addr[iia]);
#ifdef APM_VBIOS
		debug("ECC-init region %d @ 0x%lx ...", iia,
		      (unsigned long long)addr_ptr);
#endif
		for (;
		     addr_ptr <
		     ((unsigned long long *)(memc->memspace.end_addr[iia]));
		     addr_ptr += 8) {
			// Wr 8B of each 64B chunk for all memory
			*addr_ptr = 0x0ULL;	
#if (defined(APM_SIM) || defined(APM_VBIOS))
			if (((unsigned long long)addr_ptr % 0x10000000) == 0)
				debug(".");
#else
			if (!((unsigned long)addr_ptr & 0xFFFFFF)) {
#if !(defined(APM_SIM) || defined(APM_VBIOS))
				printf("*");
#endif
				data2++;
			}
			if (data2 == 16) {
				data2 = 0;
#if !(defined(APM_SIM) || defined(APM_VBIOS))
				printf("\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b");
				printf("................");
				printf("\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b");
#endif
			}
#endif
		}
#ifdef APM_VBIOS
		debug("\n");
#endif
	}
#ifdef APM_VBIOS
	data_cache_flush_all();
#endif
#if !(defined(APM_SIM) || defined(APM_VBIOS))
	printf("                ");
	printf("\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b");
	printf("\b\b\b\b\b");
#endif
	debug("INFO: ECC init delay before enable...memc_ecc_init_en()\n");
	DELAY(40000);
	// Turn on Final ECC algo
	for (iia = 0; iia < CONFIG_SYS_NUM_DDR_CTLRS; iia++) {
		mcu = (struct apm_mcu *)&memc->mcu[iia];
		if (!(mcu->enabled))
			continue;
		if ((mcu->mcu_params.ECCenable == 0)	// ||
		    // (((mcu->mcu_params.glb_err_ctrl >> 7) & 0x1) == 0)
		    ) {
			continue;
		}

		if (mcu->mcu_params.ECCenable) {
			switch (mcu->mcu_params.ECCscheme) {
			case 0:	//Disable all ECC
				mcu->mcu_wr(mcu, MCU_REG_MCUGECR,
					    (mcugecr[iia] & 0xFFFFFF7AU));
				mcu->mcu_wr(mcu, MCU_REG_SCRUB_CTL, 0);	//Disable Scrub
				break;
			case 1:
				mcu->mcu_wr(mcu, MCU_REG_MCUGECR,
					    (mcugecr[iia] | 0x10084));
				mcu->mcu_wr(mcu, MCU_REG_SCRUB_CTL,
					    (scrubctl[iia]));
				break;
			case 2:
				mcu->mcu_wr(mcu, MCU_REG_MCUGECR,
					    (mcugecr[iia] | 0x10084));
				mcu->mcu_wr(mcu, MCU_REG_SCRUB_CTL,
					    (scrubctl[iia] | 0x2));
				break;
			case 3:
				mcu->mcu_wr(mcu, MCU_REG_MCUGECR,
					    (mcugecr[iia] | 0x10085));
				mcu->mcu_wr(mcu, MCU_REG_SCRUB_CTL,
					    (scrubctl[iia] | 0x2));
				break;
			default:	// Leave configured value alone
				mcu->mcu_wr(mcu, MCU_REG_MCUGECR,
					    (mcugecr[iia]));
				mcu->mcu_wr(mcu, MCU_REG_SCRUB_CTL,
					    (scrubctl[iia]));
				break;
			}
		} else {
			mcu->mcu_wr(mcu, MCU_REG_MCUGECR, (mcugecr[iia] & 0xFFFFFF7AU));	// Disable  ECC
			mcu->mcu_wr(mcu, MCU_REG_SCRUB_CTL, 0);	//Disable Scrub
		}

	}
	DELAY(40000);
	debug("INFO: ECC init delay after enable...memc_ecc_init_en()\n");
	// Spot check 20 locations for ECC errors
	for (iia = 0; iia < memc->memspace.num_mem_regions; iia++) {
		addr_ptr = (unsigned long long *)(memc->memspace.str_addr[iia]);
		for (;
		     addr_ptr <
		     ((unsigned long long *)(memc->memspace.end_addr[iia]));
		     addr_ptr += 0x40000) {
			// Rd 8B of each 64B chunk for all memory
			data2 = *addr_ptr;
			if (data2 != 0x0) {
				debug
				    ("ERROR read after ecc init sa=0x%p (act=0x%llx vs exp=0)\n",
				     addr_ptr, data2);
				errcnt++;
			}
		}
	}
#ifdef APM_VBIOS
	data_cache_flush_all();
#endif

	if (errcnt)
		debug
		    ("INFO: ECC init of ddr space done with errors=%d...memc_ecc_init_en()\n",
		     errcnt);
	return (errcnt);
}				// memc_ecc_init_en

//======================================================================
// Phy ctrl update 
//======================================================================

#if defined(APM_SIM) || defined(APM_VBIOS)

int mcu_phy_ctl_update_loop(void *ptr)
{
	// After all config, init, training, bist, etc
	// Enable traffic to flow to Dimms
	struct apm_mcu *mcu = (struct apm_mcu *)ptr;
	int unsigned fsm_init_seq = 0;
	int unsigned fsm_init_ctl = 0;
	int unsigned ia;
	unsigned int __attribute__ ((unused)) foo;
	unsigned int __attribute__ ((unused)) last_fsm_init_seq = 0;

	int errcnt = 0;
	if (!mcu->enabled) {
		return 0;
	}
	mcu_reset_FSM_poll(mcu, MCU_RESET_FSM_stRESTART, POLL_EQUAL);

	foo = phy_read_reg(mcu, PHY_REG_CFG_ZQ_CAL_CODE);	// read to check 0x44
	debug("MCU-Phy %d: INFO   CFG_ZQ_CAL_CODE=0x%0X\n", mcu->id, foo);

	last_fsm_init_seq = mcu->mcu_rd(mcu, MCU_REG_DDR_INIT_SEQ);

	fsm_init_seq = ((0x1) << MCU_DDR_INIT_SEQ_SETMEMINITDONE_RNG);
	fsm_init_ctl =
	    (0x1U << MCU_DDR_INIT_CTL_CALIBGO_RNG) |
	    ((0x4U & 0xFU) << MCU_DDR_INIT_CTL_RCWAIT_RNG) |
	    ((0x1U & 0x7U) << MCU_DDR_INIT_CTL_REFRESHCNT_RNG);

	mcu->mcu_wr(mcu, MCU_REG_DDR_INIT_SEQ, fsm_init_seq);
	mcu->mcu_wr(mcu, MCU_REG_DDR_INIT_CTL, fsm_init_ctl);	// Kick off FSM
	mcu_reset_FSM_poll(mcu, MCU_RESET_FSM_stRESTART, POLL_EQUAL);

	for (ia = 0; ia < 4; ia++) {

		errcnt += mem_test1_raj(0x1);

		fsm_init_seq =
		    (1U << MCU_DDR_INIT_SEQ_ZQCLENAB_RNG) |
		    (1U << MCU_DDR_INIT_SEQ_CTLUPDATE_RNG) |
		    (1U << MCU_DDR_INIT_SEQ_SETMEMINITDONE_RNG);
		mcu->mcu_wr(mcu, MCU_REG_DDR_INIT_SEQ, fsm_init_seq);
		mcu->mcu_wr(mcu, MCU_REG_DDR_INIT_CTL, fsm_init_ctl);	// Kick off FSM
		mcu_reset_FSM_poll(mcu, MCU_RESET_FSM_stRESTART, POLL_EQUAL);

		foo = phy_read_reg(mcu, PHY_REG_CFG_ZQ_CAL_CODE);	// read to check 0x44
		debug("MCU-Phy %d: INFO   CFG_ZQ_CAL_CODE=0x%0X\n", mcu->id,
		      foo);
	}

	return errcnt;
}				// mcu_phy_ctl_update_loop
#endif

/******************************************************************************
 *     Mcu_RESET SW Issue (SWISS) CSR operations
 *        Common tasks from Mcu_Reset FSM
 *****************************************************************************/

void mcu_set_SWISS_TRNLOAD(void *p)
{
	// Pulse dfi_wrlvl_load dfi_rdlvl_load from Mcu to PHY
	// Tells phy its Delay CSRs are changed and ready to use
	struct apm_mcu *mcu = (struct apm_mcu *)p;
	// Once is enought
	unsigned int dat = 0x80000000 | mcu->phy_params.cfg_macro_en_val;
	mcu->mcu_wr(mcu, MCU_REG_SWISS_TRNWRLOAD, dat);
	mcu->mcu_wr(mcu, MCU_REG_SWISS_TRNRDLOAD, dat);
}

void mcu_set_SWISS_ODTADDR(void *ptr, int unsigned enab, int unsigned bnk	/* [2:0] */
			   , int unsigned addr	/* [15:0] */
			   , int unsigned odtRd, int unsigned odtWr)
{
	int unsigned data = 0;
	struct apm_mcu *mcu = (struct apm_mcu *)ptr;
	data =
	    ((enab & 0x1) << 31) |
	    ((odtRd & 0x1) << 21) |
	    ((odtWr & 0x1) << 20) | ((bnk & 0x7) << 16) | (addr & 0xFFFF);
	/* 
	   MCU_SWISS_ODTADDR_ENABLE_RNG        31
	   MCU_SWISS_ODTADDR_ODTRD_RNG         21
	   MCU_SWISS_ODTADDR_ODTWR_RNG         20
	   MCU_SWISS_ODTADDR_BANK_RNG          18:16
	   MCU_SWISS_ODTADDR_ADDRESS_RNG       15:0
	 */
	mcu->mcu_wr(mcu, MCU_REG_SWISS_ODTADDR, data);
#if APM_SIM
#else
	debug
	    ("MCU_REG_SWISS_ODTADDR   set: en=%1d odtRd=%1d odtWr=%1d bnk=%01x a=0x%04x\n",
	     enab, odtRd, odtWr, bnk, addr);
#endif
}				// mcu_set_SWISS_ODTADDR

void mcu_set_SWISS_TRNCTL(void *ptr, int unsigned enab, int unsigned wrlvl_en, int unsigned rdlvl_gate_en, int unsigned rdlvl_en, int unsigned wrlvl_cs_n	//[7:0]= 'hFF
			  , int unsigned rdlvl_cs_n	//[7:0]= 'hFF
    )
{
	int unsigned data = 0;
	struct apm_mcu *mcu = (struct apm_mcu *)ptr;
	data = ((enab & 0x1) << 31) |
	    ((wrlvl_en & 0x1) << 18) |
	    ((rdlvl_gate_en & 0x1) << 17) |
	    ((rdlvl_en & 0x1) << 16) |
	    ((wrlvl_cs_n & 0xFF) << 8) | (rdlvl_cs_n & 0xFF);
	/*
	   MCU_SWISS_TRNCTL_ENABLE_RNG         31
	   MCU_SWISS_TRNCTL_DFI_WRLVL_EN_RNG           18
	   MCU_SWISS_TRNCTL_DFI_RDLVL_GATE_EN_RNG              17
	   MCU_SWISS_TRNCTL_DFI_RDLVL_EN_RNG           16
	   MCU_SWISS_TRNCTL_DFI_WRLVL_CS_N_RNG         15:8
	   MCU_SWISS_TRNCTL_DFI_RDLVL_CS_N_RNG         7:0
	 */
	mcu->mcu_wr(mcu, MCU_REG_SWISS_TRNCTL, data);
#if APM_SIM
#else
	debug
	    ("MCU_REG_SWISS_TRNCTL   set: en=%1d wrlvl_en=%1d rdlvl_gate_en=%1d rdlvl_en=%1d wrlvl_cs_n=0x%02x rdlvl_cs_n=0x%02x\n",
	     enab, wrlvl_en, rdlvl_gate_en, rdlvl_en, wrlvl_cs_n, rdlvl_cs_n);
#endif
}				// mcu_set_SWISS_TRNCTL

void mcu_set_SWISS_OPCTL(void *ptr, int unsigned sendOp, int unsigned rddata_en, int unsigned cmd_n	//[2:0] = 'h7
			 , int unsigned cs_n	//[7:0] = 'hFF
    )
{
	int unsigned data = 0;
	struct apm_mcu *mcu = (struct apm_mcu *)ptr;
	data = ((sendOp & 0x1) << 31) | ((rddata_en & 0x1) << 12) | ((cmd_n & 0x7) << 8) |	// {RAS_N, CAS_N, WE_N}
	    (cs_n & 0xFF);
	/*
	   MCU_SWISS_OPCTL_SENDOP_RNG          31
	   MCU_SWISS_OPCTL_DFI_INIT_RDDATA_EN_RNG      12
	   MCU_SWISS_OPCTL_DFI_INIT_CMD_N_RNG          10:8
	   MCU_SWISS_OPCTL_DFI_INIT_CS_N_RNG           7:0
	 */
	mcu->mcu_wr(mcu, MCU_REG_SWISS_OPCTL, data);
#if APM_SIM
#else
	debug
	    ("MCU_REG_SWISS_OPCTL   set: sndOp=%1d rddata_en=%1d cmd_n=%1d cs_n=0x%02x\n",
	     sendOp, rddata_en, cmd_n, cs_n);
#endif
}				// mcu_set_SWISS_OPCTL
