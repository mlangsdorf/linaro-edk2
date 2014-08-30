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

#ifndef __APM_XGENET_MAC_H__
#define __APM_XGENET_MAC_H__

#include "apm_enet_common.h"
#if 0	//TODO
#ifdef BOOTLOADER
#include <asm/arch-storm/apm88xxxx_scu.h>
#else
#include <misc/xgene/slimpro/apm88xxxx_slimpro.h>
#endif
#endif


//#define APM_XG_AXGMAC_TX2RX_LOOPBACK
//#define APM_XGENET_XGMII_TX2RX_LOOPBACK	

/* AXGMAC assume port4 */
#define AXGMAC 4 //XGENET_AXGMAC_CSR_BASE_ADDR

/**
 * @brief   This function configures the MAC address of given MAC device
 * @param   priv MAC private stucture
 * @param   mac_addr_hi Higher 4 octects of MAC address
 *	    mac_addr_lo Lower 2 octects of MAC address
 * @return  None.
 **
 */
void apm_xgmac_set_mac_addr(struct apm_data_priv *priv,
			unsigned char *dev_addr);

/* Statistics related functions */

/**
 * @brief   This function returns the brief statistics counts for the device
 * @param   priv Device structure of MAC
 * @param   brief_stats Brief statistics structure to be filled
 * @return  None
 **
 */
void apm_xgmac_get_brief_stats(struct apm_data_priv *priv,
				struct eth_brief_stats *brief_stats);
/**
 * @brief   This function returns detailed statistics counts for the device
 * @param   priv Device structure of MAC
 * @param   detailed_stats Detailed statistics structure to be filled up
 * @return  None
 **
 */
void apm_xgmac_get_detailed_stats(struct apm_data_priv *priv,
				struct eth_detailed_stats *detailed_stats);
/**
 * @brief   This function returns tx rx combined statistics counts
 * @param   priv Device structure of MAC
 * @param   eth_frame_stats Tx Rx stats structure to be filled up
 * @return  None
 **
 */
void apm_xgmac_get_tx_rx_stats(struct apm_data_priv *priv,
				struct eth_frame_stats *eth_tx_rx_stats);
/**
 * @brief   This function returns rx statistics counts for the device
 * @param   priv Device structure of MAC
 * @param   eth_rx_stats Rx stats structure to be filled up
 * @return  None
 **
 */
void apm_xgmac_get_rx_stats(struct apm_data_priv *priv,
			struct eth_rx_stat *rx_stat);

/**
 * @brief   This function returns tx statistics counts for the device
 * @param   priv Device structure of MAC
 * @param   tx_stats Tx stats structure to be filled up
 * @return  None
 **
 */
void apm_xgmac_get_tx_stats(struct apm_data_priv *priv,
			struct eth_tx_stats *tx_stats);

extern void apm_xgmac_phy_link_mode(struct apm_data_priv *priv, u32 *speed, u32 *state);
extern int apm_xgmac_phy_autoneg_done(struct apm_data_priv *priv);
extern void xgenet_reset(struct apm_data_priv *priv);
extern void apm_xgmac_tx_enable(struct apm_data_priv *priv);
extern void apm_xgmac_rx_enable(struct apm_data_priv *priv);
extern void apm_xgmac_tx_disable(struct apm_data_priv *priv);
extern void apm_xgmac_rx_disable(struct apm_data_priv *priv);
extern int apm_xgmac_init(struct apm_data_priv *priv,
                unsigned char *dev_addr, int speed, int mtu, int crc);
extern void apm_xgmac_change_mtu(struct apm_data_priv *priv, u32 new_mtu);
extern void apm_xgenet_set_phyid(struct apm_data_priv *priv);
extern void enet_config_qmi_assoc(struct apm_data_priv *priv);
extern void xgenet_config_qmi_assoc(struct apm_data_priv *priv);
extern u32 apm_xgenet_get_mode(struct apm_data_priv *priv);

int
apm_xg_mac_init
(
	struct apm_data_priv *priv,
       	unsigned char *dev_addr,
        int speed,
        int mtu,
        int crc

);

void
apm_xg_select_mode( struct apm_data_priv *priv );
void
apm_xg_init_ecc( struct apm_data_priv *priv );
void
apm_xg_clk_rst_cfg( struct apm_data_priv *priv );
void
apm_xg_reset_axgmac ( struct apm_data_priv *priv );

void
apm_xg_loopback_cfg( struct apm_data_priv *priv );
void
apm_xg_serdes_init( struct apm_data_priv *priv );
void
apm_xg_bypass_resume_cfg( struct apm_data_priv *priv );

struct eth_queue_ids;

void
apm_xg_cle_bypass_mode_cfg(struct apm_data_priv *priv, u32 cle_dstqid, u32 cle_fpsel);

void apm_xgenet_init_priv(struct apm_data_priv *priv, void *port_vaddr, void *gbl_vaddr, void *mii_vaddr);

#endif  // __APM_XGENET_MAC_H__
