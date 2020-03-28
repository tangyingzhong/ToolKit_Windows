///************************************************************************
/// <copyrigth>2018-2019 Corporation.All Rights Reserved</copyrigth>
/// <author>tangyingzhong</author>
/// <contact>tangyz114987@outlook.com</contact>
/// <version>v1.0.0</version>
/// <describe>
/// Com object to connect the Database
///</describe>
/// <date>2019/7/16</date>
///***********************************************************************
#ifndef SQLCONNECTION_H
#define SQLCONNECTION_H

#include "Tool/BaseType/String.h"

#import "msado15.dll" no_namespace rename("EOF", "EndOfFile")

using namespace System::BasicType;

namespace System
{
	namespace DataBase
	{
		// Connect state of DB
		enum CONNECT_STATE_ENUM
		{
			ADO_CLOSED = 0,
			ADO_OPENED = 1,
			ADO_CONNECTING = 2,
			ADO_EXCUTING = 4,
			ADO_FETCHING = 8,
			ADO_BROKEN = 16
		};

		class SqlConnection
		{
		public:
			typedef System::Empty Empty;
			typedef System::Boolean BOOL;
			typedef CONNECT_STATE_ENUM ConnectionState;
			typedef _ConnectionPtr Connector;

		public:
			// Construct the SqlConnection
			SqlConnection(String strConnectCmd);

			// Detructe the SqlConnection
			~SqlConnection();

		private:
			// Copy SqlConnection
			SqlConnection(const SqlConnection& other) {	}

			// Asigment of SqlConnection
			SqlConnection& operator=(const SqlConnection& other) {	}

		public:
			// Open the database
			BOOL Open();

			// Close the database
			Empty Close();

			// Set the Connector
			Connector GetConnector() const
			{
				return m_Connector;
			}

			// Get connection state
			inline ConnectionState GetConnectState() const
			{
				return m_ConnectState;
			}

		private:
			// Init the connection
			Empty Initialize();

			// Destory the connection
			Empty Destory();

			// Create a connection
			Empty CreateConn();

			// Destory the Connection
			Empty DestoryConn();

			// Output error string
			Empty OutputError(String strMsg);

		private:
			// Get the ConnectStr
			inline String GetConnectStr() const
			{
				return m_ConnectCmd;
			}

			// Set the ConnectStr
			inline Empty SetConnectStr(String strConnectCmd)
			{
				m_ConnectCmd = strConnectCmd;
			}

			// Set the Connector
			inline Empty SetConnector(Connector pConnector)
			{
				m_Connector = pConnector;
			}

			// Set connection state
			inline Empty SetConnectState(ConnectionState eConnectState)
			{
				m_ConnectState = eConnectState;
			}

			// Get the disposed status
			inline BOOL GetDisposed() const
			{
				return m_Disposed;
			}

			// Set the disposed status
			inline Empty SetDisposed(BOOL bDisposed)
			{
				m_Disposed = bDisposed;
			}

		private:
			// Connect string 
			String m_ConnectCmd;

			// Connection pointer
			Connector m_Connector;

			// Connection state
			ConnectionState m_ConnectState;

			// Disposed status
			BOOL m_Disposed;

		};
	}
}

#endif // SQLCONNECTION_H