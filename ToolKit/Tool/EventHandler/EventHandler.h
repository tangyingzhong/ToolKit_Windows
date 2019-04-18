///************************************************************************
/// <copyrigth>2018-2019 Corporation.All Rights Reserved</copyrigth>
/// <author>tangyingzhong</author>
/// <contact>tangyz114987@outlook.com</contact>
/// <version>V1.0.0</version>
/// <describe>
/// Register and Unregister events for calling functions
///</describe>
/// <date>2019/3/6</date>
///***********************************************************************
#ifndef EVENT_HANDLER_H
#define EVENT_HANDLER_H

#include "EventArgs.h"
#include "Tool\Common\SystemType.h"

namespace System
{
	namespace EventArgument
	{
		///*********************************************************
		/// <class> EventHandler<Args> </class>
		/// <summary>
		/// Events handler for calling functions needed.
		/// </summary>
		/// <version>V1.0.0 </version>
		/// <goup> C++ </group>
		/// <author>tangyingzhong</author>
		/// <contact>tangyz114987@outlook.com</contact>
		///**********************************************************/
		template<class TEventArgs = EventArgs>
		class EventHandler
		{
		public:
			typedef System::Int32 Index;
			typedef System::Empty Empty;
			typedef System::Object Object;
			typedef System::Boolean BOOL;
			typedef EventHandler<TEventArgs> MySelf;
			typedef std::vector<MySelf*> EventHandlerTable;
			typedef Empty(*pHandle)(Object sender, EventArgs* e);
			typedef std::vector<pHandle> EventFuncTable;

		public:
			// Construct the Event
			EventHandler() :disposed(false)
			{

			}

			// Construct the Event with the function
			EventHandler(pHandle pCallbackFunc)
			{
				Initialize(pCallbackFunc);
			}

			// Detructe the Event
			~EventHandler()
			{
				Destory();
			}

			// Allow the object copying
			EventHandler(const EventHandler<TEventArgs>& other)
			{
				// Copy the tables
				this->Copy(other);

				// Set the disposed
				this->SetDisposed(other.GetDisposed());
			}

			// Allow the object assignment
			EventHandler<TEventArgs>& operator=(const EventHandler<TEventArgs>& other)
			{
				if (this != &other)
				{
					// Clear the handler
					this->ClearHandlerTable();

					// Clear the functions
					this->ClearFuncTable();

					// Copy the tables
					this->Copy(other);

					// Set the disposed
					this->SetDisposed(other.GetDisposed());
				}

				return *this;
			}

		public:
			// Excute the event handler 
			Empty operator()(Object sender, TEventArgs* e)
			{
				// Excute all callback functions in the function table
				for (EventFuncTable::iterator IterFunc = this->m_EventFuncTable.begin(); IterFunc != this->m_EventFuncTable.end(); ++IterFunc)
				{
					// Get the current index
					Index iCurIndex = IterFunc - this->m_EventFuncTable.begin();

					// Call back function
					this->m_EventFuncTable[iCurIndex](sender, e);
				}

				// Excute all callback functions in event handler array
				for (EventHandlerTable::iterator IterHandler = this->m_EventHandlerTable.begin(); IterHandler != this->m_EventHandlerTable.end(); ++IterHandler)
				{
					MySelf* pEventHandler = *IterHandler;

					for (EventFuncTable::iterator IterFunc = pEventHandler->m_EventFuncTable.begin(); IterFunc != pEventHandler->m_EventFuncTable.end(); ++IterFunc)
					{
						// Get the current index
						Index iCurIndex = IterFunc - pEventHandler->m_EventFuncTable.begin();

						// Call back function
						pEventHandler->m_EventFuncTable[iCurIndex](sender, e);
					}
				}
			}

			// Add the event handler
			EventHandler<TEventArgs>& operator+=(EventHandler<TEventArgs>* Handler)
			{
				return this->Register(Handler);
			}

			// Add the callback function to the event handler
			EventHandler<TEventArgs>& operator+=(pHandle pCallbackFunc)
			{
				return this->Register(pCallbackFunc);
			}

			// Remove the event handler
			EventHandler<TEventArgs>& operator-=(EventHandler<TEventArgs>* Handler)
			{
				return this->UnRegister(Handler);
			}

			// Remove the callback function from the event handler
			EventHandler<TEventArgs>& operator-=(pHandle pCallbackFunc)
			{
				return this->UnRegister(pCallbackFunc);
			}

		private:
			// Register the event handler
			EventHandler<TEventArgs>& Register(EventHandler<TEventArgs>* Handler)
			{
				this->m_EventHandlerTable.push_back(Handler);

				return *this;
			}

			// Unregister the event handler(Remember that one handler has one callback function)
			EventHandler<TEventArgs>& UnRegister(EventHandler<TEventArgs>* Handler)
			{
				// Loop check the handler table
				for (EventHandlerTable::iterator IterHandler = this->m_EventHandlerTable.begin(); IterHandler != this->m_EventHandlerTable.end(); ++IterHandler)
				{
					EventHandler<TEventArgs>* pHandler = *IterHandler;

					// Just identify the first element of the function table
					for (EventFuncTable::iterator IterFunc = pHandler->m_EventFuncTable.begin(); IterFunc != pHandler->m_EventFuncTable.end(); ++IterFunc)
					{
						if (*IterFunc == Handler->m_EventFuncTable[0])
						{
							pHandler->m_EventFuncTable.erase(IterFunc);

							break;
						}
					}
				}

				return *this;
			}

			// Register the event callback func
			EventHandler<TEventArgs>& Register(pHandle pCallbackFunc)
			{
				this->m_EventFuncTable.push_back(pCallbackFunc);

				return *this;
			}

			// Unregister the event callback func
			EventHandler<TEventArgs>& UnRegister(pHandle pCallbackFunc)
			{
				EventFuncTable::iterator IterFunc;

				for (IterFunc = this->m_EventFuncTable.begin(); IterFunc != this->m_EventFuncTable.end(); ++IterFunc)
				{
					if (*IterFunc == pCallbackFunc)
					{
						this->m_EventFuncTable.erase(IterFunc);

						break;
					}
				}

				return *this;
			}

			// Clear the handlers table
			Empty ClearHandlerTable()
			{
				EventHandlerTable().swap(this->m_EventHandlerTable);
			}

			// Clear the functions table
			Empty ClearFuncTable()
			{
				EventFuncTable().swap(this->m_EventFuncTable);
			}

			// Copy the handlers
			Empty Copy(const EventHandler<TEventArgs>& other)
			{
				// v1=v2
				this->m_EventHandlerTable.swap(other.m_EventHandlerTable);

				// v1=v2
				this->m_EventFuncTable.swap(other.m_EventFuncTable);
			}

		private:
			// Init the event handler
			Empty Initialize(pHandle pCallbackFunc)
			{
				this->m_EventFuncTable.push_back(pCallbackFunc);
			}

			// Destory the event handler
			Empty Destory()
			{
				if (!GetDisposed())
				{
					SetDisposed(true);
					// Clear handler table
					this->ClearHandlerTable();
					// Clear function table
					this->ClearFuncTable();
				}
			}

		private:
			// Get the Disposed
			inline BOOL GetDisposed() const
			{
				return m_Disposed;
			}

			// Set the Disposed
			inline Empty SetDisposed(BOOL bDisposed)
			{
				this->m_Disposed = bDisposed;
			}

		private:
			// Event handler table
			EventHandlerTable m_EventHandlerTable;

			// Event's functions table
			EventFuncTable m_EventFuncTable;

			// Disposed status
			BOOL m_Disposed;
		};
	}
}

#endif //EVENT_HANDLER_H_