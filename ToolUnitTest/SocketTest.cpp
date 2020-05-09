#include "stdafx.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Tool_UnitTest
{
	TEST_CLASS(SocketTest)
	{
	public:
		TEST_METHOD(Socket_GetLocalIP)
		{
			Socket Sock;

			String strIPAddr;

			Assert::IsTrue(Sock.GetLoaclIP(strIPAddr));
		}
	};
}
