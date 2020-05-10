#include "stdafx.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Directory_UnitTest
{
	TEST_CLASS(DirectoryTest)
	{
	public:
		TEST_METHOD(Test_Create)
		{
			Assert::IsTrue(Directory::Create(_T("D:\\23"), false));

			Assert::IsTrue(Directory::Create(_T("D:\\1\\2\\3"), true));
		}

		TEST_METHOD(Test_Delete)
		{
			Assert::IsTrue(Directory::Delete(_T("D:\\23")));

			Assert::IsTrue(Directory::Delete("D:\\1", true));
		}

		TEST_METHOD(Test_Copy)
		{
			String strSrcDirPath = _T("D:\\SrcTest");

			String strDestDirPath = _T("F:\\FinalTest\\12\\34");

			if (!Directory::Copy(strSrcDirPath, strDestDirPath))
			{
				Assert::Fail(_T("Failed to copy directory!"));
			}
		}

		TEST_METHOD(Test_IsExisted)
		{
			String strPath = _T("D:");

			Assert::IsTrue(Directory::IsExisted(strPath));

			String strPath1 = _T("D:\\");

			Assert::IsTrue(Directory::IsExisted(strPath1));

			String strPath2 = _T("D:\\45");

			Assert::IsFalse(Directory::IsExisted(strPath2));

			String strPath3 = _T("D:\\SrcTest\\2\\3333");

			Assert::IsFalse(Directory::IsExisted(strPath3));
		}

		TEST_METHOD(Test_IsEmpty)
		{
			String strPath0 = _T("D:\\");

			Assert::IsFalse(Directory::IsEmpty(strPath0));

			String strPath = _T("D:\\SrcTest");

			Assert::IsTrue(Directory::IsEmpty(strPath));

			String strPath1 = _T("D:\\SrcTest\\55");

			Assert::IsTrue(Directory::IsEmpty(strPath1));
		}

		TEST_METHOD(Test_IsDir)
		{
			String strPath = _T("D:\\aa.wav");

			Assert::IsFalse(Directory::IsDirectory(strPath));

			String strPath1 = _T("D:\\TangYingZhong");

			Assert::IsTrue(Directory::IsDirectory(strPath1));

			String strPath2 = _T("D:\\");

			Assert::IsTrue(Directory::IsDirectory(strPath2));
		}

		TEST_METHOD(Test_Contains)
		{
			String strDstPath = _T("D:\\XunLeiDownload\\ssh_offline.rar");

			String strRootPath = _T("D:\\");

			Assert::IsTrue(Directory::Contains(strRootPath, strDstPath));

			String strDstPath3 = _T("D:\\XunLeiDownload");

			Assert::IsFalse(Directory::Contains(strRootPath, strDstPath3));

			String strRootPath1 = _T("D:\\XunLeiDownload");

			Assert::IsTrue(Directory::Contains(strRootPath1, strDstPath));

			String strRootPath2 = _T("F:\\zhengwenyan");

			Assert::IsFalse(Directory::Contains(strRootPath2, strDstPath));
		}

		TEST_METHOD(Test_SetDirAttribute)
		{
			String strDstPath = _T("D:\\aa.wav");

			Directory::SetDirAttribute(strDstPath, HIDDEN);
		}

		TEST_METHOD(Test_RemoveDirAttribute)
		{
			String strDstPath = _T("D:\\aa.wav");

			Directory::RemoveDirAttribute(strDstPath, HIDDEN);
		}
	};
}