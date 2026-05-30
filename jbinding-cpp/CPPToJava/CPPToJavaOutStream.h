#ifndef __JAVA_OUT_STREAM_H__INCLUDED__

#include "CPPToJavaSequentialOutStream.h"

class CPPToJavaOutStream : public virtual IOutStream, public CPPToJavaSequentialOutStream {
private:
    jni::IOutStream * _iOutStream;
    jni::ISeekableStream * _iSeekableStream;

public:
    // IOutStream inherits ISequentialOutStream non-virtually, creating a second IUnknown path.
    // Must provide AddRef/Release explicitly to satisfy both vtable slots.
    STDMETHOD_(ULONG, AddRef)() throw() Z7_override
        { return ++_m_RefCount; }
    STDMETHOD_(ULONG, Release)() throw() Z7_override
        { if (--_m_RefCount != 0) return _m_RefCount; delete this; return 0; }

public:
    CPPToJavaOutStream(JBindingSession & jbindingSession, JNIEnv * initEnv, jobject inStream) :
        CPPToJavaSequentialOutStream(jbindingSession, initEnv, inStream), //
                _iOutStream(jni::IOutStream::_getInstanceFromObject(initEnv, inStream)), //
                _iSeekableStream(jni::ISeekableStream::_getInstanceFromObject(initEnv, inStream)) {
        TRACE_OBJECT_CREATION("CPPToJavaOutStream")
    }

    STDMETHOD(Write)(const void *data, UInt32 size, UInt32 *processedSize) {
        TRACE("WRITE(size=" << size << ")")
        HRESULT result = CPPToJavaSequentialOutStream::Write(data, size, processedSize);
#ifdef TRACE_ON
        if (processedSize) {
            TRACE("WRITE: size=" << size << ", was written:" << *processedSize << ", result:" << result);
        }
#endif
        return result;
    }

    STDMETHOD(QueryInterface)(REFGUID iid, void ** outObject) throw() Z7_override {
        if (iid == IID_IOutStream) {
            *outObject = (void *) (IOutStream *) this;
            CPPToJavaSequentialOutStream::AddRef();  // Explicitly qualify to resolve ambiguity
            return S_OK;
        }

        return CPPToJavaSequentialOutStream::QueryInterface(iid, outObject);
    }

    // Inherit AddRef and Release from base class (no need to override)

    STDMETHOD(Seek)(Int64 offset, UInt32 seekOrigin, UInt64 *newPosition);

    STDMETHOD(SetSize)(UInt64 newSize);
};

#define __JAVA_OUT_STREAM_H__INCLUDED__
#endif // __JAVA_OUT_STREAM_H__INCLUDED__
