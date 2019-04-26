///************************************************************************
/// <copyrigth>2018-2019 Corporation.All Rights Reserved</copyrigth>
/// <author>tangyingzhong</author>
/// <contact>tangyz114987@outlook.com</contact>
/// <version>V1.0.0</version>
/// <describe>
/// Test Int class 
///</describe>
/// <date>2019/4/18</date>
///***********************************************************************

#include "StdAfx.h"
#include <CppUnitTest.h>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace System::BasicType;

namespace ToolUnitTest
{
	TEST_CLASS(IntTest)
	{
	public:
		// Init the class
		TEST_CLASS_INITIALIZE(InitInt)
		{

		}

		// Clean up the class
		TEST_CLASS_CLEANUP(CleanInt)
		{

		}

		// Test == function
		TEST_METHOD(TestEqaulFunc1)
		{
			Int a = 90;

			int b = 90;

			bool bRet = false;

			if (a == b)
			{
				bRet = true;
			}

			Assert::IsTrue(bRet == true);
		}

		// Test == function
		TEST_METHOD(TestEqaulFunc2)
		{
			Int a = 90;

			Int b = 90;

			bool bRet = false;

			if (a == b)
			{
				bRet = true;
			}

			Assert::IsTrue(bRet == true);
		}

		// Test != function
		TEST_METHOD(TestNotEqaulFunc1)
		{
			Int a = 90;

			int b = 12;

			bool bRet = false;

			if (a != b)
			{
				bRet = true;
			}

			Assert::IsTrue(bRet == true);
		}

		// Test != function
		TEST_METHOD(TestNotEqaulFunc2)
		{
			Int a = 90;

			Int b = 190;

			bool bRet = false;

			if (a != b)
			{
				bRet = true;
			}

			Assert::IsTrue(bRet == true);
		}

		// Test + function
		TEST_METHOD(TestAddFunc1)
		{
			Int a = 90;

			int b = 22;

			Int c = a + b;

			Assert::IsTrue(c == 112);
		}

		// Test + function
		TEST_METHOD(TestAddFunc2)
		{
			Int a = 90;

			Int b = 22;

			Int c = a + b;

			Assert::IsTrue(c == 112);
		}

		// Test + function
		TEST_METHOD(TestAddFunc3)
		{
			Int a = 90.45;

			Int b = 22;

			Int c = a + b;

			Assert::IsTrue(c == 112);
		}

		// Test - function
		TEST_METHOD(TestSubFunc1)
		{
			Int a = 90.45;

			int b = 50;

			Int c = a - b;

			Assert::IsTrue(c == 40);
		}

		// Test - function
		TEST_METHOD(TestSubFunc2)
		{
			Int a = 90.45;

			int b = 50;

			Int c = b - a;

			Assert::IsTrue(c == -40);
		}


		// Test * function
		TEST_METHOD(TesMulFunc3)
		{
			Int a = 20;

			int b = 50;

			Int c = a*b;

			Assert::IsTrue(c == 1000);
		}

		// Test * function
		TEST_METHOD(TesMulFunc4)
		{
			Int a = 20;

			int b = 50;

			Int c = b*a;

			Assert::IsTrue(c == 1000);
		}

		// Test / function
		TEST_METHOD(TestDivideFunc1)
		{
			Int a = 100;

			int b = 50;

			Int c = a / b;

			Assert::IsTrue(c == 2);
		}

		// Test / function
		TEST_METHOD(TestDivideFunc2)
		{
			Int a = 2;

			int b = 100;

			Int c = b / a;

			Assert::IsTrue(c == 50);
		}

		// Test / function
		TEST_METHOD(TestDivideFunc3)
		{
			Int a = -30;

			int b = -90;

			Int c = b / a;

			Assert::IsTrue(c == 3);
		}

		// Test / function
		TEST_METHOD(TestDivideFunc4)
		{
			Int a = 450;

			int b = 0;

			Int c = a / b;

			Assert::IsTrue(c == -1);
		}

	
	};
}
