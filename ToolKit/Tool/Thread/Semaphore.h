///************************************************************************
/// <copyrigth>2018-2019 Corporation.All Rights Reserved</copyrigth>
/// <author>tangyingzhong</author>
/// <contact>tangyz114987@outlook.com</contact>
/// <version>V1.0.0</version>
/// <describe>
/// Signal under the windows ,which used to manage several resources' used at one time
///</describe>
/// <date>2019/3/6</date>
///***********************************************************************
#ifndef	SEMAPHORE_H
#define	SEMAPHORE_H

#include "Tool\BaseType\String.h"

using namespace System::BasicType;

namespace System
{
	namespace Thread
	{
		///*********************************************************
		/// <class> Semaphore </class>
		/// <summary>
		/// Signal for manging resouces, that just like traffic signals
		/// </summary>
		/// <version>V1.0.0 </version>
		/// <goup> C++ </group>
		/// <author>tangyingzhong</author>
		/// <contact>tangyz114987@outlook.com</contact>
		///**********************************************************/
		class Semaphore
		{
		public:
			typedef System::Empty Empty;
			typedef System::Boolean BOOL;
			typedef System::Object SemaphoreHandle;
			typedef System::Int32 ResourceCount;
			typedef System::Int32 MsTimeout;
			typedef String SemaphoreName;

		public:
			// Construct the Semaphore with name
			Semaphore(SemaphoreName strSignalName = _T(""), ResourceCount iMinCount = 1, ResourceCount iMaxCount = 1);

			// Destruct the Semaphore
			~Semaphore();

			// Allow the object copying
			Semaphore(const Semaphore& other);

			// Allow the obejct assignment
			Semaphore& operator=(const Semaphore& other);

		public:
			// Wait for a semaphore
			Empty Acquire(MsTimeout iMsTimeout = INFINITE);

			// Make the sema to be signaled
			Empty Release();

		private:
			// Initialize the semaphore
			Empty Initialize();

			// Destory the semaphore
			Empty Destory();

			// Open the semaphore
			Empty Open();

			// Close the semaphore
			Empty Close();

		private:
			// Get the SignalHandle
			inline SemaphoreHandle GetSignalHandle() const
			{
				return m_SignalHandle;
			}

			// Set the SignalHandle
			inline Empty SetSignalHandle(SemaphoreHandle hSignalHandle)
			{
				this->m_SignalHandle = hSignalHandle;
			}

			// Get the semaphore name
			inline SemaphoreName GetSignalName() const
			{
				return m_SignalName;
			}

			// Set the semaphore name
			inline Empty SetSignalName(SemaphoreName strSignalName)
			{
				this->m_SignalName = strSignalName;
			}

			// Get the min resource count
			inline ResourceCount GetMinResourceCount() const
			{
				return m_MinCount;
			}

			// Set the min resource count
			inline Empty SetMinResourceCount(ResourceCount iMinCount)
			{
				this->m_MinCount = iMinCount;
			}

			// Get the max resource count
			inline ResourceCount GetMaxResourceCount() const
			{
				return m_MaxCount;
			}

			// Set the max resource count
			inline Empty SetMaxResourceCount(ResourceCount iMaxCount)
			{
				this->m_MaxCount = iMaxCount;
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
			// Semaphore handle
			SemaphoreHandle m_SignalHandle;

			// The name of the semaphore
			SemaphoreName m_SignalName;

			// Min value of the semaphore
			ResourceCount m_MinCount;

			// Max value of the semaphore
			ResourceCount m_MaxCount;

			// Disposed status
			BOOL m_Disposed;

		};
	}
}

#endif //SEMAPHORE_TANG_H_