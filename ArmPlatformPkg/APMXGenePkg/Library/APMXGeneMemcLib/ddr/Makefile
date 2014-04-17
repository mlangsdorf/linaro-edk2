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
##

include $(TOPDIR)/config.mk

LIB	= $(obj)libddr.o

COBJS-y	+= ddr_main.o
COBJS-y	+= ddr_spd.o
COBJS-y	+= ddr_mcu.o
COBJS-y	+= ddr_phy.o
COBJS-y += ddr_config.o
COBJS-y += ddr_addrmap.o
COBJS-y	+= ddr_util.o
COBJS-y	+= kc_phy_util_tasks.o
COBJS-y	+= kc_phy_util_reg_flds.o
COBJS-y	+= pop_mc_cfg_def_1mcu_1mcu_ddr800D_6_5_x8_1RK2G.o
COBJS-y += pop_mc_cfg_def_1mcu_1mcu_ddr1066F_8_6_x8_1RK2G.o
COBJS-y += pop_mc_cfg_def_1mcu_1mcu_ddr1333H_9_7_x8_1RK2G.o
COBJS-y	+= pop_mc_cfg_def_1mcu_1mcu_ddr1550J_x8_1RK2G.o
COBJS-y	+= pop_mc_cfg_def_1mcu_1mcu_ddr1600J_x8_1RK2G.o
#COBJS-y	+= ddr_driver.o sushant main init file

COBJS-$(CONFIG_FIXED_DDR_INIT)	+= ddr_fixed_configs.o

SRCS	:= $(START:.o=.S) $(SOBJS-y:.o=.S) $(COBJS-y:.o=.c)
OBJS	:= $(addprefix $(obj),$(SOBJS-y) $(COBJS-y))

all:	$(obj).depend $(LIB)

$(LIB):	$(OBJS)
	$(call cmd_link_o_target, $(OBJS))

include $(SRCTREE)/rules.mk

sinclude $(obj).depend
