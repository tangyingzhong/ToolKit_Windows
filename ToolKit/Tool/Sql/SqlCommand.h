///************************************************************************
/// <copyrigth>2018-2019 Corporation.All Rights Reserved</copyrigth>
/// <author>tangyingzhong</author>
/// <contact>tangyz114987@outlook.com</contact>
/// <version>v1.0.0</version>
/// <describe>
/// Command to excute sql command
///</describe>
/// <date>2019/7/16</date>
///***********************************************************************
#ifndef SQLCOMMAND_H
#define SQLCOMMAND_H

#include "SqlConnection.h"
#include "SqlParamenter.h"

namespace System
{
	namespace DataBase
	{
		class SqlCommand
		{
		public:
			typedef System::Empty Empty;
			typedef System::Boolean BOOL;
			typedef System::Int32 Index;
			typedef System::Int32 AffectedRows;
			typedef _CommandPtr pCommand;
			typedef SqlConnection* Connection;
			typedef ParametersPtr Paramenter;
			typedef _RecordsetPtr pRecordSet;
			typedef _variant_t Any;

		public:
			// Construct the SqlCommand for common sql
			SqlCommand(String strSqlText, Connection pConnection);

			// Detructe the SqlCommand
			~SqlCommand();

		private:
			// Copy SqlCommand
			SqlCommand(const SqlCommand& other) {	}

			// Asigment of SqlCommand
			SqlCommand& operator=(const SqlCommand& other) {	}

		public:
			// Excute the sql(add,delete,modify)
			AffectedRows ExecuteNonQuery();

			// Excute the sql(serach sql)
			pRecordSet ExecuteNonQuery(AffectedRows& iAffectRows);

		public:
			// Add Paramenter
			Empty Add(SqlParamenter* pSqlPara);

			// Excute the process
			Empty Excute(String strStoreProcName);

			// Get the values
			Any GetParamenterValue(String strParaName);

			// Get the values
			Any GetParamenterValue(Index iParaIndex);

		private:
			// Init the command
			Empty Initialize();

			// Destory the command
			Empty Destory();

			// Create the command ptr
			Empty CreateCommand();

			// Destory the command ptr
			Empty DestoryCommand();

		private:
			// Get the Connection
			inline Connection GetConnection() const
			{
				return m_Connection;
			}

			// Set the Connection
			inline Empty SetConnection(Connection pConnection)
			{
				m_Connection = pConnection;
			}

			// Get the commmnd
			inline pCommand GetComm() const
			{
				return m_Commnd;
			}

			// Set the commmnd
			inline Empty SetComm(pCommand pComm)
			{
				m_Commnd = pComm;
			}

			// Get the SqlText
			inline String GetSqlText() const
			{
				return m_SqlText;
			}

			// Set the SqlText
			inline Empty SetSqlText(String strSqlText)
			{
				m_SqlText = strSqlText;
			}

			// Get the Paramenter
			inline SqlParamenter GetParamenter() const
			{
				return m_SqlParamenter;
			}

			// Set the Paramenter
			inline Empty SetParamenter(SqlParamenter& SqlPara)
			{
				m_SqlParamenter = SqlPara;
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
			// Database connection
			Connection m_Connection;

			// Commond of operate database
			pCommand m_Commnd;

			// Sql string as excutable cmd
			String m_SqlText;

			// Sql paramenters for store procced 
			SqlParamenter m_SqlParamenter;

			// Disposed status
			BOOL m_Disposed;

		};
	}
}

#endif // SQLCOMMAND_H