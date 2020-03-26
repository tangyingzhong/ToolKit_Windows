#include "Double.h"

using namespace System::BasicType;

// Contruct a Double 
Double::Double() :m_Value(0.0l)
{

}

// Contruct a Double with a value 
Double::Double(double dValue) :m_Value(dValue)
{

}

// Destruct the Double
Double::~Double()
{

}

// Allow the object copying
Double::Double(const Double& Another)
{
	SetValue(Another.GetValue());
}

// Allow the obejct assignment
Double& Double::operator=(const Double& Another)
{
	if (this != &Another)
	{
		SetValue(Another.GetValue());
	}

	return *this;
}

// Implement the + object
Double Double::operator+(Double& Another)
{
	return (GetValue() + Another.GetValue());
}

// Implement the + value
Double Double::operator+(double dValue)
{
	return (GetValue() + dValue);
}

// Implement the += object
Double Double::operator+=(Double& Another)
{
	return (m_Value += Another.GetValue());
}

// Implement the += value
Double Double::operator+=(double dValue)
{
	return (m_Value += dValue);
}

// Implement the -= object
Double Double::operator-=(Double& Another)
{
	return (m_Value -= Another.GetValue());
}

// Implement the -= value
Double Double::operator-=(double dValue)
{
	return (m_Value -= dValue);
}

// Implement the - object
Double Double::operator-(Double& Another)
{
	return (m_Value - Another.GetValue());
}

// Implement the - value
Double Double::operator-(double dValue)
{
	return (m_Value - dValue);
}

// Implement the * object
Double Double::operator*(Double& Another)
{
	return (m_Value * Another.GetValue());
}

// Implement the * value
Double Double::operator*(double dValue)
{
	return (m_Value * dValue);
}

// Implement the / object
Double Double::operator/(Double& Another)
{
	return (m_Value / Another.GetValue());
}

// Implement the / value
Double Double::operator/(double dValue)
{
	return (m_Value / dValue);
}

// Override the double type
Double::operator double() const
{
	return GetValue();
}

// Parse the string to double
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

// make the Double to string
String Double::ToString()
{
	return String::ToString(m_Value);
}