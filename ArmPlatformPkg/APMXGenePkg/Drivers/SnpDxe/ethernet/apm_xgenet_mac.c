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

/* apm_xg_init() pseudo code:
void apm_xg_init()
{
    apm_xg_cfg_mgnt_enet();
    apm_xg_clk_rst_cfg();
    apm_xg_serdes_init();
    apm_xg_mac_init();
    apm_xg_bypass_resume_cfg();
    apm_xg_loopback_cfg();
    apm_qm_cle_bypass_mode_cfg();
}
*/


// FIXME: replace register writes with the following
// 1. register_read( &data )
// 2. data = field_set( data, value )
// 3. repeat (2) for more fields
// 4. register_write(data)

#include "apm_enet_access.h"
#include "apm_xgenet_mac.h"
#include "apm_xgenet_csr.h"

/* TODO */
#define PHY_READ_COUNT 5

/* Compatity layer, define another function? */
/*    Address XGENET_SDS_CSR_REGS  Registers */
#define ENET_CFG_MEM_RAM_SHUTDOWN_ADDR REGSPEC_CFG_MEM_RAM_SHUTDOWN_ADDR
#define ENET_BLOCK_MEM_RDY_ADDR REGSPEC_BLOCK_MEM_RDY_ADDR
#define SATA_ENET_SDS_RST_CTL_ADDR XGENET_SDS_RST_CTL_ADDR
#define SATA_ENET_SDS_PCS_CTL2_ADDR XGENET_SDS_PCS_CTL2_ADDR
#define SATA_ENET_SDS_CTL0_ADDR XGENET_SDS_CTL0_ADDR
#define SATA_ENET_SDS_PCS_CTL0_ADDR XGENET_SDS_PCS_CTL0_ADDR
#define SATA_ENET_SDS_PCS_CTL1_ADDR XGENET_SDS_PCS_CTL1_ADDR
#define SATA_ENET_SDS_CTL1_ADDR XGENET_SDS_CTL1_ADDR
#define SATA_ENET_SDS_CMU_CTL0_ADDR XGENET_SDS_CMU_CTL0_ADDR
#define SATA_ENET_SDS_CMU_CTL1_ADDR XGENET_SDS_CMU_CTL1_ADDR
#define SATA_ENET_SDS_RX_CTL_ADDR XGENET_SDS_RX_CTL_ADDR
#define ENET_CFG_I_RX_WORDMODE0_WR REGSPEC_CFG_I_RX_WORDMODE0_WR
#define ENET_CFG_I_TX_WORDMODE0_WR REGSPEC_CFG_I_TX_WORDMODE0_WR

#define ENET_INTERFACE_MODE2_SET REGSPEC_INTERFACE_MODE2_SET /* same */
#define ENET_INTERFACE_MODE2_RD REGSPEC_INTERFACE_MODE2_RD /* same */
#define ENET_LHD_MODE_WR REGSPEC_LHD_MODE_WR /* same */
#define ENET_SRST_ADDR XGENET_SRST_ADDR
#define ENET_SRST_DEFAULT XGENET_SRST_DEFAULT	/* different */
#define ENET_CLKEN_ADDR XGENET_SRST_ADDR

#define ENET_GHD_MODE_WR REGSPEC_GHD_MODE_WR
#define ENET_CFG_I_CUSTOMER_PIN_MODE0_WR REGSPEC_CFG_I_CUSTOMER_PIN_MODE0_WR
#define ENET_CFG_CMU_I_PCIE_MODE1_WR REGSPEC_CFG_CMU_I_PCIE_MODE1_WR
#define ENET_INTERFACE_MODE2_WR REGSPEC_INTERFACE_MODE2_WR

#ifdef CONFIG_STORM_VHP
#define COUNT_FOR_TIMEOUT 5
#else
#define COUNT_FOR_TIMEOUT 10000
#endif

/* 10G only */
void apm_xgenet_set_phyid(struct apm_data_priv *priv)
{
	u32 val;

	apm_enet_read(priv, BLOCK_XGENET_MDIO_CSR, CFG_PHYID_ADDR, &val);
	val &= ~(0xFF << ((priv->port - AXGMAC) * 8));
	val |= (priv->phy_addr & 0xFF) << ((priv->port - 4) * 8);
	apm_enet_write(priv, BLOCK_XGENET_MDIO_CSR, CFG_PHYID_ADDR, val);
}

u32 apm_xgenet_get_mode(struct apm_data_priv *priv)
{
	u32 xgenet_csr_config_reg;

	apm_enet_read(priv, BLOCK_ETH_CLKRST_CSR, XGENET_CONFIG_REG_ADDR,
		&xgenet_csr_config_reg);

	if (CFG_SGMII_EN_RD(xgenet_csr_config_reg) == 0x2) /* xgmii mode */
		return PHY_MODE_XGMII;
	else
		return PHY_MODE_SGMII;
}

#if 1
/* MCXMAC */
void apm_xgmac_change_mtu(struct apm_data_priv *priv, u32 new_mtu)
{
	u32 data;

	if (priv->phy_mode == PHY_MODE_XGMII)
		return;
	/* Read current value of the Maximum Frame Length register */
	apm_enet_read(priv, BLOCK_MCX_MAC, MAX_FRAME_LEN_ADDR, &data);

	/* Write value back to Maximum Frame Length register */
	apm_enet_write(priv, BLOCK_MCX_MAC, MAX_FRAME_LEN_ADDR,
			MAX_FRAME_LEN_SET(data, new_mtu));
}

/* MCXMAC */
int apm_xgmac_is_rx_enable(struct apm_data_priv *priv)
{
	u32 data;

	if (priv->phy_mode == PHY_MODE_XGMII) {
		apm_enet_read(priv, BLOCK_AXG_MAC, AXGMAC_CONFIG_1_ADDR, &data);
		data = HSTTCTLEN1_RD(data) ? 1 : 0;
	} else {
		/* Read current value of the config 1 register */
		apm_enet_read(priv, BLOCK_MCX_MAC, MAC_CONFIG_1_ADDR, &data);
		data = RX_EN1_RD(data) ? 1 : 0;
	}

	return data;
}

/* MCXMAC  */
void apm_xgmac_rx_enable(struct apm_data_priv *priv)
{
	u32 data;

	if (priv->phy_mode == PHY_MODE_XGMII) {
		apm_enet_read(priv, BLOCK_AXG_MAC, AXGMAC_CONFIG_1_ADDR, &data);
		apm_enet_write(priv, BLOCK_AXG_MAC,
			AXGMAC_CONFIG_1_ADDR, HSTRFEN1_SET(data, 1));

		apm_enet_read(priv, BLOCK_AXG_MAC_CSR,
			XGENET_RX_DV_GATE_REG_0_ADDR, &data);
		data = TX_DV_GATE_EN0_SET(data, 0);
		data = RX_DV_GATE_EN0_SET(data, 0);
		apm_enet_write(priv, BLOCK_AXG_MAC_CSR,
			XGENET_RX_DV_GATE_REG_0_ADDR, data);
	} else {
		/* Read current value of the config 1 register */
		apm_enet_read(priv, BLOCK_MCX_MAC,
			MAC_CONFIG_1_ADDR, &data);

		/* Write value back to config 1 register */
		apm_enet_write(priv, BLOCK_MCX_MAC,
			MAC_CONFIG_1_ADDR, RX_EN1_SET(data, 1));
/*
		apm_enet_read(priv, BLOCK_MCX_MAC_CSR,
			RX_DV_GATE_REG_0_ADDR, &data);
		data = TX_DV_GATE_EN0_F2_SET(data, 0);
		data = RX_DV_GATE_EN0_F2_SET(data, 0);
		apm_enet_write(priv, BLOCK_MCX_MAC_CSR,
			RX_DV_GATE_REG_0_ADDR, data);
*/
	}
}

/* MCXMAC */
void apm_xgmac_rx_disable(struct apm_data_priv *priv)
{
	u32 data;

	if (priv->phy_mode == PHY_MODE_XGMII) {
		apm_enet_read(priv, BLOCK_AXG_MAC_CSR,
			XGENET_RX_DV_GATE_REG_0_ADDR, &data);
		data = TX_DV_GATE_EN0_SET(data, 1);
		data = RX_DV_GATE_EN0_SET(data, 1);
		apm_enet_write(priv, BLOCK_AXG_MAC_CSR,
			XGENET_RX_DV_GATE_REG_0_ADDR, data);

		apm_enet_read(priv, BLOCK_AXG_MAC, AXGMAC_CONFIG_1_ADDR, &data);
		apm_enet_write(priv, BLOCK_AXG_MAC,
			AXGMAC_CONFIG_1_ADDR, HSTRFEN1_SET(data, 0));
	} else {
/*
		apm_enet_read(priv, BLOCK_MCX_MAC_CSR,
			RX_DV_GATE_REG_0_ADDR, &data);
		data = TX_DV_GATE_EN0_F2_SET(data, 1);
		data = RX_DV_GATE_EN0_F2_SET(data, 1);
		apm_enet_write(priv, BLOCK_MCX_MAC_CSR,
			RX_DV_GATE_REG_0_ADDR, data);
*/
		/* Read current value of the config 1 register */
		apm_enet_read(priv, BLOCK_MCX_MAC, MAC_CONFIG_1_ADDR, &data);

		/* Write value back to config 1 register */
		apm_enet_write(priv, BLOCK_MCX_MAC,
			MAC_CONFIG_1_ADDR, RX_EN1_SET(data, 0));
	}
}

/* MCXMAC */
void apm_xgmac_tx_enable(struct apm_data_priv *priv)
{
	u32 data;

	if (priv->phy_mode == PHY_MODE_XGMII) {
		apm_enet_read(priv, BLOCK_AXG_MAC, AXGMAC_CONFIG_1_ADDR, &data);
		apm_enet_write(priv, BLOCK_AXG_MAC,
			AXGMAC_CONFIG_1_ADDR, HSTTFEN1_SET(data, 1));
	} else {
		/* Read current value of the config 1 register */
		apm_enet_read(priv, BLOCK_MCX_MAC, MAC_CONFIG_1_ADDR, &data);

		/* Write value back to config 1 register */
		apm_enet_write(priv, BLOCK_MCX_MAC,
			MAC_CONFIG_1_ADDR, TX_EN1_SET(data, 1));
	}
}

/* MCXMAC */
void apm_xgmac_tx_disable(struct apm_data_priv *priv)
{
	u32 data;

	if (priv->phy_mode == PHY_MODE_XGMII) {
		apm_enet_read(priv, BLOCK_AXG_MAC, AXGMAC_CONFIG_1_ADDR, &data);
		apm_enet_write(priv, BLOCK_AXG_MAC,
			AXGMAC_CONFIG_1_ADDR, HSTTFEN1_SET(data, 1));
	} else {
		/* Read current value of the config 1 register */
		apm_enet_read(priv, BLOCK_MCX_MAC, MAC_CONFIG_1_ADDR, &data);

		/* Write value back to config 1 register */
		apm_enet_write(priv, BLOCK_MCX_MAC,
			MAC_CONFIG_1_ADDR, TX_EN1_SET(data, 0));
	}
}

/* sgmii  */
int apm_xgmac_phy_autoneg_done(struct apm_data_priv *priv)
{
	u32 sts, sts1;

	if (priv->phy_mode == PHY_MODE_XGMII) {
		apm_enet_read(priv, BLOCK_ETH_CSR, LINK_STATUS_ADDR, &sts);
		apm_enet_read(priv, BLOCK_ETH_CSR, LINK_STS_INTR_ADDR, &sts1);
		if ((sts != 0) && (sts1 != 0))
			return 1;
		else
			return 0;
	}
read_sts_again:
	apm_genericmiiphy_read(priv, INT_PHY_ADDR,
		SGMII_STATUS_ADDR >> 2, &sts);
	apm_genericmiiphy_read(priv, INT_PHY_ADDR,
		SGMII_STATUS_ADDR >> 2, &sts1);
	if (sts != sts1)
		goto read_sts_again;
	return (sts & AUTO_NEGOTIATION_COMPLETE_MASK) ? 1 : 0;
}

/*sgmii */
int apm_xgenet_get_link_speed(struct apm_data_priv *priv)
{
	u32 data;
	u32 speed = priv->speed;

	if (priv->phy_mode == PHY_MODE_XGMII)
		return speed;

	if (speed == SPEED_10 || speed == SPEED_100)
		return speed;

	if (!priv->mac_to_mac) {
		apm_genericmiiphy_read(priv, INT_PHY_ADDR,
				SGMII_STATUS_ADDR >> 2, &data);
		if (LINK_STATUS_RD(data) == 0) {/* No link wih sgmii */
			apm_genericmiiphy_read(priv, priv->phy_addr,
					RTL_PHYSR_ADR, &data);
			PHY_PRINT("RTL_BMSR_ADR data: 0x%x\n", data);
			speed = RTL_PHYSR_SPEED_RD(data);
		} else {
			/* Get the final speed information from sgmii */
			apm_genericmiiphy_read(priv, INT_PHY_ADDR,
					SGMII_AN_SGMII_PARTNER_BASE_PAGE_ABILITY_ADDR >> 2, &data);
			PHY_PRINT("SGMII_AN_SGMII_PARTNER_BASE_PAGE_ABILITY_ADDR data: 0x%x\n", data);
			speed = LINK_SPEED_F1_RD(data);
		}
	} else {
		speed = priv->desired_speed;
	}
	PHY_PRINT("Phy Speed is :%d \n", speed);
	switch(speed) {
	case PHY_SPEED_10:
		return SPEED_10;

	case PHY_SPEED_100:
		return SPEED_100;
	default:
	return SPEED_1000;
	}
}

static int apm_xgmac_link_status(struct apm_data_priv *priv)
{
	u32 data, speed;

	if (!priv->mac_to_mac) {
		if (!priv->phyless) {
			apm_enet_read(priv, BLOCK_ETH_CSR, LINK_STATUS_ADDR, &data);
			priv->link_status = PORT_RD(data);
		} else
			priv->link_status = 1;
		if (!priv->link_status) {
			priv->speed = SPEED_10;
			PHY_PRINT("Port%d is down\n", priv->port);
			return 0;

		}
		/* Get the final speed information from SGMII */
		apm_genericmiiphy_read(priv, INT_PHY_ADDR,
				SGMII_AN_SGMII_PARTNER_BASE_PAGE_ABILITY_ADDR >> 2, &data);
		speed = LINK_SPEED_F1_RD(data);
		switch(speed) {
		case PHY_SPEED_10:
			speed = SPEED_10;
			break;
		case PHY_SPEED_100:
			speed = SPEED_100;
			break;
		default:
			speed = SPEED_1000;
			break;
		}
		if (priv->link_status)
			PHY_PRINT("Phy Speed is :%d \n", speed);
		else 
			PHY_PRINT("Port%d is down\n", priv->port);
		priv->speed = speed;
	} else {
		priv->link_status = 1;
		priv->speed = priv->desired_speed;
	}
	return 1;
}

/* sgmii */
void apm_xgmac_phy_link_mode(struct apm_data_priv *priv, u32 *speed, u32 *state)
{
#ifndef CONFIG_STORM_VHP
	u32 sts, sts_intr, ctl, anar, lpar, anlpar;
	u32 ganar = 0, glpar = 0;

	if (priv->phy_mode == PHY_MODE_XGMII) {
		apm_enet_read(priv, BLOCK_ETH_CSR, LINK_STATUS_ADDR, &sts);
		apm_enet_read(priv, BLOCK_ETH_CSR, LINK_STS_INTR_ADDR, &sts_intr);
		if ((sts != 0) && (sts_intr != 0)) {
			*state = 1;
			*speed = SPEED_10000;
		} else
			*speed = SPEED_0;
		return;
	}
	/* TODO change to INT_PHY_ADDR and SGMII reg */
	/* Link status is latched in PHY so read it twice */
	sts = 0x0;
	apm_genericmiiphy_read(priv, priv->phy_addr, MII_STAT_REG, &sts);
	apm_genericmiiphy_read(priv, priv->phy_addr, MII_STAT_REG, &sts);
	PHY_PRINT("MII_STAT_REG: 0x%x 0x%x\n", sts, (sts & MII_SR_LINK_STATUS));
	*state = (sts & MII_SR_LINK_STATUS) ? 1 : 0;

	/* If no link then return SPEED_0 */
	if (!(sts & MII_SR_LINK_STATUS)) {
		*speed = SPEED_0;
		return;
	}

	apm_genericmiiphy_read(priv, priv->phy_addr, MII_CTRL_REG, &ctl);
	PHY_PRINT("MII_CTRL_REG: 0x%x \n", ctl);
	apm_genericmiiphy_read(priv, priv->phy_addr, MII_AN_ADS_REG, &anar);
	PHY_PRINT("MII_AN_ADS_REG: 0x%x \n", anar);
	apm_genericmiiphy_read(priv, priv->phy_addr, MII_AN_PRTN_REG, &lpar);
	PHY_PRINT("MII_AN_PRTN_REG: 0x%x \n", lpar);
	if (sts & MII_SR_EXT_STS) {
		apm_genericmiiphy_read(priv, priv->phy_addr, MII_MASSLA_CTRL_REG, &ganar);
		PHY_PRINT("MII_MASSLA_CTRL_REG: 0x%x \n", ganar);
		apm_genericmiiphy_read(priv, priv->phy_addr, MII_MASSLA_STAT_REG, &glpar);
		PHY_PRINT("MII_MASSLA_STAT_REG: 0x%x \n", glpar);
	}

	/*
	 * If autoneg is on, figure out the link speed from the
	 * advertisement and partner ability registers. If autoneg is
	 * off, use the settings in the control register.
	 */
	*speed = SPEED_0;
	if (ctl & MII_CR_AUTO_EN) {
		anlpar = anar & lpar;
		if ((ganar & MII_MASSLA_CTRL_1000T_FD) &&
		    (glpar & MII_MASSLA_STAT_LP1000T_FD)) {
			*speed = SPEED_1000;
		} else if ((ganar & MII_MASSLA_CTRL_1000T_HD) &&
			   (glpar & MII_MASSLA_STAT_LP1000T_HD)) {
			*speed = SPEED_1000;
		} else if (anlpar & MII_ANAR_100TX_FD) {
			*speed = SPEED_100;
		} else if (anlpar & MII_ANAR_100TX_HD) {
			*speed = SPEED_100;
		} else if (anlpar & MII_ANAR_10TX_FD) {
			*speed = SPEED_10;
		} else if (anlpar & MII_ANAR_10TX_HD) {
			*speed = SPEED_10;
		}
	} else {
		if ((ctl & (MII_CR_100 | MII_CR_1000)) ==
					(MII_CR_100 | MII_CR_1000)) {
			*speed = SPEED_1000;
		} else if (ctl & MII_CR_100) {
			*speed = SPEED_100;
		} else {
			*speed = SPEED_10;
		}
	}
#else
	ENET_PRINT("VHP skip %s\n", __func__);
	*state = 1;
	*speed = SPEED_10000;
#endif
}


void sm_xgenet_mdio_auto_polling(struct apm_data_priv *priv)
{
	u32 xgenet_csr_config_reg, wrdata;

	apm_enet_read(priv, BLOCK_ETH_CLKRST_CSR, XGENET_CONFIG_REG_ADDR,
			&xgenet_csr_config_reg);
	if (xgenet_csr_config_reg == 0x2) {/* xgmii */
		if (priv->port == XGENET_0)
			wrdata = 0x20860000;
		else if (priv->port == XGENET_1)
			wrdata = 0x21060000;
		else if (priv->port == XGENET_2)
			wrdata = 0x21860000;
		else
			wrdata = 0x22060000;
		apm_enet_write(priv, BLOCK_XGENET_MDIO_CSR, MIIM_FIELD_ADDR, wrdata);
		apm_enet_write(priv, BLOCK_XGENET_MDIO_CSR, MIIM_COMMAND_ADDR, 12);

	} else {  /* This is going MENET TODO 0x17020000*/

	}
}

/* polling if the link came up */
int sm_xgenet_enet_linkup_polling(struct apm_data_priv *priv)
{
	u32 data, wrdata;
	u32 link_sts_intr_val, link_sts_val;
	u32 count_for_timeout;
	u32 xgenet_csr_config_reg;
	u32 autoneg_done = 0;

	PHY_PRINT("%s\n", __func__);
  	/* In the case of Force Link Status */
	apm_enet_read(priv, BLOCK_ETH_CSR, CFG_LINK_STS_ADDR, &data);

	if ((data & 0x00000010) == 0x00000010) {
		PHY_PRINT("LINK_UP Force Link Status\n");
		wrdata = data | 0x00000100;
		apm_enet_write(priv, BLOCK_ETH_CSR, CFG_LINK_STS_ADDR, wrdata);
	} else {
		apm_enet_read(priv, BLOCK_ETH_CLKRST_CSR, XGENET_CONFIG_REG_ADDR,
			&xgenet_csr_config_reg);
		if ((xgenet_csr_config_reg & CFG_SGMII_EN_MASK)
			== 0x00000002) {	/* xgmii */
		      /* For XGMII Mode utilize MDIO Clause 45 polling */
		      PHY_PRINT("LINK_UP XGMII --> Polling MDIO Clause 45\n");
		      sm_xgenet_mdio_auto_polling(priv);
		}
		else {	/* sgmii */
		      /* For sgmii In the case of Non AutoNeg --> Need to polling MDIO */
			apm_genericmiiphy_read(priv, INT_PHY_ADDR,
				SGMII_CONTROL_ADDR >> 2, &data);
		      if ((data & 0x00001000) == 0) {
			         PHY_PRINT("LINK_UP sgmii AutoNeg is disable --> Polling MDIO Clause 22\n");
			         sm_xgenet_mdio_auto_polling(priv);
		      }
		}
	}
	/* Polling the final link status until it is up */
	PHY_PRINT("LINK_UP Polling Link Status ...\n");
	apm_enet_read(priv, BLOCK_ETH_CSR, LINK_STATUS_ADDR, &link_sts_val);
	apm_enet_read(priv, BLOCK_ETH_CSR, LINK_STS_INTR_ADDR, &link_sts_intr_val);
	 /* poll for SGMII RX port is up or not, only if it is not up already */
	count_for_timeout = 0;
	while (((link_sts_val == 0x0) || (link_sts_intr_val == 0x0)) &&
		(count_for_timeout < COUNT_FOR_TIMEOUT)) {
		apm_enet_read(priv, BLOCK_ETH_CSR, LINK_STATUS_ADDR, &link_sts_val);
		apm_enet_read(priv, BLOCK_ETH_CSR, LINK_STS_INTR_ADDR, &link_sts_intr_val);
    		count_for_timeout++;
		udelay(1);
	}
	if (count_for_timeout >= COUNT_FOR_TIMEOUT) {
		autoneg_done = 0;
		PHY_PRINT("LINK_UP process failed: timeout_count: 10000\n");
	}
	else {
		PHY_PRINT("LINK_UP is up: at count: %d \n", count_for_timeout);
		autoneg_done = 1;
		/* Stop MDIO polling */
		if((xgenet_csr_config_reg & CFG_SGMII_EN_MASK) == 0x00000002) { /* xgmii */
			apm_enet_read(priv, BLOCK_ETH_CSR, CFG_LINK_STS_ADDR, &data);
        		if ((data & 0x00000010) != 0x00000010) { /* !force_en */
				apm_enet_write(priv, BLOCK_XGENET_MDIO_CSR, MIIM_COMMAND_ADDR, 0);
		        }
		} else { /* sgmii */
			apm_enet_read(priv, BLOCK_ETH_CSR, CFG_LINK_STS_ADDR, &data);
	        	if ((data & 0x00000010) != 0x00000010) { /* !force_en */
				apm_genericmiiphy_read(priv, INT_PHY_ADDR,
					SGMII_CONTROL_ADDR >> 2, &data);
        		    	if ((data & 0x00001000) == 0) {	/* !enable_en */
					/* TODO MENET 0x17020000 */
	               			//sm_xgenet_menet_macip_ind_csr_reg_wr_port0(0x00000024, 0x00000000);
	        		}
        		}
     		}

		apm_enet_read(priv, BLOCK_ETH_CSR, CFG_LINK_STS_ADDR, &data);
		if((data & 0x1) == 0x0) { /* link status from PCS state machine, NOT from MDIO auto scan */
        		/* write cfg_link_aggr_resume = 1 */
	        	PHY_PRINT("LINK_UP set cfg_link_aggr_resume = 1\n");
			apm_enet_write(priv, BLOCK_ETH_CSR, CFG_LINK_AGGR_RESUME_0_ADDR, 1);
		}
	}
	/* Clear link status change interrupt */
	apm_enet_read(priv, BLOCK_ETH_CSR, LINK_STS_INTR_ADDR, &link_sts_intr_val);
	if (link_sts_intr_val != 0)
		apm_enet_write(priv, BLOCK_ETH_CSR, LINK_STS_INTR_ADDR, link_sts_intr_val);

	return autoneg_done;
}

u32 enet_xgbaser_pcs_ind_csr_reg_rd(struct apm_data_priv *priv, u32 offset)
{
	u32 PCS_Ind_Command_Done, data;

	apm_enet_write(priv, BLOCK_XGENET_PCS, IND_ADDR_0_ADDR, offset);
 	apm_enet_write(priv, BLOCK_XGENET_PCS, IND_COMMAND_0_ADDR,
			REGSPEC_READ0_F8_WR(1));

	PCS_Ind_Command_Done = 0;
	while (PCS_Ind_Command_Done == 0) {
		apm_enet_read(priv, BLOCK_XGENET_PCS, IND_COMMAND_DONE_0_ADDR,
			&PCS_Ind_Command_Done);

	}
	apm_enet_read(priv, BLOCK_XGENET_PCS, IND_RDATA_0_ADDR, &data);
	apm_enet_write(priv, BLOCK_XGENET_PCS, IND_COMMAND_0_ADDR, 0x0);
	PHY_PRINT("%s read %x <- %x\n", __func__, data, offset);
	return data;
}

void enet_xgbaser_pcs_ind_csr_reg_wr(struct apm_data_priv *priv, u32 offset, u32 data)
{
	u32 PCS_Ind_Command_Done;

	apm_enet_write(priv, BLOCK_XGENET_PCS, IND_ADDR_0_ADDR, offset);
	apm_enet_write(priv, BLOCK_XGENET_PCS, IND_WDATA_0_ADDR, data);
	apm_enet_write(priv, BLOCK_XGENET_PCS, IND_COMMAND_0_ADDR,
			REGSPEC_WRITE0_F8_WR(1));

	PCS_Ind_Command_Done = 0;
	while (PCS_Ind_Command_Done == 0) {
		apm_enet_read(priv, BLOCK_XGENET_PCS, IND_COMMAND_DONE_0_ADDR,
			&PCS_Ind_Command_Done);
  	}
	PHY_PRINT("%s write %x -> %x\n", __func__, data, offset);
	apm_enet_write(priv, BLOCK_XGENET_PCS, IND_COMMAND_0_ADDR, 0);
}

void sm_xgenet_module_level_eee_init(struct apm_data_priv *priv)
{
	u32 xgenet_csr_config_reg;

	apm_enet_read(priv, BLOCK_ETH_CLKRST_CSR, XGENET_CONFIG_REG_ADDR,
		&xgenet_csr_config_reg);

	if (CFG_SGMII_EN_RD(xgenet_csr_config_reg) == 0x2) {/* xgmii mode */
		PHY_PRINT("Enable EEE capability...\n");
		enet_xgbaser_pcs_ind_csr_reg_wr(priv, PCS_EEE_CAPABILITY_ADDR,
			0x0000007f);
	} else {	/* SGMII mode */
		PHY_PRINT("Enable detect LPI...\n");
		apm_enet_write(priv, BLOCK_MCX_MAC_CSR, EEE_RX_LPI_DETECT_0_ADDR, 0x00000201);
		/* Config EEE RX Timer */
		apm_enet_write(priv, BLOCK_MCX_MAC_CSR, EEE_RX_TIMER0_0_ADDR, 0x00000100);
		apm_enet_write(priv, BLOCK_MCX_MAC_CSR, EEE_RX_TIMER1_0_ADDR, 0x00000100);
		apm_enet_write(priv, BLOCK_MCX_MAC_CSR, EEE_RX_TIMER2_0_ADDR, 0x00000100);
		PHY_PRINT("Clear LPI dectect interrupt mask...\n");
		apm_enet_write(priv, BLOCK_MCX_MAC_CSR, EEE_RX_LPI_DETECT_INTR_0MASK_ADDR, 0xfffffffe);
	}
}

void xgenet_config_qmi_assoc(struct apm_data_priv *priv)
{
        /* Configure Ethernet QMI: WQ and FPQ association, QM_SOC for now */
	switch(priv->port) {
		case XGENET_0:
		case XGENET_1:
			apm_enet_write(priv, BLOCK_ETH_QMI, REGSPEC_CFGSSQMIWQASSOC_ADDR, 0x0);
			apm_enet_write(priv, BLOCK_ETH_QMI, REGSPEC_CFGSSQMIFPQASSOC_ADDR, 0x0);
			apm_enet_write(priv, BLOCK_ETH_QMI, REGSPEC_CFGSSQMIQMLITEFPQASSOC_ADDR, 0x0);
			apm_enet_write(priv, BLOCK_ETH_QMI, REGSPEC_CFGSSQMIQMLITEWQASSOC_ADDR, 0x0);
			break;
		case XGENET_2:
		case XGENET_3:
			apm_enet_write(priv, BLOCK_ETH_QMI, REGSPEC_CFGSSQMIWQASSOC_ADDR, 0x0);
			apm_enet_write(priv, BLOCK_ETH_QMI, REGSPEC_CFGSSQMIFPQASSOC_ADDR, 0x0);
			apm_enet_write(priv, BLOCK_ETH_QMI, REGSPEC_CFGSSQMIQMLITEFPQASSOC_ADDR,
					0xffffffff);
			apm_enet_write(priv, BLOCK_ETH_QMI, REGSPEC_CFGSSQMIQMLITEWQASSOC_ADDR,
					0xffffffff);
			apm_enet_write(priv, BLOCK_ETH_QMI, REGSPEC_CFGSSQMIQMHOLD_ADDR,
					REGSPEC_QMLITE_HOLD_EN_WR(1));
			break;
		default:
			break;
	}
}

void xgenet_sds_ind_csr_reg_wr(struct apm_data_priv *priv, u32 offset, u32 data)
{
	u32 value, timeout;
        u32 SDS_Ind_Command_Addr;
	u32 SDS_Ind_Command_Done;

	/* write 1 to clear indirect error detected/ind cmd done */
        value = (CFG_IND_ADDR_WR(0)
                   | CFG_IND_ERR_WR(1)
                   | CFG_IND_CMD_DONE_WR(1)
                   | CFG_IND_RD_CMD_WR(0)
                   | CFG_IND_WR_CMD_WR(0));
	apm_enet_write(priv, BLOCK_ETH_SDS_CSR, XGENET_SDS_IND_CMD_REG_ADDR, value);
	//PHY_PRINT("%s cmd value=0x%x -> 0x%llx\n", __func__, value,
	//	XGENET_SDS_CSR_REGS_BASE_ADDR + XGENET_SDS_IND_CMD_REG_ADDR);

	value = data;
	apm_enet_write(priv, BLOCK_ETH_SDS_CSR, XGENET_SDS_IND_WDATA_REG_ADDR, value);
	//PHY_PRINT("%s data value=0x%x -> 0x%llx\n", __func__, value,
	//	XGENET_SDS_CSR_REGS_BASE_ADDR + XGENET_SDS_IND_WDATA_REG_ADDR);

	SDS_Ind_Command_Addr = offset; /* offset[15:0] */
        value = (CFG_IND_ADDR_WR(SDS_Ind_Command_Addr)
                   | CFG_IND_ERR_WR(0)
                   | CFG_IND_CMD_DONE_WR(0)
                   | CFG_IND_RD_CMD_WR(0)
                   | CFG_IND_WR_CMD_WR(1));
	apm_enet_write(priv, BLOCK_ETH_SDS_CSR, XGENET_SDS_IND_CMD_REG_ADDR, value);
	SDS_Ind_Command_Done = 0;
	while (SDS_Ind_Command_Done == 0) {
		apm_enet_read(priv, BLOCK_ETH_SDS_CSR, XGENET_SDS_IND_CMD_REG_ADDR, &value);
		//PHY_PRINT("%s cmd_done=0x%x <- 0x%llx\n", __func__, value,
		//	XGENET_SDS_CSR_REGS_BASE_ADDR + XGENET_SDS_IND_CMD_REG_ADDR);
		SDS_Ind_Command_Done = CFG_IND_CMD_DONE_RD(value);
	}

	for(timeout=0;timeout<1000;timeout++);
}

u32 xgenet_sds_ind_csr_reg_rd(struct apm_data_priv *priv, u32 offset)
{
	u32 value, timeout;
        u32 SDS_Ind_Command_Addr;
	u32 SDS_Ind_Command_Done;

	// FIXME:  CFG_IND_ADDR, CFG_IND_ERR and CFG_IND_CMD_DONE can be
	// set during write to CFG_IND_RD_CMD or CFG_IND_WR_CMD
	// CFG_IND_RD_CMD and CFG_IND_WR_CMD are self clear bits

	//PHY_PRINT("%s offset=0x%x\n", __func__, offset);
	/* write 1 to clear indirect error detected/ind cmd done */
        value = (CFG_IND_ADDR_WR(0)
                   | CFG_IND_ERR_WR(1)
                   | CFG_IND_CMD_DONE_WR(1)
                   | CFG_IND_RD_CMD_WR(0)
                   | CFG_IND_WR_CMD_WR(0));
	apm_enet_write(priv, BLOCK_ETH_SDS_CSR, XGENET_SDS_IND_CMD_REG_ADDR, value);
	//PHY_PRINT("%s value=0x%x -> 0x%llx\n", __func__, value,
	//	  XGENET_SDS_CSR_REGS_BASE_ADDR + XGENET_SDS_IND_CMD_REG_ADDR);

	SDS_Ind_Command_Addr = offset; /* offset[15:0] */
	value = (CFG_IND_ADDR_WR(SDS_Ind_Command_Addr)
                   | CFG_IND_ERR_WR(0)
                   | CFG_IND_CMD_DONE_WR(0)
                   | CFG_IND_RD_CMD_WR(1)
                   | CFG_IND_WR_CMD_WR(0));
	apm_enet_write(priv, BLOCK_ETH_SDS_CSR, XGENET_SDS_IND_CMD_REG_ADDR, value);
	//PHY_PRINT("%s cmd value=0x%x\n", __func__, value);

	SDS_Ind_Command_Done = 0;
	while (SDS_Ind_Command_Done == 0) {
		apm_enet_read(priv, BLOCK_ETH_SDS_CSR, XGENET_SDS_IND_CMD_REG_ADDR, &value);
		//PHY_PRINT("%s read cmd_done=0x%x <- 0x%llx\n", __func__, value,
		//	XGENET_SDS_CSR_REGS_BASE_ADDR + XGENET_SDS_IND_CMD_REG_ADDR);
		SDS_Ind_Command_Done = CFG_IND_CMD_DONE_RD(value);
	}

	apm_enet_read(priv, BLOCK_ETH_SDS_CSR, XGENET_SDS_IND_RDATA_REG_ADDR, &value);
	//PHY_PRINT("%s value=0x%x\n", __func__, value);
	for(timeout=0;timeout<1000;timeout++);

	return value;
}

/* Storm, Port0 for now, TODO */
#define CMU 0
static u32 sm_xgenet_set(u32 ori_val, u32 set_val, u32 end, u32 start)
{
	u32 mask = 0, new_val;
	int i;

	for (i = 0; i < 16; i++) {
		if ((i < start)||(i > end))
			mask = mask | (1 << i);
		else
			mask = mask | (0 << i);
	}
	new_val = (ori_val & mask) | (set_val << start);
	return new_val;
}

static void serdes_reset_rxd_rxa(struct apm_data_priv *priv, int port)
{
	u32 value;
	int timeout;
	int inst_base;

	inst_base = 0x0400;
	PHY_PRINT(" CH0 RX Reset Digital ...\n\r");
	value = xgenet_sds_ind_csr_reg_rd(priv, inst_base + 0x7*2);
	value = sm_xgenet_set(value, 0, 8, 8); // digital reset == 1'b0
	xgenet_sds_ind_csr_reg_wr(priv, inst_base + 0x7*2, value);

	inst_base = 0x0400;
	PHY_PRINT(" CH0 RX Reset Analog ...\n\r");
	value = xgenet_sds_ind_csr_reg_rd(priv, inst_base + 0x7*2);
	value = sm_xgenet_set(value, 0, 7, 7); // analog reset == 1'b0
	xgenet_sds_ind_csr_reg_wr(priv, inst_base + 0x7*2, value);

	for (timeout=0; timeout<0x8000; ++timeout);

	inst_base = 0x0400;
	PHY_PRINT(" CH0 RX Remove Reset Analog ...\n\r");
	value = xgenet_sds_ind_csr_reg_rd(priv, inst_base + 0x7*2);
	value = sm_xgenet_set(value, 1, 7, 7); // analog reset == 1'b1
	xgenet_sds_ind_csr_reg_wr(priv, inst_base + 0x7*2, value);

	for (timeout=0; timeout<0x8000; ++timeout);

	inst_base = 0x0400;
	PHY_PRINT(" CH0 RX Remove Reset Digital ...\n\r");
	value = xgenet_sds_ind_csr_reg_rd(priv, inst_base + 0x7*2);
	value = sm_xgenet_set(value, 1, 8, 8); // digital reset == 1'b1
	xgenet_sds_ind_csr_reg_wr(priv, inst_base + 0x7*2, value);
}

void serdes_reset_rxa(struct apm_data_priv *priv) {
	u32 value;
	int timeout;
	int inst_base;

	inst_base = 0x0400;
	PHY_PRINT(" CH0 RX Reset Analog ...\n\r");
	value = xgenet_sds_ind_csr_reg_rd(priv, inst_base + 0x7*2);
	value = sm_xgenet_set(value, 0, 7, 7); // analog reset == 1'b0
	xgenet_sds_ind_csr_reg_wr(priv, inst_base + 0x7*2, value);

	for(timeout=0; timeout<0x8000; ++timeout);

	inst_base = 0x0400;
	PHY_PRINT(" CH0 RX Remove Reset Analog ...\n\r");
	value =  xgenet_sds_ind_csr_reg_rd(priv, inst_base + 0x7*2);
	value = sm_xgenet_set(value, 1, 7, 7); // analog reset == 1'b1
	xgenet_sds_ind_csr_reg_wr(priv, inst_base + 0x7*2, value);
}
#define CMU 0
static void serdes_calib(struct apm_data_priv *priv)
{
	u32 value; 
	u32 inst_base;
	u32 infmode = 1;
 
	if (priv->phy_mode == PHY_MODE_SGMII) {
		infmode = 0;
		/* CMU_reg6  : Enable Manual PVT calibration - Anil */
		value = xgenet_sds_ind_csr_reg_rd(priv, CMU + 2*6);
		value = sm_xgenet_set(value,infmode ? 1 : 1, 2, 2);
		xgenet_sds_ind_csr_reg_wr(priv, CMU + 2*6, value);

		/* TERM CALIBRATION KC_SERDES_CMU_REGS_CMU_REG17__ADDR */
		value = xgenet_sds_ind_csr_reg_rd(priv, CMU + 2*17);
		value &= ~(0x7F << 8);
		value |= (0x0D << 8);
		value &= ~(7 << 5);
		xgenet_sds_ind_csr_reg_wr(priv, CMU + 2*17, value);
		value = xgenet_sds_ind_csr_reg_rd(priv, CMU + 2*17);

		value = xgenet_sds_ind_csr_reg_rd(priv, CMU + 2*17);
		value |= (1 << 15);
		xgenet_sds_ind_csr_reg_wr(priv, CMU + 2*17, value);
		value = xgenet_sds_ind_csr_reg_rd(priv, CMU + 2*17);
 
		value = xgenet_sds_ind_csr_reg_rd(priv, CMU + 2*17);
		value &= ~(1 << 15);
		xgenet_sds_ind_csr_reg_wr(priv, CMU + 2*17, value);
		value = xgenet_sds_ind_csr_reg_rd(priv, CMU + 2*17);

		/* DOWN CALIBRATION */
		value = xgenet_sds_ind_csr_reg_rd(priv, CMU + 2*17);
		value &= ~(0x7F << 8);
		value |= (0x2A << 8);
		value &= ~(7 << 5);
		xgenet_sds_ind_csr_reg_wr(priv, CMU + 2*17, value);
		value = xgenet_sds_ind_csr_reg_rd(priv, CMU + 2*17);

		value = xgenet_sds_ind_csr_reg_rd(priv, CMU + 2*16);
		value |= 1;
		xgenet_sds_ind_csr_reg_wr(priv, CMU + 2*16, value);
		value = xgenet_sds_ind_csr_reg_rd(priv, CMU + 2*16);

		value = xgenet_sds_ind_csr_reg_rd(priv, CMU + 2*16);
		value &= ~1;
		xgenet_sds_ind_csr_reg_wr(priv, CMU + 2*16, value);
		value = xgenet_sds_ind_csr_reg_rd(priv, CMU + 2*16);
 
		/* UP CALIBRATION */
		value = xgenet_sds_ind_csr_reg_rd(priv, CMU + 2*17);
		value &= ~(0x7F << 8);
		value |= (0x2B << 8);
		value &= ~(7 << 5);
		xgenet_sds_ind_csr_reg_wr(priv, CMU + 2*17, value);
		value = xgenet_sds_ind_csr_reg_rd(priv, CMU + 2*17);

		value = xgenet_sds_ind_csr_reg_rd(priv, CMU + 2*16);
		value |= (1 << 1);
		xgenet_sds_ind_csr_reg_wr(priv, CMU + 2*16, value);
		value = xgenet_sds_ind_csr_reg_rd(priv, CMU + 2*16);

		value = xgenet_sds_ind_csr_reg_rd(priv, CMU + 2*16);
		value &= ~(1 << 1);
		xgenet_sds_ind_csr_reg_wr(priv, CMU + 2*16, value);
		value = xgenet_sds_ind_csr_reg_rd(priv, CMU + 2*16);

		/*//////////////////////////////////////////////////////////// */
		/* Anil adding 5-2-2013 */
		/*// STARTED///// */
		/*  printf ("ANIL ADDING THIS CODE .....\n\r"); */
		inst_base = 0x0400;
		value = xgenet_sds_ind_csr_reg_rd(priv, inst_base + 14*2);
		value &= ~0x7F;  /* mask */
		value |= 0x0E; /*Anil 02/08/13 */
		xgenet_sds_ind_csr_reg_wr(priv,inst_base + 14*2, value);
		udelay(10);
	} else { /* XGMII */
		/* CMU_reg6  : Enable Manual PVT calibration - Anil */
		value = xgenet_sds_ind_csr_reg_rd(priv, CMU + 2*6);
		value = sm_xgenet_set(value,infmode ? 1: 1, 2, 2);
		xgenet_sds_ind_csr_reg_wr(priv, CMU + 2*6, value);

		/* TERM CALIBRATION KC_SERDES_CMU_REGS_CMU_REG17__ADDR */
		value = xgenet_sds_ind_csr_reg_rd(priv, CMU + 2*17);
		value &= ~(0x7F << 8);
		value |= 0x0D << 8;
		value &= ~(7 << 5);
		xgenet_sds_ind_csr_reg_wr(priv, CMU + 2*17, value);
		value = xgenet_sds_ind_csr_reg_rd(priv, CMU + 2*17);

		value = xgenet_sds_ind_csr_reg_rd(priv, CMU + 2*17);
		value |= 1 << 15;
		xgenet_sds_ind_csr_reg_wr(priv, CMU + 2*17, value);
		value = xgenet_sds_ind_csr_reg_rd(priv, CMU + 2*17);

		value = xgenet_sds_ind_csr_reg_rd(priv, CMU + 2*17);
		value &= ~(1 << 15);
		xgenet_sds_ind_csr_reg_wr(priv, CMU + 2*17, value);
		value = xgenet_sds_ind_csr_reg_rd(priv, CMU + 2*17);

		/* DOWN CALIBRATION */
		value = xgenet_sds_ind_csr_reg_rd(priv, CMU + 2*17);
		value &= ~(0x7F << 8);
		/*    value |= 0x26 << 8; */
		value |= 0x2A << 8; /* 07/31/2013 */
		value &= ~(7 << 5);
		xgenet_sds_ind_csr_reg_wr(priv, CMU + 2*17, value);
		value = xgenet_sds_ind_csr_reg_rd(priv, CMU + 2*17);

		value = xgenet_sds_ind_csr_reg_rd(priv, CMU + 2*16);
		value |= 1;
		xgenet_sds_ind_csr_reg_wr(priv, CMU + 2*16, value);
		value = xgenet_sds_ind_csr_reg_rd(priv, CMU + 2*16);

		value = xgenet_sds_ind_csr_reg_rd(priv, CMU + 2*16);
		value &= ~1;
		xgenet_sds_ind_csr_reg_wr(priv, CMU + 2*16, value);
		value = xgenet_sds_ind_csr_reg_rd(priv, CMU + 2*16);

		/* UP CALIBRATION */
		value = xgenet_sds_ind_csr_reg_rd(priv, CMU + 2*17);
		value &= ~(0x7F << 8);
		/*    value |= 0x28 << 8; */
		value |= 0x2B << 8; /* 07/31/2013 */
		value &= ~(7 << 5);
		xgenet_sds_ind_csr_reg_wr(priv, CMU + 2*17, value);
		value = xgenet_sds_ind_csr_reg_rd(priv, CMU + 2*17);

		value = xgenet_sds_ind_csr_reg_rd(priv, CMU + 2*16);
		value |= (1 << 1);
		xgenet_sds_ind_csr_reg_wr(priv, CMU + 2*16, value);
		value = xgenet_sds_ind_csr_reg_rd(priv, CMU + 2*16);

		value = xgenet_sds_ind_csr_reg_rd(priv, CMU + 2*16);
		value &= ~(1 << 1);
		xgenet_sds_ind_csr_reg_wr(priv, CMU + 2*16, value);
		value = xgenet_sds_ind_csr_reg_rd(priv, CMU + 2*16);

		/* Anil adding 5-2-2013 */
		/*// STARTED///// */
		/*  printf ("ANIL ADDING THIS CODE .....\n\r"); */
		inst_base = 0x0400;
		value = xgenet_sds_ind_csr_reg_rd(priv, inst_base + 14*2);
		value &= ~0x7F;  /* mask */
		value |= 0x0E; /*Anil 02/08/13 */
		xgenet_sds_ind_csr_reg_wr(priv, inst_base + 14*2, value);
		udelay(1);
	}
}

/* SERDES config
   the xgenet (that include enet module) will have both xfi (10G) and 1G mode running at LSPLL ONLY.
	infmode: 0: SGMII(1G), 1: XGMII(10G)
	NOTE: Storm_CLock_and_Reset_EAS.pdf
	Section 3.2.4 ETH_PLL clocks: ETH_CLK sources the Serdes reference clock for both Ethernet ports.
 	Configurations where one port is SGMII and the other is XFI are not supported.
*/
void sm_xgenet_module_program_all_regs(struct apm_data_priv *priv)
{
	u32 value, inst, inst_base;
	u32 infmode = 1; /* xgmii */

	/* xgenet_sds_CMU_cfg */
	if (priv->phy_mode == PHY_MODE_SGMII) {
		infmode = 0;
		value = xgenet_sds_ind_csr_reg_rd(priv, CMU + 2*12);
		/* data32 = FIELD_CMU_REG12_STATE_DELAY9_SET(data32, 0x1);  // Anil 0718 */
		value = sm_xgenet_set(value, 1, 7, 4);
		xgenet_sds_ind_csr_reg_rd(priv, CMU + 2*12);
		/*/////////// */
		/* CMU_reg13 */
		value = xgenet_sds_ind_csr_reg_rd(priv, CMU + 2*13);
		/* Delay time between state transition. */
		/* value = sm_xgenet_set(value,infmode ? 15 : 15, 15, 12); */
		value = sm_xgenet_set(value,infmode ? 15 : 15, 15, 12);
		/* Delay time between state transition. */
		/* value = sm_xgenet_set(value,infmode ? 15 : 15, 11, 8); */
		value = sm_xgenet_set(value,infmode ? 15 : 1, 11, 8);
		/* Delay time between state transition. */
		/* value = sm_xgenet_set(value,infmode ? 15 : 15, 7, 4); */
		value = sm_xgenet_set(value,infmode ? 15 : 2, 7, 4);
		/* Delay time between state transition. */
		/* value = sm_xgenet_set(value,infmode ? 15 : 15, 3, 0); */
		value = sm_xgenet_set(value,infmode ? 15 : 2, 3, 0);
		xgenet_sds_ind_csr_reg_wr(priv, CMU + 2*13, value);

		/*/////////// */
		/* CMU_reg14 */
		value = xgenet_sds_ind_csr_reg_rd(priv, CMU + 2*14);
		/* Delay time between state transition. */
		/* value = sm_xgenet_set(value,infmode ? 15 : 15, 15, 12); */
		value = sm_xgenet_set(value,infmode ? 15 : 2, 15, 12);
		/* Delay time between state transition. */
		/* value = sm_xgenet_set(value,infmode ? 15 : 15, 11, 8); */
		value = sm_xgenet_set(value,infmode ? 15 : 2, 11, 8);
		/* Delay time between state transition. */
		/* value = sm_xgenet_set(value,infmode ? 15 : 15, 7, 4); */
		value = sm_xgenet_set(value,infmode ? 15 : 1, 7, 4);
		/* Delay time between state transition. */
		/* value = sm_xgenet_set(value,infmode ? 15 : 15, 3, 0); */
		value = sm_xgenet_set(value,infmode ? 15 : 4, 3, 0);
		xgenet_sds_ind_csr_reg_wr(priv, CMU + 2*14, value);
		ENET_DEBUG("%s PHY_MODE_SGMII\n", __func__);
	}
	value =  xgenet_sds_ind_csr_reg_rd(priv, CMU + 2*1);
	value = sm_xgenet_set(value, 0, 0, 0);
	xgenet_sds_ind_csr_reg_wr(priv, CMU + 2*1, value);

	/* CMU_reg2 */
  	value =  xgenet_sds_ind_csr_reg_rd(priv, CMU + 2*2);
	/* Ref clk divider setting */
	value = sm_xgenet_set(value,infmode ? 0 : 0, 15, 14);
	/* Feedback divider setting */
	value = sm_xgenet_set(value,infmode ? 32 : 49, 13, 5);
	xgenet_sds_ind_csr_reg_wr(priv, CMU + 2*2, value);

	/* CMU_reg9 */
	value = xgenet_sds_ind_csr_reg_rd(priv, CMU + 2*9);
	/* Post Divider */
	value = sm_xgenet_set(value,infmode ? 0 : 1, 3, 3);
	/* Word mode for PClk */
	value = sm_xgenet_set(value,infmode ? 6 : 1, 6, 4);
	xgenet_sds_ind_csr_reg_wr(priv, CMU + 2*9, value);

	/* CMU_reg1 */
	value = xgenet_sds_ind_csr_reg_rd(priv, CMU + 2*1);
	/* PLL BW setting */
	value = sm_xgenet_set(value,infmode ? 11 : 10, 13, 10);
	/*  PLL BW setting */
	value = sm_xgenet_set(value,infmode ? 2 : 1, 9, 5);
	xgenet_sds_ind_csr_reg_wr(priv, CMU + 2*1, value);

	/* CMU_reg3 */
	value = xgenet_sds_ind_csr_reg_rd(priv, CMU + 2*3);
	value = sm_xgenet_set(value,infmode ? 0 : 0, 3, 0);
	xgenet_sds_ind_csr_reg_wr(priv, CMU + 2*3, value);

	/* CMU_reg2 */
	value = xgenet_sds_ind_csr_reg_rd(priv, CMU + 2*2);
	value = sm_xgenet_set(value,infmode ? 7 : 15, 4, 1);
	xgenet_sds_ind_csr_reg_wr(priv, CMU + 2*2, value);

	/* CMU_reg5 */
	value = xgenet_sds_ind_csr_reg_rd(priv, CMU + 2*5);
	value = sm_xgenet_set(value,infmode ? 0 : 3, 15, 14);
	value = sm_xgenet_set(value,infmode ? 0 : 3, 13, 12);
	value = sm_xgenet_set(value,infmode ? 4 : 7, 3, 1);
	/* pll_lock_resolution. Provided by Anil */
	xgenet_sds_ind_csr_reg_wr(priv, CMU + 2*5, value);

	/*  CMU_reg4 */
	/*
	value = xgenet_sds_ind_csr_reg_rd(priv, CMU + 2*4);
	value = sm_xgenet_set(value,infmode ? 0 : 0, 3, 0);
	xgenet_sds_ind_csr_reg_wr(priv, CMU + 2*4, value);
	*/

/*/////////// */
  // CMU_reg8
        value = xgenet_sds_ind_csr_reg_rd(priv, CMU + 2*8);
        value = sm_xgenet_set(value,infmode ? 7 : 7, 7, 5); // ucdiv. added by satish for correct usr clock - 01 Feb
	value = sm_xgenet_set(value, infmode ? 0: 0xAA, 15, 8); // tx_data_rate_ch3,2,1,0 = 2'h2
        xgenet_sds_ind_csr_reg_wr(priv, CMU + 2*8, value);

	/* CMU_reg6 */
	value = xgenet_sds_ind_csr_reg_rd(priv, CMU + 2*6);
	value = sm_xgenet_set(value,infmode ? 0 : 0, 10, 9);
	value = sm_xgenet_set(value,infmode ? 1 : 0, 3, 3);
	xgenet_sds_ind_csr_reg_wr(priv, CMU + 2*6, value);

	/* CMU_reg32 */
	value = xgenet_sds_ind_csr_reg_rd(priv, CMU + 2*32);
	/* Bias Current adj */
	value = sm_xgenet_set(value,infmode ? 3 : 3, 8, 7);
	xgenet_sds_ind_csr_reg_wr(priv, CMU + 2*32, value);

	/*  CMU_reg1 */
	value = xgenet_sds_ind_csr_reg_rd(priv, CMU + 2*1);
	/* Manual cal enable */
	value = sm_xgenet_set(value,infmode ? 0 : 0, 3, 3);
	xgenet_sds_ind_csr_reg_wr(priv, CMU + 2*1, value);

	/* CMU_reg3 */
	value = xgenet_sds_ind_csr_reg_rd(priv, CMU + 2*3);
	value = sm_xgenet_set(value,infmode ? 5 : 13, 15, 10);
	/* Init Momsel */
	value = sm_xgenet_set(value,infmode ? 16 : 13, 9, 4);
	xgenet_sds_ind_csr_reg_wr(priv, CMU + 2*3, value);
#if 0
	/* CMU_reg4 */
	value = xgenet_sds_ind_csr_reg_rd(priv, CMU + 2*4);
	/*  Manual cal value for PCIE - don't care, Init Momsel For 8G */
	value = sm_xgenet_set(value,infmode ? 16 : 16, 9, 4);
	xgenet_sds_ind_csr_reg_wr(priv, CMU + 2*4, value);
#endif
	/* CMU_reg34 */
	value = xgenet_sds_ind_csr_reg_rd(priv, CMU + 2*34);
	value = sm_xgenet_set(value,infmode ? 2 : 2, 15, 12);
	 value = sm_xgenet_set(value,infmode ? 10 : 10, 11, 8);
	value = sm_xgenet_set(value,infmode ? 2 : 2, 7, 4);
	value = sm_xgenet_set(value,infmode ? 10 : 10, 3, 0);
	xgenet_sds_ind_csr_reg_wr(priv, CMU + 2*34, value);

	/* CMU_reg0 */
	value = xgenet_sds_ind_csr_reg_rd(priv, CMU + 2*0);
	value = sm_xgenet_set(value,infmode ? 7 : 7, 7, 5);
	xgenet_sds_ind_csr_reg_wr(priv, CMU + 2*0, value);

	/* CMU_reg16 */
	value = xgenet_sds_ind_csr_reg_rd(priv, CMU + 2*16);
	value = sm_xgenet_set(value,infmode ? 7 : 7, 4, 2);
	xgenet_sds_ind_csr_reg_wr(priv, CMU + 2*16, value);

	/* CMU_reg30 */
	value = xgenet_sds_ind_csr_reg_rd(priv, CMU + 2*30);
	/* Lock count Wait time */
	 value = sm_xgenet_set(value,infmode ? 3 : 3, 2, 1);
	xgenet_sds_ind_csr_reg_wr(priv, CMU + 2*30, value);

	/* CMU_reg13 */
	value = xgenet_sds_ind_csr_reg_rd(priv, CMU + 2*13);
	/* Delay time between state transition */
	value = sm_xgenet_set(value,infmode ? 15 : 15, 15, 12);
	value = sm_xgenet_set(value,infmode ? 15 : 15, 11, 8);
	value = sm_xgenet_set(value,infmode ? 15 : 15, 7, 4);
	value = sm_xgenet_set(value,infmode ? 15 : 15, 3, 0);
	xgenet_sds_ind_csr_reg_wr(priv, CMU + 2*13, value);

	/*  CMU_reg14 */
	value = xgenet_sds_ind_csr_reg_rd(priv, CMU + 2*14);
	/* Delay time between state transition. */
	value = sm_xgenet_set(value,infmode ? 15 : 15, 15, 12);
	value = sm_xgenet_set(value,infmode ? 15 : 15, 11, 8);
	value = sm_xgenet_set(value,infmode ? 15 : 15, 7, 4);
	value = sm_xgenet_set(value,infmode ? 15 : 15, 3, 0);
	xgenet_sds_ind_csr_reg_wr(priv, CMU + 2*14, value);

	/* CMU_reg30 */
	value = xgenet_sds_ind_csr_reg_rd(priv, CMU + 2*30);
	/*  Ref Divider for PCI Gen3 mode - dont care,
		 FB divider for Gen3 mode - dont care
		Post Divider for Gen3 mode - dont care
	*/
	value = sm_xgenet_set(value,infmode ? 0 : 0, 3, 3);
	xgenet_sds_ind_csr_reg_wr(priv, CMU + 2*30, value);

	/* CMU_reg0 */
	value = xgenet_sds_ind_csr_reg_rd(priv, CMU + 2*0);
	/* PCIE gen3 , driven by Pipe */
	value = sm_xgenet_set(value,infmode ? 0 : 0, 0, 0);
	xgenet_sds_ind_csr_reg_wr(priv, CMU + 2*0, value);

	/* CMU_reg32 */
	value = xgenet_sds_ind_csr_reg_rd(priv, CMU + 2*32);
	value = sm_xgenet_set(value,infmode ? 3 : 3, 2, 1);
	xgenet_sds_ind_csr_reg_wr(priv, CMU + 2*32, value);

	/* CMU_reg31 */
	value = xgenet_sds_ind_csr_reg_rd(priv, CMU + 2*31);
	value = sm_xgenet_set(value,infmode ? 15 : 15, 3, 0);
	xgenet_sds_ind_csr_reg_wr(priv, CMU + 2*31, value);

	/* CMU_reg37 */
	value = xgenet_sds_ind_csr_reg_rd(priv, CMU + 2*37);
	value = sm_xgenet_set(value,infmode ? 15 : 15, 15, 12);
	value = sm_xgenet_set(value,infmode ? 15 : 15, 3, 0);
	xgenet_sds_ind_csr_reg_wr(priv, CMU + 2*37, value);

	/* xgenet_sds_rxtx_cfg */
	for(inst = 0;inst < 1;inst++) {
		inst_base = 0x0400 + inst*0x0200;
		/**  Tx CONTROL **/
		/* rxtx_reg4 */
		value = xgenet_sds_ind_csr_reg_rd(priv, inst_base + 4*2);
		value = sm_xgenet_set(value,infmode ? 0 : 2, 15, 14);
		value = sm_xgenet_set(value,infmode ? 6 : 1, 13, 11);
		value = sm_xgenet_set(value,infmode ? 4 : 4, 10, 8);
		xgenet_sds_ind_csr_reg_wr(priv,inst_base + 4*2, value);

		/* CMU_reg16 */
		/* TX Rate Change enable: Toggle 0-1-0 */
		value = xgenet_sds_ind_csr_reg_rd(priv, CMU +2*16);
		value = sm_xgenet_set(value, 0, 15, 15);
		xgenet_sds_ind_csr_reg_wr(priv, CMU + 2*16, value);

		value = xgenet_sds_ind_csr_reg_rd(priv, CMU + 2*16);
		value = sm_xgenet_set(value, 1, 15, 15);
		xgenet_sds_ind_csr_reg_wr(priv, CMU + 2*16, value);

		value = xgenet_sds_ind_csr_reg_rd(priv, CMU + 2*16);
		value = sm_xgenet_set(value, 0, 15, 15);
		xgenet_sds_ind_csr_reg_wr(priv, CMU + 2*16, value);

		value = xgenet_sds_ind_csr_reg_rd(priv, CMU + 2*16);
		value = sm_xgenet_set(value, 0, 13, 13);
		xgenet_sds_ind_csr_reg_wr(priv, CMU + 2*16, value);

		value = xgenet_sds_ind_csr_reg_rd(priv, CMU + 2*16);
		value = sm_xgenet_set(value, 1, 13, 13);
		xgenet_sds_ind_csr_reg_wr(priv, CMU + 2*16, value);

		value = xgenet_sds_ind_csr_reg_rd(priv, CMU + 2*16);
		value = sm_xgenet_set(value, 0, 13, 13);
		xgenet_sds_ind_csr_reg_wr(priv, CMU + 2*16, value);

		value = xgenet_sds_ind_csr_reg_rd(priv, CMU + 2*16);
		value = sm_xgenet_set(value, 0, 11, 11);
		xgenet_sds_ind_csr_reg_wr(priv, CMU + 2*16, value);

		value = xgenet_sds_ind_csr_reg_rd(priv, CMU + 2*16);
		value = sm_xgenet_set(value, 1, 11, 11);
		xgenet_sds_ind_csr_reg_wr(priv, CMU + 2*16, value);

		value = xgenet_sds_ind_csr_reg_rd(priv, CMU + 2*16);
		value = sm_xgenet_set(value, 0, 11, 11);
		xgenet_sds_ind_csr_reg_wr(priv, CMU + 2*16, value);

		value = xgenet_sds_ind_csr_reg_rd(priv, CMU + 2*16);
		value = sm_xgenet_set(value, 0, 9, 9);
		xgenet_sds_ind_csr_reg_wr(priv, CMU + 2*16, value);

		value = xgenet_sds_ind_csr_reg_rd(priv, CMU + 2*16);
		value = sm_xgenet_set(value, 1, 9, 9);
		xgenet_sds_ind_csr_reg_wr(priv, CMU + 2*16, value);

		value = xgenet_sds_ind_csr_reg_rd(priv, CMU + 2*16);
		value = sm_xgenet_set(value, 0, 9, 9);
		xgenet_sds_ind_csr_reg_wr(priv, CMU + 2*16, value);

		/* rxtx_reg2 */
		value = xgenet_sds_ind_csr_reg_rd(priv, inst_base + 2*2);
		value = sm_xgenet_set(value,infmode ? 1 : 1, 5, 5);
		xgenet_sds_ind_csr_reg_wr(priv, inst_base + 2*2, value);

		/* rxtx_reg6 */
		value = xgenet_sds_ind_csr_reg_rd(priv, inst_base + 6*2);
		value = sm_xgenet_set(value,infmode ? 1 : 1, 6, 6);
		value = sm_xgenet_set(value,infmode ? 8 : 8, 10, 7);
		 xgenet_sds_ind_csr_reg_wr(priv, inst_base + 6*2, value);

		/* rxtx_reg5 */
		value = xgenet_sds_ind_csr_reg_rd(priv, inst_base + 5*2);
		value = sm_xgenet_set(value,infmode ? 6 : 0, 15, 11);
		value = sm_xgenet_set(value,infmode ? 6 : 0, 10, 5);
		value = sm_xgenet_set(value,infmode ? 0 : 0, 4, 0);
		xgenet_sds_ind_csr_reg_wr(priv, inst_base + 5*2, value);

		/* rxtx_reg61 - Don't care */

		/* rxtx_reg2 */
		 value = xgenet_sds_ind_csr_reg_rd(priv, inst_base + 2*2);
		value = sm_xgenet_set(value,infmode ? 1 : 1, 12, 12);
		xgenet_sds_ind_csr_reg_wr(priv, inst_base + 2*2, value);

		/* rxtx_reg4 */
		value = xgenet_sds_ind_csr_reg_rd(priv, inst_base + 4*2);
		/* TX Forward Loopback enable */
		value = sm_xgenet_set(value,infmode ? 0 : 0, 6, 6);
		xgenet_sds_ind_csr_reg_wr(priv, inst_base + 4*2, value);

		/* rxtx_reg2 */
		value = xgenet_sds_ind_csr_reg_rd(priv, inst_base + 2*2);
		value = sm_xgenet_set(value,infmode ? 0 : 0, 11, 11);
		xgenet_sds_ind_csr_reg_wr(priv, inst_base + 2*2, value);

		/* rxtx_reg6 */
		value = xgenet_sds_ind_csr_reg_rd(priv, inst_base + 6*2);
		value = sm_xgenet_set(value,infmode ? 0 : 0, 3, 3);
		xgenet_sds_ind_csr_reg_wr(priv, inst_base + 6*2, value);

		/* rxtx_reg145 */
		value = xgenet_sds_ind_csr_reg_rd(priv, inst_base + 145*2);
		value = sm_xgenet_set(value,infmode ? 0 : 0, 0, 0);
		xgenet_sds_ind_csr_reg_wr(priv, inst_base + 145*2, value);

		/* rxtx_reg2 */
		value = xgenet_sds_ind_csr_reg_rd(priv, inst_base + 2*2);
		value = sm_xgenet_set(value,infmode ? 0 : 0, 10, 10);
		xgenet_sds_ind_csr_reg_wr(priv, inst_base + 2*2, value);

		/** RX Control **/
		/* rxtx_reg2 */
		value = xgenet_sds_ind_csr_reg_rd(priv, inst_base + 2*2);
		value = sm_xgenet_set(value,infmode ? 0 : 0, 14, 14);
		value = sm_xgenet_set(value,infmode ? 1 : 1, 8, 8);
		value = sm_xgenet_set(value,infmode ? 1 : 1, 7, 6);
		xgenet_sds_ind_csr_reg_wr(priv, inst_base + 2*2, value);

		/* rxtx_reg1 */
		value = xgenet_sds_ind_csr_reg_rd(priv, inst_base + 1*2);
		value = sm_xgenet_set(value,infmode ? 7 : 7, 15, 12);
		xgenet_sds_ind_csr_reg_wr(priv, inst_base + 1*2, value);

		/* rxtx_reg12 */
		value = xgenet_sds_ind_csr_reg_rd(priv, inst_base + 12*2);
		 value = sm_xgenet_set(value,infmode ? 0 : 0, 1, 1);
		xgenet_sds_ind_csr_reg_wr(priv, inst_base + 12*2, value);

		/* rxtx_reg61 - Don't care */

		/* rxtx_reg7 */
		value = xgenet_sds_ind_csr_reg_rd(priv, inst_base + 7*2);
		value = sm_xgenet_set(value,infmode ? 4 : 4, 5, 3);
		value = sm_xgenet_set(value,infmode ? 6 : 1, 13, 11);
		value = sm_xgenet_set(value,infmode ? 0 : 2, 10, 9);
		xgenet_sds_ind_csr_reg_wr(priv, inst_base + 7*2, value);

		/* CMU_reg16 */
		// RX rate change enable: Toggle 0-1-0
		value = xgenet_sds_ind_csr_reg_rd(priv, CMU + 2*16);
		value = sm_xgenet_set(value, 0, 14, 14);
		xgenet_sds_ind_csr_reg_wr(priv, CMU + 2*16, value);

		value = xgenet_sds_ind_csr_reg_rd(priv, CMU + 2*16);
		value = sm_xgenet_set(value, 1, 14, 14);
		xgenet_sds_ind_csr_reg_wr(priv, CMU + 2*16, value);

		value = xgenet_sds_ind_csr_reg_rd(priv, CMU + 2*16);
		value = sm_xgenet_set(value, 0, 14, 14);
		xgenet_sds_ind_csr_reg_wr(priv, CMU + 2*16, value);

		value = xgenet_sds_ind_csr_reg_rd(priv, CMU + 2*16);
		value = sm_xgenet_set(value, 0, 12, 12);
		xgenet_sds_ind_csr_reg_wr(priv, CMU + 2*16, value);

		value = xgenet_sds_ind_csr_reg_rd(priv, CMU + 2*16);
		value = sm_xgenet_set(value, 1, 12, 12);
		xgenet_sds_ind_csr_reg_wr(priv, CMU + 2*16, value);

		value = xgenet_sds_ind_csr_reg_rd(priv, CMU + 2*16);
		value = sm_xgenet_set(value, 0, 12, 12);
		xgenet_sds_ind_csr_reg_wr(priv, CMU + 2*16, value);

		value = xgenet_sds_ind_csr_reg_rd(priv, CMU + 2*16);
		value = sm_xgenet_set(value, 0, 10, 10);
		xgenet_sds_ind_csr_reg_wr(priv, CMU + 2*16, value);

		value = xgenet_sds_ind_csr_reg_rd(priv, CMU + 2*16);
		value = sm_xgenet_set(value, 1, 10, 10);
		xgenet_sds_ind_csr_reg_wr(priv, CMU + 2*16, value);

		value = xgenet_sds_ind_csr_reg_rd(priv, CMU + 2*16);
		value = sm_xgenet_set(value, 0, 10, 10);
		xgenet_sds_ind_csr_reg_wr(priv, CMU + 2*16, value);

		value = xgenet_sds_ind_csr_reg_rd(priv, CMU + 2*16);
		value = sm_xgenet_set(value, 0, 8, 8);
		xgenet_sds_ind_csr_reg_wr(priv, CMU + 2*16, value);

		value = xgenet_sds_ind_csr_reg_rd(priv, CMU + 2*16);
		value = sm_xgenet_set(value, 1, 8, 8);
		xgenet_sds_ind_csr_reg_wr(priv, CMU + 2*16, value);

		value = xgenet_sds_ind_csr_reg_rd(priv, CMU + 2*16);
		value = sm_xgenet_set(value, 0, 8, 8);
		xgenet_sds_ind_csr_reg_wr(priv, CMU + 2*16, value);

		/* rxtx_reg148 */
		value = xgenet_sds_ind_csr_reg_rd(priv, inst_base + 148*2);
		value = sm_xgenet_set(value,infmode ? 0xFFFF : 0xFFFF, 15, 0);
		xgenet_sds_ind_csr_reg_wr(priv, inst_base + 148*2, value);

		/* rxtx_reg149 */
		value = xgenet_sds_ind_csr_reg_rd(priv, inst_base + 149*2);
		value = sm_xgenet_set(value,infmode ? 0xFFFF : 0xFFFF, 15, 0);
		xgenet_sds_ind_csr_reg_wr(priv, inst_base + 149*2, value);

		/* rxtx_reg150 */
		value =  xgenet_sds_ind_csr_reg_rd(priv, inst_base + 150*2);
		 value = sm_xgenet_set(value,infmode ? 0xFFFF : 0xFFFF, 15, 0);
		xgenet_sds_ind_csr_reg_wr(priv, inst_base + 150*2, value);

		/* rxtx_reg151 */
		value = xgenet_sds_ind_csr_reg_rd(priv, inst_base + 151*2);
		value = sm_xgenet_set(value,infmode ? 0xFFFF : 0xFFFF, 15, 0);
		 xgenet_sds_ind_csr_reg_wr(priv, inst_base + 151*2, value);

		/* rxtx_reg147 */
		value = xgenet_sds_ind_csr_reg_rd(priv, inst_base + 147*2);
		value = sm_xgenet_set(value,infmode ? 6 : 6, 15, 0);
		xgenet_sds_ind_csr_reg_wr(priv, inst_base + 147*2, value);

		/* rxtx_reg1 */
		value =  xgenet_sds_ind_csr_reg_rd(priv, inst_base + 1*2);
		value = sm_xgenet_set(value,infmode ? 28 : 28, 11, 7);
		xgenet_sds_ind_csr_reg_wr(priv, inst_base + 1*2, value);

		/* rxtx_reg0 */
		value = xgenet_sds_ind_csr_reg_rd(priv, inst_base + 0*2);
		value = sm_xgenet_set(value,infmode ? 16 : 1, 15, 11);
		 value = sm_xgenet_set(value,infmode ? 16 : 13, 10, 6);
		value = sm_xgenet_set(value,infmode ? 16 : 1, 5, 1);
		xgenet_sds_ind_csr_reg_wr(priv, inst_base + 0*2, value);

		/* rxtx_reg14 */
		value =  xgenet_sds_ind_csr_reg_rd(priv, inst_base + 14*2);
		value = sm_xgenet_set(value,infmode ? 0 : 0, 6, 6);
		 xgenet_sds_ind_csr_reg_wr(priv, inst_base + 14*2, value);

		/* rxtx_reg12 */
		value = xgenet_sds_ind_csr_reg_rd(priv, inst_base + 12*2);
		/* SUM Offset enable */
		value = sm_xgenet_set(value,infmode ? 0 : 0, 2, 2);
		 xgenet_sds_ind_csr_reg_wr(priv, inst_base + 12*2, value);

		/* rxtx_reg12 */
		value = xgenet_sds_ind_csr_reg_rd(priv, inst_base + 12*2);
		/* Latch Offset Enable */
		value = sm_xgenet_set(value,infmode ? 1 : 1, 13, 13);
		xgenet_sds_ind_csr_reg_wr(priv, inst_base + 12*2, value);

		/* rxtx_reg128 */
		 value = xgenet_sds_ind_csr_reg_rd(priv, inst_base + 128*2);
		value = sm_xgenet_set(value,infmode ? 3 : 3, 3, 2);
		xgenet_sds_ind_csr_reg_wr(priv, inst_base + 128*2, value);

		/* rxtx_reg127 */
		value = xgenet_sds_ind_csr_reg_rd(priv, inst_base + 127*2);
		value = sm_xgenet_set(value,infmode ? 0 : 0, 3, 3);
		xgenet_sds_ind_csr_reg_wr(priv, inst_base + 127*2, value);

		/* rxtx_reg8 */
		value = xgenet_sds_ind_csr_reg_rd(priv, inst_base + 8*2);
		value = sm_xgenet_set(value,infmode ? 1 : 1, 14, 14);
		value = sm_xgenet_set(value,infmode ? 0 : 1, 11, 11);
		xgenet_sds_ind_csr_reg_wr(priv, inst_base + 8*2, value);

		/* rxtx_reg61 */
		value = xgenet_sds_ind_csr_reg_rd(priv, inst_base + 61*2);
		value = sm_xgenet_set(value,infmode ? 7 : 0, 13, 10);
		 xgenet_sds_ind_csr_reg_wr(priv, inst_base + 61*2, value);

		/* rxtx_reg125 */
		 value = xgenet_sds_ind_csr_reg_rd(priv, inst_base + 125*2);
		 value = sm_xgenet_set(value,infmode ? 20 : 0, 15, 9);
		value = sm_xgenet_set(value,infmode ? 1 : 1, 1, 1);
		xgenet_sds_ind_csr_reg_wr(priv, inst_base + 125*2, value);

		/* rxtx_reg11 */
		value = xgenet_sds_ind_csr_reg_rd(priv, inst_base + 11*2);
		value = sm_xgenet_set(value,infmode ? 0 : 0, 15, 11);
		xgenet_sds_ind_csr_reg_wr(priv, inst_base + 11*2, value);

		/* rxtx_reg61 */
		value = xgenet_sds_ind_csr_reg_rd(priv, inst_base + 61*2);
		value = sm_xgenet_set(value,infmode ? 1 : 0, 3, 3);
		xgenet_sds_ind_csr_reg_wr(priv, inst_base + 61*2, value);

		/* rxtx_reg102 */
		value = xgenet_sds_ind_csr_reg_rd(priv, inst_base + 102*2);
		value = sm_xgenet_set(value,infmode ? 3 : 3, 6, 5);
		xgenet_sds_ind_csr_reg_wr(priv, inst_base + 102*2, value);

		/* rxtx_reg8 */
		value = xgenet_sds_ind_csr_reg_rd(priv, inst_base + 8*2);
		value = sm_xgenet_set(value,infmode ? 0 : 0, 9, 9);
		xgenet_sds_ind_csr_reg_wr(priv, inst_base + 8*2, value);

		/* rxtx_reg96 */
		value = xgenet_sds_ind_csr_reg_rd(priv, inst_base + 96*2);
		value = sm_xgenet_set(value,infmode ? 16 : 16, 15, 11);
		 value = sm_xgenet_set(value,infmode ? 16 : 16, 10, 6);
		value = sm_xgenet_set(value,infmode ? 16 : 16, 5, 1);
		xgenet_sds_ind_csr_reg_wr(priv, inst_base + 96*2, value);

		/* rxtx_reg97 */
		value = xgenet_sds_ind_csr_reg_rd(priv, inst_base + 97*2);
		value = sm_xgenet_set(value,infmode ? 16 : 16, 15, 11);
		value = sm_xgenet_set(value,infmode ? 16 : 16, 10, 6);
		value = sm_xgenet_set(value,infmode ? 16 : 16, 5, 1);
		xgenet_sds_ind_csr_reg_wr(priv, inst_base + 97*2, value);

		/* rxtx_reg98 */
		value = xgenet_sds_ind_csr_reg_rd(priv, inst_base + 98*2);
		value = sm_xgenet_set(value,infmode ? 16 : 16, 15, 11);
		value = sm_xgenet_set(value,infmode ? 16 : 16, 10, 6);
		value = sm_xgenet_set(value,infmode ? 16 : 16, 5, 1);
		xgenet_sds_ind_csr_reg_wr(priv, inst_base + 98*2, value);

		/* rxtx_reg99 */
		value = xgenet_sds_ind_csr_reg_rd(priv, inst_base + 99*2);
		value = sm_xgenet_set(value,infmode ? 5 : 8, 15, 11);
		value = sm_xgenet_set(value,infmode ? 5 : 8, 10, 6);
		value = sm_xgenet_set(value,infmode ? 5 : 8, 5, 1);
		xgenet_sds_ind_csr_reg_wr(priv, inst_base + 99*2, value);

		// rxtx_reg100
		value = xgenet_sds_ind_csr_reg_rd(priv, inst_base + 100*2);
		// CDR Phase Loop BW
		value = sm_xgenet_set(value,infmode ? 5 : 8, 15, 11);
		// CDR Phase Loop BW
		value = sm_xgenet_set(value,infmode ? 5 : 8, 10, 6);
		// CDR Phase Loop BW
		value = sm_xgenet_set(value,infmode ? 5 : 8, 5, 1);
		xgenet_sds_ind_csr_reg_wr(priv, inst_base + 100*2, value);

		/////////////
		// rxtx_reg101
		value = xgenet_sds_ind_csr_reg_rd(priv, inst_base + 101*2);
		// CDR Phase Loop BW
		value = sm_xgenet_set(value,infmode ? 5 : 8, 15, 11);
		// CDR Phase Loop BW
		value = sm_xgenet_set(value,infmode ? 5 : 8, 10, 6);
		// CDR Phase Loop BW
		value = sm_xgenet_set(value,infmode ? 5 : 8, 5, 1);
		xgenet_sds_ind_csr_reg_wr(priv, inst_base + 101*2, value);

		/////////////
		// rxtx_reg8
		value = xgenet_sds_ind_csr_reg_rd(priv, inst_base + 8*2);
		// RX los disable
		value = sm_xgenet_set(value,infmode ? 1 : 1, 8, 8);
		xgenet_sds_ind_csr_reg_wr(priv, inst_base + 8*2, value);

		/////////////
		// rxtx_reg26
		value = xgenet_sds_ind_csr_reg_rd(priv, inst_base + 26*2);
		// BLWC Enable
		value = sm_xgenet_set(value,infmode ? 1 : 1, 3, 3);
		xgenet_sds_ind_csr_reg_wr(priv, inst_base + 26*2, value);

		/////////////
		// rxtx_reg31
		if (infmode == 0) {
			value = xgenet_sds_ind_csr_reg_rd(priv, inst_base + 31*2);
			/* H0 prese */
			value = sm_xgenet_set(value,infmode ? 0 : 0, 15, 9);
			xgenet_sds_ind_csr_reg_wr(priv, inst_base + 31*2, value);
		}

		/////////////
		// rxtx_reg81
		value = xgenet_sds_ind_csr_reg_rd(priv, inst_base + 81*2);
		// DFE BW select
		value = sm_xgenet_set(value,infmode ? 14 : 14, 15, 11);
		// DFE BW select
		value = sm_xgenet_set(value,infmode ? 14 : 14, 10, 6);
		// DFE BW select
		value = sm_xgenet_set(value,infmode ? 14 : 14, 5, 1);
		xgenet_sds_ind_csr_reg_wr(priv, inst_base + 81*2, value);

		/////////////
		// rxtx_reg82
		value = xgenet_sds_ind_csr_reg_rd(priv, inst_base + 82*2);
		// DFE BW select
		value = sm_xgenet_set(value,infmode ? 14 : 14, 15, 11);
		// DFE BW select
		value = sm_xgenet_set(value,infmode ? 14 : 14, 10, 6);
		// DFE BW select
		value = sm_xgenet_set(value,infmode ? 14 : 14, 5, 1);
		xgenet_sds_ind_csr_reg_wr(priv, inst_base + 82*2, value);

		/////////////
		// rxtx_reg83
		value = xgenet_sds_ind_csr_reg_rd(priv, inst_base + 83*2);
		// DFE BW select
		value = sm_xgenet_set(value,infmode ? 14 : 14, 15, 11);
		// DFE BW select
		value = sm_xgenet_set(value,infmode ? 14 : 14, 10, 6);
		// DFE BW select
		value = sm_xgenet_set(value,infmode ? 14 : 14, 5, 1);
		xgenet_sds_ind_csr_reg_wr(priv, inst_base + 83*2, value);

		/////////////
		// rxtx_reg84
		value = xgenet_sds_ind_csr_reg_rd(priv, inst_base + 84*2);
		// CDR phase Adaptation Loop BW
		value = sm_xgenet_set(value,infmode ? 14 : 14, 15, 11);
		// CDR phase Adaptation Loop BW
		value = sm_xgenet_set(value,infmode ? 14 : 14, 10, 6);
		// CDR phase Adaptation Loop BW
		value = sm_xgenet_set(value,infmode ? 14 : 14, 5, 1);
		xgenet_sds_ind_csr_reg_wr(priv, inst_base + 84*2, value);
		/////////////
		// rxtx_reg85
	 	value = xgenet_sds_ind_csr_reg_rd(priv, inst_base + 85*2);
		// CDR phase Adaptation Loop BW
		value = sm_xgenet_set(value,infmode ? 14 : 14, 15, 11);
		// CDR phase Adaptation Loop BW
		value = sm_xgenet_set(value,infmode ? 14 : 14, 10, 6);
		// CDR phase Adaptation Loop BW
		value = sm_xgenet_set(value,infmode ? 14 : 14, 5, 1);
		xgenet_sds_ind_csr_reg_wr(priv, inst_base + 85*2, value);

		/////////////
		// rxtx_reg86
		value = xgenet_sds_ind_csr_reg_rd(priv, inst_base + 86*2);
		// CDR phase Adaptation Loop BW
		value = sm_xgenet_set(value,infmode ? 14 : 14, 15, 11);
		// CDR phase Adaptation Loop BW
		value = sm_xgenet_set(value,infmode ? 14 : 14, 10, 6);
		// CDR phase Adaptation Loop BW
		value = sm_xgenet_set(value,infmode ? 14 : 14, 5, 1);
		xgenet_sds_ind_csr_reg_wr(priv, inst_base + 86*2, value);

		/////////////
		// rxtx_reg87
		value = xgenet_sds_ind_csr_reg_rd(priv, inst_base + 87*2);
		// DFE Main Tap (Threshold) BW
		value = sm_xgenet_set(value,infmode ? 14 : 14, 15, 11);
		// DFE Main Tap (Threshold) BW
		value = sm_xgenet_set(value,infmode ? 14 : 14, 10, 6);
		// DFE Main Tap (Threshold) BW
		value = sm_xgenet_set(value,infmode ? 14 : 14, 5, 1);
		xgenet_sds_ind_csr_reg_wr(priv, inst_base + 87*2, value);

		/////////////
		// rxtx_reg88
		value = xgenet_sds_ind_csr_reg_rd(priv, inst_base + 88*2);
		// DFE Main Tap (Threshold) BW
		value = sm_xgenet_set(value,infmode ? 14 : 14, 15, 11);
		// DFE Main Tap (Threshold) BW
		value = sm_xgenet_set(value,infmode ? 14 : 14, 10, 6);
		// DFE Main Tap (Threshold) BW
		value = sm_xgenet_set(value,infmode ? 14 : 14, 5, 1);
		xgenet_sds_ind_csr_reg_wr(priv, inst_base + 88*2, value);

		/////////////
		// rxtx_reg89
		value = xgenet_sds_ind_csr_reg_rd(priv, inst_base + 89*2);
		// DFE Main Tap (Threshold) BW
		value = sm_xgenet_set(value,infmode ? 14 : 14, 15, 11);
		// DFE Main Tap (Threshold) BW
		value = sm_xgenet_set(value,infmode ? 14 : 14, 10, 6);
		// DFE Main Tap (Threshold) BW
		value = sm_xgenet_set(value,infmode ? 14 : 14, 5, 1);
		xgenet_sds_ind_csr_reg_wr(priv, inst_base + 89*2, value);

		/////////////
		// rxtx_reg145
		value = xgenet_sds_ind_csr_reg_rd(priv, inst_base + 145*2);
		// DFE Configuration Selection
		value = sm_xgenet_set(value,infmode ? 3 : 3, 15, 14);
		xgenet_sds_ind_csr_reg_wr(priv, inst_base + 145*2, value);

		/////////////
		// rxtx_reg28
		value = xgenet_sds_ind_csr_reg_rd(priv, inst_base + 28*2);
		// DFE tap enables
		value = sm_xgenet_set(value,infmode ? 0xFFFF : 0x0, 15, 0);
		xgenet_sds_ind_csr_reg_wr(priv, inst_base + 28*2, value);

		/////////////
		// rxtx_reg7
		value = xgenet_sds_ind_csr_reg_rd(priv, inst_base + 7*2);
		// RX Resetn
		value = sm_xgenet_set(value,infmode ? 1 : 1, 8, 8);
		// RX Forward Loopback enable
		value = sm_xgenet_set(value,infmode ? 0 : 0, 14, 14);
		// RX Bist enable for PRBS transfer
		value = sm_xgenet_set(value,infmode ? 0 : 0, 6, 6);
		xgenet_sds_ind_csr_reg_wr(priv, inst_base + 7*2, value);

   		/////////////
		// rxtx_reg61
		// Bert Reset Active Low: Toggle0-1-0
		//value = xgenet_sds_ind_csr_reg_rd("rxtx_reg61", inst_base + 61*2);
		//value = sm_xgenet_set(value,infmode ? 0 : 0, 5, 5);
		//xgenet_sds_ind_csr_reg_wr("rxtx_reg61", inst_base + 61*2, value);

		//value = xgenet_sds_ind_csr_reg_rd("rxtx_reg61", inst_base + 61*2);
		//value = sm_xgenet_set(value,infmode ? 1 : 1, 5, 5);
		//xgenet_sds_ind_csr_reg_wr("rxtx_reg61", inst_base + 61*2, value);

		//value = xgenet_sds_ind_csr_reg_rd("rxtx_reg61", inst_base + 61*2);
		//value = sm_xgenet_set(value,infmode ? 0 : 0, 5, 5);
		//xgenet_sds_ind_csr_reg_wr("rxtx_reg61", inst_base + 61*2, value);

		/////////////
		// rxtx_reg6
		// Bert PRBS resync: Toggle0-1-0
		//value = xgenet_sds_ind_csr_reg_rd("rxtx_reg6", inst_base + 6*2);
		//value = sm_xgenet_set(value,infmode ? 0 : 0, 1, 1);
		//xgenet_sds_ind_csr_reg_wr("rxtx_reg6", inst_base + 6*2, value);

		//value = xgenet_sds_ind_csr_reg_rd("rxtx_reg6", inst_base + 6*2);
		//value = sm_xgenet_set(value,infmode ? 1 : 1, 1, 1);
		//xgenet_sds_ind_csr_reg_wr("rxtx_reg6", inst_base + 6*2, value);

		//value = xgenet_sds_ind_csr_reg_rd("rxtx_reg6", inst_base + 6*2);
		//value = sm_xgenet_set(value,infmode ? 0 : 0, 1, 1);
		//xgenet_sds_ind_csr_reg_wr("rxtx_reg6", inst_base + 6*2, value);

		/////////////
		// rxtx_reg6
		value = xgenet_sds_ind_csr_reg_rd(priv, inst_base + 6*2);
		// Bert Error count capture
		value = sm_xgenet_set(value,infmode ? 0 : 0, 0, 0);
		xgenet_sds_ind_csr_reg_wr(priv, inst_base + 6*2, value);

		/////////////
		// rxtx_reg12
		value = xgenet_sds_ind_csr_reg_rd(priv, inst_base + 12*2);
		// RX Serial Data swap(P and N polarity)
		value = sm_xgenet_set(value,infmode ? 0 : 0, 11, 11);
		xgenet_sds_ind_csr_reg_wr(priv, inst_base + 12*2, value);
	}
}

static void  serdes_pdown_force_vco(struct apm_data_priv *priv)
{
#if 0
	u32 value;
	u32 inst_base = 0x0400;
	/*-------------------- */
	/* POWER DOWN */
	/*-------------------- */
	value = xgenet_sds_ind_csr_reg_rd(priv, CMU + 2*0);
	/* FIELD_CMU_REG0_PDOWN_SET */
	value = sm_xgenet_set(value, 1, 14, 14);
	xgenet_sds_ind_csr_reg_wr(priv, CMU + 2*0, value);

	value = xgenet_sds_ind_csr_reg_rd(priv, CMU + 2*0);
	/* FIELD_CMU_REG5_PLL_RESETB_SET */
	value = sm_xgenet_set(value, 0, 15, 15);
	xgenet_sds_ind_csr_reg_wr(priv, CMU + 2*0, value);

	value = xgenet_sds_ind_csr_reg_rd(priv, inst_base + 2*2);
	/* TX power down */
	value = sm_xgenet_set(value, 1, 4, 4); 
	xgenet_sds_ind_csr_reg_wr(priv, inst_base + 2*2, value);

	value = xgenet_sds_ind_csr_reg_rd(priv, inst_base + 2*11);
	/* Power down RX current gen Block */
	value = sm_xgenet_set(value, 1, 0, 0); 
	xgenet_sds_ind_csr_reg_wr(priv, inst_base + 2*11, value);

	value = xgenet_sds_ind_csr_reg_rd(priv, inst_base + 2*12);
	/* RX powerdown */
	value = sm_xgenet_set(value, 1, 12, 12); 
	xgenet_sds_ind_csr_reg_wr(priv, inst_base + 2*12, value);

	value = xgenet_sds_ind_csr_reg_rd(priv, inst_base + 2*2);
	/* Soft main reset */
	value = sm_xgenet_set(value, 0, 15, 15); 
	xgenet_sds_ind_csr_reg_wr(priv, inst_base + 2*2, value);
	udelay(100);

	/*-------------------- */
	/* POWER UP */
	/*-------------------- */
	value = xgenet_sds_ind_csr_reg_rd(priv, CMU + 2*0);
	/* FIELD_CMU_REG0_PDOWN_SET */
	value = sm_xgenet_set(value, 0, 14, 14);
	xgenet_sds_ind_csr_reg_wr(priv, CMU + 2*0, value);

	value = xgenet_sds_ind_csr_reg_rd(priv, CMU + 2*0);
	/* FIELD_CMU_REG5_PLL_RESETB_SET */
	value = sm_xgenet_set(value, 1, 15, 15);
	xgenet_sds_ind_csr_reg_wr(priv, CMU + 2*0, value);

	value = xgenet_sds_ind_csr_reg_rd(priv, inst_base + 2*2);
	/* TX power down */
	value = sm_xgenet_set(value, 0, 4, 4); 
	xgenet_sds_ind_csr_reg_wr(priv, inst_base + 2*2, value);

	value = xgenet_sds_ind_csr_reg_rd(priv, inst_base + 2*11);
	/* Power down RX current gen Block */
	value = sm_xgenet_set(value, 0, 0, 0); 
	xgenet_sds_ind_csr_reg_wr(priv, inst_base + 2*11, value);

	value = xgenet_sds_ind_csr_reg_rd(priv, inst_base + 2*12);
	/* RX powerdown */
	value = sm_xgenet_set(value, 0, 12, 12); 
	xgenet_sds_ind_csr_reg_wr(priv, inst_base + 2*12, value);

	value = xgenet_sds_ind_csr_reg_rd(priv, inst_base + 2*2);
	/* Soft main reset */
	value = sm_xgenet_set(value, 1, 15, 15); 
	xgenet_sds_ind_csr_reg_wr(priv, inst_base + 2*2, value);

	udelay(100);
	/*-------------------- */
	/*  */
	/*-------------------- */

	value = xgenet_sds_ind_csr_reg_rd(priv, CMU + 2*32);
	// FIELD_CMU_REG32_FORCE_VCOCAL_START_SET
	value = sm_xgenet_set(value, 1, 14, 14);
	xgenet_sds_ind_csr_reg_wr(priv, CMU + 2*32, value);

	value = xgenet_sds_ind_csr_reg_rd(priv, CMU + 2*32);
	/* FIELD_CMU_REG32_FORCE_VCOCAL_START_SET */
	value = sm_xgenet_set(value, 0, 14, 14);
	xgenet_sds_ind_csr_reg_wr(priv, CMU + 2*32, value);
	udelay(100);
#endif
}

static void force_lat_summer_cal(struct apm_data_priv *priv)
{
	u32 inst_base = 0x400;
	u32 value;

	/* SUMMer calib 1 */
	value = xgenet_sds_ind_csr_reg_rd(priv, inst_base + 127*2);
	value = sm_xgenet_set(value, 1, 1, 1);
	xgenet_sds_ind_csr_reg_wr(priv, inst_base + 127*2, value);
	udelay(4);
	/* SUMMer calib 0 */
	value = xgenet_sds_ind_csr_reg_rd(priv, inst_base + 127*2);
	value = sm_xgenet_set(value, 0, 1, 1);
	xgenet_sds_ind_csr_reg_wr(priv, inst_base + 127*2, value);
	udelay(4);
	/* Latch calib 1 */
	value = xgenet_sds_ind_csr_reg_rd(priv, inst_base + 127*2);
	value = sm_xgenet_set(value, 1, 2, 2);
	xgenet_sds_ind_csr_reg_wr(priv, inst_base + 127*2, value);
	udelay(4);
	/* Latch calib 0 */
	value = xgenet_sds_ind_csr_reg_rd(priv, inst_base + 127*2);
	value = sm_xgenet_set(value, 0, 2, 2);
	xgenet_sds_ind_csr_reg_wr(priv, inst_base + 127*2, value);
	udelay(4);
}

void apm_xgenet_serdes_init(struct apm_data_priv *priv)
{
	u32 value, loop;
	u32 refclksel, refclk_cmos_sel; /*, customer_pin_mode; */
	u32 rx_clk_inv = 0;
	u32 pll_ready;
	u32 port_addr, i, infmode;
	u32 pll_lock, vco_calibration;
#ifdef PHY_DEBUG
	u32 rndrefclk;
	u32 tx_ready, rx_ready;
#endif
#if 0	//TODO
	char *chip_revision = apm88xxx_chip_revision();

	if (!strncmp(chip_revision, "A1", 2))
		rx_clk_inv = 1;
#endif

	apm_enet_read(priv, BLOCK_ETH_CLKRST_CSR, XGENET_CONFIG_REG_ADDR, &value);
	/* xgmii, infmode = 1 */
	infmode = CFG_SGMII_EN_RD(value) == 2 ? 1: 0; 
	PHY_PRINT("%s infmode = 0x%x\n", __func__, infmode); 
	/* module_init_enet_serdes */
	refclksel = 0;
	refclk_cmos_sel = 0;
#ifdef PHY_DEBUG
        rndrefclk = (refclksel << 1) | refclk_cmos_sel;
#endif
	PHY_PRINT("INIT_SERDES : Config Ref Clock\n");
	/* CMU_reg0 */
	value = xgenet_sds_ind_csr_reg_rd(priv, CMU + 2*0);
	value = sm_xgenet_set(value, refclksel, 13, 13);
	xgenet_sds_ind_csr_reg_wr(priv, CMU + 2*0, value);
	/* CMU_reg1 */
	value = xgenet_sds_ind_csr_reg_rd(priv, CMU + 2*1);
	value = sm_xgenet_set(value, refclk_cmos_sel, 0, 0);
	xgenet_sds_ind_csr_reg_wr(priv, CMU + 2*1, value);
	/* CMU_reg37 */
	value = xgenet_sds_ind_csr_reg_rd(priv, CMU + 2*37);
	/* CMU_reg36 */
	value = xgenet_sds_ind_csr_reg_rd(priv, CMU + 2*36);
	/* CMU_reg16 */
	value = xgenet_sds_ind_csr_reg_rd(priv, CMU + 2*16);


	 if (infmode) /* xgmii */
		 value = 0x306430;
	 else		/* SGMII */
		 value = 0x305030;

	 apm_enet_write(priv, BLOCK_ETH_CLKRST_CSR, XGENET_PLL_CFG_ADDR, value);
	if (refclk_cmos_sel) {
		 i = 0;
		 do {
			 apm_enet_read(priv, BLOCK_ETH_CLKRST_CSR, XGENET_PLL_STAT_ADDR, &value);
			 PHY_PRINT("INIT_SERDES : waiting for XGENET PLL to lock\n");
			 if (i++ > 10)
				 break;
			 udelay(100);
		 } while (value == 0);
	}
	 /* program PLL output clock divider value after PLL has locked */
	 if (infmode) /* xgmii */
		 value = 0x4;
	 else /* SGMII */
		 value = 0x5;
	 apm_enet_write(priv, BLOCK_ETH_CLKRST_CSR, XGENET_PLL_DIV_CFG_ADDR, value);

	/* XGENET_SDS_RST_CTL, Assert all reset */
        apm_enet_write(priv, BLOCK_ETH_SDS_CSR, XGENET_SDS_RST_CTL_ADDR, 0xDE);
	udelay(2);
#if 0
	apm_enet_wr32((void *)0x17001398, 0x001e1e1e); /* MDIO enable config */
	apm_enet_rd32((void *)0x17001398, &value);
	ENET_DEBUG("READ MPA_MDIO_IOCTL : 0x%08x\n", value);
#endif

	PHY_PRINT("INIT_SERDES : REFCLK using -- %s\n",(rndrefclk == 0) ? "External differential clk" : "Internal single ended (cmos) clk");
	PHY_PRINT("INIT_SERDES : %s/ENET using -- LSPLL\n",infmode ? "XGMII" : "SGMII");

	apm_enet_write(priv, BLOCK_ETH_SDS_CSR, XGENET_SDS_CTL0_ADDR, 0);
	sm_xgenet_module_program_all_regs(priv);

        if (rx_clk_inv) {
                PHY_PRINT("INIT_SERDES : Enable RXCLK Inversion.");
                for (i = 0; i < 1;  i++) {
                        PHY_PRINT("INIT_SERDES : RXTX Inst %x\n", i);
			port_addr = 0x0400 + i*0x0200;
                        value = xgenet_sds_ind_csr_reg_rd(priv, port_addr + 0xD*2);
			value = sm_xgenet_set(value, 1, 13, 13);
                        xgenet_sds_ind_csr_reg_wr(priv, port_addr + 0xD*2, value);
                }
        }
#ifdef APM_XGENET_XGMII_TX2RX_LOOPBACK	/* one port only */
	/* rxtx.reg4.tx_loopback_buf_en = 1 */
       	PHY_PRINT("INIT_SERDES : SERDES XGMII Tx2Rx Loopback\n");
	value = xgenet_sds_ind_csr_reg_rd(priv, 0x0400 + 0x4*2);
	value = sm_xgenet_set(value, 1, 6, 6);
	xgenet_sds_ind_csr_reg_wr(priv, 0x0400 + 0x4*2, value);
	/* rxtx.reg7.loopback_ena_ctle = 1 */
	value = xgenet_sds_ind_csr_reg_rd(priv, 0x0400 + 0x7*2);
	value = sm_xgenet_set(value, 1, 14, 14);
	xgenet_sds_ind_csr_reg_wr(priv, 0x0400 + 0x7*2, value);
#endif
	/* De-assert all reset */
        apm_enet_write(priv, BLOCK_ETH_SDS_CSR, XGENET_SDS_RST_CTL_ADDR, 0xDF);
	udelay(2);

	if (infmode)
		serdes_pdown_force_vco(priv);
	serdes_calib(priv);
	serdes_reset_rxd_rxa(priv, 0);

	/* INIT_SERDES : Check PLL Ready/LOCK and VCO Calibration status */
 	PHY_PRINT("INIT_SERDES : Check PLL Ready/LOCK and VCO Calibration status\n");
	loop = 1000;
	pll_ready = 0;
	while (pll_ready == 0) {
		udelay(10);
		apm_enet_read(priv, BLOCK_ETH_SDS_CSR, XGENET_SDS_CMU_STATUS0_ADDR, &value);
		PHY_PRINT("%s value=0x%x\n", __func__, value);	
		pll_ready = CFG_CMU_O_PLL_READY0_RD(value);
		vco_calibration = CFG_CMU_O_VCO_CALDONE0_RD(value) ;
		pll_lock = CFG_CMU_O_PLL_LOCK0_RD(value);
		if (((pll_ready && pll_lock && vco_calibration)) ||
			(loop -- == 0))
			break;
	}

#ifdef PHY_DEBUG
        PHY_PRINT("INIT_SERDES : PLL is %sREADY\n", pll_ready ? "" : "not ");
        PHY_PRINT("INIT_SERDES : PLL %sLOCKed\n",
		CFG_CMU_O_PLL_LOCK0_RD(value) ? "" : "not ");
        PHY_PRINT("INIT_SERDES : PLL VCO Calibration %s\n",
		CFG_CMU_O_VCO_CALDONE0_RD(value) ? "Successful" : "not Successful");

        PHY_PRINT("INIT_SERDES : Check TX/RX Ready\n");
	apm_enet_read(priv, BLOCK_ETH_SDS_CSR, XGENET_SDS_RXTX_STATUS_ADDR, &value);

	tx_ready = CFG_TX_O_TX_READY_RD(value);
	rx_ready = CFG_RX_O_RX_READY_RD(value);
        PHY_PRINT("INIT_SERDES : TX is %sready\n", tx_ready ? "" : "not ");
        PHY_PRINT("INIT_SERDES : RX is %sready\n", rx_ready ? "" : "not ");
#endif
	if (!infmode)
		force_lat_summer_cal(priv);
		
}

void xgenet_serdes_deassert(struct apm_data_priv *priv)
{
	u32 data;

	/* Clear Software Reset for Serdes */
	apm_enet_read(priv, BLOCK_ETH_CLKRST_CSR, ENET_SRST_ADDR, &data);
	PHY_PRINT("%s read 0x%x <- 0x%llx\n", __func__,
		data, XGENET_CLKRST_CSR_BASE_ADDR + ENET_SRST_ADDR);

	data = ENET_SRST_DEFAULT;
	PHY_PRINT("%s write 0x%x -> 0x%llx\n", __func__,
		data, XGENET_CLKRST_CSR_BASE_ADDR+ ENET_SRST_ADDR);
	apm_enet_write(priv, BLOCK_ETH_CLKRST_CSR, ENET_SRST_ADDR, data);
	udelay(2);
}

void apm_xgmac_set_preamble_length(struct apm_data_priv *priv, u8 length)
{
	u32 data;

	if (priv->phy_mode == PHY_MODE_SGMII) {
		/* Read current value of the config 2 register */
		apm_enet_read(priv, BLOCK_MCX_MAC, MAC_CONFIG_2_ADDR, &data);

		/* Write value back to config 2 register */
		apm_enet_write(priv, BLOCK_MCX_MAC, MAC_CONFIG_2_ADDR,
			PREAMBLE_LENGTH2_SET(data, length));
	}
}

void apm_xgmac_set_intf_mode(struct apm_data_priv *priv, u8 intf_mode)
{
	u32 data;

	if (priv->phy_mode == PHY_MODE_SGMII) {
		/* Read current value of the config 2 register */
		apm_enet_read(priv, BLOCK_MCX_MAC, MAC_CONFIG_2_ADDR, &data);

		/* Write value back to config 2 register */
		apm_enet_write(priv, BLOCK_MCX_MAC, MAC_CONFIG_2_ADDR,
			ENET_INTERFACE_MODE2_SET(data, intf_mode));
	}
}

int apm_xgmac_get_intf_mode(struct apm_data_priv *priv)
{
	u32 data = 0;

	if (priv->phy_mode == PHY_MODE_SGMII) {
		/* Read current value of the config 2 register */
		apm_enet_read(priv, BLOCK_MCX_MAC, MAC_CONFIG_2_ADDR, &data);
		data = ENET_INTERFACE_MODE2_RD(data);
	}

	return data;
}

void apm_xgmac_huge_frame_enable(struct apm_data_priv *priv, u8 enable)
{
	u32 data;

	if (priv->phy_mode == PHY_MODE_SGMII) {
		/* Read current value of the config 2 register */
		apm_enet_read(priv, BLOCK_MCX_MAC, MAC_CONFIG_2_ADDR, &data);

		/* Modify value to set or reset huge frame enable bit */
		if (enable)
			data |= HUGE_FRAME_EN2_MASK;
		else
			data &= ~HUGE_FRAME_EN2_MASK;

		/* Write value back to config 2 register */
		apm_enet_write(priv, BLOCK_MCX_MAC, MAC_CONFIG_2_ADDR, data);
	}
}

void apm_xgmac_len_field_check_enable(struct apm_data_priv *priv, u8 enable)
{
	u32 data;

	if (priv->phy_mode == PHY_MODE_SGMII) {
		/* Read current value of the config 2 register */
		apm_enet_read(priv, BLOCK_MCX_MAC, MAC_CONFIG_2_ADDR, &data);

		/* Modify value to set or reset length field check enable bit */
		if (enable)
			data |= LENGTH_CHECK2_MASK;
		else
			data &= ~LENGTH_CHECK2_MASK;

		/* Write value back to config 2 register */
		apm_enet_write(priv, BLOCK_MCX_MAC, MAC_CONFIG_2_ADDR, data);
	}
}

static void module_xgenet_config_sgmii_autoneg(struct apm_data_priv *priv, int autoneg)
{
	u32 data, speed, times = 0;

	/*
	 * All internal PHY addresses are shifted by 2 bits
	 */
reset_phy:
	ENET_DEBUG("%s autoneg=%d\n", __func__, autoneg);
        apm_genericmiiphy_write(priv, INT_PHY_ADDR,
		SGMII_TBI_CONTROL_ADDR >> 2, 0x0);
	apm_genericmiiphy_read(priv, INT_PHY_ADDR,
        	SGMII_TBI_CONTROL_ADDR >> 2, &data);
	if (!priv->mac_to_mac) {
		if (autoneg) {
			/* Bring PHY out of reset; Enable An, autonegotiation */
			PHY_PRINT(" Bring PHY out of reset; Enable An\n");
			apm_genericmiiphy_write(priv, INT_PHY_ADDR,
						SGMII_CONTROL_ADDR >> 2, 0x9140);
		}
		else {
			/* Bring PHY out of reset; No autonegotiation */
			PHY_PRINT(" Bring PHY out of reset; NO An\n");
			apm_genericmiiphy_write(priv, INT_PHY_ADDR,
						SGMII_CONTROL_ADDR >> 2, 0x8000);
		}
		udelay(1000);
		if (autoneg) {
			int loop = 50;

			/* Check autonegotiation status */
			apm_genericmiiphy_read(priv, INT_PHY_ADDR,
					SGMII_STATUS_ADDR >> 2, &data);
			PHY_PRINT(" autonegotiation status=0x%x\n", data);
			while  (AUTO_NEGOTIATION_COMPLETE_RD(data) == 0 ||
				LINK_STATUS_RD(data) == 0) {
				PHY_PRINT(" Autonegotiation status=0x%x\n", data);
				apm_genericmiiphy_read(priv, INT_PHY_ADDR,
						SGMII_STATUS_ADDR >> 2, &data);
				if (loop-- == 0)
					break;
				udelay(100);
				PHY_PRINT(" Autonegotiation status=0x%x %s\n", data, __func__);
			}
			if (LINK_STATUS_RD(data) == 0) {/*  no link wih SGMII */
				if (times ++ < 5) {
					PHY_PRINT(".");
					apm_genericmiiphy_write(priv, INT_PHY_ADDR,
								SGMII_TBI_CONTROL_ADDR >> 2, 0x8000);
					serdes_reset_rxd_rxa(priv, 0);
					goto reset_phy;
				}
			}
		} else {
			PHY_PRINT(" %s non-autoneg NOT supported\n", __func__);
		}
		if (!priv->phyless) {
			apm_enet_read(priv, BLOCK_ETH_CSR, LINK_STATUS_ADDR, &data);
			priv->link_status = PORT_RD(data);
		} else
			priv->link_status = 1;
		/* Get the final speed information from SGMII */
		apm_genericmiiphy_read(priv, INT_PHY_ADDR,
				SGMII_AN_SGMII_PARTNER_BASE_PAGE_ABILITY_ADDR >> 2, &data);
		speed = LINK_SPEED_F1_RD(data);
	} else {
		speed = priv->desired_speed;
		priv->link_status = 1;
	}
	switch(speed) {
	case PHY_SPEED_10:
		speed = SPEED_10;
		break;
	case PHY_SPEED_100:
		speed = SPEED_100;
		break;
	default:
		speed = SPEED_1000;
		break;
	}
	if (priv->link_status)
		PHY_PRINT("Phy Speed is :%d \n", speed);
	else 
		PHY_PRINT("Port%d is down\n", priv->port);

	priv->speed = speed;
}

int apm_mcxmac_init(struct apm_data_priv *priv,
		unsigned char *dev_addr, int speed, int mtu, int crc)
{
	u32 value;
	u32 temp;
	u32 addr_hi;
	u32 addr_lo;

	u32 interface_control;
	u32 mac_config_2;
	u32 icm_config0 = 0x0008503f;
#if !defined(CONFIG_APM862xx)
	u32 ecm_config0 = 0x00000032;
#endif
	u32 enet_spare_cfg = 0x00006040;
	/*u8 port = priv->port; */

	ENET_DEBUG("%s priv->phy_mode=0x%x\n", __func__, priv->phy_mode);


	/*sm_xgenet_module_level_eee_init(priv); */
#if 0
	if (priv->phy_mode == PHY_MODE_XGMII) {
		/* Program the station MAC address */
		addr_hi = *(u32 *) &dev_addr[0];
		addr_lo = *(u16 *) &dev_addr[4];
		addr_lo <<= 16;
                addr_lo |= (priv->phy_addr & 0xFFFF);
		ENET_DEBUG("MAC addr hi: %x\n", addr_hi);
		apm_enet_write(priv, BLOCK_AXG_MAC, AXGMAC_HSTMACADR_MSW_ADDR, addr_hi);
		ENET_DEBUG("MAC addr lo: %x\n", addr_lo);
		apm_enet_write(priv, BLOCK_AXG_MAC, AXGMAC_HSTMACADR_LSW_ADDR, addr_lo);
		return 0;
	}
#endif
	value = RESET_TX_FUN1_WR(1) |
		RESET_RX_FUN1_WR(1) |
		RESET_TX_MC1_WR(1)  |
		RESET_RX_MC1_WR(1)  |
		SIM_RESET1_WR(1)    |
		SOFT_RESET1_WR(1);
	apm_enet_write(priv, BLOCK_MCX_MAC, MAC_CONFIG_1_ADDR, value);
	apm_enet_read(priv, BLOCK_MCX_MAC, MAC_CONFIG_1_ADDR, &temp);
	udelay(1);
	apm_enet_write(priv, BLOCK_MCX_MAC, MAC_CONFIG_1_ADDR, 0);

	/* Initialize the MAC configuration #1 register */
	value = TX_EN1_WR(1)	  |
		TX_FLOW_EN1_WR(0) |
#ifdef APM_ENET_MAC_LOOPBACK
		LOOP_BACK1_WR(1)  |
#else
		LOOP_BACK1_WR(0)  |
#endif
		RX_FLOW_EN1_WR(0);

	/* Need this? rd_phy_reg_per_port(port_id,0x1e,M_SGMII_SGMII_TBI_CONTROL__ADDR,&data); */

	apm_enet_write(priv, BLOCK_MCX_MAC, MAC_CONFIG_1_ADDR, value);

#ifndef APM_ENET_MAC_LOOPBACK
#ifdef APM_ENET_SERDES_LOOPBACK
	module_xgenet_config_sgmii_autoneg(priv, 0);
#else
	if (!priv->mac_to_mac) {
		if (!priv->autoneg_set) {
			module_xgenet_config_sgmii_autoneg(priv, 1);
			priv->autoneg_set = 1;
		}
		speed = priv->speed;
	} else {
		module_xgenet_config_sgmii_autoneg(priv, 0);
	}
#endif
#endif
	/* SGMII follows */
	apm_enet_read(priv, BLOCK_ETH_CSR,
			ENET_SPARE_CFG_REG_ADDR, &enet_spare_cfg);

	if (speed == SPEED_10) {
		interface_control = ENET_LHD_MODE_WR(0) |
			ENET_GHD_MODE_WR(0);
		mac_config_2 = FULL_DUPLEX2_WR(1)  |
			LENGTH_CHECK2_WR(0)        |
			HUGE_FRAME_EN2_WR(0)       |
			ENET_INTERFACE_MODE2_WR(1)      | /* 10Mbps */
			PAD_CRC2_WR(crc)           |
			CRC_EN2_WR(crc)            |
			PREAMBLE_LENGTH2_WR(7);
		icm_config0 = 0x0000503f;
#if !defined(CONFIG_APM862xx)
		ecm_config0 = 0x600032;
#endif
#if defined(CONFIG_APM862xx)
		if (port == 0)
			enet_spare_cfg = enet_spare_cfg | (0x0000c040);
		else
			enet_spare_cfg = enet_spare_cfg | (0x00030040);
#endif
	} else if (speed == SPEED_100) {
		interface_control = ENET_LHD_MODE_WR(1);
		mac_config_2 = FULL_DUPLEX2_WR(1)  |
			LENGTH_CHECK2_WR(0)        |
			HUGE_FRAME_EN2_WR(0)       |
			ENET_INTERFACE_MODE2_WR(1)      | /* 100Mbps */
			PAD_CRC2_WR(crc)           |
			CRC_EN2_WR(crc)            |
			PREAMBLE_LENGTH2_WR(7);
		icm_config0 = 0x0004503f;
#if !defined(CONFIG_APM862xx)
		ecm_config0 = 0x600032;
#endif
#if defined(CONFIG_APM862xx)
		if (port == 0)
			enet_spare_cfg = enet_spare_cfg | (0x0000c040);
		else
			enet_spare_cfg = enet_spare_cfg | (0x00030040);
#endif
	} else {
		interface_control = ENET_GHD_MODE_WR(1);
		mac_config_2 = FULL_DUPLEX2_WR(1)  |
			LENGTH_CHECK2_WR(0)        |
			HUGE_FRAME_EN2_WR(0)       |
			ENET_INTERFACE_MODE2_WR(2)      | /* 1Gbps */
			PAD_CRC2_WR(crc)           |
			CRC_EN2_WR(crc)            |
			PREAMBLE_LENGTH2_WR(7);

		icm_config0 = 0x0008503f;
#if !defined(CONFIG_APM862xx)
		ecm_config0 = 0x32;
#endif
#if defined(CONFIG_APM862xx)
		if (port == 0)
			enet_spare_cfg = (enet_spare_cfg & ~0x0000c000) | (0x00000040);
		else
			enet_spare_cfg = (enet_spare_cfg & ~0x00030000) | (0x00000040);
#endif
	}
#if !defined(CONFIG_APM862xx)
	enet_spare_cfg |= 0x00006040;
#endif
	/* Initialize the MAC configuration #2 register */
	apm_enet_write(priv, BLOCK_MCX_MAC, MAC_CONFIG_2_ADDR, mac_config_2);

	/* Initialize the Interface Control Register */
	//interface_control = 0x74521808;
	apm_enet_write(priv, BLOCK_MCX_MAC, INTERFACE_CONTROL_ADDR,
			interface_control);

	/* Initialize the Maximum Frame Length register */
	//value = 0x56c92580; //MAX_FRAME_LEN_WR(mtu);
	value = MAX_FRAME_LEN_WR(0x0600);
	apm_enet_write(priv, BLOCK_MCX_MAC, MAX_FRAME_LEN_ADDR, value);

	/* Program the station MAC address */
	addr_hi = *(u32 *) &dev_addr[0];
	addr_lo = *(u16 *) &dev_addr[4];
	addr_lo <<= 16;

        if (priv->phy_mode == PHY_MODE_SGMII)
                addr_lo = (addr_lo & 0xFFFF0100) | 0x1e;
        else
                addr_lo |= (priv->phy_addr & 0xFFFF);

	ENET_DEBUG("MAC addr hi: %x\n", addr_hi);
	apm_enet_write(priv, BLOCK_MCX_MAC, STATION_ADDR0_ADDR, addr_hi);
	ENET_DEBUG("MAC addr lo: %x\n", addr_lo);
	apm_enet_write(priv, BLOCK_MCX_MAC, STATION_ADDR1_ADDR, addr_lo);

	/* Rtype should be copied from FP */
	value = 0;
	apm_enet_write(priv, BLOCK_ETH_CSR,
			RSIF_RAM_DBG_REG0_ADDR, value);

	apm_enet_write(priv, BLOCK_MCX_MAC_CSR,
			ICM_CONFIG0_REG_0_ADDR, icm_config0);

#if !defined(CONFIG_APM862xx)
	apm_enet_write(priv, BLOCK_MCX_MAC_CSR,
			ECM_CONFIG0_REG_0_ADDR, ecm_config0);
#endif
#if 0	/* Storm apm_xg_bypass_resume_cfg */
	apm_enet_write(priv, BLOCK_ETH_CSR,
			ENET_SPARE_CFG_REG_ADDR, enet_spare_cfg);
#endif

	/* TCP MSS  */
	apm_enet_read(priv, BLOCK_ETH_CSR,
			TSIF_MSS_REG0_0_ADDR, &value);

	apm_enet_write(priv, BLOCK_ETH_CSR, TSIF_MSS_REG0_0_ADDR,
			CFG_TSIF_MSS_SZ00_SET(value, DEFAULT_TCP_MSS));

	apm_enet_read(priv, BLOCK_ETH_CSR,
			TSIF_MSS_REG0_0_ADDR, &value);

	/* Rx-Tx traffic resume, apm_xg_bypass_resume_cfg*/
	//apm_enet_write(priv, BLOCK_ETH_CSR,
	//		CFG_LINK_AGGR_RESUME_0_ADDR, TX_PORT0_WR(0x1));

	if (speed != SPEED_10 && speed != SPEED_100) {
		apm_enet_read(priv, BLOCK_ETH_CSR, DEBUG_REG_ADDR, &value);
		value |= CFG_BYPASS_UNISEC_TX_WR(1) |
				CFG_BYPASS_UNISEC_RX_WR(1);
		apm_enet_write(priv, BLOCK_ETH_CSR, DEBUG_REG_ADDR, value);
	}
	apm_enet_read(priv, BLOCK_MCX_STATS, TBYT_ADDR, &value);
	ENET_DEBUG("XG MCX TBYT register: %x\n", value);
	apm_enet_read(priv, BLOCK_MCX_STATS, RBYT_ADDR, &value);
	ENET_DEBUG("XG MCX RBYT register: %x\n", value);
#if 0
	udelay(1000);
	apm_enet_read(priv, BLOCK_MCX_STATS, RFCS_ADDR, &value);
	if (value) {
		module_xgenet_config_sgmii_autoneg(priv, 1);
		ENET_PRINT("RFCS serdes reset\n");

	}
#endif
	return 0;
}
#endif

// Serdes initialization
void
apm_xg_serdes_init( struct apm_data_priv *priv )
{
    apm_xgenet_serdes_init(priv);
}

// Configure Management Ethernet (ETH4)
// clock enable and deassert reset
// FIXME: this might be called by ENET as well
void
apm_xg_cfg_mgnt_enet( struct apm_data_priv *priv )
{
    // TODO:
    // these addresses belong to ENET4, find a better way to do this

    // write ENET4->CLKEN = 0x3
    // udelay(1);
    // write ENET4->SRST = 0x0
    // udelay(1);
}


//------------------------------
// Clock, reset configuration
// - select 10/100/1G/10G mode
// - enable csr and xgenet clock
// - deassert csr, xgenet reset
// - wake up ram
void
apm_xg_clk_rst_cfg( struct apm_data_priv *priv )
{
    u32 wrdata;
    ENET_DEBUG ("XG CLK_RST configuration\n");

    apm_xg_select_mode( priv );
	
	// assert resets to clear SDS power down
	wrdata = XGENET_RESET_WR(1) | CSR_RESET_WR(1) | XGENET_SDS_RESET_WR(1);
	apm_enet_write( priv, BLOCK_ETH_CLKRST_CSR, XGENET_SRST_ADDR, wrdata );
    	udelay(10);

	apm_enet_write( priv, BLOCK_ETH_CLKRST_CSR, XGENET_CLKEN_ADDR, 0x1f );
	udelay(1000);
	apm_enet_write( priv, BLOCK_ETH_CLKRST_CSR, XGENET_CLKEN_ADDR, 0 );
	udelay(100);

    // enable all clocks
    wrdata = CSR_CLKEN_WR(1)
	| XGENET_CLKEN_WR(1);
    apm_enet_write( priv, BLOCK_ETH_CLKRST_CSR, XGENET_CLKEN_ADDR, wrdata );
    udelay(10);

    // release sds reset
    wrdata = XGENET_RESET_WR(1) | CSR_RESET_WR(1) | XGENET_SDS_RESET_WR(0);
    apm_enet_write( priv, BLOCK_ETH_CLKRST_CSR, XGENET_SRST_ADDR, wrdata );
    udelay(10);

    // release csr and sds reset
    wrdata = XGENET_RESET_WR(1) | CSR_RESET_WR(0) | XGENET_SDS_RESET_WR(0);
    apm_enet_write( priv, BLOCK_ETH_CLKRST_CSR, XGENET_SRST_ADDR, wrdata );
    udelay(10);

    apm_xg_loopback_cfg( priv );

    // TODO: move this outside this function
    // serdes init
    //apm_xg_serdes_init( priv );

    // release core, csr and sds reset
    wrdata = XGENET_RESET_WR(0) | CSR_RESET_WR(0) | XGENET_SDS_RESET_WR(0);
    apm_enet_write( priv, BLOCK_ETH_CLKRST_CSR, XGENET_SRST_ADDR, wrdata );
    udelay(10);

    apm_xg_init_ecc( priv );
}

void apm_xgmac_reset(struct apm_data_priv *priv)
{
	u32 data;

	if (priv->phy_mode == PHY_MODE_XGMII) {
		ENET_DEBUG ("XG reset AXGMAC\n");

		//apm_enet_read( priv, BLOCK_AXG_MAC, AXGMAC_CONFIG_0_ADDR, &data );
		//data |= HSTMACRST0_WR(1);  // This bit will reset the entire AXGMAC
		data = 0xe601;
		apm_enet_write(priv, BLOCK_AXG_MAC, AXGMAC_CONFIG_0_ADDR, data);
		udelay(1);

		ENET_DEBUG ("XG deassert AXGMAC reset\n");
		data = 0x0;
		apm_enet_write(priv, BLOCK_AXG_MAC, AXGMAC_CONFIG_0_ADDR, data);
		udelay(5);
	} else {
		data = (RESET_RX_MC1_MASK   |
			RESET_RX_FUN1_MASK  |
			RESET_TX_MC1_MASK   |
			RESET_TX_FUN1_MASK  |
			SIM_RESET1_MASK     |
			SOFT_RESET1_MASK);

		/* Write value back to config 1 register */
		apm_enet_write(priv, BLOCK_MCX_MAC, MAC_CONFIG_1_ADDR, data);
	}
}

//------------------------------
// AXGMAC (10G only mode) initialization
// TODO: add support for 1G mode
// - deassert reset
// - configure AXGMAC
// - set MAXFRAME length
int apm_axgmac_init (struct apm_data_priv *priv,
		unsigned char *dev_addr, int speed, int mtu, int crc)
{
    u32 wrdata, data;
    u32 addr_hi, addr_lo;

    ENET_DEBUG("XG Initialize XG MAC\n");

    apm_xgmac_reset(priv);

    ENET_DEBUG ("XG configure AXGMAC\n");
    //data |= 0xf000008d;
    data = (HSTTCTLEN1_WR(1)
	    | HSTTFEN1_WR(1)
	    | HSTRCTLEN1_WR(1)
	    | HSTRFEN1_WR(1)
#if !defined(BOOTLOADER)
	    | HSTPPEN1_WR(1)
#endif
	    | HSTLENCHK1_WR(1));
   if (crc)
	data |= (HSTGENFCS1_WR(1)
	    | REGSPEC_HSTPADMODE1_WR(1));
    data = HSTDRPLT641_SET(data, 0);
    ENET_DEBUG ("XG AXGMAC config_1: %x\n", data);

    apm_enet_write( priv, BLOCK_AXG_MAC, AXGMAC_CONFIG_1_ADDR, data );
    udelay(1);

    /*
    data = 0x25800600;
    apm_enet_write( priv, BLOCK_AXG_MAC, AXGMAC_MAXFRAME_LENGTH_ADDR, data );
    */

    wrdata = HSTMXFRMWCTX_WR(0x2580)
	| HSTMXFRMBCRX_WR(0x0600);
    apm_enet_write( priv, BLOCK_AXG_MAC, AXGMAC_MAXFRAME_LENGTH_ADDR, wrdata );
    apm_enet_read( priv, BLOCK_AXG_MAC, AXGMAC_MAXFRAME_LENGTH_ADDR, &data );
    ENET_DEBUG ("XG AXGMAC maxframe length: %x\n", data);

    addr_hi = *(u32 *) &dev_addr[0];
    addr_lo = *(u16 *) &dev_addr[4];
    ENET_DEBUG ("XG devaddr: %s\n", dev_addr);
    addr_lo <<= 16;
    apm_enet_write( priv, BLOCK_AXG_MAC, AXGMAC_HSTMACADR_LSW_ADDR, addr_hi );
    apm_enet_write( priv, BLOCK_AXG_MAC, AXGMAC_HSTMACADR_MSW_ADDR, addr_lo );

    apm_enet_read( priv, BLOCK_AXG_STATS, TBYT_ADDR, &data );
    ENET_DEBUG("XG TBYT register: %x\n", data);
    apm_enet_read( priv, BLOCK_AXG_STATS, RBYT_ADDR, &data );
    ENET_DEBUG("XG RBYT register: %x\n", data);

    return 0;
}


void
apm_xg_bypass_resume_cfg( struct apm_data_priv *priv )
{
    u32 wrdata;
    ENET_DEBUG ("XG bypass resume configuration\n");

    wrdata = RESUME_TX_WR(1);
    apm_enet_write( priv, BLOCK_ETH_CSR, CFG_BYPASS_ADDR, wrdata);

 	if (priv->phy_mode == PHY_MODE_SGMII)
		wrdata = 0x1;
	else
		wrdata = 0x0;
    apm_enet_write( priv, BLOCK_ETH_CSR, CFG_LINK_STS_ADDR, wrdata);

    wrdata = TX_PORT0_WR(1);
    apm_enet_write( priv, BLOCK_ETH_CSR, CFG_LINK_AGGR_RESUME_0_ADDR, wrdata);

    //wrdata = ENET_MPA_IDLE_WITH_QMI_EMPTY_WR(1);
    wrdata = 0x22407040;
    apm_enet_write( priv, BLOCK_ETH_CSR, ENET_SPARE_CFG_REG_ADDR, wrdata);

 	if (priv->phy_mode == PHY_MODE_SGMII) {
		apm_enet_read(priv, BLOCK_MCX_MAC_CSR, RX_DV_GATE_REG_0_ADDR, &wrdata);
		wrdata = TX_DV_GATE_EN0_F2_SET(wrdata, 0);
		wrdata = RX_DV_GATE_EN0_F2_SET(wrdata, 0);
		wrdata = RESUME_RX0_F2_SET(wrdata, 1);
		ENET_DEBUG ("%s XGENET_RX_DV_GATE_REG_0_ADDR=0x%x\n", __func__,wrdata);
		apm_enet_write(priv, BLOCK_MCX_MAC_CSR,
			RX_DV_GATE_REG_0_ADDR, wrdata);

	} else
		apm_enet_write(priv, BLOCK_AXG_MAC_CSR,
			XGENET_RX_DV_GATE_REG_0_ADDR, 0);
}


// 10GBaseR TX to RX loopback
void
apm_xg_loopback_cfg( struct apm_data_priv *priv )
{
#ifdef APM_XG_AXGMAC_TX2RX_LOOPBACK
    u32 wrdata;
    ENET_DEBUG ("XG loopback (TX to RX) configuration\n");

    wrdata = CFG_XGBASER_TX2RX_LOOPBACK1_WR(1);
    apm_enet_write( priv, BLOCK_XGENET_PCS , XGBASER_CONFIG_REG1_ADDR, wrdata );

#endif

#ifdef APM_XGENET_XGMII_TX2RX_LOOPBACK
    u32 wrdata;
    ENET_DEBUG ("XG XGMII loopback (TX to RX) configuration\n");

    wrdata = CFG_I_TX_SER_LPBK0_WR(1);
    apm_enet_write( priv, BLOCK_ETH_SDS_CSR , XGENET_SDS_CTL0_ADDR, wrdata );
#endif
}

void
apm_xg_cle_bypass_mode_cfg(struct apm_data_priv *priv, u32 cle_dstqid, u32 cle_fpsel)
{
    u32 data;

    // TODO: code from validation team
    // verify these values

    ENET_DEBUG("XG Bypass CLE\n");
#if 0
    data = (CFG_CLE_BYPASS_EN0_WR(1) | CFG_CLE_RESULT_DLYCNTR0_WR(0x08));
    apm_enet_write(priv, BLOCK_ETH_CSR, CLE_BYPASS_REG0_ADDR, data);

    //data = CFG_CLE_DSTQID1_WR(0x3 | 0x1 << 10);
    data = CFG_CLE_DSTQID1_WR(cle_dstqid);
    apm_enet_write(priv, BLOCK_ETH_CSR, CLE_BYPASS_REG1_ADDR, data);
#endif

    apm_enet_write(priv, BLOCK_ETH_CSR, CLE_BYPASS_REG0_ADDR, 0x88000000);
    data = CFG_CLE_DSTQID1_WR(cle_dstqid);
    apm_enet_write(priv, BLOCK_ETH_CSR, CLE_BYPASS_REG1_ADDR, data);
    apm_enet_write(priv, BLOCK_ETH_CSR, CLE_BYPASS_REG6_ADDR, 0x00101000);
    apm_enet_write(priv, BLOCK_ETH_CSR, CLE_BYPASS_REG8_ADDR, 0x0c000000);
  
  // cfg to enable capture of Rx cntrl wd's
    apm_enet_write(priv, BLOCK_ETH_CSR, PCKWD_REG0_ADDR, 0x0003870c);
    udelay(1);
    apm_enet_write(priv, BLOCK_ETH_CSR, PCKWD_REG0_ADDR, 0x21010000);
}

//--------------------------------------------------
// Helper functions that are called within this file
//--------------------------------------------------

//------------------------------------
// mode select XGMII(default) or SGMII
void
apm_xg_select_mode( struct apm_data_priv *priv )
{
	if (priv->phy_mode == PHY_MODE_SGMII) {
		apm_enet_write(priv, BLOCK_ETH_CLKRST_CSR, XGENET_CONFIG_REG_ADDR, 0x1);
	} else {
		// XGMII mode, CLE clock same as AXI clock, 250 MHz
		apm_enet_write(priv, BLOCK_ETH_CLKRST_CSR, XGENET_CONFIG_REG_ADDR, 0x02);
		apm_enet_write(priv, BLOCK_ETH_CLKRST_CSR, XGENET_CONFIG_REG_ADDR, 0x12);
	}
}


//------------------------------
// Wake up ram
void
apm_xg_init_ecc( struct apm_data_priv *priv )
{
    u32 wrdata, rddata;
    int i;

    ENET_DEBUG ("XG Waking up RAM\n");

    //wrdata = REGSPEC_CFG_RAM_SHUTDOWN_EN_WR(0);
    wrdata = 0;
    apm_enet_write( priv, BLOCK_ETH_DIAG_CSR, REGSPEC_CFG_MEM_RAM_SHUTDOWN_ADDR, wrdata);

    apm_enet_read( priv, BLOCK_ETH_DIAG_CSR, REGSPEC_BLOCK_MEM_RDY_ADDR, &rddata);
    while (REGSPEC_MEM_RDY_RD(rddata) != REGSPEC_BLOCK_MEM_RDY_DEFAULT)
    //while (REGSPEC_MEM_RDY_RD(rddata) == REGSPEC_BLOCK_MEM_RDY_DEFAULT)
    {
       	apm_enet_read( priv, BLOCK_ETH_DIAG_CSR, REGSPEC_BLOCK_MEM_RDY_ADDR, &rddata);
    }

    for (i=0 ; i < 5 ; i++)
    {
       	apm_enet_read( priv, BLOCK_ETH_DIAG_CSR, REGSPEC_BLOCK_MEM_RDY_ADDR, &rddata);
    }
}

/* Start Statistics related functions */
void apm_xgmac_get_brief_stats(struct apm_data_priv *priv,
				struct eth_brief_stats *brief_stats)
{
	struct eth_detailed_stats detailed_stats;

	apm_xgmac_get_detailed_stats(priv, &detailed_stats);

	brief_stats->rx_byte_count = detailed_stats.rx_stats.rx_byte_count;
	brief_stats->rx_packet_count = detailed_stats.rx_stats.rx_packet_count;
	brief_stats->rx_drop_pkt_count =
		detailed_stats.rx_stats.rx_drop_pkt_count;
	brief_stats->tx_byte_count = detailed_stats.tx_stats.tx_byte_count;
	brief_stats->tx_pkt_count = detailed_stats.tx_stats.tx_pkt_count;
	brief_stats->tx_drop_frm_count =
		detailed_stats.tx_stats.tx_drop_frm_count;
}

void apm_xgmac_get_detailed_stats(struct apm_data_priv *priv,
					struct eth_detailed_stats *stats)
{
	apm_xgmac_get_tx_rx_stats(priv, &(stats->eth_combined_stats));
	apm_xgmac_get_rx_stats(priv, &(stats->rx_stats));
	apm_xgmac_get_tx_stats(priv, &(stats->tx_stats));
}

void apm_xgmac_get_tx_rx_stats(struct apm_data_priv *priv,
					struct eth_frame_stats *tx_rx_stats)
{
	u32 block_mac_stats;

	if (priv->phy_mode == PHY_MODE_XGMII)
		block_mac_stats = BLOCK_AXG_STATS;
	else
		block_mac_stats = BLOCK_MCX_STATS;

	/* Read Stats */
	apm_enet_read(priv, block_mac_stats, TR64_ADDR,
				 &tx_rx_stats->c_64B_frames);
	apm_enet_read(priv, block_mac_stats, TR127_ADDR,
				 &tx_rx_stats->c_65_127B_frames);
	apm_enet_read(priv, block_mac_stats, TR255_ADDR,
				 &tx_rx_stats->c_128_255B_frames);
	apm_enet_read(priv, block_mac_stats, TR511_ADDR,
				 &tx_rx_stats->c_256_511B_frames);
	apm_enet_read(priv, block_mac_stats, TR1K_ADDR,
				 &tx_rx_stats->c_512_1023B_frames);
	apm_enet_read(priv, block_mac_stats, TRMAX_ADDR,
				 &tx_rx_stats->c_1024_1518B_frames);
	apm_enet_read(priv, block_mac_stats, TRMGV_ADDR,
				 &tx_rx_stats->c_1519_1522B_frames);

	/* Mask out unnecessary bits in all the fields */
	tx_rx_stats->c_64B_frames &= TX_RX_64B_FRAME_CNTR4_MASK;
	tx_rx_stats->c_65_127B_frames &= TX_RX_127B_FRAME_CNTR7_MASK;
	tx_rx_stats->c_128_255B_frames &= TX_RX_255B_FRAME_CNTR5_MASK;
	tx_rx_stats->c_256_511B_frames &= TX_RX_511B_FRAME_CNTR1_MASK;
	tx_rx_stats->c_512_1023B_frames &= TX_RX_1KB_FRAME_CNTR_MASK;
	tx_rx_stats->c_1024_1518B_frames &= TX_RX_MAXB_FRAME_CNTR_MASK;
	tx_rx_stats->c_1519_1522B_frames &= TRMGV_MASK;
}

void apm_xgmac_get_rx_stats(struct apm_data_priv *priv, struct eth_rx_stat *rx_stat)
{
	u32 block_mac_stats;

	if (priv->phy_mode == PHY_MODE_XGMII)
		block_mac_stats = BLOCK_AXG_STATS;
	else
		block_mac_stats = BLOCK_MCX_STATS;

	/* Read Stats */
	apm_enet_read(priv, block_mac_stats, RBYT_ADDR,
				 &rx_stat->rx_byte_count);
	apm_enet_read(priv, block_mac_stats, RPKT_ADDR,
				 &rx_stat->rx_packet_count);
	apm_enet_read(priv, block_mac_stats, RFCS_ADDR,
				 &rx_stat->rx_fcs_err_count);
	apm_enet_read(priv, block_mac_stats, RMCA_ADDR,
				 &rx_stat->rx_multicast_pkt_count);
	apm_enet_read(priv, block_mac_stats, RBCA_ADDR,
				 &rx_stat->rx_broadcast_pkt_count);
	apm_enet_read(priv, block_mac_stats, RXCF_ADDR,
				 &rx_stat->rx_cntrl_frame_pkt_count);
	apm_enet_read(priv, block_mac_stats, RXPF_ADDR,
				 &rx_stat->rx_pause_frame_pkt_count);
	apm_enet_read(priv, block_mac_stats, RXUO_ADDR,
				 &rx_stat->rx_unknown_op_pkt_count);
	apm_enet_read(priv, block_mac_stats, RALN_ADDR,
				 &rx_stat->rx_alignment_err_pkt_count);
	apm_enet_read(priv, block_mac_stats, RFLR_ADDR,
				 &rx_stat->rx_frm_len_err_pkt_count);
	apm_enet_read(priv, block_mac_stats, RCDE_ADDR,
				 &rx_stat->rx_code_err_pkt_count);
	apm_enet_read(priv, block_mac_stats, RCSE_ADDR,
				 &rx_stat->rx_carrier_sense_err_pkt_count);
	apm_enet_read(priv, block_mac_stats, RUND_ADDR,
				 &rx_stat->rx_undersize_pkt_count);
	apm_enet_read(priv, block_mac_stats, ROVR_ADDR,
				 &rx_stat->rx_oversize_pkt_count);
	apm_enet_read(priv, block_mac_stats, RFRG_ADDR,
				 &rx_stat->rx_fragment_count);
	apm_enet_read(priv, block_mac_stats, RJBR_ADDR,
				 &rx_stat->rx_jabber_count);
	apm_enet_read(priv, block_mac_stats, RDRP_ADDR,
				 &rx_stat->rx_drop_pkt_count);

	/* Mask out unnecessary bits in all the fields */
	rx_stat->rx_byte_count &= RX_BYTE_CNTR_MASK;
	rx_stat->rx_packet_count &= RX_PKT_CNTR_MASK;
	rx_stat->rx_fcs_err_count &= RX_FCS_ERROR_CNTR_MASK;
	rx_stat->rx_multicast_pkt_count &= RX_MC_PKT_CNTR_MASK;
	rx_stat->rx_broadcast_pkt_count &= RX_BC_PKT_CNTR_MASK;
	rx_stat->rx_cntrl_frame_pkt_count &= RX_CTRL_PKT_CNTR_MASK;
	rx_stat->rx_pause_frame_pkt_count &= RX_PAUSE_PKT_CNTR_MASK;
	rx_stat->rx_unknown_op_pkt_count &= RX_UNK_OPCODE_CNTR_MASK;
	rx_stat->rx_alignment_err_pkt_count &= RX_ALIGN_ERR_CNTR_MASK;
	rx_stat->rx_frm_len_err_pkt_count &= RX_LEN_ERR_CNTR_MASK;
	rx_stat->rx_code_err_pkt_count &= RX_CODE_ERR_CNTR_MASK;
	rx_stat->rx_carrier_sense_err_pkt_count &= RX_FALSE_CARRIER_CNTR_MASK;
	rx_stat->rx_undersize_pkt_count &= RX_UNDRSIZE_PKT_CNTR_MASK;
	rx_stat->rx_oversize_pkt_count &= RX_OVRSIZE_PKT_CNTR_MASK;
	rx_stat->rx_fragment_count &= RX_FRAG_CNTR_MASK;
	rx_stat->rx_jabber_count &= RX_JABBER_CNTR_MASK;
	rx_stat->rx_drop_pkt_count &= RX_DROPPED_PKT_CNTR_MASK;
}

void apm_xgmac_get_tx_stats(struct apm_data_priv *priv,
			struct eth_tx_stats *tx_stats)
{
	u32 block_mac_stats;

	if (priv->phy_mode == PHY_MODE_XGMII)
		block_mac_stats = BLOCK_AXG_STATS;
	else
		block_mac_stats = BLOCK_MCX_STATS;

	/* Read Stats */
	apm_enet_read(priv, block_mac_stats, TBYT_ADDR,
				 &tx_stats->tx_byte_count);
	apm_enet_read(priv, block_mac_stats, TPKT_ADDR,
				 &tx_stats->tx_pkt_count);
	apm_enet_read(priv, block_mac_stats, TMCA_ADDR,
				 &tx_stats->tx_multicast_pkt_count);
	apm_enet_read(priv, block_mac_stats, TBCA_ADDR,
				 &tx_stats->tx_broadcast_pkt_count);
	apm_enet_read(priv, block_mac_stats, TXPF_ADDR,
				 &tx_stats->tx_pause_frame_count);
	apm_enet_read(priv, block_mac_stats, TDFR_ADDR,
				 &tx_stats->tx_deferral_pkt_count);
	apm_enet_read(priv, block_mac_stats, TEDF_ADDR,
				 &tx_stats->tx_exesiv_def_pkt_count);
	apm_enet_read(priv, block_mac_stats, TSCL_ADDR,
				 &tx_stats->tx_single_coll_pkt_count);
	apm_enet_read(priv, block_mac_stats, TMCL_ADDR,
				 &tx_stats->tx_multi_coll_pkt_count);
	apm_enet_read(priv, block_mac_stats, TLCL_ADDR,
				 &tx_stats->tx_late_coll_pkt_count);
	apm_enet_read(priv, block_mac_stats, TXCL_ADDR,
				 &tx_stats->tx_exesiv_coll_pkt_count);
	apm_enet_read(priv, block_mac_stats, TNCL_ADDR,
				 &tx_stats->tx_toll_coll_pkt_count);
	apm_enet_read(priv, block_mac_stats, TPFH_ADDR,
				 &tx_stats->tx_pause_frm_hon_count);
	apm_enet_read(priv, block_mac_stats, TDRP_ADDR,
				 &tx_stats->tx_drop_frm_count);
	apm_enet_read(priv, block_mac_stats, TJBR_ADDR,
				 &tx_stats->tx_jabber_frm_count);
	apm_enet_read(priv, block_mac_stats, TFCS_ADDR,
				 &tx_stats->tx_fcs_err_frm_count);
	apm_enet_read(priv, block_mac_stats, TXCF_ADDR,
				 &tx_stats->tx_control_frm_count);
	apm_enet_read(priv, block_mac_stats, TOVR_ADDR,
				 &tx_stats->tx_oversize_frm_count);
	apm_enet_read(priv, block_mac_stats, TUND_ADDR,
				 &tx_stats->tx_undersize_frm_count);
	apm_enet_read(priv, block_mac_stats, TFRG_ADDR,
				 &tx_stats->tx_fragments_frm_count);

	/* Mask values with appropriate width of the fields */
	tx_stats->tx_byte_count &= TX_BYTE_CNTR_MASK;
	tx_stats->tx_pkt_count &= TX_PKT_CNTR_MASK;
	tx_stats->tx_multicast_pkt_count &= TX_MC_PKT_CNTR_MASK;
	tx_stats->tx_broadcast_pkt_count &= TX_BC_PKT_CNTR_MASK;
	tx_stats->tx_pause_frame_count &= TX_PAUSE_PKT_CNTR_MASK;
	tx_stats->tx_deferral_pkt_count &= TX_DEFER_PKT_CNTR_MASK;
	tx_stats->tx_exesiv_def_pkt_count &= TX_EXC_DEFER_PKT_CNTR_MASK;
	tx_stats->tx_single_coll_pkt_count &= TX_COL_PKT_CNTR_MASK;
	tx_stats->tx_multi_coll_pkt_count &= TX_MUL_COL_PKT_CNTR_MASK;
	tx_stats->tx_late_coll_pkt_count &= TX_LATE_COL_PKT_CNTR_MASK;
	tx_stats->tx_exesiv_coll_pkt_count &= TX_EXC_COL_PKT_CNTR_MASK;
	tx_stats->tx_toll_coll_pkt_count &= TX_TOTAL_COL_CNTR_MASK;
	tx_stats->tx_pause_frm_hon_count &= TX_PAUSE_FRAME_CNTR_MASK;
	tx_stats->tx_drop_frm_count &= TX_DROP_FRAME_CNTR_MASK;
	tx_stats->tx_jabber_frm_count &= TX_JABBER_FRAME_CNTR_MASK;
	tx_stats->tx_fcs_err_frm_count &= TX_FCS_ERROR_CNTR_MASK;
	tx_stats->tx_control_frm_count &= TX_CTRL_FRAME_CNTR_MASK;
	tx_stats->tx_oversize_frm_count &= TX_OVRSIZE_FRAME_CNTR_MASK;
	tx_stats->tx_undersize_frm_count &= TX_UNDSIZE_FRAME_CNTR_MASK;
	tx_stats->tx_fragments_frm_count &= TX_FRAG_CNTR_MASK;
}

int apm_xgmac_init(struct apm_data_priv *priv,
		unsigned char *dev_addr, int speed, int mtu, int crc)
{
	u32 ret;
	u32 value;

	if (priv->phy_mode == PHY_MODE_XGMII)
		ret = apm_axgmac_init(priv, dev_addr, speed, mtu, crc);
	else
		ret = apm_mcxmac_init(priv, dev_addr, 1000, mtu, crc);

	/* Enable drop if FP not available */
	apm_enet_read(priv, BLOCK_ETH_CSR, RSIF_CONFIG_REG_ADDR, &value);
	value |= CFG_RSIF_FPBUFF_TIMEOUT_EN_WR(1);
	apm_enet_write(priv, BLOCK_ETH_CSR, RSIF_CONFIG_REG_ADDR, value);

	return ret;
}

void apm_xgmac_rx_state(struct apm_data_priv *priv, u32 enable)
{
	if (enable)
		apm_xgmac_rx_enable(priv);
	else
		apm_xgmac_rx_disable(priv);
}

void apm_xgmac_tx_state(struct apm_data_priv *priv, u32 enable)
{
	if (enable)
		apm_xgmac_tx_enable(priv);
	else
		apm_xgmac_tx_disable(priv);
}

void apm_xgmac_set_ipg(struct apm_data_priv *priv, u16 ipg)
{
	u32 data;

	if (priv->phy_mode != PHY_MODE_XGMII) {
		/* Read current value of the IPG IFG register */
		apm_enet_read(priv, BLOCK_MCX_MAC, IPG_IFG_ADDR, &data);

		/* Write value back to IPG IFG register */
		apm_enet_write(priv, BLOCK_MCX_MAC, IPG_IFG_ADDR,
			B2B_IPG_SET(data, ipg));
	}

	ENET_DEBUG("Setting IPG to %d bits", ipg);
}

void apm_xgmac_set_mac_addr(struct apm_data_priv *priv,
			unsigned char *dev_addr)
{
	u32 a_hi;
	u32 a_lo;

	a_hi = *(u32 *) &dev_addr[0];
	a_lo = (u32) *(u16 *) &dev_addr[4];
	a_lo <<= 16;

	if (priv->phy_mode == PHY_MODE_XGMII) {
		apm_enet_write(priv, BLOCK_AXG_MAC, AXGMAC_HSTMACADR_LSW_ADDR, a_hi);
		apm_enet_write(priv, BLOCK_AXG_MAC, AXGMAC_HSTMACADR_MSW_ADDR, a_lo);
	} else {

		/* Write higher 4 octects to station register */
		apm_enet_write(priv, BLOCK_MCX_MAC, STATION_ADDR0_ADDR, a_hi);

		a_lo |= (priv->phy_addr & 0xFFFF);

		/* Write lower 2 octects to station register */
		apm_enet_write(priv, BLOCK_MCX_MAC, STATION_ADDR1_ADDR, a_lo);
	}
}

void apm_xgmac_tx_offload(struct apm_data_priv *priv, u32 command, u32 value)
{
	u32 data;

	switch (command) {
	/* TCP MSS 0 */
	case APM_ENET_MSS0:
		apm_enet_read(priv, BLOCK_ETH_CSR,
			TSIF_MSS_REG0_0_ADDR, &data);
		apm_enet_write(priv, BLOCK_ETH_CSR,
			TSIF_MSS_REG0_0_ADDR,
			CFG_TSIF_MSS_SZ00_SET(data, value));
		break;
	/* TCP MSS 1 */
	case APM_ENET_MSS1:
		apm_enet_read(priv, BLOCK_ETH_CSR,
			TSIF_MSS_REG0_0_ADDR, &data);
		apm_enet_write(priv, BLOCK_ETH_CSR,
			TSIF_MSS_REG0_0_ADDR,
			CFG_TSIF_MSS_SZ10_SET(data, value));
		break;
	/* TCP MSS 2 */
	case APM_ENET_MSS2:
		apm_enet_read(priv, BLOCK_ETH_CSR,
			TSIF_MSS_REG1_0_ADDR, &data);
		apm_enet_write(priv, BLOCK_ETH_CSR,
			TSIF_MSS_REG1_0_ADDR,
			CFG_TSIF_MSS_SZ20_SET(data, value));
		break;
	/* TCP MSS 3 */
	case APM_ENET_MSS3:
		apm_enet_read(priv, BLOCK_ETH_CSR,
			TSIF_MSS_REG1_0_ADDR, &data);
		apm_enet_write(priv, BLOCK_ETH_CSR,
			TSIF_MSS_REG1_0_ADDR,
			CFG_TSIF_MSS_SZ30_SET(data, value));
		break;
	/* Program TSO config */
	case APM_ENET_TSO_CFG:
		apm_enet_write(priv, BLOCK_ETH_CSR, TSO_CFG_0_ADDR, value);
		break;
	/* Insert Inser tVLAN TAG */
	case APM_ENET_INSERT_VLAN:
		apm_enet_write(priv, BLOCK_ETH_CSR,
			TSO_CFG_INSERT_VLAN_0_ADDR, value);
		break;
	}
}

void apm_xgport_reset(struct apm_data_priv *priv, u32 mii_mode)
{
	// Clock reset configuration
	priv->phy_mode = mii_mode;
	apm_xg_clk_rst_cfg(priv);
	apm_xg_serdes_init(priv);
	xgenet_config_qmi_assoc(priv);
	//apm_xgenet_set_phyid(priv);
	apm_xg_bypass_resume_cfg(priv);
}

void apm_xgport_shutdown(struct apm_data_priv *priv)
{
       	u32 val;

	/* reset serdes, csr and xgenet core */
	val = XGENET_RESET_WR(1) | CSR_RESET_WR(1) | XGENET_SDS_RESET_WR(1);
       	apm_enet_write(priv, BLOCK_ETH_CLKRST_CSR, XGENET_SRST_ADDR, val);

	/* disable csr and xgenet clock */
	val = CSR_CLKEN_WR(0) | XGENET_CLKEN_WR(0);
       	apm_enet_write(priv, BLOCK_ETH_CLKRST_CSR, XGENET_CLKEN_ADDR, val);
}

void apm_xgenet_init_priv(struct apm_data_priv *priv, void *port_vaddr, void *gbl_vaddr, void *mii_vaddr)
{
	/* Setup the ethernet base address and mac address */
	priv->vaddr_base = gbl_vaddr;
	priv->vpaddr_base = port_vaddr;

	/* Initialize base addresses for direct access */
	priv->eth_csr_addr_v        = gbl_vaddr + BLOCK_ETH_CSR_OFFSET;
	priv->eth_cle_addr_v        = gbl_vaddr + BLOCK_ETH_CLE_OFFSET;
	priv->eth_qmi_addr_v        = gbl_vaddr + BLOCK_ETH_QMI_OFFSET;
	priv->eth_sds_csr_addr_v    = gbl_vaddr + BLOCK_ETH_SDS_CSR_OFFSET;
	priv->eth_clkrst_csr_addr_v = gbl_vaddr + BLOCK_ETH_CLKRST_CSR_OFFSET;
	priv->eth_diag_csr_addr_v   = gbl_vaddr + BLOCK_ETH_DIAG_CSR_OFFSET;

	/* Initialize base addresses for Per Port MII Indirect access */
	priv->mac_mii_addr_v = mii_vaddr;

	/* Initialize base addresses for Per Port indirect & direct MCX MAC access */
	priv->mcx_mac_addr_v       = port_vaddr + BLOCK_ETH_MAC_OFFSET;
	priv->mcx_stats_addr_v     = port_vaddr + BLOCK_ETH_STATS_OFFSET;
	priv->mcx_mac_csr_addr_v   = gbl_vaddr + BLOCK_MCX_MAC_CSR_OFFSET;

	/* Initialize base addresses for Per Port indirect & direct AXG MAC access */
	priv->axg_mac_addr_v         = gbl_vaddr + BLOCK_AXG_MAC_OFFSET;
	priv->axg_stats_addr_v       = gbl_vaddr + BLOCK_AXG_STATS_OFFSET;
	priv->axg_mac_csr_addr_v     = gbl_vaddr + BLOCK_ETH_MAC_CSR_OFFSET;
	priv->xgenet_pcs_addr_v      = gbl_vaddr + BLOCK_XGENET_PCS_OFFSET;
	priv->xgenet_mdio_csr_addr_v = gbl_vaddr + BLOCK_XGENET_MDIO_CSR_OFFSET;

	ENET_DEBUG("           ETH%d VADDR: 0x%p\n", priv->port, priv->vpaddr_base);
	ENET_DEBUG("            ETH VADDR: 0x%p\n", priv->vaddr_base);
	ENET_DEBUG("        ETH CSR VADDR: 0x%p\n", priv->eth_csr_addr_v);
	ENET_DEBUG("        ETH CLE VADDR: 0x%p\n", priv->eth_cle_addr_v);
	ENET_DEBUG("        ETH QMI VADDR: 0x%p\n", priv->eth_qmi_addr_v);
	ENET_DEBUG("    ETH SDS CSR VADDR: 0x%p\n", priv->eth_sds_csr_addr_v);
	ENET_DEBUG(" ETH CLKRST CSR VADDR: 0x%p\n", priv->eth_clkrst_csr_addr_v);
	ENET_DEBUG("       ETH DIAG VADDR: 0x%p\n", priv->eth_diag_csr_addr_v);
	ENET_DEBUG("        MAC MII VADDR: 0x%p\n", priv->mac_mii_addr_v);
	ENET_DEBUG("        MCX MAC VADDR: 0x%p\n", priv->mcx_mac_addr_v);
	ENET_DEBUG("       MCX STAT VADDR: 0x%p\n", priv->mcx_stats_addr_v);
	ENET_DEBUG("    MCX MAC CSR VADDR: 0x%p\n", priv->mcx_mac_csr_addr_v);
	ENET_DEBUG("        AXG MAC VADDR: 0x%p\n", priv->axg_mac_addr_v);
	ENET_DEBUG("       AXG STAT VADDR: 0x%p\n", priv->axg_stats_addr_v);
	ENET_DEBUG("    AXG MAC CSR VADDR: 0x%p\n", priv->axg_mac_csr_addr_v);
	ENET_DEBUG("     XGENET PCS VADDR: 0x%p\n", priv->xgenet_pcs_addr_v);
	ENET_DEBUG("XGENET MDIO CSR VADDR: 0x%p\n", priv->xgenet_mdio_csr_addr_v);

	/* Initialize priv handlers */
	priv->port_reset = apm_xgport_reset;
	priv->mac_reset = apm_xgmac_reset;
	priv->get_link_status = apm_xgmac_link_status;
	if (priv->force_serdes_reset)
		priv->serdes_reset = serdes_reset_rxd_rxa;
	priv->mac_init = apm_xgmac_init;
	priv->mac_rx_state = apm_xgmac_rx_state;
	priv->mac_tx_state = apm_xgmac_tx_state;
	priv->mac_change_mtu = apm_xgmac_change_mtu;
	priv->mac_set_ipg = apm_xgmac_set_ipg;
	priv->get_stats = apm_xgmac_get_detailed_stats;
	priv->set_mac_addr = apm_xgmac_set_mac_addr;
	priv->cle_bypass = apm_xg_cle_bypass_mode_cfg;
	priv->tx_offload = apm_xgmac_tx_offload;
	priv->port_shutdown = apm_xgport_shutdown;
}

