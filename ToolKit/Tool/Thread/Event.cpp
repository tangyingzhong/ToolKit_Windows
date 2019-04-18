#include "Application\PreCompile.h"
#include "Event.h"

using namespace System::Thread;

///************************************************************************
/// <summary>
/// Construct the Event
/// </summary>
/// <param name=name>event name</param>
/// <returns></returns>
/// <remarks>
/// none
/// </remarks>
///************************************************************************
Event::Event(String strEventName) :m_EventName(strEventName), m_EventHandle(NULL), m_Disposed(false)
{
	Initialize();
}


///************************************************************************
/// <summary>
/// Destruct the Event
/// </summary>
/// <returns></returns>
/// <remarks>
/// none
/// </remarks>
///************************************************************************
Event::~Event()
{
	Destory();
}


///************************************************************************
/// <summary>
/// Copy construct Event
/// </summary>
/// <param name=other>another event object</param>
/// <returns></returns>
/// <remarks>
/// none
/// </remarks>
///***********************************************************************
Event::Event(const Event& other)
{
	this->SetEventHandle(other.GetEventHandle());
	this->SetEventName(other.GetEventName());
	this->SetDisposed(other.GetDisposed());
}


///************************************************************************
/// <summary>
/// Assignment
/// </summary>
/// <param name=other>another event object</param>
/// <returns>Event reference</returns>
/// <remarks>
/// none
/// </remarks>
///***********************************************************************
Event& Event::operator=(const Event& other)
{
	if (this != &other)
	{
		this->SetEventHandle(other.GetEventHandle());
		this->SetEventName(other.GetEventName());
		this->SetDisposed(other.GetDisposed());
	}

	return *this;
}


///************************************************************************
/// <summary>
/// Initialize the Event
/// </summary>
/// <param name=name></param>
/// <returns></returns>
/// <remarks>
/// none
/// </remarks>
///************************************************************************
Event::Empty Event::Initialize()
{

}


///************************************************************************
/// <summary>
/// Dispose the Event
/// </summary>
/// <returns></returns>
/// <remarks>
/// none
/// </remarks>
///************************************************************************
Event::Empty Event::Destory()
{
	if (!GetDisposed())
	{
		SetDisposed(true);

		// Close the event
		this->Close();
	}
}


///************************************************************************
/// <summary>
/// Open the event
/// </summary>
/// <returns></returns>
/// <remarks>
/// none
/// </remarks>
///************************************************************************
Event::BOOL Event::Open()
{
	BOOL bSuccess = false;

	this->SetEventHandle(::OpenEvent(EVENT_ALL_ACCESS, FALSE, this->GetEventName()));
	if (this->GetEventHandle() == NULL)
	{
		this->SetEventHandle(::CreateEvent(NULL, TRUE, FALSE, this->GetEventName()));
	}

	// Set the event non-signaled after created
	if (this->GetEventHandle())
	{
		this->NonSignaled();

		bSuccess = true;
	}

	return bSuccess;
}


///************************************************************************
/// <summary>
/// Activate the event
/// </summary>
/// <returns></returns>
/// <remarks>
/// none
/// </remarks>
///************************************************************************
Event::Empty Event::Signaled()
{
	if (this->GetEventHandle())
	{
		::SetEvent(this->GetEventHandle());
	}
}


///************************************************************************
/// <summary>
/// Disactivate the event
/// </summary>
/// <returns></returns>
/// <remarks>
/// none
/// </remarks>
///************************************************************************
Event::Empty Event::NonSignaled()
{
	if (this->GetEventHandle())
	{
		::ResetEvent(this->GetEventHandle());
	}
}


///************************************************************************
/// <summary>
/// Wait for the event
/// </summary>
/// <returns></returns>
/// <remarks>
/// none
/// </remarks>
///************************************************************************
Event::Empty Event::Wait(MsTimeout iMsTimeout)
{
	::WaitForSingleObject(this->GetEventHandle(), iMsTimeout);
}


///************************************************************************
/// <summary>
/// Close the event
/// </summary>
/// <returns></returns>
/// <remarks>
/// none
/// </remarks>
///************************************************************************
Event::Empty Event::Close()
{
	if (this->GetEventHandle())
	{
		this->NonSignaled();

		::CloseHandle(this->GetEventHandle());
		this->SetEventHandle(NULL);
	}
}
