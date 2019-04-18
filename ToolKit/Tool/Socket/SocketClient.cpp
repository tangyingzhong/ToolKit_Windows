#include "Application\PreCompile.h"
#include "SocketClient.h"

#pragma comment(lib, "wsock32.lib")

using namespace System::Network;

///************************************************************************
/// <summary>
/// Construct the SocketClient
/// </summary>
/// <returns></returns>
/// <remarks>
/// none
/// </remarks>
///***********************************************************************
SocketClient::SocketClient(IPAddress strIPAddress, NetPort iPortNo) :m_ServerSocket(NULL), m_ServerIP(strIPAddress), m_ServerPort(iPortNo), m_Disposed(false)
{
	Initialize();
}



///************************************************************************
/// <summary>
/// Detructe the SocketClient
/// </summary>
/// <returns></returns>
/// <remarks>
/// none
/// </remarks>
///***********************************************************************
SocketClient::~SocketClient()
{
	Destory();
}


///************************************************************************
/// <summary>
/// Initialize the socket
/// </summary>
/// <returns></returns>
/// <remarks>
/// none
/// </remarks>
///***********************************************************************
SocketClient::Empty SocketClient::Initialize()
{
	// Create a socket
	this->CreateSocket(AddressFamily::InterNetwork, SocketType::Stream, ProtocolType::Tcp);
}


///************************************************************************
/// <summary>
/// Dispose the socket
/// </summary>
/// <returns></returns>
/// <remarks>
/// none
/// </remarks>
///***********************************************************************
SocketClient::Empty SocketClient::Destory()
{
	if (!GetDisposed())
	{
		SetDisposed(true);

		// Destory the socket
		this->DestorySocket();
	}
}


///************************************************************************
/// <summary>
/// Create a socket
/// </summary>
/// <param name=family></param>
/// <param name=socketType></param>
/// <param name=protocolType></param>
/// <returns></returns>
/// <remarks>
/// none
/// </remarks>
///***********************************************************************
SocketClient::Empty SocketClient::CreateSocket(AddressFamily family, SocketType socketType, ProtocolType protocolType)
{
	this->SetServerSocket(new Socket(family, socketType, protocolType));
}


///************************************************************************
/// <summary>
/// Destory the socket
/// </summary>
/// <returns></returns>
/// <remarks>
/// none
/// </remarks>
///***********************************************************************
SocketClient::Empty SocketClient::DestorySocket()
{
	if (this->GetServerSocket())
	{
		delete this->GetServerSocket();
		this->SetServerSocket(NULL);
	}
}


///************************************************************************
/// <summary>
/// Open a server socket
/// </summary>
/// <param name=portNo></param>
/// <returns></returns>
/// <remarks>
/// none
/// </remarks>
///***********************************************************************
SocketClient::Empty SocketClient::Open()
{
	if (this->GetServerSocket())
	{
		this->GetServerSocket()->Open();
	}
}


///************************************************************************
/// <summary>
/// Close the server socket
/// </summary>
/// <returns></returns>
/// <remarks>
/// none
/// </remarks>
///***********************************************************************
SocketClient::Empty SocketClient::Close()
{
	if (this->GetServerSocket())
	{
		this->GetServerSocket()->Close();
	}
}


///************************************************************************
/// <summary>
/// Connect to the server
/// </summary>
/// <returns></returns>
/// <remarks>
/// none
/// </remarks>
///***********************************************************************
SocketClient::BOOL SocketClient::Connect()
{
	BOOL bSuccess = false;

	if (this->GetServerSocket())
	{
		bSuccess = this->GetServerSocket()->Connect(this->GetServerIP(), this->GetServerPort());
	}

	return bSuccess;
}


///************************************************************************
/// <summary>
/// Start the server
/// </summary>
/// <returns></returns>
/// <remarks>
/// none
/// </remarks>
///***********************************************************************
SocketClient::BOOL SocketClient::Start()
{
	BOOL bSuccess = false;

	// Open the server
	this->Open();

	// Connect to the server
	bSuccess = this->Connect();

	return bSuccess;
}


///************************************************************************
/// <summary>
/// Stop the server
/// </summary>
/// <returns></returns>
/// <remarks>
/// none
/// </remarks>
///***********************************************************************
SocketClient::Empty SocketClient::Stop()
{
	this->Close();
}

///************************************************************************
/// <summary>
/// Receive the data from the client
/// </summary>
/// <param name=buffer></param>
/// <param name=offset></param>
/// <param name=len></param>
/// <returns></returns>
/// <remarks>
/// none
/// </remarks>
///***********************************************************************
SocketClient::BOOL SocketClient::Receive(SByteArray pReadBuffer, Length iOffset, Length iReadSize)
{
	BOOL bSuccess = false;

	if (this->GetServerSocket())
	{
		bSuccess = this->GetServerSocket()->Receive(pReadBuffer, iOffset, iReadSize);
	}

	return bSuccess;
}


///************************************************************************
/// <summary>
/// Send the data to the client
/// </summary>
/// <param name=buffer></param>
/// <param name=offset></param>
/// <param name=len></param>
/// <returns></returns>
/// <remarks>
/// none
/// </remarks>
///***********************************************************************
SocketClient::BOOL SocketClient::Send(SByteArray pWriteBuffer, Length iOffset, Length iWriteSize)
{
	BOOL bSuccess = false;

	if (this->GetServerSocket())
	{
		bSuccess = this->GetServerSocket()->Send(pWriteBuffer, iOffset, iWriteSize);
	}

	return bSuccess;
}