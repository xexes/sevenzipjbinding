#ifndef __JAVA_IN_STREAM_H__INCLUDED__

#include "CPPToJavaSequentialInStream.h"

class CPPToJavaInStream : public virtual IInStream, public CPPToJavaSequentialInStream
{
private:
    jni::ISeekableStream * _iSeekableStream;
public:
    // IInStream inherits ISequentialInStream non-virtually, creating a second IUnknown path.
    // Must provide AddRef/Release explicitly to satisfy both vtable slots.
    STDMETHOD_(ULONG, AddRef)() throw() Z7_override
        { return ++_m_RefCount; }
    STDMETHOD_(ULONG, Release)() throw() Z7_override
        { if (--_m_RefCount != 0) return _m_RefCount; delete this; return 0; }

public:
	CPPToJavaInStream(JBindingSession & jbindingSession, JNIEnv * initEnv, jobject inStream) :
		CPPToJavaSequentialInStream(jbindingSession, initEnv, inStream),
		        _iSeekableStream(jni::ISeekableStream::_getInstanceFromObject(initEnv, inStream))
	{
	    TRACE_OBJECT_CREATION("CPPToJavaInStream")

	}

	virtual ~CPPToJavaInStream() {}

	STDMETHOD(Read)(void *data, UInt32 size, UInt32 *processedSize)
	{
		TRACE("READ(size=" << size << ")")
		HRESULT result = CPPToJavaSequentialInStream::Read(data, size, processedSize);
#ifdef TRACE_ON
		if (processedSize) {
			TRACE("READ: size=" << size << ", was read:" << *processedSize << ", result:" << result);
		}
#endif
		return result;
	}

	// Override QueryInterface to add IInStream support (base class is non-final)
	STDMETHOD(QueryInterface)(REFGUID iid, void ** outObject) throw() Z7_override
	{
		if (iid == IID_IInStream)
	    {
	        *outObject = (void *)(IInStream *)this;
	        CPPToJavaSequentialInStream::AddRef();  // Explicitly qualify to resolve ambiguity
	        return S_OK;
	    }
		return CPPToJavaSequentialInStream::QueryInterface(iid, outObject);
	}

	STDMETHOD(Seek)(Int64 offset, UInt32 seekOrigin, UInt64 *newPosition);
};

#define __JAVA_IN_STREAM_H__INCLUDED__
#endif // __JAVA_IN_STREAM_H__INCLUDED__
