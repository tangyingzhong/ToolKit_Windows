///************************************************************************
/// <copyrigth>2018-2019 Corporation.All Rights Reserved</copyrigth>
/// <author>tangyingzhong</author>
/// <contact>tangyz114987@outlook.com</contact>
/// <version>V1.0.0</version>
/// <describe>
/// It can be used to synchronize the threads
///</describe>
/// <date>2019/3/6</date>
///***********************************************************************
#ifndef	EVENT_H
#define	EVENT_H

#include "Tool\BaseType\String.h"

using namespace System::BasicType;

namespace System
{
	namespace Thread
	{
		class Event
		{
		public:
			typedef System::Empty Empty;
			typedef System::Boolean BOOL;
			typedef System::Int32 MsTimeout;
			typedef System::Object EventHandle;

		public:
			// Construct the Event
			Event(String strEventName);

			// Destruct the Event
			~Event();

			// Allow the object copying
			Event(const Event& other);

			// Allow the obejct assignment
			Event& operator=(const Event& other);

		public:
			// Open the event
			BOOL Open();

			// Activate the event
			Empty Signaled();

			// Dis-Activate the event
			Empty NonSignaled();

			// Wait for the event
			Empty Wait(MsTimeout iMsTimeout = INFINITE);

		private:
			// Initialize the Event
			Empty Initialize();

			// Destory the Event
			Empty Destory();

			// Close the event
			Empty Close();

		private:
			// Get the event name
			inline String GetEventName() const
			{
				return m_EventName;
			}

			// Set the event name
			inline Empty SetEventName(String strEventName)
			{
				this->m_EventName = strEventName;
			}

			// Get the EventHandle
			inline EventHandle GetEventHandle() const
			{
				return m_EventHandle;
			}

			// Set the EventHandle
			inline Empty SetEventHandle(EventHandle pEventHandle)
			{
				this->m_EventHandle = pEventHandle;
			}

			// Get the disposed status
			inline BOOL GetDisposed() const
			{
				return m_Disposed;
			}

			// Set the disposed status
			inline Empty SetDisposed(BOOL bDisposed)
			{
				this->m_Disposed = bDisposed;
			}

		private:
			// The name of the Event
			String m_EventName;

			// The handle of the event
			EventHandle m_EventHandle;

			// Disposed status
			BOOL m_Disposed;

		};
	}
}

#endif // EVENT_H