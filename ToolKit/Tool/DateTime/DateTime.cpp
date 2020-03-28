#include <time.h>
#include "Tool/BaseType/Int.h"
#include "Tool/Encoding/UTF16.h"
#include "DateTime.h"

using namespace System::Clock;
using namespace System::Encoding;

// Construct the DateTime
DateTime::DateTime(Int32 iYear,
	Int32 iMonth,
	Int32 iDay,
	Int32 iHour,
	Int32 iMin,
	Int32 iSec,
	Int32 iMillSec,
	TIME_TYPE_ENUM TimeType) :
m_Year(iYear),
m_Month(iMonth),
m_Day(iDay),
m_Hour(iHour),
m_Minute(iMin),
m_Second(iSec),
m_Milliseconds(iMillSec),
m_eTimeType(TimeType)
{

}

// Destrcut the DateTime
DateTime::~DateTime()
{

}

// Allow the object copying
DateTime::DateTime(const DateTime& other)
{
	m_Year = other.m_Year;

	m_Month = other.m_Month;

	m_Day = other.m_Day;

	m_Hour = other.m_Hour;

	m_Minute = other.m_Minute;

	m_Second = other.m_Second;

	m_Milliseconds = other.m_Milliseconds;

	m_eTimeType = other.m_eTimeType;
}

// Allow the obejct assignment
DateTime& DateTime::operator=(DateTime& other)
{
	if (this != &other)
	{
		m_Year = other.m_Year;

		m_Month = other.m_Month;

		m_Day = other.m_Day;

		m_Hour = other.m_Hour;

		m_Minute = other.m_Minute;

		m_Second = other.m_Second;

		m_Milliseconds = other.m_Milliseconds;

		m_eTimeType = other.m_eTimeType;
	}

	return *this;
}

// Is equal or not
Boolean DateTime::operator==(DateTime& other)
{
	return (m_Year == other. m_Year)
		&& (m_Month==other.m_Month)
		&& (m_Day==other.m_Day)
		&& (m_Hour==other.m_Hour)
		&& (m_Minute==other.m_Minute)
		&& (m_Second==other.m_Second)
		&& (m_Milliseconds==other.m_Milliseconds
		&& (m_eTimeType == other.m_eTimeType));
}

// Get time snap
time_t DateTime::ToTime_t()
{
	struct tm CurTime;

	CurTime.tm_year = m_Year - 1900;

	CurTime.tm_mon = m_Month - 1;

	CurTime.tm_mday = m_Day;

	CurTime.tm_hour = m_Hour;

	CurTime.tm_min = m_Minute;

	CurTime.tm_sec = m_Second;

	CurTime.tm_isdst = 0;

	time_t TimeSnap = mktime(&CurTime);

	return TimeSnap;
}

// Get the time from string
DateTime DateTime::FromString(String strTime, String strTimeFormat)
{
	if (strTime.IsEmpty())
	{
		return DateTime();
	}

	DateTime CurTime;

	// Get the time format's seperators
	TimeFormat FormatEnum = YEAR_MONTH_DAY;

	SepratorTable Table;

	if (!CurTime.GetTimeFormatSep(strTimeFormat, FormatEnum, Table))
	{
		return DateTime();
	}

	// Build new time format
	String strNewFormat = String(_T("%d%s%d%s%d%s%d%s%d%s%d"))
		.Arg(Table[0])
		.Arg(Table[0])
		.Arg(Table[1])
		.Arg(Table[2])
		.Arg(Table[2]);

	sscanf(strTime.ToANSIData().c_str(),
		strNewFormat.ToANSIData().c_str(),
		&CurTime.m_Year,
		&CurTime.m_Month,
		&CurTime.m_Day,
		&CurTime.m_Hour,
		&CurTime.m_Minute,
		&CurTime.m_Second);

	struct tm Time;
	
	Time.tm_year = CurTime.m_Year - 1900;

	Time.tm_mon = CurTime.m_Month - 1;

	Time.tm_mday = CurTime.m_Day;

	Time.tm_hour = CurTime.m_Hour;

	Time.tm_min = CurTime.m_Minute;

	Time.tm_sec = CurTime.m_Second;

	time_t TimeSnap = mktime(&Time);

	return DateTime::FromTime_t(TimeSnap);
}

// Get the time from time_t
DateTime DateTime::FromTime_t(time_t TimeSnap, TIME_TYPE_ENUM TimeType)
{
	time_t t = TimeSnap;

	struct tm* p = NULL;

	if (TimeType==TIME_LOCAL)
	{
		p = localtime(&t);
	}
	else if (TimeType==TIME_UTC)
	{
		p = gmtime(&t);	
	}

	DateTime CurDateTime;

	CurDateTime.m_Year = 1900 + p->tm_year;

	CurDateTime.m_Month = 1 + p->tm_mon;

	CurDateTime.m_Day = p->tm_mday;

	CurDateTime.m_Hour = p->tm_hour;

	CurDateTime.m_Minute = p->tm_min;

	CurDateTime.m_Second = p->tm_sec;

	CurDateTime.m_Milliseconds = 0;

	return CurDateTime;
}

// Current time
DateTime DateTime::Now(TIME_TYPE_ENUM TimeType)
{
	DateTime CurTime;

	if (TimeType==TIME_LOCAL)
	{
		CurTime.GetLoclTime();
	}
	else if (TimeType == TIME_UTC)
	{
		CurTime.GetUTCTime();
	}

	return CurTime;
}

// Get the UTC time
None DateTime::GetUTCTime()
{
	time_t TimeSnap = time(NULL);

	struct tm* pGmTime=NULL;

	pGmTime = gmtime(&TimeSnap);

	m_Year = 1900 + pGmTime->tm_year;

	m_Month = 1 + pGmTime->tm_mon;

	m_Day = pGmTime->tm_mday;

	m_Hour = pGmTime->tm_hour;

	m_Minute = pGmTime->tm_min;

	m_Second = pGmTime->tm_sec;

	m_Milliseconds = 0;
}

// Get the Current local time
DateTime::None DateTime::GetLoclTime()
{
	time_t t = time(NULL);

	struct tm* p = localtime(&t);

	m_Year = 1900 + p->tm_year;

	m_Month = 1 + p->tm_mon;

	m_Day = p->tm_mday;

	m_Hour = p->tm_hour;

	m_Minute = p->tm_min;

	m_Second = p->tm_sec;

	m_Milliseconds = 0;
}

// Convert time to string with sepecial seperator
String DateTime::ToString(TimeFormat TFormat,
	String strConnectSep,
	String strDataSeperator,
	String strTimeSeperator)
{
	String strDateTime;

	switch (TFormat)
	{
	case YEAR_MONTH_DAY:
	{
		strDateTime = String(_T("%d"))
			+ strDataSeperator
			+ _T("%d")
			+ strDataSeperator
			+ _T("%d");

		strDateTime.Arg(m_Year)
			.Arg(m_Month)
			.Arg(m_Day);
	}
		break;

	case HOUR_MINUTE_SECOND:
	{
		strDateTime = String(_T("%d"))
			+ strTimeSeperator
			+ _T("%d")
			+ strTimeSeperator
			+ _T("%d");

		strDateTime.Arg(m_Hour)
			.Arg(m_Minute)
			.Arg(m_Second);
	}
		break;

	case HOUR_MINUTE_SECOND_MILLISECOND:
	{
		strDateTime = String(_T("%d"))
			+ strTimeSeperator
			+ _T("%d")
			+ strTimeSeperator
			+ _T("%d")
			+ strTimeSeperator
			+ _T("%d");

		strDateTime.Arg(m_Hour)
			.Arg(m_Minute)
			.Arg(m_Second)
			.Arg(m_Milliseconds);
	}
		break;

	case YEAR_MONTH_DAY_HOUR_MINUTE_SECOND:
	{
		strDateTime = String(_T("%s"))
			+ strDataSeperator
			+ _T("%s")
			+ strDataSeperator
			+ _T("%s")
			+ strConnectSep
			+ _T("%s")
			+ strTimeSeperator
			+ _T("%s")
			+ strTimeSeperator
			+ _T("%s");

		String strYear = _T("1970");

		if (m_Year.ToString().GetLength() == 4)
		{
			strYear = m_Year.ToString();
		}

		String strMonth = _T("01");

		if (m_Month.ToString().GetLength() != 2)
		{
			strMonth = String(_T("0")) + m_Month.ToString();
		}
		else
		{
			strMonth = m_Month.ToString();
		}

		String strDay = _T("01");

		if (m_Day.ToString().GetLength() != 2)
		{
			strDay = String(_T("0")) + m_Day.ToString();
		}
		else
		{
			strDay = m_Day.ToString();
		}

		String strHour = _T("01");

		if (m_Hour.ToString().GetLength() != 2)
		{
			strHour = String(_T("0")) + m_Hour.ToString();
		}
		else
		{
			strHour = m_Hour.ToString();
		}

		String strMin = _T("01");

		if (m_Minute.ToString().GetLength() != 2)
		{
			strMin = String(_T("0")) + m_Minute.ToString();
		}
		else
		{
			strMin = m_Minute.ToString();
		}

		String strSecond = _T("01");

		if (m_Second.ToString().GetLength() != 2)
		{
			strSecond = String(_T("0")) + m_Second.ToString();
		}
		else
		{
			strSecond = m_Second.ToString();
		}

		strDateTime.Arg(strYear)
			.Arg(strMonth)
			.Arg(strDay)
			.Arg(strHour)
			.Arg(strMin)
			.Arg(strSecond);
	}
		break;

	case YEAR_MONTH_DAY_HOUR_MINUTE_SECOND_MILLISECOND:
	{
		strDateTime = String(_T("%d"))
			+ strDataSeperator
			+ _T("%d")
			+ strDataSeperator
			+ _T("%d")
			+ strConnectSep
			+ _T("%d")
			+ strTimeSeperator
			+ _T("%d")
			+ strTimeSeperator
			+ _T("%d")
			+ strTimeSeperator
			+ _T("%d");

		strDateTime.Arg(m_Year)
			.Arg(m_Month)
			.Arg(m_Day)
			.Arg(m_Hour)
			.Arg(m_Minute)
			.Arg(m_Second)
			.Arg(m_Milliseconds);
	}
		break;

	default:
	{
		strDateTime = String(_T("%d"))
			+ strDataSeperator
			+ _T("%d")
			+ strDataSeperator
			+ _T("%d")
			+ strConnectSep
			+ _T("%d")
			+ strTimeSeperator
			+ _T("%d")
			+ strTimeSeperator
			+ _T("%d")
			+ strTimeSeperator
			+ _T("%d");

		strDateTime.Arg(m_Year)
			.Arg(m_Month)
			.Arg(m_Day)
			.Arg(m_Hour)
			.Arg(m_Minute)
			.Arg(m_Second)
			.Arg(m_Milliseconds);
	}
		break;
	}

	return strDateTime;
}

// Get time format seprators
Boolean DateTime::GetTimeFormatSep(String strTimeFormat, TimeFormat& FormatEnum, SepratorTable& Table)
{
	if (strTimeFormat.IsEmpty())
	{
		return false;
	}

	// Check format 
	if (!CheckTimeFormat(strTimeFormat, FormatEnum))
	{
		return false;
	}

	// Get the seperator from the format
	if (!GetTimeSeperators(strTimeFormat, FormatEnum, Table))
	{
		return false;
	}

	if (Table.empty())
	{
		return false;
	}

	if (Table.size() != 3)
	{
		return false;
	}

	return true;
}

// Convert time to string with sepecial seperator
String DateTime::ToString(String strTimeFormat)
{
	TimeFormat FormatEnum = YEAR_MONTH_DAY;

	SepratorTable Table;

	if (!GetTimeFormatSep(strTimeFormat, FormatEnum, Table))
	{
		return _T("");
	}

	return ToString(FormatEnum, Table[1], Table[0], Table[2]);
}

// Check date
DateTime::BOOL DateTime::CheckDate(String strTimeFormat)
{
	if (strTimeFormat.IsEmpty())
	{
		return false;
	}

	if (!strTimeFormat.IsContain(_T("yyyy")))
	{
		return false;
	}

	if (!strTimeFormat.IsContain(_T("MM")))
	{
		return false;
	}

	if (!strTimeFormat.IsContain(_T("dd")))
	{
		return false;
	}

	if (strTimeFormat.GetLength()!=String(_T("yyyy-MM-dd")).GetLength()
		&& strTimeFormat.GetLength() != String(_T("yyyy-MM-dd hh:mm:ss")).GetLength()
		&& strTimeFormat.GetLength() != String(_T("yyyy-MM-dd hh:mm:ss:zz")).GetLength())
	{
		return false;
	}

	return true;
}

// Check time
DateTime::BOOL DateTime::CheckTime(String strTimeFormat)
{
	if (strTimeFormat.IsEmpty())
	{
		return false;
	}

	if (!strTimeFormat.IsContain(_T("hh")))
	{
		return false;
	}

	if (!strTimeFormat.IsContain(_T("mm")))
	{
		return false;
	}

	if (!strTimeFormat.IsContain(_T("ss")))
	{
		return false;
	}

	if (strTimeFormat.GetLength() != String(_T("hh:mm:ss")).GetLength()
		&& strTimeFormat.GetLength() != String(_T("hh:mm:ss:zz")).GetLength()
		&& strTimeFormat.GetLength() != String(_T("yyyy-MM-dd hh:mm:ss")).GetLength()
		&& strTimeFormat.GetLength() != String(_T("yyyy-MM-dd hh:mm:ss:zz")).GetLength())
	{
		return false;
	}

	return true;
}

// Check date time
DateTime::BOOL DateTime::CheckDateTime(String strTimeFormat)
{
	if (strTimeFormat.IsEmpty())
	{
		return false;
	}

	if (!CheckDate(strTimeFormat))
	{
		return false;
	}

	if (!CheckTime(strTimeFormat))
	{
		return false;
	}

	return true;
}

// Check the time format
DateTime::BOOL DateTime::CheckTimeFormat(String strTimeFormat, TimeFormat& TFormat)
{
	if (strTimeFormat.IsEmpty())
	{
		return false;
	}

	if (strTimeFormat.GetLength() != String(_T("yyyy-MM-dd")).GetLength()
		&& strTimeFormat.GetLength() != String(_T("hh:mm:ss")).GetLength()
		&& strTimeFormat.GetLength() != String(_T("hh:mm:ss:zz")).GetLength()
		&& strTimeFormat.GetLength()!=String(_T("yyyy-MM-dd hh:mm:ss")).GetLength()
		&& strTimeFormat.GetLength() != String(_T("yyyy-MM-dd hh:mm:ss:zz")).GetLength())
	{
		return false;
	}

	if (strTimeFormat.GetLength() == String(_T("yyyy-MM-dd")).GetLength())
	{
		if (!CheckDate(strTimeFormat))
		{
			return false;
		}

		TFormat = YEAR_MONTH_DAY;
	}
	else if (strTimeFormat.GetLength() == String(_T("hh:mm:ss")).GetLength()
		|| strTimeFormat.GetLength() == String(_T("hh:mm:ss:zz")).GetLength())
	{
		if (!CheckTime(strTimeFormat))
		{
			return false;
		}

		if (strTimeFormat.GetLength() == String(_T("hh:mm:ss")).GetLength())
		{
			TFormat = HOUR_MINUTE_SECOND;
		}
		else
		{
			TFormat = HOUR_MINUTE_SECOND_MILLISECOND;
		}	
	}
	else if (strTimeFormat.GetLength() == String(_T("yyyy-MM-dd hh:mm:ss")).GetLength()
		|| strTimeFormat.GetLength() == String(_T("yyyy-MM-dd hh:mm:ss:zz")).GetLength())
	{
		if (!CheckDateTime(strTimeFormat))
		{
			return false;
		}

		if (strTimeFormat.GetLength() == String(_T("yyyy-MM-dd hh:mm:ss")).GetLength())
		{
			TFormat = YEAR_MONTH_DAY_HOUR_MINUTE_SECOND;
		}
		else
		{
			TFormat = YEAR_MONTH_DAY_HOUR_MINUTE_SECOND_MILLISECOND;
		}
	}

	return true;
}

// Get the seperator from the format
DateTime::BOOL DateTime::GetTimeSeperators(String strTimeFormat, TimeFormat TFormat, SepratorTable& Table)
{
	if (strTimeFormat.IsEmpty())
	{
		return false;
	}

	String strConnectSeperator= _T(" ");
	String strDataSeperator= _T("-");
	String strTimeSeperator= _T(":");

	switch (TFormat)
	{
	case TimeFormat::YEAR_MONTH_DAY:

		strDataSeperator = strTimeFormat.SubString(4, 1);

		break;

	case TimeFormat::HOUR_MINUTE_SECOND:
	case TimeFormat::HOUR_MINUTE_SECOND_MILLISECOND:

		strTimeSeperator = strTimeFormat.SubString(2, 1);

		break;

	case TimeFormat::YEAR_MONTH_DAY_HOUR_MINUTE_SECOND:
	case TimeFormat::YEAR_MONTH_DAY_HOUR_MINUTE_SECOND_MILLISECOND:

		strDataSeperator = strTimeFormat.SubString(4, 1);

		strConnectSeperator = strTimeFormat.SubString(10, 1);

		strTimeSeperator = strTimeFormat.SubString(13, 1);

		break;

	default:

		break;
	}
	
	Table.push_back(strDataSeperator);
	Table.push_back(strConnectSeperator);
	Table.push_back(strTimeSeperator);

	return true;
}