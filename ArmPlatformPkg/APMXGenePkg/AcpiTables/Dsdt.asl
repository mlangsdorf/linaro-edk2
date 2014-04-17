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

DefinitionBlock("apm88xxxx_dsdt.aml", "DSDT", 0x05, "APM   ", "APM88xxxx", 1) {

//Operation Region For Power Control and Power Good
	OperationRegion(\PGUD, SystemMemory, 0x17000078, 4)
	OperationRegion(\PCTL, SystemMemory, 0x1700007C, 4)
	Field(\PGUD, DWordAcc, NoLock, Preserve) {
		SOCG, 1,
		L3CG, 1,
		PD0G, 1,
		PD1G, 1,
		PD2G, 1,
		PD3G, 1
	}
	Field(\PCTL, DWordAcc, NoLock, Preserve) {
		SOCC, 1,
		L3CC, 1,
		PD0C, 1,
		PD1C, 1,
		PD2C, 1,
		PD3C, 1
	}

//SOC VRM resource, power domain for SOC
	PowerResource(SCVR, 2, 0) {
		Method(_STA) {
			Return (NAnd(SOCC, One))
		}
		Method(_ON) {
			Store(One, SOCC)
			Sleep(10)
		}
		Method(_OFF) {
			Store(Zero, SOCC)
			Sleep(10)
		}
	}//SCVR

////////////////////////////////////////////////////////////////////////////////
//System Sleep States

	Name(\_S0, Package(){0x00000000, 0x00000000})
	Name(\_S1, Package(){0x00000001, 0x00000000})
	Name(\_S2, Package(){0x00000002, 0x00000000})

////////////////////////////////////////////////////////////////////////////////
//Processor
	Processor(\_SB.CPU0, 0, 0, 0) {

	Name(_UID, 0)
	Name(_HID, "ACPI0007")
        Method (_STA, 0, NotSerialized) {
			Return (0x0F)
        }

//Clock Domain Object
	Name(_CDM, 0)	//Domain 0

	Method(_PSC) {
		Return (0)
	} //_PSC

//Sleeping state correlation
	Name(_S1D, 3)
	Name(_S2D, 4)
	Name(_S3D, 6)

//Performance Control
	Name(_PCT, Package() {
		ResourceTemplate() {Register(SystemIO, 32, 0, 0x10550000, 3)},
		ResourceTemplate() {Register(SystemIO, 32, 0, 0x10550004, 3)}
	}) //_PCT
//Performance States
	Name(_PSS, Package() {
		Package() {
			2400,	//frequency MHz
			2500, 	//Power milli watts
			10,	//Latency usec
			10,	//Bus master latency usec
			0x10,	//Control value
			0x20,	//Status value
		}, //P0
		Package() {
			2400,	//frequency MHz
			2500, 	//Power milli watts
			10,	//Latency usec
			10,	//Bus master latency usec
			0x11,	//Control value
			0x21,	//Status value
		}, //P1
		Package() {
			1200,	//frequency MHz
			1500, 	//Power milli watts
			10,	//Latency usec
			10,	//Bus master latency usec
			0x12,	//Control value
			0x22,	//Status value
		}, //P2
		Package() {
			800,	//frequency MHz
			1000, 	//Power milli watts
			10,	//Latency usec
			10,	//Bus master latency usec
			0x13,	//Control value
			0x23,	//Status value
		}, //P3
		Package() {
			600,	//frequency MHz
			800, 	//Power milli watts
			10,	//Latency usec
			10,	//Bus master latency usec
			0x14,	//Control value
			0x24,	//Status value
		} //P4
	}) //_PSS
//Performance State dependency
	Name(_PSD, Package() {
		Package() {5, 0, 0, 0xFC, 2}
	}) //Domain 0

//C states
	Name(_CST, Package() {
		1,
		Package() {	//C1 state
			ResourceTemplate() {Register(SystemMemory, 32, 0, 0x10550014, 3)},
			1,
			0,	//latency usec
			2500	//power mW
		}, //C1 state
/*		Package() {	//C3 state
			ResourceTemplate() {Register(SystemMemory, 32, 0, 0x10550018, 3)},
			3,
			200000,	//latency usec
			1800	//power mW
		}, //C3 state*/
	}) //_CST
//C state dependency
	Name(_CSD, Package() {
		Package() {6, 0, 0, 0xFC, 1, 1},
//		Package() {6, 0, 0, 0xFC, 2, 2},
	}) //_CSD

	}//CPU0
////////////////////////////////////////////////////////////////////////////////
//Processor
	Processor(\_SB.CPU1, 1, 0, 0) {

	Name(_UID, 1)
	Name(_HID, "ACPI0007")
        Method(_STA) {
                Return (One)
        }

//Clock Domain Object
	Name(_CDM, 0)	//Domain 0

        Method(_PSC) {
                Return (0)
        } //_PSC

//Sleeping state correlation
	Name(_S1D, 3)
	Name(_S2D, 4)
	Name(_S3D, 6)

//Performance Control
	Name(_PCT, Package() {
		ResourceTemplate() {Register(SystemIO, 32, 0, 0x10551000, 3)},
		ResourceTemplate() {Register(SystemIO, 32, 0, 0x10551004, 3)}
	}) //_PCT
//Performance States
	Name(_PSS, Package() {
		Package() {
			2400,	//frequency MHz
			2500, 	//Power milli watts
			10,	//Latency usec
			10,	//Bus master latency usec
			0x10,	//Control value
			0x20,	//Status value
		}, //P0
		Package() {
			2400,	//frequency MHz
			2500, 	//Power milli watts
			10,	//Latency usec
			10,	//Bus master latency usec
			0x11,	//Control value
			0x21,	//Status value
		}, //P1
		Package() {
			1200,	//frequency MHz
			1500, 	//Power milli watts
			10,	//Latency usec
			10,	//Bus master latency usec
			0x12,	//Control value
			0x22,	//Status value
		}, //P2
		Package() {
			800,	//frequency MHz
			1000, 	//Power milli watts
			10,	//Latency usec
			10,	//Bus master latency usec
			0x13,	//Control value
			0x23,	//Status value
		}, //P3
		Package() {
			600,	//frequency MHz
			800, 	//Power milli watts
			10,	//Latency usec
			10,	//Bus master latency usec
			0x14,	//Control value
			0x24,	//Status value
		} //P4
	}) //_PSS
//Performance State dependency
	Name(_PSD, Package() {
		Package() {5, 0, 0, 0xFC, 2}
	}) //Domain 0

//C states
	Name(_CST, Package() {
		1,
		Package() {	//C1 state
			ResourceTemplate() {Register(SystemMemory, 32, 0, 0x10551014, 3)},
			1,
			0,	//latency usec
			2500	//power mW
		}, //C1 state
/*		Package() {	//C3 state
			ResourceTemplate() {Register(SystemMemory, 32, 0, 0x10551018, 3)},
			3,
			200000,	//latency usec
			1800	//power mW
		}, //C3 state */
	}) //_CST
//C state dependency
	Name(_CSD, Package() {
		Package() {6, 0, 0, 0xFC, 1, 1},
//		Package() {6, 0, 0, 0xFC, 2, 2},
	}) //_CSD

	//Return the MADT table
	//FIXME, need to figure out where to get table location from
	//Method(_MAT) {
	//}

	}//CPU1
////////////////////////////////////////////////////////////////////////////////
//Processor
	Processor(\_SB.CPU2, 2, 0, 0) {

	Name(_UID, 2)
	Name(_HID, "ACPI0007")
        Method(_STA) {
                Return (One)
        }

//Clock Domain Object
	Name(_CDM, 1)	//Domain 1

        Method(_PSC) {
                Return (0)
        } //_PSC

//Sleeping state correlation
	Name(_S1D, 3)
	Name(_S2D, 4)
	Name(_S3D, 6)

//Performance Control
	Name(_PCT, Package() {
		ResourceTemplate() {Register(SystemIO, 32, 0, 0x10552000, 3)},
		ResourceTemplate() {Register(SystemIO, 32, 0, 0x10552004, 3)}
	}) //_PCT
//Performance States
	Name(_PSS, Package() {
		Package() {
			2400,	//frequency MHz
			2500, 	//Power milli watts
			10,	//Latency usec
			10,	//Bus master latency usec
			0x10,	//Control value
			0x20,	//Status value
		}, //P0
		Package() {
			2400,	//frequency MHz
			2500, 	//Power milli watts
			10,	//Latency usec
			10,	//Bus master latency usec
			0x11,	//Control value
			0x21,	//Status value
		}, //P1
		Package() {
			1200,	//frequency MHz
			1500, 	//Power milli watts
			10,	//Latency usec
			10,	//Bus master latency usec
			0x12,	//Control value
			0x22,	//Status value
		}, //P2
		Package() {
			800,	//frequency MHz
			1000, 	//Power milli watts
			10,	//Latency usec
			10,	//Bus master latency usec
			0x13,	//Control value
			0x23,	//Status value
		}, //P3
		Package() {
			600,	//frequency MHz
			800, 	//Power milli watts
			10,	//Latency usec
			10,	//Bus master latency usec
			0x14,	//Control value
			0x24,	//Status value
		} //P4
	}) //_PSS
//Performance State dependency
	Name(_PSD, Package() {
		Package() {5, 0, 1, 0xFC, 2}
	}) //Domain 1

//C states
	Name(_CST, Package() {
		1,
		Package() {	//C1 state
			ResourceTemplate() {Register(SystemMemory, 32, 0, 0x10552014, 3)},
			1,
			0,	//latency usec
			2500	//power mW
		}, //C1 state
/*		Package() {	//C3 state
			ResourceTemplate() {Register(SystemMemory, 32, 0, 0x10552018, 3)},
			3,
			200000,	//latency usec
			1800	//power mW
		}, //C3 state */
	}) //_CST
//C state dependency
	Name(_CSD, Package() {
		Package() {6, 0, 0, 0xFC, 1, 1},
//		Package() {6, 0, 0, 0xFC, 2, 2},
	}) //_CSD

	//Return the MADT table
	//FIXME, need to figure out where to get table location from
	//Method(_MAT) {
	//}

	}//CPU2
////////////////////////////////////////////////////////////////////////////////
//Processor
	Processor(\_SB.CPU3, 3, 0, 0) {

	Name(_UID, 3)
	Name(_HID, "ACPI0007")
        Method(_STA) {
                Return (One)
        }

//Clock Domain Object
	Name(_CDM, 1)	//Domain 1

        Method(_PSC) {
                Return (0)
        } //_PSC

//Sleeping state correlation
	Name(_S1D, 3)
	Name(_S2D, 4)
	Name(_S3D, 6)

//Performance Control
	Name(_PCT, Package() {
		ResourceTemplate() {Register(SystemIO, 32, 0, 0x10553000, 3)},
		ResourceTemplate() {Register(SystemIO, 32, 0, 0x10553004, 3)}
	}) //_PCT
//Performance States
	Name(_PSS, Package() {
		Package() {
			2400,	//frequency MHz
			2500, 	//Power milli watts
			10,	//Latency usec
			10,	//Bus master latency usec
			0x10,	//Control value
			0x20,	//Status value
		}, //P0
		Package() {
			2400,	//frequency MHz
			2500, 	//Power milli watts
			10,	//Latency usec
			10,	//Bus master latency usec
			0x11,	//Control value
			0x21,	//Status value
		}, //P1
		Package() {
			1200,	//frequency MHz
			1500, 	//Power milli watts
			10,	//Latency usec
			10,	//Bus master latency usec
			0x12,	//Control value
			0x22,	//Status value
		}, //P2
		Package() {
			800,	//frequency MHz
			1000, 	//Power milli watts
			10,	//Latency usec
			10,	//Bus master latency usec
			0x13,	//Control value
			0x23,	//Status value
		}, //P3
		Package() {
			600,	//frequency MHz
			800, 	//Power milli watts
			10,	//Latency usec
			10,	//Bus master latency usec
			0x14,	//Control value
			0x24,	//Status value
		} //P4
	}) //_PSS
//Performance State dependency
	Name(_PSD, Package() {
		Package() {5, 0, 1, 0xFC, 2}
	}) //Domain 1

//C states
	Name(_CST, Package() {
		1,
		Package() {	//C1 state
			ResourceTemplate() {Register(SystemMemory, 32, 0, 0x10553014, 3)},
			1,
			0,	//latency usec
			2500	//power mW
		}, //C1 state
/*		Package() {	//C3 state
			ResourceTemplate() {Register(SystemMemory, 32, 0, 0x10553018, 3)},
			3,
			200000,	//latency usec
			1800	//power mW
		}, //C3 state */
	}) //_CST
//C state dependency
	Name(_CSD, Package() {
		Package() {6, 0, 0, 0xFC, 1, 1},
//		Package() {6, 0, 0, 0xFC, 2, 2},
	}) //_CSD

	//Return the MADT table
	//FIXME, need to figure out where to get table location from
	//Method(_MAT) {
	//}

	}//CPU3
////////////////////////////////////////////////////////////////////////////////
//Processor
	Processor(\_SB.CPU4, 4, 0, 0) {

	Name(_UID, 4)
	Name(_HID, "ACPI0007")
        Method(_STA) {
                Return (One)
        }

//Clock Domain Object
	Name(_CDM, 2)	//Domain 2

        Method(_PSC) {
                Return (0)
        } //_PSC

//Sleeping state correlation
	Name(_S1D, 3)
	Name(_S2D, 4)
	Name(_S3D, 6)

//Performance Control
	Name(_PCT, Package() {
		ResourceTemplate() {Register(SystemIO, 32, 0, 0x10554000, 3)},
		ResourceTemplate() {Register(SystemIO, 32, 0, 0x10554004, 3)}
	}) //_PCT
//Performance States
	Name(_PSS, Package() {
		Package() {
			2400,	//frequency MHz
			2500, 	//Power milli watts
			10,	//Latency usec
			10,	//Bus master latency usec
			0x10,	//Control value
			0x20,	//Status value
		}, //P0
		Package() {
			2400,	//frequency MHz
			2500, 	//Power milli watts
			10,	//Latency usec
			10,	//Bus master latency usec
			0x11,	//Control value
			0x21,	//Status value
		}, //P1
		Package() {
			1200,	//frequency MHz
			1500, 	//Power milli watts
			10,	//Latency usec
			10,	//Bus master latency usec
			0x12,	//Control value
			0x22,	//Status value
		}, //P2
		Package() {
			800,	//frequency MHz
			1000, 	//Power milli watts
			10,	//Latency usec
			10,	//Bus master latency usec
			0x13,	//Control value
			0x23,	//Status value
		}, //P3
		Package() {
			600,	//frequency MHz
			800, 	//Power milli watts
			10,	//Latency usec
			10,	//Bus master latency usec
			0x14,	//Control value
			0x24,	//Status value
		} //P4
	}) //_PSS
//Performance State dependency
	Name(_PSD, Package() {
		Package() {5, 0, 2, 0xFC, 2}
	}) //Domain 2

//C states
	Name(_CST, Package() {
		1,
		Package() {	//C1 state
			ResourceTemplate() {Register(SystemMemory, 32, 0, 0x10554014, 3)},
			1,
			0,	//latency usec
			2500	//power mW
		}, //C1 state
/*		Package() {	//C3 state
			ResourceTemplate() {Register(SystemMemory, 32, 0, 0x10554018, 3)},
			3,
			200000,	//latency usec
			1800	//power mW
		}, //C3 state */
	}) //_CST
//C state dependency
	Name(_CSD, Package() {
		Package() {6, 0, 0, 0xFC, 1, 1},
//		Package() {6, 0, 0, 0xFC, 2, 2},
	}) //_CSD

	//Return the MADT table
	//FIXME, need to figure out where to get table location from
	//Method(_MAT) {
	//}

	}//CPU4
////////////////////////////////////////////////////////////////////////////////
//Processor
	Processor(\_SB.CPU5, 5, 0, 0) {

	Name(_UID, 5)
	Name(_HID, "ACPI0007")
        Method(_STA) {
                Return (One)
        }

//Clock Domain Object
	Name(_CDM, 2)	//Domain 2

        Method(_PSC) {
                Return (0)
        } //_PSC

//Sleeping state correlation
	Name(_S1D, 3)
	Name(_S2D, 4)
	Name(_S3D, 6)

//Performance Control
	Name(_PCT, Package() {
		ResourceTemplate() {Register(SystemIO, 32, 0, 0x10555000, 3)},
		ResourceTemplate() {Register(SystemIO, 32, 0, 0x10555004, 3)}
	}) //_PCT
//Performance States
	Name(_PSS, Package() {
		Package() {
			2400,	//frequency MHz
			2500, 	//Power milli watts
			10,	//Latency usec
			10,	//Bus master latency usec
			0x10,	//Control value
			0x20,	//Status value
		}, //P0
		Package() {
			2400,	//frequency MHz
			2500, 	//Power milli watts
			10,	//Latency usec
			10,	//Bus master latency usec
			0x11,	//Control value
			0x21,	//Status value
		}, //P1
		Package() {
			1200,	//frequency MHz
			1500, 	//Power milli watts
			10,	//Latency usec
			10,	//Bus master latency usec
			0x12,	//Control value
			0x22,	//Status value
		}, //P2
		Package() {
			800,	//frequency MHz
			1000, 	//Power milli watts
			10,	//Latency usec
			10,	//Bus master latency usec
			0x13,	//Control value
			0x23,	//Status value
		}, //P3
		Package() {
			600,	//frequency MHz
			800, 	//Power milli watts
			10,	//Latency usec
			10,	//Bus master latency usec
			0x14,	//Control value
			0x24,	//Status value
		} //P4
	}) //_PSS
//Performance State dependency
	Name(_PSD, Package() {
		Package() {5, 0, 2, 0xFC, 2}
	}) //Domain 2

//C states
	Name(_CST, Package() {
		1,
		Package() {	//C1 state
			ResourceTemplate() {Register(SystemMemory, 32, 0, 0x10555014, 3)},
			1,
			0,	//latency usec
			2500	//power mW
		}, //C1 state
/*		Package() {	//C3 state
			ResourceTemplate() {Register(SystemMemory, 32, 0, 0x10555018, 3)},
			3,
			200000,	//latency usec
			1800	//power mW
		}, //C3 state */
	}) //_CST
//C state dependency
	Name(_CSD, Package() {
		Package() {6, 0, 0, 0xFC, 1, 1},
//		Package() {6, 0, 0, 0xFC, 2, 2},
	}) //_CSD

	//Return the MADT table
	//FIXME, need to figure out where to get table location from
	//Method(_MAT) {
	//}

	}//CPU5
////////////////////////////////////////////////////////////////////////////////
//Processor
	Processor(\_SB.CPU6, 6, 0, 0) {

	Name(_UID, 6)
	Name(_HID, "ACPI0007")
        Method(_STA) {
                Return (One)
        }

//Clock Domain Object
	Name(_CDM, 3)	//Domain 3

        Method(_PSC) {
                Return (0)
        } //_PSC

//Sleeping state correlation
	Name(_S1D, 3)
	Name(_S2D, 4)
	Name(_S3D, 6)

//Performance Control
	Name(_PCT, Package() {
		ResourceTemplate() {Register(SystemIO, 32, 0, 0x10556000, 3)},
		ResourceTemplate() {Register(SystemIO, 32, 0, 0x10556004, 3)}
	}) //_PCT
//Performance States
	Name(_PSS, Package() {
		Package() {
			2400,	//frequency MHz
			2500, 	//Power milli watts
			10,	//Latency usec
			10,	//Bus master latency usec
			0x10,	//Control value
			0x20,	//Status value
		}, //P0
		Package() {
			2400,	//frequency MHz
			2500, 	//Power milli watts
			10,	//Latency usec
			10,	//Bus master latency usec
			0x11,	//Control value
			0x21,	//Status value
		}, //P1
		Package() {
			1200,	//frequency MHz
			1500, 	//Power milli watts
			10,	//Latency usec
			10,	//Bus master latency usec
			0x12,	//Control value
			0x22,	//Status value
		}, //P2
		Package() {
			800,	//frequency MHz
			1000, 	//Power milli watts
			10,	//Latency usec
			10,	//Bus master latency usec
			0x13,	//Control value
			0x23,	//Status value
		}, //P3
		Package() {
			600,	//frequency MHz
			800, 	//Power milli watts
			10,	//Latency usec
			10,	//Bus master latency usec
			0x14,	//Control value
			0x24,	//Status value
		} //P4
	}) //_PSS
//Performance State dependency
	Name(_PSD, Package() {
		Package() {5, 0, 3, 0xFC, 2}
	}) //Domain 3

//C states
	Name(_CST, Package() {
		1,
		Package() {	//C1 state
			ResourceTemplate() {Register(SystemMemory, 32, 0, 0x10556014, 3)},
			1,
			0,	//latency usec
			2500	//power mW
		}, //C1 state
/*		Package() {	//C3 state
			ResourceTemplate() {Register(SystemMemory, 32, 0, 0x10556018, 3)},
			3,
			200000,	//latency usec
			1800	//power mW
		}, //C3 state */
	}) //_CST
//C state dependency
	Name(_CSD, Package() {
		Package() {6, 0, 0, 0xFC, 1, 1},
//		Package() {6, 0, 0, 0xFC, 2, 2},
	}) //_CSD

	//Return the MADT table
	//FIXME, need to figure out where to get table location from
	//Method(_MAT) {
	//}

	}//CPU6
////////////////////////////////////////////////////////////////////////////////
//Processor
	Processor(\_SB.CPU7, 7, 0, 0) {

	Name(_UID, 7)
	Name(_HID, "ACPI0007")
        Method(_STA) {
                Return (One)
        }

//Clock Domain Object
	Name(_CDM, 3)	//Domain 3

        Method(_PSC) {
                Return (0)
        } //_PSC

//Sleeping state correlation
	Name(_S1D, 3)
	Name(_S2D, 4)
	Name(_S3D, 6)

//Performance Control
	Name(_PCT, Package() {
		ResourceTemplate() {Register(SystemIO, 32, 0, 0x10557000, 3)},
		ResourceTemplate() {Register(SystemIO, 32, 0, 0x10557004, 3)}
	}) //_PCT
//Performance States
	Name(_PSS, Package() {
		Package() {
			2400,	//frequency MHz
			2500, 	//Power milli watts
			10,	//Latency usec
			10,	//Bus master latency usec
			0x10,	//Control value
			0x20,	//Status value
		}, //P0
		Package() {
			2400,	//frequency MHz
			2500, 	//Power milli watts
			10,	//Latency usec
			10,	//Bus master latency usec
			0x11,	//Control value
			0x21,	//Status value
		}, //P1
		Package() {
			1200,	//frequency MHz
			1500, 	//Power milli watts
			10,	//Latency usec
			10,	//Bus master latency usec
			0x12,	//Control value
			0x22,	//Status value
		}, //P2
		Package() {
			800,	//frequency MHz
			1000, 	//Power milli watts
			10,	//Latency usec
			10,	//Bus master latency usec
			0x13,	//Control value
			0x23,	//Status value
		}, //P3
		Package() {
			600,	//frequency MHz
			800, 	//Power milli watts
			10,	//Latency usec
			10,	//Bus master latency usec
			0x14,	//Control value
			0x24,	//Status value
		} //P4
	}) //_PSS
//Performance State dependency
	Name(_PSD, Package() {
		Package() {5, 0, 3, 0xFC, 2}
	}) //Domain 3

//C states
	Name(_CST, Package() {
		1,
		Package() {	//C1 state
			ResourceTemplate() {Register(SystemMemory, 32, 0, 0x10557014, 3)},
			1,
			0,	//latency usec
			2500	//power mW
		}, //C1 state
/*		Package() {	//C3 state
			ResourceTemplate() {Register(SystemMemory, 32, 0, 0x10557018, 3)},
			3,
			200000,	//latency usec
			1800	//power mW
		}, //C3 state */
	}) //_CST
//C state dependency
	Name(_CSD, Package() {
		Package() {6, 0, 0, 0xFC, 1, 1},
//		Package() {6, 0, 0, 0xFC, 2, 2},
	}) //_CSD

	//Return the MADT table
	//FIXME, need to figure out where to get table location from
	//Method(_MAT) {
	//}

	}//CPU7

///////////////////////////////////////////////////////////////////////////////
// PMU
	Device(PMU0) {
		Name(_HID, "APMC0D0C") // Device Identification Objects
		Name(_DDN, "PMU0")
		Name(_UID, "PMU0")
		Name(_STR, Unicode("PMU"))
		Name(_CID, "APMC0D0C")
		Name(_CRS, ResourceTemplate() {
			Interrupt(ResourceProducer, Level, ActiveHigh, Exclusive) { 0x0C, 0x1 }
		})
	} //PMU

////////////////////////////////////////////////////////////////////////////////
// SoC Clock
	Device(CK00) {
		Name(_HID, "APMC0C00")
		Name(_CID, 0x00)
		Name(_STR, Unicode("Reference Clock"))
		Name(_UID, "refclk")	// clock-name
		Name(CLNM, "refclk")	// clock-name
		Name(FREQ, 100000000)	// clock-frequency
	}
	Device(CK01) {
		Name(_HID, "APMC0C02")
		Name(_CID, 0x00)
		Name(_STR, Unicode("PCP PLL Clock"))
		Name(MM0A, 0x17000100)	// MMIO 0 Address
		Name(MM0S, 0x20)	// MMIO 0 Size
		Name(_UID, "pcppll")	// clock-name
		Name(CLNM, "pcppll")	// clock-name
		Name(PRNT, "refclk")	// parent-clock
	}
	Device(CK02) {
		Name(_HID, "APMC0C03")
		Name(_CID, 0x00)
		Name(_STR, Unicode("SOC PLL Clock"))
		Name(MM0A, 0x17000120)	// MMIO 0 Address
		Name(MM0S, 0x20)	// MMIO 0 Size
		Name(_UID, "socpll")	// clock-name
		Name(CLNM, "socpll")	// clock-name
		Name(PRNT, "refclk")	// parent-clock
	}
	Device(CK03) {
		Name(_HID, "APMC0C01")
		Name(_CID, 0x00)
		Name(_STR, Unicode("SOC PLL DIV2"))
		Name(_UID, "socplldiv2")// clock-name
		Name(CLNM, "socplldiv2")// clock-name
		Name(PRNT, "socpll")	// parent-clock
		Name(CMUL, 0x1)		// clock-mult
		Name(CDIV, 0x2)		// clock-div
	}
	Device(CK04) {
		Name(_HID, "APMC0C04")
		Name(_CID, 0x00)
		Name(_STR, Unicode("QM Lite Clock"))
		Name(MM0A, 0x1703C000)	// MMIO 0 Address
		Name(MM0S, 0x1000)	// MMIO 0 Size
		Name(MM1A, 0x00000000)	// MMIO 1 Address
		Name(MM1S, 0x0)		// MMIO 1 Size
		Name(_UID, "qmlclk")	// clock-name
		Name(CLNM, "qmlclk")	// clock-name
		Name(PRNT, "socplldiv2")// parent-clock
	}
	Device(CK05) {
		Name(_HID, "APMC0C04")
		Name(_CID, 0x01)
		Name(_STR, Unicode("Ethernet Clock"))
		Name(MM0A, 0x00000000)	// MMIO 0 Address
		Name(MM0S, 0x0)		// MMIO 0 Size
		Name(MM1A, 0x17000000)	// MMIO 1 Address
		Name(MM1S, 0x1000)	// MMIO 1 Size
		Name(_UID, "ethclk")	// clock-name
		Name(CLNM, "ethclk")	// clock-name
		Name(PRNT, "socplldiv2")// parent-clock
		Name(DIVO, 0x238)	// divider-offset
		Name(DIVW, 0x9)		// divider-width
		Name(DIVS, 0x0)		// divider-shift
	}
	Device(CK06) {
		Name(_HID, "APMC0C04")
		Name(_CID, 0x02)
		Name(_STR, Unicode("ETH8 Clock"))
		Name(MM0A, 0x1702C000)	// MMIO 0 Address
		Name(MM0S, 0x1000)	// MMIO 0 Size
		Name(MM1A, 0x00000000)	// MMIO 1 Address
		Name(MM1S, 0x0)		// MMIO 1 Size
		Name(_UID, "eth8clk")	// clock-name
		Name(CLNM, "eth8clk")	// clock-name
		Name(PRNT, "ethclk")	// parent-clock
	}
	Device(CK07) {
		Name(_HID, "APMC0C04")
		Name(_CID, 0x03)
		Name(_STR, Unicode("QM1 Clock"))
		Name(MM0A, 0x1F20C000)	// MMIO 0 Address
		Name(MM0S, 0x1000)	// MMIO 0 Size
		Name(MM1A, 0x00000000)	// MMIO 1 Address
		Name(MM1S, 0x0)		// MMIO 1 Size
		Name(_UID, "qm1clk")	// clock-name
		Name(CLNM, "qm1clk")	// clock-name
		Name(PRNT, "socplldiv2")// parent-clock
	}
	Device(CK08) {
		Name(_HID, "APMC0C04")
		Name(_CID, 0x04)
		Name(_STR, Unicode("ETH01 Clock"))
		Name(MM0A, 0x1F21C000)	// MMIO 0 Address
		Name(MM0S, 0x1000)	// MMIO 0 Size
		Name(MM1A, 0x00000000)	// MMIO 1 Address
		Name(MM1S, 0x0)		// MMIO 1 Size
		Name(_UID, "eth01clk")	// clock-name
		Name(CLNM, "eth01clk")	// clock-name
		Name(PRNT, "socplldiv2")// parent-clock
	}
	Device(CK09) {
		Name(_HID, "APMC0C04")
		Name(_CID, 0x05)
		Name(_STR, Unicode("ETH23 Clock"))
		Name(MM0A, 0x1F22C000)	// MMIO 0 Address
		Name(MM0S, 0x1000)	// MMIO 0 Size
		Name(MM1A, 0x00000000)	// MMIO 1 Address
		Name(MM1S, 0x0)		// MMIO 1 Size
		Name(_UID, "eth23clk")	// clock-name
		Name(CLNM, "eth23clk")	// clock-name
		Name(PRNT, "socplldiv2")// parent-clock
	}
	Device(CK0A) {
		Name(_HID, "APMC0C04")
		Name(_CID, 0x06)
		Name(_STR, Unicode("QM XGE0 Clock"))
		Name(MM0A, 0x1F60C000)	// MMIO 0 Address
		Name(MM0S, 0x1000)	// MMIO 0 Size
		Name(MM1A, 0x00000000)	// MMIO 1 Address
		Name(MM1S, 0x0)		// MMIO 1 Size
		Name(_UID, "qmxge0clk")	// clock-name
		Name(CLNM, "qmxge0clk")	// clock-name
		Name(PRNT, "socplldiv2")// parent-clock
	}
	Device(CK0B) {
		Name(_HID, "APMC0C04")
		Name(_CID, 0x07)
		Name(_STR, Unicode("XGE0 Clock"))
		Name(MM0A, 0x1F61C000)	// MMIO 0 Address
		Name(MM0S, 0x1000)	// MMIO 0 Size
		Name(MM1A, 0x00000000)	// MMIO 1 Address
		Name(MM1S, 0x0)		// MMIO 1 Size
		Name(_UID, "xge0clk")	// clock-name
		Name(CLNM, "xge0clk")	// clock-name
		Name(PRNT, "socplldiv2")// parent-clock
	}
	Device(CK0C) {
		Name(_HID, "APMC0C04")
		Name(_CID, 0x08)
		Name(_STR, Unicode("XGE1 Clock"))
		Name(MM0A, 0x1F62C000)	// MMIO 0 Address
		Name(MM0S, 0x1000)	// MMIO 0 Size
		Name(MM1A, 0x00000000)	// MMIO 1 Address
		Name(MM1S, 0x0)		// MMIO 1 Size
		Name(_UID, "xge1clk")	// clock-name
		Name(CLNM, "xge1clk")	// clock-name
		Name(PRNT, "socplldiv2")// parent-clock
	}
	Device(CK0D) {
		Name(_HID, "APMC0C04")
		Name(_CID, 0x09)
		Name(_STR, Unicode("QM XGE1 Clock"))
		Name(MM0A, 0x1F70C000)	// MMIO 0 Address
		Name(MM0S, 0x1000)	// MMIO 0 Size
		Name(MM1A, 0x00000000)	// MMIO 1 Address
		Name(MM1S, 0x0)		// MMIO 1 Size
		Name(_UID, "qmxge1clk")	// clock-name
		Name(CLNM, "qmxge1clk")	// clock-name
		Name(PRNT, "socplldiv2")// parent-clock
	}
	Device(CK0E) {
		Name(_HID, "APMC0C04")
		Name(_CID, 0x0A)
		Name(_STR, Unicode("XGE2 Clock"))
		Name(MM0A, 0x1F71C000)	// MMIO 0 Address
		Name(MM0S, 0x1000)	// MMIO 0 Size
		Name(MM1A, 0x00000000)	// MMIO 1 Address
		Name(MM1S, 0x0)		// MMIO 1 Size
		Name(_UID, "xge2clk")	// clock-name
		Name(CLNM, "xge2clk")	// clock-name
		Name(PRNT, "socplldiv2")// parent-clock
	}
	Device(CK0F) {
		Name(_HID, "APMC0C04")
		Name(_CID, 0x0B)
		Name(_STR, Unicode("XGE3 Clock"))
		Name(MM0A, 0x1F72C000)	// MMIO 0 Address
		Name(MM0S, 0x1000)	// MMIO 0 Size
		Name(MM1A, 0x00000000)	// MMIO 1 Address
		Name(MM1S, 0x0)		// MMIO 1 Size
		Name(_UID, "xge3clk")	// clock-name
		Name(CLNM, "xge3clk")	// clock-name
		Name(PRNT, "socplldiv2")// parent-clock
	}
	Device(CK10) {
		Name(_HID, "APMC0C04")
		Name(_CID, 0x0C)
		Name(_STR, Unicode("PCIE0 Clock"))
		Name(MM0A, 0x1F2BC000)	// MMIO 0 Address
		Name(MM0S, 0x1000)	// MMIO 0 Size
		Name(MM1A, 0x00000000)	// MMIO 1 Address
		Name(MM1S, 0x0)		// MMIO 1 Size
		Name(_UID, "pcie0clk")	// clock-name
		Name(CLNM, "pcie0clk")	// clock-name
		Name(PRNT, "socplldiv2")// parent-clock
		Name(EMSK, 0x0)		// enable-mask
	}
	Device(CK11) {
		Name(_HID, "APMC0C04")
		Name(_CID, 0x0D)
		Name(_STR, Unicode("PCIE1 Clock"))
		Name(MM0A, 0x1F2CC000)	// MMIO 0 Address
		Name(MM0S, 0x1000)	// MMIO 0 Size
		Name(MM1A, 0x00000000)	// MMIO 1 Address
		Name(MM1S, 0x0)		// MMIO 1 Size
		Name(_UID, "pcie1clk")	// clock-name
		Name(CLNM, "pcie1clk")	// clock-name
		Name(PRNT, "socplldiv2")// parent-clock
		Name(EMSK, 0x0)		// enable-mask
	}
	Device(CK12) {
		Name(_HID, "APMC0C04")
		Name(_CID, 0x0E)
		Name(_STR, Unicode("PCIE2 Clock"))
		Name(MM0A, 0x1F2DC000)	// MMIO 0 Address
		Name(MM0S, 0x1000)	// MMIO 0 Size
		Name(MM1A, 0x00000000)	// MMIO 1 Address
		Name(MM1S, 0x0)		// MMIO 1 Size
		Name(_UID, "pcie2clk")	// clock-name
		Name(CLNM, "pcie2clk")	// clock-name
		Name(PRNT, "socplldiv2")// parent-clock
		Name(EMSK, 0x0)		// enable-mask
	}
	Device(CK13) {
		Name(_HID, "APMC0C04")
		Name(_CID, 0x0F)
		Name(_STR, Unicode("PCIE3 Clock"))
		Name(MM0A, 0x1F50C000)	// MMIO 0 Address
		Name(MM0S, 0x1000)	// MMIO 0 Size
		Name(MM1A, 0x00000000)	// MMIO 1 Address
		Name(MM1S, 0x0)		// MMIO 1 Size
		Name(_UID, "pcie3clk")	// clock-name
		Name(CLNM, "pcie3clk")	// clock-name
		Name(PRNT, "socplldiv2")// parent-clock
		Name(EMSK, 0x0)		// enable-mask
	}
	Device(CK14) {
		Name(_HID, "APMC0C04")
		Name(_CID, 0x10)
		Name(_STR, Unicode("PCIE4 Clock"))
		Name(MM0A, 0x1F51C000)	// MMIO 0 Address
		Name(MM0S, 0x1000)	// MMIO 0 Size
		Name(MM1A, 0x00000000)	// MMIO 1 Address
		Name(MM1S, 0x0)		// MMIO 1 Size
		Name(_UID, "pcie4clk")	// clock-name
		Name(CLNM, "pcie4clk")	// clock-name
		Name(PRNT, "socplldiv2")// parent-clock
		Name(EMSK, 0x0)		// enable-mask
	}
	Device(CK16) {
		Name(_HID, "APMC0C04")
		Name(_CID, 0x11)
		Name(_STR, Unicode("USB0 Clock"))
		Name(MM0A, 0x1F28C000)	// MMIO 0 Address
		Name(MM0S, 0x1000)	// MMIO 0 Size
		Name(MM1A, 0x00000000)	// MMIO 1 Address
		Name(MM1S, 0x0)		// MMIO 1 Size
		Name(_UID, "usb0clk")	// clock-name
		Name(CLNM, "usb0clk")	// clock-name
		Name(PRNT, "socplldiv2")// parent-clock
	}
	Device(CK17) {
		Name(_HID, "APMC0C04")
		Name(_CID, 0x12)
		Name(_STR, Unicode("USB1 Clock"))
		Name(MM0A, 0x1F29C000)	// MMIO 0 Address
		Name(MM0S, 0x1000)	// MMIO 0 Size
		Name(MM1A, 0x00000000)	// MMIO 1 Address
		Name(MM1S, 0x0)		// MMIO 1 Size
		Name(_UID, "usb1clk")	// clock-name
		Name(CLNM, "usb1clk")	// clock-name
		Name(PRNT, "socplldiv2")// parent-clock
	}
	Device(CK18) {
		Name(_HID, "APMC0C04")
		Name(_CID, 0x13)
		Name(_STR, Unicode("Packet DMA Clock"))
		Name(MM0A, 0x1F27C000)	// MMIO 0 Address
		Name(MM0S, 0x1000)	// MMIO 0 Size
		Name(MM1A, 0x00000000)	// MMIO 1 Address
		Name(MM1S, 0x0)		// MMIO 1 Size
		Name(_UID, "pktdmaclk")	// clock-name
		Name(CLNM, "pktdmaclk")	// clock-name
		Name(PRNT, "socplldiv2")// parent-clock
	}
	Device(CK19) {
		Name(_HID, "APMC0C04")
		Name(_CID, 0x14)
		Name(_STR, Unicode("AHB Clock"))
		Name(MM0A, 0x1F2AC000)	// MMIO 0 Address
		Name(MM0S, 0x1000)	// MMIO 0 Size
		Name(MM1A, 0x17000000)	// MMIO 1 Address
		Name(MM1S, 0x1000)	// MMIO 1 Size
		Name(_UID, "ahbclk")	// clock-name
		Name(CLNM, "ahbclk")	// clock-name
		Name(PRNT, "socplldiv2")// parent-clock
		Name(CSRO, 0x0)		// csr-offset
		Name(CSRM, 0x1)		// csr-mask
		Name(EOFF, 0x8)		// enable-offset
		Name(EMSK, 0x1)		// enable-mask
		Name(DIVO, 0x164)	// divider-offset
		Name(DIVW, 0x5)		// divider-width
		Name(DIVS, 0x0)		// divider-shift
	}
	Device(CK1A) {
		Name(_HID, "APMC0C04")
		Name(_CID, 0x15)
		Name(_STR, Unicode("APB Clock"))
		Name(MM0A, 0x1F2AC000)	// MMIO 0 Address
		Name(MM0S, 0x1000)	// MMIO 0 Size
		Name(MM1A, 0x1F2AC000)	// MMIO 1 Address
		Name(MM1S, 0x1000)	// MMIO 1 Size
		Name(_UID, "apbclk")	// clock-name
		Name(CLNM, "apbclk")	// clock-name
		Name(PRNT, "ahbclk")	// parent-clock
		Name(CSRO, 0x0)		// csr-offset
		Name(CSRM, 0x200)	// csr-mask
		Name(EOFF, 0x8)		// enable-offset
		Name(EMSK, 0x200)	// enable-mask
		Name(DIVO, 0x10)	// divider-offset
		Name(DIVW, 0x2)		// divider-width
		Name(DIVS, 0x0)		// divider-shift
	}
	Device(CK1B) {
		Name(_HID, "APMC0C04")
		Name(_CID, 0x16)
		Name(_STR, Unicode("SPI0 Clock"))
		Name(MM0A, 0x1F2AC000)	// MMIO 0 Address
		Name(MM0S, 0x1000)	// MMIO 0 Size
		Name(MM1A, 0x00000000)	// MMIO 1 Address
		Name(MM1S, 0x0)		// MMIO 1 Size
		Name(_UID, "spi0clk")	// clock-name
		Name(CLNM, "spi0clk")	// clock-name
		Name(PRNT, "apbclk")	// parent-clock
		Name(CSRO, 0x0)		// csr-offset
		Name(CSRM, 0x100)	// csr-mask
		Name(EOFF, 0x8)		// enable-offset
		Name(EMSK, 0x100)	// enable-mask
	}
	Device(CK1C) {
		Name(_HID, "APMC0C04")
		Name(_CID, 0x17)
		Name(_STR, Unicode("SPI1 Clock"))
		Name(MM0A, 0x1F2AC000)	// MMIO 0 Address
		Name(MM0S, 0x1000)	// MMIO 0 Size
		Name(MM1A, 0x00000000)	// MMIO 1 Address
		Name(MM1S, 0x0)		// MMIO 1 Size
		Name(_UID, "spi1clk")	// clock-name
		Name(CLNM, "spi1clk")	// clock-name
		Name(PRNT, "apbclk")	// parent-clock
		Name(CSRO, 0x0)		// csr-offset
		Name(CSRM, 0x80)	// csr-mask
		Name(EOFF, 0x8)		// enable-offset
		Name(EMSK, 0x80)	// enable-mask
	}
	Device(CK1D) {
		Name(_HID, "APMC0C04")
		Name(_CID, 0x18)
		Name(_STR, Unicode("SDIO Clock"))
		Name(MM0A, 0x1F2AC000)	// MMIO 0 Address
		Name(MM0S, 0x1000)	// MMIO 0 Size
		Name(MM1A, 0x17000000)	// MMIO 1 Address
		Name(MM1S, 0x1000)	// MMIO 1 Size
		Name(_UID, "sdioclk")	// clock-name
		Name(CLNM, "sdioclk")	// clock-name
		Name(PRNT, "socplldiv2")// parent-clock
		Name(CSRO, 0x0)		// csr-offset
		Name(CSRM, 0x2)		// csr-mask
		Name(EOFF, 0x8)		// enable-offset
		Name(EMSK, 0x2)		// enable-mask
		Name(DIVO, 0x178)	// divider-offset
		Name(DIVW, 0x8)		// divider-width
		Name(DIVS, 0x0)		// divider-shift
	}
	Device(CK1E) {
		Name(_HID, "APMC0C04")
		Name(_CID, 0x19)
		Name(_STR, Unicode("UART0 Clock"))
		Name(MM0A, 0x1F2AC000)	// MMIO 0 Address
		Name(MM0S, 0x1000)	// MMIO 0 Size
		Name(MM1A, 0x00000000)	// MMIO 1 Address
		Name(MM1S, 0x0)		// MMIO 1 Size
		Name(_UID, "uart0clk")	// clock-name
		Name(CLNM, "uart0clk")	// clock-name
		Name(PRNT, "ahbclk")	// parent-clock
		Name(CSRO, 0x0)		// csr-offset
		Name(CSRM, 0x8)		// csr-mask
		Name(EOFF, 0x8)		// enable-offset
		Name(EMSK, 0x8)		// enable-mask
	}
	Device(CK1F) {
		Name(_HID, "APMC0C04")
		Name(_CID, 0x1A)
		Name(_STR, Unicode("UART1 Clock"))
		Name(MM0A, 0x1F2AC000)	// MMIO 0 Address
		Name(MM0S, 0x1000)	// MMIO 0 Size
		Name(MM1A, 0x00000000)	// MMIO 1 Address
		Name(MM1S, 0x0)		// MMIO 1 Size
		Name(_UID, "uart1clk")	// clock-name
		Name(CLNM, "uart1clk")	// clock-name
		Name(PRNT, "ahbclk")	// parent-clock
		Name(CSRO, 0x0)		// csr-offset
		Name(CSRM, 0x10)	// csr-mask
		Name(EOFF, 0x8)		// enable-offset
		Name(EMSK, 0x10)	// enable-mask
	}
	Device(CK20) {
		Name(_HID, "APMC0C04")
		Name(_CID, 0x1B)
		Name(_STR, Unicode("UART2 Clock"))
		Name(MM0A, 0x1F2AC000)	// MMIO 0 Address
		Name(MM0S, 0x1000)	// MMIO 0 Size
		Name(MM1A, 0x00000000)	// MMIO 1 Address
		Name(MM1S, 0x0)		// MMIO 1 Size
		Name(_UID, "uart2clk")	// clock-name
		Name(CLNM, "uart2clk")	// clock-name
		Name(PRNT, "ahbclk")	// parent-clock
		Name(CSRO, 0x0)		// csr-offset
		Name(CSRM, 0x20)	// csr-mask
		Name(EOFF, 0x8)		// enable-offset
		Name(EMSK, 0x20)	// enable-mask
	}
	Device(CK21) {
		Name(_HID, "APMC0C04")
		Name(_CID, 0x1C)
		Name(_STR, Unicode("UART3 Clock"))
		Name(MM0A, 0x1F2AC000)	// MMIO 0 Address
		Name(MM0S, 0x1000)	// MMIO 0 Size
		Name(MM1A, 0x00000000)	// MMIO 1 Address
		Name(MM1S, 0x0)		// MMIO 1 Size
		Name(_UID, "uart3clk")	// clock-name
		Name(CLNM, "uart3clk")	// clock-name
		Name(PRNT, "ahbclk")	// parent-clock
		Name(CSRO, 0x0)		// csr-offset
		Name(CSRM, 0x40)	// csr-mask
		Name(EOFF, 0x8)		// enable-offset
		Name(EMSK, 0x40)	// enable-mask
	}
	Device(CK22) {
		Name(_HID, "APMC0C04")
		Name(_CID, 0x1D)
		Name(_STR, Unicode("GPIO Clock"))
		Name(MM0A, 0x1F2AC000)	// MMIO 0 Address
		Name(MM0S, 0x1000)	// MMIO 0 Size
		Name(MM1A, 0x00000000)	// MMIO 1 Address
		Name(MM1S, 0x0)		// MMIO 1 Size
		Name(_UID, "gpioclk")	// clock-name
		Name(CLNM, "gpioclk")	// clock-name
		Name(PRNT, "ahbclk")	// parent-clock
		Name(CSRO, 0x0)		// csr-offset
		Name(CSRM, 0x4)		// csr-mask
		Name(EOFF, 0x8)		// enable-offset
		Name(EMSK, 0x4)		// enable-mask
	}
	Device(CK23) {
		Name(_HID, "APMC0C04")
		Name(_CID, 0x1E)
		Name(_STR, Unicode("I2C Clock"))
		Name(MM0A, 0x17000000)	// MMIO 0 Address
		Name(MM0S, 0x1000)	// MMIO 0 Size
		Name(MM1A, 0x00000000)	// MMIO 1 Address
		Name(MM1S, 0x0)		// MMIO 1 Size
		Name(_UID, "i2cclk")	// clock-name
		Name(CLNM, "i2cclk")	// clock-name
		Name(PRNT, "socplldiv2")// parent-clock
		Name(CSRO, 0x0)		// csr-offset
		Name(CSRM, 0x2)		// csr-mask
		Name(EOFF, 0x10)	// enable-offset
		Name(EMSK, 0x4)		// enable-mask
		Name(DIVO, 0x168)	// divider-offset
		Name(DIVW, 0x5)		// divider-width
		Name(DIVS, 0x0)		// divider-shift
	}
	Device(CK24) {
		Name(_HID, "APMC0C04")
		Name(_CID, 0x1F)
		Name(_STR, Unicode("RTC Clock"))
		Name(MM0A, 0x17000000)	// MMIO 0 Address
		Name(MM0S, 0x1000)	// MMIO 0 Size
		Name(MM1A, 0x00000000)	// MMIO 1 Address
		Name(MM1S, 0x0)		// MMIO 1 Size
		Name(_UID, "rtcclk")	// clock-name
		Name(CLNM, "rtcclk")	// clock-name
		Name(PRNT, "socplldiv2")// parent-clock
		Name(CSRO, 0xc)		// csr-offset
		Name(CSRM, 0x2)		// csr-mask
		Name(EOFF, 0x10)	// enable-offset
		Name(EMSK, 0x2)		// enable-mask
	}
	Device(CK25) {
		Name(_HID, "APMC0C04")
		Name(_CID, 0x20)
		Name(_STR, Unicode("TRNG PKA Clock"))
		Name(MM0A, 0x17000000)	// MMIO 0 Address
		Name(MM0S, 0x1000)	// MMIO 0 Size
		Name(MM1A, 0x00000000)	// MMIO 1 Address
		Name(MM1S, 0x0)		// MMIO 1 Size
		Name(_UID, "trngpkaclk")// clock-name
		Name(CLNM, "trngpkaclk")// clock-name
		Name(PRNT, "socplldiv2")// parent-clock
		Name(CSRO, 0xc)		// csr-offset
		Name(CSRM, 0x10)	// csr-mask
		Name(EOFF, 0x10)	// enable-offset
		Name(EMSK, 0x10)	// enable-mask
	}
	Device(CK26) {
		Name(_HID, "APMC0C04")
		Name(_CID, 0x21)
		Name(_STR, Unicode("SATA01 PHY Clock"))
		Name(MM0A, 0x1F21C000)	// MMIO 0 Address
		Name(MM0S, 0x1000)	// MMIO 0 Size
		Name(MM1A, 0x00000000)	// MMIO 1 Address
		Name(MM1S, 0x0)		// MMIO 1 Size
		Name(_UID, "sataphy1clk")	// clock-name
		Name(CLNM, "sataphy1clk")	// clock-name
		Name(PRNT, "socplldiv2")// parent-clock
		Name(CSRO, 0x4)		// csr-offset
		Name(CSRM, 0x3A)	// csr-mask
		Name(EOFF, 0x00)	// enable-offset
		Name(EMSK, 0x06)	// enable-mask
	}
	Device(CK27) {
		Name(_HID, "APMC0C04")
		Name(_CID, 0x22)
		Name(_STR, Unicode("SATA23 PHY Clock"))
		Name(MM0A, 0x1F22C000)	// MMIO 0 Address
		Name(MM0S, 0x1000)	// MMIO 0 Size
		Name(MM1A, 0x00000000)	// MMIO 1 Address
		Name(MM1S, 0x0)		// MMIO 1 Size
		Name(_UID, "sataphy2clk")	// clock-name
		Name(CLNM, "sataphy2clk")	// clock-name
		Name(PRNT, "socplldiv2")// parent-clock
		Name(CSRO, 0x4)		// csr-offset
		Name(CSRM, 0x3A)	// csr-mask
		Name(EOFF, 0x00)	// enable-offset
		Name(EMSK, 0x06)	// enable-mask
	}
	Device(CK28) {
		Name(_HID, "APMC0C04")
		Name(_CID, 0x23)
		Name(_STR, Unicode("SATA45 PHY Clock"))
		Name(MM0A, 0x1F23C000)	// MMIO 0 Address
		Name(MM0S, 0x1000)	// MMIO 0 Size
		Name(MM1A, 0x00000000)	// MMIO 1 Address
		Name(MM1S, 0x0)		// MMIO 1 Size
		Name(_UID, "sataphy3clk")	// clock-name
		Name(CLNM, "sataphy3clk")	// clock-name
		Name(PRNT, "socplldiv2")// parent-clock
		Name(CSRO, 0x4)		// csr-offset
		Name(CSRM, 0x3A)	// csr-mask
		Name(EOFF, 0x00)	// enable-offset
		Name(EMSK, 0x06)	// enable-mask
	}
	Device(CK29) {
		Name(_HID, "APMC0C04")
		Name(_CID, 0x24)
		Name(_STR, Unicode("SATA01 Clock"))
		Name(MM0A, 0x1F21C000)	// MMIO 0 Address
		Name(MM0S, 0x1000)	// MMIO 0 Size
		Name(MM1A, 0x00000000)	// MMIO 1 Address
		Name(MM1S, 0x0)		// MMIO 1 Size
		Name(_UID, "sata01clk")	// clock-name
		Name(CLNM, "sata01clk")	// clock-name
		Name(PRNT, "socplldiv2")// parent-clock
		Name(CSRO, 0x4)		// csr-offset
		Name(CSRM, 0x05)	// csr-mask
		Name(EOFF, 0x00)	// enable-offset
		Name(EMSK, 0x39)	// enable-mask
	}
	Device(CK30) {
		Name(_HID, "APMC0C04")
		Name(_CID, 0x25)
		Name(_STR, Unicode("SATA23 Clock"))
		Name(MM0A, 0x1F22C000)	// MMIO 0 Address
		Name(MM0S, 0x1000)	// MMIO 0 Size
		Name(MM1A, 0x00000000)	// MMIO 1 Address
		Name(MM1S, 0x0)		// MMIO 1 Size
		Name(_UID, "sata23clk")	// clock-name
		Name(CLNM, "sata23clk")	// clock-name
		Name(PRNT, "socplldiv2")// parent-clock
		Name(CSRO, 0x4)		// csr-offset
		Name(CSRM, 0x05)	// csr-mask
		Name(EOFF, 0x00)	// enable-offset
		Name(EMSK, 0x39)	// enable-mask
	}
	Device(CK31) {
		Name(_HID, "APMC0C04")
		Name(_CID, 0x26)
		Name(_STR, Unicode("SATA45 Clock"))
		Name(MM0A, 0x1F23C000)	// MMIO 0 Address
		Name(MM0S, 0x1000)	// MMIO 0 Size
		Name(MM1A, 0x00000000)	// MMIO 1 Address
		Name(MM1S, 0x0)		// MMIO 1 Size
		Name(_UID, "sata45clk")	// clock-name
		Name(CLNM, "sata45clk")	// clock-name
		Name(PRNT, "socplldiv2")// parent-clock
		Name(CSRO, 0x4)		// csr-offset
		Name(CSRM, 0x05)	// csr-mask
		Name(EOFF, 0x00)	// enable-offset
		Name(EMSK, 0x39)	// enable-mask
	}

///////////////////////////////////////////////////////////////////////////////
// Reboot Device
	Device(SRBD) {
		Name(_HID, "APMC0D08") // Device Identification Objects
		Name(_DDN, "SRD0")
		Name(_UID, "SRD0")
		Name(_STR, Unicode("System Reboot Device"))
		Name(_ADR, 0x17000014)
		Name(_CID, "SRBD0000")
		Name(_CRS, ResourceTemplate() {
      			Memory32Fixed(ReadWrite, 0x17000014, 0x00000100, )
		})
	} //REBOOT

///////////////////////////////////////////////////////////////////////////////
// SLIMpro Device
	Device(SLIM) {
		Name(_HID, "APMC0D01") // Device Identification Objects
		Name(_DDN, "SLIM")
		Name(_UID, "SLIM")
		Name(_STR, Unicode("SLIMpro Device"))
		Name(_CID, "APMC0D01")
		Name(_CRS, ResourceTemplate() {
			Memory32Fixed(ReadWrite, 0x10540000, 0xa100, )
			Memory32Fixed(ReadWrite, 0x17000000, 0x1000, )
			Memory32Fixed(ReadWrite, 0x17001000, 0x1000, )
			Interrupt(ResourceProducer, Level, ActiveHigh, Exclusive) { 0x0 }
			Interrupt(ResourceProducer, Level, ActiveHigh, Exclusive) { 0x1 }
			Interrupt(ResourceProducer, Level, ActiveHigh, Exclusive) { 0x2 }
			Interrupt(ResourceProducer, Level, ActiveHigh, Exclusive) { 0x3 }
			Interrupt(ResourceProducer, Level, ActiveHigh, Exclusive) { 0x4 }
			Interrupt(ResourceProducer, Level, ActiveHigh, Exclusive) { 0x5 }
			Interrupt(ResourceProducer, Level, ActiveHigh, Exclusive) { 0x6 }
			Interrupt(ResourceProducer, Level, ActiveHigh, Exclusive) { 0x7 }
			Interrupt(ResourceProducer, Level, ActiveHigh, Exclusive) { 0x8 }
			Interrupt(ResourceProducer, Level, ActiveHigh, Exclusive) { 0x9 }
		})
		Name(DBST, 0x0000) // Doorbell start index
		Name(DBEN, 0x0007) // Doorbell end index
		Name(DBRT, 0x0005) // Doorbell retry count
		Name(DBEV, 0x0007) // Doorbell event
		Name(DBIC, 0x0000) // Doorbell I2C
	} //SLIM

///////////////////////////////////////////////////////////////////////////////
// PCP Bus Device
	Device(PCPD) {
		Name(_HID, "APMC0D02") // Device Identification Objects
		Name(_DDN, "PCP0")
		Name(_UID, "PCP0")
		Name(_STR, Unicode("PCP Bus Device"))
		Name(_ADR, 0x78800000)
		Name(_CID, "APMC0D02")
		Name(_CRS, ResourceTemplate() {
			Memory32Fixed(ReadWrite, 0x78800000, 0x20000, )
			Memory32Fixed(ReadWrite, 0x7E930000, 0x40000, )
			Memory32Fixed(ReadWrite, 0x7C000000, 0x4000000, )
			Memory32Fixed(ReadWrite, 0x7E200200, 0x1000, )
			Memory32Fixed(ReadWrite, 0x7E600000, 0x1000, )
			Interrupt(ResourceProducer, Level, ActiveHigh, Exclusive) { 0x20 }
			Interrupt(ResourceProducer, Level, ActiveHigh, Exclusive) { 0x21 }
			Interrupt(ResourceProducer, Level, ActiveHigh, Exclusive) { 0x27 }
			})
	} //PCP Bus Device

///////////////////////////////////////////////////////////////////////////////
// GPIO
	Device(GP00) {
		Name(_HID, "APMC0D07") // Device Identification Objects
		Name(_CID, "APMC0D07")
		Name(_UID, "GPIO0")
		Name(_STR, Unicode("GPIO Device"))
		Name(_CRS, ResourceTemplate() {
			Memory32Fixed(ReadWrite, 0x1C024000, 0x1000)
		})
		NAME(CLNM, "gpioclk")   // clock-names
		NAME(NGPI, 32)          // ngpio
	} //GP00 Device

///////////////////////////////////////////////////////////////////////////////
//AHBC Bus
	// AHBC Device
	Device(AHBC) {
		OperationRegion(SRST, SystemMemory, 0x1F2AC000, 4)
		OperationRegion(CLKE, SystemMemory, 0x1F2AC004, 4)
		Field(SRST, DWordAcc, NoLock, Preserve) {
			ACSR, 1,
			SDRS, 1,
			IORS, 1,
			U0RS, 1,
			U1RS, 1,
			U2RS, 1,
			U3RS, 1,
			S0RS, 1,
			S1RS, 1,
			APRS, 1
		}
		Field(CLKE, DWordAcc, NoLock, Preserve) {
			ACCE, 1,
			SDCE, 1,
			IOCE, 1,
			U0CE, 1,
			U1CE, 1,
			U2CE, 1,
			U3CE, 1,
			S0CE, 1,
			S1CE, 1,
			APCE, 1
		}

		// Device Identification Objects
		Name(_HID, "APMC0D06")
		Name(_DDN, "AHBC")
		Name(_UID, "AHBC")
		Name(_CID, "APMC0D06")
		Name(_STR, Unicode("AHBC Peripheral Bus"))

		// Device Configuration Objects
		// Device Status
		Method(_STA) {
			if (LOr(LOr(NAnd(ACSR, One), NAnd(APRS, One)),
			LOr(LEqual(ACCE, Zero), LEqual(APCE, Zero)))) {
				Return (1)
			}
			Return (3)
		} //_STA

		// Device current resources, two registers
		Name(_CRS, ResourceTemplate() {
     			Memory32Fixed(ReadWrite, 0x1f2a0000, 0x80000, )
     			Memory32Fixed(ReadWrite, 0x1c000200, 0x100, )
		})

//==============================================================================

		//UART0 Device Controller
		Device(URT0) {
			//Device Identification Objects
			Name(_HID, "UART0000")
			Name(_DDN, "URT0")
			Name(_UID, "URT0")
			Name(_STR, Unicode("APM88xxxx UART0 Controller"))

			Name(_ADR, 0x1C020000)
			Name(_CID, "NS16550")

			//Disable Device Method
			Method(_DIS) {
				Store(Zero, U0CE)
				Store(One, U0RS)
			} //_DIS

			//Device Status
			Method(_STA) {
				if (LOr(NAnd(U0RS, One), LEqual(U0CE, Zero))) {
					Return (1)
				}
				Return (3)
			} //_STA

			//Device Power Management Methods
			//D0 State, ON
			Method(_PS0) {
				Store(One, U0CE)
				Store(Zero, U0RS)
			} //_PS0
			//D3 State, OFF
			Method(_PS3) {
				Store(Zero, U0CE)
				Store(One, U0RS)
			}//_PS3
			//Current Power State
			Method(_PSC) {
				if (LOr(NAnd(U0RS, One), LEqual(U0CE, Zero))) {
					Return (3)
				}
				Return (0)

			} //_PSC
			//Power Resources Needed in D0 State
			Name(_PR0, Package() {SCVR})
			//Can be put to D3 state when in S1 state
			Name(_S1D, 3)

			//Device Current Resource Settings
			//UART0 Generates an interrupt
			Name(_CRS, ResourceTemplate() {
				Register(SystemMemory, 32, 0, 0x1C020000, 3)
				UARTSerialBus(
					115200,			//Baud Rate
					DataBitsEight, 		//Bits-per-byte
					StopBitsOne, 		//StopBits
					0x00,			//Lines in use
					LittleEndian,
					ParityTypeNone,
					FlowControlNone,
					16,			//Rx Buffer size
					16, 			//Tx Buffer size
					"URT0",			//This resource for UART0
					0,
					ResourceConsumer,
					U0DT
				)
				Interrupt(ResourceProducer, Level, ActiveHigh,
				Exclusive) {108}
				})
		} //URT0

		//UART1 Device Controller
		Device(URT1) {
			//Device Identification Objects
			Name(_HID, "UART0000")
			Name(_DDN, "URT1")
			Name(_UID, "URT1")
			Name(_STR, Unicode("APM88xxxx UART1 Controller"))

			Name(_ADR, 0x1C021000)
			Name(_CID, "NS16550")

			//Disable Device Method
			Method(_DIS) {
				Store(Zero, U1CE)
				Store(One, U1RS)
			} //_DIS

			//Device Status
			Method(_STA) {
				if (LOr(NAnd(U1RS, One), LEqual(U1CE, Zero))) {
					Return (1)
				}
				Return (3)
			} //_STA

			//Device Power Management Methods
			//D0 State, ON
			Method(_PS0) {
				Store(One, U1CE)
				Store(Zero, U1RS)
			} //_PS0
			//D3 State, OFF
			Method(_PS3) {
				Store(Zero, U1CE)
				Store(One, U1RS)
			}//_PS3
			//Current Power State
			Method(_PSC) {
				if (LOr(NAnd(U1RS, One), LEqual(U1CE, Zero))) {
					Return (3)
				}
				Return (0)

			} //_PSC
			//Power Resources Needed in D0 State
			Name(_PR0, Package() {SCVR})
			//Can be put to D3 state when in S1 state
			Name(_S1D, 3)

			//Device Current Resource Settings
			//UART1 Generates an interrupt
			Name(_CRS, ResourceTemplate() {
				Register(SystemMemory, 32, 0, 0x1C021000, 3)
				UARTSerialBus(
					115200,			//Baud Rate
					DataBitsEight, 		//Bits-per-byte
					StopBitsOne, 		//StopBits
					0x00,			//Lines in use
					LittleEndian,
					ParityTypeNone,
					FlowControlNone,
					16,			//Rx Buffer size
					16, 			//Tx Buffer size
					"URT1",			//This resource for UART0
					0,
					ResourceConsumer,
					U1DT
				)
				Interrupt(ResourceProducer, Level, ActiveHigh,
				Exclusive) {108}
				})
		} //URT1
//==============================================================================
		//SPI0 Device Controller
		Device(SPI0) {

			//Device Identification Objects
			Name(_HID, "SPI00000")
			Name(_DDN, "SPI0")
			Name(_UID, "SPI0")
			Name(_STR, Unicode("APM88xxxx SPI0 Controller"))

			//Disable Device Method
			Method(_DIS) {
				Store(Zero, S0CE)
				Store(One, S0RS)
			} //_DIS

			//Device Status
			Method(_STA) {
				if (LOr(NAnd(S0RS, One), LEqual(S0CE, Zero))) {
					Return (1)
				}
				Return (3)
			} //_STA

			//Device Power Management Methods
			//D0 State, ON
			Method(_PS0) {
				Store(One, S0CE)
				Store(Zero, S0RS)
			} //_PS0
			//D3 State, OFF
			Method(_PS3) {
				Store(Zero, S0CE)
				Store(One, S0RS)
			}//_PS3
			//Current Power State
			Method(_PSC) {
				if (LOr(NAnd(S0RS, One), LEqual(S0CE, Zero))) {
					Return (3)
				}
				Return (0)

			} //_PSC
			//Power Resources Needed in D0 State
			Name(_PR0, Package() {SCVR})
			//Can be put to D3 state when in S1 state
			Name(_S1D, 3)

			//Device Current Resource Settings
			//SPI0 Generates an interrupt
			Name(_CRS, ResourceTemplate() {
				Interrupt(ResourceProducer, Level, ActiveHigh,
				Exclusive) {106}
			})
		}//SPI0

		//SPI0 CS0 connection resource
		Name(SP00, ResourceTemplate() {
			SPISerialBus(
			1,			//Slave select CS0 (_ADR)
			PolarityHigh,		//Polarity of CS0 output(_DPL)
			FourWireMode,		//(_MOD)
			8,			//8-bit frame(_LEN)
			ControllerInitiated,	//(_SLV)
			12500000,		//Speed Hz (_SPE)
			ClockPolarityHigh,	//(_POL)
			ClockPhaseSecond,	//(_PHA)
			"SPI0",			//Controller
			0,
			ResourceConsumer,
			)
		})//SP00

		//SPI0 CS1 connection resource
		Name(SP01, ResourceTemplate() {
			SPISerialBus(
			2,			//Slave select CS0 (_ADR)
			PolarityHigh,		//Polarity of CS0 output(_DPL)
			FourWireMode,		//(_MOD)
			8,			//8-bit frame(_LEN)
			ControllerInitiated,	//(_SLV)
			12500000,		//Speed Hz (_SPE)
			ClockPolarityHigh,	//(_POL)
			ClockPhaseSecond,	//(_PHA)
			"SPI0",			//Controller
			0,
			ResourceConsumer,
			)
		})//SP01

		//SPI0 CS2 connection resource
		Name(SP02, ResourceTemplate() {
			SPISerialBus(
			4,			//Slave select CS0 (_ADR)
			PolarityHigh,		//Polarity of CS0 output(_DPL)
			FourWireMode,		//(_MOD)
			8,			//8-bit frame(_LEN)
			ControllerInitiated,	//(_SLV)
			12500000,		//Speed Hz (_SPE)
			ClockPolarityHigh,	//(_POL)
			ClockPhaseSecond,	//(_PHA)
			"SPI0",			//Controller
			0,
			ResourceConsumer,
			)
		})//SP02

//==============================================================================
		//SPI1 Device Controller
		Device(SPI1) {

			//Device Identification Objects
			Name(_HID, "SPI10000")
			Name(_DDN, "SPI1")
			Name(_UID, "SPI1")
			Name(_STR, Unicode("APM88xxxx SPI1 Controller"))

			//Disable Device Method
			Method(_DIS) {
				Store(Zero, S1CE)
				Store(One, S1RS)
			} //_DIS

			//Device Status
			Method(_STA) {
				if (LOr(NAnd(S1RS, One), LEqual(S1CE, Zero))) {
					Return (1)
				}
				Return (3)
			} //_STA

			//Device Power Management Methods
			//D0 State, ON
			Method(_PS0) {
				Store(One, S1CE)
				Store(Zero, S1RS)
			} //_PS0
			//D3 State, OFF
			Method(_PS3) {
				Store(Zero, S1CE)
				Store(One, S1RS)
			}//_PS3
			//Current Power State
			Method(_PSC) {
				if (LOr(NAnd(S1RS, One), LEqual(S1CE, Zero))) {
					Return (3)
				}
				Return (0)

			} //_PSC
			//Power Resources Needed in D0 State
			Name(_PR0, Package() {SCVR})
			//Can be put to D3 state when in S1 state
			Name(_S1D, 3)

			//Device Current Resource Settings
			//SPI0 Generates an interrupt
			Name(_CRS, ResourceTemplate() {
				Interrupt(ResourceProducer, Level, ActiveHigh,
				Exclusive) {107}
			})
		}//SPI1

		//SPI1 CS0 connection resource
		Name(SP10, ResourceTemplate() {
			SPISerialBus(
			1,			//Slave select CS0 (_ADR)
			PolarityHigh,		//Polarity of CS0 output(_DPL)
			FourWireMode,		//(_MOD)
			8,			//8-bit frame(_LEN)
			ControllerInitiated,	//(_SLV)
			12500000,		//Speed Hz (_SPE)
			ClockPolarityHigh,	//(_POL)
			ClockPhaseSecond,	//(_PHA)
			"SPI1",			//Controller
			0,
			ResourceConsumer,
			)
		})//SP10

		//SPI1 CS1 connection resource
		Name(SP11, ResourceTemplate() {
			SPISerialBus(
			2,			//Slave select CS0 (_ADR)
			PolarityHigh,		//Polarity of CS0 output(_DPL)
			FourWireMode,		//(_MOD)
			8,			//8-bit frame(_LEN)
			ControllerInitiated,	//(_SLV)
			12500000,		//Speed Hz (_SPE)
			ClockPolarityHigh,	//(_POL)
			ClockPhaseSecond,	//(_PHA)
			"SPI1",			//Controller
			0,
			ResourceConsumer,
			)
		})//SP11

		//SPI1 CS2 connection resource
		Name(SP12, ResourceTemplate() {
			SPISerialBus(
			4,			//Slave select CS0 (_ADR)
			PolarityHigh,		//Polarity of CS0 output(_DPL)
			FourWireMode,		//(_MOD)
			8,			//8-bit frame(_LEN)
			ControllerInitiated,	//(_SLV)
			12500000,		//Speed Hz (_SPE)
			ClockPolarityHigh,	//(_POL)
			ClockPhaseSecond,	//(_PHA)
			"SPI1",			//Controller
			0,
			ResourceConsumer,
			)
		})//SP12
//==============================================================================
	} //AHBC
////////////////////////////////////////////////////////////////////////////////
// I2C1 VRM Bus

	Device(I2CS) {
		//Device Identification Objects
		Name(_HID, "I2CS0001")
		Name(_DDN, "I2CS")
		Name(_UID, "I2CS")
		Name(_STR, Unicode("SLIMpro IIC1 Serial Bus"))

//==============================================================================
		//PMD+L3C VRM connection resource
		Name(PCCG, ResourceTemplate() {
			I2CSerialBus(
			0x10,	//Slave Address(_ADR)
			ControllerInitiated,	//Slave Mode (_SLV)
			1000,	//Connection speed in Hz (_SPE)
			AddressingMode7Bit,	//(_MOD)
			"I2CS",	//Controller
			0,
			ResourceConsumer,
			PCVR
			)
		}) //PCCG

		//VRM Info Common to PMD+L3C
		Device(PCPV) {
			//Device Identification Objects
			Name(_HID, "PCPV0000")
			Name(_DDN, "PCCG")
			Name(_UID, "PCCG")
			Name(_STR, Unicode("APM88xxxx PMD+L3C VRM"))

			//Resources used
			Method(_CRS) {
				Return (PCCG)
			}
			Method(_PRS) {
				Return (PCCG)
			}

			//VRM Device Register Locations
			Name(POWR, 0x36)
			Name(CURR, 0x38)
			Name(VOLT, 0x40)

		} //PCPV

//==============================================================================
		//SOC VRM Connection resource
		Name(SCCG, ResourceTemplate() {
			I2CSerialBus(
			0x10,	//Slave Address(_ADR)
			ControllerInitiated,	//Slave Mode (_SLV)
			1000,	//Connection speed in Hz (_SPE)
			AddressingMode7Bit,	//(_MOD)
			"I2CS",	//Controller
			0,
			ResourceConsumer,
			SCVR
			)
		}) //SCCG

		//VRM Info for SOC domain
		Device(SOCV) {
			//Device Identification Objects
			Name(_HID, "SOCV0000")
			Name(_DDN, "SCCG")
			Name(_UID, "SCCG")
			Name(_STR, Unicode("APM88xxxx SOC VRM"))

			//Resources used
			Method(_CRS) {
				Return (SCCG)
			}
			Method(_PRS) {
				Return (SCCG)
			}

			//VRM Device Register Locations
			Name(POWR, 0x36)
			Name(CURR, 0x38)
			Name(VOLT, 0x40)
		} //SOCV


	} //I2C1

///////////////////////////////////////////////////////////////////////////////
// SATA Devices
	Device(PHY1) {
		Name(_HID, "APMC0D0A") // Device Identification Objects
		Name(_UID, 1)
		Name(_STR, Unicode("X-Gene PHY"))
	        Method(_STA, 0, NotSerialized) {
			Return (0x0)
        	}
		Name(_CRS, ResourceTemplate () {
			Memory32Fixed (ReadWrite, 0x1F21A000, 0x100)
		})
		// Tx Booster/Gain
		Name(TBG0, Buffer() { 0x1e, 0x1e, 0x1e, 0x1e, 0x1e, 0x1e })
		// Tx Booster/Gain SSD
		Name(TBG1, Buffer() { 0x2, 0x2, 0x2, 0x2, 0x2, 0x2 })
		// Tx Eye Tuning
		Name(TET0, Buffer() { 0x2, 0xa, 0xa, 0x2, 0xa, 0xa })
		// Tx Booster/Gain - pre-A3 chip
		Name(TBGA, Buffer() { 0x2, 0x2, 0x2, 0x2, 0x2, 0x2 })
		// Tx Booster/Gain SSD - pre-A3 chip
		Name(TBGB, Buffer() { 0x2, 0x2, 0x2, 0x2, 0x2, 0x2 })
		// Tx Eye Tuning - pre-A3 chip
		Name(TETA, Buffer() { 0xa, 0xa, 0xa, 0xa, 0xa, 0xa })
		// Tx Speed - pre-A3 chip
		Name(TSPA, Buffer() { 0x1, 0x3, 0x5})
		// Tx pre-cursor1 - pre-A3 chip (4 bytes - mV)
		Name(TC1A, Buffer() { 	0x0, 0x0, 0x0, 0x0,
					0x0, 0x0, 0x0, 0x0,
					0x0, 0x0, 0x0, 0x0,
					0x0, 0x0, 0x0, 0x0,
					0x0, 0x0, 0x0, 0x0,
					0x0, 0x0, 0x0, 0x0 })
		// Tx post-cursor - pre-A3 chip (4 bytes - mV)
		Name(TPCA, Buffer() {	0x0, 0x4, 0x2A, 0x68,
					0x0, 0x4, 0x2A, 0x68,
					0x0, 0x4, 0x2A, 0x68,
					0x0, 0x4, 0x2A, 0x68,
					0x0, 0x4, 0x2A, 0x68,
					0x0, 0x4, 0x2A, 0x68 })
		// Tx Amptitude - pre-A3 chip (4 bytes - mV)
		Name(TAPA, Buffer() {	0x0, 0x3, 0x0B, 0x4C,
					0x0, 0x3, 0x0B, 0x4C,
					0x0, 0x3, 0x0B, 0x4C,
					0x0, 0x3, 0x0B, 0x4C,
					0x0, 0x3, 0x0B, 0x4C,
					0x0, 0x3, 0x0B, 0x4C })
		Name(CONS, "APMC0D00:00")
		NAME(CLNM, "sataphy1clk")  // clock-names
	};
	Device(PHY2) {
		Name(_HID, "APMC0D0A") // Device Identification Objects
		Name(_UID, 2)
		Name(_STR, Unicode("X-Gene PHY"))
	        Method(_STA, 0, NotSerialized) {
			Return (0x1)
        	}
		Name(_CRS, ResourceTemplate () {
			Memory32Fixed (ReadWrite, 0x1F22A000, 0x100)
		})
		// Tx Booster/Gain
		Name(TBG0, Buffer() { 0x1e, 0x1e, 0x1e, 0x1e, 0x1e, 0x1e })
		// Tx Booster/Gain SSD
		Name(TBG1, Buffer() { 0x2, 0x2, 0x2, 0x2, 0x2, 0x2 })
		// Tx Eye Tuning
		Name(TET0, Buffer() { 0x1, 0xa, 0xa, 0x2, 0xa, 0xa })
		// Tx Booster/Gain - pre-A3 chip
		Name(TBGA, Buffer() { 0x2, 0x2, 0x2, 0x2, 0x2, 0x2 })
		// Tx Booster/Gain SSD - pre-A3 chip
		Name(TBGB, Buffer() { 0x2, 0x2, 0x2, 0x2, 0x2, 0x2 })
		// Tx Eye Tuning - pre-A3 chip
		Name(TETA, Buffer() { 0x1, 0xa, 0xa, 0x2, 0xa, 0xa })
		// Tx Speed - pre-A3 chip
		Name(TSPA, Buffer() { 0x1, 0x3, 0x5})
		// Tx pre-cursor1 - pre-A3 chip (4 bytes - mV)
		Name(TC1A, Buffer() { 	0x0, 0x0, 0x0, 0x0,
					0x0, 0x0, 0x0, 0x0,
					0x0, 0x0, 0x0, 0x0,
					0x0, 0x0, 0x0, 0x0,
					0x0, 0x0, 0x0, 0x0,
					0x0, 0x0, 0x0, 0x0 })
		// Tx post-cursor - pre-A3 chip (4 bytes - mV)
		Name(TPCA, Buffer() {	0x0, 0x4, 0x2A, 0x68,
					0x0, 0x4, 0x2A, 0x68,
					0x0, 0x4, 0x2A, 0x68,
					0x0, 0x4, 0x2A, 0x68,
					0x0, 0x4, 0x2A, 0x68,
					0x0, 0x4, 0x2A, 0x68 })
		// Tx Amptitude - pre-A3 chip (4 bytes - mV)
		Name(TAPA, Buffer() {	0x0, 0x3, 0x0B, 0x4C,
					0x0, 0x3, 0x0B, 0x4C,
					0x0, 0x3, 0x0B, 0x4C,
					0x0, 0x3, 0x0B, 0x4C,
					0x0, 0x3, 0x0B, 0x4C,
					0x0, 0x3, 0x0B, 0x4C })
		Name(CONS, "APMC0D0D:00")
		NAME(CLNM, "sataphy2clk")  // clock-names
	};
	Device(PHY3) {
		Name(_HID, "APMC0D0B") // Device Identification Objects
		Name(_UID, 3)
		Name(_STR, Unicode("X-Gene PHY"))
	        Method(_STA, 0, NotSerialized) {
			Return (0x1)
        	}
		Name(_CRS, ResourceTemplate () {
			Memory32Fixed (ReadWrite, 0x1F23A000, 0x100)
			Memory32Fixed (ReadWrite, 0x1F2D0000, 0x100)
		})
		// Tx Booster/Gain
		Name(TBG0, Buffer() { 0x1f, 0x1f, 0x1f, 0x1f, 0x1f, 0x1f })
		// Tx Booster/Gain SSD
		Name(TBG1, Buffer() { 0x3, 0x3, 0x3, 0x3, 0x3, 0x3 })
		// Tx Eye Tuning
		Name(TET0, Buffer() { 0x2, 0xa, 0xa, 0x2, 0xa, 0xa })
		// Tx Booster/Gain - pre-A3 chip
		Name(TBGA, Buffer() { 0x2, 0x2, 0x2, 0x2, 0x2, 0x2 })
		// Tx Booster/Gain SSD - pre-A3 chip
		Name(TBGB, Buffer() { 0x2, 0x2, 0x2, 0x2, 0x2, 0x2 })
		// Tx Eye Tuning - pre-A3 chip
		Name(TETA, Buffer() { 0xa, 0xa, 0xa, 0xa, 0xa, 0xa })
		// Tx Speed - pre-A3 chip
		Name(TSPA, Buffer() { 0x1, 0x3, 0x5})
		// Tx pre-cursor1 - pre-A3 chip (4 bytes - mV)
		Name(TC1A, Buffer() { 	0x0, 0x0, 0x0, 0x0,
					0x0, 0x0, 0x0, 0x0,
					0x0, 0x0, 0x0, 0x0,
					0x0, 0x0, 0x0, 0x0,
					0x0, 0x0, 0x0, 0x0,
					0x0, 0x0, 0x0, 0x0 })
		// Tx post-cursor - pre-A3 chip (4 bytes - mV)
		Name(TPCA, Buffer() {	0x0, 0x4, 0x2A, 0x68,
					0x0, 0x4, 0x2A, 0x68,
					0x0, 0x4, 0x2A, 0x68,
					0x0, 0x4, 0x2A, 0x68,
					0x0, 0x4, 0x2A, 0x68,
					0x0, 0x4, 0x2A, 0x68 })
		// Tx Amptitude - pre-A3 chip (4 bytes - mV)
		Name(TAPA, Buffer() {	0x0, 0x3, 0x0B, 0x4C,
					0x0, 0x3, 0x0B, 0x4C,
					0x0, 0x3, 0x0B, 0x4C,
					0x0, 0x3, 0x0B, 0x4C,
					0x0, 0x3, 0x0B, 0x4C,
					0x0, 0x3, 0x0B, 0x4C })
		Name(CONS, "APMC0D09:00")
		NAME(CLNM, "sataphy3clk")  // clock-names
	};
	Device(SAT0) {
		Name(_HID, "APMC0D00") // Device Identification Objects
		Name(_UID, 1)
		Name(_STR, Unicode("X-Gene SATA"))
	        Method(_STA, 0, NotSerialized) {
			Return (0x0)
        	}
		Name(_CRS, ResourceTemplate () {
			Memory32Fixed (ReadWrite, 0x1A000000, 0x1000)
			Memory32Fixed (ReadWrite, 0x1F210000, 0x10000)
			Memory32Fixed (ReadWrite, 0x1F2A0000, 0x10000)
			Memory32Fixed (ReadWrite, 0x1C000200, 0x100)
			Interrupt (ResourceConsumer, Level, ActiveHigh, Exclusive) {0x86}
		})
		NAME(CLNM, "sata01clk")  // clock-names
	} //SAT0
	Device(SAT1) {
		Name(_HID, "APMC0D0D") // Device Identification Objects
		Name(_UID, 2)
		Name(_STR, Unicode("X-Gene SATA"))
	        Method(_STA, 0, NotSerialized) {
			Return (0x1)
        	}
		Name (_CRS, ResourceTemplate () {
			Memory32Fixed (ReadWrite, 0x1A400000, 0x1000)
			Memory32Fixed (ReadWrite, 0x1F220000, 0x10000)
			Memory32Fixed (ReadWrite, 0x1F2A0000, 0x10000)
			Memory32Fixed (ReadWrite, 0x1C000200, 0x100)
			Interrupt (ResourceConsumer, Level, ActiveHigh, Exclusive) {0x87}
		})
		NAME(CLNM, "sata23clk")  // clock-names
	} //SAT1
	Device(SAT2) {
		Name(_HID, "APMC0D09") // Device Identification Objects
		Name(_UID, 3)
		Name(_STR, Unicode("X-Gene SATA"))
	        Method(_STA, 0, NotSerialized) {
			Return (0x1)
        	}
		Name(_CRS, ResourceTemplate () {
			Memory32Fixed (ReadWrite, 0x1A800000, 0x1000)
			Memory32Fixed (ReadWrite, 0x1F230000, 0x10000)
			Memory32Fixed (ReadWrite, 0x1F2A0000, 0x10000)
			Memory32Fixed (ReadWrite, 0x1C000200, 0x100)
			Interrupt (ResourceConsumer, Level, ActiveHigh, Exclusive) {0x88}
		})
		NAME(CLNM, "sata45clk") // clock-names
	} //SAT2

///////////////////////////////////////////////////////////////////////////////
// USB Devices
	Device(USB0) {
		Name(_HID, "APMC0D03")
		Name(_DDN, "USB0")
		Name(_UID, "USB0")
		Name(_STR, Unicode("APM88xxxx USB"))
		Name(_CID, "APMC0D03")
		Name(_CRS, ResourceTemplate () {
			Memory32Fixed (ReadWrite, 0x19000000, 0x100000)
			Memory32Fixed (ReadWrite, 0x1F280000,  0x10000)
			Interrupt (ResourceConsumer, Level, ActiveHigh, Exclusive) {0x89}
		})
		NAME(CLNM, "usb0clk")  // clock-names
		Name(STAT, "ok")        // status
		NAME(SDCL, 0x0)         // serdes-diff-clk
		NAME(GENS, 0x3)         // gen-sel
		NAME(OVCE, 0x0)         // Overcur Enable
		NAME(OVCI, 0x0)         // Overcur Invert
	} //USB0
	Device(USB1) {
		Name(_HID, "APMC0D03")
		Name(_DDN, "USB1")
		Name(_UID, "USB1")
		Name(_STR, Unicode("APM88xxxx USB"))
		Name(_CID, "APMC0D03")
		Name(_CRS, ResourceTemplate () {
			Memory32Fixed (ReadWrite, 0x19800000, 0x100000)
			Memory32Fixed (ReadWrite, 0x1F290000,  0x10000)
			Interrupt (ResourceConsumer, Level, ActiveHigh, Exclusive) {0x8a}
		})
		NAME(CLNM, "usb1clk")  // clock-names
		Name(STAT, "ok")        // status
		NAME(SDCL, 0x0)         // serdes-diff-clk
		NAME(GENS, 0x3)         // gen-sel
		NAME(OVCE, 0x0)         // Overcur Enable
		NAME(OVCI, 0x0)         // Overcur Invert
	} //USB1

///////////////////////////////////////////////////////////////////////////////
// QM Device
	Device(QM03) {
		Name(_HID, "APMC0D04") // Device Identification Objects
		Name(_DDN, "QM03")
		Name(_UID, "QM03")
		Name(_STR, Unicode("QM Lite Device"))
		Name(_CID, "APMC0D04")
		Name(_CRS, ResourceTemplate() {
			Memory32Fixed(ReadWrite, 0x17030000, 0x10000, )
			Memory32Fixed(ReadWrite, 0x10000000, 0x400000, )
			Interrupt(ResourceProducer, Level, ActiveHigh, Exclusive) { 0x40 }
			Interrupt(ResourceProducer, Level, ActiveHigh, Exclusive) { 0x3c }
		})
		Name(CLNM, "qmlclk") // clock-names
		Name(DVID, 0x03)     // Device ID
		Name(MQID, 0x400)    // Max QID
		Name(SLNM, "CPU_QMTM3") // Slave name
		Name(SLIF, Buffer() { 0x03, 0x00, 0x01, 0x20, 0x01 }) // Slave info
	} // QM03

	Device(QM01) {
		Name(_HID, "APMC0D04") // Device Identification Objects
		Name(_DDN, "QM01")
		Name(_UID, "QM01")
		Name(_STR, Unicode("QM 1 Device"))
		Name(_CID, "APMC0D04")
		Name(_CRS, ResourceTemplate() {
			Memory32Fixed(ReadWrite, 0x1f200000, 0x10000, )
			Memory32Fixed(ReadWrite, 0x1b000000, 0x400000, )
			Interrupt(ResourceProducer, Level, ActiveHigh, Exclusive) { 0xc0 }
			Interrupt(ResourceProducer, Level, ActiveHigh, Exclusive) { 0xa0 }
			Interrupt(ResourceProducer, Level, ActiveHigh, Exclusive) { 0xa1 }
			Interrupt(ResourceProducer, Level, ActiveHigh, Exclusive) { 0xa2 }
			Interrupt(ResourceProducer, Level, ActiveHigh, Exclusive) { 0xa3 }
			Interrupt(ResourceProducer, Level, ActiveHigh, Exclusive) { 0xa4 }
			Interrupt(ResourceProducer, Level, ActiveHigh, Exclusive) { 0xa5 }
			Interrupt(ResourceProducer, Level, ActiveHigh, Exclusive) { 0xa6 }
			Interrupt(ResourceProducer, Level, ActiveHigh, Exclusive) { 0xa7 }
			Interrupt(ResourceProducer, Level, ActiveHigh, Exclusive) { 0xa8 }
			Interrupt(ResourceProducer, Level, ActiveHigh, Exclusive) { 0xa9 }
			Interrupt(ResourceProducer, Level, ActiveHigh, Exclusive) { 0xaa }
			Interrupt(ResourceProducer, Level, ActiveHigh, Exclusive) { 0xab }
			Interrupt(ResourceProducer, Level, ActiveHigh, Exclusive) { 0xac }
			Interrupt(ResourceProducer, Level, ActiveHigh, Exclusive) { 0xad }
			Interrupt(ResourceProducer, Level, ActiveHigh, Exclusive) { 0xae }
			Interrupt(ResourceProducer, Level, ActiveHigh, Exclusive) { 0xaf }
			Interrupt(ResourceProducer, Level, ActiveHigh, Exclusive) { 0xb0 }
			Interrupt(ResourceProducer, Level, ActiveHigh, Exclusive) { 0xb1 }
			Interrupt(ResourceProducer, Level, ActiveHigh, Exclusive) { 0xb2 }
			Interrupt(ResourceProducer, Level, ActiveHigh, Exclusive) { 0xb3 }
			Interrupt(ResourceProducer, Level, ActiveHigh, Exclusive) { 0xb4 }
			Interrupt(ResourceProducer, Level, ActiveHigh, Exclusive) { 0xb5 }
			Interrupt(ResourceProducer, Level, ActiveHigh, Exclusive) { 0xb6 }
			Interrupt(ResourceProducer, Level, ActiveHigh, Exclusive) { 0xb7 }
			Interrupt(ResourceProducer, Level, ActiveHigh, Exclusive) { 0xb8 }
			Interrupt(ResourceProducer, Level, ActiveHigh, Exclusive) { 0xb9 }
			Interrupt(ResourceProducer, Level, ActiveHigh, Exclusive) { 0xba }
			Interrupt(ResourceProducer, Level, ActiveHigh, Exclusive) { 0xbb }
			Interrupt(ResourceProducer, Level, ActiveHigh, Exclusive) { 0xbc }
			Interrupt(ResourceProducer, Level, ActiveHigh, Exclusive) { 0xbd }
			Interrupt(ResourceProducer, Level, ActiveHigh, Exclusive) { 0xbe }
			Interrupt(ResourceProducer, Level, ActiveHigh, Exclusive) { 0xbf }
		})
		Name(CLNM, "qm1clk") // clock-names
		Name(DVID, 0x01)     // Device ID
		Name(MQID, 0x400)     // Max QID
		Name(SLNM, "CPU_QMTM1") // Slave name
		Name(SLIF, Buffer() { 0x01, 0x00, 0x20, 0x20, 0x20 }) // Slave info
	} // QM01

	Device(QM00) {
		Name(_HID, "APMC0D04") // Device Identification Objects
		Name(_DDN, "QM00")
		Name(_UID, "QM00")
		Name(_STR, Unicode("QM 0 Device"))
		Name(_CID, "APMC0D04")
		Name(_CRS, ResourceTemplate() {
			Memory32Fixed(ReadWrite, 0x1f600000, 0x10000, )
			Memory32Fixed(ReadWrite, 0x18000000, 0x400000, )
			Interrupt(ResourceProducer, Level, ActiveHigh, Exclusive) { 0x80 }
			Interrupt(ResourceProducer, Level, ActiveHigh, Exclusive) { 0x60 }
			Interrupt(ResourceProducer, Level, ActiveHigh, Exclusive) { 0x61 }
			Interrupt(ResourceProducer, Level, ActiveHigh, Exclusive) { 0x62 }
			Interrupt(ResourceProducer, Level, ActiveHigh, Exclusive) { 0x63 }
			Interrupt(ResourceProducer, Level, ActiveHigh, Exclusive) { 0x64 }
			Interrupt(ResourceProducer, Level, ActiveHigh, Exclusive) { 0x65 }
			Interrupt(ResourceProducer, Level, ActiveHigh, Exclusive) { 0x66 }
			Interrupt(ResourceProducer, Level, ActiveHigh, Exclusive) { 0x67 }
			Interrupt(ResourceProducer, Level, ActiveHigh, Exclusive) { 0x68 }
			Interrupt(ResourceProducer, Level, ActiveHigh, Exclusive) { 0x69 }
			Interrupt(ResourceProducer, Level, ActiveHigh, Exclusive) { 0x6a }
			Interrupt(ResourceProducer, Level, ActiveHigh, Exclusive) { 0x6b }
			Interrupt(ResourceProducer, Level, ActiveHigh, Exclusive) { 0x6c }
			Interrupt(ResourceProducer, Level, ActiveHigh, Exclusive) { 0x6d }
			Interrupt(ResourceProducer, Level, ActiveHigh, Exclusive) { 0x6e }
			Interrupt(ResourceProducer, Level, ActiveHigh, Exclusive) { 0x6f }
		})
		Name(CLNM, "qmxge0clk") // clock-names
		Name(DVID, 0x00)     // Device ID
		Name(MQID, 0x400)     // Max QID
		Name(SLNM, "CPU_QMTM0") // Slave name
		Name(SLIF, Buffer() { 0x00, 0x00, 0x10, 0x20, 0x10 }) // Slave info
	} // QM00

	Device(QM02) {
		Name(_HID, "APMC0D04") // Device Identification Objects
		Name(_DDN, "QM02")
		Name(_UID, "QM02")
		Name(_STR, Unicode("QM 2 Device"))
		Name(_CID, "APMC0D04")
		Name(_CRS, ResourceTemplate() {
			Memory32Fixed(ReadWrite, 0x1f700000, 0x10000, )
			Memory32Fixed(ReadWrite, 0x1e000000, 0x400000, )
			Interrupt(ResourceProducer, Level, ActiveHigh, Exclusive) { 0xc1 }
			Interrupt(ResourceProducer, Level, ActiveHigh, Exclusive) { 0x70 }
			Interrupt(ResourceProducer, Level, ActiveHigh, Exclusive) { 0x71 }
			Interrupt(ResourceProducer, Level, ActiveHigh, Exclusive) { 0x72 }
			Interrupt(ResourceProducer, Level, ActiveHigh, Exclusive) { 0x73 }
			Interrupt(ResourceProducer, Level, ActiveHigh, Exclusive) { 0x74 }
			Interrupt(ResourceProducer, Level, ActiveHigh, Exclusive) { 0x75 }
			Interrupt(ResourceProducer, Level, ActiveHigh, Exclusive) { 0x76 }
			Interrupt(ResourceProducer, Level, ActiveHigh, Exclusive) { 0x77 }
			Interrupt(ResourceProducer, Level, ActiveHigh, Exclusive) { 0x78 }
			Interrupt(ResourceProducer, Level, ActiveHigh, Exclusive) { 0x79 }
			Interrupt(ResourceProducer, Level, ActiveHigh, Exclusive) { 0x7a }
			Interrupt(ResourceProducer, Level, ActiveHigh, Exclusive) { 0x7b }
			Interrupt(ResourceProducer, Level, ActiveHigh, Exclusive) { 0x7c }
			Interrupt(ResourceProducer, Level, ActiveHigh, Exclusive) { 0x7d }
			Interrupt(ResourceProducer, Level, ActiveHigh, Exclusive) { 0x7e }
			Interrupt(ResourceProducer, Level, ActiveHigh, Exclusive) { 0x7f }
		})
		Name(CLNM, "qmxge1clk") // clock-names
		Name(DVID, 0x02)     // Device ID
		Name(MQID, 0x400)     // Max QID
		Name(SLNM, "CPU_QMTM2") // Slave name
		Name(SLIF, Buffer() { 0x02, 0x10, 0x10, 0x30, 0x10 }) // Slave info
	} //QM02

///////////////////////////////////////////////////////////////////////////////
// Ethernet Device
	Device(ET08) {
		Name(_HID, "APMC0D05") // Device Identification Objects
		Name(_DDN, "ET08")
		Name(_UID, "ET08")
		Name(_STR, Unicode("Ethernet RGMII Device"))
		Name(_CID, "APMC0D05")
		Name(_CRS, ResourceTemplate() {
			Memory32Fixed(ReadWrite, 0x17020000, 0x30, )
			Memory32Fixed(ReadWrite, 0x17020000, 0x10000, )
			Memory32Fixed(ReadWrite, 0x17020000, 0x20, )
			Interrupt(ResourceProducer, Level, ActiveHigh, Exclusive) { 0x38 }
			Interrupt(ResourceProducer, Level, ActiveHigh, Exclusive) { 0x39 }
			Interrupt(ResourceProducer, Level, ActiveHigh, Exclusive) { 0x3a }
		})
		Name(CLNM, "eth8clk") // clock-names
		Name(DVID, 0x08)      // Device ID
		Name(SLNM, "RGMII")
		Name(SLIF, Buffer() { 0x03, 0x00, 0x04, 0x20, 0x04 })
		Name(FMSZ, 0x233a)    // Frame-size
		Name(PHID, 0x03)      // Phy ID
		Name(PHMD, "rgmii")   // PHY mode
		Name(MAC0, Buffer() { 0x00, 0x11, 0x3a, 0x8a, 0x5a, 0x78 })	// MAC Address
	}

	Device(ET00) {
		Name(_HID, "APMC0D05") // Device Identification Objects
		Name(_DDN, "ET00")
		Name(_UID, "ET00")
		Name(_STR, Unicode("Ethernet SATA-SGMII Device"))
		Name(_CID, "APMC0D05")
		Method(_STA, 0, NotSerialized) {
			Return (0x1)
		}
		Name(_CRS, ResourceTemplate() {
			Memory32Fixed(ReadWrite, 0x1f210000, 0x30, )
			Memory32Fixed(ReadWrite, 0x1f210000, 0x10000, )
			Memory32Fixed(ReadWrite, 0x17020000, 0x10000, )
			Interrupt(ResourceProducer, Level, ActiveHigh, Exclusive) { 0x8c }
			Interrupt(ResourceProducer, Level, ActiveHigh, Exclusive) { 0x8d }
			Interrupt(ResourceProducer, Level, ActiveHigh, Exclusive) { 0x90 }
		})
		Name(CLNM, "eth01clk") // clock-names
		Name(DVID, 0x00)      // Device ID
		Name(SLNM, "SGMII0")
		Name(SLIF, Buffer() { 0x01, 0x00, 0x08, 0x20, 0x08 })
		Name(FMSZ, 0x233a)    // Frame-size
		Name(PHID, 0x1e)      // Phy ID
		Name(PHMD, "sgmii")   // PHY mode
		Name(MAC0, Buffer() { 0x00, 0x11, 0x3a, 0x8a, 0x5a, 0x6c })	// MAC Address
	}

	Device(ET01) {
		Name(_HID, "APMC0D05") // Device Identification Objects
		Name(_DDN, "ET01")
		Name(_UID, "ET01")
		Name(_STR, Unicode("Ethernet SATA-SGMII Device"))
		Name(_CID, "APMC0D05")
		Method(_STA, 0, NotSerialized) {
			Return (0x1)
		}
		Name(_CRS, ResourceTemplate() {
			Memory32Fixed(ReadWrite, 0x1f210030, 0x30, )
			Memory32Fixed(ReadWrite, 0x1f210000, 0x10000, )
			Memory32Fixed(ReadWrite, 0x17020000, 0x10000, )
			Interrupt(ResourceProducer, Level, ActiveHigh, Exclusive) { 0x8c }
			Interrupt(ResourceProducer, Level, ActiveHigh, Exclusive) { 0x8d }
			Interrupt(ResourceProducer, Level, ActiveHigh, Exclusive) { 0x90 }
		})
		Name(CLNM, "eth01clk") // clock-names
		Name(DVID, 0x01)      // Device ID
		Name(SLNM, "SGMII1")
		Name(SLIF, Buffer() { 0x01, 0x08, 0x08, 0x28, 0x08 })
		Name(FMSZ, 0x233a)    // Frame-size
		Name(PHID, 0x1e)      // Phy ID
		Name(PHMD, "sgmii")   // PHY mode
		Name(MAC0, Buffer() { 0x00, 0x11, 0x3a, 0x8a, 0x5a, 0x6d })	// MAC Address
	}

	Device(ET04) {
		Name(_HID, "APMC0D05") // Device Identification Objects
		Name(_DDN, "ET04")
		Name(_UID, "ET04")
		Name(_STR, Unicode("Ethernet 10Gb Device"))
		Name(_CID, "APMC0D05")
		Method(_STA, 0, NotSerialized) {
			Return (0x1)
		}
		Name(_CRS, ResourceTemplate() {
			Memory32Fixed(ReadWrite, 0x1f610000, 0x30, )
			Memory32Fixed(ReadWrite, 0x1f610000, 0x10000, )
			Memory32Fixed(ReadWrite, 0x1f610000, 0x10000, )
			Interrupt(ResourceProducer, Level, ActiveHigh, Exclusive) { 0x50 }
			Interrupt(ResourceProducer, Level, ActiveHigh, Exclusive) { 0x51 }
			Interrupt(ResourceProducer, Level, ActiveHigh, Exclusive) { 0x52 }
		})
		Name(CLNM, "xge0clk") // clock-names
		Name(DVID, 0x04)      // Device ID
		Name(SLNM, "SXGMII0")
		Name(SLIF, Buffer() { 0x00, 0x00, 0x08, 0x20, 0x08 })
		Name(FMSZ, 0x233a)    // Frame-size
		Name(PHID, 0x01)      // Phy ID
		Name(PHMD, "xgmii")   // PHY mode
		Name(MAC0, Buffer() { 0x00, 0x11, 0x3a, 0x8a, 0x5a, 0x74})	// MAC Address
	}

	Device(ET05) {
		Name(_HID, "APMC0D05") // Device Identification Objects
		Name(_DDN, "ET05")
		Name(_UID, "ET05")
		Name(_STR, Unicode("Ethernet 10Gb Device"))
		Name(_CID, "APMC0D05")
		Method(_STA, 0, NotSerialized) {
			Return (0x0)
		}
		Name(_CRS, ResourceTemplate() {
			Memory32Fixed(ReadWrite, 0x1f620000, 0x30, )
			Memory32Fixed(ReadWrite, 0x1f620000, 0x10000, )
			Memory32Fixed(ReadWrite, 0x1f620000, 0x10000, )
			Interrupt(ResourceProducer, Level, ActiveHigh, Exclusive) { 0x53 }
			Interrupt(ResourceProducer, Level, ActiveHigh, Exclusive) { 0x54 }
			Interrupt(ResourceProducer, Level, ActiveHigh, Exclusive) { 0x55 }
		})
		Name(CLNM, "xge0clk") // clock-names
		Name(SLNM, "SXGMII1")
		Name(SLIF, Buffer() { 0x00, 0x00, 0x08, 0x20, 0x08 })
		Name(FMSZ, 0x233a)    // Frame-size
		Name(PHID, 0x01)      // Phy ID
		Name(PHMD, "xgmii")   // PHY mode
		Name(DVID, 0x05)      // Device ID
		Name(MAC0, Buffer() { 0x00, 0x11, 0x3a, 0x8a, 0x5a, 0x75})	// MAC Address
	}

}//DSDT
