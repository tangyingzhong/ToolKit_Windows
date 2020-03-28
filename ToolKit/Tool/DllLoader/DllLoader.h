///************************************************************************
/// <copyrigth>Voice AI Technology Of ShenZhen</copyrigth>
/// <author>tangyingzhong</author>
/// <contact>yingzhong@voiceaitech.com</contact>
/// <version>v1.0.0</version>
/// <describe>
/// It is responsible for loading DLLs and unloading the DLLs
///</describe>
/// <date>2019/7/29</date>
///***********************************************************************
#ifndef DLLLOADER_H
#define DLLLOADER_H

#include "Tool/Common/SystemType.h"
#include "Tool/BaseType/String.h"

using namespace System::BasicType;

namespace System
{
	class DllLoader
	{
	public:
		// Construct the DllLoader
		DllLoader();
		
		// Detructe the DllLoader
		~DllLoader();

	private:
		// Forbid the copy DllLoader
		DllLoader(const DllLoader& other){	}
		
		// Forbid the assigment of DllLoader
		DllLoader& operator=(const DllLoader& other){	}
		
	public:
		// Is library opened or not
		Boolean IsOpen();

		// Load the library
		Boolean Load(String strLibraryName,String& strErrorMsg);

		// Unload the library
		Boolean Unload();

		// Get function
		template <class T>
		T GetFunc(String strFunctionName)
		{
			if (strFunctionName.IsEmpty())
			{
				return NULL;
			}

			if (GetLibraryModule() == NULL)
			{
				return NULL;
			}

			return (T)(::GetProcAddress(m_hLibraryModule, strFunctionName.ToAnsiData().c_str()));
		}

	private:
		// Initialize the library
		None Initialize();

		// Destory the library
		None Destory();

	private:
		// Get the Library
		inline HMODULE GetLibraryModule() const
		{
			return m_hLibraryModule;
		}

		// Set the Library
		inline None SetLibraryModule(HMODULE hLibraryModule)
		{
			m_hLibraryModule = hLibraryModule;
		}

		// Get the LibraryName
		inline String GetLibraryName() const
		{
			return m_strLibraryName;
		}

		// Set the LibraryName
		inline None SetLibraryName(String strLibraryName)
		{
			m_strLibraryName = strLibraryName;
		}

		// Set the disposed status
		inline None SetDisposed(Boolean bDisposed)
		{
			m_bDisposed = bDisposed;
		}
		
		// Get the disposed status
		inline Boolean GetDisposed() const
		{
			return m_bDisposed;
		}
		
	private:
		// Library's module handle
		HMODULE m_hLibraryModule;

		// Library's name
		String m_strLibraryName;

		// Disposed status
		Boolean m_bDisposed;	
	};
}

#endif //DLLLOADER_H
