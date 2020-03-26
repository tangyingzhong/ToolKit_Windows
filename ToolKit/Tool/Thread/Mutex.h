///************************************************************************
/// <copyrigth>Voice AI Technology Of ShenZhen</copyrigth>
/// <author>tangyingzhong</author>
/// <contact>yingzhong@voiceaitech.com</contact>
/// <version>v1.0.0</version>
/// <describe>
/// Windows lock on the user level so it is faster
///</describe>
/// <date>2019/7/16</date>
///***********************************************************************
#ifndef	MUTEX_H
#define	MUTEX_H

#include "Common/SystemType.h"

namespace System
{
	namespace Thread
	{
		class Mutex
		{
		public:
			typedef System::Empty Empty;
			typedef CRITICAL_SECTION CRITICAL;

		public:
			// Construct the Mutex
			Mutex();

			// Destruct the Mutex
			~Mutex();

		public:
			// Lock the resource
			Empty Lock();

			// Unlock the resource
			Empty Unlock();

		private:
			// Critical section
			CRITICAL m_CritialSection;
		};
	}
}

#endif // MUTEX_H