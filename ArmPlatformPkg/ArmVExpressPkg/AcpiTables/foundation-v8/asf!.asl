/*
 * Intel ACPI Component Architecture
 * iASL Compiler/Disassembler version 20130117-64 [Jan 31 2013]
 * Copyright (c) 2000 - 2013 Intel Corporation
 * 
 * Template for [ASF!] ACPI Table
 * Format: [ByteLength]  FieldName : HexFieldValue
 */

[0004]                          Signature : "ASF!"    [Alert Standard Format table]
[0004]                       Table Length : 00000072
[0001]                           Revision : 10
[0001]                           Checksum : 0B
[0006]                             Oem ID : "INTEL "
[0008]                       Oem Table ID : "TEMPLATE"
[0004]                       Oem Revision : 00000001
[0004]                    Asl Compiler ID : "INTL"
[0004]              Asl Compiler Revision : 20100528

[0001]                      Subtable Type : 00 [ASF Information]
[0001]                           Reserved : 00
[0002]                             Length : 0010
[0001]                Minimum Reset Value : 00
[0001]           Minimum Polling Interval : 00
[0002]                          System ID : 0000
[0004]                    Manufacturer ID : 00000000
[0001]                              Flags : 00
[0003]                           Reserved : 000000

[0001]                      Subtable Type : 01 [ASF Alerts]
[0001]                           Reserved : 00
[0002]                             Length : 0014
[0001]                         AssertMask : 00
[0001]                       DeassertMask : 00
[0001]                        Alert Count : 01
[0001]                  Alert Data Length : 0C

[0001]                            Address : 00
[0001]                            Command : 00
[0001]                               Mask : 00
[0001]                              Value : 00
[0001]                         SensorType : 00
[0001]                               Type : 00
[0001]                             Offset : 00
[0001]                         SourceType : 00
[0001]                           Severity : 00
[0001]                       SensorNumber : 00
[0001]                             Entity : 00
[0001]                           Instance : 00

[0001]                      Subtable Type : 02 [ASF Remote Control]
[0001]                           Reserved : 00
[0002]                             Length : 000C
[0001]                      Control Count : 01
[0001]                Control Data Length : 04
[0002]                           Reserved : 0000

[0001]                           Function : 00
[0001]                            Address : 00
[0001]                            Command : 00
[0001]                              Value : 00

[0001]                      Subtable Type : 03 [ASF RMCP Boot Options]
[0001]                           Reserved : 00
[0002]                             Length : 0017
[0007]                       Capabilities : 00 00 00 00 00 00 00
[0001]                    Completion Code : 00
[0004]                      Enterprise ID : 00000000
[0001]                            Command : 00
[0002]                          Parameter : 0000
[0002]                       Boot Options : 0000
[0002]                     Oem Parameters : 0000

[0001]                      Subtable Type : 84 [ASF Address]
[0001]                           Reserved : 00
[0002]                             Length : 0007
[0001]                      Eprom Address : 00
[0001]                       Device Count : 01
[0001]                          Addresses : 00 

