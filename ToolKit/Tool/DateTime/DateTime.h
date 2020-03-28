///************************************************************************
/// <copyrigth>2018-2019 Corporation.All Rights Reserved</copyrigth>
/// <author>tangyingzhong</author>
/// <contact>tangyz114987@outlook.com</contact>
/// <version>v1.0.0</version>
/// <describe>
/// You can get the local time from the class
///</describe>
/// <date>2019/7/16</date>
///***********************************************************************
#ifndef DATETIME_H
#define DATETIME_H

#include "Tool/Common/SystemType.h"
#include "Tool/BaseType/Int.h"
#include "Tool/BaseType/String.h"

using namespace std;
using namespace System::BasicType;

namespace System
{
	namespace Clock
	{
		class DateTime
		{
		public:
			typedef System::None None;
			typedef System::Boolean BOOL;
			typedef vector<String> SepratorTable;
			
			// Time's type
			typedef enum _TimeFormat
			{
				// Year/Month/Day
				YEAR_MONTH_DAY=0,			

				// Hour/Minute/Second
				HOUR_MINUTE_SECOND,		

				// Hour/Minute/Second/Millisecond
				HOUR_MINUTE_SECOND_MILLISECOND,		

				// Year/Month/Day Hour/Minute/Second
				YEAR_MONTH_DAY_HOUR_MINUTE_SECOND,				

				// Year/Month/Day Hour/Minute/Second/Ms
				YEAR_MONTH_DAY_HOUR_MINUTE_SECOND_MILLISECOND,				
			}TimeFormat;

			// Time type
			enum  TIME_TYPE_ENUM
			{
				// UTC time
				TIME_UTC_=0,

				// BeiJing time
				TIME_LOCAL
			};

		public:
			// Construct the DateTime
			DateTime(Int32 iYear=0,
				Int32 iMonth=0,
				Int32 iDay=0,
				Int32 iHour=8,
				Int32 iMin=0,
				Int32 iSec=0,
				Int32 iMillSec=0,
				TIME_TYPE_ENUM TimeType = TIME_LOCAL);

			// Destrcut the DateTime
			~DateTime();

			// Allow the object copying
			DateTime(const DateTime& other);

			// Allow the obejct assignment
			DateTime& operator=(DateTime& other);

			// Is equal or not
			Boolean operator==(DateTime& other);

		public:
			// Current time
			static DateTime Now(TIME_TYPE_ENUM TimeType = TIME_LOCAL);

			// Get the time from time_t
			static DateTime FromTime_t(time_t TimeSnap, TIME_TYPE_ENUM TimeType = TIME_LOCAL);

			// Get the time from string
			static DateTime FromString(String strTime, String strTimeFormat = _T("yyyy-MM-dd hh:mm:ss"));

			// Convert time to string with sepecial seperator
			String ToString(String strTimeFormat = _T("yyyy-MM-dd hh:mm:ss"));

			// Get time snap(Note: it can calculate to sec only)
			time_t ToTime_t();

		private:
			// Get the UTC time
			None GetUTCTime();

			// Get the Current local time
			None GetLoclTime();

			// Get time format seprators
			Boolean GetTimeFormatSep(String strTimeFormat, TimeFormat& FormatEnum, SepratorTable& Table);

			// Check the time format
			BOOL CheckTimeFormat(String strTimeFormat, TimeFormat& TFormat);

			// Check date
			BOOL CheckDate(String strTimeFormat);

			// Check time
			BOOL CheckTime(String strTimeFormat);

			// Check date time
			BOOL CheckDateTime(String strTimeFormat);

			// Get the seperator from the format
			BOOL GetTimeSeperators(String strTimeFormat, TimeFormat TFormat,SepratorTable& Table);

			// Convert time to string with sepecial seperator
			String ToString(TimeFormat TFormat,
				String strConnectSep = _T(" "),
				String strDataSeperator = _T("-"),
				String strTimeSeperator = _T(":"));

		private:
			// Get the time type
			inline TIME_TYPE_ENUM GetTimeType() const
			{
				return  m_eTimeType;
			}

			// Set the time type
			inline None SetTimeType(TIME_TYPE_ENUM Type)
			{
				m_eTimeType = Type;
			}

		private:
				// Time's type
				TIME_TYPE_ENUM m_eTimeType;

		public:
			// Year
			Int m_Year;

			// Month
			Int m_Month;

			// Day
			Int m_Day;

			// Hour
			Int m_Hour;

			// Minute
			Int m_Minute;

			// Second
			Int m_Second;

			// Milliseconds
			Int m_Milliseconds;
		};
	}
}

#endif // DATETIME_H