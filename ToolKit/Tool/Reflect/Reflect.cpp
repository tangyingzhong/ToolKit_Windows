#include "Reflect.h"

using namespace System;

static System::Thread::Mutex* pLock = new System::Thread::Mutex();

Reflect* Reflect::m_pInstance = NULL;

// Get the reflect instance
Reflect* Reflect::GetInstance()
{
	if (m_pInstance==NULL)
	{
		MutexLocker Locker(pLock);

		if (m_pInstance==NULL)
		{
			Reflect* pReflect = new Reflect();

			m_pInstance = pReflect;
		}
	}

	return m_pInstance;
}

// Destory the instance
None Reflect::DestoryInstance()
{
	MutexLocker Locker(pLock);

	if (m_pInstance)
	{
		delete m_pInstance;

		m_pInstance = NULL;
	}
}

// Construct the reflect
Reflect::Reflect()
{
	m_ClassTypeTable.clear();
}
 
// Destruct the reflect
Reflect::~Reflect()
{
	if (!GetDisposed())
	{
		SetDisposed(true);

		DisposeObjects();
	}
}

// Get the class type from the class name
Object Reflect::GetClassObject(String strClassName)
{
	if (strClassName.IsEmpty())
	{
		return NULL;
	}

	ClassTypeTable::iterator Iter = m_ClassTypeTable.find(strClassName.ToUTF8Data());
	if (Iter!= m_ClassTypeTable.end())
	{
		return (Iter->second)();
	}

	return NULL;
}

// Register the class
Boolean Reflect::RegisterClassType(String strClassName, CreateObject pCreateObject)
{
	if (strClassName.IsEmpty())
	{
		return false;
	}

	if (pCreateObject==NULL)
	{
		return false;
	}

	m_ClassTypeTable.insert(make_pair(strClassName.ToUTF8Data(), pCreateObject));

	return true;
}

// Dispose all registered object
None Reflect::DisposeObjects()
{
	for (ClassTypeTable::iterator Iter = m_ClassTypeTable.begin();
		Iter != m_ClassTypeTable.end(); 
		++Iter)
	{
		if (Iter->second !=NULL)
		{
			delete (Iter->second)();

			Iter->second = NULL;
		}
	}

	m_ClassTypeTable.clear();
}