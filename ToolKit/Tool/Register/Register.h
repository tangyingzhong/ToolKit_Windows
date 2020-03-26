///************************************************************************
/// <copyrigth>2018-2019 Corporation.All Rights Reserved</copyrigth>
/// <author>tangyingzhong</author>
/// <contact>tangyz114987@outlook.com</contact>
/// <version>v1.0.0</version>
/// <describe>
/// Register the module into system so that other moule can use it
///</describe>
/// <date>2019/8/18</date>
///***********************************************************************
#ifndef REGISTER_H
#define REGISTER_H

#include "Tool/Common/SystemType.h"
#include "Tool/DllLoader/DllLoader.h"
#include "ExportConfig.h"

using namespace System;
using namespace std;

#define REGISTER_CREATE_MODULE(BaseClassType,ClassType) \
DLL_API BaseClassType* CreateModule()\
{\
	return new ClassType();\
}

#define REGISTER_DESTORY_MODULE(BaseClassType) \
DLL_API void DestoryModule(BaseClassType* pModule) \
{\
	if (pModule != NULL) \
	{\
		delete pModule;\
		\
		pModule = NULL;\
	}\
}

#define REGISTER_MODULE(BaseClassType,ClassType) \
REGISTER_CREATE_MODULE(BaseClassType,ClassType); \
REGISTER_DESTORY_MODULE(BaseClassType);

#define CREATE_MODULE(BaseClassType,ModuleName) \
String strModuleName=String(ModuleName); \
int iPos= strModuleName.FindLast(_T(".")); \
String strClassName= strModuleName.Left(iPos); \
class strClassName##Creator\
{\
public:\
	typedef BaseClassType* (*CreateModule)();\
	typedef void (*DestoryModule)(BaseClassType*);\
	typedef BaseClassType* Interface;\
\
public:\
	strClassName##Creator()\
	{\
		m_pDllLoader=new DllLoader();\
\
		if(m_pDllLoader)\
		{\
			m_pDllLoader->Load(ModuleName); \
\
			CreateModule pCreateModule = m_pDllLoader->GetFunc<CreateModule>(_T("CreateModule")); \
\
			m_pInterface=pCreateModule();\
\
			m_pDestoryModule=m_pDllLoader->GetFunc<DestoryModule>(_T("DestoryModule"));\
		}\
	}\
\
	~strClassName##Creator()\
	{\
		if (m_pInterface)\
		{\
			m_pDestoryModule(m_pInterface);\
		}\
\
		if (m_pDllLoader)\
		{\
			m_pDllLoader->Unload(); \
\
			delete m_pDllLoader;\
	\
			m_pDllLoader = NULL;\
		}\
	}\
	\
	inline Interface GetInterface() const\
	{\
		return m_pInterface;\
	}\
\
private:\
	DllLoader* m_pDllLoader;\
\
	Interface m_pInterface; \
\
	DestoryModule m_pDestoryModule;\
};\
\
strClassName##Creator pCreator=new strClassName##Creator();\

#define GET_MODULE() \
pCreator->GetInterface()\

#define DESTORY_MODULE() \
if(pCreator) \
{\
	delete pCreator;\
\
	pCreator = NULL;\
}

#endif // REGISTER