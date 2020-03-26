#include "PreCompile.h"
#include "SystemLog.h"
#include "Directory/Directory.h"

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
		System::IO::Log::DestoryInstance();
	}
};

static LoggerInitialize g_LoggerInitialize;