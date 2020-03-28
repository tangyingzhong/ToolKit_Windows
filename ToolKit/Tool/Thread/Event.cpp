#include "Event.h"

using namespace System::Thread;

// Construct the Event
Event::Event() :m_EventHandle(NULL), 
m_Disposed(false)
{
	Initialize();
}

// Destruct the Event
Event::~Event()
{
	Destory();
}

// Copy construct Event
Event::Event(const Event& other)
{
	SetEventHandle(other.GetEventHandle());

	SetDisposed(other.GetDisposed());
}

// Assignment
Event& Event::operator=(const Event& other)
{
	if (this != &other)
	{
		SetEventHandle(other.GetEventHandle());

		SetDisposed(other.GetDisposed());
	}

	return *this;
}

// Initialize the Event
Event::None Event::Initialize()
{
	
}

// Dispose the Event
Event::None Event::Destory()
{
	if (!GetDisposed())
	{
		SetDisposed(true);

		Close();
	}
}

// Open the event
Event::BOOL Event::Open(String strEventName)
{
	SetEventHandle(::OpenEvent(EVENT_ALL_ACCESS, FALSE, strEventName.CStr()));
	if (GetEventHandle() == NULL)
	{
		SetEventHandle(::CreateEvent(NULL, TRUE, FALSE, strEventName.CStr()));
	}

	// Set the event non-signaled after created
	if (GetEventHandle())
	{
		NonSignaled();

		return true;
	}

	return false;
}

// Activate the event
Event::None Event::Signaled()
{
	if (GetEventHandle())
	{
		::SetEvent(GetEventHandle());
	}
}

// Disactivate the event
Event::None Event::NonSignaled()
{
	if (GetEventHandle())
	{
		::ResetEvent(GetEventHandle());
	}
}

// Wait for the event
Event::None Event::Wait(MsTimeout iMsTimeout)
{
	::WaitForSingleObject(GetEventHandle(), iMsTimeout);
}

// Close the event
Event::None Event::Close()
{
	if (GetEventHandle())
	{
		NonSignaled();

		::CloseHandle(GetEventHandle());

		SetEventHandle(NULL);
	}
}
