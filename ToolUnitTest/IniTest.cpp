#include "stdafx.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Ini_UnitTest
{
	TEST_CLASS(IniTest)
	{
	public:
		TEST_METHOD(Test_GetKeyValue)
		{
			Ini IniReader("D:\\Test.ini");

			Double dValue;

			Assert::IsTrue(IniReader.GetKeyValue("线程", "最大线程数", dValue));

			Int iTaskCount;

			Assert::IsTrue(IniReader.GetKeyValue("线程", "Task", iTaskCount));

			Assert::IsTrue(iTaskCount == 12);

			Bool bEnable;

			Assert::IsTrue(IniReader.GetKeyValue("线程", "是否启动线程", bEnable));

			Assert::IsTrue(bEnable == false);

			String strValue;

			Assert::IsTrue(IniReader.GetKeyValue("线程", "拷问自己", strValue));

			Assert::IsTrue(strValue ==  "你是什么");
		}

		TEST_METHOD(Test_SetKeyValue)
		{
			Ini IniReader("D:\\Test.ini");

			Double dValue = 9.67;

			Assert::IsTrue(IniReader.SetKeyValue("线程", "最大线程数", dValue));

			Int iTaskCount = 12;

			Assert::IsTrue(IniReader.SetKeyValue("线程", "Task", iTaskCount));

			Bool bEnable = false;

			Assert::IsTrue(IniReader.SetKeyValue("线程", "是否启动线程", bEnable));

			String strValue = "你是什么";

			Assert::IsTrue(IniReader.SetKeyValue("线程", "拷问自己", strValue));
		}
	};
}
