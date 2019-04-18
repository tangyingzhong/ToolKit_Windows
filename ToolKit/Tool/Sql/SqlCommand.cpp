#include "Application\PreCompile.h"
#include "SqlCommand.h"

using namespace System::ADO;

///************************************************************************
/// <summary>
/// Construct the SqlCommand
/// </summary>
/// <param name=con>connection object</param>
/// <returns></returns>
/// <remarks>
/// none
/// </remarks>
///***********************************************************************
SqlCommand::SqlCommand(String strSqlText, Connection pConnection) :m_Connection(pConnection),
m_Commnd(NULL),
m_SqlText(strSqlText),
m_Disposed(false)
{
	Initialize();
}


///************************************************************************
/// <summary>
/// Detructe the SqlCommand
/// </summary>
/// <returns></returns>
/// <remarks>
/// none
/// </remarks>
///***********************************************************************
SqlCommand::~SqlCommand()
{
	Destory();
}


///************************************************************************
/// <summary>
/// Init the cmd
/// </summary>
/// <param name=con>connection</param>
/// <returns></returns>
/// <remarks>
/// none
/// </remarks>
///***********************************************************************
SqlCommand::Empty SqlCommand::Initialize()
{
	// Init the com
	::CoInitialize(NULL);

	// Create command
	CreateCommand();
}


///************************************************************************
/// <summary>
/// Destory the command
/// </summary>
/// <returns></returns>
/// <remarks>
/// none
/// </remarks>
///***********************************************************************
SqlCommand::Empty SqlCommand::Destory()
{
	if (!GetDisposed())
	{
		SetDisposed(true);

		// Destory the command
		DestoryCommand();

		// UnInit the Com
		::CoUninitialize();
	}
}


///************************************************************************
/// <summary>
/// Create the command ptr
/// </summary>
/// <returns></returns>
/// <remarks>
/// none
/// </remarks>
///***********************************************************************
SqlCommand::Empty SqlCommand::CreateCommand()
{
	try
	{
		m_Commnd.CreateInstance(__uuidof(Command));
		m_Commnd->ActiveConnection = this->GetConnection()->GetConnector();
	}
	catch (_com_error e)
	{
		MessageBox(NULL, e.ErrorMessage(), _T("DB Error"), 0);
	}
}


///************************************************************************
/// <summary>
/// Destory the command ptr
/// </summary>
/// <returns></returns>
/// <remarks>
/// none
/// </remarks>
///***********************************************************************
SqlCommand::Empty SqlCommand::DestoryCommand()
{
	if (this->GetComm())
	{
		this->GetComm()->Release();

		this->SetComm(NULL);
	}
}


///************************************************************************
/// <summary>
/// Excute the sql(add,delete,modify)
/// </summary>
/// <returns></returns>
/// <remarks>
/// none
/// </remarks>
///***********************************************************************
SqlCommand::AffectedRows SqlCommand::ExecuteNonQuery()
{
	_variant_t AffectedCount = 0;

	try
	{
		// Set the sql command 
		GetComm()->CommandText = this->GetSqlText().AllocWideString();

		// Excute the sql
		GetComm()->Execute(&AffectedCount, NULL, CommandTypeEnum::adCmdText);
	}
	catch (_com_error e)
	{
		MessageBox(NULL, e.ErrorMessage(), _T("DB Error"), 0);
	}

	return (AffectedRows)AffectedCount;
}


///************************************************************************
/// <summary>
/// Excute the sql(serach)
/// </summary>
/// <param name=affectRows>get the return rows</param>
/// <returns></returns>
/// <remarks>
/// none
/// </remarks>
///***********************************************************************
SqlCommand::pRecordSet SqlCommand::ExecuteNonQuery(AffectedRows& iAffectRows)
{
	pRecordSet Records = NULL;

	try
	{
		// Set the sql command 
		GetComm()->CommandText = this->GetSqlText().AllocWideString();

		// Excute the sql
		_variant_t AffectedCount = 0;
		Records = GetComm()->Execute(&AffectedCount, NULL, CommandTypeEnum::adCmdText);

		iAffectRows = (AffectedRows)AffectedCount;
	}
	catch (_com_error e)
	{
		MessageBox(NULL, e.ErrorMessage(), _T("DB Error"), 0);
	}

	return Records;
}


///************************************************************************
/// <summary>
/// Add Paramenter
/// </summary>
/// <param name=para></param>
/// <returns></returns>
/// <remarks>
/// none
/// </remarks>
///***********************************************************************
SqlCommand::Empty SqlCommand::Add(SqlParamenter* pSqlPara)
{
	if (this->GetComm())
	{
		if (pSqlPara->GetDirection() == adParamReturnValue || pSqlPara->GetDirection() == adParamOutput)
		{
			// Create the paramenter
			IDispatch* pObject = this->GetComm()->CreateParameter(pSqlPara->GetParaName().AllocWideString(), pSqlPara->GetDataType(), pSqlPara->GetDirection(), pSqlPara->GetParamenterSize());

			// Append the para
			this->GetComm()->Parameters->Append(pObject);
		}
		else
		{
			// Create the paramenter
			IDispatch* pObject = this->GetComm()->CreateParameter(pSqlPara->GetParaName().AllocWideString(), pSqlPara->GetDataType(), pSqlPara->GetDirection(), pSqlPara->GetParamenterSize(), pSqlPara->GetParaValue());

			// Append the para
			this->GetComm()->Parameters->Append(pObject);
		}
	}
}


///************************************************************************
/// <summary>
/// Excute the process
/// </summary>
/// <param name=procName>process name</param>
/// <returns></returns>
/// <remarks>
/// none
/// </remarks>
///***********************************************************************
SqlCommand::Empty SqlCommand::Excute(String strStoreProcName)
{
	assert(strStoreProcName != _T(""));

	if (strStoreProcName == _T(""))
	{
		return;
	}

	if (this->GetComm())
	{
		try
		{
			this->GetComm()->CommandText = strStoreProcName.AllocWideString();

			this->GetComm()->CommandType = adCmdStoredProc;

			this->GetComm()->Execute(NULL, NULL, adCmdStoredProc);
		}
		catch (_com_error e)
		{
			MessageBox(NULL, e.ErrorMessage(), _T("Stored Procedure Run Error"), 0);
		}
	}
}


///************************************************************************
/// <summary>
/// Get the values
/// </summary>
/// <param name=paraName></param>
/// <returns></returns>
/// <remarks>
/// none
/// </remarks>
///***********************************************************************
SqlCommand::Any SqlCommand::GetParamenterValue(String strParaName)
{
	if (this->GetComm())
	{
		return this->GetComm()->Parameters->GetItem(strParaName.AllocWideString())->GetValue();
	}

	return 0;
}


///************************************************************************
/// <summary>
/// Get the values
/// </summary>
/// <param name=index></param>
/// <returns></returns>
/// <remarks>
/// none
/// </remarks>
///***********************************************************************
SqlCommand::Any SqlCommand::GetParamenterValue(Index index)
{
	if (this->GetComm())
	{
		return this->GetComm()->Parameters->GetItem(short(index))->GetValue();
	}

	return 0;
}