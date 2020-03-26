///************************************************************************
/// <copyrigth>Voice AI Technology Of ShenZhen</copyrigth>
/// <author>tangyingzhong</author>
/// <contact>yingzhong@voiceaitech.com</contact>
/// <version>v1.0.0</version>
/// <describe>
/// Windows socket for net operation.Low level net operation
///</describe>
/// <date>2019/7/16</date>
///***********************************************************************
#ifndef SOCKET_H
#define SOCKET_H

#include "SocketType.h"
#include "Encoding/EncodeType.h"
#include "BaseType/String.h"

using namespace System::BasicType;

namespace System
{
	namespace Network
	{
		class Socket
		{
		public:
			typedef System::Empty Empty;
			typedef System::Boolean BOOL;
			typedef System::Byte Byte;
			typedef System::ByteArray ByteArray;
			typedef System::SByte SByte;
			typedef System::SByteArray SByteArray;
			typedef System::Object Object;
			typedef System::Int32 NetPort;
			typedef System::Int32 Length;
			typedef System::FixedUInt32 Size;
			typedef System::Int32 ListenCapacity;
			typedef System::ThreadRountine ThreadRountine;
			typedef System::Encoding::ENCODE_TYPE_ENUM EncodeType;
			typedef ADDRESS_FAMILY_ENUM AddressFamily;
			typedef SOCKET_TYPE_ENUM SocketType;
			typedef PROTOCOL_ENUM ProtocolType;
			typedef SOCKET NetSocket;
			typedef SOCKADDR_IN SocketAddr;
			typedef String IPAddress;
			typedef AsyncResult* IAsyncResult;
			typedef AsyncCallBack AsyncCallBack;
			typedef std::map<std::string, vector<std::string> > MacIpTable;

		public:
			// Construct the Socket
			Socket(AddressFamily eFamily = AddressFamily::InterNetwork,
				SocketType eSocketType = SocketType::Stream,
				ProtocolType eProtocolType = ProtocolType::Tcp);

			// Detructe the Socket
			~Socket();

			// Copy Socket
			Socket(const Socket& other);

			// Asigment of Socket
			Socket& operator=(const Socket& other);

		public:
			// Bind the port
			BOOL Bind(IPAddress strIPAddress, NetPort iPortNo);

			// Listen the port
			BOOL Listen(ListenCapacity iListenNum);

			// Accept the clients
			BOOL Accept(Socket& ClientSocket);

			// Connect the server
			BOOL Connect(IPAddress strIPAddress, NetPort iPortNo);

			// Get the local ip
			BOOL GetLoaclIP(IPAddress& IpAdddr);

			// Get the local ip
			BOOL GetLoaclIP(vector<IPAddress>& vIPAddrTable);

			// Get Ip with Mac table
			Empty GetLocalIpMAc(MacIpTable& IpMacTable);

			// Get Mac by ip
			BOOL Socket::GetMacByIp(String strIpAddr, String& strMacAddr);

		public:
			// Open the socket
			Empty Open();

			// Receive the data
			BOOL Receive(SByteArray pReadBuffer, Length iOffset, Length iReadSize);

			// Send the data
			BOOL Send(SByteArray pWriteBuffer, Length iOffset, Length iWriteSize);

			// Asyn receive the data 
			BOOL BeginReceive(SByteArray pReadBuffer, 
				Length iReadSize, 
				AsyncCallBack pAsyncCallBack, 
				Object pObject);

			// End receive the data
			Length EndReceive(IAsyncResult pAsyncResult);

			// Asyn send the data
			BOOL BeginSend(SByteArray pWriteBuffer, 
				Length iWriteSize, 
				AsyncCallBack pAsyncCallBack, 
				Object pObject);

			// End send the data
			Length EndSend(IAsyncResult pAsyncResult);

			// Close the socket
			Empty Close();

		private:
			// Init the socket
			Empty Initialize();

			// Destory the socket
			Empty Destory();

			// Create a new socket
			Empty CreateSocket();

			// Destory the socket
			Empty DestorySocket();

			// Configure the socket
			Empty Configure(IPAddress strIPAddress, NetPort iPortNo);

			// Sokcet is valid or not
			BOOL IsValid();

			// Asyn the read or write 
			BOOL _Async(SByteArray pBuffer, 
				Size iBufSize, 
				AsyncCallBack pAsyncCallBack, 
				ThreadRountine pThreadRountine, 
				Object pObject);

		private:
			// The thread function of Read socket
			static Size WINAPI AsyncRead(Object pParamenter);

			// The thread function of Write socket
			static Size WINAPI AsyncWrite(Object pParamenter);

		private:
			// Get the family address
			inline AddressFamily GetAddrFamily() const
			{
				return m_AddrFamily;
			}

			// Set the family address
			inline Empty SetAddrFamily(AddressFamily eAddrFamily)
			{
				m_AddrFamily = eAddrFamily;
			}

			// Get the socket type
			inline SocketType GetSocketType() const
			{
				return m_SocketType;
			}

			// Set the socket type
			inline Empty SetSocketType(SocketType eSocketType)
			{
				m_SocketType = eSocketType;
			}

			// Get the protocol type
			inline ProtocolType GetProtocolType() const
			{
				return m_ProtocolType;
			}

			// Set the protocol type
			inline Empty SetProtocolType(ProtocolType eProtocolType)
			{
				m_ProtocolType = eProtocolType;
			}

			// Get the disposed status
			inline BOOL GetDisposed() const
			{
				return m_Disposed;
			}

			// Set the disposed	status
			inline Empty SetDisposed(BOOL bDisposed)
			{
				m_Disposed = bDisposed;
			}

		private:
			// The Socket of the server
			NetSocket m_ListenSocket;

			// The info of the server address
			SocketAddr m_SocketAddr;

			// The family of the tcp
			AddressFamily m_AddrFamily;

			// The type of the socket
			SocketType m_SocketType;

			// The protocol type of the socket
			ProtocolType m_ProtocolType;

			// Disposed status
			BOOL m_Disposed;
		};
	}
}

#endif // SOCKET_H