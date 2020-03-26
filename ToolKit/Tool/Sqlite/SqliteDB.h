///************************************************************************
/// <copyrigth>Voice AI Technology Of ShenZhen</copyrigth>
/// <author>tangyingzhong</author>
/// <contact>yingzhong@voiceaitech.com</contact>
/// <version>v1.0.0</version>
/// <describe>
///  You can operate the sqlite by this class
///</describe>
/// <date>2019/8/6</date>
///***********************************************************************
#ifndef SQLITEDB_H
#define SQLITEDB_H

#include "BaseType/String.h"
#include "Common/SystemType.h"
#include "../../ShareLib/Sqlite_3.0/include/sqlite3.h"

using namespace std;
using namespace System::BasicType;

namespace System
{
	namespace DataBase
	{
		class SqliteDB
		{
		public:
			typedef sqlite3* SqliteDataBase;
			typedef vector<vector<std::string> > RecordTable;

		public:
			// Construct the SqliteDB
			SqliteDB();

			// Detructe the SqliteDB
			~SqliteDB();

		private:
			// Forbid the Copy 
			SqliteDB(const SqliteDB& other) {	}

			// Forbid the assigment of 
			SqliteDB& operator=(const SqliteDB& other) {	}

		public:
			// Open the sqlite
			Boolean Open(String strDbFilePath);

			// Close the sqlite
			Empty Close();

			// Is opened or not
			Boolean IsOpen();

			// Excute the sql(serach sql)
			Boolean ExecuteNonQuery(String strSql,Int32 iRetCode=0);

			// Excute the sql(serach sql)
			Boolean ExecuteNonQuery(String strSql, RecordTable& Table);

			// Get the ErrorMessage
			inline String GetErrorMessage() const
			{
				return m_strErrorMessage;
			}

		private:
			// Initialize the sqlite
			Empty Initialize();

			// Destory the sqlite
			Empty Destory();

			// Excute the command 
			Boolean Excute(String strSql, Int32 iRetCode = 0);

		private:
			// Get the DB
			inline SqliteDataBase& GetDB()
			{
				return m_pDB;
			}

			// Set the DB
			inline void SetDB(SqliteDataBase pDB)
			{
				m_pDB = pDB;
			}

			// Set the ErrorMessage
			inline void SetErrorMessage(String strErrorMessage)
			{
				m_strErrorMessage = strErrorMessage;
			}

			// Get disposed status
			inline Boolean GetDisposed() const
			{
				return this->m_Disposed;
			}

			// Set the disposed status
			inline void SetDisposed(Boolean bDisposed)
			{
				this->m_Disposed = bDisposed;
			}

			// Get the IsOpen
			inline Boolean GetIsOpen() const
			{
				return m_bIsOpen;
			}

			// Set the IsOpen
			inline Empty SetIsOpen(Boolean bIsOpen)
			{
				m_bIsOpen = bIsOpen;
			}

		private:
			// Sqlite db
			SqliteDataBase m_pDB;

			// Db is opened or not
			Boolean m_bIsOpen;

			// Error Message
			String m_strErrorMessage;

			// Disposed status
			Boolean m_Disposed;
		};
	}
}

#endif //SQLITEDB_H