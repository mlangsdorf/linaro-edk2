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

#if !defined(__XGENEUSB_H__)
#define __XGENEUSB_H__

#include <Library/DebugLib.h>
#include <Library/TimerLib.h>
#include <Library/BaseLib.h>
#include <Library/MemoryAllocationLib.h>
#include <Library/IoLib.h>
#include "../../../Library/APMXGenePHYLib/phy-xgene.h"

#define USB30BID                       0x0000
#define HOSTPORTREG                    0x0030
#define POWERMNGTREG                   0x0038
#define  HOST_PORT_POWER_CONTROL_PRESENT (1 << 0)
#define  PORT_OVERCUR_ENABLE           (1 << 28)
#define  PORT_OVERCUR_INVERT           (1 << 29)
#define  PORT_POWER_DISABLE            (1 << 30)
#define HBFSIDEBANDREG                 0x003c
#define INTERRUPTSTATUSMASK            0x0064
#define PIPEUTMIREG                    0x0070
#define  CSR_PIPE_CLK_READY            (1 << 1)
#define  CSR_USE_UTMI_FOR_PIPE         (1 << 8)
#define  PIPE0_PHYSTATUS_OVERRIDE_EN   (1 << 30)
#define  PIPE0_PHYSTATUS_SYNC          (1 << 31)
#define USB_SDS_CMU_STATUS0            0xa020
#define USB_OTG_CTL                    0xa058
#define  USB_OTG_CTL_PORT_RESET_SET(dst, src) \
		(((dst) & ~0x00000100) | (((u32)(src) << 8) & 0x00000100))
#define  USB_OTG_CTL_REFCLKSEL_SET(dst, src) \
		(((dst) & ~0x00000006) | (((u32)(src) << 1) & 0x00000006))
#define  USB_OTG_CTL_REFCLKDIV_SET(dst, src) \
		(((dst) & ~0x00000018) | (((u32)(src) << 3) & 0x00000018))
#define USB_OTG_OVER                   0xa05c
#define USBCLKENREG                    0xc000
#define USBSRESETREG                   0xc008
#define GCTL                           0xc110
#define  GCTL_RAMCLKSEL_SET(dst, src) \
		(((dst) & ~0x000000C0) | (((u32)(src) << 6) & 0x000000C0))
#define  GCTL_CORESOFTRESET_SET(dst, src) \
		(((dst) & ~0x00000800) | (((u32)(src) << 11) & 0x00000800))
#define GSNPSID                        0xc120
#define GUSB2PHYCFG_0                  0xc200
#define  GUSB2PHYCFG_0_PHYSOFTRST_SET(dst, src) \
		(((dst) & ~0x80000000) | (((u32)(src) << 31) & 0x80000000))
#define  GUSB2PHYCFG_0_SUSPENDUSB20_SET(dst, src) \
		(((dst) & ~0x00000040) | (((u32)(src) << 6) & 0x00000040))
#define  GUSB2PHYCFG_0_PHYIF_SET(dst, src) \
		(((dst) & ~0x00000008) | (((u32)(src) << 3) & 0x00000008))
#define GUSB3PIPECTL_0                 0xc2c0
#define  GUSB3PIPECTL_0_PHYSOFTRST_SET(dst, src) \
		(((dst) & ~0x80000000) | (((u32)(src) << 31) & 0x80000000))
#define  GUSB3PIPECTL_0_HSTPRTCMPL_SET(dst, src) \
		(((dst) & ~0x40000000) | (((u32)(src) << 30) & 0x40000000))
#define  GUSB3PIPECTL_0_SUSPENDENABLE_SET(dst, src) \
		(((dst) & ~0x00020000) | (((u32)(src) << 17) & 0x00020000))
#define  GUSB3PIPECTL_0_DATWIDTH_SET(dst, src) \
		(((dst) & ~0x00018000) | (((u32)(src) << 15) & 0x00018000))
#define  GUSB3PIPECTL_0_RX_DETECT_TO_POLLING_LFPS_SET(dst, src) \
		(((dst) & ~0x00000100) | (((u32)(src) << 8) & 0x00000100))
#define CFG_MEM_RAM_SHUTDOWN           0xd070
#define BLOCK_MEM_RDY                  0xd074
#define INT_SLV_TMOMask                0xe010
#define CFG_AMA_MODE                   0xe014
#define  CFG_RD2WR_EN                  0x2
#define USBSTS                         0x0024
#define  USBSTS_CNR                    (1 << 11)
#define USB_SERDES_OFFSET              0xa000
#define USB_CLK_OFFSET                 0xc000


#define XGENE_DBG(fmt, args...) \
	DEBUG((EFI_D_INFO, "XGeneUsb: " fmt "\n", ## args))

#define XGENE_ERR(fmt, args...) \
	DEBUG((EFI_D_ERROR, "XGeneUsb: " fmt "\n", ## args))

#endif /* __XGENEUSB_H__ */
