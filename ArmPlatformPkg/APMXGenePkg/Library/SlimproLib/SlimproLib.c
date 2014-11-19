/**
 *  Slimrpo library
 *
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
#include <Base.h>
#include <Uefi/UefiBaseType.h>
#include <Library/DebugLib.h>
#include <Library/PrintLib.h>

#include <ipp_csr.h>
#include <ipp_interface.h>
#include <Library/SlimproLib.h>

#undef SLIMPRO_MSGACK_VIA_STATUS_CSR  // bootstrap booting

#define APM_DBMSG_REG_BASE      0x10540000
#define APM_MPA_REG_OFFSET      0x1000


#define APM_MPA_PPC0_REG_OFFSET    0x2000
#define APM_MPA_PPC1_REG_OFFSET    0x3000
#define MPA_PPC_CSR_SIZE      0x1000
#define APM_GLBL_DIAG_OFFSET    0x7000
#define APM_CFG_MEM_RAM_SHUTDOWN_ADDR   0x70

#define CONFIG_SYS_SCU_BASE  0x17000000

#define SLIMPRO_MAJOR_VER(x)    (((x) & 0xf0) >> 4)
#define SLIMPRO_MINOR_VER(x)    ((x) & 0xf)

#ifdef DEBUG
#define DBG_PRINT(arg...) DEBUG ((EFI_D_VERBOSE,## arg))
#else
#define DBG_PRINT(arg...)
#endif

#define MAXTMPSTR 32

#define IOB_RELAX(x)    { \
  volatile UINT32 delay; \
  for (delay = 0; delay < (x*1000); delay++); \
  }

/* Add delay loop */
#define IPP_DELAY    { \
  volatile UINT32 delay; \
  for (delay = 0; delay < 10000; delay++); \
}

/* we have these functions to avoid put them above 32K range */
UINT32 mmioread32(UINT32 addr)
{
  return *(UINT32 *)(VOID *) (UINT64) addr;
}

VOID mmiowrite32(UINT32 addr, UINT32 value)
{
  *(UINT32 *)(VOID *) (UINT64) addr = value;
}


CHAR8 *strcpy(CHAR8 *dst, const CHAR8 *src)
{
  CHAR8 *rt_dst = dst;
  while((*dst++ = *src++) != '\0');

  return rt_dst;
}

enum {
  PMD_900 = 0x0,
  PMD_910 = 0x1,
  PMD_920 = 0x2,
  PMD_930 = 0x3,
  PMD_940 = 0x4,
  PMD_950 = 0x5,
  PMD_960 = 0x6,
  PMD_970 = 0x7,
  PMD_980 = 0x8,
  PMD_990 = 0x9,
  PMD_1000 = 0xa,
  PMD_1100 = 0xb,
  PMD_1200 = 0xc,
  PMD_1300 = 0xd,
  PMD_UNKNOWN = 0xf,
};
enum {
  SOC_900 = 0x0,
  SOC_910 = 0x1,
  SOC_920 = 0x2,
  SOC_930 = 0x3,
  SOC_940 = 0x4,
  SOC_950 = 0x5,
  SOC_960 = 0x6,
  SOC_UNKNOWN = 0xf,
};

EFI_STATUS
EFIAPI
XGeneBMCStart(BOOLEAN Start)
{
  UINT32 data;
  UINT8 access_info, sub_type;

  DBG_PRINT("In XGeneBMCCommand\n");

  if (Start)
    sub_type = BMC_START_REQ_CMD;
  else
    sub_type = BMC_STOP_REQ_CMD;

  access_info = ENCODE_BMC_ACCESS_INFO(0, 0, 0);
  access_info = ENCODE_BMC_ACCESS_INFO_CMD(access_info, sub_type);
  data = IPP_ENCODE_DEBUG_MSG(IPP_DBG_SUBTYPE_BMC_MSG, 0,
        0, access_info);

  XGeneWriteIppMsg(data, 0);

  return EFI_SUCCESS;
}

EFI_STATUS
EFIAPI
XGeneReadIppMsg(UINT32 *data)
{
  INTN timeout_cnt = 10000;
  UINT32 msg_reg_base, acode_offset, intstat_offset;
  /* Uboot always uses Core0 for iPP messaging */
  UINT32 core = 0;

  DBG_PRINT("In XGeneReadIppMsg\n");

  msg_reg_base = (UINTN)APM_DBMSG_REG_BASE;
  intstat_offset = (core*0x1000) + AGENT_DB_STATUS_ADDR;
  acode_offset = (core*0x1000) + AGENT_DB_DIN0_ADDR;

  /* Wait for iPP message since we don't operate in INTNerrupt mode */
  while (!(mmioread32((msg_reg_base + intstat_offset))
        & DB_AVAIL_MASK)) {
    IPP_DELAY;
    if (--timeout_cnt == 0)
      return EFI_TIMEOUT;
  }

  /* Read iPP message */
  *data = mmioread32((msg_reg_base + acode_offset));
  /* Send acknowledgment to iPP */
  mmiowrite32((msg_reg_base + intstat_offset),
      DB_AVAIL_MASK);

  return EFI_SUCCESS;
}

EFI_STATUS
EFIAPI
XGeneWriteIppMsg(UINT32 data, UINT32 param)
{
  INTN timeout_cnt = 100;
  UINT32 pcode_offset, scratch_offset;
        UINT32 msg_reg_base, intstat_offset;
  /* Uboot always uses Core0 for  messaging */
  UINT32 core = 0;

  DBG_PRINT("In XGeneWriteIppMsg\n");

  msg_reg_base = (UINTN) APM_DBMSG_REG_BASE;
  scratch_offset = (core*0x1000) + AGENT_DB_DOUT0_ADDR;
  pcode_offset = (core*0x1000) + AGENT_DB_OUT_ADDR;
  intstat_offset = (core*0x1000) + AGENT_DB_STATUS_ADDR;

  /* Clear previous pending ack if any */
  if (mmioread32((msg_reg_base + intstat_offset))
        & DB_ACK_MASK) {
    mmiowrite32((msg_reg_base + intstat_offset),
        DB_ACK_MASK);
  }
  /* Send message to iPP */
  mmiowrite32((msg_reg_base + scratch_offset), param);
  mmiowrite32((msg_reg_base + pcode_offset), data);

  /* Wait for ack */
  while (!(mmioread32((msg_reg_base + intstat_offset))
        & DB_ACK_MASK)) {
    IPP_DELAY;
    if (--timeout_cnt == 0)
      return EFI_TIMEOUT;
  }

  /* Clear iPP ack */
  mmiowrite32((msg_reg_base + intstat_offset),
      DB_ACK_MASK);
  return EFI_SUCCESS;
}

EFI_STATUS
EFIAPI
XGeneIppLoadFile(CHAR8* f_name, UINT64 addr,
        UINTN offset, UINTN size)
{
  UINT32 fword[IPP_BOOTACCESS_MAX_FILENAME_SIZE/4];
  CHAR8 file_name[IPP_BOOTACCESS_MAX_FILENAME_SIZE];
  UINTN ite;
  UINT32 data;
  UINT32 param;

  DBG_PRINT("In XGeneIppLoadFile\n");

  UINT32 scratch= (CONFIG_SYS_SCU_BASE +APM_MPA_REG_OFFSET + MPA_SCRATCH_ADDR); /* decide pin strap and boot strap */
  strcpy(file_name, f_name);
  file_name[IPP_BOOTACCESS_MAX_FILENAME_SIZE-1] = '\0';
  for(ite=0;ite<4;ite++) {
    fword[ite] = 0;
  }
  for(ite=0;ite<IPP_BOOTACCESS_MAX_FILENAME_SIZE;ite++) {
    fword[ite/4] |= file_name[ite] << ((ite%4)*8);
  }
  /* Word0: Access control information */
  if(offset==0 && size==0xFFFFFFFF) {
    param =  IPP_ENCODE_BOOTACCESS_WORD0(IPP_BOOTACCESS_DEVICE_DEFAULT,IPP_BOOTACCESS_OP_READFULL);
  } else {
    param =  IPP_ENCODE_BOOTACCESS_WORD0(IPP_BOOTACCESS_DEVICE_DEFAULT,IPP_BOOTACCESS_OP_READ);
  }
  DBG_PRINT("%x\n", param);
  data = IPP_ENCODE_DATA_MSG(IPP_BOOTACCESS_HDLR,
          CTRL_BYTE_UNSED,
          IPP_DATA_MSG_CBYTE_START_BIT,
          0);
  XGeneWriteIppMsg(data, param);
  IOB_RELAX(50);
  DBG_PRINT("%x\n", fword[0]);
  /* Word1: File name (first four bytes) */
  param = fword[0];
  data = IPP_ENCODE_DATA_MSG(IPP_BOOTACCESS_HDLR,
          CTRL_BYTE_UNSED,
          IPP_DATA_MSG_CBYTE_DATA_BIT,
          1);
  XGeneWriteIppMsg(data, param);
  IOB_RELAX(50);
  DBG_PRINT("%x\n", fword[1]);
  /* Word2: File name (second four bytes) */
  param = fword[1];
  data = IPP_ENCODE_DATA_MSG(IPP_BOOTACCESS_HDLR,
          CTRL_BYTE_UNSED,
          IPP_DATA_MSG_CBYTE_DATA_BIT,
          2);
  XGeneWriteIppMsg(data, param);
  IOB_RELAX(50);
  DBG_PRINT("%x\n", fword[2]);
  /* Word3: File name (third four bytes) */
  param = fword[2];
  data = IPP_ENCODE_DATA_MSG(IPP_BOOTACCESS_HDLR,
          CTRL_BYTE_UNSED,
          IPP_DATA_MSG_CBYTE_DATA_BIT,
          3);
  XGeneWriteIppMsg(data, param);
  IOB_RELAX(50);
  DBG_PRINT("%x\n", fword[3]);
  /* Word4: File name (fourth four bytes) */
  param = fword[3];
  data = IPP_ENCODE_DATA_MSG(IPP_BOOTACCESS_HDLR,
          CTRL_BYTE_UNSED,
          IPP_DATA_MSG_CBYTE_DATA_BIT,
          4);
  XGeneWriteIppMsg(data, param);
  IOB_RELAX(50);

  DBG_PRINT("%x\n", offset);
  /* Word5: File offset (specifies where to start reading/writing in file) */
  param = offset;
  data = IPP_ENCODE_DATA_MSG(IPP_BOOTACCESS_HDLR,
          CTRL_BYTE_UNSED,
          IPP_DATA_MSG_CBYTE_DATA_BIT,
          5);
  XGeneWriteIppMsg(data, param);
  IOB_RELAX(50);

  DBG_PRINT("%x\n", size);
  /* Word6: File read size (specifies how much to read/write from file) */
  param = size;
  data = IPP_ENCODE_DATA_MSG(IPP_BOOTACCESS_HDLR,
          CTRL_BYTE_UNSED,
          IPP_DATA_MSG_CBYTE_DATA_BIT,
          6);
  XGeneWriteIppMsg(data, param);
  IOB_RELAX(50);

  DBG_PRINT("%016LX\n", addr);
  /* Word7:  */
  param =  (UINTN) (addr >> 32);
  data = IPP_ENCODE_DATA_MSG(IPP_BOOTACCESS_HDLR,
          CTRL_BYTE_UNSED,
          IPP_DATA_MSG_CBYTE_DATA_BIT,
          7);
  XGeneWriteIppMsg(data, param);
  IOB_RELAX(10);

  /* Word 8: */
  param = (UINTN) addr;
  data = IPP_ENCODE_DATA_MSG(IPP_BOOTACCESS_HDLR,
          CTRL_BYTE_UNSED,
          IPP_DATA_MSG_CBYTE_STOP_BIT,
          8);
  XGeneWriteIppMsg(data, param);
  IOB_RELAX(1000);

  if(((mmioread32(scratch)) & 0xff000000)== 0xA4000000)/*pin strap*/
  {
    UINT32 scratch4 = (CONFIG_SYS_SCU_BASE + MPA_SCRATCH4_ADDR);
    UINT32 scratch1 = (CONFIG_SYS_SCU_BASE + MPA_SCRATCH1_ADDR);
    while (((mmioread32(scratch4)) != 0x10250000) &&
            (((mmioread32(scratch1)) & 0xff) != 0x0)) {
           ;
    }
  } else {  /* bootstrap */
    while (1) {
      if(!XGeneReadIppMsg(&data)) {
        if(IPP_DECODE_MSG_TYPE(data)==IPP_OK_MSG) {
          break;
        } else {
          return EFI_TIMEOUT;
        }
      }
      IOB_RELAX(1000);
    }
  }

  return EFI_SUCCESS;
}

UINT32
EFIAPI
XGeneIppGetBootMode(VOID)
{
  UINT32 Val = mmioread32(CONFIG_SYS_SCU_BASE +
                            APM_MPA_REG_OFFSET + MPA_SCRATCH_ADDR);

  return (Val & IPP_MODE_MASK);
}

EFI_STATUS
EFIAPI
XGeneIppGetFWStrInfo(CHAR16* Str, UINT32 Len)
{
  ipp_info_t ipp_info;
  CHAR16 TpcStr[MAXTMPSTR];
  CHAR16 AvsStr[MAXTMPSTR];
  UINT32 PMDVoltage;
  CHAR16 PMDVoltageStr[MAXTMPSTR];
  UINT32 SOCVoltage;
  CHAR16 SOCVoltageStr[MAXTMPSTR];
  UINT32 Val;

  if (XGeneIppGetBootMode() == IPP_ROM_MODE_MASK)
    return EFI_UNSUPPORTED;

  Val = mmioread32(CONFIG_SYS_SCU_BASE +
                            APM_MPA_REG_OFFSET + MPA_SCRATCH_ADDR);

  ipp_info.build_info.date = mmioread32(CONFIG_SYS_SCU_BASE +
                          APM_MPA_REG_OFFSET + MPA_SCRATCH15_ADDR);
  ipp_info.bd_pwr_info.data = mmioread32(CONFIG_SYS_SCU_BASE +
                          APM_MPA_REG_OFFSET + MPA_SCRATCH14_ADDR);

  if (ipp_info.build_info.date == 0){
    UnicodeSPrint(Str, Len, L"Slimpro FW:\n\r\tVer: %d.%d\n\r",
                              SLIMPRO_MAJOR_VER(Val),
                              SLIMPRO_MINOR_VER(Val));
  } else {
    if (ipp_info.bd_pwr_info.inf.adv_mode) {
      if (ipp_info.bd_pwr_info.inf.tpc_en)
        UnicodeSPrint(TpcStr, MAXTMPSTR, L"\n\r\tTPC: enable");
      else {
        UnicodeSPrint(TpcStr, MAXTMPSTR, L"\n\r\tTPC: disable");
      }

      if (ipp_info.bd_pwr_info.inf.avs_en)
        UnicodeSPrint(AvsStr, MAXTMPSTR, L"\n\r\tAVS: supported");
      else
        UnicodeSPrint(AvsStr, MAXTMPSTR, L"\n\r\tAVS: unsupported");
    } else {
      UnicodeSPrint(TpcStr, MAXTMPSTR, L"");
      UnicodeSPrint(AvsStr, MAXTMPSTR, L"");
    }

    switch (ipp_info.bd_pwr_info.inf.pmd_vltg) {
    case PMD_900:
      PMDVoltage = 900;
      break;
    case PMD_910:
      PMDVoltage = 910;
      break;
    case PMD_920:
      PMDVoltage = 920;
      break;
    case PMD_930:
      PMDVoltage = 930;
      break;
    case PMD_940:
      PMDVoltage = 940;
      break;
    case PMD_950:
      PMDVoltage = 950;
      break;
    case PMD_960:
      PMDVoltage = 960;
      break;
    case PMD_970:
      PMDVoltage = 970;
      break;
    case PMD_980:
      PMDVoltage = 980;
      break;
    case PMD_990:
      PMDVoltage = 990;
      break;
    case PMD_1000:
      PMDVoltage = 1000;
      break;
    case PMD_1100:
      PMDVoltage = 1100;
      break;
    case PMD_1200:
      PMDVoltage = 1200;
      break;
    case PMD_1300:
      PMDVoltage = 1300;
      break;
    default:
      PMDVoltage = 0;
    }

    if (PMDVoltage)
      UnicodeSPrint(PMDVoltageStr, MAXTMPSTR, L"\n\r\tPMD: %d mV", PMDVoltage);
    else
      UnicodeSPrint(PMDVoltageStr, MAXTMPSTR, L"");

    switch (ipp_info.bd_pwr_info.inf.soc_vltg) {
    case SOC_900:
      SOCVoltage = 900;
      break;
    case SOC_910:
      SOCVoltage = 910;
      break;
    case SOC_920:
      SOCVoltage = 920;
      break;
    case SOC_930:
      SOCVoltage = 930;
      break;
    case SOC_940:
      SOCVoltage = 940;
      break;
    case SOC_950:
      SOCVoltage = 950;
      break;
    case SOC_960:
      SOCVoltage = 960;
      break;
    default:
      SOCVoltage = 0;
    }

    if (SOCVoltage)
      UnicodeSPrint(SOCVoltageStr, MAXTMPSTR, L"\n\r\tSOC: %d mV", SOCVoltage);
    else
      UnicodeSPrint(SOCVoltageStr, MAXTMPSTR, L"");

    UnicodeSPrint(Str, Len,
            L"Slimpro FW:\n\r\tVer: %d.%d (build %04x/%02x/%02x)%s%s%s%s\n\r",
            SLIMPRO_MAJOR_VER(Val), SLIMPRO_MINOR_VER(Val),
            ipp_info.build_info.inf.yyyy,
            ipp_info.build_info.inf.mm,
            ipp_info.build_info.inf.dd,
            TpcStr, AvsStr, PMDVoltageStr, SOCVoltageStr);

  }

  return EFI_SUCCESS;
}
