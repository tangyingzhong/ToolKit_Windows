///************************************************************************
/// <copyrigth>Voice AI Technology Of ShenZhen</copyrigth>
/// <author>tangyingzhong</author>
/// <contact>yingzhong@voiceaitech.com</contact>
/// <version>v1.0.0</version>
/// <describe>
///
///</describe>
/// <date>2020/2/28</date>
///***********************************************************************
#ifndef WORKTHREADCONTAINER_H
#define WORKTHREADCONTAINER_H

#include <list>
#include "MyThread.h"

namespace System
{
	namespace Thread
	{
		class WorkThreadContainer
		{
		public:
			// Construct the WorkThreadContainer
			WorkThreadContainer();

			// Detructe the WorkThreadContainer
			virtual ~WorkThreadContainer();

		private:
			// Forbid the copy WorkThreadContainer
			WorkThreadContainer(const WorkThreadContainer& other) {	};

			// Forbid the assigment of WorkThreadContainer
			WorkThreadContainer& operator=(const WorkThreadContainer& other) { return *this; };

		public:
			// Add working thread
			void Add(MyThread* pThread);

			// Remove working thread
			void Remove(MyThread* pThread);

			// Size of container
			int GetSize();

			// Is empty
			bool IsEmpty();

			// Close all threads
			void CloseAllThreads();

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
			// Thread list
			std::list<MyThread*> m_pWorkList;

			// Disposed status
			bool m_bDisposed;
		};
	}
}

#endif // WORKTHREADCONTAINER_H
