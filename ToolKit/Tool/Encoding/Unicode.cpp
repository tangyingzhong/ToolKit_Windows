#include "Tool/Buffer/Array.h"
#include "Unicode.h"

using namespace System::Encoding;
using namespace System::Buffer;

// Get the Unicode string from the multibytes array
Unicode::WStdString Unicode::GetString(SCharArray Buffer,
	Index iPos,
	Length iCount,
	EncodeType eEncodingType)
{
	if (Buffer==NULL)
	{
		return L""; 
	}

	if (iCount<=0)
	{
		return L"";
	}

	if (eEncodingType==ENCODE_ANSI)
	{
		std::string strAnsi;

		strAnsi.append(Buffer + iPos, iCount);

		return ANSIToUnicode(strAnsi);
	}
	else if (eEncodingType==ENCODE_UTF8)
	{
		std::string strUtf8;

		strUtf8.append(Buffer + iPos, iCount);

		return UTF8ToUnicode(strUtf8);
	}

	return L"";
}

// Get the Unicode string from the multibyte string
Unicode::WStdString Unicode::GetString(StdString MultiString, EncodeType eEncodingType)
{
	if (MultiString.empty())
	{
		return L"";
	}

	if (eEncodingType == ENCODE_ANSI)
	{
		return ANSIToUnicode(MultiString);
	}

	if (eEncodingType == ENCODE_UTF8)
	{
		return UTF8ToUnicode(MultiString);
	}

	return L"";
}

// UTF8 to Unicode
Unicode::WStdString Unicode::UTF8ToUnicode(StdString Utf8String)
{
	if (Utf8String.empty())
	{
		return L"";
	}

	// Get the Unicode length
	Length iWideLength = ::MultiByteToWideChar(CP_UTF8, NULL,
		Utf8String.c_str(), 
		-1,
		NULL, 
		0);
	if (iWideLength <= 0)
	{
		return L"";
	}

	// Create an Unicode buffer 
	Array<WCharacter> UnicodeArray(iWideLength + 1);
	
	// Convert the UTF8 bytes to the Unicode bytes  
	Length iUnicodeLength = ::MultiByteToWideChar(CP_UTF8, NULL, 
		Utf8String.c_str(), 
		-1, 
		UnicodeArray.Data(), 
		UnicodeArray.Size());
	if (iUnicodeLength != iWideLength)
	{
		return L"";
	}

	return WStdString(UnicodeArray.Data());
}

// ANSI to Unicode
Unicode::WStdString Unicode::ANSIToUnicode(StdString ANSIString)
{
	if (ANSIString.empty())
	{
		return L"";
	}

	// Get the Unicode length
	Length iWideLength = MultiByteToWideChar(CP_ACP, 
		0, 
		ANSIString.c_str(), 
		-1, 
		NULL,
		0);
	if (iWideLength <= 0)
	{
		return L"";
	}

	// Create a Unicode buffer    
	Array<WCharacter> UnicodeArray(iWideLength + 1);
	
	// Convert the ANSI bytes to the Unicode bytes  
	Length iUnicodeLength = ::MultiByteToWideChar(CP_ACP, 
		0, 
		ANSIString.c_str(), 
		-1, 
		UnicodeArray.Data(), 
		UnicodeArray.Size());
	if (iUnicodeLength != iWideLength)
	{
		return L"";
	}

	return WStdString(UnicodeArray.Data());
}