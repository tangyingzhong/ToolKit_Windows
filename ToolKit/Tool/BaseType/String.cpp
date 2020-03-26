#include <Shlobj.h>
#include <algorithm>
#include <string>
#include "Tool/Encoding/ANSI.h"
#include "Tool/Encoding/Unicode.h"
#include "Tool/Encoding/UTF8.h"
#include "String.h"

using namespace System::Encoding;
using namespace System::BasicType;

#ifdef UNICODE
// Construct the string auto from ansi string
String::String(const std::string strAnsiString) :m_Length(0), m_pCArray(NULL), m_Disposed(false)
{
	std::wstring strFinal = Unicode::GetString(strAnsiString, ENCODE_ANSI);

	Initialize(strFinal);
}
#else
// Construct the string auto from wide string from ansi string
String::String(const std::wstring strWString):m_Length(0), m_pCArray(NULL), m_Disposed(false)
{
	std::string strAnsi=ANSI::GetString(strWString,ENCODE_ANSI);

	Initialize(strAnsi);
}
#endif

// Contruct an empty string
String::String() :m_Length(0), m_pCArray(NULL), m_Disposed(false)
{
	Initialize(_T(""));
}

// Contruct an string with STL String
String::String(StdString OtherStdString) :m_Length(0), m_pCArray(NULL), m_Disposed(false)
{
	Initialize(OtherStdString);
}

// Contruct a string with C-type string
String::String(const CharArray pString) :m_Length(0), m_pCArray(NULL), m_Disposed(false)
{
	Initialize((CharArray)pString);
}

// Destruct the string
String::~String()
{
	Destroy();
}

// Allow the string copying
String::String(const String& other)
{
	SetStdString(other.GetStdString());
	SetLength(other.GetLength());
	CreateCArray();
	*m_pCArray = *(other.m_pCArray);
	m_WideArray = other.m_WideArray;
	SetDisposed(other.GetDisposed());
}

// Allow the obejct assignment
String& String::operator=(const String& other)
{
	if (this != &other)
	{
		SetStdString(other.GetStdString());
		SetLength(other.GetLength());
		CreateCArray();
		*m_pCArray = *(other.m_pCArray);
		m_WideArray = other.m_WideArray;
		SetDisposed(other.GetDisposed());
	}

	return *this;
}

// Init the String
String::Empty String::Initialize(StdString OtherStdString)
{
	// Set the default std String
	SetStdString(OtherStdString);

	// Set length of the String
	SetLength((Length)(GetStdString().length()));

	// Create a c array
	CreateCArray();
}

// Destory the String
String::Empty String::Destroy()
{
	if (!GetDisposed())
	{
		SetDisposed(true);

		DestoryCArray();
	}
}

// Create a c type array
String::Empty String::CreateCArray()
{
	SetCArray(new Array<Character>(GetLength() + 1));
}

// Destory the c type array
String::Empty String::DestoryCArray()
{
	if (GetCArray())
	{
		delete GetCArray();

		SetCArray(NULL);
	}
}

// Get C-type string 
LPCTSTR String::CStr()
{
	if (GetCArray() == NULL)
	{
		return NULL;
	}

	GetCArray()->Resize(GetLength() + 1);

	Array<Character>::Copy((CharArray)GetStdString().c_str(),
		GetLength(),
		GetCArray()->Data(),
		GetCArray()->Size());

	return GetCArray()->Data();
}

// Append a new std String to the String
String& String::Append(StdString& OtherStdString)
{
	StdString strString = GetStdString();

	strString.append(OtherStdString);

	// Set the std String
	SetStdString(strString);

	// Set the length
	SetLength((Length)(GetStdString().length()));

	return *this;
}

// Is the current String equals to the other one
String::BOOL String::Equal(String& OtherString)
{
	BOOL bEqual = false;

	if (GetStdString().compare(OtherString.GetStdString()) == 0)
	{
		bEqual = true;
	}

	return bEqual;
}

// Cohesion String to be a new String
String& String::operator+(String OtherString)
{
	return Append(OtherString.GetStdString());
}

// Is String equals to the other one
String::BOOL String::operator==(String OtherString)
{
	return Equal(OtherString);
}

// Is String not equals to the other one
String::BOOL String::operator!=(String OtherString)
{
	return !Equal(OtherString);
}

// Is empty string
String::BOOL String::IsEmpty()
{
	return GetStdString().empty();
}

// Set empty string
String::Empty String::SetEmpty()
{
	SetStdString(_T(""));
}

// Split the String by a seperator
String::BOOL String::Split(String strSeperator, StringTable& vStringTable)
{
	const Int32 FIND_FAIL = -1;

	const Int32 STOP_POSITION = -1;

	// Set the current character's position
	Index iCurrentIndex = Find(strSeperator, 0);
	if (iCurrentIndex == FIND_FAIL)
	{
		return false;
	}

	// Loop the vector
	Index iStartIndex = 0;

	while (STOP_POSITION != iCurrentIndex)
	{
		// Get the splited string
		String strSplitedString = SubString(iStartIndex, iCurrentIndex - iStartIndex);

		// Push the subString to the vector
		vStringTable.push_back(strSplitedString);

		// Update the start position of original String
		iStartIndex = iCurrentIndex + (Index)strSeperator.GetStdString().size();

		// Set the current character's position
		iCurrentIndex = Find(strSeperator, iStartIndex);
	}

	// The searching is to be end
	if (iStartIndex != GetLength())
	{
		// Get the last splited string
		String strSplitedString = SubString(iStartIndex);

		// Push the subString to the vector
		vStringTable.push_back(strSplitedString);
	}

	return true;
}

// Sub the string to the end
String String::SubString(Index iStartIndex)
{
	if (iStartIndex < 0 || iStartIndex >= GetLength())
	{
		return _T("");
	}

	return GetStdString().substr(iStartIndex, StdString::npos);
}

// Get the string from the left
String String::Left(Length iLength)
{
	return SubString(0, iLength);
}

// Get the string from the rigth
String String::Right(Length iLength)
{
	return SubString(GetLength() - iLength);
}

// Sub the String to get a new String
String String::SubString(Index iStartIndex, Length iSubLength)
{
	// Check the legal of the start position
	if (iStartIndex < 0 || iStartIndex >= GetLength())
	{
		return _T("");
	}

	// Get the left length that you can operate
	Length iLeftLength = GetLength() - iStartIndex;

	// Check the sub length's legal
	if (iSubLength <= 0 || iSubLength > iLeftLength)
	{
		return _T("");
	}

	return GetStdString().substr(iStartIndex, iSubLength);
}

// Find the last appearance character in the string and return its's position
String::Index String::FindLast(String strSpecialStr)
{
	return (Index)(GetStdString().find_last_of(strSpecialStr.GetStdString().c_str()));
}

// Find the appearance character in the string and return its's position
String::Index String::Find(String strSpecialStr, Index iStartPos)
{
	Index iFindPos = (Index)(StdString::npos);

	if (iStartPos < 0 || iStartPos >= GetLength() || strSpecialStr.GetStdString() == _T(""))
	{
		return iFindPos;
	}

	iFindPos = (Index)(GetStdString().find(strSpecialStr.GetStdString(), iStartPos));

	return iFindPos;
}

// Replace the string by another one
String& String::Replace(Index iReplacePos, Length iReplaceLength, String strReplaceString)
{
	if (iReplacePos < 0 || iReplacePos >= GetLength())
	{
		return *this;
	}

	if (iReplaceLength <= 0)
	{
		return *this;
	}

	StdString strString = GetStdString();

	strString.replace(iReplacePos, iReplaceLength, strReplaceString.GetStdString());

	SetStdString(strString);

	SetLength((Length)(GetStdString().length()));

	return *this;
}

// Fill the placeholde
String& String::FillPlaceholder(String strPlaceholder, String strPlaceholderValue)
{
	if (!IsContain(strPlaceholder))
	{
		return *this;
	}

	Int32 iPos = Find(strPlaceholder, 0);
	if (iPos != -1)
	{
		*this = Replace(iPos, strPlaceholder.GetLength(), strPlaceholderValue);
	}

	return *this;
}

// Fill the string with int placeholder(%s)
String& String::Arg(String strPlaceholderValue)
{
	return FillPlaceholder(_T("%s"), strPlaceholderValue);
}

// Fill the string with int placeholder(%d)
String& String::Arg(Integer iPlaceholderValue)
{
	String strValue = String::ToString<Integer>(iPlaceholderValue);

	return FillPlaceholder(_T("%d"), strValue);
}

// Fill the string with int placeholder(%f)
String& String::Arg(Single fPlaceholderValue)
{
	String strValue = String::ToString<Single>(fPlaceholderValue);

	return FillPlaceholder(_T("%f"), strValue);
}

// Fill the string with int placeholder(%lf)
String& String::Arg(Real dPlaceholderValue)
{
	String strValue = String::ToString<Real>(dPlaceholderValue);

	return FillPlaceholder(_T("%lf"), strValue);
}

// Contain a sub string or not
String::BOOL String::IsContain(String strSubString)
{
	if (Find(strSubString, 0) != -1)
	{
		return true;
	}

	return false;
}

// Contain how many character you want
String::Integer String::Contains(SByte ch)
{
	if (IsEmpty())
	{
		return 0;
	}

	std::string strData = ToAnsiData();

	return static_cast<Integer>(count(strData.begin(), strData.end(), ch));
}

// Get the wide string when you are in ANSI environment to program
System::WByteArray String::AllocWideString()
{
	const Int32 END_CHAR_COUNT = 1;

	// Get the wide string from the ANSI array
	std::wstring strWideString = ToUnicodeData();

	// Resize the wide array
	m_WideArray.Resize((Length)strWideString.length() + 1);

	// Fill the wide array
	Array<WByte>::Copy((WByteArray)strWideString.data(),
		(Length)strWideString.length(),
		m_WideArray.Data(),
		(Length)m_WideArray.Size());

	return m_WideArray.Data();
}

// Utf8 string(UNICODE->ANSI->UTF8 or ANSI->UTF8)
std::string String::ToUtf8Data()
{
#ifdef UNICODE
	std::string strAnsi = ANSI::GetString(GetStdString(), ENCODE_ANSI);

	std::string strUtf8 = UTF8::GetString(strAnsi, ENCODE_ANSI);
#else
	std::string strUtf8 = UTF8::GetString(GetStdString(), ENCODE_ANSI);
#endif

	return strUtf8;
}

// ANSI string(UNICODE->ANSI or ANSI)
std::string String::ToAnsiData()
{
#ifdef UNICODE
	std::string strAnsi = ANSI::GetString(GetStdString(), ENCODE_ANSI);
#else
	std::string strAnsi = GetStdString();
#endif

	return strAnsi;
}

// Data of the string
std::wstring String::ToUnicodeData()
{
#ifdef UNICODE
	std::wstring strData = GetStdString();
#else
	std::wstring strData = Unicode::GetString(GetStdString(), ENCODE_ANSI);
#endif

	return strData;
}

// Make string upper
String& String::MakeUpper()
{
	StdString strSource = GetStdString();

#ifdef UNICODE
	transform(strSource.begin(), strSource.end(), strSource.begin(), towupper);
#else
	transform(strSource.begin(), strSource.end(), strSource.begin(), toupper);
#endif

	SetStdString(strSource);

	return *this;
}

// Make string lower
String& String::MakeLower()
{
	StdString strSource = GetStdString();

#ifdef UNICODE
	transform(strSource.begin(), strSource.end(), strSource.begin(), towlower);
#else
	transform(strSource.begin(), strSource.end(), strSource.begin(), tolower);
#endif

	SetStdString(strSource);

	return *this;
}

// Get a character from the string at special position
String::Character String::operator[](Index iPos)
{
	if (iPos < 0 || iPos >= GetLength())
	{
		return _T('N');
	}

	return GetStdString().at(iPos);
}

// Guid to string
String String::ConvertGuid(const GUID& guid)
{
	char buffer[64] = { 0 };

	sprintf_s(buffer, sizeof(buffer),
		"{%08X-%04X-%04X-%02X%02X-%02X%02X%02X%02X%02X%02X}",
		guid.Data1, guid.Data2, guid.Data3,
		guid.Data4[0], guid.Data4[1], guid.Data4[2], guid.Data4[3],
		guid.Data4[4], guid.Data4[5], guid.Data4[6], guid.Data4[7]);

	std::string strId = buffer;

	return String(strId);
}

// Create GUID
String String::CreateGUID()
{
	CoInitialize(NULL);

	GUID guid;
	HRESULT h = CoCreateGuid(&guid);

	if (h == S_OK)
	{
		String strGuid = ConvertGuid(guid);

		strGuid = strGuid.SubString(1, strGuid.GetLength() - 2);

		CoUninitialize();

		return strGuid;
	}

	CoUninitialize();

	return _T("");
}
