///************************************************************************
/// <copyrigth>2018-2019 Corporation.All Rights Reserved</copyrigth>
/// <author>tangyingzhong</author>
/// <contact>tangyz114987@outlook.com</contact>
/// <version>V1.0.0</version>
/// <describe>
/// Convert other encoding string to be UTF8 string
///</describe>
/// <date>2019/3/6</date>
///***********************************************************************
#ifndef	UTF8_H
#define	UTF8_H

#include "Tool\Common\SystemType.h"

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
			static StdString GetString(SCharArray AsciiBuffer, Index iPos, Length iCount);

			// Get the UTF8 string from the ascii string
			static StdString GetString(StdString AsciiString);

			// Get the UTF8 string from the width char array Notice: count must contain '\0'
			static StdString GetString(WCharArray UnicodeBuffer, Index iPos, Length iCount);

			// Get the UTF8 string from the unicode string
			static StdString GetString(WStdString UnicodeString);

		private:
			// Convert Ascii string to UTF8 string
			static StdString ASCIIToUTF8(StdString AsciiString);

			// Convert Unicode string to UTF8 string
			static StdString UnicodeToUTF8(WStdString UnicodeString);
		};
	}
}

#endif // UTF8_H