///************************************************************************
/// <copyrigth>2018-2019 Corporation.All Rights Reserved</copyrigth>
/// <author>tangyingzhong</author>
/// <contact>tangyz114987@outlook.com</contact>
/// <version>v1.0.0</version>
/// <describe>
/// Delay for a time 
///</describe>
/// <date>2019/7/16</date>
///***********************************************************************
#ifndef DELAY_H
#define DELAY_H

#include "Tool/Common/SystemType.h"

namespace System
{
	namespace Clock
	{
		class Delay
		{
		public:
			typedef System::None None;
			typedef System::Int32 TimeUs;

		public:
			// Construct the Delay
			Delay();

			// Detructe the Delay
			~Delay();

		private:
			// Copy Delay
			Delay(const Delay& other) {	}

			// Asigment of Delay
			Delay& operator=(const Delay& other) {	}

		public:
			// Delay for us
			None DelayUs(TimeUs iTimeUs);

		private:
			// Init the delay 
			None Initialize();

			// Destory the delay
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
			// Disposed status
			BOOL m_Disposed;

		};
	}
}

#endif // DELAY_H