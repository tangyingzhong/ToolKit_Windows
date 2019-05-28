#include "Application\PreCompile.h"
#include "Tool\Buffer\Array.h"
#include "UTF8.h"
#include "Unicode.h"

using namespace System::Encoding;
using namespace System::Buffer;

///************************************************************************
/// <summary>
/// Get the UTF8 string from the byte array
/// </summary>
/// <param name=buffer>byte array</param>
/// <param name=index>the offset of array</param>
/// <param name=count>the count of buffer offset</param>
/// <returns>UTF8 string</returns>
/// <remarks>
/// none
/// </remarks>
///***********************************************************************
UTF8::StdString UTF8::GetString(SCharArray AsciiBuffer, Index iPos, Length iCount)
{
	Array<SCharacter> AsciiArray(iCount + 1);

	// Copy source array to the new one
	Array<SCharacter>::Copy(AsciiBuffer + iPos, iCount, AsciiArray.Data(), AsciiArray.Size());

	return ASCIIToUTF8(AsciiArray.Data());
}


///************************************************************************
/// <summary>
/// Get the UTF8 string from the byte array
/// </summary>
/// <param name=buffer>unicode byte array</param>
/// <param name=index>the offset of array</param>
/// <param name=count>the count of unicode</param>
/// <returns>UTF8 string</returns>
/// <remarks>
/// none
/// </remarks>
///***********************************************************************
UTF8::StdString UTF8::GetString(WCharArray UnicodeBuffer, Index iPos, Length iCount)
{
	Array<WCharacter> UnicodeArray(iCount + 1);

	// Copy source array to the new one
	Array<WCharacter>::Copy(UnicodeBuffer + iPos, iCount, UnicodeArray.Data(), UnicodeArray.Size());

	return UnicodeToUTF8(UnicodeArray.Data());
}


///************************************************************************
/// <summary>
/// Get the UTF8 string from the byte array
/// </summary>
/// <param name=asciiString>multibytes string</param>
/// <returns>UTF8 string</returns>
/// <remarks>
/// none
/// </remarks>
///***********************************************************************
UTF8::StdString UTF8::GetString(StdString AsciiString)
{
	return ASCIIToUTF8(AsciiString);
}


///************************************************************************
/// <summary>
/// Get the UTF8 string from the byte array
/// </summary>
/// <param name=unicodeString>unicode string</param>
/// <returns>UTF8 string</returns>
/// <remarks>
/// none
/// </remarks>
///***********************************************************************
UTF8::StdString UTF8::GetString(WStdString UnicodeString)
{
	return UnicodeToUTF8(UnicodeString);
}


///************************************************************************
/// <summary>
/// Convert Unicode string to UTF8 string
/// </summary>
/// <param name=unicodeStr>unicode string</param>
/// <returns>UTF8 string</returns>
/// <remarks>
/// none
/// </remarks>
///***********************************************************************
UTF8::StdString UTF8::UnicodeToUTF8(WStdString UnicodeString)
{
	// Get the unicode string length
	const Length END_CHAR_COUNT = 1;
	Length iUnicodeStrLength =(Length)UnicodeString.length() + END_CHAR_COUNT;

	Length iMultiLength = WideCharToMultiByte(CP_UTF8, 0, UnicodeString.c_str(), iUnicodeStrLength, NULL, 0, NULL, NULL);
	assert(iMultiLength > 0);
	if (iMultiLength <= 0)
	{
		return "";
	}

	// Create a utf8 buffer 
	Array<SCharacter> MultiBytesArray(iMultiLength + END_CHAR_COUNT);
	
	// Convert the Unicode bytes to the UTF8 bytes  
	Length iUtf8Length = WideCharToMultiByte(CP_UTF8, 0, UnicodeString.c_str(), iUnicodeStrLength, MultiBytesArray.Data(), MultiBytesArray.Size(), NULL, NULL);
	assert(iUtf8Length == iMultiLength);
	if (iUtf8Length != iMultiLength)
	{
		return "";
	}

	MultiBytesArray[iUtf8Length] = '\0';

	return MultiBytesArray.Data();
}


///************************************************************************
/// <summary>
/// Convert Ascii string to UTF8 string
/// </summary>
/// <param name=asciiStr>Ascii string</param>
/// <returns>UTF8 string</returns>
/// <remarks>
/// none
/// </remarks>
///***********************************************************************
UTF8::StdString UTF8::ASCIIToUTF8(StdString AsciiString)
{
	return UnicodeToUTF8(Unicode::GetString(AsciiString, EncodeType::E_ASCII));
}