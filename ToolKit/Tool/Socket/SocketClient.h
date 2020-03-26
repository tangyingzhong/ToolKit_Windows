///************************************************************************
/// <copyrigth>Voice AI Technology Of ShenZhen</copyrigth>
/// <author>tangyingzhong</author>
/// <contact>yingzhong@voiceaitech.com</contact>
/// <version>v1.0.0</version>
/// <describe>
/// Client using socket
///</describe>
/// <date>2019/7/16</date>
///***********************************************************************
#ifndef SOCKETCLIENT_H
#define SOCKETCLIENT_H

#include "Socket.h"

namespace System
{
	namespace Network
	{
		class SocketClient
		{
		public:
			typedef System::Empty Empty;
			typedef System::Boolean BOOL;
			typedef System::Byte Byte;
			typedef System::ByteArray ByteArray;
			typedef System::SByte SByte;
			typedef System::SByteArray SByteArray;
			typedef System::Object Object;
			typedef System::Int32 Length;
			typedef System::Int32 ListenCapacity;
			typedef System::Int32 NetPort;
			typedef System::Encoding::ENCODE_TYPE_ENUM EncodeType;
			typedef ADDRESS_FAMILY_ENUM AddressFamily;
			typedef SOCKET_TYPE_ENUM SocketType;
			typedef PROTOCOL_ENUM ProtocolType;
			typedef String IPAddress;
			typedef Socket* NetSocket;

		public:
			// Construct the SocketClient
			SocketClient(IPAddress strIPAddress, NetPort iPortNo);

			// Detructe the SocketClient
			~SocketClient();

		private:
			// Copy SocketClient
			SocketClient(const SocketClient& other) {	}

			// Asigment of SocketClient
			SocketClient& operator=(const SocketClient& other) {	}

		public:
			// Start the server
			BOOL Start();

			// Receive the data from the client
			BOOL Receive(SByteArray pReadBuffer, Length iOffset, Length iReadSize);

			// Send the data to the client
			BOOL Send(SByteArray pWriteBuffer, Length iOffset, Length iWriteSize);

			// Stop the server
			Empty Stop();

		private:
			// Initialize the socket
			Empty Initialize();

			// Destory the socket
			Empty Destory();

			// Open a server socket
			Empty Open();

			// Connect to the server
			BOOL Connect();

			// Close the server socket
			Empty Close();

			// Create a socket
			Empty CreateSocket(AddressFamily family, SocketType socketType, ProtocolType protocolType);

			// Destory the socket
			Empty DestorySocket();

		private:
			// Get the ServerSocket
			inline NetSocket GetServerSocket() const
			{
				return m_ServerSocket;
			}

			// Set the ServerSocket
			inline Empty SetServerSocket(NetSocket pServerSocket)
			{
				m_ServerSocket = pServerSocket;
			}

			// Get the server ip
			inline IPAddress GetServerIP() const
			{
				return m_ServerIP;
			}

			// Set the server ip
			inline Empty SetServerIP(IPAddress strServerIP)
			{
				m_ServerIP = strServerIP;
			}

			// Get the Server Port
			inline NetPort GetServerPort() const
			{
				return m_ServerPort;
			}

			// Set the Server Port
			inline Empty SetServerPort(NetPort iServerPort)
			{
				m_ServerPort = iServerPort;
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
			// Server socket
			NetSocket m_ServerSocket;

			// Server ip
			IPAddress m_ServerIP;

			// Server port
			NetPort m_ServerPort;

			// Disposed status
			BOOL m_Disposed;

		};
	}
}

#endif // SOCKETCLIENT_H