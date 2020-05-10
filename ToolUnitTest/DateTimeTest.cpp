#include "stdafx.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace DateTime_UnitTest
{		
	TEST_CLASS(DateTimeTest)
	{
	public:
		TEST_METHOD(Test_Now)
		{
			DateTime CurTime1 = DateTime::Now(DateTime::TIME_UTC_);

			String strData1 = CurTime1.ToString();

			std::cout << strData1.ToANSIData() << std::endl;

			DateTime CurTime2 = DateTime::Now(DateTime::TIME_LOCAL);

			String strData2 = CurTime2.ToString();

			std::cout << strData2.ToANSIData() << std::endl;
		}
		TEST_METHOD(Test_ToTime_t)
		{
			DateTime CurTime1 = DateTime::Now(DateTime::TIME_UTC_);

			time_t t1 = CurTime1.ToTime_t();

			String strTime1 = DateTime::FromTime_t(t1).ToString();

			DateTime CurTime2 = DateTime::Now(DateTime::TIME_LOCAL);

			time_t t2 = CurTime2.ToTime_t();

			String strTime2 = DateTime::FromTime_t(t2).ToString();
		}

		TEST_METHOD(Test_FromTime_t)
		{
			DateTime CurTime1 = DateTime::Now(DateTime::TIME_UTC_);

			time_t t1 = CurTime1.ToTime_t();

			DateTime Time1 = DateTime::FromTime_t(t1);

			Assert::IsTrue(CurTime1 == Time1);

			DateTime CurTime2 = DateTime::Now(DateTime::TIME_LOCAL);

			time_t t2 = CurTime2.ToTime_t();

			DateTime Time2 = DateTime::FromTime_t(t2);

			Assert::IsTrue(CurTime2 == Time2);
		}

		TEST_METHOD(Test_ToString)
		{
			DateTime CurTime1 = DateTime::Now(DateTime::TIME_UTC_);

			String strTime = CurTime1.ToString(_T("yyyy-MM-ddThh:mm:ss"));

			DateTime Time1 = DateTime::FromString(strTime, _T("yyyy-MM-ddThh:mm:ss"));

			Assert::IsTrue(CurTime1 == Time1);

			DateTime CurTime2 = DateTime::Now(DateTime::TIME_LOCAL);

			String strTime2 = CurTime2.ToString(_T("yyyy+MM+dd hh*mm*ss"));

			DateTime Time2 = DateTime::FromString(strTime2, _T("yyyy+MM+dd hh*mm*ss"));

			Assert::IsTrue(CurTime2 == Time2);

			DateTime CurTime11 = DateTime::Now(DateTime::TIME_UTC_);

			String strTime11 = CurTime11.ToString(_T("yyyy-MM-ddThh:mm:ss"));

			DateTime Time21 = DateTime::FromString(strTime11, _T("yyyy-MM-ddThh:mm:ss"));

			Assert::IsTrue(CurTime11 == Time21);
		}
	};
}