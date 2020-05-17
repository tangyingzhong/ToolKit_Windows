///************************************************************************
/// <copyrigth>Voice AI Technology Of ShenZhen</copyrigth>
/// <author>tangyingzhong</author>
/// <contact>yingzhong@voiceaitech.com</contact>
/// <version>v1.0.0</version>
/// <describe>
/// This is c++11 thread
///</describe>
/// <date>2020/2/28</date>
///***********************************************************************
#ifndef MYTHREAD_H
#define MYTHREAD_H

#include <thread>
#include <mutex>
#include "IThreadPool.h"

namespace System
{
	namespace Thread
	{
		class MyThread :public std::thread
		{
		public:
			// Construct the MyThread
			MyThread(IThreadPool* pThreadPool);

			// Detructe the MyThread
			virtual ~MyThread();

		private:
			// Forbid the copy MyThread
			MyThread(const MyThread& other) {	};

			// Forbid the assigment of MyThread
			MyThread& operator=(const MyThread& other) { return *this; };

		public:
			// Start the thread
			void Start(bool bIsDetach);

			// Get the ThreadId
			inline unsigned long long GetId() const
			{
				return m_iThreadId;
			}

			// Set the Task
			inline void SetTask(TaskEntry* pTask)
			{
				SetCurTask(pTask);
			}

			// Set the ExitThreadPool
			void SetIsExitThreadPool(bool bExitThreadPool)
			{
				GetCurTask()->SetIsExitPool(bExitThreadPool);
			}

			// Get the TransferOk
			inline bool GetTransferOk()
			{
				std::lock_guard<std::mutex> Locker(m_TransferLock);

				return m_bTransferOk;
			}

			// Set the TransferOk
			inline void SetTransferOk(bool bTransferOk)
			{
				std::lock_guard<std::mutex> Locker(m_TransferLock);

				m_bTransferOk = bTransferOk;
			}

		private:
			// Run the thread
			void Run();

			// Get thread id
			unsigned long long GetThreadId();

		private:
			// Get the disposed status
			inline bool GetDisposed() const
			{
				return m_bDisposed;
			}

			// Set the disposed status
			inline void SetDisposed(bool bDisposed)
			{
				m_bDisposed = bDisposed;
			}

			// Get the ThreadPool
			inline IThreadPool* GetThreadPool() const
			{
				return m_pThreadPool;
			}

			// Set the ThreadPool
			inline void SetThreadPool(IThreadPool* pThreadPool)
			{
				m_pThreadPool = pThreadPool;
			}

			// Get the Task
			inline TaskEntry* GetCurTask()
			{
				return m_pTask;
			}

			// Set the Task
			inline void SetCurTask(TaskEntry* pTask)
			{
				m_pTask = pTask;
			}

			// Set the ThreadId
			inline void SetId(unsigned long long iThreadId)
			{
				m_iThreadId = iThreadId;
			}

		private:
			// Thread id
			unsigned long long m_iThreadId;

			// Thread pool
			IThreadPool* m_pThreadPool;

			// Task
			TaskEntry* m_pTask;
		
			// Current thread
			std::thread m_CurThread;

			// Lock for the thread pool exit
			std::mutex m_TransferLock;

			// Is transfer task ok
			bool m_bTransferOk;

			// Disposed status
			bool m_bDisposed;
		};
	}
}

#endif // MYTHREAD_H
