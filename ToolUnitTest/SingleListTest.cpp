///************************************************************************
/// <copyrigth>2018-2019 Corporation.All Rights Reserved</copyrigth>
/// <author>tangyingzhong</author>
/// <contact>tangyz114987@outlook.com</contact>
/// <version>V1.0.0</version>
/// <describe>
/// Test Single list class 
///</describe>
/// <date>2019/4/18</date>
///***********************************************************************

#include "StdAfx.h"
#include <CppUnitTest.h>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace System::BasicType;


namespace SingleList_UnitTest
{
	TEST_CLASS(SingleListTest)
	{
	public:
		// Test add function
		TEST_METHOD(TestAddFunc)
		{
			SingleList<MyData> dList;

			for (Int index = 0; index < 5; ++index)
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
					Assert::Fail(_T("No element"));
				}

				String strIndex = String("复活节") + index.ToString();

				String strName = data.strName;

				Assert::IsTrue(strName == strIndex);
			}
		}

		// Test remove function
		TEST_METHOD(TestRemoveFunc)
		{
			SingleList<MyData> dList;

			for (Int index = 0; index < 5; ++index)
			{
				MyData data;

				String strIndex = String("复活节") + index.ToString();

				CreateMyData(90, false, strIndex, data);

				dList.Add(data);
			}

			if (!dList.Remove(3))
			{
				Assert::Fail(_T("No element"));
			}

			if (dList.Size() != 4)
			{
				Assert::Fail(_T("Size is not 4"));
			}

			for (Int index = 0; index < 4; ++index)
			{
				MyData data;

				if (!dList.Get(index, data))
				{
					Assert::Fail(_T("No element"));
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
			SingleList<MyData> dList;

			for (Int index = 0; index < 5; ++index)
			{
				MyData data;

				String strIndex = String("复活节") + index.ToString();

				CreateMyData(90, false, strIndex, data);

				dList.Add(data);
			}

			SingleList<MyData> dList2;

			dList2 = dList;

			Assert::IsTrue(dList2.Size() == 5);

			for (Int index = 0; index < 5; ++index)
			{
				MyData data;

				if (!dList2.Get(index, data))
				{
					Assert::Fail(_T("No element"));
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
			MyData & data)
		{
			data.iData = iData;

			data.strName = strName;

			data.bValue = bValue;
		}
	};
}
