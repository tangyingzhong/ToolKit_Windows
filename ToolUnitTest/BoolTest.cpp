///************************************************************************
/// <copyrigth>2018-2019 Corporation.All Rights Reserved</copyrigth>
/// <author>tangyingzhong</author>
/// <contact>tangyz114987@outlook.com</contact>
/// <version>V1.0.0</version>
/// <describe>
/// Test Bool class 
///</describe>
/// <date>2019/4/18</date>
///***********************************************************************

#include "StdAfx.h"
#include <CppUnitTest.h>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace System::BasicType;

namespace Bool_UnitTest
{
	TEST_CLASS(BoolTest)
	{
	public:
		// Test operator bool() const
		TEST_METHOD(TestMethod_operator_bool)
		{
			Bool a = false;

			bool b = true;

			std::cout << a << "-" << b << std::endl;
		}

		// Test == function
		TEST_METHOD(TestMethod_operator_Equal)
		{
			Bool a = true;

			bool b = true;

			bool bRet = false;

			if (a == b)
			{
				bRet = true;
			}

			Assert::IsTrue(bRet == true);
		}

		// Test == function
		TEST_METHOD(TestMethod_operator_Equal2)
		{
			Bool a = true;

			Bool b = true;

			bool bRet = false;

			if (a == b)
			{
				bRet = true;
			}

			Assert::IsTrue(bRet == true);
		}

		// Test != function
		TEST_METHOD(TestMethod_operator_NotEqaul)
		{
			Bool a = true;

			Bool b = false;

			bool bRet = false;

			if (a != b)
			{
				bRet = true;
			}

			Assert::IsTrue(bRet == true);
		}

		// Test != function
		TEST_METHOD(TestMethod_operator_NotEqaul2)
		{
			Bool a = true;

			bool b = false;

			bool bRet = false;

			if (a != b)
			{
				bRet = true;
			}

			Assert::IsTrue(bRet == true);
		}

		// Test ! function
		TEST_METHOD(TestMethod_operator_ReverseFunc)
		{
			Bool a = true;

			Bool c = !a;

			Assert::IsTrue(c == false);
		}

		// Test ! function
		TEST_METHOD(TestMethod_operator_ReverseFunc1)
		{
			Bool a = false;

			bool c = !a;

			Assert::IsTrue(c == true);
		}

		// Test Parse function
		TEST_METHOD(TestMethod_operator_ParseFunc)
		{
			Bool a = Bool::Parse("true");

			Assert::IsTrue(a == true);
		}

		// Test ToString function
		TEST_METHOD(TestMethod_operator_ToStringFunc)
		{
			Bool a = false;

			String strValue = a.ToString();

			Assert::IsTrue(strValue == _T("false"));
		}
	};
}
