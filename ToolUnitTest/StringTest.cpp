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

	private:
		// Test String
		String m_TestString;
	};
}
