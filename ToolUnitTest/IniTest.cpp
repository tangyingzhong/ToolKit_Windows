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
			Ini IniReader("D:\\initest.ini");

			Int iValue;

			Assert::IsTrue(IniReader.GetKeyValue("APP", "yu", iValue));
		}

		TEST_METHOD(Test_SetKeyValue)
		{
			Ini IniReader("D:\\initest1.ini");

			Double dValue = 9.67;

			Assert::IsTrue(IniReader.SetKeyValue("TU", "jk", dValue));
		}
	};
}
