///************************************************************************
/// <copyrigth>2018-2019 Corporation.All Rights Reserved</copyrigth>
/// <author>tangyingzhong</author>
/// <contact>tangyz114987@outlook.com</contact>
/// <version>V1.0.0</version>
/// <describe>
/// Log type you can configure here
///</describe>
/// <date>2019/3/6</date>
///***********************************************************************
#ifndef LOGTYPE_H
#define LOGTYPE_H

namespace System
{
	typedef enum
	{
		DB_OPEN_FAILED,
		DB_READ_FAILED,
		DB_WRITE_FAILED,
		COM_OPEN_FAILED,
		COM_READ_FAILED,
		COM_WRITE_FAILED,
		USB_OPEN_FAILED,
		USB_READ_FAILED,
		USB_WRITE_FAILED
	}LogErrorType;

	typedef enum
	{
		// The log file's max size
		MAX_FILE_SIZE = 10 * 1024 * 1024,					

		// The container of log's max contains
		MAX_MSG_NUM = 3,						

		// The number of error type
		ERROR_TYPE_NUM = 9											
	}LogConfig;
}

#endif // LOGTYPE_H