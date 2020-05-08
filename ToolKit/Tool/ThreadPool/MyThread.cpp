#include <stdio.h>
#include <string>
#include <sstream>
#include "MyThread.h"

using namespace System::Thread;

// Construct the MyThread
MyThread::MyThread(IThreadPool* pThreadPool):
	m_iThreadId(0),
	m_pThreadPool(pThreadPool),
	m_bIsDetached(true),
	m_bExitThreadPool(false),
	m_bDisposed(false)
{

}

// Detructe the MyThread
MyThread::~MyThread()
{
	if (!GetDisposed())
	{
		SetDisposed(true);

		if (m_CurThread.joinable())
		{
			m_CurThread.join();
		}
	}
}

// Set thread detach
void MyThread::SetDetachState(bool bIsDetach)
{
	SetIsDetached(bIsDetach);
}

// Get thread id
unsigned long long MyThread::GetThreadId()
{
	std::thread::id tid = std::this_thread::get_id();

	std::stringstream stream;

	stream << tid;

	std::string strThreadId = stream.str();

	unsigned long long threadId = std::stoull(strThreadId);

	return threadId;
}

// Run the thread
void MyThread::Run()
{
	SetId(GetThreadId());

	m_pTask->iThreadId = GetId();

	m_pTask->pFunc(m_pTask->pUserData, GetExitThreadPool());

	// Add current thread to idel container again
	if (GetThreadPool())
	{
		GetThreadPool()->Transfer(this);
	}
}

// Start the thread
void MyThread::Start()
{
	m_CurThread = std::thread(&MyThread::Run, this);

	if (GetIsDetached())
	{
		m_CurThread.detach();
	}
	else
	{
		m_CurThread.join();
	}
}
