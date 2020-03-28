#include <iostream>
#include "Bool.h"

using namespace System::BasicType;

// Construct the Bool
Bool::Bool() :m_Value(0)
{

}

// Construct the Bool with value
Bool::Bool(bool bValue) :m_Value(bValue)
{

}

// Detructe the Bool
Bool::~Bool()
{

}

// Allow the object copying
Bool::Bool(const Bool& Another)
{
	SetValue(Another.GetValue());
}

// Allow the obejct assignment
Bool& Bool::operator=(const Bool& Another)
{
	if (this != &Another)
	{
		SetValue(Another.GetValue());
	}

	return *this;
}

// Get the opposite result
Bool Bool::operator!()
{
	return (!GetValue());
}

// Equal to another one
Bool Bool::Equal(Bool bValue)
{
	bool bEqual = false;

	if (GetValue() == bValue.GetValue())
	{
		bEqual = true;
	}

	return bEqual;
}

// Wether they are eqauled or not
Bool Bool::operator==(const Bool& Another)
{
	return Equal(Another);
}

// Wether they are eqauled or not
Bool Bool::operator==(const bool bValue)
{
	return Equal(bValue);
}

// Wether they are eqauled or not
Bool Bool::operator!=(const Bool& Another)
{
	return Equal(Another);
}

//Wether they are eqauled or not
Bool Bool::operator!=(const bool bValue)
{
	return Equal(bValue);
}

// Override the bool type
Bool::operator bool() const
{
	return GetValue();
}

// Parse the "true" or "false" to bool
Bool Bool::Parse(String& BoolString)
{
	bool bResult = false;

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
		std::cerr << "You should input the correct bool string like: true,True,TRUE or false,False,FALSE" << std::endl;
	}

	return bResult;
}

// Bool value converts to be string
String Bool::ToString()
{
	if (GetValue() == true)
	{
		return _T("true");
	}

	return _T("false");
}