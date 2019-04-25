#include "Application\PreCompile.h"
#include <ws2tcpip.h>
#include "Tool\Buffer\Array.h"
#include "Tool\Thread\Mutex.h"
#include "Tool\Encoding\Unicode.h"
#include "Socket.h"

#pragma comment(lib,"Ws2_32.lib")
#pragma comment(lib, "wsock32.lib")

using namespace System::Buffer;
using namespace System::Thread;
using namespace System::Network;
using namespace System::Encoding;

static Mutex lock;

///************************************************************************
/// <summary>
/// Construct the Socket
/// </summary>
/// <param name=family></param>
/// <param name=socketType></param>
/// <param name=protocolType></param>
/// <returns></returns>
/// <remarks>
/// none
/// </remarks>
///***********************************************************************
Socket::Socket(AddressFamily eFamily, SocketType eSocketType, ProtocolType eProtocolType) :m_ListenSocket(INVALID_SOCKET),
m_AddrFamily(eFamily),
m_SocketType(eSocketType),
m_ProtocolType(eProtocolType),
m_Disposed(false)
{
	Initialize();
}


///************************************************************************
/// <summary>
/// Detructe the Socket
/// </summary>
/// <returns></returns>
/// <remarks>
/// none
/// </remarks>
///***********************************************************************
Socket::~Socket()
{
	Destory();
}


///************************************************************************
/// <summary>
/// Copy Socket
/// </summary>
/// <param name=other></param>
/// <returns></returns>
/// <remarks>
/// none
/// </remarks>
///***********************************************************************
Socket::Socket(const Socket& other)
{
	this->m_ListenSocket = other.m_ListenSocket;
	Array<Byte>::Copy((ByteArray)(&(other.m_SocketAddr)), sizeof(SocketAddr), (ByteArray)(&this->m_SocketAddr), sizeof(SocketAddr));
	this->SetAddrFamily(other.GetAddrFamily());
	this->SetSocketType(other.GetSocketType());
	this->SetProtocolType(other.GetProtocolType());
	this->SetDisposed(other.GetDisposed());
}


///************************************************************************
/// <summary>
/// Asigment of Socket
/// </summary>
/// <param name=other></param>
/// <returns></returns>
/// <remarks>
/// none
/// </remarks>
///***********************************************************************
Socket& Socket::operator=(const Socket& other)
{
	if (this != &other)
	{
		this->m_ListenSocket = other.m_ListenSocket;
		Array<Byte>::Copy((ByteArray)(&(other.m_SocketAddr)), sizeof(SocketAddr), (ByteArray)(&this->m_SocketAddr), sizeof(SocketAddr));
		this->SetAddrFamily(other.GetAddrFamily());
		this->SetSocketType(other.GetSocketType());
		this->SetProtocolType(other.GetProtocolType());
		this->SetDisposed(other.GetDisposed());
	}

	return *this;
}


///************************************************************************
/// <summary>
/// Init the socket
/// </summary>
/// <param name=family></param>
/// <param name=socketType></param>
/// <param name=protocolType></param>
/// <returns></returns>
/// <remarks>
/// none
/// </remarks>
///***********************************************************************
Socket::Empty Socket::Initialize()
{
	Array<Byte>::Clear((ByteArray)(&(this->m_SocketAddr)), 0, sizeof(this->m_SocketAddr));
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
Socket::Empty Socket::Destory()
{
	if (!GetDisposed())
	{
		SetDisposed(true);

		// Destory the socket
		Destory();
	}
}


///************************************************************************
/// <summary>
/// Create a new socket
/// </summary>
/// <returns></returns>
/// <remarks>
/// none
/// </remarks>
///***********************************************************************
Socket::Empty Socket::CreateSocket()
{
	// The WSADATA
	WSADATA WsdData;

	// Init the dll of socket
	WSAStartup(MAKEWORD(2, 2), &(WsdData));

	// Create a socket 
	this->m_ListenSocket = ::socket(this->GetAddrFamily(), this->GetSocketType(), this->GetProtocolType());
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
Socket::Empty Socket::DestorySocket()
{
	this->Close();

	WSACleanup();
}


///************************************************************************
/// <summary>
/// Configure the socket
/// </summary>
/// <param name=addr></param>
/// <param name=port></param>
/// <returns></returns>
/// <remarks>
/// none
/// </remarks>
///***********************************************************************
Socket::Empty Socket::Configure(IPAddress strIPAddress, NetPort iPortNo)
{
	InetPton(this->GetAddrFamily(), strIPAddress, &(this->m_SocketAddr.sin_addr));

	this->m_SocketAddr.sin_family = this->GetAddrFamily();

	this->m_SocketAddr.sin_port = htons(iPortNo);
}


///************************************************************************
/// <summary>
/// Sokcet is valid
/// </summary>
/// <returns></returns>
/// <remarks>
/// none
/// </remarks>
///***********************************************************************
Socket::BOOL Socket::IsValid()
{
	if (this->m_ListenSocket == INVALID_SOCKET)
	{
		return false;
	}

	return true;
}


///************************************************************************
/// <summary>
/// Open the socket
/// </summary>
/// <returns></returns>
/// <remarks>
/// none
/// </remarks>
///***********************************************************************
Socket::Empty Socket::Open()
{
	this->CreateSocket();
}


///************************************************************************
/// <summary>
/// Bind the port
/// </summary>
/// <param name=addr></param>
/// <param name=port></param>
/// <returns></returns>
/// <remarks>
/// none
/// </remarks>
///***********************************************************************
Socket::BOOL Socket::Bind(IPAddress strIPAddress, NetPort iPortNo)
{
	BOOL bSuccess = false;

	assert(this->IsValid() == true);

	if (!this->IsValid())
	{
		return bSuccess;
	}

	// Config the socket
	this->Configure(strIPAddress, iPortNo);

	// Bind the port
	if (::bind(this->m_ListenSocket, (LPSOCKADDR)&(this->m_SocketAddr), sizeof(SOCKADDR)) == S_FAILE)
	{
		return bSuccess;
	}

	bSuccess = true;

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
Socket::BOOL Socket::Listen(ListenCapacity iListenNum)
{
	BOOL bSuccess = false;

	assert(this->IsValid() == true);

	if (!this->IsValid())
	{
		return bSuccess;
	}

	// Ensure that we have at least one listen 
	if (iListenNum <= 0)
	{
		iListenNum = 1;
	}

	if (::listen(this->m_ListenSocket, iListenNum) == S_FAILE)
	{
		return bSuccess;
	}

	bSuccess = true;

	return bSuccess;
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
Socket::BOOL Socket::Accept(Socket& ClientSocket)
{
	BOOL bSuccess = false;

	assert(this->IsValid() == true);

	if (!this->IsValid())
	{
		return bSuccess;
	}

	SocketAddr ClientAddr;
	Length ClientAddrLen = sizeof(ClientAddr);

	// Accept the clients
	ClientSocket.m_ListenSocket = ::accept(this->m_ListenSocket, (SOCKADDR FAR*)&ClientAddr, &ClientAddrLen);

	assert(ClientSocket.m_ListenSocket != INVALID_SOCKET);

	if (ClientSocket.m_ListenSocket == INVALID_SOCKET)
	{
		return bSuccess;
	}

	// Set the client
	Array<Byte>::Copy((ByteArray)(&ClientAddr), sizeof(SocketAddr), (ByteArray)(&ClientSocket.m_SocketAddr), sizeof(SocketAddr));

	bSuccess = true;

	return bSuccess;
}


///************************************************************************
/// <summary>
/// Connect the server
/// </summary>
/// <param name=addr></param>
/// <param name=port></param>
/// <returns></returns>
/// <remarks>
/// none
/// </remarks>
///***********************************************************************
Socket::BOOL Socket::Connect(IPAddress strIPAddress, NetPort iPortNo)
{
	BOOL bSuccess = false;

	assert(this->IsValid() == true);

	if (!this->IsValid())
	{
		return bSuccess;
	}

	// Configure the socket
	this->Configure(strIPAddress, iPortNo);

	// Connect the server
	if (::connect(this->m_ListenSocket, (LPSOCKADDR)&(this->m_SocketAddr), sizeof(SOCKADDR)) == S_FAILE)
	{
		return bSuccess;
	}

	bSuccess = true;

	return bSuccess;
}


///************************************************************************
/// <summary>
/// Get the local ip
/// </summary>
/// <param name=addr></param>
/// <returns></returns>
/// <remarks>
/// none
/// </remarks>
///***********************************************************************
Socket::BOOL Socket::GetLoaclIP(IPAddress& ip)
{
	BOOL bSuccess = false;

	// Get the host name
	const System::Int32 MAX_NAME_LEN = 128;
	SByte HostName[MAX_NAME_LEN] = { 0 };

	System::Int32 iRet = ::gethostname(HostName, MAX_NAME_LEN);
	if (iRet != S_SUCCESS)
	{
		return bSuccess;
	}

#ifdef UNICODE
	// Set unicode name 
	String strHostName = Encoding::Unicode::GetString(HostName, 0, MAX_NAME_LEN, EncodeType::E_ASCII);

	// Get the host info
	PADDRINFOW ailist;
	ADDRINFOW hint;
	if (GetAddrInfo(strHostName, NULL, &hint, &ailist) != S_SUCCESS)
	{
		return bSuccess;
	}
#else
	// Set unicode name 
	String strHostName = HostName;

	// Get the host info
	PADDRINFOA ailist;
	ADDRINFOA hint;
	if (GetAddrInfo(strHostName, NULL, &hint, &ailist) != S_SUCCESS)
	{
		return bSuccess;
	}
#endif 
	TCHAR buf[INET_ADDRSTRLEN] = { 0 };
	InetNtop(this->GetAddrFamily(), &(ailist->ai_addr), buf, sizeof(buf));

	bSuccess = true;

	return bSuccess;
}


///************************************************************************
/// <summary>
/// Receive the data
/// </summary>
/// <param name=buffer></param>
/// <param name=offset></param>
/// <param name=len></param>
/// <returns></returns>
/// <remarks>
/// none
/// </remarks>
///***********************************************************************
Socket::BOOL Socket::Receive(SByteArray pReadBuffer, Length iOffset, Length iReadSize)
{
	BOOL bSuccess = false;

	assert(this->IsValid() == true);

	if (!this->IsValid())
	{
		return bSuccess;
	}

	System::Int32 iRet = ::recv(this->m_ListenSocket, pReadBuffer + iOffset, iReadSize, 0);
	if (iRet != SOCKET_ERROR)
	{
		bSuccess = true;
	}

	return bSuccess;
}


///************************************************************************
/// <summary>
/// Send the data
/// </summary>
/// <param name=buffer></param>
/// <param name=offset></param>
/// <param name=len></param>
/// <returns></returns>
/// <remarks>
/// none
/// </remarks>
///***********************************************************************
Socket::BOOL Socket::Send(SByteArray pWriteBuffer, Length iOffset, Length iWriteSize)
{
	BOOL bSuccess = false;

	assert(this->IsValid() == true);

	if (!this->IsValid())
	{
		return bSuccess;
	}

	System::Int32 iRet = ::send(this->m_ListenSocket, pWriteBuffer + iOffset, iWriteSize, 0);
	if (iRet != SOCKET_ERROR)
	{
		bSuccess = true;
	}

	return bSuccess;
}


///************************************************************************
/// <summary>
/// Close the socket
/// </summary>
/// <returns></returns>
/// <remarks>
/// none
/// </remarks>
///***********************************************************************
Socket::Empty Socket::Close()
{
	if (this->m_ListenSocket != INVALID_SOCKET)
	{
		::closesocket(this->m_ListenSocket);

		this->m_ListenSocket = INVALID_SOCKET;
	}
}


///************************************************************************
/// <summary>
/// 
/// </summary>
/// <param name=paramenter></param>
/// <returns></returns>
/// <remarks>
/// none
/// </remarks>
///***********************************************************************
Socket::Size WINAPI Socket::AsyncRead(Object paramenter)
{
	// Restore the async paramenter
	AsyncRes* result = (AsyncRes*)paramenter;

	// Get the Object state here
	Socket* s = (Socket*)(result->Result.SocketState);

	// Init the async event
	memset(&(result->AsynSocket), 0, sizeof(wsaAsync));
	if (result->AsynSocket.hEvent)
	{
		// Reset the event
		::ResetEvent(result->AsynSocket.hEvent);

		// Close the event
		::CloseHandle(result->AsynSocket.hEvent);

		result->AsynSocket.hEvent = WSACreateEvent();
	}

	// Enter the read mode
	lock.Lock();
	{
		Length len = WSARecv(s->m_ListenSocket, &(result->Result.wsaBuf), 1, &(result->Result.iOutSize), (LPDWORD)0, &(result->AsynSocket), NULL);
		if (len == 0)
		{
			if (GetLastError() == WSA_IO_PENDING)
			{
				// Wait for the operation's finish
				while (WSAGetOverlappedResult(s->m_ListenSocket, &(result->AsynSocket), &(result->Result.iOutSize), FALSE, (LPDWORD)0))
				{
					if (result->Result.pCallBackFunc)
					{
						// Call the User function
						result->Result.pCallBackFunc(&(result->Result));
					}
					break;
				}
				if (result->AsynSocket.hEvent)
				{
					// Reset the event
					::WSAResetEvent(result->AsynSocket.hEvent);

					// Close the event
					::WSACloseEvent(result->AsynSocket.hEvent);

					// Close the handle
					::CloseHandle(result->AsynSocket.hEvent);
				}
				// Release the resource
				delete result;
			}
		}
	}
	// Leave the read mode
	lock.Unlock();

	return 0;
}


///************************************************************************
/// <summary>
/// The thread function of Write socket
/// </summary>
/// <param name=paramenter></param>
/// <returns></returns>
/// <remarks>
/// none
/// </remarks>
///***********************************************************************
Socket::Size WINAPI Socket::AsyncWrite(Object paramenter)
{
	// Restore the async paramenter
	AsyncRes* result = (AsyncRes*)paramenter;

	// Get the Object state here
	Socket* s = (Socket*)(result->Result.SocketState);

	// Init the async event
	memset(&(result->AsynSocket), 0, sizeof(wsaAsync));
	if (result->AsynSocket.hEvent)
	{
		// Reset the event
		::ResetEvent(result->AsynSocket.hEvent);

		// Close the event
		::CloseHandle(result->AsynSocket.hEvent);

		result->AsynSocket.hEvent = WSACreateEvent();
	}

	// Enter the read mode
	lock.Lock();
	{
		Length len = WSASend(s->m_ListenSocket, &(result->Result.wsaBuf), 1, &(result->Result.iOutSize), 0, &(result->AsynSocket), NULL);
		if (len == 0)
		{
			if (GetLastError() == WSA_IO_PENDING)
			{
				// Wait for the operation's finish
				while (WSAGetOverlappedResult(s->m_ListenSocket, &(result->AsynSocket), &(result->Result.iOutSize), FALSE, (LPDWORD)0))
				{
					if (result->Result.pCallBackFunc)
					{
						// Call the User function
						result->Result.pCallBackFunc(&(result->Result));
					}
					break;
				}
				if (result->AsynSocket.hEvent)
				{
					// Reset the event
					::WSAResetEvent(result->AsynSocket.hEvent);

					// Close the event
					::WSACloseEvent(result->AsynSocket.hEvent);

					// Close the handle
					::CloseHandle(result->AsynSocket.hEvent);
				}
				// Release the resource
				delete result;
			}
		}
	}
	// Leave the read mode
	lock.Unlock();

	return 0;
}


///************************************************************************
/// <summary>
/// Asyn the read or write 
/// </summary>
/// <param name=buffer></param>
/// <param name=len></param>
/// <param name=callback></param>
/// <param name=threadCallBack></param>
/// <param name=self></param>
/// <returns></returns>
/// <remarks>
/// none
/// </remarks>
///***********************************************************************
Socket::BOOL Socket::_Async(SByteArray pBuffer, Size iBufSize, AsyncCallBack pAsyncCallBack, ThreadRountine pThreadRountine, Object pObject)
{
	BOOL bSuccess = false;

	assert(this->IsValid() == true);
	assert(pBuffer != NULL);
	assert(iBufSize > 0);

	if (!this->IsValid() || pBuffer == NULL || iBufSize <= 0)
	{
		return bSuccess;
	}

	// Init the Async paramenter
	AsyncRes* result = new AsyncRes();
	result->Result.wsaBuf.buf = pBuffer;
	result->Result.wsaBuf.len = iBufSize;
	result->Result.iBufSize = iBufSize;
	result->Result.pCallBackFunc = pAsyncCallBack;
	result->Result.SocketState = pObject;
	result->Result.iOutSize = 0;

	// Create a thread running the read
	::CreateThread(NULL, 0, pThreadRountine, result, 0, NULL);

	bSuccess = true;

	return bSuccess;
}


///************************************************************************
/// <summary>
/// Asyn receive the data 
/// </summary>
/// <param name=buffer></param>
/// <param name=len></param>
/// <param name=callback></param>
/// <param name=self></param>
/// <returns></returns>
/// <remarks>
/// none
/// </remarks>
///***********************************************************************
Socket::BOOL Socket::BeginReceive(SByteArray pReadBuffer, Length iReadSize, AsyncCallBack pAsyncCallBack, Object pObject)
{
	return _Async(pReadBuffer, iReadSize, pAsyncCallBack, AsyncRead, pObject);
}


///************************************************************************
/// <summary>
/// End receive the data
/// </summary>
/// <param name=asyncResult></param>
/// <returns></returns>
/// <remarks>
/// none
/// </remarks>
///***********************************************************************
Socket::Length Socket::EndReceive(IAsyncResult pAsyncResult)
{
	Length iRecSize = 0;

	assert(pAsyncResult != NULL);

	if (pAsyncResult == NULL)
	{
		return iRecSize;
	}

	iRecSize = pAsyncResult->iOutSize;

	return iRecSize;
}


///************************************************************************
/// <summary>
/// Asyn send the data
/// </summary>
/// <param name=buffer></param>
/// <param name=len></param>
/// <param name=callback></param>
/// <param name=self></param>
/// <returns></returns>
/// <remarks>
/// none
/// </remarks>
///***********************************************************************
Socket::BOOL Socket::BeginSend(SByteArray pWriteBuffer, Length iWriteSize, AsyncCallBack pAsyncCallBack, Object pObject)
{
	return _Async(pWriteBuffer, iWriteSize, pAsyncCallBack, AsyncWrite, pObject);
}


///************************************************************************
/// <summary>
/// End send the data
/// </summary>
/// <param name=asyncResult></param>
/// <returns></returns>
/// <remarks>
/// none
/// </remarks>
///***********************************************************************
Socket::Length Socket::EndSend(IAsyncResult pAsyncResult)
{
	Length iSendSize = 0;

	assert(pAsyncResult != NULL);

	if (pAsyncResult == NULL)
	{
		return iSendSize;
	}

	iSendSize = pAsyncResult->iOutSize;

	return iSendSize;
}