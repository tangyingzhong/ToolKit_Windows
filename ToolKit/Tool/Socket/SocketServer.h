///************************************************************************
/// <copyrigth>2018-2019 Corporation.All Rights Reserved</copyrigth>
/// <author>tangyingzhong</author>
/// <contact>tangyz114987@outlook.com</contact>
/// <version>v1.0.0</version>
/// <describe>
/// Server using socket
///</describe>
/// <date>2019/7/16</date>
///***********************************************************************
#ifndef SOCKETSERVER_H
#define SOCKETSERVER_H

#include "Socket.h"

namespace System
{
	namespace Network
	{
		class SocketServer
		{
		public:
			typedef System::None None;
			typedef System::Boolean BOOL;
			typedef System::Byte Byte;
			typedef System::ByteArray ByteArray;
			typedef System::SByte SByte;
			typedef System::SByteArray SByteArray;
			typedef System::Object Object;
			typedef System::Int32 Length;
			typedef System::Int32 ListenCapacity;
			typedef System::Int32 NetPort;
			typedef ADDRESS_FAMILY_ENUM AddressFamily;
			typedef SOCKET_TYPE_ENUM SocketType;
			typedef PROTOCOL_ENUM ProtocolType;
			typedef String IPAddress;
			typedef Socket* NetSocket;

		public:
			// Construct the SocketServer
			SocketServer(NetPort iPortNo, ListenCapacity iListenNum);

			// Detructe the SocketServer
			~SocketServer();

		private:
			// Copy SocketServer
			SocketServer(const SocketServer& other) {	}

			// Asigment of SocketServer
			SocketServer& operator=(const SocketServer& other) {	}

		public:
			// Start the server
			BOOL Start();

			// Accept the clients
			BOOL Accept(Socket& ClientSocket);

			// Receive the data from the client
			BOOL Receive(NetSocket ClientSocket,
				SByteArray pReadBuffer, 
				Length iOffset, 
				Length iReadSize);

			// Send the data to the client
			BOOL Send(NetSocket ClientSocket, 
				SByteArray pWriteBuffer, 
				Length iOffset, 
				Length iWriteSize);

			// Stop the server
			None Stop();

		private:
			// Initialize the socket
			None Initialize();

			// Destory the socket
			None Destory();

			// Open a server socket
			None Open();

			// Bind the server port
			BOOL Bind(IPAddress strIPAddress, NetPort iPortNo);

			// Listen the port
			BOOL Listen(ListenCapacity iListenNum);

			// Close the server socket
			None Close();

			// Create a socket 
			None CreateSocket();

			// Destory the socket
			None DestorySocket();

		private:
			// Get the ListenSocket
			inline NetSocket GetListenSocket() const
			{
				return m_ListenSocket;
			}

			// Set the ListenSocket
			inline None SetListenSocket(NetSocket pListenSocket)
			{
				m_ListenSocket = pListenSocket;
			}

			// Get the server port
			inline NetPort GetServerPort() const
			{
				return m_ServerPort;
			}

			// Set the server port
			inline None SetServerPort(NetPort iServerPort)
			{
				m_ServerPort = iServerPort;
			}

			// Get the listen number
			inline ListenCapacity GetListenNum() const
			{
				return m_ListenNum;
			}

			// Set the listen number
			inline None SetListenNum(ListenCapacity iListenNum)
			{
				m_ListenNum = iListenNum;
			}

			// Get the disposed
			inline BOOL GetDisposed() const
			{
				return m_Disposed;
			}

			// Set the disposed	
			inline None SetDisposed(BOOL bDisposed)
			{
				m_Disposed = bDisposed;
			}

		private:
			// Listen socket
			NetSocket m_ListenSocket;

			// Server port
			NetPort m_ServerPort;

			// Listen number
			ListenCapacity m_ListenNum;

			// Disposed status
			BOOL m_Disposed;

		};
	}
}

#endif // SOCKETSERVER_H