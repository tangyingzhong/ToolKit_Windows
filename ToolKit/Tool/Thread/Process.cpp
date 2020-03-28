#include <Windows.h>
#include <shellapi.h>
#include "Process.h"

using namespace System::Thread;

// Construct the Process
Process::Process() :m_Disposed(false)
{
	Initialize();
}

// Detructe the Process
Process::~Process()
{
	Destory();
}

// Initialize the  process
Process::None Process::Initialize()
{
	// Clear the process start info
	ZeroMemory(&m_StartupInfo, sizeof(ProcessStartupInfo));

	// Clear the process info
	ZeroMemory(&m_ProcessInfo, sizeof(ProcessInfo));

	// Set the operation table
	m_OpTable[PRO_EDIT] = _T("edit");

	m_OpTable[PRO_EXPLORE] = _T("explore");

	m_OpTable[PRO_FIND] = _T("find");

	m_OpTable[PRO_OPEN] = _T("open");

	m_OpTable[PRO_PRINT] = _T("print");

	m_OpTable[PRO_PROPERTIES] = _T("properties");

	m_OpTable[PRO_RUNAS] = _T("runas");

	m_OpTable[PRO_NULL] = _T("NULL");
}

// Dispose the process
Process::None Process::Destory()
{
	if (!GetDisposed())
	{
		SetDisposed(true);

		Stop();
	}
}

// Create a process
Boolean Process::CreateProc(ExcutablePath strExcutablePath, ExcutablePath strExcutableDir)
{
	Int32 iRet=::CreateProcess(strExcutablePath.CStr(),
		NULL, 
		NULL, 
		NULL,
		false, 
		0, 
		NULL, 
		strExcutableDir.CStr(),
		&m_StartupInfo, 
		&m_ProcessInfo);

	if (iRet==FALSE)
	{
		return false;
	}

	WaitForSingleObject(m_ProcessInfo.hProcess, 1000);

	return true;
}

// Destory the process
Process::None Process::DestoryProc()
{
	if (m_ProcessInfo.hThread)
	{
		::CloseHandle(m_ProcessInfo.hThread);

		m_ProcessInfo.hThread = NULL;
	}

	if (m_ProcessInfo.hProcess)
	{
		::CloseHandle(m_ProcessInfo.hProcess);

		m_ProcessInfo.hProcess = NULL;
	}
}

// Start the process
Boolean Process::Start(ExcutablePath strExcutablePath, ExcutablePath strExcutableDir)
{
	return CreateProc(strExcutablePath, strExcutableDir);
}

// Start the process by shell
Boolean Process::StartByShell(ExcutablePath strExcutablePath,
	ExcutablePath strExcutableDir,
	ProcessOpEnum eOperation, 
	ParaTable& ParamenterTable)
{
	// Build the paramenters
	String strFinalPara = _T("");

	for (Int32 iIndex = 0; iIndex < (Int32)ParamenterTable.size();++iIndex)
	{
		strFinalPara = strFinalPara + ParamenterTable[iIndex]+_T(" ");
	}

	String strParamenter = _T("");

	if (!strFinalPara.IsEmpty())
	{
		strParamenter = strFinalPara.Left(strFinalPara.GetLength() - 1);
	}

	// Excute the exe
	HINSTANCE Ret = ShellExecute(NULL,
		m_OpTable[eOperation].CStr(),
		strExcutablePath.CStr(),
		strParamenter.CStr(),
		strExcutableDir.CStr(),
		SW_HIDE);

	Int32 iRet = static_cast<Int32>(Ret->unused);

	if (iRet<32)
	{
		return false;
	}

	return true;
}

// Start the process by shell
Boolean Process::StartByAdmin(ExcutablePath strExcutablePath,
	ExcutablePath strExcutableDir,
	ParaTable& ParamenterTable)
{
	return StartByShell(strExcutablePath,
		strExcutableDir,
		PRO_RUNAS,
		ParamenterTable);
}

// Stop the process
Process::None Process::Stop()
{
	// Get the exitcode at first
	ExitCode dwExitCode;
	::GetExitCodeProcess(m_ProcessInfo.hProcess, &dwExitCode);

	// Stop the process
	::TerminateProcess(m_ProcessInfo.hProcess, dwExitCode);

	// Destory the process
	DestoryProc();
}