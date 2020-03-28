#include "SocketServer.h"

#pragma comment(lib, "wsock32.lib")

using namespace System::Network;

// Construct the SocketServer
SocketServer::SocketServer(NetPort iPortNo, ListenCapacity iListenNum) :m_ListenSocket(NULL),
m_ServerPort(iPortNo),
m_ListenNum(iListenNum),
m_Disposed(false)
{
	Initialize();
}

// Detructe the SocketServer
SocketServer::~SocketServer()
{
	Destory();
}

// Initialize the socket
SocketServer::None SocketServer::Initialize()
{
	// Create a socket
	CreateSocket();
}

// Dispose the socket
SocketServer::None SocketServer::Destory()
{
	if (!GetDisposed())
	{
		SetDisposed(true);

		Close();
	}
}

// Open a server socket
SocketServer::None SocketServer::Open()
{
	if (GetListenSocket())
	{
		GetListenSocket()->Open();
	}
}

// Bind the server port
SocketServer::BOOL SocketServer::Bind(IPAddress strIPAddress, NetPort iPortNo)
{
	BOOL bSuccess = false;

	if (GetListenSocket())
	{
		bSuccess = GetListenSocket()->Bind(strIPAddress, iPortNo);
	}

	return bSuccess;
}

// Listen the port
SocketServer::BOOL SocketServer::Listen(ListenCapacity iListenNum)
{
	BOOL bSuccess = false;

	if (GetListenSocket())
	{
		bSuccess = GetListenSocket()->Listen(iListenNum);
	}

	return bSuccess;
}

// Close the server socket
SocketServer::None SocketServer::Close()
{
	DestorySocket();
}

// Create a socket
SocketServer::None SocketServer::CreateSocket()
{
	SetListenSocket(new Socket(InterNetwork, Stream, Tcp));
}

// Destory the socket
SocketServer::None SocketServer::DestorySocket()
{
	if (GetListenSocket())
	{
		delete GetListenSocket();

		SetListenSocket(NULL);
	}
}

// Start the server
SocketServer::BOOL SocketServer::Start()
{
	// Open the server
	Open();

	// Get local ip 
	String strLocalIP;
	if (!GetListenSocket()->GetLoaclIP(strLocalIP))
	{
		return false;
	}

	// Bind the server to the port
	if (!Bind(strLocalIP, GetServerPort()))
	{
		return false;
	}

	// Listen the port
	if (!Listen(GetListenNum()))
	{
		return false;
	}

	return true;
}

// Stop the server
SocketServer::None SocketServer::Stop()
{
	Close();
}

// Accept the clients
SocketServer::BOOL SocketServer::Accept(Socket& returnSocket)
{
	if (GetListenSocket())
	{
		return GetListenSocket()->Accept(returnSocket);
	}

	return false;
}

// Receive the data from the client
SocketServer::BOOL SocketServer::Receive(NetSocket ClientSocket, 
	SByteArray pReadBuffer,
	Length iOffset, 
	Length iReadSize)
{
	if (ClientSocket == NULL || pReadBuffer == NULL || iReadSize <= 0)
	{
		return false;
	}

	return ClientSocket->Receive(pReadBuffer, iOffset, iReadSize);
}

// Send the data to the client
SocketServer::BOOL SocketServer::Send(NetSocket ClientSocket,
	SByteArray pWriteBuffer, 
	Length iOffset, 
	Length iWriteSize)
{
	if (ClientSocket == NULL || pWriteBuffer == NULL || iWriteSize <= 0)
	{
		return false;
	}

	return ClientSocket->Send(pWriteBuffer, iOffset, iWriteSize);
}