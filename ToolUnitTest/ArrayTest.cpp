///************************************************************************
/// <copyrigth>2018-2019 Corporation.All Rights Reserved</copyrigth>
/// <author>tangyingzhong</author>
/// <contact>tangyz114987@outlook.com</contact>
/// <version>V1.0.0</version>
/// <describe>
/// Test Array class 
///</describe>
/// <date>2019/4/18</date>
///***********************************************************************

#include "StdAfx.h"
#include <CppUnitTest.h>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace System::BasicType;

namespace Array_UnitTest
{
	TEST_CLASS(ArrayTest)
	{
	public:
		// Test [] function
		TEST_METHOD(TestGetCharFunc1)
		{
			Array<Int> TestArray(5);

			int iSize = TestArray.Size();

			for (Int index = 0; index < iSize; ++index)
			{
				TestArray[index] = index;
			}

			for (Int index = 0; index < iSize; ++index)
			{
				Int iValue = TestArray[index];

				Assert::IsTrue(iValue == index);
			}
		}

		// Test [] function
		TEST_METHOD(TestGetCharFunc2)
		{
			Array<Int> TestArray(5);

			int iSize = TestArray.Size();

			for (Int index = 0; index < iSize; ++index)
			{
				TestArray[index] = index;
			}

			Int iValue = TestArray[-1];

			Assert::IsTrue(iValue == 0);
		}

		// Test [] function
		TEST_METHOD(TestGetCharFunc3)
		{
			Array<Int> TestArray(5);

			int iSize = TestArray.Size();

			for (Int index = 0; index < iSize; ++index)
			{
				TestArray[index] = index;
			}

			Int iValue = TestArray[9];

			Assert::IsTrue(iValue == 0);
		}

		// Test [] function
		TEST_METHOD(TestGetCharFunc4)
		{
			Array<Int> TestArray(5);

			Int iValue = TestArray[1];

			Assert::IsTrue(iValue == 0);
		}

		// Test resize function
		TEST_METHOD(TestResizeFunc1)
		{
			Array<Int> TestArray(5);

			TestArray.Resize(10);

			Int iSize = TestArray.Size();

			Assert::IsTrue(iSize == 10);
		}

		// Test resize function
		TEST_METHOD(TestResizeFunc2)
		{
			Array<Int> TestArray(5);

			for (Int index = 0; index < TestArray.Size(); ++index)
			{
				TestArray[index] = index;
			}

			TestArray.Resize(10);

			for (Int index = 5; index < TestArray.Size(); ++index)
			{
				TestArray[index] = 8*index;
			}

			for (Int index = 0; index < TestArray.Size(); ++index)
			{
				Int iValue = TestArray[index];

				if (index < 5)
				{
					Assert::IsTrue(iValue == index);
				}

				if (index == 5)
				{
					Assert::IsTrue(iValue == 40);
				}
			}	
		}

		// Test + function
		TEST_METHOD(TestAddFunc1)
		{
			Array<Int> TestArray(5);

			for (Int index = 0; index < TestArray.Size(); ++index)
			{
				TestArray[index] = index;
			}

			Int iValue = *(TestArray + 2);

			Assert::IsTrue(iValue == 2);
		}

		// Test *(p+1) function
		TEST_METHOD(TestAddFunc2)
		{
			Array<Int> TestArray(5);

			for (Int index = 0; index < TestArray.Size(); ++index)
			{
				TestArray[index] = index;
			}

			Int iData = *(TestArray + 2);

			Assert::IsTrue(iData == 2);
		}

		// Test Clear function
		TEST_METHOD(TestClearFunc1)
		{
			Array<Int> TestArray(5);

			for (Int index = 0; index < TestArray.Size(); ++index)
			{
				TestArray[index] = index;
			}

			for (Int index = 0; index < TestArray.Size(); ++index)
			{
				Int iValue0 = TestArray[index];

				Assert::IsTrue(iValue0 == index);
			}

			TestArray.Clear();

			for (Int index = 0; index < TestArray.Size(); ++index)
			{
				Int iValue = TestArray[index];

				Assert::IsTrue(iValue == 0);
			}
		}

		// Test copy function
		TEST_METHOD(TestCopyFunc1)
		{
			String strData1 = "Fuck you";
			
			Character Buffer[1024] = {0};

			Array<Character>::Copy((Character*)strData1.CStr(), strData1.GetLength(), Buffer,1024);

			Assert::IsTrue(strData1 == String(Buffer));
		}

		// Test copy function
		TEST_METHOD(TestCopyFunc2)
		{
			String strData = "我不知道设是否";

			Array<SByte> Data1(strData.ToANSIData().length()+1);

			memcpy_s(Data1.Data(), 
				Data1.Size(), 
				strData.ToANSIData().c_str(), 
				strData.ToANSIData().length() + 1);
			
			Array<SByte> Data2(strData.ToANSIData().length() +1);

			Array<SByte>::Copy(Data1, Data2);

			String strFinalData = Data2.Data();

			Assert::IsTrue(strFinalData == strData);

			Array<SByte>::Clear(Data2,0, Data2.Size());

			strFinalData = Data2.Data();

			Assert::IsTrue(strFinalData.IsEmpty());
		}
	};
}
