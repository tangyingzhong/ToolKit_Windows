#include "Application\PreCompile.h"
#include "Directory.h"

using namespace System::IO;

///************************************************************************
/// <summary>
/// Create a directory
/// </summary>
/// <param name=strDirPath>target directory path</param>
/// <returns>false£ºcreate failed true£ºcreate ok</returns>
/// <remarks>
/// none
/// </remarks>
///***********************************************************************
Directory::BOOL Directory::Create(String strDirPath)
{
	BOOL bSuccess = false;

	int iRet = ::CreateDirectory(strDirPath, NULL);
	if (iRet == TRUE)
	{
		bSuccess = true;
	}

	return bSuccess;
}


///************************************************************************
/// <summary>
/// Delete an empty directory
/// </summary>
/// <param name=strDirPath>target directory path</param>
/// <returns>false£ºdelete failed true£ºdelete ok</returns>
/// <remarks>
/// the directory must be empty 
/// </remarks>
///***********************************************************************
Directory::BOOL Directory::Delete(String strDirPath)
{
	BOOL bSuccess = false;

	int iRet = ::RemoveDirectory(strDirPath);
	if (iRet == TRUE)
	{
		bSuccess = true;
	}

	return bSuccess;
}


///************************************************************************
/// <summary>
/// Judge that whether the directory is exist or not
/// </summary>
/// <param name=strDirPath>directory full path</param>
/// <returns>false£ºnot exist true£ºexist</returns>
/// <remarks>
/// none
/// </remarks>
///***********************************************************************
Directory::BOOL Directory::Exists(String strDirPath)
{
	BOOL bOK = false;

	// Remove the '\\' of the path
	String strFullPath = _T("");
	int iFindPos = strDirPath.FindLast(_T("\\"));
	if (iFindPos != -1)
	{
		strFullPath = strDirPath.SubString(0, iFindPos);
	}
	
	FileData data;
	DirectoryHandle hDirectory = ::FindFirstFile(strFullPath, &data);
	if (hDirectory != INVALID_HANDLE_VALUE && (data.dwFileAttributes & FileAttrEnum::DIRECTORY))
	{
		bOK = true;
	}

	::FindClose(hDirectory);

	return bOK;
}


///************************************************************************
/// <summary>
/// judge that wether the directory is empty or not
/// </summary>
/// <param name=strstrRootDirPathPath>directory full path</param>
/// <returns>false£ºnot empty true£ºempty</returns>
/// <remarks>
/// none
/// </remarks>
///***********************************************************************
Directory::BOOL Directory::IsEmpty(String strRootDirPathPath)
{
	BOOL bOK = false;

	// Build the full path of directory
	String strFullPath = _T("");
	int iFindPos = strRootDirPathPath.FindLast(_T("\\"));
	if (iFindPos == -1)
	{
		strFullPath = strRootDirPathPath + _T("\\*");
	}
	else
	{
		strFullPath = strRootDirPathPath + _T("*");
	}

	// Find the file with its attributes
	FileData data;
	DirectoryHandle hDirectory = ::FindFirstFile(strFullPath, &data);
	if (hDirectory == INVALID_HANDLE_VALUE)
	{
		return bOK;
	}

	while (1)
	{
		if (String(data.cFileName) != _T("..") || String(data.cFileName) != _T("."))
		{
			return bOK;
		}
		if (::FindNextFile(hDirectory, &data) == 0)
		{
			break;
		}
	}

	// The directory is empty
	bOK = true;

	// Close the finding
	::FindClose(hDirectory);

	return bOK;
}


///************************************************************************
/// <summary>
/// get the attribute of directory
/// </summary>
/// <param name=strDirPath>target directory full path</param>
/// <returns>the attribute</returns>
/// <remarks>
/// the directory attribute is the same as file's
/// </remarks>
///***********************************************************************
Directory::FileAttribute Directory::GetDirAttribute(String strDirPath)
{
	assert(strDirPath != _T(""));

	// Initialize the WinFileAttribute
	FileAttribute sFileAttr = { 0 };
	
	// Get the Attribute
	System::UInt64 dAttribute = ::GetFileAttributes(strDirPath);
	if (dAttribute == INVALID_FILE_ATTRIBUTES)
	{
		return sFileAttr;
	}

	// Set the WinFileAttribute Struct
	sFileAttr.dwArchive = dAttribute&(FileAttrEnum::ARCHIVE);
	sFileAttr.dwCompressed = dAttribute&(FileAttrEnum::COMPRESSED);
	sFileAttr.dwDevice = dAttribute&(FileAttrEnum::DEVICE);
	sFileAttr.dwDirectory = dAttribute&(FileAttrEnum::DIRECTORY);
	sFileAttr.dwEncrypted = dAttribute&(FileAttrEnum::ENCRYPTED);
	sFileAttr.dwHidden = dAttribute&(FileAttrEnum::HIDDEN);
	sFileAttr.dwIntegrityStream = dAttribute&(FileAttrEnum::INTEGRITYSTREAM);
	sFileAttr.dwNormal = dAttribute&(FileAttrEnum::NORMAL);
	sFileAttr.dwNoScrubData = dAttribute&(FileAttrEnum::NOSCRUBDATA);
	sFileAttr.dwNotContentIndexed = dAttribute&(FileAttrEnum::NOTCONTENTINDEXED);
	sFileAttr.dwOffline = dAttribute&(FileAttrEnum::OFFLINE);
	sFileAttr.dwReadOnly = dAttribute&(FileAttrEnum::READONLY);
	sFileAttr.dwReparsePoint = dAttribute&(FileAttrEnum::REPARSEPOINT);
	sFileAttr.dwSparseFile = dAttribute&(FileAttrEnum::SPARSEFILE);
	sFileAttr.dwSystem = dAttribute&(FileAttrEnum::SYSTEM);
	sFileAttr.dwTemporary = dAttribute&(FileAttrEnum::TEMPORARY);

	return sFileAttr;
}


///************************************************************************
/// <summary>
/// set the attribute of directory
/// </summary>
/// <param name=strDirPath>directory path</param>
/// <param name=attr>the attribute struct</param>
/// <returns></returns>
/// <remarks>
/// if there is several attribute ,you can use | to connect them
/// </remarks>
///***********************************************************************
Directory::Empty Directory::SetDirAttribute(String strDirPath, FileAttrEnum eFileAttribute)
{
	DWORD dAttribute = ::GetFileAttributes(strDirPath);

	::SetFileAttributes(strDirPath, dAttribute | eFileAttribute);
}


///************************************************************************
/// <summary>
/// Remove the attribute of the directory
/// </summary>
/// <param name=strDirPath>directory path</param>
/// <param name=attr>the attribute struct</param>
/// <returns></returns>
/// <remarks>
/// if there is several attribute ,you can use | to connect them
/// </remarks>
///***********************************************************************
Directory::Empty Directory::RemoveDirAttribute(String strDirPath, FileAttrEnum eFileAttribute)
{
	DWORD dAttribute = ::GetFileAttributes(strDirPath);

	::SetFileAttributes(strDirPath, dAttribute & (~eFileAttribute));
}


///************************************************************************
/// <summary>
/// get current process's run path
/// </summary>
/// <returns>the path of current process</returns>
/// <remarks>
/// none
/// </remarks>
///***********************************************************************
String Directory::GetCurDirectory()
{
	const int MAX_PATH_LEN = 256;

	TCHAR DirArray[MAX_PATH_LEN] = { 0 };

	int iRes = ::GetCurrentDirectory(MAX_PATH_LEN, DirArray);
	if (iRes == TRUE)
	{
		return String(DirArray);
	}

	return _T("");
}


///************************************************************************
/// <summary>
/// judge that wether the directory has the specail file in
/// </summary>
/// <param name=strRootDirPath>directory path</param>
/// <param name=fileName>specail file name</param>
/// <returns></returns>
/// <remarks>
/// none
/// </remarks>
///***********************************************************************
Directory::BOOL Directory::Contains(String strRootDirPath, String strFileName)
{
	BOOL bOK = false;

	// Build the full path of directory
	String strFullPath = _T("");
	int iFindPos = strRootDirPath.FindLast(_T("\\"));
	if (iFindPos == -1)
	{
		strFullPath = strRootDirPath + _T("\\*");
	}
	else
	{
		strFullPath = strRootDirPath + _T("*");
	}

	// Find the file with its attributes
	FileData data;
	DirectoryHandle hDirectory = ::FindFirstFile(strFullPath, &data);
	if (hDirectory == INVALID_HANDLE_VALUE)
	{
		return bOK;
	}

	while (1)
	{
		if (!FindNextFile(hDirectory, &data))
		{
			break;
		}
		// Find the file
		if (!(data.dwFileAttributes & FileAttrEnum::DIRECTORY))
		{
			if (strFileName == data.cFileName)
			{
				bOK = true;

				break;
			}
		}
	}

	// Close the finding
	::FindClose(hDirectory);

	return bOK;
}


///************************************************************************
/// <summary>
/// get all subdirectories under the directory
/// </summary>
/// <param name=strRootDirPath>root directory path</param>
/// <returns>the array of subdirectory path</returns>
/// <remarks>
/// none
/// </remarks>
///***********************************************************************
Directory::BOOL Directory::GetAllSubDir(String strRootDir, DirectoryTable& vDirectoryTable)
{
	return LookUpSubDirectory(strRootDir, vDirectoryTable);
}


///************************************************************************
/// <summary>
/// get all files under the directory
/// </summary>
/// <param name=curDir>root directory path</param>
/// <returns>the array of files' path</returns>
/// <remarks>
/// none
/// </remarks>
///***********************************************************************
Directory::BOOL Directory::GetAllFiles(String strCurrentDir, FileTable& vFileTable)
{
	return LookUpSubFiles(strCurrentDir, vFileTable);
}


///************************************************************************
/// <summary>
/// Look up all the subdirectory 
/// </summary>
/// <param name=String strDirPath>Root directory</param>
/// <param name=DirectoryTable & vDirectoryTable>Directory table</param>
/// <returns></returns>
/// <remarks>
/// None
/// </remarks>
///***********************************************************************
Directory::BOOL Directory::LookUpSubDirectory(String strDirPath, DirectoryTable& vDirectoryTable)
{
	BOOL bFind = false;

	String strFullPath = _T("");

	int iFindPos = strDirPath.FindLast(_T("\\"));
	if (iFindPos == -1)
	{
		// Build the full path of directory
		strFullPath = strDirPath + _T("\\*");
	}
	else
	{
		// Build the full path of directory
		strFullPath = strDirPath + _T("*");
	}

	// Find the file with its attributes
	FileData data;
	DirectoryHandle hDirectory = ::FindFirstFile(strFullPath, &data);
	if (hDirectory == INVALID_HANDLE_VALUE)
	{
		return bFind;
	}

	while (1)
	{
		// Find the next file or directory
		if (!FindNextFile(hDirectory, &data))
		{
			break;
		}

		// Judge the found one is directory or not
		if (data.dwFileAttributes&FileAttrEnum::DIRECTORY)
		{
			if ((String(data.cFileName) != _T("..")) && (String(data.cFileName) != _T(".")))
			{
				// Record the directory
				vDirectoryTable.push_back(String(data.cFileName));

				// Wipe out the last character '*'
				String strRoot = strDirPath.SubString(0, strDirPath.GetLength() - 1);

				// Rebuild the directory path
				String strNextDir = strRoot + data.cFileName;

				// Loop again
				LookUpSubDirectory(strNextDir, vDirectoryTable);
			}
		}
	}

	// Close the finding
	::FindClose(hDirectory);

	bFind = true;

	return bFind;
}


///************************************************************************
/// <summary>
/// Look up all files under the directory
/// </summary>
/// <param name=String strCurrentDir>Directory</param>
/// <param name=FileTable & vFileTable>File table</param>
/// <returns></returns>
/// <remarks>
/// None
/// </remarks>
///***********************************************************************
Directory::BOOL Directory::LookUpSubFiles(String strCurrentDir, FileTable& vFileTable)
{
	BOOL bFind = false;

	String strFullPath = _T("");

	int iFindPos = strCurrentDir.FindLast(_T("\\"));
	if (iFindPos == -1)
	{
		// Build the full path of directory
		strFullPath = strCurrentDir + _T("\\*");
	}
	else
	{
		// Build the full path of directory
		strFullPath = strCurrentDir + _T("*");
	}

	// Find the file with its attributes
	FileData data;
	DirectoryHandle hDirectory = ::FindFirstFile(strFullPath, &data);
	if (hDirectory == INVALID_HANDLE_VALUE)
	{
		return bFind;
	}

	while (1)
	{
		// Find the next file or directory
		if (!FindNextFile(hDirectory, &data))
		{
			break;
		}
		// Judge the next one is directory or not
		if ((data.dwFileAttributes & FileAttrEnum::DIRECTORY))
		{
			if ((String(data.cFileName) != _T("..")) && (String(data.cFileName) != _T(".")))
			{
				// Wipe out the last character '*'
				String strRootDir = strCurrentDir.SubString(0, strCurrentDir.GetLength() - 1);

				// Rebuild the directory path
				String strNextDir = strRootDir + data.cFileName;

				// Loop again
				LookUpSubFiles(strNextDir, vFileTable);
			}
			else
			{
				// it is ".." directory that we discarding.
				continue;
			}
		}
		else
		{
			// If the next one found is file and record it 
			String strFileName = strCurrentDir + data.cFileName;

			vFileTable.push_back(strFileName);
		}
	}
	// Close the finding
	::FindClose(hDirectory);

	bFind = true;

	return bFind;
}