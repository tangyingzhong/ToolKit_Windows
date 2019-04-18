#include "Application\PreCompile.h"
#include "Double.h"

using namespace System::BasicType;

///************************************************************************
/// <summary>
/// Contruct a Double 
/// </summary>
/// <returns></returns>
/// <remarks>
/// 
/// </remarks>
///***********************************************************************
Double::Double() :m_Value(0.0l)
{

}


///************************************************************************
/// <summary>
/// Contruct a Double with a value 
/// </summary>
/// <param name=v>initialize the Double with a value</param>
/// <returns></returns>
/// <remarks>
/// 
/// </remarks>
///***********************************************************************
Double::Double(double dValue) :m_Value(dValue)
{

}


///************************************************************************
/// <summary>
/// Destruct the Double
/// </summary>
/// <returns></returns>
/// <remarks>
/// none
/// </remarks>
///***********************************************************************
Double::~Double()
{

}


///************************************************************************
/// <summary>
/// Allow the object copying
/// </summary>
/// <param name=other>another double object</param>
/// <returns></returns>
/// <remarks>
/// none
/// </remarks>
///***********************************************************************
Double::Double(const Double& Another)
{
	this->SetValue(Another.GetValue());
}


///************************************************************************
/// <summary>
/// Allow the obejct assignment
/// </summary>
/// <param name=other>another double object</param>
/// <returns>self object</returns>
/// <remarks>
/// none
/// </remarks>
///***********************************************************************
Double& Double::operator=(const Double& Another)
{
	if (this != &Another)
	{
		this->SetValue(Another.GetValue());
	}

	return *this;
}


///************************************************************************
/// <summary>
/// Implement the + object
/// </summary>
/// <param name=other>Another double object</param>
/// <returns>New double object</returns>
/// <remarks>
/// none
/// </remarks>
///***********************************************************************
Double Double::operator+(Double& Another)
{
	return (this->GetValue() + Another.GetValue());
}


///************************************************************************
/// <summary>
/// Implement the + value
/// </summary>
/// <param name=value>A double value</param>
/// <returns>New double object</returns>
/// <remarks>
/// none
/// </remarks>
///***********************************************************************
Double Double::operator+(double dValue)
{
	return (this->GetValue() + dValue);
}


///************************************************************************
/// <summary>
/// Implement the += object
/// </summary>
/// <param name=other>Another double object</param>
/// <returns>New double object</returns>
/// <remarks>
/// none
/// </remarks>
///***********************************************************************
Double Double::operator+=(Double& Another)
{
	return (this->m_Value += Another.GetValue());
}


///************************************************************************
/// <summary>
/// Implement the += value
/// </summary>
/// <param name=value>A double value</param>
/// <returns>New double object</returns>
/// <remarks>
/// none
/// </remarks>
///***********************************************************************
Double Double::operator+=(double dValue)
{
	return (this->m_Value += dValue);
}


///************************************************************************
/// <summary>
/// Implement the -= object
/// </summary>
/// <param name=other>Another double object</param>
/// <returns>New double object</returns>
/// <remarks>
/// none
/// </remarks>
///************************************************************************
Double Double::operator-=(Double& Another)
{
	return (this->m_Value -= Another.GetValue());
}


///************************************************************************
/// <summary>
/// Implement the -= value
/// </summary>
/// <param name=value>A double value</param>
/// <returns>New double object</returns>
/// <remarks>
/// none
/// </remarks>
///************************************************************************
Double Double::operator-=(double dValue)
{
	return (this->m_Value -= dValue);
}


///************************************************************************
/// <summary>
/// Implement the - object
/// </summary>
/// <param name=other>Another double object</param>
/// <returns>New double object</returns>
/// <remarks>
/// none
/// </remarks>
///***********************************************************************
Double Double::operator-(Double& Another)
{
	return (this->m_Value - Another.GetValue());
}


///************************************************************************
/// <summary>
/// Implement the - value
/// </summary>
/// <param name=value>A double value</param>
/// <returns>New double object</returns>
/// <remarks>
/// none
/// </remarks>
///***********************************************************************
Double Double::operator-(double dValue)
{
	return (this->m_Value - dValue);
}


///************************************************************************
/// <summary>
/// Implement the * object
/// </summary>
/// <param name=other>Another double object</param>
/// <returns>New double object</returns>
/// <remarks>
/// none
/// </remarks>
///***********************************************************************
Double Double::operator*(Double& Another)
{
	return (this->m_Value * Another.GetValue());
}


///************************************************************************
/// <summary>
/// Implement the * value
/// </summary>
/// <param name=value>A double value</param>
/// <returns>New double object</returns>
/// <remarks>
/// none
/// </remarks>
///***********************************************************************
Double Double::operator*(double dValue)
{
	return (this->m_Value * dValue);
}


///************************************************************************
/// <summary>
/// Implement the / object
/// </summary>
/// <param name=other>Another double object</param>
/// <returns>New double object</returns>
/// <remarks>
/// none
/// </remarks>
///***********************************************************************
Double Double::operator/(Double& Another)
{
	return (this->m_Value / Another.GetValue());
}


///************************************************************************
/// <summary>
/// Implement the / value
/// </summary>
/// <param name=value>A double value</param>
/// <returns>New double object</returns>
/// <remarks>
/// none
/// </remarks>
///***********************************************************************
Double Double::operator/(double dValue)
{
	return (this->m_Value / dValue);
}


///************************************************************************
/// <summary>
/// Override the double type
/// </summary>
/// <returns> </returns>
/// <remarks>
/// none
/// </remarks>
///***********************************************************************
Double::operator double() const
{
	return this->GetValue();
}


///************************************************************************
/// <summary>
/// Parse the string to double
/// </summary>
/// <param name=DoubleString>Double string</param>
/// <returns>New double object</returns>
/// <remarks>
/// none
/// </remarks>
///***********************************************************************
Double Double::Parse(String NumberString)
{
	if (NumberString == _T("true") || NumberString == _T("True") || NumberString == _T("TRUE"))
	{
		return 1.0l;
	}
	else if (NumberString == _T("false") || NumberString == _T("False") || NumberString == _T("FALSE"))
	{
		return 0.0l;
	}

	double dNumber = String::Parse<double>(NumberString);

	return dNumber;
}


///************************************************************************
/// <summary>
/// make the Double to string
/// </summary>
/// <param name=value>Double value</param>
/// <returns>Double string</returns>
/// <remarks>
/// none
/// </remarks>
///***********************************************************************
String Double::ToString()
{
	return String::ToString(this->m_Value);
}