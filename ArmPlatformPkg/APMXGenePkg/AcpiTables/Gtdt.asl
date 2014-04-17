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
 * GTDT Table for X-Gene Processor
 *
 * Format: [ByteLength]  FieldName : HexFieldValue
 *
 **/

[0004]                          Signature : "GTDT"    [Generic Timer Description Table]
[0004]                       Table Length : 00000050
[0001]                           Revision : 01
[0001]                           Checksum : 00
[0006]                             Oem ID : "APM   "
[0008]                       Oem Table ID : "APMACPI "
[0004]                       Oem Revision : 00000001
[0004]                    Asl Compiler ID : "INTL"
[0004]              Asl Compiler Revision : 20110623

[0008]                      Timer Address : 0000000002FAF080
[0004]              Flags (decoded below) : 00000001
                           Memory Present : 1

[0004]               Secure PL1 Interrupt : 00000000
[0004]         SPL1 Flags (decoded below) : 00000000
                             Trigger Mode : 0
                                 Polarity : 0

[0004]           Non-Secure PL1 Interrupt : 0000000D
[0004]        NSPL1 Flags (decoded below) : 00000000
                             Trigger Mode : 0
                                 Polarity : 0

[0004]            Virtual Timer Interrupt : 00000000
[0004]           VT Flags (decoded below) : 00000000
                             Trigger Mode : 0
                                 Polarity : 0

[0004]           Non-Secure PL2 Interrupt : 00000000
[0004]        NSPL2 Flags (decoded below) : 00000000
                             Trigger Mode : 0
                                 Polarity : 0
