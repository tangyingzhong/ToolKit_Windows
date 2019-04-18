///************************************************************************
/// <copyrigth>2018-2019 Corporation.All Rights Reserved</copyrigth>
/// <author>tangyingzhong</author>
/// <contact>tangyz114987@outlook.com</contact>
/// <version>V1.0.0</version>
/// <describe>
/// Process control
///</describe>
/// <date>2019/3/7</date>
///***********************************************************************
#ifndef PROCESS_H
#define PROCESS_H

#include "Tool\BaseType\String.h"

using namespace System::BasicType;

namespace System
{
	namespace Thread
	{
		///*********************************************************
		/// <class> Process </class>
		/// <summary>
		/// Use it to start a process or stop process
		/// </summary>
		/// <version>V1.0.0 </version>
		/// <goup> C++ </group>
		/// <author>tangyingzhong</author>
		/// <contact>tangyz114987@outlook.com</contact>
		///**********************************************************/
		class Process
		{
		public:
			typedef System::Empty Empty;
			typedef System::Boolean BOOL;
			typedef System::UInt64 ExitCode;
			typedef String ExcutablePath;
			typedef STARTUPINFO ProcessStartupInfo;
			typedef PROCESS_INFORMATION ProcessInfo;

		public:
			// Construct the Process
			Process(ExcutablePath strExcutablePath);

			// Detructe the Process
			~Process();

		private:
			// Copy Process
			Process(const Process& other) {	}

			// Asigment of Process
			Process& operator=(const Process& other) {	}

		public:
			// Start the another process
			Empty Start();

			// Stop the process
			Empty Stop();

			// Start the process by shell
			static Empty StartByShell(ExcutablePath strExcutablePath);

		private:
			// Initialize the  process
			Empty Initialize();

			// Destory the process
			Empty Destory();

			// Create a process
			Empty CreateProc();

			// Destory the process
			Empty DestoryProc();

		private:
			// Get Excutable Path
			inline ExcutablePath GetExcutablePath() const
			{
				return m_ExcutablePath;
			}

			// Set Excutable Path
			inline Empty SetExcutablePath(ExcutablePath strExcutablePath)
			{
				this->m_ExcutablePath = strExcutablePath;
			}

			// Get the disposed status
			inline BOOL GetDisposed() const
			{
				return m_Disposed;
			}

			// Set the disposed	status
			inline Empty SetDisposed(BOOL bDisposed)
			{
				this->m_Disposed = bDisposed;
			}

		private:
			// The info of the process startup
			ProcessStartupInfo m_StartupInfo;

			// The info of the process
			ProcessInfo m_ProcessInfo;

			// Path which exe is in
			ExcutablePath m_ExcutablePath;

			// Disposed status
			BOOL m_Disposed;
		};
	}
}

#endif //PROCESS_TANG_H_