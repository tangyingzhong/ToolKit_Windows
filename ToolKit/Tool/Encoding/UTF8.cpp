#include "PreCompile.h"
#include "Buffer/Array.h"
#include "UTF8.h"
#include "ANSI.h"
#include "Unicode.h"

using namespace System::Encoding;
using namespace System::Buffer;

// Get the UTF8 string from the byte array
UTF8::StdString UTF8::GetString(SCharArray pMultiBuffer, 
	Index iPos, 
	Length iCount, 
	EncodeType eEncodeType)
{
	if (pMultiBuffer == NULL)
	{
		return "";
	}

	if (iCount <= 0)
	{
		return "";
	}

	if (eEncodeType==ENCODE_ANSI)
	{
		StdString strFinal;

		strFinal.append(pMultiBuffer + iPos, iCount);

		return ANSIToUTF8(strFinal);
	}
	else if (eEncodeType == ENCODE_UTF8)
	{
		StdString strFinal;

		strFinal.append(pMultiBuffer + iPos, iCount);

		return strFinal;
	}

	return "";
}

// Get the UTF8 string from the multi string
UTF8::StdString UTF8::GetString(StdString strMultiString, EncodeType eEncodeType)
{
	if (strMultiString.empty())
	{
		return "";
	}

	if (eEncodeType == ENCODE_ANSI)
	{
		return ANSIToUTF8(strMultiString);
	}
	else if (eEncodeType == ENCODE_UTF8)
	{
		return strMultiString;
	}

	return "";
}

// Get the UTF8 string from the byte array
UTF8::StdString UTF8::GetString(WCharArray UnicodeBuffer,
	Index iPos,
	Length iCount,
	EncodeType eEncodeType)
{
	if (UnicodeBuffer == NULL)
	{
		return "";
	}

	if (iCount <= 0)
	{
		return "";
	}

	if (eEncodeType==ENCODE_ANSI)
	{
		std::wstring strUnicode;

		strUnicode.append(UnicodeBuffer + iPos, iCount);

		std::string strMultiString = ANSI::GetString(strUnicode, eEncodeType);

		std::string strUtf8 = GetString(strMultiString, ENCODE_ANSI);

		return strUtf8;
	}
	else if (eEncodeType==ENCODE_UTF8)
	{
		std::wstring strUnicode;

		strUnicode.append(UnicodeBuffer + iPos, iCount);

		std::string strUtf8 = UnicodeToUTF8(strUnicode);

		return strUtf8;
	}

	return "";
}

// Get the UTF8 string from the byte array
UTF8::StdString UTF8::GetString(WStdString UnicodeString, EncodeType eEncodeType)
{
	if (UnicodeString.empty())
	{
		return "";
	}

	if (eEncodeType == ENCODE_ANSI)
	{
		std::string strMultiString = ANSI::GetString(UnicodeString,eEncodeType);

		std::string strUtf8 = GetString(strMultiString, ENCODE_ANSI);

		return strUtf8;
	}
	else if (eEncodeType == ENCODE_UTF8)
	{
		std::string strUtf8 = UnicodeToUTF8(UnicodeString);

		return strUtf8;
	}

	return "";
}

// Convert Unicode string to UTF8 string
UTF8::StdString UTF8::UnicodeToUTF8(WStdString UnicodeString)
{
	if (UnicodeString.empty())
	{
		return "";
	}

	// Get the utf8 length
	Length iMultiByteLength = WideCharToMultiByte(CP_UTF8,
		0, 
		UnicodeString.c_str(), 
		-1, 
		NULL, 
		0, 
		NULL, 
		NULL);
	if (iMultiByteLength <= 0)
	{
		return "";
	}

	// Create a utf8 buffer 
	Array<SCharacter> MultiBytesArray(iMultiByteLength + 1);
	
	// Convert the Unicode bytes to the UTF8 bytes  
	Length iUtf8Length = WideCharToMultiByte(CP_UTF8, 
		0, 
		UnicodeString.c_str(), 
		-1, 
		MultiBytesArray.Data(), 
		MultiBytesArray.Size(), 
		NULL,
		NULL);
	if (iUtf8Length != iMultiByteLength)
	{
		return "";
	}

	return StdString(MultiBytesArray.Data());
}

// Convert ANSI string to UTF8 string
UTF8::StdString UTF8::ANSIToUTF8(StdString ANSIString)
{
	return UnicodeToUTF8(Unicode::GetString(ANSIString, ENCODE_ANSI));
}