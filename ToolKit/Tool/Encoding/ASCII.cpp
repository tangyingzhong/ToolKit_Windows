#include <assert.h>
#include "Tool\Buffer\Array.h"
#include "ASCII.h"
#include "Unicode.h"

using namespace System::Buffer;
using namespace System::Encoding;

///************************************************************************
/// <summary>
/// Convert a unicode buffer to ascii string
/// </summary>
/// <param name=CharArray UnicodeBuffer>Unicode buffer</param>
/// <param name=Index iPos>Buffer start position</param>
/// <param name=Length iCount>Buffer count</param>
/// <returns></returns>
/// <remarks>
/// None
/// </remarks>
///***********************************************************************
ASCII::StdString ASCII::GetString(WCharArray UnicodeBuffer, Index iPos, Length iCount)
{
	Array<WCharacter> UnicodeArray(iCount + 1);

	// Copy source array to the new one
	Array<WCharacter>::Copy(UnicodeBuffer + iPos, iCount, UnicodeArray.Data(), UnicodeArray.Size());

	return UnicodeToASCII(UnicodeArray.Data());
}


///************************************************************************
/// <summary>
/// Get mutilbytes from UTF8 array Notice: count must contain '\0'
/// </summary>
/// <param name=CharArray UTF8Buffer>UTF8 buffer</param>
/// <param name=Index iPos>Buffer pos</param>
/// <param name=Length iCount>Buffer count</param>
/// <returns></returns>
/// <remarks>
/// None
/// </remarks>
///***********************************************************************
ASCII::StdString ASCII::GetString(SCharArray UTF8Buffer, Index iPos, Length iCount)
{
	Array<SCharacter> Utf8Array(iCount + 1);

	// Copy the array
	Array<SCharacter>::Copy(UTF8Buffer + iPos, iCount, Utf8Array.Data(), Utf8Array.Size());

	return UTF8ToASCII(Utf8Array.Data());
}


///************************************************************************
/// <summary>
/// Get mutilbytes from Unicode string
/// </summary>
/// <param name=unicodeStr>unicode string</param>
/// <returns>multibytes string</returns>
/// <remarks>
/// none
/// </remarks>
///***********************************************************************
ASCII::StdString ASCII::GetString(WStdString UnicodeString)
{
	return UnicodeToASCII(UnicodeString);
}


///************************************************************************
/// <summary>
/// Get mutilbytes from UTF8 string
/// </summary>
/// <param name=UTF8String>utf8 string</param>
/// <returns>multibytes string</returns>
/// <remarks>
/// none
/// </remarks>
///***********************************************************************
ASCII::StdString ASCII::GetString(StdString UTF8String)
{
	return UTF8ToASCII(UTF8String);
}


///************************************************************************
/// <summary>
/// Convert UTF8 to Mutilbytes
/// </summary>
/// <param name=utfStr>UTF8 string</param>
/// <returns>Multibytes string</returns>
/// <remarks>
/// none
/// </remarks>
///***********************************************************************
ASCII::StdString ASCII::UTF8ToASCII(StdString UTF8String)
{
	return UnicodeToASCII(Unicode::GetString(UTF8String, ENCODE_TYPE_ENUM::ENCODE_UTF8));
}


///************************************************************************
/// <summary>
/// Convert Unicode to Mutilbytes
/// </summary>
/// <param name=unicodeStr>Unicode string</param>
/// <returns>Multibytes string</returns>
/// <remarks>
/// none
/// </remarks>
///***********************************************************************
ASCII::StdString ASCII::UnicodeToASCII(WStdString UnicodeString)
{
	// Get the Unicode string real length
	const Length END_CHAR_COUNT = 1;
	Length iUnicodeLength = (Length)UnicodeString.length() + END_CHAR_COUNT;

	// Get the multibytes size
	Length iMultiByteLength = ::WideCharToMultiByte(CP_ACP, 0, UnicodeString.c_str(), iUnicodeLength, NULL, 0, NULL, NULL);
	assert(iMultiByteLength > 0);
	if (iMultiByteLength <= 0)
	{
		return "";
	}

	// Create an ASCII Array 
	Array<SCharacter> ASCIIArray(iMultiByteLength + END_CHAR_COUNT);
	
	// Convert unicode to multibytes
	Length iAsciiLength = ::WideCharToMultiByte(CP_ACP, 0, UnicodeString.c_str(), iUnicodeLength, ASCIIArray.Data(), ASCIIArray.Size(), NULL, NULL);
	assert(iAsciiLength == iMultiByteLength);
	if (iAsciiLength != iMultiByteLength)
	{
		return "";
	}

	ASCIIArray[iAsciiLength] = '\0';

	return ASCIIArray.Data();
}