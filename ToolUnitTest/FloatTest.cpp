///************************************************************************
/// <copyrigth>2018-2019 Corporation.All Rights Reserved</copyrigth>
/// <author>tangyingzhong</author>
/// <contact>tangyz114987@outlook.com</contact>
/// <version>V1.0.0</version>
/// <describe>
/// Test Float class 
///</describe>
/// <date>2019/4/18</date>
///***********************************************************************

#include "StdAfx.h"
#include <CppUnitTest.h>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace System::BasicType;

namespace Float_UnitTest
{
	TEST_CLASS(FloatTest)
	{
	public:
		// Test operator Float() const
		TEST_METHOD(TestMethod_operator_Float)
		{
			Float a = 88.76f;

			Float b = 66.89f;

			std::cout << a << "-" << b << std::endl;
		}

		// Test + function
		TEST_METHOD(TestMethod_operator_Add)
		{
			Float a = 90.66f;

			Float b = 22.12f;

			Float c = a + b;

			if (c - 112.78f <= 0.00000001f)
			{
				Assert::IsTrue(true);
			}

			Assert::IsFalse(false);
		}

		// Test += function
		TEST_METHOD(TestMethod_operator_Add2)
		{
			Float a = 90.66f;

			Float b = 22.12f;

			a += b;

			if (a - 112.78f <= 0.00000001f)
			{
				Assert::IsTrue(true);
			}

			Assert::IsFalse(false);
		}

		// Test - function
		TEST_METHOD(TestMethod_operator_Sub)
		{
			Float a = 90.45f;

			Float b = 50.1f;

			Float c = a - b;

			if (c - 40.35f <= 0.00000001f)
			{
				Assert::IsTrue(true);
			}

			Assert::IsFalse(false);
		}

		// Test -= function
		TEST_METHOD(TestMethod_operator_Sub2)
		{
			Float a = 90.45f;

			Float b = 50.1f;

			a -= b;

			if (a - 40.35f <= 0.00000001f)
			{
				Assert::IsTrue(true);
			}

			Assert::IsFalse(false);
		}


		// Test * function
		TEST_METHOD(TestMethod_operator_Sub3)
		{
			Float a = 20.0f;

			Float b = 50.0f;

			Float c = a * b;

			if (c - 1000.0f <= 0.00000001f)
			{
				Assert::IsTrue(true);
			}

			Assert::IsFalse(false);
		}

		// Test * function
		TEST_METHOD(TestMethod_operator_Mul)
		{
			Float a = 20.0f;

			Float b = 50.0f;

			Float c = a * b;

			if (c - 1000.0f <= 0.00000001f)
			{
				Assert::IsTrue(true);
			}

			Assert::IsFalse(false);
		}

		// Test / function
		TEST_METHOD(TestMethod_operator_Divide)
		{
			Float a = 100.0f;

			Float b = 50.0f;

			Float c = a / b;

			if (c - 20.0f <= 0.00000001f)
			{
				Assert::IsTrue(true);
			}

			Assert::IsFalse(false);
		}

		// Test / function
		TEST_METHOD(TestMethod_operator_Divide2)
		{
			Float a = 100.0f;

			Float b = 50.0f;

			Float c = a / b;

			if (c - 20.0f <= 0.00000001f)
			{
				Assert::IsTrue(true);
			}

			Assert::IsFalse(false);
		}

		// Test / function
		TEST_METHOD(TestMethod_operator_Divide3)
		{
			Float a = -90.0;

			Float b = -3.0f;

			Float c = a / b;

			if (c - 30.0f <= 0.00000001f)
			{
				Assert::IsTrue(true);
			}

			Assert::IsFalse(false);
		}

		// Test / function
		TEST_METHOD(TestMethod_operator_Divide4)
		{
			Float a = 450.0f;

			Float b = 3.0f;

			Float c = a / b;

			if (c - 150.0f <= 0.00000001f)
			{
				Assert::IsTrue(true);
			}

			Assert::IsFalse(false);
		}

		// Test Parse function
		TEST_METHOD(TestMethod_operator_ParseFunc)
		{
			Float a = Float::Parse(_T("890.88"));

			if (a - 890.88f <= 0.00000001f)
			{
				Assert::IsTrue(true);
			}

			Assert::IsFalse(false);
		}

		// Test Parse function
		TEST_METHOD(TestMethod_operator_ParseFunc2)
		{
			Float a = Float::Parse(_T("true"));

			if (a - 1.0f <= 0.00000001f)
			{
				Assert::IsTrue(true);
			}

			Assert::IsFalse(false);
		}

		// Test ToString function
		TEST_METHOD(TestMethod_operator_ToStringFunc)
		{
			Float a = 908.99f;

			String strValue = a.ToString();

			Assert::IsTrue(strValue == _T("908.99"));
		}
	};
}
