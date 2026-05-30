// IDecl.h

#ifndef __IDECL_H
#define __IDECL_H

#include "../Common/MyUnknown.h"

#define k_7zip_GUID_Data1 0x23170F69
#define k_7zip_GUID_Data2 0x40C1

#define k_7zip_GUID_Data3_Common  0x278A

#define k_7zip_GUID_Data3_Decoder 0x2790
#define k_7zip_GUID_Data3_Encoder 0x2791
#define k_7zip_GUID_Data3_Hasher  0x2792


#define DECL_INTERFACE_SUB(i, base, groupId, subId) \
  DEFINE_GUID(IID_ ## i, \
    k_7zip_GUID_Data1, \
    k_7zip_GUID_Data2, \
    k_7zip_GUID_Data3_Common, \
    0, 0, 0, (groupId), 0, (subId), 0, 0); \
  struct i: public base

#define DECL_INTERFACE(i, groupId, subId) DECL_INTERFACE_SUB(i, IUnknown, groupId, subId)

// Define 7-Zip specific interface macros
#define Z7_DECL_IFACE_7ZIP_SUB(i, base, groupId, subId) DECL_INTERFACE_SUB(i, base, groupId, subId)
#define Z7_DECL_IFACE_7ZIP(i, groupId, subId) DECL_INTERFACE(i, groupId, subId)

// Z7_IFACE_PURE(name): generate pure virtual declarations for ALL methods of interface 'name'
// Uses Z7_IFACEN_##name macro (e.g. Z7_IFACEN_IOpenCallbackUI) with "=0;" suffix.
// Used inside class/struct bodies to declare abstract interface methods.
#define Z7_IFACE_PURE(name)               Z7_IFACEN_ ## name(=0;)

// Z7_IFACE_IMP(name): generate override+final declarations for ALL methods of interface 'name'
// Uses Z7_IFACEN_##name macro with "Z7_override Z7_final;" suffix.
// Used inside concrete class bodies to declare overriding implementations.
#define Z7_IFACE_IMP(name)                Z7_IFACEN_ ## name(Z7_override Z7_final;)

// Z7_IFACE_DECL_PURE: declare a pure virtual interface struct using Z7_IFACEN_ macros
// These are used for UI-level (non-COM) interfaces that define Z7_IFACEN_* macros
#define Z7_IFACE_DECL_PURE_(i, base) \
  struct i : public base \
  { Z7_IFACE_PURE(i) };

#define Z7_IFACE_DECL_PURE(i) \
  struct i : public IUnknown \
  { Z7_IFACE_PURE(i) };

#endif
