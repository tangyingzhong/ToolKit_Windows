///************************************************************************
/// <copyrigth>2018-2019 Corporation.All Rights Reserved</copyrigth>
/// <author>tangyingzhong</author>
/// <contact>tangyz114987@outlook.com</contact>
/// <version>V1.0.0</version>
/// <describe>
/// Timer on the window that can used for counting
///</describe>
/// <date>2019/3/6</date>
///***********************************************************************
#ifndef TIMER_H
#define TIMER_H

#include <mmsystem.h>

#pragma comment(lib,"Winmm.lib")

namespace System
{
	namespace Clock
	{
		///*********************************************************
		/// <class>Timer</class>
		/// <summary>
		/// Calling back function template is below:
		/// void CALLBACK (TIMECALLBACK)(UINT uTimerID, UINT uMsg, DWORD_PTR dwUser, DWORD_PTR dw1, DWORD_PTR dw2);
		/// </summary>
		/// <version>V1.0.0 </version>
		/// <goup> C++</group>
		/// <author>tangyingzhong</author>
		/// <contact>tangyingzhong@szangell.com</contact>
		///*********************************************************
		class Timer
		{
		public:
			typedef System::Empty Empty;
			typedef System::Boolean BOOL;
			typedef System::Int32 TimerID;
			typedef System::Int32 DelayMs;
			typedef System::Object Object;
			typedef LPTIMECALLBACK CallBackFunc;

		public:
			// Construct the Timer 		
			Timer(DelayMs DelayTime, CallBackFunc Func, Object Paramenter);

			// Detructe the Timer
			~Timer();

		private:
			// Copy Timer
			Timer(const Timer& other) {	}

			// Asigment of Timer
			Timer& operator=(const Timer& other) {	}

		public:
			// Open the timer
			Empty Open();

			// Close the timer
			Empty Close();

		private:
			// Get timer ID
			inline TimerID GetTimerId() const
			{
				return m_TimerId;
			}

			// Set timer ID
			inline Empty SetTimerId(TimerID iTimerId)
			{
				this->m_TimerId = iTimerId;
			}

			// Get timer delay time
			inline DelayMs GetTimerDelayTime() const
			{
				return m_TimerDelayTime;
			}

			// Set timer delay time
			inline Empty SetTimerDelayTime(DelayMs iTimerDelayTime)
			{
				this->m_TimerDelayTime = iTimerDelayTime;
			}

			// Get callback func
			inline CallBackFunc GetCallbackFunc() const
			{
				return m_CallbackFunc;
			}

			// Set callback func
			inline Empty SetCallbackFunc(CallBackFunc pCallbackFunc)
			{
				this->m_CallbackFunc = pCallbackFunc;
			}

			// Get time para
			inline Object GetTimerPara() const
			{
				return m_TimerPara;
			}

			// Set time para
			inline Empty SetTimerPara(Object pTimerPara)
			{
				this->m_TimerPara = pTimerPara;
			}

			// Get the timer closed status
			inline BOOL GetClosed() const
			{
				return m_Closed;
			}

			// Set the timer closed status
			inline Empty SetClosed(BOOL bClosed)
			{
				this->m_Closed = bClosed;
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
			// Timer ID
			TimerID m_TimerId;

			// Timer's delay time
			DelayMs m_TimerDelayTime;

			// Called Func by timers
			CallBackFunc m_CallbackFunc;

			// Paramenter for the timer's call func
			Object m_TimerPara;

			// Timer is closed or not
			BOOL m_Closed;

			// Disposed status
			BOOL m_Disposed;

		};
	}
}

#endif //TIMER_H_