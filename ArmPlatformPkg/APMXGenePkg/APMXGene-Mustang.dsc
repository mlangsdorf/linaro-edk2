##
#  Copyright (c) 2013, AppliedMicro Corp. All rights reserved.
#
#  This program and the accompanying materials
#  are licensed and made available under the terms and conditions of the BSD License
#  which accompanies this distribution.  The full text of the license may be found at
#  http://opensource.org/licenses/bsd-license.php
#
#  THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
#  WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.
#
#  NOR Flash Layout
#
#  0x0000.0000 - 0x006F.FFFF => TianoCore
#  0x0007.0000 - 0x0007.FFFF => TianoCore Variables
#
#  0x0080.0000 - 0x010F.FFFF => Linux Kernel
#  0x0150.0000 - 0x0150.FFFF => DTS
#  0x0160.0000 - 0x019F.FFFF => Init ram disk (uRamdisk)
#
################################################################################
#
# Defines Section - statements that will be processed to create a Makefile.
#
################################################################################
[Defines]
  PLATFORM_NAME                  = APMXGene-Mustang
  PLATFORM_GUID                  = edcba8fd-a24e-489c-b4e9-93561f576500
  PLATFORM_VERSION               = 0.1
  DSC_SPECIFICATION              = 0x00010005
  OUTPUT_DIRECTORY               = Build/APMXGene-Mustang
  SUPPORTED_ARCHITECTURES        = AARCH64
  BUILD_TARGETS                  = DEBUG|RELEASE
  SKUID_IDENTIFIER               = DEFAULT
  FLASH_DEFINITION               = ArmPlatformPkg/APMXGenePkg/APMXGene-Mustang.fdf

!include ArmPlatformPkg/APMXGenePkg/APMXGene.dsc.inc

[LibraryClasses.common]
  ArmLib|ArmPkg/Library/ArmLib/AArch64/AArch64Lib.inf
  ArmPlatformLib|ArmPlatformPkg/APMXGenePkg/Library/APMXGeneArmPlatformLib/APMXGeneArmPlatformLib.inf
  APMXGeneMemcLib|ArmPlatformPkg/APMXGenePkg/Library/APMXGeneMemcLib/APMXGeneMemcLib.inf
  STMicroLib|ArmPlatformPkg/APMXGenePkg/Drivers/STMicro/STMicro.inf
  I2CLib|ArmPlatformPkg/APMXGenePkg/Library/I2CLib/I2CLib.inf
  SPILib|ArmPlatformPkg/APMXGenePkg/Library/SPILib/SPILib.inf
  SPIFlashLib|ArmPlatformPkg/APMXGenePkg/Library/SPIFlashLib/SPIFlashLib.inf
  SerialPortLib|ArmPlatformPkg/APMXGenePkg/Library/DWSerialPortLib/DWSerialPortLib.inf
  RegDumpLib|ArmPlatformPkg/APMXGenePkg/Library/APMXGeneRegDumpLib/APMXGeneRegDump.inf
  ArmPlatformDeviceTree|ArmPlatformPkg/APMXGenePkg/DeviceTree/DeviceTree.inf

  # ARM General Interrupt Driver in Secure and Non-secure
  ArmGicLib|ArmPkg/Drivers/ArmGic/ArmGicLib.inf

  TimerLib|ArmPkg/Library/ArmArchTimerLib/ArmArchTimerLib.inf

  # Network General
  NetLib|MdeModulePkg/Library/DxeNetLib/DxeNetLib.inf
  IpIoLib|MdeModulePkg/Library/DxeIpIoLib/DxeIpIoLib.inf
  UdpIoLib|MdeModulePkg/Library/DxeUdpIoLib/DxeUdpIoLib.inf
  DpcLib|MdeModulePkg/Library/DxeDpcLib/DxeDpcLib.inf

  UefiScsiLib|MdePkg/Library/UefiScsiLib/UefiScsiLib.inf
  UefiUsbLib|MdePkg/Library/UefiUsbLib/UefiUsbLib.inf

  XGenePHYLib|ArmPlatformPkg/APMXGenePkg/Library/APMXGenePHYLib/APMXGenePHYLib.inf

[LibraryClasses.common.SEC]
  ArmLib|ArmPkg/Library/ArmLib/AArch64/AArch64LibSec.inf
  ArmPlatformSecLib|ArmPlatformPkg/APMXGenePkg/Library/APMXGeneSecLib/APMXGeneSecLib.inf

  # Uncomment to turn on GDB stub in SEC.
  #DebugAgentLib|EmbeddedPkg/Library/GdbDebugAgent/GdbDebugAgent.inf

  #ArmGicSecLib|ArmPkg/Drivers/ArmGic/ArmGicSecLib.inf
  #ArmGicLib|ArmPkg/Drivers/ArmGic/ArmGicSecLib.inf

[BuildOptions]
  GCC:*_*_AARCH64_ARCHCC_FLAGS = -mgeneral-regs-only -DARM_CPU_AARCH64 -DAPM_XGENE -DAPM_XGENE_SPI_FLASH -DAPM_XGENE_BOOT_SPI_NOR -fno-omit-frame-pointer
  GCC:*_*_AARCH64_PP_FLAGS = -DARM_CPU_AARCH64
  GCC:*_*_AARCH64_PLATFORM_FLAGS == -I$(WORKSPACE)/ArmPlatformPkg/APMXGenePkg/Include

################################################################################
#
# Pcd Section - list of all EDK II PCD Entries defined by this Platform
#
################################################################################

[PcdsFeatureFlag.common]
 !ifdef $(EDK2_SKIP_PEICORE)
   gArmPlatformTokenSpaceGuid.PcdSystemMemoryInitializeInSec|TRUE
   gArmPlatformTokenSpaceGuid.PcdSendSgiToBringUpSecondaryCores|TRUE
 !endif

   ## If TRUE, Graphics Output Protocol will be installed on virtual handle created by ConsplitterDxe.
   #  It could be set FALSE to save size.
   gEfiMdeModulePkgTokenSpaceGuid.PcdConOutGopSupport|TRUE
   
   #
   # PCIE
   #
   gArmPlatformTokenSpaceGuid.PcdPcieRootBridgeResetGpio|TRUE
   gEfiMdeModulePkgTokenSpaceGuid.PcdInstallAcpiSdtProtocol|TRUE

[PcdsDynamicDefault.common]
   gArmTokenSpaceGuid.PcdBootingLinuxUEFI|1

[PcdsFixedAtBuild.common]
   gEfiMdeModulePkgTokenSpaceGuid.PcdFirmwareVersionString|L"1.0.0"
   gArmPlatformTokenSpaceGuid.PcdFirmwareVendor|"X-Gene Mustang Board"
   gEmbeddedTokenSpaceGuid.PcdEmbeddedPrompt|"Mustang"
   gEmbeddedTokenSpaceGuid.PcdTimerPeriod|100000

   # Memory base start at 0x40.00000000 and above
   gArmTokenSpaceGuid.PcdSystemMemoryBase|0x4000000000
   # System Memory (4GB)
   gArmTokenSpaceGuid.PcdSystemMemorySize|0x100000000


   #
   # NV Storage PCDs. Use base of 0x0780000 for NOR0
   #
   gEfiMdeModulePkgTokenSpaceGuid.PcdFlashNvStorageVariableBase|0x800000
   gEfiMdeModulePkgTokenSpaceGuid.PcdFlashNvStorageVariableSize|0x020000
   gEfiMdeModulePkgTokenSpaceGuid.PcdFlashNvStorageFtwWorkingBase|0x820000
   gEfiMdeModulePkgTokenSpaceGuid.PcdFlashNvStorageFtwWorkingSize|0x020000
   gEfiMdeModulePkgTokenSpaceGuid.PcdFlashNvStorageFtwSpareBase|0x840000
   gEfiMdeModulePkgTokenSpaceGuid.PcdFlashNvStorageFtwSpareSize|0x020000

   gArmTokenSpaceGuid.PcdVFPEnabled|1

   # Stacks for MPCores in Secure World (Top of OCM)
   gArmPlatformTokenSpaceGuid.PcdCPUCoresSecStackBase|0x1D0FF000
   gArmPlatformTokenSpaceGuid.PcdCPUCoreSecPrimaryStackSize|0x1000
   # For store Mem size after DDR calibration
   gArmPlatformTokenSpaceGuid.PcdMemSizeAddr|0x1D0FEFF8

   # For store TTB for initialize MMU before DDR calibration. 4K alignment
   gArmPlatformTokenSpaceGuid.PcdTTBBaseAddr|0x1D0A6000

   # Stacks for MPCores in Monitor Mode
   #gArmPlatformTokenSpaceGuid.PcdCPUCoresSecMonStackBase|0x2E008000
   #gArmPlatformTokenSpaceGuid.PcdCPUCoreSecMonStackSize|0x100

   # Stacks for MPCores in Normal World
   gArmPlatformTokenSpaceGuid.PcdCPUCoresStackBase|0x4001100000
   gArmPlatformTokenSpaceGuid.PcdCPUCorePrimaryStackSize|0x4000

   # Size of the region used by UEFI in permanent memory (Reserved 32MB)
   gArmPlatformTokenSpaceGuid.PcdSystemMemoryUefiRegionSize|0x08000000

   #
   # ARM Pcds
   gArmTokenSpaceGuid.PcdArmUncachedMemoryMask|0x0000000000000000

   # DW - Serial Terminal
   gEfiMdeModulePkgTokenSpaceGuid.PcdSerialRegisterBase|0x1C020000
   gEfiMdePkgTokenSpaceGuid.PcdUartDefaultBaudRate|115200
   gEfiMdePkgTokenSpaceGuid.PcdUartDefaultDataBits|8
   gEfiMdePkgTokenSpaceGuid.PcdUartDefaultParity|0
   gEfiMdePkgTokenSpaceGuid.PcdUartDefaultStopBits|1

   #
   # AHBC
   gArmPlatformTokenSpaceGuid.PcdAHBCRegisterBase|0x1f2a0000

   # DW SPI
   gArmPlatformTokenSpaceGuid.PcdDWSpiBaseAddress|0x1C025000
   gArmPlatformTokenSpaceGuid.PcdDWSpiClkInHz|12000000
   gArmPlatformTokenSpaceGuid.PcdDWSpiMaxCS|3
   gArmPlatformTokenSpaceGuid.PcdDWSpiFifoDepth|256
   gArmPlatformTokenSpaceGuid.PcdDWSpiSysClk|100000000
   gArmPlatformTokenSpaceGuid.PcdDWSpiVerId|0x3331352A

   # DW I2C
   gArmPlatformTokenSpaceGuid.PcdSysClkInHz|100000000

   #
   # ARM General Interrupt Controller
   gArmTokenSpaceGuid.PcdGicDistributorBase|0x78090000
   gArmTokenSpaceGuid.PcdGicInterruptInterfaceBase|0x780a0000

   #
   # ARM OS Loader
   #
   gArmTokenSpaceGuid.PcdArmMachineType|2272

   gArmPlatformTokenSpaceGuid.PcdDefaultBootDescription|L"BOOT OS LOADER"
   gArmPlatformTokenSpaceGuid.PcdDefaultBootType|0
   gArmPlatformTokenSpaceGuid.PcdDefaultBootArgument|"console=ttyS0,115200 root=/dev/ram rw earlyprintk=uart8250-32bit,0x1c020000 debug"

   # From NOR MTD
   #gArmPlatformTokenSpaceGuid.PcdDefaultBootDevicePath|L"VenHw(F40A3869-92C4-4275-8501-4491A1A20C19)/\\uImage"
   #gArmPlatformTokenSpaceGuid.PcdFdtDevicePath|L"VenHw(F40A3869-92C4-4275-8501-4491A1A20C19)/\\apm-mustang.dtb"
   #gArmPlatformTokenSpaceGuid.PcdDefaultBootInitrdPath|L"VenHw(F40A3869-92C4-4275-8501-4491A1A20C19)/\\uRamdisk"

   # From SD
   gArmPlatformTokenSpaceGuid.PcdDefaultBootDevicePath|L"VenHw(B225ED30-6DFD-43A9-BF6B-5753358F2F70)/HD(1,MBR,0x00000000,0x800,0x3AE800)/efi\\boot\\bootaa64.efi"
   gArmPlatformTokenSpaceGuid.PcdFdtDevicePath|L"VenHw(B225ED30-6DFD-43A9-BF6B-5753358F2F70)/HD(1,MBR,0x00000000,0x800,0x1D7400)/\\apm-mustang.dtb"
   gArmPlatformTokenSpaceGuid.PcdDefaultBootInitrdPath|L"VenHw(B225ED30-6DFD-43A9-BF6B-5753358F2F70)/HD(1,MBR,0x00000000,0x800,0x1D7400)/\\uRamdisk"

   # From SATA disk
   #gArmPlatformTokenSpaceGuid.PcdDefaultBootDevicePath|L"VenHw(F9DD58FC-C9AC-4C50-9F78-A7631E79B296)/Sata(0x0,0x0,0x0)/HD(1,MBR,0x4178A07E,0x800,0x3C00000)/\\uImage"
   #gArmPlatformTokenSpaceGuid.PcdFdtDevicePath|L"VenHw(F9DD58FC-C9AC-4C50-9F78-A7631E79B296)/Sata(0x0,0x0,0x0)/HD(1,MBR,0x4178A07E,0x800,0x3C00000)/\\mustang.dtb"
   #gArmPlatformTokenSpaceGuid.PcdDefaultBootInitrdPath|L"VenHw(F9DD58FC-C9AC-4C50-9F78-A7631E79B296)/Sata(0x0,0x0,0x0)/HD(1,MBR,0x4178A07E,0x800,0x3C00000)/\\uRamdisk"

   # Use the serial console (ConIn & ConOut) and the Graphic driver (ConOut)
   gArmPlatformTokenSpaceGuid.PcdDefaultConOutPaths|L"VenHw(D3987D4B-971A-435F-8CAF-4967EB627241)/Uart(115200,8, N,1)/VenPcAnsi()"
   gArmPlatformTokenSpaceGuid.PcdDefaultConInPaths|L"VenHw(D3987D4B-971A-435F-8CAF-4967EB627241)/Uart(115200,8, N,1)/VenPcAnsi()"
   gArmPlatformTokenSpaceGuid.PcdPlatformBootTimeOut|5

   #
   # ARM Architectual Timer Frequency
   #
   gArmTokenSpaceGuid.PcdArmArchTimerFreqInHz|50000000

   # SATA
   gArmPlatformTokenSpaceGuid.PcdSataControllerMask|0x6 # Controller 1,2

   # USB
   gArmPlatformTokenSpaceGuid.PcdUsbControllerMask|0x3

   #
   # SD
   #
   gArmPlatformTokenSpaceGuid.PcdSDIOCapLow|0xA0FC1970
   gArmPlatformTokenSpaceGuid.PcdSDIOCapHigh|0x0000008F
   gArmPlatformTokenSpaceGuid.PcdSDIOHostPhyEnableMask|1
   
   #
   # PCIE
   #
   gArmPlatformTokenSpaceGuid.PcdPcieRootBridgeMask|0x1 # Port 0 enabled
   gArmPlatformTokenSpaceGuid.PcdPcieRootBridgeGen|0x33333
   gArmPlatformTokenSpaceGuid.PcdPcieRootBridgeWidth|0x48148
   gArmPlatformTokenSpaceGuid.PcdPcieRootBridgeResetGpioPin|0x19

################################################################################
#
# Components Section - list of all EDK II Modules needed by this Platform
#
################################################################################
[Components.common]

  #
  # SEC
  #
  # ArmPlatformPkg/Sec/Sec.inf
  ArmPlatformPkg/APMXGenePkg/Sec/Sec.inf {
       <LibraryClasses>
       ArmPlatformSecLib|ArmPlatformPkg/APMXGenePkg/Library/APMXGeneSecLib/APMXGeneSecLib.inf
       APMXGeneMemcLib|ArmPlatformPkg/APMXGenePkg/Library/APMXGeneMemcLib/APMXGeneMemcLib.inf
  }

  #
  # PEI Phase modules
  #
 !ifdef $(EDK2_SKIP_PEICORE)
   ArmPlatformPkg/PrePi/PeiMPCore.inf {
       <LibraryClasses>
       ArmLib|ArmPkg/Library/ArmLib/AArch64/AArch64Lib.inf
       ArmPlatformLib|ArmPlatformPkg/APMXGenePkg/Library/APMXGeneArmPlatformLib/APMXGeneArmPlatformLib.inf
       ArmPlatformGlobalVariableLib|ArmPlatformPkg/Library/ArmPlatformGlobalVariableLib/PrePi/PrePiArmPlatformGlobalVariableLib.inf
   }
 !else
   ArmPlatformPkg/PrePeiCore/PrePeiCoreMPCore.inf {
       <LibraryClasses>
       ArmPlatformGlobalVariableLib|ArmPlatformPkg/Library/ArmPlatformGlobalVariableLib/Pei/PeiArmPlatformGlobalVariableLib.inf
   }
   MdeModulePkg/Core/Pei/PeiMain.inf
   MdeModulePkg/Universal/PCD/Pei/Pcd.inf  {
       <LibraryClasses>
       PcdLib|MdePkg/Library/BasePcdLibNull/BasePcdLibNull.inf
   }
   ArmPlatformPkg/PlatformPei/PlatformPeim.inf
   ArmPlatformPkg/MemoryInitPei/MemoryInitPeim.inf {
       <LibraryClasses>
	   PcdLib|MdePkg/Library/PeiPcdLib/PeiPcdLib.inf
   }
   ArmPkg/Drivers/CpuPei/CpuPei.inf
   IntelFrameworkModulePkg/Universal/StatusCode/Pei/StatusCodePei.inf
   Nt32Pkg/BootModePei/BootModePei.inf
   MdeModulePkg/Universal/Variable/Pei/VariablePei.inf
   MdeModulePkg/Core/DxeIplPeim/DxeIpl.inf {
       <LibraryClasses>
       NULL|IntelFrameworkModulePkg/Library/LzmaCustomDecompressLib/LzmaCustomDecompressLib.inf
   }
 !endif

   #
   # DXE
   #
   MdeModulePkg/Universal/PCD/Dxe/Pcd.inf  {
       <LibraryClasses>
       PcdLib|MdePkg/Library/BasePcdLibNull/BasePcdLibNull.inf
   }

   MdeModulePkg/Core/Dxe/DxeMain.inf {
       <LibraryClasses>
       PcdLib|MdePkg/Library/BasePcdLibNull/BasePcdLibNull.inf
       NULL|MdeModulePkg/Library/DxeCrc32GuidedSectionExtractLib/DxeCrc32GuidedSectionExtractLib.inf
   }

   #
   # SMBIOS
   #
   MdeModulePkg/Universal/SmbiosDxe/SmbiosDxe.inf
   ArmPlatformPkg/APMXGenePkg/PlatformSmbiosDxe/PlatformSmbiosDxe.inf {
       <LibraryClasses>
       SmbiosLib|ArmPlatformPkg/APMXGenePkg/Library/SmbiosLib/SmbiosLib.inf
   }

   #
   # Architectural Protocols
   #
   ArmPkg/Drivers/CpuDxe/CpuDxe.inf
   ArmPlatformPkg/Drivers/NorFlashDxe/NorFlashDxe.inf
   MdeModulePkg/Core/RuntimeDxe/RuntimeDxe.inf
   MdeModulePkg/Universal/SecurityStubDxe/SecurityStubDxe.inf
   MdeModulePkg/Universal/CapsuleRuntimeDxe/CapsuleRuntimeDxe.inf
   MdeModulePkg/Universal/Variable/RuntimeDxe/VariableRuntimeDxe.inf
   MdeModulePkg/Universal/FaultTolerantWriteDxe/FaultTolerantWriteDxe.inf
   MdeModulePkg/Universal/MonotonicCounterRuntimeDxe/MonotonicCounterRuntimeDxe.inf
   EmbeddedPkg/ResetRuntimeDxe/ResetRuntimeDxe.inf
   EmbeddedPkg/RealTimeClockRuntimeDxe/RealTimeClockRuntimeDxe.inf
   EmbeddedPkg/MetronomeDxe/MetronomeDxe.inf

   MdeModulePkg/Universal/Console/ConPlatformDxe/ConPlatformDxe.inf
   #MdeModulePkg/Universal/Console/ConSplitterDxe/ConSplitterDxe.inf
   #MdeModulePkg/Universal/Console/GraphicsConsoleDxe/GraphicsConsoleDxe.inf
   MdeModulePkg/Universal/Console/TerminalDxe/TerminalDxe.inf
   EmbeddedPkg/SerialDxe/SerialDxe.inf

   MdeModulePkg/Universal/HiiDatabaseDxe/HiiDatabaseDxe.inf

   ArmPkg/Drivers/ArmGic/ArmGicDxe.inf
   ArmPkg/Drivers/TimerDxe/TimerDxe.inf
   MdeModulePkg/Universal/WatchdogTimerDxe/WatchdogTimer.inf

   #
   # Semi-hosting filesystem
   #
   #ArmPkg/Filesystem/SemihostFs/SemihostFs.inf

   #
   # Multimedia Card Interface
   #
   EmbeddedPkg/Universal/MmcDxe/MmcDxe.inf
   ArmPlatformPkg/APMXGenePkg/Drivers/MciDxe/MciDxe.inf

   #
   # FAT filesystem + GPT/MBR partitioning
   #
   MdeModulePkg/Universal/Disk/DiskIoDxe/DiskIoDxe.inf
   MdeModulePkg/Universal/Disk/PartitionDxe/PartitionDxe.inf
   MdeModulePkg/Universal/Disk/UnicodeCollation/EnglishDxe/EnglishDxe.inf

   #
   # USB XHCI Support
   #
   ArmPlatformPkg/APMXGenePkg/Bus/Usb/UsbControllerDxe/UsbControllerDxe.inf
   MdeModulePkg/Bus/Usb/UsbBusDxe/UsbBusDxe.inf
   MdeModulePkg/Bus/Pci/XhciDxe/XhciDxe.inf
   MdeModulePkg/Bus/Usb/UsbMassStorageDxe/UsbMassStorageDxe.inf
   MdeModulePkg/Bus/Usb/UsbKbDxe/UsbKbDxe.inf

   #
   # Application
   #
   EmbeddedPkg/Ebl/Ebl.inf

 !ifdef $(EDK2_ARMVE_UEFI2_SHELL)
   ShellPkg/Application/Shell/Shell.inf {
     <LibraryClasses>
       ShellCommandLib|ShellPkg/Library/UefiShellCommandLib/UefiShellCommandLib.inf
       NULL|ShellPkg/Library/UefiShellLevel2CommandsLib/UefiShellLevel2CommandsLib.inf
       NULL|ShellPkg/Library/UefiShellLevel1CommandsLib/UefiShellLevel1CommandsLib.inf
       NULL|ShellPkg/Library/UefiShellLevel3CommandsLib/UefiShellLevel3CommandsLib.inf
       NULL|ShellPkg/Library/UefiShellDriver1CommandsLib/UefiShellDriver1CommandsLib.inf
       NULL|ShellPkg/Library/UefiShellInstall1CommandsLib/UefiShellInstall1CommandsLib.inf
       NULL|ShellPkg/Library/UefiShellDebug1CommandsLib/UefiShellDebug1CommandsLib.inf
       NULL|ShellPkg/Library/UefiShellNetwork1CommandsLib/UefiShellNetwork1CommandsLib.inf
       HandleParsingLib|ShellPkg/Library/UefiHandleParsingLib/UefiHandleParsingLib.inf
       FileHandleLib|ShellPkg/Library/UefiFileHandleLib/UefiFileHandleLib.inf
       ShellLib|ShellPkg/Library/UefiShellLib/UefiShellLib.inf
       SortLib|ShellPkg/Library/UefiSortLib/UefiSortLib.inf
       PathLib|ShellPkg/Library/BasePathLib/BasePathLib.inf

     <PcdsFixedAtBuild>
       gEfiMdePkgTokenSpaceGuid.PcdDebugPropertyMask|0xFF
       gEfiShellPkgTokenSpaceGuid.PcdShellLibAutoInitialize|FALSE
       gEfiMdePkgTokenSpaceGuid.PcdUefiLibMaxPrintBufferSize|16000
   }
 !endif

   #
   # ACPI Support
   #
   MdeModulePkg/Universal/Acpi/AcpiTableDxe/AcpiTableDxe.inf
   MdeModulePkg/Universal/Acpi/AcpiPlatformDxe/AcpiPlatformDxe.inf
   ArmPlatformPkg/APMXGenePkg/AcpiPlatformDxe/AcpiPlatformDxe.inf
   ArmPlatformPkg/APMXGenePkg/AcpiTables/APMXGene-Mustang/AcpiTables.inf

   #
   # Bds
   #
   MdeModulePkg/Universal/DevicePathDxe/DevicePathDxe.inf
   ArmPlatformPkg/Bds/Bds.inf {
     <LibraryClasses>
       PcdLib|MdePkg/Library/DxePcdLib/DxePcdLib.inf
   }

   #
   # Network stack drivers
   #
   MdeModulePkg/Universal/Network/DpcDxe/DpcDxe.inf
   MdeModulePkg/Universal/Network/ArpDxe/ArpDxe.inf
   MdeModulePkg/Universal/Network/Dhcp4Dxe/Dhcp4Dxe.inf
   MdeModulePkg/Universal/Network/Ip4ConfigDxe/Ip4ConfigDxe.inf
   MdeModulePkg/Universal/Network/Ip4Dxe/Ip4Dxe.inf
   MdeModulePkg/Universal/Network/MnpDxe/MnpDxe.inf
   MdeModulePkg/Universal/Network/VlanConfigDxe/VlanConfigDxe.inf
   MdeModulePkg/Universal/Network/Mtftp4Dxe/Mtftp4Dxe.inf
   MdeModulePkg/Universal/Network/Tcp4Dxe/Tcp4Dxe.inf
   MdeModulePkg/Universal/Network/Udp4Dxe/Udp4Dxe.inf
   MdeModulePkg/Universal/Network/UefiPxeBcDxe/UefiPxeBcDxe.inf
   ArmPlatformPkg/APMXGenePkg/Drivers/SnpDxe/SnpDxe.inf
   ArmPlatformPkg/APMXGenePkg/Drivers/MellanoxDxe/SnpDxe.inf
   
   #
   # PCI Support
   #
   ArmPlatformPkg/APMXGenePkg/Drivers/GpioDxe/GpioDxe.inf
   ArmPlatformPkg/APMXGenePkg/Bus/Pci/PciHostBridgeDxe/PciHostBridgeDxe.inf {
     <LibraryClasses>
       PcdLib|MdePkg/Library/DxePcdLib/DxePcdLib.inf
   }
   MdeModulePkg/Bus/Pci/PciBusDxe/PciBusDxe.inf
   
   #
   # IDE/AHCI Support
   #
   ArmPlatformPkg/APMXGenePkg/Drivers/SataControllerNewDxe/SataControllerDxe.inf
   DuetPkg/SataControllerDxe/SataControllerDxe.inf
   MdeModulePkg/Bus/Ata/AtaAtapiPassThru/AtaAtapiPassThru.inf
   MdeModulePkg/Bus/Ata/AtaBusDxe/AtaBusDxe.inf
   MdeModulePkg/Bus/Scsi/ScsiBusDxe/ScsiBusDxe.inf
   MdeModulePkg/Bus/Scsi/ScsiDiskDxe/ScsiDiskDxe.inf
   
   #
   # Misc
   #
   ArmPlatformPkg/APMXGenePkg/Drivers/L3CacheDxe/L3CacheDxe.inf
