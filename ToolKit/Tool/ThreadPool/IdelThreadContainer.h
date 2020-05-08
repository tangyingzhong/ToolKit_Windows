///************************************************************************
/// <copyrigth>Voice AI Technology Of ShenZhen</copyrigth>
/// <author>tangyingzhong</author>
/// <contact>yingzhong@voiceaitech.com</contact>
/// <version>v1.0.0</version>
/// <describe>
/// Idel container to have threads
///</describe>
/// <date>2020/2/28</date>
///***********************************************************************
#ifndef IDELTHREADCONTAINER_H
#define IDELTHREADCONTAINER_H

#include <vector>
#include "IThreadPool.h"
#include "MyThread.h"

namespace System
{
	namespace Thread
	{
		class IdelThreadContainer
		{
		public:
			// Construct the IdelThreadContainer
			IdelThreadContainer(IThreadPool* pThreadPool, int threadNum);

			// Detructe the IdelThreadContainer
			virtual ~IdelThreadContainer();

		private:
			// Forbid the copy IdelThreadContainer
			IdelThreadContainer(const IdelThreadContainer& other) {	};

			// Forbid the assigment of IdelThreadContainer
			IdelThreadContainer& operator=(const IdelThreadContainer& other) { return *this; };

		public:
			// Is container empty
			bool IsEmpty();

			// Size of container
			int GetSize();

			// Add Thread
			void AddThread(MyThread* pThread);

			// Get top thread
			MyThread* GetTopThread();

		private:
			// Init the container
			void Init();

			// Destory the container
			void Destory();

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

			// Get the ThreadPool
			inline IThreadPool* GetThreadPool() const
			{
				return m_pThreadPool;
			}

			// Set the ThreadPool
			inline void SetThreadPool(IThreadPool* pThreadPool)
			{
				m_pThreadPool = pThreadPool;
			}

			// Get the ThreadCnt
			inline int GetThreadCnt() const
			{
				return m_iThreadCnt;
			}

			// Set the ThreadCnt
			inline void SetThreadCnt(int iThreadCnt)
			{
				m_iThreadCnt = iThreadCnt;
			}

		private:
			// Thread pool
			IThreadPool* m_pThreadPool;

			// Thread count
			int m_iThreadCnt;

			// Thread table
			std::vector<MyThread*> m_IdelTable;

			// Disposed status
			bool m_bDisposed;
		};
	}
}

#endif // IDELTHREADCONTAINER_H
