#include "SerialPort.h"

using namespace System::IO;

// construct an unknown port 
SerialPort::SerialPort() :m_PortHandle(NULL), m_Disposed(false)
{
	Initialize();
}

// destory the port
SerialPort::~SerialPort()
{
	Destory();
}

// Init a serial port
SerialPort::None SerialPort::Initialize()
{

}

// Dispose the port source
SerialPort::None SerialPort::Destory()
{
	if (!GetDisposed())
	{
		SetDisposed(true);

		Close();
	}
}

// Set the port's read time out
SerialPort::BOOL SerialPort::SetReadTimeout(TimeoutMs iReadMs)
{
	if (GetPortHandle() == NULL)
	{
		return false;
	}

	// Get the primary time out
	TimeOut ComTimeout;
	if (::GetCommTimeouts(GetPortHandle(), &ComTimeout) == FALSE)
	{
		return false;
	}

	// Set the time 
	ComTimeout.ReadIntervalTimeout = PortTimeOut::PORT_READ_INTERVAL;

	ComTimeout.ReadTotalTimeoutMultiplier = PortTimeOut::PORT_READ_MULTIPLE;

	ComTimeout.ReadTotalTimeoutConstant = iReadMs;

	// Set the time out
	if (::SetCommTimeouts(GetPortHandle(), &ComTimeout) == FALSE)
	{
		return false;
	}

	return true;
}

// Set the port's write's time out
SerialPort::BOOL SerialPort::SetWriteTimeout(TimeoutMs iWriteMs)
{
	if (GetPortHandle() == NULL)
	{
		return false;
	}

	// Get the primary time out
	TimeOut ComTimeout;
	if (::GetCommTimeouts(GetPortHandle(), &ComTimeout) == FALSE)
	{
		return false;
	}

	// Set the time 
	ComTimeout.WriteTotalTimeoutMultiplier = PortTimeOut::PORT_WRITE_MULTIPLE;

	ComTimeout.WriteTotalTimeoutConstant = iWriteMs;

	// Set the time out
	if (::SetCommTimeouts(GetPortHandle(), &ComTimeout) == FALSE)
	{
		return false;
	}

	return true;
}

// Create a port
SerialPort::BOOL SerialPort::_CreateFile(String strPortName, FileAttrEnum eFileAttribute)
{
	if (GetPortHandle() == NULL)
	{
		return false;
	}

	SetPortHandle(::CreateFile(strPortName.CStr(),
		FileAccess::READWRITE, 
		0, 
		NULL, 
		FileMode::OPEN, 
		eFileAttribute, 
		NULL));
	if (GetPortHandle() == INVALID_HANDLE_VALUE)
	{
		Close();

		return false;
	}

	return true;
}

// config the port
SerialPort::BOOL SerialPort::Configure(BoundRate eBoundRate, Parity eParity, DataBits eDataBits, StopBits eStopBits)
{
	// Setup the port
	if (!SetupPort())
	{
		return false;
	}

	// Set the DCB 
	if (!SetupDCB(eBoundRate, eParity, eDataBits, eStopBits))
	{
		return false;
	}

	// Set the timeout
	if (!SetupTimeout())
	{
		return false;
	}

	// Clear the port cache
	if (!ClearCache())
	{
		return false;
	}

	return true;
}

// Setup the port's cache
SerialPort::BOOL SerialPort::SetupPort()
{
	if (GetPortHandle() == NULL)
	{
		return false;
	}

	if (::SetupComm(GetPortHandle(), PORT_INPUT_CACHE_SIZE, PORT_OUTPUT_CACHE_SIZE) == FALSE)
	{
		return false;
	}

	return true;
}

// Setup the port's DCB struct
SerialPort::BOOL SerialPort::SetupDCB(BoundRate eBoundRate, Parity eParity, DataBits eDataBits, StopBits eStopBits)
{
	if (GetPortHandle() == NULL)
	{
		return false;
	}

	// Get the primary DCB
	DCBBlock DcbBlock;
	if (::GetCommState(GetPortHandle(), &DcbBlock) == FALSE)
	{
		return false;
	}

	// Set the DcbBlock
	DcbBlock.BaudRate = eBoundRate;
	DcbBlock.Parity = eParity;
	DcbBlock.ByteSize = eDataBits;
	DcbBlock.StopBits = eStopBits;

	// Set the portComm
	if (::SetCommState(GetPortHandle(), &DcbBlock) == FALSE)
	{
		return false;
	}

	return true;
}

// Setup read write time out by default
SerialPort::BOOL SerialPort::SetupTimeout()
{
	if (GetPortHandle() == NULL)
	{
		return false;
	}

	// Set read time out
	if (!SetReadTimeout(PORT_READ_CONSTANT))
	{
		return false;
	}

	// Set write time out
	if (!SetWriteTimeout(PORT_WRITE_CONSTANT))
	{
		return false;
	}

	return true;
}

// Clear the port's tx and rx buffer in the driver
SerialPort::BOOL SerialPort::ClearCache()
{
	if (GetPortHandle() == NULL)
	{
		return false;
	}

	if (::PurgeComm(GetPortHandle(), ABORTRX | ABORTTX | CLEARRX | CLEARTX) == FALSE)
	{
		return false;
	}

	return true;
}

// Open the serialport
SerialPort::BOOL SerialPort::Open(const String& strPortName, 
	BoundRate eBoundRate, 
	Parity eParity, 
	DataBits eDataBits, 
	StopBits eStopBits)
{
	// Create port
	if (!_CreateFile(strPortName, FileAttrEnum::NORMAL))
	{
		return false;
	}

	// Config the port
	if (!Configure(eBoundRate, eParity, eDataBits, eStopBits))
	{
		return false;
	}

	return false;
}

// Read the port
SerialPort::PortSize SerialPort::Read(ByteArray pReadArray, Offset iOffset, ArraySize iReadSize)
{
	if (GetPortHandle() == NULL)
	{
		return 0;
	}

	// Clear the port error
	System::FixedUInt32 dwErrorFlags;

	COMSTAT ComState;

	if (::ClearCommError(GetPortHandle(), &dwErrorFlags, &ComState) == FALSE)
	{
		return 0;
	}

	// Read the bytes
	System::FixedUInt32 dwBytesRead = 0;

	if (::ReadFile(GetPortHandle(), pReadArray + iOffset, iReadSize, &dwBytesRead, NULL)==FALSE)
	{
		return 0;
	}

	return dwBytesRead;
}

// Write to the port
SerialPort::PortSize SerialPort::Write(ByteArray pWriteArray, Offset iOffset, ArraySize iWriteSize)
{
	if (GetPortHandle() == NULL)
	{
		return 0;
	}

	// Clear the port error
	System::FixedUInt32 dwErrorFlags;

	COMSTAT ComState;

	if (::ClearCommError(GetPortHandle(), &dwErrorFlags, &ComState) == FALSE)
	{
		return 0;
	}

	// Write the bytes
	System::FixedUInt32 dwBytesWrite = 0;

	if (::WriteFile(GetPortHandle(), pWriteArray + iOffset, iWriteSize, &dwBytesWrite, NULL) == FALSE)
	{
		return 0;
	}

	return dwBytesWrite;
}

// Close the port
SerialPort::None SerialPort::Close()
{
	if (GetPortHandle())
	{
		::CloseHandle(GetPortHandle());

		SetPortHandle(NULL);
	}
}

// Clear the resource having by the port
SerialPort::None SerialPort::Clear()
{
	ClearCache();
}