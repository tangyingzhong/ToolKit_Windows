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

			String strResult = m_TestString.SubString(54, - 1);

			bool ret = false;

			if (strResult == String(_T("")))
			{
				ret = true;
			}


			Assert::IsTrue(ret == true);
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


			Assert::IsTrue(ret == true);
		}

		// Test Substring function
		TEST_METHOD(TestSubString6)
		{
			m_TestString = _T("Hi,You are great,We are going to have a nice trip,hahah");

			String strResult = m_TestString.SubString(13, m_TestString.GetLength()-15);

			bool ret = false;

			if (strResult == String(_T("")))
			{
				ret = true;
			}


			Assert::IsTrue(ret != true);
		}

		// Test Substring function
		TEST_METHOD(TestSubString7)
		{
			m_TestString = _T("Hi,You are great,We are going to have a nice trip,hahah");

			String strResult = m_TestString.SubString(13);

			bool ret = false;

			if (strResult == String(_T("")))
			{
				ret = true;
			}


			Assert::IsTrue(ret != true);
		}

		// Test Substring function
		TEST_METHOD(TestSubString8)
		{
			m_TestString = _T("Hi,You are great,We are going to have a nice trip,hahah");

			String strResult = m_TestString.SubString(0);

			bool ret = false;

			if (strResult == String(_T("")))
			{
				ret = true;
			}


			Assert::IsTrue(ret != true);
		}

		// Test Substring function
		TEST_METHOD(TestSubString9)
		{
			m_TestString = _T("Hi,You are great,We are going to have a nice trip,hahah");

			String strResult = m_TestString.SubString(m_TestString.GetLength());

			bool ret = false;

			if (strResult == String(_T("")))
			{
				ret = true;
			}


			Assert::IsTrue(ret == true);
		}

		// Test Find function
		TEST_METHOD(TestFind1)
		{
			m_TestString = _T("Hi,You are great,We are going to have a nice trip,hahah");

			int iPos = m_TestString.Find(_T("r"), 0);

			Assert::IsTrue(iPos != -1);
		}

		// Test Find function
		TEST_METHOD(TestFind2)
		{
			m_TestString = _T("Hi,You are great,We are going to have a nice trip,hahah");

			int iPos = m_TestString.Find(_T(""), 0);

			Assert::IsTrue(iPos == -1);
		}

		// Test Find function
		TEST_METHOD(TestFind3)
		{
			m_TestString = _T("Hi,You are great,We are going to have a nice trip,hahah");

			int iPos = m_TestString.Find(_T("5"), 0);

			Assert::IsTrue(iPos == -1);
		}

		// Test Find function
		TEST_METHOD(TestFind4)
		{
			m_TestString = _T("Hi,You are great,We are going to have a nice trip,hahah");

			int iPos = m_TestString.Find(_T("r"), 9);

			Assert::IsTrue(iPos != -1);
		}

		// Test Find function
		TEST_METHOD(TestFind5)
		{
			m_TestString = _T("Hi,You are great,We are going to have a nice trip,hahah");

			int iPos = m_TestString.Find(_T("r"), m_TestString.GetLength());

			Assert::IsTrue(iPos == -1);
		}

		// Test Find function
		TEST_METHOD(TestFind6)
		{
			m_TestString = _T("Hi,You are great,We are going to have a nice trip,hahah");

			int iPos = m_TestString.Find(_T("r"), -43);

			Assert::IsTrue(iPos == -1);
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

		// Test spliting string
		TEST_METHOD(TestSplit4)
		{
			m_TestString = _T("Hi,You are great,We are going to have a nice trip,hahah");

			vector<String> vNewStringTable;
			Assert::IsFalse(m_TestString.Split(_T("2"), vNewStringTable));
		}

		// Test FindLast function
		TEST_METHOD(TestFindLast1)
		{
			m_TestString = _T("Hi,You are great,We are going to have a nice trip,hahah");

			int iPos = m_TestString.FindLast(_T("r"));

			Assert::IsTrue(iPos != -1);
		}

		// Test FindLast function
		TEST_METHOD(TestFindLast2)
		{
			m_TestString = _T("Hi,You are great,We are going to have a nice trip,hahah");

			int iPos = m_TestString.FindLast(_T("7"));

			Assert::IsTrue(iPos == -1);
		}

		// Test FindLast function
		TEST_METHOD(TestFindLast3)
		{
			m_TestString = _T("Hi,You are great,We are going to have a nice trip,hahah");

			int iPos = m_TestString.FindLast(_T(""));

			Assert::IsTrue(iPos == -1);
		}

		// Test FindLast function
		TEST_METHOD(TestFindLast4)
		{
			m_TestString = _T("Hi,You are great,We are going to have a nice trip,hahah");

			int iPos = m_TestString.FindLast(_T("a"));

			Assert::IsTrue(iPos != -1);
		}

		// Test Replace function
		TEST_METHOD(TestReplace1)
		{
			m_TestString = _T("Hi,You are great,We are going to have a nice trip,hahah");

			m_TestString = m_TestString.Replace(8, 1, _T("T"));

			int iPos = m_TestString.Find(_T("T"), 0);

			bool bRet = false;

			if (m_TestString[8] == _T('T'))
			{
				bRet = true;
			}

			Assert::IsTrue(bRet == true);
		}

	private:
		// Test String
		String m_TestString;
	};
}
