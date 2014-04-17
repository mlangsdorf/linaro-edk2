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
 **/

#if DDRLIB_DEBUGON
#define DEBUG
#define DEBUG_REGMOD
#endif

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

#include "ddr_lib.h"
#include "ddr_mcu.h"
#include "kc_phy_util_reg_flds.h"

/*
	   def kc_io_strength_setup(dq_stren,ad_stren,cmd_stren,ctl_stren,clk_stren,odt_stren):
	   BIT_DQ_STREN = cfg_drv_stren_array[dq_stren]
	   BIT_AD_STREN = cfg_drv_AdCmdCtlClk_stren_array[ad_stren]
	   BIT_CMD_STREN = cfg_drv_AdCmdCtlClk_stren_array[cmd_stren]
	   BIT_CTL_STREN = cfg_drv_AdCmdCtlClk_stren_array[ctl_stren]
	   BIT_CLK_STREN = cfg_drv_AdCmdCtlClk_stren_array[ctl_stren]
	   BIT_ODT_STREN = cfg_odt_stren[odt_stren] 

	   cfg_drv_stren_array = {"OFF":0x0,  
	   53:0x1,  
	   48:0x2,
	   44:0x3,
	   40:0x4,
	   37:0x5,
	   34:0x6,
	   32:0x7}
	   cfg_drv_AdCmdCtlClk_stren_array = {"OFF":0x0,
	   48:0x1,
	   40:0x2,
	   34:0x3,
	   30:0x4,
	   20:0x5,
	   17:0x6,
	   16:0x7}
	   cfg_odt_stren = {"OFF":0x0,
	   240:0x1,
	   120:0x2,
	   80:0x3,
	   60:0x4,
	   30:0x5,
	   21:0x6,
	   20:0x7}
	 */

	//   #kc_io_strength_setup(40,16,16,16,16,80)
	//   kc_io_slew_setup(0x2,0x2,0x2,0x2,0x3)
	/*
	   kc_io_slew_setup(dq_slew,ad_slew,cmd_slew,ctl_slew,clk_slew):
	   BIT_DQ_SLEW =  dq_slew
	   BIT_AD_SLEW = ad_slew
	   BIT_CMD_SLEW = cmd_slew
	   BIT_CTL_SLEW = ctl_slew
	   BIT_CLK_SLEW = clk_slew
	 */

/******************************************************************************
 *   KC PHY Tasks copied from KC Release and modified for RB
 *   /projects/svdc/vrelease/koolchip_phy/KC_T40G_D3_2G_R00_R16/verification/testbench/PHYReg_tasks.vh
 * - remove @(posedge regInfInst.clk);
 * - added input for x4
 * - seperated into two tasks
 *
 * - translated into C from SV from:
 *    potenza/MAIN/dv/lib/sv/seqs/rb/rb_mcu_kc_reg_tasks.svh#11
 *****************************************************************************/

void kc_phy_timing_param_setup(void *ptr)
{
  // Normalize to DFI clocks
  struct apm_mcu *mcu = (struct apm_mcu *)ptr;
  int unsigned cmul = (mcu->mcu_params.single_clock_mode) ? 0 : 1;
  mcu->phy_params.WL = mcu->mcu_params.t_cwl + 1; //8;
  mcu->phy_params.RL = mcu->mcu_params.t_crl + 1; //10;
  mcu->phy_params.TRCD = (((mcu->mcu_params.bank_actrd << cmul) & 0xFF) > 16) ? ((mcu->mcu_params.bank_actrd << cmul) + 1) : 16;  // Act to Rd
  mcu->phy_params.TMOD = 16;
  mcu->phy_params.TMRD = 6;
  mcu->phy_params.TRP = (((mcu->mcu_params.bank_rdpre << cmul) & 0xFF) > 14) ? (mcu->mcu_params.bank_rdpre << cmul) : 14; // Rd to Pre
  mcu->phy_params.TWLMRD = 4; // Write Leveling DQS Delay. minimum time before first DQS
  mcu->phy_params.TWRD = (((mcu->mcu_params.rank_wrrd << cmul) & 0xFF) > 16) ? (mcu->mcu_params.rank_wrrd << cmul) : 16;  // Wr to Rd
  return;
}       // kc_phy_timing_param_setup

void kc_phy_set_wrlvl_func(void *ptr, int unsigned /*0 */ orfunc)
{
  int unsigned dat;
  // Set WrLvl function to 'OR' inside of KC PHY
  dat = phy_rf_read_spare_register_1_0(ptr);
  dat = (dat & 0xFFFFFFFD) | ((orfunc & 0x1) << 1); //dat[1] = orfunc;
  phy_rf_write_spare_register_1_0(ptr, dat);
}       // kc_phy_set_wrlvl_func

void kc_phy_post_train_cfg(void *ptr)
{
  phy_rf_write_cfg_delay_from_rden_0(ptr, PHY_INIT_DLY_FROM_RD_EN_VAL);
  phy_rf_write_cfg_delay_from_rden_1(ptr, PHY_INIT_DLY_FROM_RD_EN_VAL);
  phy_rf_write_cfg_delay_from_rden_2(ptr, PHY_INIT_DLY_FROM_RD_EN_VAL);
  phy_rf_write_cfg_delay_from_rden_3(ptr, PHY_INIT_DLY_FROM_RD_EN_VAL);
  phy_rf_write_cfg_delay_from_rden_4(ptr, PHY_INIT_DLY_FROM_RD_EN_VAL);
  phy_rf_write_cfg_delay_from_rden_5(ptr, PHY_INIT_DLY_FROM_RD_EN_VAL);
  phy_rf_write_cfg_delay_from_rden_6(ptr, PHY_INIT_DLY_FROM_RD_EN_VAL);
  phy_rf_write_cfg_delay_from_rden_7(ptr, PHY_INIT_DLY_FROM_RD_EN_VAL);
}       // kc_phy_post_train_cfg

void kc_phy_pre_dfi_reset(void *ptr)
{       //JHR added for CDR Lock
  // phloop_en
  struct apm_mcu *mcu = (struct apm_mcu *)ptr;
  unsigned int __attribute__ ((unused)) rddata = 0;
  unsigned int __attribute__ ((unused)) reg;

  phy_rf_write_cfg_dqxclk_cdr_phloop_en(ptr, 0);  // 0x108
  phy_rf_write_cfg_piclk_cdr_phloop_en(ptr, 0); // 0x108
  phy_rf_write_cfg_phyclk1x_cdr_phloop_en(ptr, 0);  // 0x108
  phy_rf_write_cfg_pcclk_cdr_phloop_en(ptr, 0); // 0x108
  phy_rf_write_cfg_mcclk_cdr_phloop_en(ptr, 0); // 0x108
  DELAY(2);   //
  phy_rf_write_cfg_dqxclk_cdr_lock_reset(ptr, 0); // 0x140
  phy_rf_write_cfg_piclk_cdr_lock_reset(ptr, 0);  // 0x140
  phy_rf_write_cfg_phyclk1x_cdr_lock_reset(ptr, 0); // 0x140
  phy_rf_write_cfg_pcclk_cdr_lock_reset(ptr, 0);  // 0x140
  phy_rf_write_cfg_mcclk_cdr_lock_reset(ptr, 0);  // 0x140
  DELAY(5);   //
  phy_rf_write_cfg_cdr_reset_b(ptr, 1);
  DELAY(5);   //
  phy_write_reg(mcu, PHY_REG_CFG_CDR_CONFIG, 0x3ec2); // 0x13c
  DELAY(5);   //
  phy_rf_write_cfg_dqxclk_cdr_phloop_en(ptr, 1);  // 0x108
  DELAY(5);   //
  phy_rf_write_cfg_piclk_cdr_phloop_en(ptr, 1); // 0x108
  DELAY(5);   //
  phy_rf_write_cfg_phyclk1x_cdr_phloop_en(ptr, 1);  // 0x108
  DELAY(5);   //
  phy_rf_write_cfg_pcclk_cdr_phloop_en(ptr, 1); // 0x108
  DELAY(5);   //
  phy_rf_write_cfg_mcclk_cdr_phloop_en(ptr, 1); // 0x108
  DELAY(5);
  // Poll for CDR lock
  /* phy_rf_read_cfg_dqxclk_cdr_lock(ptr, );
     phy_rf_read_cfg_piclk_cdr_lock(ptr, );
     phy_rf_read_cfg_phyclk1x_cdr_lock(ptr, );
     phy_rf_read_cfg_pcclk_cdr_lock(ptr, );
     phy_rf_read_cfg_mcclk_cdr_lock(ptr, ); */
  phy_poll_reg(ptr, PHY_REG_CFG_CDR_LOCK, 0x1F, 0x1F);  // 0x144
  // poll_KC_PHY_DCR(.addr(0x144), .data(0x1F), .mask(0x1F) );
  DELAY(2);   // JHR 1/29
  phy_poll_reg(ptr, PHY_REG_CFG_CDR_LOCK, 0x1F, 0x1F);  // JHR 1/29
  rddata = phy_read_reg(mcu, PHY_REG_CFG_ZQ_CAL_CODE);
  debug("MCU-PHY %d: INFO: ZQ Cal Code: 0x%0x\n", mcu->id, rddata);
  DELAY(2);

  reg = mcu->phy_rd(mcu, PHY_REG_CFG_PHY_SRST);
  reg &= 0xFFFFFFFC;
  mcu->phy_wr(mcu, PHY_REG_CFG_PHY_SRST, reg);
}       // kc_phy_pre_dfi_reset

void kc_phy_dll_prog_quad_wt_steps(void *ptr, int unsigned /*0 */ lofreq)
{
  int unsigned /*31:0 */ cal_done;
  int unsigned /*[3:0] */ this_macro;
  int unsigned /*[2:0] */ this_dll;
  int unsigned /**/ addr_cal_udone;
  struct apm_mcu __attribute__ ((unused)) * mcu = (struct apm_mcu *)ptr;

  // initial values
  phy_rf_write_cfg_dll_cal_en(ptr, 0);

  // wait for reset to release
  //while(~ top.KC_T40G_D3L3_2G_R00_inst.kc_PHYReg_Wrapper_inst.kc_dll_cal_inst.arst_n)
  //  repeat(1) @(posedge top.KC_T40G_D3L3_2G_R00_inst.kc_PHYReg_Wrapper_inst.kc_dll_cal_inst.clk);

  DELAY(5);   // #1ns;

  // Wait cycles between code change and dll status update
  phy_rf_write_cfg_wait_status_timer(ptr, 4);

  // This will will difine how many no. of over samples before dll code change
  phy_rf_write_cfg_cont_samples(ptr, 0x03);

  //There are 9 macros and 3 dll's per macro. one dll in the address macro. All
  //the dll's should be calibrated. The following routine defines the loop for
  //calibrating all the dll's
  // for macro 0 .. 9 // configure macro number cfg_macro_num[3:0]
  // for dll 0 .. 2   // configure cfg_dll_num[2:0]
  // repeat go/done
  // note: there is no dll1 and 2 for macro 9
  // low_frequency should be enaled for frequencies less than DDR_1600

  if (lofreq) {   //`ifdef DDR3_800 `elsif DDR_1066
    phy_rf_write_cfg_lowfrq_en(ptr, 0x3ff);
  } else {
    phy_rf_write_cfg_lowfrq_en(ptr, 0); //For other high frequencies, disable this bit
  }

  for (this_macro = 0; this_macro < 10; this_macro = this_macro + 1) {
    debug("MCU-PHY %d: DLL cal start macro %d of 9.......\n",
          mcu->id, this_macro);
    for (this_dll = 0; this_dll < 3; this_dll = this_dll + 1) {
      phy_rf_write_cfg_macro_num(ptr, this_macro);

      // map dlls properly
      // SDLL1 : 001 Write
      // SDLL2 : 010 Read x8 and x4
      // SDLL3 : 011 Read x4
      debug("MCU    DLL-Calib for MACRO[%d] DLL[%d]\n",
            this_macro, this_dll);
      switch (this_dll) {
      case 0:
        phy_rf_write_cfg_dll_num(ptr, 1);
        break;  //cfg_dll_num = 1;
      case 1:
        phy_rf_write_cfg_dll_num(ptr, 2);
        break;  //cfg_dll_num = 2;
      case 2:
        phy_rf_write_cfg_dll_num(ptr, 3);
        break;  //cfg_dll_num = 3;
      }
      if ((this_macro == 9) && (this_dll > 0)) {
      } else {
        // go
        phy_rf_write_cfg_dll_cal_en(ptr, 1);  //dll_cal_en = 1;
        DELAY(1);
        phy_rf_write_cfg_dll_cal_en(ptr, 0);  //dll_cal_en = 0;
        debug("MCU %d: Enable DLL Calib.......\n",
              mcu->id);

        debug("MCU %d: ...wait for cal done =0x%0X\n",
              mcu->id, cal_done);
        cal_done = phy_rf_read_cfg_dll_cal_done(ptr);
        while (cal_done == 0) {
          cal_done =
              phy_rf_read_cfg_dll_cal_done(ptr);
          DELAY(3);
        }
        debug("MCU %d: cal done (= 0x%0X)\n", mcu->id,
              cal_done);
      }
      phy_rf_write_cfg_dll_sft_rst(ptr, 1); //Soft Reset to reset the DLL internal signals before every enable
      DELAY(1);
      phy_rf_write_cfg_dll_sft_rst(ptr, 0); //Soft Reset to reset the DLL internal signals
    }   // for this dll

    //Peak Computation Logic Enable
    if (this_macro != 9) {
      phy_rf_write_cfg_macro_num_pi_addr_180_cal(ptr, this_macro);  //Write Macro number for peak computation
      phy_rf_write_cfg_enable_peak_computation(ptr, 1); //Flag to selecet peak computation logic
      phy_rf_write_cfg_addr_cal_en(ptr, 1); //Enabling the address calibration block //Enable is auto cleared upon addr_cal_done
      addr_cal_udone = 0;
      while (!addr_cal_udone) { //Wait for address cal done
        addr_cal_udone =
            phy_rf_read_cfg_addr_cal_done(ptr);
      }
      phy_rf_write_cfg_enable_peak_computation(ptr, 0); //Flag to selecet peak computation logic
    }
    //Enable pi_addr_180_cal block to compute 180 for addr, or 90 for
    //DQS-DQ
    phy_rf_write_cfg_macro_num_pi_addr_180_cal(ptr, this_macro);  //Write Macro number for pi_addr_180_cal block
    phy_rf_write_cfg_addr_cal_en(ptr, 1); //Enabling addr cal for 90 degree caluculation
    addr_cal_udone = 0;
    while (!addr_cal_udone) {
      addr_cal_udone = phy_rf_read_cfg_addr_cal_done(ptr);
    }

  }     // for this macro

  // Disable at the end of process
  phy_rf_write_cfg_lowfrq_en(ptr, 0);
  DELAY(5);   //  #1000ns; //repeat (100) @(posedge top.sys_clk);
}       // kc_phy_dll_prog_quad_wt_steps

//-----------------------------------------------------------

void kc_phy_en180_cal_addrmacro(void *ptr)
{
  unsigned int addr_cal_done;
  unsigned int __attribute__ ((unused)) readData;
  struct apm_mcu *mcu = (struct apm_mcu *)ptr;
  addr_cal_done = 0;
  phy_rf_write_cfg_macro_num_pi_addr_180_cal(ptr, 9);
  phy_rf_write_cfg_addr_cal_en(ptr, 1);
  while ((!addr_cal_done)) {
    addr_cal_done = phy_rf_read_cfg_addr_cal_done(ptr);
    DELAY(1);
  }
  readData = phy_read_reg(mcu, PHY_REG_CFG_CMD_CODE); // 0xf34
  debug("MCU %d: INFO: KC PHY PI+180 Code: 0x%0x\n", mcu->id, readData);
  return;
}       // kc_phy_en180_cal_addrmacro

//-----------------------------------------------------------

void task_regs_ddr_timing(void *ptr, int unsigned /*7:0 */ trcd,
        int unsigned /*7:0 */ twrd,
        int unsigned /*7:0 */ tmod,
        int unsigned /*7:0 */ trp,
        int unsigned /*7:0 */ twlmrd,
        int unsigned /*7:0 */ twl,
        int unsigned /*7:0 */ trl)
{
  struct apm_mcu __attribute__ ((unused)) * mcu = (struct apm_mcu *)ptr;
  debug("INFO: KC PHY   WL=%2d RL=%2d \n", twl, trl);

  phy_rf_write_trcd(ptr, trcd);
  phy_rf_write_twrd(ptr, twrd);
  phy_rf_write_tmod(ptr, tmod);
  phy_rf_write_trp(ptr, trp);
  phy_rf_write_twlmrd(ptr, twlmrd);
  phy_rf_write_twl(ptr, twl);
  phy_rf_write_trl(ptr, trl);
}       // task_regs_ddr_timing

void kc_phy_init_before_train(void *ptr)
{

  struct apm_mcu *mcu = (struct apm_mcu *)ptr;
  unsigned int wdata;
  phy_rf_write_cfg_read_w_fixed_delay(ptr, KCPHY_USE_READ_W_FIXED_DELAY); // JHR ?? done here

  if (0) {    //`ifdef DISABLE DLL CAL
    phy_rf_write_cfg_disable_dll_cal(ptr, 1);
  }     // `endif

  phy_rf_write_rank7_odt(ptr, 3); // Not in quick setup
  phy_rf_write_rank6_odt(ptr, 2);
  phy_rf_write_rank5_odt(ptr, 1);
  phy_rf_write_rank4_odt(ptr, 0);
  phy_rf_write_rank3_odt(ptr, 3);
  phy_rf_write_rank2_odt(ptr, 2);
  phy_rf_write_rank1_odt(ptr, 1);
  phy_rf_write_rank0_odt(ptr, 0);
  phy_rf_write_rank7_cke(ptr, 3);
  phy_rf_write_rank6_cke(ptr, 2);
  phy_rf_write_rank5_cke(ptr, 1);
  phy_rf_write_rank4_cke(ptr, 0);
  phy_rf_write_rank3_cke(ptr, 3);
  phy_rf_write_rank2_cke(ptr, 2);
  phy_rf_write_rank1_cke(ptr, 1);
  phy_rf_write_rank0_cke(ptr, 0); //JHR 0x48 d=0xe4e4e4e4

  phy_rf_write_twrlvl_ww(ptr, 4); //JHR wrong

  phy_rf_write_trcd(ptr, mcu->phy_params.TRCD); // JHR not written ??
  phy_rf_write_twrd(ptr, mcu->phy_params.TWRD);
  phy_rf_write_tmod(ptr, mcu->phy_params.TMOD);
  phy_rf_write_trp(ptr, mcu->phy_params.TRP);
  phy_rf_write_twlmrd(ptr, mcu->phy_params.TWLMRD);
  phy_rf_write_twl(ptr, mcu->phy_params.WL);
  phy_rf_write_trl(ptr, mcu->phy_params.RL);

  phy_rf_write_wakeup_time_lp4(ptr, 500); // JHR Not written later
  phy_rf_write_wakeup_time_lp3(ptr, 200); // JHR Not written later
  phy_rf_write_wakeup_time_lp2(ptr, 40);  // JHR Not written later
  phy_rf_write_wakeup_time_lp1(ptr, 5); // JHR Not written later

  if (mcu->phy_params.phy_dis_up_54_58_5C == 0) { // JHR Not written later
    phy_rf_write_cfg_cmd_pi_byp(ptr, 0);
    phy_rf_write_cfg_cmd_pi_en(ptr, 1);
    phy_rf_write_cfg_cmd_delay(ptr,
             mcu->phy_params.
             init_val_cmd_addr_dly_54_58);
    phy_rf_write_cfg_ad_pi_en(ptr, 1);
    phy_rf_write_cfg_ad_pi_byp(ptr, 0);
    phy_rf_write_cfg_ad_delay(ptr,
            mcu->phy_params.
            init_val_cmd_addr_dly_54_58);
    phy_rf_write_cfg_ctl_pi_byp(ptr, 0);
    phy_rf_write_cfg_ctl_pi_en(ptr, 1);
    phy_rf_write_cfg_ctl_delay(ptr,
             mcu->phy_params.init_val_ctl_dly_5C);
  }
  // JHR retrain exper 5/2/13phy_rf_write_cfg_pattern1(ptr, 0x22);        // WrCal pattern - Best to do ?
  // JHR retrain exper 5/2/13phy_rf_write_cfg_pattern2(ptr, 0x33);
  // JHR retrain exper 5/2/13phy_rf_write_cfg_pattern3(ptr, 0x44);
  // JHR retrain exper 5/2/13phy_rf_write_cfg_pattern4(ptr, 0x55);
  // JHR retrain exper 5/2/13phy_rf_write_cfg_pattern5(ptr, 0x66);
  // JHR retrain exper 5/2/13phy_rf_write_cfg_pattern6(ptr, 0x77);
  // JHR retrain exper 5/2/13phy_rf_write_cfg_pattern7(ptr, 0x88);
  // JHR retrain exper 5/2/13phy_rf_write_cfg_pattern8(ptr, 0x99);        // Best to do ?

  wdata =
      ((mcu->phy_tr_dly.wrlvl_min_smpl & 0xFF) << 24) |
      ((mcu->phy_tr_dly.wrlvl_dly_stsize & 0xFF) << 16) |
      ((mcu->phy_tr_dly.wrlvl_smpl_per_dly & 0xF) << 12) |
      ((mcu->phy_tr_dly.wrlvl_max_delay_limit & 0xFFF));
  phy_write_reg(mcu, PHY_REG_CFG_TRAINING_CONFIG_1, wdata); // 0x80

  wdata =
      ((mcu->phy_tr_dly.rdlvl_dly_stsize & 0xFF) << 16) |
      ((mcu->phy_tr_dly.rdlvl_smpl_per_dly & 0xF) << 12) |
      ((mcu->phy_tr_dly.rdlvl_max_delay_limit & 0xFFF));
  phy_write_reg(mcu, PHY_REG_CFG_TRAINING_CONFIG_2, wdata); // 0x84

  wdata =
      ((mcu->phy_tr_dly.cfg_gate_retrain_val & 0xFF) << 16) |
      ((mcu->phy_tr_dly.wrcal_max_delay_limit & 0xFFF));
  phy_write_reg(mcu, PHY_REG_CFG_TRAINING_CONFIG_4, wdata); // 0x8C

  debug("INFO: KC PHY   WL=%2d RL=%2d \n", mcu->phy_params.WL,
        mcu->phy_params.RL);
  return;
}       // kc_phy_init_before_train

//! PHY LOOPBACK Routine
int mcu_kc_phy_pbrs_loopback_old(void *ptr)
{
  int unsigned faildat;
  int unsigned bit_sel;
  int unsigned bits;
  int unsigned prbs_done;
  struct apm_mcu *mcu = (struct apm_mcu *)ptr;

  debug("Mcu PHY Data/Address loopback test starting...\n");

  // ------ DATA Loopback
  // GONZO JHR  1/29 0xb00 too small
  phy_rf_write_cfg_prbs_trip_cnt_l(ptr, 0xb00); //lower 32 bits of the prbs trip count
  phy_rf_write_cfg_prbs_trip_cnt_h(ptr, 0x000); //upper 32 bits of prbs trip count
  phy_rf_write_cfg_data_loopback_en(ptr, 1);  //loopback enable for datapath

  phy_rf_write_cfg_bert_resetb(ptr, 0); //put the prbs blovks in reset
  phy_rf_write_cfg_loopback_en(ptr, 1); //enable the loopback
  bit_sel = 0;
  prbs_done = 0;

  for (bit_sel = 0; bit_sel < 8; bit_sel = bit_sel + 1) {
    // this loop selects the bit of the all the macro's
    //  i.e if prbs bit sel is 0, then bit zero of  all the bytes will be checked
    bits = bit_sel;
    phy_rf_write_prbs_bit_sel(ptr, bits);
    phy_rf_write_cfg_bert_resetb(ptr, 1);
    while (!prbs_done) {
      prbs_done = phy_rf_read_cfg_prbs_cnt_done(ptr);
    }
    prbs_done = 0;

    //poll for prbs fail register and see if any of the bits from 0-8 are set
    // read register with Addr: 0xa8 . bits 8:0, represent the prsbs fail for
    // each macro
    faildat = phy_read_reg(mcu, PHY_REG_CFG_PRBS_CAPTURE);
    if (faildat & 0x1) {
      debug
          ("MCU : ERROR KC PHY PRBS fail Data Loopback PHY_REG_CFG_PRBS_CAPTURE=0x%x bit=%0d\n",
           faildat, bit_sel);
    } else {
      debug
          ("MCU : INFO KC PHY PRBS Data Loopback PHY_REG_CFG_PRBS_CAPTURE=0x%x bit=%0d\n",
           faildat, bit_sel);
    }
    faildat = phy_read_reg(mcu, PHY_REG_CFG_PRBS_STATUS);
    if (faildat & 0xFF) {
      debug
          ("MCU : ERROR KC PHY PRBS fail Data Loopback PHY_REG_CFG_PRBS_STATUS=0x%x bit=%0d\n",
           faildat, bit_sel);
    } else {
      debug
          ("MCU: INFO KC PHY PRBS Data Loopback PHY_REG_CFG_PRBS_STATUS=0x%x bit=%0d\n",
           faildat, bit_sel);
    }

    phy_rf_write_cfg_bert_resetb(ptr, 0); //put the prbs blocks in reset before changing the bit select
    DELAY(1); // #30ns;
    debug("Mcu PHY Data loopback test loop %0d of  7 finished.\n",
          bit_sel);
  }     // for (bit_sel = 0; bit_sel < 8; bit_sel=bit_sel+1)

  // Addr loopback
  debug("Mcu PHY Data loopback done - Start Addr Loopback ...\n");

  //Repeat the above loop with address loopback enabled.
  // and the forloop ranges  from 0-12
  phy_rf_write_cfg_prbs_trip_cnt_l(ptr, 0xb00); //lower 32 bits of the prbs trip count
  phy_rf_write_cfg_prbs_trip_cnt_h(ptr, 0x000); //upper 32 bits of prbs trip count
  phy_rf_write_cfg_data_loopback_en(ptr, 0);  //loopback enable for datapath
  phy_rf_write_cfg_add_loopback_en(ptr, 1); //loopback enable for command path

  phy_rf_write_cfg_bert_resetb(ptr, 0); //put the prbs blovks in reset
  phy_rf_write_cfg_loopback_en(ptr, 1); //enable the loopback
  bit_sel = 0;
  prbs_done = 0;

  for (bit_sel = 0; bit_sel < 13; bit_sel = bit_sel + 1) {  // TBD 12 or 13 ??
    // this loop selects the bit of the all the macro's
    //  i.e if prbs bit sel is 0, then bit zero of  all the bytes will be checked
    bits = bit_sel;
    phy_rf_write_prbs_bit_sel(ptr, bits);
    phy_rf_write_cfg_bert_resetb(ptr, 1);
    while (!prbs_done) {
      prbs_done = phy_rf_read_cfg_prbs_cnt_done(ptr);
    }
    prbs_done = 0;

    //poll for prbs fail register and see if any of the bits from 0-8 are set
    // read register with Addr: 0xa8 . bits 8:0, represent the prsbs fail for
    // each macro

    faildat = phy_read_reg(mcu, PHY_REG_CFG_PRBS_CAPTURE);
    if (faildat & 0x1) {
      debug
          ("MCU : ERROR KC PHY PRBS fail Addr Loopback PHY_REG_CFG_PRBS_CAPTURE=0x%x bit=%0d\n",
           faildat, bit_sel);
    } else {
      debug
          ("MCU : INFO KC PHY PRBS Addr Loopback PHY_REG_CFG_PRBS_CAPTURE=0x%x bit=%0d\n",
           faildat, bit_sel);
    }
    faildat = phy_read_reg(mcu, PHY_REG_CFG_PRBS_STATUS);
    if (faildat & 0xFF) {
      debug
          ("MCU : ERROR KC PHY PRBS fail Addr Loopback PHY_REG_CFG_PRBS_STATUS=0x%x bit=%0d\n",
           faildat, bit_sel);
    } else {
      debug
          ("MCU : INFO KC PHY PRBS Addr Loopback PHY_REG_CFG_PRBS_STATUS=0x%x bit=%0d\n",
           faildat, bit_sel);
    }

    phy_rf_write_cfg_bert_resetb(ptr, 0); //put the prbs blocks in reset before changing the bit select

    DELAY(1); // #30ns;
    debug("Mcu PHY Addr loopback test loop %0d of 12 finished.\n",
          bit_sel);
  }     // for (bit_sel = 0; bit_sel < 8; bit_sel=bit_sel+1)

  // Shut off and recover
  phy_rf_write_cfg_data_loopback_en(ptr, 0);  //loopback enable for datapath
  phy_rf_write_cfg_add_loopback_en(ptr, 0); //loopback enable for command path
  phy_rf_write_cfg_loopback_en(ptr, 0); //enable the loopback

  debug("Mcu PHY Data/Addr Loopback finished!\n");
  return 0;
}       // mcu_kc_phy_pbrs_loopback_old

// =================================================
// =================================================
// =================================================
// =================================================
// =================================================

//! DM short
int prbs_short_loopback_dm(void *ptr)
{
  return prbs_general_loopback_dm(ptr, 0x9, 1); //DM,Short
}
int prbs_long_loopback_dm(void *ptr)
{
  return prbs_general_loopback_dm(ptr, 0xb, 1); //DM,Long
}

//! DM short
int prbs_short_loopback_dm_infinite(void *ptr)
{
  return prbs_general_loopback_dm(ptr, 0x9, 0xffffffff);  //DM,Short
}
int prbs_long_loopback_dm_infinite(void *ptr)
{
  return prbs_general_loopback_dm(ptr, 0xb, 0xffffffff);  //DM,Long
}

int prbs_general_loopback_dm(void *ptr, int unsigned lbtype,
           int unsigned loopcnt)
{
  int unsigned ix, ix1, iy, data, pdata;
  int unsigned __attribute__ ((unused)) speed, dmmask;
  int error_cnt;
  struct apm_mcu *mcu = (struct apm_mcu *)ptr;
  int unsigned loops = 0;
  dmmask = mcu->phy_params.prbs_dm_status_mask;

  debug("################################################# \n");
  debug("\t     PRBS DM:  MCU-PHY %1d  starting.....\n", mcu->id);
  debug("################################################# \n");
  speed = phy_read_reg(mcu, 0xf3c);
  debug("PRBS for PLL speed = 0x%0x\n", speed);

  error_cnt = 0;
  phy_write_reg(mcu, PHY_REG_CFG_DQX_PEAK_0, 0x7fff);
  phy_write_reg(mcu, PHY_REG_CFG_DQX_PEAK_1, 0x6fff);
  phy_write_reg(mcu, PHY_REG_CFG_DQX_PEAK_2, 0x4fff);
  phy_write_reg(mcu, PHY_REG_CFG_DQX_PEAK_3, 0x4fff);
  phy_write_reg(mcu, PHY_REG_CFG_DQX_PEAK_4, 0x6fff);
  phy_write_reg(mcu, PHY_REG_CFG_DQX_PEAK_5, 0x6fff);
  phy_write_reg(mcu, PHY_REG_CFG_DQX_PEAK_6, 0x6fff);
  phy_write_reg(mcu, PHY_REG_CFG_DQX_PEAK_7, 0x6fff);
  phy_write_reg(mcu, PHY_REG_CFG_DQX_PEAK_8, 0x3fff);
  //phy_write_reg(mcu, PHY_REG_CFG_RECEIVER_BIAS(0x3ffff)
  //phy_write_reg(mcu, PHY_REG_CFG_PHY_CONFIG(0x3)
  while (loops < loopcnt) {
    loops++;
    for (ix = 0; ix < 8; ix++) {
      // Bit select
      debug("-----------------------------------\n");
      debug("... bit select %0d\n", ix);
      for (ix1 = 0; ix1 < 10; ix1++) {
        debug("... loop# %0d\n", ix1);
        phy_write_reg(mcu, PHY_REG_CFG_PRBS_RESETB,
                0x0);
        phy_write_reg(mcu, PHY_REG_CFG_PRBS_TRIP_L,
                0x00000100);
        phy_write_reg(mcu, PHY_REG_CFG_PRBS_TRIP_H,
                0x00000000);
        //phy_write_reg(mcu, PHY_REG_CFG_PRBS_CAPTURE, 0x00000001);
        phy_write_reg(mcu, PHY_REG_CFG_PRBS_BIT_SEL,
                ix);
        switch (lbtype) {
        case 0x9:
          phy_write_reg(mcu, PHY_REG_CFG_LOOPBACK,
                  0x9);
          break;  //DM,Short
        case 0xB:
          phy_write_reg(mcu, PHY_REG_CFG_LOOPBACK,
                  0xb);
          break;  //DM,Long
        default:
          phy_write_reg(mcu, PHY_REG_CFG_LOOPBACK,
                  0x9);
          break;  //DM,Short
        }
        data =
            phy_read_reg(mcu, PHY_REG_CFG_PRBS_STATUS);
        debug("\tBEFORE RUN: PRBS_STATUS = 0x%0x\n",
              data);
        for (iy = 0; iy < 1; iy++) {
          phy_write_reg(mcu,
                  PHY_REG_CFG_PRBS_RESETB,
                  0x0);
          phy_write_reg(mcu,
                  PHY_REG_CFG_PRBS_RESETB,
                  0x1);
        }
        pdata = 0;
        while (pdata == 0) {
          pdata =
              phy_read_reg(mcu,
               PHY_REG_CFG_PRBS_CNT_DONE);
        }
        phy_write_reg(mcu, PHY_REG_CFG_PRBS_CAPTURE,
                0x00000001);
        data =
            phy_read_reg(mcu, PHY_REG_CFG_PRBS_STATUS);
        debug("\tAFTER RUN: PRBS_STATUS = 0x%0x\n",
              data);
        if ((data &
             (~mcu->phy_params.prbs_dm_status_mask)) !=
            0x0) {
          debug
              ("\tAFTER RUN: ERROR BAD PRBS_STATUS =0x%0X msk=0x%0X",
               data,
               mcu->phy_params.
               prbs_dm_status_mask);
          debug("  loop(%d /%d )\n", ix, ix1);
          error_cnt++;
        } else {
          debug
              ("\tAFTER RUN: GOOD      PRBS_STATUS =0x%0X msk=0x%0X",
               data,
               mcu->phy_params.
               prbs_dm_status_mask);
          debug("  loop(%d /%d )\n", ix, ix1);

        }

        data = phy_read_reg(mcu, PHY_REG_CFG_PRBS_ERR_CNT_1); // DM0,1
        debug("\tDM1,DM0 = 0x%0x\n", data);
        data = phy_read_reg(mcu, PHY_REG_CFG_PRBS_ERR_CNT_2); // DM2,3
        debug("\tDM3,DM2 = 0x%0x\n", data);
        data = phy_read_reg(mcu, PHY_REG_CFG_PRBS_ERR_CNT_3); // DM4,5
        debug("\tDM5,DM4 = 0x%0x\n", data);
        data = phy_read_reg(mcu, PHY_REG_CFG_PRBS_ERR_CNT_4); // DM6,7
        debug("\tDM7,DM6 = 0x%0x\n", data);
        data = phy_read_reg(mcu, PHY_REG_CFG_PRBS_ERR_CNT_5); // AM1, DM8
        debug("\tAM1,DM8 = 0x%0x\n", data);
        data = phy_read_reg(mcu, PHY_REG_CFG_PRBS_ERR_CNT_6); // A3, AM2
        debug("\tAM3,AM2 = 0x%0x\n", data);
        data = phy_read_reg(mcu, PHY_REG_CFG_PRBS_ERR_CNT_7); // AM5, AM4
        debug("\tAM5,AM4 = 0x%0x\n", data);
        debug
            ("\tAFTER RUN: NOTE: PHY_REG_CFG_PRBS_ERR_CNT_1/7 only matter if CFG_PRBS_STATUS non-zero\n");
      }
    }
  }
  data = phy_read_reg(mcu, PHY_REG_CFG_PRBS_STATUS);
  debug("################################################# \n");
  debug("################################################# \n");
  debug("\t     PRBS DM:  MCU-PHY %1d\n", mcu->id);
  debug
      ("\tDONE PRBS DM:  summary errors = %d  PRBS_STATUS =0x%0X \n",
       error_cnt, data);
  debug("################################################# \n");
  debug("################################################# \n");
  return error_cnt;
}

// =================================================
// =================================================

//!  PRBS AM Short
int prbs_short_loopback_am(void *ptr)
{
  // phy_write_reg(mcu, PHY_REG_CFG_LOOPBACK, 0x5); //AM,Short
  return prbs_general_loopback_am(ptr, 0x5);
}       // prbs_short_loopback_am

//!  PRBS AM Long
int prbs_long_loopback_am(void *ptr)
{
  // phy_write_reg(mcu, PHY_REG_CFG_LOOPBACK, 0x7); //AM,Long
  return prbs_general_loopback_am(ptr, 0x7);
}       // prbs_long_loopback_am

//----------------------------------------

//! Generic Address macro PRBS
int prbs_general_loopback_am(void *ptr, int unsigned lbtype)
{
  unsigned int ix, ix1, iy, data, pdata, sdm_dly, pi_sel, pi_code, dly;
  unsigned int __attribute__ ((unused)) speed;
  int error_cnt;
  struct apm_mcu *mcu = (struct apm_mcu *)ptr;

  debug("################################################# \n");
  debug("\t     PRBS AM:  MCU-PHY %1d  starting.....\n", mcu->id);
  debug("################################################# \n");

  error_cnt = 0;
  speed = phy_read_reg(mcu, 0xf3c);
  debug("\n\n##### PRBS lbtype=0x%X   for   PLL speed = 0x%0x\n\n",
        lbtype, speed);
  phy_write_reg(mcu, PHY_REG_CFG_DQX_PEAK_0, 0x7fff);
  phy_write_reg(mcu, PHY_REG_CFG_DQX_PEAK_1, 0x6fff);
  phy_write_reg(mcu, PHY_REG_CFG_DQX_PEAK_2, 0x4fff);
  phy_write_reg(mcu, PHY_REG_CFG_DQX_PEAK_3, 0x4fff);
  phy_write_reg(mcu, PHY_REG_CFG_DQX_PEAK_4, 0x6fff);
  phy_write_reg(mcu, PHY_REG_CFG_DQX_PEAK_5, 0x6fff);
  phy_write_reg(mcu, PHY_REG_CFG_DQX_PEAK_6, 0x6fff);
  phy_write_reg(mcu, PHY_REG_CFG_DQX_PEAK_7, 0x6fff);
  phy_write_reg(mcu, PHY_REG_CFG_DQX_PEAK_8, 0x3fff);

  // Bit select -
  for (pi_sel = 0; pi_sel < 4; pi_sel++) {
    // for (pi_sel = 0; pi_sel < 1; pi_sel++) {

    for (sdm_dly = 0; sdm_dly < 16; sdm_dly++) {
      // for (sdm_dly = 0; sdm_dly < 8; sdm_dly++) {

      for (pi_code = 0; pi_code < 64; pi_code++) {
        // for (pi_code = 0; pi_code < 1; pi_code++) {

        dly =
            ((sdm_dly << 8) | (pi_sel << 6) |
             (pi_code));
        debug("AM and CTL DELAY REGISTER: 0x%0x\n",
              dly);

        phy_write_reg(mcu, PHY_REG_CFG_CMD_DELAY, dly);
        phy_write_reg(mcu, PHY_REG_CFG_AD_DELAY, dly);
        phy_write_reg(mcu, PHY_REG_CFG_CTL_DELAY, dly);

        // FullDM/AM loopback for (ix = 0; ix < 12; ix++ ) {
        for (ix = 8; ix < 12; ix++) { // for just AM bits

          debug
              ("-----------------------------------\n");
          debug("... bit select %0d\n", ix);

          //
          for (ix1 = 0; ix1 < 3; ix1++) {

            debug("... loop# %0d\n", ix1);

            phy_write_reg(mcu,
                    PHY_REG_CFG_PRBS_RESETB,
                    0x0);
            phy_write_reg(mcu,
                    PHY_REG_CFG_PRBS_TRIP_L,
                    0x00000100);
            phy_write_reg(mcu,
                    PHY_REG_CFG_PRBS_TRIP_H,
                    0x00000000);
            // phy_write_reg(mcu, PHY_REG_CFG_PRBS_CAPTURE, 0x00000001);
            // Note: KoolChips - not possible to induce SW error
            phy_write_reg(mcu,
                    PHY_REG_CFG_PRBS_BIT_SEL,
                    ix);
            switch (lbtype) {
            case 0x7:
              phy_write_reg(mcu,
                      PHY_REG_CFG_LOOPBACK,
                      0x7);
              break;  //AM,Long
            case 0x5:
              phy_write_reg(mcu,
                      PHY_REG_CFG_LOOPBACK,
                      0x5);
              break;  //AM,Short
            default:
              phy_write_reg(mcu,
                      PHY_REG_CFG_LOOPBACK,
                      0x5);
              break;
            }
            data =
                phy_read_reg(mcu,
                 PHY_REG_CFG_PRBS_STATUS);
            debug
                ("\tBEFORE RUN: PRBS_STATUS = 0x%0x \n",
                 data);

            for (iy = 0; iy < 2; iy++) {
              phy_write_reg(mcu,
                      PHY_REG_CFG_PRBS_RESETB,
                      0x0);
              phy_write_reg(mcu,
                      PHY_REG_CFG_PRBS_RESETB,
                      0x1);
            }
            pdata = 0;
            while (pdata == 0) {
              pdata =
                  phy_read_reg(mcu,
                   PHY_REG_CFG_PRBS_CNT_DONE);
            }

            phy_write_reg(mcu,
                    PHY_REG_CFG_PRBS_CAPTURE,
                    0x00000001);
            data =
                phy_read_reg(mcu,
                 PHY_REG_CFG_PRBS_STATUS);
            debug
                ("\tAFTER RUN: PRBS_STATUS = 0x%0x\n",
                 data);
            if (data != 0x0) {
#if APM_SIM
#else
              debug
                  ("\tAFTER RUN: error bad PRBS_STATUS = 0x%0x loop(%d /%d /%d /%d /%d )\n",
                   data, pi_sel,
                   sdm_dly, pi_code,
                   ix, ix1);
#endif
              error_cnt++;
            } else {
#if APM_SIM
#else
              debug
                  ("\tAFTER RUN: good PRBS_STATUS = 0x%0x loop(%d /%d /%d /%d /%d )\n",
                   data, pi_sel,
                   sdm_dly, pi_code,
                   ix, ix1);
#endif
            }

            data = phy_read_reg(mcu, PHY_REG_CFG_PRBS_ERR_CNT_1); // DM0,1
            debug("\tDM1,DM0 = 0x%0x\n",
                  data);
            data = phy_read_reg(mcu, PHY_REG_CFG_PRBS_ERR_CNT_2); // DM2,3
            debug("\tDM3,DM2 = 0x%0x\n",
                  data);
            data = phy_read_reg(mcu, PHY_REG_CFG_PRBS_ERR_CNT_3); // DM4,5
            debug("\tDM5,DM4 = 0x%0x\n",
                  data);
            data = phy_read_reg(mcu, PHY_REG_CFG_PRBS_ERR_CNT_4); // DM6,7
            debug("\tDM7,DM6 = 0x%0x\n",
                  data);
            data = phy_read_reg(mcu, PHY_REG_CFG_PRBS_ERR_CNT_5); // AM1, DM8
            debug("\tAM1,DM8 = 0x%0x\n",
                  data);
            data = phy_read_reg(mcu, PHY_REG_CFG_PRBS_ERR_CNT_6); // A3, AM2
            debug("\tAM3,AM2 = 0x%0x\n",
                  data);
            data = phy_read_reg(mcu, PHY_REG_CFG_PRBS_ERR_CNT_7); // AM5, AM4
            debug("\tAM5,AM4 = 0x%0x\n",
                  data);
            debug
                ("\tAFTER RUN: NOTE: PHY_REG_CFG_PRBS_ERR_CNT_1/7 only matter if CFG_PRBS_STATUS non-zero\n");
          }
        }
      }
    }
  }
  debug("################################################# \n");
  debug("################################################# \n");
  debug("\t     PRBS AM:  MCU-PHY %1d\n", mcu->id);
  data = phy_read_reg(mcu, PHY_REG_CFG_PRBS_STATUS);
  debug("\tDone PRBS AM:  summary errors = %d   PRBS_STATUS = 0x%0x \n",
        error_cnt, data);
  debug("################################################# \n");
  debug("################################################# \n");
  return error_cnt;
}       // prbs_short_loopback_am

// =================================================
// =================================================
// =================================================
// =================================================
// =================================================

//! PHY LOOPBACK Routine - translated from Python
int mcu_kc_phy_prbs_short_loopback_sweep(void *ptr,
           int unsigned dqx, int unsigned lbtype)
{

  unsigned int wdata;
  unsigned int __attribute__ ((unused)) wwdata;
  unsigned int regAddr = 0;
  unsigned int done, ix, lb_seq, data, pdata, ecRegAddr, errCnt, datack,
      foostatus;
  struct apm_mcu *mcu = (struct apm_mcu *)ptr;

  switch (dqx) {
  case 0:
    regAddr = 0x2b4;
    break;
  case 1:
    regAddr = 0x434;
    break;
  case 2:
    regAddr = 0x5b4;
    break;
  case 3:
    regAddr = 0x734;
    break;
  case 4:
    regAddr = 0x8b4;
    break;
  case 5:
    regAddr = 0xa34;
    break;
  case 6:
    regAddr = 0xbb4;
    break;
  case 7:
    regAddr = 0xd34;
    break;
  case 8:
    regAddr = 0xeb4;
    break;
  }

  phy_write_reg(mcu, PHY_REG_CFG_RECEIVER_BIAS, 0xffffffff);
  phy_write_reg(mcu, PHY_REG_CFG_PHY_CONFIG, 0x3);
  phy_write_reg(mcu, PHY_REG_CFG_MACRO_ENABLE, 0x1ffff);

  switch (dqx) {
  case 0:
    ecRegAddr = 0xe0;
    break;
  case 1:
    ecRegAddr = 0xe0;
    break;
  case 2:
    ecRegAddr = 0xe4;
    break;
  case 3:
    ecRegAddr = 0xe4;
    break;
  case 4:
    ecRegAddr = 0xe8;
    break;
  case 5:
    ecRegAddr = 0xe8;
    break;
  case 6:
    ecRegAddr = 0xec;
    break;
  case 7:
    ecRegAddr = 0xec;
    break;
  case 8:
    ecRegAddr = 0xf0;
    break;
  case 9:
    ecRegAddr = 0xf0;
    break;
  default:
    ecRegAddr = 0xe0;
    break;
  }
  data = phy_read_reg(mcu, ecRegAddr);
#if APM_SIM
#else
  debug
      ("MCU-PHY %d: INFO: -- start prbs_short_loopback_sweep()  DQX=%0d LBTYPE=0x%x\n",
       mcu->id, dqx, lbtype);
  debug
      ("MCU-PHY %d: INFO: -- start PRBS_LOOP_DQS_SCHMOO  DQX_PEAK_%0d  initial ecReg=0x%x\n",
       mcu->id, dqx, data);
#endif
  done = 0;
  for (ix = 0; ix < PHY_PRBS_LOOP_DQS_SCHMOO; ix++) { // in range(0x80):
    // place ix starting from 9th bit of data
    wdata = ix << 8 | 0xff;
    // write CFG_DQX_PEAK_<n> register
#if APM_SIM
#else
    debug
        ("MCU-PHY %d: INFO: ----- writing to DQX_PEAK_%0d with 0x%0x  (loop %d of %d)\n",
         mcu->id, dqx, wdata, ix, PHY_PRBS_LOOP_DQS_SCHMOO);
#endif
    // i2cWritePHY_NWL(regAddr, wdata)
    phy_write_reg(mcu, regAddr, wdata);
    // start PRBS run
    phy_write_reg(mcu, PHY_REG_CFG_PRBS_RESETB, 0);
    phy_write_reg(mcu, PHY_REG_CFG_PRBS_TRIP_L, 0x10000);
    phy_write_reg(mcu, PHY_REG_CFG_PRBS_TRIP_H, 0);

    //    if(PRBS_AM_LONG):
    //        i2c_write_CFG_LOOPBACK(0x7) //AM,Long
    //    if(PRBS_DM_LONG):
    //        i2c_write_CFG_LOOPBACK(0xb) //DM,Long
    //    if(PRBS_AM_SHORT):
    //        i2c_write_CFG_LOOPBACK(0x5) //AM,Short
    //    if(PRBS_DM_SHORT):
    //        i2c_write_CFG_LOOPBACK(0x9) //DM,Short
    //    if(PRBS_AM_DM_SHORT):
    //        i2c_write_CFG_LOOPBACK(0xd) //AM,DM,Short
    //    if(PRBS_AM_DM_LONG):
    //        i2c_write_CFG_LOOPBACK(0xe) //AM,DM,Long
    switch (lbtype) {
    case PRBS_AM_LONG:
      lb_seq = 0x7;
      break;
    case PRBS_DM_LONG:
      lb_seq = 0xb;
      break;
    case PRBS_AM_SHORT:
      lb_seq = 0x5;
      break;
    case PRBS_DM_SHORT:
      lb_seq = 0x9;
      break;
    case PRBS_AM_DM_SHORT:
      lb_seq = 0xd;
      break;
    case PRBS_AM_DM_LONG:
      lb_seq = 0xe;
      break;
    default:
      lb_seq = 0x9;
      break;
    }
    phy_write_reg(mcu, PHY_REG_CFG_LOOPBACK, lb_seq);

    // Clear the PRBS Status Register
    // data = i2c_read_CFG_PRBS_STATUS()
    data = phy_read_reg(mcu, PHY_REG_CFG_PRBS_STATUS);

    // Bring PRBS Logic out of reset to start PRBS
    phy_write_reg(mcu, PHY_REG_CFG_PRBS_RESETB, 0x1);

    // Poll for PRBS DONE
    pdata = 0;
    while (pdata == 0) {
      pdata = phy_read_reg(mcu, PHY_REG_CFG_PRBS_CNT_DONE);
    }
    phy_write_reg(mcu, PHY_REG_CFG_PRBS_CAPTURE, 0x1);

    ////// reading the status bit indexed by dqx
    //data1 = i2c_read_CFG_PRBS_ERR_CNT_1()
    // reading error count from errCntAddr
    // ecRegAddr = errCntAddr[dqx]
    switch (dqx) {
    case 0:
      ecRegAddr = 0xe0;
      break;
    case 1:
      ecRegAddr = 0xe0;
      break;
    case 2:
      ecRegAddr = 0xe4;
      break;
    case 3:
      ecRegAddr = 0xe4;
      break;
    case 4:
      ecRegAddr = 0xe8;
      break;
    case 5:
      ecRegAddr = 0xe8;
      break;
    case 6:
      ecRegAddr = 0xec;
      break;
    case 7:
      ecRegAddr = 0xec;
      break;
    case 8:
      ecRegAddr = 0xf0;
      break;
    case 9:
      ecRegAddr = 0xf0;
      break;
    }
    data = phy_read_reg(mcu, ecRegAddr);

    errCnt = 0;
    if ((dqx % 2) == 0) {
      errCnt = data & 0xffff;
    } else {
      errCnt = data >> 16;
    }
    // wwdata = i2cReadPHY_NWL(regAddr)
    wwdata = phy_read_reg(mcu, regAddr);

    foostatus = phy_read_reg(mcu, PHY_REG_CFG_PRBS_STATUS);
    datack = (foostatus >> dqx) & 1;
#if APM_SIM
#else
    debug
        ("MCU-PHY %d:... DQX_PEAK_%0d=0x%0x / err count=0x%0x / status = %0x  (loop %d of %d)\n",
         mcu->id, dqx, wwdata, errCnt, datack, ix,
         PHY_PRBS_LOOP_DQS_SCHMOO);
#endif
    // fop.write("... DQX_PEAK_%0d=0x%0x / error count=0x%0x / status = %0x\n" % (dqx, wwdata, errCnt, datack))
    //  sleep(0.5)
    DELAY(3);
    if (datack == 0) {
      done = 1;
      break;
    }
  }

  if (done) {
    ////// capture here
#if APM_SIM
#else
    debug
        ("MCU-PHY %d: INFO ... prbs passed for DQX_PEAK_%0d at 0x%0x :))))))\n",
         mcu->id, dqx, wdata);
#endif
  } else {
#if APM_SIM
#else
    debug
        ("MCU-PHY %d: ERROR ... prbs failed for DQX_PEAK_%0d with error count=%0d :((((((((\n",
         mcu->id, dqx, errCnt);
#endif
  }
#if APM_SIM
#else
  debug
      ("MCU-PHY %d: dqx=%d lbtype=%d  mcu_kc_phy_prbs_short_loopback_sweep finished!",
       mcu->id, dqx, lbtype);
#endif
  return errCnt;
}       // mcu_kc_phy_prbs_short_loopback_sweep

// =================================================
// =================================================
// =================================================
// =================================================
// =================================================

int mcu_kc_phy_pbrs_loopback(void *ptr)
{
  int unsigned err = 0;
  debug("Mcu PHY mcu_kc_phy_pbrs_loopback start...\n");

  // err = prbs_short_loopback_am(ptr);
  err = prbs_short_loopback_dm(ptr);
  debug("\tAFTER RUN: Loop Back test had errors = %d\n", err);
  return err;
}

// =================================================
// =================================================
// =================================================
// =================================================
// =================================================

void kc_phy_cdr_lock(void *ptr)
{       // From TestChip CDR Lock

  struct apm_mcu *mcu = (struct apm_mcu *)ptr;
  unsigned int rddata, rddata2;
  // From KC routine cdr_lock_apm() 2/2 Purna

  DELAYP(2);
  mcu->phy_wr(mcu, PHY_REG_CFG_CDR_LOCK_RESET, 0x1f); // 0x140
  DELAYP(2);
  phy_write_reg(mcu, PHY_REG_CFG_CDR_ENABLE, 0x0);  // 0x108
  DELAYP(2);
  mcu->phy_wr(mcu, PHY_REG_CFG_CDR_LOCK_RESET, 0x0);  // 0x140
  DELAYP(2);
  mcu->phy_wr(mcu, PHY_REG_CFG_CDR_RESETB, 0x1);  // 0xF44
  DELAYP(1);
  phy_write_reg(mcu, PHY_REG_CFG_CDR_CONFIG, 0x3ec2); // 0x13C
  DELAYP(2);

  // All CDR LOCK
  phy_write_reg(mcu, PHY_REG_CFG_CDR_ENABLE, 0x1F); // 0x108
  DELAYP(2);
  phy_poll_reg(ptr, PHY_REG_CFG_CDR_LOCK, 0x1F, 0x1F);  //0x144

  // From KC routine lock_check_apm() 2/2 Purna
  DELAYP(2);
  phy_poll_reg(ptr, PHY_REG_CFG_CDR_LOCK, 0x1F, 0x1F);  //0x144

  rddata = mcu->phy_rd(mcu, PHY_REG_CFG_PI_CODE); //0x148
  DELAYP(10);
  rddata2 = mcu->phy_rd(mcu, PHY_REG_CFG_PI_CODE);
  if (rddata != rddata2) {
    debug("ERROR PI CODE change after CDR Lock 0x%x -> 0x%x\n",
          rddata, rddata2);
  };

  // From KC routine deassert_phy_soft_reset_apm() 2/2 Purna
  DELAYP(2);
  mcu->phy_wr(mcu, PHY_REG_CFG_PHY_SRST, 0x0);
  DELAYP(2);
  mcu->phy_wr(mcu, PHY_REG_CFG_PHY_SRST, 0x1);
  DELAYP(2);
  mcu->phy_wr(mcu, PHY_REG_CFG_PHY_SRST, 0x0);
  DELAYP(2);
  mcu->phy_wr(mcu, PHY_REG_CFG_PHY_SRST, 0x1);
  DELAYP(2);
  mcu->phy_wr(mcu, PHY_REG_CFG_PHY_SRST, 0x0);

  return;
}       // kc_phy_cdr_lock

// =================================================
// =================================================

void kc_phy_quick_setup(void *ptr)
{
  int unsigned wdata = 0;
  struct apm_mcu *mcu = (struct apm_mcu *)ptr;
  phy_param_t *p_phy = &mcu->phy_params;

  // Python routines kc_csr_setup_apm() - Drop 2/5/13 Purna

  // setup Analog
  // AM/DM Stength/Slew Rates
  phy_write_reg(mcu, PHY_REG_CFG_RECEIVER_BIAS, 0x7ffff); // 0x114
  phy_write_reg(mcu, PHY_REG_CFG_ZQ_CAL_CODE, mcu->phy_params.zqcal_code);  // 0x44

  // setup I/Os
  // Mode Register
  //BIT_CFG_READ_W_FIXED_DELAY_12_1 = 0x1
  //BIT_CFG_RDLVL_MODE_6_2_ = 0x2
  //BIT_CFG_WRLVL_MODE_4_2 = 0x2
  //BIT_CFG_RDLVL_GATE_MODE_2_2 = 0x2
  //BIT_CFG_CMD_OE_0_1 = 0x1
  //BIT_CFG_RESET_OE_1_1 = 0x1
  //BIT_CFG_X4_EN_14_1 = 0x0
  //BIT_CFG_PARITY_OE_15_1 = 0x0
  wdata = (KCPHY_USE_READ_W_FIXED_DELAY << 12) | ((p_phy->cfg_parity_oe & 0x1) << 15) | ((mcu->mcu_params.by4_mode & 0x1) << 14) | ((p_phy->phy_train_mode & 0x3) << 6) | ((p_phy->phy_train_mode & 0x3) << 4) | ((p_phy->phy_train_mode & 0x3) << 2) | 0x3;  // 0x10ab
  phy_write_reg(mcu, PHY_REG_CFG_PHY_CONFIG, wdata);  // 0x0 JHR prbs vs init

  // Disable DLL Calibration
  phy_write_reg(mcu, PHY_REG_CFG_DISABLE_DLL_CAL, 0x2); // 0xbc

  // Configure Training Registers
  wdata = phy_read_reg(mcu, PHY_REG_CFG_TRAINING_CONFIG_1);
  wdata =
      ((mcu->phy_tr_dly.wrlvl_min_smpl & 0xFF) << 24) |
      ((mcu->phy_tr_dly.wrlvl_dly_stsize & 0xFF) << 16) |
      ((mcu->phy_tr_dly.wrlvl_smpl_per_dly & 0xF) << 12) |
      ((mcu->phy_tr_dly.wrlvl_max_delay_limit & 0xFFF));
  phy_write_reg(mcu, PHY_REG_CFG_TRAINING_CONFIG_1, wdata); // 0x80

  wdata = phy_read_reg(mcu, PHY_REG_CFG_TRAINING_CONFIG_2);
  wdata =
      ((mcu->phy_tr_dly.rdlvl_dly_stsize & 0xFF) << 16) |
      ((mcu->phy_tr_dly.rdlvl_smpl_per_dly & 0xF) << 12) |
      ((mcu->phy_tr_dly.rdlvl_max_delay_limit & 0xFFF));
  phy_write_reg(mcu, PHY_REG_CFG_TRAINING_CONFIG_2, wdata); // 0x84

  wdata = phy_read_reg(mcu, PHY_REG_CFG_TRAINING_CONFIG_3);
  wdata =
      ((mcu->phy_tr_dly.gtlvl_min_smpl & 0xFF) << 24) |
      ((mcu->phy_tr_dly.gtlvl_dly_stsize & 0xFF) << 16) |
      ((mcu->phy_tr_dly.gtlvl_smpl_per_dly & 0xF) << 12) |
      ((mcu->phy_tr_dly.gtlvl_max_delay_limit & 0xFFF));
  phy_write_reg(mcu, PHY_REG_CFG_TRAINING_CONFIG_3, wdata); // 0x88

  wdata = phy_read_reg(mcu, PHY_REG_CFG_TRAINING_CONFIG_4);
  wdata =
      ((mcu->phy_tr_dly.cfg_gate_retrain_val & 0xFF) << 16) |
      ((mcu->phy_tr_dly.wrcal_max_delay_limit & 0xFFF));
  phy_write_reg(mcu, PHY_REG_CFG_TRAINING_CONFIG_4, wdata); // 0x8C

  // Enable Only CK0,2,4,6
  wdata =
      ((mcu->phy_params.cfg_cs_en & 0xFF) << 24) |
      ((mcu->phy_params.cfg_ck_en & 0xFF) << 16) |
      ((mcu->phy_params.cfg_odt_en & 0xFF) << 8) |
      ((mcu->phy_params.cfg_cke_en & 0xFF));
  phy_write_reg(mcu, PHY_REG_CFG_MEM_OE, wdata);  // 0x4

  if (!(mcu->mcu_params.ECCenable))
    mcu->phy_params.cfg_macro_en_val &= KCPHY_CFG_MACRO_NOECC_MASK;
  if (mcu->mcu_params.by4_mode) {
    phy_write_reg(mcu, PHY_REG_CFG_MACRO_ENABLE, (mcu->phy_params.cfg_macro_en_val & KCPHY_CFG_MACRO_x4_MASK)); // 0x8
  } else {
    phy_write_reg(mcu, PHY_REG_CFG_MACRO_ENABLE, (mcu->phy_params.cfg_macro_en_val & KCPHY_CFG_MACRO_x8_MASK)); // 0x8
  }
  phy_write_reg(mcu, PHY_REG_CFG_WRCAL_ADDR, 0x00001200); // 0x14 - any valid dimm address

  // For KC TESTCHIP ONLY *NOT FOR CUSTOMER PRODUCT*
  // i2c_write_spare_register_1_0(0x3)

  // DIMM related setup
  phy_write_reg(mcu, PHY_REG_CFG_ZQ_COUNTER, 0xfffffff0); // 0x94

  return;
}       // kc_phy_quick_setup

// =================================================
// =================================================

void kc_phy_quick_setup_prbs(void *ptr)
{
  int unsigned readData, wdata = 0;
  struct apm_mcu *mcu = (struct apm_mcu *)ptr;
  phy_param_t *p_phy = &mcu->phy_params;

  // setup Analog
  // AM/DM Stength/Slew Rates
  phy_write_reg(mcu, PHY_REG_CFG_ANALOG_CONFIG_2, 0xffffffff);  // 0x3c JHR GONZO set in drv_str()
  phy_write_reg(mcu, PHY_REG_CFG_ANALOG_CONFIG_3, 0xffffffff);  // 0x40 JHR GONZO set in drv_str()
  phy_write_reg(mcu, PHY_REG_CFG_RECEIVER_BIAS, 0x7ffff); // 0x114
  phy_write_reg(mcu, PHY_REG_CFG_ZQ_CAL_CODE, mcu->phy_params.zqcal_code);  // 0x44

  // setup I/Os
  // Mode Register
  //BIT_CFG_READ_W_FIXED_DELAY_12_1 = 0x1
  //BIT_CFG_RDLVL_MODE_6_2_ = 0x2
  //BIT_CFG_WRLVL_MODE_4_2 = 0x2
  //BIT_CFG_RDLVL_GATE_MODE_2_2 = 0x2
  //BIT_CFG_CMD_OE_0_1 = 0x1
  //BIT_CFG_RESET_OE_1_1 = 0x1
  //BIT_CFG_X4_EN_14_1 = 0x0
  //BIT_CFG_PARITY_OE_15_1 = 0x0
  wdata = (0x0 << 12) | ((p_phy->cfg_parity_oe & 0x1) << 15) | ((mcu->mcu_params.by4_mode & 0x1) << 14) | ((p_phy->phy_train_mode & 0x3) << 6) | ((p_phy->phy_train_mode & 0x3) << 4) | ((p_phy->phy_train_mode & 0x3) << 2) | 0x3; // 0x10ab
  phy_write_reg(mcu, PHY_REG_CFG_PHY_CONFIG, wdata);
  // Enable Only CK0,1,2,3 if loaded
  wdata =
      ((mcu->phy_params.cfg_cs_en & 0xFF) << 24) |
      ((mcu->phy_params.cfg_ck_en & 0xFF) << 16) |
      ((mcu->phy_params.cfg_odt_en & 0xFF) << 8) |
      ((mcu->phy_params.cfg_cke_en & 0xFF));
  phy_write_reg(mcu, PHY_REG_CFG_MEM_OE, wdata);  // 0x4
  if (mcu->mcu_params.by4_mode) {
    phy_write_reg(mcu, PHY_REG_CFG_MACRO_ENABLE, (mcu->phy_params.cfg_macro_en_val & KCPHY_CFG_MACRO_x4_MASK)); // 0x8
  } else {
    phy_write_reg(mcu, PHY_REG_CFG_MACRO_ENABLE, (mcu->phy_params.cfg_macro_en_val & KCPHY_CFG_MACRO_x8_MASK)); // 0x8
  }

  // setup training
  phy_write_reg(mcu, PHY_REG_SPARE_REGISTER_1_0, 0x2);  //Gonzo Josh see bit 0 == 0 old:0x3 TC// 0xf2c
  phy_rf_write_cfg_num_of_wr_samples(ptr, 0x28);  //RMW
  phy_rf_write_cfg_num_of_gt_samples(ptr, 0x0);
  phy_rf_write_cfg_read_w_fixed_delay(ptr, KCPHY_USE_READ_W_FIXED_DELAY);
  phy_rf_write_cfg_disable_dll_cal(ptr, 1);
  phy_write_reg(mcu, PHY_REG_CFG_WRCAL_ADDR, 0x31f000ac); // 0x14

  // setup 1 RANK
  phy_rf_write_cfg_cs0_oe(ptr, 1);
  phy_rf_write_cfg_ck0_oe(ptr, 1);
  phy_rf_write_cfg_odt0_oe(ptr, 1);
  phy_rf_write_cfg_cke0_oe(ptr, 1);
  phy_write_reg(mcu, PHY_REG_CFG_RANK_EN, 1); // 0x68

  //  DIMM related setup
  phy_write_reg(mcu, PHY_REG_CFG_DDR_PARAM_1, 0x0410080e);
  phy_write_reg(mcu, PHY_REG_CFG_DDR_PARAM_2, 0x0e100606);
  /*wdata =
     (((mcu->phy_params.TWLMRD) & 0xFF) << 24) |
     (((mcu->phy_params.TMOD) & 0xFF) << 16) |
     (((0xC) & 0xFF) << 8) | // tWRLVL_WW - GONZO use param
     ((mcu->phy_params.TRP) & 0xFF) ;
     phy_write_reg(mcu, PHY_REG_CFG_DDR_PARAM_1, wdata);

     wdata =
     (((mcu->phy_params.TRCD) & 0xFF) << 24) |
     (((mcu->phy_params.TWRD) & 0xFF) << 16) |
     (((mcu->phy_params.WL) & 0xFF) << 8) | //
     ((mcu->phy_params.RL) & 0xFF) ;
     phy_write_reg(mcu, PHY_REG_CFG_DDR_PARAM_2, wdata); */
  // KC commented phy_write_reg(mcu, PHY_REG_CFG_WAKEUP_TIME, 0x1f4c8285)
  // KC commented phy_write_reg(mcu, PHY_REG_CFG_CMD_DELAY, 0x400);
  // KC commented phy_write_reg(mcu, PHY_REG_CFG_AD_DELAY, 0x400);
  // KC commented phy_write_reg(mcu, PHY_REG_CFG_CTL_DELAY, 0x400);

  phy_write_reg(mcu, PHY_REG_CFG_ZQ_COUNTER, 0xfffffff0); // 0x94

  // GONZO not done here --- i2cWritePHY_NWL(0x30, 1) // MC_POWER_OK

  // NOTE: Address calibration - 180 deg
  phy_write_reg(mcu, PHY_REG_CFG_ADDR_CAL_EN, 0x25);  // 0xf58
  readData = 0;
  while (readData == 0) {
    readData = phy_read_reg(mcu, PHY_REG_CFG_ADDR_CAL_DONE);  // 0xf5c
  }
  readData = phy_read_reg(mcu, PHY_REG_CFG_CMD_CODE); // 0xf34

  debug("INFO: KC PHY-%1d  PI+180 Code: 0x%0x\n", mcu->id, readData);
  debug("INFO: KC PHY     WL=%2d RL=%2d \n",
        mcu->phy_params.WL, mcu->phy_params.RL);
  return;
}       // kc_phy_quick_setup_prbs

// =================================================
// =================================================
// =================================================
// =================================================

void init_bypss_fix_kc1333(void *p)
{
  struct apm_mcu *mcu = (struct apm_mcu *)p;

  // Fib part 1333 DM0,4,5,6,7
  mcu->phy_tr_dly.rank_dly[0].wr_lvl[0 * 2] = 0x136;
  mcu->phy_tr_dly.rank_dly[0].wr_lvl[1 * 2] = 0x15D;  //INTERPOLATED
  mcu->phy_tr_dly.rank_dly[0].wr_lvl[2 * 2] = 0x184;  //INTERPOLATED
  mcu->phy_tr_dly.rank_dly[0].wr_lvl[3 * 2] = 0x1AB;  //INTERPOLATED
  mcu->phy_tr_dly.rank_dly[0].wr_lvl[4 * 2] = 0x1EE;
  mcu->phy_tr_dly.rank_dly[0].wr_lvl[5 * 2] = 0x20C;
  mcu->phy_tr_dly.rank_dly[0].wr_lvl[6 * 2] = 0x233;
  mcu->phy_tr_dly.rank_dly[0].wr_lvl[7 * 2] = 0x248;
  mcu->phy_tr_dly.rank_dly[0].wr_lvl[8 * 2] = 0x200;  //INTERPOLATED

  mcu->phy_tr_dly.rank_dly[0].gt_lvl[0 * 2] = 0x4F0;
  mcu->phy_tr_dly.rank_dly[0].gt_lvl[1 * 2] = 0x507;  //INTERPOLATED
  mcu->phy_tr_dly.rank_dly[0].gt_lvl[2 * 2] = 0x51E;  //INTERPOLATED
  mcu->phy_tr_dly.rank_dly[0].gt_lvl[3 * 2] = 0x535;  //INTERPOLATED
  mcu->phy_tr_dly.rank_dly[0].gt_lvl[4 * 2] = 0x54E;
  mcu->phy_tr_dly.rank_dly[0].gt_lvl[5 * 2] = 0x562;
  mcu->phy_tr_dly.rank_dly[0].gt_lvl[6 * 2] = 0x58C;
  mcu->phy_tr_dly.rank_dly[0].gt_lvl[7 * 2] = 0x5B5;
  mcu->phy_tr_dly.rank_dly[0].gt_lvl[8 * 2] = 0x550;  //INTERPOLATED

  mcu->phy_tr_dly.rank_dly[0].rd_lvl[0 * 2] = 0x32;
  mcu->phy_tr_dly.rank_dly[0].rd_lvl[1 * 2] = 0x35; //INTERPOLATED
  mcu->phy_tr_dly.rank_dly[0].rd_lvl[2 * 2] = 0x35; //INTERPOLATED
  mcu->phy_tr_dly.rank_dly[0].rd_lvl[3 * 2] = 0x35; //INTERPOLATED
  mcu->phy_tr_dly.rank_dly[0].rd_lvl[4 * 2] = 0x36;
  mcu->phy_tr_dly.rank_dly[0].rd_lvl[5 * 2] = 0x34;
  mcu->phy_tr_dly.rank_dly[0].rd_lvl[6 * 2] = 0x35;
  mcu->phy_tr_dly.rank_dly[0].rd_lvl[7 * 2] = 0x2A;
  mcu->phy_tr_dly.rank_dly[0].rd_lvl[8 * 2] = 0x35; //INTERPOLATED

}

// =================================================
// =================================================
// =================================================
// =================================================
// =================================================

void kc_phy_drv_strength_slew_setup(void *ptr)
{
  //int unsigned readData = 0;
  int unsigned wdata = 0;
  struct apm_mcu *mcu = (struct apm_mcu *)ptr;
  //  phy_write_reg(mcu, , );
  //   = phy_read_reg(mcu, );

  // Python routines def drv_strength_slew_setup():
  //                                       reportRXSTREN = 120
  //   kc_io_strength_setup(40,16,16,16,16,reportRXSTREN)
  /*
     def kc_io_strength_setup(dq_stren,ad_stren,cmd_stren,ctl_stren,clk_stren,odt_stren):
     BIT_DQ_STREN = cfg_drv_stren_array[dq_stren]
     BIT_AD_STREN = cfg_drv_AdCmdCtlClk_stren_array[ad_stren]
     BIT_CMD_STREN = cfg_drv_AdCmdCtlClk_stren_array[cmd_stren]
     BIT_CTL_STREN = cfg_drv_AdCmdCtlClk_stren_array[ctl_stren]
     BIT_CLK_STREN = cfg_drv_AdCmdCtlClk_stren_array[ctl_stren]
     BIT_ODT_STREN = cfg_odt_stren[odt_stren]

     cfg_drv_stren_array = {"OFF":0x0,
     53:0x1,
     48:0x2,
     44:0x3,
     40:0x4,
     37:0x5,
     34:0x6,
     32:0x7}
     cfg_drv_AdCmdCtlClk_stren_array = {"OFF":0x0,
     48:0x1,
     40:0x2,
     34:0x3,
     30:0x4,
     20:0x5,
     17:0x6,
     16:0x7}
     cfg_odt_stren = {"OFF":0x0,
     240:0x1,
     120:0x2,
     80:0x3,
     60:0x4,
     30:0x5,
     21:0x6,
     20:0x7}
   */

  //   #kc_io_strength_setup(40,16,16,16,16,80)
  //   kc_io_slew_setup(0x2,0x2,0x2,0x2,0x3)
  /*
     kc_io_slew_setup(dq_slew,ad_slew,cmd_slew,ctl_slew,clk_slew):
     BIT_DQ_SLEW =  dq_slew
     BIT_AD_SLEW = ad_slew
     BIT_CMD_SLEW = cmd_slew
     BIT_CTL_SLEW = ctl_slew
     BIT_CLK_SLEW = clk_slew
   */

  //   i2c_write_CFG_ANALOG_CONFIG_2((BIT_CMD_STREN << 18) | (BIT_AD_SLEW << 16) | (BIT_AD_STREN << 13) | (BIT_DQ_SLEW << 8) | (BIT_DQ_STREN << 5) | (BIT_DQ_SLEW << 3) | BIT_DQ_STREN)

  wdata =
      ((mcu->phy_params.bit_cmd_stren & 0x7) << 18) |
      ((mcu->phy_params.bit_ad_slew & 0x3) << 16) |
      ((mcu->phy_params.bit_ad_stren & 0x7) << 13) |
      ((mcu->phy_params.bit_dq_slew & 0x3) << 8) |
      ((mcu->phy_params.bit_dq_stren & 0x7) << 5) |
      ((mcu->phy_params.bit_dq_slew & 0x3) << 3) |
      (mcu->phy_params.bit_dq_stren & 0x7);
  phy_write_reg(mcu, PHY_REG_CFG_ANALOG_CONFIG_2, wdata); // 0x3c
  //   i2c_write_CFG_ANALOG_CONFIG_3((BIT_ODT_STREN << 12) | (BIT_CLK_SLEW << 10) | (BIT_CLK_STREN << 7) | (BIT_CTL_SLEW << 5) | (BIT_CTL_STREN << 2) | BIT_CMD_SLEW)

  wdata =
      ((mcu->phy_params.bit_odt_stren & 0x7) << 12) |
      ((mcu->phy_params.bit_clk_slew & 0x3) << 10) |
      ((mcu->phy_params.bit_clk_stren & 0x7) << 7) |
      ((mcu->phy_params.bit_ctl_slew & 0x3) << 5) |
      ((mcu->phy_params.bit_ctl_stren & 0x7) << 2) |
      (mcu->phy_params.bit_cmd_slew & 0x3);
  phy_write_reg(mcu, PHY_REG_CFG_ANALOG_CONFIG_3, wdata); // 0x40

  return;
}       // kc_phy_drv_strength_slew_setup

// =================================================
// =================================================
//  main Driver for PHY setup setup
// =================================================
// =================================================

int mcu_kc_phy_setup_tc(void *ptr)
{
  // Redefined from KC testchip setup
  //  NOTE: Test chip uses I2C - delyas between
  //
  unsigned int wdata, readData, dat;
  struct apm_mcu *mcu = (struct apm_mcu *)ptr;
  phy_param_t *p_phy = &mcu->phy_params;
  int unsigned __attribute__ ((unused)) en_dll_cal =
      p_phy->en_phy_dll_cal;
  int unsigned __attribute__ ((unused)) lo_freq = p_phy->dll_cal_lo_freq;

  // KC PHY setup timing paramters from Mcu/SPD settings
#if APM_SIM
#else
  debug("Mcu PHY %1d   param setup ...x4=%1d dllcal=%1d lofreq=%1d \n",
        mcu->id, mcu->mcu_params.by4_mode, en_dll_cal, lo_freq);
#endif
  debug("MCU-PHY %d: INFO: Finish KC PLL Lock stuff \n", mcu->id);
  // CFG_PHY_RESET is ONLY in TC, not in Product  i2c_write_CFG_PHY_RESET(0x0)
  // JHR 5/29 mcu->phy_wr(mcu, PHY_REG_CFG_PLL_RESET, 0x0);
  // JHR 5/29 DELAY(120);
  // JHR 5/29 mcu->phy_wr(mcu, PHY_REG_CFG_PHY_RESET, 0x0);
  // JHR 5/29 DELAY(120);
  mcu->phy_wr(mcu, PHY_REG_CFG_CDR_RESETB, 0x0);
  DELAY(120);
  mcu->phy_wr(mcu, PHY_REG_CFG_PRBS_RESETB, 0x0);
  DELAY(120);
  mcu->phy_wr(mcu, PHY_REG_CFG_PHY_SRST, 0x1);
  DELAY(120);

  // setup Dimm timings
  // KC PHY Timing Init
  kc_phy_timing_param_setup(ptr);

  debug("MCU-PHY %d: INFO: drive strengthn-slew setup \n", mcu->id);
  kc_phy_drv_strength_slew_setup(ptr);  // TC Python routines (_apm)

  debug("MCU-PHY %d: INFO: CSR Setup \n", mcu->id);
  kc_phy_quick_setup(ptr);  // JHR moved 5/29

  wdata = (((mcu->phy_params.TWLMRD) & 0xFF) << 24) | (((mcu->phy_params.TMOD) & 0xFF) << 16) | (((mcu->phy_params.twrlvl_ww) & 0xFF) << 8) | // tWRLVL_WW
      ((mcu->phy_params.TRP) & 0xFF);
  phy_write_reg(mcu, PHY_REG_CFG_DDR_PARAM_1, wdata);

  wdata = (((mcu->phy_params.TRCD) & 0xFF) << 24) | (((mcu->phy_params.TWRD) & 0xFF) << 16) | (((mcu->phy_params.WL) & 0xFF) << 8) |  //
      ((mcu->phy_params.RL) & 0xFF);
  phy_write_reg(mcu, PHY_REG_CFG_DDR_PARAM_2, wdata);

  debug("KC PHY-%1d  INFO:  ", mcu->id);
  debug("WL=%2d RL=%2d \n", mcu->phy_params.WL, mcu->phy_params.RL);

  debug("MCU-PHY %d: INFO: CDR LOCK start\n", mcu->id);
  kc_phy_cdr_lock(ptr); // CDR reset & lock & deassert_phy_soft_reset

  debug("MCU-PHY %d: INFO: DLL Cal not enabled\n", mcu->id);
  // KC recommends not using DLL Calibration

  debug("MCU-PHY %d: INFO: 180 enabled\n", mcu->id);
  // NOTE: Address calibration - 180 deg
  phy_write_reg(mcu, PHY_REG_CFG_ADDR_CAL_EN, 0x25);  // 0xf58
  DELAY(20);
  readData = 0;
  while (readData == 0) {
    readData = phy_read_reg(mcu, PHY_REG_CFG_ADDR_CAL_DONE);  // 0xf5c
  }

  /* PostTC rtl settings */
  dat = phy_rf_read_dqs_weak_pull_down_disable(ptr);  // Read value to check
  // JHR value 0x0 by default - weak pull down on
  if (mcu->phy_params.phy_disable_pullup) {
    dat =
        (dat & 0xFFFFFFFE) | (0x1 & mcu->phy_params.
            phy_disable_pullup);
    phy_rf_write_dqs_weak_pull_down_disable(ptr, dat);
  }
  // Added 26sept2012 - added for R29 release
  // JHR phy_rf_write_cfg_timeout_counter(ptr, (0x7FF << 10)); //
  phy_rf_write_cfg_timeout_counter(ptr, (0x3FFFFF << 10));  //

  // same as below kc_phy_set_wrlvl_func(ptr, 1);   // set WrLvl OR gate
  dat = phy_rf_read_spare_register_1_0(ptr);
  //dat = (dat & 0xFFFFFFFC) | (0x2);
  dat = (dat & 0xFFFFFFFC) | (PHY_WRLVL_USE_OR_GATE << 1);
  // bit 0 must be 0 in 1:1 mode !!!DUHHHHHHHHHH!!
  // bit 1 = 1 for WrLvl OR gate ( = 0 for AND gate)
  phy_rf_write_spare_register_1_0(ptr, dat);  // Wr Lvl OR gate

  DELAY(20);
  readData = phy_read_reg(mcu, PHY_REG_CFG_CMD_CODE); // 0xf34
  debug("INFO: KC PHY-%1d PI+180 Code: 0x%0x\n", mcu->id, readData);

  if (p_phy->phy_short_gt_preamble_en != 0) {
    dat = mcu->phy_params.phy_short_gt_preamble_val;
    mcu->phy_wr(mcu, PHY_REG_CFG_GATE_PRE_VAL_3, dat);
    dat = ((dat & 0xFF) << 24) |
        ((dat & 0xFF) << 16) | ((dat & 0xFF) << 8) | ((dat & 0xFF));
    mcu->phy_wr(mcu, PHY_REG_CFG_GATE_PRE_VAL_1, dat);
    mcu->phy_wr(mcu, PHY_REG_CFG_GATE_PRE_VAL_2, dat);
  }

  debug("Mcu PHY  init config done. Ready for dfi_init_start...\n");
  return 0;
}       // mcu_kc_phy_setup_tc

//-------------------------------------------

int mcu_kc_phy_setup_tc_prbs(void *ptr)
{
  // Redefined from KC testchip setup
  //  NOTE: Test chip uses I2C - delyas between
  //
  struct apm_mcu *mcu = (struct apm_mcu *)ptr;
  int unsigned __attribute__ ((unused)) en_dll_cal =
      mcu->phy_params.en_phy_dll_cal;
  int unsigned __attribute__ ((unused)) lo_freq =
      mcu->phy_params.dll_cal_lo_freq;

  // KC PHY setup timing paramters from Mcu/SPD settings
#if APM_SIM
#else
  debug
      ("Mcu PHY %1d   initial DCR config starting...x4=%1d dllcal=%1d lofreq=%1d \n",
       mcu->id, mcu->mcu_params.by4_mode, en_dll_cal, lo_freq);
  kc_phy_timing_param_setup(ptr);
#endif
  // Original replace
  debug("MCU-PHY %d: INFO: CDR LOCK start\n", mcu->id);
  // kc_phy_cdr_lock(ptr); // CDR reset & lock
  kc_phy_pre_dfi_reset(ptr);  //JHR tmp 1/31 PRBS

  debug("MCU-PHY %d: INFO: Setup \n", mcu->id);
  kc_phy_quick_setup_prbs(ptr);

  debug("MCU-PHY %d: INFO: DLL Cal not enabled\n", mcu->id);

  debug("MCU-PHY %d: INFO: 180 enabled\n", mcu->id);

  kc_phy_drv_strength_slew_setup(ptr);  // TC from Python routines

  // JHR TMP 1/31 // Added 26sept2012 - added for R29 release
  // JHR TMP 1/31 phy_rf_write_cfg_timeout_counter(ptr, (0x7FF<<10) );
  // JHR TMP 1/31 // same as below kc_phy_set_wrlvl_func(ptr, 1);   // set WrLvl OR gate
  // JHR TMP 1/31 dat = phy_rf_read_spare_register_1_0(ptr);
  // JHR TMP 1/31 dat = (dat & 0xFFFFFFFD) | (0x2);
  // JHR TMP 1/31 phy_rf_write_spare_register_1_0(ptr, dat); // Wr Lvl OR gate
  debug
      ("Mcu PHY  initial DCR configuration finished. Ready for dfi_init_start...\n");

  // Copy PHY training fixed delays
  // init_bypss_fix_kc1333(ptr);

  return 0;
}       // mcu_kc_phy_setup_tc_prbs

