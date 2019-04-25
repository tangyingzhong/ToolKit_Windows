///************************************************************************
/// <copyrigth>2018-2019 Corporation.All Rights Reserved</copyrigth>
/// <author>tangyingzhong</author>
/// <contact>tangyz114987@outlook.com</contact>
/// <version>V1.0.0</version>
/// <describe>
/// Test String class 
///</describe>
/// <date>2019/4/18</date>
///***********************************************************************

#include "StdAfx.h"
#include <CppUnitTest.h>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace System::BasicType;

namespace ToolUnitTest
{
	TEST_CLASS(StringTest)
	{
	public:
		// Init the class
		TEST_CLASS_INITIALIZE(InitString)
		{

		}

		// Clean up the class
		TEST_CLASS_CLEANUP(CleanString)
		{

		}

		// Test spliting string
		TEST_METHOD(TestSplit1)
		{
			m_TestString = _T("Hi,You are great,We are going to have a nice trip,hahah");

			vector<String> vNewStringTable;
			Assert::IsTrue(m_TestString.Split(_T(","), vNewStringTable));
		}

		// Test spliting string
		TEST_METHOD(TestSplit2)
		{
			m_TestString = _T("Hi,You are great,We are going to have a nice trip,hahah");

			vector<String> vNewStringTable;
			Assert::IsTrue(m_TestString.Split(_T("t"), vNewStringTable));
		}

		// Test spliting string
		TEST_METHOD(TestSplit3)
		{
			m_TestString = _T("Hi,You are great,We are going to have a nice trip,hahah");

			vector<String> vNewStringTable;
			Assert::IsFalse(m_TestString.Split(_T(""), vNewStringTable));
		}

		// Test Substring function
		TEST_METHOD(TestSubString1)
		{
			m_TestString = _T("Hi,You are great,We are going to have a nice trip,hahah");

			String strResult = m_TestString.SubString(-1, 123);

			bool ret = false;

			if (strResult == String(_T("")))
			{
				ret = true;
			}


			Assert::IsTrue(ret == true);
		}

		// Test Substring function
		TEST_METHOD(TestSubString2)
		{
			m_TestString = _T("Hi,You are great,We are going to have a nice trip,hahah");

			String strResult = m_TestString.SubString(0, 5200);

			bool ret = false;

			if (strResult == String(_T("")))
			{
				ret = true;
			}


			Assert::IsTrue(ret == true);
		}

		// Test Substring function
		TEST_METHOD(TestSubString3)
		{
			m_TestString = _T("Hi,You are great,We are going to have a nice trip,hahah");

			String strResult = m_TestString.SubString(32, m_TestString.GetLength() - 1);

			bool ret = false;

			if (strResult == String(_T("")))
			{
				ret = true;
			}


			Assert::IsTrue(ret != true);
		}

		// Test Substring function
		TEST_METHOD(TestSubString4)
		{
			m_TestString = _T("Hi,You are great,We are going to have a nice trip,hahah");

			String strResult = m_TestString.SubString(m_TestString.GetLength(), m_TestString.GetLength());

			bool ret = false;

			if (strResult == String(_T("")))
			{
				ret = true;
			}


			Assert::IsTrue(ret == true);
		}

		// Test Substring function
		TEST_METHOD(TestSubString5)
		{
			m_TestString = _T("Hi,You are great,We are going to have a nice trip,hahah");

			String strResult = m_TestString.SubString(13, m_TestString.GetLength());

			bool ret = false;

			if (strResult == String(_T("")))
			{
				ret = true;
			}


			Assert::IsTrue(ret != true);
		}

		// Test Substring function
		TEST_METHOD(TestSubString6)
		{
			m_TestString = _T("Hi,You are great,We are going to have a nice trip,hahah");

			String strResult = m_TestString.SubString(13, 0);

			bool ret = false;

			if (strResult == String(_T("")))
			{
				ret = true;
			}


			Assert::IsTrue(ret == true);
		}

		// Test Substring function
		TEST_METHOD(TestSubString7)
		{
			m_TestString = _T("Hi,You are great,We are going to have a nice trip,hahah");

			String strResult = m_TestString.SubString(13, -1);

			bool ret = false;

			if (strResult == String(_T("")))
			{
				ret = true;
			}


			Assert::IsTrue(ret == true);
		}

		// Test Substring function
		TEST_METHOD(TestSubString8)
		{
			m_TestString = _T("Hi,You are great,We are going to have a nice trip,hahah");

			String strResult = m_TestString.SubString(0, m_TestString.GetLength() + 12);

			bool ret = false;

			if (strResult == String(_T("")))
			{
				ret = true;
			}


			Assert::IsTrue(ret == true);
		}

	private:
		// Test String
		String m_TestString;
	};
}
