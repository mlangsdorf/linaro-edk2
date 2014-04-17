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

#ifndef _DDR_LIB_H_
#define _DDR_LIB_H_

#if defined(APM_SIM)

#define APM_MARKERN(num)	//apm_markern(num)
extern void apm_markern(int);
#define APM_MARKERN_WRITE32(_ocm_addr, _data32) *((volatile unsigned int*)_ocm_addr)=(_data32)
#define OCM_C0_TEST_PRGS_ADDR       0x1d0FF00C
extern void exec_dsb(void);
#define DSB_SY_CALL     exec_dsb()
#define DSB_SY_CALL_WDELAY   {DELAY(5);exec_dsb();}

#elif defined(APM_VBIOS)

#include <common.h>
#define APM_MARKERN(num)
#define APM_MARKERN_WRITE32(_ocm_addr, _data32)
#define DSB_SY_CALL     asm volatile("dsb sy")

#define DSB_SY_CALL_WDELAY     {DELAY(5); asm volatile("dsb sy"); }

#elif defined(APM_TIANOCORE)

#include <Library/IoLib.h>
#include <Include/APMXGeneSlimPROCSR.h>
#include <Library/I2CLib/I2CLib.h>
#include <Library/BaseMemoryLib.h>
#include <Library/TimerLib.h>
#include <Library/DebugLib.h>
#define CONFIG_SYS_SCU_BASE     0x17000000
#define APM_MPA_REG_OFFSET      0x1000
#define APM_MARKERN(num)
#define APM_MARKERN_WRITE32(_ocm_addr, _data32)
#define DSB_SY_CALL     asm volatile("dsb sy")
#define DSB_SY_CALL_WDELAY     {DELAY(5);asm volatile("dsb sy");}
#define getenv_ulong(x, y, z)	(z)
#define printf		info
#define readl		MmioRead32
#define writel(v, a)	MmioWrite32((a), (v))
#define i2c_read	I2c_Read
#define i2c_write	I2c_Write
#define memset(p, v, s) SetMem((p), (s), (v))
#define udelay		MicroSecondDelay
typedef UINT32    u32;
typedef UINT64    u64;
extern void print_size (unsigned long long size, const char *s);

#define DDR_INFO
#undef DDR_DBG

#ifdef DDR_DBG
#define debug(arg...) DEBUG ((EFI_D_ERROR,## arg))
#else
#define debug(arg...)
#endif

#ifdef DDR_INFO
#define info(arg...) DEBUG ((EFI_D_INFO,## arg))
#else
#define info(arg...)
#endif

#else

#include <common.h>
#define APM_MARKERN(num)
#define APM_MARKERN_WRITE32(_ocm_addr, _data32)
#define DSB_SY_CALL     asm volatile("dsb sy")
#define DSB_SY_CALL_WDELAY     {DELAY(5);asm volatile("dsb sy");}

#endif

#define DDR_SCU_WRITE32(_scu_offset, _data32) *(volatile unsigned int*)(SCU_BASE_ADDR+_scu_offset) = (_data32)
#define DDR_SCU_READ32(_scu_offset) (unsigned int)(*(volatile unsigned int*)(SCU_BASE_ADDR+_scu_offset))

// Build Options - fixed and otherwise
#define DO_INIT_SEQ_CTLUPDATE 0x0U

#define PHY_ZQCAL_CODE_VALUE 0xa2f
#define PHY_EN_SW_CTL_UP_ZQ 0
#define PHY_WRLVL_USE_OR_GATE 1     //WRLVL-PRIME DQ (0: AND-GATE 1: OR-GATE)
#define FIX_WRLVL_BACKOFF
//#define FIX_WRLVL_BACKOFF_NOTFULL     // To be used in future
#define FIX_WRLVL_BACKOFF_MVALUE 0x2U //Multiply - for doing 2/3
#define FIX_WRLVL_BACKOFF_DVALUE 0x3U //Divide

#define FIX_WRLVL_BIT8_BEFOREWRCAL

//#define FIX_BROKEN_WRCAL_PERMACRO    // Not yet matured

#define CMP_BROKEN_WRDQ_VALUE 0x30
#define FIX_BROKEN_WRDQ_PERMACRO
#define FIX_BROKEN_WRDQ_VALUE 0x48

#define CLEAR_WRDESKEW_TRIM

//#define DEFAULT_WRLVL_VALUE  0x0U
//#define FIX_DEFAULT_WRLVL

#define CHANGE_WRCAL_PATTERN
#define CHANGE_WRCAL_PAT1 0xFF00FF00
#define CHANGE_WRCAL_PAT2 0xAA5555AA

//#define FIX_DEFAULT_WRDQX
//#define DEFAULT_WR_DQX_VALUE 0x60U

#define DEFAULT_RDEYE_VALUE  0x20U
#define FIX_DEFAULT_RDE
#define FIX_DEFAULT_RDE_BFRDSK
#define FIX_DEFAULT_RDE_BEF2ND

#define CMP_BROKEN_RDEYE_VALUE 0x20U

#define FIX_BROKEN_RDEYE_PERMACRO
#define FIX_BROKEN_RDEYE_VALUE 0x40U	// This value might change based on DIMM/SPEED
// #define KCPHY_PEVM_STSIZE_2 1
// #define FIX_BROKEN_WRCAL_PERMACRO    // Not yet matured


#define USE_KCTC_PLL_VALS 0x0

#ifdef APM_SIM
#define SKIP_SPD_INIT      0x1
#define SKIP_TIMING_CONFIG 0x1
#else
#define SKIP_SPD_INIT      0
#define SKIP_TIMING_CONFIG 0
#endif

#define MCU_ENABLE_MASK  0x1
#define DESIRED_DUAL_MCB    1
#define DESIRED_MCB_INTRLV  1
#define DESIRED_DUAL_MCU    1
#define DESIRED_MCU_INTRLV  1
#define DESIRED_RANK_INTRLV 1
#define DESIRED_RANK_HASHEN 1
#define DESIRED_RANK_HASH   0x3U

#define MC_DIMM_SPEED   1600

#ifdef APM_SIM
#define MC_ECC_SCHEME 3
#define BIST_TEST_NUMBER 0x0
#else
#define MC_ECC_SCHEME 3
#define BIST_TEST_NUMBER 0x0
#endif

#define MCU_SPEC_READ 0x1U
#define DIMM_ADDR_MIRROR_CTRL 0xAAU
#define DIMM_MR1_RTTNOM_U1R_DIC   0x46U	                  // Single Rank UDIMM (DIMM-staticODT=40ohm)
#define DIMM_MR1_RTTNOM_U2R_DIC   DIMM_MR1_RTTNOM_U1R_DIC // OLD-[0x2U	// Dual Rank UDIMM   (DIMM-staticODT=OFF)]
#define DIMM_MR1_RTTNOM_DIC       DIMM_MR1_RTTNOM_U1R_DIC // Backwards compatibility.. using original # define in POP files.
#define DIMM_MR2_RTTWR_U1R        0x0U	                  // Single Rank DIMM   (DIMM-dynamicODT=OFF)
#define DIMM_MR2_RTTWR_U2R        DIMM_MR2_RTTWR_U1R      // OLD-[0x2U	// Dual Rank UDIMM    (DIMM-dynamicODT=120ohm)]
#define DIMM_MR2_RTTWR            DIMM_MR2_RTTWR_U1R	  // Backwards compatibility.. using original # define in POP files.
#define DIMM_RANK_MASK  0x1U
#define DIMM_DESKEW_RANK_MASK 0x0U

#define MCU_PHY_EARLY_RDGATELVL_ENAB 0

#define PHY_PEVM_RETRAIN_EN 0x0U
#define PHY_PEVM_RETRAIN_WRLVL_EN 0x1U
#define PHY_PEVM_RETRAIN_GTLVL_EN 0x0U
#define PHY_PEVM_RETRAIN_RDLVL_EN 0x1U
#define PHY_PEVM_RETRAIN_DIS_DYNODT 0x1U

#define PHY_DIS_UP_54_58_5C               0x1U
#define PHY_INIT_VAL_CMD_ADDR_DELAY_54_58 0x80U
#define PHY_INIT_VAL_CTL_DELAY_5C         0x80U
#define PHY_EN_POSTTR_2T_ADJ_CMD_ADDR     0x0U
#define PHY_POSTTR_ADJ_VAL_2T_CMD_ADDR_DELAY 0x80U

#define KCPHY_ADD_T_CRL_MARGIN         0x1
#define KCPHY_SUB_T_CWL_MARGIN         0x0
#define KCPHY_FIXED_READEN_DELAY       0x7
#define KCPHY_USE_READ_W_FIXED_DELAY   0x1

#define KCPHY_DISABLE_PULLUP 0x1U
#define KCPHY_PEVM_WRLVL_SMPL_PER_DLY  0x6U
#define KCPHY_PEVM_WRLVL_MIN_SMPLS     0x20U
#define KCPHY_PEVM_GTLVL_SMPL_PER_DLY  0x7U
#define KCPHY_PEVM_GTLVL_MIN_SMPLS     0x80U
#define KCPHY_PEVM_RDLVL_SMPL_PER_DLY  0xDU

#define KCPHY_SHORT_GT_PREAMBLE_EN 0x1U
#define KCPHY_SHORT_GT_PREAMBLE_VAL 0x90U

#define KCPHY_CFG_MACRO_x8_MASK    0x15555U
#define KCPHY_CFG_MACRO_x4_MASK    0x3FFFFU
#define KCPHY_CFG_MACRO_ENABLE_VAL 0x3FFFFU
#define KCPHY_CFG_MACRO_NOECC_MASK 0x0FFFFU
#define KCPHY_PRBS_DM_STATUS_MASK  0x000U

#define KCPHY_BIT_DQ_STREN    0x6U
#define KCPHY_BIT_AD_STREN    0x4U
#define KCPHY_BIT_CMD_STREN   0x4U
#define KCPHY_BIT_CTL_STREN   0x4U
#define KCPHY_BIT_CLK_STREN   0x6U
#define KCPHY_BIT_ODT_STREN   0x4U

#define KCPHY_BIT_DQ_SLEW     0x2U	//For 1866DIMM with ECC: 0x3U
#define KCPHY_BIT_AD_SLEW     0x1U	//For 1866DIMM with ECC: 0x2U
#define KCPHY_BIT_CMD_SLEW    0x1U	//For 1866DIMM with ECC: 0x2U
#define KCPHY_BIT_CTL_SLEW    0x1U	//For 1866DIMM with ECC: 0x2U
#define KCPHY_BIT_CLK_SLEW    0x1U	//For 1866DIMM with ECC: 0x2U

// Arch timer delays
#if defined(APM_SIM)
extern void arch_timer_udelay(unsigned int usec);
#define DELAY(x)    arch_timer_udelay(x)
#define DELAYP(x)   arch_timer_udelay(x)
#else

#ifdef APM_VBIOS
#define DELAY(x)    USDELAY(x)
#define DELAYP(x)   MSDELAY(x)

#else
#define DELAY(x)    udelay(x)
#define DELAYP(x)   udelay(x*1000)
#endif
#endif

//  Function headers

unsigned int csw_read_reg(void *, unsigned int);
void csw_write_reg(void *, unsigned int, unsigned int);
unsigned int mcu_read_reg(void *p, unsigned int reg);
void mcu_write_reg(void *p, unsigned int reg, unsigned int value);
unsigned int mcu_regmod(void *p, unsigned int reg, unsigned int value,
			unsigned int bh, unsigned int bl);
unsigned int mcb_read_reg(void *p, unsigned int reg);
void mcb_write_reg(void *p, unsigned int reg, unsigned int value);
unsigned int phy_read_reg(void *p, unsigned int reg);
void phy_write_reg(void *p, unsigned int reg, unsigned int value);

int mcu_pre_init(void *);
int mcu_post_init(void *);
int spd_ddr_init(void *);

// Generic paramters  populate_mc_default_parms() - calls functions for Speed
int populate_mc_default_parms(void *ptr);

// ddr_fixed_configs.c
int fixed_mcu_config(void *ptr);

int mcu_csr_config(void *ptr);
int mcu_csr_config22(void *ptr);

int mcu_post_train_setup(void *ptr);
int mem_test1_raj(int unsigned olcnt);
int mem_test2_ds(void);
int mem_test2_64_raj(int unsigned olcnt);
int mem_test_kc1(int unsigned olcnt);
int mem_test_kc2(int unsigned olcnt, unsigned int addr_start,
		 unsigned int addr_end);
int pop_mc_cfg_def_1mcu_1mcu_ddr1600J_x8_1RK2G(void *ptr);
int pop_mc_cfg_def_1mcu_1mcu_ddr1550J_x8_1RK2G(void *ptr);
int pop_mc_cfg_def_1mcu_1mcu_ddr1333H_9_7_x8_1RK2G(void *ptr);
int pop_mc_cfg_def_1mcu_1mcu_ddr1066F_8_6_x8_1RK2G(void *ptr);
int pop_mc_cfg_def_1mcu_1mcu_ddr800D_6_5_x8_1RK2G(void *ptr);

// ddr_mcu.c
int mcu_reset_status_poll(void *p, unsigned int status, unsigned int mask,
			  unsigned int flag);
int mcu_init_done_poll(void *p);
void mcu_reset_FSM_poll(void *p, unsigned int status, unsigned int flag);

int mcu_pre_assert_mc_pwr(void *ptr);
int mcu_assert_mc_pwr_ok(void *);
int mcu_post_assert_mc_pwr(void *ptr);
int mcu_post_assert_mc_pwr_tc(void *ptr);
int dimm_mcu_fsm_init(void *ptr);
int mcu_en_traffic_mem_init_done(void *ptr);
int mcu_en_traffic_mem_test1_raj(void *ptr);
int mcu_bist_check_in_prog(void *ptr);
int mcu_en_bist_init_done_R0(void *ptr);
int mcu_en_bist_init_done_R1(void *ptr);
int mcu_en_bist_init_done_R01(void *ptr);
int mcu_bist_walk_one_row_test(void *ptr);
int mcu_bist_chk_b2b_test(void *ptr);
int mcu_bist_shmoo_test(void *ptr);
int mcu_bist_chk_b2b_multi_rank_test(void *ptr);
int memc_ecc_init_en(void *ptr);	//memc ptr
int mcu_phy_ctl_update_loop(void *ptr);
void mcu_phy_rdfifo_reset(void *ptr);

void mcu_set_SWISS_TRNLOAD(void *p);
void mcu_set_SWISS_ODTADDR(void *ptr, int unsigned enab, int unsigned bnk	/* [2:0] */
			   , int unsigned addr	/* [15:0] */
			   , int unsigned odtRd, int unsigned odtWr);
void mcu_set_SWISS_TRNCTL(void *ptr, int unsigned enab, int unsigned wrlvl_en, int unsigned rdlvl_gate_en, int unsigned rdlvl_en, int unsigned wrlvl_cs_n	//[7:0]= 'hFF
			  , int unsigned rdlvl_cs_n	//[7:0]= 'hFF
    );
void mcu_set_SWISS_OPCTL(void *ptr, int unsigned sendOp, int unsigned rddata_en, int unsigned cmd_n	//[2:0] = 'h7
			 , int unsigned cs_n	//[7:0] = 'hFF
    );

// ddr_phy.c
void phy_restore_train_dly_csrs(void *p, int unsigned rankmask,
				int unsigned setWr, int unsigned setGt,
				int unsigned setRd);
void phy_save_train_dly_csrs(void *p);
void init_phy_tr_dly_vals(void *p);
int calib_bypss_fix(void *p);
int mcu_kc_phy_setup_org(void *ptr);
int mcu_kc_phy_setup_tc(void *ptr);	// from kc_phy_util_task.c
int mcu_kc_phy_setup_tc_prbs(void *ptr);
int calib_pevm_seperate_steps(void *ptr);
int retrain_pevm_sep_steps(void *ptr);
int phy_correct_rdeye_delays(void *ptr, unsigned int rank);
int phy_redo_check_rdeye(void *ptr, unsigned int rank, unsigned int redo);


void init_bypss_fix_kc1333(void *p);

//! PHY LOOPBACK Routine
int mcu_kc_phy_pbrs_loopback(void *);

// ddr_util.c
int memsys_unreset(void *p);
void CSWCR_setup(void *p, unsigned int mask);
void mcb_mode_setup(void *p, unsigned int mode, unsigned int spec_read);
int mcb_mcu_init_clock_deassert_reset(void *p);
void phy_poll_reg(void *p, unsigned int reg, unsigned int value,
		  unsigned int mask);
int memc_addr_cfg(void *ptr);
int mcu_rank_addr_cfg(void *p, unsigned int mcb_intrlv, unsigned int mcu_intrlv,
		      unsigned int full_addr);

// ddr_config.c
int ddr_spd_init(void *);
int mcu_timing_config(void *);
unsigned int getRttNomfromMR1(unsigned int mr1val);
unsigned int putRttNomintoMR1(unsigned int mr1val, unsigned int rttnom);
unsigned int minAllowedRankHash(unsigned int hash_size, unsigned int rank_size,
		unsigned int rank_config, unsigned int rank_base_low);


int memc_dummy_fn(void *);

// Enums for polling
#define POLL_GREATER	2
#define POLL_LESS	1
#define POLL_EQUAL      0

#endif /* _DDR_LIB_H_ */

