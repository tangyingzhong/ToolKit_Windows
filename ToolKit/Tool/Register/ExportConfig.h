///************************************************************************
/// <copyrigth>2018-2019 Corporation.All Rights Reserved</copyrigth>
/// <author>tangyingzhong</author>
/// <contact>tangyz114987@outlook.com</contact>
/// <version>v1.0.0</version>
/// <describe>
/// DLL configure here 
///</describe>
/// <date>2019/7/25</date>
///***********************************************************************
#ifndef EXPORTCONFIG_H
#define EXPORTCONFIG_H

#ifdef EXPORT_FUNCTION

#define FUNC_ITEM extern "C" __declspec(dllexport)

#else 

#define FUNC_ITEM extern "C" __declspec(dllimport)

#endif

#ifdef EXPORT_CLASS

#define CLASS_ITEM  __declspec(dllexport)

#else 

#define CLASS_ITEM  __declspec(dllimport)

#endif

#endif //EXPORTCONFIG_H
