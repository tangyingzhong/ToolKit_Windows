///************************************************************************
/// <copyrigth>2018-2019 Corporation.All Rights Reserved</copyrigth>
/// <author>tangyingzhong</author>
/// <contact>tangyz114987@outlook.com</contact>
/// <version>v1.0.0</version>
/// <describe>
/// Sql paras for sql command
///</describe>
/// <date>2019/7/16</date>
///***********************************************************************
#ifndef SQLPARAMENTER_H
#define SQLPARAMENTER_H

#include "Tool/BaseType/String.h"

#import "msado15.dll" no_namespace rename("EOF", "EndOfFile")

using namespace System::BasicType;

namespace System
{
	namespace DataBase
	{
		class SqlParamenter
		{
		public:
			typedef System::None None;
			typedef System::Int32 ParamenterSize;
			typedef  _ParameterPtr Paramenter;
			typedef _variant_t ParamenterType;

		public:
			// Construct the SqlParamenter
			SqlParamenter(String strParaName = _T("default"),
				DataTypeEnum DataType = DataTypeEnum::adInteger,
				ParameterDirectionEnum ParaDirection = ParameterDirectionEnum::adParamInput,
				ParamenterSize ParaSize = 4,
				ParamenterType Value = 1);

			// Detructe the SqlParamenter
			~SqlParamenter();

			// Copy SqlParamenter
			SqlParamenter(const SqlParamenter& other);

			// Asigment of SqlParamenter
			SqlParamenter& operator=(const SqlParamenter& other);

		public:
			// Get paramenter name
			inline String GetParaName() const
			{
				return m_ParaName;
			}

			// Set paramenter name
			inline None SetParaName(String strParaName)
			{
				m_ParaName = strParaName;
			}

			// Get the data type
			inline DataTypeEnum GetDataType() const
			{
				return m_DataType;
			}

			// Set the data type
			inline None SetDataType(DataTypeEnum eDataType)
			{
				m_DataType = eDataType;
			}

			// Get the Direction
			inline ParameterDirectionEnum GetDirection() const
			{
				return m_Direction;
			}

			// Set the Direction
			inline None SetDirection(ParameterDirectionEnum eDirection)
			{
				m_Direction = eDirection;
			}

			// Get the ParamenterSize
			inline ParamenterSize GetParamenterSize() const
			{
				return m_ParaSize;
			}

			// Set the ParamenterSize
			inline None SetParamenterSize(ParamenterSize iParaSize)
			{
				m_ParaSize = iParaSize;
			}

			// Get the Value
			inline ParamenterType GetParaValue() const
			{
				return m_ParaValue;
			}

			// Set the Value
			inline None SetParaValue(ParamenterType ParaValue)
			{
				m_ParaValue = ParaValue;
			}

		private:
			// Init the paramenter
			None Initialize();

			// Destory the paramenter
			None Destory();

		private:
			// Get the disposed status
			inline BOOL GetDisposed() const
			{
				return m_Disposed;
			}

			// Set the disposed status
			inline None SetDisposed(BOOL bDisposed)
			{
				m_Disposed = bDisposed;
			}

		private:
			// The paramenter's name
			String m_ParaName;

			// The type of the paramenter
			DataTypeEnum m_DataType;

			// The direction of the paramenter
			ParameterDirectionEnum m_Direction;

			// The size of the paramenter
			ParamenterSize m_ParaSize;

			// Paramenter's value
			ParamenterType m_ParaValue;

			// Disposed status
			BOOL m_Disposed;
		};
	}
}

#endif // SQLPARAMENTER_H