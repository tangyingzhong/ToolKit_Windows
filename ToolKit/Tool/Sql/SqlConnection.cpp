#include <iostream>
#include "SqlConnection.h"

using namespace System::DataBase;

// Construct the SqlConnection
SqlConnection::SqlConnection(String strConnectCmd) :m_ConnectCmd(strConnectCmd),
m_Connector(NULL),
m_ConnectState(ConnectionState::ADO_CLOSED),
m_Disposed(false)
{
	Initialize();
}

// Detructe the SqlConnection
SqlConnection::~SqlConnection()
{
	Destory();
}

// Init the connection
SqlConnection::Empty SqlConnection::Initialize()
{
	// Init the com
	::CoInitialize(NULL);

	// Create connect instance
	CreateConn();
}

// Destory the connection
SqlConnection::Empty SqlConnection::Destory()
{
	if (!GetDisposed())
	{
		SetDisposed(true);

		// Destory the connection
		DestoryConn();

		// UnInit the Com
		::CoUninitialize();
	}
}

// Output error string
Empty SqlConnection::OutputError(String strMsg)
{
#ifdef UNICODE
	std::cerr << strMsg.CStr() << std::endl;
#else
	std::cerr << strMsg.CStr() << std::endl;
#endif
}

// Create a connection
SqlConnection::Empty SqlConnection::CreateConn()
{
	try
	{
		m_Connector.CreateInstance(__uuidof(Connection));
	}
	catch (_com_error e)
	{
		OutputError(const_cast<TCHAR*>(e.ErrorMessage()));
	}
}

// Destory the Connection
SqlConnection::Empty SqlConnection::DestoryConn()
{
	Close();
}

// Open the DB
SqlConnection::BOOL SqlConnection::Open()
{
	try
	{
		HRESULT hConnect = GetConnector()->Open(GetConnectStr().CStr(), _T(""), _T(""), adConnectUnspecified);
		if (SUCCEEDED(hConnect))
		{
			SetConnectState(ConnectionState::ADO_OPENED);

			return true;
		}
	}
	catch (_com_error e)
	{
		Close();

		// Update the connect state
		SetConnectState(ConnectionState::ADO_BROKEN);

		// Send the error outside
		OutputError(const_cast<TCHAR*>(e.ErrorMessage()));
	}

	return false;
}

// Close the DB
SqlConnection::Empty SqlConnection::Close()
{
	if (GetConnector())
	{
		GetConnector()->Release();

		SetConnectState(ConnectionState::ADO_CLOSED);
	}
}