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

#include "SnpDxe.h"

UINT32 eth_initialized; 
//
//  Functions in Net Library
//

UINT8 apm_mac_addr[6] = {0x00, 0x11, 0x22, 0x33, 0x44, 0x55};
extern EFI_GUID gShellVariableGuid;

static void AsciiStrToEthAddr(CHAR16 *MacBuf, UINT8 *MAC)
{
#define A_D(x) ( ((x >= L'a')&&(x <= L'f'))?(x-L'a'+0xa):(((x >= L'A')&&(x <= L'F'))?(x-L'A'+0xa):(x-L'0')) )

  *MAC++ = (A_D(*MacBuf)<<4) + A_D(*(MacBuf+1));
  *MAC++ = (A_D(*(MacBuf+3))<<4) + A_D(*(MacBuf+4));
  *MAC++ = (A_D(*(MacBuf+6))<<4) + A_D(*(MacBuf+7));
  *MAC++ = (A_D(*(MacBuf+9))<<4) + A_D(*(MacBuf+10));
  *MAC++ = (A_D(*(MacBuf+12))<<4) + A_D(*(MacBuf+13));
  *MAC++ = (A_D(*(MacBuf+15))<<4) + A_D(*(MacBuf+16));
}

static void GetEnvMacAddr(UINT8* MacBuf)
{
  EFI_STATUS  Status;
  UINTN       Size;
  CHAR16      Buf[20];

  Size = sizeof(Buf);
  Status = gRT->GetVariable(L"RGMII_MAC0",
                            &gShellVariableGuid,
                            0,
                            &Size,
                            (void *)Buf);

  if (EFI_ERROR (Status)) {
    DEBUG((EFI_D_ERROR, "GetVariable MAC ERROR !!!"));
    *((UINT8*)MacBuf+0) = apm_mac_addr[0];
    *((UINT8*)MacBuf+1) = apm_mac_addr[1];
    *((UINT8*)MacBuf+2) = apm_mac_addr[2];
    *((UINT8*)MacBuf+3) = apm_mac_addr[3];
    *((UINT8*)MacBuf+4) = apm_mac_addr[4];
    *((UINT8*)MacBuf+5) = apm_mac_addr[5];
  } else {
    UINT8       MAC[20];

    AsciiStrToEthAddr (Buf, MAC);
    DEBUG((EFI_D_ERROR, "GetVariable  MAC: %2x:%2x:%2x:%2x:%2x:%x !!!", 
          MAC[0], MAC[1], MAC[2], MAC[3], MAC[4], MAC[5]));

    apm_mac_addr[0] = *((UINT8*)MacBuf) = MAC[0];
    apm_mac_addr[1] = *((UINT8*)MacBuf+1) = MAC[1];
    apm_mac_addr[2] = *((UINT8*)MacBuf+2) = MAC[2];
    apm_mac_addr[3] = *((UINT8*)MacBuf+3) = MAC[3];
    apm_mac_addr[4] = *((UINT8*)MacBuf+4) = MAC[4];
    apm_mac_addr[5] = *((UINT8*)MacBuf+5) = MAC[5];
  }
}

EFI_STATUS
APMXGeneNet_Initialize (
  IN OUT  UINT32                       *InterfaceCount,
  IN OUT  NET_INTERFACE_INFO           *InterfaceInfoBuffer
  )
{
  DBG("Enter APMXGeneNet_Initialize\n");
  *InterfaceCount = 1;
  InterfaceInfoBuffer[0].InterfaceIndex = 0;
#if 1	//TODO	original
  GetEnvMacAddr(InterfaceInfoBuffer[0].MacAddr.Addr);
#endif
  return EFI_SUCCESS;
}

EFI_STATUS
APMXGeneNet_Finalize (
  VOID
  )
{
  DBG("Enter APMXGeneNet_Finalize\n");
  return EFI_SUCCESS;
}

EFI_STATUS
APMXGeneNet_Set_Receive_Filter (
  IN  UINT32                           Index,
  IN  UINT32                           EnableFilter,
  IN  UINT32                           MCastFilterCnt,
  IN  EFI_MAC_ADDRESS                  * MCastFilter
  )
{
  DBG("Enter APMXGeneNet_Set_Receive_Filter\n");
  return EFI_SUCCESS;
}

EFI_STATUS
APMXGeneNet_Receive (
  IN      UINT32                      Index,
//TODO  IN OUT  UINT32                      *BufferSize,
  IN OUT  UINTN                      *BufferSize,
  OUT     VOID                        *Buffer
  )
{
  //TODO DBG("Enter APMXGeneNet_Receive\n");
#if 1	//TODO
  if (eth_initialized) {
	int rc;
#if 0
    DBG("Enter APMXGeneNet_Receive Buffer=0x%p BufferSize=0x%p\n",
	Buffer, BufferSize);
#endif
    rc = (&emac_dev[0])->recv(&emac_dev[0], Buffer, BufferSize);
	return rc;
  }

#endif
  return EFI_SUCCESS;
}


EFI_STATUS
APMXGeneNet_Transmit (
  IN  UINT32                          Index,
  IN  UINT32                          HeaderSize,
  IN  UINT32                          BufferSize,
  IN  VOID                            *Buffer,
  IN  EFI_MAC_ADDRESS                 * SrcAddr,
  IN  EFI_MAC_ADDRESS                 * DestAddr,
  IN  UINT16                          *Protocol
  )
{

	UINT16 prot;
#if 0
  DBG("Enter APMXGeneNet_Transmit\n");
    DBG("   Index=0x%x, HeaderSize=0x%x, BufferSize=0x%x prot=0x%x\n", Index, HeaderSize, BufferSize, *Protocol);
DBG("  Src:\n");
putshex((unsigned char*)SrcAddr, 6);
DBG("\n Dest:");
putshex((unsigned char*)DestAddr, 6);
#endif
   DBG("APMXGeneNet_Transmit &emac_dev[0]=0x%p\n",  &emac_dev[0]);

   if (!eth_initialized) {
   	(&emac_dev[0])->init(&emac_dev[0]);
	eth_initialized = 1;
   }

   if (HeaderSize) {
	
	CopyMem (Buffer, DestAddr, 6);
	CopyMem (Buffer + 6, SrcAddr, 6);
	prot = PXE_SWAP_UINT16(*Protocol);
	DBG("APMXGeneNet_Transmit prot=0x%x\n", prot);
	CopyMem (Buffer + 12, &prot, 2);
   }
   apm_eth_tx( &emac_dev[0], Buffer, BufferSize);

  return EFI_SUCCESS;
}

VOID
APMXGeneNet_Halt (
  IN UINT32 Index;
  )
{
  if (eth_initialized) {
     /* stop rx and tx */
     (&emac_dev[0])->halt(&emac_dev[0]);
  }
}
