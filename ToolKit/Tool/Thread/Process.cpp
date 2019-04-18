#include "Application\PreCompile.h"
#include <shellapi.h>
#include "Process.h"

using namespace System::Thread;

///************************************************************************
/// <summary>
/// Construct the Process
/// </summary>
/// <returns></returns>
/// <remarks>
/// none
/// </remarks>
///***********************************************************************
Process::Process(ExcutablePath strExcutablePath) :m_ExcutablePath(strExcutablePath), m_Disposed(false)
{
	Initialize();
}


///************************************************************************
/// <summary>
/// Detructe the Process
/// </summary>
/// <returns></returns>
/// <remarks>
/// none
/// </remarks>
///***********************************************************************
Process::~Process()
{
	Destory();
}


///************************************************************************
/// <summary>
/// Initialize the  process
/// </summary>
/// <returns></returns>
/// <remarks>
/// none
/// </remarks>
///***********************************************************************
Process::Empty Process::Initialize()
{
	// Clear the process start info
	ZeroMemory(&m_StartupInfo, sizeof(ProcessStartupInfo));

	// Clear the process info
	ZeroMemory(&m_ProcessInfo, sizeof(ProcessInfo));
}


///************************************************************************
/// <summary>
/// Dispose the process
/// </summary>
/// <returns></returns>
/// <remarks>
/// none
/// </remarks>
///***********************************************************************
Process::Empty Process::Destory()
{
	if (!GetDisposed())
	{
		SetDisposed(true);

		// Stop the process
		this->Stop();
	}
}


///************************************************************************
/// <summary>
/// Create a process
/// </summary>
/// <returns></returns>
/// <remarks>
/// none
/// </remarks>
///***********************************************************************
Process::Empty Process::CreateProc()
{
	::CreateProcess(this->GetExcutablePath(), NULL, NULL, NULL, false, 0, NULL, NULL, &m_StartupInfo, &m_ProcessInfo);
}


///************************************************************************
/// <summary>
/// Destory the process
/// </summary>
/// <returns></returns>
/// <remarks>
/// none
/// </remarks>
///***********************************************************************
Process::Empty Process::DestoryProc()
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


///************************************************************************
/// <summary>
/// Start the another process
/// </summary>
/// <param name=targetPath></param>
/// <returns></returns>
/// <remarks>
/// none
/// </remarks>
///***********************************************************************
Process::Empty Process::Start()
{
	CreateProc();
}


///************************************************************************
/// <summary>
/// Stop the process
/// </summary>
/// <returns></returns>
/// <remarks>
/// none
/// </remarks>
///***********************************************************************
Process::Empty Process::Stop()
{
	// Get the exitcode at first
	ExitCode dwExitCode;
	::GetExitCodeProcess(m_ProcessInfo.hProcess, &dwExitCode);

	// Stop the process
	::TerminateProcess(m_ProcessInfo.hProcess, dwExitCode);

	// Destory the process
	DestoryProc();
}


///************************************************************************
/// <summary>
/// Start the process by shell
/// </summary>
/// <returns></returns>
/// <remarks>
/// none
/// </remarks>
///***********************************************************************
Process::Empty Process::StartByShell(ExcutablePath strExcutablePath)
{
	ShellExecute(NULL, _T("open"), strExcutablePath, NULL, NULL, SW_SHOWNORMAL);
}