///************************************************************************
/// <copyrigth>Voice AI Technology Of ShenZhen</copyrigth>
/// <author>tangyingzhong</author>
/// <contact>yingzhong@voiceaitech.com</contact>
/// <version>v1.0.0</version>
/// <describe>
/// Log type you can configure here
///</describe>
/// <date>2019/7/16</date>
///***********************************************************************
#ifndef LOGTYPE_H
#define LOGTYPE_H

#include "BaseType/String.h"
#include "Common/SystemType.h"
#include "Encoding/Unicode.h"

using namespace System;
using namespace System::BasicType;

namespace System
{
	namespace IO
	{
		enum LOG_TYPE_ENUM
		{
			// Log the common information
			LOGGING_INFORMATION=0,

			// Log the debug message
			LOGGING_DEBUG,

			// Log the error message
			LOGGING_ERROR,
		};

		enum LOG_CONFIG_ENUM
		{
			// The log file's max size
			MAX_FILE_SIZE = 800 * 1024 * 1024,

			// The container of log's max contains
			MAX_MSG_NUM = 1,

			// The number of log type
			LOG_TYPE_NUM = 3
		};
	}
}

static String GetFileName(SByteArray pFileName)
{
	std::string strFilePath = pFileName;

	String strFileName = strFilePath;

	Int32 iPos = strFileName.FindLast(_T("\\"));

	String strFinalFileName = strFileName.Right(strFileName.GetLength() - iPos - 1);

	return strFinalFileName;
}

static String GetFunctionName(SByteArray pFuncName)
{
	String strFunctionName = pFuncName;

	return strFunctionName;
}

#define _FILE_  GetFileName(__FILE__)

#define _FUNCNAME_ GetFunctionName(__FUNCTION__)

#endif // LOGTYPE_H