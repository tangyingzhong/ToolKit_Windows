#include "Application\PreCompile.h"
#include "Semaphore.h"

using namespace System::Thread;

///************************************************************************
/// <summary>
/// Construct a Semaphore with name
/// </summary>
/// <returns></returns>
/// <remarks>
/// none
/// </remarks>
///***********************************************************************
Semaphore::Semaphore(SemaphoreName strSignalName, ResourceCount iMinCount, ResourceCount iMaxCount) :m_SignalHandle(NULL),
m_SignalName(strSignalName),
m_MinCount(iMinCount),
m_MaxCount(iMaxCount),
m_Disposed(false)
{
	Initialize();
}


///************************************************************************
/// <summary>
/// Copy construct Semaphore
/// </summary>
/// <param name=other></param>
/// <returns></returns>
/// <remarks>
/// none
/// </remarks>
///***********************************************************************
Semaphore::Semaphore(const Semaphore& other)
{
	this->SetSignalHandle(other.GetSignalHandle());
	this->SetSignalName(other.GetSignalName());
	this->SetMinResourceCount(other.GetMinResourceCount());
	this->SetMaxResourceCount(other.GetMaxResourceCount());
	this->SetDisposed(other.GetDisposed());
}


///************************************************************************
/// <summary>
/// Assignment
/// </summary>
/// <param name=other></param>
/// <returns></returns>
/// <remarks>
/// none
/// </remarks>
///***********************************************************************
Semaphore& Semaphore::operator=(const Semaphore& other)
{
	if (this != &other)
	{
		this->SetSignalHandle(other.GetSignalHandle());
		this->SetSignalName(other.GetSignalName());
		this->SetMinResourceCount(other.GetMinResourceCount());
		this->SetMaxResourceCount(other.GetMaxResourceCount());
		this->SetDisposed(other.GetDisposed());
	}

	return *this;
}


///************************************************************************
/// <summary>
/// destory the Semaphore
/// </summary>
/// <returns></returns>
/// <remarks>
/// none
/// </remarks>
///***********************************************************************
Semaphore::~Semaphore()
{
	Destory();
}


///************************************************************************
/// <summary>
/// Initialize the semaphore
/// </summary>
/// <returns></returns>
/// <remarks>
/// none
/// </remarks>
///***********************************************************************
Semaphore::Empty Semaphore::Initialize()
{
	// Open the semaphore
	this->Open();
}


///************************************************************************
/// <summary>
/// Dispose the semaphore
/// </summary>
/// <returns></returns>
/// <remarks>
/// none
/// </remarks>
///***********************************************************************
Semaphore::Empty Semaphore::Destory()
{
	if (!GetDisposed())
	{
		SetDisposed(true);

		// Close the semaphore
		this->Close();
	}
}


///************************************************************************
/// <summary>
/// Open the semaphore
/// </summary>
/// <returns></returns>
/// <remarks>
/// none
/// </remarks>
///***********************************************************************
Semaphore::Empty Semaphore::Open()
{
	this->SetSignalHandle(::OpenSemaphore(SEMAPHORE_ALL_ACCESS, false, this->GetSignalName().CStr()));
	if (this->GetSignalHandle() == NULL)
	{
		this->SetSignalHandle(::CreateSemaphore(NULL, this->GetMinResourceCount(), this->GetMaxResourceCount(), this->GetSignalName().CStr()));
	}
}


///************************************************************************
/// <summary>
/// Close the semaphore
/// </summary>
/// <returns></returns>
/// <remarks>
/// none
/// </remarks>
///***********************************************************************
Semaphore::Empty Semaphore::Close()
{
	if (this->GetSignalHandle())
	{
		::CloseHandle(this->GetSignalHandle());

		this->SetSignalHandle(NULL);
	}
}


///************************************************************************
/// <summary>
/// Wait for a semaphore
/// </summary>
/// <param name=sem></param>
/// <param name=time></param>
/// <returns></returns>
/// <remarks>
/// none
/// </remarks>
///***********************************************************************
Semaphore::Empty Semaphore::Acquire(MsTimeout iMsTimeout)
{
	::WaitForSingleObject(this->GetSignalHandle(), iMsTimeout);
}


///************************************************************************
/// <summary>
/// Make the sema to be signaled
/// </summary>
/// <param name=sem></param>
/// <returns></returns>
/// <remarks>
/// none
/// </remarks>
///***********************************************************************
Semaphore::Empty Semaphore::Release()
{
	::ReleaseSemaphore(this->GetSignalHandle(), 1, NULL);
}