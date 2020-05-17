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

			TaskEntry Task2;

			Task2.SetTaskId(2);

			Task2.SetTaskName("监控服务2");

			Task2.SetUserFunc(TaskCallbackFunc2);

			Task2.SetUserData(this);

			Assert::IsTrue(m_Pool.AddTask(&Task2));

			while (true)
			{
				Sleep(30000);

				SetExitTask(true);

				Sleep(30000);

				SetExitTask1(true);

				break;
			}

			m_Pool.Stop();
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

		// Get the exit task 
		inline Boolean GetExitTask1()
		{
			std::lock_guard<std::mutex> Locker(m_Lock1);

			return m_bExitTask1;
		}

		// Set the exit task
		inline void SetExitTask1(Boolean bExited)
		{
			std::lock_guard<std::mutex> Locker(m_Lock1);

			m_bExitTask1 = bExited;
		}

	private:
		// Callback count
		Int m_iExcuteCount;

		// Lock for the exit flag
		std::mutex m_Lock;

		// Exit thread
		Boolean m_bExitTask;

		// Lock for the exit flag
		std::mutex m_Lock1;

		// Exit thread
		Boolean m_bExitTask1;

		// Thread pool
		ThreadPool m_Pool;

		// Save the count
		Boolean Save(String strFilePath,String strData)
		{
			File FileHelper;

			if (!FileHelper.Open(strFilePath,File::FileMode::OPENORCREATE,File::FileAccess::WRITE))
			{
				return false;
			}

			FileHelper.Write(strData.ToANSIData().c_str(), 0, strData.ToANSIData().length());

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
				std::string strData = std::string("我的线程执行次数:") 
					+ std::to_string(pThis->m_iExcuteCount++)
					+"\r\n";

				std::cout << strData;

				pThis->Save("D:\\Pool1.txt", strData);

				for (int index = 0; index < iDelayCount; ++index)
				{
					if (pTask->GetIsExitPool())
					{
						return;
					}

					if (pThis->GetExitTask())
					{
						return;
					}

					std::this_thread::sleep_for(std::chrono::milliseconds(iDelayTime));
				}
			}
		}

		// Task callback function
		static void TaskCallbackFunc2(TaskEntry* pTask)
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

				if (pThis->GetExitTask1())
				{
					break;
				}

				// Do your business
				std::string strData = std::string("我的线程执行次数:")
					+ std::to_string(pThis->m_iExcuteCount++)
					+ "\r\n";

				std::cout << strData;

				pThis->Save("D:\\Pool2.txt", strData);

				for (int index = 0; index < iDelayCount; ++index)
				{
					if (pTask->GetIsExitPool())
					{
						return;
					}

					if (pThis->GetExitTask1())
					{
						return;
					}

					std::this_thread::sleep_for(std::chrono::milliseconds(iDelayTime));
				}
			}
		}
	};
}
