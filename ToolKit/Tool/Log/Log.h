///************************************************************************
/// <copyrigth>Voice AI Technology Of ShenZhen</copyrigth>
/// <author>tangyingzhong</author>
/// <contact>yingzhong@voiceaitech.com</contact>
/// <version>v1.0.0</version>
/// <describe>
/// Log the message to the file
///</describe>
/// <date>2019/7/16</date>
///***********************************************************************
#ifndef LOG_H
#define LOG_H

#include "File/File.h"
#include "Thread/MutexLocker.h"
#include "DateTime/DateTime.h"
#include "BaseType/String.h"
#include "LogType.h"

using namespace System;
using namespace System::BasicType;
using namespace System::Thread;
using namespace System::Clock;

namespace System
{
	namespace IO
	{
		class Log
		{
		public:
			typedef System::Empty Empty;
			typedef System::Boolean BOOL;
			typedef BasicType::Int LineNumber;
			typedef BasicType::Int ProcessID;
			typedef BasicType::Int ThreadID;
			typedef System::Int32 Index;
			typedef System::UInt64 Size;
			typedef System::FILE_MODE_ENUM FileMode;
			typedef System::FILE_ACCESS_ENUM FileAccess;
			typedef System::SEEK_ORIGIN_ENUM SeekOrigin;
			typedef System::FILE_ATTRIBUTE_ENUM FileAttrEnum;
			typedef DateTime::TimeFormat TimeFormat;
			typedef LOG_TYPE_ENUM LogType;
			typedef std::queue<String> LogMessageTable;
			typedef Mutex* Lock;

		public:
			// Get the instance of log
			static Log* GetInstance();

			// Destory log self
			static Empty DestoryInstance();

		private:
			// Construct the log
			Log();

			// Destruct the log
			~Log();

			// Copy the log
			Log(Log& other) {	}

			// Assignment of log
			Log& operator=(Log& other) {	}

		public:
			// Config the log environment
			Empty ConfigureEnvironment(String strLogDirectory);

			// Log the message to the file
			Empty Record(LogType eLogType,
				ProcessID strProcessID,
				ThreadID strThreadID,
				String strFileName,
				LineNumber iLineNo,
				String strFuncName,
				String strMessage,
				String strRemark = _T(""));

			// Flush the message in buffer into the file
			Empty Flush();

			// Log the message to trace window
			Empty Trace(LogType eLogType,
				ProcessID strProcessID,
				ThreadID strThreadID,
				String strFileName,
				LineNumber iLineNo,
				String strFuncName,
				String strMessage,
				String strRemark = _T(""));

			// Set max logger size
			Empty SetMaxLoggerSize(Size iSize);

		private:
			// Init the Log
			Empty Initialize();

			// Destory the Log
			Empty Destory();

			// Create log directory
			BOOL CreateLogDirectory();

			// Create log file
			BOOL CreateLogFile();

			// New file name
			String CreateFileName();

			// Get current log file size
			Size GetCurLogFileSize();

			// Register the log type
			Empty RegisterLogType();

			// Get local time
			String LocalTime(String strTimeFormat = _T("yyyy-MM-dd hh:mm:ss"));

			// Log message to the file
			Empty LogToFile(String& strLogFileName, String& strLogMessage);

			// Log message
			Empty WriteLog();

			// Build the message
			String BuildMessage(LogType eLogType,
				ProcessID strProcessID,
				ThreadID strThreadID,
				String strFileName,
				LineNumber iLineNo,
				String strFuncName,
				String strMessage,
				String strRemark);

			// Push the message into the log buffer
			Empty Add(String& strMessage);

			// Connect all the message  
			String ConnectAllMessages();

			// Clear the log buffer
			Empty Clear();

			// Bacckup log file
			Empty BackupLog(String strLogFileName);

			// Add seperate lines to log file
			BOOL AddSeperateLines(String strLogFileName);

		private:
			// Get the FileName
			inline String GetFileName() const
			{
				return m_LogFileName;
			}

			// Set the FileName
			inline Empty SetFileName(String strLogFileName)
			{
				m_LogFileName = strLogFileName;
			}

			// Get the Log directory
			inline String GetLogDirectory() const
			{
				return m_LogDirectory;
			}

			// Set the Log directory
			inline Empty SetLogDirectory(String strLogDirectory)
			{
				m_LogDirectory = strLogDirectory;
			}

			// Get the Log Size
			inline Size GetMaxLogSize() const
			{
				return m_iMaxLogSize;
			}

			// Set the Log Size
			inline void SetMaxLogSize(Size iLogSize)
			{
				m_iMaxLogSize = iLogSize;
			}

			// Get the Disposed
			inline Boolean GetDisposed() const
			{
				return m_bDisposed;
			}

			// Set the Disposed
			inline Empty SetDisposed(Boolean bDisposed)
			{
				m_bDisposed = bDisposed;
			}

		private:
			// The instance of log
			static Log* m_Instance;

			// The mutex
			static Lock m_Mutex;

		private:
			// The name of log file
			String m_LogFileName;

			// The directory of log file
			String m_LogDirectory;

			// Message array
			LogMessageTable m_LogMesaageTable;

			// Max log size
			Size m_iMaxLogSize;

			// Message type
			String LogTypeArray[LOG_CONFIG_ENUM::LOG_TYPE_NUM];

			// Disposed state
			Boolean m_bDisposed;
		};
	}
}

#endif // LOG_H