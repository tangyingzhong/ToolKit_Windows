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

namespace System
{
	namespace Thread
	{
		struct UserData
		{
			typedef bool(*GetIsExitThreadPool)();

			// User data
			void* pUserData;

			// Is exit the thread pool (Read not for write)
			GetIsExitThreadPool pPoolFunc;

			UserData()
			{
				pUserData = NULL;

				pPoolFunc = NULL;
			}
		};

		struct TaskEntry
		{
			typedef void(*TaskCallbackFunc)(UserData* pUserData);

			// Task id
			int iTaskId;

			// Thread id (Read not for write)
			unsigned long long iThreadId;

			// Task callback function
			TaskCallbackFunc pUserFunc;

			// User data
			UserData AttachedUserData;

			TaskEntry()
			{
				iTaskId = 0;

				iThreadId = 0;

				pUserFunc = NULL;
			}
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
