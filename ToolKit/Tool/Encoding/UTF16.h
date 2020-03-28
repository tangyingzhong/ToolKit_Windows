///************************************************************************
/// <copyrigth>2018-2019 Corporation.All Rights Reserved</copyrigth>
/// <author>tangyingzhong</author>
/// <contact>tangyz114987@outlook.com</contact>
/// <version>v1.0.0</version>
/// <describe>
/// Convert other encoding string to be UTF16 string
///</describe>
/// <date>2019/7/16</date>
///***********************************************************************
#ifndef UTF16_H
#define UTF16_H

#include "EncodeType.h"

namespace System
{
	namespace Encoding
	{
		class UTF16
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
			// Construct the UTF16
			UTF16() {	}

			// Detructe the UTF16
			~UTF16() {	}

			// Forbid the object copying
			UTF16(const UTF16& other) {	}

			// Forbid the obejct assignment
			UTF16& operator=(const UTF16& other) {	}

		public:
			// Get the UTF16 string from the multibytes array Notice: count must contain '\0'
			static WStdString GetString(SCharArray Buffer,
				Index iPos, 
				Length iCount, 
				EncodeType eEncodingType);

			// Get the UTF16 string from the multibyte string
			static WStdString GetString(StdString MultiString, EncodeType eEncodingType);

		private:
			//UTF8 to UTF16
			static WStdString UTF8ToUTF16(StdString Utf8String);

			//ANSI to UTF16
			static WStdString ANSIToUTF16(StdString ANSIString);
		};
	}
}

#endif // UTF16_H