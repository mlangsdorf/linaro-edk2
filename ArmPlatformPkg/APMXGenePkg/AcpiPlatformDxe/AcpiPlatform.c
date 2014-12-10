/** @file
  APM X-Gene ACPI Platform Driver

  Copyright (c) 2014, Applied Micro Curcuit Corporation. All rights reserved.<BR>
  This program and the accompanying materials
  are licensed and made available under the terms and conditions of the BSD License
  which accompanies this distribution.  The full text of the license may be found at
  http://opensource.org/licenses/bsd-license.php

  THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
  WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.

**/
#include <PiDxe.h>
#include <Guid/EventGroup.h>
#include <Guid/ArmMpCoreInfo.h>
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
#include <Protocol/AcpiTable.h>
#include <Guid/Acpi.h>
#include <IndustryStandard/Acpi51.h>
#include "XGeneEthMAC.h"
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

/**
  This function calculates and updates an UINT8 checksum.

  @param[in]  Buffer          Pointer to buffer to checksum
  @param[in]  Size            Number of bytes to checksum

**/
VOID
AcpiTableChecksum (
  IN UINT8      *Buffer,
  IN UINTN      Size
  )
{
  UINTN ChecksumOffset;

  ChecksumOffset = OFFSET_OF (EFI_ACPI_DESCRIPTION_HEADER, Checksum);

  //
  // Set checksum to 0 first.
  //
  Buffer[ChecksumOffset] = 0;

  //
  // Update checksum value.
  //
  Buffer[ChecksumOffset] = CalculateCheckSum8 (Buffer, Size);
}

/**
  Notify function for event group EVT_SIGNAL_EXIT_BOOT_SERVICES. This is used
  to configure the system clock and PHY accordingly.

  @param[in]  Event   The Event that is being processed.
  @param[in]  Context The Event Context.

**/
VOID
EFIAPI
OnAcpiExitBootServices(
  IN EFI_EVENT        Event,
  IN VOID             *Context
  )
{
  // Configure Ethernet MAC accordingly
  XGeneEthMACInit();
}

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
  EFI_EVENT  ExitBootServicesEvent;

  Status = gBS->CreateEvent (
                  EVT_SIGNAL_EXIT_BOOT_SERVICES,
                  TPL_NOTIFY,
                  OnAcpiExitBootServices,
                  NULL,
                  &ExitBootServicesEvent);
  ASSERT_EFI_ERROR(Status);

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

  return EFI_SUCCESS;
}
