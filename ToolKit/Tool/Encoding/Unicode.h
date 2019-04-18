///************************************************************************
/// <copyrigth>2018-2019 Corporation.All Rights Reserved</copyrigth>
/// <author>tangyingzhong</author>
/// <contact>tangyz114987@outlook.com</contact>
/// <version>V1.0.0</version>
/// <describe>
/// Convert other encoding string to be Unicode string
///</describe>
/// <date>2019/3/6</date>
///***********************************************************************
#ifndef UNICODE_H
#define UNICODE_H

#include "Tool\Common\SystemType.h"

namespace System
{
	namespace Encoding
	{
		///*********************************************************
		/// <class> Unicode </class>
		/// <summary>
		/// Convert string to be Unicode one
		/// </summary>
		/// <version>V1.0.0 </version>
		/// <goup> C++ </group>
		/// <author>tangyingzhong</author>
		/// <contact>tangyz114987@outlook.com</contact>
		///**********************************************************/
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
			typedef System::EncodeType EncodeType;

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
			static WStdString GetString(SCharArray Buffer, Index iPos, Length iCount, EncodeType EncodingType);

			// Get the Unicode string from the multibyte string
			static WStdString GetString(StdString MultiString, EncodeType EncodingType);

		private:
			//UTF8 to Unicode
			static WStdString UTF8ToUnicode(StdString Utf8String);

			//ASCII to Unicode
			static WStdString AsciiToUnicode(StdString AsciiString);
		};
	}
}

#endif //UNICODE_H_