///************************************************************************
/// <copyrigth>2018-2019 Corporation.All Rights Reserved</copyrigth>
/// <author>tangyingzhong</author>
/// <contact>tangyz114987@outlook.com</contact>
/// <version>V1.0.0</version>
/// <describe>
/// Windows socket for net operation
///</describe>
/// <date>2019/3/6</date>
///***********************************************************************
#ifndef SOCKET_H
#define SOCKET_H

#include <WinSock2.h>
#include "SocketType.h"
#include "Tool\BaseType\String.h"

using namespace System::BasicType;

namespace System
{
	namespace Network
	{
		///*********************************************************
		/// <class>Socket</class>
		/// <summary>
		///  Low level net operation
		/// </summary>
		/// <version>V1.0.0 </version>
		/// <goup> C++</group>
		/// <author>tangyingzhong</author>
		/// <contact>tangyingzhong@szangell.com</contact>
		///*********************************************************
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
			typedef System::UInt64 Size;
			typedef System::Int32 ListenCapacity;
			typedef System::ThreadRountine ThreadRountine;
			typedef SOCKET NetSocket;
			typedef SOCKADDR_IN SocketAddr;
			typedef String IPAddress;
			typedef AsyncResult* IAsyncResult;
			typedef AsyncCallBack AsyncCallBack;

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
			BOOL GetLoaclIP(IPAddress& strIPAddress);

		public:
			// Open the socket
			Empty Open();

			// Receive the data
			BOOL Receive(SByteArray pReadBuffer, Length iOffset, Length iReadSize);

			// Send the data
			BOOL Send(SByteArray pWriteBuffer, Length iOffset, Length iWriteSize);

			// Asyn receive the data 
			BOOL BeginReceive(SByteArray pReadBuffer, Length iReadSize, AsyncCallBack pAsyncCallBack, Object pObject);

			// End receive the data
			Length EndReceive(IAsyncResult pAsyncResult);

			// Asyn send the data
			BOOL BeginSend(SByteArray pWriteBuffer, Length iWriteSize, AsyncCallBack pAsyncCallBack, Object pObject);

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
			BOOL _Async(SByteArray pBuffer, Size iBufSize, AsyncCallBack pAsyncCallBack, ThreadRountine pThreadRountine, Object pObject);

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
				this->m_AddrFamily = eAddrFamily;
			}

			// Get the socket type
			inline SocketType GetSocketType() const
			{
				return m_SocketType;
			}

			// Set the socket type
			inline Empty SetSocketType(SocketType eSocketType)
			{
				this->m_SocketType = eSocketType;
			}

			// Get the protocol type
			inline ProtocolType GetProtocolType() const
			{
				return m_ProtocolType;
			}

			// Set the protocol type
			inline Empty SetProtocolType(ProtocolType eProtocolType)
			{
				this->m_ProtocolType = eProtocolType;
			}

			// Get the disposed status
			inline BOOL GetDisposed() const
			{
				return m_Disposed;
			}

			// Set the disposed	status
			inline Empty SetDisposed(BOOL bDisposed)
			{
				this->m_Disposed = bDisposed;
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

#endif //SOCKET_H_