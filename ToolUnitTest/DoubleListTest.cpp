///************************************************************************
/// <copyrigth>2018-2019 Corporation.All Rights Reserved</copyrigth>
/// <author>tangyingzhong</author>
/// <contact>tangyz114987@outlook.com</contact>
/// <version>V1.0.0</version>
/// <describe>
/// Test double list class 
///</describe>
/// <date>2019/4/18</date>
///***********************************************************************

#include "StdAfx.h"
#include <CppUnitTest.h>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace System::BasicType;


namespace DoubleList_UnitTest
{
	TEST_CLASS(DoubleListTest)
	{
	public:
		// Test add function
		TEST_METHOD(TestAddFunc)
		{
			DoubleList<MyData> dList;

			for (Int index=0;index<5;++index)
			{
				MyData data;

				String strIndex = String("复活节") + index.ToString();

				CreateMyData(90, false, strIndex, data);

				dList.Add(data);
			}

			for (Int index = 0; index < 5; ++index)
			{
				MyData data;

				if (!dList.Get(index, data))
				{
					Assert::Fail(String(_T("No element")).ToUnicodeData().c_str());
				}

				String strIndex = String("复活节") + index.ToString();

				String strName = data.strName;

				Assert::IsTrue(strName == strIndex);
			}
		}

		// Test remove function
		TEST_METHOD(TestRemoveFunc)
		{
			DoubleList<MyData> dList;

			for (Int index = 0; index < 5; ++index)
			{
				MyData data;

				String strIndex = String("复活节") + index.ToString();

				CreateMyData(90, false, strIndex, data);

				dList.Add(data);
			}

			if (!dList.Remove(3))
			{
				Assert::Fail(String(_T("No element")).ToUnicodeData().c_str());
			}

			if (dList.Size() != 4)
			{
				Assert::Fail(String(_T("Size != 4")).ToUnicodeData().c_str());
			}

			for (Int index = 0; index < 4; ++index)
			{
				MyData data;

				if (!dList.Get(index, data))
				{
					Assert::Fail(String(_T("No element")).ToUnicodeData().c_str());
				}

				if (index == 3)
				{
					String strIndex = String("复活节") + (++index).ToString();

					String strName = data.strName;

					Assert::IsTrue(strName == strIndex);
				}
				else
				{
					String strIndex = String("复活节") + index.ToString();

					String strName = data.strName;

					Assert::IsTrue(strName == strIndex);
				}
			}
		}

		// Test add function
		TEST_METHOD(TestAssignConstructorFunc)
		{
			DoubleList<MyData> dList;

			for (Int index = 0; index < 5; ++index)
			{
				MyData data;

				String strIndex = String("复活节") + index.ToString();

				CreateMyData(90, false, strIndex, data);

				dList.Add(data);
			}

			DoubleList<MyData> dList2;

			dList2 = dList;

			Assert::IsTrue(dList2.Size() == 5);

			for (Int index = 0; index < 5; ++index)
			{
				MyData data;

				if (!dList2.Get(index, data))
				{
					Assert::Fail(String(_T("No element")).ToUnicodeData().c_str());
				}

				String strIndex = String("复活节") + index.ToString();

				String strName = data.strName;

				Assert::IsTrue(strName == strIndex);
			}
		}

	private:
		struct MyData
		{
			String strName;

			Int iData;

			Bool bValue;
		};

		MyData m_MyData;

		// Create my data
		None CreateMyData(int iData,
			bool bValue,
			String strName, 
			MyData& data)
		{
			data.iData = iData;

			data.strName = strName;
				
			data.bValue = bValue;
		}
	};
}
