#ifndef CPPTOJAVASEQUENTIALINSTREAM_H_
#define CPPTOJAVASEQUENTIALINSTREAM_H_

#include "7zip/Archive/IArchive.h"
#include "Common/MyCom.h"

#include "CPPToJavaAbstract.h"

#include "JavaStatInfos/JavaPackageSevenZip.h"

// Custom non-final COM implementation for classes that will be inherited
// Based on Z7_COM_UNKNOWN_IMP_1 but without Z7_final to allow overriding in derived classes
#define MY_QUERYINTERFACE_BEGIN \
  STDMETHOD(QueryInterface)(REFGUID iid, void **outObject) throw() Z7_override { \
  if (iid == IID_IUnknown)

#define MY_QUERYINTERFACE_ENTRY(i) \
  else if (iid == IID_ ## i) \
    { i *ti = this;  *outObject = ti; }

#define MY_QUERYINTERFACE_END \
  else return E_NOINTERFACE; \
  ++_m_RefCount; return S_OK; }

#define MY_ADDREF_RELEASE_NONFINAL \
  private: \
  STDMETHOD_(ULONG, AddRef)() throw() Z7_override \
    { return ++_m_RefCount; } \
  STDMETHOD_(ULONG, Release)() throw() Z7_override \
    { if (--_m_RefCount != 0) return _m_RefCount; \
      delete this;  return 0; }

#define MY_UNKNOWN_IMP1_NONFINAL(i) \
  MY_QUERYINTERFACE_BEGIN \
  { IUnknown *tu = this; *outObject = tu; } \
  MY_QUERYINTERFACE_ENTRY(i) \
  MY_QUERYINTERFACE_END \
  MY_ADDREF_RELEASE_NONFINAL

class CPPToJavaSequentialInStream :
	public CPPToJavaAbstract, //
	public virtual ISequentialInStream, //
	public CMyUnknownImp {

	jni::ISequentialInStream * _iSequentialInStream;
public:
	MY_UNKNOWN_IMP1_NONFINAL(ISequentialInStream)

public:
	CPPToJavaSequentialInStream(JBindingSession & jbindingSession, JNIEnv * initEnv, jobject sequentialInStream)
		: CPPToJavaAbstract(jbindingSession, initEnv, sequentialInStream),
		  _iSequentialInStream(jni::ISequentialInStream::_getInstanceFromObject(initEnv, sequentialInStream))
	{
	    TRACE_OBJECT_CREATION("CPPToJavaSequentialInStream")
	}

	virtual ~CPPToJavaSequentialInStream() {}

	/*
	 * FROM 7-ZIP:
	 * Out: if size != 0, return_value = S_OK and (*processedSize == 0),
	 * then there are no more bytes in stream.
	 * if (size > 0) && there are bytes in stream,
	 * this function must read at least 1 byte.
	 * This function is allowed to read less than number of remaining bytes in stream.
	 * You must call Read function in loop, if you need exact amount of data
	 */
	STDMETHOD(Read)(void *data, UInt32 size, UInt32 *processedSize);
};


#endif /*CPPTOJAVASEQUENTIALINSTREAM_H_*/
