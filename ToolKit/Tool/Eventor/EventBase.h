///************************************************************************
/// <copyrigth>Voice AI Technology Of ShenZhen</copyrigth>
/// <author>tangyingzhong</author>
/// <contact>yingzhong@voiceaitech.com</contact>
/// <version>v1.0.0</version>
/// <describe>
/// It is an event base for solving firing and listening events
///</describe>
/// <date>2019/12/11</date>
///***********************************************************************
#ifndef EVENTBASE_H
#define EVENTBASE_H

#include "EventHandler/EventHandler.h"
#include "IEvent.h"

namespace System
{
	template<class T1 = IEvent, class T2 = EventArgs>
	class EventBase :public T1
	{
	public:
		typedef IEventHandler::HandlerFunc HandlerFunc;

	public:
		// Construct the EventBase
		EventBase() :m_bDisposed(false)
		{
			Initialize();
		}

	protected:
		// Detructe the EventBase
		virtual ~EventBase()
		{
			if (!GetDisposed())
			{
				SetDisposed(true);

				Destory();
			}
		}

	public:
		// Listen plugins
		virtual Empty Listen(Object pListener,
			HandlerFunc pListenHandler,
			Int32 iEventID)
		{
			m_EventHandler.RegisterEvent(pListener, iEventID, pListenHandler);
		}

	protected:
		// Notidy all listeners who listening this event id
		Empty Notify(Object pNotifier, Int32 iEventID, T2* pArgs)
		{
			m_EventHandler.FireEvent(pNotifier, iEventID, pArgs);
		}

	private:
		// Initialize the EventBase
		Empty Initialize(){	}

		// Destory the EventBase
		Empty Destory(){	}

	private:
		// Get the disposed status
		inline Boolean GetDisposed() const
		{
			return m_bDisposed;
		}

		// Set the disposed status
		inline Empty SetDisposed(Boolean bDisposed)
		{
			m_bDisposed = bDisposed;
		}

	private:
		// Event handler container
		EventHandler m_EventHandler;

		// Disposed status
		Boolean m_bDisposed;
	};
}

#endif // EVENTBASE_H
