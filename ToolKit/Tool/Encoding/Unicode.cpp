#include "Application\PreCompile.h"
#include "Tool\Buffer\Array.h"
#include "Unicode.h"

using namespace System::Encoding;
using namespace System::Buffer;

///************************************************************************
/// <summary>
/// Get the Unicode string from the multibytes array
/// </summary>
/// <param name=buffer>Multibyte array</param>
/// <param name=index>Buffer start index</param>
/// <param name=count>Buffer count</param>
/// <returns>Unicode string</returns>
/// <remarks>
/// Note: Buffer must contain '\0'
/// </remarks>
///***********************************************************************
Unicode::WStdString Unicode::GetString(SCharArray Buffer, Index iPos, Length iCount, EncodeType EncodingType)
{
	Array<SCharacter> MultibyteArray(iCount + 1);

	// Copy the array
	Array<SCharacter>::Copy(Buffer + iPos, iCount, MultibyteArray, MultibyteArray.Size());

	//Set the string
	StdString MultiString = MultibyteArray;

	return GetString(MultiString, EncodingType);
}


///************************************************************************
/// <summary>
/// Get the Unicode string from the multibyte string
/// </summary>
/// <param name=StdString MultiString></param>
/// <returns></returns>
/// <remarks>
/// None
/// </remarks>
///***********************************************************************
Unicode::WStdString Unicode::GetString(StdString MultiString, EncodeType EncodingType)
{
	assert(EncodingType != EncodeType::E_UNICODE);

	if (EncodingType == EncodeType::E_UNICODE)
	{
		return L"";
	}

	if (EncodingType == EncodeType::E_ASCII)
	{
		return AsciiToUnicode(MultiString);
	}

	return UTF8ToUnicode(MultiString);
}


///************************************************************************
/// <summary>
/// UTF8 to Unicode
/// </summary>
/// <param name=utfStr>UTF8 string</param>
/// <returns>Unicode String</returns>
/// <remarks>
/// none
/// </remarks>
///***********************************************************************
Unicode::WStdString Unicode::UTF8ToUnicode(StdString Utf8String)
{
	// Get the utf8 string length 
	int iUtf8StrLength = (int)Utf8String.length() + 1;
	int iWideLength = ::MultiByteToWideChar(CP_UTF8, NULL, Utf8String.c_str(), iUtf8StrLength, NULL, 0);
	assert(iWideLength > 0);
	if (iWideLength <= 0)
	{
		return L"";
	}

	// Create an unicode buffer 
	Array<WCharacter> UnicodeArray(iWideLength + 1);
	
	// Convert the UTF8 bytes to the Unicode bytes  
	int iUnicodeLength = ::MultiByteToWideChar(CP_UTF8, NULL, Utf8String.c_str(), iUtf8StrLength, UnicodeArray, iWideLength);
	assert(iUnicodeLength == iWideLength);
	if (iUnicodeLength != iWideLength)
	{
		return L"";
	}

	UnicodeArray[iUnicodeLength] = '\0';

	// Set the unicode string
	WStdString UnicodeString = UnicodeArray;

	return UnicodeString;
}


///************************************************************************
/// <summary>
/// ASCII to Unicode
/// </summary>
/// <param name=asciiStr>ascii string</param>
/// <returns>unicode string</returns>
/// <remarks>
/// none
/// </remarks>
///***********************************************************************
Unicode::WStdString Unicode::AsciiToUnicode(StdString AsciiString)
{
	// Get the ascii string length
	int iAsciiLength = (int)AsciiString.length() + 1;
	int iWideLength = MultiByteToWideChar(CP_ACP, 0, AsciiString.c_str(), iAsciiLength, NULL, 0);
	assert(iWideLength > 0);
	if (iWideLength <= 0)
	{
		return L"";
	}

	// Create a unicode buffer    
	Array<WCharacter> UnicodeArray(iWideLength + 1);
	// Clear the array
	Array<WCharacter>::Clear(UnicodeArray, 0, UnicodeArray.Size());

	// Convert the ascii bytes to the unicode bytes  
	int iUnicodeLength = ::MultiByteToWideChar(CP_ACP, 0, AsciiString.c_str(), iAsciiLength, UnicodeArray, iWideLength);
	assert(iUnicodeLength == iWideLength);
	if (iUnicodeLength != iWideLength)
	{
		return L"";
	}

	UnicodeArray[iUnicodeLength] = '\0';

	// Set the unicode string
	WStdString UnicodeString = UnicodeArray;

	return UnicodeString;
}