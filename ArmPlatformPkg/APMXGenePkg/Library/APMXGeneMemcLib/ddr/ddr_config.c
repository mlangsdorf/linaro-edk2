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

#ifdef APM_SIM
#include "apm_ddr_sdram.h"
#include "ddr_lib.h"

#define DDR_RELAX_EN        0
#define DDR_RELAX_MARGIN_0  0
#define DDR_RELAX_MARGIN_1  0
#define RD2RD_MARGIN   0
#define RD2WR_MARGIN   1
#define WR2WR_MARGIN   0
#define WR2RD_MARGIN   1

#define EN_RDDESKEW 0
#define EN_RDLVL2ND 0
#define EN_WRDESKEW 1

#define debug1(fmt,args...) debug(fmt ,##args)

#elif defined(APM_VBIOS)

#include <common.h>
#include <stdio.h>
#include <string.h>
#include <apm_ddr_sdram.h>
#include "ddr_lib.h"

#define debug(fmt,args...)     lprintf(8, fmt ,##args)
#define debug1(fmt,args...)    lprintf(5, fmt ,##args)

unsigned int g_ddr_relax_en = 0;
unsigned int g_ddr_relax_margin_0 = 0;
unsigned int g_ddr_relax_margin_1 = 0;
unsigned int g_ddr_rd2rdmargin[4] = { 0, 0, 0, 0 };
unsigned int g_ddr_rd2wrmargin[4] = { 1, 1, 1, 1 };
unsigned int g_ddr_wr2wrmargin[4] = { 0, 0, 0, 0 };
unsigned int g_ddr_wr2rdmargin[4] = { 1, 1, 1, 1 };
unsigned int g_ddr_pll_force = 0;
unsigned int g_ddr_pll_div[4] = { 0, 0, 0, 0 };
unsigned int g_ddr_en_rddeskew = 0;
unsigned int g_ddr_en_rdlvl2nd = 0;
unsigned int g_ddr_en_wrdeskew = 1;
unsigned int g_ddr_tcrl[4] = { 1, 1, 1, 1 };
unsigned int g_ddr_tcwl[4] = { 0, 0, 0, 0 };
unsigned int g_ddr_mr_valid = 0;
unsigned int g_ddr_mr_rttnom = DIMM_MR1_RTTNOM_U1R_DIC;
unsigned int g_ddr_mr_rttnom1 = DIMM_MR1_RTTNOM_U1R_DIC;
unsigned int g_ddr_mr_rttwr = DIMM_MR2_RTTWR_U1R;
unsigned int g_ddr_mr_rttwr1 = DIMM_MR2_RTTWR_U1R;


#elif defined(APM_TIANOCORE)

#include "apm_ddr_sdram.h"
#include "ddr_lib.h"

#define EN_RDDESKEW 0
#define EN_RDLVL2ND 0
#define EN_WRDESKEW 1

#define debug1(fmt,args...) debug(fmt ,##args)

#else

#include <common.h>
#include <command.h>
#include <asm/io.h>
#include <asm/arch/apm_ddr_sdram.h>
#include "ddr_lib.h"

#define EN_RDDESKEW 0
#define EN_RDLVL2ND 0
#define EN_WRDESKEW 1

#define debug1(fmt,args...) debug(fmt ,##args)

#endif

#include "ddr_spd.h"
#include "ddr_mcu.h"

/* Fixed values used in timing calculation */
#define MCU_FIXTIME_TCCD_VAL    4
// NOTE: MUST +1 Mcu cycle: Phy Rank switch btwn fast to slow lane.
#define PHY_RANK_DIMM_DLY_VAL     2
#define PHY_FIXTIME_RTR_VAL     6+PHY_RANK_DIMM_DLY_VAL
#define PHY_FIXTIME_WTW_VAL     6+PHY_RANK_DIMM_DLY_VAL
#define PHY_FIXTIME_RTW_VAL     6+PHY_RANK_DIMM_DLY_VAL
#define PHY_FIXTIME_WTR_VAL     6+PHY_RANK_DIMM_DLY_VAL

int mcu_board_specific_settings(void *p)
{
	struct apm_mcu *mcu = (struct apm_mcu *)p;

	/* Enable only populated ck, cke, cs, odt signals (noise - power) */
	mcu->phy_params.cfg_cs_en = mcu->phy_tr_dly.rank_mask;
	switch (mcu->mcu_params.activeslots) {
	case 0x1:		// Max 2 needed for 1 dimm (incl quad rank)
		// Either slot 01 or 23 could be pop
		mcu->phy_params.cfg_ck_en = mcu->phy_tr_dly.rank_mask & 0xF;
		mcu->phy_params.cfg_odt_en = mcu->phy_tr_dly.rank_mask & 0xF;
		mcu->phy_params.cfg_cke_en = mcu->phy_params.cfg_odt_en;
		break;
	case 0x2:		// Max 4 needed for 2 dimms (incl quad rank)
		mcu->phy_params.cfg_ck_en = mcu->phy_tr_dly.rank_mask & 0xF;
		mcu->phy_params.cfg_odt_en = mcu->phy_tr_dly.rank_mask & 0xF;
		mcu->phy_params.cfg_cke_en = mcu->phy_params.cfg_odt_en;
		break;
	case 0x3:		// Max 4 ck needed for 3 dimms (incl quad rank) - split CK
		mcu->phy_params.cfg_ck_en = mcu->phy_tr_dly.rank_mask & 0xF;
		// Max 6 ck needed for 3 dimms (incl quad rank) - split CK
		mcu->phy_params.cfg_odt_en = mcu->phy_tr_dly.rank_mask & 0x3F;
		mcu->phy_params.cfg_cke_en = mcu->phy_params.cfg_odt_en;
		break;
	default:{
			mcu->phy_params.cfg_ck_en = 0xF;
			mcu->phy_params.cfg_odt_en = 0x3F;
			mcu->phy_params.cfg_cke_en = 0x3F;
		}
	}
	return 0;
}

int ddr_spd_init(void *p)
{
	unsigned int i, j, err;
	unsigned long long rank_size;
	unsigned int activeslots, common_dimm_type, component_width,
	    mcu_clk_min_ps;
	unsigned int rank_shift, total_n_ranks, total_n_slots_active;
	unsigned int pll_force, pll_forced_speed;
  unsigned int pll_force_div, pll_force_idiv, pll_force_fbdiv,
      pll_force_odiv;
	unsigned int enabled_rddeskew, enabled_rdlvl2nd, enabled_wrdeskew;
	unsigned int dis_rank = 0;
	struct apm_mcu *mcu = (struct apm_mcu *)p;

	if (!mcu->enabled)
		return 0;

	err = 0;
	activeslots = 0;
	common_dimm_type = 0;
	total_n_slots_active = 0;
	for (i = 0; i < CONFIG_SYS_DIMM_SLOTS_PER_CTLR; i++) {
		debug(" GetI2C SPD MCU[%d]-Slot[%d]\n", mcu->id, i);
		activeslots |= (get_spd(mcu, i) & 0x1) << i;
	}
	if (!activeslots) {
		mcu->enabled = 0;
		debug("MCU[%d] - No DIMMs detected, disabling MCU\n", mcu->id);
		return 0;
	}
	mcu->mcu_params.activeslots = activeslots;
	/* Calculate DIMM timing params based of SPD data */
	for (i = 0; i < CONFIG_SYS_DIMM_SLOTS_PER_CTLR; i++) {
		if (!((activeslots >> i) & 0x1)) {
			continue;
		}
		total_n_slots_active += 1;
		err += compute_dimm_parameters(mcu, i);
		/* check common dimm type */
		if (!common_dimm_type) {
			common_dimm_type = (mcu->spd_info[i].module_type) & 0xF;
		} else if (((mcu->spd_info[i - 1].module_type) & 0xF) !=
			   ((mcu->spd_info[i].module_type) & 0xF)) {
			common_dimm_type = 0xF;
		}
		/* Enable the Address Mirror if the DIMMs support */
		if (mcu->dimm_params[i].mirrored_dimm) {
			mcu->mcu_params.mirror_ctrl = DIMM_ADDR_MIRROR_CTRL;
			debug("MCU[%d]-Slot[%d] Address Mirrored DIMM\n",
			      mcu->id, i);
		} else {
			mcu->mcu_params.mirror_ctrl = 0x0;
		}

		rank_shift = 0;

		debug("\tdimm-%d org-ranks:%d\n", i,
		      mcu->dimm_params[i].n_ranks);
		for (j = 0; j < (mcu->dimm_params[i].n_ranks); j++) {
			if (j > 1)
				rank_shift = 2;
			mcu->phy_tr_dly.rank_mask |=
			    (0x1 << (j + i * 2 + rank_shift)) & ~(mcu->
			                      mcu_params.
			                      ranksdisable
			                      [i]);
			debug
			    ("\tAvailable-rank:%d [i=%x j=%x rank_shift=%x], rank-disable=%x\n",
			     (0x1 << (j + i * 2 + rank_shift)), i, j,
			     rank_shift, mcu->mcu_params.ranksdisable[i]);
			if (!
			    (~(mcu->mcu_params.ranksdisable[i]) &
			     (0x1 << (j + i * 2 + rank_shift)))) {
				dis_rank++;
				debug
				    ("MCU[%d] Dsiabling rank: #%d of slot:#%d\n",
				     mcu->id, j, i);
			}
		}
		mcu->dimm_params[i].n_ranks -= dis_rank;
		debug("\tdimm-%d new-ranks:%d\n", i,
		      mcu->dimm_params[i].n_ranks);
	}

	total_n_ranks = 0;
	for (j = 0; j < 8; j++) {
		if (((mcu->phy_tr_dly.rank_mask) >> j) & 0x1) {
			total_n_ranks++;
		}
	}
	debug("MCU[%d] Total-ranks: 0x%x [rank-mask=0x%x]\n", mcu->id,
	      total_n_ranks, mcu->phy_tr_dly.rank_mask);
	mcu->mcu_params.dimm_type = UNKNOWN;	//default
	if (err) {
		debug("Error from SPD [ERROR=%d]\n", err);
	}
	switch (common_dimm_type) {
	case 0x0:
	case 0xF:
		debug("Unsupported common DRAM type.... 0x%x\n",
		      common_dimm_type);
		mcu->mcu_params.dimm_type = UNKNOWN;	//Unknown 
		err |= 0x4;
		break;
	case 0x2:		/* UDIMM */
	case 0x6:		/* Mini-UDIMM */
		mcu->mcu_params.dimm_type = UDIMM;
		break;
	case 0x1:		/* RDIMM */
	case 0x5:		/* Mini-RDIMM */
		mcu->mcu_params.dimm_type = RDIMM;
		break;
	case 0x3:		/* SO-DIMM */
	case 0x4:		/* Micro-DIMM */
	case 0x8:		/* SO-DIMM */
		mcu->mcu_params.dimm_type = SODIMM;
		break;
	case 0xB:		/* LRDIMM */
		mcu->mcu_params.dimm_type = LRDIMM;
		break;
	default:
		mcu->mcu_params.dimm_type = UNKNOWN;
		break;
	}
	if (err) {
		debug("Error from DIMM-type [ERROR=%d]\n", err);
	}
	/* Software needs to do wr-cal for multi-slot configuration */
	if (total_n_slots_active > 1) {
		mcu->phy_tr_dly.sw_wrcal_rank_mask = mcu->phy_tr_dly.rank_mask;
		mcu->phy_tr_dly.phy_wrcal_rank_mask = 0;
	} else {
		mcu->phy_tr_dly.sw_wrcal_rank_mask = 0;
		mcu->phy_tr_dly.phy_wrcal_rank_mask = mcu->phy_tr_dly.rank_mask;
	}

	err += mcu_board_specific_settings(p);

	if ((mcu->id > 4) && (mcu->phy_tr_dly.rank_mask > 1)) {
		// Increase drive for Mcu1,2,3 if multi-rank
		mcu->phy_params.bit_dq_stren +=
		    (mcu->phy_params.bit_dq_stren < 7) ? 1 : 0;
		mcu->phy_params.bit_ad_stren +=
		    (mcu->phy_params.bit_ad_stren < 7) ? 3 : 0;
		mcu->phy_params.bit_cmd_stren +=
		    (mcu->phy_params.bit_cmd_stren < 7) ? 3 : 0;
		mcu->phy_params.bit_ctl_stren +=
		    (mcu->phy_params.bit_ctl_stren < 7) ? 3 : 0;
		mcu->phy_params.bit_clk_stren +=
		    (mcu->phy_params.bit_clk_stren < 7) ? 3 : 0;
		mcu->phy_params.bit_dq_slew = 1;
		mcu->phy_params.bit_ad_slew = 1;
		mcu->phy_params.bit_cmd_slew = 1;
		mcu->phy_params.bit_ctl_slew = 1;
		mcu->phy_params.bit_clk_slew = 1;

		mcu->phy_params.bit_odt_stren -=
		    (mcu->phy_params.bit_clk_stren > 1) ? 1 : 0;
		mcu->phy_params.zqcal_code = 0xBEF;
	}
#if APM_SIM
#else
	debug
	    ("MCU[%d] Setting wr-cal-rank-mask: 0x%x [SW:0x%x]\n",
	     mcu->id, mcu->phy_tr_dly.phy_wrcal_rank_mask,
	     mcu->phy_tr_dly.sw_wrcal_rank_mask);
#endif
	pll_forced_speed = mcu->mcu_params.speed_desired;
	pll_force = 0;
#ifdef APM_VBIOS
	pll_force = g_ddr_pll_force;
  pll_force_div = g_ddr_pll_div[0];
  pll_force_idiv = g_ddr_pll_div[1];
  pll_force_fbdiv = g_ddr_pll_div[2];
  pll_force_odiv = g_ddr_pll_div[3];
#else
#ifdef PLL_FORCE
	pll_force = 1;
	pll_forced_speed = PLL_FORCED_SPEED;
  pll_force_div = PLL_FORCED_DIV;
  pll_force_idiv = 0x3;
  pll_force_fbdiv = 0x7F;
  pll_force_odiv = 0x1;

#else
	pll_force = 0;
	pll_forced_speed = 0;
	pll_force_div = 0;
	pll_force_idiv = 0;
	pll_force_fbdiv = 0;
	pll_force_odiv = 0;
#endif
#endif
	if (pll_force)
		debug("Forcing PLL...\n");
	/* Calculate common max DIMM clock support */
	mcu->mcu_params.speed_supported = 3200;
	mcu_clk_min_ps = rdiv((2 * 1000000ULL), (mcu->mcu_params.speed_desired));

	for (i = 0; i < CONFIG_SYS_DIMM_SLOTS_PER_CTLR; i++) {
	    if (!((activeslots >> i) & 0x1)) {
	      continue;
	    }
	    mcu->mcu_params.speed_supported =
	        min(mcu->mcu_params.speed_supported,
	      rdiv((2 * 1000000ULL),
	           (mcu->dimm_params[i].tCKmin_X_ps)));
	    if (pll_force) {
	      mcu_clk_min_ps = rdiv((2 * 1000000ULL), (pll_forced_speed));  //pll_forced_speed;
	      mcu->dimm_params[i].tCKmin_X_ps =
	          rdiv((2 * 1000000ULL), (pll_forced_speed));
	    } else {
	      mcu_clk_min_ps =
	          max(mcu_clk_min_ps,
	        mcu->dimm_params[i].tCKmin_X_ps);
	      mcu->dimm_params[i].tCKmin_X_ps = mcu_clk_min_ps; //update with expected speed for calc
	    }
	  }

	if (!mcu_clk_min_ps) {
		debug("common max clock caluclaiton ERROR: tCKmin_X_ps=%dps\n",
		      mcu_clk_min_ps);
		return 4;
	}

	if (pll_force) {
		mcu->mcu_params.clk_mhz_max = pll_forced_speed / 2;	//PLL_FORCED_SPEED/2; // in rounded MHz
		mcu->mcu_params.speed = pll_forced_speed;	//PLL_FORCED_SPEED; 
	} else {
		mcu->mcu_params.clk_mhz_max = ((10000000ULL / mcu_clk_min_ps) + 5) / 10;	// in rounded MHz
		mcu->mcu_params.speed = min((2 * mcu->mcu_params.clk_mhz_max), mcu->mcu_params.speed_desired);	// in Mbps (speed_.... = 2*clk_mhz)
	}
	mcu->mcu_params.clk_mhz_pll = (mcu->mcu_params.speed / 2);	//in Hz
#if APM_SIM
#else
	debug
	    ("MCU[%d] Speed-desired: %dMbps   Speed-supported: %dMbps [%dMHz]\n",
	     mcu->id, mcu->mcu_params.speed_desired,
	     mcu->mcu_params.speed_supported,
	     (((mcu->mcu_params.speed_supported * 10) + 5) / 20));
	debug
	    ("MCU[%d] Target ClkFreq: %dMHz    DDR-PLL should be set to: %dMHz\n",
	     mcu->id, mcu->mcu_params.clk_mhz_max, mcu->mcu_params.clk_mhz_pll);
#endif
#ifdef APM_VBIOS
	enabled_rddeskew = g_ddr_en_rddeskew;
	enabled_rdlvl2nd = g_ddr_en_rdlvl2nd;
	enabled_wrdeskew = g_ddr_en_wrdeskew;
#else
	enabled_rddeskew = EN_RDDESKEW;
	enabled_rdlvl2nd = EN_RDLVL2ND;
	enabled_wrdeskew = EN_WRDESKEW;
#endif
	/* Enable rd-deskew only for first rank */
	mcu->phy_tr_dly.rddeskew_rank_mask = 0;
	if (enabled_rddeskew) {
		if (mcu->mcu_params.speed > 1700) {
			if (total_n_ranks > 1) {
				if ((mcu->phy_tr_dly.rank_mask) & 0x1) {
					mcu->phy_tr_dly.rddeskew_rank_mask = 1;
				}
			}
		}
#if APM_SIM
#else
		debug
		    ("MCU[%d] Setting rd deskew-rank-mask: 0x%x\n",
		     mcu->id, mcu->phy_tr_dly.rddeskew_rank_mask);
#endif
	}
	/* Enable 2nd level rd-leveling of non-first ranks */
	mcu->phy_tr_dly.rdlvl2nd_rank_mask = 0;
	if (enabled_rdlvl2nd) {
		if (total_n_ranks > 1) {
			// (i=1) Only 2nd+ ranks 2ndlvlRDleveling
			for (i = 1; i < MCU_SUPPORTED_RANKS; i++) {
				if ((mcu->phy_tr_dly.rank_mask >> i) & 0x1) {
					mcu->phy_tr_dly.rdlvl2nd_rank_mask |=
					    (0x1U << i);
				}
			}
		}
	}
//	mcu->phy_tr_dly.rdlvl2nd_rank_mask &=
//	    mcu->phy_tr_dly.rddeskew_rank_mask;

#if APM_SIM
#else
	debug
	    ("MCU[%d] Setting 2nd level rd level rank-mask: 0x%x\n",
	     mcu->id, mcu->phy_tr_dly.rdlvl2nd_rank_mask);
#endif
	/* Enable wr-deskew only for first rank */
	mcu->phy_tr_dly.wrdeskew_rank_mask = 0;
	if (enabled_wrdeskew) {
		if (mcu->mcu_params.speed > 1400) {
			if (total_n_ranks > 1) {
				if ((mcu->phy_tr_dly.rank_mask) & 0x1) {
					mcu->phy_tr_dly.wrdeskew_rank_mask = 1;
				}
			}
		}
#if APM_SIM
#else
		debug
		    ("MCU[%d] Setting wr deskew-rank-mask: 0x%x\n",
		     mcu->id, mcu->phy_tr_dly.wrdeskew_rank_mask);
#endif
	}
	if (pll_force_div) {
	    mcu->mcu_params.pllctl0_idiv = pll_force_idiv;
	    mcu->mcu_params.pllctl0_fbdiv = pll_force_fbdiv;
	    mcu->mcu_params.pllctl0_odiv = pll_force_odiv;
	  } else {
	    /* Set PLL config parameters */
	    mcu->mcu_params.pllctl0_idiv = 0x5;
	    switch (mcu->mcu_params.speed) {
	#if USE_KCTC_PLL_VALS
	    case 400:
	      mcu->mcu_params.pllctl0_fbdiv = 0x5F; //95;
	      mcu->mcu_params.pllctl0_odiv = 3;
	      break;
	    case 666:
	    case 667:
	      mcu->mcu_params.pllctl0_fbdiv = 0x78; //120;
	      mcu->mcu_params.pllctl0_odiv = 2;
	      break;
	    case 800:
	      mcu->mcu_params.pllctl0_fbdiv = 0x7F; // 127;   // KC value
	      mcu->mcu_params.pllctl0_odiv = 3;
	      mcu->mcu_params.pllctl0_idiv = 3;
	      break;
	    case 1066:
	    case 1067:
	      mcu->mcu_params.pllctl0_fbdiv = 0xA9; // 169;  // KC value
	      mcu->mcu_params.pllctl0_odiv = 1;
	      mcu->mcu_params.pllctl0_idiv = 7;
	      break;
	    case 1333:
	    case 1334:
	      mcu->mcu_params.pllctl0_fbdiv = 0xD4; // 212;   // KC value
	      mcu->mcu_params.pllctl0_odiv = 1;
	      mcu->mcu_params.pllctl0_idiv = 7;
	      break;
	    case 1550:
	      mcu->mcu_params.pllctl0_fbdiv = 0xBA;   //186;
	      mcu->mcu_params.pllctl0_odiv = 1;
	      break;
	    case 1600:
	      mcu->mcu_params.pllctl0_fbdiv = 0x7F; // 127;  // KC value
	      mcu->mcu_params.pllctl0_odiv = 1;
	      mcu->mcu_params.pllctl0_idiv = 3;
	      break;
	    case 1866:
	    case 1867:
	      mcu->mcu_params.pllctl0_fbdiv = 0x94; // 148;   // KC value
	      mcu->mcu_params.pllctl0_odiv = 0x0;
	      mcu->mcu_params.pllctl0_idiv = 7;
	      break;
	    case 2133:
	    case 2134:
	      mcu->mcu_params.pllctl0_fbdiv = 0x7F; //127;   // KC value
	      mcu->mcu_params.pllctl0_odiv = 0x0;
	      mcu->mcu_params.pllctl0_idiv = 5;
	      break;
	    default:  // 1600
	      mcu->mcu_params.pllctl0_fbdiv = 0x7F; //127;   // KC value
	      mcu->mcu_params.pllctl0_odiv = 1;
	      mcu->mcu_params.pllctl0_idiv = 3;
	      break;
	#else
	    case 400:
	      mcu->mcu_params.pllctl0_fbdiv = 0x5F; //95;
	      mcu->mcu_params.pllctl0_odiv = 3;
	      break;
	    case 666:
	    case 667:
	      mcu->mcu_params.pllctl0_fbdiv = 0x78; //120;
	      mcu->mcu_params.pllctl0_odiv = 2;
	      break;
	    case 800:
	      mcu->mcu_params.pllctl0_fbdiv = 0xC0; //144;
	      mcu->mcu_params.pllctl0_odiv = 3;
	      break;
	    case 1066:
	    case 1067:
	      mcu->mcu_params.pllctl0_fbdiv = 0x80; //128;
	      mcu->mcu_params.pllctl0_odiv = 1;
	      break;
	    case 1333:
	    case 1334:
	      mcu->mcu_params.pllctl0_fbdiv = 0xA0; //160;
	      mcu->mcu_params.pllctl0_odiv = 1;
	      break;
	    case 1600:
	//              mcu->mcu_params.pllctl0_fbdiv = 0xC0;   //192;      //803MHz
	//              mcu->mcu_params.pllctl0_odiv = 1;                   //800MHz
	      mcu->mcu_params.pllctl0_fbdiv = 0x7F; // 127;  // KC value -> 800MHz
	      mcu->mcu_params.pllctl0_odiv = 1; // KC value -> 800MHz
	      mcu->mcu_params.pllctl0_idiv = 3; // KC value -> 800MHz
	      break;
	    case 1866:
	    case 1867:
	      mcu->mcu_params.pllctl0_fbdiv = 0x70; //112;
	      mcu->mcu_params.pllctl0_odiv = 0x0;
	      break;
	    case 2133:
	    case 2134:
	      mcu->mcu_params.pllctl0_fbdiv = 0x80; //128;
	      mcu->mcu_params.pllctl0_odiv = 0x0;
	      break;
	    default:  //1600
	      mcu->mcu_params.pllctl0_fbdiv = 0xC0; //160;
	      mcu->mcu_params.pllctl0_odiv = 0x1;
	      break;
	#endif
	    }
	  }

	  if (mcu->mcu_params.speed > 2200) { // Not to be used
	    mcu->phy_params.en_phy_dll_cal = 1;
	    debug("MCU[%d] Enabling DLL cal\n", mcu->id);
	  } else {
	    mcu->phy_params.en_phy_dll_cal = 0;
	  }
	  if (mcu->mcu_params.speed < 1100)
	    mcu->phy_params.dll_cal_lo_freq = 1;
	  else
	    mcu->phy_params.dll_cal_lo_freq = 0;

	  /* Calculate MCU timing params common for all DIMMs */
	  err |= compute_timing_params(mcu);
	  /* Check ECC for the channel DIMMs */
	  if (mcu->timing_params.all_DIMMs_ECC_capable) {
	    mcu->phy_params.cfg_macro_en_val = KCPHY_CFG_MACRO_ENABLE_VAL;
	    if (mcu->mcu_params.ECCenable) {
	      debug("MCU[%d]: DIMM ECC capable - Enabling ECC\n",
	            mcu->id);
	      mcu->mcu_params.glb_err_ctrl |= 0x10080;
	    } else {
	      debug("MCU[%d]: DIMM ECC capable - Not Enabling ECC\n",
	            mcu->id);
	      mcu->mcu_params.glb_err_ctrl &= ~0x8F;
	      mcu->mcu_params.ECCenable = 0;
	    }
	  } else {
	    debug("MCU[%d}: DIMM ECC not supported\n", mcu->id);
	    mcu->mcu_params.glb_err_ctrl &= ~0x8F;
	    mcu->mcu_params.ECCenable = 0;
	    mcu->mcu_params.ECCscheme = 0;
	    mcu->phy_params.cfg_macro_en_val =
	        (KCPHY_CFG_MACRO_ENABLE_VAL & KCPHY_CFG_MACRO_NOECC_MASK);
	  }

	  component_width = 0;
	  rank_size = 0;
	  for (i = 0; i < CONFIG_SYS_DIMM_SLOTS_PER_CTLR; i++) {
	    if (!((activeslots >> i) & 0x1)) {
	      continue;
	    }
	    mcu->timing_params.ndimms_present++;
	    mcu->mcu_params.ranksperslot[i] = mcu->dimm_params[i].n_ranks;
	    if (!component_width) {
	      component_width = mcu->dimm_params[i].component_width;
	    } else if (component_width !=
	         mcu->dimm_params[i].component_width) {
	      err |= 0x8;
	      component_width = 0xF;
	    }
	    if (!rank_size) {
	      rank_size = mcu->dimm_params[i].rank_density;
	    } else if (rank_size > mcu->dimm_params[i].rank_density) {
	      rank_size = mcu->dimm_params[i].rank_density;
	    }
	#if APM_SIM
	#else
	    debug
	        ("MCU[%d]-Slot[%d]: n_ranks=%d rank-size=%dMB component-width=%d\n",
	         mcu->id, i, mcu->dimm_params[i].n_ranks,
	         (mcu->dimm_params[i].rank_density) / (1024 * 1024),
	         mcu->dimm_params[i].component_width);
	#endif
	    mcu->mcu_params.rca[i] = mcu->dimm_params[i].rca;
	    mcu->mcu_params.rcb[i] = mcu->dimm_params[i].rcb;
	  }
	  if (mcu->timing_params.all_DIMMs_registered) {
	    mcu->mcu_params.rc_en = 1;  //mcu->timing_params.all_DIMMs_registered;
	    debug("MCU[%d] Enabling RC programming for RDIMM\n", mcu->id);
	  }
	  if (component_width == 4) {
	    mcu->mcu_params.by4_mode = 1;
	    mcu->phy_params.cfg_macro_en_val &= KCPHY_CFG_MACRO_x4_MASK;
	  } else if (component_width == 8) {
	    mcu->mcu_params.by4_mode = 0;
	    mcu->phy_params.cfg_macro_en_val &= KCPHY_CFG_MACRO_x8_MASK;
	  } else {
	    err |= 0x10;
	    debug("  ERROR: Unsupported x4/x8 mode [bits/component = %d]\n",
	          component_width);
	  }
	  if (rank_size) {
	    mcu->mcu_params.minranksize = rank_size;
	  } else {
	    debug("  ERROR: Null common minimum rank size\n");
	    err |= 0x20;
	  }

	  if (mcu->timing_params.tCKmin_X_ps != mcu_clk_min_ps) {
	    debug
	        (" ERROR: MCU common max-clock caluclaiton  [tCKmin_X_ps=%dps timing-calc-tCKmin_X_ps%dps]\n",
	         mcu_clk_min_ps, mcu->timing_params.tCKmin_X_ps);
	    err |= 0x40;
	  }
	  return err;
	}


int mcu_timing_config(void *p)
{
	unsigned int i, temp;
	unsigned int mr0, mr1, mr2, mr3, ranks;
	unsigned int calc0, calc1, cycls;
	unsigned int cl, al, crl, cwl, blby2;
	unsigned int actpre1, rdpre, rdpre1, wrpre, wrrec, wrpre1, preact;
	unsigned int __attribute__ ((unused)) trfcmin;
	unsigned int tck_ps;
	struct apm_mcu *mcu = (struct apm_mcu *)p;
	unsigned int relax_time_en, relax_margin_0, relax_margin_1, margin;
	unsigned int relax_rd2rd_margin, relax_rd2wr_margin, relax_wr2wr_margin, relax_wr2rd_margin;
	unsigned int mr1_rttnom, mr2_rttwr;
	mcu_param_t *mp = &mcu->mcu_params;
	timing_params_t *tp = &mcu->timing_params;

	if (!(mcu->enabled)) {
		return 0;
	}

	/* Generate MCU CSR valis for timiing parameters */
	debug(" * Generate MCU CSR values for timiing parameters *\n");
	cl = tp->lowest_common_SPD_caslat;
	crl = tp->cas_read_latency;
	cwl = tp->cas_write_latency;
	mp->cl = cl;
	if (mcu->timing_params.all_DIMMs_registered) {
		mp->t_crl =
		    (mcu->phy_params.en_2T_adj_incr_latency) ? crl + 1 : crl;
		mp->t_cwl =
		    (mcu->phy_params.en_2T_adj_incr_latency) ? cwl + 1 : cwl;
	} else {
		mp->t_crl =
		    (mcu->phy_params.en_2T_adj_incr_latency) ? crl : crl - 1;
		mp->t_cwl =
		    (mcu->phy_params.en_2T_adj_incr_latency) ? cwl : cwl - 1;
	}
	if (mp->t_crl < MCU_T_CRL_MIN) {
		debug("ERROR *** t_crl=%d < %d not supported.\n", mp->t_crl,
		      MCU_T_CRL_MIN);
		return 1;
	}
	if (mp->t_cwl < MCU_T_CWL_MIN) {
		debug("ERROR *** t_cwl=%d < %d not supported.\n", mp->t_cwl,
		      MCU_T_CWL_MIN);
		return 1;
	}
	if (mp->t_crl > MCU_T_CRL_MAX) {
		debug("ERROR *** t_crl=%d > %d not supported.\n", mp->t_crl,
		      MCU_T_CRL_MAX);
		return 1;
	}
	if (mp->t_cwl > MCU_T_CWL_MAX) {
		debug("ERROR *** t_cwl=%d > %d not supported.\n", mp->t_cwl,
		      MCU_T_CWL_MAX);
		return 1;
	}

	mcu->phy_params.WL = (mcu->mcu_params.t_cwl) + 1;
	mcu->phy_params.RL = (mcu->mcu_params.t_crl) + 1;

	//------- Setting custom t-crl
	#ifdef APM_VBIOS
	  if (g_ddr_tcrl[mcu->id]) {
	    mp->t_crl += g_ddr_tcrl[mcu->id];
	    debug("\n\nMCU[%d] Setting Custom t_crl: %d\n\n", mcu->id,
	          mp->t_crl);
	  }
	  if (g_ddr_tcwl[mcu->id]) {
	    mp->t_cwl -= g_ddr_tcwl[mcu->id];
	    debug("\n\nMCU[%d] Setting Custom t_cwl: %d\n\n", mcu->id,
	          mp->t_cwl);
	  }
	#else

	if (KCPHY_ADD_T_CRL_MARGIN > 0) {
		mp->t_crl += KCPHY_ADD_T_CRL_MARGIN;	//1/2
		debug("\n\nMCU[%d] Setting Custom t_crl: %d\n\n", mcu->id,
		      mp->t_crl);
	}

  if (KCPHY_SUB_T_CWL_MARGIN > 0) {
    mp->t_cwl -= KCPHY_SUB_T_CWL_MARGIN;  //1/2
    debug("\n\nMCU[%d] Setting Custom t_cwl: %d\n\n", mcu->id,
          mp->t_cwl);
  }
#endif

	blby2 = (mp->burst_len) / 2;
	al = tp->additive_latency;
	tck_ps = tp->tCKmin_X_ps;

#ifdef APM_SIM
	relax_time_en = DDR_RELAX_EN;
	relax_margin_0 = DDR_RELAX_MARGIN_0;
	relax_margin_1 = DDR_RELAX_MARGIN_1;
	relax_rd2rd_margin = RD2RD_MARGIN;
	relax_rd2wr_margin = RD2WR_MARGIN;
	relax_wr2wr_margin = WR2WR_MARGIN;
	relax_wr2rd_margin = WR2RD_MARGIN;
#else
#ifdef APM_VBIOS
	relax_time_en = g_ddr_relax_en;
	relax_margin_0 = g_ddr_relax_margin_0;
	relax_margin_1 = g_ddr_relax_margin_1;
  relax_rd2rd_margin = g_ddr_rd2rdmargin[mcu->id];
  relax_rd2wr_margin = g_ddr_rd2wrmargin[mcu->id];
  relax_wr2wr_margin = g_ddr_wr2wrmargin[mcu->id];
  relax_wr2rd_margin = g_ddr_wr2rdmargin[mcu->id];
#else
	relax_time_en = 1;
	relax_margin_0 = (mp->tmargin >> 12) & 0xF;
	relax_margin_1 = (mp->tmargin >> 8) & 0xF;
	relax_rd2rd_margin = (mp->tmargin >> 4) & 0xF;
	relax_rd2wr_margin = (mp->tmargin >> 20) & 0xF;
	relax_wr2wr_margin = mp->tmargin & 0xF;
	relax_wr2rd_margin = (mp->tmargin >> 16) & 0xF;
	debug
	      ("Margin 0 is %x Margin 1 is %x RD2RD Margin %x RD2WR Margin %x WR2WR Margin %x WR2RD Margin %x\n",
	       relax_margin_0, relax_margin_1, relax_rd2rd_margin,
	       relax_rd2wr_margin, relax_wr2wr_margin, relax_wr2rd_margin);
#endif
#endif

	// Note: APM_SIM printf fails with 3+ args
	debug("\t[latency: cl=%d cwl=%d ", cl, cwl);
	debug("crl=%d bl=%d, ", crl, blby2 * 2);
	debug("al=%d, tck=%d]\n", al, tck_ps);
	if (relax_time_en)
		debug("\t[Timing relaxation by: %d, %d]\n\n", relax_margin_0,
		      relax_margin_1);

	/* BANK-ACTPRE: val = trasmin*mtb / tck_ps [csr = (val/2)-1] */
	calc0 = rdiv(tp->tRAS_ps, tck_ps);
	calc1 = calc0;
	actpre1 = calc1;
	cycls = max(2, rdiv(calc1, 2));
	margin = relax_time_en * (relax_margin_1 * 2);
	mp->bank_actpre = cycls + margin - 1;
#if APM_SIM
#else
	debug("\tMCU[%d] BANK-ACTPRE=0x%0X [%d->%d->%d(+%d)]\n", mcu->id,
	      mp->bank_actpre, calc0, calc1, cycls, margin);
#endif
	/* BANK-RDPRE: val = trtpmin*mtb / tck_ps + al [csr = (val/2)-1] */
	calc0 = max(4, rdiv(tp->tRTP_ps, tck_ps));
	rdpre = calc0;
	calc1 = calc0 + al;
	rdpre1 = calc1;
	cycls = max(2, rdiv(calc1, 2));
	margin = relax_time_en * (relax_margin_1);
	mp->bank_rdpre = cycls + margin - 1;
#if APM_SIM
#else
	debug("\tMCU[%d] BANK-RDPRE=0x%X [%d->%d->%d(+%d)]\n", mcu->id,
	      mp->bank_rdpre, calc0, calc1, cycls, margin);
#endif
	/* BANK-WRPRE: val = twrmin*mtb / tck_ps + al + cwl + blby2 [csr = (val/2)-1] */
	calc0 = rdiv(tp->tWR_ps, tck_ps);
	wrpre = calc0;
	calc1 = calc0 + al + cwl + blby2;
	wrpre1 = calc1;
	cycls = max(2, rdiv(calc1, 2));
	margin = relax_time_en * (relax_margin_1);
	mp->bank_wrpre = cycls + margin - 1;
#if APM_SIM
#else
	debug("\tMCU[%d] BANK-WRPRE=0x%X [%d->%d>%d(+%d)]\n", mcu->id,
	      mp->bank_wrpre, calc0, calc1, cycls, margin);
#endif
	/* BANK-PREACT: val = trpmin*mtb / tck_ps [csr = (val/2)-1] */
	calc0 = rdiv(tp->tRP_ps, tck_ps);
	preact = calc0;
	calc1 = calc0;
	cycls = max(2, rdiv(calc1, 2));
	margin = relax_time_en * (relax_margin_0);
	mp->bank_preact = cycls - 1 + margin;
#if APM_SIM
#else
	debug("\tMCU[%d] BANK-PREACT=0x%X [%d->%d->%d(+%d)]\n", mcu->id,
	      mp->bank_preact, calc0, calc1, cycls, margin);
#endif
	/* BANK-ACTACT: val = trcmin*mtb / tck_ps [csr = (val/2)-1] */
	calc0 = rdiv(tp->tRC_ps, tck_ps);
	calc1 = calc0;
	cycls = max(2, rdiv(calc1, 2));
	margin = relax_time_en * (relax_margin_0 + relax_margin_1 * 2);
	mp->bank_actact = cycls - 1 + margin;
#if APM_SIM
#else
	debug("\tMCU[%d] BANK-ACTACT=0x%X [%d->%d->%d(+%d)]\n", mcu->id,
	      mp->bank_actact, calc0, calc1, cycls, margin);
#endif
	/* BANK-RDAACT: val = rdpre+preact + al [csr = (val/2)-1] */
	calc0 = rdpre + preact;
	calc1 = calc0 + al;
	cycls = max(2, rdiv(calc1, 2));
	margin = relax_time_en * (relax_margin_0 + relax_margin_1);
	mp->bank_rdaact = cycls - 1 + margin;
#if APM_SIM
#else
	debug("\tMCU[%d] BANK-RDAACT=0x%X [%d->%d->%d(+%d)]\n", mcu->id,
	      mp->bank_rdaact, calc0, calc1, cycls, margin);
#endif
	/* BANK-WRAACT: val = wrpre+preact + al + cwl + blby2 [csr = (val/2)-1] */
	calc0 = wrpre + preact;
	calc1 = calc0 + al + cwl + blby2;
	cycls = max(2, rdiv(calc1, 2));
	margin = relax_time_en * (relax_margin_0 + relax_margin_1);
	mp->bank_wraact = cycls - 1 + margin;
#if APM_SIM
#else
	debug("\tMCU[%d] BANK-WRAACT=0x%X [%d->%d->%d(+%d)]\n", mcu->id,
	      mp->bank_wraact, calc0, calc1, cycls, margin);
#endif
	/* BANK-ACTRD: val = trcdmin*mtb / tck_ps [csr = (val/2)-1] */
	calc0 = rdiv(tp->tRCD_ps, tck_ps);
	calc1 = calc0;
	cycls = max(2, rdiv(calc1, 2));
	margin = relax_time_en * (relax_margin_1);
	mp->bank_actrd = cycls + margin - 1;
#if APM_SIM
#else
	debug("\tMCU[%d] BANK-ACTRD=0x%X [%d->%d->%d(+%d)]\n", mcu->id,
	      mp->bank_actrd, calc0, calc1, cycls, margin);
#endif
	/* BANK-ACTWR: val = trcdmin*mtb / tck_ps [csr = (val/2)-1] */
	calc0 = rdiv(tp->tRCD_ps, tck_ps);
	calc1 = calc0;
	cycls = max(2, rdiv(calc1, 2));
	margin = relax_time_en * (relax_margin_1);
	mp->bank_actwr = cycls + margin - 1;
#if APM_SIM
#else
	debug("\tMCU[%d] BANK-ACTWR=0x%X [%d->%d->%d(+%d)]\n", mcu->id,
	      mp->bank_actwr, calc0, calc1, cycls, margin);
#endif
	/* BANK-ACTRDA: val = actpre1 - rdpre1 [csr = (val/2)-1] */
	calc0 = actpre1 < rdpre1 ? 0 : (actpre1 - rdpre1);
	calc1 = calc0;
	cycls = max(2, rdiv(calc1, 2));
	margin = relax_time_en * (relax_margin_1);
	mp->bank_actrda = cycls - 1 + margin;
#if APM_SIM
#else
	debug("\tMCU[%d] BANK-ACTRDA=0x%X [%d->%d->%d(+%d)]\n", mcu->id,
	      mp->bank_actrda, calc0, calc1, cycls, margin);
#endif
	/* BANK-ACTWRA: val = actpre1 - wrpre1  [csr = (val/2)-1] */
	calc0 = actpre1 < wrpre1 ? 0 : (actpre1 - wrpre1);
	calc1 = calc0;
	cycls = max(2, rdiv(calc1, 2));
	margin = relax_time_en * (relax_margin_1);
	mp->bank_actwra = cycls - 1 + margin;
#if APM_SIM
#else
	debug("\tMCU[%d] BANK-ACTWRA=0x%X [%d->%d->%d(+%d)]\n", mcu->id,
	      mp->bank_actwra, calc0, calc1, cycls, margin);
#endif
	/* RANK-ACTACT: val = trrdmin*mtb / tck_ps  [csr = (val/2)-1] */
	calc0 = rdiv(tp->tRRD_ps, tck_ps);
	calc1 = max(4, calc0);
	cycls = max(2, rdiv(calc1, 2));
	margin = relax_time_en * (relax_margin_0);
	mp->rank_actact = cycls - 1 + margin;
#if APM_SIM
#else
	debug("\tMCU[%d] RANK-ACTACT=0x%X [%d->%d->%d(+%d)]\n", mcu->id,
	      mp->rank_actact, calc0, calc1, cycls, margin);
#endif
	/* RANK-RDRD: val = (tCCD = 4)  [csr = (val/2)-1] */
	calc0 = MCU_FIXTIME_TCCD_VAL;
	calc1 = calc0;
	cycls = max(2, rdiv(calc1, 2));
	margin = relax_rd2rd_margin;
	mp->rank_rdrd = cycls - 1 + margin;
#if APM_SIM
#else
	debug("\tMCU[%d] RANK-RDRD=0x%X [%d->%d->%d(+%d)]\n", mcu->id,
	      mp->rank_rdrd, calc0, calc1, cycls, margin);
#endif
	/* RANK-WRWR: val = (tCCD = 4)  [csr = (val/2)-1] */
	calc0 = MCU_FIXTIME_TCCD_VAL;
	calc1 = calc0;
	cycls = max(2, rdiv(calc1, 2));
	margin = relax_wr2wr_margin;
	mp->rank_wrwr = cycls - 1 + margin;
#if APM_SIM
#else
	debug("\tMCU[%d] RANK-WRWR=0x%X [%d->%d->%d(+%d)]\n", mcu->id,
	      mp->rank_wrwr, calc0, calc1, cycls, margin);
#endif
	/* RANK-RDWR: val = (tCCD = 4) + cl + 2 - cwl  [csr = (val/2)-1] */
	calc0 = MCU_FIXTIME_TCCD_VAL;
	calc1 = calc0 + cl + 2 - cwl;
	cycls = max(2, rdiv(calc1, 2));
	margin = relax_rd2wr_margin;
	mp->rank_rdwr = cycls - 1 + margin;
#if APM_SIM
#else
	debug("\tMCU[%d] RANK-RDWR=0x%X [%d->%d->%d(+%d)]\n", mcu->id,
	      mp->rank_rdwr, calc0, calc1, cycls, margin);
#endif
	/* RANK-WRRD: val = twtrmin*mtb / tck_ps + cwl + blby2  [csr = (val/2)-1] */
	calc0 = rdiv(tp->tWTR_ps, tck_ps);
	calc1 = max(4, calc0) + cwl + blby2;	// + 1 Phy delay min lane to max
	cycls = max(2, rdiv(calc1, 2));
	margin = relax_wr2rd_margin;
	mp->rank_wrrd = cycls - 1 + margin;
#if APM_SIM
#else
	debug("\tMCU[%d] RANK-WRRD=0x%X [%d->%d->%d(+%d)]\n", mcu->id,
	      mp->rank_wrrd, calc0, calc1, cycls, margin);
#endif
	/* RANK-ACTFAW: val = tfawmin*mtb / tck_ps  [csr = (val/2)-1] */
	calc0 = rdiv(tp->tFAW_ps, tck_ps);
	calc1 = calc0;
	cycls = max(2, rdiv(calc1, 2));
	margin = 2 + relax_time_en * (relax_margin_0 * 4);
	mp->rank_actfaw = cycls - 1 + margin;
#if APM_SIM
#else
	debug("\tMCU[%d] RANK-ACTFAW=0x%X [%d->%d->%d(+%d)]\n", mcu->id,
	      mp->rank_actfaw, calc0, calc1, cycls, margin);
#endif
	/* SYS-RDRD: val = phy_rtr + blby2  [csr = (val/2)-1] */
	calc0 = PHY_FIXTIME_RTR_VAL;
	calc1 = calc0 + blby2;
	cycls = max(2, rdiv(calc1, 2));
	margin = 0;	
	mp->sys_rdrd = cycls - 1 + margin;
#if APM_SIM
#else
	debug("\tMCU[%d] SYS-RDRD=0x%X [%d->%d->%d(+%d)]\n", mcu->id,
	      mp->sys_rdrd, calc0, calc1, cycls, margin);
#endif
	/* SYS-WRWR: val = phy_wtw + blby2  [csr = (val/2)-1] */
	calc0 = PHY_FIXTIME_WTW_VAL;
	calc1 = calc0 + blby2;
	cycls = max(2, rdiv(calc1, 2));
	margin = 0;	
	mp->sys_wrwr = cycls - 1 + margin;
#if APM_SIM
#else
	debug("\tMCU[%d] SYS-WRWR=0x%X [%d->%d->%d(+%d)]\n", mcu->id,
	      mp->sys_wrwr, calc0, calc1, cycls, margin);
#endif
	/* SYS-RDWR: val = phy_rtw + cl + blby2 - cwl  [csr = (val/2)-1] */
	calc0 = PHY_FIXTIME_RTW_VAL;
	calc1 = calc0 + cl + blby2 - cwl;
	cycls = max(2, rdiv(calc1, 2));
	margin = 0;		
	mp->sys_rdwr = cycls - 1 + margin;
#if APM_SIM
#else
	debug("\tMCU[%d] SYS-RDWR=0x%X [%d->%d->%d(+%d)]\n", mcu->id,
	      mp->sys_rdwr, calc0, calc1, cycls, margin);
#endif
	/* SYS-WRRD: val = phy_wtr + cwl + blby2 - cl  [csr = (val/2)-1] */
	calc0 = PHY_FIXTIME_WTR_VAL;
	calc1 = calc0 + cwl + blby2 - cl;
	cycls = max(2, rdiv(calc1, 2));
	margin = 0;		
	mp->sys_wrrd = cycls - 1 + margin;
#if APM_SIM
#else
	debug("\tMCU[%d] SYS-WRRD=0x%X [%d->%d->%d(+%d)]\n", mcu->id,
	      mp->sys_wrrd, calc0, calc1, cycls, margin);
#endif
	/* RANK-REFACTREF: val = trfcmin*mtb / tck_ps  [csr = (val/2)-1] */
	calc0 = rdiv(tp->tRFC_ps, tck_ps);
	trfcmin = calc0;
	calc1 = calc0;
	cycls = max(2, rdiv(calc1, 2));
	margin = 0;		// + relax_time_en*(relax_margin+1);
	mp->rank_refactref = cycls - 1 + margin;
#if APM_SIM
#else
	debug("\tMCU[%d] SYS-REFACTREF=0x%X [%d->%d->%d(+%d)]\n", mcu->id,
	      mp->rank_refactref, calc0, calc1, cycls, margin);
#endif
	/* REFINT: val = refrrate*8*mtb / tck_ps  [csr = (val/2)-1] */
	calc0 = rdiv(tp->refresh_rate_ps, tck_ps);
	calc1 = calc0;
	cycls = max(2, rdiv(calc1, 2));
	margin = 0;		// + relax_time_en*(relax_margin+1);
	mp->rank_refint = cycls - 1 + margin;
#if APM_SIM
#else
	debug("\tMCU[%d] REFINT=0x%X [%d->%d->%d(+%d)]\n", mcu->id,
	      mp->rank_refint, calc0, calc1, cycls, margin);
#endif
	/* REF-BURST-CNT: val = refint*4  [csr = (val/2)-1] */
	mp->rank_ref_burst_cnt = 4;
	debug("\tMCU[%d] REF-BURST-CNT=0x%X \n", mcu->id,
	      mp->rank_ref_burst_cnt);

	debug("\n");
	/* Mode Register Programming */
	ranks = 1;
	for (i = 0; i < CONFIG_SYS_DIMM_SLOTS_PER_CTLR; i++) {
		if (!((mp->activeslots >> i) & 0x1)) {
			continue;
		}
		if (mcu->dimm_params[i].n_ranks > 1)
			ranks++;
	}
	switch (wrpre) {
	case 5:
		wrrec = 0x1;
		break;
	case 6:
		wrrec = 0x2;
		break;
	case 7:
		wrrec = 0x3;
		break;
	case 8:
		wrrec = 0x4;
		break;
	case 9:
	case 10:
		wrrec = 0x5;
		break;
	case 11:
	case 12:
		wrrec = 0x6;
		break;
	case 13:
	case 14:
		wrrec = 0x7;
		break;
	default:
		wrrec = 0;
		break;
	}
	if (cl >= 12) {
		mr0 =
		    0x100 | ((wrrec & 0x7) << 9) | (0x70 & (0x10 * (cl - 12))) |
		    0x4;
	} else {
		mr0 = 0x100 | ((wrrec & 0x7) << 9) | (0x70 & ((cl - 4) << 4));
	}
	mp->mode_reg[0] = mr0;
#if APM_SIM
#else
	debug("\tMCU[%d] MR0: 0x%04X [wrore:%d, wrrecovery:%d]\n", mcu->id, mr0, wrpre, wrrec);	//0x550
#endif
#ifdef APM_VBIOS
	if (g_ddr_mr_valid) {
		if ((mcu->id == 0) || (mcu->id == 2)) {
			mr1_rttnom = g_ddr_mr_rttnom;
		} else {
			mr1_rttnom = g_ddr_mr_rttnom1;
		}
	} else {
		if (ranks == 1) {
			mr1_rttnom = DIMM_MR1_RTTNOM_U1R_DIC;
		} else {
			mr1_rttnom = DIMM_MR1_RTTNOM_U2R_DIC;
		}
		debug1("*** Using default RTTNOM: 0x%x ***\n", mr1_rttnom);
		g_ddr_mr_rttnom = mr1_rttnom;
		g_ddr_mr_rttnom1 = mr1_rttnom;
	}
#else
	if (ranks == 1) {
		mr1_rttnom = DIMM_MR1_RTTNOM_U1R_DIC;
	} else {
		mr1_rttnom = DIMM_MR1_RTTNOM_U2R_DIC;
	}
#endif
	mr1 = mr1_rttnom;
	if (al == (cl - 2))
		mr1 |= (2 << 3);	//0x54
	else if (al == (cl - 1))
		mr1 |= (1 << 3);	//0x4C
	mp->mode_reg[1] = mr1;
	debug("\tMCU[%d] MR1: 0x%04X\n", mcu->id, mr1);	//0x44

	mr2 = (cwl - 5) << 3;
#ifdef APM_VBIOS
	if (g_ddr_mr_valid) {
		if ((mcu->id == 0) || (mcu->id == 2)) {
			mr2_rttwr = g_ddr_mr_rttwr;
		} else {
			mr2_rttwr = g_ddr_mr_rttwr1;
		}
	} else {
		if (ranks == 1) {
			mr2_rttwr = DIMM_MR2_RTTWR_U1R;
		} else {
			mr2_rttwr = DIMM_MR2_RTTWR_U2R;
		}
		debug1("*** Using default RTTWR: 0x%x ***\n", mr2_rttwr);
		g_ddr_mr_rttwr = mr2_rttwr;
		g_ddr_mr_rttwr1 = mr2_rttwr;
	}
#else
	if (ranks == 1)
		mr2_rttwr = DIMM_MR2_RTTWR_U1R;
	else
		mr2_rttwr = DIMM_MR2_RTTWR_U2R;
#endif
	if ((mp->activeslots) > 1)
		mr2 |= 0x200;
	else if (mr2_rttwr)
		mr2 |= (mr2_rttwr & 0x3) << 9;

	mp->mode_reg[2] = mr2;
	debug("\tMCU[%d] MR2: 0x%04X\n", mcu->id, mr2);

	mr3 = 0x0;
	mp->mode_reg[3] = mr3;
	debug("\tMCU[%d] MR3: 0x%04X\n", mcu->id, mr3);

	// Wr Lvl RttNom setting (/2 /4 /6 only!!)
	temp = getRttNomfromMR1(mp->mode_reg[1]);
	switch (temp) {
	case 1:
		mcu->mcu_params.rttnom_wrlvl = temp;
		break;
	case 2:
		mcu->mcu_params.rttnom_wrlvl = temp;
		break;
	case 3:
		mcu->mcu_params.rttnom_wrlvl = temp;
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
	// TBD- Quad Rank disable rank 1,3 or rank 2,3 RttNom (depends on dimm)
	mcu->mcu_params.rank_mask_disable_rttnom = 0;

	/* clk200us calc */
	debug("\n");
	mp->clks200us = rdiv((200 + 4) * 1000000U / 2, (tck_ps));
	debug("\tMCU[%d] clks200us: 0x%06X\n", mcu->id, mp->clks200us);
	mp->clks500us = rdiv((500 + 10) * 1000000U / 2, (tck_ps));
	debug("\tMCU[%d] clks500us: 0x%06X\n", mcu->id, mp->clks500us);
	mp->clks6us = rdiv((((6) * 1000000U / 2) + 200000U), (tck_ps));
	debug("\tMCU[%d] clks6us: 0x%06X\n", mcu->id, mp->clks6us);
	mp->clkstxpr = 0x1FF;
#if APM_SIM
#else
	debug("\tMCU[%d] clkstxpr: 0x%06X [trfcmin:%d]\n", mcu->id,
	      mp->clkstxpr, trfcmin);
#endif
	return 0;
}

unsigned int getRttNomfromMR1(unsigned int mr1val)
{
	unsigned int bout = 0;
	bout = ((mr1val >> 7) & 0x4) |	/*A9 */
	    ((mr1val >> 5) & 0x2) |	/*A6 */
	    ((mr1val >> 2) & 0x1);	/*A2 */
	return bout;
}

unsigned int putRttNomintoMR1(unsigned int mr1val, unsigned int rttnom)
{
	unsigned int bout = 0;
	bout = (mr1val & 0xFDBB) | ((rttnom & 0x4) << 7) |	/*A9 */
	    ((rttnom & 0x2) << 5) |	/*A6 */
	    ((rttnom & 0x1) << 2);	/*A2 */
	return bout;
}

