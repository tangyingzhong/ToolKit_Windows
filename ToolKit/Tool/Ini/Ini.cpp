#include "Ini.h"

// Construct the Ini
Ini::Ini(String strIniFilePath):
	m_strIniFilePath(strIniFilePath),
	m_strErrorText(String("")),
	m_bDisposed(false)
{

}

// Detructe the Ini
Ini::~Ini()
{
	if (!GetDisposed())
	{
		SetDisposed(true);
	}
}

// Get error message
String Ini::GetErrorMsg()
{
	return GetErrorText();
}

// Get key's value
Boolean Ini::GetValue(String strAppName, String strKey, String& strDefaultValue)
{
	if (strAppName.IsEmpty())
	{
		SetErrorText(String("App name is empty !"));

		return false;
	}

	if (strKey.IsEmpty())
	{
		SetErrorText(String("Key name is empty !"));

		return false;
	}

	if (GetIniFilePath().IsEmpty())
	{
		SetErrorText(String("You must configure the file path at first !"));

		return false;
	}

	Character Buffer[1024] = { 0 };

	// It is no need to verify its return
	::GetPrivateProfileString(strAppName.CStr(), 
		strKey.CStr(), 
		NULL ,
		Buffer, 
		1024,
		GetIniFilePath().CStr());

	strDefaultValue = Buffer;

	return true;
}

// Set key's value
Boolean Ini::SetValue(String strAppName, String strKey, String strValue)
{
	if (strAppName.IsEmpty())
	{
		SetErrorText(String("App name is empty !"));

		return false;
	}

	if (strKey.IsEmpty())
	{
		SetErrorText(String("Key name is empty !"));

		return false;
	}

	if (GetIniFilePath().IsEmpty())
	{
		SetErrorText(String("You must configure the file path at first !"));

		return false;
	}

	// It is no need to verify its return
	::WritePrivateProfileString(strAppName.CStr(), 
		strKey.CStr(), 
		strValue.CStr(),
		GetIniFilePath().CStr());

	return true;
}

// Get key's value
Boolean Ini::GetKeyValue(String strAppName, String strKey, String& strDefaultValue)
{
	return GetValue(strAppName, strKey, strDefaultValue);
}

// Get key's value
Boolean Ini::GetKeyValue(String strAppName, String strKey, Int& iDefaultValue)
{
	String strValue;

	if (!GetKeyValue(strAppName, strKey, strValue))
	{
		return false;
	}

	iDefaultValue = Int::Parse(strValue);

	return true;
}

// Get key's value
Boolean Ini::GetKeyValue(String strAppName, String strKey, Double& dDefaultValue)
{
	String strValue;

	if (!GetKeyValue(strAppName, strKey, strValue))
	{
		return false;
	}

	dDefaultValue = Double::Parse(strValue);

	return true;
}

// Get key's value
Boolean Ini::GetKeyValue(String strAppName, String strKey, Bool& bDefaultValue)
{
	String strValue;

	if (!GetKeyValue(strAppName, strKey, strValue))
	{
		return false;
	}

	bDefaultValue = Bool::Parse(strValue);

	return true;
}

// Set key's value
Boolean Ini::SetKeyValue(String strAppName, String strKey, String strValue)
{
	return SetValue(strAppName, strKey, strValue);
}

// Set key's value
Boolean Ini::SetKeyValue(String strAppName, String strKey, Int iValue)
{
	String strValue = iValue.ToString();

	return SetKeyValue(strAppName, strKey, strValue);
}

// Set key's value
Boolean Ini::SetKeyValue(String strAppName, String strKey, Double dValue)
{
	String strValue = dValue.ToString();

	return SetKeyValue(strAppName, strKey, strValue);
}

// Set key's value
Boolean Ini::SetKeyValue(String strAppName, String strKey, Bool bValue)
{
	String strValue = bValue.ToString();

	return SetKeyValue(strAppName, strKey, strValue);
}
