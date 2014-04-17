#if !defined(__XGENE_USB_H__)
#define __XGENE_USB_H__

#include <Uefi.h>
#include <Protocol/ComponentName.h>
#include <Protocol/DriverBinding.h>
#include <Protocol/PciIo.h>
#include <Protocol/IdeControllerInit.h>
#include <Library/UefiDriverEntryPoint.h>
#include <Library/DebugLib.h>
#include <Library/TimerLib.h>
#include <Library/UefiLib.h>
#include <Library/BaseLib.h>
#include <Library/ArmLib.h>
#include <Library/BaseMemoryLib.h>
#include <Library/MemoryAllocationLib.h>
#include <Library/DevicePathLib.h>
#include <Library/UefiBootServicesTableLib.h>

typedef UINT32 u32;
typedef UINT64 u64;
typedef UINT8  u8;
typedef UINT32 uint32_t;

#define USB_EXTCLK 1
#define USB_INTCLK 0

/* General definition */
#define BIT0    0x00000001
#define BIT1    0x00000002
#define BIT2    0x00000004
#define BIT3    0x00000008
#define BIT4    0x00000010
#define BIT5    0x00000020
#define BIT6    0x00000040
#define BIT7    0x00000080
#define BIT8    0x00000100
#define BIT9    0x00000200
#define BIT10    0x00000400
#define BIT11    0x00000800
#define BIT12    0x00001000
#define BIT13    0x00002000
#define BIT14    0x00004000
#define BIT15    0x00008000
#define BIT16    0x00010000
#define BIT17    0x00020000
#define BIT18    0x00040000
#define BIT19    0x00080000
#define BIT20    0x00100000
#define BIT21    0x00200000
#define BIT22    0x00400000
#define BIT23    0x00800000
#define BIT24    0x01000000
#define BIT25    0x02000000
#define BIT26    0x04000000
#define BIT27    0x08000000
#define BIT28    0x10000000
#define BIT29    0x20000000
#define BIT30    0x40000000
#define BIT31    0x80000000

/*
 *  USB CSR Registers
 */
#define USB_CSR_USB30Bid    0x0000
#define USB_CSR_SlvRdErrAttributes              0x4
#define USB_CSR_SlvWrErrAttributes              0x8
#define USB_CSR_MstRdErrAttributes              0xc
#define USB_CSR_MstWrErrAttributes              0x10
#define USB_CSR_Endian      0x0014
#define USB_CSR_ram_ctrl1   0x0018
#define USB_CSR_ram_ctrl2   0x001c
#define USB_CSR_ram_ctrl3   0x0020
#define USB_CSR_HostPortReg          0x0030
#define USB_CSR_HubPortReg           0x0034
#define USB_CSR_PowerMngtReg         0x0038
#define USB_CSR_port_power_invert    (BIT31)
#define USB_CSR_port_ovrcur_invert   (BIT29)
#define USB_CSR_port_ovrcur_enable   (BIT28)
#define USB_CSR_pme_generation       (BIT9)
#define USB_CSR_pme_en               (BIT8)
#define USB_CSR_host_port_power_control_present  (BIT0)
#define USB_CSR_HBFSideBandReg       0x003c
#define USB_CSR_FladjReg             0x40
#define USB_CSR_Debug0               0x44
#define USB_CSR_Debug1               0x48
#define USB_CSR_SwInt                0x4c
#define USB_CSR_LA_Trace_Hi          0x50
#define USB_CSR_LA_Trace_Lo          0x54
#define USB_CSR_XHC_CTRL             0x58
#define USB_CSR_InterruptStatus      0x0060
#define USB_CSR_InterruptStatusMask  0x0064
#define USB_CSR_PipeUtmiReg          0x0070
#define USB_CSR_pipe0_phystatus_sync        (BIT31)
#define USB_CSR_power_present_override_dis  (BIT26)
#define USB_CSR_csr_use_utmi_for_pipe       (BIT8)
#define USB_CSR_csr_utmi_clk_ready          (BIT3)
#define USB_CSR_csr_pipe_clk_ready          (BIT1)
#define USB_CSR_WakeOnUSBCtlReg             0x0080
#define USB_CSR_HBFMasterMaskRegLow         0x94
#define USB_CSR_HBFMasterMaskRegHigh        0x98
#define USB_CSR_HBFMasterBaseAddrRegLow     0x9c
#define USB_CSR_HBFMasterBaseAddrRegHigh    0xa0
#define USB_CSR_HBFMasterDestAddrRegLow     0xa4
#define USB_CSR_HBFMasterDestAddrRegHigh    0xa8
#define USB_CSR_SHIM_CTL                    0xac

/*
 * USB SERDES CSR register offset
 */
#define USB_SDS_CSR                          0xa000
#define USB_SDS_CSR_USB_PIPE_CTL             (USB_SDS_CSR + 0x0)
#define USB_SDS_CSR_USB_PIPE_PCS_STATUS0     (USB_SDS_CSR + 0x4)
#define USB_SDS_CSR_USB_PIPE_PCS_STATUS1     (USB_SDS_CSR + 0x8)

#define USB_SDS_CSR_USB_PIPE_PCS_CTL0        (USB_SDS_CSR + 0xc)
#define USB_SDS_CSR_USB_PIPE_PCS_pd_rdy_i    (BIT31)

#define USB_SDS_CSR_USB_PIPE_PCS_CTL1        (USB_SDS_CSR + 0x10)
#define USB_SDS_CSR_USB_PIPE_PCS_RCV_DET_CTL (USB_SDS_CSR + 0x14)
#define USB_SDS_CSR_USB_SDS_CTL0             (USB_SDS_CSR + 0x18)

#define USB_SERDES_TOTAL_CH    1
#define USB_SERDES_CH_NUM    0

typedef union usb_sds_ctl0 {
  u32 val;
  struct {
    u32 cfg_i_customer_pin_mode : 15;
    u32 cfg_i_force_vcocal_start : 1;
    u32 cfg_i_usr_clk_buf_ena : 1;
    u32 cfg_i_refclk_cmos_sel : 1;
    u32 cfg_i_usr_pd_pll : 1;
    u32 cfg_i_rx_ctle_lpbck : 1;
    u32 cfg_i_rx_spare : 4;
    u32 cfg_i_tx_ser_lpbk : 1;
    u32 cfg_i_tx_rxlpbk_en : 1;
    u32 cfg_i_tx_spare : 3;
    u32 reserved : 3;
  } field;
} usb_sds_ctl0_r;

typedef union usb_gusb3pipectl {
  u32 val;
  struct {
    u32 ElasticBufferMode : 1;
#define TxDemphasis_Minus6_0dB    0
#define TxDemphasis_Minus3_5dB    1
#define TxDemphasis_NoDeemphasis  2
    u32 TxDeemphasis : 2;
    u32 TxMargin : 3;
    u32 TxSwing : 1;
    u32 reserved : 1;
    u32 RX_DETECT_to_Polling_LFPS : 1;
    u32 LFPSFilt : 1;
    u32 P3ExSigP2 : 1;
    u32 P3P2TranOK : 1;
    u32 LFPSP0Algn : 1;
    u32 SkipRxDet : 1;
    u32 AbortRxDetInU2 : 1;
#define PIPE_DATWIDTH_32    0
#define PIPE_DATWIDTH_16    1
#define PIPE_DATWIDTH_8      2
    u32 DatWidth : 2;
    u32 Suspend_en : 1;
    u32 DELAYP1TRANS : 1;
    u32 DelayP1P2P3 : 3;
    u32 DisRxDetU3RxDet : 1;
    u32 StartRxdetU3RxDet : 1;
    u32 request_p1p2p3 : 1;
    u32 u1u2exitfail_to_recov : 1;
    u32 ping_enhancement_en : 1;
    u32 Ux_exit_in_Px : 1;
    u32 DisRxDetP3 : 1;
    u32 u2SSInactP3ok : 1;
    u32 HstPrtCmpl : 1;
    u32 PHYSoftRst : 1;
  } field;
} usb_gusb3pipectl_r;

typedef union usb_gusb2phycfg {
  u32 val;
  struct {
    u32 TOutCal : 3;
    u32 PHYIf : 1;
    u32 ULPI_UTMI_Sel : 1;
    u32 FSIntf : 1;
    u32 SusPHY : 1;
    u32 PHYSel : 1;
    u32 EnblSlpM : 1;
    u32 reserved3 : 1;
    u32 USBTrdTim : 4;
    u32 reserved2 : 1;
    u32 ULPIAutoRes : 1;
    u32 reserved1 : 1;
    u32 ULPIExtVbusDrv : 1;
    u32 ULPIExtVbusIndicator : 1;
    u32 reserved : 12;
    u32 PHYSoftRst : 1;
  } field;
} usb_gusb2phycfg_r;

typedef union usb_gctl {
  u32 val;
  struct {
    u32 DsblClkGtng : 1;
    u32 GblHibernationEn : 1;
    u32 U2EXIT_LFPS : 1;
    u32 DisScramble : 1;
    u32 ScaleDown : 2;
    u32 RAMClkSel : 2;
    u32 DebugAttach : 1;
    u32 U1U2TimerScale : 1;
    u32 SOFITPSYNC : 1;
    u32 CoreSoftReset : 1;
    u32 PrtCapDir : 2;
    u32 FRMSCLDWN : 2;
    u32 U2RSTECN : 1;
    u32 reserved : 1;
    u32 MASTERFILTBYPASS : 1;
    u32 PwrDnScale : 13;
  } field;
} usb_gctl_r;

#define USB_SDS_CSR_USB_SDS_MISC_CTL       (USB_SDS_CSR + 0x1c)
#define USB_SDS_CSR_USB_SDS_CMU_STATUS0    (USB_SDS_CSR + 0x20)
#define USB_SDS_CSR_USB_SDS_DEBUG_REG      (USB_SDS_CSR + 0x24)
#define USB_SDS_CSR_USB_PIPE_DEBUG_REG     (USB_SDS_CSR + 0x28)
#define USB_SDS_CSR_USB_SDS_IND_CMD_REG    (USB_SDS_CSR + 0x2c)
#define USB_SDS_CSR_USB_SDS_IND_RDATA_REG  (USB_SDS_CSR + 0x50)
#define USB_SDS_CSR_USB_SDS_IND_WDATA_REG  (USB_SDS_CSR + 0x54)
#define USB_SDS_CSR_USB_OTG_CTL            (USB_SDS_CSR + 0x58)
#define USB_SDS_CSR_port_reset             (BIT8)

typedef union usb_otg_ctl {
  u32 val;
  struct {
    u32 commonon : 1;
#define USB_SDS_CSR_refclksel_pll_core  0x3
#define USB_SDS_CSR_refclksel_int    0x2
#define USB_SDS_CSR_refclksel_ext1_8V  0x1
#define USB_SDS_CSR_refclksel_ext_crys  0x0
    u32 refclksel : 2;
#define USB_SDS_CSR_refclkdiv_19_2MHz  0b11
#define USB_SDS_CSR_refclkdiv_48MHz    0b10
#define USB_SDS_CSR_refclkdiv_24MHz    0b01
#define USB_SDS_CSR_refclkdiv_12MHz    0b00
    u32 refclkdiv : 2;
    u32 reserved : 3;
    u32 port_reset : 1;
    u32 loopback_enable : 1;
    u32 siddq : 1;
    u32 vate_test_enable : 1;
    u32 test_dataout_sel : 1;
    u32 test_address : 4;
    u32 test_data_in : 8;
    u32 ate_reset : 1;
    u32 hbist_enable : 1;
    u32 fbist_enable : 1;
    u32 lbist_enable : 1;
    u32 bist_enable : 1;
    u32 reserved1 : 2;
  } field;
} usb_otg_ctl_r;

#define USB_SDS_CSR_USB_OTG_OVER      (USB_SDS_CSR + 0x5c)
typedef union usb_otg_over {
  u32 val;
  struct {
    u32 bias_tune : 1;
    u32 compdis_tune : 3;
    u32 pll_tune : 1;
    u32 sqrx_tune : 3;
    u32 txfsls_tune : 4;
    u32 txpreemphsis_tune : 2;
    u32 txrise_tune : 1;
    u32 txvref_tune : 4;
    u32 txhsx_tune : 2;
    u32 vreg_tune : 1;
    u32 reserved : 10;
  } field;
} usb_otg_over_r;
#define USB_SDS_CSR_USB_OTG_STAT      (USB_SDS_CSR + 0x60)
#define USB_SDS_CSR_OTG_DEFAULT        (USB_SDS_CSR + 0x64)


/*
 * Clock & Reset Register
 */
#define USB_CLKRST_CSR                   0xc000
#define USB_CLKRST_CSR_USBClkEnReg       (USB_CLKRST_CSR + 0x0)
#define USB_CLKRST_CSR_clk_utmi_clken    (BIT3)
#define USB_CLKRST_CSR_clk_pipe_clken    (BIT2)
#define USB_CLKRST_CSR_clk_usb_clken     (BIT1)
#define USB_CLKRST_CSR_csr_clken         (BIT0)

#define USB_CLKRST_CSR_USBSResetReg      (USB_CLKRST_CSR + 0x8)
#define USB_CLKRST_CSR_utmi_clk_reset    (BIT6)
#define USB_CLKRST_CSR_pipe_clk_reset    (BIT5)
#define USB_CLKRST_CSR_sds_reset         (BIT4)
#define USB_CLKRST_CSR_vaux_reset        (BIT3)
#define USB_CLKRST_CSR_vcc_reset         (BIT2)
#define USB_CLKRST_CSR_axi_core_reset    (BIT1)
#define USB_CLKRST_CSR_csr_reset         (BIT0)


#define USB_GUSB3PIPECTL_PHYSoftRst      BIT31
#define USB_GUSB3PIPECTL_ReqP1P2P3       BIT24
#define USB_GUSB3PIPECTL_StrRxDetU3      BIT23
#define USB_GUSB3PIPECTL_DisRxDetU3      BIT22
#define USB_GUSB3PIPECTL_DlyPhyPwrChg    BIT18
#define USB_GUSB3PIPECTL_SusUSB3Phy      BIT17
#define USB_GUSB3PIPECTL_DATWIDTH_SHL    15
#define USB_GUSB3PIPECTL_DATWIDTH_MSK    (BIT15 | BIT16)
#define USB_GUSB3PIPECTL_DATWIDTH_32     0
#define USB_GUSB3PIPECTL_DATWIDTH_16     BIT15
#define USB_GUSB3PIPECTL_DATWIDTH_8      BIT16
#define USB_GUSB3PIPECTL_TxSwing         BIT6
#define USB_GUSB3PIPECTL_TxMargin_SHL    3
#define USB_GUSB3PIPECTL_TxMargin_MSK    (BIT5 | BIT4 | BIT3)
#define USB_GUSB2PHYCFG_PHYSoftRst       BIT31
#define USB_GUSB2PHYCFG_USBTrdTim_MSK    (BIT13 | BIT12  BIT11 | BIT10)
#define USB_GUSB2PHYCFG_USBTrdTim_SHF    10
#define USB_GUSB2PHYCFG_SusPHY           BIT6

//<----- apm88xxxx_defines.h


/* Trace debug */
#define SM_DBGTRC_CLKRST_CSR        0xc000 // 0x1f2e0000 TRACE + PCS_Serdes
#define DBGTRCClkEnReg              0
#define DBGTRCResetReg              8
#define DBGTRCClkMuxReg             c

#define SM_TRACE_SDS_CSR_REGS       0xa000
#define SM_TRACE_CLK_MACRO_REG      0x40

/* USB CSR registers define */
#define CSR_BIT(x)  (0x80000000 >> x)

/* PCS Register */
#define USB_CSR_PCSREG           (USB30_CSR_REGS0 + 0x70)
#define USB_CSR_PCSREG_TX_DEEMPH_3P5_MSK    0x0000003F
#define USB_CSR_PCSREG_TX_DEEMPH_3P5_SHR    26
#define USB_CSR_PCSREG_TX_DEEMPH_3P5_VAL(x) \
               ((x << (31 - USB_CSR_PCSREG_TX_DEEMPH_3P5_SHR)) & 0x0000003F)
/* Serdes register 0 - Clock and Reset */
#define USB_CSR_PHYREG0_CLOCK_RESET        (USB30_CSR_REGS0 + 0x80)
#define USB_CSR_PHY_PORTRESET0             (CSR_BIT(0))
#define USB_CSR_PHY_MPLL_MULTIPLIER_MSK    0x7F000000
#define USB_CSR_PHY_MPLL_MULTIPLIER_SHR    24
#define USB_CSR_PHY_MPLL_MULTIPLIER(x)     ((x << USB_CSR_PHY_MPLL_MULTIPLIER_SHR) & USB_CSR_PHY_MPLL_MULTIPLIER_MSK)
#define USB_CSR_PHY_FSEL_MSK               0x003F0000
#define USB_CSR_PHY_SSC_RANGE_MSK          0x000000C0
#define USB_CSR_PHY_SSC_RANGE(x)           ((x << 6) & USB_CSR_PHY_SSC_RANGE_MSK)
#define USB_CSR_PHY_SSC_EN                 0x00000020
#define USB_CSR_PHY_REF_USE_PAD            0x00000004
#define USB_CSR_PHY_REF_SSP_EN             0x00000002
#define USB_CSR_PHY_REF_CLKDIV2            0x00000001

#define USB30_CSR_REGS0 0x0
#define USB_CSR_PHYREG1_PARAMETER_CONTROL    (USB30_CSR_REGS0 + 0x84)
#define USB_CSR_PHYREG2_UTMI_CONTROL         (USB30_CSR_REGS0 + 0x88)
#define USB_CSR_PHYREG3_TEST_AND_SERIAL      (USB30_CSR_REGS0 + 0x8C)
#define USB_CSR_PHYREG4_CR_BUS0              (USB30_CSR_REGS0 + 0x90)
#define USB_CSR_PHYREG5_CR_BUS1              (USB30_CSR_REGS0 + 0x94)
#define USB_CSR_PHYREG6_BOUNDARY_SCAN        (USB30_CSR_REGS0 + 0x98)
#define USB_CSR_PLLREG_CLKDIV                (USB30_CSR_REGS0 + 0x9C)
#define USB_CSR_PHYCLOCKREADY                (USB30_CSR_REGS0 + 0xA0)
#define USB_CSR_WAKEONUSBCTLREG              (USB30_CSR_REGS0 + 0xC0)
#define USB_CSR_HBFMASTERMASKREGLOW          (USB30_CSR_REGS0 + 0xC4)
#define USB_CSR_HBFMASTERMASKREGHIGH         (USB30_CSR_REGS0 + 0xC8)
#define USB_CSR_HBFMASTERBASEADDRREGLOW      (USB30_CSR_REGS0 + 0xCC)
#define USB_CSR_HBFMASTERBASEADDRREGHIGH     (USB30_CSR_REGS0 + 0xD0)
#define USB_CSR_HBFMASTERDESTADDRREGLOW      (USB30_CSR_REGS0 + 0xD4)
#define USB_CSR_HBFMASTERDESTADDRREGHIGH     (USB30_CSR_REGS0 + 0xD8)

/* GLBL_DIAG_CSR */
#define GLBL_DIAG_CSR                       0xd000
#define USB_CSR_CFG_DIAG_SEL                (GLBL_DIAG_CSR + 0x0)
#define USB_CSR_CFG_READ_BW_LAT_ADDR_MASK   (GLBL_DIAG_CSR + 0x4)
#define USB_CSR_CFG_READ_BW_LAT_ADDR_PAT    (GLBL_DIAG_CSR + 0x8)
#define USB_CSR_CFG_WRITE_BW_LAT_ADDR_MASK  (GLBL_DIAG_CSR + 0xC)
#define USB_CSR_CFG_WRITE_BW_LAT_ADDR_PAT   (GLBL_DIAG_CSR + 0x10)
#define USB_CSR_CFG_DIAG_START_STOP         (GLBL_DIAG_CSR + 0x14)
#define USB_CSR_CFG_BW_MSTR_STOP_CNT        (GLBL_DIAG_CSR + 0x18)
#define USB_CSR_CFG_BW_SLV_STOP_CNT         (GLBL_DIAG_CSR + 0x1C)
#define USB_CSR_CFG_DBG_TRIG_CTRL           (GLBL_DIAG_CSR + 0x44)
#define USB_CSR_CFG_DBG_PAT_REG_0           (GLBL_DIAG_CSR + 0x48)
#define USB_CSR_CFG_DBG_PAT_MASK_REG_0      (GLBL_DIAG_CSR + 0x4C)
#define USB_CSR_CFG_DBG_PAT_REG_1           (GLBL_DIAG_CSR + 0x50)
#define USB_CSR_CFG_DBG_PAT_MASK_REG_1      (GLBL_DIAG_CSR + 0x54)
#define USB_CSR_CFG_SECC_INT_THRSH_REG      (GLBL_DIAG_CSR + 0x64)
#define USB_CSR_CFG_MEM_ECC_BYPASS          (GLBL_DIAG_CSR + 0x68)
#define USB_CSR_CFG_MEM_PWRDN_DIS           (GLBL_DIAG_CSR + 0x6C)
#define USB_CSR_CFG_MEM_RAM_SHUTDOWN        (GLBL_DIAG_CSR + 0x70)
#define USB_CSR_CFG_AXI_SLV_RD_TMO          (GLBL_DIAG_CSR + 0x78)
#define USB_CSR_CFG_AXI_SLV_WR_TMO          (GLBL_DIAG_CSR + 0x7C)
#define USB_CSR_CFG_AXI_SS_CSR_TMO          (GLBL_DIAG_CSR + 0x84)
#define USB_CSR_DBG_ECC_INT_OUT             (GLBL_DIAG_CSR + 0x5C)
#define USB_CSR_DBG_ECC_INT_OUTMask         (GLBL_DIAG_CSR + 0x60)
#define USB_CSR_STS_READ_LATENCY_OUTPUT     (GLBL_DIAG_CSR + 0x20)
#define USB_CSR_STS_AXI_MRD_BW_CLK_CNT      (GLBL_DIAG_CSR + 0x24)
#define USB_CSR_STS_AXI_MRD_BW_BYTE_CNT     (GLBL_DIAG_CSR + 0x28)
#define USB_CSR_STS_AXI_MWR_BW_CLK_CNT      (GLBL_DIAG_CSR + 0x2C)
#define USB_CSR_STS_AXI_MWR_BW_BYTE_CNT     (GLBL_DIAG_CSR + 0x30)
#define USB_CSR_STS_AXI_SRD_BW_CLK_CNT      (GLBL_DIAG_CSR + 0x34)
#define USB_CSR_STS_AXI_SRD_BW_BYTE_CNT     (GLBL_DIAG_CSR + 0x38)
#define USB_CSR_STS_AXI_SWR_BW_CLK_CNT      (GLBL_DIAG_CSR + 0x3C)
#define USB_CSR_STS_AXI_SWR_BW_BYTE_CNT     (GLBL_DIAG_CSR + 0x40)
#define USB_CSR_DBG_TRIG_OUT                (GLBL_DIAG_CSR + 0x58)
#define USB_CSR_BLOCK_MEM_RDY               (GLBL_DIAG_CSR + 0x74)
#define USB_CSR_STS_AXI_SLV_TMO             (GLBL_DIAG_CSR + 0x80)
#define USB_CSR_STS_READ_LATENCY_TOT_READ_REQS  (GLBL_DIAG_CSR + 0x8C)

/* USB_DSF_AMPP_CSR */
#define USB_DSF_AMPP_CSR                    0x8000
#define USB_CSR_AMPP_CTL                    (USB_DSF_AMPP_CSR + 0x0)
#define USB_CSR_AMPP_DOMAIN_ID              (USB_DSF_AMPP_CSR + 0x4)
#define USB_CSR_AMPP_DMT_SA_0               (USB_DSF_AMPP_CSR + 0x50)
#define USB_CSR_AMPP_DMT_EA_0               (USB_DSF_AMPP_CSR + 0x54)
#define USB_CSR_AMPP_DMT_RW_0               (USB_DSF_AMPP_CSR + 0x58)
#define USB_CSR_AMPP_DMT_SA_1               (USB_DSF_AMPP_CSR + 0x60)
#define USB_CSR_AMPP_DMT_EA_1               (USB_DSF_AMPP_CSR + 0x64)
#define USB_CSR_AMPP_DMT_RW_1               (USB_DSF_AMPP_CSR + 0x68)
#define USB_CSR_AMPP_INT                    (USB_DSF_AMPP_CSR + 0x18)
#define USB_CSR_AMPP_INTMASK                (USB_DSF_AMPP_CSR + 0x1C)
#define USB_CSR_AMPP_RD_VIO_LOG_0           (USB_DSF_AMPP_CSR + 0x8)
#define USB_CSR_AMPP_RD_VIO_LOG_1           (USB_DSF_AMPP_CSR + 0xC)
#define USB_CSR_AMPP_WR_VIO_LOG_0           (USB_DSF_AMPP_CSR + 0x10)
#define USB_CSR_AMPP_WR_VIO_LOG_1           (USB_DSF_AMPP_CSR + 0x14)

/* USB Fabric registers*/
/* Global register */
#define USB_GSBUSCFG0    0xC100
#define USB_GSBUSCFG1    0xC104
#define USB_GTXTHRCFG    0xC108
#define USB_GRXTHRCFG    0xC10C
#define USB_GCTL    0xC110
#define USB_GCTL_U2RSTECN              BIT16
#define USB_GCTL_FRMSCLDWN_SHL         14
#define USB_GCTL_FRMSCLDWN_MSK         (BIT15 | BIT14)
#define USB_GCTL_FRMSCLDWN(x)          \
                      ((x << USB_GCTL_FRMSCLDWN_SHL) & USB_GCTL_FRMSCLDWN_MSK)
#define USB_GCTL_CoreSoftRst           BIT11
#define USB_GCTL_PortCapDir_Host       BIT12  //0x01
#define USB_GCTL_PortCapDir_Device     BIT13  //0x10
#define USB_GCTL_PortCapDir_OTG        (BIT12 | BIT13)  //0x11
#define USB_GCTL_PwrDnScale_SHF        19
#define USB_GCTL_PwrDnScale_MSK        (0xFFF80000)
#define USB_GCTL_RAMClkSel_SHL         6
#define USB_GCTL_RAMClkSel_MSK         (BIT7 | BIT6)
#define USB_GCTL_RAMClkSel_BusClk      0
#define USB_GCTL_RAMClkSel_PipeClk     (BIT6)
#define USB_GCTL_RAMClkSel_PipeDiv2Clk (BIT7)
#define USB_GCTL_ScaleDownMode_SHL     4
#define USB_GCTL_ScaleDownMode_MSK     (BIT5 | BIT4)
#define USB_GCTL_ScaleDownMode(x)      \
              ((x << USB_GCTL_ScaleDownMode_SHL) & USB_GCTL_ScaleDownMode_MSK)
#define USB_GCTL_DisScramble           BIT3
#define USB_GCTL_SSPwrClmp             BIT2
#define USB_GEVTEN                     0xC114
#define USB_GSTS                       0xC118
#define USB_GSNPSID                    0xC120
#define USB_GGPIO                      0xC124
#define USB_GUID                       0xC128
#define USB_GUCTL                      0xC12C
#define USB_GBUSERRADDRLO              0xC130
#define USB_GBUSERRADDRHI              0xC134
#define USB_GPRTBIMAPLO                0xC138
#define USB_GPRTBIMAPHI                0xC13C
#define USB_GHWPARAMS0                 0xC140
#define USB_GHWPARAMS1                 0xC144
#define USB_GHWPARAMS2                 0xC148
#define USB_GHWPARAMS3                 0xC14C
#define USB_GHWPARAMS4                 0xC150
#define USB_GHWPARAMS5                 0xC154
#define USB_GHWPARAMS6                 0xC158
#define USB_GHWPARAMS7                 0xC15C
#define USB_GDBGFIFOSPACE              0xC160
#define USB_GDBGLTSSM                  0xC164
#define USB_GDBGLNMCC                  0xC168
#define USB_GDBGBMU                    0xC16C
#define USB_GDBGLSPMUX                 0xC170
#define USB_GDBGLSP                    0xC174
#define USB_GDBGEPINFO0                0xC178
#define USB_GDBGEPINFO1                0xC17C
#define USB_GPRTBIMAP_HSLO             0xC180
#define USB_GPRTBIMAP_HSHI             0xC184
#define USB_GPRTBIMAP_FSLO             0xC188
#define USB_GPRTBIMAP_FSHI             0xC18C
#define USB_GUSB2PHYCFG(x)             (0xC200 + 4*x)
#define USB_GUSB2PHYCFG_PHYSoftRst     BIT31
#define USB_GUSB2PHYCFG_USBTrdTim_MSK  (BIT13 | BIT12  BIT11 | BIT10)
#define USB_GUSB2PHYCFG_USBTrdTim_SHF  10
#define USB_GUSB2PHYCFG_SusPHY         BIT6
#define USB_GUSB2PHYCFG_PhyIf          BIT3

#define USB_GUSB2I2CCTL(x)             (0xC240 + 4*x)
#define USB_GUSB2PHYACC(x)             (0xC280 + 4*x)
#define USB_GUSB3PIPECTL(x)            (0xC2C0 + 4*x)
#define USB_GUSB3PIPECTL_PHYSoftRst    BIT31
#define USB_GUSB3PIPECTL_ReqP1P2P3     BIT24
#define USB_GUSB3PIPECTL_StrRxDetU3    BIT23
#define USB_GUSB3PIPECTL_DisRxDetU3    BIT22
#define USB_GUSB3PIPECTL_DelayP1       BIT21
#define USB_GUSB3PIPECTL_DelayP2       BIT20
#define USB_GUSB3PIPECTL_DelayP3       BIT19
#define USB_GUSB3PIPECTL_DlyPhyPwrChg  BIT18
#define USB_GUSB3PIPECTL_SusUSB3Phy    BIT17
#define USB_GUSB3PIPECTL_DATWIDTH_SHL  15
#define USB_GUSB3PIPECTL_DATWIDTH_MSK  (BIT15 | BIT16)
#define USB_GUSB3PIPECTL_DATWIDTH_32   0
#define USB_GUSB3PIPECTL_DATWIDTH_16   BIT15
#define USB_GUSB3PIPECTL_DATWIDTH_8    BIT16
#define USB_GUSB3PIPECTL_SkipRxDet     BIT13
#define USB_GUSB3PIPECTL_LFPSP0Algn    BIT12
#define USB_GUSB3PIPECTL_P3P2TranOK    BIT11
#define USB_GUSB3PIPECTL_TxSwing       BIT6
#define USB_GUSB3PIPECTL_TxMargin_SHL  3
#define USB_GUSB3PIPECTL_TxMargin_MSK  (BIT5 | BIT4 | BIT3)
#define USB_GUSB3PIPECTL_TxMargin(x)   ((x << USB_GUSB3PIPECTL_TxMargin_SHL) & USB_GUSB3PIPECTL_TxMargin_MSK)
/* val 0 = Normal operation */
/* val 1 = 800-1200mV for Full swing OR 400-700 for Half swing */
/* val 2 = required, vendor defined */
/* val 3 = required, vendor defined */
/* val 4 = required, 200-400mV for Full swing OR 100-200mV for Half swing */
/* val 5 = optional, 200-400mV for Full swing OR 100-200mV for Half swing */
#define USB_GUSB3PIPECTL_TxDemphasis_SHL  1
#define USB_GUSB3PIPECTL_TxDemphasis_MSK  (BIT2 | BIT1)
#define USB_GUSB3PIPECTL_TxDemphasis_NoDeemphasis  ((2 << USB_GUSB3PIPECTL_TxDemphasis_SHL) & USB_GUSB3PIPECTL_TxDemphasis_MSK)
#define USB_GUSB3PIPECTL_TxDemphasis_Minus6_0dB    ((0 << USB_GUSB3PIPECTL_TxDemphasis_SHL) & USB_GUSB3PIPECTL_TxDemphasis_MSK)
#define USB_GUSB3PIPECTL_TxDemphasis_Minus3_5dB    ((1 << USB_GUSB3PIPECTL_TxDemphasis_SHL) & USB_GUSB3PIPECTL_TxDemphasis_MSK)

#define USB_GTXFIFOSIZ    0xC300
#define USB_GRXFIFOSIZ    0xC380
#define USB_GEVNTADR_L    0xC400
#define USB_GEVNTADR_H    0xC404
#define USB_GEVNTSIZ      0xC408
#define USB_GEVNTCOUNT    0xC40C
#define USB_GHWPARAMS8    0xC600

#define INT_SLV_TMOMask     0xE010
#define CFG_AMA_MODE        0xE014
/*eXtensible Host Controller Capability Registers*/
#define USB_CAPLENGTH     0x0
#define USB_HCSPARAMS1    0x4
#define USB_HCSPARAMS2    0x8
#define USB_HCSPARAMS3    0xC
#define USB_HCCPARAMS     0x10
#define USB_DBOFF         0x14
#define USB_RTSOFF        0x18

/*Host Controller Operational Registers*/
#define USB_CAPLENGTH_BASE    0x20
#define USB_HOST_CTRL_OPERATION_BASE  USB_CAPLENGTH_BASE
#define USB_USBCMD            (USB_HOST_CTRL_OPERATION_BASE + 0x0)
#define USB_USBSTS            (USB_HOST_CTRL_OPERATION_BASE + 0x4)
#define USB_PAGESIZE          (USB_HOST_CTRL_OPERATION_BASE + 0x8)
#define USB_DNCTRL            (USB_HOST_CTRL_OPERATION_BASE + 0x14)
#define USB_CRCR_LO           (USB_HOST_CTRL_OPERATION_BASE + 0x18)
#define USB_CRCR_HI           (USB_HOST_CTRL_OPERATION_BASE + 0x1C)
#define USB_DCBAAP_LO         (USB_HOST_CTRL_OPERATION_BASE + 0x30)
#define USB_DCBAAP_HI         (USB_HOST_CTRL_OPERATION_BASE + 0x34)
#define USB_CONFIG            (USB_HOST_CTRL_OPERATION_BASE + 0x38)

/*Host Controller Port Register Set*/
#define USB_HOST_CTRL_PORT_BASE (USB_CAPLENGTH_BASE + 0x400)
#define USB_PORTSC            (USB_HOST_CTRL_PORT_BASE + 0x0)
#define USB_PORTPMSC          (USB_HOST_CTRL_PORT_BASE + 0x4)
#define USB_PORTLI            (USB_HOST_CTRL_PORT_BASE + 0x8)

/*Host Controller Runtime Registers*/
#define USB_HOST_CTRL_RUNTIME_BASE    0x440
#define USB_MFINDEX           (USB_HOST_CTRL_RUNTIME_BASE + 0x0)

/*Interrupter Registers*/
#define USB_INT_BASE  0x460
#define USB_IMAN              (USB_INT_BASE + 0x0)
#define USB_IMOD              (USB_INT_BASE + 0x4)
#define USB_ERSTSZ            (USB_INT_BASE + 0x8)
#define USB_ERSTBA_LO         (USB_INT_BASE + 0x10)
#define USB_ERSTBA_HI         (USB_INT_BASE + 0x14)
#define USB_ERDP_LO           (USB_INT_BASE + 0x18)
#define USB_ERDP_HI           (USB_INT_BASE + 0x1C)

#define apmusb_info(args...)  \
    do { \
    DEBUG((EFI_D_INFO, "XGeneUsb: " fmt "\n", ## args)); \
    } while (0)

#define apmusb_err(fmt, args...)     \
    do { \
    DEBUG((EFI_D_ERROR, "XGeneUsb: " fmt "\n", ## args)); \
    } while (0)


#if 0
#define apmusb_dbg(fmt, args...)     \
    do { \
    DEBUG((EFI_D_INFO, "XGeneUsb: " fmt "\n", ## args)); \
    } while (0)
#else
#define apmusb_dbg(fmt, args...)
#endif

#define GLB_REG_OFF 0xC100

struct xhci_gctl_reg {
  UINT32 usc_cfg0;//00
  UINT32 usc_cfg1;//04
  UINT32 tx_thr_cfg;//08
  UINT32 rx_thr_cfg;//0c
  UINT32 gctl;//10
  UINT32 gevten;//14
  UINT32 gsts;//18
  UINT32 resv;//1c
  UINT32 gsnpsid;//20
  UINT32 ggpio;//24
  UINT32 guid;//28
  UINT32 guctl;
  UINT32 gbuserraddr0;
  UINT32 gbuserraddr1;
  UINT32 gprtbimap0;
  UINT32 gprtbimap1;//3c
  UINT32 ghwparm[8];//40
  UINT32 gdbgfifo;//60
  UINT32 gdbgltssm;
  UINT32 gdbgllnmcc;
  UINT32 gdbgbmu;
  UINT32 gdbglspmux;//70
  UINT32 gdbglsp;
  UINT32 gdbgepinfo0;
  UINT32 gdbgepinfo1;
  UINT32 gprtbimap_hs0;//80
  UINT32 gprtbimap_hs1;
  UINT64 gprtbimap_fs[15];
  UINT32 gusb2phycfg[16];
  UINT32 gusb2i2cctl[16];  // 0x200
  UINT32 gusb2phyacc[16];
  UINT32 gusb3pipeclt[16];
  UINT32 gtxfifosz[31];
};

UINT32 apm_usb_readl(VOID* addr);
VOID apm_usb_writel(VOID* addr, UINT32 val);
UINT32 usb_apm_wait_register(VOID* reg, UINT32 mask, UINT32 val,
                  INTN interval, UINT64 timeout);
VOID apm_usb_pipe_dump(VOID* csr_base);
VOID usb_regs_default_value_check(VOID* csr_base);

#endif /* __XGENE_USB_H__ */
