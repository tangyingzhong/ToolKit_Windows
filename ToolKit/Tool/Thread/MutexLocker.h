///************************************************************************
/// <copyrigth>Voice AI Technology Of ShenZhen</copyrigth>
/// <author>tangyingzhong</author>
/// <contact>yingzhong@voiceaitech.com</contact>
/// <version>v1.0.0</version>
/// <describe>
/// It can help you release the lock automatically when your lock is out of scope
///</describe>
/// <date>2019/7/16</date>
///***********************************************************************
#ifndef MUTEXLOCKER_H
#define MUTEXLOCKER_H

#include "Mutex.h"

namespace System
{
	namespace Thread
	{
		class MutexLocker
		{
		public:
			typedef System::Empty Empty;
			typedef Mutex* Lock;

		public:
			// Construct the MutexLocker
			MutexLocker(Lock pLock);

			// Detructe the MutexLocker
			~MutexLocker();

		private:
			// Get the Locker
			inline Lock GetLocker() const
			{
				return m_Lock;
			}

			// Set the Locker
			inline Empty SetLocker(Lock pLock)
			{
				m_Lock = pLock;
			}

		private:
			// Thread lock
			Lock m_Lock;
		};
	}
}

#endif // MUTEXLOCKER_H