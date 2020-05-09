#include "stdafx.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Tool_UnitTest
{
	TEST_CLASS(Player_UnitTest)
	{
	public:
		TEST_METHOD(TestMethod_Play)
		{
			AudioPlayer Player;

			Assert::IsTrue(Player.Play(_T("D:\\林俊杰 - 可惜没如果.wav")));
		}
	};
}