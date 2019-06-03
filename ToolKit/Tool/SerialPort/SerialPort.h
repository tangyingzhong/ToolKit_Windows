///************************************************************************
/// <copyrigth>2018-2019 Corporation.All Rights Reserved</copyrigth>
/// <author>tangyingzhong</author>
/// <contact>tangyz114987@outlook.com</contact>
/// <version>V1.0.0</version>
/// <describe>
/// Serial port's operation supported here
///</describe>
/// <date>2019/3/6</date>
///***********************************************************************
#ifndef SERIALPORT_H
#define SERIALPORT_H

#include "Tool\BaseType\String.h"

using namespace System::BasicType;

namespace System
{
	namespace IO
	{
		class SerialPort
		{
		public:
			typedef System::Empty Empty;
			typedef System::Boolean BOOL;
			typedef System::Byte Byte;
			typedef System::ByteArray ByteArray;
			typedef System::BoundRate BoundRate;
			typedef System::Parity Parity;
			typedef System::DataBits DataBits;
			typedef System::StopBits StopBits;
			typedef System::PortTimeOut PortTimeOut;
			typedef System::FileAttrEnum FileAttrEnum;
			typedef System::FileAttribute FileAttribute;
			typedef System::Object PortHandle;
			typedef System::Int32 Offset;
			typedef System::Int32 TimeoutMs;
			typedef System::Int32 PortSize;
			typedef PortSize ArraySize;
			typedef DCB DCBBlock;
			typedef COMMTIMEOUTS TimeOut;

		public:
			// Construct the port with port's name
			SerialPort();

			// Destruct the port
			~SerialPort();

		private:
			// Copy the port
			SerialPort(const SerialPort& other) {	}

			// Assignment of port
			SerialPort& operator=(const SerialPort& other) {	}

		public:
			// Open the port with rate,parity,databits,stopbits
			virtual BOOL Open(const String& strPortName,
				BoundRate eBoundRate = BoundRate::PORT_SUPER_SPEED,
				Parity eParity = Parity::PORT_NO,
				DataBits eDataBits = DataBits::PORT_EIGHT,
				StopBits eStopBits = StopBits::PORT_ONE);

			// Read the port
			virtual PortSize Read(ByteArray pReadArray, Offset iOffset, ArraySize iReadSize);

			// Write to the port
			virtual PortSize Write(ByteArray pWriteArray, Offset iOffset, ArraySize iWriteSize);

			// Set total read time out
			virtual BOOL SetReadTimeout(TimeoutMs iReadMs);

			// Set toal write time out
			virtual BOOL SetWriteTimeout(TimeoutMs iWriteMs);

			// Close the port
			virtual Empty Close();

			// Clear the port
			virtual Empty Clear();

		private:
			// Init the port
			Empty Initialize();

			// Destory the port
			Empty Destory();

			// Configure the port
			BOOL Configure(BoundRate eBoundRate, Parity eParity, DataBits eDataBits, StopBits eStopBits);

			// Setup the port
			BOOL SetupPort();

			// Setup the DCB
			BOOL SetupDCB(BoundRate eBoundRate, Parity eParity, DataBits eDataBits, StopBits eStopBits);

			// Setup the time out
			BOOL SetupTimeout();

			// Clear the port cache
			BOOL ClearCache();

			// Create the File
			BOOL _CreateFile(String strPortName, FileAttrEnum eFileAttribute);

		private:
			// Get the PortHandle
			inline PortHandle GetPortHandle() const
			{
				return m_PortHandle;
			}

			// Set the PortHandle
			inline Empty SetPortHandle(PortHandle hPortHandle)
			{
				this->m_PortHandle = hPortHandle;
			}

			// Get the disposed status
			inline BOOL GetDisposed() const
			{
				return m_Disposed;
			}

			// Set the disposed status
			inline Empty SetDisposed(BOOL bDisposed)
			{
				this->m_Disposed = bDisposed;
			}

		private:
			// The handle of the port
			PortHandle m_PortHandle;

			// Disposed status
			BOOL m_Disposed;
		};
	}
}

#endif // SERIALPORT_H