#include "MutexLocker.h"

using namespace System::Thread;

// Construct the MutexLocker
MutexLocker::MutexLocker(Lock pLock) :m_Lock(pLock)
{
	if (GetLocker())
	{
		GetLocker()->Lock();
	}
}

// Detructe the MutexLocker
MutexLocker::~MutexLocker()
{
	if (GetLocker())
	{
		GetLocker()->Unlock();
	}
}