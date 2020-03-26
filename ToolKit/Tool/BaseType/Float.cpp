#include "Float.h"

using namespace System::BasicType;

// Contruct a Float
Float::Float() :m_Value(0.0f)
{

}

// Contruct a Float with a value 
Float::Float(float dValue) :m_Value(dValue)
{

}

// Destruct the Float
Float::~Float()
{

}

// Allow the object copying
Float::Float(const Float& Another)
{
	SetValue(Another.GetValue());
}

// Allow the obejct assignment
Float& Float::operator=(const Float& Another)
{
	if (this != &Another)
	{
		SetValue(Another.GetValue());
	}

	return *this;
}

// Implement the + object
Float Float::operator+(Float& Another)
{
	return (GetValue() + Another.GetValue());
}

// Implement the + value
Float Float::operator+(float dValue)
{
	return (GetValue() + dValue);
}

// Implement the += object
Float Float::operator+=(Float& Another)
{
	return (m_Value += Another.GetValue());
}

// Implement the += value
Float Float::operator+=(float dValue)
{
	return (m_Value += dValue);
}

// Implement the -= object
Float Float::operator-=(Float& Another)
{
	return (m_Value -= Another.GetValue());
}

// Implement the -= value
Float Float::operator-=(float dValue)
{
	return (m_Value -= dValue);
}

// Implement the - object
Float Float::operator-(Float& Another)
{
	return (m_Value - Another.GetValue());
}

// Implement the - value
Float Float::operator-(float dValue)
{
	return (m_Value - dValue);
}

// Implement the * object
Float Float::operator*(Float& Another)
{
	return (m_Value * Another.GetValue());
}

// Implement the * value
Float Float::operator*(float dValue)
{
	return (m_Value * dValue);
}

// Implement the / object
Float Float::operator/(Float& Another)
{
	return (m_Value / Another.GetValue());
}

// Implement the / value
Float Float::operator/(float dValue)
{
	return (m_Value / dValue);
}

// Override the float type
Float::operator float() const
{
	return GetValue();
}

// Parse the string to Float
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

// make the Float to string
String Float::ToString()
{
	return String::ToString(m_Value);
}