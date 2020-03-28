///************************************************************************
/// <copyrigth>2018-2019 Corporation.All Rights Reserved</copyrigth>
/// <author>tangyingzhong</author>
/// <contact>tangyz114987@outlook.com</contact>
/// <version>v1.0.0</version>
/// <describe>
/// Count the time 
///</describe>
/// <date>2019/7/16</date>
///***********************************************************************
#ifndef COUNTER_H
#define COUNTER_H

#include "Tool/Common/SystemType.h"

namespace System
{
	namespace Clock
	{
		class Counter
		{
		public:
			typedef System::None None;
			typedef System::Real TimeS;
			typedef System::Real TimeMs;
			typedef System::Real TimeUs;
			typedef LARGE_INTEGER LargeTime;

		public:
			// Construct the Counter
			Counter();

			// Detructe the Counter
			~Counter();

		private:
			// Copy Counter
			Counter(const Counter& other) {	}

			// Asigment of Counter
			Counter& operator=(const Counter& other) {	}

		public:
			// Start the counter
			None Start();

			// Stop the counter
			None Stop();

			// Get the total time (s)
			TimeS GetCountTimeS();

			// Get the total time (ms)
			TimeMs GetCountTimeMs();

			// Get the total time (us)
			TimeUs GetCountTimeUs();

		private:
			// Init the Counter 
			None Initialize();

			// Destory the Counter
			None Destory();

		private:
			// Get the disposed
			inline BOOL GetDisposed() const
			{
				return m_Disposed;
			}

			// Set the disposed	
			inline None SetDisposed(BOOL bDisposed)
			{
				m_Disposed = bDisposed;
			}

		private:
			// Previous time
			LargeTime m_PreviousTime;

			// Current time
			LargeTime m_CurTime;

			// CPU frequency
			LargeTime m_CpuFreq;

			// Disposed status
			BOOL m_Disposed;

		};
	}
}

#endif // COUNTER_H