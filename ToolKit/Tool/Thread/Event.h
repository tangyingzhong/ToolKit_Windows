///************************************************************************
/// <copyrigth>2018-2019 Corporation.All Rights Reserved</copyrigth>
/// <author>tangyingzhong</author>
/// <contact>tangyz114987@outlook.com</contact>
/// <version>v1.0.0</version>
/// <describe>
/// It can be used to synchronize the threads
///</describe>
/// <date>2019/7/16</date>
///***********************************************************************
#ifndef	EVENT_H
#define	EVENT_H

#include "Tool/BaseType/String.h"

using namespace System::BasicType;

namespace System
{
	namespace Thread
	{
		class Event
		{
		public:
			typedef System::None None;
			typedef System::Boolean BOOL;
			typedef System::Int32 MsTimeout;
			typedef System::Object EventHandle;

		public:
			// Construct the Event
			Event();

			// Destruct the Event
			~Event();

			// Allow the object copying
			Event(const Event& other);

			// Allow the obejct assignment
			Event& operator=(const Event& other);

		public:
			// Open the event
			BOOL Open(String strEventName = _T(""));

			// Activate the event
			None Signaled();

			// Dis-Activate the event
			None NonSignaled();

			// Wait for the event
			None Wait(MsTimeout iMsTimeout = INFINITE);

		private:
			// Initialize the Event
			None Initialize();

			// Destory the Event
			None Destory();

			// Close the event
			None Close();

		private:
			// Get the EventHandle
			inline EventHandle GetEventHandle() const
			{
				return m_EventHandle;
			}

			// Set the EventHandle
			inline None SetEventHandle(EventHandle pEventHandle)
			{
				m_EventHandle = pEventHandle;
			}

			// Get the disposed status
			inline BOOL GetDisposed() const
			{
				return m_Disposed;
			}

			// Set the disposed status
			inline None SetDisposed(BOOL bDisposed)
			{
				m_Disposed = bDisposed;
			}

		private:
			// The handle of the event
			EventHandle m_EventHandle;

			// Disposed status
			BOOL m_Disposed;

		};
	}
}

#endif // EVENT_H