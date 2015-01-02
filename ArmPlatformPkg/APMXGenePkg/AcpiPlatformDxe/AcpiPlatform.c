/** @file
  APM X-Gene ACPI Platform Driver

  Copyright (C) 2014, Red Hat, Inc.
  Copyright (c) 2014, Applied Micro Curcuit Corporation. All rights reserved.

  This program and the accompanying materials are licensed and made available
  under the terms and conditions of the BSD License which accompanies this
  distribution.  The full text of the license may be found at
  http://opensource.org/licenses/bsd-license.php

  THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS, WITHOUT
  WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.
**/
#include <Guid/ArmMpCoreInfo.h>
#include <Guid/ShellVariableGuid.h>
#include <IndustryStandard/Acpi.h>
#include <Library/BaseLib.h>
#include <Library/BaseMemoryLib.h>
#include <Library/DebugLib.h>
#include <Library/PcdLib.h>
#include <Library/PrintLib.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Library/UefiRuntimeServicesTableLib.h>
#include <Protocol/AcpiTable.h>

#include "XGeneCPU.h"

//
// Event to be signalled when PublishArmProcessorTable() in
// "ArmPkg/Drivers/CpuDxe/CpuMpCore.c" installs the gArmMpCoreInfoGuid
// configuration table.
//
// gBS->InstallConfigurationTable() signals the event group with the matching
// GUID. Refer to the documentation of the CreateEventEx() boot service in the
// UEFI spec.
//
STATIC EFI_EVENT mArmMpCoreInfoTableInstalledEvent;

VOID
EFIAPI
OnArmMpCoreInfoTableInstalled (
  IN EFI_EVENT Event,
  IN VOID      *Context
  )
{
  EFI_STATUS Status;

  Status = XGeneInstallApicTable ();
  if (!EFI_ERROR (Status)) {
    DEBUG ((EFI_D_INFO,
      "%a: installed MADT based on MpCoreInfo config table\n",
      __FUNCTION__));
    gBS->CloseEvent (Event);
  }
}

//
// We'll generate AML for the following SSDT:
//
// DefinitionBlock("Ssdt.aml", "SSDT", 2, "REDHAT", "MACADDRS", 0x00000001)
// {
//   Name (\MAC0, Package (6) { 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF })
//   Name (\MAC1, Package (6) { 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF })
//   ...
//   Name (\MACn, Package (6) { 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF })
// }
//
#define NUM_MACS      3
#define NUM_MAC_BYTES 6

#pragma pack(1)
typedef struct {
  UINT8 BytePrefix;
  UINT8 ByteValue;
} AML_BYTE;

typedef struct {
  UINT8    NameOp;
  UINT8    RootChar;
  UINT32   Name;
  UINT8    PackageOp;
  UINT8    PkgLength;
  UINT8    NumElements;
  AML_BYTE MacAddr[NUM_MAC_BYTES];
} MAC_PACKAGE;

typedef struct {
  EFI_ACPI_DESCRIPTION_HEADER Hdr;
  MAC_PACKAGE                 MacPackage[NUM_MACS];
} MAC_SSDT;
#pragma pack()

STATIC
EFI_STATUS
EFIAPI
InstallMacAddrSsdt (
  VOID
  )
{
  MAC_SSDT                Ssdt;
  UINTN                   MacIdx;
  EFI_STATUS              Status;
  EFI_ACPI_TABLE_PROTOCOL *AcpiTableProtocol;
  UINTN                   TableKey;

  Ssdt.Hdr.Signature       = SIGNATURE_32 ('S', 'S', 'D', 'T');
  Ssdt.Hdr.Length          = sizeof Ssdt;
  Ssdt.Hdr.Revision        = 2;
  Ssdt.Hdr.Checksum        = 0;
  Ssdt.Hdr.OemTableId      = SIGNATURE_64 ('M', 'A', 'C',
                               'A', 'D', 'D', 'R', 'S');
  Ssdt.Hdr.OemRevision     = 1;
  Ssdt.Hdr.CreatorId       = PcdGet32 (PcdAcpiDefaultCreatorId);
  Ssdt.Hdr.CreatorRevision = PcdGet32 (PcdAcpiDefaultCreatorRevision);

  CopyMem (Ssdt.Hdr.OemId, "REDHAT", 6);

  for (MacIdx = 0; MacIdx < NUM_MACS; ++MacIdx) {
    CHAR16      MacName[3 + 1 + 1];
    UINTN       DataSize;
    CHAR16      MacValue[NUM_MAC_BYTES * 3 - 1 + 1];
    MAC_PACKAGE *MacPkg;
    UINTN       ByteIdx;

    UnicodeSPrintAsciiFormat (MacName, sizeof MacName, "MAC%c", L'0' + MacIdx);
    DataSize = sizeof MacValue;
    Status = gRT->GetVariable (MacName, &gShellVariableGuid,
                    NULL /* Attributes */, &DataSize, MacValue);
    if (EFI_ERROR (Status) || DataSize != sizeof MacValue ||
        MacValue[NUM_MAC_BYTES * 3 - 1] != L'\0') {
      DEBUG ((EFI_D_WARN, "%a: failed to retrieve \"%s\": Status=\"%r\" "
        "DataSize=0x%Lx\n", __FUNCTION__, MacName, Status, (UINT64)DataSize));
      StrnCpy (MacValue, L"FF:FF:FF:FF:FF:FF", NUM_MAC_BYTES * 3 - 1);
    } else {
      DEBUG ((EFI_D_INFO, "%a: fetched \"%s\": \"%s\"\n", __FUNCTION__,
        MacName, MacValue));
    }

    MacPkg              = Ssdt.MacPackage + MacIdx;
    MacPkg->NameOp      = 0x08;
    MacPkg->RootChar    = '\\';
    MacPkg->Name        = SIGNATURE_32 ('M', 'A', 'C', ('0' + MacIdx));
    MacPkg->PackageOp   = 0x12;
    MacPkg->PkgLength   = sizeof *MacPkg - OFFSET_OF (MAC_PACKAGE, PkgLength);
    MacPkg->NumElements = NUM_MAC_BYTES;

    for (ByteIdx = 0; ByteIdx < NUM_MAC_BYTES; ++ByteIdx) {
      AML_BYTE *AmlByte;

      AmlByte             = MacPkg->MacAddr + ByteIdx;
      AmlByte->BytePrefix = 0x0A;
      AmlByte->ByteValue  = StrHexToUintn (MacValue + ByteIdx * 3);
    }
  }

  Status = gBS->LocateProtocol (&gEfiAcpiTableProtocolGuid,
                  NULL /* Registration */,
                  (VOID **)&AcpiTableProtocol);
  if (EFI_ERROR (Status)) {
    DEBUG ((EFI_D_ERROR, "%a: LocateProtocol: %r\n", __FUNCTION__, Status));
    return Status;
  }

  Status = AcpiTableProtocol->InstallAcpiTable (AcpiTableProtocol, &Ssdt,
                                sizeof Ssdt, &TableKey);
  if (EFI_ERROR (Status)) {
    DEBUG ((EFI_D_ERROR, "%a: InstallAcpiTable: %r\n", __FUNCTION__, Status));
  }
  return Status;
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
  EFI_STATUS Status;

  Status = gBS->CreateEventEx (
                  EVT_NOTIFY_SIGNAL,                 // Type,
                  TPL_CALLBACK,                      // NotifyTpl
                  OnArmMpCoreInfoTableInstalled,     // NotifyFunction
                  NULL,                              // NotifyContext
                  &gArmMpCoreInfoGuid,               // EventGroup
                  &mArmMpCoreInfoTableInstalledEvent // Event
                  );
  ASSERT_EFI_ERROR(Status);

  //
  // The configuration table may already exist, kick the event to check.
  //
  gBS->SignalEvent (mArmMpCoreInfoTableInstalledEvent);

  InstallMacAddrSsdt ();
  return EFI_SUCCESS;
}
