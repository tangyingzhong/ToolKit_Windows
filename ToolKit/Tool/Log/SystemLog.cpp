#include "Tool/Directory/Directory.h"
#include "SystemLog.h"

System::IO::Log* pSystemLogger = System::IO::Log::GetInstance();

struct LoggerInitialize
{
	LoggerInitialize()
	{
		String strCurExePath = System::IO::Directory::GetExcutableDirectory();

		strCurExePath = System::IO::Directory::AddEnding(strCurExePath) + _T("SystemLog");

		pSystemLogger->ConfigureEnvironment(strCurExePath);
	}

	~LoggerInitialize()
	{
		pSystemLogger->Flush();

		System::IO::Log::DestoryInstance();
	}
};

static LoggerInitialize g_LoggerInitialize;