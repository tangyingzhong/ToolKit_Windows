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

			if (strResult == _T(""))
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

			if (strResult == _T(""))
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

			if (strResult == _T(""))
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

			if (strResult == _T(""))
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

			if (strResult == _T(""))
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

			if (strResult == _T(""))
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

			if (strResult == _T(""))
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

			if (strResult == _T(""))
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

			if (strResult ==_T(""))
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

			String strOld = m_TestString;

			m_TestString = m_TestString.Replace(8, 1, _T("T"));

			Assert::IsTrue(m_TestString != strOld);
		}

		// Test Replace function
		TEST_METHOD(TestReplace2)
		{
			m_TestString = _T("Hi,You are great,We are going to have a nice trip,hahah");

			String strOld = m_TestString;

			m_TestString = m_TestString.Replace(-1, 1, _T("T"));

			Assert::IsTrue(m_TestString == strOld);
		}

		// Test Replace function
		TEST_METHOD(TestReplace3)
		{
			m_TestString = _T("Hi,You are great,We are going to have a nice trip,hahah");

			String strOld = m_TestString;

			m_TestString = m_TestString.Replace(0, -1, _T("T"));

			Assert::IsTrue(m_TestString == strOld);
		}

		// Test Replace function
		TEST_METHOD(TestReplace4)
		{
			m_TestString = _T("Hi,You are great,We are going to have a nice trip,hahah");

			String strOld = m_TestString;

			m_TestString = m_TestString.Replace(3, 1, _T("S"));

			Assert::IsTrue(m_TestString != strOld);
		}

		// Test Replace function
		TEST_METHOD(TestReplace5)
		{
			m_TestString = _T("Hi,You are great,We are going to have a nice trip,hahah");

			String strOld = m_TestString;

			m_TestString = m_TestString.Replace(3, 3, _T("We"));

			Assert::IsTrue(m_TestString != strOld);
		}

		// Test Replace function
		TEST_METHOD(TestReplace6)
		{
			m_TestString = _T("Hi,You are great,We are going to have a nice trip,hahah");

			String strOld = m_TestString;

			m_TestString = m_TestString.Replace(m_TestString.GetLength(), 3, _T("We"));

			Assert::IsTrue(m_TestString == strOld);
		}

		// Test Replace function
		TEST_METHOD(TestReplace7)
		{
			m_TestString = _T("Hi,You are great,We are going to have a nice trip,hahah");

			String strOld = m_TestString;

			m_TestString = m_TestString.Replace(1, 0, _T("We"));

			Assert::IsTrue(m_TestString == strOld);
		}

		// Test Replace function
		TEST_METHOD(TestReplace8)
		{
			m_TestString = _T("Hi,You are great,We are going to have a nice trip,hahah");

			String strOld = m_TestString;

			m_TestString = m_TestString.Replace(1, m_TestString.GetLength(), _T("kkk"));

			Assert::IsTrue(m_TestString != strOld);
		}

		// Test Replace function
		TEST_METHOD(TestReplace9)
		{
			m_TestString = _T("Hi,You are great,We are going to have a nice trip,hahah");

			String strOld = m_TestString;

			m_TestString = m_TestString.Replace(1, m_TestString.GetLength() + 10, _T("kkk"));

			Assert::IsTrue(m_TestString != strOld);
		}

		// Test Replace function
		TEST_METHOD(TestReplace10)
		{
			m_TestString = _T("Hi,You are great,We are going to have a nice trip,hahah");

			String strOld = m_TestString;

			m_TestString = m_TestString.Replace(1, m_TestString.GetLength() + 10, _T(""));

			Assert::IsTrue(m_TestString != strOld);
		}

		// Test AllocWideString function
		TEST_METHOD(TestAllocWideString1)
		{
			m_TestString = _T("Hi,You are great,We are going to have a nice trip,hahah");

			wchar_t pWBuffer[60] = {0};
		
			memcpy_s(pWBuffer, sizeof(pWBuffer), m_TestString.AllocWideString(),sizeof(wchar_t)*m_TestString.GetLength());
		}

		// Test Makeupper function
		TEST_METHOD(TestMakeUpper1)
		{
			m_TestString = _T("Hi,You are great,We are going to have a nice trip,hahah");

			m_TestString = m_TestString.MakeUpper();
		}

		// Test MakeLower function
		TEST_METHOD(TestMakeLower)
		{
			m_TestString = _T("OK,YOU ARE RIGHT,I SHOULD DO MY BEST TO HANDLE IT");

			m_TestString = m_TestString.MakeLower();
		}

		// Test [] function
		TEST_METHOD(TestGetCharFunc1)
		{
			m_TestString = _T("OK,YOU ARE RIGHT,I SHOULD DO MY BEST TO HANDLE IT");

			TCHAR ch = m_TestString[3];

			Assert::IsTrue(ch != _T('N'));
		}

		// Test [] function
		TEST_METHOD(TestGetCharFunc2)
		{
			m_TestString = _T("OK,YOU ARE RIGHT,I SHOULD DO MY BEST TO HANDLE IT");

			TCHAR ch = m_TestString[-1];

			Assert::IsTrue(ch == _T('N'));
		}

		// Test [] function
		TEST_METHOD(TestGetCharFunc3)
		{
			m_TestString = _T("OK,YOU ARE RIGHT,I SHOULD DO MY BEST TO HANDLE IT");

			TCHAR ch = m_TestString[m_TestString.GetLength()];

			Assert::IsTrue(ch == _T('N'));
		}

		// Test [] function
		TEST_METHOD(TestGetCharFunc4)
		{
			m_TestString = _T("OK,YOU ARE RIGHT,I SHOULD DO MY BEST TO HANDLE IT");

			TCHAR ch = m_TestString[11.2];

			Assert::IsTrue(ch != _T('N'));
		}

		// Test [] function
		TEST_METHOD(TestGetCharFunc5)
		{
			m_TestString = _T("OK,YOU ARE RIGHT,I SHOULD DO MY BEST TO HANDLE IT");

			TCHAR ch = m_TestString['a'];

			Assert::IsTrue(ch == _T('N'));
		}

		// Test + function
		TEST_METHOD(TestAddFunc1)
		{
			m_TestString = _T("OK,YOU ARE RIGHT,I SHOULD DO MY BEST TO HANDLE IT");

			String strOld = m_TestString;

			m_TestString + _T(" Calm dowm");

			Assert::IsTrue(strOld != m_TestString);
		}

		// Test + function
		TEST_METHOD(TestAddFunc2)
		{
			m_TestString = _T("OK,YOU ARE RIGHT,I SHOULD DO MY BEST TO HANDLE IT");

			String strOld = m_TestString;

			m_TestString + String(_T(" Love you Winnie"));

			Assert::IsTrue(strOld != m_TestString);
		}

		// Test + function
		TEST_METHOD(TestAddFunc3)
		{
			m_TestString = _T("OK,YOU ARE RIGHT,I SHOULD DO MY BEST TO HANDLE IT");

			String strOld = m_TestString;

			m_TestString + std::wstring(_T(" Love you Winnie"));

			Assert::IsTrue(strOld != m_TestString);
		}

		// Test == function
		TEST_METHOD(TestEqualFunc1)
		{
			m_TestString = _T("OK,YOU ARE RIGHT,I SHOULD DO MY BEST TO HANDLE IT");

			bool bRet = false;

			if (m_TestString == _T("OK,YOU ARE RIGHT,I SHOULD DO MY BEST TO HANDLE IT"))
			{
				bRet = true;
			}

			Assert::IsTrue(bRet == true);
		}

		// Test == function
		TEST_METHOD(TestEqualFunc2)
		{
			m_TestString = _T("OK,YOU ARE RIGHT,I SHOULD DO MY BEST TO HANDLE IT");

			bool bRet = false;

			if (m_TestString == String(_T("OK,YOU ARE RIGHT,I SHOULD DO MY BEST TO HANDLE IT")))
			{
				bRet = true;
			}

			Assert::IsTrue(bRet == true);
		}

		// Test == function
		TEST_METHOD(TestEqualFunc3)
		{
			m_TestString = _T("OK,YOU ARE RIGHT,I SHOULD DO MY BEST TO HANDLE IT");

			bool bRet = false;

			if (m_TestString == std::wstring(_T("OK,YOU ARE RIGHT,I SHOULD DO MY BEST TO HANDLE IT")))
			{
				bRet = true;
			}

			Assert::IsTrue(bRet == true);
		}

		// Test != function
		TEST_METHOD(TestNotEqualFunc1)
		{
			m_TestString = _T("OK,YOU ARE RIGHT,I SHOULD DO MY BEST TO HANDLE IT");

			bool bRet = false;

			if (m_TestString != std::wstring(_T("OK")))
			{
				bRet = true;
			}

			Assert::IsTrue(bRet == true);
		}

		// Test != function
		TEST_METHOD(TestNotEqualFunc2)
		{
			m_TestString = _T("OK,YOU ARE RIGHT,I SHOULD DO MY BEST TO HANDLE IT");

			bool bRet = false;

			if (m_TestString != String(_T("OK")))
			{
				bRet = true;
			}

			Assert::IsTrue(bRet == true);
		}

		// Test != function
		TEST_METHOD(TestNotEqualFunc3)
		{
			m_TestString = _T("OK,YOU ARE RIGHT,I SHOULD DO MY BEST TO HANDLE IT");

			bool bRet = false;

			if (m_TestString != _T("OK"))
			{
				bRet = true;
			}

			Assert::IsTrue(bRet == true);
		}

		// Test parse function
		TEST_METHOD(TestParseFunc1)
		{
			m_TestString = _T("452");

			int iResult = String::Parse<int>(m_TestString);

			Assert::IsTrue(iResult == 452);
		}

		// Test parse function
		TEST_METHOD(TestParseFunc2)
		{
			m_TestString = _T("452.415");

			float fResult = String::Parse<float>(m_TestString);

			Assert::IsTrue(fResult >= 452.415f);
		}

		// Test parse function
		TEST_METHOD(TestParseFunc3)
		{
			m_TestString = _T("452.415");

			double dResult = String::Parse<double>(m_TestString);

			Assert::IsTrue(dResult >= 452.415l);
		}

		// Test parse function
		TEST_METHOD(TestParseFunc4)
		{
			m_TestString = _T("-90");

			int iResult = String::Parse<int>(m_TestString);

			Assert::IsTrue(iResult == -90);
		}

		// Test parse function
		TEST_METHOD(TestParseFunc5)
		{
			m_TestString = _T("-90.67");

			float fResult = String::Parse<float>(m_TestString);

			Assert::IsTrue(fResult >= -90.67f);
		}

		// Test tostring function
		TEST_METHOD(TestToString1)
		{
			int iTest = 999;

			String strTest = String::ToString(iTest);

			Assert::IsTrue(strTest == _T("999"));
		}

		// Test tostring function
		TEST_METHOD(TestToString2)
		{
			int iTest = -999;

			String strTest = String::ToString(iTest);

			Assert::IsTrue(strTest == _T("-999"));
		}

		// Test tostring function
		TEST_METHOD(TestToString3)
		{
			float iTest = -999.8888f;

			String strTest = String::ToString(iTest);

			Assert::IsTrue(strTest != _T("-999.8888"));
		}

		// Test tostring function
		TEST_METHOD(TestToString4)
		{
			float iTest = 999.8888f;

			String strTest = String::ToString(iTest);

			Assert::IsTrue(strTest != _T("999.8888"));
		}

		// Test tostring function
		TEST_METHOD(TestToString5)
		{
			double iTest = 999.8888l;

			String strTest = String::ToString(iTest);

			Assert::IsTrue(strTest != _T("999.8888"));
		}

		// Test tostring function
		TEST_METHOD(TestToString6)
		{
			double iTest = -999.8888l;

			String strTest = String::ToString(iTest);

			Assert::IsTrue(strTest != _T("-999.8888"));
		}

	private:
		// Test String
		String m_TestString;
	};
}
