/** @file  NorFlashDxe.c

  Copyright (c) 2011 - 2014, ARM Ltd. All rights reserved.<BR>

  This program and the accompanying materials
  are licensed and made available under the terms and conditions of the BSD License
  which accompanies this distribution.  The full text of the license may be found at
  http://opensource.org/licenses/bsd-license.php

  THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
  WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.

**/

#include <Library/UefiLib.h>
#include <Library/BaseMemoryLib.h>
#include <Library/MemoryAllocationLib.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Library/PcdLib.h>
#include <Library/DxeServicesTableLib.h>
#include <Library/UefiRuntimeLib.h>
#include <Guid/GlobalVariable.h>
#include <Guid/EventGroup.h>

#include "NorFlashDxe.h"
#include <ArmPlatform.h>
#include <Library/TimerLib.h>

STATIC EFI_EVENT  mNorFlashVirtualAddrChangeEvent = NULL;

//
// Global variable declarations
//
NOR_FLASH_INSTANCE **mNorFlashInstances;
UINTN                *mNorFlashDeviceCount;
/* This buffer used for runtime */
VOID                 *TmpRuntimeBuffer;

NOR_FLASH_INSTANCE  mNorFlashInstanceTemplate = {
  NOR_FLASH_SIGNATURE, // Signature
  NULL, // Handle ... NEED TO BE FILLED

  FALSE, // Initialized
  NULL, // Initialize

  0, // DeviceBaseAddress ... NEED TO BE FILLED
  0, // RegionBaseAddress ... NEED TO BE FILLED
  0, // Size ... NEED TO BE FILLED
  0, // StartLba

  {
    EFI_BLOCK_IO_PROTOCOL_REVISION2, // Revision
    NULL, // Media ... NEED TO BE FILLED
    NorFlashBlockIoReset, // Reset;
    NorFlashBlockIoReadBlocks,          // ReadBlocks
    NorFlashBlockIoWriteBlocks,         // WriteBlocks
    NorFlashBlockIoFlushBlocks          // FlushBlocks
  }, // BlockIoProtocol

  {
    0, // MediaId ... NEED TO BE FILLED
    FALSE, // RemovableMedia
    TRUE, // MediaPresent
    FALSE, // LogicalPartition
    FALSE, // ReadOnly
    FALSE, // WriteCaching;
    0, // BlockSize ... NEED TO BE FILLED
    4, //  IoAlign
    0, // LastBlock ... NEED TO BE FILLED
    0, // LowestAlignedLba
    1, // LogicalBlocksPerPhysicalBlock
  }, //Media;

  FALSE, // SupportFvb ... NEED TO BE FILLED
  {
    FvbGetAttributes, // GetAttributes
    FvbSetAttributes, // SetAttributes
    FvbGetPhysicalAddress,  // GetPhysicalAddress
    FvbGetBlockSize,  // GetBlockSize
    FvbRead,  // Read
    FvbWrite, // Write
    FvbEraseBlocks, // EraseBlocks
    NULL, //ParentHandle
    FvbGetMappedAddress,
  }, //  FvbProtoccol;

  {
    {
      {
        HARDWARE_DEVICE_PATH,
        HW_VENDOR_DP,
        {
          (UINT8)( sizeof(VENDOR_DEVICE_PATH)      ),
          (UINT8)((sizeof(VENDOR_DEVICE_PATH)) >> 8),
  }
      },
      { 0x0, 0x0, 0x0, { 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0 }}, // GUID ... NEED TO BE FILLED
    },
    {
      END_DEVICE_PATH_TYPE,
      END_ENTIRE_DEVICE_PATH_SUBTYPE,
      {
        sizeof (EFI_DEVICE_PATH_PROTOCOL),
        0
      }
    }
  } // DevicePath
};

#ifdef APM_XGENE_GFC_FLASH

EFI_PHYSICAL_ADDRESS XgeneNor0Base = APM_XGENE_NOR0_BASE;

struct NorCmdSequence NorCmdSet2CmdSequence[] = {

/* READ Commands  */
  /* CMDSET2_CMD_READ_DEVICE_ID */ {
  {0x555, 0x2AA, 0x555, 0x001, 0x00E, 0x00F},
  {0xAA, 0x55, 0x90, 0x227E, 0xFF, 0xFF}
  },
  /* CMDSET2_CMD_READ_STATUS_REGISTER */ {
  {0xFFF, 0xFFF, 0xFFF, 0xFFF, 0xFFF, 0xFFF},
  {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF}
  },
  /* CMDSET2_CMD_CLEAR_STATUS_REGISTER */ {
  {0xFFF, 0xFFF, 0xFFF, 0xFFF, 0xFFF, 0xFFF},
  {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF}
  },
  /* CMDSET2_CMD_READ_ARRAY */ {
  {0x555, 0xFFF, 0xFFF, 0xFFF, 0xFFF, 0xFFF},
  {0xF0, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF}
  },
  /* CMDSET2_CMD_READ_CFI_QUERY */ {
  {0x555, 0xFFF, 0xFFF, 0xFFF, 0xFFF, 0xFFF},
  {0x98, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF}
  },

/* WRITE Commands */
  /* CMDSET2_CMD_WORD_PROGRAM_SETUP */ {
  {0x555, 0x2AA, 0x555, 0xFFF, 0xFFF, 0xFFF},
  {0xAA, 0x55, 0xA0, 0xFF, 0xFF, 0xFF}
  },
  /* CMDSET2_CMD_ALTERNATE_WORD_PROGRAM_SETUP */ {
  {0x555, 0x2AA, 0xFFF, 0xFFF, 0xFFF, 0xFFF},
  {0xAA, 0x55, 0xFF, 0xFF, 0xFF, 0xFF}
  },
  /* CMDSET2_CMD_BUFFERED_PROGRAM_SETUP */ {
  {0x555, 0x2AA, 0xEEE, 0xFFF, 0xFFF, 0xFFF},
  {0xAA, 0x55, 0x25, 0xFF, 0xFF, 0xFF}
  },
  /* CMDSET2_CMD_BUFFERED_PROGRAM_CONFIRM */ {
  {0xEEE, 0xFFF, 0xFFF, 0xFFF, 0xFFF, 0xFFF},
  {0x29, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF}
  },
  /* CMDSET2_CMD_BEFP_SETUP */ {
  {0xFFF, 0xFFF, 0xFFF, 0xFFF, 0xFFF, 0xFFF},
  {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF}
  },
  /* CMDSET2_CMD_BEFP_CONFIRM */ {
  {0xFFF, 0xFFF, 0xFFF, 0xFFF, 0xFFF, 0xFFF},
  {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF}
  },

/* ERASE Commands */
  /* CMDSET2_CMD_BLOCK_ERASE_SETUP */ {
  {0x555, 0x2AA, 0x555, 0xFFF, 0xFFF, 0xFFF},
  {0xAA, 0x55, 0x80, 0xFF, 0xFF, 0xFF}
  },
  /* CMDSET2_CMD_BLOCK_ERASE_CONFIRM */ {
  {0x555, 0x2AA, 0xEEE, 0xFFF, 0xFFF, 0xFFF},
  {0xAA, 0x55, 0x30, 0xFF, 0xFF, 0xFF}
  },

/* SUSPEND Commands */
  /* CMDSET2_CMD_PROGRAM_OR_ERASE_SUSPEND */ {
  {0xEEE, 0xFFF, 0xFFF, 0xFFF, 0xFFF, 0xFFF},
  {0xB0, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF}
  },
  /* CMDSET2_CMD_SUSPEND_RESUME */ {
  {0xEEE, 0xFFF, 0xFFF, 0xFFF, 0xFFF, 0xFFF},
  {0x30, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF}
  },

/* BLOCK LOCKING / UNLOCKING Commands */
  /* CMDSET2_CMD_LOCK_BLOCK_SETUP */ {
  {0xFFF, 0xFFF, 0xFFF, 0xFFF, 0xFFF, 0xFFF},
  {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF}
  },
  /* CMDSET2_CMD_LOCK_BLOCK */ {
  {0xFFF, 0xFFF, 0xFFF, 0xFFF, 0xFFF, 0xFFF},
  {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF}
  },
  /* CMDSET2_CMD_UNLOCK_BLOCK */ {
  {0xFFF, 0xFFF, 0xFFF, 0xFFF, 0xFFF, 0xFFF},
  {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF}
  },
  /* CMDSET2_CMD_LOCK_DOWN_BLOCK */ {
  {0xFFF, 0xFFF, 0xFFF, 0xFFF, 0xFFF, 0xFFF},
  {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF}
  },

/* PROTECTION Commands */
  /* CMDSET2_CMD_PROGRAM_PROTECTION_REGISTER_SETUP */ {
  {0xFFF, 0xFFF, 0xFFF, 0xFFF, 0xFFF, 0xFFF},
  {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF}
  },

/* CONFIGURATION Commands  */
  /* CMDSET2_CMD_READ_CONFIGURATION_REGISTER_SETUP */ {
  {0xFFF, 0xFFF, 0xFFF, 0xFFF, 0xFFF, 0xFFF},
  {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF}
  },
  /* CMDSET2_CMD_READ_CONFIGURATION_REGISTER */ {
  {0xFFF, 0xFFF, 0xFFF, 0xFFF, 0xFFF, 0xFFF},
  {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF}
  },

};

VOID NorCmdSet2SendNorCmd(UINTN BaseAddr, UINT32 Offset, enum NorFlashCmd Cmd)
{
  INT32 i = 0;
  UINTN Addr = 0;

  for (i = 0 ; i < MaxNorCmdSet2Cycles ; i++) {
    if (NorCmdSet2CmdSequence[Cmd].NorBusCycleAddr[i] == 0xFFF)
      break;
    if (NorCmdSet2CmdSequence[Cmd].NorBusCycleAddr[i] == 0xEEE) {
      Addr = CREATE_NOR_ADDRESS(BaseAddr, Offset);
    }
    else {
      Addr = CREATE_NOR_ADDRESS(XgeneNor0Base, NorCmdSet2CmdSequence[Cmd].NorBusCycleAddr[i]);
    }
    //DEBUG((EFI_D_WARN, "Addr=%p Data=%x\n", Addr, NorCmdSet2CmdSequence[Cmd].NorBusCycleData[i]));
    *((volatile UINT16*)Addr) = NorCmdSet2CmdSequence[Cmd].NorBusCycleData[i];
    asm volatile("dsb sy":::);
    asm volatile("isb":::);
  }
}

UINTN NorSectorAddr( IN UINTN Offset)
{
  UINTN NorSectAddr = 0ULL;
  UINTN B1 = 4ULL * SIZE_32KB;
  UINTN B2 = B1 + 254ULL * SIZE_128KB;
  if (Offset < B1) {
    NorSectAddr = (Offset - Offset % SIZE_32KB);
  } else if (Offset < B2) {
    NorSectAddr = (Offset - Offset % SIZE_128KB);
  }  else {
    NorSectAddr = (Offset - Offset % SIZE_32KB);
  }
  return NorSectAddr;
}

UINTN NorNextSectorAddr( IN UINTN Offset)
{
  UINTN NorNextSectAddr = 0ULL;
  UINTN B1 = 4ULL * SIZE_32KB;
  UINTN B2 = B1 + 254ULL * SIZE_128KB;
  UINTN B3 = B2 + B1;
  if (Offset < B1) {
    NorNextSectAddr = Offset + SIZE_32KB - Offset % SIZE_32KB;
  } else if (Offset < B2) {
    NorNextSectAddr = Offset + SIZE_128KB - Offset % SIZE_128KB;
    NorNextSectAddr = ((NorNextSectAddr >= B3) ? (B2 + SIZE_32KB) : NorNextSectAddr);
  } else {
    NorNextSectAddr = Offset + SIZE_32KB - Offset % SIZE_32KB;
  }
  return NorNextSectAddr;
}

BOOLEAN
NorFlashChipIsReady (
  IN NOR_FLASH_INSTANCE     *Instance,
  IN UINTN                  Address
  )
{
  UINT16 Word1, Word2;
  volatile UINT16 *PtrWord = (UINT16 *)Address;

  Word1 = *PtrWord;
  Word2 = *PtrWord;

  return (Word1 == Word2);
}

EFI_STATUS
NorFlashEraseSingleSector (
  IN NOR_FLASH_INSTANCE     *Instance,
  IN UINTN                  Address
  )
{
  DEBUG((DEBUG_BLKIO,"NorFlashEraseSingleSector(Sector=0x%08x\n", Address));

  // Request a block erase and then confirm it
  SEND_NOR_COMMAND(Instance->DeviceBaseAddress + NorSectorAddr(Address), 0, CMDSET2_CMD_BLOCK_ERASE_SETUP);
  SEND_NOR_COMMAND(Instance->DeviceBaseAddress + NorSectorAddr(Address), 0, CMDSET2_CMD_BLOCK_ERASE_CONFIRM);
  /* Sector Erase time : 2 s for 16Kword and 3.5 s for 64Kword  */
  /* page 72, S29WS-N_00_I2 Nov 10, 2006 */
#if !defined(APM_XGENE_NO_NORDELAY)
  MicroSecondDelay(100);
  for (;;) {
    if (NorFlashChipIsReady(Instance, Address))
      break;

    MicroSecondDelay(1000000);
  }
#endif
  // Put device back into Read Array mode
  SEND_NOR_COMMAND (Instance->DeviceBaseAddress + NorSectorAddr(Address), 0, CMDSET2_CMD_READ_ARRAY);

  return EFI_SUCCESS;
}

EFI_STATUS
NorFlashEraseSectors (
  IN NOR_FLASH_INSTANCE     *Instance,
  IN UINTN                  Address,
  IN UINTN                  Size
  )
{
  UINTN Sector;
  UINTN Start =  NorSectorAddr(Address);
  UINTN  End = NorNextSectorAddr(Address + Size - 1);

  for (Sector = Start ; Sector < End ; Sector = NorNextSectorAddr(Sector)) {
    NorFlashEraseSingleSector(Instance, Sector);
  }

  return EFI_SUCCESS;
}

EFI_STATUS
NorFlashEraseSingleBlock (
  IN NOR_FLASH_INSTANCE     *Instance,
  IN UINTN                  BlockAddress
  )
{
  // Do nothing here
  // Erase is taken taken care by the write function
  // Keep UEFI happy
  return EFI_SUCCESS;
}

EFI_STATUS
NorFlashWriteBuffer (
  IN NOR_FLASH_INSTANCE     *Instance,
  IN UINTN                  TargetAddress,
  IN UINTN                  BufferSizeInBytes,
  IN UINT32                 *Buffer
  )
{
  UINTN                 BufferSizeInWords;
  UINTN                 Count;
  UINTN                 Addr;
  volatile UINT16       *BufferPtr = (UINT16 *)Buffer;


  //DEBUG((EFI_D_BLKIO,"NorFlashWriteBuffer(TargetAddress:0x%X BufferSizeInBytes:0x%X)\n",TargetAddress, BufferSizeInBytes));

  // Prepare the data destination address
  Addr = TargetAddress;

  SEND_NOR_COMMAND(Instance->DeviceBaseAddress + NorSectorAddr(TargetAddress - Instance->DeviceBaseAddress), 0, CMDSET2_CMD_BUFFERED_PROGRAM_SETUP);

  // From now on we work in 16-bit words
  BufferSizeInWords = BufferSizeInBytes / sizeof(UINT16);

  // Write the word count, which is (buffer_size_in_words - 1),
  // because word count 0 means one word.
  SEND_TO_NOR(Instance->DeviceBaseAddress + NorSectorAddr(TargetAddress - Instance->DeviceBaseAddress), 0, BufferSizeInWords-1);

  // Write the data to the NOR Flash, advancing each address by 4 bytes
  for(Count=0; Count < BufferSizeInWords; Count++, Addr += sizeof(UINT16), BufferPtr++) {
    SEND_TO_NOR(Addr, 0, *BufferPtr);
  }

  // Issue the Buffered Program Confirm command, to start the programming operation
  SEND_NOR_COMMAND (Instance->DeviceBaseAddress + NorSectorAddr(TargetAddress - Instance->DeviceBaseAddress), 0, CMDSET2_CMD_BUFFERED_PROGRAM_CONFIRM);

#if !defined(APM_XGENE_NO_NORDELAY)
  MicroSecondDelay(100);
  for (;;) {
    if (NorFlashChipIsReady(Instance, Addr))
      break;

    MicroSecondDelay(1000);
  }
#endif

  // Put device back into Read Array mode
  SEND_NOR_COMMAND (Instance->DeviceBaseAddress, 0, CMDSET2_CMD_READ_ARRAY);

  return EFI_SUCCESS;
}

EFI_STATUS
NorFlashWriteMultipleBuffers (
  IN NOR_FLASH_INSTANCE     *Instance,
  IN UINTN                  Addr,
  IN UINTN                  BufferSizeInBytes,
  IN UINT8                  *Buffer
  )
{
  UINT8           *pWriteBuffer;
  EFI_STATUS      Status = EFI_SUCCESS;
  UINT32          NumBytesWritten;
  EFI_LBA         DstPtr;
  EFI_LBA         Next32KBoundary;
  UINTN           Incr;

  // The buffer must be valid
  if (Buffer == NULL) {
    return EFI_INVALID_PARAMETER;
  }

  if(Instance->Media.ReadOnly == TRUE) {
    return EFI_WRITE_PROTECTED;
  }

  // If no bytes, return success
  if(BufferSizeInBytes == 0) {
    return EFI_SUCCESS;
  }

  // Ensure alignment
  if ((Addr % 2) != 0) {
    return EFI_INVALID_PARAMETER;
  }

  // Write in chunks of CMDSET2_MAX_BUFFER_SIZE_IN_BYTES,
  // breaking at 32K boundaries
  pWriteBuffer = (UINT8 *)Buffer;
  for (DstPtr = Addr, NumBytesWritten = 0; NumBytesWritten < BufferSizeInBytes; ) {
    Next32KBoundary = ((DstPtr / SIZE_32KB) + 1) * SIZE_32KB;
    Incr = ((DstPtr + CMDSET2_MAX_BUFFER_SIZE_IN_BYTES <  Next32KBoundary) ? CMDSET2_MAX_BUFFER_SIZE_IN_BYTES : (Next32KBoundary - DstPtr));

    Status = NorFlashWriteBuffer (Instance, DstPtr, Incr, (UINT32 *)pWriteBuffer);
    if (EFI_ERROR(Status)) {
      break;
    }

    DstPtr += Incr;
    pWriteBuffer += Incr;
    NumBytesWritten += Incr;
  }

  //DEBUG((DEBUG_BLKIO, "NorFlashWriteMultipleBuffers: Exit Status = \"%r\".\n", Status));
  return Status;
}

EFI_STATUS
NorFlashWriteBlocks (
  IN NOR_FLASH_INSTANCE     *Instance,
  IN EFI_LBA                Lba,
  IN UINTN                  BufferSizeInBytes,
  IN VOID                   *Buffer,
  IN BOOLEAN                Erase
  )
{
  UINTN      X1, X2, X3;
  UINTN      S1, S2, S3;
  UINTN      O1, O2, O3;
  UINTN      base_offset;
  EFI_LBA    Lba1, Lba2, Lba3;
  UINT8     *Buffer1 = NULL, *Buffer2 =  NULL, *Buffer3 = NULL;
  EFI_TPL    OriginalTPL;

  // if not initialized, initialize instance first
  if (!Instance->Initialized && Instance->Initialize) {
    Instance->Initialize(Instance);
  }

  // The buffer must be valid
  if (Buffer == NULL) {
    return EFI_INVALID_PARAMETER;
  }

  if (Instance->Media.ReadOnly == TRUE) {
    return EFI_WRITE_PROTECTED;
  }

  // We must have some bytes to read
  DEBUG((DEBUG_BLKIO, "NorFlashWriteBlocks: BufferSizeInBytes=0x%x Buffer:0x%p\n", BufferSizeInBytes, Buffer));
  if (BufferSizeInBytes == 0) {
    return EFI_BAD_BUFFER_SIZE;
  }

  // Determine the Buffer limits
  base_offset = Instance->RegionBaseAddress - Instance->DeviceBaseAddress;
  O2 = Lba * Instance->Media.BlockSize + base_offset;
  O1 = NorSectorAddr(O2);
  X1 = Instance->DeviceBaseAddress + O1;
  S1 = O2 - O1;
  X2 = Instance->DeviceBaseAddress + O2;
  S2 = BufferSizeInBytes;
  O3 = O2 + BufferSizeInBytes;
  X3 = Instance->DeviceBaseAddress + O3;
  if (NorSectorAddr(O3) == O3)
    S3 = 0;
  else
    S3 = NorNextSectorAddr(O3) - O3;

  Lba1 = (X1-Instance->DeviceBaseAddress-base_offset)/Instance->Media.BlockSize;
  Lba2 = (X2-Instance->DeviceBaseAddress-base_offset)/Instance->Media.BlockSize;
  Lba3 = (X3-Instance->DeviceBaseAddress-base_offset)/Instance->Media.BlockSize;

  DEBUG((DEBUG_BLKIO, "Lba=%ld Lbal=%ld Lba2=%ld Lba3=%ld\n",
          Lba, Lba1, Lba2, Lba3));
  DEBUG((DEBUG_BLKIO, "O1=0x%lx O2=0x%lx O3=0x%lx X1=0x%lx X2=0x%lx X3=0x%lx "
          "S1=0x%lx S2=0x%lx S3=0x%lx\n", O1, O2, O3, X1, X2, X3, S1, S2, S3)); ASSERT(1);

  if (!VALID_NOR_ADDR(X1, Instance->DeviceBaseAddress)) {
    DEBUG((DEBUG_BLKIO, "Invalid address: 0x%lx\n", X1));
    return EFI_INVALID_PARAMETER;
  }

  if (!VALID_NOR_ADDR(X2, Instance->DeviceBaseAddress)) {
    DEBUG((DEBUG_BLKIO, "Invalid address: 0x%lx\n", X2));
    return EFI_INVALID_PARAMETER;
  }

  if (!VALID_NOR_ADDR(X3, Instance->DeviceBaseAddress)) {
    DEBUG((DEBUG_BLKIO, "Invalid address: 0x%lx\n", X3));
    return EFI_INVALID_PARAMETER;
  }

  // Entire sector is erase in an erase operation
  // Preserve the data that is not in the range
  if (S1) {
    Buffer1 = TmpRuntimeBuffer;
    ASSERT(S1 < MAX_RUNTIME_BUFFER_SIZE);
    NorFlashReadBlocks(Instance,Lba1,S1,Buffer1);
  }

  Buffer2 = (UINT8 *) Buffer;
  if (S3) {
    Buffer3 = TmpRuntimeBuffer;
    ASSERT(S3 < MAX_RUNTIME_BUFFER_SIZE);
    NorFlashReadBlocks(Instance,Lba3,S3,Buffer3);
  }

  // Raise TPL to TPL_HIGH to stop anyone from interrupting us.
  if (!EfiAtRuntime ()) {
    OriginalTPL = gBS->RaiseTPL (TPL_HIGH_LEVEL);
  } else {
    // This initialization is only to prevent the compiler to complain about the
    // use of uninitialized variables
    OriginalTPL = TPL_HIGH_LEVEL;
  }

  // Erase and write
  if (S1) {
    NorFlashEraseSectors(Instance, X1 - Instance->DeviceBaseAddress, S1);
  }

  NorFlashEraseSectors(Instance, X2 - Instance->DeviceBaseAddress, S2);

  if (S3) {
    NorFlashEraseSectors(Instance, X3 - Instance->DeviceBaseAddress, S3);
  }

  if (S1) {
    NorFlashWriteMultipleBuffers(Instance, X1, S1, Buffer1);
  }

  NorFlashWriteMultipleBuffers(Instance, X2, S2, Buffer2);

  if (S3) {
    NorFlashWriteMultipleBuffers(Instance, X3, S3, Buffer3);
  }

  if (!EfiAtRuntime ()) {
    // Interruptions can resume.
    gBS->RestoreTPL (OriginalTPL);
  }

  return EFI_SUCCESS;
}

EFI_STATUS
NorFlashReadBlocks (
  IN NOR_FLASH_INSTANCE   *Instance,
  IN EFI_LBA              Lba,
  IN UINTN                BufferSizeInBytes,
  OUT VOID                *Buffer
  )
{
  UINTN Addr = Lba * Instance->Media.BlockSize + Instance->RegionBaseAddress;
  UINT16 *SrcPtr = (UINT16 *)Addr;
  UINT16 *DstPtr = Buffer;
  UINTN Count;

  if (!VALID_NOR_ADDR(Addr, Instance->DeviceBaseAddress)) {
    DEBUG((DEBUG_ERROR, "Invalid address: 0x%lx\n", Addr));
    return EFI_INVALID_PARAMETER;
  }

  // The buffer must be valid
  if (Buffer == NULL) {
    return EFI_INVALID_PARAMETER;
  }

  // We must have some bytes to read
  DEBUG((DEBUG_BLKIO, "NorFlashReadBlocks: BufferSize=0x%x bytes.\n", BufferSizeInBytes));
  if (BufferSizeInBytes == 0) {
    return EFI_SUCCESS;
  }

  // Put the device into Read Array mode
  SEND_NOR_COMMAND (Instance->DeviceBaseAddress, 0, CMDSET2_CMD_READ_ARRAY);

  for (Count = 0 ; Count < BufferSizeInBytes ; Count += 2, SrcPtr++, DstPtr++)  {
    *DstPtr = *SrcPtr;
  }

  return EFI_SUCCESS;
}
#else /* APM_XGENE_SPI_FLASH */

EFI_STATUS
NorFlashEraseSingleBlock (
  IN NOR_FLASH_INSTANCE     *Instance,
  IN UINTN                  BlockAddress
  )
{
  DEBUG((DEBUG_BLKIO,"NorFlashEraseSingleBlock(Address=0x%08x\n", BlockAddress));
  return NorFlashPlatformErase(BlockAddress, Instance->Media.BlockSize);
}

EFI_STATUS
NorFlashWriteBlocks (
  IN NOR_FLASH_INSTANCE     *Instance,
  IN EFI_LBA                Lba,
  IN UINTN                  BufferSizeInBytes,
  IN VOID                   *Buffer,
  IN BOOLEAN                Erase
  )
{
  EFI_STATUS      Status = EFI_SUCCESS;
  EFI_TPL         OriginalTPL = TPL_HIGH_LEVEL;
  UINT32 Addr = Lba * Instance->Media.BlockSize + Instance->RegionBaseAddress;

  // if not initialized, initialize instance first
  if (!Instance->Initialized && Instance->Initialize) {
    Instance->Initialize(Instance);
  }

  // The buffer must be valid
  if (Buffer == NULL) {
    return EFI_INVALID_PARAMETER;
  }

  if (Instance->Media.ReadOnly == TRUE) {
    return EFI_WRITE_PROTECTED;
  }

  // We must have some bytes to read
  DEBUG((DEBUG_BLKIO, "NorFlashWriteBlocks: BufferSizeInBytes=0x%x Buffer:0x%p\n", BufferSizeInBytes, Buffer));
  if (BufferSizeInBytes == 0) {
    return EFI_BAD_BUFFER_SIZE;
  }

  if (!EfiAtRuntime ()) {
    // Raise TPL to TPL_HIGH to stop anyone from interrupting us.
    OriginalTPL = gBS->RaiseTPL (TPL_HIGH_LEVEL);
  } else {
    // This initialization is only to prevent the compiler to complain about the
    // use of uninitialized variables
    OriginalTPL = TPL_HIGH_LEVEL;
  }

  if (Erase) {
    Status = NorFlashPlatformErase(Addr, BufferSizeInBytes);
  }

  if (!EFI_ERROR(Status)) {
    Status = NorFlashPlatformWrite(Addr, (VOID *)Buffer, BufferSizeInBytes);
    DEBUG((DEBUG_BLKIO, "NorFlashWriteBlocks: Exit BufferSizeInBytes=0x%x Buffer:0x%p\n", BufferSizeInBytes, Buffer));
  }

  if (!EfiAtRuntime()) {
    // Interruptions can resume.
    gBS->RestoreTPL (OriginalTPL);
  }

  return Status;
}

EFI_STATUS NorFlashReadBlocks (
  IN NOR_FLASH_INSTANCE   *Instance,
  IN EFI_LBA              Lba,
  IN UINTN                BufferSizeInBytes,
  OUT VOID                *Buffer
  )
{
  UINT32 Addr = Lba * Instance->Media.BlockSize + Instance->RegionBaseAddress;

  // if not initialized, initialize instance first
  if (!Instance->Initialized && Instance->Initialize) {
    Instance->Initialize(Instance);
  }

  // The buffer must be valid
  if (Buffer == NULL) {
    return EFI_INVALID_PARAMETER;
  }

  // We must have some bytes to read
  DEBUG((DEBUG_BLKIO, "NorFlashReadBlocks: BufferSize=0x%x bytes.\n", BufferSizeInBytes));
  if (BufferSizeInBytes == 0) {
    return EFI_SUCCESS;
  }

  return NorFlashPlatformRead(Addr, (VOID *)Buffer, BufferSizeInBytes);
}
#endif

EFI_STATUS
NorFlashUnlockSingleBlockIfNecessary (
  IN NOR_FLASH_INSTANCE     *Instance,
  IN UINTN                  BlockAddress
  )
{
  return EFI_SUCCESS;
}

/**
 * The following function presumes that the block has already been unlocked.
 **/
EFI_STATUS
NorFlashUnlockAndEraseSingleBlock (
  IN NOR_FLASH_INSTANCE     *Instance,
  IN UINTN                  BlockAddress
  )
{
  EFI_STATUS      Status;
  UINTN           Index;
  EFI_TPL         OriginalTPL;

  if (!EfiAtRuntime ()) {
    // Raise TPL to TPL_HIGH to stop anyone from interrupting us.
    OriginalTPL = gBS->RaiseTPL (TPL_HIGH_LEVEL);
  } else {
    // This initialization is only to prevent the compiler to complain about the
    // use of uninitialized variables
    OriginalTPL = TPL_HIGH_LEVEL;
  }

  Index = 0;
  // The block erase might fail a first time (SW bug ?). Retry it ...
  do {
    // Unlock the block if we have to
    Status = NorFlashUnlockSingleBlockIfNecessary (Instance, BlockAddress);
    if (!EFI_ERROR(Status)) {
      Status = NorFlashEraseSingleBlock (Instance, BlockAddress);
    }
    Index++;
  } while ((Index < NOR_FLASH_ERASE_RETRY) && (Status == EFI_WRITE_PROTECTED));

  if (Index == NOR_FLASH_ERASE_RETRY) {
    DEBUG((EFI_D_ERROR,"EraseSingleBlock(BlockAddress=0x%08x: Block Locked Error (try to erase %d times)\n", BlockAddress,Index));
  }

  if (!EfiAtRuntime()) {
    // Interruptions can resume.
    gBS->RestoreTPL (OriginalTPL);
  }

  return Status;
}

EFI_STATUS
NorFlashReset (
  IN  NOR_FLASH_INSTANCE *Instance
  )
{
  // As there is no specific RESET to perform, ensure that the devices is in the default Read Array mode
#if defined(APM_XGENE_GFC_FLASH)
  SEND_NOR_COMMAND (Instance->DeviceBaseAddress, 0, CMDSET2_CMD_READ_ARRAY);
#endif

  return EFI_SUCCESS;
}

EFI_STATUS
NorFlashCreateInstance (
  IN UINTN                  NorFlashDeviceBase,
  IN UINTN                  NorFlashRegionBase,
  IN UINTN                  NorFlashSize,
  IN UINT32                 MediaId,
  IN UINT32                 BlockSize,
  IN BOOLEAN                SupportFvb,
  IN CONST GUID             *NorFlashGuid,
  OUT NOR_FLASH_INSTANCE**  NorFlashInstance
  )
{
  EFI_STATUS Status;
  NOR_FLASH_INSTANCE* Instance;

  ASSERT(NorFlashInstance != NULL);

  Instance = AllocateRuntimeCopyPool (sizeof(NOR_FLASH_INSTANCE),&mNorFlashInstanceTemplate);
  if (Instance == NULL) {
    return EFI_OUT_OF_RESOURCES;
  }

  DEBUG((DEBUG_BLKIO, "FvbGetMappedAddress: 0x%p\n", FvbGetMappedAddress));

  Instance->DeviceBaseAddress = NorFlashDeviceBase;
  Instance->RegionBaseAddress = NorFlashRegionBase;
  Instance->Size = NorFlashSize;

  Instance->BlockIoProtocol.Media = &Instance->Media;
  Instance->Media.MediaId = MediaId;
  Instance->Media.BlockSize = BlockSize;
  Instance->Media.LastBlock = (NorFlashSize / BlockSize)-1;

  CopyGuid (&Instance->DevicePath.Vendor.Guid,NorFlashGuid);

  if (SupportFvb) {
    Instance->SupportFvb = TRUE;
    Instance->Initialize = NorFlashFvbInitialize;

    Status = gBS->InstallMultipleProtocolInterfaces (
                  &Instance->Handle,
                  &gEfiDevicePathProtocolGuid, &Instance->DevicePath,
                  &gEfiBlockIoProtocolGuid,  &Instance->BlockIoProtocol,
                  &gEfiFirmwareVolumeBlockProtocolGuid, &Instance->FvbProtocol,
                  NULL
                  );
    if (EFI_ERROR(Status)) {
      FreePool(Instance);
      return Status;
    }
  } else {
    Instance->Initialized = TRUE;

    Status = gBS->InstallMultipleProtocolInterfaces (
                    &Instance->Handle,
                    &gEfiDevicePathProtocolGuid, &Instance->DevicePath,
                    &gEfiBlockIoProtocolGuid,  &Instance->BlockIoProtocol,
                    NULL
                    );
    if (EFI_ERROR(Status)) {
      FreePool(Instance);
      return Status;
    }
  }

  *NorFlashInstance = Instance;
  return Status;
}

/**
  Notification function of EVT_SIGNAL_VIRTUAL_ADDRESS_CHANGE.

  This is a notification function registered on EVT_SIGNAL_VIRTUAL_ADDRESS_CHANGE event.
  It convers pointer to new virtual address.

  @param  Event        Event whose notification function is being invoked.
  @param  Context      Pointer to the notification function's context.

**/
VOID
EFIAPI
NorFlashVirtualNotifyEvent (
  IN EFI_EVENT                            Event,
  IN VOID                                 *Context
  )
{
  INTN Index;
  for (Index = 0; Index < *mNorFlashDeviceCount; Index++) {
    if (!mNorFlashInstances[Index]->PhysicalAddress) {
      /* FIXME: EfiConvertPointer doesn't deal with zero address */
      mNorFlashInstances[Index]->PhysicalAddress |= 0x1;
    }
    if (!mNorFlashInstances[Index]->DeviceBaseAddress) {
      /* FIXME: EfiConvertPointer doesn't deal with zero address */
      mNorFlashInstances[Index]->DeviceBaseAddress |= 0x1;
    }
    if (!mNorFlashInstances[Index]->RegionBaseAddress) {
      /* FIXME: EfiConvertPointer doesn't deal with zero address */
      mNorFlashInstances[Index]->RegionBaseAddress |= 0x1;
    }
    EfiConvertPointer (0x0, (VOID **) &mNorFlashInstances[Index]->PhysicalAddress);
    EfiConvertPointer (0x0, (VOID **) &mNorFlashInstances[Index]->DeviceBaseAddress);
    EfiConvertPointer (0x0, (VOID **) &mNorFlashInstances[Index]->RegionBaseAddress);

    mNorFlashInstances[Index]->PhysicalAddress &= ~(EFI_PHYSICAL_ADDRESS)0x1;
    mNorFlashInstances[Index]->DeviceBaseAddress &= ~(EFI_PHYSICAL_ADDRESS)0x1;
    mNorFlashInstances[Index]->RegionBaseAddress &= ~(EFI_PHYSICAL_ADDRESS)0x1;

    // Convert BlockIo protocol
    EfiConvertPointer (0x0, (VOID**)&mNorFlashInstances[Index]->BlockIoProtocol.FlushBlocks);
    EfiConvertPointer (0x0, (VOID**)&mNorFlashInstances[Index]->BlockIoProtocol.ReadBlocks);
    EfiConvertPointer (0x0, (VOID**)&mNorFlashInstances[Index]->BlockIoProtocol.Reset);
    EfiConvertPointer (0x0, (VOID**)&mNorFlashInstances[Index]->BlockIoProtocol.WriteBlocks);

    // Convert Fvb
    EfiConvertPointer (0x0, (VOID**)&mNorFlashInstances[Index]->FvbProtocol.EraseBlocks);
    EfiConvertPointer (0x0, (VOID**)&mNorFlashInstances[Index]->FvbProtocol.GetAttributes);
    EfiConvertPointer (0x0, (VOID**)&mNorFlashInstances[Index]->FvbProtocol.GetBlockSize);
    EfiConvertPointer (0x0, (VOID**)&mNorFlashInstances[Index]->FvbProtocol.GetPhysicalAddress);
    EfiConvertPointer (0x0, (VOID**)&mNorFlashInstances[Index]->FvbProtocol.Read);
    EfiConvertPointer (0x0, (VOID**)&mNorFlashInstances[Index]->FvbProtocol.SetAttributes);
    EfiConvertPointer (0x0, (VOID**)&mNorFlashInstances[Index]->FvbProtocol.Write);

  }

  EfiConvertPointer (0x0, (VOID **) &mNorFlashInstances);
  EfiConvertPointer (0x0, (VOID **) &mNorFlashDeviceCount);
  EfiConvertPointer (0x0, (VOID **) &TmpRuntimeBuffer);
#ifdef APM_XGENE_GFC_FLASH
  EfiConvertPointer (0x0, (VOID **) &NorCmdSet2CmdSequence);
  if (!XgeneNor0Base) {
    XgeneNor0Base |= 0x1;
  }
  EfiConvertPointer (0x0, (VOID **) &XgeneNor0Base);
  XgeneNor0Base &= ~(EFI_PHYSICAL_ADDRESS)0x1;
#endif
}

EFI_STATUS
EFIAPI
NorFlashInitialise (
  IN EFI_HANDLE         ImageHandle,
  IN EFI_SYSTEM_TABLE   *SystemTable
  )
{
  EFI_STATUS              Status;
  UINT32                  Index;
  NOR_FLASH_DESCRIPTION*  NorFlashDevices;
  UINT32                  NorFlashDeviceCount;
  BOOLEAN                 ContainVariableStorage;

  Status = NorFlashPlatformInitialization ();
  if (EFI_ERROR(Status)) {
    DEBUG((EFI_D_ERROR,"NorFlashInitialise: Fail to initialize Nor Flash devices\n"));
    return Status;
  }

  Status = NorFlashPlatformGetDevices (&NorFlashDevices,&NorFlashDeviceCount);
  if (EFI_ERROR(Status)) {
    DEBUG((EFI_D_ERROR,"NorFlashInitialise: Fail to get Nor Flash devices\n"));
    return Status;
  }

  mNorFlashInstances = AllocateRuntimePool (sizeof(NOR_FLASH_INSTANCE*) * NorFlashDeviceCount);
  mNorFlashDeviceCount = AllocateRuntimePool (sizeof(UINTN));
  TmpRuntimeBuffer = AllocateRuntimePool (MAX_RUNTIME_BUFFER_SIZE);
  if (!mNorFlashInstances || !mNorFlashDeviceCount || !TmpRuntimeBuffer) {
    DEBUG((EFI_D_ERROR,"NorFlashInitialise: Out of resource\n"));
    return Status;
  }
  *mNorFlashDeviceCount = NorFlashDeviceCount;

  for (Index = 0; Index < NorFlashDeviceCount; Index++) {
    // Check if this NOR Flash device contain the variable storage region
    DEBUG((EFI_D_INFO, "NorFlashDevices[Index].DeviceBaseAddress =%p NorFlashDevices[Index].RegionBaseAddress = %p NorFlashDevices[Index].Size = %p\n",
            NorFlashDevices[Index].DeviceBaseAddress,
            NorFlashDevices[Index].RegionBaseAddress,
            NorFlashDevices[Index].Size));

    ContainVariableStorage =
        (NorFlashDevices[Index].RegionBaseAddress <= PcdGet32 (PcdFlashNvStorageVariableBase)) &&
        (PcdGet32 (PcdFlashNvStorageVariableBase) + PcdGet32 (PcdFlashNvStorageVariableSize) <= NorFlashDevices[Index].RegionBaseAddress + NorFlashDevices[Index].Size);

    Status = NorFlashCreateInstance (
                NorFlashDevices[Index].DeviceBaseAddress,
                NorFlashDevices[Index].RegionBaseAddress,
                NorFlashDevices[Index].Size,
                Index,
                NorFlashDevices[Index].BlockSize,
                ContainVariableStorage,
                &NorFlashDevices[Index].Guid,
                &mNorFlashInstances[Index]
    );
    if (EFI_ERROR(Status)) {
      DEBUG((EFI_D_ERROR,"NorFlashInitialise: Fail to create instance for NorFlash[%d]\n",Index));
    }
  }

  Status = gBS->CreateEventEx (
                  EVT_NOTIFY_SIGNAL,
                  TPL_NOTIFY,
                  NorFlashVirtualNotifyEvent,
                  NULL,
                  &gEfiEventVirtualAddressChangeGuid,
                  &mNorFlashVirtualAddrChangeEvent
                  );
  ASSERT_EFI_ERROR (Status);

  return Status;
}
