///************************************************************************
/// <copyrigth>2018-2019 Corporation.All Rights Reserved</copyrigth>
/// <author>tangyingzhong</author>
/// <contact>tangyz114987@outlook.com</contact>
/// <version>V1.0.0</version>
/// <describe>
/// Com object to connect the Database
///</describe>
/// <date>2019/3/6</date>
///***********************************************************************
#ifndef SQLCONNECTION_H
#define SQLCONNECTION_H

#include <comdef.h>
#include <COMUTIL.H>
#include "Tool\BaseType\String.h"

#import "msado15.dll" no_namespace rename("EOF", "EndOfFile")

using namespace System::BasicType;

namespace System
{
	namespace ADO
	{
		// Connect state of DB
		typedef enum _ConnectionState
		{
			ADO_CLOSED = 0,
			ADO_OPENED = 1,
			ADO_CONNECTING = 2,
			ADO_EXCUTING = 4,
			ADO_FETCHING = 8,
			ADO_BROKEN = 16
		}ConnectionState;

		///*********************************************************
		/// <class>SqlConnection</class>
		/// <summary>
		///  Connect the database
		/// </summary>
		/// <version>V1.0.0 </version>
		/// <goup> C++</group>
		/// <author>tangyingzhong</author>
		/// <contact>tangyingzhong@szangell.com</contact>
		///*********************************************************
		class SqlConnection
		{
		public:
			typedef System::Empty Empty;
			typedef System::Boolean BOOL;
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
			Empty Open();

			// Close the database
			Empty Close();

			// Set the Connector
			Connector GetConnector() const
			{
				return this->m_Connector;
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

		private:
			// Get the ConnectStr
			inline String GetConnectStr() const
			{
				return m_ConnectCmd;
			}

			// Set the ConnectStr
			inline Empty SetConnectStr(String strConnectCmd)
			{
				this->m_ConnectCmd = strConnectCmd;
			}

			// Set the Connector
			inline Empty SetConnector(Connector pConnector)
			{
				this->m_Connector = pConnector;
			}

			// Set connection state
			inline Empty SetConnectState(ConnectionState eConnectState)
			{
				this->m_ConnectState = eConnectState;
			}

			// Get the disposed status
			inline BOOL GetDisposed() const
			{
				return m_Disposed;
			}

			// Set the disposed status
			inline Empty SetDisposed(BOOL bDisposed)
			{
				this->m_Disposed = bDisposed;
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

#endif //SQLCONNECTION_H_