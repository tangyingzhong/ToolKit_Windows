///************************************************************************
/// <copyrigth>2018-2019 Corporation.All Rights Reserved</copyrigth>
/// <author>tangyingzhong</author>
/// <contact>tangyz114987@outlook.com</contact>
/// <version>V1.0.0</version>
/// <describe>
/// Windows lock on the user level so it is faster
///</describe>
/// <date>2019/3/6</date>
///***********************************************************************
#ifndef	MUTEX_H
#define	MUTEX_H

namespace System
{
	namespace Thread
	{
		///*********************************************************
		/// <class> Mutex </class>
		/// <summary>
		/// Lock the object or code section 
		/// </summary>
		/// <version>V1.0.0 </version>
		/// <goup> C++ </group>
		/// <author>tangyingzhong</author>
		/// <contact>tangyz114987@outlook.com</contact>
		///**********************************************************/
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

#endif //MUTEX_H_