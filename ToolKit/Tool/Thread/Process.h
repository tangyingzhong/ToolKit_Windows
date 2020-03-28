///************************************************************************
/// <copyrigth>2018-2019 Corporation.All Rights Reserved</copyrigth>
/// <author>tangyingzhong</author>
/// <contact>tangyz114987@outlook.com</contact>
/// <version>v1.0.0</version>
/// <describe>
/// Process control
///</describe>
/// <date>2019/7/16</date>
///***********************************************************************
#ifndef PROCESS_H
#define PROCESS_H

#include <map>
#include "Tool/Common/SystemType.h"
#include "Tool/BaseType/String.h"

using namespace System::BasicType;

namespace System
{
	namespace Thread
	{
		enum ProcessOpEnum
		{
			// Open the file with edit.exe
			PRO_EDIT=0,

			// Brower the file
			PRO_EXPLORE,

			// Search the directory you set
			PRO_FIND,

			// Open a file or exe
			PRO_OPEN,

			// Print file, failed if it is not a file
			PRO_PRINT,

			// Show the file's properties
			PRO_PROPERTIES,

			// Run the exe with admin access
			PRO_RUNAS,

			// Default mode = PRO_OPEN
			PRO_NULL
		};

		class Process
		{
		public:
			typedef System::None None;
			typedef System::Boolean BOOL;
			typedef System::FixedUInt32 ExitCode;
			typedef String ExcutablePath;
			typedef vector<String> ParaTable;
			typedef STARTUPINFO ProcessStartupInfo;
			typedef PROCESS_INFORMATION ProcessInfo;

		public:
			// Construct the Process
			Process();

			// Detructe the Process
			~Process();

		private:
			// Copy Process
			Process(const Process& other) {	}

			// Asigment of Process
			Process& operator=(const Process& other) {	}

		public:
			// Start the process without administrator
			Boolean Start(ExcutablePath strExcutablePath, ExcutablePath strExcutableDir);

			// Stop the process
			None Stop();

			// Start the process by shell
			Boolean StartByShell(ExcutablePath strExcutablePath,
				ExcutablePath strExcutableDir,
				ProcessOpEnum eOperation, 
				ParaTable& ParamenterTable);

			// Start the process by shell
			Boolean StartByAdmin(ExcutablePath strExcutablePath,
				ExcutablePath strExcutableDir,
				ParaTable& ParamenterTable);

		private:
			// Initialize the  process
			None Initialize();

			// Destory the process
			None Destory();

			// Create a process
			Boolean CreateProc(ExcutablePath strExcutablePath, ExcutablePath strExcutableDir);

			// Destory the process
			None DestoryProc();

		private:
			// Get the disposed status
			inline BOOL GetDisposed() const
			{
				return m_Disposed;
			}

			// Set the disposed	status
			inline None SetDisposed(BOOL bDisposed)
			{
				m_Disposed = bDisposed;
			}

		private:
			// The info of the process startup
			ProcessStartupInfo m_StartupInfo;

			// The info of the process
			ProcessInfo m_ProcessInfo;

			// Operation table
			std::map<ProcessOpEnum, String> m_OpTable;

			// Disposed status
			BOOL m_Disposed;
		};
	}
}

#endif // PROCESS_H