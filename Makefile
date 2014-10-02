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
#  APM X-Gene TianoCore Makefile
#
##

SHELL:=/bin/bash
EDK2DIR=$(shell pwd)
EDK2TOOLSDIR=$(EDK2DIR)/BaseTools
export EDK_TOOLS_PATH=$(EDK2TOOLSDIR)

export ARCH=arm64
#export CROSS_COMPILE:=aarch64-apm-linux-gnu-
#export CROSS_COMPILER_PATH:=/tools/arm/armv8/Theobroma/opt/apm-aarch64/6.0.4/bin
export ASL_BIN_DIR:=$(shell pwd)/../tools/acpi
export IASL_PREFIX:=$(shell pwd)/../tools/acpi/usr/bin/

all: clean basetools tianocore tianocore_apps
.PHONY : all

debug: clean basetools tianocore_debug tianocore_apps_debug
.PHONY : debug


clean: clean_tianocore clean_tianocore_debug clean_tianocore_apps clean_tianocore_apps_debug clean_tianocore_UHP clean_tianocore_UHP_debug clean_tianocore_GFC clean_tianocore_GFC_debug  clean_basetools
	@echo
	@echo "############################### Clean APM Binary Files ###########################"
	rm -rf $(EDK2DIR)/Build/APMXGene-Mustang

clean_conf:
	rm -rf $(EDK2DIR)/Conf/.cache
	rm -rf $(EDK2DIR)/Conf/BuildEnv.sh
	rm -rf $(EDK2DIR)/Conf/build_rule.txt
	rm -rf $(EDK2DIR)/Conf/target.txt
	rm -rf $(EDK2DIR)/Conf/tools_def.txt

reallyclean: clean_conf clean
	@echo
	@echo "############################### Clean Binary Files ###########################"
	rm -rf $(EDK2DIR)/Build/APMXGene-Mustang

clean_basetools:
	@echo
	@echo "################################# Clean BaseTools ############################"
	find $(EDK2TOOLSDIR) -type f -name \*.d -exec rm -f {} \;
	cd $(EDK2DIR) && \
	.  $(EDK2DIR)/edksetup.sh && \
	make -C $(EDK2TOOLSDIR) clean

clean_tianocore:
	@echo
	@echo "################################# Clean TianoCore ############################"
	@touch $(EDK2DIR)/ArmPlatformPkg/APMXGenePkg/DeviceTree/DeviceTree.c
	cd $(EDK2DIR) && \
	.  $(EDK2DIR)/edksetup.sh && \
	AARCH64LINUXGCC_TOOLS=${CROSS_COMPILER_PATH}/${CROSS_COMPILE} build -v -b RELEASE -a AARCH64 -t ARMLINUXGCC -p ArmPlatformPkg/APMXGenePkg/APMXGene-Mustang.dsc clean

clean_tianocore_GFC:
	@echo
	@echo "################################# Clean TianoCore GFC ############################"
	@touch $(EDK2DIR)/ArmPlatformPkg/APMXGenePkg/DeviceTree/DeviceTree.c
	cd $(EDK2DIR) && \
	.  $(EDK2DIR)/edksetup.sh && \
	AARCH64LINUXGCC_TOOLS=${CROSS_COMPILER_PATH}/${CROSS_COMPILE} build -v -b RELEASE -a AARCH64 -t ARMLINUXGCC -p ArmPlatformPkg/APMXGenePkg/APMXGene-Mustang-GFC.dsc clean

clean_tianocore_GFC_debug:
	@echo
	@echo "################################# Clean TianoCore GFC Debug ############################"
	@touch $(EDK2DIR)/ArmPlatformPkg/APMXGenePkg/DeviceTree/DeviceTree.c
	cd $(EDK2DIR) && \
	.  $(EDK2DIR)/edksetup.sh && \
	AARCH64LINUXGCC_TOOLS=${CROSS_COMPILER_PATH}/${CROSS_COMPILE} build -v -b DEBUG -a AARCH64 -t ARMLINUXGCC -p ArmPlatformPkg/APMXGenePkg/APMXGene-Mustang-GFC.dsc clean

clean_tianocore_UHP:
	@echo
	@echo "################################# Clean TianoCore UHP Debug ############################"
	@touch $(EDK2DIR)/ArmPlatformPkg/APMXGenePkg/DeviceTree/DeviceTree.c
	cd $(EDK2DIR) && \
	.  $(EDK2DIR)/edksetup.sh && \
	AARCH64LINUXGCC_TOOLS=${CROSS_COMPILER_PATH}/${CROSS_COMPILE} build -v -b RELEASE -a AARCH64 -t ARMLINUXGCC -p ArmPlatformPkg/APMXGenePkg/APMXGene-Mustang-UHP.dsc clean

clean_tianocore_UHP_debug:
	@echo
	@echo "################################# Clean TianoCore UHP Debug ############################"
	@touch $(EDK2DIR)/ArmPlatformPkg/APMXGenePkg/DeviceTree/DeviceTree.c
	cd $(EDK2DIR) && \
	.  $(EDK2DIR)/edksetup.sh && \
	AARCH64LINUXGCC_TOOLS=${CROSS_COMPILER_PATH}/${CROSS_COMPILE} build -v -b DEBUG -a AARCH64 -t ARMLINUXGCC -p ArmPlatformPkg/APMXGenePkg/APMXGene-Mustang-UHP.dsc clean

clean_tianocore_debug:
	@echo
	@echo "################################# Clean TianoCore Debug ############################"
	@touch $(EDK2DIR)/ArmPlatformPkg/APMXGenePkg/DeviceTree/DeviceTree.c
	cd $(EDK2DIR) && \
	.  $(EDK2DIR)/edksetup.sh && \
	AARCH64LINUXGCC_TOOLS=${CROSS_COMPILER_PATH}/${CROSS_COMPILE} build -v -b DEBUG -a AARCH64 -t ARMLINUXGCC -p ArmPlatformPkg/APMXGenePkg/APMXGene-Mustang.dsc clean

clean_tianocore_apps:
	@echo
	@echo "################################# Clean TianoCore Debug ############################"
	cd $(EDK2DIR) && \
	.  $(EDK2DIR)/edksetup.sh && \
	AARCH64LINUXGCC_TOOLS=${CROSS_COMPILER_PATH}/${CROSS_COMPILE} build -v -b RELEASE -a AARCH64 -t ARMLINUXGCC -p ArmPlatformPkg/APMXGenePkg/Applications/AppPkg.dsc clean

clean_tianocore_apps_debug:
	@echo
	@echo "################################# Clean TianoCore Debug ############################"
	cd $(EDK2DIR) && \
	.  $(EDK2DIR)/edksetup.sh && \
	AARCH64LINUXGCC_TOOLS=${CROSS_COMPILER_PATH}/${CROSS_COMPILE} build -v -b DEBUG -a AARCH64 -t ARMLINUXGCC -p ArmPlatformPkg/APMXGenePkg/Applications/AppPkg.dsc clean

basetools:
	@echo
	@echo "############################## Build TianoCore Tools #########################"
	cd $(EDK2DIR) && \
	.  $(EDK2DIR)/edksetup.sh && \
	make -C $(EDK2TOOLSDIR)

tianocore:
	@echo
	@echo "################################# Build TianoCore ############################"
	cd $(EDK2DIR)/ArmPlatformPkg/APMXGenePkg/DeviceTree && ./makedtb.sh
	cd $(EDK2DIR) && \
	.  $(EDK2DIR)/edksetup.sh && \
	AARCH64LINUXGCC_TOOLS=${CROSS_COMPILER_PATH}/${CROSS_COMPILE} build -v -D EDK2_ARMVE_UEFI2_SHELL -b RELEASE -a AARCH64 -t ARMLINUXGCC -p ArmPlatformPkg/APMXGenePkg/APMXGene-Mustang.dsc

tianocore_UHP:
	@echo
	@echo "################################# Build TianoCore UHP ############################"
	cd $(EDK2DIR)/ArmPlatformPkg/APMXGenePkg/DeviceTree && ./makedtb.sh
	cd $(EDK2DIR) && \
	.  $(EDK2DIR)/edksetup.sh && \
	AARCH64LINUXGCC_TOOLS=${CROSS_COMPILER_PATH}/${CROSS_COMPILE} build -v -D EDK2_ARMVE_UEFI2_SHELL -b RELEASE -a AARCH64 -t ARMLINUXGCC -p ArmPlatformPkg/APMXGenePkg/APMXGene-Mustang-UHP.dsc

tianocore_GFC:
	@echo
	@echo "################################# Build TianoCore GFC ############################"
	cd $(EDK2DIR)/ArmPlatformPkg/APMXGenePkg/DeviceTree && ./makedtb.sh
	cd $(EDK2DIR) && \
	.  $(EDK2DIR)/edksetup.sh && \
	AARCH64LINUXGCC_TOOLS=${CROSS_COMPILER_PATH}/${CROSS_COMPILE} build -v -D EDK2_ARMVE_UEFI2_SHELL -b RELEASE -a AARCH64 -t ARMLINUXGCC -p ArmPlatformPkg/APMXGenePkg/APMXGene-Mustang-GFC.dsc

tianocore_GFC_debug:
	@echo
	@echo "################################# Build TianoCore Debug ############################"
	cd $(EDK2DIR)/ArmPlatformPkg/APMXGenePkg/DeviceTree && ./makedtb.sh
	cd $(EDK2DIR) && \
	.  $(EDK2DIR)/edksetup.sh && \
	AARCH64LINUXGCC_TOOLS=${CROSS_COMPILER_PATH}/${CROSS_COMPILE} build -v -D EDK2_ARMVE_UEFI2_SHELL -b DEBUG -a AARCH64 -t ARMLINUXGCC -p ArmPlatformPkg/APMXGenePkg/APMXGene-Mustang-GFC.dsc

tianocore_debug:
	@echo
	@echo "################################# Build TianoCore Debug ############################"
	cd $(EDK2DIR)/ArmPlatformPkg/APMXGenePkg/DeviceTree && ./makedtb.sh
	cd $(EDK2DIR) && \
	.  $(EDK2DIR)/edksetup.sh && \
	AARCH64LINUXGCC_TOOLS=${CROSS_COMPILER_PATH}/${CROSS_COMPILE} build -v -D EDK2_ARMVE_UEFI2_SHELL -b DEBUG -a AARCH64 -t ARMLINUXGCC -p ArmPlatformPkg/APMXGenePkg/APMXGene-Mustang.dsc

tianocore_UHP_debug:
	@echo
	@echo "################################# Build TianoCore UHP Debug ############################"
	cd $(EDK2DIR)/ArmPlatformPkg/APMXGenePkg/DeviceTree && ./makedtb.sh
	cd $(EDK2DIR) && \
	.  $(EDK2DIR)/edksetup.sh && \
	AARCH64LINUXGCC_TOOLS=${CROSS_COMPILER_PATH}/${CROSS_COMPILE} build -v -D EDK2_ARMVE_UEFI2_SHELL -b DEBUG -a AARCH64 -t ARMLINUXGCC -p ArmPlatformPkg/APMXGenePkg/APMXGene-Mustang-UHP.dsc

tianocore_apps:
	@echo
	@echo "################################# Build TianoCore Debug ############################"
	cd $(EDK2DIR) && \
	.  $(EDK2DIR)/edksetup.sh && \
	AARCH64LINUXGCC_TOOLS=${CROSS_COMPILER_PATH}/${CROSS_COMPILE} build -v -D EDK2_ARMVE_UEFI2_SHELL -b RELEASE -a AARCH64 -t ARMLINUXGCC -p ArmPlatformPkg/APMXGenePkg/Applications/AppPkg.dsc

tianocore_apps_debug:
	@echo
	@echo "################################# Build TianoCore Debug ############################"
	cd $(EDK2DIR) && \
	.  $(EDK2DIR)/edksetup.sh && \
	AARCH64LINUXGCC_TOOLS=${CROSS_COMPILER_PATH}/${CROSS_COMPILE} build -v -D EDK2_ARMVE_UEFI2_SHELL -b DEBUG -a AARCH64 -t ARMLINUXGCC -p ArmPlatformPkg/APMXGenePkg/Applications/AppPkg.dsc
