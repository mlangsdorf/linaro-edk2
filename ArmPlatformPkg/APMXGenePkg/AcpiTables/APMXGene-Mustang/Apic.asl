/**
 * Copyright (c) 2013, AppliedMicro Corp. All rights reserved.
 *
 * This program and the accompanying materials are licensed and made
 * available under the terms and conditions of the BSD License which
 * accompanies this distribution.  The full text of the license may be
 * found at * http://opensource.org/licenses/bsd-license.php
 *
 * THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
 * WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.
 *
 * APIC Table for X-Gene Processor
 * 
 * Format: [ByteLength]  FieldName : HexFieldValue
 *
 **/

[0004]                          Signature : "APIC"    [Multiple APIC Description Table (MADT)]
[0004]                       Table Length : 00000184
[0001]                           Revision : 01
[0001]                           Checksum : 00
[0006]                             Oem ID : "APM   "
[0008]                       Oem Table ID : "XGENE   "
[0004]                       Oem Revision : 00000002
[0004]                    Asl Compiler ID : "INTL"
[0004]              Asl Compiler Revision : 20110623

[0004]                 Local Apic Address : 00000000
[0004]              Flags (decoded below) : 00000001
                      PC-AT Compatibility : 1

[0001]                      Subtable Type : 0B [Generic Interrupt Controller]
[0001]                             Length : 28
[0002]                           Reserved : 0000
[0004]              Local GIC Hardware ID : 00000000
[0004]                      Processor UID : 00000000
[0004]              Flags (decoded below) : 00000001
                        Processor Enabled : 1
[0004]           Parking Protocol Version : 00000001
[0004]              Performance Interrupt : 00000000
[0008]                     Parked Address : 0000004000008000
[0008]                       Base Address : 00000000780A0000

[0001]                      Subtable Type : 0B [Generic Interrupt Controller]
[0001]                             Length : 28
[0002]                           Reserved : 0000
[0004]              Local GIC Hardware ID : 00000001
[0004]                      Processor UID : 00000001
[0004]              Flags (decoded below) : 00000001
                        Processor Enabled : 1
[0004]           Parking Protocol Version : 00000001
[0004]              Performance Interrupt : 00000000
[0008]                     Parked Address : 0000004000009000
[0008]                       Base Address : 00000000780A0000

[0001]                      Subtable Type : 0B [Generic Interrupt Controller]
[0001]                             Length : 28
[0002]                           Reserved : 0000
[0004]              Local GIC Hardware ID : 00000002
[0004]                      Processor UID : 00000002
[0004]              Flags (decoded below) : 00000001
                        Processor Enabled : 1
[0004]           Parking Protocol Version : 00000001
[0004]              Performance Interrupt : 00000000
[0008]                     Parked Address : 000000400000A000
[0008]                       Base Address : 00000000780A0000

[0001]                      Subtable Type : 0B [Generic Interrupt Controller]
[0001]                             Length : 28
[0002]                           Reserved : 0000
[0004]              Local GIC Hardware ID : 00000003
[0004]                      Processor UID : 00000003
[0004]              Flags (decoded below) : 00000001
                        Processor Enabled : 1
[0004]           Parking Protocol Version : 00000001
[0004]              Performance Interrupt : 00000000
[0008]                     Parked Address : 000000400000B000
[0008]                       Base Address : 00000000780A0000

[0001]                      Subtable Type : 0B [Generic Interrupt Controller]
[0001]                             Length : 28
[0002]                           Reserved : 0000
[0004]              Local GIC Hardware ID : 00000004
[0004]                      Processor UID : 00000004
[0004]              Flags (decoded below) : 00000001
                        Processor Enabled : 1
[0004]           Parking Protocol Version : 00000001
[0004]              Performance Interrupt : 00000000
[0008]                     Parked Address : 000000400000C000
[0008]                       Base Address : 00000000780A0000

[0001]                      Subtable Type : 0B [Generic Interrupt Controller]
[0001]                             Length : 28
[0002]                           Reserved : 0000
[0004]              Local GIC Hardware ID : 00000005
[0004]                      Processor UID : 00000005
[0004]              Flags (decoded below) : 00000001
                        Processor Enabled : 1
[0004]           Parking Protocol Version : 00000001
[0004]              Performance Interrupt : 00000000
[0008]                     Parked Address : 000000400000D000
[0008]                       Base Address : 00000000780A0000

[0001]                      Subtable Type : 0B [Generic Interrupt Controller]
[0001]                             Length : 28
[0002]                           Reserved : 0000
[0004]              Local GIC Hardware ID : 00000006
[0004]                      Processor UID : 00000006
[0004]              Flags (decoded below) : 00000001
                        Processor Enabled : 1
[0004]           Parking Protocol Version : 00000001
[0004]              Performance Interrupt : 00000000
[0008]                     Parked Address : 000000400000E000
[0008]                       Base Address : 00000000780A0000

[0001]                      Subtable Type : 0B [Generic Interrupt Controller]
[0001]                             Length : 28
[0002]                           Reserved : 0000
[0004]              Local GIC Hardware ID : 00000007
[0004]                      Processor UID : 00000007
[0004]              Flags (decoded below) : 00000001
                        Processor Enabled : 1
[0004]           Parking Protocol Version : 00000001
[0004]              Performance Interrupt : 00000000
[0008]                     Parked Address : 000000400000F000
[0008]                       Base Address : 00000000780A0000

[0001]                      Subtable Type : 0C [Generic Interrupt Distributor]
[0001]                             Length : 18
[0002]                           Reserved : 0000
[0004]              Local GIC Hardware ID : 00000000
[0008]                       Base Address : 0000000078090000
[0004]                     Interrupt Base : 00000000
[0004]                           Reserved : 00000000
