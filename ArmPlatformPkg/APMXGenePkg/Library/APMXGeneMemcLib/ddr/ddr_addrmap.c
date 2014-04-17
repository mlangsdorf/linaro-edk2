/**
 * APM X-Gene DDR3 controller
 *
 * Copyright (c) 2013, AppliedMicro Corp. All rights reserved.
 * All rights reserved. Feng Kan <fkan@apm.com>.
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

#if defined(APM_SIM)
#include "apm_ddr_sdram.h"
#elif defined(APM_VBIOS)
#include <common.h>
#include <stdio.h>
#include <string.h>
#include <apm_ddr_sdram.h>
#elif defined(APM_TIANOCORE)
#include "apm_ddr_sdram.h"
#else
#include <command.h>
#include <asm/io.h>
#include <asm/arch/apm_ddr_sdram.h>
#include "config.h"
#endif

#include "ddr_lib.h"
#include "ddr_mcu.h"

int mcu_rank_addr_cfg(void *p, unsigned int mcb_intrlv, unsigned int mcu_intrlv,
		      unsigned int full_addr)
{
	unsigned int i, j, k, rnk_mul, rnk_mask;
	unsigned int activeslots, ranksdisable, ranksperslot;
	unsigned long rank_size, rsize_param;
	unsigned int mcu_base, rank_cfg, rank_present, rankintrlv;
	unsigned int mcumcb_base_adj;

	struct apm_mcu *mcu = (struct apm_mcu *)p;
	mcu_param_t *p_parm = &mcu->mcu_params;

	if (!(mcu->enabled)) {
		return 0;
	}

	/* Determine rank config, active slots and presented rank */
	rank_cfg = ~(p_parm->by4_mode) & 0x1;
	activeslots = p_parm->activeslots;
	rank_present = 0;
	k = 0;
	for (i = 0; i < CONFIG_SYS_DIMM_SLOTS_PER_CTLR; i++) {
		if (!((activeslots >> i) & 0x1)) {
			continue;
		}

		ranksperslot = p_parm->ranksperslot[i];
		ranksdisable = p_parm->ranksdisable[i];
		debug("\tranksperslot: 0x%X ranksdisable: 0x%0X\n",
				ranksperslot, ranksdisable);
		for (j = 0; j < ranksperslot; j++) {
			if (rank_present & 0x80)
				break;
			rank_present |= (((~ranksdisable >> j) & 0x1) << k);
			k++;
		}
	}

	debug("\trank_present: 0x%X [k:%d]\n", rank_present, k);
	// mcu->mcu_wr(mcu, MCB0_REG_ADDR_MODE_ADDR,     0x0); 
	p_parm->activeranks = rank_present;

	// Determine if rank interleave &/or rank hash
	// assume all ranks identical - Storm Limitation
	switch (rank_present) {
		case 0x03:
		case 0x0c:
		case 0x05: // 2 ranks active
			rankintrlv = (p_parm->desired_rank_intrlv) ? 
				0x1 : 0x0 ;
			break;
		case 0x0F:
		case 0x33:
		case 0xCC: // 4 ranks active
			rankintrlv = (p_parm->desired_rank_intrlv) ? 
				(p_parm->desired_rank_intrlv & 0x3) : 0x0 ;
			break;
		case 0x3F:
		case 0xCF:// 6 ranks active - use 2 way only
			rankintrlv = (p_parm->desired_rank_intrlv) ? 
				(0x1) : 0x0 ;
			break;
		case 0xFF: // 8 ranks active
			rankintrlv = (p_parm->desired_rank_intrlv) ? 
				(p_parm->desired_rank_intrlv & 0x7) : 0x0 ;
			break;
		case 1:
		case 4:
		default: // For odd ranks 1/3/5
			rankintrlv = 0;
			break;
	}

	// Determine base and size
	rsize_param = ((p_parm->minranksize) / (1024 * 1024));
	switch (rsize_param) {
		case 512:       // 512MB
			rnk_mul = 0x2;
			rank_size = 0;
			rnk_mask = 0x3FFE;
			break;                //512M/rank
		case 1024:      // 1GB
			rnk_mul = 0x4;
			rank_size = 1;
			rnk_mask = 0x3FFC;
			break;                //1024M/rank
		case 2048:      // 2GB
			rnk_mul = 0x8;
			rank_size = 2;
			rnk_mask = 0x3FF8;
			break;                //2048M/rank
		case 4096:      // 4GB
			rnk_mul = 0x10;
			rank_size = 3;
			rnk_mask = 0x3FF0;
			break;                //4096M/rank
		case 8192:      // 8GB
			rnk_mul = 0x20;
			rank_size = 4;
			rnk_mask = 0x3FE0;
			break;                //8192M/rank
		case 16384:     // 16GB
			rnk_mul = 0x40;
			rank_size = 5;
			rnk_mask = 0x3FC0;
			break;                //16384M/rank
		default:// 1GB
			rnk_mul = 4;
			rank_size = 7;
			//mcu_base = 0x8;
			rnk_mask = 0x3F80;
			break;                //unsupported
	}

	/* DDR base address will be fixed to base 0x40 xxxx xxxx */
	mcu_base = 0x400;
	if (mcb_intrlv && mcu_intrlv) {
		/* mcb interleave and mcu interleave */
		mcu_base = mcu_base >> 2;
	} else if (mcb_intrlv || mcu_intrlv) {
		/* either mcb interleave or mcu interleave */
		mcu_base = mcu_base >> 1;
	}

	/* Determine actual rank base and rank mask */
	switch (rankintrlv){
		case 1:
			rnk_mask = (rnk_mask << 1) & 0x3FFF;
			break;
		case 3:
			rnk_mask = (rnk_mask << 2) & 0x3FFF;
			break;
		case 7:
			rnk_mask = (rnk_mask << 3) & 0x3FFF;
			break;
		default:
			break;
	}

	/* Rank Hashing */
	p_parm->hash_enable = p_parm->desired_rank_hash_en;

	debug("MCU[%d]-AddrMap: ranksize: %ld, rank-cfg:%d, activeslots:%d\n",
		mcu->id, rank_size, rank_cfg, activeslots);

	/* FIX ME: for more readable */
	// Adjust Address Base to fit Mcu region - depends on Intrlv & dual Mcu/Mcb
	debug("\tMCB %d: mcb interleave %x - mcu interleave %x\n", 
			mcu->mcb_id, mcb_intrlv, mcu_intrlv);
	debug("\tMCB %d: rank interleave %x - rank hashing %x\n", 
			 mcu->mcb_id, rankintrlv, p_parm->hash_enable);
	mcumcb_base_adj = 0x0U;
	mcumcb_base_adj |=
	    (mcb_intrlv == 1) ? 0x0U :
	    (mcu_intrlv == 1) ? 
			(((mcu->mcb_id) & 0x1) << 9) : (((mcu->mcb_id) & 0x1) << 10);
	mcumcb_base_adj |= (mcu_intrlv == 1) ? 0x0U : (((mcu->id) & 0x1) << 9);	//[37]
	debug("\tMCB %d: base adj %x\n", mcu->mcb_id, mcumcb_base_adj);

#if APM_SIM
	if (mcb_intrlv || mcu_intrlv) {
		mcu_base = 0;
	}
#endif

	j = 0;
	for (i = 0; i < MCU_SUPPORTED_RANKS; i++) {
		if ((rank_present >> i) & 0x1) {
			p_parm->rank_base_low[i] = 0;
			p_parm->rank_mask_low[i] = rankintrlv;
			p_parm->rank_hash[i] = 0;

			switch (rank_size) {
				case 0:     // 512MB
				case 1:     // 1GB
				case 2:     // 2GB
				case 3:     // 4GB
				case 4:     // 8GB
				case 5:     // 16GB
					p_parm->rank_size[i] = rank_size;
					p_parm->rank_config[i] = 1* rank_cfg;
					p_parm->rank_base_high[i] = mcumcb_base_adj |
						(mcu_base + ((j/(rankintrlv + 1)) 
						* rnk_mul * (rankintrlv + 1)));
					p_parm->rank_mask_high[i] = rnk_mask;
					p_parm->rank_base_low[i] = 
						(rankintrlv) ? (j%(rankintrlv + 1)) : 0;
					j++;
					p_parm->rank_hash[i] = 
						minAllowedRankHash(p_parm->desired_rank_hash,
								rank_size, rank_cfg,
								rankintrlv);
					p_parm->rank_hash[i] = 
						(p_parm->hash_enable) ? p_parm->rank_hash[i] : 0;
					break;

				default:
					p_parm->rank_size[i] = 0x7;
					p_parm->rank_mask_high[i] = 0x0;
					p_parm->rank_base_low[i] = 0;
					p_parm->rank_mask_low[i] = 0;
					p_parm->rank_hash[i] = 0;
					break;
			}
			debug("\trank[%d] size: 0x%llx\n", i,
					p_parm->rank_size[i]);
			debug("\trank[%d] base: 0x%X\n", i,
					p_parm->rank_base_high[i]);
			debug("\trank[%d] mask: 0x%X\n", i,
					p_parm->rank_mask_high[i]);
			debug("\trank[%d] hash: 0x%x\n", i,
					p_parm->rank_hash[i]);
			debug("\trank[%d] lobase: 0x%X\n", i,
					p_parm->rank_base_low[i]);
			debug("\trank[%d] lomask: 0x%X\n", i,
					p_parm->rank_mask_low[i]);
		} else {
			p_parm->rank_size[i] = 0x7;
			p_parm->rank_mask_high[i] = 0x0;
			p_parm->rank_base_low[i] = 0;
			p_parm->rank_mask_low[i] = 0;
			p_parm->rank_hash[i] = 0;
		}

	}
	return 0;
}

int mcu_prog_csr_rank_cfg(void *p)
{
	unsigned int i;
	unsigned int offset;
	struct apm_mcu *mcu = (struct apm_mcu *)p;
	mcu_param_t *p_parm = &mcu->mcu_params;
	if (!(mcu->enabled)) {
		return 0;
	}

	mcu->mcu_wr(mcu, MCU_REG_HASH_CTL, p_parm->hash_enable);
	for (i = 0; i < MCU_SUPPORTED_RANKS; i++) {
		offset = i * 0x40;
		if (p_parm->rank_size[i] == 0x7) {
			mcu->mcu_wr(mcu, MCU_REG_RANK_0_SIZE + offset,
				    p_parm->rank_size[i]);
		} else {
			mcu->mcu_wr(mcu, MCU_REG_RANK_0_SIZE + offset,
				    p_parm->rank_size[i]);
			mcu->mcu_wr(mcu, MCU_REG_RANK_0_CONFIG + offset,
				    p_parm->rank_config[i]);
			mcu->mcu_wr(mcu, MCU_REG_RANK_0_BASE + offset,
				    ((((p_parm->rank_base_low[i]) & 0x7U) << 16)
				     | ((p_parm->rank_base_high[i]) &
					0x3FFFU)));
			mcu->mcu_wr(mcu, MCU_REG_RANK_0_MASK + offset,
				    ((((p_parm->rank_mask_low[i]) & 0x7U) << 16)
				     | ((p_parm->rank_mask_high[i]) &
					0x3FFFU)));
			mcu->mcu_wr(mcu, MCU_REG_RANK_0_HASH_SIZE + offset,
				    (p_parm->rank_hash[i]));

		}
	}
	return 0;
}

/* Determine all Mcb/Mcu address mapping based 
 * on desired setting & dimm configuration 
 * Note: 32b addressing not supported  
 */
int memc_addr_cfg(void *ptr)
{
	unsigned int err = 0;
	struct apm_memc *memc = (struct apm_memc *)ptr;
	apm_mem_space_t *p_sp = (apm_mem_space_t *) (&memc->memspace);
	mcu_param_t *p_parm;
	struct apm_mcu *mcu;
	struct apm_mcb *mcb;

	unsigned long long mcu_addr_size[4];
	unsigned long long mcu_low_base[4];
	unsigned long long rbase, rsize;
	unsigned int mcu_active, iia, i;
	mcu_active = 0;
	debug(" ENTRY: %s > \n", __FUNCTION__);

	// Check enabled Mcus & decide if dual mcb/mcu & intrlv
	// Note: mcu  must be same mem footprint to intrlv

	// Reapply intrleave etc - after SPD has deterimined DIMM etc
	for (iia = 0; iia < CONFIG_SYS_NUM_DDR_CTLRS; iia++) {
		mcu = (struct apm_mcu *)&(memc->mcu[iia]);
		mcu_active |= (mcu->enabled) ? (1 << iia) : 0;
	}
	/*
	 * Check if Legal Mcu config
	 */
	switch (mcu_active) {
	case 0x1:
	case 0x2:
	case 0x3:
	case 0x4:
	case 0x5:
	case 0x7:
	case 0x8:
	case 0xC:
	case 0xD:
	case 0xF:
		break;
	default:{		/* Mcu0 must be present !!!! */
			debug
			    ("ERROR: Illegal Mcu config Mcu0-Mcu2 must be enabled! mcu_en=%1X \n",
			     mcu_active);
			break;
		}
	}

	for (iia = 0; iia < CONFIG_SYS_NUM_DDR_CTLRS; iia++) {
		mcu = (struct apm_mcu *)&(memc->mcu[iia]);
		mcb = (struct apm_mcb *)&(memc->mcb[(iia / 2)]);
		p_parm = (mcu_param_t *) & mcu->mcu_params;
		err +=
		    mcu_rank_addr_cfg(mcu, memc->mcb_intrlv, mcb->mcu_intrlv,
				      memc->full_addr);

		if (mcu->enabled) {
			mcu_addr_size[iia] = 0;
			mcu_low_base[iia] = 0x3FFF;
			mcu_active |= (1 << iia);
			for (i = 0; i < MCU_SUPPORTED_RANKS; i++) {
				rsize = p_parm->rank_size[i];
				switch (rsize) {	// Calc size in 512MB incr
				case 0:
					mcu_addr_size[iia] += 1;
					break;
				case 1:
					mcu_addr_size[iia] += 2;
					break;
				case 2:
					mcu_addr_size[iia] += 4;
					break;
				case 3:
					mcu_addr_size[iia] += 8;
					break;
				case 4:
					mcu_addr_size[iia] += 16;
					break;
				case 5:
					mcu_addr_size[iia] += 32;
					break;
				default:
					break;
				}
				// get lowest base
				if (rsize < 6) {
					rbase = p_parm->rank_base_high[i];
					if ((rbase & 0x3FFF) <
					    mcu_low_base[iia]) {
						mcu_low_base[iia] =
						    (rbase & 0x3FFF);
					}
				}
			}
			// Check if no base is set - size is zero
			if (mcu_low_base[iia] == 0x3FFF) {
				mcu_addr_size[iia] = 0;
			}
		} else {
			mcu_addr_size[iia] = 0;
		}
	}

	// Set MemSpace
	// Assume it is continous for 1 Mcu or any Intrlv Mcu
	// Check if interleave is bad etc
	// TBD - adjust for 2GB Dram B region 0x80_0000_0000
	switch (mcu_active) {
	case 0x1:
	case 0x2:
	case 0x4:
	case 0x8:
		for (iia = 0; iia < CONFIG_SYS_NUM_DDR_CTLRS; iia++)
			if (mcu_active & (1 << iia))
				i = iia;
		p_sp->num_mem_regions = 1;
		p_sp->str_addr[0] = (unsigned long long)(mcu_low_base[i] << 28);
		p_sp->end_addr[0] = (unsigned long long)p_sp->str_addr[0] +
		    (mcu_addr_size[i] * 0x20000000ULL) - 1;
		break;
	case 0x3:
		if (memc->mcb[0].mcu_intrlv) {
			p_sp->num_mem_regions = 1;
			p_sp->str_addr[0] =
			    (unsigned long long)(mcu_low_base[0] << 28)
			    * 2ULL;
			p_sp->end_addr[0] =
			    (unsigned long long)p_sp->str_addr[0] +
			    (2ULL * mcu_addr_size[0] * 0x20000000ULL) -
			    1;
		} else {
			p_sp->num_mem_regions = 2;
			p_sp->str_addr[0] =
			    (unsigned long long)(mcu_low_base[0] << 28);
			p_sp->end_addr[0] =
			    (unsigned long long)p_sp->str_addr[0] +
			    (mcu_addr_size[0] * 0x20000000ULL) - 1;
			p_sp->str_addr[1] =
			    (unsigned long long)(mcu_low_base[1] << 28);
			p_sp->end_addr[1] =
			    (unsigned long long)p_sp->str_addr[1] +
			    (mcu_addr_size[1] * 0x20000000ULL) - 1;
		}
		break;
	case 0x5:
		if (memc->mcb_intrlv) {
			p_sp->num_mem_regions = 1;
			p_sp->str_addr[0] =
			    (unsigned long long)(mcu_low_base[0] << 28)
			    * 2ULL;
			p_sp->end_addr[0] =
			    (unsigned long long)p_sp->str_addr[0] +
			    (2ULL * mcu_addr_size[0] * 0x20000000ULL) -
			    1;
		} else {
			p_sp->num_mem_regions = 2;
			p_sp->str_addr[0] =
			    (unsigned long long)(mcu_low_base[0] << 28);
			p_sp->end_addr[0] =
			    (unsigned long long)p_sp->str_addr[0] +
			    (mcu_addr_size[0] * 0x20000000ULL) - 1;
			p_sp->str_addr[1] =
			    (unsigned long long)(mcu_low_base[2] << 28);
			p_sp->end_addr[1] =
			    (unsigned long long)p_sp->str_addr[1] +
			    (mcu_addr_size[2] * 0x20000000ULL) - 1;

		}
		break;
	case 0xC:
		if (memc->mcb[1].mcu_intrlv) {
			p_sp->num_mem_regions = 1;
			p_sp->str_addr[0] =
			    (unsigned long long)(mcu_low_base[2] << 28)
			    * 2ULL;
			p_sp->end_addr[0] =
			    (unsigned long long)p_sp->str_addr[0] +
			    (2ULL * mcu_addr_size[2] * 0x20000000ULL) -
			    1;
		} else {
			p_sp->num_mem_regions = 2;
			p_sp->str_addr[0] =
			    (unsigned long long)(mcu_low_base[2] << 28);
			p_sp->end_addr[0] =
			    (unsigned long long)p_sp->str_addr[0] +
			    (mcu_addr_size[2] * 0x20000000ULL) - 1;
			p_sp->str_addr[1] =
			    (unsigned long long)(mcu_low_base[3] << 28);
			p_sp->end_addr[1] =
			    (unsigned long long)p_sp->str_addr[1] +
			    (mcu_addr_size[3] * 0x20000000ULL) - 1;
		}
		break;
	case 0xF:
		if (memc->mcb_intrlv) {
			if (memc->mcb[0].mcu_intrlv && memc->mcb[1].mcu_intrlv) {	// Both Mcu Intrlv
				p_sp->num_mem_regions = 1;
				p_sp->str_addr[0] =
				    (unsigned long long)(mcu_low_base[0]
							 << 28) * 4ULL;
				p_sp->end_addr[0] =
				    (unsigned long long)p_sp->
				    str_addr[0] +
				    (4ULL * mcu_addr_size[0] *
				     0x20000000ULL) - 1ULL;
			} else {	// Neither Mcu Intrlv
				p_sp->num_mem_regions = 2;
				p_sp->str_addr[0] =
				    (unsigned long long)(mcu_low_base[0]
							 << 28) * 2ULL;
				p_sp->end_addr[0] =
				    (unsigned long long)p_sp->
				    str_addr[0] +
				    (2ULL * mcu_addr_size[0] *
				     0x20000000ULL) - 1ULL;
				p_sp->str_addr[1] =
				    (unsigned long long)(mcu_low_base[1]
							 << 28) * 2ULL;
				p_sp->end_addr[1] =
				    (unsigned long long)p_sp->
				    str_addr[1] +
				    (2ULL * mcu_addr_size[1] *
				     0x20000000ULL) - 1ULL;
			}
		} else {	// No Mcb Intrlv
			iia = 0;
			p_sp->num_mem_regions = 0;
			for (i = 0; i < 4; i += 2) {
				if (memc->mcb[0].mcu_intrlv) {
					p_sp->str_addr[iia] =
					    (unsigned long
					     long)(mcu_low_base[i] <<
						   28) * 2ULL;
					p_sp->end_addr[iia] =
					    (unsigned long long)p_sp->
					    str_addr[i] +
					    (2ULL * mcu_addr_size[i] *
					     0x20000000ULL) - 1ULL;
					iia++;
				} else {
					p_sp->str_addr[iia] =
					    (unsigned long
					     long)(mcu_low_base[i] <<
						   28);
					p_sp->end_addr[iia] =
					    (unsigned long long)p_sp->
					    str_addr[i] +
					    (mcu_addr_size[i] *
					     0x20000000ULL) - 1ULL;
					iia++;
					p_sp->str_addr[iia] =
						(unsigned long long)
						(mcu_low_base[i + 1] << 28);
					p_sp->end_addr[iia] =
					    (unsigned long long)p_sp->
					    str_addr[i + 1] +
					    (mcu_addr_size[i + 1] *
					     0x20000000ULL) - 1ULL;
					iia++;
				}
			}
			p_sp->num_mem_regions = iia;
		}
		break;
	default:
		debug
		    ("ERROR: Illegal Mcu configurations Mcu0 must be enabled \n");
		break;
		
	}
	// Print Address Region Info
#if APM_SIM
#else
	debug("INFO: %s()  mem regions = %d \n", __FUNCTION__,
	      p_sp->num_mem_regions);
	for (i = 0; i < p_sp->num_mem_regions; i++) {
#if defined(APM_VBIOS)
		debug("INFO: region %1d  startA=0x%0X  endA=0x%0X\n", i,
		      p_sp->str_addr[i], p_sp->end_addr[i]);
#else
		debug("INFO: region %1d  startA=0x%0llX  endA=0x%0llX\n", i,
		      p_sp->str_addr[i], p_sp->end_addr[i]);
#endif
	}
#endif

	// Finally Program all CSRs
	// Program CSW bits
	CSWCR_setup(memc, (((memc->full_addr & 0x1) << 2) |
			   ((memc->mcb_intrlv & 0x1) << 1) |
			   (memc->dual_mcb & 0x1)));
	debug("INFO: CSW setup  42b=%1d McbI=%1d ", memc->full_addr,
	      memc->mcb_intrlv);
	debug("DMcb=%1d\n", memc->dual_mcb);

	// 2 Mcb
	for (iia = 0; iia < CONFIG_SYS_NUM_DDR_CTLRS; iia += 2) {
		mcb_mode_setup(&memc->mcu[iia],
			       (((0x1 & memc->mcb[iia / 2].mcu_intrlv) << 3) |
				((0x1 & memc->mcb[iia / 2].dual_mcu) << 2) |
				((0x1 & memc->mcb_intrlv) << 1) |
				(0x1 & (~(memc->full_addr)))),
			       memc->mcb[iia / 2].spec_read);
		debug("INFO: Mcb[%d]  ", iia / 2);
		debug("setup  McuI=%1d  DMcu=%1d ",
		      memc->mcb[iia / 2].mcu_intrlv,
		      memc->mcb[iia / 2].dual_mcu);
		debug("McbI=%1d 32b=%1d \n", memc->mcb_intrlv,
		      (0x1 & (~(memc->full_addr))));
	}
	// Mcu Csrs
	for (iia = 0; iia < CONFIG_SYS_NUM_DDR_CTLRS; iia++) {
		mcu = (struct apm_mcu *)&(memc->mcu[iia]);
		mcu_prog_csr_rank_cfg(mcu);
	}
	debug(" EXIT: %s < \n", __FUNCTION__);
	return err;
}

unsigned int minAllowedRankHash(unsigned int hash_size,
		unsigned int rank_size,
		unsigned int rank_config,
		unsigned int rankintrlv) {
	unsigned int bout = hash_size;

	if (hash_size > 5) {
		debug("Max supported rank hash size is 2MB\n");
		hash_size = 5;
	}

	/* Calc allowed min hash size from rank info */
	switch (rank_size) {
		case 0:
		case 1:
			switch (rankintrlv) {
				case 0x0: bout = hash_size; break; // 64kB min
				case 0x1: bout = (hash_size < 1) ? 1 : hash_size; break;
				case 0x3: bout = (hash_size < 2) ? 2 : hash_size; break;
				case 0x7: bout = (hash_size < 3) ? 3 : hash_size; break;
				default: bout = (hash_size < 3) ? 3 : hash_size; break;
			}
			break;
			/*  */
		case 2:
		case 3:
			if (rank_config == 0) {
				switch (rankintrlv) {
					case 0x0: bout = (hash_size < 1) ? 1 : hash_size; break; // 128kB min
					case 0x1: bout = (hash_size < 2) ? 2 : hash_size; break;
					case 0x3: bout = (hash_size < 3) ? 3 : hash_size; break;
					case 0x7: bout = (hash_size < 4) ? 4 : hash_size; break;
					default: bout = (hash_size < 4) ? 4 : hash_size; break;
				}
			} else {
				switch (rankintrlv) {
					case 0x0: bout = hash_size; break; // 64kB min
					case 0x1: bout = (hash_size < 1) ? 1 : hash_size; break;
					case 0x3: bout = (hash_size < 2) ? 2 : hash_size; break;
					case 0x7: bout = (hash_size < 3) ? 3 : hash_size; break;
					default: bout = (hash_size < 3) ? 3 : hash_size; break;
				}
			}
			break;
			/*  */
		case 4:
			switch (rankintrlv) {
				case 0x0: bout = (hash_size < 1) ? 1 : hash_size; break; // 128kB min
				case 0x1: bout = (hash_size < 2) ? 2 : hash_size; break;
				case 0x3: bout = (hash_size < 3) ? 3 : hash_size; break;
				case 0x7: bout = (hash_size < 4) ? 4 : hash_size; break;
				default: bout = (hash_size < 4) ? 4 : hash_size; break;
			}
			break;
		case 5:
		default:
			switch (rankintrlv) {
				case 0x0: bout = (hash_size < 2) ? 2 : hash_size; break; // 256kB min
				case 0x1: bout = (hash_size < 3) ? 3 : hash_size; break;
				case 0x3: bout = (hash_size < 4) ? 4 : hash_size; break;
				case 0x7: bout = 5; break;
				default: bout = (hash_size < 5) ? 5 : hash_size; break;
			}
			break;
			/*  */
	}
	return bout;
}  /* minAllowedRankHash */

