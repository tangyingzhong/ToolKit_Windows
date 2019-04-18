#include "Application\PreCompile.h"
#include "SqlParamenter.h"

using namespace System::ADO;

///************************************************************************
/// <summary>
/// Construct the SqlParamenter
/// </summary>
/// <param name=paraName>paramenter name</param>
/// <param name=type>para's type</param>
/// <param name=direction>para's direction</param>
/// <param name=size>para's size</param>
/// <returns></returns>
/// <remarks>
/// none
/// </remarks>
///***********************************************************************
SqlParamenter::SqlParamenter(String strParaName, DataTypeEnum DataType, ParameterDirectionEnum ParaDirection, ParamenterSize ParaSize, ParamenterType Value)
{
	Initialize();
}


///************************************************************************
/// <summary>
/// Detructe the SqlParamenter
/// </summary>
/// <returns></returns>
/// <remarks>
/// none
/// </remarks>
///***********************************************************************
SqlParamenter::~SqlParamenter()
{
	Destory();
}



///************************************************************************
/// <summary>
/// Copy SqlParamenter
/// </summary>
/// <param name=other></param>
/// <returns></returns>
/// <remarks>
/// this is not a deep copy
/// </remarks>
///***********************************************************************
SqlParamenter::SqlParamenter(const SqlParamenter& other)
{
	this->SetParaName(other.GetParaName());
	this->SetDataType(other.GetDataType());
	this->SetDirection(other.GetDirection());
	this->SetParamenterSize(other.GetParamenterSize());
	this->SetParaValue(other.GetParaValue());
	this->SetDisposed(other.GetDisposed());
}


///************************************************************************
/// <summary>
/// Asigment of SqlParamenter
/// </summary>
/// <param name=other></param>
/// <returns></returns>
/// <remarks>
/// none
/// </remarks>
///***********************************************************************
SqlParamenter& SqlParamenter::operator=(const SqlParamenter& other)
{
	if (this != &other)
	{
		this->SetParaName(other.GetParaName());
		this->SetDataType(other.GetDataType());
		this->SetDirection(other.GetDirection());
		this->SetParamenterSize(other.GetParamenterSize());
		this->SetParaValue(other.GetParaValue());
		this->SetDisposed(other.GetDisposed());
	}

	return *this;
}

///************************************************************************
/// <summary>
/// Init the paramenter
/// </summary>
/// <param name=paraName>paramenter name</param>
/// <param name=type>para's type</param>
/// <param name=direction>para's direction</param>
/// <param name=size>para's size</param>
/// <returns></returns>
/// <remarks>
/// none
/// </remarks>
///***********************************************************************
SqlParamenter::Empty SqlParamenter::Initialize()
{

}


///************************************************************************
/// <summary>
/// Destory the paramenter
/// </summary>
/// <returns></returns>
/// <remarks>
/// none
/// </remarks>
///***********************************************************************
SqlParamenter::Empty SqlParamenter::Destory()
{
	if (!GetDisposed())
	{
		SetDisposed(true);
	}
}