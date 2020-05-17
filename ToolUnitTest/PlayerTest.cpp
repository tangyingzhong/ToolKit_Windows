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
				Player.Play("D:\\林俊杰.-.[因你而在](2013)[WAV].wav");
				});

			Sleep(50000);

			Player.Pause();

			Sleep(10000);

			Player.Continue();

			Sleep(50000);

			Player.Stop();

			if (t.joinable())
			{
				t.join();
			}
		}
	};
}