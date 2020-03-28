#include "Semaphore.h"

using namespace System::Thread;

// Construct a Semaphore with name
Semaphore::Semaphore(SemaphoreName strSignalName, 
	ResourceCount iMinCount, 
	ResourceCount iMaxCount) :m_SignalHandle(NULL),
m_SignalName(strSignalName),
m_MinCount(iMinCount),
m_MaxCount(iMaxCount),
m_Disposed(false)
{
	Initialize();
}

// Copy construct Semaphore
Semaphore::Semaphore(const Semaphore& other)
{
	SetSignalHandle(other.GetSignalHandle());

	SetSignalName(other.GetSignalName());

	SetMinResourceCount(other.GetMinResourceCount());

	SetMaxResourceCount(other.GetMaxResourceCount());

	SetDisposed(other.GetDisposed());
}

// Assignment
Semaphore& Semaphore::operator=(const Semaphore& other)
{
	if (this != &other)
	{
		SetSignalHandle(other.GetSignalHandle());

		SetSignalName(other.GetSignalName());

		SetMinResourceCount(other.GetMinResourceCount());

		SetMaxResourceCount(other.GetMaxResourceCount());

		SetDisposed(other.GetDisposed());
	}

	return *this;
}

// Destory the Semaphore
Semaphore::~Semaphore()
{
	Destory();
}

// Initialize the semaphore
Semaphore::None Semaphore::Initialize()
{
	Open();
}

// Dispose the semaphore
Semaphore::None Semaphore::Destory()
{
	if (!GetDisposed())
	{
		SetDisposed(true);

		Close();
	}
}

// Open the semaphore
Semaphore::None Semaphore::Open()
{
	SetSignalHandle(::OpenSemaphore(SEMAPHORE_ALL_ACCESS, 
		false, 
		GetSignalName().CStr()));

	if (GetSignalHandle() == NULL)
	{
		SetSignalHandle(::CreateSemaphore(NULL, 
			GetMinResourceCount(), 
			GetMaxResourceCount(), 
			GetSignalName().CStr()));
	}
}

// Close the semaphore
Semaphore::None Semaphore::Close()
{
	if (GetSignalHandle())
	{
		::CloseHandle(GetSignalHandle());

		SetSignalHandle(NULL);
	}
}

// Wait for a semaphore
Semaphore::None Semaphore::Acquire(MsTimeout iMsTimeout)
{
	::WaitForSingleObject(GetSignalHandle(), iMsTimeout);
}

// Make the sema to be signaled
Semaphore::None Semaphore::Release()
{
	::ReleaseSemaphore(GetSignalHandle(), 1, NULL);
}