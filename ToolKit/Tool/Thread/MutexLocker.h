///************************************************************************
/// <copyrigth>2018-2019 Corporation.All Rights Reserved</copyrigth>
/// <author>tangyingzhong</author>
/// <contact>tangyz114987@outlook.com</contact>
/// <version>V1.0.0</version>
/// <describe>
/// It can help you release the lock automatically when your lock is out of scope
///</describe>
/// <date>2019/3/6</date>
///***********************************************************************
#ifndef MUTEXLOCKER_H
#define MUTEXLOCKER_H

#include "Mutex.h"

namespace System
{
	namespace Thread
	{
		///*********************************************************
		/// <class> MutexLocker </class>
		/// <summary>
		/// Help user to manage the lock automatically
		/// </summary>
		/// <version>V1.0.0 </version>
		/// <goup> C++ </group>
		/// <author>tangyingzhong</author>
		/// <contact>tangyz114987@outlook.com</contact>
		///**********************************************************/
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
				this->m_Lock = pLock;
			}

		private:
			// Thread lock
			Lock m_Lock;
		};
	}
}

#endif //MUTEXLOCKER_TANG_H_