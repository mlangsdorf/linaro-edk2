/*
 * APM X-Gene USB host controller driver
 *
 * Copyright (c) 2014, AppliedMicro Corp. All rights reserved.
 *
 * This program and the accompanying materials
 * are licensed and made available under the terms and conditions of the BSD
 * License which accompanies this distribution.  The full text of the license
 *  may be found at http://opensource.org/licenses/bsd-license.php
 *
 * THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
 * WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS
 * OR IMPLIED.
 *
 */
#include "XGeneUsb.h"

struct xgene_xhci_context {
	UINT8 Cid;			/* Controller ID */
	INTN  Irq;
	UINT32 Clk2Sel;
	UINT32 OvrcurEn;
	UINT32 OvrcurIvrt;
	VOID __iomem *CsrBase;		/* CSR base address of IP */
	VOID __iomem *MmioBase;	/* XHCI I/O base address */

	struct xgene_phy_ctx Phy;
};


/*
 * Wait until a register has a specific value or timeout.
 * Unit for interval and timeout parameters are micro-second
 */
UINT32
XGeneWaitRegister (
  VOID			*Reg,
  UINT32		Mask,
  UINT32		val,
  UINTN			Interval,
  UINT64		Timeout
  )
{
	INTN Deadline = 0;
	UINT32 Tmp;

	Tmp = MmioRead32 ((UINTN)Reg);
	while (((Tmp & Mask) != val) && (Deadline < Timeout)) {
		MicroSecondDelay(Interval);
		Tmp = MmioRead32 ((UINTN)Reg);
		Deadline += Interval;
	}

	return Tmp;
}

VOID
XGeneXhciEnable (
  struct xgene_xhci_context *Hpriv
  )
{
	VOID *CsrBase = Hpriv->CsrBase;

	/* Enable clock */
	MmioWrite32 ((UINTN)(CsrBase + USBCLKENREG), 0xF);

	/* Place blocks under reset */
	MmioWrite32 ((UINTN)(CsrBase + USBSRESETREG), 0x7F);

	/* Remove blocks under reset */
	MmioWrite32 ((UINTN)(CsrBase + USBSRESETREG), 0x0);
}

INTN
XGeneXhciInitMemblk (
  struct xgene_xhci_context *Hpriv
  )
{
	VOID *CsrBase = Hpriv->CsrBase;
	UINT32 Data;
	UINTN Try;

	/* Clear memory shutdown */
	Data = MmioRead32 ((UINTN)(CsrBase + CFG_MEM_RAM_SHUTDOWN));
	if (Data == 0) {
		XGENE_DBG("memory already released from shutdown\n");
		return 0;
	}

	/* USB controller memory in shutdown. Remove from shutdown. */
	XGENE_DBG("Release memory from shutdown\n");
	MmioWrite32 ((UINTN)(CsrBase + CFG_MEM_RAM_SHUTDOWN), 0);
	Data = MmioRead32 ((UINTN)(CsrBase + CFG_MEM_RAM_SHUTDOWN));

	/* Check for at least ~1ms */
	Try = 1000;
	do {
		Data = MmioRead32 ((UINTN)(CsrBase + BLOCK_MEM_RDY));
		if (Data != 0xFFFFFFFF)
			MicroSecondDelay(1);
	} while (Data != 0xFFFFFFFF && Try-- > 0);
	if (Try <= 0) {
		XGENE_ERR("failed to release memory from shutdown\n");
		return -1;
	}
	return 0;
}

UINTN XgeneXhciHwInit (
  struct xgene_xhci_context *Hpriv
  )
{
	VOID *CsrBase = Hpriv->CsrBase;
	VOID *fabric_base = Hpriv->MmioBase;
	UINT32 Data;
	INTN Ret = 0;

	XGENE_DBG("USB Initialization ...\n");

	/* Enable USB controller */
	XGeneXhciEnable(Hpriv);

	Data = MmioRead32 ((UINTN)(CsrBase + POWERMNGTREG));
	Data |= PORT_POWER_DISABLE;
	MmioWrite32 ((UINTN)(CsrBase + POWERMNGTREG), Data);

	/* Read BID and Global SynopsysID */
	Data = MmioRead32 ((UINTN)fabric_base + GSNPSID);
	XGENE_DBG("SynopsysID=%04x - RN=%04x\n", (u16) (Data >> 16), (u16) Data);

	/* Read/Write Coherency Override Enable */
	Data = MmioRead32 ((UINTN)(CsrBase + HBFSIDEBANDREG));
	Data |= 0xF;
	MmioWrite32 ((UINTN)(CsrBase + HBFSIDEBANDREG), Data);

	/* Initialize RAM shutdown */
	XGeneXhciInitMemblk(Hpriv);

	/* Tune eye pattern */
	MmioWrite32 ((UINTN)(CsrBase + USB_OTG_OVER), 0x001c0365);

	/* Reset Ref. clock select to default and enable port reset */
	Data = MmioRead32 ((UINTN)(CsrBase + USB_OTG_CTL));
	Data = USB_OTG_CTL_REFCLKSEL_SET(Data, 0);
	Data = USB_OTG_CTL_REFCLKDIV_SET(Data, 0);
	Data = USB_OTG_CTL_PORT_RESET_SET(Data, 1);
	Data |= (Hpriv->Clk2Sel << 1);
	MmioWrite32 ((UINTN)(CsrBase + USB_OTG_CTL), Data);
	XGENE_DBG("Clk2Sel=0x%x\n", Hpriv->Clk2Sel);

	/* Enable core interrupt */
	XGENE_DBG("Enable core interrupt\n");
	MmioWrite32 ((UINTN)(CsrBase + INTERRUPTSTATUSMASK), 0xFFFFFFF0);

	/* Enable AXI Interrupts */
	MmioWrite32 ((UINTN)(CsrBase + INT_SLV_TMOMask), 0x0);

	/* Control/Monitor status of PIPE or UTMI signals */
	Data = MmioRead32 ((UINTN)(CsrBase + PIPEUTMIREG));
	Data |= PIPE0_PHYSTATUS_OVERRIDE_EN;
	Data |= CSR_USE_UTMI_FOR_PIPE;
	MmioWrite32 ((UINTN)(CsrBase + PIPEUTMIREG), Data);

	/* Configure Power Management Register */
	Data = MmioRead32 ((UINTN)(CsrBase + POWERMNGTREG));
	if (Hpriv->OvrcurEn) {
		XGENE_DBG("Enable port over current\n");
		Data |= PORT_OVERCUR_ENABLE;
		if (Hpriv->OvrcurIvrt) {
			XGENE_DBG("Set port over current inverted\n");
			Data |= PORT_OVERCUR_INVERT;
		}
	}
	Data |= HOST_PORT_POWER_CONTROL_PRESENT;
	MmioWrite32 ((UINTN)(CsrBase + POWERMNGTREG), Data);

	Data = MmioRead32 ((UINTN)(CsrBase + HOSTPORTREG));
	Data |= 0x1;
	MmioWrite32 ((UINTN)(CsrBase + HOSTPORTREG), Data);

	/* PHY Controller Configuration */
	XGENE_DBG("Clear USB3 PHY soft reset\n");
	Data = MmioRead32 ((UINTN)fabric_base + GUSB3PIPECTL_0);
	Data = GUSB3PIPECTL_0_HSTPRTCMPL_SET(Data, 0);
	Data = GUSB3PIPECTL_0_SUSPENDENABLE_SET(Data, 0);
	Data = GUSB3PIPECTL_0_RX_DETECT_TO_POLLING_LFPS_SET(Data, 1);
	Data = GUSB3PIPECTL_0_DATWIDTH_SET(Data, 1);	/* 16 bit */
	Data = GUSB3PIPECTL_0_PHYSOFTRST_SET(Data, 0);
	MmioWrite32 ((UINTN)(fabric_base + GUSB3PIPECTL_0), Data);

	/* Clear USB2 PHY soft reset  */
	XGENE_DBG("Clear USB2 PHY soft reset\n");
	Data = MmioRead32 ((UINTN)fabric_base + GUSB2PHYCFG_0);
	Data = GUSB2PHYCFG_0_PHYSOFTRST_SET(Data, 0);
	Data = GUSB2PHYCFG_0_SUSPENDUSB20_SET(Data, 0);
	Data = GUSB2PHYCFG_0_PHYIF_SET(Data, 0);
	MmioWrite32 ((UINTN)(fabric_base + GUSB2PHYCFG_0), Data);

	/* Clear CORE soft reset */
	XGENE_DBG("Clear USB CORE reset\n");
	Data = MmioRead32 ((UINTN)fabric_base + GCTL);
	Data = GCTL_RAMCLKSEL_SET(Data, 0);
	Data = GCTL_CORESOFTRESET_SET(Data, 0);
	MmioWrite32 ((UINTN)(fabric_base + GCTL), Data);

	/* Clear OTG PHY reset */
	XGENE_DBG("Clear OTG PHY reset\n");
	Data = MmioRead32 ((UINTN)(CsrBase + USB_OTG_CTL));
	Data = USB_OTG_CTL_PORT_RESET_SET(Data, 0);
	MmioWrite32 ((UINTN)(CsrBase + USB_OTG_CTL), Data);

	Data = MmioRead32 ((UINTN)(CsrBase + POWERMNGTREG));
	Data &= ~PORT_POWER_DISABLE;
	MmioWrite32 ((UINTN)(CsrBase + POWERMNGTREG), Data);

	/*  Poll register CNR until its cleared */
	Data = XGeneWaitRegister(fabric_base + USBSTS,
				      USBSTS_CNR, 0x0, 100, 2000000);
	if (Data & USBSTS_CNR) {
		XGENE_ERR("Timeout waiting for USB controller ready\n");
		return -1;
	} else {
		XGENE_DBG("USB Controller is ready\n");
	}

	return Ret;
}

INTN XGeneXhciInit (
  UINT64			SerdesBase,
  UINT64			XhciBase,
  UINTN				Irq,
  UINTN				Cid,
  UINT32			Clk2Sel,
  UINT32			OvrcurEn,
  UINT32			OvrcurIvrt
  )
{
	struct xgene_xhci_context *Hpriv;
	INTN Ret;

	Hpriv = AllocateZeroPool(sizeof(struct xgene_xhci_context));
	if (!Hpriv) {
		XGENE_ERR("can't alloc host context\n");
		return -1;
	}
	Hpriv->CsrBase = (VOID *) SerdesBase;
	if (!Hpriv->CsrBase) {
		XGENE_ERR("can't map PHY CSR resource\n");
		Ret  = -1;
		goto error;
	}

	Hpriv->MmioBase = (VOID *) XhciBase;
	if (!Hpriv->MmioBase) {
		XGENE_ERR("can't map MMIO resource\n");
		Ret  = -1;
		goto error;
	}

	Hpriv->Cid = Cid;
	Hpriv->Irq = Irq;
	Hpriv->Clk2Sel = Clk2Sel;
	Hpriv->OvrcurEn = OvrcurEn;
	Hpriv->OvrcurIvrt = OvrcurIvrt;

	Hpriv->Phy.mode = MODE_USB;
	Hpriv->Phy.clk_type = CLK_EXT_DIFF;
	Hpriv->Phy.lane = 1;
	Hpriv->Phy.sds_base = Hpriv->CsrBase + USB_SERDES_OFFSET;
	Hpriv->Phy.clk_base = Hpriv->CsrBase + USB_CLK_OFFSET;
	Hpriv->Phy.core_base = Hpriv->CsrBase;
	Hpriv->Phy.inited = 0;
	Hpriv->Phy.ref_100MHz = 1;

	/* Configure the host controller */
	XgeneXhciHwInit(Hpriv);

	XGENE_DBG("USB%d PHY initialized\n", Cid);
	return 0;

error:
	FreePool(Hpriv);
	return Ret;
}
