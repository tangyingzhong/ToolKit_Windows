///************************************************************************
/// <copyrigth>2018-2019 Corporation.All Rights Reserved</copyrigth>
/// <author>tangyingzhong</author>
/// <contact>tangyz114987@outlook.com</contact>
/// <version>v1.0.0</version>
/// <describe>
/// Support file operations on window
///</describe>
/// <date>2019/7/16</date>
///***********************************************************************
#ifndef FILE_H
#define FILE_H

#include "Tool/BaseType/String.h"

using namespace System::BasicType;

namespace System
{
	namespace IO
	{
		class File
		{
		public:
			typedef System::None None;
			typedef System::Boolean BOOL;
			typedef System::FILE_MODE_ENUM FileMode;
			typedef System::FILE_ACCESS_ENUM FileAccess;
			typedef System::SEEK_ORIGIN_ENUM SeekOrigin;
			typedef System::FILE_ATTRIBUTE_ENUM FileAttrEnum;
			typedef System::FileAttribute FileAttribute;
			typedef System::Character Character;
			typedef System::CharArray CharArray;
			typedef System::SByte SByte;
			typedef System::SByteArray SByteArray;
			typedef System::WByte WByte;
			typedef System::WByteArray WByteArray;
			typedef System::Object FileHandle;
			typedef System::UInt64 FileSize;
			typedef System::FixedUInt32 ArraySize;
			typedef System::Int32 Index;
			typedef Index Offset;

		public:
			// Construct the File
			File();

			// Destruct the File
			~File();

		private:
			// Copy the File
			File(const File& other) {	}

			// Asignment of File
			File& operator=(const File& other) {	}

		public:
			// Open the File with the define mode and access
			BOOL Open(String strFilePath, 
				FileMode OpenMode, 
				FileAccess OperateAccess = FileAccess::READWRITE);

			// Read the File to the array started with offset position
			ArraySize Read(char* pReadArray, Offset iOffset, ArraySize iArraySize);

			// Write to the File with the array started with offset position
			ArraySize Write(CONST char* pWriteArray, Offset iOffset, ArraySize iArraySize);

			// Close the File
			None Close();

			// Create a new File and cover one if it is exist in the directory
			BOOL Create(String strFileName);

			// Get the File Size 
			FileSize GetSize();

			// Set the position of the File Pointer 
			Offset Seek(SeekOrigin SeekType, Offset iOffset);

			// Flush the file and cause the buffer data written to the file
			BOOL Flush();

			// Judge that File is exist or not
			static BOOL IsExisted(String strFileName);

			// Delete the File
			static BOOL Delete(String strFileName);

			// Move the File in different volume
			static BOOL Move(String strSrcFilePath, String strDestFilePath);

			// Rename the File 
			static BOOL Rename(String strSrcFileName, String strDestFileName);

			// Copy the File and no access to cover exist one
			static BOOL Copy(String strSrcFilePath, String strDestFilePath);

			// Get the File Attribute(hidden,directory,normal ,system etc.)
			static FileAttribute GetAttributes(String strFileName);

		private:
			// File is opened 
			BOOL IsOpen();

			// Create the File
			BOOL _CreateFile(String strFilePath, 
				FileMode OpenMode,
				FileAccess OperateAccess, 
				FileAttrEnum AttributeEnum);

			// Prepare the envir
			static BOOL PrepareEnvironment(String strFilePath);

		private:
			// Initialize the File
			None Initialize();

			// Destory the File
			None Destory();

		private:
			// Get the Handle
			inline FileHandle GetFileHandle() const
			{
				return m_FileHandle;
			}

			// Set the Handle
			inline None SetFileHandle(FileHandle hFileHandle)
			{
				m_FileHandle = hFileHandle;
			}

			// Get the FileName
			inline String GetFileName() const
			{
				return m_FileName;
			}

			// Set the FileName
			inline None SetFileName(String strFileName)
			{
				m_FileName = strFileName;
			}

			// Get the Disposed
			inline BOOL GetDisposed() const
			{
				return m_Disposed;
			}

			// Set the Disposed
			inline None SetDisposed(BOOL bDisposed)
			{
				m_Disposed = bDisposed;
			}

		private:
			// The Handle of File
			FileHandle m_FileHandle;

			// File name
			String m_FileName;

			// Disposed status
			BOOL m_Disposed;
		};
	}
}

#endif // FILE_H