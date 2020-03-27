#include "Tool/Buffer/Array.h"
#include "ANSI.h"
#include "UTF8.h"
#include "UTF16.h"

using namespace System::Buffer;
using namespace System::Encoding;

// Convert a UTF16 buffer to ANSI string
ANSI::StdString ANSI::GetString(WCharArray UTF16Buffer,
	Index iPos,
	Length iCount,
	EncodeType eEncodeType)
{
	if (UTF16Buffer==NULL)
	{
		return "";
	}

	if (iCount<=0)
	{
		return "";
	}

	std::wstring strUTF16;

	strUTF16.append(UTF16Buffer + iPos, iCount);

	std::string strAnsi = UTF16ToANSI(strUTF16);

	return strAnsi;
}

// Get mutilbytes from multibyte array Notice: count must contain '\0'
ANSI::StdString ANSI::GetString(SCharArray MultibyteBuffer,
	Index iPos,
	Length iCount,
	EncodeType eEncodeType)
{
	if (MultibyteBuffer==NULL)
	{
		return "";
	}

	if (iCount <= 0)
	{
		return "";
	}

	if (eEncodeType==ENCODE_UTF8)
	{
		std::string strUtf8;

		strUtf8.append(MultibyteBuffer + iPos, iCount);

		return UTF8ToANSI(strUtf8);
	}
	else if (eEncodeType == ENCODE_ANSI)
	{
		std::string strAnsi;

		strAnsi.append(MultibyteBuffer + iPos, iCount);

		return strAnsi;
	}

	return "";
}

// Get mutilbytes from UTF16 string
ANSI::StdString ANSI::GetString(WStdString UTF16String)
{
	if (UTF16String.empty())
	{
		return "";
	}

	return UTF16ToANSI(UTF16String);
}

// Get mutilbytes from multibyte string
ANSI::StdString ANSI::GetString(StdString strMultiString, EncodeType eEncodeType)
{
	if (strMultiString.empty())
	{
		return "";
	}

	if (eEncodeType==ENCODE_UTF8)
	{
		return UTF8ToANSI(strMultiString);
	}
	else if (eEncodeType == ENCODE_ANSI)
	{
		return strMultiString;
	}

	return "";
}

// Convert UTF8 to Mutilbytes
ANSI::StdString ANSI::UTF8ToANSI(StdString UTF8String)
{
	return UTF16ToANSI(UTF16::GetString(UTF8String, EncodeType::ENCODE_UTF8));
}

// Convert UTF16 to Mutilbytes
ANSI::StdString ANSI::UTF16ToANSI(WStdString UTF16String)
{
	if (UTF16String.empty())
	{
		return "";
	}

	// Get the multibytes size
	Length iMultiByteLength = ::WideCharToMultiByte(CP_ACP,
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

	// Create an ANSI Array 
	Array<SCharacter> ANSIArray(iMultiByteLength + 1);
	
	// Convert UTF16 to multibytes
	Length iANSILength = ::WideCharToMultiByte(CP_ACP,
		0,
		UTF16String.c_str(),
		-1,
		ANSIArray.Data(),
		ANSIArray.Size(),
		NULL,
		NULL);
	if (iANSILength != iMultiByteLength)
	{
		return "";
	}

	return StdString(ANSIArray.Data());
}