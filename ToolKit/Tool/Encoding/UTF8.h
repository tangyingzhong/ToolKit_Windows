///************************************************************************
/// <copyrigth>2018-2019 Corporation.All Rights Reserved</copyrigth>
/// <author>tangyingzhong</author>
/// <contact>tangyz114987@outlook.com</contact>
/// <version>v1.0.0</version>
/// <describe>
/// Convert other encoding string to be UTF8 string
///</describe>
/// <date>2019/7/16</date>
///***********************************************************************
#ifndef	 UTF8_H
#define UTF8_H

#include "EncodeType.h"

namespace System
{
	namespace Encoding
	{
		class UTF8
		{
		public:
			typedef System::Int32 Index;
			typedef System::Int32 Length;
			typedef System::SByte SCharacter;
			typedef System::SByteArray SCharArray;
			typedef System::WByte WCharacter;
			typedef System::WByteArray WCharArray;
			typedef std::string StdString;
			typedef std::wstring WStdString;
			typedef ENCODE_TYPE_ENUM EncodeType;

		private:
			// Construct the UTF8
			UTF8() {	}

			// Destruct the UTF8
			~UTF8() {	}

			// Forbid the object copying
			UTF8(const UTF8& other) {	}

			// Forbid the obejct assignment
			UTF8& operator=(const UTF8& other) {	}

		public:	
			// Get the UTF8 string from the multibytes array Notice: count must contain '\0'
			static StdString GetString(SCharArray pMultiBuffer, 
				Index iPos,
				Length iCount, 
				EncodeType eEncodeType);

			// Get the UTF8 string from the multi string
			static StdString GetString(StdString strMultiString,EncodeType eEncodeType);

			// Get the UTF8 string from the width char array Notice: count must contain '\0'
			static StdString GetString(WCharArray UTF16Buffer, 
				Index iPos, 
				Length iCount);

			// Get the UTF8 string from the UTF16 string
			static StdString GetString(WStdString UTF16String);

		private:
			// Convert ANSI string to UTF8 string
			static StdString ANSIToUTF8(StdString ANSIString);

			// Convert UTF16 string to UTF8 string
			static StdString UTF16ToUTF8(WStdString UTF16String);
		};
	}
}

#endif // UTF8_H