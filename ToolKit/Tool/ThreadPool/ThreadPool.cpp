#include <mutex>
#include <thread>
#include <iostream>
#include <sstream>
#include "MyThread.h"
#include "ThreadPool.h"

using namespace System::Thread;

// Construct the ThreadPool
ThreadPool::ThreadPool(int threadNum) :
	m_iMonitorThreadId(0),
	m_iThreadCnt(threadNum),
	m_pIdelContainer(NULL),
	m_bStopPool(false),
	m_bForceStop(false),
	m_iCurWorkNum(0),
	m_strErrorText(""),
	m_bDisposed(false)
{
	// Create idel container
	CreateIdelContainer();
}

// Detructe the ThreadPool
ThreadPool::~ThreadPool()
{
	if (!GetDisposed())
	{
		SetDisposed(true);

		Stop(true);
	}
}

// Create idel container
void ThreadPool::CreateIdelContainer()
{
	SetIdelTable(new IdelThreadContainer(this, GetThreadCnt()));
}

// Destory idel container
void ThreadPool::DestoryIdelContainer()
{
	if (GetIdelTable())
	{
		delete GetIdelTable();

		SetIdelTable(NULL);
	}
}

// Force to exit all busy threads
void ThreadPool::ForceExitAllBusyThreads()
{
	if (!m_WorkContainer.IsEmpty())
	{
		m_WorkContainer.CloseAllThreads();
	}
}

// Destory busy container
void ThreadPool::DestoryBusyContainer()
{
	m_WorkContainer.CloseAllThreads();
}

// Get thread id
unsigned long long ThreadPool::GetThreadId()
{
	std::thread::id tid = std::this_thread::get_id();

	std::stringstream stream;

	stream << tid;

	std::string strThreadId = stream.str();

	unsigned long long threadId = std::stoull(strThreadId);

	return threadId;
}

// Is all idel threads ready
bool ThreadPool::IsAllIdelThreadsReady()
{
	std::lock_guard<std::mutex> Locker(m_WorkLock);

	if (GetIdelTable() == NULL)
	{
		SetErrorText("Idel container is empty !");

		return false;
	}

	if (GetIdelTable()->IsEmpty())
	{
		SetErrorText("Idel container has no any thread !");

		return false;
	}

	// Check current working thread number
	if (GetCurWorkNum() != 0)
	{
		std::cout << "There are some still working threads !" << std::endl;

		return false;
	}

	if (!GetIdelTable()->IsAllThreadsReady())
	{
		std::cout << "Wait for some thread's transferring ok !" << std::endl;

		return false;
	}

	return true;
}

// Wait for busy threads' exit
bool ThreadPool::IsAllBusyThreadsExited()
{
	std::lock_guard<std::mutex> Locker(m_WorkLock);

	if (!m_WorkContainer.IsEmpty())
	{
		std::cout << "Wait for work container empty" << std::endl;

		return false;
	}

	return true;
}

// Run the pool
void ThreadPool::Run()
{
	// Get the monitor thread's id
	SetMonitorThreadId(GetThreadId());

	while (1)
	{
		if (GetStopPool())
		{
			if (GetForceStop())
			{
				// Force to exit all busy threads
				ForceExitAllBusyThreads();

				std::cout << "Force to exit the thread pool" << std::endl;
			}
			else
			{
				std::cout << "Not force to exit the pool" << std::endl;
			}

			// Wait for all busy threads' exit
			if (!IsAllBusyThreadsExited())
			{
				continue;
			}

			// Wait for all ldel threads ready
			if (!IsAllIdelThreadsReady())
			{
				continue;
			}

			// Destory idel container
			DestoryIdelContainer();

			break;
		}

		// Get an idel thread 
		MyThread* pThread = GetAnIdelThread();
		if (pThread == NULL)
		{
			std::this_thread::sleep_for(std::chrono::milliseconds(500));

			continue;
		}

		std::cout << "Get an idel thread to run the task " << std::endl;

		std::cout << "Idel container size :" << GetIdelTable()->GetSize() << std::endl;

		// Get a task
		TaskEntry* pCurTask = GetOneTask();
		if (pCurTask == NULL || pCurTask->IsEmpty())
		{
			std::this_thread::sleep_for(std::chrono::milliseconds(500));

			continue;
		}

		std::cout << "Get a task to run: " << std::to_string(pCurTask->GetTaskId()) << std::endl;

		// Start thread
		if (!StartTaskThread(pThread, pCurTask))
		{
			std::this_thread::sleep_for(std::chrono::milliseconds(500));

			continue;
		}

		std::cout << "Start task now with thread : " << std::to_string(pThread->GetId()) << std::endl;
	}
}

// Start thread
bool ThreadPool::StartTaskThread(MyThread* pThread,TaskEntry* pTask)
{
	if (pThread == NULL)
	{
		SetErrorText("Failed to start the thread because it is null !");

		return false;
	}

	pThread->SetTask(pTask);

	pThread->SetTransferOk(false);

	if (!pTask->GetIsDetached())
	{
		// Add the thread to work container
		AddToWorkContainer(pThread);

		SetCurWorkNum(GetCurWorkNum() + 1);

		std::cout << "Add the idel thread to work container" << std::endl;

		std::cout << "work container size :" << m_WorkContainer.GetSize() << std::endl;
	}

	pThread->Start(pTask->GetIsDetached());

	return true;
}

// Start pool
void ThreadPool::Start()
{
	m_MonitorThread = std::thread(&ThreadPool::Run, this);
}

// Stop pool
int ThreadPool::Stop(bool bForce)
{
	SetStopPool(true);

	SetForceStop(bForce);

	if (m_MonitorThread.joinable())
	{
		m_MonitorThread.join();
	}

	return 0;
}

// Get a task
TaskEntry* ThreadPool::GetOneTask()
{
	if (m_TaskContainer.IsEmpty())
	{
		SetErrorText("Failed to get a task from task container because it is empty !");

		return NULL;
	}

	std::lock_guard<std::mutex> Locker(m_TaskLock);

	TaskEntry* pTask = m_TaskContainer.GetOneTask();

	return pTask;
}

// Add Task to pool
bool ThreadPool::AddTask(TaskEntry* pTask)
{
	if (pTask==NULL)
	{
		SetErrorText("Failed to add task because it is null !");

		return false;
	}

	std::lock_guard<std::mutex> Locker(m_TaskLock);

	int iRet = m_TaskContainer.AddTask(pTask);
	if (iRet==1)
	{
		SetErrorText("Failed to add task because task is full !");

		return false;
	}
	else if (iRet == 2)
	{
		SetErrorText("Failed to add task because task container is full !");

		return false;
	}

	return true;
}

// Get an idel thread
MyThread* ThreadPool::GetAnIdelThread()
{
	if (GetIdelTable() == NULL)
	{
		SetErrorText("Idel table is null !");

		return NULL;
	}

	if (GetIdelTable()->IsEmpty())
	{
		SetErrorText("Idel table is empty !");

		return NULL;
	}

	std::lock_guard<std::mutex> Locker(m_IdelLock);

	return GetIdelTable()->GetTopThread();
}

// Add to work container
bool ThreadPool::AddToWorkContainer(MyThread* pThread)
{
	if (pThread == NULL)
	{
		SetErrorText("Failed to add to busy container,because of thread is null !");

		return false;
	}

	std::lock_guard<std::mutex> Locker(m_WorkLock);

	m_WorkContainer.Add(pThread);

	return true;
}

// Remove from the work container
bool ThreadPool::RemoveFromWorkContainer(MyThread* pThread)
{
	if (pThread == NULL)
	{
		SetErrorText("Failed to remove the thread because of thread is null !");

		return false;
	}

	std::lock_guard<std::mutex> Locker(m_WorkLock);

	m_WorkContainer.Remove(pThread);

	return true;
}

// Add to idel container
bool ThreadPool::AddToIdelContainer(MyThread* pThread)
{
	if (pThread == NULL)
	{
		SetErrorText("Failed to add thread to idel container because of thread is null !");

		return false;
	}

	std::lock_guard<std::mutex> Locker(m_IdelLock);

	GetIdelTable()->AddThread(pThread);

	return true;
}

// Transfer thread to container
bool ThreadPool::Transfer(MyThread* pThread)
{
	std::cout << "Enter the final transfer job" << std::endl;

	// Remove from the work list
	if (!RemoveFromWorkContainer(pThread))
	{
		return false;
	}

	std::cout << "Finish the removing from work container:" << std::to_string(pThread->GetId()) << std::endl;

	std::cout << "Final work container size :" << m_WorkContainer.GetSize() << std::endl;

	// Add to the idel table
	if (!AddToIdelContainer(pThread))
	{
		return false;
	}

	std::cout << "Re-add to the idel container" << std::endl;

	std::cout << "Final idel container size :" << GetIdelTable()->GetSize() << std::endl;

	pThread->SetTransferOk(true);

	// Total working thread number's update
	SetCurWorkNum(GetCurWorkNum() - 1);

	return true;
}

// Get error message
std::string ThreadPool::GetErrorMsg()
{
	return GetErrorText();
}
