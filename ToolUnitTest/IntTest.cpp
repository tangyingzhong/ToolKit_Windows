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

namespace Int_UnitTest
{
	TEST_CLASS(IntTest)
	{
	public:
		// Test operator int() const
		TEST_METHOD(TestMethod_operator_int)
		{
			Int a = 88;

			int b = 66;

			std::cout << a << "-" << b << std::endl;
		}

		// Test == function
		TEST_METHOD(TestMethod_operator_Equal)
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
		TEST_METHOD(TestMethod_operator_Equal2)
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
		TEST_METHOD(TestMethod_operator_NotEqaul)
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
		TEST_METHOD(TestMethod_operator_NotEqaul2)
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
		TEST_METHOD(TestMethod_operator_Add)
		{
			Int a = 90;

			int b = 22;

			Int c = a + b;

			Assert::IsTrue(c == 112);
		}

		// Test + function
		TEST_METHOD(TestMethod_operator_Add2)
		{
			Int a = 90;

			Int b = 22;

			Int c = a + b;

			Assert::IsTrue(c == 112);
		}

		// Test + function
		TEST_METHOD(TestMethod_operator_Add3)
		{
			Int a = 90.45;

			Int b = 22;

			Int c = a + b;

			Assert::IsTrue(c == 112);
		}

		// Test - function
		TEST_METHOD(TestMethod_operator_Sub)
		{
			Int a = 90.45;

			int b = 50;

			Int c = a - b;

			Assert::IsTrue(c == 40);
		}

		// Test - function
		TEST_METHOD(TestMethod_operator_Sub2)
		{
			Int a = 90.45;

			int b = 50;

			Int c = b - a;

			Assert::IsTrue(c == -40);
		}


		// Test * function
		TEST_METHOD(TestMethod_operator_Sub3)
		{
			Int a = 20;

			int b = 50;

			Int c = a*b;

			Assert::IsTrue(c == 1000);
		}

		// Test * function
		TEST_METHOD(TestMethod_operator_Mul)
		{
			Int a = 20;

			int b = 50;

			Int c = b*a;

			Assert::IsTrue(c == 1000);
		}

		// Test / function
		TEST_METHOD(TestMethod_operator_Divide)
		{
			Int a = 100;

			int b = 50;

			Int c = a / b;

			Assert::IsTrue(c == 2);
		}

		// Test / function
		TEST_METHOD(TestMethod_operator_Divide2)
		{
			Int a = 2;

			int b = 100;

			Int c = b / a;

			Assert::IsTrue(c == 50);
		}

		// Test / function
		TEST_METHOD(TestMethod_operator_Divide3)
		{
			Int a = -30;

			int b = -90;

			Int c = b / a;

			Assert::IsTrue(c == 3);
		}

		// Test / function
		TEST_METHOD(TestMethod_operator_Divide4)
		{
			Int a = 450;

			int b = 0;

			Int c = a / b;

			Assert::IsTrue(c == -1);
		}

		// Test % function
		TEST_METHOD(TestMethod_operator_SeFunc1)
		{
			Int a = 450;

			int b = 50;

			Int c = a % b;

			Assert::IsTrue(c == 0);
		}

		// Test % function
		TEST_METHOD(TestMethod_operator_SeFunc2)
		{
			Int a = 450;

			int b = 7;

			Int c = a % b;

			Assert::IsTrue(c == 2);
		}

		// Test << function
		TEST_METHOD(TestMethod_operator_LeftFunc1)
		{
			Int a = 2;

			Int c = a << 2;

			Assert::IsTrue(c == 8);
		}
	
		// Test << function
		TEST_METHOD(TestMethod_operator_LeftFunc2)
		{
			Int a = -2;

			Int c = a << 2;

			Assert::IsTrue(c == -8);
		}

		// Test << function
		TEST_METHOD(TestMethod_operator_LeftFunc3)
		{
			Int a = 2;

			Int c = a << -2;

			Assert::IsTrue(c != -8);
		}

		// Test >> function
		TEST_METHOD(TestMethod_operator_RightFunc)
		{
			Int a = 2;

			Int c = a >> -2;

			Assert::IsTrue(c != -8);
		}

		// Test >> function
		TEST_METHOD(TestMethod_operator_RightFunc1)
		{
			Int a = 2;

			Int c = a >> 2;

			Assert::IsTrue(c != -8);
		}

		// Test >> function
		TEST_METHOD(TestMethod_operator_RightFunc2)
		{
			Int a = 4;

			Int c = a >> 2;

			Assert::IsTrue(c == 1);
		}

		// Test ! function
		TEST_METHOD(TestMethod_operator_ReverseFunc)
		{
			Int a = 2;

			Int c = !a;

			Assert::IsTrue(c == 0);
		}

		// Test ! function
		TEST_METHOD(TestMethod_operator_ReverseFunc1)
		{
			Int a = 200;

			Int c = !a;

			Assert::IsTrue(c == 0);
		}

		// Test ! function
		TEST_METHOD(TestMethod_operator_ReverseFunc2)
		{
			Int a = 0;

			Int c = !a;

			Assert::IsTrue(c == 1);
		}

		// Test ++ function
		TEST_METHOD(TestMethod_operator_AddPlus)
		{
			Int a = 2;

			a++;

			Assert::IsTrue(a == 3);
		}

		// Test ++ function
		TEST_METHOD(TestMethod_operator_AddPlus2)
		{
			Int a = 2;

			++a;

			Assert::IsTrue(a == 3);
		}

		// Test ++ function
		TEST_METHOD(TestMethod_operator_AddPlus3)
		{
			Int a = 2;

			Assert::IsFalse(a++ == 3);

			Assert::IsTrue(a == 3);
		}

		// Test ++ function
		TEST_METHOD(TestMethod_operator_AddPlus4)
		{
			Int a = 2;

			Assert::IsTrue(++a == 3);
		}

		// Test > function
		TEST_METHOD(TestMethod_operator_Bigger)
		{
			Int a = 2;

			Int b = 32;

			Assert::IsTrue(b > a);
		}

		// Test > function
		TEST_METHOD(TestMethod_operator_Bigger1)
		{
			Int a = 2;

			int b = 32;

			Assert::IsTrue(b > a);
		}

		// Test >= function
		TEST_METHOD(TestMethod_operator_Bigger2)
		{
			Int a = 122;

			Int b = 122;

			Assert::IsTrue(a >= b);
		}

		// Test >= function
		TEST_METHOD(TestMethod_operator_Bigger3)
		{
			Int a = 122;

			int b = 122;

			Assert::IsTrue(a >= b);
		}

		// Test <= function
		TEST_METHOD(TestMethod_operator_SmallThanFunc1)
		{
			Int a = 12;

			int b = 122;

			Assert::IsTrue(a <= b);
		}

		// Test <= function
		TEST_METHOD(TestMethod_operator_SmallThanFunc2)
		{
			Int a = 122;

			int b = 122;

			Assert::IsTrue(a <= b);
		}

		// Test <= function
		TEST_METHOD(TestMethod_operator_SmallThanFunc3)
		{
			Int a = 122;

			int b = 500;

			Assert::IsTrue(a < b);
		}

		// Test <= function
		TEST_METHOD(TestMethod_operator_SmallThanFunc4)
		{
			Int a = 122;

			Int b = 500;

			Assert::IsTrue(a < b);
		}

		// Test Parse function
		TEST_METHOD(TestMethod_operator_ParseFunc)
		{
			Int a = Int::Parse(_T("890"));

			Assert::IsTrue(a == 890);
		}

		// Test ToString function
		TEST_METHOD(TestMethod_operator_ToStringFunc)
		{
			Int a = 908;

			String strValue =a.ToString();

			Assert::IsTrue(strValue == _T("908"));
		}
	};
}
