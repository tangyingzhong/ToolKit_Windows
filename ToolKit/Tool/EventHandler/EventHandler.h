///************************************************************************
/// <copyrigth>2018-2019 Corporation.All Rights Reserved</copyrigth>
/// <author>tangyingzhong</author>
/// <contact>tangyz114987@outlook.com</contact>
/// <version>v1.0.0</version>
/// <describe>
/// Event container which used to be a center of sub-pub 
///</describe>
/// <date>2019/7/16</date>
///***********************************************************************
#ifndef EVENTHANDLER_H
#define EVENTHANDLER_H

#include <vector>
#include <map>
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
		virtual None FireEvent(Object pSender, Int32 iEventID, EventArgs* pArgs);

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
		None Initialize();

		// Destory the event handler
		None Destory();

		// Clear the map table
		None ClearTable();

	private:
		// Get the disposed state
		inline Boolean GetDisposed() const
		{
			return m_bDisposed;
		}

		// Set the disposed state
		inline None SetDisposed(Boolean bDisposed)
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
