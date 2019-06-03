///************************************************************************
/// <copyrigth>2018-2019 Corporation.All Rights Reserved</copyrigth>
/// <author>tangyingzhong</author>
/// <contact>tangyz114987@outlook.com</contact>
/// <version>V1.0.0</version>
/// <describe>
/// Convert other encoding string to be ASCII string
///</describe>
/// <date>2019/3/6</date>
///***********************************************************************
#ifndef ASCII_H
#define ASCII_H

#include "Tool\Common\SystemType.h"

namespace System
{
	namespace Encoding
	{
		class ASCII
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
			// Forbid construct the ASCII
			ASCII() {	}

			// Forbid destructe the ASCII
			~ASCII() {	}

			// Forbid the object copying
			ASCII(const ASCII& Another) {	}

			// Forbid the obejct assignment
			ASCII& operator=(const ASCII& Another) {	}

		public:
			// Get mutilbytes from Unicode array Notice: count must contain '\0'
			static StdString GetString(WCharArray UnicodeBuffer, Index iPos, Length iCount);

			// Get mutilbytes from UNICODE string
			static StdString GetString(WStdString UnicodeString);

			// Get mutilbytes from UTF8 array Notice: count must contain '\0'
			static StdString GetString(SCharArray UTF8Buffer, Index iPos, Length iCount);

			// Get mutilbytes from UTF8 string
			static StdString GetString(StdString UTF8String);

		private:
			// Convert UTF8 to Mutilbytes
			static StdString UTF8ToASCII(StdString UTF8String);

			// Convert Unicode to Mutilbytes
			static StdString UnicodeToASCII(WStdString UnicodeString);
		};
	}
}

#endif // ASCII_H