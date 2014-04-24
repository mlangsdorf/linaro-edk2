/**
 * Copyright (c) 2013, AppliedMicro Corp. All rights reserved.
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


#define ALIGN_16MB(addr)      	ALIGN_POINTER(addr, (16*1024*1024))
#define ALIGN(x, a)     	(((x) + ((a) - 1)) & ~((a) - 1))
#define GET_CELL(p)     	(p += 4, *((const UINT32 *)(p-4)))

#define ALIGN(x, a)     (((x) + ((a) - 1)) & ~((a) - 1))
#define PALIGN(p, a)    ((void *)(ALIGN((unsigned long)(p), (a))))
#define GET_CELL(p)     (p += 4, *((const UINT32 *)(p-4)))

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


VOID DumpHex(UINT8 *ptr, INTN len)
{
  int i;

  for (i = 0; i < len; i++) {
    if ((i % 32) == 0) {
      DEBUG((DEBUG_VERBOSE, "\n0x%016LX:", (UINTN) ptr + i));
    }
    if ((i % 4) == 0)
      DEBUG((DEBUG_VERBOSE, " %02X", ptr[i]));
    else
      DEBUG((DEBUG_VERBOSE, "%02X", ptr[i]));
  }
}

VOID
DumpSystemTable(EFI_SYSTEM_TABLE *SysTbl)
{
  DEBUG((DEBUG_VERBOSE, "EFI System Table 0x%016LX\n", SysTbl));
  DEBUG((DEBUG_VERBOSE, " Signature: 0x%016LX\n", SysTbl->Hdr.Signature));
  DEBUG((DEBUG_VERBOSE, "  Revision: 0x%08X\n", SysTbl->Hdr.Revision));
  DEBUG((DEBUG_VERBOSE, "HeaderSize: 0x%08X\n", SysTbl->Hdr.HeaderSize));
  DEBUG((DEBUG_VERBOSE, "     CRC32: 0x%08X\n", SysTbl->Hdr.CRC32));
  DEBUG((DEBUG_VERBOSE, "  FirmwareVendor: 0x%016LX\n", SysTbl->FirmwareVendor));
  DEBUG((DEBUG_VERBOSE, "FirmwareRevision: 0x%08X\n", SysTbl->FirmwareRevision));
  DEBUG((DEBUG_VERBOSE, "     %04d Tables: 0x%016LX\n",
        SysTbl->NumberOfTableEntries, SysTbl->ConfigurationTable));
  /* DumpHex(SysTbl, sizeof(*SysTbl)); */
}

#if 1
VOID
PrintMemoryMap (
  VOID
  )
{
  EFI_STATUS            Status;
  UINTN                 MemoryMapSize;
  EFI_MEMORY_DESCRIPTOR *MemoryMap;
  EFI_MEMORY_DESCRIPTOR *MemoryMapPtr;
  UINTN                 MapKey;
  UINTN                 DescriptorSize;
  UINT32                DescriptorVersion;
  UINTN                 Pages;
  UINTN                 Index;


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
     DEBUG((DEBUG_VERBOSE, "Out of resource\n"));
     return;
   }
   Status = gBS->GetMemoryMap (&MemoryMapSize, MemoryMap, &MapKey, &DescriptorSize, &DescriptorVersion);
  }

  if (!EFI_ERROR(Status)) {
   MemoryMapPtr = MemoryMap;
   for (Index = 0; Index < (MemoryMapSize / DescriptorSize); Index++) {
     DEBUG((DEBUG_VERBOSE, "MemoryMap:  %d [0x%llX, 0x%llX]\n",
         MemoryMapPtr->Type,
         (UINTN)MemoryMapPtr->PhysicalStart,
         (UINTN)(MemoryMapPtr->PhysicalStart + MemoryMapPtr->NumberOfPages * EFI_PAGE_SIZE)));
     MemoryMapPtr = (EFI_MEMORY_DESCRIPTOR*)((UINTN)MemoryMapPtr + DescriptorSize);
   }
  }
}

#endif

EFI_STATUS
PrepareUEFI (
  IN     CONST CHAR8*         CommandLineString,
  IN     UINTN                KernelImageSize,
  IN     EFI_PHYSICAL_ADDRESS InitrdImage,
  IN     UINTN                InitrdImageSize,
  IN OUT EFI_PHYSICAL_ADDRESS *ParamBlobBase,
  IN OUT UINTN                *ParamBlobSize)
{
  EFI_STATUS                  Status;
  EFI_PHYSICAL_ADDRESS        KernelParamsAddress;
  EFI_PHYSICAL_ADDRESS        KernelImage;
  EFI_PHYSICAL_ADDRESS        InitrdImageStart;
  EFI_PHYSICAL_ADDRESS        InitrdImageEnd;
  LIST_ENTRY                  ResourceList;
  LIST_ENTRY                  ResourceIOList;
  BDS_SYSTEM_MEMORY_RESOURCE  *Resource;
  EFI_PHYSICAL_ADDRESS        MemDesc;
  EFI_MEMORY_DESCRIPTOR       *MemDescPtr;
  UINTN                       MemDescCnt = 0;
  UINT64                      MemLength = 0;
  EFI_PHYSICAL_ADDRESS        TmpVal = 0;
  UINTN                       Index;
  BOOLEAN                     CpusNodeExist;
  UINTN                       CoreMpId;
  UINT32                      MpId;
  UINT32                      ClusterId;
  UINT32                      CoreId;
  UINT64                      CpuReleaseAddr;
  CHAR8                       Name[10];
  CONST VOID*                 Method;
  ARM_PROCESSOR_TABLE         *ArmProcessorTable;
  ARM_CORE_INFO               *ArmCoreInfoTable;

  UINT32                      FdtAlignment;
  VOID                        *fdt = NULL;
  UINTN                       FdtSize;
  INTN                        node;
  INTN                        cpu_node;
  INT32                        lenp;
  INTN                        err;

  // If FDT load address needs to be aligned, allocate more space.
  FdtAlignment = PcdGet32 (PcdArmLinuxFdtAlignment);

  //64K is enough for fdt wrapper
  FdtSize = 64*1024;

  Status = gBS->AllocatePages (AllocateAnyPages, EfiBootServicesData,
                  EFI_SIZE_TO_PAGES (FdtSize + FdtAlignment), ParamBlobBase);
  if (EFI_ERROR (Status)) {
    DEBUG ((EFI_D_ERROR, "Failed to allocate Fdt address\n"));
    ASSERT_EFI_ERROR(Status);
    return Status;
  }

  fdt = (VOID *)*ParamBlobBase;

  if (FdtAlignment != 0) {
    fdt = (VOID *)ALIGN ((EFI_PHYSICAL_ADDRESS)fdt, (EFI_PHYSICAL_ADDRESS) FdtAlignment);
  }

  if (fdt_create_empty_tree(fdt, FdtSize)) {
    DEBUG ((EFI_D_ERROR, "Failed to create Fdt\n"));
    Status = EFI_NOT_FOUND;
    ASSERT_EFI_ERROR(Status);
    return Status;
  }

  node = fdt_add_subnode(fdt, 0, "chosen");
  if (node < 0) {
    DEBUG((EFI_D_ERROR,"Error on finding 'chosen' node\n"));
    Status = EFI_INVALID_PARAMETER;
    ASSERT_EFI_ERROR(Status);
    return Status;
  }

  //
  // Set Linux CmdLine
  //
  if ((CommandLineString != NULL) && (AsciiStrLen (CommandLineString) > 0)) {
    err = fdt_setprop(fdt, node, "bootargs", CommandLineString, AsciiStrSize(CommandLineString));
    if (err) {
      DEBUG((EFI_D_ERROR,"Fail to set new 'bootarg' (err:%d)\n",err));
      Status = EFI_INVALID_PARAMETER;
      ASSERT_EFI_ERROR(Status);
      return Status;
    }
  }

  //
  // Set Linux Initrd
  //
  if (InitrdImageSize != 0) {
    InitrdImageStart = cpu_to_fdtn (InitrdImage);
    err = fdt_setprop(fdt, node, "linux,initrd-start", &InitrdImageStart, sizeof(EFI_PHYSICAL_ADDRESS));
    if (err) {
      DEBUG((EFI_D_ERROR,"Fail to set new 'linux,initrd-start' (err:%d)\n",err));
      Status = EFI_INVALID_PARAMETER;
      ASSERT_EFI_ERROR(Status);
      return Status;

    }

    InitrdImageEnd = cpu_to_fdtn (InitrdImage + InitrdImageSize);
    err = fdt_setprop(fdt, node, "linux,initrd-end", &InitrdImageEnd, sizeof(EFI_PHYSICAL_ADDRESS));
    if (err) {
      DEBUG((EFI_D_ERROR,"Fail to set new 'linux,initrd-start' (err:%d)\n",err));
      Status = EFI_INVALID_PARAMETER;
      ASSERT_EFI_ERROR(Status);
      return Status;
    }
  }


  // Determine total memory resource
  GetSystemMemoryResources (&ResourceList);
  GetMemmoryMapIOResources(&ResourceIOList);
  Resource = (BDS_SYSTEM_MEMORY_RESOURCE *) ResourceList.ForwardLink;
  while (&Resource->Link != &ResourceList) {
   if (Resource->ResourceLength > 0)
     MemDescCnt++;
   if (MemLength == 0)
     MemLength = Resource->ResourceLength;
   Resource = (BDS_SYSTEM_MEMORY_RESOURCE *) Resource->Link.ForwardLink;
  }

  Resource = (BDS_SYSTEM_MEMORY_RESOURCE *) ResourceIOList.ForwardLink;
  while (&Resource->Link != &ResourceIOList) {
   if (Resource->ResourceLength > 0)
     MemDescCnt++;
   Resource = (BDS_SYSTEM_MEMORY_RESOURCE *) Resource->Link.ForwardLink;
  }

  DEBUG((DEBUG_VERBOSE, "Number of Mem descriptors:%d\n", MemDescCnt));

  // Try anywhere there is available space
  Status = gBS->AllocatePages (AllocateAnyPages, EfiBootServicesData,
   EFI_SIZE_TO_PAGES((MemDescCnt + 1) * sizeof(EFI_MEMORY_DESCRIPTOR)), &MemDesc);
  if (EFI_ERROR(Status)) {
   ASSERT_EFI_ERROR(Status);
   return Status;
  }

  // Set system memory descriptors:
  //  UEFI memory code space
  MemDescPtr = (EFI_MEMORY_DESCRIPTOR *)MemDesc;

  MemDescPtr->Type = EfiLoaderCode;
  MemDescPtr->PhysicalStart = PcdGet64(PcdSystemMemoryBase) + MemLength -
                          PcdGet32(PcdSystemMemoryUefiRegionSize);
  MemDescPtr->VirtualStart = 0;
  MemDescPtr->NumberOfPages = PcdGet32(PcdSystemMemoryUefiRegionSize) >>
                          EFI_PAGE_SHIFT;
  MemDescPtr->Attribute = EFI_MEMORY_RUNTIME | EFI_MEMORY_WB;
  DEBUG((DEBUG_VERBOSE, "EFI Memory 0x%16LX page %ld\n",
      MemDescPtr->PhysicalStart, MemDescPtr->NumberOfPages));

//  err = fdt_add_mem_rsv(fdt, MemDescPtr->PhysicalStart,
//                             MemDescPtr->NumberOfPages * EFI_PAGE_SIZE);
//  if (err != 0) {
//    Print(L"Warning: Fail to add 'memreserve' (err:%d)\n", err);
//  }

  MemDescPtr++;

  //  System memory
  GetSystemMemoryResources (&ResourceList);
  Resource = (BDS_SYSTEM_MEMORY_RESOURCE *) ResourceList.ForwardLink;
  for ( ; &Resource->Link != &ResourceList; ) {
   BDS_SYSTEM_MEMORY_RESOURCE *Prev;
   if (Resource->ResourceLength > 0) {
     MemDescPtr->Type = EfiConventionalMemory;
     MemDescPtr->PhysicalStart = Resource->PhysicalStart;
     MemDescPtr->VirtualStart = 0;
     MemDescPtr->NumberOfPages = Resource->ResourceLength >> EFI_PAGE_SHIFT;
     MemDescPtr->Attribute = EFI_MEMORY_WB;
     DEBUG((DEBUG_VERBOSE, "System Memory 0x%16LX page %ld\n",
         MemDescPtr->PhysicalStart, MemDescPtr->NumberOfPages));
     MemDescPtr++;
   }
   /* Free this entry */
   Prev = Resource;
   Resource = (BDS_SYSTEM_MEMORY_RESOURCE *) Resource->Link.ForwardLink;
   FreePool(Prev);
  }

  // Memory Map IO
  GetMemmoryMapIOResources(&ResourceIOList);
  Resource = (BDS_SYSTEM_MEMORY_RESOURCE *) ResourceIOList.ForwardLink;
  for ( ; &Resource->Link != &ResourceIOList; ) {
   BDS_SYSTEM_MEMORY_RESOURCE *Prev;
   if (Resource->ResourceLength > 0) {
     /* force Linux to map */
     MemDescPtr->Type = EfiMemoryMappedIO;
     MemDescPtr->PhysicalStart = Resource->PhysicalStart;
     MemDescPtr->VirtualStart = 0;
     MemDescPtr->NumberOfPages = Resource->ResourceLength >> EFI_PAGE_SHIFT;
     MemDescPtr->Attribute = EFI_MEMORY_UC | EFI_MEMORY_RUNTIME;
     DEBUG((DEBUG_VERBOSE, "System Memory Map IO 0x%16LX page %ld\n",
         MemDescPtr->PhysicalStart, MemDescPtr->NumberOfPages));
     MemDescPtr++;
   }
   /* Free this entry */
   Prev = Resource;
   Resource = (BDS_SYSTEM_MEMORY_RESOURCE *) Resource->Link.ForwardLink;
   FreePool(Prev);
  }

  TmpVal = cpu_to_fdtn((EFI_PHYSICAL_ADDRESS) gST);
  err = fdt_setprop(fdt, node, "linux,efi-system-table", &TmpVal, sizeof(EFI_PHYSICAL_ADDRESS));
  if (err) {
    DEBUG((EFI_D_ERROR,"Fail to set new 'linux,efi-system-table' (err:%d)\n",err));
    Status = EFI_INVALID_PARAMETER;
    ASSERT_EFI_ERROR(Status);
    return Status;

  }

  TmpVal = cpu_to_fdtn(MemDesc);
  err = fdt_setprop(fdt, node, "linux,efi-mmap-addr", &TmpVal, sizeof(EFI_PHYSICAL_ADDRESS));
  if (err) {
    DEBUG((EFI_D_ERROR,"Fail to set new 'linux,efi-mmap-addr' (err:%d)\n",err));
    Status = EFI_INVALID_PARAMETER;
    ASSERT_EFI_ERROR(Status);
    return Status;

  }

  TmpVal = cpu_to_fdtn(sizeof (EFI_MEMORY_DESCRIPTOR) * (MemDescCnt + 1));
  err = fdt_setprop(fdt, node, "linux,efi-mmap-size", &TmpVal, sizeof(EFI_PHYSICAL_ADDRESS));
  if (err) {
    DEBUG((EFI_D_ERROR,"Fail to set new 'linux,efi-mmap-size' (err:%d)\n",err));
    Status = EFI_INVALID_PARAMETER;
    ASSERT_EFI_ERROR(Status);
    return Status;

  }

  TmpVal = cpu_to_fdtn(sizeof (EFI_MEMORY_DESCRIPTOR));
  err = fdt_setprop(fdt, node, "linux,efi-mmap-desc-size", &TmpVal, sizeof(EFI_PHYSICAL_ADDRESS));
  if (err) {
    DEBUG((EFI_D_ERROR,"Fail to set new 'linux,efi-mmap-desc-size' (err:%d)\n",err));
    Status = EFI_INVALID_PARAMETER;
    ASSERT_EFI_ERROR(Status);
    return Status;

  }
  TmpVal = cpu_to_fdtn(EFI_MEMORY_DESCRIPTOR_VERSION);
  err = fdt_setprop(fdt, node, "linux,efi-mmap-desc-ver", &TmpVal, sizeof(EFI_PHYSICAL_ADDRESS));
  if (err) {
    DEBUG((EFI_D_ERROR,"Fail to set new 'linux,efi-mmap-desc-ver' (err:%d)\n",err));
    Status = EFI_INVALID_PARAMETER;
    ASSERT_EFI_ERROR(Status);
    return Status;
  }

  if (sizeof(UINTN) == 4)
  	TmpVal = cpu_to_fdtn(32);
  else
  	TmpVal = cpu_to_fdtn(64);
  
  err = fdt_setprop(fdt, node, "linux,efi-bits", &TmpVal, sizeof(EFI_PHYSICAL_ADDRESS));
  if (err) {
    DEBUG((EFI_D_ERROR,"Fail to set new 'linux,efi-bits' (err:%d)\n",err));
    Status = EFI_INVALID_PARAMETER;
    ASSERT_EFI_ERROR(Status);
    return Status;
  }

//  DumpSystemTable(gST);

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
      MpId = ArmReadMpidr ();
      ClusterId = GET_CLUSTER_ID(MpId);
      CoreId    = GET_CORE_ID(MpId);

      node = fdt_subnode_offset(fdt, 0, "cpus");
      if (node < 0) {
        // Create the /cpus node
        node = fdt_add_subnode(fdt, 0, "cpus");
        fdt_setprop_string(fdt, node, "name", "cpus");
        fdt_setprop_cell (fdt, node, "#address-cells", sizeof (UINTN) / 4);
        fdt_setprop_cell(fdt, node, "#size-cells", 0);
        CpusNodeExist = FALSE;
      } else {
        CpusNodeExist = TRUE;
      }

      // Get pointer to ARM processor table
      ArmProcessorTable = (ARM_PROCESSOR_TABLE *)gST->ConfigurationTable[Index].VendorTable;
      ArmCoreInfoTable = ArmProcessorTable->ArmCpus;

      for (Index = 0; Index < ArmProcessorTable->NumberOfEntries; Index++) {
        CoreMpId = (UINTN) GET_MPID (ArmCoreInfoTable[Index].ClusterId,
                             ArmCoreInfoTable[Index].CoreId);
        AsciiSPrint (Name, 10, "cpu@%x", CoreMpId);

        // If the 'cpus' node did not exist then create all the 'cpu' nodes.
        // In case 'cpus' node is provided in the original FDT then we do not add
        // any 'cpu' node.
        if (!CpusNodeExist) {
          cpu_node = fdt_add_subnode (fdt, node, Name);
          if (cpu_node < 0) {
            DEBUG ((EFI_D_ERROR, "Error on creating '%s' node\n", Name));
            Status = EFI_INVALID_PARAMETER;
            ASSERT_EFI_ERROR(Status);
            return Status;
          }

          fdt_setprop_string (fdt, cpu_node, "device_type", "cpu");

          CoreMpId = cpu_to_fdtn (CoreMpId);
          fdt_setprop (fdt, cpu_node, "reg", &CoreMpId, sizeof (CoreMpId));
        } else {
          cpu_node = fdt_subnode_offset(fdt, node, Name);
        }

        // Expected the secondary
        // cores are spinning waiting for the Operating System to release them
        if (cpu_node >= 0) {
          // We as the bootloader are responsible for either creating or updating
          // these entries. Do not trust the entries in the DT. We only know about
          // 'spin-table' type. Do not try to update other types if defined.
          Method = fdt_getprop(fdt, cpu_node, "enable-method", &lenp);
          if ( (Method == NULL) || (!AsciiStrCmp((CHAR8 *)Method, "spin-table")) ) {
            fdt_setprop_string(fdt, cpu_node, "enable-method", "spin-table");
            CpuReleaseAddr = cpu_to_fdtn(ArmCoreInfoTable[Index].MailboxSetAddress);
            fdt_setprop(fdt, cpu_node, "cpu-release-addr", &CpuReleaseAddr, sizeof(CpuReleaseAddr));

            // If it is not the primary core than the cpu should be disabled
            if (((ArmCoreInfoTable[Index].ClusterId != ClusterId) || (ArmCoreInfoTable[Index].CoreId != CoreId))) {
              fdt_setprop_string(fdt, cpu_node, "status", "disabled");
            }
          } else {
            Print(L"Warning: Unsupported enable-method type for CPU[%d] : %a\n", Index, (CHAR8 *)Method);
          }
        }
      }
      break;
    }
  }

  // Check if load address is above LINUX_ATAG_MAX_OFFSET
  if ((EFI_PHYSICAL_ADDRESS)fdt > LINUX_ATAG_MAX_OFFSET) {
    // Relocate it to avoid StartLinux function from a relocation
    //   and not update the physical address of the command line
    KernelImage = PcdGet64(PcdSystemMemoryBase) + 0x80000;
    DEBUG((DEBUG_VERBOSE, "Relocate kernel parameter from 0x%16LX to 0x%16LX\n",
        (EFI_PHYSICAL_ADDRESS)fdt, ALIGN_16MB(KernelImage + KernelImageSize)));
    KernelParamsAddress = (EFI_PHYSICAL_ADDRESS) CopyMem(
                            ALIGN_16MB(KernelImage + KernelImageSize),
                            fdt, FdtSize);
    gBS->FreePages((EFI_PHYSICAL_ADDRESS)fdt, EFI_SIZE_TO_PAGES(FdtSize));
  } else {
    KernelParamsAddress = (EFI_PHYSICAL_ADDRESS)fdt;
  }


  DEBUG_CODE_BEGIN();
  DebugDumpFdt ((VOID *)KernelParamsAddress);
  PrintMemoryMap();
  DEBUG_CODE_END();

  *ParamBlobBase = KernelParamsAddress;
  *ParamBlobSize = fdt_totalsize ((VOID *)KernelParamsAddress);


  return EFI_SUCCESS;
}
