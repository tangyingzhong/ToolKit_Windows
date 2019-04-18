///************************************************************************
/// <copyrigth>2018-2019 Corporation.All Rights Reserved</copyrigth>
/// <author>tangyingzhong</author>
/// <contact>tangyz114987@outlook.com</contact>
/// <version>V1.0.0</version>
/// <describe>
/// Count the time 
///</describe>
/// <date>2019/3/6</date>
///***********************************************************************
#ifndef COUNTER_H
#define COUNTER_H

namespace System
{
	namespace Clock
	{
		///*********************************************************
		/// <class>Counter</class>
		/// <summary>
		/// Count the time for task
		/// </summary>
		/// <version>V1.0.0 </version>
		/// <goup> C++</group>
		/// <author>tangyingzhong</author>
		/// <contact>tangyingzhong@szangell.com</contact>
		///*********************************************************
		class Counter
		{
		public:
			typedef System::Empty Empty;
			typedef System::Double TimeS;
			typedef System::Double TimeMs;
			typedef System::Double TimeUs;
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
				this->m_Disposed = bDisposed;
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

#endif //COUNTER_H_