#include "Tool/File/File.h"
#include "Directory.h"
#include <WinBase.h>

using namespace System::IO;

// Create a directory( It just can create a directory without subdirectory)
Directory::BOOL Directory::Create(String strDirPath)
{
	if (strDirPath.IsEmpty())
	{
		return false;
	}

	if (::CreateDirectory(TrimEnding(strDirPath).CStr(), NULL) == TRUE)
	{
		return true;
	}

	return false;
}

// Create new directory recursively
Directory::BOOL Directory::Create(String strDirPath, BOOL bRecursive)
{
	if (strDirPath.IsEmpty() || (!strDirPath.IsContain(_T("\\")) && !strDirPath.IsContain(_T(":"))))
	{
		return false;
	}

	// Not recursive mode
	if (!bRecursive)
	{
		return Create(strDirPath);
	}

	// It is the recuresive ending
	if (IsExisted(strDirPath))
	{
		return true;
	}

	// Extract the path
	String strDir = Extract(strDirPath);

	// Create the path recursively
	if (!Create(strDir,bRecursive))
	{
		return false;
	}

	return Create(strDirPath);
}

// Extract the directory
String Directory::Extract(String strDirPath)
{
	if (strDirPath.IsEmpty())
	{
		return _T("");
	}

	// Standard the directory
	String strStandardPath = TrimEnding(strDirPath);

	Int32 iPos = strStandardPath.FindLast(_T("\\"));
	if (iPos != -1)
	{
		return strStandardPath.Left(iPos);
	}

	return _T("");
}

// Trim path ending without "\\"
String Directory::TrimEnding(String strPath)
{
	String strStandardPath = _T("");

	if (strPath.IsEmpty())
	{
		return strStandardPath;
	}

	Int32 iPos = strPath.FindLast(_T("\\"));
	if ((iPos + 1) == strPath.GetLength())
	{
		strStandardPath = strPath.Left(iPos);
	}
	else
	{
		strStandardPath = strPath;
	}

	return strStandardPath;
}

// Add path ending with "\\"
String Directory::AddEnding(String strPath)
{
	String strStandardPath = _T("");

	if (strPath.IsEmpty())
	{
		return strStandardPath;
	}

	Int32 iPos = strPath.FindLast(_T("\\"));
	if ((iPos + 1) == strPath.GetLength())
	{
		strStandardPath = strPath;
	}
	else
	{
		strStandardPath = strPath+_T("\\");
	}

	return strStandardPath;
}

// Is dest diretory name equal the src one
Directory::BOOL Directory::IsEqual(String strSrcDirPath, String strDestDirPath)
{
	if (strSrcDirPath.IsEmpty() || (!strSrcDirPath.IsContain(_T("\\")) && !strSrcDirPath.IsContain(_T(":"))))
	{
		return false;
	}

	if (strDestDirPath.IsEmpty() || (!strDestDirPath.IsContain(_T("\\")) && !strDestDirPath.IsContain(_T(":"))))
	{
		return false;
	}

	// Get the src directory name
	Int32 iPos = strSrcDirPath.FindLast(_T("\\"));

	String strSrcDirName = strSrcDirPath.Right(strSrcDirPath.GetLength()-iPos-1);

	// Get the dest directory name D:\\34.json
	Int32 iDestPos = strDestDirPath.FindLast(_T("\\"));

	String strDestDirName = strDestDirPath.Right(strDestDirPath.GetLength() - iDestPos-1);

	return strSrcDirName == strDestDirName;
}

// Build new directory or file path
String Directory::Build(String strSrcPath, String strDestPath)
{
	if (strSrcPath.IsEmpty() || (!strSrcPath.IsContain(_T("\\")) && !strSrcPath.IsContain(_T(":"))))
	{
		return _T("");
	}

	if (strDestPath.IsEmpty() || (!strDestPath.IsContain(_T("\\")) && !strDestPath.IsContain(_T(":"))))
	{
		return _T("");
	}

	// Get dest directory name
	Int32 iDstPos = strDestPath.FindLast(_T("\\"));

	String strDstShortName = strDestPath.Right(strDestPath.GetLength() - iDstPos - 1);

	// Get the src short name
	Int32 iSrcPos = strSrcPath.Find(strDstShortName,0);

	String strSrcShortName = strSrcPath.Right(strSrcPath.GetLength() - iSrcPos -1- strDstShortName.GetLength());
	
	String strFinalPath = Directory::AddEnding(strDestPath) + strSrcShortName;

	return strFinalPath;
}

// Create the whole directory on the dest directory
Directory::BOOL Directory::CreateSrcDirOnDest(String strSrcDirPath, String strNewDestDirPath)
{
	if (strSrcDirPath.IsEmpty() || (!strSrcDirPath.IsContain(_T("\\")) && !strSrcDirPath.IsContain(_T(":"))))
	{
		return false;
	}

	if (strNewDestDirPath.IsEmpty() || (!strNewDestDirPath.IsContain(_T("\\")) && !strNewDestDirPath.IsContain(_T(":"))))
	{
		return false;
	}

	// Get all sub directories
	DirectoryTable DirTable;
	Directory::GetAllSubDir(strSrcDirPath, DirTable);

	// Create all sub directories
	for (Int32 iIndex = 0; iIndex < (Int32)DirTable.size(); ++iIndex)
	{
		// Build new dest sub dir path
		String strNewSubDirPath = Build(DirTable[iIndex], strNewDestDirPath);

		if (!Directory::Create(strNewSubDirPath, true))
		{
			return false;
		}
	}

	if (DirTable.empty())
	{
		// Create src directory at dest path
		if (!Directory::Create(strNewDestDirPath, true))
		{
			return false;
		}
	}

	return true;
}

// Copy source directory files to dest one
Directory::BOOL Directory::CopySrcFilesToDest(String strSrcDirPath, String strNewDestDirPath)
{
	if (strSrcDirPath.IsEmpty() || (!strSrcDirPath.IsContain(_T("\\")) && !strSrcDirPath.IsContain(_T(":"))))
	{
		return false;
	}

	if (strNewDestDirPath.IsEmpty() || (!strNewDestDirPath.IsContain(_T("\\")) && !strNewDestDirPath.IsContain(_T(":"))))
	{
		return false;
	}

	// Get all src files
	FileTable FileList;
	GetAllFiles(strSrcDirPath, FileList);

	// Copy src files to the dest directory
	for (Int32 iIndex = 0; iIndex < (Int32)FileList.size(); ++iIndex)
	{
		// Build new dest file path
		String strNewFilePath = Build(FileList[iIndex], strNewDestDirPath);

		if (!File::Copy(FileList[iIndex], strNewFilePath))
		{
			return false;
		}
	}

	return true;
}

// Copy source directory files to dest one when no cover
Directory::BOOL Directory::CopySrcFilesToDest_NotCover(String strSrcDirPath, String strNewDestDirPath)
{
	if (strSrcDirPath.IsEmpty() || (!strSrcDirPath.IsContain(_T("\\")) && !strSrcDirPath.IsContain(_T(":"))))
	{
		return false;
	}

	if (strNewDestDirPath.IsEmpty() || (!strNewDestDirPath.IsContain(_T("\\")) && !strNewDestDirPath.IsContain(_T(":"))))
	{
		return false;
	}

	// Get all src files
	FileTable FileList;
	GetAllFiles(strSrcDirPath, FileList);

	// Get all src files
	FileTable DstFileList;
	GetAllFiles(strNewDestDirPath, DstFileList);

	// Get the new file table
	FileTable FinalFileTable;

	for (Int32 iIndex = 0; iIndex < (Int32)FileList.size(); ++iIndex)
	{
		String strNewFilePath = Build(FileList[iIndex], strNewDestDirPath);

		Int32 iDstIndex = 0;
		for (iDstIndex = 0; iDstIndex < (Int32)DstFileList.size(); ++iDstIndex)
		{
			if (strNewFilePath == DstFileList[iDstIndex])
			{
				break;
			}
		}

		if (iDstIndex == (Int32)DstFileList.size())
		{
			FinalFileTable.push_back(FileList[iIndex]);
		}
	}

	// Copy src files to the dest directory 
	for (Int32 iIndex = 0; iIndex < (Int32)FinalFileTable.size(); ++iIndex)
	{
		// Build new dest file path
		String strNewFilePath = Build(FinalFileTable[iIndex], strNewDestDirPath);

		if (!File::Copy(FinalFileTable[iIndex], strNewFilePath))
		{
			return false;
		}
	}

	return true;
}

// Build the new root directory
String Directory::BuildNewRoot(String strSrcPath, String strDestPath, String strCurPath)
{
	if (strSrcPath.IsEmpty() || (!strSrcPath.IsContain(_T("\\")) && !strSrcPath.IsContain(_T(":"))))
	{
		return _T("");
	}

	if (strDestPath.IsEmpty() || (!strDestPath.IsContain(_T("\\")) && !strDestPath.IsContain(_T(":"))))
	{
		return _T("");
	}

	if (strCurPath.IsEmpty() || (!strCurPath.IsContain(_T("\\")) && !strCurPath.IsContain(_T(":"))))
	{
		return _T("");
	}

	// Get the src short name
	Int32 iSrcPos = strSrcPath.FindLast(_T("\\"));

	String strSrcShortName = strSrcPath.Right(strSrcPath.GetLength() - iSrcPos - 1);

	String strFinalPath = Directory::AddEnding(strDestPath) + strSrcShortName;

	return strFinalPath;
}

// Copy the directory(No sub directory)
Directory::BOOL Directory::Copy(String strSrcDirPath, String strDestDirPath, BOOL bCover)
{
	if (strSrcDirPath.IsEmpty() || (!strSrcDirPath.IsContain(_T("\\")) && !strSrcDirPath.IsContain(_T(":"))))
	{
		return false;
	}

	if (strDestDirPath.IsEmpty() || (!strDestDirPath.IsContain(_T("\\")) && !strDestDirPath.IsContain(_T(":"))))
	{
		return false;
	}

	// Build new dest directory
	String strNewDestDirPath = BuildNewRoot(strSrcDirPath, strDestDirPath, strSrcDirPath);

	// Is dest directry existed 
	if (!IsExisted(strNewDestDirPath))
	{
		// Create the whole directory on the dest directory
		if (!CreateSrcDirOnDest(strSrcDirPath, strNewDestDirPath))
		{
			return false;
		}

		// Copy source directory files to dest one
		if (!CopySrcFilesToDest(strSrcDirPath, strNewDestDirPath))
		{
			return false;
		}

		return true;
	}

	if (bCover)
	{
		// Delete the directory
		if (!Directory::Delete(strNewDestDirPath, true))
		{
			return false;
		}

		// Create the whole directory on the dest directory
		if (!CreateSrcDirOnDest(strSrcDirPath, strNewDestDirPath))
		{
			return false;
		}

		// Copy source directory files to dest one
		if (!CopySrcFilesToDest(strSrcDirPath, strNewDestDirPath))
		{
			return false;
		}

		return true;
	}

	// Create the whole directory on the dest directory
	if (!CreateSrcDirOnDest(strSrcDirPath, strNewDestDirPath))
	{
		return false;
	}

	// Copy source directory files to dest one
	if (!CopySrcFilesToDest_NotCover(strSrcDirPath, strNewDestDirPath))
	{
		return false;
	}

	return true;
}

// Delete an None directory(The dir has no sub-directory)
Directory::BOOL Directory::Delete(String strDirPath)
{
	if (strDirPath.IsEmpty())
	{
		return false;
	}

	if (::RemoveDirectory(TrimEnding(strDirPath).CStr()) == TRUE)
	{
		return true;
	}

	return false;
}

// Delete the directory recursively
Directory::BOOL Directory::Delete(String strDirPath, BOOL bRecursive)
{
	if (strDirPath.IsEmpty() || (!strDirPath.IsContain(_T("\\")) && !strDirPath.IsContain(_T(":"))))
	{
		return false;
	}

	if (!bRecursive)
	{
		return Delete(strDirPath);
	}

	// Trim the ending 
	String strDir = TrimEnding(strDirPath);
	
	// Is the directory
	if (!IsDirectory(strDir))
	{
		return false;
	}

	// Search the directoy
	String strBackup = strDir;

	strDir = strDir + _T("\\*");

	FileData data;
	DirectoryHandle hDirectory = ::FindFirstFile(strDir.CStr(), &data);
	if (hDirectory == INVALID_HANDLE_VALUE)
	{
		return false;
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
			if (String(data.cFileName) == _T("..") || String(data.cFileName) == _T("."))
			{
				continue;
			}

			// Wipe out the last character '*'
			String strRootDir = strDir.SubString(0, strDir.GetLength() - 1);

			// Rebuild the directory path
			String strNextDir = strRootDir + data.cFileName;

			// Delete the directory recursively
			if (!Delete(strNextDir, bRecursive))
			{
				return false;
			}
		}
		else
		{
			// If the next one found is file and record it 
			String strFileName = AddEnding(strBackup) + data.cFileName;

			// Delete the file
			if (!File().Delete(strFileName))
			{
				return false;
			}			
		}
	}

	// Close the finding
	::FindClose(hDirectory);

	// Delete the directory
	return Delete(strBackup);
}

// Is the drive letter valid
Directory::BOOL Directory::IsDriveLetterValid(String strDriveLetter)
{
	if (strDriveLetter.IsEmpty())
	{
		return false;
	}

	if (!strDriveLetter.IsContain(_T(":")))
	{
		strDriveLetter = strDriveLetter + _T(":");
	}

	String strFilePath = strDriveLetter + _T("\\");

	return IsValidRootDriveDirectory(strFilePath);
}

// Is valid drive root directory
Directory::BOOL Directory::IsValidRootDriveDirectory(String strDirPath)
{
	if (strDirPath.IsEmpty())
	{
		return false;
	}

	if (!strDirPath.IsContain(_T(":")))
	{
		return false;
	}

	if (GetDriveType(strDirPath.CStr()) != DRIVE_FIXED)
	{
		return false;
	}

	return true;
}

// Judge that whether the directory is exist or not
Directory::BOOL Directory::IsExisted(String strDirPath)
{
	if (strDirPath.IsEmpty())
	{
		return false;
	}

	FileData data;

	String strDirectory = TrimEnding(strDirPath);

	if (strDirectory.GetLength()==2)
	{
		// Is valid dirve root directory
		if (!IsValidRootDriveDirectory(strDirectory))
		{
			return false;
		}

		return true;
	}

	DirectoryHandle hDirectory = ::FindFirstFile(strDirectory.CStr(), &data);

	if (hDirectory != INVALID_HANDLE_VALUE && (data.dwFileAttributes & FileAttrEnum::DIRECTORY))
	{
		::FindClose(hDirectory);

		return true;
	}

	::FindClose(hDirectory);

	return false;
}

// judge that wether the directory is None or not
Directory::BOOL Directory::IsEmpty(String strRootDirPathPath)
{
	if (strRootDirPathPath.IsEmpty())
	{
		return true;
	}

	// Build the full path of directory
	String strFullPath = _T("");

	int iFindPos = strRootDirPathPath.FindLast(_T("\\"));
	if (iFindPos == -1)
	{
		return true;
	}
	else if (iFindPos == strRootDirPathPath.GetLength() - 1)
	{
		strFullPath = strRootDirPathPath + _T("*");
	}
	else
	{
		strFullPath = strRootDirPathPath + _T("\\*");
	}

	// Find the file with its attributes
	FileData data;

	DirectoryHandle hDirectory = ::FindFirstFile(strFullPath.CStr(), &data);
	if (hDirectory == INVALID_HANDLE_VALUE)
	{
		return true;
	}

	Int32 bFind = 1;

	BOOL bNone = true;

	while (bFind)
	{
		if (String(data.cFileName) == _T("..") || String(data.cFileName) == _T("."))
		{
			bFind = ::FindNextFile(hDirectory, &data);
		}
		else
		{
			bNone = false;

			break;
		}
	}

	// Close the finding
	::FindClose(hDirectory);

	if (bNone)
	{
		return true;
	}

	return false;
}

// Is directory
Directory::BOOL Directory::IsDirectory(String strPath)
{
	if (strPath.IsEmpty() || (!strPath.IsContain(_T("\\")) && !strPath.IsContain(_T(":"))))
	{
		return false;
	}

	// Check wether it is directory 
	FileAttribute Attr = GetDirAttribute(strPath);
	if (Attr.dwDirectory ==0)
	{
		return false;
	}
	
	return true;
}

// Get the attribute of directory
Directory::FileAttribute Directory::GetDirAttribute(String strDirPath)
{
	if (strDirPath.IsEmpty())
	{
		return FileAttribute();
	}

	// Initialize the WinFileAttribute
	FileAttribute sFileAttr = { 0 };

	// Get the Attribute
	System::UInt64 dAttribute = ::GetFileAttributes(TrimEnding(strDirPath).CStr());
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
	sFileAttr.dwNormal = dAttribute&(FileAttrEnum::NORMAL);
	sFileAttr.dwNotContentIndexed = dAttribute&(FileAttrEnum::NOTCONTENTINDEXED);
	sFileAttr.dwOffline = dAttribute&(FileAttrEnum::OFFLINE);
	sFileAttr.dwReadOnly = dAttribute&(FileAttrEnum::READONLY);
	sFileAttr.dwReparsePoint = dAttribute&(FileAttrEnum::REPARSEPOINT);
	sFileAttr.dwSparseFile = dAttribute&(FileAttrEnum::SPARSEFILE);
	sFileAttr.dwSystem = dAttribute&(FileAttrEnum::SYSTEM);
	sFileAttr.dwTemporary = dAttribute&(FileAttrEnum::TEMPORARY);
	sFileAttr.dwVirtual = dAttribute&(FileAttrEnum::VIRTUAL);

	return sFileAttr;
}

// Set the attribute of directory
Directory::None Directory::SetDirAttribute(String strDirPath, FileAttrEnum eFileAttribute)
{
	String strDirectory = TrimEnding(strDirPath);

	DWORD dAttribute = ::GetFileAttributes(strDirectory.CStr());

	::SetFileAttributes(strDirectory.CStr(), dAttribute | eFileAttribute);
}

// Remove the attribute of the directory
Directory::None Directory::RemoveDirAttribute(String strDirPath, FileAttrEnum eFileAttribute)
{
	String strDirectory = TrimEnding(strDirPath);

	DWORD dAttribute = ::GetFileAttributes(strDirectory.CStr());

	::SetFileAttributes(strDirectory.CStr(), dAttribute & (~eFileAttribute));
}

// Get current directory of main project
String Directory::GetCurDirectory()
{
	const int MAX_PATH_LEN = 256;

	TCHAR DirArray[MAX_PATH_LEN] = { 0 };

	if (::GetCurrentDirectory(MAX_PATH_LEN, DirArray) != FALSE)
	{
		return String(DirArray);
	}

	return _T("");
}

// Get exe file path
String Directory::GetExcutableDirectory()
{
	const int MAX_PATH_LEN = 256;

	TCHAR DirArray[MAX_PATH_LEN] = { 0 };

	if (::GetModuleFileName(NULL, DirArray, MAX_PATH_LEN) != FALSE)
	{
		String strFullPath = DirArray;

		Int32 iPos = strFullPath.FindLast(_T("\\"));

		String strExeDir = strFullPath.Left(iPos);

		return strExeDir;
	}

	return _T("");
}

// Judge that wether the directory has the specail file in
Directory::BOOL Directory::Contains(String strRootDirPath, String strFileName)
{
	if (strRootDirPath.IsEmpty())
	{
		return false;
	}

	if (strFileName.IsEmpty())
	{
		return false;
	}

	// Get the file short name
	Int32 iPos = strFileName.FindLast(_T("\\"));

	String strShortFileName = strFileName.Right(strFileName.GetLength() - iPos - 1);

	// Build the full path of directory
	String strFullPath = _T("");

	int iFindPos = strRootDirPath.FindLast(_T("\\"));
	if (iFindPos == -1)
	{
		return false;
	}
	else if (iFindPos== strRootDirPath.GetLength()-1)
	{
		strFullPath = strRootDirPath + _T("*");
	}
	else
	{
		strFullPath = strRootDirPath + _T("\\*");
	}

	// Find the file with its attributes
	FileData data;

	DirectoryHandle hDirectory = ::FindFirstFile(strFullPath.CStr(), &data);
	if (hDirectory == INVALID_HANDLE_VALUE)
	{
		return false;
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
			if (strShortFileName == data.cFileName)
			{
				// Close the finding
				::FindClose(hDirectory);

				return true;
			}
		}
	}

	// Close the finding
	::FindClose(hDirectory);

	return false;
}

// Get all subdirectories under the directory
Directory::BOOL Directory::GetAllSubDir(String strRootDir, DirectoryTable& vDirectoryTable)
{
	return LookUpSubDirectory(strRootDir, vDirectoryTable);
}

// Get all files under the directory
Directory::BOOL Directory::GetAllFiles(String strCurrentDir, FileTable& vFileTable)
{
	return LookUpSubFiles(strCurrentDir, vFileTable);
}

// Look up all the subdirectory 
Directory::BOOL Directory::LookUpSubDirectory(String strDirPath, DirectoryTable& vDirectoryTable)
{
	if (strDirPath.IsEmpty())
	{
		return false;
	}

	int iFindPos = strDirPath.FindLast(_T("\\"));
	if (iFindPos == -1)
	{
		return false;
	}
	else if (iFindPos==strDirPath.GetLength()-1)
	{
		strDirPath = strDirPath + _T("*");
	}
	else
	{		
		strDirPath = strDirPath + _T("\\*");
	}

	// Find the file with its attributes
	FileData data;

	DirectoryHandle hDirectory = ::FindFirstFile(strDirPath.CStr(), &data);
	if (hDirectory == INVALID_HANDLE_VALUE)
	{
		return false;
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
			if (String(data.cFileName) == _T("..") || String(data.cFileName) == _T("."))
			{
				continue;
			}

			// Wipe out the last character '*'
			String strRoot = strDirPath.SubString(0, strDirPath.GetLength() - 1);

			// Rebuild the directory path
			String strNextDir = strRoot + data.cFileName;

			// Record the directory
			vDirectoryTable.push_back(strNextDir);

			// Loop again
			LookUpSubDirectory(strNextDir, vDirectoryTable);
		}
	}

	// Close the finding
	::FindClose(hDirectory);

	return true;
}

// Look up all files under the directory
Directory::BOOL Directory::LookUpSubFiles(String strCurrentDir, FileTable& vFileTable)
{
	if (strCurrentDir.IsEmpty())
	{
		return false;
	}

	String strBackup = strCurrentDir;

	int iFindPos = strCurrentDir.FindLast(_T("\\"));
	if (iFindPos == -1)
	{
		return false;
	}
	else if (iFindPos== strCurrentDir.GetLength()-1)
	{
		strCurrentDir = strCurrentDir + _T("*");
	}
	else
	{
		strCurrentDir = strCurrentDir + _T("\\*");
	}

	// Find the file with its attributes
	FileData data;

	DirectoryHandle hDirectory = ::FindFirstFile(strCurrentDir.CStr(), &data);
	if (hDirectory == INVALID_HANDLE_VALUE)
	{
		return false;
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
			if (String(data.cFileName) == _T("..") || String(data.cFileName) == _T("."))
			{
				continue;
			}

			// Wipe out the last character '*'
			String strRootDir = strCurrentDir.SubString(0, strCurrentDir.GetLength() - 1);

			// Rebuild the directory path
			String strNextDir = strRootDir + data.cFileName;

			// Loop again
			LookUpSubFiles(strNextDir, vFileTable);
		}
		else
		{
			// If the next one found is file and record it 
			String strFileName = AddEnding(strBackup) + data.cFileName;

			vFileTable.push_back(strFileName);
		}
	}
	// Close the finding
	::FindClose(hDirectory);

	return true;
}