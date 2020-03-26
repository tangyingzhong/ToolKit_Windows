#ifndef EVENTHANDLER_H
#define EVENTHANDLER_H

#include "IEventHandler.h"

using namespace std;
using namespace System;
using namespace System::EventArgument;

namespace System
{
	class EventHandler :public IEventHandler
	{
	public:
		typedef vector<HandlerFunc> HandlerFuncTable;
		typedef std::map<Int32, HandlerFuncTable> IDFuncMapTable;
		typedef std::map<Object, IDFuncMapTable> EventMapTable;

	public:
		// Construct the event handler
		EventHandler();

		// Destruct the event handler
		~EventHandler();

	private:
		// Forbid the object copy
		EventHandler(const EventHandler& other) {    }

		// Forbid the object assign
		EventHandler& operator=(const EventHandler& other) {    }

	public:
		// Fire event
		virtual Empty FireEvent(Object pSender, Int32 iEventID, EventArgs* pArgs);

		// Register an object's callback to the event handler
		virtual Boolean RegisterEvent(Object pReceiver, Int32 iEventID, HandlerFunc pHandlerFunc);

		// UnRegister receiver
		virtual Boolean UnRegisterEvent(Object pReceiver);

		// UnRegister receiver
		virtual Boolean UnRegisterEvent(Object pReceiver, Int32 iEventID);

		// UnRegister an object's callback from the event handler
		virtual Boolean UnRegisterEvent(Object pReceiver, Int32 iEventID, HandlerFunc pHandlerFunc);

		// UnRegister all eventids
		virtual Boolean UnRegisterEvent(Int32 iEventID);

		// UnRegister all eventid's func
		virtual Boolean UnRegisterEvent(Int32 iEventID, HandlerFunc pHandlerFunc);

		// UnRegister all funcs
		virtual Boolean UnRegisterEvent(HandlerFunc pHandlerFunc);

	private:
		// Initialize the event handler
		Empty Initialize();

		// Destory the event handler
		Empty Destory();

		// Clear the map table
		Empty ClearTable();

	private:
		// Get the disposed state
		inline Boolean GetDisposed() const
		{
			return m_bDisposed;
		}

		// Set the disposed state
		inline Empty SetDisposed(Boolean bDisposed)
		{
			m_bDisposed = bDisposed;
		}

	private:
		// Event map table
		EventMapTable m_EventMapTable;

		// Disposed status
		Boolean m_bDisposed;
	};
}

#endif //EVENTHANDLER_H
