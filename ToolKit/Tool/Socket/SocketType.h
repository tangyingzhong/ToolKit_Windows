///************************************************************************
/// <copyrigth>2018-2019 Corporation.All Rights Reserved</copyrigth>
/// <author>tangyingzhong</author>
/// <contact>tangyz114987@outlook.com</contact>
/// <version>V1.0.0</version>
/// <describe>
/// Some needing paramenters or types of socket
///</describe>
/// <date>2019/3/7</date>
///***********************************************************************
#ifndef SOCKETTYPE_H
#define SOCKETTYPE_H

#include "Tool\Common\SystemType.h"

namespace System
{
	namespace Network
	{
		typedef enum _SocketResult
		{
			S_SUCCESS = 0,
			S_FAILE
		}SocketResult;

		typedef enum _AddressFamily
		{

			UnknownAddr = -1,												// Unknown address family.	
			UnspecifiedAddr = 0,											// Unspecified address family.		
			Unix = 1,														// Unix local to host address.
			InterNetwork = 2,												// Address for IP version 4.
			ImpLink = 3,													// ARPANET IMP address.
			PupAddr = 4,													// Address for PUP protocols.
			Chaos = 5,														// Address for MIT CHAOS protocols.
			IpxAddr = 6,													// IPX or SPX address.
			NS = 6,															// Address for Xerox NS protocols.
			Osi = 7,														// Address for OSI protocols.
			Iso = 7,														// Address for ISO protocols.
			Ecma = 8,														// European Computer Manufacturers Association (ECMA) address.
			DataKit = 9,													// Address for Datakit protocols.
			Ccitt = 10,														// Addresses for CCITT protocols, such as X.25.
			Sna = 11,														// IBM SNA address.
			DecNet = 12,													// DECnet address.
			DataLink = 13,													// Direct data-link interface address.
			Lat = 14,														// LAT address.
			HyperChannel = 15,												// NSC Hyperchannel address.
			AppleTalk = 16,													// AppleTalk address.
			NetBios = 17,													// NetBios address.
			VoiceView = 18,													// VoiceView address.
			FireFox = 19,													// FireFox address.
			Banyan = 21,													// Banyan address.
			Atm = 22,														// Native ATM services address.
			InterNetworkV6 = 23,											// Address for IP version 6.
			Cluster = 24,													// Address for Microsoft cluster products.
			Ieee12844 = 25,													// IEEE 1284.4 workgroup address.
			Irda = 26,														// IrDA address.
			NetworkDesigners = 28,											// Address for Network Designers OSI gateway-enabled protocols.
			Max = 29,														// MAX address.
		}AddressFamily;

		typedef enum _ProtocolType
		{
			UnknownProtocol = -1,											// Unknown protocol.
			IPv6HopByHopOptions = 0,										// IPv6 Hop by Hop Options header.
			UnspecifiedProtocol = 0,										// Unspecified protocol.
			IP = 0,															// Internet Protocol.
			Icmp = 1,														// Internet Control Message Protocol.
			Igmp = 2,														// Internet Group Management Protocol.
			Ggp = 3,														// Gateway To Gateway Protocol.
			IPv4 = 4,														// Internet Protocol version 4.
			Tcp = 6,														// Transmission Control Protocol.
			PupProtocol = 12,												// PARC Universal Packet Protocol.
			Udp = 17,														// User Datagram Protocol.
			Idp = 22,														// Internet Datagram Protocol.
			IPv6 = 41,														// Internet Protocol version 6 (IPv6).
			IPv6RoutingHeader = 43,											// IPv6 Routing header.
			IPv6FragmentHeader = 44,										// IPv6 Fragment header.
			IPSecEncapsulatingSecurityPayload = 50,							// IPv6 Encapsulating Security Payload header.
			IPSecAuthenticationHeader = 51,									// IPv6 Authentication header. For details, see RFC 2292 section 2.2.1, available
			IcmpV6 = 58,													// Internet Control Message Protocol for IPv6.
			IPv6NoNextHeader = 59,											// IPv6 No next header.
			IPv6DestinationOptions = 60,									// IPv6 Destination Options header.
			ND = 77,														// Net Disk Protocol (unofficial).
			RawProtocol = 255,												// Raw IP packet protocol.
			IpxProtocol = 1000,												// Internet Packet Exchange Protocol.
			Spx = 1256,														// Sequenced Packet Exchange protocol.
			SpxII = 1257,													// Sequenced Packet Exchange version 2 protocol.
		}ProtocolType;

		typedef enum _SocketType
		{
			// Specifies an unknown Socket type.
			UnknownType = -1,

			// Supports reliable, two-way, connection-based byte streams without the duplication
			// of data and without preservation of boundaries. A Socket of this type communicates
			// with a single peer and requires a remote host connection before communication
			// can begin. System.Net.Sockets.SocketType.Stream uses the Transmission Control
			// Protocol (System.Net.Sockets.ProtocolType.Tcp) System.Net.Sockets.ProtocolType
			// and the InterNetworkSystem.Net.Sockets.AddressFamily.
			Stream = 1,

			// Supports datagrams, which are connectionless, unreliable messages of a fixed
			// (typically small) maximum length. Messages might be lost or duplicated and
			// might arrive out of order. A System.Net.Sockets.Socket of type System.Net.Sockets.SocketType.Dgram
			// requires no connection prior to sending and receiving data, and can communicate
			// with multiple peers. System.Net.Sockets.SocketType.Dgram uses the Datagram
			// Protocol (System.Net.Sockets.ProtocolType.Udp) and the System.Net.Sockets.AddressFamily.InterNetworkSystem.Net.Sockets.AddressFamily.
			Dgram = 2,

			// Supports access to the underlying transport protocol. Using the System.Net.Sockets.SocketTypeSystem.Net.Sockets.SocketType.Raw,
			// you can communicate using protocols like Internet Control Message Protocol
			// (System.Net.Sockets.ProtocolType.Icmp) and Internet Group Management Protocol
			// (System.Net.Sockets.ProtocolType.Igmp). Your application must provide a complete
			// IP header when sending. Received datagrams return with the IP header and
			// options intact.
			RawType = 3,

			// Supports connectionless, message-oriented, reliably delivered messages, and
			// preserves message boundaries in data. Rdm (Reliably Delivered Messages) messages
			// arrive unduplicated and in order. Furthermore, the sender is notified if
			// messages are lost. If you initialize a Socket using System.Net.Sockets.SocketType.Rdm,
			// you do not require a remote host connection before sending and receiving
			// data. With System.Net.Sockets.SocketType.Rdm, you can communicate with multiple
			// peers.
			Rdm = 4,

			// Provides connection-oriented and reliable two-way transfer of ordered byte
			// streams across a network. System.Net.Sockets.SocketType.Seqpacket does not
			// duplicate data, and it preserves boundaries within the data stream. A Socket
			// of type System.Net.Sockets.SocketType.Seqpacket communicates with a single
			// peer and requires a remote host connection before communication can begin.
			Seqpacket = 5,
		}SocketType;

		// Asynchronize configure structure
		typedef struct _AsyncResult
		{
			WSABUF wsaBuf;
			System::Int32 iBufSize;
			typedef Empty(*AsyncCallBack)(struct _AsyncResult*);
			AsyncCallBack pCallBackFunc;
			Object SocketState;
			System::UInt64 iOutSize;
		}AsyncResult;

		// Socket call back function
		typedef AsyncResult::AsyncCallBack AsyncCallBack;

		// The way of windows Async
		typedef WSAOVERLAPPED wsaAsync;

		// Asynchronize result
		typedef struct
		{
			wsaAsync AsynSocket;
			AsyncResult Result;
		}AsyncRes;
	}
}

#endif // SOCKETTYPE_H