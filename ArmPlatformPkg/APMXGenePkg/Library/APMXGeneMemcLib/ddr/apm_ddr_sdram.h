/**
 * SPD SDRAM detection code supports APM cpu's with DDR2/3 controller
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

#ifndef __APM_SPD_DDR_H__
#define __APM_SPD_DDR_H__

// --------------------------------------------------------------
// Platform Ifdefs
// --------------------------------------------------------------

#if defined(APM_SIM)

#ifndef debug
#define debug   pcpprintf
#endif
#include "ddr_spd.h"

#elif defined(APM_VBIOS)

#include "common.h"
extern unsigned int g_ddr_relax_en;
extern unsigned int g_ddr_relax_margin_0;
extern unsigned int g_ddr_relax_margin_1;
extern unsigned int g_ddr_cl_margin;
extern unsigned int g_ddr_rd2rdmargin[4];
extern unsigned int g_ddr_rd2wrmargin[4];
extern unsigned int g_ddr_wr2wrmargin[4];
extern unsigned int g_ddr_wr2rdmargin[4];
extern unsigned int g_ddr_pll_force;
extern unsigned int g_ddr_pll_div[4];
extern unsigned int g_ddr_en_rddeskew;
extern unsigned int g_ddr_en_rdlvl2nd;
extern unsigned int g_ddr_en_wrdeskew;
extern unsigned int g_ddr_tcrl[];
extern unsigned int g_ddr_tcwl[];
extern unsigned int g_ddr_mr_valid;
extern unsigned int g_ddr_mr_rttnom;
extern unsigned int g_ddr_mr_rttnom1;
extern unsigned int g_ddr_mr_rttwr;
extern unsigned int g_ddr_mr_rttwr1;
extern unsigned int g_ddr_wrlvl_min_smpl;
extern unsigned int g_ddr_wrlvl_smpl_per_dly;
#ifdef debug
#undef debug
#endif
#define debug(fmt,args...)     lprintf(8, fmt ,##args)

#include <types.h>
#ifdef CONFIG_PD
#define PALLADIUM
#endif

#include "ddr_spd.h"

#elif defined(APM_TIANOCORE)

#include "ddr_spd.h"

#else

#include "common.h"
#include <asm/types.h>
#include "../../../cpu/potenza/storm/ddr/ddr_spd.h"

#endif

//-----------------------------------------------------------------

#ifndef max
#define max(a,b) (a > b ? a : b)
#endif
#ifndef min
#define min(a,b) (a < b ? a : b)
#endif

typedef spd_eeprom_t generic_spd_eeprom_t;

#ifndef CONFIG_SYS_NUM_DDR_CTLRS
#define CONFIG_SYS_NUM_DDR_CTLRS 4
#endif

#define CONFIG_SYS_DIMM_SLOTS_PER_CTLR 2
#define CONFIG_SYS_NO_OF_DIMMS CONFIG_SYS_NUM_DDR_CTLRS*CONFIG_SYS_DIMM_SLOTS_PER_CTLR

#define APM_UMC_BLOCK_MQ	0	/* UMC MQ CSR block */
#define APM_UMC_BLOCK_NWL	1	/* UMC NWL CSR block */
#define APM_UMC_OFFSET_NWL	0x2000
#define APM_UMC_BASE		APM_CSR_UMC0_BASE_LO

#define MEM_DDR			1 /**< DDR1 memory */
#define MEM_DDR1		2 /**< DDR1 memory */
#define MEM_DDR2		4 /**< DDR2 memory */
#define MEM_DDR3		8 /**< DDR3 memory */

#define SCU_BASE_ADDR 0x17000000
#define SCU_SOC_PWR_CTL 0x70

#define PCP_RB_BASE		0x7C000000

/*
 * PCP page 
 */
#define RB_CSW_PAGE		0x220
#define RB_MCB_PAGE		0x270
#define RB_MCU_PAGE		0x280

/*
 * CSW
 */
#define PCP_RB_CSW_BASE		PCP_RB_BASE + 0x2200000
#define RB_CSWCR		0x0
#define RB_MCB_REG_OFFSET	0x100
#define RB_MCB0RCR		0x400
#define RB_MCB0CCR		0x408
#define RB_MCB1RCR		0x500
#define RB_MCB1CCR		0x508

/*
 * MCB
 */
#define PCP_RB_MCB_BASE		PCP_RB_BASE + 0x2700000
#define PCP_RB_MCB_OFFSET	0x0020000
#define RB_MCB_ADDRRMR		0x0
#define RB_MCB_SPECRMR		0x4
#define RB_MCB_MCU_PLLRST	0xC0
#define RB_MCB_MCU_PLLCTL0	0xC4
#define RB_MCB_MCU_PLLCTL1	0xC8
#define RB_MCB_MCU_PLLSTS	0xCC
#define RB_MCB_MCU_CLKCTL	0xD0
#define RB_MCB_MCU_RSTCTL	0xD4
#define RB_MCB_MCU_OFFSET	0x20

/*
 * Memory Controller Unit
 */
#define PCP_RB_MCU_BASE		PCP_RB_BASE + 0x2800000
#define	PCP_RB_MCU_OFFSET	0x0040000
#define	MCU_PMU_OFFSET		0x0010000
#define	MCU_PHY_OFFSET		0x0020000

#ifdef CONFIG_DDR_IO_CALIB
#endif

/** Types of memory sizes */
typedef enum {
	MB256,	/**< 256 MB */
	MB512,	/**< 512 MB */
	MB1024,	/**< 1024 MB */
	MB2048,	/**< 2048 MB */
	MB4096,	/**< 4096 MB */
	MBSIZEMAX
} component_mem_size_e;

/** Types of memory speed grades */
typedef enum {
	MHZ133,	/**< 133 MHz : 266Mbps */
	MHZ167,	/**< 167 MHz : 333Mnps */
	MHZ200,	/**< 200 MHz : 400Mbps */
	MHZ267,	/**< 267 MHz : 533Mbps */
	MHZ333,	/**< 333 MHz : 666Mbps */
	MHZ400,	/**< 400 MHz : 800Mbps */
	MHZ533,	/**< 533 MHz : 1066Mbps */
	MHZ667,	/**< 667 MHz : 1333Mbps */
	MHZ800,	/**< 800 MHz : 1600Mbps */
	MHZ933,	/**< 933 MHz : 1866Mbps */
	MHZ1067, /**< 1067 MHz : 2133Mbps */
	MHZ1200, /**< 1200 MHz : 2400Mbps */
	MHZSPEEDMAX
} component_speed_grade_e;

/** Types of memory configurations */
typedef enum {
	CFG64Mx4,     /**< 64MB x 4 type config for 256MB */
	CFG32Mx8,     /**< 32MB x 8 type config for 256MB */
	CFG16Mx16,    /**< 16MB x 16 type config for 256MB */
	CFG128Mx4 = 0,/**< 128MB x 4 type config for 512MB */
	CFG64Mx8,     /**< 64MB x 8 type config for 512MB */
	CFG32Mx16,    /**< 32MB x 16 type config for 512MB */
	CFG256Mx4 = 0,/**< 256MB x 4 type config for 1024MB */
	CFG128Mx8,    /**< 128MB x 8 type config for 1024MB */
	CFG64Mx16,    /**< 64MB x 16 type config for 1024MB */
	CFG512Mx4 = 0,/**< 512MB x 4 type config for 2048MB */
	CFG256Mx8,    /**< 256MB x 8 type config for 2048MB */
	CFG128Mx16,   /**< 128MB x 16 type config for 2048MB */
	CFG1024Mx4 = 0,
		      /**< 1024MB x 4 type config for 4096MB */
	CFG512Mx8,    /**< 512MB x 8 type config for 4096MB */
	CFG256Mx16,   /**< 256MB x 16 type config for 4096MB */
	CFGMAX = 2
} dimm_mem_config_e;

/** Types of dimm type */
typedef enum {
	UDIMM,
	RDIMM,
	SODIMM,
	RSODIMM,
	LRDIMM,
	UNKNOWN
} dimm_type_e;

#define MAX_SPEED_CFG		7
#define MAX_SIZE		5
#define MAX_CONFIG		3

/* Default memory config */
#define DEF_MEM_TYPE		MEM_DDR2
#ifndef CONFIG_ISS
#define DEF_SPEED_GRD		MHZ400
#define DEF_MEM_SIZE		MB4096
#define DEF_MEM_CONFIG		CFG512Mx8
#else
#define DEF_SPEED_GRD		MHZ133
#define DEF_MEM_SIZE		MB512
#define DEF_MEM_CONFIG		CFG64Mx4
#endif

#ifndef TRUE
#define TRUE            1
#endif
#ifndef FALSE
#define FALSE           0
#endif

#define ONE_BILLION     1000000000
#define SIZE256MB       0x10000000
#define MPIC_FRR        0x1000
#define MULDIV64(m1, m2, d)     (unsigned int)(((unsigned long)(m1) * (unsigned long)(m2)) / (unsigned long)(d))

/* Parameters for a DDR2 dimm computed from the SPD */
typedef struct dimm_params_s {

	/* DIMM organization parameters */
	char mpart[19];		/* guaranteed null terminated */

	unsigned int n_ranks;
	unsigned long long rank_density;
	unsigned long long capacity;
	unsigned int data_width;
	unsigned int primary_sdram_width;
	unsigned int ec_sdram_width;
	unsigned int registered_dimm;

	/* RDIMM RC values from SPD */
	unsigned int rca;
	unsigned int rcb;

	/* SDRAM device parameters */
	unsigned int n_row_addr;
	unsigned int n_col_addr;
	unsigned int edc_config;	/* 0 = none, 1 = parity, 2 = ECC */
	unsigned int n_banks_per_sdram_device;
	unsigned int burst_lengths_bitmask;	/* BL=4 bit 2, BL=8 = bit 3 */
	unsigned int row_density;
	unsigned int component_width;	/*  */

	/* used in computing base address of DIMMs */
	unsigned long long base_address;
	/* mirrored DIMMs */
	unsigned int mirrored_dimm;	/* only for ddr3 */

	/* DIMM timing parameters */

	unsigned int mtb_ps;	/* medium timebase ps, only for ddr3 */
	unsigned int tAA_ps;	/* minimum CAS latency time, only for ddr3 */
	unsigned int tFAW_ps;	/* four active window delay, only for ddr3 */

	/*
	 * SDRAM clock periods
	 * The range for these are 1000-10000 so a short should be sufficient
	 */
	unsigned int tCKmin_X_ps;
	unsigned int tCKmin_X_minus_1_ps;
	unsigned int tCKmin_X_minus_2_ps;
	unsigned int tCKmax_ps;

	/* SPD-defined CAS latencies */
	unsigned int caslat_X;
	unsigned int caslat_X_minus_1;
	unsigned int caslat_X_minus_2;

	unsigned int caslat_lowest_derated;	/* Derated CAS latency */

	/* basic timing parameters */
	unsigned int tRCD_ps;
	unsigned int tRP_ps;
	unsigned int tRAS_ps;

	unsigned int tWR_ps;	/* maximum = 63750 ps */
	unsigned int tWTR_ps;	/* maximum = 63750 ps */
	unsigned int tRFC_ps;	/* max = 255 ns + 256 ns + .75 ns
				   = 511750 ps */

	unsigned int tRRD_ps;	/* maximum = 63750 ps */
	unsigned int tRC_ps;	/* maximum = 254 ns + .75 ns = 254750 ps */

	unsigned int refresh_rate_ps;

	/* Output driver impedance */
	unsigned int output_driver;

	/* DDR3 doesn't need these as below */
	unsigned int tIS_ps;	/* byte 32, spd->ca_setup */
	unsigned int tIH_ps;	/* byte 33, spd->ca_hold */
	unsigned int tDS_ps;	/* byte 34, spd->data_setup */
	unsigned int tDH_ps;	/* byte 35, spd->data_hold */
	unsigned int tRTP_ps;	/* byte 38, spd->trtp */
	unsigned int tDQSQ_max_ps;	/* byte 44, spd->tdqsq */
	unsigned int tQHS_ps;	/* byte 45, spd->tqhs */
} dimm_params_t;

typedef struct {
	/* parameters to constrict */

	unsigned int tCKmin_X_ps;
	unsigned int tCKmax_ps;
	unsigned int tCKmax_max_ps;
	unsigned int tRCD_ps;
	unsigned int tRP_ps;
	unsigned int tRAS_ps;

	unsigned int tWR_ps;	/* maximum = 63750 ps */
	unsigned int tWTR_ps;	/* maximum = 63750 ps */
	unsigned int tRFC_ps;	/* maximum = 255 ns + 256 ns + .75 ns
				   = 511750 ps */

	unsigned int tRRD_ps;	/* maximum = 63750 ps */
	unsigned int tRC_ps;	/* maximum = 254 ns + .75 ns = 254750 ps */
	unsigned int tFAW_ps;	/*  */

	unsigned int refresh_rate_ps;

	unsigned int tIS_ps;	/* byte 32, spd->ca_setup */
	unsigned int tIH_ps;	/* byte 33, spd->ca_hold */
	unsigned int tDS_ps;	/* byte 34, spd->data_setup */
	unsigned int tDH_ps;	/* byte 35, spd->data_hold */
	unsigned int tRTP_ps;	/* byte 38, spd->trtp */
	unsigned int tDQSQ_max_ps;	/* byte 44, spd->tdqsq */
	unsigned int tQHS_ps;	/* byte 45, spd->tqhs */

	unsigned int ndimms_present;
	unsigned int lowest_common_SPD_caslat;
	unsigned int highest_common_derated_caslat;
	unsigned int additive_latency;
	unsigned int cas_write_latency;
	unsigned int cas_read_latency;
	unsigned int all_DIMMs_burst_lengths_bitmask;
	unsigned int all_DIMMs_registered;
	unsigned int all_DIMMs_unbuffered;
	unsigned int all_DIMMs_ECC_capable;

	unsigned long long total_mem;
	unsigned long long base_address;
} timing_params_t;

typedef struct mcu_param {
	/* MCU registers that are not SPD derived */
	dimm_type_e dimm_type;
	unsigned int rc_en;
	unsigned int speed;
	unsigned int speed_desired;
	unsigned int speed_supported;
	unsigned int clk_mhz_max;
	unsigned int clk_mhz_pll;
	unsigned int ranksdisable[CONFIG_SYS_DIMM_SLOTS_PER_CTLR];
	unsigned int ranksperslot[CONFIG_SYS_DIMM_SLOTS_PER_CTLR];
	unsigned long long minranksize;	/* Common minimum rank size across all slots */
	unsigned int ECCenable;
	unsigned int ECCscheme;
	unsigned int cl;	/* Lowest Common CAS RL */
	unsigned int t_crl;	/* CAS read latency minus one */
	unsigned int t_cwl;	/* CAS write latency minus one */
	unsigned int burst_len;
	unsigned int tmargin;

	unsigned int activeslots;	/* one hot dimm preset */
	unsigned int activeranks;	/* one hot rank preset */

	/* MCB register PLL setting for one Mcu */
	// unsigned int ;
	unsigned int /*       */ pllctl0_ssen;
	unsigned int /* [9:0] */ pllctl0_vstep;
	unsigned int /* [6:0] */ pllctl0_ss_mod;
	unsigned int /* [1:0] */ pllctl0_odiv;
	unsigned int /* [8:0] */ pllctl0_fbdiv;
	unsigned int /* [2:0] */ pllctl0_idiv;
	unsigned int /* [11:0] */ pllctl1_tm_ctrl;
	unsigned int /*       */ pllctl1_pdn;
	unsigned int /*       */ pllctl1_bypass;
	unsigned int /*       */ single_clock_mode;

	/* MCU registers */
	unsigned int mode_reg[4];	/* MRS 0-4 Mode register setting */
	unsigned int rttnom_wrlvl;	/* RttNom during Wr Lvl only three allowed */
	unsigned int rttnom;	/* RttNom for normal Ops */
	unsigned int rttwr;	/* Dynamic ODT RttWr */
	unsigned int rank_mask_disable_rttnom;	/*Disable RttNom for quad ranks */

	unsigned int clks200us;
	unsigned int clks500us;
	unsigned int clkstxpr;
	unsigned int clkstmrd;
	unsigned int clkstmod;
	unsigned int clkstzqc_zqs;
	unsigned int clkstzqc_zql;
	unsigned int clks6us;

	unsigned int rank_rd_odt[8];
	unsigned int rank_wr_odt[8];

	unsigned int hpweight;
	unsigned int lpweight;
	unsigned int wpweight;
	unsigned int maxinterval;
	unsigned int quantumsize;
	unsigned int agethres_hp;
	unsigned int agethres_lp;
	unsigned int agethres_wp;
	unsigned int page_mode;
	unsigned int by4_mode;
	unsigned int hash_enable;
	unsigned int desired_rank_hash_en;
	unsigned int desired_rank_hash;
	unsigned int mirror_ctrl;
	unsigned int fast_cpu_enable;
	unsigned int desired_rank_intrlv;

	/* RDIMM RC values per 2 ranks - always four registers */
	unsigned int rca[4];
	unsigned int rcb[4];

	unsigned int bank_actpre;
	unsigned int bank_rdpre;
	unsigned int bank_wrpre;
	unsigned int bank_preact;
	unsigned int bank_actact;
	unsigned int bank_rdaact;
	unsigned int bank_wraact;
	unsigned int bank_actrd;
	unsigned int bank_actwr;
	unsigned int bank_actrda;
	unsigned int bank_actwra;

	unsigned int rank_actact;
	unsigned int rank_rdrd;
	unsigned int rank_wrwr;
	unsigned int rank_rdwr;
	unsigned int rank_wrrd;
	unsigned int rank_actfaw;
	unsigned int sys_rdrd;
	unsigned int sys_wrwr;
	unsigned int sys_rdwr;
	unsigned int sys_wrrd;

	unsigned int rank_refactref;
	unsigned int rank_refint;
	unsigned int rank_ref_burst_cnt;

	unsigned int zqcctl_enable;
	unsigned int zqcctl_interval;

	unsigned int zqcdly;

	unsigned long long rank_size[8];
	unsigned int rank_config[8];
	unsigned int rank_hash[8];
	unsigned int rank_base_low[8];
	unsigned int rank_base_high[8];
	unsigned int rank_mask_low[8];
	unsigned int rank_mask_high[8];

	unsigned int scrub_ctrl;
	unsigned long long scrub_start;
	unsigned long long scrub_end;

	unsigned int glb_err_ctrl;

	unsigned int sleep_ctrl;
	unsigned int lsleep_ctrl;
	unsigned int dsleep_ctrl;

	unsigned int phy_pm_ctl;

	unsigned int rank_srxnodll;
	unsigned int rank_srxdll;
	unsigned int rank_ckemin;
	unsigned int rank_pdxnodll;
	unsigned int rank_pdxdll;
	unsigned int rank_rdpde;
	unsigned int rank_wrpde;
	unsigned int rank_wrapde;
	unsigned int rank_odtl;

	unsigned int sram_sleep_ctrl;
	unsigned int sram_rmw_ctrl;

	unsigned int tWRLVL_WW;
	unsigned int tRDLVL_RR;
} mcu_param_t;

typedef struct rnk_tr_dly_val {
	unsigned int wr_lvl[18];
	unsigned int gt_lvl[18];
	unsigned int rd_lvl[18];
	unsigned int fix_wr_lvl[18];
	unsigned int fix_gt_lvl[18];
	unsigned int fix_rd_lvl[18];
} rnk_tr_dly_val_t;

typedef struct phy_tr_dly_val {
	unsigned int rank_mask;
	unsigned int phy_wrcal_rank_mask;
	unsigned int sw_wrcal_rank_mask;
	unsigned int wrdeskew_rank_mask;
	unsigned int rddeskew_rank_mask;
	unsigned int rdlvl2nd_rank_mask;
	unsigned int wrlvl_max_delay_limit;	/*11:0 */
	unsigned int gtlvl_max_delay_limit;	/*11:0 */
	unsigned int rdlvl_max_delay_limit;	/*11:0 */
	unsigned int wrcal_max_delay_limit;	/*11:0 */
	unsigned int wrlvl_smpl_per_dly;
	unsigned int gtlvl_smpl_per_dly;
	unsigned int rdlvl_smpl_per_dly;
	unsigned int wrlvl_min_smpl;	/*7:0 */
	unsigned int gtlvl_min_smpl;	/*7:0 */
	unsigned int wrlvl_dly_stsize;	/*7:0 */
	unsigned int rdlvl_dly_stsize;	/*7:0 */
	unsigned int gtlvl_dly_stsize;	/*7:0 */
	unsigned int cfg_gate_retrain_val;
	unsigned int fix_wrlvl_flg;
	unsigned int fix_gtlvl_flg;
	unsigned int fix_rdlvl_flg;
	rnk_tr_dly_val_t rank_dly[8];
	unsigned int wrdq_dly[18];
  unsigned int rd_dsk[9];
  unsigned int wr_dsk[9];
} phy_tr_dly_val_t;

typedef struct phy_param {
	unsigned int phy_train_mode;	/* Use 2 for PEVM / 1 for MC Eval */
	unsigned int cfg_parity_oe;	/*Output enable parity ports */
	unsigned int pevm_retrain_en;
	unsigned int pevm_retrain_wr;
	unsigned int pevm_retrain_gt;
	unsigned int pevm_retrain_rd;
	unsigned int en_phy_dll_cal;
	unsigned int dll_cal_lo_freq;
	unsigned int phy_disable_pullup;
	unsigned int phy_short_gt_preamble_en;
	unsigned int phy_short_gt_preamble_val;

	unsigned int phy_dis_up_54_58_5C;
	unsigned int init_val_cmd_addr_dly_54_58;
	unsigned int init_val_ctl_dly_5C;
	unsigned int en_2T_adj_incr_latency;
	unsigned int en_posttr_2T_adj_cmd_addr_dly;
	unsigned int posttr_val_2T_cmd_addr_dly;

	unsigned int cfg_macro_en_val;
	unsigned int cfg_cke_en;
	unsigned int cfg_odt_en;
	unsigned int cfg_ck_en;
	unsigned int cfg_cs_en;
	unsigned int prbs_dm_status_mask;
	unsigned int zqcal_code;
	unsigned int TRCD;
	unsigned int TMOD;
	unsigned int TMRD;
	unsigned int TRP;
	unsigned int TWLMRD;
	unsigned int TWRD;
	unsigned int WL;
	unsigned int RL;
	unsigned int twrlvl_ww;
	unsigned int bit_dq_stren;
	unsigned int bit_ad_stren;
	unsigned int bit_cmd_stren;
	unsigned int bit_ctl_stren;
	unsigned int bit_clk_stren;
	unsigned int bit_odt_stren;
	unsigned int bit_dq_slew;
	unsigned int bit_ad_slew;
	unsigned int bit_cmd_slew;
	unsigned int bit_ctl_slew;
	unsigned int bit_clk_slew;
} phy_param_t;

typedef struct apm_mcu {
	unsigned int id;
	unsigned int enabled;
	unsigned int mcb_id;
	unsigned long phy_addr;
	unsigned long csw_base;
	unsigned long mcb_base;
	unsigned long base;

	unsigned int (*mcb_rd) (void *, unsigned int);
	void (*mcb_wr) (void *, unsigned int, unsigned int);
	unsigned int (*mcu_rd) (void *, unsigned int);
	void (*mcu_wr) (void *, unsigned int, unsigned int);
	unsigned int (*mcu_rmw) (void *, unsigned int, unsigned int,
				 unsigned int, unsigned int);
	unsigned int (*csw_rd) (void *, unsigned int);
	void (*csw_wr) (void *, unsigned int, unsigned int);
	unsigned int (*phy_rd) (void *, unsigned int);
	void (*phy_wr) (void *, unsigned int, unsigned int);

	//void (*mcu_reset)(void); -> moved to memc level
	int (*p_spd_init) (void *);
	int (*p_pll_config) (void *);
	int (*p_timing_config) (void *);
	int (*p_csr_config) (void *);

	// pre_init calls -> phy_setup & phy_pre_init
	int (*p_pre_init) (void *);
	int (*p_phy_setup) (void *);
	int (*p_phy_pre_init) (void *);
	// After pre_init -> MC_POWER_OK 
	// post_init calls  -> phy_post_init & mcu_post_init > training or bypass
	int (*p_post_init) (void *);
	int (*p_phy_post_init) (void *);
	int (*p_dimm_post_init) (void *);
	int (*p_phy_calib) (void *);
	unsigned int prbs_test;
	int (*p_prbs_test) (void *);
	unsigned int bist_test;
	int (*p_post_train_setup) (void *);
	int (*p_bist_test) (void *);
	int (*p_meminitdone) (void *);
	int (*p_phy_retrain) (void *);

	mcu_param_t mcu_params;
	phy_param_t phy_params;
	generic_spd_eeprom_t spd_info[CONFIG_SYS_DIMM_SLOTS_PER_CTLR];
	dimm_params_t dimm_params[CONFIG_SYS_DIMM_SLOTS_PER_CTLR];
	timing_params_t timing_params;
	phy_tr_dly_val_t phy_tr_dly;

	/*
	 * I2C SPD address
	 */
	unsigned char spd_mux;	/* SPD mux I2C address */
	unsigned char spd_mux_addr;	/* SPD mux address for this MCU */
	unsigned char spd_addr[CONFIG_SYS_DIMM_SLOTS_PER_CTLR];
} apm_mcu_t;

typedef struct apm_mcb {
	unsigned int desired_dual_mcu;
	unsigned int desired_mcu_intrlv;
	unsigned int dual_mcu;
	unsigned int mcu_intrlv;
	unsigned int spec_read;
} apm_mcb_t;

typedef struct apm_mem_space {
	/* Up to five memory regions */
	unsigned int num_mem_regions;
	unsigned long long str_addr[5];
	unsigned long long end_addr[5];
} apm_mem_space_t;

typedef struct apm_memc {
	unsigned int dual_mcb;
	unsigned int mcb_intrlv;
	unsigned int full_addr;
	unsigned int desired_dual_mcb;
	unsigned int desired_mcb_intrlv;

	struct apm_mcb mcb[2];
	struct apm_mcu mcu[4];
	struct apm_mem_space memspace;
	int (*p_memsys_unreset) (void *);
	int (*p_mcb_reset) (void *);
	int (*p_mcu_reset) (void *);
	int (*p_mc_pwr_ok) (void *);
	int (*p_addressmap) (void *);
	int (*p_tlb_map) (void *);
	int (*p_mem_test_init) (void *);	/* Final step to test &/or init all MC memory  */
	// Outside functions
	int (*p_setup) (void *, unsigned int);	/* Call to setup data-struct & functions */
	int (*p_spdcal) (void *, unsigned int);	/* Call to Read SPD & Calc timing */
	int (*p_init) (void *, unsigned int);	/* Main function to kick-off training */
} apm_memc_t;

int ddr_sys_setup(void *ptr, unsigned int flag);
int ddr_sys_spd_calc(void *ptr, unsigned int flag);
int ddr_sys_init(void *, unsigned int flag);

#endif

