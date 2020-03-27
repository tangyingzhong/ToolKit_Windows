#include "Tool/Buffer/Array.h"
#include "UTF8.h"
#include "ANSI.h"
#include "UTF16.h"

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
UTF8::StdString UTF8::GetString(WCharArray UTF16Buffer,
	Index iPos,
	Length iCount)
{
	if (UTF16Buffer == NULL)
	{
		return "";
	}

	if (iCount <= 0)
	{
		return "";
	}

	std::wstring strUTF16;

	strUTF16.append(UTF16Buffer + iPos, iCount);

	std::string strUtf8 = UTF16ToUTF8(strUTF16);

	return strUtf8;
}

// Get the UTF8 string from the byte array
UTF8::StdString UTF8::GetString(WStdString UTF16String)
{
	if (UTF16String.empty())
	{
		return "";
	}

	return UTF16ToUTF8(UTF16String);
}

// Convert UTF16 string to UTF8 string
UTF8::StdString UTF8::UTF16ToUTF8(WStdString UTF16String)
{
	if (UTF16String.empty())
	{
		return "";
	}

	// Get the utf8 length
	Length iMultiByteLength = WideCharToMultiByte(CP_UTF8,
		0, 
		UTF16String.c_str(), 
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
	
	// Convert the UTF16 bytes to the UTF8 bytes  
	Length iUtf8Length = WideCharToMultiByte(CP_UTF8, 
		0, 
		UTF16String.c_str(), 
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
	return UTF16ToUTF8(UTF16::GetString(ANSIString, ENCODE_ANSI));
}