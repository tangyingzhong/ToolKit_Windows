///************************************************************************
/// <copyrigth>2018-2019 Corporation.All Rights Reserved</copyrigth>
/// <author>tangyingzhong</author>
/// <contact>tangyz114987@outlook.com</contact>
/// <version>v1.0.0</version>
/// <describe>
/// Serial port's operation supported here
///</describe>
/// <date>2019/7/16</date>
///***********************************************************************
#ifndef SERIALPORT_H
#define SERIALPORT_H

#include "PortType.h"
#include "Tool/BaseType/String.h"

using namespace System::BasicType;

namespace System
{
	namespace IO
	{
		class SerialPort
		{
		public:
			typedef System::None None;
			typedef System::Boolean BOOL;
			typedef System::Byte Byte;
			typedef System::ByteArray ByteArray;	
			typedef System::FILE_ATTRIBUTE_ENUM FileAttrEnum;
			typedef System::FileAttribute FileAttribute;
			typedef System::Object PortHandle;
			typedef System::Int32 Offset;
			typedef System::Int32 TimeoutMs;
			typedef System::Int32 PortSize;
			typedef System::FILE_MODE_ENUM FileMode;
			typedef System::FILE_ACCESS_ENUM FileAccess;
			typedef System::SEEK_ORIGIN_ENUM SeekOrigin;
			typedef System::FILE_ATTRIBUTE_ENUM FileAttrEnum;
			typedef PortSize ArraySize;
			typedef DCB DCBBlock;
			typedef COMMTIMEOUTS TimeOut;
			typedef BOUNDRATE_ENUM BoundRate;
			typedef PARITY_ENUM Parity;
			typedef DATABIT_ENUM DataBits;
			typedef STOPBIT_ENUM StopBits;
			typedef PORT_TIMEOUT_ENUM PortTimeOut;
			typedef PORT_CACHE_ENUM PortCache;
			typedef PORT_CACHE_STATE_ENUM CacheStatus;

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
			virtual None Close();

			// Clear the port
			virtual None Clear();

		private:
			// Init the port
			None Initialize();

			// Destory the port
			None Destory();

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
			inline None SetPortHandle(PortHandle hPortHandle)
			{
				m_PortHandle = hPortHandle;
			}

			// Get the disposed status
			inline BOOL GetDisposed() const
			{
				return m_Disposed;
			}

			// Set the disposed status
			inline None SetDisposed(BOOL bDisposed)
			{
				m_Disposed = bDisposed;
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