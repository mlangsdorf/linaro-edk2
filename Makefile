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

# SHELL:=/bin/bash
EDK2DIR=$(shell pwd)
EDK2TOOLSDIR=$(EDK2DIR)/BaseTools
export EDK_TOOLS_PATH=$(EDK2TOOLSDIR)

export ARCH=
export CROSS_COMPILE:=aarch64-linux-gnu-
export CROSS_COMPILER_PATH:=/usr/bin
export ASL_BIN_DIR:=/usr/bin

export FEDORA_CROSS:=/bin/aarch64-linux-gnu-
export LINARO_CROSS:=/opt/gcc-linaro-aarch64-linux-gnu-4.8-2014.02_linux/bin/aarch64-linux-gnu-

UEFI_TOOLS=../uefi-tools


all: clean basetools tianocore tianocore_apps
.PHONY : all

debug: clean basetools tianocore_debug tianocore_apps_debug
.PHONY : debug

linaro: clean basetools linaro_build
.PHONY : linaro

linaro_debug: clean basetools linaro_build_debug
.PHONY : linaro_debug

clean: clean_tianocore clean_tianocore_debug clean_basetools clean_linaro_tools clean_foundation clean_fvp
	@echo
	@echo "############################### Clean APM Binary Files ###########################"
	rm -rf $(EDK2DIR)/Build/APMXGene-Mustang

clean_conf:
	rm -rf $(EDK2DIR)/Conf/.cache
	rm -rf $(EDK2DIR)/Conf/BuildEnv.sh
	rm -rf $(EDK2DIR)/Conf/build_rule.txt
	rm -rf $(EDK2DIR)/Conf/target.txt
	rm -rf $(EDK2DIR)/Conf/tools_def.txt

reallyclean: clean_conf clean_tianocore clean_tianocore_debug clean_tianocore_VHP_debug clean_tianocore_VHP clean_basetools
	@echo
	@echo "############################### Clean Binary Files ###########################"
	rm -rf $(EDK2DIR)/Build/APMXGene-Mustang

clean_linaro_tools:
	@echo
	@echo "################################# Clean Linaro Tools ############################"
	cd $(EDK2DIR) && \
	.  $(EDK2DIR)/edksetup.sh && \
	rm -f uefi-build.sh platforms.config parse-platforms.sh

clean_basetools:
	@echo
	@echo "################################# Clean BaseTools ############################"
	find $(EDK2TOOLSDIR) -type f -name \*.d -exec rm -f {} \;
	cd $(EDK2DIR) && \
	.  $(EDK2DIR)/edksetup.sh && \
	make -C $(EDK2TOOLSDIR) clean

clean_tianocore:
	@touch $(EDK2DIR)/ArmPlatformPkg/APMXGenePkg/DeviceTree/DeviceTree.c
	@echo
	@echo "################################# Clean TianoCore ############################"
	cd $(EDK2DIR) && \
	.  $(EDK2DIR)/edksetup.sh && \
	AARCH64LINUXGCC_TOOLS=${CROSS_COMPILER_PATH}/${CROSS_COMPILE} build -v -b RELEASE -a AARCH64 -t ARMLINUXGCC -p ArmPlatformPkg/APMXGenePkg/APMXGene-Mustang.dsc clean

clean_tianocore_VHP:
	@echo
	@echo "################################# Clean TianoCore VHP ############################"
	cd $(EDK2DIR) && \
	.  $(EDK2DIR)/edksetup.sh && \
	AARCH64LINUXGCC_TOOLS=${CROSS_COMPILER_PATH}/${CROSS_COMPILE} build -v -b RELEASE -a AARCH64 -t ARMLINUXGCC -p ArmPlatformPkg/APMXGenePkg/APMXGene-Mustang-VHP.dsc clean

clean_tianocore_VHP_debug:
	@echo
	@echo "################################# Clean TianoCore VHP Debug ############################"
	cd $(EDK2DIR) && \
	.  $(EDK2DIR)/edksetup.sh && \
	AARCH64LINUXGCC_TOOLS=${CROSS_COMPILER_PATH}/${CROSS_COMPILE} build -v -b DEBUG -a AARCH64 -t ARMLINUXGCC -p ArmPlatformPkg/APMXGenePkg/APMXGene-Mustang-VHP.dsc clean

clean_tianocore_UHP_debug:
	@echo
	@echo "################################# Clean TianoCore UHP Debug ############################"
	cd $(EDK2DIR) && \
	.  $(EDK2DIR)/edksetup.sh && \
	AARCH64LINUXGCC_TOOLS=${CROSS_COMPILER_PATH}/${CROSS_COMPILE} build -v -b DEBUG -a AARCH64 -t ARMLINUXGCC -p ArmPlatformPkg/APMXGenePkg/APMXGene-Mustang-UHP.dsc clean

clean_tianocore_debug:
	@touch $(EDK2DIR)/ArmPlatformPkg/APMXGenePkg/DeviceTree/DeviceTree.c
	@echo
	@echo "################################# Clean TianoCore Debug ############################"
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
	AARCH64LINUXGCC_TOOLS=${CROSS_COMPILER_PATH}/${CROSS_COMPILE} build -v -D AARCH64_MP_PROTOCOL -D EDK2_ARMVE_UEFI2_SHELL -b RELEASE -a AARCH64 -t ARMLINUXGCC -p ArmPlatformPkg/APMXGenePkg/APMXGene-Mustang.dsc

tianocore_UHP:
	@echo
	@echo "################################# Build TianoCore UHP ############################"
	cd $(EDK2DIR) && \
	.  $(EDK2DIR)/edksetup.sh && \
	AARCH64LINUXGCC_TOOLS=${CROSS_COMPILER_PATH}/${CROSS_COMPILE} build -v -D EDK2_ARMVE_UEFI2_SHELL -b RELEASE -a AARCH64 -t ARMLINUXGCC -p ArmPlatformPkg/APMXGenePkg/APMXGene-Mustang-UHP.dsc

tianocore_VHP:
	@echo
	@echo "################################# Build TianoCore VHP ############################"
	cd $(EDK2DIR) && \
	.  $(EDK2DIR)/edksetup.sh && \
	AARCH64LINUXGCC_TOOLS=${CROSS_COMPILER_PATH}/${CROSS_COMPILE} build -v -D EDK2_ARMVE_UEFI2_SHELL -b RELEASE -a AARCH64 -t ARMLINUXGCC -p ArmPlatformPkg/APMXGenePkg/APMXGene-Mustang-VHP.dsc

tianocore_VHP_debug:
	@echo
	@echo "################################# Build TianoCore Debug ############################"
	cd $(EDK2DIR) && \
	.  $(EDK2DIR)/edksetup.sh && \
	AARCH64LINUXGCC_TOOLS=${CROSS_COMPILER_PATH}/${CROSS_COMPILE} build -v -D EDK2_ARMVE_UEFI2_SHELL -b DEBUG -a AARCH64 -t ARMLINUXGCC -p ArmPlatformPkg/APMXGenePkg/APMXGene-Mustang-VHP.dsc

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

clean_foundation:
	@echo
	@echo "################################# Clean Foundation ############################"
	rm -rf Build/ArmVExpress-RTSM-AEMv8Ax4-foundation

foundation:
	@echo
	@echo "################################# Build Foundation ############################"
	. ./edksetup.sh && \
	CROSS_COMPILE=${FEDORA_CROSS} build -v -D EDK2_ARMVE_UEFI2_SHELL -b RELEASE -a AARCH64 -t ARMLINUXGCC -p ArmPlatformPkg/ArmVExpressPkg/ArmVExpress-RTSM-AEMv8Ax4-foundation.dsc

foundation_debug:
	@echo
	@echo "################################# Build Foundation Debug ############################"
	. ./edksetup.sh && \
	CROSS_COMPILE=${FEDORA_CROSS} build -v -D EDK2_ARMVE_UEFI2_SHELL -b DEBUG -a AARCH64 -t ARMLINUXGCC -p ArmPlatformPkg/ArmVExpressPkg/ArmVExpress-RTSM-AEMv8Ax4-foundation.dsc

clean_fvp:
	@echo
	@echo "################################# Clean FVP ############################"
	rm -rf Build/ArmVExpress-FVP-AArch64

fvp:
	@echo
	@echo "################################# Build FVP ############################"
	. ./edksetup.sh && \
	CROSS_COMPILE=${LINARO_CROSS} build -v -D EDK2_ARMVE_UEFI2_SHELL -b RELEASE -a AARCH64 -t ARMLINUXGCC -p ArmPlatformPkg/ArmVExpressPkg/ArmVExpress-FVP-AArch64.dsc

fvp_debug:
	@echo
	@echo "################################# Build FVP ############################"
	. ./edksetup.sh && \
	CROSS_COMPILE=${LINARO_CROSS} build -v -D EDK2_ARMVE_UEFI2_SHELL -b DEBUG -a AARCH64 -t ARMLINUXGCC -p ArmPlatformPkg/ArmVExpressPkg/ArmVExpress-FVP-AArch64.dsc

uefi-build.sh platforms.config parse-platforms.sh:
	@[ -d $(UEFI_TOOLS) ] || (echo "Please git clone $(UEFI_TOOLS) first." ; exit 1)
	ln -s $(UEFI_TOOLS)/$@

linaro_tools: uefi-build.sh platforms.config parse-platforms.sh

linaro_build: linaro_tools
	./uefi-build.sh -b RELEASE apm_mustang

linaro_build_debug: linaro_tools
	./uefi-build.sh -b DEBUG apm_mustang

