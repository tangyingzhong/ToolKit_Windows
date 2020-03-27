///************************************************************************
/// <copyrigth>Voice AI Technology Of ShenZhen</copyrigth>
/// <author>tangyingzhong</author>
/// <contact>yingzhong@voiceaitech.com</contact>
/// <version>v1.0.0</version>
/// <describe>
/// Encode type
///</describe>
/// <date>2019/7/16</date>
///***********************************************************************
#ifndef ENCODE_TYPE_H
#define ENCODE_TYPE_H

#include <string>
#include "Tool/Common/SystemType.h"

namespace System
{
	namespace Encoding
	{
		// Encode type of the string
		enum ENCODE_TYPE_ENUM
		{
			// ANSI type string
			ENCODE_ANSI = 0,

			// UTF8 type string
			ENCODE_UTF8
		};
	}
}

#endif // ENCODE_TYPE_H