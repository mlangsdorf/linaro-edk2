/**
 * Copyright (c) 2014, AppliedMicro Corp. All rights reserved.
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
 
#define XGENET_PLL_STAT                         0x00000250
#define XGENET_PLL_CFG                          0x00000240
#define XGENET_PLL_DIV_CFG                      0x0000024c
#define XGENET_SDS_RST_CTL                      0x0000001c
#define XGENET_SDS_CTL0                         0x0000000c
#define SATA_ENET_CLK_MACRO_REG                 0x0000004c
#define SATA_ENET_SDS_RST_CTL                   0x00000024
#define SATA_ENET_SDS_CTL0                      0x0000000c
#define SATA_ENET_SDS_CMU_STATUS0               0x00000014
#define SATA_ENET_SDS0_RXTX_STATUS              0x00000018
#define CFG_TX_O_TX_READY_F1_RD(src)            (((src) & 0x00100000) >> 20)
#define CFG_RX_O_RX_READY_F1_RD(src)            (((src) & 0x00000001))

#define XGENET_SDS_CMU_STATUS0                  0x00000014
#define CFG_CMU_O_PLL_READY0_RD(src)            (((src) & 0x00000001))
#define CFG_CMU_O_VCO_CALDONE0_RD(src)          (((src) & 0x00000004) >> 2)
#define CFG_CMU_O_PLL_LOCK0_RD(src)             (((src) & 0x00000002) >> 1)
#define XGENET_SDS_RXTX_STATUS                  0x00000018

#define CFG_TX_O_TX_READY_RD(src)               (((src) & 0x00100000) >> 20)
#define CFG_RX_O_RX_READY_RD(src)               (((src) & 0x00000001))

#define CMU_REG16_TX_RATE_CHANGE_ENA_CH0        15
#define CMU_REG16_RX_RATE_CHANGE_ENA_CH0        14
#define CMU_REG16_TX_RATE_CHANGE_ENA_CH1        13
#define CMU_REG16_RX_RATE_CHANGE_ENA_CH1        12
#define CMU_REG16_TX_RATE_CHANGE_ENA_CH2        11
#define CMU_REG16_RX_RATE_CHANGE_ENA_CH2        10
#define CMU_REG16_TX_RATE_CHANGE_ENA_CH3        9
#define CMU_REG16_RX_RATE_CHANGE_ENA_CH3        8

enum eth_port {
	ENET_0 = 0,
	ENET_1,
	ENET_2,
	ENET_3,
	XGENET_0,
	XGENET_1,
	XGENET_2,
	XGENET_3,
};

static void cmu_toggle0to10(struct xgene_phy_ctx *ctx, enum cmu_type_t cmu_type,
			u32 reg, u32 bits)
{
	cmu_clrbits(ctx, cmu_type, reg, bits);
	cmu_toggle1to0(ctx, cmu_type, reg, bits);
}

static void enet_phy_reset_rxa(struct xgene_phy_ctx *ctx, int port)
{
	u32 lane = port & 0x1;

	serdes_clrbits(ctx, lane, RXTX_REG7, RXTX_REG7_RESETB_RXA_MASK);
	/* As per PHY design spec, the reset requires a minimum of 100us. */
	usleep_range(100, 150);
	serdes_setbits(ctx, lane, RXTX_REG7, RXTX_REG7_RESETB_RXA_MASK);
}

void enet_phy_reset_rxd_rxa(struct xgene_phy_ctx *ctx, int port)
{
	u32 lane;

	lane = port & 0x1;
	xgene_phy_reset_rxd(ctx, lane);
	enet_phy_reset_rxa(ctx, lane);
}

static void xgenet_phy_cmu_cfg(struct xgene_phy_ctx *ctx)
{
	u32 value;
	u32 infmode;
	u32 pll_manualcal = 0;

	infmode = (ctx->mode == MODE_XFI) ? 1 : 0;
	if (ctx->mode == MODE_SGMII) {
		cmu_rd(ctx, PHY_CMU, CMU_REG12, &value);
		value = CMU_REG12_STATE_DELAY9_SET(value, 1);
		cmu_wr(ctx, PHY_CMU, CMU_REG12, value);

		cmu_rd(ctx, PHY_CMU, CMU_REG13, &value);
		value = CMU_REG13_STATE_DELAY1_SET(value, 15);
		value = CMU_REG13_STATE_DELAY2_SET(value, 1);
		value = CMU_REG13_STATE_DELAY3_SET(value, 2);
		value = CMU_REG13_STATE_DELAY4_SET(value, 2);
		cmu_wr(ctx, PHY_CMU, CMU_REG13, value);

		cmu_rd(ctx, PHY_CMU, CMU_REG14, &value);
		value = CMU_REG14_STATE_DELAY5_SET(value, 2);
		value = CMU_REG14_STATE_DELAY6_SET(value, 2);
		value = CMU_REG14_STATE_DELAY7_SET(value, 1);
		value = CMU_REG14_STATE_DELAY8_SET(value, 4);
		cmu_wr(ctx, PHY_CMU, CMU_REG14, value);
	}
	cmu_rd(ctx, PHY_CMU, CMU_REG1, &value);
	value = CMU_REG1_REFCLK_CMOS_SEL_SET(value, 0);
	cmu_wr(ctx, PHY_CMU, CMU_REG1, value);

	cmu_rd(ctx, PHY_CMU, CMU_REG2, &value);
	value = CMU_REG2_PLL_REFDIV_SET(value, 0);
	value = CMU_REG2_PLL_FBDIV_SET(value, infmode ? 32 : 49);
	cmu_wr(ctx, PHY_CMU, CMU_REG2, value);

	cmu_rd(ctx, PHY_CMU, CMU_REG9, &value);
	value = CMU_REG9_PLL_POST_DIVBY2_SET(value, infmode ? 0 : 1);
	value = CMU_REG9_TX_WORD_MODE_CH0_SET(value, infmode ? 6 : 1);
	cmu_wr(ctx, PHY_CMU, CMU_REG9, value);

	cmu_rd(ctx, PHY_CMU, CMU_REG1, &value);
	value = CMU_REG1_PLL_CP_SET(value, infmode ? 11 : 10);
	value = CMU_REG1_PLL_CP_SEL_SET(value, infmode ? 5 : 1);
	cmu_wr(ctx, PHY_CMU, CMU_REG1, value);

	cmu_rd(ctx, PHY_CMU, CMU_REG3, &value);
	value = CMU_REG3_VCOVARSEL_SET(value, infmode ? 15 : 0);
	cmu_wr(ctx, PHY_CMU, CMU_REG3, value);

	cmu_rd(ctx, PHY_CMU, CMU_REG2, &value);
	value = CMU_REG2_PLL_LFRES_SET(value, infmode ? 5 : 15);
	cmu_wr(ctx, PHY_CMU, CMU_REG2, value);

	cmu_rd(ctx, PHY_CMU, CMU_REG5, &value);
	value = CMU_REG5_PLL_LFSMCAP_SET(value, infmode ? 0 : 3);
	value = CMU_REG5_PLL_LFCAP_SET(value, infmode ? 0 : 3);
	value = CMU_REG5_PLL_LOCK_RESOLUTION_SET(value, infmode ? 4 : 7);
	cmu_wr(ctx, PHY_CMU, CMU_REG5, value);

	cmu_rd(ctx, PHY_CMU, CMU_REG8, &value);
	value = CMU_REG8_PLL_UCDIV_SET(value, 7);
	value = CMU_REG8_CH3_0_PLL_UCDIV(value, infmode ? 0 : 0xaa);
	cmu_wr(ctx, PHY_CMU, CMU_REG8, value);

	cmu_rd(ctx, PHY_CMU, CMU_REG6, &value);
	value = CMU_REG6_PLL_VREGTRIM_SET(value, 0);
	value = CMU_REG6_USR_CLK_BUF_ENA_SET(value, infmode ? 1 : 0);
	cmu_wr(ctx, PHY_CMU, CMU_REG6, value);

	cmu_rd(ctx, PHY_CMU, CMU_REG32, &value);
	value = CMU_REG32_IREF_ADJ_SET(value, 3);
	cmu_wr(ctx, PHY_CMU, CMU_REG32, value);

	cmu_rd(ctx, PHY_CMU, CMU_REG1, &value);
	value = CMU_REG1_PLL_MANUALCAL_SET(value, pll_manualcal);
	cmu_wr(ctx, PHY_CMU, CMU_REG1, value);

	cmu_rd(ctx, PHY_CMU, CMU_REG3, &value);
	value = CMU_REG3_VCO_MANMOMSEL_SET(value, infmode ? 5 : 0xd);
	value = CMU_REG3_VCO_MOMSEL_INIT_SET(value, infmode ? 16 : 0xd);
	cmu_wr(ctx, PHY_CMU, CMU_REG3, value);

	cmu_rd(ctx, PHY_CMU, CMU_REG34, &value);
	value = CMU_REG34_VCO_CAL_VTH_HI_MIN_SET(value, 2);
	value = CMU_REG34_VCO_CAL_VTH_HI_MAX_SET(value, 10);
	value = CMU_REG34_VCO_CAL_VTH_LO_MIN_SET(value, 2);
	value = CMU_REG34_VCO_CAL_VTH_LO_MAX_SET(value, 10);
	cmu_wr(ctx, PHY_CMU, CMU_REG34, value);

	cmu_rd(ctx, PHY_CMU, CMU_REG0, &value);
	value = CMU_REG0_CAL_COUNT_RESOL_SET(value, 7);
	cmu_wr(ctx, PHY_CMU, CMU_REG0, value);

	cmu_rd(ctx, PHY_CMU, CMU_REG16, &value);
	value = CMU_REG16_VCOCAL_WAIT_BTW_CODE_SET(value, 7);
	cmu_wr(ctx, PHY_CMU, CMU_REG16, value);

	cmu_rd(ctx, PHY_CMU, CMU_REG30, &value);
	value = CMU_REG30_LOCK_COUNT_SET(value, 3);
	cmu_wr(ctx, PHY_CMU, CMU_REG30, value);

	if (infmode) {
		cmu_rd(ctx, PHY_CMU, CMU_REG13, &value);
		value = CMU_REG13_STATE_DELAY1_SET(value, 15);
		value = CMU_REG13_STATE_DELAY2_SET(value, 15);
		value = CMU_REG13_STATE_DELAY3_SET(value, 15);
		value = CMU_REG13_STATE_DELAY4_SET(value, 15);
		cmu_wr(ctx, PHY_CMU, CMU_REG13, value);

		cmu_rd(ctx, PHY_CMU, CMU_REG14, &value);
		value = CMU_REG14_STATE_DELAY5_SET(value, 15);
		value = CMU_REG14_STATE_DELAY6_SET(value, 15);
		value = CMU_REG14_STATE_DELAY7_SET(value, 15);
		value = CMU_REG14_STATE_DELAY8_SET(value, 15);
		cmu_wr(ctx, PHY_CMU, CMU_REG14, value);
	}

	cmu_rd(ctx, PHY_CMU, CMU_REG30, &value);
	/*
	 * Ref Divider for PCI Gen3 mode - dont care,
	 * FB divider for Gen3 mode - dont care
	 * Post Divider for Gen3 mode - dont care
	 */
	value = CMU_REG30_PCIE_MODE_SET(value, 0);
	cmu_wr(ctx, PHY_CMU, CMU_REG30, value);

	cmu_rd(ctx, PHY_CMU, CMU_REG0, &value);
	value = CMU_REG0_PCIEGEN3_SET(value, 0);
	cmu_wr(ctx, PHY_CMU, CMU_REG0, value);

	cmu_rd(ctx, PHY_CMU, CMU_REG32, &value);
	value = CMU_REG32_PVT_CAL_WAIT_SEL_SET(value, 3);
	cmu_wr(ctx, PHY_CMU, CMU_REG32, value);

	cmu_rd(ctx, PHY_CMU, CMU_REG31, &value);
	value = CMU_REG31_OVERRIDE_CH3_0_SET(value, 15);
	cmu_wr(ctx, PHY_CMU, CMU_REG31, value);

	cmu_rd(ctx, PHY_CMU, CMU_REG37, &value);
	value = CMU_REG37_CAL_DONE_OVR_SET(value, 15);
	value = CMU_REG37_SEARCH_DONE_OVR_SET(value, 15);
	cmu_wr(ctx, PHY_CMU, CMU_REG37, value);
}

static void xgenet_phy_rxtx_cfg(struct xgene_phy_ctx *ctx)
{
	u32 infmode;
	u32 value, inst;
	u32 pq_reg = 0xa, tmp;

	infmode = (ctx->mode == MODE_XFI) ? 1 : 0;
	for (inst = 0; inst < 1; inst++) {
		/*  Tx CONTROL */
		serdes_rd(ctx, 0, RXTX_REG4, &value);
		value = RXTX_REG4_TX_DATA_RATE_SET(value, infmode ? 0 : 2);
		value = RXTX_REG4_TX_WORD_MODE_SET(value, infmode ? 6 : 1);
		value = RXTX_REG4_TX_PRBS_SEL_SET(value, infmode ? 4 : 4);
		serdes_wr(ctx, 0, RXTX_REG4, value);

		/* TX Rate Change enable: Toggle 0-1-0 */
		cmu_toggle0to10(ctx, PHY_CMU, CMU_REG16,
			CMU_REG16_TX_RATE_CHANGE_ENA_CH0);

		cmu_toggle0to10(ctx, PHY_CMU, CMU_REG16,
			CMU_REG16_TX_RATE_CHANGE_ENA_CH1);

		cmu_toggle0to10(ctx, PHY_CMU, CMU_REG16,
			CMU_REG16_TX_RATE_CHANGE_ENA_CH2);

		cmu_toggle0to10(ctx, PHY_CMU, CMU_REG16,
			CMU_REG16_TX_RATE_CHANGE_ENA_CH3);

		serdes_rd(ctx, 0, RXTX_REG2, &value);
		value = RXTX_REG2_TX_FIFO_ENA_SET(value, 1);
		serdes_wr(ctx, 0, RXTX_REG2, value);

		serdes_rd(ctx, 0, RXTX_REG6, &value);
		value = RXTX_REG6_TXAMP_ENA_SET(value, 1);
		value = RXTX_REG6_TXAMP_CNTL_SET(value, infmode ? 15 : 8);
		serdes_wr(ctx, 0, RXTX_REG6, value);

		serdes_rd(ctx, 0, RXTX_REG5, &value);
		value = RXTX_REG5_TX_CN1_SET(value, infmode ? 2 : 0);
		value = RXTX_REG5_TX_CP1_SET(value, infmode ? 15 : 0);
		value = RXTX_REG5_TX_CN2_SET(value, infmode ? 2 : 0);
		serdes_wr(ctx, 0, RXTX_REG5, value);

		serdes_rd(ctx, 0, RXTX_REG2, &value);
		value = RXTX_REG2_RESETB_TXD_SET(value, 1);
		serdes_wr(ctx, 0, RXTX_REG2, value);

		serdes_rd(ctx, 0, RXTX_REG4, &value);
		value = RXTX_REG4_TX_LOOPBACK_BUF_EN_SET(value, 0);
		serdes_wr(ctx, 0, RXTX_REG4, value);

		serdes_rd(ctx, 0, RXTX_REG2, &value);
		value = RXTX_REG2_BIST_ENA_TX_SET(value, 0);
		serdes_wr(ctx, 0, RXTX_REG2, value);

		serdes_rd(ctx, 0, RXTX_REG6, &value);
		value = RXTX_REG6_TX_IDLE_SET(value, 0);
		serdes_wr(ctx, 0, RXTX_REG6, value);

		serdes_rd(ctx, 0, RXTX_REG145, &value);
		value = RXTX_REG145_TX_IDLE_SATA_SET(value, 0);
		serdes_wr(ctx, 0, RXTX_REG145, value);

		serdes_rd(ctx, 0, RXTX_REG2, &value);
		value = RXTX_REG2_TX_INV_SET(value, 0);
		serdes_wr(ctx, 0, RXTX_REG2, value);

		/* RX Control */
		serdes_rd(ctx, 0, RXTX_REG2, &value);
		value = RXTX_REG2_RESETB_TERM_SET(value, 0);
		value = RXTX_REG2_VTT_ENA_SET(value, 1);
		value = RXTX_REG2_VTT_SEL_SET(value, 1);
		serdes_wr(ctx, 0, RXTX_REG2, value);

		serdes_rd(ctx, 0, RXTX_REG1, &value);
		value = RXTX_REG1_RXACVCM_SET(value, 7);
		if (infmode)
			value = RXTX_REG1_RXIREF_ADJ_SET(value, 3);
		serdes_wr(ctx, 0, RXTX_REG1, value);

		serdes_rd(ctx, 0, RXTX_REG12, &value);
		value = RXTX_REG12_RX_DET_TERM_ENABLE_SET(value, 0);
		serdes_wr(ctx, 0, RXTX_REG12, value);

		serdes_rd(ctx, 0, RXTX_REG7, &value);
		value = RXTX_REG7_RX_PRBS_SEL_SET(value, 4);
		value = RXTX_REG7_RX_WORD_MODE_SET(value, infmode ? 6 : 1);
		value = RXTX_REG7_RX_DATA_RATE_SET(value, infmode ? 0 : 2);
		serdes_wr(ctx, 0, RXTX_REG7, value);

		/*  RX rate change enable: Toggle 0-1-0 */
		cmu_toggle0to10(ctx, PHY_CMU, CMU_REG16,
			CMU_REG16_RX_RATE_CHANGE_ENA_CH0);

		cmu_toggle0to10(ctx, PHY_CMU, CMU_REG16,
			CMU_REG16_RX_RATE_CHANGE_ENA_CH1);

		cmu_toggle0to10(ctx, PHY_CMU, CMU_REG16,
			CMU_REG16_RX_RATE_CHANGE_ENA_CH2);

		cmu_toggle0to10(ctx, PHY_CMU, CMU_REG16,
			CMU_REG16_RX_RATE_CHANGE_ENA_CH3);

		serdes_rd(ctx, 0, RXTX_REG148, &value);
		value = RXTX_REG148_BIST_WORD_CNT0_SET(value, 0xFFFF);
		serdes_wr(ctx, 0, RXTX_REG148, 0xFFFF);

		serdes_rd(ctx, 0, RXTX_REG149, &value);
		value = RXTX_REG149_BIST_WORD_CNT1_SET(value, 0xFFFF);
		serdes_wr(ctx, 0, RXTX_REG149, 0xFFFF);

		serdes_rd(ctx, 0, RXTX_REG150, &value);
		value = RXTX_REG150_BIST_WORD_CNT2_SET(value, 0xFFFF);
		serdes_wr(ctx, 0, RXTX_REG150, 0xFFFF);

		serdes_rd(ctx, 0, RXTX_REG151, &value);
		value = RXTX_REG151_BIST_WORD_CNT_3_SET(value, 0xffff);
		serdes_wr(ctx, 0, RXTX_REG151, 0xFFFF);

		serdes_rd(ctx, 0, RXTX_REG147, &value);
		value = RXTX_REG147_STMC_OVERRIDE_SET(value, 6);
		serdes_wr(ctx, 0, RXTX_REG147, value);

		serdes_rd(ctx, 0, RXTX_REG1, &value);
		/* CTLE Full rate Control */
		tmp = 16;
		if (!preB0Chip) {  /* B0 */
			switch (ctx->lane) {
			case XGENET_0:
				tmp = 24;
				break;
			case XGENET_1:
				tmp = 28;
				break;
			case XGENET_2:
				tmp = 16;
				break;
			case XGENET_3:
				tmp = 28;
				break;
			}
		}
		value = RXTX_REG1_CTLE_EQ_SET(value, infmode ? tmp : 28);
		serdes_wr(ctx, 0, RXTX_REG1, value);

		serdes_rd(ctx, 0, RXTX_REG0, &value);
		value = RXTX_REG0_CTLE_EQ_HR_SET(value, infmode ? 16 : 13);
		value = RXTX_REG0_CTLE_EQ_QR_SET(value, infmode ? 16 : 13);
		value = RXTX_REG0_CTLE_EQ_FR_SET(value, infmode ? 16 : 13);
		serdes_wr(ctx, 0, RXTX_REG0, value);

		serdes_rd(ctx, 0, RXTX_REG14, &value);
		value = RXTX_REG14_CTLE_LATCAL_MAN_ENA_SET(value, 0);
		serdes_wr(ctx, 0, RXTX_REG14, value);

		serdes_rd(ctx, 0, RXTX_REG12, &value);
		value = RXTX_REG12_SUMOS_ENABLE_SET(value, 0);
		serdes_wr(ctx, 0, RXTX_REG12, value);

		serdes_rd(ctx, 0, RXTX_REG12, &value);
		value = RXTX_REG12_LATCH_OFF_ENA_SET(value, 1);
		serdes_wr(ctx, 0, RXTX_REG12, value);

		serdes_rd(ctx, 0, RXTX_REG128, &value);
		value = RXTX_REG128_LATCH_CAL_WAIT_SEL_SET(value, 3);
		serdes_wr(ctx, 0, RXTX_REG128, value);

		serdes_rd(ctx, 0, RXTX_REG127, &value);
		value = RXTX_REG127_LATCH_MAN_CAL_ENA_SET(value, 0);
		serdes_wr(ctx, 0, RXTX_REG127, value);

		serdes_rd(ctx, 0, RXTX_REG8, &value);
		value = RXTX_REG8_CDR_LOOP_ENA_SET(value, 1);
		value = RXTX_REG8_CDR_BYPASS_RXLOS_SET(value, infmode ? 0 : 1);
		serdes_wr(ctx, 0, RXTX_REG8, value);

		serdes_rd(ctx, 0, RXTX_REG61, &value);
		value = RXTX_REG61_SPD_SEL_CDR_SET(value, infmode ? 7 : 1);
		serdes_wr(ctx, 0, RXTX_REG61, value);

		/* NOTE: Need to implement per port contrl */
		serdes_rd(ctx, 0, RXTX_REG125, &value);
		/* IQ phase different */
		if (infmode) {
			if (ctx->lane == XGENET_3)
				pq_reg = 0x10;
		} else {
			pq_reg = 0;
		}
		value = RXTX_REG125_PQ_REG_SET(value, infmode ? pq_reg : 0);
		value = RXTX_REG125_PHZ_MANUAL_SET(value, 1);
		serdes_wr(ctx, 0, RXTX_REG125, value);

		serdes_rd(ctx, 0, RXTX_REG11, &value);
		value = RXTX_REG11_PHASE_ADJUST_LIMIT_SET(value, 0);
		serdes_wr(ctx, 0, RXTX_REG11, value);

		serdes_rd(ctx, 0, RXTX_REG61, &value);
		value = RXTX_REG61_LOADFREQ_SHIFT_SET(value, infmode ? 1 : 0);
		serdes_wr(ctx, 0, RXTX_REG61, value);

		serdes_rd(ctx, 0, RXTX_REG102, &value);
		value = RXTX_REG102_FREQLOOP_LIMIT_SET(value, 3);
		serdes_wr(ctx, 0, RXTX_REG102, value);

		serdes_rd(ctx, 0, RXTX_REG8, &value);
		value = RXTX_REG8_SSC_ENABLE_SET(value, 0);
		serdes_wr(ctx, 0, RXTX_REG8, value);

		serdes_rd(ctx, 0, RXTX_REG96, &value);
		value = RXTX_REG96_MU_FREQ1_SET(value, 16);
		value = RXTX_REG96_MU_FREQ2_SET(value, 16);
		value = RXTX_REG96_MU_FREQ3_SET(value, 16);
		serdes_wr(ctx, 0, RXTX_REG96, value);

		serdes_rd(ctx, 0, RXTX_REG97, &value);
		value = RXTX_REG97_MU_FREQ4_SET(value, 16);
		value = RXTX_REG97_MU_FREQ5_SET(value, 16);
		value = RXTX_REG97_MU_FREQ6_SET(value, 16);
		serdes_wr(ctx, 0, RXTX_REG97, value);

		serdes_rd(ctx, 0, RXTX_REG98, &value);
		value = RXTX_REG98_MU_FREQ7_SET(value, 16);
		value = RXTX_REG98_MU_FREQ8_SET(value, 16);
		value = RXTX_REG98_MU_FREQ9_SET(value, 16);
		serdes_wr(ctx, 0, RXTX_REG98, value);

		serdes_rd(ctx, 0, RXTX_REG99, &value);
		value = RXTX_REG99_MU_PHASE1_SET(value, infmode ? 5 : 8);
		value = RXTX_REG99_MU_PHASE2_SET(value, infmode ? 5 : 8);
		value = RXTX_REG99_MU_PHASE3_SET(value, infmode ? 5 : 8);
		serdes_wr(ctx, 0, RXTX_REG99, value);

		serdes_rd(ctx, 0, RXTX_REG100, &value);
		value = RXTX_REG100_MU_PHASE4_SET(value, infmode ? 5 : 8);
		value = RXTX_REG100_MU_PHASE5_SET(value, infmode ? 5 : 8);
		value = RXTX_REG100_MU_PHASE6_SET(value, infmode ? 5 : 8);
		serdes_wr(ctx, 0, RXTX_REG100, value);

		serdes_rd(ctx, 0, RXTX_REG101, &value);
		value = RXTX_REG101_MU_PHASE7_SET(value, infmode ? 5 : 8);
		value = RXTX_REG101_MU_PHASE8_SET(value, infmode ? 5 : 8);
		value = RXTX_REG101_MU_PHASE9_SET(value, infmode ? 5 : 8);
		serdes_wr(ctx, 0, RXTX_REG101, value);

		serdes_rd(ctx, 0, RXTX_REG8, &value);
		value = RXTX_REG8_SD_DISABLE_SET(value, 1);
		serdes_wr(ctx, 0, RXTX_REG8, value);

		serdes_rd(ctx, 0, RXTX_REG26, &value);
		value = RXTX_REG26_BLWC_ENA_SET(value, 1);
		serdes_wr(ctx, 0, RXTX_REG26, value);

		if (infmode == 0) {
			serdes_rd(ctx, 0, RXTX_REG31, &value);
			value = RXTX_REG31_DFE_PRESET_VALUE_H0_SET(value, 0);
			serdes_wr(ctx, 0, RXTX_REG31, value);
		}

		serdes_rd(ctx, 0, RXTX_REG81, &value);
		value = RXTX_REG81_MU_DFE1_SET(value, 14);
		value = RXTX_REG81_MU_DFE2_SET(value, 14);
		value = RXTX_REG81_MU_DFE3_SET(value, 14);
		serdes_wr(ctx, 0, RXTX_REG81, value);

		serdes_rd(ctx, 0, RXTX_REG82, &value);
		value = RXTX_REG82_MU_DFE4_SET(value, 14);
		value = RXTX_REG82_MU_DFE5_SET(value, 14);
		value = RXTX_REG82_MU_DFE6_SET(value, 14);
		serdes_wr(ctx, 0, RXTX_REG82, value);

		serdes_rd(ctx, 0, RXTX_REG83, &value);
		value = RXTX_REG83_MU_DFE7_SET(value, 14);
		value = RXTX_REG83_MU_DFE8_SET(value, 14);
		value = RXTX_REG83_MU_DFE9_SET(value, 14);
		serdes_wr(ctx, 0, RXTX_REG83, value);

		serdes_rd(ctx, 0, RXTX_REG84, &value);
		value = RXTX_REG84_MU_PH1_SET(value, 14);
		value = RXTX_REG84_MU_PH2_SET(value, 14);
		value = RXTX_REG84_MU_PH3_SET(value, 14);
		serdes_wr(ctx, 0, RXTX_REG84, value);

		serdes_rd(ctx, 0, RXTX_REG85, &value);
		value = RXTX_REG85_MU_PH4_SET(value, 14);
		value = RXTX_REG85_MU_PH5_SET(value, 14);
		value = RXTX_REG85_MU_PH6_SET(value, 14);
		serdes_wr(ctx, 0, RXTX_REG85, value);

		serdes_rd(ctx, 0, RXTX_REG86, &value);
		value = RXTX_REG86_MU_PH7_SET(value, 14);
		value = RXTX_REG86_MU_PH8_SET(value, 14);
		value = RXTX_REG86_MU_PH9_SET(value, 14);
		serdes_wr(ctx, 0, RXTX_REG86, value);

		serdes_rd(ctx, 0, RXTX_REG87, &value);
		value = RXTX_REG87_MU_TH1_SET(value, 14);
		value = RXTX_REG87_MU_TH2_SET(value, 14);
		value = RXTX_REG87_MU_TH3_SET(value, 14);
		serdes_wr(ctx, 0, RXTX_REG87, value);

		serdes_rd(ctx, 0, RXTX_REG88, &value);
		value = RXTX_REG88_MU_TH4_SET(value, 14);
		value = RXTX_REG88_MU_TH5_SET(value, 14);
		value = RXTX_REG88_MU_TH6_SET(value, 14);
		serdes_wr(ctx, 0, RXTX_REG88, value);

		serdes_rd(ctx, 0, RXTX_REG89, &value);
		value = RXTX_REG89_MU_TH7_SET(value, 14);
		value = RXTX_REG89_MU_TH8_SET(value, 14);
		value = RXTX_REG89_MU_TH9_SET(value, 14);
		serdes_wr(ctx, 0, RXTX_REG89, value);

		serdes_rd(ctx, 0, RXTX_REG145, &value);
		value = RXTX_REG145_RXDFE_CONFIG_SET(value, 3);
		serdes_wr(ctx, 0, RXTX_REG145, value);

		serdes_rd(ctx, 0, RXTX_REG28, &value);
		value = RXTX_REG28_DFE_TAP_ENA_SET(value, infmode ? 0x7 : 0x0);
		serdes_wr(ctx, 0, RXTX_REG28, value);

		serdes_rd(ctx, 0, RXTX_REG7, &value);
		value = RXTX_REG7_RESETB_RXD_SET(value, 1);
		value =  RXTX_REG7_LP_ENA_CTLE_SET(value, 0);
		value = RXTX_REG7_BIST_ENA_RX_SET(value, 0);
		serdes_wr(ctx, 0, RXTX_REG7, value);

		serdes_rd(ctx, 0, RXTX_REG6, &value);
		value = RXTX_REG6_RX_BIST_ERRCNT_RD_SET(value, 0);
		serdes_wr(ctx, 0, RXTX_REG6, value);

		serdes_rd(ctx, 0, RXTX_REG12, &value);
		value = RXTX_REG12_RX_INV_SET(value, 0);
		serdes_wr(ctx, 0, RXTX_REG12, value);
	}
}

static void sm_xgenet_program_all_regs(struct xgene_phy_ctx *ctx)
{
	xgenet_phy_cmu_cfg(ctx);
	xgenet_phy_rxtx_cfg(ctx);
}

static int enet_vco_status(struct xgene_phy_ctx *ctx)
{
	int pll_lock, vco_calibration;
	int pll_det;
	int vco_cal_fail;
	u32 rd_val;

	cmu_rd(ctx, PHY_CMU, CMU_REG7, &rd_val);
	pll_lock = CMU_REG7_PLL_LOCK_RD(rd_val);
	vco_calibration = CMU_REG7_PLL_CALIB_DONE_RD(rd_val);
	pll_det = CMU_REG7_PLL_DET_RD(rd_val);
	vco_cal_fail = CMU_REG7_VCO_CAL_FAIL_RD(rd_val);
	if (!vco_calibration) {
		dev_err(ctx->dev, "VCO_CALIB: PLL VCO calibration failed\n");
		dev_err(ctx->dev, "VCO_CALIB: PLL DET : 0x%x\n", pll_det);
	}
	return (((vco_cal_fail << 3) | (pll_det << 1) | (pll_lock == 0)));
}

static int get_roundoff_avg(int accum, int samples)
{
	return (accum + (samples / 2)) / samples;
}

static void force_lat_summer_cal(struct xgene_phy_ctx *ctx, int port)
{
	u32 lane = port & 0x1;

	/* Start SUMMER calibration */
	serdes_setbits(ctx, lane, RXTX_REG127,
		RXTX_REG127_FORCE_SUM_CAL_START_MASK);
	/*
	 * As per PHY design spec, the Summer calibration requires a minimum
	 * of 100us to complete.
	 */
	usleep_range(100, 500);
	serdes_clrbits(ctx, lane, RXTX_REG127,
		RXTX_REG127_FORCE_SUM_CAL_START_MASK);
	/*
	 * As per PHY design spec, the auto calibration requires a minimum
	 * of 100us to complete.
	 */
	usleep_range(100, 500);
	/* Start latch calibration */
	serdes_setbits(ctx, lane, RXTX_REG127,
		RXTX_REG127_FORCE_LAT_CAL_START_MASK);
	/*
	 * As per PHY design spec, the latch calibration requires a minimum
	 * of 100us to complete.
	 */
	usleep_range(100, 500);
	serdes_clrbits(ctx, lane, RXTX_REG127,
		RXTX_REG127_FORCE_LAT_CAL_START_MASK);
}

static void gen_avg_val(struct xgene_phy_ctx *ctx, u32 port, u32 loop)
{
	int avg_loop = loop;
	int MAX_LOOP = 10;
	int lat_do = 0, lat_xo = 0, lat_eo = 0, lat_so = 0;
	int lat_de = 0, lat_xe = 0, lat_ee = 0, lat_se = 0;
	int sum_cal = 0;
	int lat_do_itr, lat_xo_itr, lat_eo_itr, lat_so_itr;
	int lat_de_itr, lat_xe_itr, lat_ee_itr, lat_se_itr;
	int sum_cal_itr = 0;
	int fail_even = 0;
	int fail_odd = 0;
	u32 value, lane;

	lane = port & 0x1;

	dev_dbg(ctx->dev, "Generating Average Value\n");
	/* Enable RX Hi-Z termination enable */
	serdes_setbits(ctx, lane, RXTX_REG12,
		RXTX_REG12_RX_DET_TERM_ENABLE_MASK);

	/* Turn off DFE  */
	serdes_rd(ctx, lane, RXTX_REG28, &value);
	value = RXTX_REG28_DFE_TAP_ENA_SET(value, 0);
	serdes_wr(ctx, lane, RXTX_REG28, 0);

	/* DFE Presets to zero  */
	serdes_rd(ctx, lane, RXTX_REG31, &value);
	serdes_wr(ctx, lane, RXTX_REG31, 0);

	while (avg_loop > 0) {
		force_lat_summer_cal(ctx, port);
		usleep_range(100, 200);
		serdes_rd(ctx, lane, RXTX_REG21, &value);
		lat_do_itr = RXTX_REG21_DO_LATCH_CALOUT_RD(value);
		lat_xo_itr = RXTX_REG21_XO_LATCH_CALOUT_RD(value);
		fail_odd   = RXTX_REG21_LATCH_CAL_FAIL_ODD_RD(value);

		serdes_rd(ctx, lane, RXTX_REG22, &value);
		lat_eo_itr = RXTX_REG22_EO_LATCH_CALOUT_RD(value);
		lat_so_itr = RXTX_REG22_SO_LATCH_CALOUT_RD(value);
		fail_even  = RXTX_REG22_LATCH_CAL_FAIL_EVEN_RD(value);

		serdes_rd(ctx, lane, RXTX_REG23, &value);
		lat_de_itr = RXTX_REG23_DE_LATCH_CALOUT_RD(value);
		lat_xe_itr = RXTX_REG23_XE_LATCH_CALOUT_RD(value);

		serdes_rd(ctx, lane, RXTX_REG24, &value);
		lat_ee_itr = RXTX_REG24_EE_LATCH_CALOUT_RD(value);
		lat_se_itr = RXTX_REG24_SE_LATCH_CALOUT_RD(value);

		serdes_rd(ctx, lane, RXTX_REG121, &value);
		sum_cal_itr = RXTX_REG121_SUMOS_CAL_CODE_RD(value);

		if ((fail_even == 0 || fail_even == 1) &&
				(fail_odd == 0 || fail_odd == 1)) {
			lat_do += lat_do_itr;
			lat_xo += lat_xo_itr;
			lat_eo += lat_eo_itr;
			lat_so += lat_so_itr;
			lat_de += lat_de_itr;
			lat_xe += lat_xe_itr;
			lat_ee += lat_ee_itr;
			lat_se += lat_se_itr;
			sum_cal += sum_cal_itr;
			avg_loop--;
		}
		xgene_phy_reset_rxd(ctx, lane);
	}

	/* Update with Average Value */
	/* Latch Calibration Value */
	serdes_rd(ctx, lane, RXTX_REG127, &value);
	value = RXTX_REG127_DO_LATCH_MANCAL_SET(value,
		get_roundoff_avg(lat_do, MAX_LOOP));
	value = RXTX_REG127_XO_LATCH_MANCAL_SET(value,
		get_roundoff_avg(lat_xo, MAX_LOOP));
	serdes_wr(ctx, lane, RXTX_REG127, value);

	serdes_rd(ctx, lane, RXTX_REG128, &value);
	value = RXTX_REG128_EO_LATCH_MANCAL_SET(value,
		get_roundoff_avg(lat_eo, MAX_LOOP));
	value = RXTX_REG128_SO_LATCH_MANCAL_SET(value,
		get_roundoff_avg(lat_so, MAX_LOOP));
	serdes_wr(ctx, lane, RXTX_REG128, value);

	serdes_rd(ctx, lane, RXTX_REG129, &value);
	value = RXTX_REG129_DE_LATCH_MANCAL_SET(value,
		get_roundoff_avg(lat_de, MAX_LOOP));
	value = RXTX_REG129_XE_LATCH_MANCAL_SET(value,
		get_roundoff_avg(lat_xe, MAX_LOOP));
	serdes_wr(ctx, lane, RXTX_REG129, value);

	serdes_rd(ctx, lane, RXTX_REG130, &value);
	value = RXTX_REG130_EE_LATCH_MANCAL_SET(value,
		get_roundoff_avg(lat_ee, MAX_LOOP));
	value = RXTX_REG130_SE_LATCH_MANCAL_SET(value,
		get_roundoff_avg(lat_se, MAX_LOOP));
	serdes_wr(ctx, lane, RXTX_REG130, value);

	/* Summer Calibration Value */
	serdes_rd(ctx, lane, RXTX_REG14, &value);
	value = RXTX_REG14_CLTE_LATCAL_MAN_PROG_SET(value,
		get_roundoff_avg(sum_cal, MAX_LOOP));
	serdes_wr(ctx, lane, RXTX_REG14, value);

	/* Manual Summer Calibration */
	serdes_rd(ctx, lane, RXTX_REG14, &value);
	value = RXTX_REG14_CTLE_LATCAL_MAN_ENA_SET(value, 0x1);
	serdes_wr(ctx, lane, RXTX_REG14, value);

	/* Manual Latch Calibration */
	serdes_rd(ctx, lane, RXTX_REG127, &value);
	value = RXTX_REG127_LATCH_MAN_CAL_ENA_SET(value, 0x1);
	serdes_wr(ctx, lane, RXTX_REG127, value);

	/* Turn on DFE  */
	serdes_rd(ctx, lane, RXTX_REG28, &value);
	value = RXTX_REG28_DFE_TAP_ENA_SET(value, 7);
	serdes_wr(ctx, lane, RXTX_REG28, value);

	/* DFE Presets to 0x2a00(default) */
	serdes_rd(ctx, lane, RXTX_REG31, &value);
	serdes_wr(ctx, lane, RXTX_REG31, 0x2a00);

	/* Disable RX Hi-Z termination enable */
	serdes_rd(ctx, lane, RXTX_REG12, &value);
	value = RXTX_REG12_RX_DET_TERM_ENABLE_SET(value, 0);
	serdes_wr(ctx, lane, RXTX_REG12, value);
}

static void sm_init_xgenet_phy(struct xgene_phy_ctx *ctx, u32 *pll_ready)
{
	u32 value, loop;
	u32 refclksel, refclk_cmos_sel;
	u32 i, infmode;
	u32 pll_lock, vco_calibration;
	u32 tx_ready, rx_ready;

	infmode = (ctx->mode == MODE_XFI) ? 1 : 0;
	refclksel = 0;
	refclk_cmos_sel = 0;
	cmu_rd(ctx, PHY_CMU, CMU_REG0, &value);
	value = CMU_REG0_PLL_REF_SEL_SET(value, refclksel);
	cmu_wr(ctx, PHY_CMU, CMU_REG0, value);
	cmu_rd(ctx, PHY_CMU, CMU_REG1, &value);
	value = CMU_REG1_REFCLK_CMOS_SEL_SET(value, refclk_cmos_sel);
	cmu_wr(ctx, PHY_CMU, CMU_REG1, value);

	if (infmode) /* xgmii */
		value = 0x306430;
	else		/* sgmii */
		value = 0x305030;

	writel(value, ctx->clk_base + XGENET_PLL_CFG);
	if (refclk_cmos_sel) {
		i = 0;
		do {
			value = readl(ctx->clk_base +  XGENET_PLL_STAT);
			if (i++ > 10)
				break;
			usleep_range(100, 200);
		} while (value == 0);
	}
	/* program PLL output clock divider value after PLL has locked */
	if (infmode) /* xgmii */
		value = 0x4;
	else /* sgmii */
		value = 0x5;
	writel(value, ctx->clk_base + XGENET_PLL_DIV_CFG);

	/* Assert all reset */
	writel(0xDE, ctx->sds_base + XGENET_SDS_RST_CTL);
	/* Force a barrier */
	value = readl(ctx->sds_base + XGENET_SDS_RST_CTL);

	writel(0, ctx->sds_base + XGENET_SDS_CTL0);
	sm_xgenet_program_all_regs(ctx);

	/* De-assert all reset */
	writel(0xDF, ctx->sds_base + XGENET_SDS_RST_CTL);
	loop = 1000;
	do {
		usleep_range(800, 1000);
		value = readl(ctx->sds_base + XGENET_SDS_CMU_STATUS0);
		*pll_ready = CFG_CMU_O_PLL_READY0_RD(value);
		vco_calibration = CFG_CMU_O_VCO_CALDONE0_RD(value);
		pll_lock = CFG_CMU_O_PLL_LOCK0_RD(value);
		value = readl(ctx->sds_base + XGENET_SDS_RXTX_STATUS);
		tx_ready = CFG_TX_O_TX_READY_RD(value);
		rx_ready = CFG_RX_O_RX_READY_RD(value);
		if (((*pll_ready && pll_lock && vco_calibration)) &&
			(tx_ready && rx_ready))
			break;
		loop--;

	} while (loop != 0);

	if (!loop) {
		dev_err(ctx->dev, "XFI: PLL is %sready\n",
			*pll_ready ? "" : "not ");
		dev_err(ctx->dev, "XFI: PLL is %slocked\n",
			pll_lock ? "" : "not ");
		dev_err(ctx->dev, "XFI: PLL VCO calibration is %s\n",
			vco_calibration ? "successful" : "not successful");
		dev_err(ctx->dev, "XFI: TX is %sready\n",
			tx_ready ? "" : "not ");
		dev_err(ctx->dev, "XFI: RX is %sready\n",
			rx_ready ? "" : "not ");
	}
}

static void enet_phy_cmu_cfg(struct xgene_phy_ctx *ctx)
{
	u32 value;
	int man_pvt_cal = 0;

	/* HSPLL Controls */
	cmu_rd(ctx, PHY_CMU, CMU_REG0, &value);
	value = CMU_REG0_CAL_COUNT_RESOL_SET(value, 7);
	cmu_wr(ctx, PHY_CMU, CMU_REG0, value);

	cmu_rd(ctx, PHY_CMU, CMU_REG1, &value);
	value = CMU_REG1_PLL_CP_SET(value, 1);

	value = CMU_REG1_PLL_CP_SEL_SET(value, 5);
	value = CMU_REG1_PLL_MANUALCAL_SET(value, 0);
	cmu_wr(ctx, PHY_CMU, CMU_REG1, value);

	cmu_rd(ctx, PHY_CMU, CMU_REG2, &value);
	value = CMU_REG2_PLL_LFRES_SET(value, 0xa);
	value = CMU_REG2_PLL_FBDIV_SET(value, 124);
	value = CMU_REG2_PLL_REFDIV_SET(value, 1);
	cmu_wr(ctx, PHY_CMU, CMU_REG2, value);

	cmu_rd(ctx, PHY_CMU, CMU_REG3, &value);
	value = CMU_REG3_VCOVARSEL_SET(value, 7);
	value = CMU_REG3_VCO_MOMSEL_INIT_SET(value, 0x1b);
	value = CMU_REG3_VCO_MANMOMSEL_SET(value, 0x1b);
	cmu_wr(ctx, PHY_CMU, CMU_REG3, value);

	cmu_rd(ctx, PHY_CMU, CMU_REG5, &value);
	value = CMU_REG5_PLL_LFSMCAP_SET(value, 3);
	value = CMU_REG5_PLL_LFCAP_SET(value, 4);
	value = CMU_REG5_PLL_LOCK_RESOLUTION_SET(value, 7);
	cmu_wr(ctx, PHY_CMU, CMU_REG5, value);

	cmu_rd(ctx, PHY_CMU, CMU_REG6, &value);
	value = CMU_REG6_PLL_VREGTRIM_SET(value, 0);
	value = CMU_REG6_MAN_PVT_CAL_SET(value, man_pvt_cal);
	cmu_wr(ctx, PHY_CMU, CMU_REG6, value);

	cmu_rd(ctx, PHY_CMU, CMU_REG8, &value);
	value = CMU_REG8_CH3_0_PLL_UCDIV(value, 255);
	cmu_wr(ctx, PHY_CMU, CMU_REG8, value);

	cmu_rd(ctx, PHY_CMU, CMU_REG9, &value);
	value = CMU_REG9_TX_WORD_MODE_CH1_SET(value, 1);
	value = CMU_REG9_TX_WORD_MODE_CH0_SET(value, 1);
	value = CMU_REG9_PLL_POST_DIVBY2_SET(value, 1);
	cmu_wr(ctx, PHY_CMU, CMU_REG9, value);

	cmu_rd(ctx, PHY_CMU, CMU_REG13, &value);
	value = CMU_REG13_STATE_DELAY4_SET(value, 0xFFFF);
	cmu_wr(ctx, PHY_CMU, CMU_REG13, value);

	cmu_rd(ctx, PHY_CMU, CMU_REG14, &value);
	value = CMU_REG14_STATE_DELAY8_SET(value, 0xFFFF);
	cmu_wr(ctx, PHY_CMU, CMU_REG14, value);

	cmu_rd(ctx, PHY_CMU, CMU_REG16, &value);
	value = CMU_REG16_CALIBRATION_DONE_OVERRIDE_SET(value, 0);
	value = CMU_REG16_BYPASS_PLL_LOCK_SET(value, 0);
	value = CMU_REG16_VCOCAL_WAIT_BTW_CODE_SET(value, 7);
	cmu_wr(ctx, PHY_CMU, CMU_REG16, value);

	cmu_rd(ctx, PHY_CMU, CMU_REG30, &value);
	value = CMU_REG30_PCIE_MODE_SET(value, 0);
	value = CMU_REG30_LOCK_COUNT_SET(value, 3);
	cmu_wr(ctx, PHY_CMU, CMU_REG30, value);

	cmu_rd(ctx, PHY_CMU, CMU_REG31, &value);
	value = CMU_REG31_OVERRIDE_CH3_0_SET(value, 0xF);
	cmu_wr(ctx, PHY_CMU, CMU_REG31, value);

	cmu_rd(ctx, PHY_CMU, CMU_REG32, &value);
	value = CMU_REG32_PVT_CAL_WAIT_SEL_SET(value, 3);
	value = CMU_REG32_IREF_ADJ_SET(value, 3);
	cmu_wr(ctx, PHY_CMU, CMU_REG32, value);

	cmu_rd(ctx, PHY_CMU, CMU_REG34, &value);
	value = CMU_REG34_VCO_CAL_VTH_SET(value, 0x8d27);
	cmu_wr(ctx, PHY_CMU, CMU_REG34, value);

	cmu_rd(ctx, PHY_CMU, CMU_REG37, &value);
	value = CMU_REG37_CAL_DONE_OVR_SET(value, 0xF);
	value = CMU_REG37_SEARCH_DONE_OVR_SET(value, 0xF);
	if (!preB0Chip) /* B0 */
		value = CMU_REG37_LATCH_CAL_DONE_OVR_SET(value, 0xF);
	cmu_wr(ctx, PHY_CMU, CMU_REG37, value);
}

static void enet_phy_rxtx_cfg(struct xgene_phy_ctx *ctx)
{
	u32 value, inst;
	u32 sm_b0;

	sm_b0 = !preB0Chip;
	for (inst = 0; inst < 2; inst++) {
		serdes_rd(ctx, inst, RXTX_REG147, &value);
		value = RXTX_REG147_STMC_OVERRIDE_SET(value, 6);
		serdes_wr(ctx, inst, RXTX_REG147, value);

		serdes_rd(ctx, inst, RXTX_REG0, &value);
		value = RXTX_REG0_CTLE_EQ_HR_SET(value, 0x10);
		value = RXTX_REG0_CTLE_EQ_QR_SET(value, 0x10);
		value = RXTX_REG0_CTLE_EQ_FR_SET(value, sm_b0 ? 0x16 : 0x10);
		serdes_wr(ctx, inst, RXTX_REG0, value);

		serdes_rd(ctx, inst, RXTX_REG1, &value);
		value = RXTX_REG1_RXACVCM_SET(value, 0x7);
		if (sm_b0) {
			value = RXTX_REG1_CTLE_EQ_SET(value, 0x10);
			value = RXTX_REG1_RXVREG1_SET(value, 0x3);
		} else {
			value = RXTX_REG1_CTLE_EQ_SET(value, 0x0);
		}
		serdes_wr(ctx, inst, RXTX_REG1, value);

		serdes_rd(ctx, inst, RXTX_REG2, &value);
		value = RXTX_REG2_VTT_ENA_SET(value, 1);
		value = RXTX_REG2_VTT_SEL_SET(value, 1);
		value = RXTX_REG2_TX_FIFO_ENA_SET(value, 1);
		serdes_wr(ctx, inst, RXTX_REG2, value);

		serdes_rd(ctx, inst, RXTX_REG4, &value);
		value = RXTX_REG4_TX_DATA_RATE_SET(value, 3);
		value = RXTX_REG4_TX_WORD_MODE_SET(value, 1);
		serdes_wr(ctx, inst, RXTX_REG4, value);

		serdes_rd(ctx, inst, RXTX_REG5, &value);
		value = RXTX_REG5_TX_CN1_SET(value, 0);
		value = RXTX_REG5_TX_CP1_SET(value, 0xf);
		value = RXTX_REG5_TX_CN2_SET(value, 0);
		serdes_wr(ctx, inst, RXTX_REG5, value);

		serdes_rd(ctx, inst, RXTX_REG6, &value);
		value = RXTX_REG6_TXAMP_CNTL_SET(value, 0xf);
		value = RXTX_REG6_TXAMP_ENA_SET(value, 1);
		serdes_wr(ctx, inst, RXTX_REG6, value);

		serdes_rd(ctx, inst, RXTX_REG7, &value);
		value = RXTX_REG7_BIST_ENA_RX_SET(value, 0);
		value = RXTX_REG7_RX_WORD_MODE_SET(value, 1);
		value = RXTX_REG7_RX_DATA_RATE_SET(value, 3);
		serdes_wr(ctx, inst, RXTX_REG7, value);

		serdes_rd(ctx, inst, RXTX_REG8, &value);
		value = RXTX_REG8_CDR_LOOP_ENA_SET(value, 1);
		value = RXTX_REG8_CDR_BYPASS_RXLOS_SET(value, 0);
		value = RXTX_REG8_SSC_ENABLE_SET(value, 0);
		value = RXTX_REG8_SD_DISABLE_SET(value, 0);
		value = RXTX_REG8_SD_VREF_SET(value, 4);
		serdes_wr(ctx, inst, RXTX_REG8, value);

		serdes_rd(ctx, inst, RXTX_REG11, &value);
		value = RXTX_REG11_PHASE_ADJUST_LIMIT_SET(value, 0);
		serdes_wr(ctx, inst, RXTX_REG11, value);

		serdes_rd(ctx, inst, RXTX_REG12, &value);
		value = RXTX_REG12_LATCH_OFF_ENA_SET(value, 1);
		value = RXTX_REG12_SUMOS_ENABLE_SET(value, 0);
		value = RXTX_REG12_RX_DET_TERM_ENABLE_SET(value, 1);
		serdes_wr(ctx, inst, RXTX_REG12, value);

		/* TX Rate Change enable: Toggle 0-1-0 */
		cmu_toggle0to10(ctx, PHY_CMU, CMU_REG16,
			CMU_REG16_TX_RATE_CHANGE_ENA_CH0);

		cmu_toggle0to10(ctx, PHY_CMU, CMU_REG16,
			CMU_REG16_TX_RATE_CHANGE_ENA_CH1);

		cmu_toggle0to10(ctx, PHY_CMU, CMU_REG16,
			CMU_REG16_TX_RATE_CHANGE_ENA_CH2);

		cmu_toggle0to10(ctx, PHY_CMU, CMU_REG16,
			CMU_REG16_TX_RATE_CHANGE_ENA_CH3);

		/* RX Rate Change enable: Toggle 0-1-0 */
		cmu_toggle0to10(ctx, PHY_CMU, CMU_REG16,
			CMU_REG16_RX_RATE_CHANGE_ENA_CH0);

		cmu_toggle0to10(ctx, PHY_CMU, CMU_REG16,
			CMU_REG16_RX_RATE_CHANGE_ENA_CH1);

		cmu_toggle0to10(ctx, PHY_CMU, CMU_REG16,
			CMU_REG16_RX_RATE_CHANGE_ENA_CH2);

		cmu_toggle0to10(ctx, PHY_CMU, CMU_REG16,
			CMU_REG16_RX_RATE_CHANGE_ENA_CH3);

		serdes_rd(ctx, inst, RXTX_REG26, &value);
		value = RXTX_REG26_PERIOD_ERROR_LATCH_SET(value, 0);
		value = RXTX_REG26_BLWC_ENA_SET(value, 1);
		serdes_wr(ctx, inst, RXTX_REG26, value);

		serdes_rd(ctx, inst, RXTX_REG28, &value);
		value = RXTX_REG28_DFE_TAP_ENA_SET(value, sm_b0 ? 0 : 7);
		serdes_wr(ctx, inst, RXTX_REG28, value);

		serdes_rd(ctx, inst, RXTX_REG31, &value);
		value = RXTX_REG31_DFE_PRESET_VALUE_H0_H1_SET(value, 0);
		serdes_wr(ctx, inst, RXTX_REG31, value);

		serdes_rd(ctx, inst, RXTX_REG61, &value);
		value = RXTX_REG61_ISCAN_INBERT_SET(value, 1);
		value = RXTX_REG61_SPD_SEL_CDR_SET(value, sm_b0 ? 6 : 1);
		value = RXTX_REG61_EYE_COUNT_WIDTH_SEL_SET(value, 0);
		value = RXTX_REG61_LOADFREQ_SHIFT_SET(value, 0);
		serdes_wr(ctx, inst, RXTX_REG61, value);

		serdes_rd(ctx, inst, RXTX_REG62, &value);
		value = RXTX_REG62_PERIOD_H1_QLATCH_SET(value, 0);
		serdes_wr(ctx, inst, RXTX_REG62, value);

		serdes_rd(ctx, inst, RXTX_REG81, &value);
		value = RXTX_REG81_MU_DFE1_SET(value, 0xe);
		value = RXTX_REG81_MU_DFE2_SET(value, 0xe);
		value = RXTX_REG81_MU_DFE3_SET(value, 0xe);
		serdes_wr(ctx, inst, RXTX_REG81, value);

		serdes_rd(ctx, inst, RXTX_REG83, &value);
		value = RXTX_REG82_MU_DFE4_SET(value, 0xe);
		value = RXTX_REG82_MU_DFE5_SET(value, 0xe);
		value = RXTX_REG82_MU_DFE6_SET(value, 0xe);
		serdes_wr(ctx, inst, RXTX_REG83, value);

		serdes_rd(ctx, inst, RXTX_REG83, &value);
		value =	RXTX_REG83_MU_DFE7_SET(value, 0xe);
		value =	RXTX_REG83_MU_DFE8_SET(value, 0xe);
		value =	RXTX_REG83_MU_DFE9_SET(value, 0xe);
		serdes_wr(ctx, inst, RXTX_REG83, value);

		serdes_rd(ctx, inst, RXTX_REG84, &value);
		value = RXTX_REG84_MU_PH1_SET(value, 0xe);
		value = RXTX_REG84_MU_PH2_SET(value, 0xe);
		value = RXTX_REG84_MU_PH3_SET(value, 0xe);
		serdes_wr(ctx, inst, RXTX_REG84, value);

		serdes_rd(ctx, inst, RXTX_REG85, &value);
		value = RXTX_REG85_MU_PH4_SET(value, 0xe);
		value = RXTX_REG85_MU_PH5_SET(value, 0xe);
		value = RXTX_REG85_MU_PH6_SET(value, 0xe);
		serdes_wr(ctx, inst, RXTX_REG85, value);

		serdes_rd(ctx, inst, RXTX_REG86, &value);
		value = RXTX_REG86_MU_PH7_SET(value, 0xe);
		value = RXTX_REG86_MU_PH8_SET(value, 0xe);
		value = RXTX_REG86_MU_PH9_SET(value, 0xe);
		serdes_wr(ctx, inst, RXTX_REG86, value);

		serdes_rd(ctx, inst, RXTX_REG87, &value);
		value = RXTX_REG87_MU_TH1_SET(value, 0xe);
		value = RXTX_REG87_MU_TH2_SET(value, 0xe);
		value = RXTX_REG87_MU_TH3_SET(value, 0xe);
		serdes_wr(ctx, inst, RXTX_REG87, value);

		serdes_rd(ctx, inst, RXTX_REG88, &value);
		value = RXTX_REG88_MU_TH4_SET(value, 0xe);
		value = RXTX_REG88_MU_TH5_SET(value, 0xe);
		value = RXTX_REG88_MU_TH6_SET(value, 0xe);
		serdes_wr(ctx, inst, RXTX_REG88, value);

		serdes_rd(ctx, inst, RXTX_REG89, &value);
		value = RXTX_REG89_MU_TH7_SET(value, 0xe);
		value = RXTX_REG89_MU_TH8_SET(value, 0xe);
		value = RXTX_REG89_MU_TH9_SET(value, 0xe);
		serdes_wr(ctx, inst, RXTX_REG89, value);

		serdes_rd(ctx, inst, RXTX_REG96, &value);
		value = RXTX_REG96_MU_FREQ1_SET(value, 0x10);
		value = RXTX_REG96_MU_FREQ2_SET(value, 0x10);
		value = RXTX_REG96_MU_FREQ3_SET(value, 0x10);
		serdes_wr(ctx, inst, RXTX_REG96, value);

		serdes_rd(ctx, inst, RXTX_REG97, &value);
		value = RXTX_REG97_MU_FREQ4_SET(value, 0x10);
		value = RXTX_REG97_MU_FREQ5_SET(value, 0x10);
		value = RXTX_REG97_MU_FREQ6_SET(value, 0x10);
		serdes_wr(ctx, inst, RXTX_REG97, value);

		serdes_rd(ctx, inst, RXTX_REG98, &value);
		value = RXTX_REG98_MU_FREQ7_SET(value, 0x10);
		value = RXTX_REG98_MU_FREQ8_SET(value, 0x10);
		value = RXTX_REG98_MU_FREQ9_SET(value, 0x10);
		serdes_wr(ctx, inst, RXTX_REG98, value);

		serdes_rd(ctx, inst, RXTX_REG99, &value);
		value = RXTX_REG99_MU_PHASE1_SET(value, 7);
		value = RXTX_REG99_MU_PHASE2_SET(value, 7);
		value = RXTX_REG99_MU_PHASE3_SET(value, 7);
		serdes_wr(ctx, inst, RXTX_REG99, value);

		serdes_rd(ctx, inst, RXTX_REG100, &value);
		value = RXTX_REG100_MU_PHASE4_SET(value, 7);
		value = RXTX_REG100_MU_PHASE5_SET(value, 7);
		value = RXTX_REG100_MU_PHASE6_SET(value, 7);
		serdes_wr(ctx, inst, RXTX_REG100, value);

		serdes_rd(ctx, inst, RXTX_REG101, &value);
		value = RXTX_REG101_MU_PHASE7_SET(value, 7);
		value = RXTX_REG101_MU_PHASE8_SET(value, 7);
		value = RXTX_REG101_MU_PHASE9_SET(value, 7);
		serdes_wr(ctx, inst, RXTX_REG101, value);

		serdes_rd(ctx, inst, RXTX_REG102, &value);
		value = RXTX_REG102_FREQLOOP_LIMIT_SET(value, 0);
		serdes_wr(ctx, inst, RXTX_REG102, value);

		serdes_rd(ctx, inst, RXTX_REG125, &value);
		value = RXTX_REG125_PQ_REG_SET(value, 0);
		value = RXTX_REG125_SIGN_PQ_SET(value, 0);
		value = RXTX_REG125_PHZ_MANUAL_SET(value, 1);
		serdes_wr(ctx, inst, RXTX_REG125, value);

		serdes_rd(ctx, inst, RXTX_REG127, &value);
		value = RXTX_REG127_LATCH_MAN_CAL_ENA_SET(value, 0);
		serdes_wr(ctx, inst, RXTX_REG127, value);

		serdes_rd(ctx, inst, RXTX_REG128, &value);
		value = RXTX_REG128_LATCH_CAL_WAIT_SEL_SET(value, 2);
		serdes_wr(ctx, inst, RXTX_REG128, value);

		serdes_rd(ctx, inst, RXTX_REG145, &value);
		value = RXTX_REG145_RXDFE_CONFIG_SET(value, 3);
		value = RXTX_REG145_TX_IDLE_SATA_SET(value, 0);
		serdes_wr(ctx, inst, RXTX_REG145, value);

		serdes_rd(ctx, inst, RXTX_REG148, &value);
		value = RXTX_REG148_BIST_WORD_CNT0_SET(value, 0xffff);
		serdes_wr(ctx, inst, RXTX_REG148, value);

		serdes_rd(ctx, inst, RXTX_REG149, &value);
		value = RXTX_REG149_BIST_WORD_CNT1_SET(value, 0xffff);
		serdes_wr(ctx, inst, RXTX_REG149, value);

		serdes_rd(ctx, inst, RXTX_REG150, &value);
		value = RXTX_REG150_BIST_WORD_CNT2_SET(value, 0xffff);
		serdes_wr(ctx, inst, RXTX_REG150, value);

		serdes_rd(ctx, inst, RXTX_REG151, &value);
		value = RXTX_REG151_BIST_WORD_CNT_3_SET(value, 0xffff);
		serdes_wr(ctx, inst, RXTX_REG151, value);
	}
}

static void sm_enet_program_all_regs(struct xgene_phy_ctx *ctx)
{
	enet_phy_cmu_cfg(ctx);
	enet_phy_rxtx_cfg(ctx);
}

static int sm_enet_init_enet_phy(struct xgene_phy_ctx *ctx)
{
	u32 value;
	u32 refclk = 0, refclksel, refclk_cmos_sel;
	u32 pll_ready, loop = 100;
	u32 pll_lock, vco_calibration;
	u32 tx_ready, rx_ready;

	refclksel = (refclk >> 1) & 1;
	refclk_cmos_sel = refclk & 1;

	writel(0x20, ctx->sds_base + SATA_ENET_SDS_RST_CTL);
	writel(0xDE, ctx->sds_base + SATA_ENET_SDS_RST_CTL);
	/*
	 * set cfg_i_customer_pin_mode = 0,
	 * all register are programmed through indirect programming
	 */
	writel(0x0, ctx->sds_base + SATA_ENET_SDS_CTL0);

	cmu_rd(ctx, PHY_CMU, CMU_REG12, &value);
	value = CMU_REG12_STATE_DELAY9_SET(value, 2);
	cmu_wr(ctx, PHY_CMU, CMU_REG12, value);

	cmu_rd(ctx, PHY_CMU, CMU_REG0, &value);
	value = CMU_REG0_PLL_REF_SEL_SET(value, refclksel);
	cmu_wr(ctx, PHY_CMU, CMU_REG0, value);

	cmu_rd(ctx, PHY_CMU, CMU_REG1, &value);
	value = CMU_REG1_REFCLK_CMOS_SEL_SET(value, refclk_cmos_sel);
	cmu_wr(ctx, PHY_CMU, CMU_REG1, value);
	sm_enet_program_all_regs(ctx);
	writel(0xDF, ctx->sds_base + SATA_ENET_SDS_RST_CTL);
	do {
		usleep_range(100, 200);
		value = readl(ctx->sds_base + SATA_ENET_SDS_CMU_STATUS0);
		pll_ready = CFG_CMU_O_PLL_READY0_RD(value);
		pll_lock = CFG_CMU_O_PLL_LOCK0_RD(value);
		vco_calibration = CFG_CMU_O_VCO_CALDONE0_RD(value);
		if (((pll_ready && pll_lock && vco_calibration)) ||
				(loop-- == 0))
			break;
	} while (loop != 0);

	dev_dbg(ctx->dev, "SATA-Enet: PLL is %sready\n",
		pll_ready ? "" : "not ");
	dev_dbg(ctx->dev, "SATA-Enet: PLL is %slocked\n",
		pll_lock ? "" : "not ");
	if (!vco_calibration)
		dev_err(ctx->dev, "SATA-Enet: PLL VCO calibration failed\n");
	value = readl(ctx->sds_base +  SATA_ENET_SDS0_RXTX_STATUS);
	tx_ready = CFG_TX_O_TX_READY_F1_RD(value);
	rx_ready = CFG_RX_O_RX_READY_F1_RD(value);
	if (!tx_ready || !rx_ready) {
		dev_err(ctx->dev, "SATA-Enet: TX is %sready\n",
			tx_ready ? "" : "not ");
		dev_err(ctx->dev, "SATA-Enet: RX is %sready\n",
			rx_ready ? "" : "not ");
	}
	return pll_ready;
}

static int xgene_phy_hw_init_xfi(struct xgene_phy_ctx *ctx,
		enum clk_type_t clk_type, int ssc_enable)
{
	u32 pll_ready;
	u32 pll_manualcal = 0;

	if (ctx->mode == MODE_XFI) {
		sm_init_xgenet_phy(ctx, &pll_ready);
	} else {
		int vco_fail = 0, loop = 30;

		do {
			sm_init_xgenet_phy(ctx, &pll_ready);
			usleep_range(100, 200);
			if (pll_manualcal == 0)
				vco_fail = enet_vco_status(ctx);
			loop--;
		} while (((vco_fail & 0x1e) || (pll_ready == 0)) &&
			(loop != 0));
		force_lat_summer_cal(ctx, 0);
	}
	gen_avg_val(ctx, ctx->lane, 10);
	return 0;
}

static int xgene_phy_hw_init_sata_sgmii(struct xgene_phy_ctx *ctx,
		enum clk_type_t clk_type, int ssc_enable)
{
	int vco_fail, port;

	do {
		xgene_phy_pdwn_force_vco(ctx, PHY2_CMU, ctx->clk_type);
		sm_enet_init_enet_phy(ctx);
		vco_fail = enet_vco_status(ctx) >> 3;
	} while (vco_fail);

	for (port = 0; port < 2; port++) {
		if (preB0Chip)
			gen_avg_val(ctx, port, 20);
		else
			xgene_phy_gen_avg_val(ctx, port);
	}

	return 0;
}

