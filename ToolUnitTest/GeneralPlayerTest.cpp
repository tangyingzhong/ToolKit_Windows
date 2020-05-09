#include "stdafx.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Tool_UnitTest
{
	TEST_CLASS(GeneralPlayer_UnitTest)
	{
	public:
		TEST_METHOD(TestMethod_Load)
		{
			GeneralPlayer GeneralAudioPlayer;

			Assert::IsTrue(GeneralAudioPlayer.Load(_T("D:\\林俊杰 - 可惜没如果.wav")));
		}

		TEST_METHOD(TestMethod_Play)
		{
			GeneralPlayer GeneralAudioPlayer;

			Assert::IsTrue(GeneralAudioPlayer.Load(_T("D:\\林俊杰 - 可惜没如果.wav")));

			Assert::IsTrue(GeneralAudioPlayer.Play());

			FixedInt32 iEventCode = 0;
			GeneralAudioPlayer.WaitForCompletion(2 * 60 * 60, &iEventCode);
		}

		TEST_METHOD(TestMethod_GetCurVolume)
		{
			GeneralPlayer GeneralAudioPlayer;

			Assert::IsTrue(GeneralAudioPlayer.Load(_T("D:\\林俊杰 - 可惜没如果.wav")));

			FixedInt32 iVolume = GeneralAudioPlayer.GetCurrentVolume();

			Assert::IsTrue(iVolume != -1);

			Assert::IsTrue(GeneralAudioPlayer.Play());

			FixedInt32 iEventCode = 0;
			GeneralAudioPlayer.WaitForCompletion(2 * 60 * 1000, &iEventCode);
		}

		TEST_METHOD(TestMethod_SetCurVolume)
		{
			GeneralPlayer GeneralAudioPlayer;

			Assert::IsTrue(GeneralAudioPlayer.Load(_T("D:\\林俊杰 - 可惜没如果.wav")));

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
	};
}