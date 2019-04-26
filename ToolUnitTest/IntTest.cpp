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

		// Test % function
		TEST_METHOD(TestSeFunc1)
		{
			Int a = 450;

			int b = 50;

			Int c = a % b;

			Assert::IsTrue(c == 0);
		}

		// Test % function
		TEST_METHOD(TestSeFunc2)
		{
			Int a = 450;

			int b = 7;

			Int c = a % b;

			Assert::IsTrue(c == 2);
		}

		// Test << function
		TEST_METHOD(TestLeftFunc1)
		{
			Int a = 2;

			Int c = a << 2;

			Assert::IsTrue(c == 8);
		}
	
		// Test << function
		TEST_METHOD(TestLeftFunc2)
		{
			Int a = -2;

			Int c = a << 2;

			Assert::IsTrue(c == -8);
		}

		// Test << function
		TEST_METHOD(TestLeftFunc3)
		{
			Int a = 2;

			Int c = a << -2;

			Assert::IsTrue(c != -8);
		}

		// Test >> function
		TEST_METHOD(TestRightFunc1)
		{
			Int a = 2;

			Int c = a >> -2;

			Assert::IsTrue(c != -8);
		}

		// Test >> function
		TEST_METHOD(TestRightFunc2)
		{
			Int a = 2;

			Int c = a >> 2;

			Assert::IsTrue(c != -8);
		}

		// Test >> function
		TEST_METHOD(TestRightFunc3)
		{
			Int a = 4;

			Int c = a >> 2;

			Assert::IsTrue(c == 1);
		}

		// Test ! function
		TEST_METHOD(TestReverseFunc)
		{
			Int a = 2;

			Int c = !a;

			Assert::IsTrue(c == 0);
		}

		// Test ! function
		TEST_METHOD(TestReverseFunc1)
		{
			Int a = 200;

			Int c = !a;

			Assert::IsTrue(c == 0);
		}

		// Test ! function
		TEST_METHOD(TestReverseFunc2)
		{
			Int a = 0;

			Int c = !a;

			Assert::IsTrue(c == 1);
		}

		// Test ++ function
		TEST_METHOD(TestAddAddFunc1)
		{
			Int a = 2;

			a++;

			Assert::IsTrue(a == 3);
		}

		// Test ++ function
		TEST_METHOD(TestAddAddFunc2)
		{
			Int a = 2;

			++a;

			Assert::IsTrue(a == 3);
		}

		// Test ++ function
		TEST_METHOD(TestAddAddFunc3)
		{
			Int a = 2;

			Assert::IsTrue(a++ == 3);
		}

		// Test ++ function
		TEST_METHOD(TestAddAddFunc4)
		{
			Int a = 2;

			Assert::IsTrue(++a == 3);
		}

		// Test > function
		TEST_METHOD(TestBiggerFunc4)
		{
			Int a = 2;

			Int b = 32;

			Assert::IsTrue(b > a);
		}

		// Test > function
		TEST_METHOD(TestBiggerFunc2)
		{
			Int a = 2;

			int b = 32;

			Assert::IsTrue(b > a);
		}

		// Test >= function
		TEST_METHOD(TestBiggerThanFunc3)
		{
			Int a = 122;

			Int b = 122;

			Assert::IsTrue(a >= b);
		}

		// Test >= function
		TEST_METHOD(TestBiggerThanFunc4)
		{
			Int a = 122;

			int b = 122;

			Assert::IsTrue(a >= b);
		}

		// Test <= function
		TEST_METHOD(TestSmallThanFunc1)
		{
			Int a = 12;

			int b = 122;

			Assert::IsTrue(a <= b);
		}

		// Test <= function
		TEST_METHOD(TestSmallThanFunc2)
		{
			Int a = 122;

			int b = 122;

			Assert::IsTrue(a <= b);
		}

		// Test <= function
		TEST_METHOD(TestSmallThanFunc3)
		{
			Int a = 122;

			int b = 500;

			Assert::IsTrue(a < b);
		}

		// Test <= function
		TEST_METHOD(TestSmallThanFunc4)
		{
			Int a = 122;

			Int b = 500;

			Assert::IsTrue(a < b);
		}

		// Test Parse function
		TEST_METHOD(TestParseFunc1)
		{
			Int a = Int::Parse(_T("890"));

			Assert::IsTrue(a == 890);
		}

		// Test ToString function
		TEST_METHOD(TestToStringFunc1)
		{
			Int a = 908;

			String strValue =a.ToString();

			Assert::IsTrue(strValue == _T("908"));
		}
	};
}
