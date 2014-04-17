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

#ifndef __APM_ENET_MAC_H__
#define __APM_ENET_MAC_H__

#include "apm_enet_common.h"
#include "apm_enet_csr.h"
#if 0	//TODO
#ifdef BOOTLOADER
#include <asm/arch-storm/apm88xxxx_scu.h>
#else
#include <misc/xgene/slimpro/apm88xxxx_slimpro.h>
#endif
#endif

/* MAC APIs */
void apm_gmac_pad_crc_enable(struct apm_data_priv *priv, u8 enable);
void apm_gmac_crc_enable(struct apm_data_priv *priv, u8 enable);
void apm_gmac_set_ipg(struct apm_data_priv *priv, u16 ipg);
void apm_gmac_reset(struct apm_data_priv *priv);
int apm_gmac_phy_autoneg_done(struct apm_data_priv *priv);
void apm_gmac_phy_init(struct apm_data_priv *priv);
int apm_gmac_init(struct apm_data_priv *priv, unsigned char *dev_addr, 
		int speed, int mtu, int crc);
void apm_gmac_change_mtu(struct apm_data_priv *priv, u32 new_mtu);
void apm_gmac_phy_link_mode(struct apm_data_priv *priv, u32 *speed, u32 *state);
int apm_gmac_phy_enable_scan_cycle(struct apm_data_priv *priv, int enable);
void apm_gmac_set_mac_addr(struct apm_data_priv *priv, unsigned char *dev_addr);
int apm_get_link_speed(struct apm_data_priv *priv);
void enet_reset(struct apm_data_priv *priv);
void apm_enet_init_priv(struct apm_data_priv *priv, void *port_vaddr, 
		void *gbl_vaddr, void *mii_vaddr);
void apm_menet_config_qmi_assoc(struct apm_data_priv *priv);
void apm_enet_config_qmi_assoc(struct apm_data_priv *priv);
void apm_enet_cle_bypass_mode_cfg(struct apm_data_priv *priv, u32 cle_dstqid, 
		u32 cle_fpsel);
void apm_menet_clk_rst_cfg( struct apm_data_priv *priv );

/* Statistics APIs */
void apm_gmac_get_detailed_stats(struct apm_data_priv *priv,
			struct eth_detailed_stats *detailed_stats);
void apm_gmac_get_tx_rx_stats(struct apm_data_priv *priv,
			struct eth_frame_stats *eth_tx_rx_stats);
void apm_gmac_get_rx_stats(struct apm_data_priv *priv,
			struct eth_rx_stat *rx_stat);
void apm_gmac_get_tx_stats(struct apm_data_priv *priv,
			struct eth_tx_stats *tx_stats);

#endif	/* __APM_ENET_MAC_H__ */
