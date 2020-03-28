#include "SqlParamenter.h"

using namespace System::DataBase;

// Construct the SqlParamenter
SqlParamenter::SqlParamenter(String strParaName,
	DataTypeEnum DataType,
	ParameterDirectionEnum ParaDirection,
	ParamenterSize ParaSize,
	ParamenterType Value) :m_ParaName(strParaName),
	m_DataType(DataType),
	m_Direction(ParaDirection),
	m_ParaSize(ParaSize),
	m_ParaValue(Value),
	m_Disposed(false)
{
	Initialize();
}

// Detructe the SqlParamenter
SqlParamenter::~SqlParamenter()
{
	Destory();
}

// Copy SqlParamenter
SqlParamenter::SqlParamenter(const SqlParamenter& other)
{
	SetParaName(other.GetParaName());
	SetDataType(other.GetDataType());
	SetDirection(other.GetDirection());
	SetParamenterSize(other.GetParamenterSize());
	SetParaValue(other.GetParaValue());
	SetDisposed(other.GetDisposed());
}

// Asigment of SqlParamenter
SqlParamenter& SqlParamenter::operator=(const SqlParamenter& other)
{
	if (this != &other)
	{
		SetParaName(other.GetParaName());
		SetDataType(other.GetDataType());
		SetDirection(other.GetDirection());
		SetParamenterSize(other.GetParamenterSize());
		SetParaValue(other.GetParaValue());
		SetDisposed(other.GetDisposed());
	}

	return *this;
}

// Init the paramenter
SqlParamenter::None SqlParamenter::Initialize()
{

}

// Destory the paramenter
SqlParamenter::None SqlParamenter::Destory()
{
	if (!GetDisposed())
	{
		SetDisposed(true);
	}
}