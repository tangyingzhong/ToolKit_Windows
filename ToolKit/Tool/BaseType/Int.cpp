#include <iostream>
#include "Tool/Common/SystemType.h"
#include "Int.h"

using namespace System::BasicType;

// Contruct a int 
Int::Int() :m_Value(0)
{

}

// Contruct a int with a GetValue 
Int::Int(int iGetValue) :m_Value(iGetValue)
{

}

// Destruct the int
Int::~Int()
{

}

// Copy Int
Int::Int(const Int& Another)
{
	SetValue(Another.GetValue());
}

// Asiigment of Int
Int& Int::operator=(const Int& Another)
{
	if (this != &Another)
	{
		SetValue(Another.GetValue());
	}

	return *this;
}

// Implement the + object
Int Int::operator+(Int& Another)
{
	return (GetValue() + Another.GetValue());
}

// Implement the + GetValue
Int Int::operator+(int iValue)
{
	return (GetValue() + iValue);
}

// Implement the += object
Int Int::operator+=(Int& Another)
{
	return (m_Value += Another.GetValue());
}

// Implement the += GetValue
Int Int::operator+=(int iValue)
{
	return (m_Value += iValue);
}

// Implement the -= object
Int Int::operator-=(Int& Another)
{
	return (m_Value -= Another.GetValue());
}

// Implement the -= GetValue
Int Int::operator-=(int iValue)
{
	return (m_Value -= iValue);
}

// Implement the - object
Int Int::operator-(Int& Another)
{
	return (GetValue() - Another.GetValue());
}

// Implement the - GetValue
Int Int::operator-(int iValue)
{
	return (GetValue() - iValue);
}

// Implement the * object
Int Int::operator*(Int& Another)
{
	return (GetValue()*Another.GetValue());
}

// Implement the * GetValue
Int Int::operator*(int iValue)
{
	return (GetValue()*iValue);
}

// Implement the / object
Int Int::operator/(Int& Another)
{
	if (Another.GetValue() == 0)
	{
		std::cerr << "Divider can't be 0" << std::endl;
	
		return -1;
	}

	return (GetValue() / Another.GetValue());
}

// Implement the / GetValue
Int Int::operator/(int iValue)
{
	if (iValue == 0)
	{
		std::cerr << "Divider can't be 0" << std::endl;

		return -1;
	}

	return (GetValue() / iValue);
}

// Implement the % object
Int Int::operator%(Int& Another)
{
	return ((GetValue()) % (Another.GetValue()));
}

// Implement the % GetValue
Int Int::operator%(int iValue)
{
	return (GetValue() % iValue);
}

// Equal to another one
Int::BOOL Int::Equal(Int Another)
{
	BOOL bEqual = false;

	if (GetValue() == Another.GetValue())
	{
		bEqual = true;
	}

	return bEqual;
}

// Implement the == object
Int::BOOL Int::operator==(Int& Another)
{
	return Equal(Another);
}

// Implement the % GetValue
Int::BOOL Int::operator==(int iValue)
{
	return Equal(iValue);
}

// Implement the != object
Int::BOOL Int::operator!=(Int& Another)
{
	return !Equal(Another);
}

// Implement the % GetValue
Int::BOOL Int::operator!=(int iValue)
{
	return !Equal(iValue);
}

// Implement the << object
Int Int::operator << (Int& Another)
{
	return (m_Value << Another.GetValue());
}

// Implement the << GetValue
Int Int::operator<<(int iValue)
{
	return (m_Value << iValue);
}

// Implement the >> object
Int Int::operator >> (Int& Another)
{
	return (m_Value >> Another.GetValue());
}

// Implement the >> GetValue
Int Int::operator >> (int iValue)
{
	return (m_Value >> iValue);
}

// Implement the ! object
Int::BOOL Int::operator!()
{
	return (!GetValue());
}

// Implement the object++ 
Int& Int::operator++()
{
	++(m_Value);

	return *this;
}

// Implement the ++object
Int Int::operator++(int)
{
	Int temp = *this;

	(m_Value)++;

	return temp;
}

// Implement the >object
Int::BOOL Int::operator>(Int& Another)
{
	BOOL bOK = false;

	if (GetValue() > Another.GetValue())
	{
		bOK = true;
	}

	return bOK;
}

// Implement the > GetValue
Int::BOOL Int::operator>(int iValue)
{
	BOOL bOK = false;

	if (GetValue() > iValue)
	{
		bOK = true;
	}

	return bOK;
}

// Implement the >=object
Int::BOOL Int::operator>=(Int& Another)
{
	BOOL bOK = false;

	if (GetValue() >= Another.GetValue())
	{
		bOK = true;
	}

	return bOK;
}

// Implement the >= GetValue
Int::BOOL Int::operator>=(int iValue)
{
	BOOL bOK = false;

	if (GetValue() >= iValue)
	{
		bOK = true;
	}

	return bOK;
}

// Implement the <object
Int::BOOL Int::operator<(Int& Another)
{
	BOOL bOK = false;

	if (GetValue() < Another.GetValue())
	{
		bOK = true;
	}

	return bOK;
}

// Implement the < GetValue
Int::BOOL Int::operator<(int iValue)
{
	BOOL bOK = false;

	if (GetValue() < iValue)
	{
		bOK = true;
	}

	return bOK;
}

// Implement the <=object
Int::BOOL Int::operator<=(Int& Another)
{
	BOOL bOK = false;

	if (GetValue() <= Another.GetValue())
	{
		bOK = true;
	}

	return bOK;
}

// Implement the < GetValue
Int::BOOL Int::operator<=(int iValue)
{
	BOOL bOK = false;

	if (GetValue() <= iValue)
	{
		bOK = true;
	}

	return bOK;
}

// Override the int type
Int::operator int() const
{
	return GetValue();
}

// Parse the string to int
Int Int::Parse(String NumberString)
{
	if (NumberString == _T("true") || NumberString == _T("True") || NumberString == _T("TRUE"))
	{
		return 1;
	}
	else if (NumberString == _T("false") || NumberString == _T("False") || NumberString == _T("FALSE"))
	{
		return 0;
	}

	int iNumber = String::Parse<int>(NumberString);

	return iNumber;
}

// make the int to string
String Int::ToString()
{
	return String::ToString(m_Value);
}