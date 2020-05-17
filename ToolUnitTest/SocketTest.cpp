#include "stdafx.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Socket_UnitTest
{
	TEST_CLASS(SocketTest)
	{
	public:
		TEST_METHOD(Socket_GetLocalIP)
		{
			Socket Sock;

			String strIPAddr;

			Assert::IsTrue(Sock.GetLoaclIP(strIPAddr));

			Assert::IsTrue(strIPAddr == "192.168.1.2");
		}

		// Client
		TEST_METHOD(Socket_Client)
		{
			SocketClient Client("192.168.1.2",8080);

			if (Client.Start())
			{
				SByte RecvBuffer[1024] = {0};

				if (Client.Receive(RecvBuffer, 0, 1024))
				{
					std::string  strData = "do you want to know what?";

					Client.Send((char*)strData.c_str(), 0, strData.length());

					Client.Stop();
				}
			}
		}

		// Server
		TEST_METHOD(Socket_Server)
		{
			SocketServer Server(8080,13);

			if (Server.Start())
			{
				Socket Client;

				if (Server.Accept(Client))
				{
					SByte RecvBuffer[1024] = { 0 };

					if (Server.Receive(&Client,RecvBuffer, 0, 1024))
					{
						std::string  strData = "do you want to know what?";

						Server.Send(&Client, (char*)strData.c_str(), 0, strData.length());

						Server.Stop();
					}
				}
			}
		}
	};
}
