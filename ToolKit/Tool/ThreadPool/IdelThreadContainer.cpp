#include "IdelThreadContainer.h"

using namespace System::Thread;

// Construct the IdelThreadContainer
IdelThreadContainer::IdelThreadContainer(IThreadPool* pThreadPool, int threadNum) :
	m_pThreadPool(pThreadPool),
	m_iThreadCnt(threadNum),
	m_bDisposed(false)
{
	Init();
}

// Detructe the IdelThreadContainer
IdelThreadContainer::~IdelThreadContainer()
{
	if (!GetDisposed())
	{
		SetDisposed(true);

		Destory();
	}
}

// Init the container
void IdelThreadContainer::Init()
{
	for (int index = 0; index < GetThreadCnt(); ++index)
	{
		MyThread* pThread = new MyThread(GetThreadPool());

		m_IdelTable.push_back(pThread);
	}
}

// Destory the container
void IdelThreadContainer::Destory()
{
	for (std::vector<MyThread*>::iterator Iter = m_IdelTable.begin();
		Iter != m_IdelTable.end();
		++Iter)
	{
		MyThread* pThread = *Iter;

		delete pThread;

		pThread = NULL;
	}
}

// Size of container
int IdelThreadContainer::GetSize()
{
	return static_cast<int>(m_IdelTable.size());
}

// Is container empty
bool IdelThreadContainer::IsEmpty()
{
	return m_IdelTable.empty();
}

// Add Thread
void IdelThreadContainer::AddThread(MyThread* pThread)
{
	m_IdelTable.push_back(pThread);
}

// Get top thread
MyThread* IdelThreadContainer::GetTopThread()
{
	MyThread* pThread = m_IdelTable.back();

	m_IdelTable.pop_back();

	return pThread;
}
