/** @file
  APM X-Gene Ethernet Firmware Initialization Driver

  Copyright (c) 2014, Applied Micro Curcuit Corporation. All rights reserved.<BR>
  This program and the accompanying materials
  are licensed and made available under the terms and conditions of the BSD License
  which accompanies this distribution.  The full text of the license may be found at
  http://opensource.org/licenses/bsd-license.php

  THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
  WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.

  This driver is called to initialize the FW part of the PHY in preparation
  for the OS.

**/

#include <Guid/ShellVariableGuid.h>
#include <Library/UefiRuntimeServicesTableLib.h>
#include <Library/DebugLib.h>
#include <Library/TimerLib.h>
#include <APMXGeneSocCsr.h>

#include <PiDxe.h>
#include <Guid/EventGroup.h>
#include <Protocol/AcpiTable.h>
#include <Protocol/FirmwareVolume2.h>
#include <Library/BaseLib.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Protocol/AcpiSystemDescriptionTable.h>
#include <Library/DebugLib.h>
#include <Library/PcdLib.h>
#include <Library/PrintLib.h>
#include <Library/DebugLib.h>
#include <Library/BaseMemoryLib.h>
#include <Library/UefiRuntimeServicesTableLib.h>
#include <IndustryStandard/Acpi.h>
#include <IndustryStandard/AcpiAml.h>

#define EFI_ACPI_MAX_NUM_TABLES		20
#define DSDT_SIGNATURE			0x54445344
#define ACPI_ETH_ID			"APMC0D05"
#define PREFIX_VARIABLE_NAME		L"MAC"
#define PREFIX_VARIABLE_NAME_COMPAT	L"RGMII_MAC"
#define ACPI_ETH_DEVID_KEY "devid"
#define ACPI_ETH_MAC_KEY "local-mac-address"

static EFI_STATUS XGeneProcessDSDTChild(
  EFI_ACPI_SDT_PROTOCOL *AcpiTableProtocol,
  EFI_ACPI_HANDLE ChildHandle, UINTN *MacNextID)
{
  EFI_STATUS         Status;
  EFI_ACPI_DATA_TYPE DataType;
  CONST UINT8        *Data;
  CONST VOID         *Buffer;
  UINTN              DataSize;
  EFI_ACPI_HANDLE    DevHandle;
  INTN               Found;

  Status = AcpiTableProtocol->GetOption(ChildHandle, 0, &DataType, &Buffer, &DataSize);
  if (EFI_ERROR(Status))
    return EFI_SUCCESS;

  Data = Buffer;
  //
  // Skip all non-device type
  if (DataSize != 2 || Data[0] != AML_EXT_OP || Data[1] != AML_EXT_DEVICE_OP)
    return EFI_SUCCESS;

  //
  // Walk the device type node
  Found = 0;
  for (DevHandle = NULL; ; ) {
    Status = AcpiTableProtocol->GetChild(ChildHandle, &DevHandle);
    if (EFI_ERROR(Status) || DevHandle == NULL)
      break;

    //
    // Search for _HID with APM Ethernet ID
    Status = AcpiTableProtocol->GetOption(DevHandle, 0, &DataType, &Buffer, &DataSize);
    if (EFI_ERROR(Status))
      break;
    Data = Buffer;
    DEBUG((DEBUG_VERBOSE, "Data Type 0x%02X %02X\n", Data[0], DataSize > 1 ? Data[1] : 0));
    if (DataSize == 1 && Data[0] == AML_NAME_OP) {
      Status = AcpiTableProtocol->GetOption(DevHandle, 1, &DataType, &Buffer, &DataSize);
      if (EFI_ERROR(Status))
        break;
      Data = Buffer;
      if (DataType == EFI_ACPI_DATA_TYPE_NAME_STRING &&
          AsciiStrnCmp((CHAR8 *) Data, "_HID", 4) == 0) {
        EFI_ACPI_HANDLE ValueHandle;
        Status = AcpiTableProtocol->GetOption(DevHandle, 2, &DataType, &Buffer, &DataSize);
        if (EFI_ERROR(Status))
          break;
        if (DataType != EFI_ACPI_DATA_TYPE_CHILD)
          continue;

        AcpiTableProtocol->Open((VOID *) Buffer, &ValueHandle);
        Status = AcpiTableProtocol->GetOption(ValueHandle, 1, &DataType, &Buffer, &DataSize);
        Data = Buffer;
        if (EFI_ERROR(Status) ||
            DataType != EFI_ACPI_DATA_TYPE_STRING ||
            AsciiStrCmp((CHAR8 *) Data, ACPI_ETH_ID) != 0) {
          AcpiTableProtocol->Close(ValueHandle);
          continue;
        }

        DEBUG((DEBUG_VERBOSE, "Found Ethernet device\n"));
        AcpiTableProtocol->Close(ValueHandle);
        Found = 1;
      }
    } else if (DataSize == 1 && Data[0] == AML_METHOD_OP && Found) {
      Status = AcpiTableProtocol->GetOption(DevHandle, 1, &DataType, &Buffer, &DataSize);
      if (EFI_ERROR(Status))
        break;

      Data = Buffer;
      if (DataType == EFI_ACPI_DATA_TYPE_NAME_STRING &&
          AsciiStrnCmp((CHAR8 *) Data, "_DSM", 4) == 0) {
        //
        // Walk the _DSM node
        EFI_ACPI_HANDLE    DSMHandle;
        EFI_ACPI_HANDLE    PkgHandle;
        EFI_ACPI_HANDLE    KeyValueHandle;
        for (DSMHandle = NULL; ; ) {
          Status = AcpiTableProtocol->GetChild(DevHandle, &DSMHandle);
          if (EFI_ERROR(Status) || DSMHandle == NULL)
            break;

          //
          // Search for AML_STORE_OP type
          Status = AcpiTableProtocol->GetOption(DSMHandle, 0, &DataType, &Buffer, &DataSize);
          if (EFI_ERROR(Status))
            continue;

          Data = Buffer;
          if (DataSize != 1 || Data[0] != AML_STORE_OP)
            continue;

          Status = AcpiTableProtocol->GetOption(DSMHandle, 1, &DataType, &Buffer, &DataSize);
          if (EFI_ERROR(Status))
            break;
          DEBUG((DEBUG_VERBOSE, "_DSM Subnode Store Type %d\n", DataType));
          if (DataType != EFI_ACPI_DATA_TYPE_CHILD)
            continue;

          //
          // Open package data
          AcpiTableProtocol->Open((VOID *) Buffer, &PkgHandle);
          Status = AcpiTableProtocol->GetOption(PkgHandle, 0, &DataType, &Buffer, &DataSize);

          Data = Buffer;
          DEBUG((DEBUG_VERBOSE, "_DSM Subnode Store Op Code 0x%02X %02X\n",
                Data[0], DataSize > 1 ? Data[1] : 0));
          if (DataSize != 1 || Data[0] != AML_PACKAGE_OP) {
            AcpiTableProtocol->Close(PkgHandle);
            continue;
          }

          //
          // Walk the package items
          for (KeyValueHandle = NULL; ; ) {
            CHAR16 MACEnv[30];
            CHAR16 MACValue16[30];
            CHAR8 MACBuffer[30];
            UINTN Size;

            Status = AcpiTableProtocol->GetChild(PkgHandle, &KeyValueHandle);
            if (EFI_ERROR(Status) || KeyValueHandle == NULL)
              break;

            Status = AcpiTableProtocol->GetOption(KeyValueHandle, 0, &DataType, &Buffer, &DataSize);
            if (EFI_ERROR(Status))
              break;

            Data = Buffer;
            DEBUG((DEBUG_VERBOSE, "_DSM Key Value Op Code %d 0x%02X %02X\n",
                DataType, Data[0], DataSize > 1 ? Data[1] : 0));
            if (DataSize != 1 && Data[0] != AML_STRING_PREFIX)
              continue;

            Status = AcpiTableProtocol->GetOption(KeyValueHandle, 1, &DataType, &Buffer, &DataSize);
            if (EFI_ERROR(Status))
              break;

            Data = Buffer;
            if (DataType != EFI_ACPI_DATA_TYPE_STRING
                    || AsciiStrCmp((CHAR8 *) Data, ACPI_ETH_MAC_KEY) != 0)
              continue;
            DEBUG((DEBUG_VERBOSE, "_DSM Key Type %d. Found Mac address key\n", DataType));

            //
            // Get the MAC from PCD ENV
            UnicodeSPrint(MACEnv, sizeof(MACEnv), L"%s%d", PREFIX_VARIABLE_NAME, *MacNextID);
            Size = sizeof(MACValue16);
            Status = gRT->GetVariable(MACEnv, &gShellVariableGuid,
                                      0, &Size, (VOID *) MACValue16);
            if (EFI_ERROR(Status)) {
              DEBUG((DEBUG_VERBOSE, "No MAC set for %S\n", MACEnv));

	      UnicodeSPrint(MACEnv, sizeof(MACEnv), L"%s%d", PREFIX_VARIABLE_NAME_COMPAT, *MacNextID);
	      Size = sizeof(MACValue16);
	      Status = gRT->GetVariable(MACEnv, &gShellVariableGuid,
					0, &Size, (VOID *) MACValue16);
	      if (EFI_ERROR(Status)) {
                DEBUG((DEBUG_VERBOSE, "No MAC set for %S\n", MACEnv));
		return EFI_SUCCESS;
	      }
            }
            *MacNextID += 1;
            DEBUG((DEBUG_VERBOSE, "%s %s\n", MACEnv, MACValue16));

            UnicodeStrToAsciiStr(MACValue16, MACBuffer);

            //
            // We found the node. Update the MAC
            Status = AcpiTableProtocol->GetChild(PkgHandle, &KeyValueHandle);
            if (EFI_ERROR(Status) || KeyValueHandle == NULL)
              break;

            Status = AcpiTableProtocol->SetOption(KeyValueHandle, 1, MACBuffer, AsciiStrSize(MACBuffer));
            if (EFI_ERROR(Status))
              break;
            DEBUG((DEBUG_VERBOSE, "Set %s %s\n", MACEnv, MACValue16));
            break;
          }
          AcpiTableProtocol->Close(PkgHandle);
        }
      }
    }
  }

  return EFI_SUCCESS;
}

static EFI_STATUS XGeneProcessDSDT(
  EFI_ACPI_SDT_PROTOCOL *AcpiTableProtocol,
  EFI_ACPI_HANDLE TableHandle)
{
  EFI_STATUS              Status;
  EFI_ACPI_HANDLE         ChildHandle;
  UINTN                   MacEntryID;
  //
  // Parse table for device type
  MacEntryID = 0;
  for (ChildHandle = NULL; ; ) {
    Status = AcpiTableProtocol->GetChild(TableHandle, &ChildHandle);
    if (EFI_ERROR(Status))
      break;
    if (ChildHandle == NULL)
      break;

    XGeneProcessDSDTChild(AcpiTableProtocol, ChildHandle, &MacEntryID);
  }

  return EFI_SUCCESS;
}

EFI_STATUS XGeneEthMACInit(void)
{
  EFI_STATUS              Status;
  EFI_ACPI_SDT_PROTOCOL   *AcpiTableProtocol;
  EFI_ACPI_SDT_HEADER     *Table;
  EFI_ACPI_TABLE_VERSION  TableVersion;
  UINTN                   TableKey;
  EFI_ACPI_HANDLE         TableHandle;
  UINTN                   i;

  DEBUG((DEBUG_VERBOSE, "Configure Ethernet MAC...\n"));

  //
  // Find the AcpiTable protocol
  Status = gBS->LocateProtocol(&gEfiAcpiSdtProtocolGuid, NULL, (VOID**) &AcpiTableProtocol);
  if (EFI_ERROR(Status)) {
    DEBUG((DEBUG_ERROR, "Unable to locate ACPI table protocol\n"));
    return EFI_SUCCESS;
  }

  //
  // Search for DSDT Table
  for (i = 0; i < EFI_ACPI_MAX_NUM_TABLES; i++) {
    Status = AcpiTableProtocol->GetAcpiTable(i, &Table, &TableVersion, &TableKey);
    if (EFI_ERROR(Status))
      break;
    if (Table->Signature != DSDT_SIGNATURE)
      continue;

    Status = AcpiTableProtocol->OpenSdt(TableKey, &TableHandle);
    if (EFI_ERROR(Status))
      break;

    XGeneProcessDSDT(AcpiTableProtocol, TableHandle);

    AcpiTableProtocol->Close(TableHandle);
  }

  return EFI_SUCCESS;
}
