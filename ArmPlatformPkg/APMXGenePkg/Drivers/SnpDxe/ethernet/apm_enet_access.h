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

#ifndef __APM_ENET_ACCESS_H__
#define __APM_ENET_ACCESS_H__

#ifndef APM_XGENE
#include <config.h>
#include <common.h>
#include <net.h>
#else
//#include <stdlib.h>
//#include <stdio.h>
//#include <string.h>
#include <Library/IoLib.h>
#include <Library/DebugLib.h>
#include <Library/TimerLib.h>
#include <Library/BaseMemoryLib.h>
typedef UINT8 u8;
typedef UINT16 u16;
typedef UINT32 u32;
typedef UINT64 u64;

#if 1
struct eth_device {
	char name[16];
	unsigned char enetaddr[6];
	int iobase;
	int state;

	int  (*init) (struct eth_device * /*TODO , bd_t * */);
	int  (*send) (struct eth_device*, volatile void* packet, int length);
	int  (*recv) (struct eth_device *, VOID *Buffer, UINTN *BufferSize);
	void (*halt) (struct eth_device *);
#ifdef CONFIG_MCAST_TFTP
	int (*mcast) (struct eth_device *, u32 ip, u8 set);
#endif
	int  (*write_hwaddr) (struct eth_device *);
	struct eth_device *next;
	int index;
	void *priv;
};
#endif



#ifndef ARRAY_SIZE
#define ARRAY_SIZE(x)   (sizeof(x) / sizeof((x)[0]))
#endif

#define readl           MmioRead32
#define writel(v, a)    MmioWrite32((a), (v))
#define udelay          MicroSecondDelay
//#define memset(p, v, s) SetMem((p), (s), (v))
#define memset(dest,ch,count)             SetMem(dest,(UINTN)(count),(UINT8)(ch))
#define memcpy(dest,source,count)         CopyMem(dest,source,(UINTN)(count))
#define printf          info
#define strcmp                            AsciiStrCmp
#define strcpy(strDest,strSource)         AsciiStrCpy(strDest,strSource)
#define strncpy(strDest,strSource,count)  AsciiStrnCpy(strDest,strSource,(UINTN)count)

#define DDR_INFO
#undef DDR_DBG

#ifdef DDR_DBG
#define debug(arg...) DEBUG ((EFI_D_ERROR,## arg))
#else
#define debug(arg...)
#endif

#ifdef DDR_INFO
#define info(arg...) DEBUG ((EFI_D_INFO,## arg))
#else
#define info(arg...)
#endif

#endif
#include "apm_enet_common.h"

#define BOOTLOADER

#undef BYPASS_CLE

#define ENET_DBG_ERR
#define ENET_PRINT_ENABLE
#undef PHY_DEBUG	//TODO
#undef FAM_UBOOT
#undef DEBUG_HEXDUMP	//TODO
#undef  ENET_DBG	//TODO
#undef DEBUG_RD   
#undef DEBUG_WR   
#undef DEBUG_RX 
#undef DEBUG_TX	//TODO
#undef ENET_REGISTER_READ
#undef ENET_REGISTER_WRITE

#define STORM_FPGA_CLS_BYPASS

// Buffer Length encoded as per QM message format
enum apm_enet_buf_len {
	BUF_LEN_256B = 0x7000,
	BUF_LEN_1K   = 0x6000,
	BUF_LEN_2K   = 0x5000,
	BUF_LEN_4K   = 0x4000,
	BUF_LEN_16K  = 0x0
};

#ifdef ENET_PRINT_ENABLE
#define ENET_PRINT(x, ...)		printf((x), ##__VA_ARGS__)
#else
#define ENET_PRINT(x, ...)
#endif

#ifdef PHY_DEBUG
#define PHY_PRINT(x, ...)		printf((x), ##__VA_ARGS__)
#else
#define PHY_PRINT(x, ...)
#endif

#ifdef ENET_DBG
#define ENET_DEBUG(x, ...)		printf((x), ##__VA_ARGS__)
#else
#define ENET_DEBUG(x, ...)	
#endif

#ifdef ENET_DBG_ERR
#define ENET_DEBUG_ERR(x, ...)		printf((x), ##__VA_ARGS__)
#else
#define ENET_DEBUG_ERR(x, ...)	    
#endif

#ifdef DEBUG_RD
#define ENET_DEBUG_RD(x, ...)		printf((x), ##__VA_ARGS__)
#else
#define ENET_DEBUG_RD(x, ...)		
#endif

#ifdef DEBUG_WR
#define ENET_DEBUG_WR(x, ...)		printf((x), ##__VA_ARGS__)
#else
#define ENET_DEBUG_WR(x, ...)		
#endif

#ifdef ENET_REGISTER_READ
#define ENET_REG_RD(x, ...)		printf((x), ##__VA_ARGS__)
#else
#define ENET_REG_RD(x, ...)
#endif

#ifdef ENET_REGISTER_WRITE
#define ENET_REG_WR(x, ...)		printf((x), ##__VA_ARGS__)
#else
#define ENET_REG_WR(x, ...)
#endif

#ifdef DEBUG_HEXDUMP
#define ENET_RXHEXDUMP(b, l)		putshex(b, l)
#define ENET_TXHEXDUMP(b, l)		putshex(b, l)
#else
#define ENET_RXHEXDUMP(b, l)
#define ENET_TXHEXDUMP(b, l)
#endif

#undef DEBUG_RX //TODO
#ifdef DEBUG_RX
#define ENET_DEBUG_RX(x, ...)		printf((x), ##__VA_ARGS__)
#else
#define ENET_DEBUG_RX(x, ...)		
#endif

#ifdef DEBUG_TX
#define ENET_DEBUG_TX(x, ...)		printf((x), ##__VA_ARGS__)
#else
#define ENET_DEBUG_TX(x, ...)		
#endif

#define physical_addr(x) 	((unsigned int) (x))
#define virtual_addr(x)	 	((void *) (x))

#define NO_RX_BUFF		16

#define ENET_ADDR_LENGTH	6
#define EMAC_NUM_DEV		1

#define TX_DATA_LEN_MASK	0XFFF
#define ENET_MAX_MTU_ALIGNED	1536 //TODO PKTSIZE_ALIGN

#ifndef CONFIG_STORM_VHP
#define PBN_CLEAR_SUPPORT
#endif

#undef APM_ENET_SERDES_LOOPBACK

#ifdef APM_ENET_SERDES_LOOPBACK
#undef APM_ENET_MAC_LOOPBACK
#define NON_AUTO_NEGOTIATION	1
#endif

#if defined(CONFIG_STORM)
#define invalidate_dcache_range(x, y)
#define flush_dcache_range(x, y)
#endif

// FIXME: do we need mailbox related variables ?
// FIXME: do we need pbn ?  can we have qinfo instead of qid etc ?
/* Queues related parameters per Enet port */
struct eth_queue_ids {
	u32 rx_qid;
	u32 rx_mbid; 	/* mailbox id for receive queue */
	u32 rx_fp_qid;
	u32 rx_fp_mbid;
	u32 rx_fp_pbn;
	u32 tx_qid;		/* Endque q id	      */
	u32 comp_qid;		/* completion q id    */
	u32 comp_mb;		/* completion mailbox */
	u32 qm_ip;
};

struct enet_frame {
	unsigned char dest_addr[ENET_ADDR_LENGTH];
	unsigned char source_addr[ENET_ADDR_LENGTH];
	unsigned short type;
	unsigned char enet_data[1];
};

/* private information regarding device */
struct apm_enet_dev {
	struct apm_data_priv priv;
	struct eth_device *ndev;
	u32 port_id;
	u32 qm_ip;
	struct apm_emac_error_stats estats;
	struct apm_emac_stats stats;
	struct eth_queue_ids queues;
};

#ifdef inline
#undef inline
#endif
/* Ethernet raw register write routine */
inline int apm_enet_wr32(void *addr, u32 data);


/* Ethernet raw register read routine */
inline int apm_enet_rd32(void *addr, u32 *data);

/**
 * @brief   This function performs preclassifier engine Initialization
 * 	    and node configurations.  
 * @param   port_id - GE Port number
 * @param   *eth_q  - Pointer to queue configurations used by Ethernet 
 * @return  0 - success or -1 - failure
 */
int apm_preclass_init(u8 port_id, struct eth_queue_ids *eth_q);

/**
 * @brief   This function updates preclassifier rule of allowing incoming
 *          Ethernet packets dstmac address which are same as macaddr
 * @param   port_id - GE Port number
 * @param   macaddr - Ethenet MAC Address
 */
void apm_preclass_update_mac(u8 port_id, u8 *macaddr);

int apm_eth_tx(struct eth_device *dev, volatile void *ptr, int len);
int apm_eth_rx(struct eth_device *dev, VOID *Buffer, UINTN *BufferSize);
int apm_eth_qm_init(struct apm_enet_dev *priv_dev);
int apm_eth_fp_init(struct apm_enet_dev *priv_dev);

#endif	/* __APM_ENET_ACCESS_H__ */
