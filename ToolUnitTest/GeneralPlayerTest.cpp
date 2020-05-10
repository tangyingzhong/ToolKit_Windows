#include "stdafx.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace GeneralPlayer_UnitTest
{
	TEST_CLASS(GeneralPlayerTest)
	{
	public:
		TEST_METHOD(TestMethod_Load)
		{
			GeneralPlayer GeneralAudioPlayer;

			Assert::IsTrue(GeneralAudioPlayer.Load(_T("D:\\aa.wav")));
		}

		TEST_METHOD(TestMethod_Play)
		{
			GeneralPlayer GeneralAudioPlayer;

			Assert::IsTrue(GeneralAudioPlayer.Load(_T("D:\\aa.wav")));

			Assert::IsTrue(GeneralAudioPlayer.Play());

			FixedInt32 iEventCode = 0;
			GeneralAudioPlayer.WaitForCompletion(2 * 60 * 60, &iEventCode);
		}

		TEST_METHOD(TestMethod_GetCurVolume)
		{
			GeneralPlayer GeneralAudioPlayer;

			Assert::IsTrue(GeneralAudioPlayer.Load(_T("D:\\aa.wav")));

			FixedInt32 iVolume = GeneralAudioPlayer.GetCurrentVolume();

			Assert::IsTrue(iVolume != -1);

			Assert::IsTrue(GeneralAudioPlayer.Play());

			FixedInt32 iEventCode = 0;
			GeneralAudioPlayer.WaitForCompletion(2 * 60 * 1000, &iEventCode);
		}

		TEST_METHOD(TestMethod_SetCurVolume)
		{
			GeneralPlayer GeneralAudioPlayer;

			Assert::IsTrue(GeneralAudioPlayer.Load(_T("D:\\aa.wav")));

			FixedInt32 iVolume =10;

			Assert::IsTrue(GeneralAudioPlayer.SetVolume(iVolume));

			Assert::IsTrue(GeneralAudioPlayer.Play());

			FixedInt32 iEventCode = 0;
			GeneralAudioPlayer.WaitForCompletion(2 * 60 * 500, &iEventCode);

			FixedInt32 iVolume1 = 300;

			Assert::IsTrue(GeneralAudioPlayer.SetVolume(iVolume1));

			Assert::IsTrue(GeneralAudioPlayer.Play());

			FixedInt32 iEventCode1 = 0;
			GeneralAudioPlayer.WaitForCompletion(2 * 60 * 200, &iEventCode1);

			FixedInt32 iVolume2 = 1000;

			Assert::IsTrue(GeneralAudioPlayer.SetVolume(iVolume2));

			Assert::IsTrue(GeneralAudioPlayer.Play());

			FixedInt32 iEventCode12 = 0;
			GeneralAudioPlayer.WaitForCompletion(2 * 60 * 1000, &iEventCode12);
		}

		TEST_METHOD(TestMethod_Playing)
		{
			GeneralPlayer Player;

			Player.Load("D:\\aa.wav");

			Player.SetVolume(1000);

			std::thread t = std::thread([=, &Player] {
				Player.Play();
				});

			Sleep(10000);

			Player.Pause();

			Sleep(5000);

			Player.Resume();

			Sleep(15000);

			Player.Stop();

			if (t.joinable())
			{
				t.join();
			}
		}
	};
}