#include <stdio.h>
#include <string>
#include <sstream>
#include "MyThread.h"

using namespace System::Thread;

// Construct the MyThread
MyThread::MyThread(IThreadPool* pThreadPool) :
	m_iThreadId(0),
	m_pThreadPool(pThreadPool),
	m_bTransferOk(true),
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

	GetCurTask()->SetThreadId(GetId());

	(GetCurTask()->GetUserFunc())(GetCurTask());

	// Add current thread to idel container again
	if (GetThreadPool())
	{
		GetThreadPool()->Transfer(this);
	}
}

// Start the thread
void MyThread::Start(bool bIsDetach)
{
	m_CurThread = std::thread(&MyThread::Run, this);

	if (bIsDetach)
	{
		m_CurThread.detach();
	}
}
