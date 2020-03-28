///************************************************************************
/// <copyrigth>2018-2019 Corporation.All Rights Reserved</copyrigth>
/// <author>tangyingzhong</author>
/// <contact>tangyz114987@outlook.com</contact>
/// <version>v1.0.0</version>
/// <describe>
/// Signal under the windows ,which used to manage several resources' used at one time
///</describe>
/// <date>2019/7/16</date>
///***********************************************************************
#ifndef	SEMAPHORE_H
#define	SEMAPHORE_H

#include "Tool/BaseType/String.h"

using namespace System::BasicType;

namespace System
{
	namespace Thread
	{
		class Semaphore
		{
		public:
			typedef System::None None;
			typedef System::Boolean BOOL;
			typedef System::Object SemaphoreHandle;
			typedef System::Int32 ResourceCount;
			typedef System::Int32 MsTimeout;
			typedef String SemaphoreName;

		public:
			// Construct the Semaphore with name
			Semaphore(SemaphoreName strSignalName = _T(""), 
				ResourceCount iMinCount = 1, 
				ResourceCount iMaxCount = 1);

			// Destruct the Semaphore
			~Semaphore();

			// Allow the object copying
			Semaphore(const Semaphore& other);

			// Allow the obejct assignment
			Semaphore& operator=(const Semaphore& other);

		public:
			// Wait for a semaphore
			None Acquire(MsTimeout iMsTimeout = INFINITE);

			// Make the sema to be signaled
			None Release();

		private:
			// Initialize the semaphore
			None Initialize();

			// Destory the semaphore
			None Destory();

			// Open the semaphore
			None Open();

			// Close the semaphore
			None Close();

		private:
			// Get the SignalHandle
			inline SemaphoreHandle GetSignalHandle() const
			{
				return m_SignalHandle;
			}

			// Set the SignalHandle
			inline None SetSignalHandle(SemaphoreHandle hSignalHandle)
			{
				m_SignalHandle = hSignalHandle;
			}

			// Get the semaphore name
			inline SemaphoreName GetSignalName() const
			{
				return m_SignalName;
			}

			// Set the semaphore name
			inline None SetSignalName(SemaphoreName strSignalName)
			{
				m_SignalName = strSignalName;
			}

			// Get the min resource count
			inline ResourceCount GetMinResourceCount() const
			{
				return m_MinCount;
			}

			// Set the min resource count
			inline None SetMinResourceCount(ResourceCount iMinCount)
			{
				m_MinCount = iMinCount;
			}

			// Get the max resource count
			inline ResourceCount GetMaxResourceCount() const
			{
				return m_MaxCount;
			}

			// Set the max resource count
			inline None SetMaxResourceCount(ResourceCount iMaxCount)
			{
				m_MaxCount = iMaxCount;
			}

			// Get the disposed status
			inline BOOL GetDisposed() const
			{
				return m_Disposed;
			}

			// Set the disposed status
			inline None SetDisposed(BOOL bDisposed)
			{
				m_Disposed = bDisposed;
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

#endif // SEMAPHORE_H