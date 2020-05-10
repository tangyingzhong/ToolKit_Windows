///************************************************************************
/// <copyrigth>2018-2019 Corporation.All Rights Reserved</copyrigth>
/// <author>tangyingzhong</author>
/// <contact>tangyz114987@outlook.com</contact>
/// <version>V1.0.0</version>
/// <describe>
/// Test Double class 
///</describe>
/// <date>2019/4/18</date>
///***********************************************************************

#include "StdAfx.h"
#include <CppUnitTest.h>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace System::BasicType;

namespace Double_UnitTest
{
	TEST_CLASS(DoubleTest)
	{
	public:
		// Test operator Double() const
		TEST_METHOD(TestMethod_operator_Double)
		{
			Double a = 88.76;

			double b = 66.89;

			std::cout << a << "-" << b << std::endl;
		}

		// Test + function
		TEST_METHOD(TestMethod_operator_Add)
		{
			Double a = 90.66;

			Double b = 22.12;

			double c = a + b;

			if (c - 112.78 <= 0.00000001)
			{
				Assert::IsTrue(true);
			}

			Assert::IsFalse(false);
		}

		// Test += function
		TEST_METHOD(TestMethod_operator_Add2)
		{
			Double a = 90.66;

			Double b = 22.12;

			a += b;

			if (a - 112.78 <= 0.00000001)
			{
				Assert::IsTrue(true);
			}

			Assert::IsFalse(false);
		}

		// Test - function
		TEST_METHOD(TestMethod_operator_Sub)
		{
			Double a = 90.45;

			Double b = 50.1;

			Double c = a - b;

			if (c - 40.35 <= 0.00000001)
			{
				Assert::IsTrue(true);
			}

			Assert::IsFalse(false);
		}

		// Test -= function
		TEST_METHOD(TestMethod_operator_Sub2)
		{
			Double a = 90.45;

			double b = 50.1;

			a -= b;

			if (a - 40.35 <= 0.00000001)
			{
				Assert::IsTrue(true);
			}

			Assert::IsFalse(false);
		}


		// Test * function
		TEST_METHOD(TestMethod_operator_Sub3)
		{
			Double a = 20;

			Double b = 50;

			Double c = a * b;

			if (c - 1000.0 <= 0.00000001)
			{
				Assert::IsTrue(true);
			}

			Assert::IsFalse(false);
		}

		// Test * function
		TEST_METHOD(TestMethod_operator_Mul)
		{
			Double a = 20;

			double b = 50;

			Double c = a * b;

			if (c - 1000.0 <= 0.00000001)
			{
				Assert::IsTrue(true);
			}

			Assert::IsFalse(false);
		}

		// Test / function
		TEST_METHOD(TestMethod_operator_Divide)
		{
			Double a = 100;

			Double b = 50;

			Double c = a / b;

			if (c - 20.0 <= 0.00000001)
			{
				Assert::IsTrue(true);
			}

			Assert::IsFalse(false);
		}

		// Test / function
		TEST_METHOD(TestMethod_operator_Divide2)
		{
			Double a = 100;

			double b = 50;

			Double c = a / b;

			if (c - 20.0 <= 0.00000001)
			{
				Assert::IsTrue(true);
			}

			Assert::IsFalse(false);
		}

		// Test / function
		TEST_METHOD(TestMethod_operator_Divide3)
		{
			Double a = -90.0;

			Double b = -3;

			Double c = a / b;

			if (c - 30.0 <= 0.00000001)
			{
				Assert::IsTrue(true);
			}

			Assert::IsFalse(false);
		}

		// Test / function
		TEST_METHOD(TestMethod_operator_Divide4)
		{
			double a = 450;

			Double b = 3;

			Double c = a / b;

			if (c - 150.0 <= 0.00000001)
			{
				Assert::IsTrue(true);
			}

			Assert::IsFalse(false);
		}

		// Test Parse function
		TEST_METHOD(TestMethod_operator_ParseFunc)
		{
			Double a = Double::Parse(_T("890.88"));

			if (a - 890.88 <= 0.00000001)
			{
				Assert::IsTrue(true);
			}

			Assert::IsFalse(false);
		}

		// Test Parse function
		TEST_METHOD(TestMethod_operator_ParseFunc2)
		{
			Double a = Double::Parse(_T("true"));

			if (a - 1.0 <= 0.00000001)
			{
				Assert::IsTrue(true);
			}

			Assert::IsFalse(false);
		}

		// Test ToString function
		TEST_METHOD(TestMethod_operator_ToStringFunc)
		{
			Double a = 908.99;

			String strValue = a.ToString();

			Assert::IsTrue(strValue == _T("908.99"));
		}
	};
}
