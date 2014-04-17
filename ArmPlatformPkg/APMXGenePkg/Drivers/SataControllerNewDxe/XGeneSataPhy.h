/*
 * APM SATA Host/PHY driver
 *
 * Copyright (c) 2014, Applied Micro Circuits Corporation
 * Author: Loc Ho <lho@apm.com>
 *         Tuan Phan <tphan@apm.com>
 *         Suman Tripathi <stripathi@apm.com>
 *
 * This program and the accompanying materials
 *are licensed and made available under the terms and conditions of the BSD License
 * which accompanies this distribution.  The full text of the license may be found at
 * http://opensource.org/licenses/bsd-license.php
 *
 * THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
 * WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.
 */
#ifndef __XGENESATAPHY_H__
#define __XGENESATAPHY_H__

/* Porting wrapper */
typedef UINT32 u32;
typedef UINT64 u64;
typedef UINT8  u8;

#define readl(x)		*((volatile u32 *) (x))
#define writel(v, x)		*((volatile u32 *) (x)) = (v)
#define strcmp			AsciiStrCmp
#define ARRAY_SIZE(x)		sizeof(x)/sizeof(x[0])
#define __iomem
#define ENODEV			19
#define dev_dbg(arg...)		DEBUG((EFI_D_BLKIO,## arg))
#define dev_err(arg...)		DEBUG((EFI_D_ERROR,## arg))
#define pr_debug(arg...)	DEBUG((EFI_D_BLKIO,## arg))
#define usleep_range(x, y)	MicroSecondDelay((x))
#define preA3Chip		xgene_ahci_is_preA3()

/* Max 2 lanes per a PHY unit */
#define MAX_LANE		2

/* Clock macro type */
enum cmu_type_t {
	REF_CMU = 0,	/* Clock macro is the internal reference clock */
	PHY_CMU = 1,	/* Clock macro is the PLL for the Serdes */
	PHY2_CMU = 2,	/* Clock macro is the 2nd PLL for the Serdes */
};

enum mux_type_t {
	MUX_SELECT_ATA = 0,	/* Switch the MUX to ATA */
	MUX_SELECT_SGMMII = 0,	/* Switch the MUX to SGMII */
};

enum clk_type_t {
	CLK_EXT_DIFF = 0,	/* External differential */
	CLK_INT_DIFF = 1,	/* Internal differential */
	CLK_INT_SING = 2,	/* Internal single ended */
};

enum phy_mode {
	MODE_SATA	= 0,	/* List them for simple reference */
	MODE_SGMII	= 1,
	MODE_PCIE	= 2,
	MODE_USB	= 3,
	MODE_XFI	= 4,
	MODE_MAX
};

enum disk_type {
	DISK_SSD = 0,
	DISK_HDD = 1
};

struct xgene_sata_override_param {
	enum disk_type disk_type[MAX_LANE];
	u32 speed[MAX_LANE]; /* Index for override parameter per lane */
	u32 txspeed[3]; 		/* Tx speed */
	u32 txboostgain_ssd[MAX_LANE*3];/* Tx freq boost and gain control */
	u32 txboostgain[MAX_LANE*3];	/* Tx freq boost and gain control */
	u32 txeyetuning[MAX_LANE*3]; 	/* Tx eye tuning */
	u32 txeyedirection[MAX_LANE*3]; /* Tx eye tuning direction */
	u32 txamplitude[MAX_LANE*3];	/* Tx amplitude control */
	u32 txprecursor_cn1[MAX_LANE*3]; /* Tx emphasis taps 1st pre-cursor */
	u32 txprecursor_cn2[MAX_LANE*3]; /* Tx emphasis taps 2nd pre-cursor */
	u32 txpostcursor_cp1[MAX_LANE*3]; /* Tx emphasis taps post-cursor */
};

struct xgene_phy_ctx {
	enum phy_mode mode;		/* Mode of operation */
	enum clk_type_t clk_type;	/* Input clock selection */
	int lane;			/* # of lane used */
	void __iomem *sds_base;		/* PHY CSR base addr */
	void __iomem *clk_base;		/* PHY clock CSR base addr */
	void __iomem *core_base;	/* Core base if PCIE PHY */
	void __iomem *ext_cmu_base;	/* PHY SDS/Ref PLL CMU external */
	int ref_100MHz;			/* Reference clock 100Mhz */
	int inited;			/* Initialized? */

	/* Override Serdes parameters */
	struct xgene_sata_override_param sata_param;
};

struct xgene_ahci_context {
	u8 cid;				/* Controller ID */
	int irq;
	void __iomem *csr_base;		/* CSR base address of IP */
	void __iomem *mmio_base;	/* AHCI I/O base address */

	struct xgene_phy_ctx phy;
};

int xgene_phy_hw_init(struct xgene_phy_ctx *ctx);
int xgene_ahci_init(UINT64 serdes_base, UINT64 ahci_base, UINT64 pcie_clk_base,
		    int cid, int irq);
int xgene_ahci_is_preA3(void);

#endif /* __XGENESATAPHY_H__ */

