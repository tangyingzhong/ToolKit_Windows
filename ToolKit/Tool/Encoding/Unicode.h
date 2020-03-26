///************************************************************************
/// <copyrigth>2018-2019 Corporation.All Rights Reserved</copyrigth>
/// <author>tangyingzhong</author>
/// <contact>tangyz114987@outlook.com</contact>
/// <version>v1.0.0</version>
/// <describe>
/// Convert other encoding string to be Unicode string
///</describe>
/// <date>2019/7/16</date>
///***********************************************************************
#ifndef UNICODE_H
#define UNICODE_H

#include "EncodeType.h"

namespace System
{
	namespace Encoding
	{
		class Unicode
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
			// Construct the Unicode
			Unicode() {	}

			// Detructe the Unicode
			~Unicode() {	}

			// Forbid the object copying
			Unicode(const Unicode& other) {	}

			// Forbid the obejct assignment
			Unicode& operator=(const Unicode& other) {	}

		public:
			// Get the Unicode string from the multibytes array Notice: count must contain '\0'
			static WStdString GetString(SCharArray Buffer,
				Index iPos, 
				Length iCount, 
				EncodeType eEncodingType);

			// Get the Unicode string from the multibyte string
			static WStdString GetString(StdString MultiString, EncodeType eEncodingType);

		private:
			//UTF8 to Unicode
			static WStdString UTF8ToUnicode(StdString Utf8String);

			//ANSI to Unicode
			static WStdString ANSIToUnicode(StdString ANSIString);
		};
	}
}

#endif // UNICODE_H