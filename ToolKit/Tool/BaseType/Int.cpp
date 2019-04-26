#include "Application\PreCompile.h"
#include "Int.h"

using namespace System::BasicType;

///************************************************************************
/// <summary>
/// Contruct a int 
/// </summary>
/// <returns></returns>
/// <remarks>
/// none
/// </remarks>
///***********************************************************************
Int::Int() :m_Value(0)
{

}


///************************************************************************
/// <summary>
/// Contruct a int with a GetValue 
/// </summary>
/// <param name=v>initialize the Int with a GetValue</param>
/// <returns></returns>
/// <remarks>
/// none
/// </remarks>
///***********************************************************************
Int::Int(int iGetValue) :m_Value(iGetValue)
{

}

///************************************************************************
/// <summary>
/// Destruct the int
/// </summary>
/// <returns></returns>
/// <remarks>
/// none
/// </remarks>
///***********************************************************************
Int::~Int()
{

}


///************************************************************************
/// <summary>
/// Copy Int
/// </summary>
/// <param name=Another></param>
/// <returns></returns>
/// <remarks>
/// none
/// </remarks>
///***********************************************************************
Int::Int(const Int& Another)
{
	this->SetValue(Another.GetValue());
}


///************************************************************************
/// <summary>
/// Asiigment of Int
/// </summary>
/// <param name=Another></param>
/// <returns></returns>
/// <remarks>
/// none
/// </remarks>
///***********************************************************************
Int& Int::operator=(const Int& Another)
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
/// <param name=Another>Object of Int</param>
/// <returns>The result of +</returns>
/// <remarks>
/// none
/// </remarks>
///***********************************************************************
Int Int::operator+(Int& Another)
{
	return (this->GetValue() + Another.GetValue());
}


///************************************************************************
/// <summary>
/// Implement the + GetValue
/// </summary>
/// <param name=GetValue>A GetValue</param>
/// <returns>The Object</returns>
/// <remarks>
/// 
/// </remarks>
///***********************************************************************
Int Int::operator+(int iValue)
{
	return (this->GetValue() + iValue);
}


///************************************************************************
/// <summary>
/// Implement the += object
/// </summary>
/// <param name=Another></param>
/// <returns></returns>
/// <remarks>
/// none
/// </remarks>
///***********************************************************************
Int Int::operator+=(Int& Another)
{
	return (this->m_Value += Another.GetValue());
}


///************************************************************************
/// <summary>
/// Implement the += GetValue
/// </summary>
/// <param name=GetValue></param>
/// <returns></returns>
/// <remarks>
/// none
/// </remarks>
///***********************************************************************
Int Int::operator+=(int iValue)
{
	return (this->m_Value += iValue);
}


///************************************************************************
/// <summary>
/// Implement the -= object
/// </summary>
/// <param name=Another></param>
/// <returns></returns>
/// <remarks>
/// none
/// </remarks>
///************************************************************************
Int Int::operator-=(Int& Another)
{
	return (this->m_Value -= Another.GetValue());
}


///************************************************************************
/// <summary>
/// Implement the -= GetValue
/// </summary>
/// <param name=GetValue></param>
/// <returns></returns>
/// <remarks>
/// none
/// </remarks>
///************************************************************************
Int Int::operator-=(int iValue)
{
	return (this->m_Value -= iValue);
}


///************************************************************************
/// <summary>
/// Implement the - object
/// </summary>
/// <param name=Another>Object of Int</param>
/// <returns>The Int Object</returns>
/// <remarks>
/// 
/// </remarks>
///***********************************************************************
Int Int::operator-(Int& Another)
{
	return (this->GetValue() - Another.GetValue());
}


///************************************************************************
/// <summary>
/// Implement the - GetValue
/// </summary>
/// <param name=GetValue>A GetValue</param>
/// <returns>The Int Object</returns>
/// <remarks>
/// 
/// </remarks>
///***********************************************************************
Int Int::operator-(int iValue)
{
	return (this->GetValue() - iValue);
}


///************************************************************************
/// <summary>
/// Implement the * object
/// </summary>
/// <param name=Another>An Object of Int</param>
/// <returns>Object of Int</returns>
/// <remarks>
/// 
/// </remarks>
///***********************************************************************
Int Int::operator*(Int& Another)
{
	return (this->GetValue()*Another.GetValue());
}


///************************************************************************
/// <summary>
/// Implement the * GetValue
/// </summary>
/// <param name=GetValue>A GetValue</param>
/// <returns>The Int Object</returns>
/// <remarks>
/// 
/// </remarks>
///***********************************************************************
Int Int::operator*(int iValue)
{
	return (this->GetValue()*iValue);
}


///************************************************************************
/// <summary>
/// Implement the / object
/// </summary>
/// <param name=Another>An Object</param>
/// <returns>The Int Object</returns>
/// <remarks>
/// 
/// </remarks>
///***********************************************************************
Int Int::operator/(Int& Another)
{
	if (Another.GetValue() == 0)
	{
		return -1;
	}

	return (this->GetValue() / Another.GetValue());
}


///************************************************************************
/// <summary>
/// Implement the / GetValue
/// </summary>
/// <param name=GetValue>A GetValue</param>
/// <returns>The Int Object</returns>
/// <remarks>
/// 
/// </remarks>
///***********************************************************************
Int Int::operator/(int iValue)
{
	if (iValue == 0)
	{
		return -1;
	}

	return (this->GetValue() / iValue);
}


///************************************************************************
/// <summary>
/// Implement the % object
/// </summary>
/// <param name=Another>An Object</param>
/// <returns>The Object of Int</returns>
/// <remarks>
/// 
/// </remarks>
///***********************************************************************
Int Int::operator%(Int& Another)
{
	return ((this->GetValue()) % (Another.GetValue()));
}


///************************************************************************
/// <summary>
/// Implement the % GetValue
/// </summary>
/// <param name=GetValue>A GetValue</param>
/// <returns>Int Object</returns>
/// <remarks>
/// 
/// </remarks>
///***********************************************************************
Int Int::operator%(int iValue)
{
	return (this->GetValue() % iValue);
}


///************************************************************************
/// <summary>
/// Implement the == object
/// </summary>
/// <param name=Another>the Another object</param>
/// <returns>false£ºnot equal true£ºequal</returns>
/// <remarks>
/// none
/// </remarks>
///***********************************************************************
Int::BOOL Int::operator==(Int& Another)
{
	BOOL bEqual = false;

	if (this->GetValue() == Another.GetValue())
	{
		bEqual = true;
	}

	return bEqual;
}


///************************************************************************
/// <summary>
/// Implement the % GetValue
/// </summary>
/// <param name=GetValue>int GetValue</param>
/// <returns>false£ºnot equal true£ºequal</returns>
/// <remarks>
/// none
/// </remarks>
///***********************************************************************
Int::BOOL Int::operator==(int iValue)
{
	BOOL bEqual = false;

	if (this->GetValue() == iValue)
	{
		bEqual = true;
	}

	return bEqual;
}


///************************************************************************
/// <summary>
/// Implement the != object
/// </summary>
/// <param name=Another>the Another object</param>
/// <returns>false£ºequal true£ºnot equal</returns>
/// <remarks>
/// none
/// </remarks>
///***********************************************************************
Int::BOOL Int::operator!=(Int& Another)
{
	BOOL bEqual = false;

	if (this->GetValue() != Another.GetValue())
	{
		bEqual = true;
	}

	return bEqual;
}


///************************************************************************
/// <summary>
/// Implement the % GetValue
/// </summary>
/// <param name=GetValue>int GetValue</param>
/// <returns>false£ºequal true£ºnot equal</returns>
/// <remarks>
/// none
/// </remarks>
///***********************************************************************
Int::BOOL Int::operator!=(int iValue)
{
	BOOL bEqual = false;

	if (this->GetValue() != iValue)
	{
		bEqual = true;
	}

	return bEqual;
}


///************************************************************************
/// <summary>
/// Implement the << object
/// </summary>
/// <param name=Another>the Another object</param>
/// <returns>reference int </returns>
/// <remarks>
/// none
/// </remarks>
///***********************************************************************
Int Int::operator << (Int& Another)
{
	return (this->m_Value << Another.GetValue());
}


///************************************************************************
/// <summary>
/// Implement the << GetValue
/// </summary>
/// <param name=GetValue>int GetValue</param>
/// <returns>reference int</returns>
/// <remarks>
/// none
/// </remarks>
///***********************************************************************
Int Int::operator<<(int iValue)
{
	return (this->m_Value << iValue);
}


///************************************************************************
/// <summary>
/// Implement the >> object
/// </summary>
/// <param name=Another>the Another object</param>
/// <returns>reference int</returns>
/// <remarks>
/// none
/// </remarks>
///***********************************************************************
Int Int::operator >> (Int& Another)
{
	return (this->m_Value >> Another.GetValue());
}


///************************************************************************
/// <summary>
/// Implement the >> GetValue
/// </summary>
/// <param name=GetValue>int GetValue</param>
/// <returns>reference int</returns>
/// <remarks>
/// none
/// </remarks>
///***********************************************************************
Int Int::operator >> (int iValue)
{
	return (this->m_Value >> iValue);
}


///************************************************************************
/// <summary>
/// Implement the ! object
/// </summary>
/// <returns>reference int</returns>
/// <remarks>
/// none
/// </remarks>
///***********************************************************************
Int::BOOL Int::operator!()
{
	return (!this->GetValue());
}


///************************************************************************
/// <summary>
/// Implement the object++ 
/// </summary>
/// <returns>reference of Int</returns>
/// <remarks>
/// this is a++
/// </remarks>
///***********************************************************************
Int& Int::operator++()
{
	(this->m_Value)++;

	return *this;
}


///************************************************************************
/// <summary>
/// Implement the ++object
/// </summary>
/// <param name=></param>
/// <returns>reference of Int</returns>
/// <remarks>
/// this is ++a
/// </remarks>
///***********************************************************************
Int& Int::operator++(int)
{
	++(this->m_Value);

	return *this;
}


///************************************************************************
/// <summary>
/// Implement the >object
/// </summary>
/// <param name=Another>the Another object</param>
/// <returns>false£º<=   true£º></returns>
/// <remarks>
/// none
/// </remarks>
///***********************************************************************
Int::BOOL Int::operator>(Int& Another)
{
	BOOL bOK = false;

	if (this->GetValue() > Another.GetValue())
	{
		bOK = true;
	}

	return bOK;
}


///************************************************************************
/// <summary>
/// Implement the > GetValue
/// </summary>
/// <param name=Another>int GetValue</param>
/// <returns>false£º<=   true£º></returns>
/// <remarks>
/// none
/// </remarks>
///***********************************************************************
Int::BOOL Int::operator>(int iValue)
{
	BOOL bOK = false;

	if (this->GetValue() > iValue)
	{
		bOK = true;
	}

	return bOK;
}


///************************************************************************
/// <summary>
/// Implement the >=object
/// </summary>
/// <param name=Another>the Another obeject</param>
/// <returns>false£º<   true£º>= </returns>
/// <remarks>
/// none
/// </remarks>
///***********************************************************************
Int::BOOL Int::operator>=(Int& Another)
{
	BOOL bOK = false;

	if (this->GetValue() >= Another.GetValue())
	{
		bOK = true;
	}

	return bOK;
}


///************************************************************************
/// <summary>
/// Implement the >= GetValue
/// </summary>
/// <param name=Another>int GetValue</param>
/// <returns>false£º<   true£º>= </returns>
/// <remarks>
/// none
/// </remarks>
///***********************************************************************
Int::BOOL Int::operator>=(int iValue)
{
	BOOL bOK = false;

	if (this->GetValue() >= iValue)
	{
		bOK = true;
	}

	return bOK;
}


///************************************************************************
/// <summary>
/// Implement the <object
/// </summary>
/// <param name=Another>the Another object</param>
/// <returns>false£º>=   true£º< </returns>
/// <remarks>
/// none
/// </remarks>
///***********************************************************************
Int::BOOL Int::operator<(Int& Another)
{
	BOOL bOK = false;

	if (this->GetValue() < Another.GetValue())
	{
		bOK = true;
	}

	return bOK;
}


///************************************************************************
/// <summary>
/// Implement the < GetValue
/// </summary>
/// <param name=Another>int GetValue</param>
/// <returns>false£º>=   true£º< </returns>
/// <remarks>
/// none
/// </remarks>
///***********************************************************************
Int::BOOL Int::operator<(int iValue)
{
	BOOL bOK = false;

	if (this->GetValue() < iValue)
	{
		bOK = true;
	}

	return bOK;
}


///************************************************************************
/// <summary>
/// Implement the <=object
/// </summary>
/// <param name=Another>the Another object</param>
/// <returns>false£º>   true£º<= </returns>
/// <remarks>
/// none
/// </remarks>
///***********************************************************************
Int::BOOL Int::operator<=(Int& Another)
{
	BOOL bOK = false;

	if (this->GetValue() <= Another.GetValue())
	{
		bOK = true;
	}

	return bOK;
}


///************************************************************************
/// <summary>
/// Implement the < GetValue
/// </summary>
/// <param name=Another>int GetValue</param>
/// <returns>false£º>   true£º<= </returns>
/// <remarks>
/// none
/// </remarks>
///***********************************************************************
Int::BOOL Int::operator<=(int iValue)
{
	BOOL bOK = false;

	if (this->GetValue() <= iValue)
	{
		bOK = true;
	}

	return bOK;
}


///************************************************************************
/// <summary>
/// Override the int type
/// </summary>
/// <returns></returns>
/// <remarks>
/// none
/// </remarks>
///***********************************************************************
Int::operator int() const
{
	return this->GetValue();
}


///************************************************************************
/// <summary>
/// Parse the string to int
/// </summary>
/// <param name=str>the string</param>
/// <returns>int GetValue</returns>
/// <remarks>
/// none
/// </remarks>
///***********************************************************************
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


///************************************************************************
/// <summary>
/// make the int to string
/// </summary>
/// <param name=GetValue>int GetValue</param>
/// <returns>a string</returns>
/// <remarks>
/// 
/// </remarks>
///***********************************************************************
String Int::ToString()
{
	return String::ToString(this->m_Value);
}