#include <iostream>
#include "Tool/Directory/Directory.h"
#include "File.h"

using namespace System::IO;

// Construct the File Stream
File::File() :m_FileHandle(NULL), m_FileName(_T("")), m_Disposed(false)
{
	Initialize();
}

// Destruct the File Stream
File::~File()
{
	Destory();
}

// Initialize the File
File::None File::Initialize()
{

}

// Dispose the File
File::None File::Destory()
{
	if (!GetDisposed())
	{
		SetDisposed(true);

		Close();
	}
}

// File is opened 
File::BOOL File::IsOpen()
{
	if (GetFileHandle())
	{
		return true;
	}

	return false;
}

// Create the windows file handle
File::BOOL File::_CreateFile(String strFilePath, 
	FileMode OpenMode, 
	FileAccess OperateAccess, 
	FileAttrEnum AttributeEnum)
{
	if (strFilePath.IsEmpty())
	{
		return false;
	}

	// Set the file name
	SetFileName(strFilePath);

	// Create the file 
	SetFileHandle(::CreateFile(GetFileName().CStr(), OperateAccess, 0, NULL, OpenMode, AttributeEnum, NULL));
	if (GetFileHandle() == INVALID_HANDLE_VALUE)
	{
		if (GetLastError()==32)
		{
			std::cerr<< "File is used by another process, please close it at first" << std::endl;
		}

		return false;
	}

	// Set the file pointer position
	if (OpenMode == FileMode::APPEND)
	{
		Seek(SeekOrigin::END, 0);
	}
	else
	{
		Seek(SeekOrigin::BEGIN, 0);
	}

	return true;
}

// Judge that whether the file is exist or not
File::BOOL File::IsExisted(String strFileName)
{
	if (strFileName.IsEmpty())
	{
		return false;
	}

	// Get the valid file attribute
	FileAttribute Attributes = GetAttributes(strFileName);
	if (Attributes.IsEmpty())
	{
		return false;
	}

	// If it is not directory then we get the this file existed 
	if (Attributes.dwDirectory == 0)
	{
		return true;
	}

	return false;
}

// Create a file with default mode and access
File::BOOL File::Create(String strFileName)
{
	return _CreateFile(strFileName, 
		FileMode::CREATE, 
		FileAccess::READWRITE, 
		FileAttrEnum::NORMAL);
}

// Delete the special file
File::BOOL File::Delete(String strFileName)
{
	if (strFileName.IsEmpty())
	{
		return false;
	}

	if (::DeleteFile(strFileName.CStr()) == FALSE)
	{
		return false;
	}

	return true;
}

// Get the file's size
File::FileSize File::GetSize()
{
	if (!IsOpen())
	{
		return 0;
	}

	LARGE_INTEGER LargeFileSize = { 0 };

	if (!GetFileSizeEx(GetFileHandle(), &LargeFileSize))
	{
		return 0;
	}

	return LargeFileSize.QuadPart;
}

// Get the File Attribute(hidden,directory,normal ,system etc.)
File::FileAttribute File::GetAttributes(String strFileName)
{
	FileAttribute Attribute = { 0 };

	if (strFileName.IsEmpty())
	{
		return Attribute;
	}

	System::UInt64 dwAttribute = ::GetFileAttributes(strFileName.CStr());
	if (dwAttribute == INVALID_FILE_ATTRIBUTES)
	{
		return Attribute;
	}

	// Set the FileAttribute Struct
	Attribute.dwArchive = dwAttribute&(FileAttrEnum::ARCHIVE);
	Attribute.dwCompressed = dwAttribute&(FileAttrEnum::COMPRESSED);
	Attribute.dwDevice = dwAttribute&(FileAttrEnum::DEVICE);
	Attribute.dwDirectory = dwAttribute&(FileAttrEnum::DIRECTORY);
	Attribute.dwEncrypted = dwAttribute&(FileAttrEnum::ENCRYPTED);
	Attribute.dwHidden = dwAttribute&(FileAttrEnum::HIDDEN);
	Attribute.dwNormal = dwAttribute&(FileAttrEnum::NORMAL);
	Attribute.dwNotContentIndexed = dwAttribute&(FileAttrEnum::NOTCONTENTINDEXED);
	Attribute.dwOffline = dwAttribute&(FileAttrEnum::OFFLINE);
	Attribute.dwReadOnly = dwAttribute&(FileAttrEnum::READONLY);
	Attribute.dwReparsePoint = dwAttribute&(FileAttrEnum::REPARSEPOINT);
	Attribute.dwSparseFile = dwAttribute&(FileAttrEnum::SPARSEFILE);
	Attribute.dwSystem = dwAttribute&(FileAttrEnum::SYSTEM);
	Attribute.dwTemporary = dwAttribute&(FileAttrEnum::TEMPORARY);
	Attribute.dwVirtual = dwAttribute&(FileAttrEnum::VIRTUAL);

	return Attribute;
}

// Move the file pointer to special position
File::Offset File::Seek(SeekOrigin SeekType, Offset iOffset)
{
	Offset FileOffset = 0;

	if (!IsOpen() || iOffset < 0)
	{
		return FileOffset;
	}

	FileOffset = ::SetFilePointer(GetFileHandle(), iOffset, NULL, SeekType);

	return FileOffset;
}

// Prepare the envir
File::BOOL File::PrepareEnvironment(String strFilePath)
{
	if (strFilePath.IsEmpty())
	{
		return false;
	}

	Int32 iCount = strFilePath.Contains('\\');
	if (iCount < 1)
	{
		return false;
	}
	
	// Get the root directory
	Int32 iPos = strFilePath.FindLast(_T("\\"));
	if (iPos == -1)
	{
		return false;
	}

	String strRootDirectory = Directory::AddEnding(strFilePath.Left(iPos));

	// Check the directory's existed
	if (!Directory::IsExisted(strRootDirectory))
	{
		if (!Directory::Create(strRootDirectory, true))
		{
			return false;
		}
	}

	return true;
}

// Move the file to another path
File::BOOL File::Move(String strSrcFilePath, String strDestFilePath)
{
	// Check their legal attribute
	if (strSrcFilePath.IsEmpty() || strDestFilePath.IsEmpty())
	{
		return false;
	}

	// Prepare the dest environment
	if (!PrepareEnvironment(strDestFilePath))
	{
		return false;
	}

	// Copy this file to the destination
	if (!Copy(strSrcFilePath, strDestFilePath))
	{
		Int32 iCode = GetLastError();

		return false;
	}

	// Delete the source file 
	if (!Delete(strSrcFilePath))
	{
		return false;
	}

	return true;
}

// Rename the file
File::BOOL File::Rename(String strSrcFileName, String strDestFileName)
{
	if (strSrcFileName.IsEmpty() || strDestFileName.IsEmpty())
	{
		return false;
	}

	// Prepare the dest environment
	if (!PrepareEnvironment(strDestFileName))
	{
		return false;
	}

	if (::MoveFile(strSrcFileName.CStr(), strDestFileName.CStr()) == FALSE)
	{
		return false;
	}

	return true;
}

// Copy the file to another path
File::BOOL File::Copy(String strSrcFilePath, String strDestFilePath)
{
	if (strSrcFilePath.IsEmpty() || strDestFilePath.IsEmpty())
	{
		return false;
	}

	// Prepare the dest environment
	if (!PrepareEnvironment(strDestFilePath))
	{
		return false;
	}

	if (::CopyFile(strSrcFilePath.CStr(), strDestFilePath.CStr(), true) == FALSE)
	{
		Int32 iRetCode = ::GetLastError();

		return false;
	}

	return true;
}

// Make the buffer stream written to the file
File::BOOL File::Flush()
{
	if (!IsOpen())
	{
		return false;
	}

	if (::FlushFileBuffers(GetFileHandle()) == FALSE)
	{
		return false;
	}

	return true;
}

// Open the file with mode and access
File::BOOL File::Open(String strFilePath, FileMode OpenMode, FileAccess OperateAccess)
{
	return (_CreateFile(strFilePath, 
		OpenMode,
		OperateAccess, 
		FileAttrEnum::NORMAL));
}

// Read the data from file
File::ArraySize File::Read(char* pReadArray, Offset iOffset, ArraySize iArraySize)
{
	// Check the legal input
	if (pReadArray == NULL || iOffset < 0 || iArraySize < 0)
	{
		return 0;
	}

	// Check that wether the file is opened or not
	if (!IsOpen())
	{
		return 0;
	}

	ArraySize dwReadBytes = 0;

	if (::ReadFile(GetFileHandle(), pReadArray, iArraySize, &dwReadBytes, NULL) == FALSE)
	{
		return 0;
	}

	return dwReadBytes;
}

// Write the data to file 
File::ArraySize File::Write(CONST char* pWriteArray, Offset iOffset, ArraySize iArraySize)
{
	// Check the legal input
	if (pWriteArray == NULL || iOffset < 0 || iArraySize < 0)
	{
		return 0;
	}

	// Check that wether the file is opened or not
	if (!IsOpen())
	{
		return 0;
	}

	ArraySize dwWriteBytes = 0;

	if (::WriteFile(GetFileHandle(), pWriteArray, iArraySize, &dwWriteBytes, NULL) == FALSE)
	{
		return 0;
	}

	return dwWriteBytes;
}

// Close the file opened now
File::None File::Close()
{
	if (GetFileHandle())
	{
		::CloseHandle(GetFileHandle());

		SetFileHandle(NULL);
	}
}