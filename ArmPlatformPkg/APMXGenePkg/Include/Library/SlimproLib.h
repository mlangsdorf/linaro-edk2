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

#ifndef _SLIMPROLIB_H_
#define _SLIMPROLIB_H_

/** Mode mask */
#define IPP_MODE_MASK           0x0C000000
/** Mode value ROM Code */
#define IPP_ROM_MODE_MASK       0x04000000
/** Mode value RUNTIME Code */
#define IPP_RUNTIME_MODE_MASK   0x08000000
/** Mode value EXTERNAL Code */
#define IPP_EXTBOOT_MODE_MASK   0x0C000000
/** Mode shift */
#define IPP_MODE_SHIFT          26

EFI_STATUS
EFIAPI
XGeneBMCStart(BOOLEAN Start);

EFI_STATUS
EFIAPI
XGeneReadIppMsg(UINT32 *data);

EFI_STATUS
EFIAPI
XGeneWriteIppMsg(UINT32 data, UINT32 param);

EFI_STATUS
EFIAPI
XGeneIppLoadFile(CHAR8* f_name, UINT64 addr,
        UINTN offset, UINTN size);

UINT32
EFIAPI
XGeneIppGetBootMode(VOID);

EFI_STATUS
EFIAPI
XGeneIppGetFWStrInfo(CHAR16* Str, UINT32 Len);

#endif /* _SLIMPROLIB_H_*/
