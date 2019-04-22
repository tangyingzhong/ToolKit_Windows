#include "Application\PreCompile.h"
#include "Tool\Encoding\ASCII.h"
#include "Tool\Encoding\Unicode.h"
#include "Tool\Directory\Directory.h"
#include "Log.h"

using namespace System::IO;

Log* Log::m_Instance = NULL;

Log::Lock Log::m_Mutex = new Mutex();

String Log::m_Directory = _T("D:\\SystemLog");

String Log::m_BackupDirectory = _T("D:\\BackupLog");

///************************************************************************
/// <summary>
/// get the instance of log
/// </summary>
/// <returns></returns>
/// <remarks>
/// none
/// </remarks>
///***********************************************************************
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


///************************************************************************
/// <summary>
/// construct the log
/// </summary>
/// <returns></returns>
/// <remarks>
/// none
/// </remarks>
///***********************************************************************
Log::Log()
{
	Initialize();
}


///************************************************************************
/// <summary>
/// destory the log
/// </summary>
/// <returns></returns>
/// <remarks>
/// none
/// </remarks>
///***********************************************************************
Log::~Log()
{
	Destory();
}


///************************************************************************
/// <summary>
/// init the log
/// </summary>
/// <returns></returns>
/// <remarks>
/// none
/// </remarks>
///***********************************************************************
Log::Empty Log::Initialize()
{
	// Create a file
	CreateLogFile();

	// Register the error type
	RegisterErrorType();
}


///************************************************************************
/// <summary>
/// dispose the resource of log
/// </summary>
/// <returns></returns>
/// <remarks>
/// none
/// </remarks>
///***********************************************************************
Log::Empty Log::Destory()
{
	// Destory the log file
	DestoryLogFile();
}


///************************************************************************
/// <summary>
/// create a file handle
/// </summary>
/// <returns></returns>
/// <remarks>
/// none
/// </remarks>
///***********************************************************************
Log::Empty Log::CreateLogFile()
{
	this->SetLogFile(new File());
}


///************************************************************************
/// <summary>
/// destory the file handle
/// </summary>
/// <returns></returns>
/// <remarks>
/// none
/// </remarks>
///***********************************************************************
Log::Empty Log::DestoryLogFile()
{
	if (this->GetLogFile())
	{
		delete this->GetLogFile();
		SetLogFile(NULL);
	}
}


///************************************************************************
/// <summary>
/// register the error type
/// </summary>
/// <returns></returns>
/// <remarks>
/// none
/// </remarks>
///***********************************************************************
Log::Empty Log::RegisterErrorType()
{
	ErrorTypeArray[ErrorType::COM_OPEN_FAILED] = _T("COM_OPEN_FAILED");
	ErrorTypeArray[ErrorType::COM_READ_FAILED] = _T("COM_READ_FAILED");
	ErrorTypeArray[ErrorType::COM_WRITE_FAILED] = _T("COM_WRITE_FAILED");
	ErrorTypeArray[ErrorType::DB_OPEN_FAILED] = _T("DB_OPEN_FAILED");
	ErrorTypeArray[ErrorType::DB_READ_FAILED] = _T("DB_READ_FAILED");
	ErrorTypeArray[ErrorType::DB_WRITE_FAILED] = _T("DB_WRITE_FAILED");
	ErrorTypeArray[ErrorType::USB_OPEN_FAILED] = _T("USB_OPEN_FAILED");
	ErrorTypeArray[ErrorType::USB_READ_FAILED] = _T("USB_READ_FAILED");
	ErrorTypeArray[ErrorType::USB_WRITE_FAILED] = _T("USB_WRITE_FAILED");
}


///************************************************************************
/// <summary>
/// log the message into file
/// </summary>
/// <param name=fileName>file full path</param>
/// <param name=logMessage>log message</param>
/// <returns></returns>
/// <remarks>
/// none
/// </remarks>
///***********************************************************************
Log::Empty Log::LogToFile(String& strLogFileName, String& strLogMessage)
{
	assert(strLogFileName != _T(""));
	assert(strLogMessage != _T(""));

	if (this->GetLogFile() == NULL)
	{
		// Create the file handle
		CreateLogFile();
	}

	// Open the file
	this->GetLogFile()->Open(strLogFileName, FileMode::APPEND, FileAccess::WRITE);
	this->GetLogFile()->Seek(SeekOrigin::END, 0);

	// Change the encode of the log message
	std::string LogMsg = System::Encoding::ASCII::GetString(strLogMessage.AllocWideString());

	// Write the message to the file
	this->GetLogFile()->Write((SByteArray)LogMsg.c_str(), 0, strLogMessage.GetLength());

	// Close the file
	this->GetLogFile()->Close();
}


///************************************************************************
/// <summary>
/// get the current time
/// </summary>
/// <returns></returns>
/// <remarks>
/// none
/// </remarks>
///***********************************************************************
String Log::LocalTime()
{
	char CurTimeArray[200] = { 0 };

	// Get the local time
	SYSTEMTIME CurrentTime;
	::GetLocalTime(&CurrentTime);

	// Format the time
	sprintf_s(CurTimeArray, 200, "%04d_%02d_%02d", CurrentTime.wYear, CurrentTime.wMonth, CurrentTime.wDay);

	// Transmit the time
	std::string strTime = std::string(CurTimeArray);

	std::wstring strWTime = System::Encoding::Unicode::GetString(strTime, EncodeType::E_ASCII);

	return strWTime;
}


///************************************************************************
/// <summary>
/// create a new file name
/// </summary>
/// <returns></returns>
/// <remarks>
/// none
/// </remarks>
///***********************************************************************
String Log::CreateFileName()
{
	if (!this->GetLogFile())
	{
		this->CreateLogFile();
	}

	// Get the current time
	String strCurrentTime = LocalTime();

	// Organize the new file name
	String strRootDir = Log::m_Directory + _T("\\");

	String strFileName = strRootDir + _T("SystemLog_") + strCurrentTime + _T(".log");

	return strFileName;
}


///************************************************************************
/// <summary>
/// back up the log file to another directory
/// </summary>
/// <param name=destDir></param>
/// <returns></returns>
/// <remarks>
/// none
/// </remarks>
///***********************************************************************
Log::Empty Log::BackupLogFile()
{
	if (!this->GetLogFile())
	{
		this->CreateLogFile();
	}

	if (!Directory::Exists(m_BackupDirectory))
	{
		Directory::Create(m_BackupDirectory);
	}

	String strSrcDirectory = Log::m_Directory;

	String strDestDirectory = Log::m_BackupDirectory;

	// Find all the log file of source directory
	Directory::FileTable vFileTable;
	Directory::GetAllFiles(strSrcDirectory, vFileTable);

	// Move to dest directory
	for (Index iFileIndex = 0; iFileIndex < (Index)vFileTable.size();iFileIndex++)
	{
		// Rebuild the source path
		String strSrcPath = strSrcDirectory + _T("\\") + vFileTable[iFileIndex];

		// Build the dest path
		String strDestPath = strDestDirectory + _T("\\") + _T("_") + vFileTable[iFileIndex];

		this->GetLogFile()->Move(strSrcPath, strDestPath);
	}
}


///************************************************************************
/// <summary>
/// write the message to log
/// </summary>
/// <returns></returns>
/// <remarks>
/// none
/// </remarks>
///***********************************************************************
Log::Empty Log::WriteLog()
{
	if (Directory::Exists(Log::m_Directory) == false)
	{
		// Create a directory
		Directory::Create(Log::m_Directory);
	}

	if (this->GetFileName() == _T(""))
	{
		// Create a new file name
		this->SetFileName(this->CreateFileName());
	}

	if (!this->GetLogFile()->Exists(this->GetFileName()))
	{
		// Create the file
		this->GetLogFile()->Create(this->GetFileName());

		this->GetLogFile()->Close();
	}
	// Connect all string together 
	String strNewMessage = ConnectAllMessages();

	// Clear all messages in log buffer
	this->Clear();

	// Get the current file's size
	Size iCurFileSize = 0;
	if (this->GetLogFile()->Open(this->GetFileName(), FileMode::OPEN, FileAccess::READ) == true)
	{
		iCurFileSize = this->GetLogFile()->GetSize();

		this->GetLogFile()->Close();
	}

	// Compare the size with preSet fileSize
	Size leftSize = LogConfig::MAX_FILE_SIZE - iCurFileSize;

	Size iMsgLen = strNewMessage.GetLength();

	if (leftSize < iMsgLen)
	{
		// Back up the full log file
		this->BackupLogFile();

		// Create a new file name
		this->SetFileName(this->CreateFileName());

		// Log the message to the new file
		this->LogToFile(this->GetFileName(), strNewMessage);

		return;
	}

	// Write the connected message to the file
	this->LogToFile(this->GetFileName(), strNewMessage);
}


///************************************************************************
/// <summary>
/// build a full log message
/// </summary>
/// <param name=errorType>error type</param>
/// <param name=errorFileName>error happened file name</param>
/// <param name=errorLine>error happened line in file</param>
/// <param name=errorFuncName>error happend in which method</param>
/// <param name=errorMsg>error message</param>
/// <param name=remark>remark</param>
/// <returns>log message</returns>
/// <remarks>
/// none
/// </remarks>
///***********************************************************************
String Log::BuildMessage(ErrorType eErrorType, String strErrorFileName, LineNumber iErrorLine, String strErrorFuncName, String strErrorMsg, String strRemark)
{
	// Get the time
	String strCurTime = this->LocalTime();

	// Build the message
	String strBuildMsg = _T("");

	strBuildMsg = strBuildMsg + _T("ErrorType:")
		+ ErrorTypeArray[eErrorType]
		+ _T("|") + _T("ErrorFile:")
		+ strErrorFileName
		+ _T("|") + _T("ErrorLine:")
		+ String::ToString(iErrorLine)
		+ _T("|") + _T("ErrorFunction:")
		+ strErrorFuncName
		+ _T("|") + _T("ErrorMessage:")
		+ strErrorMsg
		+ _T("|") + _T("ErrorRemark:")
		+ strRemark
		+ _T("|") + _T("ErrorTime:")
		+ strCurTime
		+ _T("\r\n");

	return strBuildMsg;
}



///************************************************************************
/// <summary>
/// add log message into container
/// </summary>
/// <param name=message></param>
/// <returns></returns>
/// <remarks>
/// none
/// </remarks>
///***********************************************************************
Log::Empty Log::Add(String& strMessage)
{
	this->m_LogMesaageTable.push_back(strMessage);
}




///************************************************************************
/// <summary>
/// Connect all string together 
/// </summary>
/// <returns>a new log message</returns>
/// <remarks>
/// none
/// </remarks>
///***********************************************************************
String Log::ConnectAllMessages()
{
	String strMessage = _T("");
	for (Index iIndex = 0; iIndex < (Index)(this->m_LogMesaageTable.size()); iIndex++)
	{
		strMessage = strMessage + this->m_LogMesaageTable[iIndex];
	}

	return strMessage;
}



///************************************************************************
/// <summary>
/// clear the log message container
/// </summary>
/// <returns></returns>
/// <remarks>
/// none
/// </remarks>
///***********************************************************************
Log::Empty Log::Clear()
{
	LogMessageTable::iterator iter;

	for (iter = this->m_LogMesaageTable.begin(); iter != this->m_LogMesaageTable.end();)
	{
		iter = this->m_LogMesaageTable.erase(iter);
	}
}


///************************************************************************
/// <summary>
/// record log message
/// </summary>
/// <param name=errorType>error type</param>
/// <param name=errorFileName>error happened file name</param>
/// <param name=errorLine>error happened line in file</param>
/// <param name=errorFuncName>error happend in which method</param>
/// <param name=errorMsg>error message</param>
/// <param name=remark>remark</param>
/// <returns></returns>
/// <remarks>
/// none
/// </remarks>
///***********************************************************************
Log::Empty Log::Record(ErrorType eErrorType, String strErrorFileName, LineNumber iErrorLine, String strErrorFuncName, String strErrorMsg, String strRemark)
{
	// Rebuild the message
	String strBuildMessage = BuildMessage(eErrorType, strErrorFileName, iErrorLine, strErrorFuncName, strErrorMsg, strRemark);

	// Judge the current message's number
	if (this->m_LogMesaageTable.size() < LogConfig::MAX_MSG_NUM)
	{
		// Log the message into buffer
		this->Add(strBuildMessage);

		return;
	}

	// Log the message into file
	this->WriteLog();

	// Log the message into buffer
	this->Add(strBuildMessage);
}


///************************************************************************
/// <summary>
/// flush the log messages in container to the file
/// </summary>
/// <returns></returns>
/// <remarks>
/// none
/// </remarks>
///***********************************************************************
Log::Empty Log::Flush()
{
	this->WriteLog();
}