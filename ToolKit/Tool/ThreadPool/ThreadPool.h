///************************************************************************
/// <copyrigth>Voice AI Technology Of ShenZhen</copyrigth>
/// <author>tangyingzhong</author>
/// <contact>yingzhong@voiceaitech.com</contact>
/// <version>v1.0.0</version>
/// <describe>
///
///</describe>
/// <date>2020/2/28</date>
///***********************************************************************
#ifndef THREADPOOL_H
#define THREADPOOL_H

#include <queue>
#include <mutex>
#include "IThreadPool.h"
#include "MyThread.h"
#include "TaskContainer.h"
#include "IdelThreadContainer.h"
#include "WorkThreadContainer.h"

namespace System
{
	namespace Thread
	{
		class ThreadPool :public IThreadPool
		{
		public:
			// Construct the ThreadPool
			ThreadPool(int threadNum = 8);

			// Detructe the ThreadPool
			virtual ~ThreadPool();

		private:
			// Forbid the copy ThreadPool
			ThreadPool(const ThreadPool& other) {	};

			// Forbid the assigment of ThreadPool
			ThreadPool& operator=(const ThreadPool& other) { return *this; };

		public:
			// Start pool
			virtual void Start();

			// Stop pool
			virtual int Stop(bool bForce);

			// Add Task to pool
			virtual bool AddTask(TaskEntry& task);

			// Transfer thread to container
			virtual bool Transfer(MyThread* pThread);

			// Get error message
			virtual std::string GetErrorMsg();

		private:
			// Create idel container
			void CreateIdelContainer();

			// Destory idel container
			void DestoryIdelContainer();

			// Destory busy container
			void DestoryBusyContainer();

			// Run the pool
			void Run();

			// Get a task
			bool GetOneTask(TaskEntry& task);

			// Get an idel thread
			MyThread* GetAnIdelThread();

			// Add to work container
			bool AddToWorkContainer(MyThread* pThread);

			// Remove from the work container
			bool RemoveFromWorkContainer(MyThread* pThread);

			// Add to idel container
			bool AddToIdelContainer(MyThread* pThread);

			// Configure the thread
			bool ConfigureThread(MyThread* pThread, TaskEntry& task, bool bDetached);

			// Start thread
			void StartThread(MyThread* pThread);

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

			// Get the ErrorText
			inline std::string GetErrorText() const
			{
				return m_strErrorText;
			}

			// Set the ErrorText
			inline void SetErrorText(std::string strErrorText)
			{
				m_strErrorText = strErrorText;
			}

			// Get the ThreadCnt
			inline int GetThreadCnt() const
			{
				return m_iThreadCnt;
			}

			// Set the ThreadCnt
			inline void SetThreadCnt(int iThreadCnt)
			{
				m_iThreadCnt = iThreadCnt;
			}

			// Get the IdelTable
			inline IdelThreadContainer* GetIdelTable() const
			{
				return m_pIdelContainer;
			}

			// Set the IdelTable
			inline void SetIdelTable(IdelThreadContainer* pIdelTable)
			{
				m_pIdelContainer = pIdelTable;
			}

			// Get the IsStop
			inline bool GetIsForceStop() const
			{
				return m_bForceStop;
			}

			// Set the IsStop
			inline void SetIsForceStop(bool bIsStop)
			{
				m_bForceStop = bIsStop;
			}

			// Get the ForceStop
			inline bool GetForceStop() const
			{
				return m_bForceStop;
			}

			// Set the ForceStop
			inline void SetForceStop(bool bForceStop)
			{
				m_bForceStop = bForceStop;
			}

			// Get the StopPool
			inline bool GetStopPool() const
			{
				return m_bStopPool;
			}

			// Set the StopPool
			inline void SetStopPool(bool bStopPool)
			{
				m_bStopPool = bStopPool;
			}

		private:
			// Monitor thread
			std::thread m_MonitorThread;

			// Thread count in pool
			int m_iThreadCnt;

			// Idel container
			IdelThreadContainer* m_pIdelContainer;

			// Work container
			WorkThreadContainer m_WorkContainer;

			// Task queue
			TaskContainer m_TaskContainer;

			// Lock for the work list
			std::mutex m_WorkLock;

			// Lock for the idel table
			std::mutex m_IdelLock;

			// Lock for the task container
			std::mutex m_TaskLock;

			// Stop the pool
			bool m_bStopPool;

			// Force to stop
			bool m_bForceStop;

			// Error message
			std::string m_strErrorText;

			// Disposed status
			bool m_bDisposed;
		};
	}
}

#endif // THREADPOOL_H
