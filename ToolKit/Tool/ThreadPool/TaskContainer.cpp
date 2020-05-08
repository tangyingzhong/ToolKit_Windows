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
int TaskContainer::AddTask(TaskEntry& task)
{
	if (m_TaskQueue.size() > MAX_TASK_QUEUE)
	{
		return 1;
	}

	m_TaskQueue.push(task);

	return 0;
}

// Get a task
bool TaskContainer::GetOneTask(TaskEntry& task)
{
	if (IsEmpty())
	{
		return false;
	}

	task = m_TaskQueue.front();

	m_TaskQueue.pop();

	return true;
}

// Is empty
bool TaskContainer::IsEmpty()
{
	return m_TaskQueue.empty();
}
