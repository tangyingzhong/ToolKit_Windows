#include "Application\PreCompile.h"
#include "NetPrinter.h"

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
NetPrinter::NetPrinter() :m_Disposed(false)
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
NetPrinter::~NetPrinter()
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
NetPrinter::Empty NetPrinter::Initialize()
{

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
NetPrinter::Empty NetPrinter::Destory()
{


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
NetPrinter::BOOL NetPrinter::Open()
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
NetPrinter::BOOL NetPrinter::Close()
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
NetPrinter::Size NetPrinter::Read(ByteArray pReadBuffer, Index iOffset, Length iReadSize)
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
NetPrinter::Size NetPrinter::Write(ByteArray pWriteBuffer, Index iOffset, Length iWriteSize)
{
	Size dwWriteSize = 0;


	return dwWriteSize;
}