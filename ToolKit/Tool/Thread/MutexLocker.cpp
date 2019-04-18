#include "Application\PreCompile.h"
#include "MutexLocker.h"

using namespace System::Thread;

///************************************************************************
/// <summary>
/// Construct the MutexLocker
/// </summary>
/// <param name=locker></param>
/// <returns></returns>
/// <remarks>
/// none
/// </remarks>
///***********************************************************************
MutexLocker::MutexLocker(Lock pLock) :m_Lock(pLock)
{
	if (GetLocker())
	{
		GetLocker()->Lock();
	}
}


///************************************************************************
/// <summary>
/// Detructe the MutexLocker
/// </summary>
/// <returns></returns>
/// <remarks>
/// none
/// </remarks>
///***********************************************************************
MutexLocker::~MutexLocker()
{
	if (GetLocker())
	{
		GetLocker()->Unlock();
	}
}