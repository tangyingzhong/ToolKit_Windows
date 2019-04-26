#include "Application\PreCompile.h"
#include "Tool\Encoding\ASCII.h"
#include "Tool\Encoding\Unicode.h"
#include "String.h"

using namespace System::BasicType;

///************************************************************************
/// <summary>
/// Contruct an empty string
/// </summary>
/// <returns></returns>
/// <remarks>
/// none
/// </remarks>
///***********************************************************************
String::String() :m_Length(0), m_Disposed(false)
{
	this->Initialize(_T(""));
}


///************************************************************************
/// <summary>
/// Contruct an string with STL String
/// </summary>
/// <param name=StdString OtherStdString>std String</param>
/// <returns></returns>
/// <remarks>
/// none
/// </remarks>
///***********************************************************************
String::String(StdString& OtherStdString) :m_Length(0), m_Disposed(false)
{
	this->Initialize(OtherStdString);
}


///************************************************************************
/// <summary>
/// Contruct an string with C-type String
/// </summary>
/// <param name=pStr>C-type String</param>
/// <returns></returns>
/// <remarks>
///  none
/// </remarks>
///***********************************************************************
String::String(CharArray pString) :m_Length(0), m_Disposed(false)
{
	this->Initialize(pString);
}


///************************************************************************
/// <summary>
/// Destruct the string
/// </summary>
/// <returns></returns>
/// <remarks>
/// none
/// </remarks>
///***********************************************************************
String::~String()
{
	this->Destroy();
}


///************************************************************************
/// <summary>
/// Allow the string copying
/// </summary>
/// <param name=other>another String string</param>
/// <returns></returns>
/// <remarks>
/// none
/// </remarks>
///***********************************************************************
String::String(const String& other)
{
	this->SetStdString(other.GetStdString());
	this->SetLength(other.GetLength());
	this->m_WideArray = other.m_WideArray;
	this->SetDisposed(other.GetDisposed());
}


///************************************************************************
/// <summary>
/// Allow the obejct assignment
/// </summary>
/// <param name=other>another String string</param>
/// <returns>the refernce of current String</returns>
/// <remarks>
/// none
/// </remarks>
///***********************************************************************
String& String::operator=(const String& other)
{
	if (this != &other)
	{
		this->SetStdString(other.GetStdString());
		this->SetLength(other.GetLength());
		this->m_WideArray = other.m_WideArray;
		this->SetDisposed(other.GetDisposed());
	}

	return *this;
}


///************************************************************************
/// <summary>
/// Init the String
/// </summary>
/// <param name=StdString OtherStdString>Std String</param>
/// <returns></returns>
/// <remarks>
/// Note: it can transfer C-type String to be Std String
/// </remarks>
///***********************************************************************
String::Empty String::Initialize(StdString OtherStdString)
{
	// Set the default std String
	this->SetStdString(OtherStdString);

	// Set length of the String
	this->SetLength((Length)this->GetStdString().length());
}


///************************************************************************
/// <summary>
/// Destory the String
/// </summary>
/// <returns></returns>
/// <remarks>
/// none
/// </remarks>
///***********************************************************************
String::Empty String::Destroy()
{
	if (!this->GetDisposed())
	{
		this->SetDisposed(true);

	}
}


///************************************************************************
/// <summary>
/// Append a new std String to the String
/// </summary>
/// <param name=str>std String</param>
/// <returns>the current String</returns>
/// <remarks>
/// none
/// </remarks>
///***********************************************************************
String& String::Append(StdString& OtherStdString)
{
	// Set the std String
	this->SetStdString(this->GetStdString().append(OtherStdString));

	// Set the length
	this->SetLength((Length)this->GetStdString().length());

	return *this;
}


///************************************************************************
/// <summary>
/// Is the current String equals to the other one
/// </summary>
/// <param name=other>the other String</param>
/// <returns>false£ºnot eqaul true£ºequal</returns>
/// <remarks>
/// none
/// </remarks>
///***********************************************************************
String::BOOL String::Equal(String& OtherString)
{
	BOOL bEqual = false;

	if (this->GetStdString().compare(OtherString.GetStdString()) == 0)
	{
		bEqual = true;
	}

	return bEqual;
}


///************************************************************************
/// <summary>
/// Cohesion String to be a new String
/// </summary>
/// <param name=str>String</param>
/// <returns>current String</returns>
/// <remarks>
/// none
/// </remarks>
///***********************************************************************
String& String::operator+(String OtherString)
{
	return Append(OtherString.GetStdString());
}


///************************************************************************
/// <summary>
/// Is String equals to the other one
/// </summary>
/// <param name=other>another String</param>
/// <returns>false£ºnot equal true£ºequal</returns>
/// <remarks>
/// none
/// </remarks>
///***********************************************************************
String::BOOL String::operator==(String OtherString)
{
	BOOL bEqual = false;

	if (this->GetStdString() == OtherString.GetStdString())
	{
		bEqual = true;
	}

	return bEqual;
}


///************************************************************************
/// <summary>
/// Is String not equals to the other one
/// </summary>
/// <param name=other>another String</param>
/// <returns>false£ºequal true£ºnot equal</returns>
/// <remarks>
/// none
/// </remarks>
///***********************************************************************
String::BOOL String::operator!=(String OtherString)
{
	BOOL bEqual = false;

	if (this->GetStdString() != OtherString.GetStdString())
	{
		bEqual = true;
	}

	return bEqual;
}


///************************************************************************
/// <summary>
/// Split the String by a seperator
/// </summary>
/// <param name=ch>seperator</param>
/// <returns>a String arrray</returns>
/// <remarks>
/// none
/// </remarks>
///***********************************************************************
String::BOOL String::Split(String strSeperator, StringTable& vStringTable)
{
	BOOL bSuccess = false;

	// Set the current character's position
	Index iCurrentIndex = this->Find(strSeperator, 0);
	if (iCurrentIndex == -1)
	{
		return bSuccess;
	}

	// Loop to vector
	Index iStartIndex = 0;
	while (StdString::npos != iCurrentIndex)
	{
		// Get the splited string
		String strSplitedString = this->SubString(iStartIndex, iCurrentIndex - iStartIndex);

		// Push the subString to the vector
		vStringTable.push_back(strSplitedString);

		// Update the start position of original String
		iStartIndex = iCurrentIndex + (Index)strSeperator.GetStdString().size();

		// Set the current character's position
		iCurrentIndex = this->Find(strSeperator, iStartIndex);
	}

	// The searching is to be end
	if (iStartIndex != this->GetLength())
	{
		// Get the last splited string
		String strSplitedString = this->SubString(iStartIndex);

		// Push the subString to the vector
		vStringTable.push_back(strSplitedString);
	}

	bSuccess = true;

	return bSuccess;
}


///************************************************************************
/// <summary>
/// Sub the string to the end
/// </summary>
/// <param name=Index iStartIndex></param>
/// <returns></returns>
/// <remarks>
/// None
/// </remarks>
///***********************************************************************
String String::SubString(Index iStartIndex)
{
	if (iStartIndex < 0 || iStartIndex >= this->GetLength())
	{
		return _T("");
	}

	return this->GetStdString().substr(iStartIndex, StdString::npos);
}


///************************************************************************
/// <summary>
/// Sub the String to get a new String
/// </summary>
/// <param name=startIndex>start position</param>
/// <param name=length>distance of subbing</param>
/// <returns>A new String</returns>
/// <remarks>
/// none
/// </remarks>
///***********************************************************************
String String::SubString(Index iStartIndex, Length iSubLength)
{
	// Check the legal of the start position
	if (iStartIndex < 0 || iStartIndex >= this->GetLength())
	{
		return _T("");
	}

	// Get the left length that you can operate
	Length iLeftLength = this->GetLength() - iStartIndex;

	// Check the sub length's legal
	if (iSubLength <= 0 || iSubLength > iLeftLength)
	{
		return _T("");
	}

	return this->GetStdString().substr(iStartIndex, iSubLength);
}


///************************************************************************
/// <summary>
/// Find the last appearance character in the string and return its's position
/// </summary>
/// <param name=String SpecialStr></param>
/// <returns>Failed: -1</returns>
/// <remarks>
/// None
/// </remarks>
///***********************************************************************
String::Index String::FindLast(String strSpecialStr)
{
	return (Index)(this->GetStdString().find_last_of(strSpecialStr.GetStdString().c_str()));
}


///************************************************************************
/// <summary>
/// Find the appearance character in the string and return its's position
/// </summary>
/// <param name=Index iStartPos>Start finding position</param>
/// <param name=String SpecialStr>The string that you want to find</param>
/// <returns>Failed return -1</returns>
/// <remarks>
/// None
/// </remarks>
///***********************************************************************
String::Index String::Find(String strSpecialStr, Index iStartPos)
{
	Index iFindPos = (Index)(StdString::npos);

	if (iStartPos < 0 || iStartPos >= this->GetLength() || strSpecialStr.GetStdString() == _T(""))
	{
		return iFindPos;
	}

	iFindPos = (Index)(this->GetStdString().find(strSpecialStr.GetStdString(), iStartPos));

	return iFindPos;
}


///************************************************************************
/// <summary>
/// Replace the string by another one
/// </summary>
/// <param name=Index iReplacePos></param>
/// <param name=Length iReplaceLength></param>
/// <returns></returns>
/// <remarks>
/// Note: you can use "" to replace source string(trunc the string)
/// </remarks>
///***********************************************************************
String& String::Replace(Index iReplacePos, Length iReplaceLength, String strReplaceString)
{
	if (iReplacePos < 0 || iReplacePos >= this->GetLength())
	{
		return *this;
	}

	if (iReplaceLength <= 0)
	{
		return *this;
	}

	StdString strSource = this->GetStdString();

	strSource.replace(iReplacePos, iReplaceLength, strReplaceString.GetStdString());

	this->SetStdString(strSource);

	return *this;
}


///************************************************************************
/// <summary>
/// Get the wide string when you are in ASCII environment to program
/// </summary>
/// <returns></returns>
/// <remarks>
/// Note: you are in ASCII mode so that you need this function or it is no need.
/// </remarks>
///***********************************************************************
System::WByteArray String::AllocWideString()
{
	// Get the ASCII string at first
	std::string strAsciiString = System::Encoding::ASCII::GetString(this->GetStdString());

	// Create an ascii array 
	Array<SByte> AsciiArray((Int32)strAsciiString.length() + 1);

	// Copy the Ascii string to the Ascii buffer
	Array<SByte>::Copy((SByteArray)strAsciiString.c_str(), (Int32)strAsciiString.length(), AsciiArray, AsciiArray.Size());

	// Get the wide string from the ascii array
	std::wstring strWideString = System::Encoding::Unicode::GetString(AsciiArray, 0, AsciiArray.Size(), EncodeType::E_ASCII);

	// Resize the wide array
	this->m_WideArray.Resize((Length)strWideString.length());

	// Fill the wide array
	Array<WByte>::Copy((WByteArray)strWideString.data(), (Length)strWideString.length(), this->m_WideArray, this->m_WideArray.Size());

	return this->m_WideArray;
}


///************************************************************************
/// <summary>
/// Make string upper
/// </summary>
/// <returns></returns>
/// <remarks>
/// None
/// </remarks>
///***********************************************************************
String& String::MakeUpper()
{
	StdString strSource = this->GetStdString();

#ifdef UNICODE
	transform(strSource.begin(), strSource.end(), strSource.begin(), towupper);
#else
	transform(strSource.begin(), strSource.end(), strSource.begin(), toupper);
#endif

	this->SetStdString(strSource);

	return *this;
}


///************************************************************************
/// <summary>
/// Make string lower
/// </summary>
/// <returns></returns>
/// <remarks>
/// None
/// </remarks>
///***********************************************************************
String& String::MakeLower()
{
	StdString strSource = this->GetStdString();

#ifdef UNICODE
	transform(strSource.begin(), strSource.end(), strSource.begin(), towlower);
#else
	transform(strSource.begin(), strSource.end(), strSource.begin(), tolower);
#endif

	this->SetStdString(strSource);

	return *this;
}


///************************************************************************
/// <summary>
/// Get a character from the string at special position
/// </summary>
/// <param name=Index iPos></param>
/// <returns>Failed: 'N'</returns>
/// <remarks>
/// None
/// </remarks>
///***********************************************************************
String::Character String::operator[](Index iPos)
{
	if (iPos < 0 || iPos >= this->GetLength())
	{
		return _T('N');
	}

	return this->GetStdString().at(iPos);
}