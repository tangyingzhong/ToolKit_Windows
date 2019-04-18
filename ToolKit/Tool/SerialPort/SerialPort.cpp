#include "Application\PreCompile.h"
#include "SerialPort.h"

using namespace System::IO;

///************************************************************************
/// <summary>
/// construct an unknown port 
/// </summary>
/// <returns></returns>
/// <remarks>
/// none
/// </remarks>
///***********************************************************************
SerialPort::SerialPort() :m_PortHandle(NULL), m_Disposed(false)
{
	Initialize();
}


///************************************************************************
/// <summary>
/// destory the port
/// </summary>
/// <returns></returns>
/// <remarks>
/// none
/// </remarks>
///***********************************************************************
SerialPort::~SerialPort()
{
	Destory();
}


///************************************************************************
/// <summary>
/// init a serial port
/// </summary>
/// <returns></returns>
/// <remarks>
/// none
/// </remarks>
///***********************************************************************
SerialPort::Empty SerialPort::Initialize()
{

}


///************************************************************************
/// <summary>
/// dispose the port source
/// </summary>
/// <returns></returns>
/// <remarks>
/// none
/// </remarks>
///***********************************************************************
SerialPort::Empty SerialPort::Destory()
{
	if (!GetDisposed())
	{
		SetDisposed(true);

		// Close the port
		this->Close();
	}
}


///************************************************************************
/// <summary>
/// Set the port's read time out
/// </summary>
/// <param name=readMs>time (ms)</param>
/// <returns></returns>
/// <remarks>
/// none
/// </remarks>
///***********************************************************************
SerialPort::BOOL SerialPort::SetReadTimeout(TimeoutMs iReadMs)
{
	BOOL bSuccess = false;

	assert(this->GetPortHandle() != NULL);

	if (this->GetPortHandle() == NULL)
	{
		return bSuccess;
	}

	// Get the primary time out
	TimeOut ComTimeout;
	if (::GetCommTimeouts(this->GetPortHandle(), &ComTimeout) == FALSE)
	{
		return bSuccess;
	}

	// Set the time 
	ComTimeout.ReadIntervalTimeout = PortTimeOut::PORT_READ_INTERVAL;
	ComTimeout.ReadTotalTimeoutMultiplier = PortTimeOut::PORT_READ_MULTIPLE;
	ComTimeout.ReadTotalTimeoutConstant = iReadMs;

	// Set the time out
	if (::SetCommTimeouts(this->GetPortHandle(), &ComTimeout) == FALSE)
	{
		return bSuccess;
	}

	bSuccess = true;

	return bSuccess;
}


///************************************************************************
/// <summary>
/// Set the port's write's time out
/// </summary>
/// <param name=writeMs>time (ms)</param>
/// <returns></returns>
/// <remarks>
/// none
/// </remarks>
///***********************************************************************
SerialPort::BOOL SerialPort::SetWriteTimeout(TimeoutMs iWriteMs)
{
	BOOL bSuccess = false;

	assert(this->GetPortHandle() != NULL);

	if (this->GetPortHandle() == NULL)
	{
		return bSuccess;
	}

	// Get the primary time out
	TimeOut ComTimeout;
	if (::GetCommTimeouts(this->GetPortHandle(), &ComTimeout) == FALSE)
	{
		return bSuccess;
	}

	// Set the time 
	ComTimeout.WriteTotalTimeoutMultiplier = PortTimeOut::PORT_WRITE_MULTIPLE;
	ComTimeout.WriteTotalTimeoutConstant = iWriteMs;

	// Set the time out
	if (::SetCommTimeouts(this->GetPortHandle(), &ComTimeout) == FALSE)
	{
		return bSuccess;
	}

	bSuccess = true;

	return bSuccess;
}


///************************************************************************
/// <summary>
/// create a port
/// </summary>
/// <param name=portName>port's path in os</param>
/// <param name=attr>the atrribute of port</param>
/// <returns>FAILED or SUCCESS</returns>
/// <remarks>
/// none
/// </remarks>
///***********************************************************************
SerialPort::BOOL SerialPort::_CreateFile(String strPortName, FileAttrEnum eFileAttribute)
{
	BOOL bSuccess = false;

	assert(this->GetPortHandle() != NULL);

	if (this->GetPortHandle() == NULL)
	{
		return bSuccess;
	}

	this->SetPortHandle(::CreateFile(strPortName, FileAccess::READWRITE, 0, NULL, FileMode::OPEN, eFileAttribute, NULL));
	if (this->GetPortHandle() == INVALID_HANDLE_VALUE)
	{
		this->Close();

		return bSuccess;
	}

	bSuccess = true;

	return bSuccess;
}


///************************************************************************
/// <summary>
/// config the port
/// </summary>
/// <param name=rate>bound reate</param>
/// <param name=parity>parity </param>
/// <param name=dataBits>transfer data's width</param>
/// <param name=stopBits>stop bit</param>
/// <returns></returns>
/// <remarks>
/// none
/// </remarks>
///***********************************************************************
SerialPort::BOOL SerialPort::Configure(BoundRate eBoundRate, Parity eParity, DataBits eDataBits, StopBits eStopBits)
{
	BOOL bSuccess = false;

	// Setup the port
	bSuccess = this->SetupPort();
	if (!bSuccess)
	{
		return bSuccess;
	}

	// Set the DCB 
	bSuccess = this->SetupDCB(eBoundRate, eParity, eDataBits, eStopBits);
	if (!bSuccess)
	{
		return bSuccess;
	}

	// Set the timeout
	bSuccess = this->SetupTimeout();
	if (!bSuccess)
	{
		return bSuccess;
	}

	// Clear the port cache
	bSuccess = this->ClearCache();
	if (!bSuccess)
	{
		return bSuccess;
	}

	return bSuccess;
}


///************************************************************************
/// <summary>
/// setup the port's cache
/// </summary>
/// <returns></returns>
/// <remarks>
/// none
/// </remarks>
///***********************************************************************
SerialPort::BOOL SerialPort::SetupPort()
{
	BOOL bSuccess = false;

	assert(this->GetPortHandle() != NULL);

	if (this->GetPortHandle() == NULL)
	{
		return bSuccess;
	}

	if (::SetupComm(this->GetPortHandle(), PortCache::PORT_INPUT_CACHE_SIZE, PortCache::PORT_OUTPUT_CACHE_SIZE) == FALSE)
	{
		return bSuccess;
	}

	bSuccess = true;

	return bSuccess;
}



///************************************************************************
/// <summary>
/// setup the port's DCB struct
/// </summary>
/// <param name=rate>bound reate</param>
/// <param name=parity>parity</param>
/// <param name=dataBits>every data's width</param>
/// <param name=stopBits>stop bit</param>
/// <returns></returns>
/// <remarks>
/// none
/// </remarks>
///***********************************************************************
SerialPort::BOOL SerialPort::SetupDCB(BoundRate eBoundRate, Parity eParity, DataBits eDataBits, StopBits eStopBits)
{
	BOOL bSuccess = false;

	assert(this->GetPortHandle() != NULL);

	if (this->GetPortHandle() == NULL)
	{
		return bSuccess;
	}

	// Get the primary DCB
	DCBBlock DcbBlock;
	if (::GetCommState(GetPortHandle(), &DcbBlock) == FALSE)
	{
		return bSuccess;
	}

	// Set the DcbBlock
	DcbBlock.BaudRate = eBoundRate;
	DcbBlock.Parity = eParity;
	DcbBlock.ByteSize = eDataBits;
	DcbBlock.StopBits = eStopBits;

	// Set the portComm
	if (::SetCommState(GetPortHandle(), &DcbBlock) == FALSE)
	{
		return bSuccess;
	}

	bSuccess = true;

	return bSuccess;
}


///************************************************************************
/// <summary>
/// setup read write time out by default
/// </summary>
/// <returns></returns>
/// <remarks>
/// none
/// </remarks>
///***********************************************************************
SerialPort::BOOL SerialPort::SetupTimeout()
{
	BOOL bSuccess = false;

	assert(this->GetPortHandle() != NULL);

	if (this->GetPortHandle() == NULL)
	{
		return bSuccess;
	}

	// Set read time out
	bSuccess = this->SetReadTimeout(PortTimeOut::PORT_READ_CONSTANT);
	if (!bSuccess)
	{
		return bSuccess;
	}

	// Set write time out
	bSuccess = this->SetWriteTimeout(PortTimeOut::PORT_WRITE_CONSTANT);
	if (!bSuccess)
	{
		return bSuccess;
	}

	return bSuccess;
}


///************************************************************************
/// <summary>
/// clear the port's tx and rx buffer in the driver
/// </summary>
/// <returns></returns>
/// <remarks>
/// none
/// </remarks>
///***********************************************************************
SerialPort::BOOL SerialPort::ClearCache()
{
	BOOL bSuccess = false;

	assert(this->GetPortHandle() != NULL);

	if (this->GetPortHandle() == NULL)
	{
		return bSuccess;
	}

	if (::PurgeComm(this->GetPortHandle(), CacheStatus::ABORTRX | CacheStatus::ABORTTX | CacheStatus::CLEARRX | CacheStatus::CLEARTX) == FALSE)
	{
		return bSuccess;
	}

	bSuccess = true;

	return bSuccess;
}


///************************************************************************
/// <summary>
/// open the serialport
/// </summary>
/// <param name=portName>port path</param>
/// <param name=rate>bound rate</param>
/// <param name=parity>parity</param>
/// <param name=dataBits>data width</param>
/// <param name=stopBits>stop bits</param>
/// <returns></returns>
/// <remarks>
/// none
/// </remarks>
///***********************************************************************
SerialPort::BOOL SerialPort::Open(const String& strPortName, BoundRate eBoundRate, Parity eParity, DataBits eDataBits, StopBits eStopBits)
{
	BOOL bSuccess = false;

	// Create port
	bSuccess = this->_CreateFile(strPortName, FileAttrEnum::NORMAL);
	if (!bSuccess)
	{
		return bSuccess;
	}

	// Config the port
	bSuccess = this->Configure(eBoundRate, eParity, eDataBits, eStopBits);
	if (!bSuccess)
	{
		return bSuccess;
	}

	return bSuccess;
}


///************************************************************************
/// <summary>
/// read the port
/// </summary>
/// <param name=arr>buffer</param>
/// <param name=offset>offset of buffer</param>
/// <param name=readSize>buffer size</param>
/// <returns>real reading size</returns>
/// <remarks>
/// none
/// </remarks>
///***********************************************************************
SerialPort::PortSize SerialPort::Read(ByteArray pReadArray, Offset iOffset, ArraySize iReadSize)
{
	System::UInt64 dwBytesRead = 0;

	assert(this->GetPortHandle() != NULL);

	if (this->GetPortHandle() == NULL)
	{
		return dwBytesRead;
	}

	// Clear the port error
	System::UInt64 dwErrorFlags;
	COMSTAT ComState;
	if (::ClearCommError(GetPortHandle(), &dwErrorFlags, &ComState) == FALSE)
	{
		return dwBytesRead;
	}

	// Read the bytes
	::ReadFile(this->GetPortHandle(), pReadArray + iOffset, iReadSize, &dwBytesRead, NULL);

	return dwBytesRead;
}


///************************************************************************
/// <summary>
/// write to the port
/// </summary>
/// <param name=arr>buffer</param>
/// <param name=offset>offset of buffer</param>
/// <param name=writeSize>buffer size</param>
/// <returns>real writing size</returns>
/// <remarks>
/// none
/// </remarks>
///***********************************************************************
SerialPort::PortSize SerialPort::Write(ByteArray pWriteArray, Offset iOffset, ArraySize iWriteSize)
{
	System::UInt64 dwBytesWrite = 0;

	assert(this->GetPortHandle() != NULL);

	if (this->GetPortHandle() == NULL)
	{
		return dwBytesWrite;
	}

	// Clear the port error
	System::UInt64 dwErrorFlags;
	COMSTAT ComState;
	if (::ClearCommError(GetPortHandle(), &dwErrorFlags, &ComState) == FALSE)
	{
		return dwBytesWrite;
	}

	// Write the bytes
	::WriteFile(this->GetPortHandle(), pWriteArray + iOffset, iWriteSize, &dwBytesWrite, NULL);

	return dwBytesWrite;
}


///************************************************************************
/// <summary>
/// close the port
/// </summary>
/// <returns></returns>
/// <remarks>
/// none
/// </remarks>
///***********************************************************************
SerialPort::Empty SerialPort::Close()
{
	if (this->GetPortHandle())
	{
		::CloseHandle(this->GetPortHandle());

		this->SetPortHandle(NULL);
	}
}


///************************************************************************
/// <summary>
/// clear the resource having by the port
/// </summary>
/// <returns></returns>
/// <remarks>
/// none
/// </remarks>
///***********************************************************************
SerialPort::Empty SerialPort::Clear()
{
	this->ClearCache();
}