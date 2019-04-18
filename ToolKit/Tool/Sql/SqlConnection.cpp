#include "Application\PreCompile.h"
#include "SqlConnection.h"

using namespace System::ADO;

///************************************************************************
/// <summary>
/// Construct the SqlConnection
/// </summary>
/// <param name=connectStr>connect string</param>
/// <returns></returns>
/// <remarks>
/// none
/// </remarks>
///***********************************************************************
SqlConnection::SqlConnection(String strConnectCmd) :m_ConnectCmd(strConnectCmd),
m_Connector(NULL),
m_ConnectState(ConnectionState::ADO_CLOSED),
m_Disposed(false)
{
	Initialize();
}


///************************************************************************
/// <summary>
/// Detructe the SqlConnection
/// </summary>
/// <returns></returns>
/// <remarks>
/// none
/// </remarks>
///***********************************************************************
SqlConnection::~SqlConnection()
{
	Destory();
}


///************************************************************************
/// <summary>
/// Init the connection
/// </summary>
/// <param name=conStr>connect string</param>
/// <returns></returns>
/// <remarks>
/// none
/// </remarks>
///***********************************************************************
SqlConnection::Empty SqlConnection::Initialize()
{
	// Init the com
	::CoInitialize(NULL);

	// Create connect instance
	CreateConn();
}


///************************************************************************
/// <summary>
/// Destory the connection
/// </summary>
/// <returns></returns>
/// <remarks>
/// none
/// </remarks>
///***********************************************************************
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


///************************************************************************
/// <summary>
/// Create a connection
/// </summary>
/// <returns></returns>
/// <remarks>
/// none
/// </remarks>
///***********************************************************************
SqlConnection::Empty SqlConnection::CreateConn()
{
	try
	{
		m_Connector.CreateInstance(__uuidof(Connection));
	}
	catch (_com_error e)
	{
		MessageBox(NULL, e.ErrorMessage(), _T("Database Error"), 0);
	}
}


///************************************************************************
/// <summary>
/// Destory the Connection
/// </summary>
/// <returns></returns>
/// <remarks>
/// none
/// </remarks>
///***********************************************************************
SqlConnection::Empty SqlConnection::DestoryConn()
{
	// Close the conn
	this->Close();
}


///************************************************************************
/// <summary>
/// Open the DB
/// </summary>
/// <returns></returns>
/// <remarks>
/// none
/// </remarks>
///***********************************************************************
SqlConnection::Empty SqlConnection::Open()
{
	try
	{
		HRESULT hConnect = this->GetConnector()->Open(this->GetConnectStr().AllocWideString(), _T(""), _T(""), adConnectUnspecified);
		if (SUCCEEDED(hConnect))
		{
			this->SetConnectState(ConnectionState::ADO_OPENED);
		}
	}
	catch (_com_error e)
	{
		this->Close();

		// Update the connect state
		this->SetConnectState(ConnectionState::ADO_BROKEN);

		// Send the error outside
		MessageBox(NULL, e.ErrorMessage(), _T("Database Error"), 0);
	}
}


///************************************************************************
/// <summary>
/// Close the DB
/// </summary>
/// <returns></returns>
/// <remarks>
/// none
/// </remarks>
///***********************************************************************
SqlConnection::Empty SqlConnection::Close()
{
	if (this->GetConnector())
	{
		this->GetConnector()->Close();

		this->SetConnectState(ConnectionState::ADO_CLOSED);
	}
}