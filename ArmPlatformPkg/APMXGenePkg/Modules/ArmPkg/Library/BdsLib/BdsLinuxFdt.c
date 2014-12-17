/** @file
*
*  Copyright (c) 2011-2013, ARM Limited. All rights reserved.
*
*  This program and the accompanying materials
*  are licensed and made available under the terms and conditions of the BSD License
*  which accompanies this distribution.  The full text of the license may be found at
*  http://opensource.org/licenses/bsd-license.php
*
*  THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
*  WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.
*
**/

#include <Library/ArmSmcLib.h>
#include <Library/PcdLib.h>
#include <libfdt.h>
#include <IndustryStandard/ArmSmc.h>
#include "BdsInternal.h"
#include "BdsLinuxLoader.h"

#define ALIGN(x, a)     (((x) + ((a) - 1)) & ~((a) - 1))
#define PALIGN(p, a)    ((void *)(ALIGN((unsigned long)(p), (a))))
#define GET_CELL(p)     (p += 4, *((const UINT32 *)(p-4)))
#define PREFIX_VARIABLE_NAME            L"MAC"
#define A_D(x) (((x >= L'a')&&(x <= L'f'))?(x-L'a'+0xa):(((x >= L'A')&&(x <= L'F'))?(x-L'A'+0xa):(x-L'0')))
#define CONFIG_INTERFACE_COUNT 4

#ifdef AARCH64_MP_PROTOCOL
#define CPU_OFFSET  8
#else
#define CPU_OFFSET  0
#endif

extern EFI_GUID gShellVariableGuid;
UINT8 ApmMacAddr[][6] = {{0x00}, {0x00}, {0x00}, {0x00}};

VOID AsciiStrToEthAddr (CHAR16 *MACStr, UINT8 *MAC)
{
  *MAC++ = (A_D(*MACStr)<<4) + A_D(*(MACStr+1));
  *MAC++ = (A_D(*(MACStr+3))<<4) + A_D(*(MACStr+4));
  *MAC++ = (A_D(*(MACStr+6))<<4) + A_D(*(MACStr+7));
  *MAC++ = (A_D(*(MACStr+9))<<4) + A_D(*(MACStr+10));
  *MAC++ = (A_D(*(MACStr+12))<<4) + A_D(*(MACStr+13));
  *MAC++ = (A_D(*(MACStr+15))<<4) + A_D(*(MACStr+16));
}

VOID GetEnvMacAddr(UINTN Index, UINT8* MACStr)
{
  EFI_STATUS  Status;
  UINTN       Size;
  CHAR16      Buf[20];
  CHAR16      MACEnv[30];

  if (Index > sizeof(ApmMacAddr)/sizeof(ApmMacAddr[0]))
    return;

  UnicodeSPrint(MACEnv, sizeof(MACEnv), L"%s%d", PREFIX_VARIABLE_NAME, Index);
  Size = sizeof(Buf);
  Status = gRT->GetVariable(MACEnv,
                            &gShellVariableGuid,
                            0,
                            &Size,
                            (VOID*)Buf);

  if (EFI_ERROR (Status))
    DEBUG((EFI_D_ERROR, "GetVariable %s ERROR\n", MACEnv));
  else
    AsciiStrToEthAddr (Buf, MACStr);
}

EFI_STATUS
MACAddrInit (VOID
 )
{
  UINTN Index;

  for (Index = 0; Index < sizeof(ApmMacAddr)/sizeof(ApmMacAddr[0]);
        Index++)
    GetEnvMacAddr(Index, &ApmMacAddr[Index][0]);
  return EFI_SUCCESS;
}

STATIC inline
UINTN
cpu_to_fdtn (UINTN x) {
  if (sizeof (UINTN) == sizeof (UINT32)) {
    return cpu_to_fdt32 (x);
  } else {
    return cpu_to_fdt64 (x);
  }
}

typedef struct {
  UINTN   Base;
  UINTN   Size;
} FdtRegion;

typedef struct __attribute__((packed)) {
  UINTN   Base;
  UINT32  Size;
} FdtRegion32;

STATIC
UINTN
IsPrintableString (
  IN CONST VOID* data,
  IN UINTN len
  )
{
  CONST CHAR8 *s = data;
  CONST CHAR8 *ss;

  // Zero length is not
  if (len == 0) {
    return 0;
  }

  // Must terminate with zero
  if (s[len - 1] != '\0') {
    return 0;
  }

  ss = s;
  while (*s/* && isprint(*s)*/) {
    s++;
  }

  // Not zero, or not done yet
  if (*s != '\0' || (s + 1 - ss) < len) {
    return 0;
  }

  return 1;
}

STATIC
VOID
PrintData (
  IN CONST CHAR8* data,
  IN UINTN len
  )
{
  UINTN i;
  CONST CHAR8 *p = data;

  // No data, don't print
  if (len == 0)
    return;

  if (IsPrintableString (data, len)) {
    Print(L" = \"%a\"", (const char *)data);
  } else if ((len % 4) == 0) {
    Print(L" = <");
    for (i = 0; i < len; i += 4) {
      Print(L"0x%08x%a", fdt32_to_cpu(GET_CELL(p)),i < (len - 4) ? " " : "");
    }
    Print(L">");
  } else {
    Print(L" = [");
    for (i = 0; i < len; i++)
      Print(L"%02x%a", *p++, i < len - 1 ? " " : "");
    Print(L"]");
  }
}

VOID
DebugDumpFdt (
  IN VOID*                FdtBlob
  )
{
  struct fdt_header *bph;
  UINT32 off_dt;
  UINT32 off_str;
  CONST CHAR8* p_struct;
  CONST CHAR8* p_strings;
  CONST CHAR8* p;
  CONST CHAR8* s;
  CONST CHAR8* t;
  UINT32 tag;
  UINTN sz;
  UINTN depth;
  UINTN shift;
  UINT32 version;

  {
    // Can 'memreserve' be printed by below code?
    INTN num = fdt_num_mem_rsv(FdtBlob);
    INTN i, err;
    UINT64 addr = 0,size = 0;

    for (i = 0; i < num; i++) {
      err = fdt_get_mem_rsv(FdtBlob, i, &addr, &size);
      if (err) {
        DEBUG((EFI_D_ERROR, "Error (%d) : Cannot get memreserve section (%d)\n", err, i));
      }
      else {
        Print(L"/memreserve/ \t0x%lx \t0x%lx;\n",addr,size);
      }
    }
  }

  depth = 0;
  shift = 4;

  bph = FdtBlob;
  off_dt = fdt32_to_cpu(bph->off_dt_struct);
  off_str = fdt32_to_cpu(bph->off_dt_strings);
  p_struct = (CONST CHAR8*)FdtBlob + off_dt;
  p_strings = (CONST CHAR8*)FdtBlob + off_str;
  version = fdt32_to_cpu(bph->version);

  p = p_struct;
  while ((tag = fdt32_to_cpu(GET_CELL(p))) != FDT_END) {
    if (tag == FDT_BEGIN_NODE) {
      s = p;
      p = PALIGN(p + AsciiStrLen (s) + 1, 4);

      if (*s == '\0')
              s = "/";

      Print(L"%*s%a {\n", depth * shift, L" ", s);

      depth++;
      continue;
    }

    if (tag == FDT_END_NODE) {
      depth--;

      Print(L"%*s};\n", depth * shift, L" ");
      continue;
    }

    if (tag == FDT_NOP) {
      Print(L"%*s// [NOP]\n", depth * shift, L" ");
      continue;
    }

    if (tag != FDT_PROP) {
      Print(L"%*s ** Unknown tag 0x%08x\n", depth * shift, L" ", tag);
      break;
    }
    sz = fdt32_to_cpu(GET_CELL(p));
    s = p_strings + fdt32_to_cpu(GET_CELL(p));
    if (version < 16 && sz >= 8)
            p = PALIGN(p, 8);
    t = p;

    p = PALIGN(p + sz, 4);

    Print(L"%*s%a", depth * shift, L" ", s);
    PrintData(t, sz);
    Print(L";\n");
  }
}

STATIC
BOOLEAN
IsLinuxReservedRegion (
  IN EFI_MEMORY_TYPE MemoryType
  )
{
  switch(MemoryType) {
  case EfiRuntimeServicesCode:
  case EfiRuntimeServicesData:
  case EfiUnusableMemory:
  case EfiACPIReclaimMemory:
  case EfiACPIMemoryNVS:
  case EfiReservedMemoryType:
    return TRUE;
  default:
    return FALSE;
  }
}

STATIC
BOOLEAN
IsPsciSmcSupported (
  VOID
  )
{
  BOOLEAN               PsciSmcSupported;
  UINTN                 Rx;

  PsciSmcSupported = FALSE;

  // Check the SMC response to the Presence SMC
  Rx = ARM_SMC_ID_PRESENCE;
  ArmCallSmc (&Rx);
  if (Rx == 1) {
    // Check the SMC UID
    Rx = ARM_SMC_ID_UID;
    ArmCallSmc (&Rx);
    if (Rx == ARM_TRUSTZONE_UID_4LETTERID) {
      Rx = ARM_SMC_ID_UID + 1;
      ArmCallSmc (&Rx);
      if (Rx == ARM_TRUSTZONE_ARM_UID) {
        PsciSmcSupported = TRUE;
      }
    }
  }

  return PsciSmcSupported;
}


/**
** Relocate the FDT blob to a more appropriate location for the Linux kernel.
** This function will allocate memory for the relocated FDT blob.
**
** @retval EFI_SUCCESS on success.
** @retval EFI_OUT_OF_RESOURCES or EFI_INVALID_PARAMETER on failure.
*/
STATIC
EFI_STATUS
RelocateFdt (
  EFI_PHYSICAL_ADDRESS   OriginalFdt,
  UINTN                  OriginalFdtSize,
  EFI_PHYSICAL_ADDRESS   *RelocatedFdt,
  UINTN                  *RelocatedFdtSize,
  EFI_PHYSICAL_ADDRESS   *RelocatedFdtAlloc
  )
{
  EFI_STATUS            Status;
  INTN                  Error;
  UINT64                FdtAlignment;

  *RelocatedFdtSize = OriginalFdtSize + FDT_ADDITIONAL_ENTRIES_SIZE;

  // If FDT load address needs to be aligned, allocate more space.
  FdtAlignment = PcdGet32 (PcdArmLinuxFdtAlignment);
  if (FdtAlignment != 0) {
    *RelocatedFdtSize += FdtAlignment;
  }

  // Try below a watermark address.
  Status = EFI_NOT_FOUND;
  if (PcdGet32 (PcdArmLinuxFdtMaxOffset) != 0) {
    *RelocatedFdt = LINUX_FDT_MAX_OFFSET;
    Status = gBS->AllocatePages (AllocateMaxAddress, EfiBootServicesData,
                    EFI_SIZE_TO_PAGES (*RelocatedFdtSize), RelocatedFdt);
    if (EFI_ERROR (Status)) {
      DEBUG ((EFI_D_WARN, "Warning: Failed to load FDT below address 0x%lX (%r). Will try again at a random address anywhere.\n", *RelocatedFdt, Status));
    }
  }

  // Try anywhere there is available space.
  if (EFI_ERROR (Status)) {
    Status = gBS->AllocatePages (AllocateAnyPages, EfiBootServicesData,
                    EFI_SIZE_TO_PAGES (*RelocatedFdtSize), RelocatedFdt);
    if (EFI_ERROR (Status)) {
      ASSERT_EFI_ERROR (Status);
      return EFI_OUT_OF_RESOURCES;
    } else {
      DEBUG ((EFI_D_WARN, "WARNING: Loaded FDT at random address 0x%lX.\nWARNING: There is a risk of accidental overwriting by other code/data.\n", *RelocatedFdt));
    }
  }

  DEBUG ((EFI_D_WARN, "\n", *RelocatedFdt));
  *RelocatedFdtAlloc = *RelocatedFdt;
  if (FdtAlignment != 0) {
    *RelocatedFdt = ALIGN (*RelocatedFdt, FdtAlignment);
  }

  // Load the Original FDT tree into the new region
  Error = fdt_open_into ((VOID*)(UINTN) OriginalFdt,
            (VOID*)(UINTN)(*RelocatedFdt), *RelocatedFdtSize);
  if (Error) {
    DEBUG ((EFI_D_ERROR, "fdt_open_into(): %a\n", fdt_strerror (Error)));
    gBS->FreePages (*RelocatedFdtAlloc, EFI_SIZE_TO_PAGES (*RelocatedFdtSize));
    return EFI_INVALID_PARAMETER;
  }

  DEBUG_CODE_BEGIN();
//    DebugDumpFdt ((VOID *) *RelocatedFdt);
  DEBUG_CODE_END();

  return EFI_SUCCESS;
}


EFI_STATUS
PrepareFdt (
  IN     CONST CHAR8*         CommandLineArguments,
  IN     EFI_PHYSICAL_ADDRESS InitrdImage,
  IN     UINTN                InitrdImageSize,
  IN OUT EFI_PHYSICAL_ADDRESS *FdtBlobBase,
  IN OUT UINTN                *FdtBlobSize
  )
{
  EFI_STATUS            Status;
  EFI_PHYSICAL_ADDRESS  NewFdtBlobBase;
  EFI_PHYSICAL_ADDRESS  NewFdtBlobAllocation;
  UINTN                 NewFdtBlobSize;
  VOID*                 fdt;
  INTN                  err;
  INTN                  node;
  INTN                  cpu_node;
  INT32                 lenp;
  CONST VOID*           BootArg;
  CONST VOID*           Method;
  EFI_PHYSICAL_ADDRESS  InitrdImageStart;
  EFI_PHYSICAL_ADDRESS  InitrdImageEnd;
  FdtRegion             Region;
  FdtRegion32           Region32;
  UINTN                 Index;
  CHAR8                 Name[10];
  LIST_ENTRY            ResourceList;
  BDS_SYSTEM_MEMORY_RESOURCE  *Resource;
  ARM_PROCESSOR_TABLE   *ArmProcessorTable;
  ARM_CORE_INFO         *ArmCoreInfoTable;
  UINT64                CpuReleaseAddr;
  UINTN                 MemoryMapSize;
  EFI_MEMORY_DESCRIPTOR *MemoryMap;
  EFI_MEMORY_DESCRIPTOR *MemoryMapPtr;
  UINTN                 MapKey;
  UINTN                 DescriptorSize;
  UINT32                DescriptorVersion;
  UINTN                 Pages;
  BOOLEAN               PsciSmcSupported;
  UINTN                 OriginalFdtSize;
  UINTN                 CoreMpId;
  UINTN                 Smc;

  NewFdtBlobAllocation = 0;

  //
  // Sanity checks on the original FDT blob.
  //
  err = fdt_check_header ((VOID*)(UINTN)(*FdtBlobBase));
  if (err != 0) {
    Print (L"ERROR: Device Tree header not valid (err:%d)\n", err);
    return EFI_INVALID_PARAMETER;
  }

  // The original FDT blob might have been loaded partially.
  // Check that it is not the case.
  OriginalFdtSize = (UINTN)fdt_totalsize ((VOID*)(UINTN)(*FdtBlobBase));
  if (OriginalFdtSize > *FdtBlobSize) {
    Print (L"ERROR: Incomplete FDT. Only %d/%d bytes have been loaded.\n",
           *FdtBlobSize, OriginalFdtSize);
    return EFI_INVALID_PARAMETER;
  }

  //
  // Relocate the FDT to its final location.
  //
  Status = RelocateFdt (*FdtBlobBase, OriginalFdtSize,
             &NewFdtBlobBase, &NewFdtBlobSize, &NewFdtBlobAllocation);
  if (EFI_ERROR (Status)) {
    goto FAIL_RELOCATE_FDT;
  }

  //
  // Ensure the Power State Coordination Interface (PSCI) SMCs are there if supported
  //
  PsciSmcSupported = FALSE;
  if (FeaturePcdGet (PcdArmPsciSupport) == TRUE) {
    PsciSmcSupported = IsPsciSmcSupported();
    if (PsciSmcSupported == FALSE) {
      DEBUG ((EFI_D_ERROR, "Warning: The Power State Coordination Interface (PSCI) is not supported by your platform Trusted Firmware.\n"));
    }
  }

  fdt = (VOID*)(UINTN)NewFdtBlobBase;

  node = fdt_subnode_offset (fdt, 0, "chosen");
  if (node < 0) {
    // The 'chosen' node does not exist, create it
    node = fdt_add_subnode(fdt, 0, "chosen");
    if (node < 0) {
      DEBUG((EFI_D_ERROR,"Error on finding 'chosen' node\n"));
      Status = EFI_INVALID_PARAMETER;
      goto FAIL_COMPLETE_FDT;
    }
  }

  DEBUG_CODE_BEGIN();
    BootArg = fdt_getprop(fdt, node, "bootargs", &lenp);
    if (BootArg != NULL) {
      DEBUG((EFI_D_ERROR,"BootArg: %a\n",BootArg));
    }
  DEBUG_CODE_END();

  //
  // Set Linux CmdLine
  //
  if ((CommandLineArguments != NULL) && (AsciiStrLen (CommandLineArguments) > 0)) {
    err = fdt_setprop(fdt, node, "bootargs", CommandLineArguments, AsciiStrSize(CommandLineArguments));
    if (err) {
      DEBUG((EFI_D_ERROR,"Fail to set new 'bootarg' (err:%d)\n",err));
    }
  }

  //
  // Set Linux Initrd
  //
  if (InitrdImageSize != 0) {
    InitrdImageStart = cpu_to_fdt64 (InitrdImage);
    err = fdt_setprop(fdt, node, "linux,initrd-start", &InitrdImageStart, sizeof(EFI_PHYSICAL_ADDRESS));
    if (err) {
      DEBUG((EFI_D_ERROR,"Fail to set new 'linux,initrd-start' (err:%d)\n",err));
    }
    InitrdImageEnd = cpu_to_fdt64 (InitrdImage + InitrdImageSize);
    err = fdt_setprop(fdt, node, "linux,initrd-end", &InitrdImageEnd, sizeof(EFI_PHYSICAL_ADDRESS));
    if (err) {
      DEBUG((EFI_D_ERROR,"Fail to set new 'linux,initrd-start' (err:%d)\n",err));
    }
  }

  //
  // Set Physical memory setup if does not exist
  //
  node = fdt_subnode_offset(fdt, 0, "memory");
  if (node < 0) {
    // The 'memory' node does not exist, create it
    node = fdt_add_subnode(fdt, 0, "memory");
  }
  if (node >= 0) {
    int FdtItemLen;
    const UINT32 *FdtItem;
    UINT64 FdtMemSize;


    fdt_setprop_string(fdt, node, "name", "memory");
    fdt_setprop_string(fdt, node, "device_type", "memory");

    GetSystemMemoryResources (&ResourceList);
    Resource = (BDS_SYSTEM_MEMORY_RESOURCE*)ResourceList.ForwardLink;
    FdtItem = (UINT32 *) fdt_getprop(fdt, node, "reg", &FdtItemLen);
    if (FdtItemLen == sizeof(UINT32)*3) {
      /* Entry size is 3 DWORD - 64-bit base address and 32-bit size.
         Update size if entry size is 0. */
      FdtMemSize = fdt32_to_cpu(FdtItem[2]);
      if (FdtMemSize == 0) {
        Region32.Base = cpu_to_fdt64((UINTN)Resource->PhysicalStart);
        Region32.Size = cpu_to_fdt32((UINTN)Resource->ResourceLength);
        err = fdt_setprop(fdt, node, "reg", &Region32, sizeof(Region32));

      }
    } else if (FdtItemLen == sizeof(UINT32)*4) {
      /* Entry size is 4 DWORD - 64-bit base address and 64-bit size.
         Update size if entry size is 0. */
      FdtMemSize = fdt64_to_cpu(*((UINT64 *) &FdtItem[2]));
      if (sizeof(UINTN) == sizeof(UINT32)) {
        Region.Base = cpu_to_fdt32((UINTN)Resource->PhysicalStart);
        Region.Size = cpu_to_fdt32((UINTN)Resource->ResourceLength);
      } else {
        Region.Base = cpu_to_fdt64((UINTN)Resource->PhysicalStart);
        Region.Size = cpu_to_fdt64((UINTN)Resource->ResourceLength);
      }

      if (FdtMemSize != 0) {
        err = fdt_setprop(fdt, node, "reg", &Region, sizeof(Region));
      }
    } else if (FdtItemLen == 0) {
      /* Newly added - just add it */
      if (sizeof(UINTN) == sizeof(UINT32)) {
        Region.Base = cpu_to_fdt32((UINTN)Resource->PhysicalStart);
        Region.Size = cpu_to_fdt32((UINTN)Resource->ResourceLength);
      } else {
        Region.Base = cpu_to_fdt64((UINTN)Resource->PhysicalStart);
        Region.Size = cpu_to_fdt64((UINTN)Resource->ResourceLength);
      }

      Region.Base = cpu_to_fdtn ((UINTN)Resource->PhysicalStart);
      Region.Size = cpu_to_fdtn ((UINTN)Resource->ResourceLength);

      err = fdt_setprop(fdt, node, "reg", &Region, sizeof(Region));
    }
    if (err) {
      DEBUG((EFI_D_ERROR,"Fail to set new 'memory region' (err:%d)\n",err));
    }
  }

  //
  // Add the memory regions reserved by the UEFI Firmware
  //

  // Retrieve the UEFI Memory Map
  MemoryMap = NULL;
  MemoryMapSize = 0;
  Status = gBS->GetMemoryMap (&MemoryMapSize, MemoryMap, &MapKey, &DescriptorSize, &DescriptorVersion);
  if (Status == EFI_BUFFER_TOO_SMALL) {
    // The UEFI specification advises to allocate more memory for the MemoryMap buffer between successive
    // calls to GetMemoryMap(), since allocation of the new buffer may potentially increase memory map size.
    Pages = EFI_SIZE_TO_PAGES (MemoryMapSize) + 1;
    MemoryMap = AllocatePages (Pages);
    if (MemoryMap == NULL) {
      Status = EFI_OUT_OF_RESOURCES;
      goto FAIL_COMPLETE_FDT;
    }
    Status = gBS->GetMemoryMap (&MemoryMapSize, MemoryMap, &MapKey, &DescriptorSize, &DescriptorVersion);
  }

  // Go through the list and add the reserved region to the Device Tree
  if (!EFI_ERROR(Status)) {
    MemoryMapPtr = MemoryMap;
    for (Index = 0; Index < (MemoryMapSize / DescriptorSize); Index++) {
      if (IsLinuxReservedRegion ((EFI_MEMORY_TYPE)MemoryMapPtr->Type)) {
        DEBUG((DEBUG_VERBOSE, "Reserved region of type %d [0x%lX, 0x%lX]\n",
            MemoryMapPtr->Type,
            (UINTN)MemoryMapPtr->PhysicalStart,
            (UINTN)(MemoryMapPtr->PhysicalStart + MemoryMapPtr->NumberOfPages * EFI_PAGE_SIZE)));
        err = fdt_add_mem_rsv(fdt, MemoryMapPtr->PhysicalStart, MemoryMapPtr->NumberOfPages * EFI_PAGE_SIZE);
        if (err != 0) {
          Print(L"Warning: Fail to add 'memreserve' (err:%d)\n", err);
        }
      }
      MemoryMapPtr = (EFI_MEMORY_DESCRIPTOR*)((UINTN)MemoryMapPtr + DescriptorSize);
    }
  }

  //
  // Setup Arm Mpcore Info if it is a multi-core or multi-cluster platforms.
  //
  // For 'cpus' and 'cpu' device tree nodes bindings, refer to this file
  // in the kernel documentation:
  // Documentation/devicetree/bindings/arm/cpus.txt
  //
  for (Index=0; Index < gST->NumberOfTableEntries; Index++) {
    // Check for correct GUID type
    if (CompareGuid (&gArmMpCoreInfoGuid, &(gST->ConfigurationTable[Index].VendorGuid))) {
      node = fdt_subnode_offset(fdt, 0, "cpus");
      if (node >= 0) {
        /* remove existing cpus in fdt */
        fdt_del_node(fdt, node);
      }

      // Create the /cpus node
      node = fdt_add_subnode(fdt, 0, "cpus");
      fdt_setprop_string(fdt, node, "name", "cpus");
      fdt_setprop_cell (fdt, node, "#address-cells", sizeof (UINTN) / 4);
      fdt_setprop_cell(fdt, node, "#size-cells", 0);

      // Get pointer to ARM processor table
      ArmProcessorTable = (ARM_PROCESSOR_TABLE *)gST->ConfigurationTable[Index].VendorTable;
      ArmCoreInfoTable = ArmProcessorTable->ArmCpus;

      for (Index = 0; Index < ArmProcessorTable->NumberOfEntries; Index++) {
        CoreMpId = (UINTN) GET_MPID (ArmCoreInfoTable[Index].ClusterId,
                             ArmCoreInfoTable[Index].CoreId);
        AsciiSPrint (Name, 10, "cpu@%03x", CoreMpId);

        cpu_node = fdt_add_subnode (fdt, node, Name);
        if (cpu_node < 0) {
          DEBUG ((EFI_D_ERROR, "Error on creating '%s' node\n", Name));
          Status = EFI_INVALID_PARAMETER;
          goto FAIL_COMPLETE_FDT;
        }

        fdt_setprop_string (fdt, cpu_node, "device_type", "cpu");

        CoreMpId = cpu_to_fdtn (CoreMpId);
        fdt_setprop (fdt, cpu_node, "reg", &CoreMpId, sizeof (CoreMpId));
        if (PsciSmcSupported) {
          fdt_setprop_string (fdt, cpu_node, "enable-method", "psci");
        }

        // If Power State Coordination Interface (PSCI) is not supported then it is expected the secondary
        // cores are spinning waiting for the Operating System to release them
        if ((PsciSmcSupported == FALSE) && (cpu_node >= 0)) {
          // We as the bootloader are responsible for either creating or updating
          // these entries. Do not trust the entries in the DT. We only know about
          // 'spin-table' type. Do not try to update other types if defined.
          Method = fdt_getprop(fdt, cpu_node, "enable-method", &lenp);
          if ( (Method == NULL) || (!AsciiStrCmp((CHAR8 *)Method, "spin-table")) ) {
            fdt_setprop_string(fdt, cpu_node, "enable-method", "spin-table");
            CpuReleaseAddr = cpu_to_fdt64(ArmCoreInfoTable[Index].MailboxSetAddress + CPU_OFFSET);
            fdt_setprop(fdt, cpu_node, "cpu-release-addr", &CpuReleaseAddr, sizeof(CpuReleaseAddr));
          } else {
            Print(L"Warning: Unsupported enable-method type for CPU[%d] : %a\n", Index, (CHAR8 *)Method);
          }
        }
      }
      break;
    }
  }

  // If the Power State Coordination Interface is supported then we signal it in the Device Tree
  if (PsciSmcSupported == TRUE) {
    // Before to create it we check if the node is not already defined in the Device Tree
    node = fdt_subnode_offset(fdt, 0, "psci");
    if (node < 0) {
      // The 'psci' node does not exist, create it
      node = fdt_add_subnode(fdt, 0, "psci");
      if (node < 0) {
        DEBUG((EFI_D_ERROR,"Error on creating 'psci' node\n"));
        Status = EFI_INVALID_PARAMETER;
        goto FAIL_COMPLETE_FDT;
      } else {
        fdt_setprop_string (fdt, node, "compatible", "arm,psci");
        fdt_setprop_string (fdt, node, "method", "smc");

        Smc = cpu_to_fdtn (ARM_SMC_ARM_CPU_SUSPEND);
        fdt_setprop (fdt, node, "cpu_suspend", &Smc, sizeof (Smc));

        Smc = cpu_to_fdtn (ARM_SMC_ARM_CPU_OFF);
        fdt_setprop (fdt, node, "cpu_off", &Smc, sizeof (Smc));

        Smc = cpu_to_fdtn (ARM_SMC_ARM_CPU_ON);
        fdt_setprop (fdt, node, "cpu_on", &Smc, sizeof (Smc));

        Smc = cpu_to_fdtn (ARM_SMC_ARM_MIGRATE);
        fdt_setprop (fdt, node, "migrate", &Smc, sizeof (Smc));
      }
    }
  }

  MACAddrInit();
  //
  // Enable mnet node in the DT
  //
  node = fdt_path_offset(fdt, "/soc/ethernet@17020000");
  if (node < 0)
    DEBUG((EFI_D_ERROR,"Can't find RMGII\n"));
  else {
    fdt_setprop(fdt, node, "status", "ok", sizeof("ok"));
    fdt_setprop(fdt, node, "local-mac-address", &ApmMacAddr[0],
        sizeof(ApmMacAddr[0]));
  }

  //
  // Enable sgmii node in the DT
  //
  node = fdt_path_offset(fdt, "/soc/ethernet@1f210000");
  if (node < 0)
    DEBUG((EFI_D_ERROR,"Can't find SGMII0\n"));
  else {
    fdt_setprop(fdt, node, "status", "ok", sizeof("ok"));
    fdt_setprop(fdt, node, "local-mac-address", &ApmMacAddr[1],
        sizeof(ApmMacAddr[0]));
  }
  node = fdt_path_offset(fdt, "/soc/ethernet@1f210030");
  if (node < 0)
    DEBUG((EFI_D_ERROR,"Can't find SGMII1\n"));
  else {
    fdt_setprop(fdt, node, "status", "ok", sizeof("ok"));
    fdt_setprop(fdt, node, "local-mac-address", &ApmMacAddr[2],
        sizeof(ApmMacAddr[0]));
  }
  //
  // Enable xfi node in the DT
  //
  node = fdt_path_offset(fdt, "/soc/ethernet@1f610000");
  if (node < 0)
    DEBUG((EFI_D_ERROR,"Can't find XFI0\n"));
  else {
    fdt_setprop(fdt, node, "status", "ok", sizeof("ok"));
    fdt_setprop(fdt, node, "local-mac-address", &ApmMacAddr[3],
        sizeof(ApmMacAddr[0]));
  }

  //
  // Remove sata2 clock ref
  //
  node = fdt_path_offset(fdt, "/soc/sata@1a400000");
  if (node < 0)
    DEBUG((EFI_D_ERROR,"Can't find sata2\n"));
  else {
    fdt_delprop(fdt, node, "clocks");
    fdt_delprop(fdt, node, "phys");
    fdt_delprop(fdt, node, "phy-names");
  }
    
  node = fdt_path_offset(fdt, "/soc/phy@1f22a000");
  if (node < 0)
    DEBUG((EFI_D_ERROR,"Can't find phy2\n"));
  else
    fdt_delprop(fdt, node, "clocks");

  node = fdt_path_offset(fdt, "/soc/clocks/sataphy1clk@1f22c000");
  if (node < 0)
    DEBUG((EFI_D_ERROR,"Can't find sataphy2clk\n"));
  else
    fdt_del_node(fdt, node);

  node = fdt_path_offset(fdt, "/soc/clocks/sata23clk@1f22c000");
  if (node < 0)
    DEBUG((EFI_D_ERROR,"Can't find sata23clk\n"));
  else
    fdt_del_node(fdt, node);

  //
  // Remove sata3 clock ref
  //
  node = fdt_path_offset(fdt, "/soc/sata@1a800000");
  if (node < 0)
    DEBUG((EFI_D_ERROR,"Can't find sata3\n"));
  else {
    fdt_delprop(fdt, node, "clocks");
    fdt_delprop(fdt, node, "phys");
    fdt_delprop(fdt, node, "phy-names");
  }

  node = fdt_path_offset(fdt, "/soc/phy@1f23a000");
  if (node < 0)
    DEBUG((EFI_D_ERROR,"Can't find phy3\n"));
  else
    fdt_delprop(fdt, node, "clocks");

  node = fdt_path_offset(fdt, "/soc/clocks/sataphy1clk@1f23c000");
  if (node < 0)
    DEBUG((EFI_D_ERROR,"Can't find sataphy3clk\n"));
  else
    fdt_del_node(fdt, node);

  node = fdt_path_offset(fdt, "/soc/clocks/sata45clk@1f23c000");
  if (node < 0)
    DEBUG((EFI_D_ERROR,"Can't find sata45clk\n"));
  else
    fdt_del_node(fdt, node);

  //
  // Set clock frequency of serial0
  //
  node = fdt_path_offset(fdt, "/soc/serial@1c020000");
  if (node < 0)
    DEBUG((EFI_D_ERROR,"Can't find serial0\n"));
  else {
    UINT32 Freq = cpu_to_fdt32(50000000); 
    fdt_setprop(fdt, node, "clock-frequency", &Freq, sizeof(Freq));
  }

  node = fdt_path_offset(fdt, "/soc/serial@1c021000");
  if (node < 0)
    DEBUG((EFI_D_ERROR,"Can't find serial1\n"));
  else {
    UINT32 Freq = cpu_to_fdt32(50000000); 
    fdt_setprop(fdt, node, "clock-frequency", &Freq, sizeof(Freq));
  }

  //
  // Set GIC register
  //
  node = fdt_path_offset(fdt, "/interrupt-controller@78010000");
  if (node < 0)
    DEBUG((EFI_D_ERROR,"Can't find GIC\n"));
  else {
    int FdtItemLen;
    UINT32 *FdtItem;
    UINT32 Item[16];

    FdtItem = (UINT32 *) fdt_getprop(fdt, node, "reg", &FdtItemLen);

    if (fdt32_to_cpu(FdtItem[1]) == 0x78010000 &&
                      FdtItemLen == sizeof(UINT32) * 16){
      CopyMem((VOID *)Item, (VOID *)FdtItem, FdtItemLen);

      Item[1] = cpu_to_fdt32(fdt32_to_cpu(Item[1]) + 0x80000);
      Item[5] = cpu_to_fdt32(fdt32_to_cpu(Item[5]) + 0x80000);
      Item[9] = cpu_to_fdt32(fdt32_to_cpu(Item[9]) + 0x80000);
      Item[13] = cpu_to_fdt32(fdt32_to_cpu(Item[13]) + 0x80000);

      fdt_setprop(fdt, node, "reg", &Item, FdtItemLen);
    }
  }

  //
  // Enable usb0 node in the DT
  //
  node = fdt_path_offset(fdt, "/soc/dwusb@19000000");
  if (node)
    fdt_setprop(fdt, node, "status", "ok", sizeof("ok"));
  else
    DEBUG((EFI_D_ERROR,"Can't find usb0\n"));

  //
  // Enable usb1 node in the DT
  //
  node = fdt_path_offset(fdt, "/soc/dwusb@19800000");
  if (node)
    fdt_setprop(fdt, node, "status", "ok", sizeof("ok"));
  else
    DEBUG((EFI_D_ERROR,"Can't find usb1\n"));

  DEBUG_CODE_BEGIN();
    //DebugDumpFdt (fdt);
  DEBUG_CODE_END();

  // If we succeeded to generate the new Device Tree then free the old Device Tree
  gBS->FreePages (*FdtBlobBase, EFI_SIZE_TO_PAGES (*FdtBlobSize));

  *FdtBlobBase = NewFdtBlobBase;
  *FdtBlobSize = (UINTN)fdt_totalsize ((VOID*)(UINTN)(NewFdtBlobBase));
  return EFI_SUCCESS;

FAIL_COMPLETE_FDT:
  gBS->FreePages (NewFdtBlobAllocation, EFI_SIZE_TO_PAGES (NewFdtBlobSize));

FAIL_RELOCATE_FDT:
  *FdtBlobSize = (UINTN)fdt_totalsize ((VOID*)(UINTN)(*FdtBlobBase));
  // Return success even if we failed to update the FDT blob.
  // The original one is still valid.
  return EFI_SUCCESS;
}
