#include "Tool/Buffer/Array.h"
#include "UTF16.h"

using namespace System::Encoding;
using namespace System::Buffer;

// Get the UTF16 string from the multibytes array
UTF16::WStdString UTF16::GetString(SCharArray Buffer,
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

		return ANSIToUTF16(strAnsi);
	}
	else if (eEncodingType==ENCODE_UTF8)
	{
		std::string strUtf8;

		strUtf8.append(Buffer + iPos, iCount);

		return UTF8ToUTF16(strUtf8);
	}

	return L"";
}

// Get the UTF16 string from the multibyte string
UTF16::WStdString UTF16::GetString(StdString MultiString, EncodeType eEncodingType)
{
	if (MultiString.empty())
	{
		return L"";
	}

	if (eEncodingType == ENCODE_ANSI)
	{
		return ANSIToUTF16(MultiString);
	}

	if (eEncodingType == ENCODE_UTF8)
	{
		return UTF8ToUTF16(MultiString);
	}

	return L"";
}

// UTF8 to UTF16
UTF16::WStdString UTF16::UTF8ToUTF16(StdString Utf8String)
{
	if (Utf8String.empty())
	{
		return L"";
	}

	// Get the UTF16 length
	Length iWideLength = ::MultiByteToWideChar(CP_UTF8, NULL,
		Utf8String.c_str(), 
		-1,
		NULL, 
		0);
	if (iWideLength <= 0)
	{
		return L"";
	}

	// Create an UTF16 buffer 
	Array<WCharacter> UTF16Array(iWideLength + 1);
	
	// Convert the UTF8 bytes to the UTF16 bytes  
	Length iUTF16Length = ::MultiByteToWideChar(CP_UTF8, NULL, 
		Utf8String.c_str(), 
		-1, 
		UTF16Array.Data(), 
		UTF16Array.Size());
	if (iUTF16Length != iWideLength)
	{
		return L"";
	}

	return WStdString(UTF16Array.Data());
}

// ANSI to UTF16
UTF16::WStdString UTF16::ANSIToUTF16(StdString ANSIString)
{
	if (ANSIString.empty())
	{
		return L"";
	}

	// Get the UTF16 length
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

	// Create a UTF16 buffer    
	Array<WCharacter> UTF16Array(iWideLength + 1);
	
	// Convert the ANSI bytes to the UTF16 bytes  
	Length iUTF16Length = ::MultiByteToWideChar(CP_ACP, 
		0, 
		ANSIString.c_str(), 
		-1, 
		UTF16Array.Data(), 
		UTF16Array.Size());
	if (iUTF16Length != iWideLength)
	{
		return L"";
	}

	return WStdString(UTF16Array.Data());
}