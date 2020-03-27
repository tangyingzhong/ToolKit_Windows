///************************************************************************
/// <copyrigth>2018-2019 Corporation.All Rights Reserved</copyrigth>
/// <author>tangyingzhong</author>
/// <contact>tangyz114987@outlook.com</contact>
/// <version>v1.0.0</version>
/// <describe>
/// It is prepared for the logger so that you can easily use log
///</describe>
/// <date>2019/8/1</date>
///***********************************************************************
#ifndef SYSTEMLOG_H
#define SYSTEMLOG_H

#include <iostream>
#include "Log.h"

extern System::IO::Log* pSystemLogger;

#define LOG(LogType,FileName,LineNo,FunctionName,Message,Remark) \
pSystemLogger->Record(LogType, \
GetCurrentProcessId(), \
GetCurrentThreadId(), \
FileName,\
LineNo, \
FunctionName, \
Message,\
Remark); 

#define LOG_TRACE(LogType,FileName,LineNo,FunctionName,Message,Remark) \
pSystemLogger->Trace(LogType, \
GetCurrentProcessId(), \
GetCurrentThreadId(), \
FileName,\
LineNo, \
FunctionName, \
Message,\
Remark); 

#define LOG_STD(Message) \
{\
	String strMsg = Message;\
\
	std::cout << strMsg.ToANSIData().c_str() << std::endl;\
}

#define SET_MAX_LOG_SIZE(iSize) pSystemLogger->SetMaxLoggerSize(iSize);

#define LOG_FLUSH() pSystemLogger->Flush();

#define LOG_DEBUG(Message,Remark) \
LOG(System::IO::LOG_TYPE_ENUM::LOGGING_DEBUG,_FILE_,__LINE__,_FUNCNAME_,Message,Remark) \
LOG_TRACE(System::IO::LOG_TYPE_ENUM::LOGGING_DEBUG,_FILE_,__LINE__,_FUNCNAME_,Message,Remark) \
LOG_STD(Message)

#define LOG_ERROR(Message,Remark) \
LOG(System::IO::LOG_TYPE_ENUM::LOGGING_ERROR,_FILE_,__LINE__,_FUNCNAME_,Message,Remark) \
LOG_TRACE(System::IO::LOG_TYPE_ENUM::LOGGING_DEBUG,_FILE_,__LINE__,_FUNCNAME_,Message,Remark) \
LOG_STD(Message)

#define LOG_INFORMATION(Message,Remark) \
LOG(System::IO::LOG_TYPE_ENUM::LOGGING_INFORMATION,_FILE_,__LINE__,_FUNCNAME_,Message,Remark) \
LOG_TRACE(System::IO::LOG_TYPE_ENUM::LOGGING_DEBUG,_FILE_,__LINE__,_FUNCNAME_,Message,Remark) \
LOG_STD(Message)

#define LOG_DEBUG_EX(Message) \
{ \
String strMesg=Message; \
String strRemark = _T("");\
LOG(System::IO::LOG_TYPE_ENUM::LOGGING_DEBUG, _FILE_, __LINE__, _FUNCNAME_, strMesg, strRemark) \
LOG_TRACE(System::IO::LOG_TYPE_ENUM::LOGGING_DEBUG, _FILE_, __LINE__, _FUNCNAME_, strMesg, strRemark) \
LOG_STD(Message) \
}

#define LOG_ERROR_EX(Message) \
{ \
String strMesg=Message; \
String strRemark = _T("");\
LOG(System::IO::LOG_TYPE_ENUM::LOGGING_ERROR,_FILE_,__LINE__,_FUNCNAME_,strMesg,strRemark) \
LOG_TRACE(System::IO::LOG_TYPE_ENUM::LOGGING_DEBUG,_FILE_,__LINE__,_FUNCNAME_,strMesg,strRemark) \
LOG_STD(Message) \
}

#define LOG_INFORMATION_EX(Message) \
{ \
String strMesg=Message; \
String strRemark = _T(""); \
LOG(System::IO::LOG_TYPE_ENUM::LOGGING_INFORMATION,_FILE_,__LINE__,_FUNCNAME_,strMesg,strRemark) \
LOG_TRACE(System::IO::LOG_TYPE_ENUM::LOGGING_DEBUG,_FILE_,__LINE__,_FUNCNAME_,strMesg,strRemark) \
LOG_STD(Message) \
}

class AutoLogger
{
public:
	AutoLogger(String strFileName,
		int iLineNo, 
		String strFunctionName, 
		String strStartMessage,
		String strEndMessage) :m_strFileName(strFileName),
		m_iLineNo(iLineNo),
		m_strFunctionName(strFunctionName),
		m_strStartMessage(strStartMessage),
		m_strEndMessage(strEndMessage)
	{
		LOG(System::IO::LOG_TYPE_ENUM::LOGGING_DEBUG,
			m_strFileName, 
			m_iLineNo, 
			m_strFunctionName, 
			m_strStartMessage, 
			_T(""));

		LOG_TRACE(System::IO::LOG_TYPE_ENUM::LOGGING_DEBUG,
			m_strFileName, 
			m_iLineNo,
			m_strFunctionName,
			m_strStartMessage,
			_T(""));
	}

	~AutoLogger()
	{
		LOG(System::IO::LOG_TYPE_ENUM::LOGGING_DEBUG,
			m_strFileName, 
			m_iLineNo, 
			m_strFunctionName, 
			m_strEndMessage,
			_T(""));

		LOG_TRACE(System::IO::LOG_TYPE_ENUM::LOGGING_DEBUG,
			m_strFileName, 
			m_iLineNo, 
			m_strFunctionName, 
			m_strEndMessage,
			_T(""));
	}

private:
	String m_strFileName;

	int m_iLineNo;

	String m_strFunctionName;

	String m_strStartMessage;

	String m_strEndMessage;
};

#define LOG_BEGIN() \
String strStartMessage = String(_T("-----------------Start Function : %s-----------------")).Arg(_FUNCNAME_);\
\
String strEndMessage = String(_T("-----------------End Function : %s-----------------")).Arg(_FUNCNAME_);\
\
AutoLogger Logger(_FILE_,__LINE__,_FUNCNAME_,strStartMessage,strEndMessage);

#define LOG_START(strMesage) \
String strStartMessage = String(_T("-----------------Start to %s-----------------")).Arg(strMesage);\
\
String strEndMessage = String(_T("-----------------Finish to %s-----------------")).Arg(strMesage);\
\
AutoLogger Logger(_FILE_,__LINE__,_FUNCNAME_,strStartMessage,strEndMessage);

#endif //SYSTEMLOG_H