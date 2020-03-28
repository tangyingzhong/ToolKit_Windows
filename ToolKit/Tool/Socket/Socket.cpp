#include <WinSock2.h>
#include <ws2tcpip.h>
#include <Iphlpapi.h>
#include "Tool/Buffer/Array.h"
#include "Tool/Thread/Mutex.h"
#include "Tool/Encoding/UTF16.h"
#include "Tool/BaseType/String.h"
#include "Socket.h"

#pragma comment(lib,"Ws2_32.lib")
#pragma comment(lib, "wsock32.lib")
#pragma comment(lib,"Iphlpapi.lib")

using namespace System::Buffer;
using namespace System::Thread;
using namespace System::Network;
using namespace System::Encoding;

static Mutex lock;

// Construct the Socket
Socket::Socket(AddressFamily eFamily,
	SocketType eSocketType,
	ProtocolType eProtocolType) :
	m_ListenSocket(INVALID_SOCKET),
	m_AddrFamily(eFamily),
	m_SocketType(eSocketType),
	m_ProtocolType(eProtocolType),
	m_Disposed(false)
{
	Initialize();
}

// Detructe the Socket
Socket::~Socket()
{
	Destory();
}

// Copy Socket
Socket::Socket(const Socket& other)
{
	m_ListenSocket = other.m_ListenSocket;

	Array<Byte>::Copy((ByteArray)(&(other.m_SocketAddr)), 
		sizeof(SocketAddr), 
		(ByteArray)(&m_SocketAddr), 
		sizeof(SocketAddr));

	SetAddrFamily(other.GetAddrFamily());

	SetSocketType(other.GetSocketType());

	SetProtocolType(other.GetProtocolType());

	SetDisposed(other.GetDisposed());
}

// Asigment of Socket
Socket& Socket::operator=(const Socket& other)
{
	if (this != &other)
	{
		m_ListenSocket = other.m_ListenSocket;

		Array<Byte>::Copy((ByteArray)(&(other.m_SocketAddr)),
			sizeof(SocketAddr),
			(ByteArray)(&m_SocketAddr),
			sizeof(SocketAddr));

		SetAddrFamily(other.GetAddrFamily());

		SetSocketType(other.GetSocketType());

		SetProtocolType(other.GetProtocolType());

		SetDisposed(other.GetDisposed());
	}

	return *this;
}

// Init the socket
Socket::None Socket::Initialize()
{
	Array<Byte>::Clear((ByteArray)(&(m_SocketAddr)), 0, sizeof(m_SocketAddr));
}

// Dispose the socket
Socket::None Socket::Destory()
{
	if (!GetDisposed())
	{
		SetDisposed(true);

		Destory();
	}
}

// Create a new socket
Socket::None Socket::CreateSocket()
{
	// The WSADATA
	WSADATA WsdData;

	// Init the dll of socket
	WSAStartup(MAKEWORD(2, 2), &(WsdData));

	// Create a socket 
	m_ListenSocket = ::socket(GetAddrFamily(), GetSocketType(), GetProtocolType());
}

// Destory the socket
Socket::None Socket::DestorySocket()
{
	Close();

	WSACleanup();
}

// Configure the socket
Socket::None Socket::Configure(IPAddress strIPAddress, NetPort iPortNo)
{
	inet_pton(AF_INET, strIPAddress.ToANSIData().c_str(), &m_SocketAddr.sin_addr);

	m_SocketAddr.sin_family = GetAddrFamily();

	m_SocketAddr.sin_port = htons(iPortNo);
}

// Sokcet is valid
Socket::BOOL Socket::IsValid()
{
	if (m_ListenSocket == INVALID_SOCKET)
	{
		return false;
	}

	return true;
}

// Open the socket
Socket::None Socket::Open()
{
	CreateSocket();
}

// Bind the port
Socket::BOOL Socket::Bind(IPAddress strIPAddress, NetPort iPortNo)
{
	if (!IsValid())
	{
		return false;
	}

	// Config the socket
	Configure(strIPAddress, iPortNo);

	// Bind the port
	if (::bind(m_ListenSocket, (LPSOCKADDR)&(m_SocketAddr), sizeof(SOCKADDR)) == S_FAILE)
	{
		return false;
	}

	return true;
}

// Listen the port
Socket::BOOL Socket::Listen(ListenCapacity iListenNum)
{
	if (!IsValid())
	{
		return false;
	}

	// Ensure that we have at least one listen 
	if (iListenNum <= 0)
	{
		iListenNum = 1;
	}

	if (::listen(m_ListenSocket, iListenNum) == S_FAILE)
	{
		return false;
	}

	return true;
}

// Accept the clients
Socket::BOOL Socket::Accept(Socket& ClientSocket)
{
	if (!IsValid())
	{
		return false;
	}

	SocketAddr ClientAddr;
	Length ClientAddrLen = sizeof(ClientAddr);

	// Accept the clients
	ClientSocket.m_ListenSocket = ::accept(m_ListenSocket, (SOCKADDR FAR*)&ClientAddr, &ClientAddrLen);
	if (ClientSocket.m_ListenSocket == INVALID_SOCKET)
	{
		return false;
	}

	// Set the client
	Array<Byte>::Copy((ByteArray)(&ClientAddr), 
		sizeof(SocketAddr), 
		(ByteArray)(&ClientSocket.m_SocketAddr),
		sizeof(SocketAddr));

	return true;
}

// Connect the server
Socket::BOOL Socket::Connect(IPAddress strIPAddress, NetPort iPortNo)
{
	if (!IsValid())
	{
		return false;
	}

	// Configure the socket
	Configure(strIPAddress, iPortNo);

	// Connect the server
	if (::connect(m_ListenSocket, (LPSOCKADDR)&(m_SocketAddr), sizeof(SOCKADDR)) == S_FAILE)
	{
		return false;
	}

	return true;
}

// Get the local ip
Socket::BOOL Socket::GetLoaclIP(IPAddress& IpAdddr)
{
	// The WSADATA
	WSADATA WsdData;

	// Init the dll of socket
	WSAStartup(MAKEWORD(2, 2), &(WsdData));

	const System::Int32 MAX_NAME_LEN = 128;

	// Get the host name
	SByte HostName[MAX_NAME_LEN] = { 0 };

	if (::gethostname(HostName, MAX_NAME_LEN) != S_SUCCESS)
	{
		return false;
	}

	std::string strHostName = HostName;

	String strFinalHostName = strHostName;

	// Get the host info
	ADDRINFO hint;

	memset(&hint, 0, sizeof(ADDRINFO));

	hint.ai_family = AF_INET;

	hint.ai_flags = AI_PASSIVE;

	hint.ai_protocol = 0;

	hint.ai_socktype = SOCK_STREAM;

	ADDRINFO* ailist;
	if (GetAddrInfoA(strFinalHostName.ToANSIData().c_str(), NULL, &hint, &ailist) != S_SUCCESS)
	{
		return false;
	}

	ADDRINFO* CurList = ailist;
	
	std::string strCurIpAddr;

	for (CurList = ailist; CurList != NULL; CurList = CurList->ai_next)
	{
		struct sockaddr_in * pAddr = (struct sockaddr_in *)CurList->ai_addr;

		char IpAddr[16];

		sprintf(IpAddr, "%d.%d.%d.%d",
			(*pAddr).sin_addr.S_un.S_un_b.s_b1,
			(*pAddr).sin_addr.S_un.S_un_b.s_b2,
			(*pAddr).sin_addr.S_un.S_un_b.s_b3,
			(*pAddr).sin_addr.S_un.S_un_b.s_b4);

		strCurIpAddr = IpAddr;
	}

	IpAdddr = String(strCurIpAddr);

	freeaddrinfo(ailist);

	WSACleanup();

	return true;
}

// Get the local ip
Socket::BOOL Socket::GetLoaclIP(vector<IPAddress>& vIPAddrTable)
{
	// The WSADATA
	WSADATA WsdData;

	// Init the dll of socket
	WSAStartup(MAKEWORD(2, 2), &(WsdData));

	const System::Int32 MAX_NAME_LEN = 128;

	// Get the host name
	SByte HostName[MAX_NAME_LEN] = { 0 };

	if (::gethostname(HostName, MAX_NAME_LEN) != S_SUCCESS)
	{
		return false;
	}

	std::string strHostName = HostName;

	String strFinalHostName = strHostName;

	// Get the host info
	ADDRINFO hint;

	memset(&hint, 0, sizeof(ADDRINFO));

	hint.ai_family = AF_INET;

	hint.ai_flags = AI_PASSIVE;

	hint.ai_protocol = 0;

	hint.ai_socktype = SOCK_STREAM;

	ADDRINFO* ailist;
	if (GetAddrInfoA(strFinalHostName.ToANSIData().c_str(), NULL, &hint, &ailist) != S_SUCCESS)
	{
		return false;
	}

	ADDRINFO* CurList = ailist;

	for (CurList = ailist; CurList != NULL; CurList = CurList->ai_next)
	{
		struct sockaddr_in * pAddr = (struct sockaddr_in *)CurList->ai_addr;

		char IpAddr[16];

		sprintf(IpAddr, "%d.%d.%d.%d",
			(*pAddr).sin_addr.S_un.S_un_b.s_b1,
			(*pAddr).sin_addr.S_un.S_un_b.s_b2,
			(*pAddr).sin_addr.S_un.S_un_b.s_b3,
			(*pAddr).sin_addr.S_un.S_un_b.s_b4);
		
		std::string strCurIpAddr = IpAddr;

		vIPAddrTable.push_back(String(strCurIpAddr));
	}

	freeaddrinfo(ailist);

	WSACleanup();

	return true;
}

// Get Ip with Mac table
Socket::None Socket::GetLocalIpMAc(MacIpTable& IpMacTable)
{
	// Store local machine's card's info
	PIP_ADAPTER_INFO pIpAdapterInfo = new IP_ADAPTER_INFO();

	unsigned long stSize = sizeof(IP_ADAPTER_INFO);

	int nRel = GetAdaptersInfo(pIpAdapterInfo, &stSize);

	int netCardNum = 0;

	int IPnumPerNetCard = 0;

	// Not enoough space for GetAdaptersInfo Func
	if (ERROR_BUFFER_OVERFLOW == nRel)
	{
		delete pIpAdapterInfo;

		// New size it needs
		pIpAdapterInfo = (PIP_ADAPTER_INFO)new BYTE[stSize];

		nRel = GetAdaptersInfo(pIpAdapterInfo, &stSize);
	}

	if (ERROR_SUCCESS == nRel)
	{
		while (pIpAdapterInfo)
		{
			// Get MAC
			char MacAddr[50] = { 0 };

			std::string strShortMac="";

			for (DWORD i = 0; i < pIpAdapterInfo->AddressLength; i++)
			{
				sprintf(MacAddr, "%02X-", pIpAdapterInfo->Address[i]);

				strShortMac = strShortMac+MacAddr;
			}

			String strFinalMac = strShortMac;

			std::string strCurMac = strFinalMac.Left(strFinalMac.GetLength()-1).ToANSIData();

			// Get Mac's IP
			IP_ADDR_STRING *pIpAddrString = &(pIpAdapterInfo->IpAddressList);

			vector<std::string> vIpTable;

			do
			{
				std::string strCurIpAddr=pIpAddrString->IpAddress.String;

				vIpTable.push_back(strCurIpAddr);

				pIpAddrString = pIpAddrString->Next;

			} while (pIpAddrString);

			// Save the mac and ip
			IpMacTable[strCurMac] = vIpTable;

			pIpAdapterInfo = pIpAdapterInfo->Next;
		}
	}

	if (pIpAdapterInfo)
	{
		delete pIpAdapterInfo;
	}
}

// Get Mac by ip
Socket::BOOL Socket::GetMacByIp(String strIpAddr, String& strMacAddr)
{
	if (strIpAddr.IsEmpty())
	{
		return false;
	}

	Socket::MacIpTable Table;

	GetLocalIpMAc(Table);

	vector<std::string> IpAddrTable;

	for (Socket::MacIpTable::iterator Iter = Table.begin();
		Iter != Table.end();
		++Iter)
	{
		IpAddrTable = Iter->second;

		for (Int32 iIndex = 0; iIndex < (Int32)IpAddrTable.size(); ++iIndex)
		{
			if (strIpAddr.ToANSIData() == IpAddrTable[iIndex])
			{
				std::string strCurMac = Iter->first;

				strMacAddr = String(strCurMac);

				return true;
			}
		}
	}

	return false;
}

// Receive the data
Socket::BOOL Socket::Receive(SByteArray pReadBuffer, Length iOffset, Length iReadSize)
{
	if (!IsValid())
	{
		return false;
	}

	if (::recv(m_ListenSocket, pReadBuffer + iOffset, iReadSize, 0) != SOCKET_ERROR)
	{
		return  true;
	}

	return false;
}

// Send the data
Socket::BOOL Socket::Send(SByteArray pWriteBuffer, Length iOffset, Length iWriteSize)
{
	if (!IsValid())
	{
		return false;
	}

	if (::send(m_ListenSocket, pWriteBuffer + iOffset, iWriteSize, 0) != SOCKET_ERROR)
	{
		return true;
	}

	return false;
}

// Close the socket
Socket::None Socket::Close()
{
	if (m_ListenSocket != INVALID_SOCKET)
	{
		::closesocket(m_ListenSocket);

		m_ListenSocket = INVALID_SOCKET;
	}
}

// Asyn read the data
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
		Length len = WSARecv(s->m_ListenSocket,
			&(result->Result.wsaBuf), 
			1, 
			&(result->Result.iOutSize), 
			(LPDWORD)0, 
			&(result->AsynSocket),
			NULL);
		if (len == 0)
		{
			if (GetLastError() == WSA_IO_PENDING)
			{
				// Wait for the operation's finish
				while (WSAGetOverlappedResult(s->m_ListenSocket, 
					&(result->AsynSocket), 
					&(result->Result.iOutSize),
					FALSE, 
					(LPDWORD)0))
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

// The thread function of Write socket
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
		Length len = WSASend(s->m_ListenSocket, 
			&(result->Result.wsaBuf), 
			1, 
			&(result->Result.iOutSize), 
			0, 
			&(result->AsynSocket), NULL);
		if (len == 0)
		{
			if (GetLastError() == WSA_IO_PENDING)
			{
				// Wait for the operation's finish
				while (WSAGetOverlappedResult(s->m_ListenSocket, 
					&(result->AsynSocket), 
					&(result->Result.iOutSize), 
					FALSE,
					(LPDWORD)0))
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

// Asyn the read or write 
Socket::BOOL Socket::_Async(SByteArray pBuffer, 
	Size iBufSize, 
	AsyncCallBack pAsyncCallBack, 
	ThreadRountine pThreadRountine, 
	Object pObject)
{
	if (!IsValid() || pBuffer == NULL || iBufSize <= 0)
	{
		return false;
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

	return true;
}

// Asyn receive the data 
Socket::BOOL Socket::BeginReceive(SByteArray pReadBuffer, 
	Length iReadSize, 
	AsyncCallBack pAsyncCallBack, 
	Object pObject)
{
	return _Async(pReadBuffer,
		iReadSize, 
		pAsyncCallBack, 
		AsyncRead, 
		pObject);
}

// End receive the data
Socket::Length Socket::EndReceive(IAsyncResult pAsyncResult)
{
	Length iRecSize = 0;

	if (pAsyncResult == NULL)
	{
		return iRecSize;
	}

	iRecSize = pAsyncResult->iOutSize;

	return iRecSize;
}

// Asyn send the data
Socket::BOOL Socket::BeginSend(SByteArray pWriteBuffer, 
	Length iWriteSize,
	AsyncCallBack pAsyncCallBack, 
	Object pObject)
{
	return _Async(pWriteBuffer, 
		iWriteSize, 
		pAsyncCallBack, 
		AsyncWrite, 
		pObject);
}

// End send the data
Socket::Length Socket::EndSend(IAsyncResult pAsyncResult)
{
	Length iSendSize = 0;

	if (pAsyncResult == NULL)
	{
		return iSendSize;
	}

	iSendSize = pAsyncResult->iOutSize;

	return iSendSize;
}