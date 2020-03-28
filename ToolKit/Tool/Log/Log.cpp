#include <iostream>
#include "Tool/Encoding/ANSI.h"
#include "Tool/Encoding/UTF16.h"
#include "Tool/Directory/Directory.h"
#include "Tool/DateTime/DateTime.h"
#include "Log.h"

using namespace System::IO;
using namespace System::Clock;

Log* Log::m_Instance = NULL;

Log::Lock Log::m_Mutex = new Mutex();

// Get the instance of log
Log* Log::GetInstance()
{
	if (m_Instance == NULL)
	{
		MutexLocker locker(m_Mutex);

		if (m_Instance == NULL)
		{
			Log* log = new Log();

			m_Instance = log;
		}
	}

	return m_Instance;
}

// Destory log self
Log::None Log::DestoryInstance()
{
	if (m_Instance)
	{
		delete m_Instance;

		m_Instance = NULL;
	}
}

// Construct the log
Log::Log() :m_LogDirectory(_T("")), m_iMaxLogSize(MAX_FILE_SIZE)
{
	Initialize();
}

// Destory the log
Log::~Log()
{
	Destory();
}

// Init the log
Log::None Log::Initialize()
{
	String strCurExePath = System::IO::Directory::GetExcutableDirectory();

	strCurExePath = System::IO::Directory::AddEnding(strCurExePath) + _T("SystemLog");

	ConfigureEnvironment(strCurExePath);

	RegisterLogType();
}

// Dispose the resource of log
Log::None Log::Destory()
{
	if (!GetDisposed())
	{
		SetDisposed(true);

		Flush();
	}
}

// Register the log type
Log::None Log::RegisterLogType()
{
	LogTypeArray[LOGGING_ERROR] = _T("LOG_ERROR");

	LogTypeArray[LOGGING_INFORMATION] = _T("LOG_INFORMATION");

	LogTypeArray[LOGGING_DEBUG] = _T("LOG_DEBUG");
}

// Add seperate lines to log file
Log::BOOL Log::AddSeperateLines(String strLogFileName)
{
	if (strLogFileName.IsEmpty())
	{
		return false;
	}

	File FileHelper;

	if (!FileHelper.Open(strLogFileName, FileMode::OPEN, FileAccess::READWRITE))
	{
		return false;
	}

	FileHelper.Seek(SeekOrigin::END, 0);

	std::string strSepData = "\r\n\r\n";

	FileHelper.Write(strSepData.c_str(), 0, static_cast<FixedUInt32>(strSepData.length()));

	FileHelper.Close();

	return true;
}

// Log the message into file
Log::None Log::LogToFile(String& strLogFileName, String& strLogMessage)
{
	if (strLogFileName.IsEmpty() || strLogMessage.IsEmpty())
	{
		return;
	}

	File FileHelper;

	FileHelper.Open(strLogFileName, FileMode::APPEND, FileAccess::WRITE);

	FileHelper.Seek(SeekOrigin::END, 0);

	FixedUInt32 uLen =static_cast<FixedUInt32>(strLogMessage.ToANSIData().length());

	FileHelper.Write((SByteArray)strLogMessage.ToANSIData().c_str(), 0, uLen);

	FileHelper.Close();
}

// Get the current time
String Log::LocalTime(String strTimeFormat)
{
	return DateTime::Now().ToString(strTimeFormat);
}

// Create log directory
Log::BOOL Log::CreateLogDirectory()
{
	if (GetLogDirectory().IsEmpty())
	{
		std::cerr << "Please configure the log environment at first with interface: ConfigureEnvironment" << std::endl;

		return false;
	}

	if (!Directory::IsExisted(GetLogDirectory()))
	{
		// Create a directory
		if (!Directory::Create(GetLogDirectory(), true))
		{
			return false;
		}
	}

	return true;
}

// Create log file
Log::BOOL Log::CreateLogFile()
{
	// Create log file name
	if (GetFileName().IsEmpty())
	{
		SetFileName(CreateFileName());
	}

	File FileHelper;

	if (!FileHelper.IsExisted(GetFileName()))
	{
		if (!FileHelper.Create(GetFileName()))
		{
			return false;
		}
	}

	return true;
}

// Create a new file name
String Log::CreateFileName()
{
	// Organize the new file name
	String strRootDir = Directory::AddEnding(GetLogDirectory());

	String strFileName = strRootDir + _T("SystemLog") + _T(".log");

	return strFileName;
}

// Get current log file size
Log::Size Log::GetCurLogFileSize()
{
	Size iCurFileSize = 0;

	File FileHelper;

	if (FileHelper.Open(GetFileName(), FileMode::OPEN, FileAccess::READ))
	{
		iCurFileSize = FileHelper.GetSize();
	}

	FileHelper.Close();

	return iCurFileSize;
}

// Write the message to log
Log::None Log::WriteLog()
{
	// Create a log directory
	if (!CreateLogDirectory())
	{
		return;
	}

	// Create a log file
	if (!CreateLogFile())
	{
		std::cerr << "Create a log file failed!" << std::endl;

		return;
	}

	// Connect all string together 
	String strNewMessage = ConnectAllMessages();

	// Clear all messages in log buffer
	Clear();

	// Get the current file's size
	Size iCurFileSize = GetCurLogFileSize();

	// Compare the size with preSet fileSize
	Size leftSize = GetMaxLogSize() - iCurFileSize;

	Size iMsgLen = strNewMessage.GetLength();

	if (leftSize < iMsgLen)
	{
		// Backup the old log
		BackupLog(GetFileName());

		// Create a new file name
		SetFileName(CreateFileName());

		// Log the message to the new file
		LogToFile(GetFileName(), strNewMessage);

		return;
	}

	// Write the connected message to the file
	LogToFile(GetFileName(), strNewMessage);
}

// Bacckup log file
None Log::BackupLog(String strLogFileName)
{
	// Create a new file name
	Int32 iPos = strLogFileName.FindLast(_T("\\"));

	String strLogDir = strLogFileName.Left(iPos + 1);

	String strLogName = strLogFileName.Right(strLogFileName.GetLength() - iPos - 1);

	Int32 iPos1 = strLogName.FindLast(_T("."));

	String strLog = strLogName.Left(iPos1);

	String strNewLogFileName = strLogDir
		+ strLog
		+ _T("_")
		+ LocalTime(_T("yyyy_MM_dd_hh_mm_ss"))
		+ _T(".log");

	// Rename the log file
	File::Rename(strLogFileName, strNewLogFileName);

	// Create a new file with old name
	File FileHelper;

	FileHelper.Create(strLogFileName);

	FileHelper.Close();
}

// Build a full log message
String Log::BuildMessage(LogType eLogType,
	ProcessID strProcessID,
	ThreadID strThreadID,
	String strFileName,
	LineNumber iLineNo,
	String strFuncName,
	String strMessage,
	String strRemark)
{
	// Get the time
	String strCurTime = LocalTime();

	// Build the message
	String strBuildMsg = _T("");

	strBuildMsg = String(_T("[")) + LogTypeArray[eLogType] + _T("]")
		+ _T("[") + strProcessID.ToString() + _T("]")
		+ _T("[") + strThreadID.ToString() + _T("]")
		+ _T("[") + strFileName + _T("]")
		+ _T("[") + iLineNo.ToString() + _T("]")
		+ _T("[") + strFuncName + _T("]")
		+ _T("[") + strMessage + _T("]")
		+ _T("[") + strRemark + _T("]")
		+ _T("[") + strCurTime + _T("]")
		+ _T("\r\n");

	return strBuildMsg;
}

// Add log message into container
Log::None Log::Add(String& strMessage)
{
	m_LogMesaageTable.push(strMessage);
}

// Connect all string together 
String Log::ConnectAllMessages()
{
	String strMessage = _T("");

	for (Index iIndex = 0; iIndex < (Index)(m_LogMesaageTable.size()); ++iIndex)
	{
		String strLogMsg = m_LogMesaageTable.front();

		m_LogMesaageTable.pop();

		strMessage = strMessage + strLogMsg;
	}

	return strMessage;
}

// Clear the log message container
Log::None Log::Clear()
{
	while (!m_LogMesaageTable.empty())
	{
		m_LogMesaageTable.pop();
	}

	LogMessageTable().swap(m_LogMesaageTable);
}

// Config the log environment
Log::None Log::ConfigureEnvironment(String strLogDirectory)
{
	if (strLogDirectory.IsEmpty())
	{
		std::cerr << "Please give me a correct directory for the log" << std::endl;

		return;
	}

	SetLogDirectory(strLogDirectory);
}

// Record log message
Log::None Log::Record(LogType eLogType,
	ProcessID strProcessID,
	ThreadID strThreadID,
	String strFileName,
	LineNumber iLineNo,
	String strFuncName,
	String strMessage,
	String strRemark)
{
	MutexLocker locker(m_Mutex);

	// Rebuild the message
	String strBuildMessage = BuildMessage(eLogType,
		strProcessID,
		strThreadID,
		strFileName,
		iLineNo,
		strFuncName,
		strMessage,
		strRemark);

	// Judge the current message's number
	Int32 iLogTableSize = static_cast<Int32>(m_LogMesaageTable.size());
	if (iLogTableSize < MAX_MSG_NUM)
	{
		// Log the message into buffer
		Add(strBuildMessage);

		return;
	}

	// Log the message into file
	WriteLog();

	// Log the message into buffer
	Add(strBuildMessage);
}

// Flush the log messages in container to the file
Log::None Log::Flush()
{
	MutexLocker locker(m_Mutex);

	// Write the left messages
	WriteLog();
}

// Log the message to trace window
Log::None Log::Trace(LogType eLogType,
	ProcessID strProcessID,
	ThreadID strThreadID,
	String strFileName,
	LineNumber iLineNo,
	String strFuncName,
	String strMessage,
	String strRemark)
{
	MutexLocker locker(m_Mutex);

	// Rebuild the message
	String strBuildMessage = BuildMessage(eLogType,
		strProcessID,
		strThreadID,
		strFileName,
		iLineNo,
		strFuncName,
		strMessage,
		strRemark);

	::OutputDebugString(strBuildMessage.CStr());
}

// Set log size
Log::None Log::SetMaxLoggerSize(Size iSize)
{
	SetMaxLogSize(iSize);
}