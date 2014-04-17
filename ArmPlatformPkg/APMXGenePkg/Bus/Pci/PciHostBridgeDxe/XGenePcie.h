#ifndef _XGENEPCIE_H_
#define _XGENEPCIE_H_

#include "PciHostBridge.h"
#include "XGenePcieCore.h"
#include "XGenePcieSerdes.h"

#define XGENE_PCIE_FIRST_BUS         0
#define XGENE_PCIE_LAST_BUS          15


EFI_STATUS
EFIAPI
XGenePcieSetupHostPre(VOID);

EFI_STATUS
EFIAPI
XGenePcieSetupPrimaryBus(UINT32, UINT32, UINT32);

EFI_STATUS
EFIAPI
XGenePcieSetupHostPost(UINT32, PCI_HOST_BRIDGE_INSTANCE *);


#define PCIE_OP_PROTO(rw,size,type,op,mask)                               \
EFI_STATUS                                                                \
EFIAPI                                                                    \
XGenePcie##rw##Config##size(                                           \
  IN      PCI_ROOT_BRIDGE_INSTANCE *RootInstance,                         \
  IN      UINTN                     Address,                              \
  IN      type                      Val                                  \
  );

PCIE_OP_PROTO(Read,8,UINT8 *,pcie_cfg_in8,0)
PCIE_OP_PROTO(Read,16,UINT16 *,pcie_cfg_in16,1)
PCIE_OP_PROTO(Read,32,UINT32 *,pcie_cfg_in32,3)
PCIE_OP_PROTO(Write,8,UINT8,pcie_cfg_out8,0)
PCIE_OP_PROTO(Write,16,UINT16,pcie_cfg_out16,1)
PCIE_OP_PROTO(Write,32,UINT32,pcie_cfg_out32,3)

#endif /* _XGENEPCIE_H_ */
