///************************************************************************
/// <copyrigth>2018-2019 Corporation.All Rights Reserved</copyrigth>
/// <author>tangyingzhong</author>
/// <contact>tangyz114987@outlook.com</contact>
/// <version>v1.0.0</version>
/// <describe>
/// Windows lock on the user level so it is faster
///</describe>
/// <date>2019/7/16</date>
///***********************************************************************
#ifndef	MUTEX_H
#define	MUTEX_H

#include "Tool/Common/SystemType.h"

namespace System
{
	namespace Thread
	{
		class Mutex
		{
		public:
			typedef System::None None;
			typedef CRITICAL_SECTION CRITICAL;

		public:
			// Construct the Mutex
			Mutex();

			// Destruct the Mutex
			~Mutex();

		public:
			// Lock the resource
			None Lock();

			// Unlock the resource
			None Unlock();

		private:
			// Critical section
			CRITICAL m_CritialSection;
		};
	}
}

#endif // MUTEX_H