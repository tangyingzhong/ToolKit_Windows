///************************************************************************
/// <copyrigth>2018-2019 Corporation. All Rights Reserved</copyrigth>
/// <author>tangyingzhong</author>
/// <contact>tangyz114987@outlook.com</contact>
/// <version>V1.0.0</version>
/// <describe>
/// Net printer which always works by TCP/IP protocol
///</describe>
/// <date>2019/4/25</date>
///***********************************************************************
#ifndef NETPRINTER_H
#define NETPRINTER_H

#include "Tool\Printer\IPrinter.h"

namespace System
{
	namespace Peripherals
	{
		///*********************************************************
		/// <class> NetPrinter </class>
		/// <summary>
		/// It is a higher level abstract for net printer
		/// </summary>
		/// <version>V1.0.0 </version>
		/// <goup> C++</group>
		/// <author>tangyingzhong</author>
		/// <contact>tangyz114987@outlook.com</contact>
		///*********************************************************
		class NetPrinter :public IPrinter
		{
		public:
			
		public:
			// Construct the object
			NetPrinter();

			// Distruct the object
			~NetPrinter();

		private:
			// Defualt implement the copy construct
			NetPrinter(const NetPrinter& other) {	}

			// Default implement the object assignment
			NetPrinter& operator=(const NetPrinter& other) {	}

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

		private:
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
			// Disposed status
			BOOL m_Disposed;
		};
	}
}

#endif //NETPRINTER_H