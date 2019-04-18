#include "Application\PreCompile.h"
#include "Mutex.h"

using namespace System::Thread;

///************************************************************************
/// <summary>
/// Construct a lock
/// </summary>
/// <returns></returns>
/// <remarks>
/// none
/// </remarks>
///***********************************************************************
Mutex::Mutex()
{
	InitializeCriticalSection(&m_CritialSection);
}


///************************************************************************
/// <summary>
/// destory the lock
/// </summary>
/// <returns></returns>
/// <remarks>
/// none
/// </remarks>
///***********************************************************************
Mutex::~Mutex()
{
	DeleteCriticalSection(&m_CritialSection);
}


///************************************************************************
/// <summary>
/// Lock the resource
/// </summary>
/// <returns></returns>
/// <remarks>
/// none
/// </remarks>
///***********************************************************************
Mutex::Empty Mutex::Lock()
{
	EnterCriticalSection(&m_CritialSection);
}


///************************************************************************
/// <summary>
/// Unlock the resource
/// </summary>
/// <returns></returns>
/// <remarks>
/// none
/// </remarks>
///***********************************************************************
Mutex::Empty Mutex::Unlock()
{
	LeaveCriticalSection(&m_CritialSection);
}