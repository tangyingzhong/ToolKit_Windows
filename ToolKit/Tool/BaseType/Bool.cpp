#include "Application\PreCompile.h"
#include "Bool.h"

using namespace System::BasicType;

///************************************************************************
/// <summary>
/// Construct the Bool
/// </summary>
/// <returns></returns>
/// <remarks>
/// none
/// </remarks>
///***********************************************************************
Bool::Bool() :m_Value(false)
{

}


///************************************************************************
/// <summary>
/// Construct the Bool with value
/// </summary>
/// <param name=value></param>
/// <returns></returns>
/// <remarks>
/// none
/// </remarks>
///***********************************************************************
Bool::Bool(bool bValue) :m_Value(bValue)
{

}


///************************************************************************
/// <summary>
/// Detructe the Bool
/// </summary>
/// <returns></returns>
/// <remarks>
/// none
/// </remarks>
///***********************************************************************
Bool::~Bool()
{

}


///************************************************************************
/// <summary>
/// Allow the object copying
/// </summary>
/// <param name=other>the other bool</param>
/// <returns></returns>
/// <remarks>
/// none
/// </remarks>
///***********************************************************************
Bool::Bool(const Bool& Another)
{
	this->SetValue(Another.GetValue());
}


///************************************************************************
/// <summary>
/// Allow the obejct assignment
/// </summary>
/// <param name=other>the other bool</param>
/// <returns>reference of bool</returns>
/// <remarks>
/// none
/// </remarks>
///***********************************************************************
Bool& Bool::operator=(const Bool& Another)
{
	if (this != &Another)
	{
		this->SetValue(Another.GetValue());
	}

	return *this;
}


///************************************************************************
/// <summary>
/// Get the opposite result
/// </summary>
/// <returns>bool</returns>
/// <remarks>
/// none
/// </remarks>
///***********************************************************************
Bool Bool::operator!()
{
	return (!this->GetValue());
}


///************************************************************************
/// <summary>
/// Wether they are eqauled or not
/// </summary>
/// <param name=other>the other bool</param>
/// <returns>bool</returns>
/// <remarks>
/// none
/// </remarks>
///***********************************************************************
Bool Bool::operator==(const Bool& Another)
{
	System::Boolean bEqual = false;

	if (this->GetValue() == Another.GetValue())
	{
		bEqual = true;
	}

	return bEqual;
}


///************************************************************************
/// <summary>
/// Wether they are eqauled or not
/// </summary>
/// <param name=other>bool value</param>
/// <returns>bool</returns>
/// <remarks>
/// none
/// </remarks>
///***********************************************************************
Bool Bool::operator==(const bool bValue)
{
	System::Boolean bEqual = false;

	if (this->GetValue() == bValue)
	{
		bEqual = true;
	}

	return bEqual;
}


///************************************************************************
/// <summary>
/// Wether they are eqauled or not
/// </summary>
/// <param name=other>the other bool</param>
/// <returns>bool</returns>
/// <remarks>
/// none
/// </remarks>
///***********************************************************************
Bool Bool::operator!=(const Bool& Another)
{
	System::Boolean bEqual = false;

	if (this->GetValue() != Another.GetValue())
	{
		bEqual = true;
	}

	return bEqual;
}


///************************************************************************
/// <summary>
///Wether they are eqauled or not
/// </summary>
/// <param name=other>bool value</param>
/// <returns>bool</returns>
/// <remarks>
/// none
/// </remarks>
///***********************************************************************
Bool Bool::operator!=(const bool bValue)
{
	System::Boolean bEqual = false;

	if (this->GetValue() != bValue)
	{
		bEqual = true;
	}

	return bEqual;
}


///************************************************************************
/// <summary>
/// Override the bool type
/// </summary>
/// <returns> </returns>
/// <remarks>
/// none
/// </remarks>
///***********************************************************************
Bool::operator bool() const
{
	return this->GetValue();
}


///************************************************************************
/// <summary>
/// Parse the "true" or "false" to bool
/// </summary>
/// <param name=BoolString>bool string</param>
/// <returns>bool value</returns>
/// <remarks>
/// none
/// </remarks>
///***********************************************************************
Bool Bool::Parse(String& BoolString)
{
	System::Boolean bResult = false;

	if (BoolString == _T("true") || BoolString == _T("True") || BoolString == _T("TRUE"))
	{
		bResult = true;
	}
	else if (BoolString == _T("false") || BoolString == _T("False") || BoolString == _T("FALSE"))
	{
		bResult = false;
	}
	else
	{
		MessageBox(NULL, _T("You should input the correct bool string like: true,True,TRUE or false,False,FALSE"), _T("ErrorTips"), 0);
	}

	return bResult;
}


///************************************************************************
/// <summary>
/// Bool value converts to be string
/// </summary>
/// <returns>string</returns>
/// <remarks>
/// none
/// </remarks>
///***********************************************************************
String Bool::ToString()
{
	if (this->GetValue() == true)
	{
		return _T("true");
	}

	return _T("false");
}