#include "Application\PreCompile.h"
#include "File.h"

using namespace System::IO;

///************************************************************************
/// <summary>
/// construct the File Stream
/// </summary>
/// <returns></returns>
/// <remarks>
/// none
/// </remarks>
///***********************************************************************
File::File() :m_FileHandle(NULL), m_FileName(_T("")), m_Disposed(false)
{
	Initialize();
}


///************************************************************************
/// <summary>
/// destruct the File Stream
/// </summary>
/// <returns></returns>
/// <remarks>
/// none
/// </remarks>
///***********************************************************************
File::~File()
{
	Destory();
}


///************************************************************************
/// <summary>
/// Initialize the File
/// </summary>
/// <returns></returns>
/// <remarks>
/// none
/// </remarks>
///***********************************************************************
File::Empty File::Initialize()
{

}


///************************************************************************
/// <summary>
/// Dispose the File
/// </summary>
/// <returns></returns>
/// <remarks>
/// none
/// </remarks>
///***********************************************************************
File::Empty File::Destory()
{
	if (!GetDisposed())
	{
		SetDisposed(true);

		// Close the File
		this->Close();
	}
}


///************************************************************************
/// <summary>
/// File is opened 
/// </summary>
/// <returns>true£ºOpened  false£ºNot opened</returns>
/// <remarks>
/// none
/// </remarks>
///***********************************************************************
File::BOOL File::IsOpen()
{
	if (this->GetFileHandle())
	{
		return true;
	}

	return false;
}


///************************************************************************
/// <summary>
/// create the windows file handle
/// </summary>
/// <param name=path>the name of target file</param>
/// <param name=mode>operation mode</param>
/// <param name=access>operation access</param>
/// <param name=attr>operation attribute</param>
/// <returns>FIALED£ºopen file failed SUCCESS£ºsuccessfully open</returns>
/// <remarks>
/// none
/// </remarks>
///***********************************************************************
File::BOOL File::_CreateFile(String strFilePath, FileMode OpenMode, FileAccess OperateAccess, FileAttrEnum AttributeEnum)
{
	BOOL bSuccess = false;

	assert(strFilePath != _T(""));

	if (strFilePath == _T(""))
	{
		return bSuccess;
	}

	// Set the file name
	this->SetFileName(strFilePath);

	// Create the file 
	this->SetFileHandle(::CreateFile(this->GetFileName(), OperateAccess, 0, NULL, OpenMode, AttributeEnum, NULL));
	if (this->GetFileHandle() == INVALID_HANDLE_VALUE)
	{
		this->Close();

		return bSuccess;
	}

	// Set the file pointer position
	if (OpenMode == FileMode::APPEND)
	{
		this->Seek(SeekOrigin::END, 0);
	}
	else
	{
		this->Seek(SeekOrigin::BEGIN, 0);
	}

	bSuccess = true;

	return bSuccess;
}


///************************************************************************
/// <summary>
/// judge that whether the file is exist or not
/// </summary>
/// <param name=fileName>file's full path</param>
/// <returns>true£ºexists false£ºnot exist</returns>
/// <remarks>
/// none
/// </remarks>
///***********************************************************************
File::BOOL File::Exists(String strFileName)
{
	BOOL bExisted = false;

	assert(strFileName != _T(""));

	if (strFileName == _T(""))
	{
		return bExisted;
	}

	// Get the valid file attribute
	FileAttribute Attributes = this->GetAttributes(strFileName);
	if (Attributes.IsEmpty())
	{
		return bExisted;
	}

	// If it is not directory then we get the this file existed 
	if (Attributes.dwDirectory == 0)
	{
		bExisted = true;

		return bExisted;
	}

	return bExisted;
}


///************************************************************************
/// <summary>
/// create a file with default mode and access
/// </summary>
/// <param name=path>full file path</param>
/// <returns>FAILED or SUCCESS</returns>
/// <remarks>
/// none
/// </remarks>
///***********************************************************************
File::BOOL File::Create(String strFileName)
{
	return _CreateFile(strFileName, FileMode::CREATE, FileAccess::READWRITE, FileAttrEnum::NORMAL);
}


///************************************************************************
/// <summary>
/// delete the special file
/// </summary>
/// <param name=path>file's full path</param>
/// <returns>0£ºdelete failed other£ºdelete ok</returns>
/// <remarks>
/// none
/// </remarks>
///***********************************************************************
File::BOOL File::Delete(String strFileName)
{
	BOOL bSuccess = false;

	if (::DeleteFile(strFileName) == FALSE)
	{
		return bSuccess;
	}

	bSuccess = true;

	return bSuccess;
}


///************************************************************************
/// <summary>
/// get the file's size
/// </summary>
/// <returns>the total size of file</returns>
/// <remarks>
/// none
/// </remarks>
///***********************************************************************
File::FileSize File::GetSize()
{
	FileSize dwFileSize = 0;

	assert(this->IsOpen() == true);

	if (!this->IsOpen())
	{
		return dwFileSize;
	}

	dwFileSize = ::GetFileSize(this->GetFileHandle(), NULL);

	return dwFileSize;
}


///************************************************************************
/// <summary>
/// Get the File Attribute(hidden,directory,normal ,system etc.)
/// </summary>
/// <param name=path>file's path</param>
/// <returns>windows file's attribute</returns>
/// <remarks>
/// this attribute is different in differnt os
/// </remarks>
///***********************************************************************
File::FileAttribute File::GetAttributes(String strFileName)
{
	FileAttribute Attribute = { 0 };

	assert(strFileName != _T(""));

	if (strFileName == _T(""))
	{
		return Attribute;
	}

	System::UInt64 dwAttribute = ::GetFileAttributes(strFileName);
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
	Attribute.dwIntegrityStream = dwAttribute&(FileAttrEnum::INTEGRITYSTREAM);
	Attribute.dwNormal = dwAttribute&(FileAttrEnum::NORMAL);
	Attribute.dwNoScrubData = dwAttribute&(FileAttrEnum::NOSCRUBDATA);
	Attribute.dwNotContentIndexed = dwAttribute&(FileAttrEnum::NOTCONTENTINDEXED);
	Attribute.dwOffline = dwAttribute&(FileAttrEnum::OFFLINE);
	Attribute.dwReadOnly = dwAttribute&(FileAttrEnum::READONLY);
	Attribute.dwReparsePoint = dwAttribute&(FileAttrEnum::REPARSEPOINT);
	Attribute.dwSparseFile = dwAttribute&(FileAttrEnum::SPARSEFILE);
	Attribute.dwSystem = dwAttribute&(FileAttrEnum::SYSTEM);
	Attribute.dwTemporary = dwAttribute&(FileAttrEnum::TEMPORARY);

	return Attribute;
}


///************************************************************************
/// <summary>
/// move the file pointer to special position
/// </summary>
/// <param name=origin>start position of moving</param>
/// <param name=offset>the distance of moving</param>
/// <returns>the position distance of pointer</returns>
/// <remarks>
/// none
/// </remarks>
///***********************************************************************
File::Offset File::Seek(SeekOrigin SeekType, Offset iOffset)
{
	Offset FileOffset = 0;

	assert(this->IsOpen() == true);
	assert(iOffset >= 0);

	if (!this->IsOpen() || iOffset < 0)
	{
		return FileOffset;
	}

	FileOffset = ::SetFilePointer(this->GetFileHandle(), iOffset, NULL, SeekType);

	return FileOffset;
}


///************************************************************************
/// <summary>
/// move the file to another path
/// </summary>
/// <param name=sourceFilePath>source file's path</param>
/// <param name=destFilePath>destinate file's path</param>
/// <returns>0£ºmove failed other£ºmove ok</returns>
/// <remarks>
/// this moving is limited to differnt file's path
/// </remarks>
///***********************************************************************
File::BOOL File::Move(String strSrcFilePath, String strDestFilePath)
{
	BOOL bSuccess = false;

	// Check their legal attribute
	assert(strSrcFilePath != _T(""));
	assert(strDestFilePath != _T(""));

	if (strSrcFilePath == _T("") || strDestFilePath == _T(""))
	{
		return bSuccess;
	}

	// Copy this file to the destination
	bSuccess = this->Copy(strSrcFilePath, strDestFilePath);
	if (!bSuccess)
	{
		return bSuccess;
	}

	// Delete the source file 
	bSuccess = this->Delete(strSrcFilePath);

	return bSuccess;
}


///************************************************************************
/// <summary>
/// rename the file
/// </summary>
/// <param name=sourceFileName>source file name</param>
/// <param name=destFileName>the name you want to change to be</param>
/// <returns>0£ºrename failed other£ºrename ok</returns>
/// <remarks>
/// the file name is file's full path and their path is the same,but name
/// </remarks>
///***********************************************************************
File::BOOL File::Rename(String strSrcFileName, String strDestFileName)
{
	BOOL bSuccess = false;

	assert(strSrcFileName != _T(""));
	assert(strDestFileName != _T(""));

	if (strSrcFileName == _T("") || strDestFileName == _T(""))
	{
		return bSuccess;
	}

	if (::MoveFile(strSrcFileName, strDestFileName) == FALSE)
	{
		return bSuccess;
	}

	bSuccess = true;

	return bSuccess;
}


///************************************************************************
/// <summary>
/// copy the file to another path
/// </summary>
/// <param name=sourceFilePath>source file path</param>
/// <param name=destFilePath>destinate file path</param>
/// <returns>0£ºcopy failed other£ºcopy ok</returns>
/// <remarks>
/// none
/// </remarks>
///***********************************************************************
File::BOOL File::Copy(String strSrcFilePath, String strDestFilePath)
{
	BOOL bSuccess = false;

	assert(strSrcFilePath != _T(""));
	assert(strDestFilePath != _T(""));

	if (strSrcFilePath == _T("") || strDestFilePath == _T(""))
	{
		return bSuccess;
	}

	if (::CopyFile(strSrcFilePath, strDestFilePath, true) == FALSE)
	{
		return bSuccess;
	}

	bSuccess = true;

	return bSuccess;
}


///************************************************************************
/// <summary>
/// make the buffer stream written to the file
/// </summary>
/// <returns>0£ºflush failed other£ºflush ok</returns>
/// <remarks>
/// the flush target file must be opened
/// </remarks>
///***********************************************************************
File::BOOL File::Flush()
{
	BOOL bSuccess = false;

	assert(this->IsOpen() == true);

	if (!this->IsOpen())
	{
		return bSuccess;
	}

	if (::FlushFileBuffers(this->GetFileHandle()) == FALSE)
	{
		return bSuccess;
	}

	bSuccess = true;

	return bSuccess;
}


///************************************************************************
/// <summary>
/// open the file with mode and access
/// </summary>
/// <param name=path>file's full path</param>
/// <param name=mode>open mode</param>
/// <param name=access>open access</param>
/// <returns>FAILED or SUCCESS</returns>
/// <remarks>
/// the mode and access value defined in WinType.h
/// </remarks>
///***********************************************************************
File::BOOL File::Open(String strFilePath, FileMode OpenMode, FileAccess OperateAccess)
{
	return (_CreateFile(strFilePath, OpenMode, OperateAccess, FileAttrEnum::NORMAL));
}


///************************************************************************
/// <summary>
/// read the data from file
/// </summary>
/// <param name=arr>buffer </param>
/// <param name=offset>buffer offset to have the data</param>
/// <param name=readSize>read total size</param>
/// <returns>real read size</returns>
/// <remarks>
/// none
/// </remarks>
///***********************************************************************
File::FileSize File::Read(SByteArray pReadArray, Offset iOffset, ArraySize iArraySize)
{
	FileSize dwReadBytes = 0;

	assert(pReadArray != NULL);
	assert(iOffset >= 0);
	assert(iArraySize > 0);
	assert(IsOpen() == true);

	// Check the legal input
	if (pReadArray == NULL || iOffset < 0 || iArraySize < 0)
	{
		return dwReadBytes;
	}

	// Check that wether the file is opened or not
	if (!this->IsOpen())
	{
		return dwReadBytes;
	}

	::ReadFile(this->GetFileHandle(), pReadArray, iArraySize, &dwReadBytes, NULL);

	return dwReadBytes;
}


///************************************************************************
/// <summary>
/// write the data to file 
/// </summary>
/// <param name=arr>buffer with data </param>
/// <param name=offset>the offset of begining writing</param>
/// <param name=writeSize>total write size</param>
/// <returns>real write size</returns>
/// <remarks>
/// none
/// </remarks>
///***********************************************************************
File::FileSize File::Write(const SByteArray pWriteArray, Offset iOffset, ArraySize iArraySize)
{
	FileSize dwWriteBytes = 0;

	assert(pWriteArray != NULL);
	assert(iOffset >= 0);
	assert(iArraySize > 0);
	assert(IsOpen() == true);

	// Check the legal input
	if (pWriteArray == NULL || iOffset < 0 || iArraySize < 0)
	{
		return dwWriteBytes;
	}

	// Check that wether the file is opened or not
	if (!this->IsOpen())
	{
		return dwWriteBytes;
	}

	::WriteFile(this->GetFileHandle(), pWriteArray, iArraySize, &dwWriteBytes, NULL);

	return dwWriteBytes;
}


///************************************************************************
/// <summary>
/// close the file opened now
/// </summary>
/// <returns></returns>
/// <remarks>
/// none
/// </remarks>
///***********************************************************************
File::Empty File::Close()
{
	if (this->GetFileHandle())
	{
		::CloseHandle(this->GetFileHandle());

		this->SetFileHandle(NULL);
	}
}