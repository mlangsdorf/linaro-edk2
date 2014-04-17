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

#include <APMXGeneMemc.h>
#include <Uefi/UefiBaseType.h>
#include <Library/DebugLib.h>
#include <Library/TimerLib.h>

#define EFUSE0_SHADOW_ADDR_ABS                  0x1054a000UL
#define EFUSE1_SHADOW_ADDR_ABS                  0x1054a004UL


#define PMD0_DISABLE_MASK       0x00000001
#define PMD1_DISABLE_MASK       0x00000002
#define PMD2_DISABLE_MASK       0x00000004
#define PMD3_DISABLE_MASK       0x00000008
#define ALL_CPU_RESET_MASK      0x00800000
#define MAX_NUM_PMD   4
#define PCP_RB_CSW_PxRCR_ADDR                   0x7e200100UL
#define PCP_RB_CSW_PxRSR_ADDR                   0x7e200104UL
#define PCP_RB_CSW_PxRCR_STARTC0_MASK           0x1
#define PCP_RB_CSW_PxRCR_STARTC1_MASK           0x2
#define PCP_RB_CSW_PxRCR_STARTC0_STARTC1_MASK   0x3

#define u32 UINT32

/* return 1 if pmd available else return 0 */
int apm88xxxx_is_pmd_available(u32 pmd)
{
  u32 val;
  volatile void *reg;
  if (pmd >= MAX_NUM_PMD)
    return 0;

  reg = (void *)EFUSE0_SHADOW_ADDR_ABS;
  val = *((u32 *)reg);

  if (!(val & (1 << pmd)))
    return 1;
  else
    return 0;
}

/* return 1 if all cpus are out of reset else return 0 */
static inline int apm88xxxx_is_all_cpu_reset(void)
{
  u32 val;
  volatile void *reg;

  reg = (void *)EFUSE1_SHADOW_ADDR_ABS;
  val = *((u32 *)reg);

  if (val & ALL_CPU_RESET_MASK)
    return 1;
  else
    return 0;
}

int apm88xxxx_get_num_available_pmds(void)
{
  int cnt = 0;
  u32   pmd;

  for (pmd = 0; pmd < MAX_NUM_PMD; pmd++) {
    if (apm88xxxx_is_pmd_available(pmd))
      cnt ++;
  }

  return cnt;
}

int apm88xxxx_get_num_available_cores(void)
{
  return (2 * apm88xxxx_get_num_available_pmds());
}

int apm88xxxx_get_first_valid_cpuid(void)
{
  u32   pmd;

  for (pmd = 0; pmd < MAX_NUM_PMD; pmd++) {
    if (apm88xxxx_is_pmd_available(pmd)) {
      return (2 * pmd);
    }
  }
  return -1;
}

int apm88xxxx_is_core_inreset(int pmd, int core)
{
  u32 val;
  volatile void *reg;

  reg = (void *)(PCP_RB_CSW_PxRSR_ADDR + (pmd << 4));
  val = *((u32 *)reg);

  return val & (1 << core);
}

void apm88xxxx_print_valid_pmd(void)
{
  int pmd;

  DEBUG ((EFI_D_VERBOSE, "CPUs:  "));
  for (pmd = MAX_NUM_PMD - 1; pmd >= 0; pmd--) {
    if (!apm88xxxx_is_pmd_available(pmd)) {
      DEBUG ((EFI_D_VERBOSE, "XX"));
      continue;
    }
    DEBUG ((EFI_D_VERBOSE, "%c%c",
      apm88xxxx_is_core_inreset(pmd, 1) ? '0' : '1',
      apm88xxxx_is_core_inreset(pmd, 0) ? '0' : '1'));
  }
  DEBUG ((EFI_D_VERBOSE, "\n"));
}

void apm88xxxx_start_core(u32 pmd, u32 start_mask)
{
  u32 val;
  volatile void *reg;

  reg = (void *)(PCP_RB_CSW_PxRCR_ADDR + (pmd << 4));

  val = *((u32 *)reg);
  val |= start_mask;
  *((u32 *)reg) = val;
  val = *((u32 *)reg);
}

int apm88xxxx_start_secondary_cores(void)
{
  int first_valid_cpuid;
  u32 start_mask;
  u32 pmd;

  int num_cores;
  int cnt = 1;

  if (apm88xxxx_is_all_cpu_reset())
    return 0;

  first_valid_cpuid = apm88xxxx_get_first_valid_cpuid();

  /* We enable all CPUs for now */
  num_cores = MAX_NUM_PMD * 2;
  for (pmd = 0; pmd < MAX_NUM_PMD && cnt < num_cores; pmd++) {
    if (!apm88xxxx_is_pmd_available(pmd))
      continue;
    if ((2 * pmd) == first_valid_cpuid) {
      start_mask = PCP_RB_CSW_PxRCR_STARTC1_MASK;
      cnt++;
    } else if (cnt + 2 <= num_cores) {
      start_mask = PCP_RB_CSW_PxRCR_STARTC0_STARTC1_MASK;
                        cnt += 2;
    } else {
      start_mask = PCP_RB_CSW_PxRCR_STARTC0_MASK;
      cnt++;
    }
    if (apm88xxxx_is_core_inreset(pmd, 0) ||
        apm88xxxx_is_core_inreset(pmd, 1)) {
      apm88xxxx_start_core(pmd, start_mask);
    }
  }
  /* FIXME: Need to wait all CPUs initialize done here */
  MicroSecondDelay(1000000);
  apm88xxxx_print_valid_pmd();

  return 0;
}

BOOLEAN
ArmPlatformSecIsPrimaryCore (
  IN  UINTN                     MpId
  )
{
  return 1; /* FIXME */
}

/**
  Initialize the Secure peripherals and memory regions

  If Trustzone is supported by your platform then this function makes the required initialization
  of the secure peripherals and memory regions.

**/
VOID
ArmPlatformSecTrustzoneInit (
  IN  UINTN                     MpId
  )
{
  /* Do nothing */
}

/**
  Initialize controllers that must setup at the early stage

  Some peripherals must be initialized in Secure World.
  For example, some L2x0 requires to be initialized in Secure World

**/
RETURN_STATUS
ArmPlatformSecInitialize (
  IN  UINTN                     MpId
  )
{

  RETURN_STATUS Status;
  /* If it is not the primary core then there is nothing to do */
  if (!ArmPlatformSecIsPrimaryCore(MpId)) {
    return RETURN_SUCCESS;
  }

  /* Initialize DDR */
  Status = APMXGeneMemcInit();

  apm88xxxx_start_secondary_cores();

  return Status;
}

/**
  Call before jumping to Normal World

  This function allows the firmware platform to do extra actions before
  jumping to the Normal World

**/
VOID
ArmPlatformSecExtraAction (
  IN  UINTN         MpId,
  OUT EFI_PHYSICAL_ADDRESS*        JumpAddress
  )
{
  *JumpAddress = PcdGet64(PcdFvBaseAddress);
}

/**
  Call to initalize early Sec boot memory for stack space
 
 **/
VOID 
ArmPlatformSecBootMemoryInit (
  VOID
  )
{
  /* Do nothing as stack is located on OCM and its is already initalized */
}

VOID
ArmCpuSetup (
  IN  UINTN         MpId
  )
{
  /* Do nothing */
}
