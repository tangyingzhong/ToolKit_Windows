#include <algorithm>
#include "WorkThreadContainer.h"

using namespace System::Thread;

// Construct the WorkThreadContainer
WorkThreadContainer::WorkThreadContainer():m_bDisposed(false)
{

}

// Detructe the WorkThreadContainer
WorkThreadContainer::~WorkThreadContainer()
{
	if (!GetDisposed())
	{
		SetDisposed(true);
	}
}

// Close all threads
void WorkThreadContainer::CloseAllThread()
{
	for (std::list<MyThread*>::iterator Iter = m_pWorkList.begin();
		Iter != m_pWorkList.end();
		++Iter)
	{
		MyThread* pThread = *Iter;

		// Force to exit the thread pool
		pThread->SetIsExitThreadPool(true);

		delete pThread;

		pThread = nullptr;
	}
}

// Add working thread
void WorkThreadContainer::Add(MyThread* pThread)
{
	m_pWorkList.push_back(pThread);
}

// Remove working thread
void WorkThreadContainer::Remove(MyThread* pThread)
{
	std::list<MyThread*>::iterator Iter = find(m_pWorkList.begin(), m_pWorkList.end(), pThread);

	m_pWorkList.erase(Iter);
}

// Size of container
int WorkThreadContainer::GetSize()
{
	return static_cast<int>(m_pWorkList.size());
}

// Is empty
bool WorkThreadContainer::IsEmpty()
{
	return m_pWorkList.empty();
}
