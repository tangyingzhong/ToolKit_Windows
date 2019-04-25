///************************************************************************
/// <copyrigth>2018-2019 Corporation. All Rights Reserved</copyrigth>
/// <author>tangyingzhong</author>
/// <contact>tangyz114987@outlook.com</contact>
/// <version>V1.0.0</version>
/// <describe>
/// Local printer which can be used with SerialPort or USB or LPT
///</describe>
/// <date>2019/4/25</date>
///***********************************************************************
#ifndef LOCALPRINTER_H
#define LOCALPRINTER_H

#include "Tool\Printer\IPrinter.h"
#include "Tool\USB\USB.h"

namespace System
{
	namespace Peripherals
	{
		///*********************************************************
		/// <class> LocalPrinter </class>
		/// <summary>
		/// It is a higher level abstract for local printer so that it must
		/// support different type connection to printer,such as COM,USB,LPT
		/// But it is more difficult to use because of its needing ESC command
		/// to operate the printer.
		/// </summary>
		/// <version>V1.0.0 </version>
		/// <goup> C++</group>
		/// <author>tangyingzhong</author>
		/// <contact>tangyz114987@outlook.com</contact>
		///*********************************************************
		class LocalPrinter :public IPrinter
		{
		public:
			typedef System::IO::USB* RealPrinter;

		public:
			// Construct the object
			LocalPrinter();

			// Distruct the object
			~LocalPrinter();

		private:
			// Defualt implement the copy construct
			LocalPrinter(const LocalPrinter& other) {	}

			// Default implement the object assignment
			LocalPrinter& operator=(const LocalPrinter& other) {	}

		public:
			// Open the printer
			virtual BOOL Open();

			// Close the printer
			virtual BOOL Close();

			// Read data from the printer
			virtual Size Read(ByteArray pReadBuffer, Index iOffset, Length iReadSize);

			// Write data to the printer
			virtual Size Write(ByteArray pWriteBuffer, Index iOffset, Length iWriteSize);

		private:
			// Initialize the object
			Empty Initialize();

			// Destory the object
			Empty Destory();

			// Create a real printer
			Empty CreateRealPrinter();

			// Destory the real printer
			Empty DestoryRealPrinter();

		private:
			// Get RealPrinter
			inline RealPrinter GetRealPrinter() const
			{
				return m_RealPrinter;
			}

			// Set RealPrinter
			inline Empty SetRealPrinter(RealPrinter pRealPrinter)
			{
				this->m_RealPrinter = pRealPrinter;
			}

			// Get disposed status
			inline BOOL GetDisposed() const
			{
				return this->m_Disposed;
			}

			// Set disposed status
			inline Empty SetDisposed(BOOL bDisposed)
			{
				this->m_Disposed = bDisposed;
			}

		private:
			// Real printer 
			RealPrinter m_RealPrinter;
			
			// Disposed status
			BOOL m_Disposed;
		};
	}
}

#endif //LOCALPRINTER_H