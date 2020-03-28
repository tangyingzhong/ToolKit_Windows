///************************************************************************
/// <copyrigth>Voice AI Technology Of ShenZhen</copyrigth>
/// <author>tangyingzhong</author>
/// <contact>yingzhong@voiceaitech.com</contact>
/// <version>v1.0.0</version>
/// <describe>
/// Reflect the class name to class type
///</describe>
/// <date>2019/8/11</date>
///***********************************************************************
#ifndef REFLECT_H
#define REFLECT_H

#include <map>
#include "Tool/Common/SystemType.h"
#include "Tool/Thread/Mutex.h"
#include "Tool/Thread/MutexLocker.h"
#include "Tool/BaseType/String.h"

using namespace std;
using namespace System::BasicType;
using namespace System::Thread;

namespace System
{
	class Reflect
	{
	public:
		typedef Mutex* Lock;
		typedef Object (*CreateObject)();
		typedef map<string, CreateObject> ClassTypeTable;

	public:
		// Get the reflect instance
		static Reflect* GetInstance();

		// Destory the instance
		static None DestoryInstance();

	private:
		// Construct the reflect
		Reflect();

		// Destruct the reflect
		~Reflect();

	public:
		// Get the class type from the class name
		Object GetClassObject(String strClassName);

		// Register the class 
		Boolean RegisterClassType(String strClassName,CreateObject pCreateObject);

	private:
		// Dispose all registered object
		None DisposeObjects();

	private:
		// Get the Disposed
		inline Boolean GetDisposed() const
		{
			return m_bDisposed;
		}

		// Set the Disposed
		inline void SetDisposed(Boolean bDisposed)
		{
			m_bDisposed = bDisposed;
		}

	private:
		// The instance of myself
		static Reflect* m_pInstance;

		// Container to have all register class type
		ClassTypeTable m_ClassTypeTable;

		// Disposed state
		Boolean m_bDisposed;
	};
}

#define REFLECT(ClassName)  \
class ClassName##Helper \
{  \
public:  \
	ClassName##Helper() \
	{ \
		System::Reflect::GetInstance()->RegisterClassType(_T(#ClassName), CreateModule); \
	} \
	\
	static Object CreateObject() \
	{ \
		return new ClassName();  \
	} \
};  \
   \
ClassName##Helper m_ClassName##Helper;

#endif //REFLECT_H