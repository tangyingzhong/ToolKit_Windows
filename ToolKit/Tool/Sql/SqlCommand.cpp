#include "PreCompile.h"
#include "SqlCommand.h"

using namespace System::ADO;

// Construct the SqlCommand
SqlCommand::SqlCommand(String strSqlText, Connection pConnection) :m_Connection(pConnection),
m_Commnd(NULL),
m_SqlText(strSqlText),
m_Disposed(false)
{
	Initialize();
}

// Detructe the SqlCommand
SqlCommand::~SqlCommand()
{
	Destory();
}

// Init the cmd
SqlCommand::Empty SqlCommand::Initialize()
{
	// Init the com
	::CoInitialize(NULL);

	// Create command
	CreateCommand();
}

// Destory the command
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

// Create the command ptr
SqlCommand::Empty SqlCommand::CreateCommand()
{
	try
	{
		m_Commnd.CreateInstance(__uuidof(Command));

		m_Commnd->ActiveConnection = GetConnection()->GetConnector();
	}
	catch (_com_error e)
	{
		ERROR_MESSAGEBOX(_T("DB Error"), e.ErrorMessage());
	}
}

// Destory the command ptr
SqlCommand::Empty SqlCommand::DestoryCommand()
{
	if (GetComm())
	{
		GetComm()->Release();

		SetComm(NULL);
	}
}

// Excute the sql(add,delete,modify)
SqlCommand::AffectedRows SqlCommand::ExecuteNonQuery()
{
	_variant_t AffectedCount = 0;

	try
	{
		// Set the sql command 
		GetComm()->CommandText = GetSqlText().AllocWideString();

		// Excute the sql
		GetComm()->Execute(&AffectedCount, NULL, CommandTypeEnum::adCmdText);
	}
	catch (_com_error e)
	{
		ERROR_MESSAGEBOX(_T("DB Error"), e.ErrorMessage());
	}

	return (AffectedRows)AffectedCount;
}

// Excute the sql(serach)
SqlCommand::pRecordSet SqlCommand::ExecuteNonQuery(AffectedRows& iAffectRows)
{
	pRecordSet Records = NULL;

	try
	{
		// Set the sql command 
		GetComm()->CommandText = GetSqlText().AllocWideString();

		// Excute the sql
		_variant_t AffectedCount = 0;
		Records = GetComm()->Execute(&AffectedCount, NULL, CommandTypeEnum::adCmdText);

		iAffectRows = (AffectedRows)AffectedCount;
	}
	catch (_com_error e)
	{
		ERROR_MESSAGEBOX(_T("DB Error"), e.ErrorMessage());
	}

	return Records;
}

// Add Paramenter
SqlCommand::Empty SqlCommand::Add(SqlParamenter* pSqlPara)
{
	if (GetComm())
	{
		if (pSqlPara->GetDirection() == adParamReturnValue || pSqlPara->GetDirection() == adParamOutput)
		{
			// Create the paramenter
			IDispatch* pObject = GetComm()->CreateParameter(pSqlPara->GetParaName().AllocWideString(), 
				pSqlPara->GetDataType(),
				pSqlPara->GetDirection(), 
				pSqlPara->GetParamenterSize());

			// Append the para
			GetComm()->Parameters->Append(pObject);
		}
		else
		{
			// Create the paramenter
			IDispatch* pObject = GetComm()->CreateParameter(pSqlPara->GetParaName().AllocWideString(), 
				pSqlPara->GetDataType(),
				pSqlPara->GetDirection(),
				pSqlPara->GetParamenterSize(), 
				pSqlPara->GetParaValue());

			// Append the para
			GetComm()->Parameters->Append(pObject);
		}
	}
}

// Excute the process
SqlCommand::Empty SqlCommand::Excute(String strStoreProcName)
{
	if (strStoreProcName == _T(""))
	{
		return;
	}

	if (GetComm())
	{
		try
		{
			GetComm()->CommandText = strStoreProcName.AllocWideString();

			GetComm()->CommandType = adCmdStoredProc;

			GetComm()->Execute(NULL, NULL, adCmdStoredProc);
		}
		catch (_com_error e)
		{
			ERROR_MESSAGEBOX(_T("Stored Procedure Run Error"), e.ErrorMessage());
		}
	}
}

// Get the values
SqlCommand::Any SqlCommand::GetParamenterValue(String strParaName)
{
	if (GetComm())
	{
		return GetComm()->Parameters->GetItem(strParaName.AllocWideString())->GetValue();
	}

	return 0;
}

// Get the values
SqlCommand::Any SqlCommand::GetParamenterValue(Index index)
{
	if (GetComm())
	{
		return GetComm()->Parameters->GetItem(short(index))->GetValue();
	}

	return 0;
}