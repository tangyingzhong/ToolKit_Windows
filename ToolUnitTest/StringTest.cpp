#include "stdafx.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace String_UnitTest
{
	TEST_CLASS(StringTest)
	{
	public:
		TEST_METHOD(TestMethod_Constrcutor1)
		{
			std::string strWhat = "I don't know every thing";

			String strFinal = strWhat;

			Assert::IsTrue(strFinal == _T("I don't know every thing"));

			std::string strWhat1 = "其实我不知道啊";

			String strFinal1 = strWhat1;

			Assert::IsTrue(strFinal1 == "其实我不知道啊");

			std::wstring strTest1 = L"我在游荡人间，你可知否";

			String strTest11 = strTest1;

			Assert::IsTrue(strTest11 == L"我在游荡人间，你可知否");
		}

		TEST_METHOD(TestMethod_UTF8)
		{
			std::string strFileData = GetFileData(_T("D:\\app.txt"));

			String strTest23 = String(strFileData, ENCODE_UTF8);

			std::string strUtf8 = strTest23.ToUTF8Data();

			std::string strAnsi = strTest23.ToANSIData();

			std::wstring strUnicode = strTest23.ToUnicodeData();

			std::string strFileData1 = GetFileData(_T("D:\\app1.txt"));

			String strTest33 = strFileData1;

			std::wstring strBigFileData1 = Unicode::GetString(strFileData1, ENCODE_ANSI);

			String strTest34 = strBigFileData1;
		}
		TEST_METHOD(TestMethod_Arg)
		{
			String strTest1 = _T("Source_test_string:%d + %f=%lf,%s");

			strTest1.Arg(15).Arg(2.5f).Arg(5.778).Arg(_T("Fromtt"));

			Assert::IsTrue(strTest1 == _T("Source_test_string:15 + 2.5=5.778,Fromtt"));

			String strFinal = _T("%d+%f+%lf=%s");

			strFinal.Arg(_T("78")).Arg(8.6).Arg(89).Arg(9.5f);

			Assert::IsTrue(strFinal == _T("89+9.5+8.6=78"));
		}

		TEST_METHOD(TestMethod_Split)
		{
			String strTest1 = _T("Source_test_string");

			String::StringTable Table1;

			Assert::IsTrue(strTest1.Split(_T("_"), Table1));

			String strTest2 = _T("-Source-test-string-");

			String::StringTable Table2;

			Assert::IsFalse(strTest2.Split(_T("_"), Table2));

			Assert::IsTrue(strTest2.Split(_T("-"), Table2));

			String strTest3 = _T("-Source-test-string-%$");

			String::StringTable Table3;

			Assert::IsTrue(strTest3.Split(_T("%"), Table3));
		}

		TEST_METHOD(TestMethod_SubString)
		{
			String strTest = _T("I need an assistant now");

			String strNew1 = strTest.SubString(-1);

			Assert::IsTrue(strNew1 == _T(""));

			String strNew2 = strTest.SubString(0);

			Assert::IsTrue(strNew2 == strTest);

			String strNew3 = strTest.SubString(13434);

			Assert::IsTrue(strNew3 == _T(""));

			String strNew4 = strTest.SubString(-1, 8980);

			Assert::IsTrue(strNew4 == _T(""));

			String strNew5 = strTest.SubString(0, strTest.GetLength());

			Assert::IsTrue(strNew5 == strTest);

			String strNew6 = strTest.SubString(13434, -1);

			Assert::IsTrue(strNew6 == _T(""));

			String strNew7 = strTest.SubString(-1, strTest.GetLength());

			Assert::IsTrue(strNew7 == _T(""));
		}

		TEST_METHOD(TestMethod_Left)
		{
			String strTest = _T("I need an assistant now\\yu\\reess\\yuer");

			String strNew1 = strTest.Left(9090);

			Assert::IsTrue(strNew1.IsEmpty());

			String strNew2 = strTest.Left(-1);

			Assert::IsTrue(strNew2.IsEmpty());

			String strNew3 = strTest.Left(strTest.GetLength());

			Assert::IsTrue(strNew3==strTest);

			String strNew4 = strTest.Left(0);

			Assert::IsTrue(strNew4==_T(""));

			String strNew5 = strTest.Left(strTest.GetLength() - 2);

			Assert::IsTrue(strNew5 == _T("I need an assistant now\\yu\\reess\\yu"));
		}

		TEST_METHOD(TestMethod_Right)
		{
			String strTest = _T("I need an assistant now\\yu\\reess\\yuer");

			String strNew1 = strTest.Right(9090);

			Assert::IsTrue(strNew1 == _T(""));

			String strNew2 = strTest.Right(-1);

			Assert::IsTrue(strNew2 == _T(""));

			String strNew3 = strTest.Right(strTest.GetLength());

			Assert::IsTrue(strNew3 == strTest);

			String strNew4 = strTest.Right(0);

			Assert::IsTrue(strNew4 == _T(""));

			String strNew5 = strTest.Right(strTest.GetLength() - 2);

			Assert::IsTrue(strNew5 == _T("need an assistant now\\yu\\reess\\yuer"));
		}

		TEST_METHOD(TestMethod_Find)
		{
			String strTest = _T("I need an assistant now\\yu\\reess\\yuer");

			Int32 iPos1 = strTest.Find(_T("\\"), 0);

			Assert::AreNotEqual(-1, iPos1);

			Int32 iPos11 = strTest.Find(_T("\\"), 24);

			Assert::AreNotEqual(-1, iPos11);

			Int32 iPos2 = strTest.Find(_T("%"), 0);

			Assert::AreEqual(-1, iPos2);

			Int32 iPos3 = strTest.Find(_T("%"), -1);

			Assert::AreEqual(-1, iPos3);

			Int32 iPos4 = strTest.Find(_T("\\"), -1);

			Assert::AreEqual(-1, iPos4);

			Int32 iPos5 = strTest.Find(_T("\\"), 7898);

			Assert::AreEqual(-1, iPos5);

			Int32 iPos6 = strTest.Find(_T(""), 7898);

			Assert::AreEqual(-1, iPos6);
		}

		TEST_METHOD(TestMethod_FindLast)
		{
			String strTest = _T("I need an assistant now\\yu\\reess\\yuer");

			Int32 iPos1 = strTest.FindLast(_T("\\"));

			Assert::AreNotEqual(-1, iPos1);

			Int32 iPos2 = strTest.FindLast(_T("%"));

			Assert::AreEqual(-1, iPos2);

			Int32 iPos6 = strTest.FindLast(_T(""));

			Assert::AreEqual(-1, iPos6);
		}

		TEST_METHOD(TestMethod_Replace)
		{
			String strTest = _T("I need an assistant now\\yu\\reess\\yuer");

			strTest.Replace(23, 1, _T("/"));

			strTest.Replace(23, 6, _T("Common"));

			strTest.Replace(0, 1, _T("\\"));

			strTest.Replace(0, -1, _T("\\"));

			strTest.Replace(-1, -1, _T("\\"));

			strTest.Replace(7893, 9344, _T("\\"));
		}

		TEST_METHOD(TestMethod_IsContain)
		{
			String strTest = _T("I need an assistant now\\yu\\reess\\yuer");

			Assert::IsTrue(strTest.IsContain(_T("\\")));

			Assert::IsFalse(strTest.IsContain(_T("&")));
		}

		TEST_METHOD(TestMethod_AllocWideString)
		{
			String strTest = _T("I need an assistant 我很幸运");

			std::wstring w = strTest.AllocWideString();

			Assert::IsTrue(w == strTest.ToUnicodeData());
		}

		TEST_METHOD(TestMethod_ToANSIData)
		{
			String strTest = _T("I need an assistant 我很幸运");

			std::string strAnsi = strTest.ToANSIData();

			Assert::IsTrue(strAnsi == "I need an assistant 我很幸运");
		}

		TEST_METHOD(TestMethod_UnicodeData)
		{
			String strTest = _T("I need an assistant 我很幸运");

			std::wstring w = strTest.ToUnicodeData();

			Assert::IsTrue(w == strTest.ToUnicodeData());
		}

		TEST_METHOD(TestMethod_MakeUpper)
		{
			String strTest = _T("I need an assistant now\\yu\\reess\\yuer");

			strTest.MakeUpper();

			Assert::IsTrue(strTest == _T("I NEED AN ASSISTANT NOW\\YU\\REESS\\YUER"));
		}

		TEST_METHOD(TestMethod_MakeLower)
		{
			String strTest = _T("CAN YOU DO ME A FAVOR?");

			strTest.MakeLower();

			Assert::IsTrue(strTest == _T("can you do me a favor?"));
		}

		TEST_METHOD(TestMethod_operator_index)
		{
			String strTest = _T("I need an assistant now\\yu\\reess\\yuer");

			Character strIndex = strTest[1];

			Assert::IsTrue(strIndex == _T(' '));

			Character strIndex0 = strTest[5];

			Assert::IsTrue(strIndex0 == _T('d'));

			Character strIndex1 = strTest[-1];

			Assert::IsTrue(strIndex1 == _T('N'));

			Character strIndex2 = strTest[9093];

			Assert::IsTrue(strIndex2 == _T('N'));
		}

		TEST_METHOD(TestMethod_operator_Add)
		{
			String strTest = _T("Great you are! ");

			strTest + _T("boy")+_T(" and girl");

			Assert::IsTrue(strTest == _T("Great you are! boy and girl"));
		}

		TEST_METHOD(TestMethod_operator_Equal)
		{
			String strTest = _T("Great you are!");

			String strTest1 = _T("Great you are !");

			Assert::IsFalse(strTest == strTest1);

			String strTest2 = _T("Great you are!");

			Assert::IsTrue(strTest == strTest2);
		}

		TEST_METHOD(TestMethod_operator_NotEqual)
		{
			String strTest = _T("Great you are!");

			String strTest1 = _T("erererr !");

			Assert::IsTrue(strTest != strTest1);

			String strTest2 = _T("Great you are!");

			Assert::IsFalse(strTest != strTest2);
		}

		TEST_METHOD(TestMethod_operator_IsNone)
		{
			String strTest = _T("Great you are!");

			Assert::IsFalse(strTest.IsEmpty());

			String strTest2 =_T("");

			Assert::IsTrue(strTest2.IsEmpty());
		}

		TEST_METHOD(TestMethod_operator_CStr)
		{
			String strTest = _T("Great you are! 我很幸运");

			LPCTSTR pTest = strTest.CStr();

			Assert::IsTrue(pTest != NULL);
		}

		TEST_METHOD(TestMethod_operator_Parse)
		{
			String strData = _T("15478");

			Int32 iData1 = String::Parse<Int32>(strData);

			Assert::IsTrue(iData1==15478);

			String strData1 = _T("79384rer");

			Int32 iData2 = String::Parse<Int32>(strData1);

			Assert::IsTrue(iData2 == 79384);

			String strData2 = _T("yuhf");

			Int32 iData3 = String::Parse<Int32>(strData2);

			Assert::IsTrue(iData3 == 0);
		}

		TEST_METHOD(TestMethod_operator_ToString)
		{
			Int32 iData1 = 9089;

			String strData1=String::ToString<Int32>(iData1);

			Assert::IsTrue(strData1 == _T("9089"));

			Real Data2 = 9089.52;

			String strData2 = String::ToString<Real>(Data2);

			Assert::IsTrue(strData2.IsContain(_T("9089.52")));
		}

	private:
		// Get a string
		std::string GetFileData(String strFilePath)
		{
			File FileHelper;

			if (!FileHelper.Open(strFilePath, File::FileMode::OPEN, File::FileAccess::READWRITE))
			{
				return "";
			}

			SByte buffer[1024] = { 0 };

			FileHelper.Read(buffer, 0, 1024);

			FileHelper.Close();

			return buffer;
		}
	};
}