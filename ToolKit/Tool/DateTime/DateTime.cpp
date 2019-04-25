#include "Application\PreCompile.h"
#include "DateTime.h"

using namespace System::Clock;


///************************************************************************
/// <summary>
/// Construct the DateTime
/// </summary>
/// <returns></returns>
/// <remarks>
/// None
/// </remarks>
///***********************************************************************
DateTime::DateTime()
{
	this->GetLoclTime();
}


///************************************************************************
/// <summary>
/// Destrcut the DateTime
/// </summary>
/// <returns></returns>
/// <remarks>
/// None
/// </remarks>
///***********************************************************************
DateTime::~DateTime()
{

}


///************************************************************************
/// <summary>
/// Allow the object copying
/// </summary>
/// <param name=const DateTime & other></param>
/// <returns></returns>
/// <remarks>
/// None
/// </remarks>
///***********************************************************************
DateTime::DateTime(const DateTime& other)
{
	this->m_Year = other.m_Year;

	this->m_Month = other.m_Month;

	this->m_Day = other.m_Day;

	this->m_Hour = other.m_Hour;

	this->m_Minute = other.m_Minute;

	this->m_Second = other.m_Second;

	this->m_Milliseconds = other.m_Milliseconds;
}


///************************************************************************
/// <summary>
/// Allow the obejct assignment
/// </summary>
/// <param name=DateTime & other></param>
/// <returns></returns>
/// <remarks>
/// None
/// </remarks>
///***********************************************************************
DateTime& DateTime::operator=(DateTime& other)
{
	if (this != &other)
	{
		this->m_Year = other.m_Year;

		this->m_Month = other.m_Month;

		this->m_Day = other.m_Day;

		this->m_Hour = other.m_Hour;

		this->m_Minute = other.m_Minute;

		this->m_Second = other.m_Second;

		this->m_Milliseconds = other.m_Milliseconds;
	}

	return *this;
}


///************************************************************************
/// <summary>
/// Current time
/// </summary>
/// <returns></returns>
/// <remarks>
/// None
/// </remarks>
///***********************************************************************
DateTime DateTime::Now()
{
	return DateTime();
}


///************************************************************************
/// <summary>
/// Get the Current local time
/// </summary>
/// <returns></returns>
/// <remarks>
/// None
/// </remarks>
///***********************************************************************
DateTime::Empty DateTime::GetLoclTime()
{
	SYSTEMTIME LocalTime;

	::GetLocalTime(&LocalTime);

	this->m_Year = LocalTime.wYear;

	this->m_Month = LocalTime.wMonth;

	this->m_Day = LocalTime.wDay;

	this->m_Hour = LocalTime.wHour;

	this->m_Minute = LocalTime.wMinute;

	this->m_Second = LocalTime.wSecond;

	this->m_Milliseconds = LocalTime.wMilliseconds;
}


///************************************************************************
/// <summary>
/// Convert time to string with sepecial seperator
/// </summary>
/// <returns></returns>
/// <remarks>
/// Note: Time's format is like 2019/4/18 11:19::12::32
/// </remarks>
///***********************************************************************
String DateTime::ToString(TimeFormat TFormat, String strSeperator)
{
	String strDateTime = _T("");

	switch (TFormat)
	{
	case YEAR_MONTH_DAY:
		strDateTime = this->m_Year.ToString() + strSeperator
			+ this->m_Month.ToString() + strSeperator
			+ this->m_Day.ToString();

		break;

	case HOUR_MINUTE_SECOND:
		strDateTime = this->m_Hour.ToString() + strSeperator
			+ this->m_Minute.ToString() + strSeperator
			+ this->m_Second.ToString();

		break;

	case HOUR_MINUTE_SECOND_MILLISECOND:
		strDateTime = this->m_Hour.ToString() + strSeperator
			+ this->m_Minute.ToString() + strSeperator
			+ this->m_Second.ToString() + strSeperator
			+ this->m_Milliseconds.ToString();

		break;

	case YEAR_MONTH_DAY_HOUR_MINUTE_SECOND:
		strDateTime = this->m_Year.ToString() + strSeperator
			+ this->m_Month.ToString() + strSeperator
			+ this->m_Day.ToString() + strSeperator
			+ this->m_Hour.ToString() + strSeperator
			+ this->m_Minute.ToString() + strSeperator
			+ this->m_Second.ToString();

		break;

	case YEAR_MONTH_DAY_HOUR_MINUTE_SECOND_MILLISECOND:
		strDateTime = this->m_Year.ToString() + strSeperator
			+ this->m_Month.ToString() + strSeperator
			+ this->m_Day.ToString() + strSeperator
			+ this->m_Hour.ToString() + strSeperator
			+ this->m_Minute.ToString() + strSeperator
			+ this->m_Second.ToString() + strSeperator
			+ this->m_Milliseconds.ToString();

		break;

	default:
		strDateTime = this->m_Year.ToString() + strSeperator
			+ this->m_Month.ToString() + strSeperator
			+ this->m_Day.ToString() + strSeperator
			+ this->m_Hour.ToString() + strSeperator
			+ this->m_Minute.ToString() + strSeperator
			+ this->m_Second.ToString() + strSeperator
			+ this->m_Milliseconds.ToString();

		break;
	}

	return strDateTime;
}