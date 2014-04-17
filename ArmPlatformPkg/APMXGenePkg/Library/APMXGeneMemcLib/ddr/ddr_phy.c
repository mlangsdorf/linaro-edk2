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
#define debug1(fmt,args...) debug(fmt ,##args)
#elif defined(APM_VBIOS)
#include <common.h>
#include <stdio.h>
#include <apm_ddr_sdram.h>
#define debug(fmt,args...)     lprintf(8, fmt ,##args)
#define debug1(fmt,args...)    lprintf(5, fmt ,##args)
#elif defined(APM_TIANOCORE)
#include "apm_ddr_sdram.h"
#define debug1(fmt,args...) debug(fmt ,##args)
#else
#include <common.h>
#include <command.h>
#include <asm/io.h>
#include <asm/arch/apm_ddr_sdram.h>
#include "config.h"
#define debug1(fmt,args...) debug(fmt ,##args)
#endif

#include "ddr_mcu.h"
#include "ddr_lib.h"
#include "kc_phy_util_reg_flds.h"

/******************************************************************************
 *     PHY Tr Delay Csr accesses
 *****************************************************************************/

void phy_restore_train_dly_csrs(void *p, int unsigned rankmask,
        int unsigned setWr,
        int unsigned setGt, int unsigned setRd)
{
  int iia, jjb;
  struct apm_mcu *mcu = (struct apm_mcu *)p;
  int unsigned by4 = mcu->mcu_params.by4_mode;
  for (iia = 0; iia < MCU_SUPPORTED_RANKS; iia++) {
    if ((rankmask >> iia) & 0x1) {
      for (jjb = 0; jjb < PHY_SUPPORTED_LANES; jjb++) {
        if (setWr) {
          phy_write_reg(mcu,
                  (PHY_CFG_REG_WRLVL_DELAY0_0
                   +
                   iia *
                   PHY_REG_INCR_4_RANK_OFFSET
                   +
                   jjb *
                   PHY_REG_INCR_4_MACRO_OFFSET),
                  mcu->phy_tr_dly.
                  rank_dly[iia].wr_lvl[jjb *
                     2]);
          if (by4) {
            phy_write_reg(mcu,
                    (PHY_CFG_REG_WRLVL_DELAY0_0_1
                     +
                     iia *
                     PHY_REG_INCR_4_RANK_OFFSET
                     +
                     jjb *
                     PHY_REG_INCR_4_MACRO_OFFSET),
                    mcu->phy_tr_dly.
                    rank_dly[iia].
                    wr_lvl[jjb * 2 +
                     1]);
          }
        }
        if (setGt) {
          phy_write_reg(mcu,
                  (PHY_CFG_REG_RDLVL_GATE_DELAY0_0
                   +
                   iia *
                   PHY_REG_INCR_4_RANK_OFFSET
                   +
                   jjb *
                   PHY_REG_INCR_4_MACRO_OFFSET),
                  mcu->phy_tr_dly.
                  rank_dly[iia].gt_lvl[jjb *
                     2]);
          if (by4) {
            phy_write_reg(mcu,
                    (PHY_CFG_REG_RDLVL_GATE_DELAY0_0_1
                     +
                     iia *
                     PHY_REG_INCR_4_RANK_OFFSET
                     +
                     jjb *
                     PHY_REG_INCR_4_MACRO_OFFSET),
                    mcu->phy_tr_dly.
                    rank_dly[iia].
                    gt_lvl[jjb * 2 +
                     1]);
          }
        }
        if (setRd) {
          phy_write_reg(mcu,
                  (PHY_CFG_REG_RDLVL_DELAY0_0
                   +
                   iia *
                   PHY_REG_INCR_4_RANK_OFFSET
                   +
                   jjb *
                   PHY_REG_INCR_4_MACRO_OFFSET),
                  mcu->phy_tr_dly.
                  rank_dly[iia].rd_lvl[jjb *
                     2]);
          if (by4) {
            phy_write_reg(mcu,
                    (PHY_CFG_REG_RDLVL_DELAY0_0_1
                     +
                     iia *
                     PHY_REG_INCR_4_RANK_OFFSET
                     +
                     jjb *
                     PHY_REG_INCR_4_MACRO_OFFSET),
                    mcu->phy_tr_dly.
                    rank_dly[iia].
                    rd_lvl[jjb * 2 +
                     1]);
          }
        }
      }
    }
  }

  /*
   * Must reset statemachine to take in new changes
   */
  mcu_reset_FSM_poll(mcu, MCU_RESET_FSM_stRESTART, POLL_EQUAL);
  mcu_set_SWISS_TRNLOAD(mcu);
  mcu_reset_FSM_poll(mcu, MCU_RESET_FSM_stRESTART, POLL_EQUAL);
}       // phy_restore_train_dly_csrs

//======================================================================

void phy_save_train_dly_csrs(void *p)
{
  int iia, jjb;
  struct apm_mcu *mcu = (struct apm_mcu *)p;
  int unsigned by4 = mcu->mcu_params.by4_mode;
  for (iia = 0; iia < MCU_SUPPORTED_RANKS; iia++) {
    if ((mcu->phy_tr_dly.rank_mask >> iia) & 0x1) {
      for (jjb = 0; jjb < PHY_SUPPORTED_LANES; jjb++) {
        mcu->phy_tr_dly.rank_dly[iia].wr_lvl[jjb * 2] =
            phy_read_reg(mcu,
             (PHY_CFG_REG_WRLVL_DELAY0_0 +
              iia *
              PHY_REG_INCR_4_RANK_OFFSET +
              jjb *
              PHY_REG_INCR_4_MACRO_OFFSET));
        if (by4) {
          mcu->phy_tr_dly.rank_dly[iia].
              wr_lvl[jjb * 2 + 1] =
              phy_read_reg(mcu,
               (PHY_CFG_REG_WRLVL_DELAY0_0_1
                +
                iia *
                PHY_REG_INCR_4_RANK_OFFSET
                +
                jjb *
                PHY_REG_INCR_4_MACRO_OFFSET));
        }
        mcu->phy_tr_dly.rank_dly[iia].gt_lvl[jjb * 2] =
            phy_read_reg(mcu,
             (PHY_CFG_REG_RDLVL_GATE_DELAY0_0
              +
              iia *
              PHY_REG_INCR_4_RANK_OFFSET +
              jjb *
              PHY_REG_INCR_4_MACRO_OFFSET));
        if (by4) {
          mcu->phy_tr_dly.rank_dly[iia].
              gt_lvl[jjb * 2 + 1] =
              phy_read_reg(mcu,
               (PHY_CFG_REG_RDLVL_GATE_DELAY0_0_1
                +
                iia *
                PHY_REG_INCR_4_RANK_OFFSET
                +
                jjb *
                PHY_REG_INCR_4_MACRO_OFFSET));
        }
        mcu->phy_tr_dly.rank_dly[iia].rd_lvl[jjb * 2] =
            phy_read_reg(mcu,
             (PHY_CFG_REG_RDLVL_DELAY0_0 +
              iia *
              PHY_REG_INCR_4_RANK_OFFSET +
              jjb *
              PHY_REG_INCR_4_MACRO_OFFSET));
        if (by4) {
          mcu->phy_tr_dly.rank_dly[iia].
              rd_lvl[jjb * 2 + 1] =
              phy_read_reg(mcu,
               (PHY_CFG_REG_RDLVL_DELAY0_0_1
                +
                iia *
                PHY_REG_INCR_4_RANK_OFFSET
                +
                jjb *
                PHY_REG_INCR_4_MACRO_OFFSET));
        }
      }
    }
  }
}       // phy_save_train_dly_csrs

//======================================================================

void phy_display_post_train_csrs(void *p, unsigned int rankmask)
{
  int iia, jjb, kkc;
  struct apm_mcu *mcu = (struct apm_mcu *)p;
  int unsigned
      __attribute__ ((unused)) cfg_analog2, cfg_analog3, picode, cdrlock,
      commandcode, rttnom, dic, rttwr, trnerr, terrmacro;
  int unsigned __attribute__ ((unused)) zqcode, cfg_dly_from_rden;

  cfg_analog2 = mcu->phy_rd(mcu, PHY_REG_CFG_ANALOG_CONFIG_2);
  cfg_analog3 = mcu->phy_rd(mcu, PHY_REG_CFG_ANALOG_CONFIG_3);
  picode = mcu->phy_rd(mcu, PHY_REG_CFG_PI_CODE);
  cdrlock = mcu->phy_rd(mcu, PHY_REG_CFG_CDR_LOCK);
  commandcode = mcu->phy_rd(mcu, PHY_REG_CFG_CMD_CODE);
  zqcode = mcu->phy_rd(mcu, PHY_REG_CFG_ZQ_CAL_CODE);

  cfg_dly_from_rden = phy_read_reg(mcu, PHY_REG_CFG_DELAY_FROM_RD_EN);

  trnerr = mcu->phy_rd(mcu, KC_PHY_REG36);
  terrmacro = mcu->phy_rd(mcu, KC_PHY_REG49);
  // Start Display

  // WrLvl
  debug1("\n\nWrLvl \t");
  for (iia = 0; iia < MCU_SUPPORTED_RANKS; iia++) {
    if ((rankmask >> iia) & 0x1) {
      debug1("\tR%01d", iia);
    }
  }
  debug1("\n");
  for (jjb = 0; jjb < PHY_SUPPORTED_LANES * 2; jjb++) {
    if (!((mcu->phy_params.cfg_macro_en_val >> jjb) & 0x1))
      continue;
    if ((jjb % 2) == 0)
      debug1("Ln %2d   ", jjb / 2);
    else
      debug1("Ln %2d x4", jjb / 2);
    for (iia = 0; iia < MCU_SUPPORTED_RANKS; iia++) {
      if ((rankmask >> iia) & 0x1) {
        debug1("\t0x%03X",
               mcu->phy_tr_dly.rank_dly[iia].
               wr_lvl[jjb]);
      }
    }
    if (jjb > 15) {
      debug1(" ecc");
    }
    debug1("\n");
  }
  debug1("\n");

  // GtLvl
  debug1("GtLvl \t");
  for (iia = 0; iia < MCU_SUPPORTED_RANKS; iia++) {
    if ((rankmask >> iia) & 0x1) {
      debug1("\tR%01d", iia);
    }
  }
  debug1("\n");
  for (jjb = 0; jjb < PHY_SUPPORTED_LANES * 2; jjb++) {
    if (!((mcu->phy_params.cfg_macro_en_val >> jjb) & 0x1))
      continue;
    if ((jjb % 2) == 0)
      debug1("Ln %2d   ", jjb / 2);
    else
      debug1("Ln %2d x4", jjb);
    for (iia = 0; iia < MCU_SUPPORTED_RANKS; iia++) {
      if ((rankmask >> iia) & 0x1) {
        debug1("\t0x%03X",
               mcu->phy_tr_dly.rank_dly[iia].
               gt_lvl[jjb]);
      }
    }
    if (jjb > 15) {
      debug1(" ecc");
    }
    debug1("\n");
  }
  debug1("\n");

  // RdLvl
  debug1("RdLvl \t");
  for (iia = 0; iia < MCU_SUPPORTED_RANKS; iia++) {
    if ((rankmask >> iia) & 0x1) {
      debug1("\tR%01d", iia);
    }
  }
  debug1("\n");
  for (jjb = 0; jjb < PHY_SUPPORTED_LANES * 2; jjb++) {
    if (!((mcu->phy_params.cfg_macro_en_val >> jjb) & 0x1))
      continue;
    if ((jjb % 2) == 0)
      debug1("Ln %2d   ", jjb / 2);
    else
      debug1("Ln %2d x4", jjb / 2);
    for (iia = 0; iia < MCU_SUPPORTED_RANKS; iia++) {
      if ((rankmask >> iia) & 0x1) {
        debug1("\t0x%03X",
               mcu->phy_tr_dly.rank_dly[iia].
               rd_lvl[jjb]);
      }
    }
    if (jjb > 15) {
      debug1(" ecc");
    }
    debug1("\n");
  }
  debug1("\n");

  // Rd-Deskew-Trim
  debug1("RdDsk-Trim ");
  iia = 0;    // Supported only for rank-0
  if ((mcu->phy_tr_dly.rddeskew_rank_mask >> iia) & 0x1) {
    debug1("\t\tR%01d", iia);
    debug1("\n");
    debug1("Bit\t\t\t0 1 2 3 4 5 6 7 \n");
    debug1("   \t\t\t| | | | | | | | \n");
    for (jjb = 0; jjb < PHY_SUPPORTED_LANES; jjb++) {
      if (!((mcu->phy_params.
             cfg_macro_en_val >> jjb * 2) & 0x1))
        continue;
      debug1("Ln %2d   ", jjb);
      debug1("\t");
      for (kkc = 0; kkc < 8; kkc++)
        debug1("%d ",
               ((mcu->phy_tr_dly.rd_dsk[jjb]) >> (kkc *
                    3)) &
               0x7);
      if (jjb > 15) {
        debug1(" ecc");
      }
      debug1("\n");
    }
  } else {
    debug1("\t\tR%01d [DESKEW-DISSABLED]", iia);
  }
  debug1("\n");

  // Wr-Deskew-Trim
  debug1("WrDsk-Trim ");
  iia = 0;    // Supported only for rank-0
  if ((mcu->phy_tr_dly.wrdeskew_rank_mask >> iia) & 0x1) {
    debug1("\t\tR%01d", iia);
    debug1("\n");
    debug1("Bit\t\t\t0 1 2 3 4 5 6 7 \n");
    debug1("   \t\t\t| | | | | | | | \n");
    for (jjb = 0; jjb < PHY_SUPPORTED_LANES; jjb++) {
      if (!((mcu->phy_params.
             cfg_macro_en_val >> jjb * 2) & 0x1))
        continue;
      debug1("Ln %2d   ", jjb);
      debug1("\t");
      for (kkc = 0; kkc < 8; kkc++)
        debug1("%d ",
               ((mcu->phy_tr_dly.wr_dsk[jjb]) >> (kkc *
                    3)) &
               0x7);
      if (jjb == 8) {
        debug1(" ecc");
      }
      debug1("\n");
    }
  } else {
    debug1("\t\tR%01d - [DESKEW-DISSABLED]", iia);
  }
  debug1("\n");

  debug("Phy Train Error Reg=0x%08x  Macro=0x%08x\n\n", trnerr,
        terrmacro);

  debug("DQ/DQS DriveStrength = %d  Slew = %d\n",
        ((cfg_analog2 >> 5) & 0x7), ((cfg_analog2 >> 8) & 0x3));
  debug("ADDR   DriveStrength = %d  Slew = %d\n",
        ((cfg_analog2 >> 13) & 0x7), ((cfg_analog2 >> 16) & 0x3));
  debug("CMD    DriveStrength = %d  Slew = %d\n",
        ((cfg_analog2 >> 18) & 0x7), ((cfg_analog3 >> 0) & 0x3));
  debug("CLOCK  DriveStrength = %d  Slew = %d\n",
        ((cfg_analog3 >> 7) & 0x7), ((cfg_analog3 >> 10) & 0x3));
  debug("CTL    DriveStrength = %d  Slew = %d\n",
        ((cfg_analog3 >> 2) & 0x7), ((cfg_analog3 >> 5) & 0x3));
  debug("ODT     RcvrStrength = %d  \n", ((cfg_analog3 >> 12) & 0x7));

  rttnom = ((mcu->mcu_params.mode_reg[1] >> 7) & 0x4) |
      ((mcu->mcu_params.mode_reg[1] >> 5) & 0x2) |
      ((mcu->mcu_params.mode_reg[1] >> 2) & 0x1);
  dic = ((mcu->mcu_params.mode_reg[1] >> 4) & 0x2) |
      ((mcu->mcu_params.mode_reg[1] >> 1) & 0x1);
  rttwr = ((mcu->mcu_params.mode_reg[2] >> 9) & 0x3);
  debug("Dimm RttNom = %d  DIC = %d\n", rttnom, dic);
  debug("Dimm RttWr  = %d  \n", rttwr);
  debug("PHY  ZQ Code  {0x%02X , 0x%02X} {neg,pos} \n",
        ((zqcode >> 6) & 0x3F), (zqcode & 0x3F));
  debug("     PI Code = 0x%X \n", picode);
  debug("    CDR Lock = 0x%X \n", cdrlock);
  debug("COMMAND Code = 0x%X (PI+180) \n", commandcode);
  debug
      ("Dly from Rd En = R0 \tR1 \tR2 \tR3 \tR4 \tR5 \tR6 \tR7\n                 ");
  for (iia = 0; iia < 8; iia++) {
    debug("0x%02X\t", ((cfg_dly_from_rden >> (iia * 3)) & 0x7));
  }
  debug("\n");

}       // phy_display_post_train_csrs

//======================================================================

void phy_save_rddsk_dly_csrs(void *p)
{
  int jjb, rddata;
  struct apm_mcu *mcu = (struct apm_mcu *)p;
  for (jjb = 0; jjb < PHY_SUPPORTED_LANES; jjb++) {
    rddata = phy_read_reg(mcu,
              (PHY_CFG_RDLVL_TRIM_N +
               jjb * PHY_REG_INCR_4_MACRO_OFFSET));
    mcu->phy_tr_dly.rd_dsk[jjb] = rddata;
  }
}       // phy_save_rddsk_dly_csrs

//======================================================================

void phy_save_wrdsk_dly_csrs(void *p)
{
  int jjb, rddata;
  struct apm_mcu *mcu = (struct apm_mcu *)p;
  for (jjb = 0; jjb < PHY_SUPPORTED_LANES; jjb++) {
    rddata = phy_read_reg(mcu,
              (PHY_CFG_WRLVL_TRIM_N +
               jjb * PHY_REG_INCR_4_MACRO_OFFSET));
    mcu->phy_tr_dly.wr_dsk[jjb] = rddata;
  }
}       // phy_save_wrdsk_dly_csrs

//======================================================================

void phy_clear_wrdsk_dly_csrs(void *p)
{
  int jjb, addr;
  struct apm_mcu *mcu = (struct apm_mcu *)p;

  for (jjb = 0; jjb < PHY_SUPPORTED_LANES; jjb++) {
    addr =
        (PHY_CFG_WRLVL_TRIM_N + jjb * PHY_REG_INCR_4_MACRO_OFFSET);
    phy_write_reg(mcu, addr, 0x0);  //Clear all TRIM
//              phy_write_reg(mcu, addr, 0xFFFFFFFF); // Set TRIM to MAX
    debug1("Clearing PHY[%d]-WRDESKEW-TRIM-MACRO[%d] @0x%x\n",
           mcu->id, jjb, addr);
  }
}       // phy_save_wrdsk_dly_csrs

//======================================================================

void phy_save_wrdq_dly_csrs(void *p)
{
  int jjb, rddata;
  struct apm_mcu *mcu = (struct apm_mcu *)p;
  for (jjb = 0; jjb < PHY_SUPPORTED_LANES; jjb++) {
    rddata = phy_read_reg(mcu,
              (PHY_CFG_WRDQ_DEL_N_0 +
               jjb * PHY_REG_INCR_4_MACRO_OFFSET));
    mcu->phy_tr_dly.wrdq_dly[jjb * 2] = rddata & 0xFFF;
    mcu->phy_tr_dly.wrdq_dly[jjb * 2 + 1] =
        ((rddata >> 12) & 0xFFF);
  }
}       // phy_save_wrdq_dly_csrs

//======================================================================

void init_phy_tr_dly_vals(void *p)
{
  int iia, jjb;
  struct apm_mcu *mcu = (struct apm_mcu *)p;
  for (iia = 0; iia < MCU_SUPPORTED_RANKS; iia++) {
    for (jjb = 0; jjb < PHY_SUPPORTED_LANES; jjb++) {
      mcu->phy_tr_dly.rank_dly[iia].wr_lvl[jjb * 2] =
          PHY_CFG_REG_WRLVL_DELAY;
      mcu->phy_tr_dly.rank_dly[iia].wr_lvl[jjb * 2 + 1] =
          PHY_CFG_REG_WRLVL_DELAY;
      mcu->phy_tr_dly.rank_dly[iia].gt_lvl[jjb * 2] =
          PHY_CFG_REG_RDLVL_GATE_DELAY;
      mcu->phy_tr_dly.rank_dly[iia].gt_lvl[jjb * 2 + 1] =
          PHY_CFG_REG_RDLVL_GATE_DELAY;
      mcu->phy_tr_dly.rank_dly[iia].rd_lvl[jjb * 2] =
          PHY_CFG_REG_RDLVL_DELAY;
      mcu->phy_tr_dly.rank_dly[iia].rd_lvl[jjb * 2 + 1] =
          PHY_CFG_REG_RDLVL_DELAY;
    }
  }
  /* Init to Phy CSR reset value */
  for (jjb = 0; jjb < PHY_SUPPORTED_LANES; jjb++) {
    mcu->phy_tr_dly.wrdq_dly[jjb * 2] = 0x40;
    mcu->phy_tr_dly.wrdq_dly[jjb * 2 + 1] = 0x40;

  }
  return;
}       // init_phy_tr_dly_vals

/******************************************************************************
 *     Utility functions
 *****************************************************************************/

void mcu_phy_rdfifo_reset(void *ptr)
{
  // RdFifoReset - clears Mcu & PHY's read data path
  int unsigned dat;
  struct apm_mcu *mcu = (struct apm_mcu *)ptr;
  dat = mcu->mcu_rd(mcu, MCU_REG_RDLVLCTL);
  dat |= 0x100U;
  mcu->mcu_wr(mcu, MCU_REG_RDLVLCTL, dat);  // Toggle rd fifo reset
  dat &= (~0x100U);
  mcu->mcu_wr(mcu, MCU_REG_RDLVLCTL, dat);
  /* MCU_RDLVLCTL_SAMPLE_DELAY_RNG       21:16
     MCU_RDLVLCTL_RDFIFO_RESET_RNG       8
     MCU_RDLVLCTL_RDLVL_EN_RNG           3 << only this asserted
     MCU_RDLVLCTL_RDLVLALLDONE_RNG       2
     MCU_RDLVLCTL_DORDLVL_RNG            1
     MCU_RDLVLCTL_RDLVLENDRANK_RNG       0
   */
}

/******************************************************************************
 *     Cal or Bypass routines (setup PHY trace delays compensation)
 *****************************************************************************/

int calib_bypss_fix(void *ptr)
{
  // Bypass training & restore PHY Tr Delay CSRs
  struct apm_mcu *mcu = (struct apm_mcu *)ptr;
  if (!mcu->enabled) {
    return 0;
  }

  /* Write PHY Training Delay CSRS
   *
   */
  phy_restore_train_dly_csrs(ptr, mcu->phy_tr_dly.rank_mask, 1, 1, 1);
  init_bypss_fix_kc1333(ptr);

  /*
   * Toggle lvl_load signals : MCU TRAIN Wr Rd Load
   *   enables PHY to use restored Tr Delay CSRs
   */
  mcu_reset_FSM_poll(mcu, MCU_RESET_FSM_stRESTART, POLL_EQUAL);
  mcu_set_SWISS_TRNLOAD(mcu);

  /*
   * Setup initialization control
   */
  mcu_reset_FSM_poll(mcu, MCU_RESET_FSM_stRESTART, POLL_EQUAL);

  phy_save_train_dly_csrs(ptr);
  return 0;
}       // calib_bypss_fix

//======================================================================

int mcu_check_phy_trainerr(void *ptr, int unsigned expphyerr)
{
  struct apm_mcu *mcu = (struct apm_mcu *)ptr;
  int unsigned rddata;
  int unsigned iia;
  int bout = 0;
  // bit[0] = error
  // bit[1] = timeout error
  // bit[2] = IRQ for PHY error
  // bit[3] = Phy error

  // Mcu_Reset FSM timeout error (Phy did no converge and send back done for a training step)
  rddata = mcu->mcu_rd(mcu, MCU_REG_DDR_INIT_STATUS);
  if ((expphyerr & 0x1) !=
      ((rddata >> MCU_DDR_INIT_STATUS_TIMEOUTERR_RNG) & 0x1)) {
    debug
        ("MCU  : ERROR Mcu PEVM (Phy) TimeoutErr does not  match: act(%01d) vs exp(%01d)\n",
         ((rddata >> MCU_DDR_INIT_STATUS_TIMEOUTERR_RNG) & 0x1),
         (expphyerr & 0x1));
    debug
        ("MCU %d: INFO  Mcu PEVM (Phy) WrLvl,GtLvl,RdLvl = {%01X} steps done.\n",
         mcu->id,
         ((rddata >> MCU_DDR_INIT_STATUS_RDLVLDONE_RNG) & 0x7));
    bout |= 0x3;
  } else {
    debug
        ("MCU  : INFO  Mcu PEVM (Phy) TimeoutErr matches: act(%01d) vs exp(%01d)\n",
         ((rddata >> MCU_DDR_INIT_STATUS_TIMEOUTERR_RNG) & 0x1),
         (expphyerr & 0x1));
  }

  // Check MCU_REG_MCUGESR for IRQ
  rddata = mcu->mcu_rd(mcu, MCU_REG_MCUGESR);
  if ((expphyerr & 0x1) !=
      ((rddata >> MCU_MCUGESR_PHYTRAININGERR_RNG) & 0x1)) {
    debug
        ("MCU  : ERROR  MCUGESR IRQ: PhyTrainingErr no match: act(%01d) vs exp(%01d)\n",
         ((rddata >> MCU_MCUGESR_PHYTRAININGERR_RNG) & 0x1),
         (expphyerr & 0x1));
    bout |= 0x5;
  } else {
    debug
        ("MCU  : INFO  MCUGESR IRQ: PhyTrainingErr match: act(%01d) vs exp(%01d)\n",
         ((rddata >> MCU_MCUGESR_PHYTRAININGERR_RNG) & 0x1),
         (expphyerr & 0x1));
  }

  // Read PHY error Csrs
  rddata = phy_read_reg(mcu, KC_PHY_REG36);
  if ((expphyerr & 0x1)) {
    // GONZO - if expecting an error
  } else {
    if ((rddata & 0x1F) != 0x0) {
      debug
          ("MCU %d: ERROR  Phy unexpected training_error :{WrLvl,WrCal,GtLvl,RdLvl,TrainErr}={%02X}\n",
           mcu->id, (rddata & 0x1F));
      bout |= 0x9;
    } else {
      // No Error
      debug
          ("MCU %d: INFO  Phy no training_error :{WrLvl,WrCal,GtLvl,RdLvl,TrainErr}={%02X}\n",
           mcu->id, (rddata & 0x1F));
    }
  }

  // Read Phy per lane info
  // Get Per lane info
  rddata = phy_read_reg(mcu, KC_PHY_REG49);
  debug("MCU %d: PHYCSR CFG_MACRO_TR_ERROR  lane [", mcu->id);
  // define  KC_PHY_REG49_MACRO8_0_ERROR_RNG  16
  for (iia = 0; iia < 9; iia++) {
    debug("(%01d  e=%01d)", iia, ((rddata >> (iia * 2)) & 0x1));
  }
  if (mcu->mcu_params.by4_mode) {
    debug("] x4 nibble 0\n");
    debug("MCU %d: PHYCSR CFG_MACRO_TR_ERROR  lane [", mcu->id);
    for (iia = 0; iia < 9; iia++) {
      debug(" (%01d  e=%01d) ", iia,
            ((rddata >> ((iia * 2) + 1)) & 0x1));
    }
    debug("] x4 nibble 1\n");
  } else {
    debug("] x8\n");
  }
  return bout;
}       // mcu_check_phy_trainerr

int phy_correct_wrdq_delays(void *ptr);

int kc_phy_wrcal_deskew(void *ptr,
      int unsigned rank, int unsigned checktrainerr)
{
  int slice, olddelay;
  int err0 = 0;
  int unsigned cs_n;
  struct apm_mcu *mcu = (struct apm_mcu *)ptr;
#ifdef FIX_BROKEN_WRCAL_PERMACRO
  int err_wrcal = 0;
#endif
  cs_n = (~(1U << rank)) & 0xFF;

  mcu_phy_rdfifo_reset(ptr);
  // turn on  dfi_rdlvl_cs_n
  mcu_set_SWISS_TRNCTL(ptr, 1, 0, 0, 0, 0xFF, cs_n);

  mcu_set_SWISS_ODTADDR(ptr, 1, 0, 0x0F00, 0, 0);
  mcu_reset_FSM_poll(mcu, MCU_RESET_FSM_stRESTART, POLL_EQUAL);
  mcu_set_SWISS_OPCTL(ptr, 1, 0, MCU_PRE, cs_n);
  mcu_reset_FSM_poll(mcu, MCU_RESET_FSM_stRESTART, POLL_EQUAL);
  mcu_set_SWISS_ODTADDR(ptr, 0, 0, 0x0000, 0, 0);

  //WrCal
  if ((mcu->phy_tr_dly.phy_wrcal_rank_mask >> rank) & 0x1) {
    debug
        ("MCU%d :: mc_kc_phy_eval_mode_wrcal::Starting WrCal  rank=%01d\n",
         mcu->id, rank);
    phy_rf_write_cfg_wrcal_en(ptr, 0x1);  // rmw4B_KC_PHY(.addr(0x1C) ,.data(0x2),.mask(0x2) );
    // #500ns;
    phy_poll_reg(ptr, 0x18U, 0x1U, 0x1U);

#ifdef FIX_BROKEN_WRCAL_PERMACRO
    // Not matured yet
    if (checktrainerr)
      err_wrcal += mcu_check_phy_trainerr(ptr, 0);
    if (err_wrcal) {
      err0 += phy_correct_wrcal_delays(ptr, rank);
//                      err0 += phy_correct_wrcal_delays(ptr, rank);    // Intentially run 2nd time
//                      err0 += phy_correct_wrcal_delays(ptr, rank);    // Intentially run 3rd time
//                      err0 += phy_correct_wrcal_delays(ptr, rank);    // Intentially run 4th time

      /*
       * Must reset statemachine to take in new changes
       */
      mcu_reset_FSM_poll(ptr, MCU_RESET_FSM_stRESTART,
             POLL_EQUAL);
      mcu_set_SWISS_TRNLOAD(ptr);
      mcu_reset_FSM_poll(ptr, MCU_RESET_FSM_stRESTART,
             POLL_EQUAL);

      err0 += mcu_check_phy_trainerr(ptr, 0);
    }
#else
    if (checktrainerr)
      err0 += mcu_check_phy_trainerr(ptr, 0);
#endif
    phy_rf_write_cfg_wrcal_en(ptr, 0x0);  //rmw4B_KC_PHY(.addr(0x1C) ,.data(0x0),.mask(0x2) );
    debug
        ("MCU%d ::  mc_kc_phy_eval_mode_wrcal::Finished WrCal  rank=%01d\n",
         mcu->id, rank);
  }
  //Deskew
  if ((mcu->phy_tr_dly.rddeskew_rank_mask >> rank) & 0x1) {
    debug
        ("MCU%d ::  mc_kc_phy_eval_mode_wrcal::Starting Rd Deskew  rank=%01d\n",
         mcu->id, rank);

#ifdef FIX_DEFAULT_RDE_BFRDSK
    // Set default/start value as 0x20.. and then backoff by 0x10
    if ((mcu->phy_tr_dly.rddeskew_rank_mask >> rank) & 0x1) {
      if (rank == 0) {  //RD-DESKEW supported only for Rank-0
        debug
            ("\n\nMCU[%d] - FIXING DEFAULT RDE Leveling values for all macros (Before PEVM-RD-DESKEW)\n",
             mcu->id);
        for (slice = 0; slice < PHY_SUPPORTED_LANES * 2;
             slice++) {
          if (!
              ((mcu->phy_params.
                cfg_macro_en_val >> slice) & 0x1))
            continue;
          mcu->phy_tr_dly.rank_dly[rank].
              rd_lvl[slice] = DEFAULT_RDEYE_VALUE;
        }
        debug("\n Restoring the FIX delays...\n\n");
        phy_restore_train_dly_csrs(mcu, (0x1U << rank),
                 0, 0, 1);
      }
    }
#endif
    //deskew rd
    phy_rf_write_cfg_rd_deskew_en(ptr, 0x1);  // rmw4B_KC_PHY(.addr(0x1C) ,.data(0x1),.mask(0x1) );
    DELAY(50);
    // #5000ns;
    phy_poll_reg(ptr, 0x24, 0x1, 0x1);  // .optimeout(5000)
    if (checktrainerr)
      err0 += mcu_check_phy_trainerr(ptr, 0);
    phy_rf_write_cfg_rd_deskew_en(ptr, 0x0);  //rmw4B_KC_PHY(.addr(0x1C) ,.data(0x0),.mask(0x1) );
    debug
        ("MCU%d :: mc_kc_phy_eval_mode_wrcal::Finished Rd Deskew  rank=%01d\n",
         mcu->id, rank);
    phy_save_train_dly_csrs(ptr);
#ifdef FIX_DEFAULT_RDE
    /*
     *  AUTOFIX: Back-Off RDE based on default value [new-lvl -= (default-reg-value)/2]
     */
    for (slice = 0; slice < PHY_SUPPORTED_LANES * 2; slice++) {
      if (!
          ((mcu->phy_params.cfg_macro_en_val >> slice) & 0x1))
        continue;
      olddelay = mcu->phy_tr_dly.rank_dly[rank].rd_lvl[slice];
      if (olddelay > (DEFAULT_RDEYE_VALUE / 2)) {
        mcu->phy_tr_dly.rank_dly[rank].
            rd_lvl[slice] -= (DEFAULT_RDEYE_VALUE / 2);
        debug
            ("\t\t Correcting RDE-LVL RANK[%d]-Macro[%d]: 0x%x [old:0x%x] after DESKEW\n",
             rank, slice,
             mcu->phy_tr_dly.rank_dly[rank].
             rd_lvl[slice], olddelay);
      }

    }
    debug("\n Restoring the Auto Fixed delays...\n\n");
    phy_restore_train_dly_csrs(mcu, (0x1U << rank), 0, 0, 1);
    mcu_phy_rdfifo_reset(ptr);

#endif
  }
  if ((mcu->phy_tr_dly.rdlvl2nd_rank_mask >> rank) & 0x1) {
    debug
        ("MCU%d :: mc_kc_phy_eval_mode_wrcal::Starting 2nd lvl Rd leveling  rank=%01d\n",
         mcu->id, rank);
#ifdef FIX_DEFAULT_RDE_BEF2ND
    // Set default/start value as 0x20... and then backoff by 0x10
    if ((mcu->phy_tr_dly.rddeskew_rank_mask >> rank) & 0x1) {
      if (rank == 0) {  //RD-DESKEW supported only for Rank-0
        debug
            ("\n\nMCU[%d] - FIXING DEFAULT RDE Leveling values for all macros (Before PEVM-RD-DESKEW)\n",
             mcu->id);
        for (slice = 0; slice < PHY_SUPPORTED_LANES * 2;
             slice++) {
          if (!
              ((mcu->phy_params.
                cfg_macro_en_val >> slice) & 0x1))
            continue;
          mcu->phy_tr_dly.rank_dly[rank].
              rd_lvl[slice] = DEFAULT_RDEYE_VALUE;
        }
        debug("\n Restoring the FIX delays...\n\n");
        phy_restore_train_dly_csrs(mcu, (0x1U << rank),
                 0, 0, 1);
      }
    }
#endif
    //2nd rd Lvl
    phy_rf_write_cfg_2nd_rdlvl_en(ptr, 0x1);
    // #1000ns;
    phy_poll_reg(ptr, 0x24, 0x1, 0x1);  // .optimeout(5000)
    if (checktrainerr)
      err0 += mcu_check_phy_trainerr(ptr, 0);
    phy_rf_write_cfg_2nd_rdlvl_en(ptr, 0x0);
    debug
        ("MCU%d :: mc_kc_phy_eval_mode_wrcal::Finished 2nd Rd Lvl  rank=%01d\n",
         mcu->id, rank);
#ifdef FIX_DEFAULT_RDE
    /*
     *  AUTOFIX: Back-Off RDE based on default value [new-lvl -= (default-reg-value)/2]
     */
    phy_save_train_dly_csrs(mcu);
    for (slice = 0; slice < PHY_SUPPORTED_LANES * 2; slice++) {
      if (!
          ((mcu->phy_params.cfg_macro_en_val >> slice) & 0x1))
        continue;
      olddelay = mcu->phy_tr_dly.rank_dly[rank].rd_lvl[slice];
      if (olddelay > (DEFAULT_RDEYE_VALUE / 2)) {
        mcu->phy_tr_dly.rank_dly[rank].
            rd_lvl[slice] -= (DEFAULT_RDEYE_VALUE / 2);
        debug
            ("\t\t Correcting RDE-LVL RANK[%d]-Macro[%d]: 0x%x [old:0x%x] after 2nd level\n",
             rank, slice,
             mcu->phy_tr_dly.rank_dly[rank].
             rd_lvl[slice], olddelay);
      }

    }
    debug("\n Restoring the Auto Fixed delays...\n\n");
    phy_restore_train_dly_csrs(mcu, (0x1U << rank), 0, 0, 1);
    mcu_phy_rdfifo_reset(ptr);

#endif
  }

  if ((mcu->phy_tr_dly.wrdeskew_rank_mask >> rank) & 0x1) {
    debug
        ("MCU%d :: mc_kc_phy_eval_mode_wrcal::Start Wr Deskew  rank=%01d\n",
         mcu->id, rank);
    //wr deskew
    phy_rf_write_cfg_wr_deskew_en(ptr, 0x1);
    // #20000ns;
    phy_poll_reg(ptr, 0x24, 0x2, 0x2);  // .optimeout(5000)
    if (checktrainerr)
      err0 += mcu_check_phy_trainerr(ptr, 0);
    phy_rf_write_cfg_wr_deskew_en(ptr, 0x0);
    debug
        ("MCU%d :: mc_kc_phy_eval_mode_wrcal::Finished Wr Deskew  rank=%01d\n",
         mcu->id, rank);
    //Check/Fix broken WR-DQ-DQS based on FIX_BROKEN_WRDQ_PERMACRO
    err0 += phy_correct_wrdq_delays(mcu);
  }

  /* if (m_en_phy_deskew_cleanup) {
     // Bug  - KC PHY leaves bank 1 activate
     // do PREA on this rank
     mcu_set_SWISS_ODTADDR(ptr, 1, 0x0, 0x0F00, 0, 0 );
     mcu_reset_FSM_poll(mcu, MCU_RESET_FSM_stRESTART, POLL_EQUAL);
     mcu_set_SWISS_OPCTL(ptr, 1, 0, MCU_PRE, cs_n );
     mcu_reset_FSM_poll(mcu, MCU_RESET_FSM_stRESTART, POLL_EQUAL);
     } */// if (m_en_phy_deskew_cleanup)

  // Turn off dfi_rdlvl_cs_n
  mcu_set_SWISS_TRNCTL(ptr, 1, 0, 0, 0, 0xFF, 0xFF);
  mcu_set_SWISS_TRNCTL(ptr, 0, 0, 0, 0, 0xFF, 0xFF);

  mcu_phy_rdfifo_reset(ptr);
  return err0;
}       // kc_phy_wrcal_deskew

int kc_phy_sw_wrcal_deskew(void *ptr,
         int unsigned rank, int unsigned checktrainerr)
{
  int err0 = 0;
  int unsigned cs_n, cyc_offset, wrlvl_uncertainty, jjb, iia;
  int unsigned __attribute__ ((unused)) d0, d1, d2;
  int wrd[9] = { 0, 0, 0, 0, 0, 0, 0, 0, 0 };
  int unsigned wrd_cmp;
  struct apm_mcu *mcu = (struct apm_mcu *)ptr;
  iia = rank;
  jjb = 0;
  cyc_offset = 1;
  wrlvl_uncertainty = 10;

  cs_n = (~(1U << rank)) & 0xFF;

  mcu_phy_rdfifo_reset(ptr);
  // turn on  dfi_rdlvl_cs_n
  mcu_set_SWISS_TRNCTL(ptr, 1, 0, 0, 0, 0xFF, cs_n);

  mcu_set_SWISS_ODTADDR(ptr, 1, 0, 0x0F00, 0, 0);
  mcu_reset_FSM_poll(mcu, MCU_RESET_FSM_stRESTART, POLL_EQUAL);
  mcu_set_SWISS_OPCTL(ptr, 1, 0, MCU_PRE, cs_n);
  mcu_reset_FSM_poll(mcu, MCU_RESET_FSM_stRESTART, POLL_EQUAL);
  mcu_set_SWISS_ODTADDR(ptr, 0, 0, 0x0000, 0, 0);

  //WrCal
  debug
      ("MCU%d :: mc_kc_phy_eval_mode_wrcal::Starting SW WrCal  rank=%01d\n",
       mcu->id, rank);

  d0 = 0xff & mcu->phy_tr_dly.rank_dly[iia].wr_lvl[jjb * 2];  //read_wrlvl_farr[rank][i]()
  cyc_offset = 0x1;
  wrd[0] =
      (cyc_offset << 8) | (0xff & mcu->phy_tr_dly.rank_dly[iia].
         wr_lvl[jjb * 2]);
  wrd_cmp = wrd[0];

  for (jjb = 1; jjb < PHY_SUPPORTED_LANES; jjb++) {

    //cyc_offset =1;
    d1 = (cyc_offset << 8) | (0xff & mcu->phy_tr_dly.
            rank_dly[iia].wr_lvl[jjb * 2]);

    if (!(d1 & 0xFF)) {
      wrd[jjb] = 0;
    } else {
      if (d1 < (wrd_cmp + wrlvl_uncertainty)) {
        cyc_offset = cyc_offset + 1;
      }
      wrd[jjb] = (cyc_offset << 8) | (d1 & 0xFF);
      wrd_cmp = wrd[jjb];
      debug("MCU  :: VENU FINAL VAL iib%x  val%x\n",
            jjb, wrd[jjb]);
    }
  }

  for (jjb = 0; jjb < PHY_SUPPORTED_LANES; jjb++) {
    debug
        ("MCU%d :: mc_kc_phy_eval_mode_sw_wrcal::Starting SW WrCal WRLVL new values dm=%01x\n",
         jjb, wrd[jjb]);
    mcu->phy_tr_dly.rank_dly[iia].wr_lvl[jjb * 2] = wrd[jjb];
  }

  for (jjb = 0; jjb < PHY_SUPPORTED_LANES; jjb++) {
    phy_write_reg(mcu,
            (PHY_CFG_REG_WRLVL_DELAY0_0 +
             iia * PHY_REG_INCR_4_RANK_OFFSET +
             jjb * PHY_REG_INCR_4_MACRO_OFFSET),
            mcu->phy_tr_dly.rank_dly[iia].wr_lvl[jjb * 2]);
  }
  if (checktrainerr)
    err0 += mcu_check_phy_trainerr(ptr, 0);
  phy_rf_write_cfg_wrcal_en(ptr, 0x0);  //rmw4B_KC_PHY(.addr(0x1C) ,.data(0x0),.mask(0x2) );
  debug
      ("MCU%d ::  mc_kc_phy_eval_mode_wrcal::Finished WrCal  rank=%01d\n",
       mcu->id, rank);

  mcu_set_SWISS_TRNCTL(ptr, 1, 0, 0, 0, 0xFF, 0xFF);
  mcu_set_SWISS_TRNCTL(ptr, 0, 0, 0, 0, 0xFF, 0xFF);

  mcu_phy_rdfifo_reset(ptr);
  return err0;
}       // kc_phy_sw_wrcal_deskew

//==================================================================
int phy_correct_wrcal_delays(void *ptr, unsigned int rank)
{
  // If WR-cal values are less then 0x100, fix it to 0x1xx / 0x2xx / 0x3xx
  unsigned int err, err0, n, by4;
  unsigned int readData, prevData = 0, offset, offset_nxt, nextData =
      0, offsetp, wdata;
  struct apm_mcu *mcu = (struct apm_mcu *)ptr;
  if (!mcu->enabled) {
    return 1;
  }
  err = 0;
  by4 = mcu->mcu_params.by4_mode;

  for (n = 0; n < 18; n++) {
    if (!((mcu->phy_params.cfg_macro_en_val >> n) & 0x1))
      continue;
    offset =
        PHY_CFG_REG_WRLVL_DELAY0_0 +
        (unsigned int)((n / 2 * PHY_REG_INCR_4_MACRO_OFFSET) +
           (rank * PHY_REG_INCR_4_RANK_OFFSET) +
           (4 * (by4 & n & 0x1)));
    readData = phy_read_reg(mcu, offset) & 0xFFF;
    if (n < 8) {
      offset_nxt =
          PHY_CFG_REG_WRLVL_DELAY0_0 +
          (unsigned
           int)(((n + 2) / 2 * PHY_REG_INCR_4_MACRO_OFFSET) +
          (rank * PHY_REG_INCR_4_RANK_OFFSET) +
          (4 * (by4 & (n + 2) & 0x1)));
      nextData = phy_read_reg(mcu, offset_nxt) & 0xFFF;
    }
    err0 = 0;
    wdata = 0;
    if (n > 16) // ECC slice
      offsetp = PHY_CFG_REG_WRLVL_DELAY0_0 +
          (unsigned int)((((n / 2) - 4) *
              PHY_REG_INCR_4_MACRO_OFFSET) +
             (rank * PHY_REG_INCR_4_RANK_OFFSET) +
             (4 * (by4 & n & 0x1)));
    else
      offsetp =
          PHY_CFG_REG_WRLVL_DELAY0_0 +
          (unsigned int)((((n / 2) - 1) *
              PHY_REG_INCR_4_MACRO_OFFSET) +
             (rank * PHY_REG_INCR_4_RANK_OFFSET) +
             (4 * (by4 & n & 0x1)));
    prevData = phy_read_reg(mcu, offsetp) & 0xFFF;
    if ((n < 8) && (nextData - readData > 0x80)
        && (readData < 0x100)) {
      debug("MCU-PHY[%d] FIX_BROKEN_WRCAL macro:%d <8\n",
            mcu->id, n);
      debug("\tc@ 0x%x:0x%x n@ 0x%x:0x%x\n", offset, readData,
            offset_nxt, nextData);
      if (((nextData - readData) <
           (0x100 - (nextData & 0xFF))) && (nextData > 0x200))
        wdata =
            ((((nextData >> 8) & 0x3) -
              1) << 8) | readData;
      else
        wdata = (nextData & 0x300) | readData;
    } else if ((n >= 8)
         && ((prevData - readData > 0x40)
             || ((prevData >> 8) > (readData >> 8)))
         && (readData < 0x300)) {
      debug("MCU-PHY[%d] FIX_BROKEN_WRCAL macro:%d >8\n",
            mcu->id, n);
      debug("\tc@ 0x%x:0x%x p@ 0x%x:0x%x \n", offset,
            readData, offsetp, prevData);
      if (readData <= prevData)
        wdata =
            ((((prevData >> 8) & 0x3) +
              1) << 8) | (readData & 0xFF);
      else if (readData > prevData)
        wdata = (prevData & 0x300) | (readData & 0xFF);
      else
        continue;
    } else {
      continue;
    }

    debug
        ("[WR-CAL read:0x%x, prev:0x%x, fixed:0x%x]: ERR:%d\n",
         readData, prevData, wdata, err0);
    if (!err0)
      phy_write_reg(mcu, offset, wdata);
    err += err0;
  }
  /*
   * Must reset statemachine to take in new changes
   */
  mcu_reset_FSM_poll(mcu, MCU_RESET_FSM_stRESTART, POLL_EQUAL);
  mcu_set_SWISS_TRNLOAD(mcu);
  mcu_reset_FSM_poll(mcu, MCU_RESET_FSM_stRESTART, POLL_EQUAL);
  return err;
}
int phy_correct_rdeye_delays(void *ptr, unsigned int rank)
{
  // If RD-lvl (EYE) values are less then 0x20, fix it to 0x40
  unsigned int n, err;
  unsigned int readData, offset, wdata = 0;
  struct apm_mcu *mcu = (struct apm_mcu *)ptr;
  if (!mcu->enabled) {
    return 1;
  }
  err = 0;
  wdata = FIX_BROKEN_RDEYE_VALUE; // This value might change based on DIMM/SPEED
  for (n = 0; n < 9; n++) {
    // byte/x4[0] of the macro
    offset =
        PHY_CFG_REG_RDLVL_DELAY0_0 +
        (unsigned int)((n * PHY_REG_INCR_4_MACRO_OFFSET) +
           (rank * PHY_REG_INCR_4_RANK_OFFSET));
    // Check if macro enabled
    if (!((mcu->phy_params.cfg_macro_en_val >> (n * 2)) & 0x1))
      continue;
    readData = phy_read_reg(mcu, offset) & 0xFFF;
    if (readData < CMP_BROKEN_RDEYE_VALUE) {

#ifdef FIX_BROKEN_RDEYE_PERMACRO
      phy_write_reg(mcu, offset, wdata);
      debug
          ("MCU-PHY[%d] : FIX_BROKEN_RDEYE macro:%d [PEVM-RDlvl-read: 0x%03X]\n",
           mcu->id, n * 2, readData);
#else
      debug
          ("MCU-PHY[%d] : Need FIX_BROKEN_RDEYE macro:%d [PEVM-RDlvl-read: 0x%03X]\n",
           mcu->id, n * 2, readData);
      err++;
#endif
    }
    // x4[1] of same macro
    offset += 4;
    if (!
        ((mcu->phy_params.cfg_macro_en_val >> ((n * 2) + 1)) & 0x1))
      continue;
    readData = phy_read_reg(mcu, offset) & 0xFFF;
    if (readData < 0x20) {
#ifdef FIX_BROKEN_RDEYE_PERMACRO
      phy_write_reg(mcu, offset, wdata);
      debug
          ("MCU-PHY[%d] : FIX_BROKEN_RDEYE macro:%d [PEVM-RDlvl-read: 0x%03X]\n",
           mcu->id, n * 2, readData);
#else
      debug
          ("MCU-PHY[%d] : Need FIX_BROKEN_RDEYE macro:%d [PEVM-RDlvl-read: 0x%03X]\n",
           mcu->id, n * 2, readData);
      err++;
#endif
    }
  }
  /*
   * Must reset statemachine to take in new changes
   */
  mcu_reset_FSM_poll(mcu, MCU_RESET_FSM_stRESTART, POLL_EQUAL);
  mcu_set_SWISS_TRNLOAD(mcu);
  mcu_reset_FSM_poll(mcu, MCU_RESET_FSM_stRESTART, POLL_EQUAL);
  return err;
}

int phy_correct_wrdq_delays(void *ptr)
{
  // If RD-lvl (EYE) values are less then 0x20, fix it to 0x40
  unsigned int n, err;
  unsigned int readData, offset, wdata = 0;
  struct apm_mcu *mcu = (struct apm_mcu *)ptr;
  if (!mcu->enabled) {
    return 1;
  }
  err = 0;
  wdata = FIX_BROKEN_WRDQ_VALUE;  // This value might change based on DIMM/SPEED //0x40; //0x28;
  for (n = 0; n < 9; n++) {
    // byte/x4[0] of the macro
    offset =
        PHY_CFG_WRDQ_DEL_N_0 +
        (unsigned int)((n * PHY_REG_INCR_4_MACRO_OFFSET));
    // Check if macro enabled
    if (!((mcu->phy_params.cfg_macro_en_val >> (n * 2)) & 0x1))
      continue;
    readData = phy_read_reg(mcu, offset);
    if ((readData & 0xFFF) < CMP_BROKEN_WRDQ_VALUE) {

#ifdef FIX_BROKEN_WRDQ_PERMACRO
      phy_write_reg(mcu, offset,
              ((readData & 0xFFF000) | wdata));
      debug
          ("MCU-PHY[%d] : FIX_BROKEN_WRDQ macro:%d [After PEVM-WR-deskew: 0x%03X]\n",
           mcu->id, n * 2, readData & 0xFFF);
#else
      debug
          ("MCU-PHY[%d] : Need FIX_BROKEN_WRDQ macro:%d [After PEVM-WR-deskew: 0x%03X]\n",
           mcu->id, n * 2, readData & 0xFFF);
      err++;
#endif
    }
    // x4[1] of same macro
    if (!
        ((mcu->phy_params.cfg_macro_en_val >> ((n * 2) + 1)) & 0x1))
      continue;
    readData = phy_read_reg(mcu, offset);
    if (((readData >> 12) & 0xFFF) < 0x20) {
#ifdef FIX_BROKEN_WRDQ_PERMACRO
      phy_write_reg(mcu, offset,
              ((wdata << 12) | (readData & 0xFFF)));
      debug
          ("MCU-PHY[%d] : FIX_BROKEN_WRDQ macro:%d [After PEVM-WR-deskew: 0x%03X]\n",
           mcu->id, n * 2, (readData >> 12));
#else
      debug
          ("MCU-PHY[%d] : Need FIX_BROKEN_WRDQ macro:%d [After PEVM-WR-deskew: 0x%03X]\n",
           mcu->id, n * 2, (readData >> 12));
      err++;
#endif
    }
  }
  /*
   * Must reset statemachine to take in new changes
   */
  mcu_reset_FSM_poll(mcu, MCU_RESET_FSM_stRESTART, POLL_EQUAL);
  mcu_set_SWISS_TRNLOAD(mcu);
  mcu_reset_FSM_poll(mcu, MCU_RESET_FSM_stRESTART, POLL_EQUAL);
  return err;
}

int phy_redo_check_rdeye(void *ptr, unsigned int rank, unsigned int redo)
{
  // If RD-lvl (EYE) values are less then 0x20, fix it to 0x40
  unsigned int n, err;
  unsigned int readData, offset;
  struct apm_mcu *mcu = (struct apm_mcu *)ptr;
  if (!mcu->enabled) {
    return 1;
  }
  err = 0;
  debug
      ("\nMCU[%d]-RANK[%d]-CHECK-BROKEN-RDEYE[%d] --------------------\n",
       mcu->id, rank, redo);
//CHECK-BROKEN
  for (n = 0; n < 9; n++) {
    // byte/x4[0] of the macro
    offset =
        PHY_CFG_REG_RDLVL_DELAY0_0 +
        (unsigned int)((n * PHY_REG_INCR_4_MACRO_OFFSET) +
           (rank * PHY_REG_INCR_4_RANK_OFFSET));
    // Check if macro enabled
    if (!((mcu->phy_params.cfg_macro_en_val >> (n * 2)) & 0x1))
      continue;
    readData = phy_read_reg(mcu, offset) & 0xFFF;
    if (readData < 0x20) {

      debug
          ("MCU-PHY[%d] : REDO_BROKEN_RDEYE macro:%d [PEVM-RDlvl-read: 0x%03X]\n",
           mcu->id, n * 2, readData);
      err++;
    }
    // x4[1] of same macro
    offset += 4;
    if (!
        ((mcu->phy_params.cfg_macro_en_val >> ((n * 2) + 1)) & 0x1))
      continue;
    readData = phy_read_reg(mcu, offset) & 0xFFF;
    if (readData < 0x20) {
      debug
          ("MCU-PHY[%d] : REDO_BROKEN_RDEYE macro:%d [PEVM-RDlvl-read: 0x%03X]\n",
           mcu->id, n * 2, readData);
      err++;
    }
  }

  return err;
}

//==================================================================
int calib_pevm_seperate_steps(void *ptr)
{
  // PHY PEVM training for all lanes and ranks
  //
  int unsigned iia = 0, slice;
  int err0 = 0, err1 = 0;
  int unsigned fsm_init_seq = 0;
  int unsigned fsm_init_ctl = 0;
  int unsigned mr2val, mr1val, wdata, sumdelay, olddelay;
//    int unsigned early_rdg = MCU_PHY_EARLY_RDGATELVL_ENAB;
  int unsigned __attribute__ ((unused)) rddata;
  struct apm_mcu *mcu = (struct apm_mcu *)ptr;
  if (!mcu->enabled) {
    return 0;
  }

  fsm_init_ctl =
      (1U << MCU_DDR_INIT_CTL_CALIBGO_RNG) |
      ((0x4U & 0xFU) << MCU_DDR_INIT_CTL_RCWAIT_RNG) |
      ((0x1U & 0x7U) << MCU_DDR_INIT_CTL_REFRESHCNT_RNG);

  /*
   * Setup MCU Training FSM CSRs
   */

  mcu->mcu_wr(mcu, MCU_REG_WRLVLMRD, (0x14U));  // MCU_WRLVLMRD_VALUE_RNG  7:0
  mcu->mcu_wr(mcu, MCU_REG_WRLVLTMRS, (0x0000FFFFU | ((mcu->mcu_params.tWRLVL_WW & 0xFF) << 24)));  //
  /* MCU_WRLVLTMRS_WW_RNG 31:24
     MCU_WRLVLTMRS_MAX_RNG   19:0
   */
  mcu->mcu_wr(mcu, MCU_REG_RDLVLTMRS, (0x0010FFFFU | ((mcu->mcu_params.tRDLVL_RR & 0xFF) << 24)));  //
  /* MCU_RDLVLTMRS_RR_RNG 31:24
     MCU_RDLVLTMRS_BBGAP_RNG  23:20
     MCU_RDLVLTMRS_MAX_RNG  19:0
   */
  //JHR 1/28 mcu->mcu_wr(mcu, MCU_REG_WRLVLDLY, (0x07040B09U)); //
  mcu->mcu_wr(mcu, MCU_REG_WRLVLDLY, (0x0A090F0FU));  //
  /* MCU_WRLVLDLY_WRRESPLAT_RNG          31:24
     MCU_WRLVLDLY_MR2WRLVLEN_RNG         23:16
     MCU_WRLVLDLY_WRLVLDLL_RNG           15:8
     MCU_WRLVLDLY_WRLVLEN2LOAD_RNG       7:0
   */
  // JHR 1/28 mcu->mcu_wr(mcu, MCU_REG_RDLVLDLY, (0x0A050704U)); //
  mcu->mcu_wr(mcu, MCU_REG_RDLVLDLY, (0x100A0C0AU));  //
  /* MCU_RDLVLDLY_RDRESPLAT_RNG          31:24
     MCU_RDLVLDLY_MR2RDLVLEN_RNG         23:16
     MCU_RDLVLDLY_RDLVLDLL_RNG           15:8
     MCU_RDLVLDLY_RDLVLENLOAD_RNG                7:0
   */
  mcu->mcu_wr(mcu, MCU_REG_WRLVLCTL, (0x00000008U));  //
  /* MCU_WRLVLCTL_WRLVL_EN_RNG           3 << only this asserted
     MCU_WRLVLCTL_WRLVLALLDONE_RNG       2
     MCU_WRLVLCTL_DOWRLVL_RNG            1
     MCU_WRLVLCTL_WRLVLENDRANK_RNG       0
   */
  mcu->mcu_wr(mcu, MCU_REG_RDGATECTL, (0x00000008U)); //
  /* MCU_RDGATECTL_RDGATE_EN_RNG         3 << only this asserted
     MCU_RDGATECTL_RDGATEALLDONE_RNG     2
     MCU_RDGATECTL_DORDGATE_RNG          1
     MCU_RDGATECTL_RDGATEENDRANK_RNG     0

   */
  mcu->mcu_wr(mcu, MCU_REG_RDLVLCTL, (0x00000008U));  //
  /* MCU_RDLVLCTL_SAMPLE_DELAY_RNG       21:16
     MCU_RDLVLCTL_RDFIFO_RESET_RNG       8
     MCU_RDLVLCTL_RDLVL_EN_RNG           3 << only this asserted
     MCU_RDLVLCTL_RDLVLALLDONE_RNG       2
     MCU_RDLVLCTL_DORDLVL_RNG            1
     MCU_RDLVLCTL_RDLVLENDRANK_RNG       0
   */

  mcu_phy_rdfifo_reset(ptr);

  /*
   *  Per rank calibration loop
   */
  for (iia = 0; iia < MCU_SUPPORTED_RANKS; iia++) {
    if ((mcu->phy_tr_dly.rank_mask >> iia) & 0x1) {

      /*
       *  PEVM: WR leveling
       */
      // Disable DLL-Reset
      wdata = mcu->mcu_rd(mcu, MCU_REG_MRS_0_VALUE) & 0xFEFF;
      mcu->mcu_wr(mcu, MCU_REG_MRS_0_VALUE, wdata);

      // Must turn off MR2 dynamic odt before WrLvl
      // And only allow MR1 RttNom { RZQ/2 or RZQ/4 or RZQ/6 }
      mr1val = mcu->mcu_rd(mcu, MCU_REG_MRS_1_VALUE);
      wdata =
          putRttNomintoMR1(mr1val,
               mcu->mcu_params.rttnom_wrlvl);
      mcu->mcu_wr(mcu, MCU_REG_MRS_1_VALUE, wdata);

      mr2val = mcu->mcu_rd(mcu, MCU_REG_MRS_2_VALUE);
      wdata = mr2val & 0xFFFFF9FF;
      mcu->mcu_wr(mcu, MCU_REG_MRS_2_VALUE, wdata);
      mcu_reset_FSM_poll(mcu, MCU_RESET_FSM_stRESTART,
             POLL_EQUAL);
      fsm_init_seq = (1U << MCU_DDR_INIT_SEQ_MRENAB_RNG);
      mcu->mcu_wr(mcu, MCU_REG_DDR_INIT_SEQ, fsm_init_seq);
      mcu->mcu_wr(mcu, MCU_REG_DDR_INIT_CTL, fsm_init_ctl); // Kick off FSM

      mcu_reset_FSM_poll(mcu, MCU_RESET_FSM_stRESTART,
             POLL_EQUAL);
#ifdef FIX_DEFAULT_WRDQX
      wdata = (DEFAULT_WR_DQX_VALUE & 0x7FU);
      wdata |= ((DEFAULT_WR_DQX_VALUE & 0x7FU) << 7);
      wdata |= ((DEFAULT_WR_DQX_VALUE & 0x7FU) << 14);
      wdata |= ((DEFAULT_WR_DQX_VALUE & 0x7FU) << 21);
      phy_write_reg(mcu, PHY_CFG_DQX_90_1, wdata);
      phy_write_reg(mcu, PHY_CFG_DQX_90_2, wdata);
      phy_write_reg(mcu, PHY_CFG_DQX_90_3,
              (DEFAULT_WR_DQX_VALUE & 0x7FU));
#endif

#ifdef CHANGE_WRCAL_PATTERN
      /*
       *  CHANGE: WR_CAL pattern (Default pattern does not toggle bit3 & bit 7)
       */
      wdata = CHANGE_WRCAL_PAT1;
      phy_write_reg(mcu, PHY_CFG_REG_WRCAL_PAT1, wdata);
      wdata = CHANGE_WRCAL_PAT2;
      phy_write_reg(mcu, PHY_CFG_REG_WRCAL_PAT2, wdata);
#endif

#ifdef FIX_DEFAULT_WRLVL
      // Set default/start value as 0 (starting '0' is not good... just for expr)
      debug
          ("\n\nMCU[%d] - FIXING DEFAULT WR Leveling values for all macros (Before PEVM-WRLVL):\n",
           mcu->id);
      for (slice = 0; slice < PHY_SUPPORTED_LANES * 2;
           slice++) {
        if (!
            ((mcu->phy_params.
              cfg_macro_en_val >> slice) & 0x1))
          continue;
        mcu->phy_tr_dly.rank_dly[iia].
            wr_lvl[slice] = DEFAULT_WRLVL_VALUE;
      }
      debug("\n Restoring the FIX delays...\n\n");
      phy_restore_train_dly_csrs(mcu, (0x1U << iia), 1, 0, 0);
#endif
      fsm_init_seq =
          (1U << MCU_DDR_INIT_SEQ_WRLVLENAB_RNG) |
          (0U << MCU_DDR_INIT_SEQ_GATEENAB_RNG)
          | (0U << MCU_DDR_INIT_SEQ_RDLVLENAB_RNG);
      mcu->mcu_wr(mcu, MCU_REG_DDR_INIT_SEQ, fsm_init_seq);
      mcu->mcu_wr(mcu, MCU_REG_PHY_CSR_LVL_RANK_SEL, iia);  // MCU_PHY_CSR_LVL_RANK_SEL_RANK_NUM_RNG 2:0
      debug
          ("MCU%d :: #### start PEVM train WrLvl only for  rank=%01d\n",
           mcu->id, iia);
      mcu->mcu_wr(mcu, MCU_REG_DDR_INIT_CTL, fsm_init_ctl); // Kick off FSM

      DELAY(5); // FSM runs ~15-30us
      mcu_reset_FSM_poll(mcu, MCU_RESET_FSM_stRESTART,
             POLL_EQUAL);
      // Look for training errors & copy delay values before WrCal & deskew
      err0 += mcu_check_phy_trainerr(ptr, 0);
      phy_save_train_dly_csrs(ptr);
      mcu_phy_rdfifo_reset(ptr);

      // Restore MR1 & MR2
      mcu->mcu_wr(mcu, MCU_REG_MRS_1_VALUE, mr1val);
      mcu->mcu_wr(mcu, MCU_REG_MRS_2_VALUE, mr2val);
      fsm_init_seq = (1U << MCU_DDR_INIT_SEQ_MRENAB_RNG);
      mcu->mcu_wr(mcu, MCU_REG_DDR_INIT_SEQ, fsm_init_seq);
      mcu->mcu_wr(mcu, MCU_REG_DDR_INIT_CTL, fsm_init_ctl); // Kick off FSM

#ifdef FIX_WRLVL_BACKOFF
      /*
       *  AUTOFIX: WR leveling (lvl -= min_samples)
       */
      for (slice = 0; slice < PHY_SUPPORTED_LANES * 2;
           slice++) {
        if (!
            ((mcu->phy_params.
              cfg_macro_en_val >> slice) & 0x1))
          continue;
        olddelay =
            mcu->phy_tr_dly.rank_dly[iia].wr_lvl[slice];
        if (olddelay > mcu->phy_tr_dly.wrlvl_min_smpl) {
#ifdef FIX_WRLVL_BACKOFF_NOTFULL
          // Full backoff might put WR-LVL in uncertain window
          //  (2/3'rd backoff is prefered at the cost of loss of margin)
          mcu->phy_tr_dly.rank_dly[iia].
              wr_lvl[slice] -=
              ((mcu->phy_tr_dly.
                wrlvl_min_smpl) *
               FIX_WRLVL_BACKOFF_MVALUE) /
              FIX_WRLVL_BACKOFF_DVALUE;
#else
          mcu->phy_tr_dly.rank_dly[iia].
              wr_lvl[slice] -=
              mcu->phy_tr_dly.wrlvl_min_smpl;
#endif
#ifdef FIX_WRLVL_BIT8_BEFOREWRCAL
          // Set all WR-LVL as 0x1XX to avoid WR-CAL problem
          //  (WR-CAL migh be off by 1clk between two ranks, when CLK & DQS are alighed)
          mcu->phy_tr_dly.rank_dly[iia].
              wr_lvl[slice] |= 0x100;
#endif
          debug
              ("\t\t Correcting WR-LVL RANK[%d]-Macro[%d]: 0x%x [old:0x%x]\n",
               iia, slice,
               mcu->phy_tr_dly.
               rank_dly[iia].
               wr_lvl[slice], olddelay);
        }

      }
      debug("\n Restoring the Auto Fixed delays...\n\n");
      phy_restore_train_dly_csrs(mcu, (0x1U << iia), 1, 0, 0);
#endif
      /*
       *  FIX: WR leveling
       */
      if (mcu->phy_tr_dly.fix_wrlvl_flg) {
        debug
            ("\n\nMCU[%d] - FIXING WR Leveling values for all macros:\n",
             mcu->id);
        for (slice = 0;
             slice < PHY_SUPPORTED_LANES * 2; slice++) {
          if (!
              ((mcu->phy_params.
                cfg_macro_en_val >> slice)
               & 0x1))
            continue;
          mcu->phy_tr_dly.rank_dly[iia].
              wr_lvl[slice] =
              mcu->phy_tr_dly.
              rank_dly[iia].fix_wr_lvl[slice];
        }
        debug("\n Restoring the FIX delays...\n\n");
        phy_restore_train_dly_csrs(mcu,
                 (0x1U <<
                  iia), 1, 0, 0);
        mcu_phy_rdfifo_reset(ptr);

        debug("\n Disabling WR-CAL...\n");
        mcu->phy_tr_dly.phy_wrcal_rank_mask &=
            ~(0x1 << iia);
      }

      /*
       *  PEVM: RDG leveling
       */
      mcu_reset_FSM_poll(mcu, MCU_RESET_FSM_stRESTART,
             POLL_EQUAL);
      if (MCU_PHY_EARLY_RDGATELVL_ENAB) {
//                      if (early_rdg) {}
        mcu_set_SWISS_TRNCTL(mcu, 1 /*enab */ , 0 /*wrlvl_en */
                 , 1 /*rdlvl_gate_en */ , 0 /*rdlvl_en */
                 , 0xFF /*wrlvl_cs_n[7:0]= 'hFF */
                 , ((~(0x1U << iia)) & 0xFF)  /*rdlvl_cs_n[7:0]= 'hFF */
            );
      }
      fsm_init_seq =
          (0U << MCU_DDR_INIT_SEQ_WRLVLENAB_RNG) |
          (1U << MCU_DDR_INIT_SEQ_GATEENAB_RNG) |
          (0U << MCU_DDR_INIT_SEQ_RDLVLENAB_RNG);
      mcu->mcu_wr(mcu, MCU_REG_DDR_INIT_SEQ, fsm_init_seq);
      mcu->mcu_wr(mcu, MCU_REG_PHY_CSR_LVL_RANK_SEL, iia);  // MCU_PHY_CSR_LVL_RANK_SEL_RANK_NUM_RNG 2:0
      debug
          ("MCU%d :: #### start PEVM train  GtLvl only  for  rank=%01d\n",
           mcu->id, iia);
      mcu->mcu_wr(mcu, MCU_REG_DDR_INIT_CTL, fsm_init_ctl); // Kick off FSM
      if (MCU_PHY_EARLY_RDGATELVL_ENAB) {
//                      if (early_rdg) {}
        mcu_set_SWISS_TRNCTL(mcu, 0 /*enab */ , 0 /*wrlvl_en */
                 , 0 /*rdlvl_gate_en */ , 0 /*rdlvl_en */
                 , 0xFF /*wrlvl_cs_n  [7:0]= 'hFF */
                 , 0xFF /*rdlvl_cs_n [7:0]= 'hFF */
            );
      }

      DELAY(10);  // FSM runs ~15-30us
      mcu_reset_FSM_poll(mcu, MCU_RESET_FSM_stRESTART,
             POLL_EQUAL);
      // Look for training errors & possibly copy delay values before WrCal & deskew
      err1 = mcu_check_phy_trainerr(ptr, 0);
      phy_save_train_dly_csrs(ptr);
      mcu_phy_rdfifo_reset(ptr);

      if (err1)
        debug
            ("\nPHY[%d] *** PEVM-RDG leveling ERROR: %d ***\n",
             mcu->id, err1);

      /*
       *  FIX: RDG leveling
       */
      if (mcu->phy_tr_dly.fix_gtlvl_flg) {
        debug
            ("\n\nMCU[%d] - FIXING RDG Leveling values for all macros:\n",
             mcu->id);
        for (slice = 0;
             slice < PHY_SUPPORTED_LANES * 2; slice++) {
          if (!
              ((mcu->phy_params.
                cfg_macro_en_val >> slice)
               & 0x1))
            continue;
          mcu->phy_tr_dly.rank_dly[iia].
              gt_lvl[slice] =
              mcu->phy_tr_dly.
              rank_dly[iia].fix_gt_lvl[slice];
        }
        debug("\n Restoring the FIX delays...\n\n");
        phy_restore_train_dly_csrs(mcu,
                 (0x1U <<
                  iia), 0, 1, 0);
        mcu_phy_rdfifo_reset(ptr);
      }

      /*
       *  FIX: RDG Read-Enable delay
       */
      rddata =
          phy_read_reg(mcu, PHY_REG_CFG_DELAY_FROM_RD_EN);
      rddata &= ~(0x7);
      rddata |= KCPHY_FIXED_READEN_DELAY;
      debug("PHY[%d] Setting FIXED RDEN: 0x%x\n\n",
            mcu->id, rddata);
      phy_write_reg(mcu, PHY_REG_CFG_DELAY_FROM_RD_EN,
              rddata);

      /*
       *  PEVM: RDE leveling
       */
#ifdef FIX_DEFAULT_RDE
      // Set default/start value as 0x20 .. and then back-off by 0x10
      debug
          ("\n\nMCU[%d] - FIXING DEFAULT RDE Leveling values for all macros (Before PEVM-RDEYE):\n",
           mcu->id);
      for (slice = 0; slice < PHY_SUPPORTED_LANES * 2;
           slice++) {
        if (!
            ((mcu->phy_params.
              cfg_macro_en_val >> slice) & 0x1))
          continue;
        mcu->phy_tr_dly.rank_dly[iia].
            rd_lvl[slice] = DEFAULT_RDEYE_VALUE;
      }
      debug("\n Restoring the FIX delays...\n\n");
      phy_restore_train_dly_csrs(mcu, (0x1U << iia), 0, 0, 1);
#endif
      if (MCU_PHY_EARLY_RDGATELVL_ENAB) {
//                      if (early_rdg) {}
        mcu_set_SWISS_TRNCTL(mcu, 1 /*enab */ , 0 /*wrlvl_en */
                 , 0 /*rdlvl_gate_en */ , 1 /*rdlvl_en */
                 , 0xFF /*wrlvl_cs_n[7:0]= 'hFF */
                 , ((~(0x1U << iia)) & 0xFF)  /*rdlvl_cs_n[7:0]= 'hFF */
            );
      }

      fsm_init_seq =
          (0U << MCU_DDR_INIT_SEQ_WRLVLENAB_RNG) |
          (0U << MCU_DDR_INIT_SEQ_GATEENAB_RNG) |
          (1U << MCU_DDR_INIT_SEQ_RDLVLENAB_RNG);
      mcu->mcu_wr(mcu, MCU_REG_DDR_INIT_SEQ, fsm_init_seq);
      mcu->mcu_wr(mcu, MCU_REG_PHY_CSR_LVL_RANK_SEL, iia);  // MCU_PHY_CSR_LVL_RANK_SEL_RANK_NUM_RNG 2:0
      debug
          ("MCU%d :: #### start PEVM train  RdLvl only  for  rank=%01d\n",
           mcu->id, iia);
      mcu->mcu_wr(mcu, MCU_REG_DDR_INIT_CTL, fsm_init_ctl); // Kick off FSM
      if (MCU_PHY_EARLY_RDGATELVL_ENAB) {
//                      if (early_rdg) {}
        mcu_set_SWISS_TRNCTL(mcu, 0 /*enab */ , 0 /*wrlvl_en */
                 , 0 /*rdlvl_gate_en */ , 0 /*rdlvl_en */
                 , 0xFF /*wrlvl_cs_n  [7:0]= 'hFF */
                 , 0xFF /*rdlvl_cs_n [7:0]= 'hFF */
            );
      }

      DELAY(5); // FSM runs ~15-30us
      mcu_reset_FSM_poll(mcu, MCU_RESET_FSM_stRESTART,
             POLL_EQUAL);
      // Look for training errors & possibly copy delay values before WrCal & deskew
      err1 = mcu_check_phy_trainerr(ptr, 0);
      phy_save_train_dly_csrs(ptr);

      if (err1)
        debug
            ("\nPHY[%d] *** PEVM-RDE leveling ERROR: %d ***\n",
             mcu->id, err1);
#ifdef FIX_DEFAULT_RDE
      /*
       *  AUTOFIX: Back-Off RDE based on default value [new-lvl -= (default-reg-value)/2]
       */
      for (slice = 0; slice < PHY_SUPPORTED_LANES * 2;
           slice++) {
        if (!
            ((mcu->phy_params.
              cfg_macro_en_val >> slice) & 0x1))
          continue;
        olddelay =
            mcu->phy_tr_dly.rank_dly[iia].rd_lvl[slice];
        if (olddelay > (DEFAULT_RDEYE_VALUE / 2)) {
          mcu->phy_tr_dly.rank_dly[iia].
              rd_lvl[slice] -=
              (DEFAULT_RDEYE_VALUE / 2);
          debug
              ("\t\t Correcting RDE-LVL RANK[%d]-Macro[%d]: 0x%x [old:0x%x]\n",
               iia, slice,
               mcu->phy_tr_dly.
               rank_dly[iia].
               rd_lvl[slice], olddelay);
        }

      }
      debug("\n Restoring the Auto Fixed delays...\n\n");
      phy_restore_train_dly_csrs(mcu, (0x1U << iia), 0, 0, 1);
      mcu_phy_rdfifo_reset(ptr);

#endif
      //Check/Fix broken RDE based on FIX_BROKEN_RDEYE_PERMACRO
      err0 += phy_correct_rdeye_delays(ptr, iia);

      phy_save_train_dly_csrs(ptr);
      mcu_phy_rdfifo_reset(ptr);

      /*
       *  FIX: RDE leveling
       */
      if (mcu->phy_tr_dly.fix_rdlvl_flg) {
        debug
            ("\n\nMCU[%d] - FIXING RDE Leveling values for all macros:\n",
             mcu->id);
        for (slice = 0;
             slice < PHY_SUPPORTED_LANES * 2; slice++) {
          if (!
              ((mcu->phy_params.
                cfg_macro_en_val >> slice)
               & 0x1))
            continue;
          mcu->phy_tr_dly.rank_dly[iia].
              rd_lvl[slice] =
              mcu->phy_tr_dly.
              rank_dly[iia].fix_rd_lvl[slice];
        }
        debug("\n Restoring the FIX delays...\n\n");
        phy_restore_train_dly_csrs(mcu,
                 (0x1U <<
                  iia), 0, 0, 1);
        mcu_phy_rdfifo_reset(ptr);
      }

      /*
       *  AUTOFIX: RDG leveling (pull/push rdg-lvl based on rdg+rde)
       */
      debug
          ("\n\nMCU[%d] - AUTO-FIXING RDG Leveling values for all macros:\n",
           mcu->id);
      for (slice = 0; slice < PHY_SUPPORTED_LANES * 2;
           slice++) {
        if (!
            ((mcu->phy_params.
              cfg_macro_en_val >> slice) & 0x1))
          continue;
        olddelay =
            mcu->phy_tr_dly.rank_dly[iia].gt_lvl[slice];
        sumdelay =
            (mcu->phy_tr_dly.rank_dly[iia].
             gt_lvl[slice] & 0xFF) +
            mcu->phy_tr_dly.rank_dly[iia].rd_lvl[slice];
        if ((sumdelay > 0x60)
            && (sumdelay <= 0x70)) {
          mcu->phy_tr_dly.rank_dly[iia].
              gt_lvl[slice] -= 0x10;
          debug
              ("\t\tRANK[%d]-MACRO[%d] AutoFix RDG-delay: 0x%x [0x%x(fr)+0x%x=0x%x 0x60-0x70]\n",
               iia, slice,
               mcu->phy_tr_dly.
               rank_dly[iia].
               gt_lvl[slice], olddelay,
               mcu->phy_tr_dly.
               rank_dly[iia].
               rd_lvl[slice], sumdelay);
        } else if ((sumdelay > 0x70)
             && (sumdelay <= 0x80)) {
          mcu->phy_tr_dly.rank_dly[iia].
              gt_lvl[slice] -= 0x20;
          debug
              ("\t\tRANK[%d]-MACRO[%d] AutoFix RDG-delay: 0x%x [0x%x(fr)+0x%x=0x%x 0x70-0x80]\n",
               iia, slice,
               mcu->phy_tr_dly.
               rank_dly[iia].
               gt_lvl[slice], olddelay,
               mcu->phy_tr_dly.
               rank_dly[iia].
               rd_lvl[slice], sumdelay);
        } else if ((sumdelay > 0x80)
             && (sumdelay <= 0x90)) {
          mcu->phy_tr_dly.rank_dly[iia].
              gt_lvl[slice] += 0x18;
          debug
              ("\t\tRANK[%d]-MACRO[%d] AutoFix RDG-delay: 0x%x [0x%x(fr)+0x%x=0x%x 0x80-0x90]\n",
               iia, slice,
               mcu->phy_tr_dly.
               rank_dly[iia].
               gt_lvl[slice], olddelay,
               mcu->phy_tr_dly.
               rank_dly[iia].
               rd_lvl[slice], sumdelay);
        } else if ((sumdelay > 0x90)
             && (sumdelay <= 0x98)) {
          mcu->phy_tr_dly.rank_dly[iia].
              gt_lvl[slice] += 0x8;
          debug
              ("\t\tRANK[%d]-MACRO[%d] AutoFix RDG-delay: 0x%x [0x%x(fr)+0x%x=0x%x 0x90-0x98]\n",
               iia, slice,
               mcu->phy_tr_dly.
               rank_dly[iia].
               gt_lvl[slice], olddelay,
               mcu->phy_tr_dly.
               rank_dly[iia].
               rd_lvl[slice], sumdelay);
        } else {
          debug
              ("\t\tRANK[%d]-MACRO[%d] HW-RDG-delay: 0x%x    [+0x%x=0x%x] \n",
               iia, slice,
               mcu->phy_tr_dly.
               rank_dly[iia].
               gt_lvl[slice],
               mcu->phy_tr_dly.
               rank_dly[iia].
               rd_lvl[slice], sumdelay);
        }
      }
      debug("\n Restoring the Auto Fixed delays...\n\n");
      phy_restore_train_dly_csrs(mcu, (0x1U << iia), 0, 1, 0);
      mcu_phy_rdfifo_reset(ptr);

      /*
       *  PEVM: WR-CAL, WR-Deskew, RD-Deskew & 2nd RD lvl
       */
      // PHY Write Calibration required
      // (optional) PHY Deskew and 2nd Rd lvl
      // check with KC on recommendations (only do middle rank for now - long ~50 us total)
      if ((mcu->phy_tr_dly.sw_wrcal_rank_mask >> iia) & 0x1) {
        debug("\n\n WR-CAL sw[%d]\n\n",
              mcu->phy_tr_dly.sw_wrcal_rank_mask);
        err0 += kc_phy_sw_wrcal_deskew(ptr, iia, 1);
      }
      if (((mcu->phy_tr_dly.phy_wrcal_rank_mask >> iia) & 0x1)
          ||
          ((mcu->phy_tr_dly.rddeskew_rank_mask >> iia) & 0x1)
          ||
          ((mcu->phy_tr_dly.rdlvl2nd_rank_mask >> iia) & 0x1)
          ||
          ((mcu->phy_tr_dly.
            wrdeskew_rank_mask >> iia) & 0x1)) {
        debug
            ("\n\n WR-CAL phy[%d], rddeskew[%d], 2ndlvl[%d], wrdeskew [%d] (rank %d)\n\n",
             mcu->phy_tr_dly.
             phy_wrcal_rank_mask,
             mcu->phy_tr_dly.rddeskew_rank_mask,
             mcu->phy_tr_dly.rdlvl2nd_rank_mask,
             mcu->phy_tr_dly.wrdeskew_rank_mask, iia);
        err0 += kc_phy_wrcal_deskew(ptr, iia, 1);
      }
      phy_save_train_dly_csrs(ptr);
      mcu_phy_rdfifo_reset(ptr);
    }
  }
  rddata = phy_read_reg(mcu, PHY_REG_CFG_DELAY_FROM_RD_EN);
  /*
   * Toggle lvl_load signals : MCU TRAIN Wr Rd Load
   *   enables PHY to use restored Tr Delay CSRs
   */
  phy_rf_write_cfg_read_w_fixed_delay(ptr, KCPHY_USE_READ_W_FIXED_DELAY);

  mcu_reset_FSM_poll(mcu, MCU_RESET_FSM_stRESTART, POLL_EQUAL);
  mcu_set_SWISS_TRNLOAD(mcu);

  mcu_phy_rdfifo_reset(ptr);

  /*
   * Save off training delays (optional for driver)
   */
  phy_save_train_dly_csrs(ptr);
  phy_save_wrdq_dly_csrs(ptr);
  phy_save_rddsk_dly_csrs(ptr);
  phy_save_wrdsk_dly_csrs(ptr);
  phy_display_post_train_csrs(ptr, mcu->phy_tr_dly.rank_mask);

#ifdef CLEAR_WRDESKEW_TRIM
  /*
   * Clear WR-DESKEW trim values (WR-DESKEW use used only to adjust DQ-DQS delay)
   */
  phy_clear_wrdsk_dly_csrs(ptr);
#endif

  return err0;
}       // calib_pevm_seperate_steps

//==================================================================
//==================================================================
int retrain_pevm_sep_steps(void *ptr)
{
  // PHY PEVM training for all lanes and ranks
  //
  int unsigned jjb, iia = 0;
  int err0 = 0;
  int unsigned fsm_init_seq = 0;
  int unsigned fsm_init_ctl = 0;
  int unsigned mr2val, wdata, disDynOdt;
  int unsigned __attribute__ ((unused)) rddata;
  struct apm_mcu *mcu = (struct apm_mcu *)ptr;
  if (!mcu->enabled) {
    return 0;
  }
  // Do ZQC & Phy Ctrl Update and stack Refreshes to all ranks

  fsm_init_ctl =
      (1U << MCU_DDR_INIT_CTL_CALIBGO_RNG) |
      ((0x4U & 0xFU) << MCU_DDR_INIT_CTL_RCWAIT_RNG) |
      ((0x5U & 0x7U) << MCU_DDR_INIT_CTL_REFRESHCNT_RNG);
  fsm_init_seq =
      (1U << MCU_DDR_INIT_SEQ_PREREFRESHENAB_RNG) |
      (1U << MCU_DDR_INIT_SEQ_ZQCLENAB_RNG) |
      (DO_INIT_SEQ_CTLUPDATE << MCU_DDR_INIT_SEQ_CTLUPDATE_RNG) |
      (1U << MCU_DDR_INIT_SEQ_SETMEMINITDONE_RNG);

  /*
   * Already done -- setup MCU Training FSM CSRs
   */

  fsm_init_ctl =
      (1U << MCU_DDR_INIT_CTL_CALIBGO_RNG) |
      ((0x4U & 0xFU) << MCU_DDR_INIT_CTL_RCWAIT_RNG) |
      ((0x4U & 0x7U) << MCU_DDR_INIT_CTL_REFRESHCNT_RNG);

  /*
   * Retrain per rank - set MemInitDone after every step
   * Combine Gate & Rd Level training
   *   - no WrCal or Deskew
   */
  for (iia = 0; iia < MCU_SUPPORTED_RANKS; iia++) {
    if ((mcu->phy_tr_dly.rank_mask >> iia) & 0x1) {

      disDynOdt = PHY_PEVM_RETRAIN_DIS_DYNODT;
      // Delete old values

      if (PHY_PEVM_RETRAIN_WRLVL_EN) {
        // Must turn off MR2 dynamic odt before WrLvl
        //  ?? can we allow traffic to flow again with it off ??
        debug
            ("MCU%d :: #### start PEVM retrain WrLvl only for  rank=%01d\n",
             mcu->id, iia);
        if (PHY_PEVM_RETRAIN_DIS_DYNODT) {
          mr2val =
              mcu->mcu_rd(mcu,
              MCU_REG_MRS_2_VALUE);
          disDynOdt = (mr2val & 0x600) ? 1 : 0;
          wdata = mr2val & 0xFFFFF9FF;
          if (disDynOdt)
            mcu->mcu_wr(mcu,
                  MCU_REG_MRS_2_VALUE,
                  wdata);
        }
        // MCU_PHY_CSR_LVL_RANK_SEL_RANK_NUM_RNG 2:
        mcu->phy_wr(mcu,
              PHY_REG_CFG_RETRAIN_ENABLE, 0x4);
        DELAY(5);
        mcu->mcu_wr(mcu,
              MCU_REG_PHY_CSR_LVL_RANK_SEL, iia);
        mcu_reset_FSM_poll(mcu,
               MCU_RESET_FSM_stRESTART,
               POLL_EQUAL);
        fsm_init_seq =
            (1U << MCU_DDR_INIT_SEQ_PREREFRESHENAB_RNG)
            | (disDynOdt << MCU_DDR_INIT_SEQ_MRENAB_RNG)
            | (1U <<
               MCU_DDR_INIT_SEQ_TXPRENAB_RNG) |
            (1U <<
             MCU_DDR_INIT_SEQ_WRLVLENAB_RNG) |
            (0U << MCU_DDR_INIT_SEQ_SETMEMINITDONE_RNG);
        mcu->mcu_wr(mcu, MCU_REG_DDR_INIT_SEQ,
              fsm_init_seq);
        mcu->mcu_wr(mcu, MCU_REG_DDR_INIT_CTL, fsm_init_ctl); // Kick off FSM

        mcu_reset_FSM_poll(mcu,
               MCU_RESET_FSM_stRESTART,
               POLL_EQUAL);
        // Look for training errors & possibly copy delay values before WrCal & deskew
        err0 += mcu_check_phy_trainerr(ptr, 0);
        //phy_save_train_dly_csrs(ptr);

        if (disDynOdt) {
          // Restore MR2
          mcu->mcu_wr(mcu,
                MCU_REG_MRS_2_VALUE,
                mr2val);
          fsm_init_seq =
              (1U << MCU_DDR_INIT_SEQ_MRENAB_RNG)
              | (0U <<
                 MCU_DDR_INIT_SEQ_SETMEMINITDONE_RNG);
          mcu->mcu_wr(mcu,
                MCU_REG_DDR_INIT_SEQ,
                fsm_init_seq);
          mcu->mcu_wr(mcu, MCU_REG_DDR_INIT_CTL, fsm_init_ctl); // Kick off FSM
          mcu_reset_FSM_poll(mcu,
                 MCU_RESET_FSM_stRESTART,
                 POLL_EQUAL);
        }
        mcu->phy_wr(mcu,
              PHY_REG_CFG_RETRAIN_ENABLE, 0x0);
        DELAY(5);
      }
      if (PHY_PEVM_RETRAIN_GTLVL_EN) {
        for (jjb = 0; jjb < PHY_SUPPORTED_LANES; jjb++) {
          mcu->phy_tr_dly.rank_dly[iia].
              gt_lvl[jjb * 2] = 0x100;
          mcu->phy_tr_dly.rank_dly[iia].
              gt_lvl[jjb * 2 + 1] = 0x100;
        }
        phy_restore_train_dly_csrs(mcu,
                 (0x1U <<
                  iia), 0, 1, 0);
        mcu_set_SWISS_TRNLOAD(mcu);

        debug
            ("MCU%d :: #### start PEVM retrain  Gt Lvl  for  rank=%01d\n",
             mcu->id, iia);

        fsm_init_seq =
            (1U << MCU_DDR_INIT_SEQ_PREREFRESHENAB_RNG)
            | (1U <<
               MCU_DDR_INIT_SEQ_TXPRENAB_RNG) |
            (1U <<
             MCU_DDR_INIT_SEQ_GATEENAB_RNG) |
            (1U << MCU_DDR_INIT_SEQ_SETMEMINITDONE_RNG);
        // mcu->phy_wr(mcu, PHY_REG_CFG_RETRAIN_ENABLE, 0x1);
        DELAY(5);
        mcu->mcu_wr(mcu, MCU_REG_DDR_INIT_SEQ,
              fsm_init_seq);
        mcu->mcu_wr(mcu, MCU_REG_DDR_INIT_CTL, fsm_init_ctl); // Kick off FSM

        DELAY(3); // FSM runs ~15-30us
        mcu_reset_FSM_poll(mcu,
               MCU_RESET_FSM_stRESTART,
               POLL_EQUAL);
        // Look for training errors & possibly copy delay values before WrCal & deskew
        err0 += mcu_check_phy_trainerr(ptr, 0);
        mcu->phy_wr(mcu,
              PHY_REG_CFG_RETRAIN_ENABLE, 0x0);
        DELAY(5);
      }
      if (PHY_PEVM_RETRAIN_RDLVL_EN) {
        for (jjb = 0; jjb < PHY_SUPPORTED_LANES; jjb++) {
          mcu->phy_tr_dly.rank_dly[iia].
              rd_lvl[jjb * 2] = 0x10;
          mcu->phy_tr_dly.rank_dly[iia].
              rd_lvl[jjb * 2 + 1] = 0x10;
        }
        phy_restore_train_dly_csrs(mcu,
                 (0x1U <<
                  iia), 0, 0, 1);
        mcu_set_SWISS_TRNLOAD(mcu);

        debug
            ("MCU%d :: #### start PEVM retrain  Rd Lvl  for  rank=%01d\n",
             mcu->id, iia);
        fsm_init_seq =
            (1U << MCU_DDR_INIT_SEQ_PREREFRESHENAB_RNG)
            | (1U <<
               MCU_DDR_INIT_SEQ_TXPRENAB_RNG) |
            (1U <<
             MCU_DDR_INIT_SEQ_RDLVLENAB_RNG) |
            (1U << MCU_DDR_INIT_SEQ_SETMEMINITDONE_RNG);
        //mcu->phy_wr(mcu, PHY_REG_CFG_RETRAIN_ENABLE, 0x1);
        DELAY(5);
        mcu->mcu_wr(mcu, MCU_REG_DDR_INIT_SEQ,
              fsm_init_seq);
        mcu->mcu_wr(mcu, MCU_REG_DDR_INIT_CTL, fsm_init_ctl); // Kick off FSM

        DELAY(3); // FSM runs ~15-30us
        mcu_reset_FSM_poll(mcu,
               MCU_RESET_FSM_stRESTART,
               POLL_EQUAL);
        // Look for training errors & possibly copy delay values before WrCal & deskew
        err0 += mcu_check_phy_trainerr(ptr, 0);
        mcu->phy_wr(mcu,
              PHY_REG_CFG_RETRAIN_ENABLE, 0x0);
        DELAY(5);
      }
    }
    mcu->phy_wr(mcu, PHY_REG_CFG_RETRAIN_ENABLE, 0x0);
    mcu_phy_rdfifo_reset(ptr);
    // WrCal needs to be redone
    if ((mcu->phy_tr_dly.sw_wrcal_rank_mask >> iia) & 0x1) {
      debug("\n\n WR-CAL sw[%d]\n\n",
            mcu->phy_tr_dly.sw_wrcal_rank_mask);
      err0 += kc_phy_sw_wrcal_deskew(ptr, iia, 1);
    }
    if (((mcu->phy_tr_dly.phy_wrcal_rank_mask >> iia) & 0x1)) {
      debug
          ("\n\n WR-CAL phy[%d], rddeskew[%d], 2ndlvl[%d], wrdeskew [%d] (rank %d)\n\n",
           mcu->phy_tr_dly.phy_wrcal_rank_mask,
           mcu->phy_tr_dly.rddeskew_rank_mask,
           mcu->phy_tr_dly.rdlvl2nd_rank_mask,
           mcu->phy_tr_dly.wrdeskew_rank_mask, iia);
      //mcu->phy_wr(mcu, PHY_REG_CFG_RETRAIN_ENABLE, 0x8);
      err0 += kc_phy_wrcal_deskew(ptr, iia, 1);
    }
    phy_save_train_dly_csrs(ptr);

  }

  mcu->phy_wr(mcu, PHY_REG_CFG_RETRAIN_ENABLE, 0x0);
  /*
   * Save off training delays (optional for driver)
   */
  phy_save_train_dly_csrs(ptr);
  phy_display_post_train_csrs(ptr, mcu->phy_tr_dly.rank_mask);

  return err0;
}       // retrain_pevm_sep_steps

//==================================================================
//==================================================================
//==================================================================
//==================================================================

int mcu_kc_phy_setup_org(void *ptr)
{
  // Original KC PHY setup/init routine
  // TBD replaced due to code size
  //
  int unsigned __attribute__ ((unused)) dat;
  struct apm_mcu *mcu = (struct apm_mcu *)ptr;
  phy_param_t *p_phy = &mcu->phy_params;
  int unsigned en_dll_cal = p_phy->en_phy_dll_cal;
  int unsigned lo_freq = p_phy->dll_cal_lo_freq;

  // KC PHY setup routine -
  debug
      ("Mcu PHY %1d  initial DCR config starting... x4=%1d ",
       mcu->id, mcu->mcu_params.by4_mode);
  debug("dllcal=%1d lofreq=%1d \n", en_dll_cal, lo_freq);
  kc_phy_timing_param_setup(ptr);

  kc_phy_pre_dfi_reset(ptr);  // CDR reset & lock

  kc_phy_init_before_train(ptr);
  //JHR added KC new in again
  kc_phy_quick_setup(ptr);

  if (en_dll_cal) {
    debug
        ("MCU-PHY %d: INFO: Enable DLL Cal: lo-freq0x%01d\n",
         mcu->id, lo_freq);
    kc_phy_dll_prog_quad_wt_steps(ptr, lo_freq);  // step 11 - set 1 if Freq 1066 MHz or lower
  } else {
    debug("MCU-PHY %d: WARNING: DLL Cal not enabled\n", mcu->id);
  }

  kc_phy_en180_cal_addrmacro(ptr);  // step 12

  kc_phy_drv_strength_slew_setup(ptr);  // from Python routines

  dat = phy_rf_read_dqs_weak_pull_down_disable(ptr);  // Read value to check
  // JHR value 0x0 by default - weak pull down on
  if (mcu->phy_params.phy_disable_pullup) {
    dat =
        (dat & 0xFFFFFFFE) | (0x1 & mcu->phy_params.
            phy_disable_pullup);
    phy_rf_write_dqs_weak_pull_down_disable(ptr, dat);
  }
  // Added 26sept2012 - added for R29 release
  phy_rf_write_cfg_timeout_counter(ptr, (0x7FF << 10));
  // same as below kc_phy_set_wrlvl_func(ptr, 1);   // set WrLvl OR gate
  dat = phy_rf_read_spare_register_1_0(ptr);
  dat = (dat & 0xFFFFFFFC) | (0x2);
  // JHR bit 0 must be 0 in 1:1 mode !!!DUHHHHHHHHHH!!
  phy_rf_write_spare_register_1_0(ptr, dat);  // Wr Lvl OR gate
  debug
      ("Mcu PHY  initial DCR configuration finished. Ready for dfi_init_start...\n");

  /* JHR 2/28/13 - PHY change Rd/Wr Preamble length
     3 registers reduce gate preamble from 180 (0x80808080) degree to 90 degree (0x40404040).
     i2c_write_CFG_GATE_PRE_VAL_3(0x40)
     i2c_write_CFG_GATE_PRE_VAL_1(0x40404040)
     i2c_write_CFG_GATE_PRE_VAL_2(0x40404040)
   */
  if (p_phy->phy_short_gt_preamble_en != 0) {
    dat = mcu->phy_params.phy_short_gt_preamble_val;
    mcu->phy_wr(mcu, PHY_REG_CFG_GATE_PRE_VAL_3, dat);
    dat = ((dat & 0xFF) << 24) |
        ((dat & 0xFF) << 16) | ((dat & 0xFF) << 8) | ((dat & 0xFF));
    mcu->phy_wr(mcu, PHY_REG_CFG_GATE_PRE_VAL_1, dat);
    mcu->phy_wr(mcu, PHY_REG_CFG_GATE_PRE_VAL_2, dat);
  }
  return 0;
}

