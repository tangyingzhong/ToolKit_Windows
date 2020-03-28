#include "Mutex.h"

using namespace System::Thread;

// Construct a lock
Mutex::Mutex()
{
	InitializeCriticalSection(&m_CritialSection);
}

// destory the lock
Mutex::~Mutex()
{
	DeleteCriticalSection(&m_CritialSection);
}

// Lock the resource
Mutex::None Mutex::Lock()
{
	EnterCriticalSection(&m_CritialSection);
}

// Unlock the resource
Mutex::None Mutex::Unlock()
{
	LeaveCriticalSection(&m_CritialSection);
}