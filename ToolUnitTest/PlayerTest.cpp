#include "stdafx.h"
#include "CppUnitTest.h"
#include <thread>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Player_UnitTest
{
	TEST_CLASS(PlayerTest)
	{
	public:
		TEST_METHOD(TestMethod_Play)
		{
			AudioPlayer Player;

			std::thread t = std::thread([=,&Player]{
				Player.Play(_T("D:\\aa.wav"));
				});

			Sleep(10000);

			Player.Pause();

			Sleep(5000);

			Player.Continue();

			Sleep(15000);

			Player.Stop();

			if (t.joinable())
			{
				t.join();
			}
		}
	};
}