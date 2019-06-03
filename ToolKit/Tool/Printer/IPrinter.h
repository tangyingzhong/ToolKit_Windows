///************************************************************************
/// <copyrigth>2018-2019 Corporation. All Rights Reserved</copyrigth>
/// <author>tangyingzhong</author>
/// <contact>tangyz114987@outlook.com</contact>
/// <version>V1.0.0</version>
/// <describe>
/// You can use this interface to operate different type printers
/// USB Printer's GUID is { 0xA5DCBF10L, 0x6530, 0x11D2,0x90, 0x1F, 0x00, 0xC0, 0x4F, 0xB9, 0x51, 0xED }
///</describe>
/// <date>2019/4/25</date>
///***********************************************************************
#ifndef IPRINTER_H
#define IPRINTER_H

#include "Tool\Common\SystemType.h"

namespace System
{
	namespace Peripherals
	{
		class IPrinter
		{
		public:
			typedef System::Boolean BOOL;
			typedef System::Empty Empty;
			typedef System::Object Object;
			typedef System::Byte Byte;
			typedef System::ByteArray ByteArray;
			typedef System::UInt64 Size;
			typedef System::Int32 Index;
			typedef System::Int32 Length;

		public:
			// Distruct the object
			virtual ~IPrinter() {	}

		public:
			// Open the printer
			virtual BOOL Open() = 0;

			// Close the printer
			virtual BOOL Close() = 0;

			// Read data from the printer
			virtual Size Read(ByteArray pReadBuffer, Index iOffset, Length iReadSize) = 0;

			// Write data to the printer
			virtual Size Write(ByteArray pWriteBuffer, Index iOffset, Length iWriteSize) = 0;
		};
	}
}

#endif // IPRINTER_H