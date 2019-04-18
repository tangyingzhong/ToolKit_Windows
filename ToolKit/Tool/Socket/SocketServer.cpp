#include "Application\PreCompile.h"
#include "SocketServer.h"

#pragma comment(lib, "wsock32.lib")

using namespace System::Network;

///************************************************************************
/// <summary>
/// Construct the SocketServer
/// </summary>
/// <returns></returns>
/// <remarks>
/// none
/// </remarks>
///***********************************************************************
SocketServer::SocketServer(NetPort iPortNo, ListenCapacity iListenNum) :m_ListenSocket(NULL),
m_ServerPort(iPortNo),
m_ListenNum(iListenNum),
m_Disposed(false)
{
	Initialize();
}


///************************************************************************
/// <summary>
/// Detructe the SocketServer
/// </summary>
/// <returns></returns>
/// <remarks>
/// none
/// </remarks>
///***********************************************************************
SocketServer::~SocketServer()
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
SocketServer::Empty SocketServer::Initialize()
{
	// Create a socket
	CreateSocket();
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
SocketServer::Empty SocketServer::Destory()
{
	if (!GetDisposed())
	{
		SetDisposed(true);

		// Close the server
		this->Close();
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
SocketServer::Empty SocketServer::Open()
{
	if (this->GetListenSocket())
	{
		this->GetListenSocket()->Open();
	}
}


///************************************************************************
/// <summary>
/// Bind the server port
/// </summary>
/// <param name=ip></param>
/// <param name=serverPort></param>
/// <returns></returns>
/// <remarks>
/// none
/// </remarks>
///***********************************************************************
SocketServer::BOOL SocketServer::Bind(IPAddress strIPAddress, NetPort iPortNo)
{
	BOOL bSuccess = false;

	if (this->GetListenSocket())
	{
		bSuccess = this->GetListenSocket()->Bind(strIPAddress, iPortNo);
	}

	return bSuccess;
}


///************************************************************************
/// <summary>
/// Listen the port
/// </summary>
/// <param name=num></param>
/// <returns></returns>
/// <remarks>
/// none
/// </remarks>
///***********************************************************************
SocketServer::BOOL SocketServer::Listen(ListenCapacity iListenNum)
{
	BOOL bSuccess = false;

	if (this->GetListenSocket())
	{
		bSuccess = this->GetListenSocket()->Listen(iListenNum);
	}

	return bSuccess;
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
SocketServer::Empty SocketServer::Close()
{
	this->DestorySocket();
}


///************************************************************************
/// <summary>
/// Create a socket
/// </summary>
/// <returns></returns>
/// <remarks>
/// none
/// </remarks>
///***********************************************************************
SocketServer::Empty SocketServer::CreateSocket()
{
	this->SetListenSocket(new Socket(AddressFamily::InterNetwork, SocketType::Stream, ProtocolType::Tcp));
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
SocketServer::Empty SocketServer::DestorySocket()
{
	if (this->GetListenSocket())
	{
		delete this->GetListenSocket();
		SetListenSocket(NULL);
	}
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
SocketServer::BOOL SocketServer::Start()
{
	BOOL bSuccess = false;

	// Open the server
	this->Open();

	// Get local ip 
	String strLocalIP;
	bSuccess = this->GetListenSocket()->GetLoaclIP(strLocalIP);
	if (!bSuccess)
	{
		return bSuccess;
	}

	// Bind the server to the port
	bSuccess = this->Bind(strLocalIP, this->GetServerPort());
	if (!bSuccess)
	{
		return bSuccess;
	}

	// Listen the port
	bSuccess = this->Listen(this->GetListenNum());
	if (!bSuccess)
	{
		return bSuccess;
	}

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
SocketServer::Empty SocketServer::Stop()
{
	this->Close();
}

///************************************************************************
/// <summary>
/// Accept the clients
/// </summary>
/// <returns></returns>
/// <remarks>
/// none
/// </remarks>
///***********************************************************************
SocketServer::BOOL SocketServer::Accept(Socket& returnSocket)
{
	BOOL bSuccess = false;

	if (this->GetListenSocket())
	{
		bSuccess = this->GetListenSocket()->Accept(returnSocket);
	}
	return bSuccess;
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
SocketServer::BOOL SocketServer::Receive(NetSocket ClientSocket, SByteArray pReadBuffer, Length iOffset, Length iReadSize)
{
	BOOL bSuccess = false;

	if (ClientSocket == NULL || pReadBuffer == NULL || iReadSize <= 0)
	{
		return bSuccess;
	}

	bSuccess = ClientSocket->Receive(pReadBuffer, iOffset, iReadSize);

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
SocketServer::BOOL SocketServer::Send(NetSocket ClientSocket, SByteArray pWriteBuffer, Length iOffset, Length iWriteSize)
{
	BOOL bSuccess = false;

	if (ClientSocket == NULL || pWriteBuffer == NULL || iWriteSize <= 0)
	{
		return bSuccess;
	}

	bSuccess = ClientSocket->Send(pWriteBuffer, iOffset, iWriteSize);

	return bSuccess;
}