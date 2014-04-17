/** @file
  This file implements the XGene USB Initialization process.

  Copyright (c) Applied Micro Circuit Corporation. All rights reserved.<BR>

  This program and the accompanying materials
  are licensed and made available under the terms and conditions of the BSD License
  which accompanies this distribution.  The full text of the license may be found at
  http://opensource.org/licenses/bsd-license.php

  THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
  WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.

**/

#include "XGeneUsbSerdesKoolchip.h"
#include "XGeneUsb.h"

#define readl(x)     *((volatile UINT32 *) (x))
#define writel(x, v) *((volatile UINT32 *) (x)) = (v)

VOID xgene_usb_udelay(UINT64 us)
{
  MicroSecondDelay(us);
}

VOID xgene_usb_mdelay(UINT64 us)
{
  MicroSecondDelay(us*1000);
}

UINT32 apm_usb_readl(VOID* addr)
{
  return readl(addr);
}

VOID apm_usb_writel(VOID* addr, UINT32 val)
{
  writel(addr, val);
}

VOID apm_usb_ind_sds_wr(VOID *csr_base, UINT32 offset, UINT32 data)
{

  UINT32 cap_value;
  UINTN ind_addr_cmd;
  UINT32 ind_cmd_reg_addr = USB_SDS_CSR_USB_SDS_IND_CMD_REG;
  UINT32 ind_wdata_reg_addr = USB_SDS_CSR_USB_SDS_IND_WDATA_REG;

  ind_addr_cmd = (offset << 4) | 0x00000005;

  apm_usb_writel(csr_base + ind_wdata_reg_addr, data);
  apm_usb_writel(csr_base + ind_cmd_reg_addr, ind_addr_cmd);  // Write CMU_reg0 register
  //apmusb_dbg("SERDES SDS INDIRECT WR: 0x%x value: 0x%08X\n", offset, data);
  cap_value = 0;
  xgene_usb_udelay(1000);
  while (cap_value != 0x00000004) {
    cap_value = apm_usb_readl(csr_base + ind_cmd_reg_addr);
    cap_value = cap_value & 0x00000004;
  }
}

VOID apm_usb_ind_sds_rd(VOID *csr_base, UINT32 offset, UINT32 * data)
{

  UINT32 cap_value;
  UINTN ind_addr_cmd;
  UINT32 ind_cmd_reg_addr = USB_SDS_CSR_USB_SDS_IND_CMD_REG;
  UINT32 ind_rdata_reg_addr = USB_SDS_CSR_USB_SDS_IND_RDATA_REG;

  ind_addr_cmd = (offset << 4) | 0x000000006;

  apm_usb_writel(csr_base + ind_cmd_reg_addr, ind_addr_cmd);  // Read CMU_reg0 register
  xgene_usb_udelay(1000);
  cap_value = 0;
  while (cap_value != 0x00000004) {
    cap_value = apm_usb_readl(csr_base + ind_cmd_reg_addr);
    cap_value = cap_value & 0x00000004;
  }

  *data = apm_usb_readl(csr_base + ind_rdata_reg_addr);
  //apmusb_dbg("SERDES SDS INDIRECT RD: 0x%x value: 0x%08X\n", offset, *data);
}

VOID apm_usb_ind_pcs_wr(VOID *csr_base, UINT32 offset, UINT32 data)
{

  UINT32 cap_value;
  UINTN ind_addr_cmd;
  UINT32 ind_cmd_reg_addr = USB_SDS_CSR_USB_SDS_IND_CMD_REG;
  UINT32 ind_wdata_reg_addr = USB_SDS_CSR_USB_SDS_IND_WDATA_REG;

  ind_addr_cmd = (offset << 4) | 0x00000005;
  ind_addr_cmd = ind_addr_cmd | ((1 << 16) << 4);  // Setting the 20th bit of ind_addr[21:4].

  apm_usb_writel(csr_base + ind_wdata_reg_addr, data);
  apm_usb_writel(csr_base + ind_cmd_reg_addr, ind_addr_cmd);  // Write CMU_reg0 register
  xgene_usb_udelay(1000);
  apmusb_dbg("SERDES PCS INDIRECT WR: 0x%x value: 0x%08X\n", offset, data);
  cap_value = 0;
  while (cap_value != 0x00000004) {
    cap_value = apm_usb_readl(csr_base + ind_cmd_reg_addr);
    cap_value = cap_value & 0x00000004;
  }
}

VOID apm_usb_ind_pcs_rd(VOID *csr_base, UINT32 offset, UINT32 * data)
{

  UINT32 cap_value;
  UINTN ind_addr_cmd;
  UINT32 ind_cmd_reg_addr = USB_SDS_CSR_USB_SDS_IND_CMD_REG;
  UINT32 ind_rdata_reg_addr = USB_SDS_CSR_USB_SDS_IND_RDATA_REG;

  ind_addr_cmd = (offset << 4) | 0x000000006;
  ind_addr_cmd = ind_addr_cmd | ((1 << 16) << 4);  // Setting the 20th bit of ind_addr[21:4].

  apm_usb_writel(csr_base + ind_cmd_reg_addr, ind_addr_cmd);  // Read CMU_reg0 register
  xgene_usb_udelay(1000);
  cap_value = 0;
  while (cap_value != 0x00000004) {
    cap_value = apm_usb_readl(csr_base + ind_cmd_reg_addr);
    cap_value = cap_value & 0x00000004;
  }

  *data = apm_usb_readl(csr_base + ind_rdata_reg_addr);
  apmusb_dbg("SERDES PCS INDIRECT RD: 0x%x value: 0x%08X\n", offset, *data);
}

/*
 * Wait until a register has a specific value or timeout
 */
UINT32 usb_apm_wait_register(VOID *reg, UINT32 mask, UINT32 val,
      INTN interval, UINT64 timeout)
{
    UINT64 deadline = 0;
    UINT32 tmp;

    tmp = apm_usb_readl(reg);
    while (((tmp & mask) != val) && (deadline < timeout)) {
      if(interval>0)
        xgene_usb_mdelay(interval);
      tmp = apm_usb_readl(reg);
      deadline++;
    }

    return tmp;
}


/**************************************************************
 * SERDES CONFIGURATION
 **************************************************************/
/**
 * CMU Registers configuration
 */
VOID apm_usb_kc_pll_asic(VOID* csr_base)
{
  INTN pll_lfres = 0xb;
  INTN vcovarsel = 0x4;
  UINT32 data;

  apmusb_dbg("CMU Register configuration\n");
  apm_usb_ind_sds_rd(csr_base, KC_SERDES_CMU_REG_ADDR(1), &data);
  data = FIELD_CMU_REG1_PLL_CP_SET(data, 0xf);
  data = FIELD_CMU_REG1_PLL_CP_SEL_SET(data, 0xc);
  data = FIELD_CMU_REG1_PLL_ENA_VCO_SET(data, 0x1);
  apm_usb_ind_sds_wr(csr_base, KC_SERDES_CMU_REG_ADDR(1), data);
  apm_usb_ind_sds_rd(csr_base, KC_SERDES_CMU_REG_ADDR(1), &data);
  apm_usb_ind_sds_rd(csr_base, KC_SERDES_CMU_REG_ADDR(3), &data);
  data = FIELD_CMU_REG3_VCOVARSEL_SET(data, vcovarsel);
  apm_usb_ind_sds_wr(csr_base, KC_SERDES_CMU_REG_ADDR(3), data);
  apm_usb_ind_sds_rd(csr_base, KC_SERDES_CMU_REG_ADDR(3), &data);

  apm_usb_ind_sds_rd(csr_base, KC_SERDES_CMU_REG_ADDR(2), &data);
  data = FIELD_CMU_REG2_PLL_LFRES_SET(data, pll_lfres);
  data = FIELD_CMU_REG2_PLL_FBDIV_SET(data, 0x31); //control off from PIPE
  apm_usb_ind_sds_wr(csr_base, KC_SERDES_CMU_REG_ADDR(2), data);
  apm_usb_ind_sds_rd(csr_base, KC_SERDES_CMU_REG_ADDR(2), &data);
  apm_usb_ind_sds_rd(csr_base, KC_SERDES_CMU_REG_ADDR(5), &data);
  data = FIELD_CMU_REG5_PLL_LFCAP_SET(data, 0);
  data = FIELD_CMU_REG5_PLL_LFSMCAP_SET(data, 0);
  apm_usb_ind_sds_wr(csr_base, KC_SERDES_CMU_REG_ADDR(5), data);
  apm_usb_ind_sds_rd(csr_base, KC_SERDES_CMU_REG_ADDR(5), &data);

  apm_usb_ind_sds_rd(csr_base, KC_SERDES_CMU_REG_ADDR(4), &data);
  data = FIELD_CMU_REG4_VCOVARSEL_PCIE_SET(data, 0x4);
  apm_usb_ind_sds_wr(csr_base, KC_SERDES_CMU_REG_ADDR(4), data);
  apm_usb_ind_sds_rd(csr_base, KC_SERDES_CMU_REG_ADDR(4), &data);

  apm_usb_ind_sds_rd(csr_base, KC_SERDES_CMU_REG_ADDR(6), &data);
  data = FIELD_CMU_REG6_PLL_VREGTRIM_SET(data, 0x0);
  apm_usb_ind_sds_wr(csr_base, KC_SERDES_CMU_REG_ADDR(6), data);
  apm_usb_ind_sds_rd(csr_base, KC_SERDES_CMU_REG_ADDR(6), &data);

  apm_usb_ind_sds_rd(csr_base, KC_SERDES_CMU_REG_ADDR(32), &data);
  data = FIELD_CMU_REG32_IREF_ADJ_SET(data, 0x3);
  apm_usb_ind_sds_wr(csr_base, KC_SERDES_CMU_REG_ADDR(32), data);
  apm_usb_ind_sds_rd(csr_base, KC_SERDES_CMU_REG_ADDR(32), &data);

  apm_usb_ind_sds_rd(csr_base, KC_SERDES_CMU_REG_ADDR(1), &data);
  data = FIELD_CMU_REG1_PLL_MANUALCAL_SET(data, 0x0);
  apm_usb_ind_sds_wr(csr_base, KC_SERDES_CMU_REG_ADDR(1), data);
  apm_usb_ind_sds_rd(csr_base, KC_SERDES_CMU_REG_ADDR(1), &data);

  apm_usb_ind_sds_rd(csr_base, KC_SERDES_CMU_REG_ADDR(3), &data);
  data = FIELD_CMU_REG3_VCO_MOMSEL_INIT_SET(data, 0x10);
  apm_usb_ind_sds_wr(csr_base, KC_SERDES_CMU_REG_ADDR(3), data);
  apm_usb_ind_sds_rd(csr_base, KC_SERDES_CMU_REG_ADDR(3), &data);

  apm_usb_ind_sds_rd(csr_base, KC_SERDES_CMU_REG_ADDR(4), &data);
  data = FIELD_CMU_REG4_VCO_MOMSEL_INIT_PCIE_SET(data, 0x10);
  apm_usb_ind_sds_wr(csr_base, KC_SERDES_CMU_REG_ADDR(4), data);
  apm_usb_ind_sds_rd(csr_base, KC_SERDES_CMU_REG_ADDR(4), &data);

  apm_usb_ind_sds_rd(csr_base, KC_SERDES_CMU_REG_ADDR(34), &data);
  data = FIELD_CMU_REG34_VCO_CAL_VTH_HI_MIN_SET(data, 0x2);
  data = FIELD_CMU_REG34_VCO_CAL_VTH_HI_MAX_SET(data, 0xa);
  data = FIELD_CMU_REG34_VCO_CAL_VTH_LO_MIN_SET(data, 0x2);
  data = FIELD_CMU_REG34_VCO_CAL_VTH_LO_MAX_SET(data, 0xa);
  apm_usb_ind_sds_wr(csr_base, KC_SERDES_CMU_REG_ADDR(34), data);
  apm_usb_ind_sds_rd(csr_base, KC_SERDES_CMU_REG_ADDR(34), &data);

  apm_usb_ind_sds_rd(csr_base, KC_SERDES_CMU_REG_ADDR(0), &data);
  data = FIELD_CMU_REG0_CAL_COUNT_RESOL_SET(data, 0x7); //pll lock calibration
  apm_usb_ind_sds_wr(csr_base, KC_SERDES_CMU_REG_ADDR(0), data);
  apm_usb_ind_sds_rd(csr_base, KC_SERDES_CMU_REG_ADDR(0), &data);

  apm_usb_ind_sds_rd(csr_base, KC_SERDES_CMU_REG_ADDR(16), &data);
  data = FIELD_CMU_REG16_VCOCAL_WAIT_BTW_CODE_SET(data, 0x7); //VCO Calb wait time
  apm_usb_ind_sds_wr(csr_base, KC_SERDES_CMU_REG_ADDR(16), data);
  apm_usb_ind_sds_rd(csr_base, KC_SERDES_CMU_REG_ADDR(16), &data);

  apm_usb_ind_sds_rd(csr_base, KC_SERDES_CMU_REG_ADDR(30), &data);
  data = FIELD_CMU_REG30_LOCK_COUNT_SET(data, 0x3); //Lock count wait time
  apm_usb_ind_sds_wr(csr_base, KC_SERDES_CMU_REG_ADDR(30), data);
  apm_usb_ind_sds_rd(csr_base, KC_SERDES_CMU_REG_ADDR(30), &data);

  apm_usb_ind_sds_rd(csr_base, KC_SERDES_CMU_REG_ADDR(13), &data);
  data = FIELD_CMU_REG13_STATE_DELAY1_SET(data, 0xf);
  data = FIELD_CMU_REG13_STATE_DELAY2_SET(data, 0xf);
  data = FIELD_CMU_REG13_STATE_DELAY3_SET(data, 0xf);
  data = FIELD_CMU_REG13_STATE_DELAY4_SET(data, 0xf);
  apm_usb_ind_sds_wr(csr_base, KC_SERDES_CMU_REG_ADDR(13), data);
  apm_usb_ind_sds_rd(csr_base, KC_SERDES_CMU_REG_ADDR(13), &data);

  apm_usb_ind_sds_rd(csr_base, KC_SERDES_CMU_REG_ADDR(14), &data);
  data = FIELD_CMU_REG14_STATE_DELAY5_SET(data, 0xf);
  data = FIELD_CMU_REG14_STATE_DELAY6_SET(data, 0xf);
  data = FIELD_CMU_REG14_STATE_DELAY7_SET(data, 0xf);
  data = FIELD_CMU_REG14_STATE_DELAY8_SET(data, 0xf);
  apm_usb_ind_sds_wr(csr_base, KC_SERDES_CMU_REG_ADDR(14), data);
  apm_usb_ind_sds_rd(csr_base, KC_SERDES_CMU_REG_ADDR(14), &data);

  //PCIE mode enable ??? do we set this

  apm_usb_ind_sds_rd(csr_base, KC_SERDES_CMU_REG_ADDR(32), &data);
  data = FIELD_CMU_REG32_PVT_CAL_WAIT_SEL_SET(data, 0x3);
  apm_usb_ind_sds_wr(csr_base, KC_SERDES_CMU_REG_ADDR(32), data);
  apm_usb_ind_sds_rd(csr_base, KC_SERDES_CMU_REG_ADDR(32), &data);

  apm_usb_ind_sds_rd(csr_base, KC_SERDES_CMU_REG_ADDR(31), &data);
  data = FIELD_CMU_REG31_LOS_OVERRIDE_CH3_SET(data, 0x1);
  data = FIELD_CMU_REG31_LOS_OVERRIDE_CH2_SET(data, 0x1);
  data = FIELD_CMU_REG31_LOS_OVERRIDE_CH1_SET(data, 0x1);
  data = FIELD_CMU_REG31_LOS_OVERRIDE_CH0_SET(data, 0x1);
  apm_usb_ind_sds_wr(csr_base, KC_SERDES_CMU_REG_ADDR(31), data);
  apm_usb_ind_sds_rd(csr_base, KC_SERDES_CMU_REG_ADDR(31), &data);

  apm_usb_ind_sds_rd(csr_base, KC_SERDES_CMU_REG_ADDR(37), &data);
  data = FIELD_CMU_REG37_CTLE_CAL_DONE_OVR_SET(data, 0xf);
  data = FIELD_CMU_REG37_FT_SEARCH_DONE_OVR_SET(data, 0xf);
  apm_usb_ind_sds_wr(csr_base, KC_SERDES_CMU_REG_ADDR(37), data);
  apm_usb_ind_sds_rd(csr_base, KC_SERDES_CMU_REG_ADDR(37), &data);
}

/**
 * SERDES Transmit Configuration
 */
VOID apm_usb_kc_tx_asic(VOID* csr_base)
{
  UINT32 data;

  apmusb_dbg("Configure KoolChip Transmit\n");
  //TX control
  apm_usb_ind_sds_rd(csr_base, KC_SERDES_RXTX_REG_CH0 + KC_SERDES_RXTX_REG2__ADDR, &data);
  data = FIELD_RXTX_REG2_TX_FIFO_ENA_SET(data, 0x1);
  data = FIELD_RXTX_REG2_RESETB_TXD_SET(data, 0x1);
  data = FIELD_RXTX_REG2_BIST_ENA_TX_SET(data, 0x0);
  data = FIELD_RXTX_REG2_TX_INV_SET(data, 0x0);
  apm_usb_ind_sds_wr(csr_base, KC_SERDES_RXTX_REG_CH0 + KC_SERDES_RXTX_REG2__ADDR, data);

  apm_usb_ind_sds_rd(csr_base, KC_SERDES_RXTX_REG_CH0 + KC_SERDES_RXTX_REG6__ADDR, &data);
  data = FIELD_RXTX_REG6_TXAMP_ENA_SET(data, 0x1);
  data = FIELD_RXTX_REG6_TXAMP_CNTL_SET(data, 0x8);
  data = FIELD_RXTX_REG6_TX_IDLE_SET(data, 0x0);
  apm_usb_ind_sds_wr(csr_base, KC_SERDES_RXTX_REG_CH0 + KC_SERDES_RXTX_REG6__ADDR, data);

  apm_usb_ind_sds_rd(csr_base, KC_SERDES_RXTX_REG_CH0 + KC_SERDES_RXTX_REG4__ADDR, &data);
  data = FIELD_RXTX_REG4_TX_LOOPBACK_BUF_EN_SET(data, 0x0);
  apm_usb_ind_sds_wr(csr_base, KC_SERDES_RXTX_REG_CH0 + KC_SERDES_RXTX_REG4__ADDR, data);

  apm_usb_ind_sds_rd(csr_base, KC_SERDES_RXTX_REG_CH0 + KC_SERDES_RXTX_REG145__ADDR, &data);
  data = FIELD_RXTX_REG145_TX_IDLE_SATA_SET(data, 0x0);
  apm_usb_ind_sds_wr(csr_base, KC_SERDES_RXTX_REG_CH0 + KC_SERDES_RXTX_REG145__ADDR, data);
}

/**
 * SERDES Receive Configuration
 */
VOID apm_usb_kc_rx_asic(VOID* csr_base)
{
  UINT32 data;
  apmusb_dbg("Configure KoolChip Receive\n");

  apm_usb_ind_sds_rd(csr_base, KC_SERDES_RXTX_REG_CH0 + KC_SERDES_RXTX_REG2__ADDR, &data);
  data = FIELD_RXTX_REG2_RESETB_TERM_SET(data, 0x0);  // is this correct ???
  data = FIELD_RXTX_REG2_VTT_ENA_SET(data, 0x1);
  data = FIELD_RXTX_REG2_VTT_SEL_SET(data, 0x1);
  apm_usb_ind_sds_wr(csr_base, KC_SERDES_RXTX_REG_CH0 + KC_SERDES_RXTX_REG2__ADDR, data);

  apm_usb_ind_sds_rd(csr_base, KC_SERDES_RXTX_REG_CH0 + KC_SERDES_RXTX_REG1__ADDR, &data);
  data = FIELD_RXTX_REG1_RXACVCM_SET(data, 0x7);
  apm_usb_ind_sds_wr(csr_base, KC_SERDES_RXTX_REG_CH0 + KC_SERDES_RXTX_REG1__ADDR, data);

  apm_usb_ind_sds_rd(csr_base, KC_SERDES_RXTX_REG_CH0 + KC_SERDES_RXTX_REG12__ADDR, &data);
  data = FIELD_RXTX_REG12_RX_DET_TERM_ENABLE_SET(data, 0x0);
  apm_usb_ind_sds_wr(csr_base, KC_SERDES_RXTX_REG_CH0 + KC_SERDES_RXTX_REG12__ADDR, data);
#if 0
  //RX Word Mode, RX data rate  --> conrol by PIPE ????
  apm_usb_ind_sds_rd(csr_base, KC_SERDES_RXTX_REG_CH0 + KC_SERDES_RXTX_REG148__ADDR, &data);
  data = 0xffff; //rx bist word count 0
  apm_usb_ind_sds_wr(csr_base, KC_SERDES_RXTX_REG_CH0 + KC_SERDES_RXTX_REG148__ADDR, data);

  apm_usb_ind_sds_rd(csr_base, KC_SERDES_RXTX_REG_CH0 + KC_SERDES_RXTX_REG149__ADDR, &data);
  data = 0xffff; //rx bist word count 1
  apm_usb_ind_sds_wr(csr_base, KC_SERDES_RXTX_REG_CH0 + KC_SERDES_RXTX_REG149__ADDR, data);

  apm_usb_ind_sds_rd(csr_base, KC_SERDES_RXTX_REG_CH0 + KC_SERDES_RXTX_REG150__ADDR, &data);
  data = 0xffff; //rx bist word count 2
  apm_usb_ind_sds_wr(csr_base, KC_SERDES_RXTX_REG_CH0 + KC_SERDES_RXTX_REG150__ADDR, data);

  apm_usb_ind_sds_rd(csr_base, KC_SERDES_RXTX_REG_CH0 + KC_SERDES_RXTX_REG151__ADDR, &data);
  data = 0xffff; //rx bist word count 3
  apm_usb_ind_sds_wr(csr_base, KC_SERDES_RXTX_REG_CH0 + KC_SERDES_RXTX_REG151__ADDR, data);
#endif
  apm_usb_ind_sds_rd(csr_base, KC_SERDES_RXTX_REG_CH0 + KC_SERDES_RXTX_REG147__ADDR, &data);
    //  data = FIELD_RXTX_REG147_STMC_OVERRIDE_SET(data, 0x1); /*fixme: hknguyen. Original */
  data = FIELD_RXTX_REG147_STMC_OVERRIDE_SET(data, 0x6);
  apm_usb_ind_sds_wr(csr_base, KC_SERDES_RXTX_REG_CH0 + KC_SERDES_RXTX_REG147__ADDR, data);

  apm_usb_ind_sds_rd(csr_base, KC_SERDES_RXTX_REG_CH0 + KC_SERDES_RXTX_REG1__ADDR, &data);
  data = FIELD_RXTX_REG1_CTLE_EQ_SET(data, 0x1c);
  apm_usb_ind_sds_wr(csr_base, KC_SERDES_RXTX_REG_CH0 + KC_SERDES_RXTX_REG1__ADDR, data);

  apm_usb_ind_sds_rd(csr_base, KC_SERDES_RXTX_REG_CH0 + KC_SERDES_RXTX_REG0__ADDR, &data);
  data = FIELD_RXTX_REG0_CTLE_EQ_FR_SET(data, 0x10);
  data = FIELD_RXTX_REG0_CTLE_EQ_QR_SET(data, 0x10);
  data = FIELD_RXTX_REG0_CTLE_EQ_HR_SET(data, 0x10);
  apm_usb_ind_sds_wr(csr_base, KC_SERDES_RXTX_REG_CH0 + KC_SERDES_RXTX_REG0__ADDR, data);

  //CTLE MAN mode select, what does this mean ????

  apm_usb_ind_sds_rd(csr_base, KC_SERDES_RXTX_REG_CH0 + KC_SERDES_RXTX_REG12__ADDR, &data);
  data = FIELD_RXTX_REG12_LATCH_OFF_ENA_SET(data, 0x1);
  apm_usb_ind_sds_wr(csr_base, KC_SERDES_RXTX_REG_CH0 + KC_SERDES_RXTX_REG12__ADDR, data);

  apm_usb_ind_sds_rd(csr_base, KC_SERDES_RXTX_REG_CH0 + KC_SERDES_RXTX_REG128__ADDR, &data);
  data = FIELD_RXTX_REG128_LATCH_CAL_WAIT_SEL_SET(data, 0x3);
  apm_usb_ind_sds_wr(csr_base, KC_SERDES_RXTX_REG_CH0 + KC_SERDES_RXTX_REG128__ADDR, data);

  apm_usb_ind_sds_rd(csr_base, KC_SERDES_RXTX_REG_CH0 + KC_SERDES_RXTX_REG8__ADDR, &data);
  data = FIELD_RXTX_REG8_CDR_LOOP_ENA_SET(data, 0x1);
  data = FIELD_RXTX_REG8_CDR_BYPASS_RXLOS_SET(data, 0x0);
  apm_usb_ind_sds_wr(csr_base, KC_SERDES_RXTX_REG_CH0 + KC_SERDES_RXTX_REG8__ADDR, data);

  apm_usb_ind_sds_rd(csr_base, KC_SERDES_RXTX_REG_CH0 + KC_SERDES_RXTX_REG61__ADDR, &data);
  data = FIELD_RXTX_REG61_SPD_SEL_CDR_SET(data, 0x4);
  data &= ~(0x120); //tqnguyen: deassert bert_resetb and eye_acc_resetb
  apm_usb_ind_sds_wr(csr_base, KC_SERDES_RXTX_REG_CH0 + KC_SERDES_RXTX_REG61__ADDR, data);

  apm_usb_ind_sds_rd(csr_base, KC_SERDES_RXTX_REG_CH0 + KC_SERDES_RXTX_REG125__ADDR, &data);
  data = FIELD_RXTX_REG125_PQ_REG_SET(data, 0x8);
  data = FIELD_RXTX_REG125_PHZ_MANUAL_SET(data, 0x1);
  apm_usb_ind_sds_wr(csr_base, KC_SERDES_RXTX_REG_CH0 + KC_SERDES_RXTX_REG125__ADDR, data);

  apm_usb_ind_sds_rd(csr_base, KC_SERDES_RXTX_REG_CH0 + KC_SERDES_RXTX_REG11__ADDR, &data);
  data = FIELD_RXTX_REG11_PHASE_ADJUST_LIMIT_SET(data, 0x0);
  apm_usb_ind_sds_wr(csr_base, KC_SERDES_RXTX_REG_CH0 + KC_SERDES_RXTX_REG11__ADDR, data);

  apm_usb_ind_sds_rd(csr_base, KC_SERDES_RXTX_REG_CH0 + KC_SERDES_RXTX_REG61__ADDR, &data);
  data = FIELD_RXTX_REG61_LOADFREQ_SHIFT_SET(data, 0x0);
  apm_usb_ind_sds_wr(csr_base, KC_SERDES_RXTX_REG_CH0 + KC_SERDES_RXTX_REG61__ADDR, data);

  apm_usb_ind_sds_rd(csr_base, KC_SERDES_RXTX_REG_CH0 + KC_SERDES_RXTX_REG102__ADDR, &data);
  data = FIELD_RXTX_REG102_FREQLOOP_LIMIT_SET(data, 0x0);
  apm_usb_ind_sds_wr(csr_base, KC_SERDES_RXTX_REG_CH0 + KC_SERDES_RXTX_REG102__ADDR, data);

  apm_usb_ind_sds_rd(csr_base, KC_SERDES_RXTX_REG_CH0 + KC_SERDES_RXTX_REG8__ADDR, &data);
  data = FIELD_RXTX_REG8_SSC_ENABLE_SET(data, 0x1);
  apm_usb_ind_sds_wr(csr_base, KC_SERDES_RXTX_REG_CH0 + KC_SERDES_RXTX_REG8__ADDR, data);

  apm_usb_ind_sds_rd(csr_base, KC_SERDES_RXTX_REG_CH0 + KC_SERDES_RXTX_REG96__ADDR, &data);
  data = FIELD_RXTX_REG96_MU_FREQ1_SET(data, 0x10);
  data = FIELD_RXTX_REG96_MU_FREQ2_SET(data, 0x10);
  data = FIELD_RXTX_REG96_MU_FREQ3_SET(data, 0x10);
  apm_usb_ind_sds_wr(csr_base, KC_SERDES_RXTX_REG_CH0 + KC_SERDES_RXTX_REG96__ADDR, data);

  apm_usb_ind_sds_rd(csr_base, KC_SERDES_RXTX_REG_CH0 + KC_SERDES_RXTX_REG97__ADDR, &data);
  data = FIELD_RXTX_REG97_MU_FREQ4_SET(data, 0x10);
  data = FIELD_RXTX_REG97_MU_FREQ5_SET(data, 0x10);
  data = FIELD_RXTX_REG97_MU_FREQ6_SET(data, 0x10);
  apm_usb_ind_sds_wr(csr_base, KC_SERDES_RXTX_REG_CH0 + KC_SERDES_RXTX_REG97__ADDR, data);

  apm_usb_ind_sds_rd(csr_base, KC_SERDES_RXTX_REG_CH0 + KC_SERDES_RXTX_REG98__ADDR, &data);
  data = FIELD_RXTX_REG98_MU_FREQ7_SET(data, 0x10);
  data = FIELD_RXTX_REG98_MU_FREQ8_SET(data, 0x10);
  data = FIELD_RXTX_REG98_MU_FREQ9_SET(data, 0x10);
  apm_usb_ind_sds_wr(csr_base, KC_SERDES_RXTX_REG_CH0 + KC_SERDES_RXTX_REG98__ADDR, data);

  apm_usb_ind_sds_rd(csr_base, KC_SERDES_RXTX_REG_CH0 + KC_SERDES_RXTX_REG99__ADDR, &data);
  data = FIELD_RXTX_REG99_MU_PHASE1_SET(data, 0x7);
  data = FIELD_RXTX_REG99_MU_PHASE2_SET(data, 0x7);
  data = FIELD_RXTX_REG99_MU_PHASE3_SET(data, 0x7);
  apm_usb_ind_sds_wr(csr_base, KC_SERDES_RXTX_REG_CH0 + KC_SERDES_RXTX_REG99__ADDR, data);

  apm_usb_ind_sds_rd(csr_base, KC_SERDES_RXTX_REG_CH0 + KC_SERDES_RXTX_REG100__ADDR, &data);
  data = FIELD_RXTX_REG100_MU_PHASE4_SET(data, 0x7);
  data = FIELD_RXTX_REG100_MU_PHASE5_SET(data, 0x7);
  data = FIELD_RXTX_REG100_MU_PHASE6_SET(data, 0x7);
  apm_usb_ind_sds_wr(csr_base, KC_SERDES_RXTX_REG_CH0 + KC_SERDES_RXTX_REG100__ADDR, data);

  apm_usb_ind_sds_rd(csr_base, KC_SERDES_RXTX_REG_CH0 + KC_SERDES_RXTX_REG101__ADDR, &data);
  data = FIELD_RXTX_REG101_MU_PHASE7_SET(data, 0x7);
  data = FIELD_RXTX_REG101_MU_PHASE8_SET(data, 0x7);
  data = FIELD_RXTX_REG101_MU_PHASE9_SET(data, 0x7);
  apm_usb_ind_sds_wr(csr_base, KC_SERDES_RXTX_REG_CH0 + KC_SERDES_RXTX_REG101__ADDR, data);

  apm_usb_ind_sds_rd(csr_base, KC_SERDES_RXTX_REG_CH0 + KC_SERDES_RXTX_REG8__ADDR, &data);
    //  data = FIELD_RXTX_REG8_SD_DISABLE_SET(data, 0x1); /* fixme: hknguyen. Original */
  data = FIELD_RXTX_REG8_SD_DISABLE_SET(data, 0);
  apm_usb_ind_sds_wr(csr_base, KC_SERDES_RXTX_REG_CH0 + KC_SERDES_RXTX_REG8__ADDR, data);

  apm_usb_ind_sds_rd(csr_base, KC_SERDES_RXTX_REG_CH0 + KC_SERDES_RXTX_REG26__ADDR, &data);
  data = FIELD_RXTX_REG26_BLWC_ENA_SET(data, 0x1);
  apm_usb_ind_sds_wr(csr_base, KC_SERDES_RXTX_REG_CH0 + KC_SERDES_RXTX_REG26__ADDR, data);

  apm_usb_ind_sds_rd(csr_base, KC_SERDES_RXTX_REG_CH0 + KC_SERDES_RXTX_REG81__ADDR, &data);
  data = FIELD_RXTX_REG81_MU_DFE1_SET(data, 0xe);
  data = FIELD_RXTX_REG81_MU_DFE2_SET(data, 0xe);
  data = FIELD_RXTX_REG81_MU_DFE3_SET(data, 0xe);
  apm_usb_ind_sds_wr(csr_base, KC_SERDES_RXTX_REG_CH0 + KC_SERDES_RXTX_REG81__ADDR, data);

  apm_usb_ind_sds_rd(csr_base, KC_SERDES_RXTX_REG_CH0 + KC_SERDES_RXTX_REG82__ADDR, &data);
  data = FIELD_RXTX_REG82_MU_DFE4_SET(data, 0xe);
  data = FIELD_RXTX_REG82_MU_DFE5_SET(data, 0xe);
  data = FIELD_RXTX_REG82_MU_DFE6_SET(data, 0xe);
  apm_usb_ind_sds_wr(csr_base, KC_SERDES_RXTX_REG_CH0 + KC_SERDES_RXTX_REG82__ADDR, data);

  apm_usb_ind_sds_rd(csr_base, KC_SERDES_RXTX_REG_CH0 + KC_SERDES_RXTX_REG83__ADDR, &data);
  data = FIELD_RXTX_REG83_MU_DFE7_SET(data, 0xe);
  data = FIELD_RXTX_REG83_MU_DFE8_SET(data, 0xe);
  data = FIELD_RXTX_REG83_MU_DFE9_SET(data, 0xe);
  apm_usb_ind_sds_wr(csr_base, KC_SERDES_RXTX_REG_CH0 + KC_SERDES_RXTX_REG83__ADDR, data);

  apm_usb_ind_sds_rd(csr_base, KC_SERDES_RXTX_REG_CH0 + KC_SERDES_RXTX_REG84__ADDR, &data);
  data = FIELD_RXTX_REG84_MU_PH1_SET(data, 0xe);
  data = FIELD_RXTX_REG84_MU_PH2_SET(data, 0xe);
  data = FIELD_RXTX_REG84_MU_PH3_SET(data, 0xe);
  apm_usb_ind_sds_wr(csr_base, KC_SERDES_RXTX_REG_CH0 + KC_SERDES_RXTX_REG84__ADDR, data);

  apm_usb_ind_sds_rd(csr_base, KC_SERDES_RXTX_REG_CH0 + KC_SERDES_RXTX_REG85__ADDR, &data);
  data = FIELD_RXTX_REG85_MU_PH4_SET(data, 0xe);
  data = FIELD_RXTX_REG85_MU_PH5_SET(data, 0xe);
  data = FIELD_RXTX_REG85_MU_PH6_SET(data, 0xe);
  apm_usb_ind_sds_wr(csr_base, KC_SERDES_RXTX_REG_CH0 + KC_SERDES_RXTX_REG85__ADDR, data);

  apm_usb_ind_sds_rd(csr_base, KC_SERDES_RXTX_REG_CH0 + KC_SERDES_RXTX_REG86__ADDR, &data);
  data = FIELD_RXTX_REG86_MU_PH7_SET(data, 0xe);
  data = FIELD_RXTX_REG86_MU_PH8_SET(data, 0xe);
  data = FIELD_RXTX_REG86_MU_PH9_SET(data, 0xe);
  apm_usb_ind_sds_wr(csr_base, KC_SERDES_RXTX_REG_CH0 + KC_SERDES_RXTX_REG86__ADDR, data);

  apm_usb_ind_sds_rd(csr_base, KC_SERDES_RXTX_REG_CH0 + KC_SERDES_RXTX_REG87__ADDR, &data);
  data = FIELD_RXTX_REG87_MU_TH1_SET(data, 0xe);
  data = FIELD_RXTX_REG87_MU_TH2_SET(data, 0xe);
  data = FIELD_RXTX_REG87_MU_TH3_SET(data, 0xe);
  apm_usb_ind_sds_wr(csr_base, KC_SERDES_RXTX_REG_CH0 + KC_SERDES_RXTX_REG87__ADDR, data);

  apm_usb_ind_sds_rd(csr_base, KC_SERDES_RXTX_REG_CH0 + KC_SERDES_RXTX_REG88__ADDR, &data);
  data = FIELD_RXTX_REG88_MU_TH4_SET(data, 0xe);
  data = FIELD_RXTX_REG88_MU_TH5_SET(data, 0xe);
  data = FIELD_RXTX_REG88_MU_TH6_SET(data, 0xe);
  apm_usb_ind_sds_wr(csr_base, KC_SERDES_RXTX_REG_CH0 + KC_SERDES_RXTX_REG88__ADDR, data);

  apm_usb_ind_sds_rd(csr_base, KC_SERDES_RXTX_REG_CH0 + KC_SERDES_RXTX_REG89__ADDR, &data);
  data = FIELD_RXTX_REG89_MU_TH7_SET(data, 0xe);
  data = FIELD_RXTX_REG89_MU_TH8_SET(data, 0xe);
  data = FIELD_RXTX_REG89_MU_TH9_SET(data, 0xe);
  apm_usb_ind_sds_wr(csr_base, KC_SERDES_RXTX_REG_CH0 + KC_SERDES_RXTX_REG89__ADDR, data);

  apm_usb_ind_sds_rd(csr_base, KC_SERDES_RXTX_REG_CH0 + KC_SERDES_RXTX_REG145__ADDR, &data);
  data = FIELD_RXTX_REG145_RXDFE_CONFIG_SET(data, 0x3);
  apm_usb_ind_sds_wr(csr_base, KC_SERDES_RXTX_REG_CH0 + KC_SERDES_RXTX_REG145__ADDR, data);

  apm_usb_ind_sds_rd(csr_base, KC_SERDES_RXTX_REG_CH0 + KC_SERDES_RXTX_REG28__ADDR, &data);
    //  data = 0xffff; //DFE tab enables  /* fixme:hknguyen. Original */
  data = 0x7;
  apm_usb_ind_sds_wr(csr_base, KC_SERDES_RXTX_REG_CH0 + KC_SERDES_RXTX_REG28__ADDR, data);

  apm_usb_ind_sds_rd(csr_base, KC_SERDES_RXTX_REG_CH0 + KC_SERDES_RXTX_REG7__ADDR, &data);
  data = FIELD_RXTX_REG7_RESETB_RXD_SET(data, 0x1);
  data = FIELD_RXTX_REG7_LOOP_BACK_ENA_CTLE_SET(data, 0x0);
  data = FIELD_RXTX_REG7_BIST_ENA_RX_SET(data, 0x0);
  apm_usb_ind_sds_wr(csr_base, KC_SERDES_RXTX_REG_CH0 + KC_SERDES_RXTX_REG7__ADDR, data);

  apm_usb_ind_sds_rd(csr_base, KC_SERDES_RXTX_REG_CH0 + KC_SERDES_RXTX_REG12__ADDR, &data);
  data = FIELD_RXTX_REG12_RX_INV_SET(data, 0x0);
  apm_usb_ind_sds_wr(csr_base, KC_SERDES_RXTX_REG_CH0 + KC_SERDES_RXTX_REG12__ADDR, data);

    /*invert rx clock*/
/*  apm_usb_ind_sds_rd(csr_base, KC_SERDES_RXTX_REG_CH0 + KC_SERDES_RXTX_REG13__ADDR, &data);
  data = data | 0x2000;
  apm_usb_ind_sds_wr(csr_base, KC_SERDES_RXTX_REG_CH0 + KC_SERDES_RXTX_REG13__ADDR, data);
*/
}

/**
 * Tuning Koolchip SERDES
 */
VOID apm_usb_kc_tuning(VOID* csr_base)
{
  UINT32 data;

  apmusb_dbg("Turning KoolChip USB ...\n");

  //extend receiver detect time
  apm_usb_ind_pcs_rd(csr_base, KC_PIPE_REGS_RECEIVE_DETECT_CONTROL__ADDR, &data);
  data = FIELD_RECEIVE_DETECT_CONTROL_RX_PRES_ONE_CNT_TH_SET(data, 0x7d0);   //2000
//  data = FIELD_RECEIVE_DETECT_CONTROL_RX_PRES_ONE_CNT_TH_SET(data, 0xFA0);  //10000
  apm_usb_ind_pcs_wr(csr_base, KC_PIPE_REGS_RECEIVE_DETECT_CONTROL__ADDR, data);

  //clear new_lfps mode
  apm_usb_ind_pcs_rd(csr_base, KC_PIPE_REGS_SERDES_CONTROL3__ADDR, &data);
  data = data & ~(1<<27);
  data = FIELD_SERDES_CONTROL3_RX_LOS_BASED_LFPS_SET(data, 0x1);
  apm_usb_ind_pcs_wr(csr_base, KC_PIPE_REGS_SERDES_CONTROL3__ADDR, data);

  apmusb_dbg("Enable power sequence: \n");
  data = apm_usb_readl(csr_base+USB_SDS_CSR_USB_PIPE_PCS_CTL0);
  data |= USB_SDS_CSR_USB_PIPE_PCS_pd_rdy_i;
  apm_usb_writel(csr_base+USB_SDS_CSR_USB_PIPE_PCS_CTL0, data);

  //CDR SEL override
  apm_usb_ind_pcs_rd(csr_base, KC_PIPE_REGS_SERDES_DFE_CONTROL0__ADDR, &data);
  data = FIELD_SERDES_DFE_CONTROL0_P2S_I_SPD_SEL_CDR_OVR_LN_SET(data, 0x7);
  apm_usb_ind_pcs_wr(csr_base, KC_PIPE_REGS_SERDES_DFE_CONTROL0__ADDR, data);

  //increase tx amp, channel 0 bit location is different from rest of channels
  apm_usb_ind_pcs_rd(csr_base, KC_PIPE_REGS_SERDES_CONTROL3__ADDR, &data);
  data = FIELD_SERDES_CONTROL3_P2S_I_TX_AMP_EN_LN0_SET(data, 0x1);
  data = FIELD_SERDES_CONTROL3_P2S_I_TX_AMP_LN0_SET(data, 0xa);
  apm_usb_ind_pcs_wr(csr_base, KC_PIPE_REGS_SERDES_CONTROL3__ADDR, data);
}


/**************************************************************
 * USB CONFIGURATION
 **************************************************************/

/**
 * Power up USB SERDES.
 * This seems not necessary because SERDES is reset when enabling USB controller.
 * (refer the apm_usb_enable procedure)
 */
VOID apm_usb_serdes_powerup(VOID *csr_base, INTN assert) {
  UINT32 data;

  /* CMU registers */
  // CMU_reg0 bit 14
  apm_usb_ind_sds_rd(csr_base, KC_SERDES_CMU_REG_ADDR(0), &data);
  data = FIELD_CMU_REG0_PDOWN_SET(data, assert);
  apm_usb_ind_sds_wr(csr_base, KC_SERDES_CMU_REG_ADDR(0), data);
  // CMU_reg1 bit 15
  apm_usb_ind_sds_rd(csr_base, KC_SERDES_CMU_REG_ADDR(1), &data);
  data = FIELD_CMU_REG1_PLL_PDOWN_SET(data, assert);
  apm_usb_ind_sds_wr(csr_base, KC_SERDES_CMU_REG_ADDR(1), data);

  /* Per-channel power down */
  // rxtx_reg2 register
  apm_usb_ind_sds_rd(csr_base, KC_SERDES_RXTX_REG_CH0 + KC_SERDES_RXTX_REG2__ADDR, &data);
  data = FIELD_RXTX_REG2_RXPDBIAS_SET(data,assert);
  data = FIELD_RXTX_REG2_TX_PDOWN_SET(data,assert);
  apm_usb_ind_sds_wr(csr_base, KC_SERDES_RXTX_REG_CH0 + KC_SERDES_RXTX_REG2__ADDR, data);
  // rxtx_reg12 register
  apm_usb_ind_sds_rd(csr_base, KC_SERDES_RXTX_REG_CH0 + KC_SERDES_RXTX_REG12__ADDR, &data);
  data = FIELD_RXTX_REG12_RX_PDOWN_SET(data,assert);
  apm_usb_ind_sds_wr(csr_base, KC_SERDES_RXTX_REG_CH0 + KC_SERDES_RXTX_REG12__ADDR, data);

}

VOID apm_enable_traceclk(VOID *csr_base)
{
  UINT32 reg_val;
  VOID *clkmem = (VOID *) 0x1f2e0000;
  INTN timeoutpoll = 2000;

  apmusb_dbg( "Enabling Trace Clk\n");
//  clkmem = ioremap(0x1f2e0000, 0x10000);

  /* Enable Trace CLK */
  reg_val = apm_usb_readl(clkmem+SM_DBGTRC_CLKRST_CSR + DBGTRCClkEnReg);
  reg_val |= 0x00000001;
  apm_usb_writel(clkmem+SM_DBGTRC_CLKRST_CSR + DBGTRCClkEnReg,reg_val);

  /* Release reset Trace DBG */
  apmusb_dbg( "Deasserting trace reset\n");
  reg_val = apm_usb_readl(clkmem+SM_DBGTRC_CLKRST_CSR + DBGTRCResetReg);
  reg_val &= ~0x00000001;
  apm_usb_writel(clkmem+SM_DBGTRC_CLKRST_CSR + DBGTRCResetReg,reg_val);

  /* Reset PCIE Clock MACRO */
  apmusb_dbg( "Deasserting PCIE Clock MACRO reset\n");
  reg_val = apm_usb_readl(clkmem+SM_TRACE_SDS_CSR_REGS + SM_TRACE_CLK_MACRO_REG);
  reg_val |= 0x00000001;
  apm_usb_writel(clkmem+SM_TRACE_SDS_CSR_REGS + SM_TRACE_CLK_MACRO_REG, reg_val);

  /* Polling status */
  reg_val = usb_apm_wait_register(clkmem+SM_TRACE_SDS_CSR_REGS + SM_TRACE_CLK_MACRO_REG, 0xC0000000, 0xC0000000, 1, timeoutpoll);
}

/*
 * Configure clocks
 */
INTN apm_usb_serdes_clk_config(VOID *csr_base, INTN clk_type)
{
  UINT32 reg_val;

  if(clk_type == USB_INTCLK){
    // Enable trace clock
    apm_enable_traceclk(csr_base);

    apmusb_dbg("Configure Internal SERDES/PIPE Clock\n");
    apm_usb_ind_sds_rd(csr_base, KC_SERDES_CMU_REG_ADDR(1), &reg_val);
    reg_val = FIELD_CMU_REG1_REFCLK_CMOS_SEL_SET(reg_val, 1);
    apm_usb_ind_sds_wr(csr_base, KC_SERDES_CMU_REG_ADDR(1), reg_val);

    apm_usb_ind_sds_rd(csr_base, KC_SERDES_CMU_REG_ADDR(0), &reg_val);
    reg_val = FIELD_CMU_REG0_PLL_REF_SEL_SET(reg_val, 1);
    apm_usb_ind_sds_wr(csr_base, KC_SERDES_CMU_REG_ADDR(0), reg_val);
  } else if (clk_type == USB_EXTCLK){
    apmusb_dbg("Configure External SERDES/PIPE Clock\n");
    apm_usb_ind_sds_rd(csr_base, KC_SERDES_CMU_REG_ADDR(1), &reg_val);
    reg_val = FIELD_CMU_REG1_REFCLK_CMOS_SEL_SET(reg_val, 0);
    apm_usb_ind_sds_wr(csr_base, KC_SERDES_CMU_REG_ADDR(1), reg_val);
    apm_usb_ind_sds_rd(csr_base, KC_SERDES_CMU_REG_ADDR(0), &reg_val);
    reg_val = FIELD_CMU_REG0_PLL_REF_SEL_SET(reg_val, 0);
    apm_usb_ind_sds_wr(csr_base, KC_SERDES_CMU_REG_ADDR(0), reg_val);
  } else {
    apmusb_err("Unknown RefClk type!!!\n");
    return -1;
  }
  return 0;
}


VOID apm_usb_init_memblk(VOID *csr_base)
{
  UINTN rd_data;
  UINTN i;

  apmusb_dbg("Clear RAM shutdown and wait for memory ready\n");
  // Clear memory shutdown
  apm_usb_writel(csr_base+USB_CSR_CFG_MEM_RAM_SHUTDOWN, 0);
  rd_data = apm_usb_readl(csr_base+USB_CSR_CFG_MEM_RAM_SHUTDOWN);

  // Wait for memory ready
  rd_data = apm_usb_readl(csr_base+USB_CSR_BLOCK_MEM_RDY);
  while (rd_data != 0xFFFFFFFF) {
    rd_data = apm_usb_readl(csr_base+USB_CSR_BLOCK_MEM_RDY);
    xgene_usb_udelay(20);
  }
  for (i = 0; i < 8; i++) {
    rd_data = apm_usb_readl(csr_base + USB_CSR_BLOCK_MEM_RDY);
    xgene_usb_udelay(10);
  }
}

/*
 * Enbale USB host controller
 */
VOID apm_usb_enable(VOID* csr_base)
{
  UINT32 val;

  /* Enable clock through CLK_RST module */
  apmusb_dbg("Enable UTMI, PIPE, USB and CSR clock\n");
  val = USB_CLKRST_CSR_clk_utmi_clken |
      USB_CLKRST_CSR_clk_pipe_clken |
      USB_CLKRST_CSR_clk_usb_clken |
      USB_CLKRST_CSR_csr_clken;
  apm_usb_writel(csr_base+USB_CLKRST_CSR_USBClkEnReg, val);
  xgene_usb_mdelay(10);

  /* Place sds, vaux, vcc, axi and csr under reset*/
  apmusb_dbg("Place SDS/VAUX/VCC/AXI/CSR block under reset\n");
  val = USB_CLKRST_CSR_utmi_clk_reset |
      USB_CLKRST_CSR_pipe_clk_reset |
      USB_CLKRST_CSR_sds_reset |
      USB_CLKRST_CSR_vaux_reset |
      USB_CLKRST_CSR_vcc_reset |
      USB_CLKRST_CSR_axi_core_reset |
      USB_CLKRST_CSR_csr_reset;
  apm_usb_writel(csr_base+USB_CLKRST_CSR_USBSResetReg, val);
  xgene_usb_mdelay(100);

  /* Place UTMI and PIPE clock under reset, and release other from reset */
  apmusb_dbg("Place UTMI and PIPE clock under reset\n");
  val = ~USB_CLKRST_CSR_sds_reset &
     ~USB_CLKRST_CSR_vaux_reset &
     ~USB_CLKRST_CSR_vcc_reset &
     ~USB_CLKRST_CSR_axi_core_reset &
     ~USB_CLKRST_CSR_csr_reset;
  apm_usb_writel(csr_base+USB_CLKRST_CSR_USBSResetReg, val /*0x60*/);
  xgene_usb_mdelay(100);
}

VOID apm_usb_pipe_power_enable(VOID *csr_base)
{
  UINT32 val;

  /* Enable PIPE power sequence */
  apmusb_dbg("Enable power sequence: \n");
  val = apm_usb_readl(csr_base+USB_SDS_CSR_USB_PIPE_PCS_CTL0);
  val |= USB_SDS_CSR_USB_PIPE_PCS_pd_rdy_i;
  apm_usb_writel(csr_base+USB_SDS_CSR_USB_PIPE_PCS_CTL0, val);

  /* Polling PCS_STATUS0 until PIPE clock valid status */
  apmusb_dbg("Wait until PIPE clock valid\n");
  val = usb_apm_wait_register(csr_base+USB_SDS_CSR_USB_PIPE_PCS_STATUS0, 0x10000000, 0x10000000, 1, 20000);
  if(val & 0x10000000) {
    apmusb_dbg(" PIPE clock valid (val=0x%08x)\n", val);
  } else {
    apmusb_err(" PIPE clock time out (val=0x%08x) !!!\n", val);
  }
}

/**
 * Configure SERDES Koolchip.
 */
VOID apm_usb_kc_serdes_cfg(VOID *csr_base, INTN clk_type)
{

  /* KoolChip SERDES Configuration */
  apm_usb_kc_tuning(csr_base);
  apm_usb_kc_tx_asic(csr_base);
  apm_usb_kc_rx_asic(csr_base);
  apm_usb_serdes_clk_config(csr_base, clk_type);
  apm_usb_kc_pll_asic(csr_base);

#ifdef APM_USB_VDEBUG
  apm_usb_kc_dump(csr_base);
#endif
}

VOID apm_usb_kc_serdes_disable(VOID *csr_base, INTN clk_type)
{
  apm_usb_serdes_clk_config(csr_base, clk_type);
}

/*
 * Configure USB2 clocks.
 * Use 12MHz external clock for USB0 and 48MHz internal
 * clock for USB1.
 */
VOID usb2_clk_config(VOID *csr_base, INTN port_num) {
  usb_otg_ctl_r usb_otg_ctl;

  apmusb_dbg("Configure USB2 PHY clock\n");
  usb_otg_ctl.val = apm_usb_readl(csr_base+USB_SDS_CSR_USB_OTG_CTL);
  usb_otg_ctl.field.port_reset = 1;
  if(port_num == 0) {
    /* refclksel=1, refclkdiv = 12MHz, port_reset=1 */
    usb_otg_ctl.field.refclksel = USB_SDS_CSR_refclksel_ext_crys;
    usb_otg_ctl.field.refclkdiv = USB_SDS_CSR_refclkdiv_12MHz;
  }
  else {
    /* refclksel=1, refclkdiv = 48MHz, port_reset=1*/
    usb_otg_ctl.field.refclksel = USB_SDS_CSR_refclksel_pll_core;
    usb_otg_ctl.field.refclkdiv = USB_SDS_CSR_refclkdiv_48MHz;
  }
  apm_usb_writel(csr_base+USB_SDS_CSR_USB_OTG_CTL, usb_otg_ctl.val);
}


/**
 * Initialize USB Controller.
 */

INTN apm_usb_init(UINT64 csr_base, UINT64 xhci_base, INTN cid, INTN irq, UINT32 gen_sel, INTN clk_sel, INTN ovrcur_en, INTN ovrcur_ivrt)
{
  usb_sds_ctl0_r usb_sds_ctl0;
  UINTN reg_value;
  struct xhci_gctl_reg *gbl_regs;
  VOID *pcsr_base = (VOID *)csr_base;
  VOID *pxhci_base = (VOID *)xhci_base;
  INTN rc;

  apmusb_dbg("USB Initialization ... \n");

  apmusb_dbg("USB%d: CSR PAddr 0x%016LX VAddr 0x%p, XHCI PAddr 0x%016LX VAddr 0x%p \n", cid, csr_base, pcsr_base, xhci_base, pxhci_base);

  gbl_regs = pxhci_base + GLB_REG_OFF;
  
  /* Enable USB */
  apm_usb_enable(pcsr_base);

  /* SERDES power up */
  apm_usb_serdes_powerup(pcsr_base, 0);

  /* Initialize RAM shutdown */
  apm_usb_init_memblk(pcsr_base);

  apm_usb_writel(pcsr_base+USB_CSR_Endian, 0x0);

  /* Read ID */
  reg_value = apm_usb_readl(pcsr_base+USB_CSR_USB30Bid);
  apmusb_dbg("USB3.0 port %d ID: %x\n", cid, reg_value);

  /* Read Global SynopsysID */
  reg_value = apm_usb_readl(&gbl_regs->gsnpsid);
  apmusb_dbg("SynopsysID: Core Identification Number=%04x - release number=%04x\n",
      (UINT16)(reg_value >> 16),(UINT16)reg_value);

  reg_value = apm_usb_readl(pcsr_base+USB_CSR_HBFSideBandReg);
  reg_value |= 0x5; // Read/Write Coherency Override Enable
  apm_usb_writel(pcsr_base+USB_CSR_HBFSideBandReg, reg_value);
  xgene_usb_mdelay(10);
  reg_value = apm_usb_readl(pcsr_base+USB_CSR_HBFSideBandReg);
  reg_value |= 0xa;
  apm_usb_writel(pcsr_base+USB_CSR_HBFSideBandReg, reg_value);

  /* Enable PIPE Power Sequence */
  apm_usb_pipe_power_enable(pcsr_base);

  apmusb_dbg("Customer pin mode for USB3 operation\n");
  usb_sds_ctl0.val = apm_usb_readl(pcsr_base + USB_SDS_CSR_USB_SDS_CTL0);
  usb_sds_ctl0.field.cfg_i_customer_pin_mode = 0x0D21;
  usb_sds_ctl0.field.cfg_i_usr_pd_pll = 0;

  /* select between single-ended and differential source clock */
  
  if (clk_sel == USB_INTCLK) {
    usb_sds_ctl0.field.cfg_i_refclk_cmos_sel = 1;
  } else {
    usb_sds_ctl0.field.cfg_i_refclk_cmos_sel = 0;
  }
  usb_sds_ctl0.field.cfg_i_rx_spare = 0;
  apm_usb_writel(pcsr_base + USB_SDS_CSR_USB_SDS_CTL0, usb_sds_ctl0.val);
 

  /* Initialize SERDES */
  if(gen_sel == 3) {
    apm_usb_kc_serdes_cfg(pcsr_base, clk_sel);
  }
  else {
    apm_usb_kc_serdes_disable(pcsr_base, clk_sel);
  }

  /* Tune eye pattern */
  apm_usb_writel(pcsr_base+USB_SDS_CSR_USB_OTG_OVER, 0x001c0365);

  /* Configure USB2 PHY clock */
  usb2_clk_config(pcsr_base, cid);

  /* Reset USB Core */
  apmusb_dbg("Put USB Core into reset\n");
  reg_value = apm_usb_readl(&gbl_regs->gctl);
  reg_value |= BIT11; // Activate soft reset
  apm_usb_writel(&gbl_regs->gctl, reg_value);

  /* PowerPresent from PHY is forwarded to controller */
  /* Control/Monitor status of PIPE or UTMI signals */
  reg_value = apm_usb_readl(pcsr_base+USB_CSR_PipeUtmiReg); //ClockReady register
  reg_value |= USB_CSR_power_present_override_dis; // Set power_present_override_dis = 1
  apm_usb_writel(pcsr_base+USB_CSR_PipeUtmiReg, reg_value);

  /* Configure Power Management Register */
  apmusb_dbg("Enable port over current\n");
  reg_value = apm_usb_readl(pcsr_base+USB_CSR_PowerMngtReg);

  if(ovrcur_en) {
    reg_value |= USB_CSR_port_ovrcur_enable;
    if(ovrcur_ivrt) {
      apmusb_dbg("Enable port over current invert\n");
      reg_value |= USB_CSR_port_ovrcur_invert;
    }
  }

  reg_value |= USB_CSR_host_port_power_control_present;
  apm_usb_writel(pcsr_base+USB_CSR_PowerMngtReg, reg_value);
  
  /* Disable USB 3.0 */
  if(gen_sel < 3) {
    apmusb_dbg("Disable USB3.0 capability\n");
    reg_value = apm_usb_readl(pcsr_base+USB_CSR_HostPortReg);
    reg_value |= 0x1;
    apm_usb_writel(pcsr_base+USB_CSR_HostPortReg, reg_value);
  }

  apmusb_dbg("Put USB2/USB3 PHY into reset\n");
  /* Reset USB3 PHY */
  reg_value = apm_usb_readl(&gbl_regs->gusb3pipeclt[0]);
  reg_value |= BIT31;
  apm_usb_writel(&gbl_regs->gusb3pipeclt[0], reg_value);
  /* Reset USB2 PHY */
  reg_value = apm_usb_readl(&gbl_regs->gusb2phycfg[0]);
  reg_value |= BIT31;
  apm_usb_writel(&gbl_regs->gusb2phycfg[0], reg_value);
  xgene_usb_udelay(5000);

  /* PHY Controller Configuration */
  apmusb_dbg("Clear USB3 PHY soft reset\n");
  usb_gusb3pipectl_r usb_gusb3pipectl;
  usb_gusb3pipectl.val = apm_usb_readl(&gbl_regs->gusb3pipeclt[0]);
  usb_gusb3pipectl.field.TxDeemphasis = TxDemphasis_Minus3_5dB;
  usb_gusb3pipectl.field.DatWidth = PIPE_DATWIDTH_16;
  usb_gusb3pipectl.field.PHYSoftRst = 0;
  usb_gusb3pipectl.field.SkipRxDet = 1;
  usb_gusb3pipectl.field.TxSwing = 1;
  usb_gusb3pipectl.field.TxMargin = 1;
  apm_usb_writel(&gbl_regs->gusb3pipeclt[0], usb_gusb3pipectl.val);
  
  /* Clear USB2 PHY soft reset  */
  apmusb_dbg("Clear USB2 PHY soft reset\n");
  reg_value = apm_usb_readl(&gbl_regs->gusb2phycfg[0]);
  reg_value &= ~USB_GUSB2PHYCFG_PHYSoftRst &
           ~USB_GUSB2PHYCFG_SusPHY &
           ~USB_GUSB2PHYCFG_PhyIf;
  apm_usb_writel(&gbl_regs->gusb2phycfg[0], reg_value);
  xgene_usb_udelay(100);

  /* Clear CORE soft reset */
  apmusb_dbg("Clear USB CORE reset\n");
  usb_gctl_r usb_gctl;
  usb_gctl.val = apm_usb_readl(&gbl_regs->gctl);
  //usb_gctl.field.PwrDnScale = usb_para.sus_clk / 16000;
  usb_gctl.field.RAMClkSel = 0; //1;
  usb_gctl.field.U2RSTECN = 0; //1;
  usb_gctl.field.CoreSoftReset = 0;
  apm_usb_writel(&gbl_regs->gctl, usb_gctl.val);

  /* Release reset for DWC core */
  reg_value = apm_usb_readl(&gbl_regs->gctl);
  reg_value = reg_value & (~USB_GCTL_CoreSoftRst); // De-activate core soft reset
  apm_usb_writel(&gbl_regs->gctl, reg_value);
  xgene_usb_udelay(5000);

  /* Check CMU PLL ready */
  if(gen_sel == 3) {
    apmusb_dbg("Wait until CMU PLL ready\n"); // apm_usb_serdes_lock_pll
    reg_value = usb_apm_wait_register(pcsr_base+USB_SDS_CSR_USB_SDS_CMU_STATUS0, 0x7, 0x7, 1, 1000);
    if(reg_value & 0x7)
      apmusb_dbg("CMU PLL ready (CMU_STATUS0 0x%08x)\n", reg_value);
    else
      apmusb_dbg("Timeout waiting for SERDES CMU PLL ready (0x%08x)!!!\n", reg_value);

    /* Waiting when CLK is stable */
    apmusb_dbg("Waiting PHY status de-asserted ...");
    reg_value = usb_apm_wait_register(pcsr_base+USB_CSR_PipeUtmiReg, USB_CSR_pipe0_phystatus_sync, 0, 1, 1000);
    if((reg_value & USB_CSR_pipe0_phystatus_sync) != 0) {
      apmusb_err("Timeout waiting for PHY status de-asserted\n");
      rc = -1;
      goto error;
    }
    apmusb_dbg("PHY Status de-asserted\n");
   }

  xgene_usb_mdelay(150);

  /* Release resets after PIPE clock and UTMI clock is stable */
  apmusb_dbg("Release resets after PIPE clock and UTMI clock is stable\n");
  reg_value = apm_usb_readl(pcsr_base+USB_CLKRST_CSR_USBSResetReg);
  reg_value &= ~USB_CLKRST_CSR_utmi_clk_reset &
      ~USB_CLKRST_CSR_pipe_clk_reset;
  apm_usb_writel(pcsr_base+USB_CLKRST_CSR_USBSResetReg, reg_value);

  /* Clear OTG PHY reset */
  apmusb_dbg("Clear OTG PHY reset\n");
  usb_otg_ctl_r usb_otg_ctl;
  usb_otg_ctl.val = apm_usb_readl(pcsr_base+USB_SDS_CSR_USB_OTG_CTL);
  usb_otg_ctl.field.port_reset = 0;
  apm_usb_writel(pcsr_base+USB_SDS_CSR_USB_OTG_CTL, usb_otg_ctl.val);
  xgene_usb_mdelay(10);

  /* Enable core interrupt */
  apmusb_dbg("Enable core interrupt\n");
  apm_usb_writel(pcsr_base+USB_CSR_InterruptStatusMask, 0xFFFFFFFE);

  /* Enable AXI Interrupts */
  apm_usb_writel(pcsr_base+INT_SLV_TMOMask, 0x0);
  apm_usb_writel(pcsr_base+USB_CSR_SlvRdErrAttributes, 0xffffffff);
  apm_usb_writel(pcsr_base+USB_CSR_SlvWrErrAttributes, 0xffffffff);
  apm_usb_writel(pcsr_base+USB_CSR_MstRdErrAttributes, 0xffffffff);
  apm_usb_writel(pcsr_base+USB_CSR_MstWrErrAttributes, 0xffffffff);

  /* Enable Read to Write Flush */
  apm_usb_writel(pcsr_base+CFG_AMA_MODE, 0x2);

  if (gen_sel == 3) {
    apmusb_dbg("Waiting PIPE clock ready ...");
    reg_value = usb_apm_wait_register(pcsr_base+USB_CSR_PipeUtmiReg, USB_CSR_csr_pipe_clk_ready, USB_CSR_csr_pipe_clk_ready, 1, 2000);
    if((reg_value & USB_CSR_csr_pipe_clk_ready) == 0) {
      apmusb_err("Timeout waiting for PIPE clock ready (0x%08x)\n", reg_value);
      rc = -1;
      goto error;
    } else
      apmusb_dbg("PIPE clock ready\n");
  }

  /*  Poll register CNR until its cleared */
  apmusb_dbg("Wait until USB Controller is ready\n");
  reg_value = usb_apm_wait_register(pxhci_base+USB_USBSTS, 0x800, 0x0, 10,2000);
  if(reg_value & 0x800) {
    apmusb_dbg("Timeout waiting for USB ready\n");
    rc =  -1;
    goto error;
  } else {
    apmusb_dbg("USB controller is ready, USBSTS=%x\n", reg_value);
  }
  xgene_usb_mdelay(100);

  return 0;

error:
  return rc;
}
