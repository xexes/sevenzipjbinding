#ifndef CPPTOJAVAARCHIVEEXTRACTCALLBACK_H_
#define CPPTOJAVAARCHIVEEXTRACTCALLBACK_H_

#include "CPPToJavaProgress.h"
#include "CPPToJavaCryptoGetTextPassword.h"

class CPPToJavaArchiveExtractCallback : public virtual IArchiveExtractCallback,
        public virtual ICryptoGetTextPassword, public virtual CPPToJavaProgress {
private:
    ICryptoGetTextPassword * _cryptoGetTextPasswordImpl;
    jni::IArchiveExtractCallback * _iArchiveExtractCallback;

public:
    // IArchiveExtractCallback and ICryptoGetTextPassword each have non-virtual IUnknown paths.
    // Must provide AddRef/Release explicitly to satisfy all vtable slots.
    STDMETHOD_(ULONG, AddRef)() throw() Z7_override
        { return ++_m_RefCount; }
    STDMETHOD_(ULONG, Release)() throw() Z7_override
        { if (--_m_RefCount != 0) return _m_RefCount; delete this; return 0; }

public:
    CPPToJavaArchiveExtractCallback(JBindingSession & jbindingSession, JNIEnv * initEnv,
                                    jobject archiveExtractCallbackImpl) :
        CPPToJavaProgress(jbindingSession, initEnv, archiveExtractCallbackImpl),
                _iArchiveExtractCallback(jni::IArchiveExtractCallback::_getInstanceFromObject(
                        initEnv, archiveExtractCallbackImpl)) {
        TRACE_OBJECT_CREATION("CPPToJavaArchiveExtractCallback")

        jclass cryptoGetTextPasswordClass = initEnv->FindClass(CRYPTOGETTEXTPASSWORD_CLASS);
        FATALIF(cryptoGetTextPasswordClass == NULL,
                "Can't find class " CRYPTOGETTEXTPASSWORD_CLASS);

        if (initEnv->IsInstanceOf(_javaImplementation, cryptoGetTextPasswordClass)) {
            CMyComPtr<ICryptoGetTextPassword> cryptoGetTextPasswordComPtr =
                    new CPPToJavaCryptoGetTextPassword(_jbindingSession, initEnv,
                            _javaImplementation);
            _cryptoGetTextPasswordImpl = cryptoGetTextPasswordComPtr.Detach();
        } else {
            _cryptoGetTextPasswordImpl = NULL;
        }

    }

    ~CPPToJavaArchiveExtractCallback() {
        TRACE_OBJECT_CALL("~CPPToJavaArchiveExtractCallback");

        if (_cryptoGetTextPasswordImpl) {
            _cryptoGetTextPasswordImpl->Release();
        }
    }

    STDMETHOD(QueryInterface)(REFGUID refguid, void ** p) throw() Z7_override {
        TRACE_OBJECT_CALL("QueryInterface");

        if (refguid == IID_ICryptoGetTextPassword && _cryptoGetTextPasswordImpl) {
            *p = (void *) (ICryptoGetTextPassword *) _cryptoGetTextPasswordImpl;
            _cryptoGetTextPasswordImpl->AddRef();
            return S_OK;
        }

        return CPPToJavaProgress::QueryInterface(refguid, p);
    }

    // Inherit AddRef and Release from CPPToJavaProgress (non-final now)

    STDMETHOD(SetTotal)(UInt64 total) {
        TRACE_OBJECT_CALL("SetTotal");
        return CPPToJavaProgress::SetTotal(total);
    }

    STDMETHOD(SetCompleted)(const UInt64 *completeValue) {
        TRACE_OBJECT_CALL("SetCompleted");
        return CPPToJavaProgress::SetCompleted(completeValue);
    }

    STDMETHOD(CryptoGetTextPassword)(BSTR *password) {
        TRACE_OBJECT_CALL("CryptoGetTextPassword");

        if (_cryptoGetTextPasswordImpl) {
            return _cryptoGetTextPasswordImpl->CryptoGetTextPassword(password);
        }

        return E_NOINTERFACE;
    }

    STDMETHOD(GetStream)(UInt32 index, ISequentialOutStream **outStream, Int32 askExtractMode);

    /*
     * FROM 7-ZIP:
     *
     * GetStream OUT: S_OK - OK, S_FALSE - skeep this file
     *
     */
    STDMETHOD(PrepareOperation)(Int32 askExtractMode);
    STDMETHOD(SetOperationResult)(Int32 resultEOperationResult);
};

#endif /*CPPTOJAVAARCHIVEEXTRACTCALLBACK_H_*/
