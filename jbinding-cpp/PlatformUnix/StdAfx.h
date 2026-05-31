#ifndef __STDAFX_H__INCLUDED__
#define __STDAFX_H__INCLUDED__

// Allow COM methods to throw (removes nothrow attribute from STDMETHOD)
#define COM_STDMETHOD_CAN_THROW

// Remove throw() specification from interface methods for jbinding compatibility
// Must be defined before IDecl.h is included (IDecl.h checks #ifndef Z7_COM7F_E)
#define Z7_COM7F_E
#define Z7_COM7F_IMF(f)       STDMETHODIMP f
#define Z7_COM7F_IMF2(t, f)   STDMETHODIMP_(t) f
#define Z7_COM7F_EO           Z7_override
#define Z7_COM7F_EOF          Z7_override Z7_final

#include "Common/Common.h"

// Compatibility aliases for old p7zip-style MY_UNKNOWN_IMP macros
// used by jbinding code
#include "Common/MyCom.h"
#ifndef MY_UNKNOWN_IMP
#define MY_UNKNOWN_IMP Z7_COM_UNKNOWN_IMP_0
#define MY_UNKNOWN_IMP1(i) Z7_COM_UNKNOWN_IMP_1(i)
#define MY_UNKNOWN_IMP2(i1, i2) Z7_COM_UNKNOWN_IMP_2(i1, i2)
#define MY_UNKNOWN_IMP3(i1, i2, i3) Z7_COM_UNKNOWN_IMP_3(i1, i2, i3)
#define MY_UNKNOWN_IMP4(i1, i2, i3, i4) Z7_COM_UNKNOWN_IMP_4(i1, i2, i3, i4)
#define MY_UNKNOWN_IMP5(i1, i2, i3, i4, i5) Z7_COM_UNKNOWN_IMP_5(i1, i2, i3, i4, i5)
#define MY_UNKNOWN_IMP6(i1, i2, i3, i4, i5, i6) Z7_COM_UNKNOWN_IMP_6(i1, i2, i3, i4, i5, i6)
#define MY_UNKNOWN_IMP7(i1, i2, i3, i4, i5, i6, i7) Z7_COM_UNKNOWN_IMP_7(i1, i2, i3, i4, i5, i6, i7)
#endif

#include <stdlib.h>

#endif // __STDAFX_H__INCLUDED__
