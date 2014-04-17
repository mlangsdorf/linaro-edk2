/**
 * APM X-Gene DDR3 controller code
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

#ifdef APM_SIM
#include "apm_ddr_sdram.h"
#define debug1 debug

#elif defined(APM_VBIOS)

#include <common.h>
#ifndef CONFIG_SYS_SPD_BUS_NUM
#define CONFIG_SYS_SPD_BUS_NUM	0
#endif
#include <stdio.h>
#include <string.h>
#include <apm_ddr_sdram.h>
#include <iolib/i2c/apm_i2c.h>
#define debug1(fmt,args...)    lprintf(5, fmt ,##args)

unsigned int g_ddr_cl_margin = 0;

#elif defined(APM_TIANOCORE)

#include "apm_ddr_sdram.h"
#define debug1(fmt,args...) debug(fmt ,##args)

#else
#include <common.h>
#include <command.h>
#include <i2c.h>
#include <asm/io.h>
#include <asm/arch/apm_ddr_sdram.h>
#include "config.h"
#define debug1(fmt,args...) debug(fmt ,##args)
#endif

#define DDR_CL_MARGIN 0

#include "ddr_spd.h"
#include "ddr_lib.h"

#ifndef NULL
#define NULL 0
#endif

static int crc16(char *ptr, int count)
{
	int crc, i;

	crc = 0;
	while (--count >= 0) {
		crc = crc ^ (int)*ptr++ << 8;
		for (i = 0; i < 8; ++i)
			if (crc & 0x8000)
				crc = crc << 1 ^ 0x1021;
			else
				crc = crc << 1;
	}
	return crc & 0xffff;
}

unsigned int spd_check(spd_eeprom_t * spd)
{
	/*
	 * SPD byte0[7] - CRC coverage
	 * 0 = CRC covers bytes 0~125
	 * 1 = CRC covers bytes 0~116
	 */
	int spdcrc_chk_sum;
	int spdcrc_cs_len;
	char spdcrc_crc_lsb;	/* byte 126 */
	char spdcrc_crc_msb;	/* byte 127 */
	char spdcrc_rd_crclsb;	/* byte 126 */
	char spdcrc_rd_crcmsb;	/* byte 127 */

	if ((spd->info_size_crc) & 0x80)
		spdcrc_cs_len = 117;
	else
		spdcrc_cs_len = 126;
	spdcrc_chk_sum = crc16((char *)spd, spdcrc_cs_len);

	spdcrc_crc_lsb = (unsigned char)(spdcrc_chk_sum & 0xff);
	spdcrc_crc_msb = (unsigned char)(spdcrc_chk_sum >> 8);

	spdcrc_rd_crclsb = spd->crc[0];	//*(spd+126);
	spdcrc_rd_crcmsb = spd->crc[1];	//*(spd+127);

	if ((spdcrc_rd_crclsb == spdcrc_crc_lsb)
	    && (spdcrc_rd_crcmsb == spdcrc_crc_msb)) {
		return 0;
	} else {
		debug("SPD checksum unexpected.\n"
		      "Checksum lsb in SPD = %02X, computed SPD = %02X\n"
		      "Checksum msb in SPD = %02X, computed SPD = %02X\n",
		      spdcrc_rd_crclsb, spdcrc_crc_lsb, spdcrc_rd_crcmsb,
		      spdcrc_crc_msb);
		return 2;
	}
}

#if APM_SIM
unsigned int __ilog2(unsigned long x)
#else
static __inline__ unsigned int __ilog2(unsigned long x)
#endif
{
	int i;

	if (x == 0)
		return 0;

	for (i = 0; x != 0; i++)
		x >>= 1;

	return i - 1;
}

/*
 * Board-specific Platform code can reimplement spd_ddr_init_hang () if needed
 */
void spd_ddr_init_hang(void)
{
	while (1) ;
}

#if 0
unsigned char spd_read(unsigned char chip, unsigned int addr)
{
	unsigned char data[2] = { 0, 0 };

	if (0 != i2c_read(chip, addr, 1, data, 1)) {
		debug("spd_read(0x%02X, 0x%02X) failed\n", chip, addr);
		return -1;
	}
	debug("spd_read(0x%02X, 0x%02X) data 0x%02X\n", chip, addr, data[0]);
	return data[0];
}
#endif

void print_spd_info(unsigned char *spd)
{
#if !defined(APM_TIANOCORE)
	unsigned char *ptr = 0;
	unsigned char i;
	ptr = ((spd_eeprom_t *) spd)->mpart;
	debug1("\tDIMM Vendor : 0x%X%X\n", ((spd_eeprom_t *) spd)->dmid_lsb,
	       ((spd_eeprom_t *) spd)->dmid_msb);
	debug1("\tDIMM Part : ");
	debug1("%c", (*ptr++));
	for (i = 0; i < 18; i++)
		debug1("%c", (*ptr++));
	debug1("\n\t");
	switch (((spd_eeprom_t *) spd)->module_type & 0xf) {
	case 0x01:		/* RDIMM */
		debug1("RDIMM: ");
		break;
	case 0x05:		/* Mini-RDIMM */
		debug1("Mini-RDIMM: ");
		break;
	case 0x02:		/* UDIMM */
		debug1("UDIMM: ");
		break;
	case 0x03:		/* SO-DIMM */
	case 0x08:		/* SO-DIMM */
		debug1("SODIMM: ");
		break;
	case 0x04:		/* Micro-DIMM */
		debug1("Micro-DIMM: ");
		break;
	case 0x06:		/* Mini-UDIMM */
		debug1("Mini-UDIMM ");
		break;
	case 0x0B:		/* LRDIMM */
		debug1("LRDIMM: ");
		break;
	default:
		debug1("Unknown DIMM: ");
		break;
	}
	debug1("%dMB/rank\n",
	       (int)(compute_ranksize((spd_eeprom_t *) spd) / (1024 * 1024)));
	debug1("\n");
#endif
}

unsigned char spd_read(unsigned int addr, unsigned int size)
{
	return SPD_MEMTYPE_DDR3;
}

unsigned int get_spd(void *p, unsigned int slot)
{

	struct apm_mcu *mcu = (struct apm_mcu *)p;
	generic_spd_eeprom_t *spd;
	unsigned char dimm_type = 0;
	unsigned char i2c_address;
	int err;

	spd = &mcu->spd_info[slot];
	err = 0;
#ifdef APM_VBIOS
	i2c_set_bus_num(1);
	DELAY(100);
	err += i2c_set_bus_speed(CONFIG_SYS_I2C_SPEED);
	DELAY(100);
#endif
	memset(spd, 0, sizeof(generic_spd_eeprom_t));
	if (err)
		return 0;

	/*
	 * If a mux is provisioned, set the mux correctly first
	 */
	if (mcu->spd_mux != 0) {
		if (i2c_write(mcu->spd_mux, 0, 1, &mcu->spd_mux_addr, 1)) {
			debug("Can not send comment to MUX");
			return 0;
		}
	}

	i2c_address = mcu->spd_addr[slot];

	/*
	 * If no spd address, assume not populated
	 */
	if (i2c_address == 0)
		return 0;

	dimm_type = 0;
	/* Check for DIMM type before reading */
	err = i2c_read(i2c_address, 2, 1, &dimm_type, 1);
	if (dimm_type == SPD_MEMTYPE_DDR3) {
		debug1("MCU[%d]-Slot[%d]-DDR3-DIMM-FOUND\n", mcu->id, slot);
		debug("\tReading DIMM SPD data @0x%llx...\n",
		      (unsigned long long)spd);

		err += i2c_read(i2c_address, 0, 1, (unsigned char *)spd,
				sizeof(spd_eeprom_t));
	} else {
		debug("\tMCU[%d]-Slot[%d]-NO-DIMM\n", mcu->id, slot);
		return 0;
	}

	if (err == 0) {
		print_spd_info((unsigned char *)spd);
		return 1;
	}

	return 0;
}

/*
 * DDR3 releated compute dimm param functions
 */
unsigned long long compute_ranksize(spd_eeprom_t * spd)
{
	unsigned long long bsize;

	int nbit_sdram_cap_bsize = 0;
	int nbit_primary_bus_width = 0;
	int nbit_sdram_width = 0;

	if ((spd->density_banks & 0xf) < 7)
		nbit_sdram_cap_bsize = (spd->density_banks & 0xf) + 28;
	if ((spd->bus_width & 0x7) < 4)
		nbit_primary_bus_width = (spd->bus_width & 0x7) + 3;
	if ((spd->organization & 0x7) < 4)
		nbit_sdram_width = (spd->organization & 0x7) + 2;

	bsize = 1ULL << (nbit_sdram_cap_bsize - 3
			 + nbit_primary_bus_width - nbit_sdram_width);

//        debug("DDR: DDR III rank density = 0x%16llx\n", bsize);
//      debug("DDR: DDR III rank density = 0x%x\n", bsize);

	return bsize;
}

unsigned int rdiv(unsigned int a, unsigned int b)
{
	unsigned int temp;

	temp = (a * 10) / b;

	if ((temp % 10) != 0)
		temp = temp + 10;

	return temp / 10;
}

/*
 * compute_dimm_parameters for DDR3 SPD
 *
 * Compute DIMM parameters based upon the SPD information in spd.
 * Writes the results to the dimm_params_t structure pointed by pdimm.
 *
 */
unsigned int compute_dimm_parameters(void *p, unsigned int dimm_number)
{
	unsigned int retval;
	unsigned int mtb_ps;
	unsigned int i;
	generic_spd_eeprom_t *spd;
	dimm_params_t *pdimm;
	struct apm_mcu *mcu = (struct apm_mcu *)p;

	spd = &mcu->spd_info[dimm_number];
	pdimm = &mcu->dimm_params[dimm_number];
	debug("\nCompute DIMMS prameters for MCU[%d]-DIMM[%d] ---\n", mcu->id,
	      dimm_number);
	if (spd->mem_type) {
		if (spd->mem_type != SPD_MEMTYPE_DDR3) {
			debug("DIMM %u: is not a DDR3 SPD.\n", dimm_number);
			return 1;
		}
	} else {
		memset((char *)pdimm, 0, sizeof(dimm_params_t));
		return 1;
	}

	retval = spd_check(spd);
	if (retval) {
		debug1("\tDIMM %u: failed checksum\n", dimm_number);
	} else {
		debug1("\tDIMM %u: SPD checksum pass\n", dimm_number);
	}
	/*
	 * The part name in ASCII in the SPD EEPROM is not null terminated.
	 * Guarantee null termination here by presetting all bytes to 0
	 * and copying the part name in ASCII from the SPD onto it
	 */
	for (i = 0; i < sizeof(pdimm->mpart) - 1; i++)
		pdimm->mpart[i] = spd->mpart[i];
	pdimm->mpart[i - 1] = 0;

	/* DIMM organization parameters */
	pdimm->n_ranks = ((spd->organization >> 3) & 0x7) + 1;
	pdimm->component_width = 0x1 << ((spd->organization & 0x7) + 2);
	pdimm->rank_density = compute_ranksize((spd_eeprom_t *) spd);
	pdimm->capacity = pdimm->n_ranks * pdimm->rank_density;
	debug("\tDIMM Capacity (%d ranks): total 0x%llx\n", pdimm->n_ranks,
	      pdimm->capacity);
	pdimm->primary_sdram_width = 1 << (3 + (spd->bus_width & 0x7));
	if ((spd->bus_width >> 3) & 0x3)
		pdimm->ec_sdram_width = 8;
	else
		pdimm->ec_sdram_width = 0;
	pdimm->data_width = pdimm->primary_sdram_width + pdimm->ec_sdram_width;

	switch (spd->module_type & 0xf) {
	case 0x01:		/* RDIMM */
	case 0x05:		/* Mini-RDIMM */
		debug("\tRegister DIMM detected: Type 0x%X\n",
		      spd->module_type & 0xf);
		pdimm->registered_dimm = 1;	/* register buffered */
		break;

	case 0x0B:		/* LRDIMM */
		debug("\tLRDIMM detected: Type 0x%X\n", spd->module_type & 0xf);
		pdimm->registered_dimm = 1;	/* register buffered */
		break;

	case 0x02:		/* UDIMM */
	case 0x03:		/* SO-DIMM */
	case 0x08:		/* SO-DIMM */
	case 0x04:		/* Micro-DIMM */
	case 0x06:		/* Mini-UDIMM */
		debug("\tUnbuffered DIMM detected: Type 0x%X\n",
		      spd->module_type & 0xf);
		pdimm->registered_dimm = 0;	/* unbuffered */
		break;

	default:
		debug("\tUnknown dimm_type 0x%02X\n", spd->module_type);
		return 1;
	}

	/* SDRAM device parameters */
	pdimm->n_row_addr = ((spd->addressing >> 3) & 0x7) + 12;
	pdimm->n_col_addr = (spd->addressing & 0x7) + 9;
	pdimm->n_banks_per_sdram_device =
	    8 << ((spd->density_banks >> 4) & 0x7);
	debug("\tAddressing: Row: %d Col: %d Bank: %d\n", pdimm->n_row_addr,
	      pdimm->n_col_addr, pdimm->n_banks_per_sdram_device);

	/*
	 * The SPD spec has not the ECC bit,
	 * We consider the DIMM as ECC capability
	 * when the extension bus exist
	 */
	if (pdimm->ec_sdram_width)
		pdimm->edc_config = 0x02;
	else
		pdimm->edc_config = 0x00;

	/*
	 * The SPD spec has not the burst length byte
	 * but DDR3 spec has nature BL8 and BC4,
	 * BL8 -bit3, BC4 -bit2
	 */
	pdimm->burst_lengths_bitmask = 0x0c;
	pdimm->row_density = __ilog2(pdimm->rank_density);

	/* MTB - medium timebase
	 * The unit in the SPD spec is ns,
	 * We convert it to ps.
	 * eg: MTB = 0.125ns (125ps)
	 */
	mtb_ps = (spd->mtb_dividend * 1000) / spd->mtb_divisor;
	pdimm->mtb_ps = mtb_ps;
	debug("\tMTB(ps): %d\n", mtb_ps);

	/*
	 * sdram minimum cycle time
	 * we assume the MTB is 0.125ns
	 * eg:
	 * tCK_min=15 MTB (1.875ns) ->DDR3-1066
	 *        =12 MTB (1.5ns) ->DDR3-1333
	 *        =10 MTB (1.25ns) ->DDR3-1600
	 */
	pdimm->tCKmin_X_ps = (spd->tCK_min * mtb_ps);
	debug("\tCK min(ps): %d (min-supported by DIMM)\n", pdimm->tCKmin_X_ps);
	/*
	 * CAS latency supported
	 * bit4 - CL4
	 * bit5 - CL5
	 * bit18 - CL18
	 */
	pdimm->caslat_X = ((spd->caslat_msb << 8) | spd->caslat_lsb) << 4;
	debug("\tSPD CAS Latency: 0x%4x\n", pdimm->caslat_X);

	/*
	 * min CAS latency time
	 * eg: tAA_min =
	 * DDR3-800D    100 MTB (12.5ns)
	 * DDR3-1066F   105 MTB (13.125ns)
	 * DDR3-1333H   108 MTB (13.5ns)
	 * DDR3-1600H   90 MTB (11.25ns)
	 */
	pdimm->tAA_ps = spd->tAA_min * mtb_ps;
	debug("\tAA min(ps): %d\n", pdimm->tAA_ps);

	/*
	 * min write recovery time
	 * eg:
	 * tWR_min = 120 MTB (15ns) -> all speed grades.
	 */
	pdimm->tWR_ps = spd->tWR_min * mtb_ps;
	debug("\tWR min(ps): %d\n", pdimm->tWR_ps);

	/*
	 * min RAS to CAS delay time
	 * eg: tRCD_min =
	 * DDR3-800     100 MTB (12.5ns)
	 * DDR3-1066F   105 MTB (13.125ns)
	 * DDR3-1333H   108 MTB (13.5ns)
	 * DDR3-1600H   90 MTB (11.25)
	 */
	pdimm->tRCD_ps = spd->tRCD_min * mtb_ps;
	debug("\tRCD min(ps): %d\n", pdimm->tRCD_ps);

	/*
	 * min row active to row active delay time
	 * eg: tRRD_min =
	 * DDR3-800(1KB page)   80 MTB (10ns)
	 * DDR3-1333(1KB page)  48 MTB (6ns)
	 */
	pdimm->tRRD_ps = spd->tRRD_min * mtb_ps;
	debug("\tRRD min(ps): %d\n", pdimm->tRRD_ps);

	/*
	 * min row precharge delay time
	 * eg: tRP_min =
	 * DDR3-800D    100 MTB (12.5ns)
	 * DDR3-1066F   105 MTB (13.125ns)
	 * DDR3-1333H   108 MTB (13.5ns)
	 * DDR3-1600H   90 MTB (11.25ns)
	 */
	pdimm->tRP_ps = spd->tRP_min * mtb_ps;
	debug("\tRP min(ps): %d\n", pdimm->tRP_ps);

	/* min active to precharge delay time
	 * eg: tRAS_min =
	 * DDR3-800D    300 MTB (37.5ns)
	 * DDR3-1066F   300 MTB (37.5ns)
	 * DDR3-1333H   288 MTB (36ns)
	 * DDR3-1600H   280 MTB (35ns)
	 */
	pdimm->tRAS_ps = (((spd->tRAS_tRC_ext & 0xf) << 8) | spd->tRAS_min_lsb)
	    * mtb_ps;
	debug("\tRAS min(ps): %d\n", pdimm->tRAS_ps);
	/*
	 * min active to actice/refresh delay time
	 * eg: tRC_min =
	 * DDR3-800D    400 MTB (50ns)
	 * DDR3-1066F   405 MTB (50.625ns)
	 * DDR3-1333H   396 MTB (49.5ns)
	 * DDR3-1600H   370 MTB (46.25ns)
	 */
	pdimm->tRC_ps = (((spd->tRAS_tRC_ext & 0xf0) << 4) | spd->tRC_min_lsb)
	    * mtb_ps;
	debug("\tRC min(ps): %d\n", pdimm->tRC_ps);
	/*
	 * min refresh recovery delay time
	 * eg: tRFC_min =
	 * 512Mb        720 MTB (90ns)
	 * 1Gb          880 MTB (110ns)
	 * 2Gb          1280 MTB (160ns)
	 */
	pdimm->tRFC_ps = ((spd->tRFC_min_msb << 8) | spd->tRFC_min_lsb)
	    * mtb_ps;
	debug("\tRFC min(ps): %d\n", pdimm->tRFC_ps);

	/*
	 * min internal write to read command delay time
	 * eg: tWTR_min = 40 MTB (7.5ns) - all speed bins.
	 * tWRT is at least 4 mclk independent of operating freq.
	 */
	pdimm->tWTR_ps = spd->tWTR_min * mtb_ps;
	debug("\tWTR (ps): %d\n", pdimm->tWTR_ps);

	/*
	 * min internal read to precharge command delay time
	 * eg: tRTP_min = 40 MTB (7.5ns) - all speed bins.
	 * tRTP is at least 4 mclk independent of operating freq.
	 */
	pdimm->tRTP_ps = spd->tRTP_min * mtb_ps;
	debug("\tRTP (ps): %d\n", pdimm->tRTP_ps);

	/*
	 * Average periodic refresh interval
	 * tREFI = 7.8 us at normal temperature range
	 *       = 3.9 us at ext temperature range
	 */
	pdimm->refresh_rate_ps = (7800U * 8 * mtb_ps);	// div by tclks is done while calculating actual ref-int for CSR
	debug("\tREF-INT (ps): %d\n", pdimm->refresh_rate_ps);

	/*
	 * min four active window delay time
	 * eg: tFAW_min =
	 * DDR3-800(1KB page)   320 MTB (40ns)
	 * DDR3-1066(1KB page)  300 MTB (37.5ns)
	 * DDR3-1333(1KB page)  240 MTB (30ns)
	 * DDR3-1600(1KB page)  240 MTB (30ns)
	 */
	pdimm->tFAW_ps = (((spd->tFAW_msb & 0xf) << 8) | spd->tFAW_min)
	    * mtb_ps;
	debug("\tFAW (ps): %d\n", pdimm->tFAW_ps);

	/*
	 * We need check the address mirror for unbuffered DIMM
	 * If SPD indicate the address map mirror, The DDR controller
	 * need care it.
	 */
	if ((spd->module_type == SPD_MODULETYPE_UDIMM) ||
	    (spd->module_type == SPD_MODULETYPE_SODIMM) ||
	    (spd->module_type == SPD_MODULETYPE_MICRODIMM) ||
	    (spd->module_type == SPD_MODULETYPE_MINIUDIMM)) {
		pdimm->mirrored_dimm =
		    spd->mod_section.unbuffered.addr_mapping & 0x1;
		debug("\tAddress Mirrored DIMM\n");
	}

	/*
	 * RDIMM R/C programming
	 */
	if (pdimm->registered_dimm == 1) {
		pdimm->rca = 0;
		pdimm->rca = spd->mod_section.uc[9];
		pdimm->rca |= spd->mod_section.uc[10] << 8;
		pdimm->rca |= spd->mod_section.uc[11] << 16;
		pdimm->rca |= spd->mod_section.uc[12] << 24;

		pdimm->rcb = 0;
		pdimm->rcb = spd->mod_section.uc[13];
		pdimm->rcb |= spd->mod_section.uc[14] << 8;
	}
	debug("\n");
	return retval;
}

#if 0
void compute_dimm_info(struct apm_ddr_info_s *ddr_info)
{
	unsigned char iic0_dimm_addr[] = SPD_EEPROM_ADDRESS;
	/*
	 * Get spd information from the dimm.
	 */
	ddr_info->dimm_addr[0][0] = iic0_dimm_addr[0];
	get_spd(ddr_info->spd_info[0], ddr_info->dimm_addr[0][0]);
#ifdef DEBUG
	DUMP_SPD_INFO((unsigned char *)ddr_info->spd_info[0]);
#endif

	if (ddr3_compute_dimm_parameters(ddr_info->spd_info[0],
					 ddr_info->dimm_params[0], 0)) {
		SPD_DBG_PRINT("Incorrect DIMM parameters\n");
		hang();
	}

}

static unsigned long get_tcyc(unsigned char reg)
{
	/*
	 * Byte 9, et al: Cycle time for CAS Latency=X, is split into two
	 * nibbles: the higher order nibble (bits 4-7) designates the cycle time
	 * to a granularity of 1ns; the value presented by the lower order
	 * nibble (bits 0-3) has a granularity of .1ns and is added to the value
	 * designated by the higher nibble. In addition, four lines of the lower
	 * order nibble are assigned to support +.25, +.33, +.66, and +.75.
	 */

	unsigned char subfield_b = reg & 0x0F;

	switch (subfield_b & 0x0F) {
	case 0x0:
	case 0x1:
	case 0x2:
	case 0x3:
	case 0x4:
	case 0x5:
	case 0x6:
	case 0x7:
	case 0x8:
	case 0x9:
		return 1000 * (reg >> 4) + 100 * subfield_b;
	case 0xA:
		return 1000 * (reg >> 4) + 250;
	case 0xB:
		return 1000 * (reg >> 4) + 333;
	case 0xC:
		return 1000 * (reg >> 4) + 667;
	case 0xD:
		return 1000 * (reg >> 4) + 750;
	}
	return 0;
}

/**
 * For the memory DIMMs installed, this routine verifies that
 * frequency previously calculated is supported.
 */
static int check_frequency(unsigned long *dimm_ranks,
			   unsigned char const iic0_dimm_addr[],
			   unsigned long num_dimm_banks,
			   unsigned long sdram_freq)
{
	unsigned long dimm_num;
	unsigned long cycle_time = 0;
	unsigned long calc_cycle_time;

	/*
	 * calc_cycle_time is calculated from DDR frequency set by board/chip
	 * and is expressed in picoseconds to match the way DIMM cycle time is
	 * calculated below.
	 */
	calc_cycle_time = MULDIV64(ONE_BILLION, 1000, sdram_freq);

	for (dimm_num = 0; dimm_num < num_dimm_banks; dimm_num++) {
		if (dimm_ranks[dimm_num]) {
			cycle_time =
			    get_tcyc(spd_read(iic0_dimm_addr[dimm_num], 9));
			debug("cycle_time: %lu ps\n", cycle_time);

			if (cycle_time > (calc_cycle_time + 10)) {
				/*
				 * the provided sdram cycle_time is too small
				 * for the available DIMM cycle_time. The
				 * additional 10ps is here to accept a small
				 * uncertainty.
				 */
				debug("ERROR: DRAM DIMM detected with "
				      "cycle_time %d ps in slot %d \n while "
				      "calculated cycle time is %d ps.\n",
				      (unsigned int)cycle_time,
				      (unsigned int)dimm_num,
				      (unsigned int)calc_cycle_time);
				debug("Replace the DIMM, or change DDR "
				      "frequency via strapping bits.\n\n");
				spd_ddr_init_hang();
			}
		}
	}
	return (1000000 / cycle_time);
}

/**
 * This routine gets size information for the installed memory
 * DIMMs.
 */
static void get_dimm_size(unsigned long dimm_ranks[],
			  unsigned char const iic0_dimm_addr[],
			  unsigned long num_dimm_banks,
			  unsigned long *const rows,
			  unsigned long *const banks,
			  unsigned long *const cols, unsigned long *const width)
{
	unsigned long dimm_num;

	*rows = 0;
	*banks = 0;
	*cols = 0;
	*width = 0;
	for (dimm_num = 0; dimm_num < num_dimm_banks; dimm_num++) {
		unsigned long t;
		if (!dimm_ranks[dimm_num])
			continue;

		/* Rows */
		t = spd_read(iic0_dimm_addr[dimm_num], 3);
		if (0 == *rows) {
			*rows = t;
		} else if (t != *rows) {
			debug("ERROR: DRAM DIMM modules do not all "
			      "have the same number of rows.\n\n");
			spd_ddr_init_hang();
		}
		/* Banks */
		t = spd_read(iic0_dimm_addr[dimm_num], 17);
		if (0 == *banks) {
			*banks = t;
		} else if (t != *banks) {
			debug("ERROR: DRAM DIMM modules do not all "
			      "have the same number of banks.\n\n");
			spd_ddr_init_hang();
		}
		/* Columns */
		t = spd_read(iic0_dimm_addr[dimm_num], 4);
		if (0 == *cols) {
			*cols = t;
		} else if (t != *cols) {
			debug("ERROR: DRAM DIMM modules do not all "
			      "have the same number of columns.\n\n");
			spd_ddr_init_hang();
		}
		/* Data width */
		t = spd_read(iic0_dimm_addr[dimm_num], 6);
		if (0 == *width) {
			*width = t;
		} else if (t != *width) {
			debug("ERROR: DRAM DIMM modules do not all "
			      "have the same data width.\n\n");
			spd_ddr_init_hang();
		}
	}
	debug("Number of rows: %lu\n", *rows);
	debug("Number of columns: %lu\n", *cols);
	debug("Number of banks: %lu\n", *banks);
	debug("Data width: %lu\n", *width);
	if (*rows > 14) {
		debug("ERROR: DRAM DIMM modules have %lu address rows.\n",
		      *rows);
		debug("Only modules with 14 or fewer rows are supported.\n\n");
		spd_ddr_init_hang();
	}
	if (4 != *banks && 8 != *banks) {
		debug("ERROR: DRAM DIMM modules have %lu banks.\n", *banks);
		debug("Only modules with 4 or 8 banks are supported.\n\n");
		spd_ddr_init_hang();
	}
	if (*cols > 12) {
		debug("ERROR: DRAM DIMM modules have %lu address columns.\n",
		      *cols);
		debug("Only modules with 12 or fewer columns are "
		      "supported.\n\n");
		spd_ddr_init_hang();
	}
	if (32 != *width && 40 != *width && 64 != *width && 72 != *width) {
		debug("ERROR: DRAM DIMM modules have a width of %lu bit.\n",
		      *width);
		debug("Only modules with widths of 32, 40, 64, and 72 bits "
		      "are supported.\n\n");
		spd_ddr_init_hang();
	}
}

/**
 * Only 1.8V modules are supported.  This routine verifies this.
 */
static void check_voltage_type(unsigned long dimm_ranks[],
			       unsigned char const iic0_dimm_addr[],
			       unsigned long num_dimm_banks)
{
	unsigned long dimm_num;
	unsigned long voltage_type;

	for (dimm_num = 0; dimm_num < num_dimm_banks; dimm_num++) {
		if (!dimm_ranks[dimm_num])
			continue;

		voltage_type = spd_read(iic0_dimm_addr[dimm_num], 8);
		if (0x05 != voltage_type) {	/* 1.8V for DDR2 */
			debug("ERROR: Slot %lu provides 1.8V for DDR2 "
			      "DIMMs.\n", dimm_num);
			switch (voltage_type) {
			case 0x00:
				debug("This DIMM is 5.0 Volt/TTL.\n");
				break;
			case 0x01:
				debug("This DIMM is LVTTL.\n");
				break;
			case 0x02:
				debug("This DIMM is 1.5 Volt.\n");
				break;
			case 0x03:
				debug("This DIMM is 3.3 Volt/TTL.\n");
				break;
			case 0x04:
				debug("This DIMM is 2.5 Volt.\n");
				break;
			default:
				debug("This DIMM is an unknown " "voltage.\n");
				break;
			}
			debug("Replace it with a 1.8V DDR2 DIMM.\n\n");
			spd_ddr_init_hang();
		}
	}
}
#endif

/*
 * Round mclk_ps to nearest 10 ps in memory controller code.
 *
 * If an imprecise data rate is too high due to rounding error
 * propagation, compute a suitably rounded mclk_ps to compute
 * a working memory controller configuration.
 */
unsigned int get_memory_clk_period_ps(void *p)
{
	unsigned int mclk_ps, freqDDR;
	struct apm_mcu *mcu = (struct apm_mcu *)p;
//      debug(" ENTRY: %s >>>> \n", __FUNCTION__);
#if 1
	/* We need to get the DDR freq here */
	freqDDR = 1000000ULL * mcu->mcu_params.clk_mhz_pll;
	/* mclk_ps x 10 = 10,000,000,000,000 / freqDDR. We accomplish this with 32-bit operations */
	mclk_ps = (100 * 1000000000000ULL / freqDDR);

//      debug("DDR Frequency (ps): %d rounded %d freq is %d\n",
//            (mclk_ps + 55) / 100, mclk_ps, freqDDR);
	/* Round to nearest 10 ps */
	mclk_ps = (mclk_ps + 55) / 100;
#else
	mclk_ps = (1000000ULL * ((mcu->mcu_params.speed) / 2));
	freqDDR = (1000000000000ULL / mclk_ps)
//          debug("DDR Frequency (ps): %d freq is %d\n", mclk_ps, freqDDR);
	    /* Round to nearest 10 ps */
#endif
//      debug(" EXIT: %s >>>> \n", __FUNCTION__);
	    return (mclk_ps);
}

unsigned int time_ps_to_clk(void *p, unsigned int time_ps)
{
	unsigned int mclk_ps, freqDDR;
	struct apm_mcu *mcu = (struct apm_mcu *)p;
	/* We need to get the DDR freq here */
	freqDDR = 1000000ULL * mcu->mcu_params.clk_mhz_pll;
	/* mclk_ps = 2,000,000,000,000 / freqDDR. We accomplish this with 32-bit operations */
	mclk_ps = (1000000000000ULL / freqDDR);
	time_ps = time_ps * 10 / mclk_ps;

	if ((time_ps % 10) == 0)
		return time_ps / 10;
	else
		return (time_ps + 10) / 10;
}

unsigned int mclk_to_picos(void *p, unsigned int mclk)
{
	return get_memory_clk_period_ps(p) * mclk;
}

/* 
 * compute the CAS write latency according to DDR3 spec
 * CWL = 5 if tCK >= 2.5ns
 *       6 if 2.5ns > tCK >= 1.875ns
 *       7 if 1.875ns > tCK >= 1.5ns
 *       8 if 1.5ns > tCK >= 1.25ns
 */
unsigned int compute_cas_write_latency(void *p)
{
	unsigned int cwl;
	const unsigned int mclk_ps = get_memory_clk_period_ps(p);

//      debug(" ENTRY: %s >>> \n", __FUNCTION__);
	if (mclk_ps >= 2500)	//800
		cwl = 5;
	else if (mclk_ps >= 1875)	//1066
		cwl = 6;
	else if (mclk_ps >= 1500)	//1333
		cwl = 7;
	else if (mclk_ps >= 1250)	//1600
		cwl = 8;
	else if (mclk_ps >= 1071)	//1866
		cwl = 9;
	else if (mclk_ps >= 937)	//2133
		cwl = 10;
	else if (mclk_ps >= 833)	//2400
		cwl = 11;
	else
		cwl = 8;

//      debug(" EXIT: %s <<< \n", __FUNCTION__);
	return cwl;
}

unsigned int compute_cas_latency(void *p)
{
	unsigned int i;
//      debug(" ENTRY: %s >>> \n", __FUNCTION__);
	unsigned int tAAmin_ps = 0;
	unsigned int tCKmin_X_ps = 0;
	unsigned int common_caslat;
	unsigned int caslat_actual;
	unsigned int retry = 16;
	unsigned int tmp;
	unsigned int mclk_ps;
	unsigned int cl_margin;
	unsigned int activeslots;
	dimm_params_t *dp;
	timing_params_t *tp;
	struct apm_mcu *mcu = (struct apm_mcu *)p;

	mclk_ps = get_memory_clk_period_ps(mcu);
	activeslots = mcu->mcu_params.activeslots;
	tp = &mcu->timing_params;

#ifdef APM_VBIOS
	cl_margin = g_ddr_cl_margin;
#else
	cl_margin = DDR_CL_MARGIN;
#endif

	/* compute the common CAS latency supported between slots */
	tmp = 0;
	for (i = 0; i < CONFIG_SYS_NO_OF_DIMMS; i++) {
		if (!((activeslots >> i) & 0x1)) {
			continue;
		}
		dp = &mcu->dimm_params[i];
		if (!tmp)
			tmp = dp->caslat_X;
		else
			tmp |= dp->caslat_X;
	}
	if (!tmp) {
		debug("No cas latency for any slot on this mcu\n");
		return 1;
	}
	common_caslat = tmp;

	/* compute the max tAAmin tCKmin between slots */
	for (i = 0; i < CONFIG_SYS_NO_OF_DIMMS; i++) {
		if (!((activeslots >> i) & 0x1)) {
			continue;
		}
		dp = &mcu->dimm_params[i];
		tAAmin_ps = max(tAAmin_ps, dp->tAA_ps);
		tCKmin_X_ps = max(tCKmin_X_ps, dp->tCKmin_X_ps);
	}
	/* validate if the memory clk is in the range of dimms */
	//if (mclk_ps < tCKmin_X_ps) {  /*FIXME*/
	if ((mclk_ps + 1) < tCKmin_X_ps) {
		debug("The DIMM max tCKmin is %d ps, "
		      "doesn't support the MCLK cycle %d ps\n",
		      tCKmin_X_ps, mclk_ps);
#ifdef APM_VBIOS
    if (g_ddr_pll_force)
      debug("Ignoring warning...\n");
    else
      return 1;
#else
#ifndef PLL_FORCE
		return 1;
#else
		debug("Ignoring warning...\n");
#endif
#endif
	}
	/* determine the acutal cas latency */
	caslat_actual = (tAAmin_ps + mclk_ps - 1) / mclk_ps;
	/* check if the dimms support the CAS latency */
	while (!(common_caslat & (1 << caslat_actual)) && retry > 0) {
		caslat_actual++;
		retry--;
	}
	/* once the caculation of caslat_actual is completed
	 * we must verify that this CAS latency value does not
	 * exceed tAAmax, which is 20 ns for all DDR3 speed grades
	 */
	if (caslat_actual * mclk_ps > 20000) {
		debug("The choosen cas latency %d is too large\n",
		      caslat_actual);
		return 1;
	}
	tp->lowest_common_SPD_caslat = caslat_actual + cl_margin;

	debug("\tLowest common CAS latency: %d\n", caslat_actual);

//      debug(" EXIT: %s <<< \n", __FUNCTION__);
	return 0;
}

/*
 * compute_timing_params
 *
 * This will derive the timing parameters from dimm parameters
 */
unsigned int compute_timing_params(void *p)
{
	unsigned int i;

//      debug(" ENTRY: %s >> \n", __FUNCTION__);
	unsigned int tCKmin_X_ps = 0;
	unsigned int tCKmax_ps = 0xFFFFFFFF;
	unsigned int tCKmax_max_ps = 0;
	unsigned int tRCD_ps = 0;
	unsigned int tRP_ps = 0;
	unsigned int tRAS_ps = 0;
	unsigned int tWR_ps = 0;
	unsigned int tWTR_ps = 0;
	unsigned int tRFC_ps = 0;
	unsigned int tRRD_ps = 0;
	unsigned int tRC_ps = 0;
	unsigned int tFAW_ps = 0;
	unsigned int refresh_rate_ps = 0xFFFFFFFF;	//#S# 0
	unsigned int tIS_ps = 0;
	unsigned int tIH_ps = 0;
	unsigned int tDS_ps = 0;
	unsigned int tDH_ps = 0;
	unsigned int tRTP_ps = 0;
	unsigned int tDQSQ_max_ps = 0;
	unsigned int tQHS_ps = 0;

	unsigned int temp1, temp2;
	unsigned int additive_latency = 0;

	unsigned int activeslots;
	dimm_params_t *dimm_params = NULL;
	struct apm_mcu *mcu = (struct apm_mcu *)p;
	timing_params_t *tp;

	activeslots = mcu->mcu_params.activeslots;

	if (!activeslots) {
		debug("no dimms this memory controller\n");
		return 0;
	}

	for (i = 0; i < CONFIG_SYS_DIMM_SLOTS_PER_CTLR; i++) {
		/*
		 * If there are no ranks on this DIMM,
		 * it probably doesn't exist, so skip it.
		 */
		if (!((activeslots >> i) & 0x1)) {
			continue;
		}

		dimm_params = &mcu->dimm_params[i];

		/*
		 * Find minimum tCKmax_ps to find fastest slow speed,
		 * i.e., this is the slowest the whole system can go.
		 */
		tCKmax_ps = min(tCKmax_ps, dimm_params->tCKmax_ps);

		/* Either find maximum value to determine slowest
		 * speed, delay, time, period, etc */
		tCKmin_X_ps = max(tCKmin_X_ps, dimm_params->tCKmin_X_ps);
		tCKmax_max_ps = max(tCKmax_max_ps, dimm_params->tCKmax_ps);
		tRCD_ps = max(tRCD_ps, dimm_params->tRCD_ps);
		tRP_ps = max(tRP_ps, dimm_params->tRP_ps);
		tRAS_ps = max(tRAS_ps, dimm_params->tRAS_ps);
		tWR_ps = max(tWR_ps, dimm_params->tWR_ps);
		tWTR_ps = max(tWTR_ps, dimm_params->tWTR_ps);
		tRFC_ps = max(tRFC_ps, dimm_params->tRFC_ps);
		tRRD_ps = max(tRRD_ps, dimm_params->tRRD_ps);
		tRC_ps = max(tRC_ps, dimm_params->tRC_ps);
		tFAW_ps = max(tFAW_ps, dimm_params->tFAW_ps);
		tIS_ps = max(tIS_ps, dimm_params->tIS_ps);
		tIH_ps = max(tIH_ps, dimm_params->tIH_ps);
		tDS_ps = max(tDS_ps, dimm_params->tDS_ps);
		tDH_ps = max(tDH_ps, dimm_params->tDH_ps);
		tRTP_ps = max(tRTP_ps, dimm_params->tRTP_ps);
		tQHS_ps = max(tQHS_ps, dimm_params->tQHS_ps);
		//#S# refresh_rate_ps = max(refresh_rate_ps, dimm_params->refresh_rate_ps);
		refresh_rate_ps =
		    min(refresh_rate_ps, dimm_params->refresh_rate_ps);

		/*
		 * Find maximum tDQSQ_max_ps to find slowest.
		 *
		 * FIXME: is finding the slowest value the correct
		 * strategy for this parameter?
		 */
		tDQSQ_max_ps = max(tDQSQ_max_ps, dimm_params->tDQSQ_max_ps);

	}

	tp = &mcu->timing_params;

	tp->tCKmin_X_ps = tCKmin_X_ps;
	tp->tCKmax_ps = tCKmax_ps;
	tp->tCKmax_max_ps = tCKmax_max_ps;
	tp->tRCD_ps = tRCD_ps;
	tp->tRP_ps = tRP_ps;
	tp->tRAS_ps = tRAS_ps;
	tp->tWR_ps = tWR_ps;
	tp->tWTR_ps = tWTR_ps;
	tp->tRFC_ps = tRFC_ps;
	tp->tRRD_ps = tRRD_ps;
	tp->tRC_ps = tRC_ps;
	tp->tFAW_ps = tFAW_ps;
	tp->refresh_rate_ps = refresh_rate_ps;
	tp->tIS_ps = tIS_ps;
	tp->tIH_ps = tIH_ps;
	tp->tDS_ps = tDS_ps;
	tp->tDH_ps = tDH_ps;
	tp->tRTP_ps = tRTP_ps;
	tp->tDQSQ_max_ps = tDQSQ_max_ps;
	tp->tQHS_ps = tQHS_ps;

	debug("\nCommon Timings Parameters for MCU[%d] ---\n", mcu->id);
	debug("\ttCK: min %d (used for timing calculations)\n", tCKmin_X_ps);
	debug("\ttCK: max %d max-max %d (not-calculated)\n", tCKmax_ps,
	      tCKmax_max_ps);
	debug("\ttRCD: %d tRP: %d tRAS: %d\n", tRCD_ps, tRP_ps, tRAS_ps);
	debug("\ttWR: %d tWTR: %d tRFC: %d\n", tWR_ps, tWTR_ps, tRFC_ps);
	debug("\ttRRD: %d tRC: %d tFAW: %d\n", tRRD_ps, tRC_ps, tFAW_ps);
	debug("\ttRTP: %d  tREFI: %d\n", tRTP_ps, refresh_rate_ps);
	//debug("\ttIS: %d tIH: %d tDS: %d tDH: %d tDQSQ: %d tQHS: %d\n", tIS_ps, tIH_ps, tDS_ps,
	//      tDH_ps, tDQSQ_max_ps, tQHS_ps);

	/* Determine common burst length for all DIMMs. */
	temp1 = 0xff;
	for (i = 0; i < CONFIG_SYS_DIMM_SLOTS_PER_CTLR; i++) {
		if (!((activeslots >> i) & 0x1)) {
			continue;
		}
		temp1 &= mcu->dimm_params[i].burst_lengths_bitmask;
	}
	tp->all_DIMMs_burst_lengths_bitmask = temp1;

	/* Determine if all DIMMs registered buffered. */
	temp1 = temp2 = 0;
	for (i = 0; i < CONFIG_SYS_NO_OF_DIMMS; i++) {
		if (!((activeslots >> i) & 0x1)) {
			continue;
		}
		if (mcu->dimm_params[i].registered_dimm)
			temp1 = 1;
		if (!mcu->dimm_params[i].registered_dimm)
			temp2 = 1;
	}

	tp->all_DIMMs_registered = 0;
	if (temp1 && !temp2) {
		tp->all_DIMMs_registered = 1;
	}

	tp->all_DIMMs_unbuffered = 0;
	if (!temp1 && temp2) {
		tp->all_DIMMs_unbuffered = 1;
	}

	/* CHECKME: */
	if (!tp->all_DIMMs_registered && !tp->all_DIMMs_unbuffered) {
		debug("ERROR:  Mix of registered buffered and unbuffered "
		      "DIMMs detected!\n");
		return 1;
	}

	/* Determine if all DIMMs ECC capable. */
	temp1 = 1;
	for (i = 0; i < CONFIG_SYS_NO_OF_DIMMS; i++) {
		if (!((activeslots >> i) & 0x1)) {
			continue;
		}
		if (dimm_params[i].edc_config != 2) {
			temp1 = 0;
			break;
		}
	}
	tp->all_DIMMs_ECC_capable = temp1;
	if (temp1) {
		debug("\tall DIMMs ECC capable\n");
	} else {
		debug
		    ("\tWarning: not all DIMMs ECC capable, cant enable ECC\n");
	}

	/* Compute minimum cas latency */
	if (compute_cas_latency(mcu))
		return 1;

	/*
	 * Compute additive latency.
	 *
	 * For DDR1, additive latency should be 0.
	 *
	 * For DDR2, with ODT enabled, use "a value" less than ACTTORW,
	 *      which comes from Trcd, and also note that:
	 *          add_lat + caslat must be >= 4
	 *
	 * For DDR3, we use the AL=0
	 *
	 * When to use additive latency for DDR2:
	 *
	 * I. Because you are using CL=3 and need to do ODT on writes and
	 *    want functionality.
	 *    1. Are you going to use ODT? (Does your board not have
	 *      additional termination circuitry for DQ, DQS, DQS_,
	 *      DM, RDQS, RDQS_ for x4/x8 configs?)
	 *    2. If so, is your lowest supported CL going to be 3?
	 *    3. If so, then you must set AL=1 because
	 *
	 *       WL >= 3 for ODT on writes
	 *       RL = AL + CL
	 *       WL = RL - 1
	 *       ->
	 *       WL = AL + CL - 1
	 *       AL + CL - 1 >= 3
	 *       AL + CL >= 4
	 *  QED
	 *
	 *  RL >= 3 for ODT on reads
	 *  RL = AL + CL
	 *
	 *  Since CL aren't usually less than 2, AL=0 is a minimum,
	 *  so the WL-derived AL should be the  -- FIXME?
	 *
	 * II. Because you are using auto-precharge globally and want to
	 *     use additive latency (posted CAS) to get more bandwidth.
	 *     1. Are you going to use auto-precharge mode globally?
	 *
	 *        Use addtivie latency and compute AL to be 1 cycle less than
	 *        tRCD, i.e. the READ or WRITE command is in the cycle
	 *        immediately following the ACTIVATE command..
	 *
	 * III. Because you feel like it or want to do some sort of
	 *      degraded-performance experiment.
	 *     1.  Do you just want to use additive latency because you feel
	 *         like it?
	 *
	 * Validation:  AL is less than tRCD, and within the other
	 * read-to-precharge constraints.
	 */
	/*
	 * The system will not use the global auto-precharge mode.
	 * However, it uses the page mode, so we set AL=0
	 */
	additive_latency = 0;

	/*
	 * Validate additive latency
	 * FIXME: move to somewhere else to validate
	 *
	 * AL <= tRCD(min)
	 */
	if (mclk_to_picos(mcu, mcu->id) > tRCD_ps) {
		debug("Error: invalid additive latency exceeds tRCD(min).\n");
		return 1;
	}

	/*
	 * RL = CL + AL;  RL >= 3 for ODT_RD_CFG to be enabled
	 * WL = RL - 1;  WL >= 3 for ODT_WL_CFG to be enabled
	 * ADD_LAT (the register) must be set to a value less
	 * than ACTTORW if WL = 1, then AL must be set to 1
	 * RD_TO_PRE (the register) must be set to a minimum
	 * tRTP + AL if AL is nonzero
	 */

	/*
	 * Additive latency will be applied only if the memctl option to
	 * use it.
	 */
	tp->cas_write_latency = compute_cas_write_latency(mcu);
	tp->cas_read_latency = tp->lowest_common_SPD_caslat;
	if (tp->cas_read_latency < 6)
		additive_latency = tp->lowest_common_SPD_caslat - 2;
	else if (tp->cas_read_latency < 7)
		additive_latency = tp->lowest_common_SPD_caslat - 1;
	tp->additive_latency = additive_latency;
	return 0;
}
