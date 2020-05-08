///************************************************************************
/// <copyrigth>Voice AI Technology Of ShenZhen</copyrigth>
/// <author>tangyingzhong</author>
/// <contact>yingzhong@voiceaitech.com</contact>
/// <version>v1.0.0</version>
/// <describe>
///
///</describe>
/// <date>2020/3/2</date>
///***********************************************************************
#ifndef TASKCONTAINER_H
#define TASKCONTAINER_H

#include <queue>
#include "IThreadPool.h"

#define MAX_TASK_QUEUE 1024

namespace System
{
	namespace Thread
	{
		class TaskContainer
		{
		public:
			// Construct the TaskContainer
			TaskContainer();

			// Detructe the TaskContainer
			virtual ~TaskContainer();

		private:
			// Forbid the copy TaskContainer
			TaskContainer(const TaskContainer& other) {	};

			// Forbid the assigment of TaskContainer
			TaskContainer& operator=(const TaskContainer& other) { return *this; };

		public:
			// Add task
			int AddTask(TaskEntry& task);

			// Get a task
			bool GetOneTask(TaskEntry& task);

			// Is empty
			bool IsEmpty();

		private:
			// Get the disposed status
			inline bool GetDisposed() const
			{
				return m_bDisposed;
			}

			// Set the disposed status
			inline void SetDisposed(bool bDisposed)
			{
				m_bDisposed = bDisposed;
			}

		private:
			// Task queue
			std::queue<TaskEntry> m_TaskQueue;

			// Disposed status
			bool m_bDisposed;
		};
	}
}

#endif // TASKCONTAINER_H
