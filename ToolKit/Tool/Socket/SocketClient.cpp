#include "SocketClient.h"

#pragma comment(lib, "wsock32.lib")

using namespace System::Network;

// Construct the SocketClient
SocketClient::SocketClient(IPAddress strIPAddress, NetPort iPortNo) :m_ServerSocket(NULL), 
m_ServerIP(strIPAddress), 
m_ServerPort(iPortNo), 
m_Disposed(false)
{
	Initialize();
}

// Detructe the SocketClient
SocketClient::~SocketClient()
{
	Destory();
}

// Initialize the socket
SocketClient::None SocketClient::Initialize()
{
	CreateSocket(InterNetwork, Stream, Tcp);
}

// Dispose the socket
SocketClient::None SocketClient::Destory()
{
	if (!GetDisposed())
	{
		SetDisposed(true);

		DestorySocket();
	}
}

// Create a socket
SocketClient::None SocketClient::CreateSocket(AddressFamily family, SocketType socketType, ProtocolType protocolType)
{
	SetServerSocket(new Socket(family, socketType, protocolType));
}

// Destory the socket
SocketClient::None SocketClient::DestorySocket()
{
	if (GetServerSocket())
	{
		delete GetServerSocket();

		SetServerSocket(NULL);
	}
}

// Open a server socket
SocketClient::None SocketClient::Open()
{
	if (GetServerSocket())
	{
		GetServerSocket()->Open();
	}
}

// Close the server socket
SocketClient::None SocketClient::Close()
{
	if (GetServerSocket())
	{
		GetServerSocket()->Close();
	}
}

// Connect to the server
SocketClient::BOOL SocketClient::Connect()
{
	if (GetServerSocket())
	{
		return GetServerSocket()->Connect(GetServerIP(), GetServerPort());
	}

	return false;
}

// Start the server
SocketClient::BOOL SocketClient::Start()
{
	// Open the server
	Open();

	// Connect to the server
	return Connect();
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
SocketClient::None SocketClient::Stop()
{
	Close();
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

	if (GetServerSocket())
	{
		bSuccess = GetServerSocket()->Receive(pReadBuffer, iOffset, iReadSize);
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

	if (GetServerSocket())
	{
		bSuccess = GetServerSocket()->Send(pWriteBuffer, iOffset, iWriteSize);
	}

	return bSuccess;
}