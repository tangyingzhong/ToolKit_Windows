#include "stdafx.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Pool_UnitTest
{
	TEST_CLASS(ThreadPoolTest)
	{
	public:
		TEST_METHOD(Test_PoolStartFunc)
		{
			m_Pool.Start();

			TaskEntry Task;

			Task.SetTaskId(1);

			Task.SetTaskName("监控服务");

			Task.SetUserFunc(TaskCallbackFunc);

			Task.SetUserData(this);

			Assert::IsTrue(m_Pool.AddTask(&Task));

			while (true)
			{
				Sleep(60000);

				m_Pool.Stop(true);

				break;
			}
		}

	private:
		// Get the exit task 
		inline Boolean GetExitTask()
		{
			std::lock_guard<std::mutex> Locker(m_Lock);

			return m_bExitTask;
		}

		// Set the exit task
		inline void SetExitTask(Boolean bExited)
		{
			std::lock_guard<std::mutex> Locker(m_Lock);

			m_bExitTask = bExited;
		}

	private:
		// Callback count
		Int m_iExcuteCount;

		// Lock for the exit flag
		std::mutex m_Lock;

		// Exit thread
		Boolean m_bExitTask;

		// Thread pool
		ThreadPool m_Pool;

		// Save the count
		Boolean Save(Int32 iCount)
		{
			File FileHelper;

			if (!FileHelper.Open("D:\\PoolTest.txt",File::FileMode::OPENORCREATE,File::FileAccess::WRITE))
			{
				return false;
			}

			std::string strCount = Int(iCount).ToString().ToANSIData() + "\r\n";

			FileHelper.Write(strCount.c_str(), 0, strCount.length());

			FileHelper.Close();

			return true;
		}

		// Task callback function
		static void TaskCallbackFunc(TaskEntry* pTask)
		{
			ThreadPoolTest* pThis = (ThreadPoolTest*)(pTask->GetUserData());

			Int32 iTotalDelayTime = 600;

			Int iDelayTime = 60;

			Int32 iDelayCount = iTotalDelayTime / iDelayTime;

			while (1)
			{
				if (pTask->GetIsExitPool())
				{
					break;
				}

				if (pThis->GetExitTask())
				{
					break;
				}

				// Do your business
				std::cout << "我的线程执行次数:" << pThis->m_iExcuteCount++ << std::endl;

				pThis->Save(pThis->m_iExcuteCount);

				for (int index = 0; index < iDelayCount; ++index)
				{
					if (pTask->GetIsExitPool())
					{
						break;
					}

					std::this_thread::sleep_for(std::chrono::milliseconds(iDelayTime));
				}
			}
		}
	};
}
