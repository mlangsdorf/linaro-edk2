/*
 * Copyright (c) 2013, Al Stone <al.stone@linaro.org>
 * All rights reserved.
 * 
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 
 * 1. Redistributions of source code must retain the above copyright 
 * notice, this list of conditions and the following disclaimer.
 * 
 * 2. Redistributions in binary form must reproduce the above copyright
 * notice, this list of conditions and the following disclaimer in the 
 * documentation and/or other materials provided with the distribution.
 * 
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT 
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED
 * TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
 * PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
 * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
 * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS 
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 * 
 * 
 * NB: This License is also known as the "BSD 2-Clause License".
 * 
 * 
 * Template for [CSRT] ACPI Table
 * Format: [ByteLength]  FieldName : HexFieldValue
 * 
 */

[0004]                          Signature : "CSRT"    [Core System Resource Table]
[0004]                       Table Length : 0000014C
[0001]                           Revision : 01
[0001]                           Checksum : 0D
[0006]                             Oem ID : "LINARO"
[0008]                       Oem Table ID : "FOUNDATI"
[0004]                       Oem Revision : 00000001
[0004]                    Asl Compiler ID : "INTL"
[0004]              Asl Compiler Revision : 20121114


[0004]                             Length : 00000088
[0004]                          Vendor ID : 4C544E49
[0004]                       Subvendor ID : 00000000
[0002]                          Device ID : 9C60
[0002]                       Subdevice ID : 0000
[0002]                           Revision : 0002
[0002]                           Reserved : 0000
[0004]                 Shared Info Length : 0000001C

[0002]                      Major Version : 0001
[0002]                      Minor Version : 0000
[0004]              MMIO Base Address Low : B3A00000
[0004]             MMIO Base Address High : 00000000
[0004]                      GSI Interrupt : 0000002A
[0001]                 Interrupt Polarity : 02
[0001]                     Interrupt Mode : 00
[0001]                       Num Channels : 06
[0001]                  DMA Address Width : 20
[0002]                  Base Request Line : 0000
[0002]              Num Handshake Signals : 0010
[0004]                     Max Block Size : 00000FFF

[0004]                             Length : 0000000C
[0002]                               Type : 0003
[0002]                            Subtype : 0001
[0004]                                UID : 20495053

[0004]                             Length : 0000000C
[0002]                               Type : 0003
[0002]                            Subtype : 0000
[0004]                                UID : 30414843

[0004]                             Length : 0000000C
[0002]                               Type : 0003
[0002]                            Subtype : 0000
[0004]                                UID : 31414843

[0004]                             Length : 0000000C
[0002]                               Type : 0003
[0002]                            Subtype : 0000
[0004]                                UID : 32414843

[0004]                             Length : 0000000C
[0002]                               Type : 0003
[0002]                            Subtype : 0000
[0004]                                UID : 33414843

[0004]                             Length : 0000000C
[0002]                               Type : 0003
[0002]                            Subtype : 0000
[0004]                                UID : 34414843

[0004]                             Length : 0000000C
[0002]                               Type : 0003
[0002]                            Subtype : 0000
[0004]                                UID : 35414843

[0004]                             Length : 000000A0
[0004]                          Vendor ID : 4C544E49
[0004]                       Subvendor ID : 00000000
[0002]                          Device ID : 9C60
[0002]                       Subdevice ID : 0000
[0002]                           Revision : 0003
[0002]                           Reserved : 0000
[0004]                 Shared Info Length : 0000001C

[0002]                      Major Version : 0001
[0002]                      Minor Version : 0000
[0004]              MMIO Base Address Low : 00000000
[0004]             MMIO Base Address High : 00000000
[0004]                      GSI Interrupt : 0000002B
[0001]                 Interrupt Polarity : 02
[0001]                     Interrupt Mode : 00
[0001]                       Num Channels : 08
[0001]                  DMA Address Width : 20
[0002]                  Base Request Line : 0010
[0002]              Num Handshake Signals : 0010
[0004]                     Max Block Size : 00000FFF

[0004]                             Length : 0000000C
[0002]                               Type : 0003
[0002]                            Subtype : 0001
[0004]                                UID : 20433249

[0004]                             Length : 0000000C
[0002]                               Type : 0003
[0002]                            Subtype : 0000
[0004]                                UID : 30414843

[0004]                             Length : 0000000C
[0002]                               Type : 0003
[0002]                            Subtype : 0000
[0004]                                UID : 31414843

[0004]                             Length : 0000000C
[0002]                               Type : 0003
[0002]                            Subtype : 0000
[0004]                                UID : 32414843

[0004]                             Length : 0000000C
[0002]                               Type : 0003
[0002]                            Subtype : 0000
[0004]                                UID : 33414843

[0004]                             Length : 0000000C
[0002]                               Type : 0003
[0002]                            Subtype : 0000
[0004]                                UID : 34414843

[0004]                             Length : 0000000C
[0002]                               Type : 0003
[0002]                            Subtype : 0000
[0004]                                UID : 35414843

[0004]                             Length : 0000000C
[0002]                               Type : 0003
[0002]                            Subtype : 0000
[0004]                                UID : 36414843

[0004]                             Length : 0000000C
[0002]                               Type : 0003
[0002]                            Subtype : 0000
[0004]                                UID : 37414843
