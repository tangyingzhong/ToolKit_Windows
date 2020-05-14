///************************************************************************
/// <copyrigth>Voice AI Technology Of ShenZhen</copyrigth>
/// <author>tangyingzhong</author>
/// <contact>yingzhong@voiceaitech.com</contact>
/// <version>v1.0.0</version>
/// <describe>
/// It offers the thread pool interfaces
///</describe>
/// <date>2020/2/28</date>
///***********************************************************************
#ifndef ITHREADPOOL_H
#define ITHREADPOOL_H

#include <string>
#include <mutex>

namespace System
{
	namespace Thread
	{
		class TaskEntry
		{
		public:
			typedef void(*TaskCallbackFunc)(TaskEntry* pTask);

		public:
			// Contruct the task
			TaskEntry():
				m_iTaskId(0),
				m_iThreadId(0),
				m_bIsExitPool(false),
				m_pUserFunc(NULL),
				m_pUserData(NULL)
			{

			}

			// Copy construct the task
			TaskEntry(const TaskEntry& other)
			{
				//SetIsExitPool(other.GetIsExitPool());

				SetTaskId(other.GetTaskId());

				SetThreadId(other.GetThreadId());

				SetUserFunc(other.GetUserFunc());

				SetUserData(other.GetUserData());
			}

			// Assign the task
			TaskEntry& operator=(const TaskEntry& other)
			{
				if (this != &other)
				{
					//SetIsExitPool(other.GetIsExitPool());

					SetTaskId(other.GetTaskId());

					SetThreadId(other.GetThreadId());

					SetUserFunc(other.GetUserFunc());

					SetUserData(other.GetUserData());
				}

				return *this;
			}

			// Get the IsExitPool
			inline bool GetIsExitPool()
			{
				std::lock_guard<std::mutex> Locker(m_ExitPoolLock);

				return m_bIsExitPool;
			}

			// Set the IsExitPool
			inline void SetIsExitPool(bool bIsExitPool)
			{
				std::lock_guard<std::mutex> Locker(m_ExitPoolLock);

				m_bIsExitPool = bIsExitPool;
			}

			// Get the TaskId
			inline int GetTaskId() const
			{
				return m_iTaskId;
			}

			// Set the TaskId
			inline void SetTaskId(int iTaskId)
			{
				m_iTaskId = iTaskId;
			}

			// Get the ThreadId
			inline unsigned long long GetThreadId() const
			{
				return m_iThreadId;
			}

			// Set the ThreadId
			inline void SetThreadId(unsigned long long iThreadId)
			{
				m_iThreadId = iThreadId;
			}

			// Get the UserFunc
			inline TaskCallbackFunc GetUserFunc() const
			{
				return m_pUserFunc;
			}

			// Set the UserFunc
			inline void SetUserFunc(TaskCallbackFunc pUserFunc)
			{
				m_pUserFunc = pUserFunc;
			}

			// Get the UserData
			inline void* GetUserData() const
			{
				return m_pUserData;
			}

			// Set the UserData
			inline void SetUserData(void* pUserData)
			{
				m_pUserData = pUserData;
			}

		private:
			// Task id
			int m_iTaskId;
			
			// Thread id (Read not for write)
			unsigned long long m_iThreadId;
		
			// Task callback function
			TaskCallbackFunc m_pUserFunc;
		
			// User data
			void* m_pUserData;
		
			// Lock for the thread pool exit
			std::mutex m_ExitPoolLock;

			// Is exit the thread pool
			bool m_bIsExitPool;
		};

		class MyThread;

		class IThreadPool
		{
		public:
			// Detructe the IThreadPool
			virtual ~IThreadPool() {	}

		public:
			// Start pool
			virtual void Start() = 0;

			// Stop pool
			virtual int Stop(bool bForce) = 0;

			// Add Task to pool
			virtual int AddTask(TaskEntry& task) = 0;

			// Get error message
			virtual std::string GetErrorMsg() = 0;

			// Transfer thread to container (It is no need to use for user)
			virtual bool Transfer(MyThread* pThread) = 0;	
		};
	}
}

#endif // ITHREADPOOL_H
