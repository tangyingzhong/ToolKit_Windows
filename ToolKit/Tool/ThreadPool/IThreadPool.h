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
				m_strTaskName("Task"),
				m_bIsDetached(false),
				m_iThreadId(0),
				m_pUserFunc(NULL),
				m_pUserData(NULL),
				m_pExitPoolLock(NULL),
				m_bIsExitPool(false)				
			{
				SetExitPoolLock(new std::mutex());
			}

			// Destruct the task
			~TaskEntry()
			{
				if (GetExitPoolLock())
				{
					delete GetExitPoolLock();

					SetExitPoolLock(NULL);
				}
			}

			// Copy construct the task
			TaskEntry(const TaskEntry& other)
			{
				SetTaskId(other.GetTaskId());

				SetTaskName(other.GetTaskName());

				SetIsDetached(other.GetIsDetached());

				SetThreadId(other.GetThreadId());

				SetUserFunc(other.GetUserFunc());

				SetUserData(other.GetUserData());

				SetExitPoolLock(other.GetExitPoolLock());

				SetIsExitPool(other.GetIsExitPool());
			}

			// Assign the task
			TaskEntry& operator=(const TaskEntry& other)
			{
				if (this != &other)
				{
					SetTaskId(other.GetTaskId());

					SetTaskName(other.GetTaskName());

					SetIsDetached(other.GetIsDetached());

					SetThreadId(other.GetThreadId());

					SetUserFunc(other.GetUserFunc());

					SetUserData(other.GetUserData());

					SetExitPoolLock(other.GetExitPoolLock());

					SetIsExitPool(other.GetIsExitPool());
				}

				return *this;
			}

			// Is empty
			bool IsEmpty()
			{
				return GetUserFunc() == NULL;
			}

			// Get the IsExitPool
			inline bool GetIsExitPool() const
			{
				m_pExitPoolLock->lock();

				bool bRet = m_bIsExitPool;

				m_pExitPoolLock->unlock();

				return bRet;
			}

			// Set the IsExitPool
			inline void SetIsExitPool(bool bIsExitPool)
			{
				m_pExitPoolLock->lock();

				m_bIsExitPool = bIsExitPool;

				m_pExitPoolLock->unlock();
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

			// Get the IsDetached
			inline bool GetIsDetached() const
			{
				return m_bIsDetached;
			}

			// Set the IsDetached
			inline void SetIsDetached(bool bIsDetached)
			{
				m_bIsDetached = bIsDetached;
			}

			// Get the TaskName
			inline std::string GetTaskName() const
			{
				return m_strTaskName;
			}

			// Set the TaskName
			inline void SetTaskName(std::string strTaskName)
			{
				m_strTaskName = strTaskName;
			}

			// Get the ExitPoolLock
			inline std::mutex* GetExitPoolLock() const
			{
				return m_pExitPoolLock;
			}

			// Set the ExitPoolLock
			inline void SetExitPoolLock(std::mutex* pExitPoolLock)
			{
				m_pExitPoolLock = pExitPoolLock;
			}

		private:
			// Task id
			int m_iTaskId;
			
			// Task name
			std::string m_strTaskName;
		
			// Is detach the task
			bool m_bIsDetached;
			
			// Thread id (Read not for write)
			unsigned long long m_iThreadId;
		
			// Task callback function
			TaskCallbackFunc m_pUserFunc;
		
			// User data
			void* m_pUserData;
		
			// Lock for the thread pool exit
			std::mutex* m_pExitPoolLock;
			
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
			virtual int Stop(bool bForce = false) = 0;

			// Add Task to pool
			virtual bool AddTask(TaskEntry* pTask) = 0;

			// Get error message
			virtual std::string GetErrorMsg() = 0;

			// Transfer thread to container (It is no need to use for user)
			virtual bool Transfer(MyThread* pThread) = 0;	
		};
	}
}

#endif // ITHREADPOOL_H
