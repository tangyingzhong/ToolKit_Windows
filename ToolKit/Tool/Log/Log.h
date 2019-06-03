///************************************************************************
/// <copyrigth>2018-2019 Corporation.All Rights Reserved</copyrigth>
/// <author>tangyingzhong</author>
/// <contact>tangyz114987@outlook.com</contact>
/// <version>V1.0.0</version>
/// <describe>
/// Log the message to the file
///</describe>
/// <date>2019/3/6</date>
///***********************************************************************
#ifndef LOG_H
#define LOG_H

#include "LogType.h"
#include "Tool\File\File.h"
#include "Tool\Thread\MutexLocker.h"
#include "Tool\BaseType\String.h"

using namespace System::BasicType;
using namespace System::Thread;

namespace System
{
	namespace IO
	{
		class Log
		{
		public:
			typedef System::Empty Empty;
			typedef System::Boolean BOOL;
			typedef System::Int32 LineNumber;
			typedef System::Int32 Index;
			typedef System::Int32 Size;
			typedef LogErrorType ErrorType;
			typedef File* LogFile;
			typedef Mutex* Lock;
			typedef vector<String> LogMessageTable;

		public:
			// Get the instance of log
			static Log* GetInstance();

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
			// Log the message to the file
			virtual Empty Record(ErrorType eErrorType, String strErrorFileName, LineNumber iErrorLine, String strErrorFuncName, String strErrorMsg, String strRemark);

			// Flush the message in buffer into the file
			virtual Empty Flush();

		private:
			// Init the Log
			Empty Initialize();

			// Destory the Log
			Empty Destory();

			// Create a file
			Empty CreateLogFile();

			// Destory the file
			Empty DestoryLogFile();

			// New file name
			String CreateFileName();

			// Register the error type
			Empty RegisterErrorType();

			// Get local time
			String LocalTime();

			// Log message to the file
			Empty LogToFile(String& strLogFileName, String& strLogMessage);

			// Log message
			Empty WriteLog();

			// Build the message
			String BuildMessage(ErrorType eErrorType, String strErrorFileName, LineNumber iErrorLine, String strErrorFuncName, String strErrorMsg, String strRemark);

			// Push the message into the log buffer
			Empty Add(String& strMessage);

			// Connect all the message  
			String ConnectAllMessages();

			// Clear the log buffer
			Empty Clear();

			// Back up the log
			Empty BackupLogFile();

		private:
			// Get the LogFile
			inline LogFile GetLogFile() const
			{
				return m_LogFile;
			}

			// Set the LogFile
			inline Empty SetLogFile(LogFile pLogFile)
			{
				this->m_LogFile = pLogFile;
			}

			// Get the FileName
			inline String GetFileName() const
			{
				return m_LogFileName;
			}

			// Set the FileName
			inline Empty SetFileName(String strLogFileName)
			{
				this->m_LogFileName = strLogFileName;
			}

		private:
			// The instance of log
			static Log* m_Instance;

			// The mutex
			static Lock m_Mutex;

		private:
			// The file in the windows
			LogFile m_LogFile;

			// The name of log file
			String m_LogFileName;

			// The directory of log file
			String m_Directory;

			// Back up directory of log file
			String m_BackupDirectory;

			// Message array
			LogMessageTable m_LogMesaageTable;

			// Message type
			String ErrorTypeArray[LogConfig::ERROR_TYPE_NUM];
		};
	}
}

#endif // LOG_H