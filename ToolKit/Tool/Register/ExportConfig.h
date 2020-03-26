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

#define EXPOT_MODULE

#ifdef EXPOT_MODULE

#define DLL_API extern "C" __declspec(dllexport)

#else 

#define DLL_API __declspec(dllimport)

#endif

#endif //EXPORTCONFIG_H
