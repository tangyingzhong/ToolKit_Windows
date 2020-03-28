///************************************************************************
/// <copyrigth>2018-2019 Corporation.All Rights Reserved</copyrigth>
/// <author>tangyingzhong</author>
/// <contact>tangyz114987@outlook.com</contact>
/// <version>v1.0.0</version>
/// <describe>
/// Some needing paramenters or types of socket
///</describe>
/// <date>2019/7/16</date>
///***********************************************************************
#ifndef SOCKETTYPE_H
#define SOCKETTYPE_H

#include <ws2tcpip.h>
#include "Tool/Common/SystemType.h"

namespace System
{
	namespace Network
	{
		enum SOKCET_RESULT
		{
			S_SUCCESS = 0,

			S_FAILE
		};

		enum ADDRESS_FAMILY_ENUM
		{
			// Unknown address family.	
			UnknownAddr = -1,						

			// Unspecified address family.	
			UnspecifiedAddr = 0,				

			// Unix local to host address.
			Unix = 1,						

			// Address for IP version 4.
			InterNetwork = 2,			

			// ARPANET IMP address.
			ImpLink = 3,				

			// Address for PUP protocols.
			PupAddr = 4,							

			// Address for MIT CHAOS protocols.
			Chaos = 5,							

			// IPX or SPX address.
			IpxAddr = 6,															

			// Address for Xerox NS protocols.
			NS = 6,																	

			// Address for OSI protocols.
			Osi = 7,																	

			// Address for ISO protocols.
			Iso = 7,												

			// European Computer Manufacturers Association (ECMA) address.
			Ecma = 8,																

			// Address for Datakit protocols.
			DataKit = 9,							

			// Addresses for CCITT protocols, such as X.25.
			Ccitt = 10,														

			// IBM SNA address.
			Sna = 11,																

			// DECnet address.
			DecNet = 12,					

			// Direct data-link interface address.
			DataLink = 13,									

			// LAT address.
			Lat = 14,												

			// NSC Hyperchannel address.
			HyperChannel = 15,	

			// AppleTalk address.
			AppleTalk = 16,								

			// NetBios address.
			NetBios = 17,														

			// VoiceView address.
			VoiceView = 18,													

			// FireFox address.
			FireFox = 19,												

			// Banyan address.
			Banyan = 21,														

			// Native ATM services address.
			Atm = 22,																

			// Address for IP version 6.
			InterNetworkV6 = 23,								

			// Address for Microsoft cluster products.
			Cluster = 24,															

			// IEEE 1284.4 workgroup address.
			Ieee12844 = 25,									

			// IrDA address.
			Irda = 26,													

			// Address for Network Designers OSI gateway-enabled protocols.
			NetworkDesigners = 28,									

			// MAX address.
			Max = 29,																
		};

		enum PROTOCOL_ENUM
		{
			// Unknown protocol.
			UnknownProtocol = -1,										

			// IPv6 Hop by Hop Options header.
			IPv6HopByHopOptions = 0,								

			// Unspecified protocol.
			UnspecifiedProtocol = 0,		

			// Internet Protocol.
			IP = 0,												

			// Internet Control Message Protocol.
			Icmp = 1,																

			// Internet Group Management Protocol.
			Igmp = 2,																

			// Gateway To Gateway Protocol.
			Ggp = 3,																

			// Internet Protocol version 4.
			IPv4 = 4,																

			// Transmission Control Protocol.
			Tcp = 6,																

			// PARC Universal Packet Protocol.
			PupProtocol = 12,							

			// User Datagram Protocol.
			Udp = 17,																

			// Internet Datagram Protocol.
			Idp = 22,																

			// Internet Protocol version 6 (IPv6).
			IPv6 = 41,																

			// IPv6 Routing header.
			IPv6RoutingHeader = 43,										

			// IPv6 Fragment header.
			IPv6FragmentHeader = 44,									

			// IPv6 Encapsulating Security Payload header.
			IPSecEncapsulatingSecurityPayload = 50,				

			// IPv6 Authentication header. For details, see RFC 2292 section 2.2.1, available
			IPSecAuthenticationHeader = 51,							

			// Internet Control Message Protocol for IPv6.
			IcmpV6 = 58,														

			// IPv6 No next header.
			IPv6NoNextHeader = 59,										

			// IPv6 Destination Options header.
			IPv6DestinationOptions = 60,								

			// Net Disk Protocol (unofficial).
			ND = 77,															

			// Raw IP packet protocol.
			RawProtocol = 255,											

			// Internet Packet Exchange Protocol.
			IpxProtocol = 1000,												

			// Sequenced Packet Exchange protocol.
			Spx = 1256,															

			// Sequenced Packet Exchange version 2 protocol.
			SpxII = 1257,															
		};

		enum SOCKET_TYPE_ENUM
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
		};

		// Asynchronize configure structure
		struct AsyncResult
		{
			WSABUF wsaBuf;

			Int32 iBufSize;

			typedef None(*AsyncCallBack)(struct AsyncResult*);

			AsyncCallBack pCallBackFunc;

			Object SocketState;

			FixedUInt32 iOutSize;
		};

		// Socket call back function
		typedef AsyncResult::AsyncCallBack AsyncCallBack;

		// The way of windows Async
		typedef WSAOVERLAPPED wsaAsync;

		// Asynchronize result
		struct AsyncRes
		{
			wsaAsync AsynSocket;

			AsyncResult Result;
		};
	}
}

#endif // SOCKETTYPE_H