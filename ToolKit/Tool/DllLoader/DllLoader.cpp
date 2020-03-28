#include "DllLoader.h"

using namespace System;

// Construct the DllLoader
DllLoader::DllLoader():m_strLibraryName(_T("")),
m_hLibraryModule(NULL),
m_bDisposed(false)
{
	Initialize();
}

// Detructe the DllLoader
DllLoader::~DllLoader()
{
	Destory();
}

// Initialize the library
None DllLoader::Initialize()
{
	
}

// Destory the library
None DllLoader::Destory()
{
	if (!GetDisposed())
	{
		SetDisposed(true);

		Unload();
	}
}

// Is library opened or not
Boolean DllLoader::IsOpen()
{
	if (GetLibraryModule())
	{
		return true;
	}

	return false;
}

// Load the library
Boolean DllLoader::Load(String strLibraryName, String& strErrorMsg)
{
	if (strLibraryName.IsEmpty())
	{
		return false;
	}

	if (IsOpen())
	{
		return true;
	}

	SetLibraryName(strLibraryName);

	SetLibraryModule(::LoadLibraryEx(GetLibraryName().CStr(), 
		NULL, 
		LOAD_WITH_ALTERED_SEARCH_PATH));

	if (GetLibraryModule())
	{
		return true;
	}

	DWORD dErrorCode = GetLastError();

	strErrorMsg = String(_T("Failed to load dll . Error code: %d")).Arg((Int32)dErrorCode);

	MessageBox(NULL, strErrorMsg.CStr(),_T("DllLoader Error"), 0);

	return false;
}

// Unload the library
Boolean DllLoader::Unload()
{
	if (IsOpen())
	{
		if (::FreeLibrary(GetLibraryModule()) == TRUE)
		{
			SetLibraryModule(NULL);

			return true;
		}

		return false;
	}

	return true;
}