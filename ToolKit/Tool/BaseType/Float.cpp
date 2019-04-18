#include "Application\PreCompile.h"
#include "Float.h"

using namespace System::BasicType;

///************************************************************************
/// <summary>
/// Contruct a Float 
/// </summary>
/// <returns></returns>
/// <remarks>
/// 
/// </remarks>
///***********************************************************************
Float::Float() :m_Value(0.0f)
{

}


///************************************************************************
/// <summary>
/// Contruct a Float with a value 
/// </summary>
/// <param name=v>initialize the Float with a value</param>
/// <returns></returns>
/// <remarks>
/// 
/// </remarks>
///***********************************************************************
Float::Float(float dValue) :m_Value(dValue)
{

}


///************************************************************************
/// <summary>
/// Destruct the Float
/// </summary>
/// <returns></returns>
/// <remarks>
/// none
/// </remarks>
///***********************************************************************
Float::~Float()
{

}


///************************************************************************
/// <summary>
/// Allow the object copying
/// </summary>
/// <param name=other>another Float object</param>
/// <returns></returns>
/// <remarks>
/// none
/// </remarks>
///***********************************************************************
Float::Float(const Float& Another)
{
	this->SetValue(Another.GetValue());
}


///************************************************************************
/// <summary>
/// Allow the obejct assignment
/// </summary>
/// <param name=other>another Float object</param>
/// <returns>self object</returns>
/// <remarks>
/// none
/// </remarks>
///***********************************************************************
Float& Float::operator=(const Float& Another)
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
/// <param name=other>another Float object</param>
/// <returns>a new Float object</returns>
/// <remarks>
/// none
/// </remarks>
///***********************************************************************
Float Float::operator+(Float& Another)
{
	return (this->GetValue() + Another.GetValue());
}


///************************************************************************
/// <summary>
/// Implement the + value
/// </summary>
/// <param name=value>A Float value</param>
/// <returns>a new Float object</returns>
/// <remarks>
/// none
/// </remarks>
///***********************************************************************
Float Float::operator+(float dValue)
{
	return (this->GetValue() + dValue);
}


///************************************************************************
/// <summary>
/// Implement the += object
/// </summary>
/// <param name=other>another Float object</param>
/// <returns>a new Float object</returns>
/// <remarks>
/// none
/// </remarks>
///***********************************************************************
Float Float::operator+=(Float& Another)
{
	return (this->m_Value += Another.GetValue());
}


///************************************************************************
/// <summary>
/// Implement the += value
/// </summary>
/// <param name=value>a Float value</param>
/// <returns>a new Float object</returns>
/// <remarks>
/// none
/// </remarks>
///***********************************************************************
Float Float::operator+=(float dValue)
{
	return (this->m_Value += dValue);
}


///************************************************************************
/// <summary>
/// Implement the -= object
/// </summary>
/// <param name=other>another Float object</param>
/// <returns>a new Float object</returns>
/// <remarks>
/// none
/// </remarks>
///************************************************************************
Float Float::operator-=(Float& Another)
{
	return (this->m_Value -= Another.GetValue());
}


///************************************************************************
/// <summary>
/// Implement the -= value
/// </summary>
/// <param name=value>a Float value</param>
/// <returns>a new Float object</returns>
/// <remarks>
/// none
/// </remarks>
///************************************************************************
Float Float::operator-=(float dValue)
{
	return (this->m_Value -= dValue);
}


///************************************************************************
/// <summary>
/// Implement the - object
/// </summary>
/// <param name=other>another Float object</param>
/// <returns>a new Float object</returns>
/// <remarks>
/// none
/// </remarks>
///***********************************************************************
Float Float::operator-(Float& Another)
{
	return (this->m_Value - Another.GetValue());
}


///************************************************************************
/// <summary>
/// Implement the - value
/// </summary>
/// <param name=value>A Float value</param>
/// <returns>a new Float object</returns>
/// <remarks>
/// none
/// </remarks>
///***********************************************************************
Float Float::operator-(float dValue)
{
	return (this->m_Value - dValue);
}


///************************************************************************
/// <summary>
/// Implement the * object
/// </summary>
/// <param name=other>another Float object</param>
/// <returns>a new Float object</returns>
/// <remarks>
/// none
/// </remarks>
///***********************************************************************
Float Float::operator*(Float& Another)
{
	return (this->m_Value * Another.GetValue());
}


///************************************************************************
/// <summary>
/// Implement the * value
/// </summary>
/// <param name=value>A Float value</param>
/// <returns>a new Float object</returns>
/// <remarks>
/// none
/// </remarks>
///***********************************************************************
Float Float::operator*(float dValue)
{
	return (this->m_Value * dValue);
}


///************************************************************************
/// <summary>
/// Implement the / object
/// </summary>
/// <param name=other>another Float object</param>
/// <returns>a new Float object</returns>
/// <remarks>
/// none
/// </remarks>
///***********************************************************************
Float Float::operator/(Float& Another)
{
	return (this->m_Value / Another.GetValue());
}


///************************************************************************
/// <summary>
/// Implement the / value
/// </summary>
/// <param name=value>A Float value</param>
/// <returns>a new Float object</returns>
/// <remarks>
/// none
/// </remarks>
///***********************************************************************
Float Float::operator/(float dValue)
{
	return (this->m_Value / dValue);
}


///************************************************************************
/// <summary>
/// Override the float type
/// </summary>
/// <returns> </returns>
/// <remarks>
/// none
/// </remarks>
///***********************************************************************
Float::operator float() const
{
	return this->GetValue();
}


///************************************************************************
/// <summary>
/// Parse the string to Float
/// </summary>
/// <param name=FloatString>Float string</param>
/// <returns>a new Float object</returns>
/// <remarks>
/// none
/// </remarks>
///***********************************************************************
Float Float::Parse(String NumberString)
{
	if (NumberString == _T("true") || NumberString == _T("True") || NumberString == _T("TRUE"))
	{
		return 1.0f;
	}
	else if (NumberString == _T("false") || NumberString == _T("False") || NumberString == _T("FALSE"))
	{
		return 0.0f;
	}

	float fNumber = String::Parse<float>(NumberString);

	return fNumber;
}


///************************************************************************
/// <summary>
/// make the Float to string
/// </summary>
/// <param name=value>Float value</param>
/// <returns>a string</returns>
/// <remarks>
/// none
/// </remarks>
///***********************************************************************
String Float::ToString()
{
	return String::ToString(this->m_Value);
}