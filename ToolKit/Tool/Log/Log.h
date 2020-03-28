///************************************************************************
/// <copyrigth>2018-2019 Corporation.All Rights Reserved</copyrigth>
/// <author>tangyingzhong</author>
/// <contact>tangyz114987@outlook.com</contact>
/// <version>v1.0.0</version>
/// <describe>
/// Log the message to the file
///</describe>
/// <date>2019/7/16</date>
///***********************************************************************
#ifndef LOG_H
#define LOG_H

#include <queue>
#include "Tool/File/File.h"
#include "Tool/Thread/MutexLocker.h"
#include "Tool/DateTime/DateTime.h"
#include "Tool/BaseType/String.h"
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
			typedef System::None None;
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
			static None DestoryInstance();

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
			None ConfigureEnvironment(String strLogDirectory);

			// Log the message to the file
			None Record(LogType eLogType,
				ProcessID strProcessID,
				ThreadID strThreadID,
				String strFileName,
				LineNumber iLineNo,
				String strFuncName,
				String strMessage,
				String strRemark = _T(""));

			// Flush the message in buffer into the file
			None Flush();

			// Log the message to trace window
			None Trace(LogType eLogType,
				ProcessID strProcessID,
				ThreadID strThreadID,
				String strFileName,
				LineNumber iLineNo,
				String strFuncName,
				String strMessage,
				String strRemark = _T(""));

			// Set max logger size
			None SetMaxLoggerSize(Size iSize);

		private:
			// Init the Log
			None Initialize();

			// Destory the Log
			None Destory();

			// Create log directory
			BOOL CreateLogDirectory();

			// Create log file
			BOOL CreateLogFile();

			// New file name
			String CreateFileName();

			// Get current log file size
			Size GetCurLogFileSize();

			// Register the log type
			None RegisterLogType();

			// Get local time
			String LocalTime(String strTimeFormat = _T("yyyy-MM-dd hh:mm:ss"));

			// Log message to the file
			None LogToFile(String& strLogFileName, String& strLogMessage);

			// Log message
			None WriteLog();

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
			None Add(String& strMessage);

			// Connect all the message  
			String ConnectAllMessages();

			// Clear the log buffer
			None Clear();

			// Bacckup log file
			None BackupLog(String strLogFileName);

			// Add seperate lines to log file
			BOOL AddSeperateLines(String strLogFileName);

		private:
			// Get the FileName
			inline String GetFileName() const
			{
				return m_LogFileName;
			}

			// Set the FileName
			inline None SetFileName(String strLogFileName)
			{
				m_LogFileName = strLogFileName;
			}

			// Get the Log directory
			inline String GetLogDirectory() const
			{
				return m_LogDirectory;
			}

			// Set the Log directory
			inline None SetLogDirectory(String strLogDirectory)
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
			inline None SetDisposed(Boolean bDisposed)
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