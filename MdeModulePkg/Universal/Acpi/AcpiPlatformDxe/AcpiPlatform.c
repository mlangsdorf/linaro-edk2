/** @file
  Sample ACPI Platform Driver

  Copyright (c) 2008 - 2011, Intel Corporation. All rights reserved.<BR>
  This program and the accompanying materials
  are licensed and made available under the terms and conditions of the BSD License
  which accompanies this distribution.  The full text of the license may be found at
  http://opensource.org/licenses/bsd-license.php

  THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
  WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.

**/ 
#include <PiDxe.h>

#include <Protocol/AcpiTable.h>
#include <Protocol/FirmwareVolume2.h>

#include <Library/BaseLib.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Library/DebugLib.h>
#include <Library/PcdLib.h>

#include <Library/PrintLib.h>
#include <Library/DebugLib.h>
#include <Library/BaseMemoryLib.h>
#include <Library/UefiRuntimeServicesTableLib.h>

#include <IndustryStandard/Acpi.h>

#define DEBUG_MAC_PATCH	0
#if (DEBUG_MAC_PATCH)
	#define DEBUG_MAC(x)	DEBUG(x)
#else
	#define DEBUG_MAC(x)
#endif

#define HID_NAME	"APMC0D05"
extern EFI_GUID gShellVariableGuid;
typedef struct {
	CHAR8	EthName[10];
	CHAR8	MacName[10];
	CHAR16   NvName[18];
}ETH_PORT;

static ETH_PORT EthernetPort[5] = {	{"ET08", "MAC0", L"RGMII_MAC0"},
					{"ET00", "MAC0", L"SGMII_MAC0"},
					{"ET01", "MAC0", L"SGMII_MAC1"},
					{"ET04", "MAC0", L"TENGI_MAC0"},
					{"ET05", "MAC0", L"TENGI_MAC1"},
				  };

static int ContainStr(CHAR8 *SrcStr, CHAR8 *SubStr)
{
	while (*SrcStr && *SubStr)
		if (*SrcStr != *SubStr)
			break;
		else {
		   	SrcStr++; 
			SubStr++;
		}

	return (*SubStr)?0:1;
}

void AsciiStrToEthAddr(CHAR16 *MacBuf, UINT8 *MAC)
{
#define A_D(x) ( ((x >= L'a')&&(x <= L'f'))?(x-L'a'+0xa):(((x >= L'A')&&(x <= L'F'))?(x-L'A'+0xa):(x-L'0')) )

	*MAC++ = (A_D(*MacBuf)<<4) + A_D(*(MacBuf+1));
	*MAC++ = (A_D(*(MacBuf+3))<<4) + A_D(*(MacBuf+4));
	*MAC++ = (A_D(*(MacBuf+6))<<4) + A_D(*(MacBuf+7));
	*MAC++ = (A_D(*(MacBuf+9))<<4) + A_D(*(MacBuf+10));
	*MAC++ = (A_D(*(MacBuf+12))<<4) + A_D(*(MacBuf+13));
	*MAC++ = (A_D(*(MacBuf+15))<<4) + A_D(*(MacBuf+16));
}

EFI_STATUS
EFIAPI
ApmPatchAcpiTable(UINT8 *CurrentTable,
 		  UINTN  TableSize 
  )
{
	EFI_STATUS  Status;
	UINTN       Size;
	CHAR16      MacBuf[20];
	int i, EthIndex;

	EthIndex = 0;

	DEBUG_MAC((EFI_D_ERROR, "print CurrentTable TableSize=%d\n", TableSize));
	for (i=0; i<(TableSize-5); i++, CurrentTable++)
	{
		if (ContainStr((CHAR8 *)CurrentTable, (CHAR8 *)HID_NAME) > 0) {
			DEBUG_MAC((EFI_D_ERROR, "Found HID_NAME i=%d\n", i));
			for (; i<(TableSize-5); i++, CurrentTable++) {
				if (ContainStr((CHAR8 *)CurrentTable, (CHAR8 *)(EthernetPort[EthIndex].EthName)) > 0) {
					DEBUG_MAC((EFI_D_ERROR, "Found EthName =%c%c%c%c\n", 
								*(EthernetPort[EthIndex].EthName),
								*(EthernetPort[EthIndex].EthName+1),
								*(EthernetPort[EthIndex].EthName+2),
								*(EthernetPort[EthIndex].EthName+3)

					      ));
					break;	
				}
			}
			for (; i<(TableSize-5); i++, CurrentTable++) {
				if (ContainStr((CHAR8 *)CurrentTable, (CHAR8 *)(EthernetPort[EthIndex].MacName)) > 0) {
					DEBUG_MAC((EFI_D_ERROR, "Found MacName =%c%c%c%c\n", 
								*(CurrentTable),
								*(CurrentTable+1),
								*(CurrentTable+2),
								*(CurrentTable+3)
					      ));
					break;	
				}
			}

			/* point to the MAC value location */
			CurrentTable += 8;
			i += 8;

			DEBUG_MAC((EFI_D_ERROR, "i:0x%x Mac =%2x:%2x:%2x:%2x:%2x:%2x\n", i, *(CurrentTable),
						*(CurrentTable+1),
						*(CurrentTable+2),
						*(CurrentTable+3),
						*(CurrentTable+4),
						*(CurrentTable+5)							
			      ));
			/* update the MAC */
			Size = sizeof(MacBuf);
			Status = gRT->GetVariable(EthernetPort[EthIndex].NvName,
					&gShellVariableGuid,
					0,
					&Size,
					(void *)MacBuf);

			if (EFI_ERROR (Status)) {
				DEBUG_MAC((EFI_D_ERROR, "GetVariable MAC ERROR !!!"));
			} else {
				UINT8       MAC[20];

				AsciiStrToEthAddr (MacBuf, MAC);

				DEBUG_MAC((EFI_D_ERROR, "GetVariable %s MAC: %2x:%2x:%2x:%2x:%2x:%x !!!", EthernetPort[EthIndex].NvName, 
							MAC[0], MAC[1], MAC[2], MAC[3], MAC[4], MAC[5]));

				*((UINT8*)CurrentTable) = MAC[0];
				*((UINT8*)CurrentTable+1) = MAC[1];
				*((UINT8*)CurrentTable+2) = MAC[2];
				*((UINT8*)CurrentTable+3) = MAC[3];
				*((UINT8*)CurrentTable+4) = MAC[4];
				*((UINT8*)CurrentTable+5) = MAC[5];
			}

			CurrentTable += 6;
			i += 6;
			EthIndex++;
		}
	}

	return (EFI_SUCCESS);
}

/**
  Locate the first instance of a protocol.  If the protocol requested is an
  FV protocol, then it will return the first FV that contains the ACPI table
  storage file.

  @param  Instance      Return pointer to the first instance of the protocol

  @return EFI_SUCCESS           The function completed successfully.
  @return EFI_NOT_FOUND         The protocol could not be located.
  @return EFI_OUT_OF_RESOURCES  There are not enough resources to find the protocol.

**/
EFI_STATUS
LocateFvInstanceWithTables (
  OUT EFI_FIRMWARE_VOLUME2_PROTOCOL **Instance
  )
{
  EFI_STATUS                    Status;
  EFI_HANDLE                    *HandleBuffer;
  UINTN                         NumberOfHandles;
  EFI_FV_FILETYPE               FileType;
  UINT32                        FvStatus;
  EFI_FV_FILE_ATTRIBUTES        Attributes;
  UINTN                         Size;
  UINTN                         Index;
  EFI_FIRMWARE_VOLUME2_PROTOCOL *FvInstance;

  FvStatus = 0;

  //
  // Locate protocol.
  //
  Status = gBS->LocateHandleBuffer (
                   ByProtocol,
                   &gEfiFirmwareVolume2ProtocolGuid,
                   NULL,
                   &NumberOfHandles,
                   &HandleBuffer
                   );
  if (EFI_ERROR (Status)) {
    //
    // Defined errors at this time are not found and out of resources.
    //
    return Status;
  }



  //
  // Looking for FV with ACPI storage file
  //

  for (Index = 0; Index < NumberOfHandles; Index++) {
    //
    // Get the protocol on this handle
    // This should not fail because of LocateHandleBuffer
    //
    Status = gBS->HandleProtocol (
                     HandleBuffer[Index],
                     &gEfiFirmwareVolume2ProtocolGuid,
                     (VOID**) &FvInstance
                     );
    ASSERT_EFI_ERROR (Status);

    //
    // See if it has the ACPI storage file
    //
    Status = FvInstance->ReadFile (
                           FvInstance,
                           (EFI_GUID*)PcdGetPtr (PcdAcpiTableStorageFile),
                           NULL,
                           &Size,
                           &FileType,
                           &Attributes,
                           &FvStatus
                           );

    //
    // If we found it, then we are done
    //
    if (Status == EFI_SUCCESS) {
      *Instance = FvInstance;
      break;
    }
  }

  //
  // Our exit status is determined by the success of the previous operations
  // If the protocol was found, Instance already points to it.
  //

  //
  // Free any allocated buffers
  //
  gBS->FreePool (HandleBuffer);

  return Status;
}


/**
  This function calculates and updates an UINT8 checksum.

  @param  Buffer          Pointer to buffer to checksum
  @param  Size            Number of bytes to checksum

**/
VOID
AcpiPlatformChecksum (
  IN UINT8      *Buffer,
  IN UINTN      Size
  )
{
  UINTN ChecksumOffset;

  ChecksumOffset = OFFSET_OF (EFI_ACPI_DESCRIPTION_HEADER, Checksum);

  //
  // Set checksum to 0 first
  //
  Buffer[ChecksumOffset] = 0;

  //
  // Update checksum value
  //
  Buffer[ChecksumOffset] = CalculateCheckSum8(Buffer, Size);
}


/**
  Entrypoint of Acpi Platform driver.

  @param  ImageHandle
  @param  SystemTable

  @return EFI_SUCCESS
  @return EFI_LOAD_ERROR
  @return EFI_OUT_OF_RESOURCES

**/
EFI_STATUS
EFIAPI
AcpiPlatformEntryPoint (
  IN EFI_HANDLE         ImageHandle,
  IN EFI_SYSTEM_TABLE   *SystemTable
  )
{
  EFI_STATUS                     Status;
  EFI_ACPI_TABLE_PROTOCOL        *AcpiTable;
  EFI_FIRMWARE_VOLUME2_PROTOCOL  *FwVol;
  INTN                           Instance;
  EFI_ACPI_COMMON_HEADER         *CurrentTable;
  UINTN                          TableHandle;
  UINT32                         FvStatus;
  UINTN                          TableSize;
  UINTN                          Size;

  Instance     = 0;
  CurrentTable = NULL;
  TableHandle  = 0;

  //
  // Find the AcpiTable protocol
  //
  Status = gBS->LocateProtocol (&gEfiAcpiTableProtocolGuid, NULL, (VOID**)&AcpiTable);
  if (EFI_ERROR (Status)) {
    return EFI_ABORTED;
  }

  //
  // Locate the firmware volume protocol
  //
  Status = LocateFvInstanceWithTables (&FwVol);
  if (EFI_ERROR (Status)) {
    return EFI_ABORTED;
  }
  //
  // Read tables from the storage file.
  //
  while (Status == EFI_SUCCESS) {

    Status = FwVol->ReadSection (
                      FwVol,
                      (EFI_GUID*)PcdGetPtr (PcdAcpiTableStorageFile),
                      EFI_SECTION_RAW,
                      Instance,
                      (VOID**) &CurrentTable,
                      &Size,
                      &FvStatus
                      );
    if (!EFI_ERROR(Status)) {
      //
      // Add the table
      //
      TableHandle = 0;

      TableSize = ((EFI_ACPI_DESCRIPTION_HEADER *) CurrentTable)->Length;
      ASSERT (Size >= TableSize);

      //
      // Checksum ACPI table
      //
      AcpiPlatformChecksum ((UINT8*)CurrentTable, TableSize);

      ApmPatchAcpiTable((UINT8*)CurrentTable, TableSize);

      //
      // Install ACPI table
      //
      Status = AcpiTable->InstallAcpiTable (
                            AcpiTable,
                            CurrentTable,
                            TableSize,
                            &TableHandle
                            );

      //
      // Free memory allocated by ReadSection
      //
      gBS->FreePool (CurrentTable);

      if (EFI_ERROR(Status)) {
        return EFI_ABORTED;
      }

      //
      // Increment the instance
      //
      Instance++;
      CurrentTable = NULL;
    }
  }

  return EFI_SUCCESS;
}

