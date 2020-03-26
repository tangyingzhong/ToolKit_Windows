///************************************************************************
/// <copyrigth>Voice AI Technology Of ShenZhen</copyrigth>
/// <author>tangyingzhong</author>
/// <contact>yingzhong@voiceaitech.com</contact>
/// <version>v1.0.0</version>
/// <describe>
/// It can be used to synchronize the threads
///</describe>
/// <date>2019/7/16</date>
///***********************************************************************
#ifndef	EVENT_H
#define	EVENT_H

#include "BaseType/String.h"

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
			// Get the EventHandle
			inline EventHandle GetEventHandle() const
			{
				return m_EventHandle;
			}

			// Set the EventHandle
			inline Empty SetEventHandle(EventHandle pEventHandle)
			{
				m_EventHandle = pEventHandle;
			}

			// Get the disposed status
			inline BOOL GetDisposed() const
			{
				return m_Disposed;
			}

			// Set the disposed status
			inline Empty SetDisposed(BOOL bDisposed)
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