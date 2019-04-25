#include "Application\PreCompile.h"
#include "LocalPrinter.h"

using namespace System::Peripherals;

///************************************************************************
/// <summary>
/// Construct the object
/// </summary>
/// <returns></returns>
/// <remarks>
/// None
/// </remarks>
///***********************************************************************
LocalPrinter::LocalPrinter():m_Disposed(false)
{
	Initialize();
}


///************************************************************************
/// <summary>
/// Distruct the object
/// </summary>
/// <returns></returns>
/// <remarks>
/// None
/// </remarks>
///***********************************************************************
LocalPrinter::~LocalPrinter()
{
	Destory();
}


///************************************************************************
/// <summary>
/// Initialize the object
/// </summary>
/// <returns></returns>
/// <remarks>
/// None
/// </remarks>
///***********************************************************************
LocalPrinter::Empty LocalPrinter::Initialize()
{
	// Create a real printer
	this->CreateRealPrinter();
}


///************************************************************************
/// <summary>
/// Destory the object
/// </summary>
/// <returns></returns>
/// <remarks>
/// None
/// </remarks>
///***********************************************************************
LocalPrinter::Empty LocalPrinter::Destory()
{
	if (!this->GetDisposed())
	{
		this->SetDisposed(true);

		// Destory the real printer
		this->DestoryRealPrinter();
	}
}


///************************************************************************
/// <summary>
/// Create a real printer
/// </summary>
/// <returns></returns>
/// <remarks>
/// None
/// </remarks>
///***********************************************************************
LocalPrinter::Empty LocalPrinter::CreateRealPrinter()
{
	String strVID = _T("");

	String strPID = _T("");

	GUID PrinterGUID = { 0xA5DCBF10L, 0x6530, 0x11D2,0x90, 0x1F, 0x00, 0xC0, 0x4F, 0xB9, 0x51, 0xED };

	this->SetRealPrinter(new System::IO::USB(strVID, strPID, PrinterGUID));
}


///************************************************************************
/// <summary>
/// Destory the real printer
/// </summary>
/// <returns></returns>
/// <remarks>
/// None
/// </remarks>
///***********************************************************************
LocalPrinter::Empty LocalPrinter::DestoryRealPrinter()
{
	if (this->GetRealPrinter())
	{
		delete this->GetRealPrinter();

		this->SetRealPrinter(NULL);
	}
}


///************************************************************************
/// <summary>
/// Open the printer
/// </summary>
/// <returns></returns>
/// <remarks>
/// None
/// </remarks>
///***********************************************************************
LocalPrinter::BOOL LocalPrinter::Open()
{
	BOOL bOpened = false;


	return bOpened;
}


///************************************************************************
/// <summary>
/// Close the printer
/// </summary>
/// <returns></returns>
/// <remarks>
/// None
/// </remarks>
///***********************************************************************
LocalPrinter::BOOL LocalPrinter::Close()
{
	BOOL bClosed = false;


	return bClosed;
}


///************************************************************************
/// <summary>
/// Read data from the printer
/// </summary>
/// <param name=ByteArray pReadBuffer></param>
/// <param name=Index iOffset></param>
/// <param name=Length iReadSize></param>
/// <returns></returns>
/// <remarks>
/// None
/// </remarks>
///***********************************************************************
LocalPrinter::Size LocalPrinter::Read(ByteArray pReadBuffer, Index iOffset, Length iReadSize)
{
	Size dwReadSize = 0;


	return dwReadSize;
}


///************************************************************************
/// <summary>
/// Write data to the printer
/// </summary>
/// <param name=ByteArray pWriteBuffer></param>
/// <param name=Index iOffset></param>
/// <param name=Length iWriteSize></param>
/// <returns></returns>
/// <remarks>
/// Note: you can write the data or ESC command to the printer
/// </remarks>
///***********************************************************************
LocalPrinter::Size LocalPrinter::Write(ByteArray pWriteBuffer, Index iOffset, Length iWriteSize)
{
	Size dwWriteSize = 0;


	return dwWriteSize;
}