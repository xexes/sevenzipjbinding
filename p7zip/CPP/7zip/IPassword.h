// IPassword.h

#ifndef __IPASSWORD_H
#define __IPASSWORD_H

#include "../Common/MyTypes.h"
#include "../Common/MyUnknown.h"

#include "IDecl.h"

#define PASSWORD_INTERFACE(i, x) DECL_INTERFACE(i, 5, x)

#define Z7_IFACEM_ICryptoGetTextPassword(x) \
  x(CryptoGetTextPassword(BSTR *password))

PASSWORD_INTERFACE(ICryptoGetTextPassword, 0x10)
{
  STDMETHOD(CryptoGetTextPassword)(BSTR *password) PURE;
};

#define Z7_IFACEM_ICryptoGetTextPassword2(x) \
  x(CryptoGetTextPassword2(Int32 *passwordIsDefined, BSTR *password))

PASSWORD_INTERFACE(ICryptoGetTextPassword2, 0x11)
{
  STDMETHOD(CryptoGetTextPassword2)(Int32 *passwordIsDefined, BSTR *password) PURE;
};

#endif
