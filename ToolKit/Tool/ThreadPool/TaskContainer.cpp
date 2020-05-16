#include "TaskContainer.h"

using namespace System::Thread;

// Construct the TaskContainer
TaskContainer::TaskContainer() :m_bDisposed(false)
{

}

// Detructe the TaskContainer
TaskContainer::~TaskContainer()
{
	if (!GetDisposed())
	{
		SetDisposed(true);
	}
}

// Add task
int TaskContainer::AddTask(TaskEntry* pTask)
{
	if (m_TaskQueue.size() > MAX_TASK_QUEUE)
	{
		return 1;
	}

	m_TaskQueue.push(pTask);

	return 0;
}

// Get a task
TaskEntry* TaskContainer::GetOneTask()
{
	if (IsEmpty())
	{
		return NULL;
	}

	TaskEntry* pTask = m_TaskQueue.front();

	m_TaskQueue.pop();

	return pTask;
}

// Is empty
bool TaskContainer::IsEmpty()
{
	return m_TaskQueue.empty();
}
