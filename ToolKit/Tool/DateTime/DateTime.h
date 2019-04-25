///************************************************************************
/// <copyrigth>2018-2019 Corporation.All Rights Reserved</copyrigth>
/// <author>tangyingzhong</author>
/// <contact>tangyz114987@outlook.com</contact>
/// <version>V1.0.0</version>
/// <describe>
/// You can get the local time from the class
///</describe>
/// <date>2019/3/6</date>
///***********************************************************************
#ifndef DATETIME_H
#define DATETIME_H

#include "Tool\BaseType\Int.h"
#include "Tool\BaseType\String.h"

using namespace System::BasicType;

namespace System
{
	namespace Clock
	{
		///*********************************************************
		/// <class> DateTime </class>
		/// <summary>
		/// Supported time getting
		/// </summary>
		/// <version>V1.0.0 </version>
		/// <goup> C++ </group>
		/// <author>tangyingzhong</author>
		/// <contact>tangyz114987@outlook.com</contact>
		///**********************************************************/
		class DateTime
		{
		public:
			typedef System::Empty Empty;
			typedef System::Boolean BOOL;
			
			// Time's type
			typedef enum _TimeFormat
			{
				YEAR_MONTH_DAY=0,											// Year/Month/Day
				HOUR_MINUTE_SECOND,											// Hour/Minute/Second
				HOUR_MINUTE_SECOND_MILLISECOND,								// Hour/Minute/Second/Millisecond
				YEAR_MONTH_DAY_HOUR_MINUTE_SECOND,							// Year/Month/Day Hour/Minute/Second
				YEAR_MONTH_DAY_HOUR_MINUTE_SECOND_MILLISECOND,				// Year/Month/Day Hour/Minute/Second/Ms
			}TimeFormat;

		public:
			// Construct the DateTime
			DateTime();

			// Destrcut the DateTime
			~DateTime();

			// Allow the object copying
			DateTime(const DateTime& other);

			// Allow the obejct assignment
			DateTime& operator=(DateTime& other);

		public:
			// Current time
			static DateTime Now();

			// Convert time to string with sepecial seperator
			String ToString(TimeFormat TFormat,String strSeperator);

		private:
			// Get the Current local time
			Empty GetLoclTime();

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

#endif //!DATETIME_H_