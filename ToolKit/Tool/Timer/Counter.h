///************************************************************************
/// <copyrigth>Voice AI Technology Of ShenZhen</copyrigth>
/// <author>tangyingzhong</author>
/// <contact>yingzhong@voiceaitech.com</contact>
/// <version>v1.0.0</version>
/// <describe>
/// Count the time 
///</describe>
/// <date>2019/7/16</date>
///***********************************************************************
#ifndef COUNTER_H
#define COUNTER_H

#include "Common/SystemType.h"

namespace System
{
	namespace Clock
	{
		class Counter
		{
		public:
			typedef System::Empty Empty;
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
			Empty Start();

			// Stop the counter
			Empty Stop();

			// Get the total time (s)
			TimeS GetCountTimeS();

			// Get the total time (ms)
			TimeMs GetCountTimeMs();

			// Get the total time (us)
			TimeUs GetCountTimeUs();

		private:
			// Init the Counter 
			Empty Initialize();

			// Destory the Counter
			Empty Destory();

		private:
			// Get the disposed
			inline BOOL GetDisposed() const
			{
				return m_Disposed;
			}

			// Set the disposed	
			inline Empty SetDisposed(BOOL bDisposed)
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