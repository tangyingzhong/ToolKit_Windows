///************************************************************************
/// <copyrigth>2018-2019 Corporation.All Rights Reserved</copyrigth>
/// <author>tangyingzhong</author>
/// <contact>tangyz114987@outlook.com</contact>
/// <version>V1.0.0</version>
/// <describe>
/// Support file operations on window
///</describe>
/// <date>2019/3/6</date>
///***********************************************************************
#ifndef FILE_H
#define FILE_H

#include "Tool\BaseType\String.h"

using namespace System::BasicType;

namespace System
{
	namespace IO
	{
		///*********************************************************
		/// <class>File</class>
		/// <summary>
		/// It support the file operations on window
		/// </summary>
		/// <version>V1.0.0 </version>
		/// <goup> C++</group>
		/// <author>tangyingzhong</author>
		/// <contact>tangyingzhong@szangell.com</contact>
		///*********************************************************
		class File
		{
		public:
			typedef System::Empty Empty;
			typedef System::Boolean BOOL;
			typedef System::FileMode FileMode;
			typedef System::FileAccess FileAccess;
			typedef System::SeekOrigin SeekOrigin;
			typedef System::FileAttrEnum FileAttrEnum;
			typedef System::FileAttribute FileAttribute;
			typedef System::ByteArray ByteArray;
			typedef System::SByteArray SByteArray;
			typedef System::Object FileHandle;
			typedef System::UInt64 FileSize;
			typedef System::Int32 Index;
			typedef Index Offset;
			typedef FileSize ArraySize;

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
			virtual BOOL Open(String strFilePath, FileMode OpenMode, FileAccess OperateAccess = FileAccess::READWRITE);

			// Read the File to the array started with offset position
			virtual FileSize Read(SByteArray pReadArray, Offset iOffset, ArraySize iArraySize);

			// Write to the File with the array started with offset position
			virtual FileSize Write(const SByteArray pWriteArray, Offset iOffset, ArraySize iArraySize);

			// Close the File
			virtual Empty Close();

			// Create a new File and cover one if it is exist in the directory
			virtual BOOL Create(String strFileName);

			// Judge that File is exist or not
			virtual BOOL Exists(String strFileName);

			// Delete the File
			virtual BOOL Delete(String strFileName);

			// Get the File Size 
			virtual FileSize GetSize();

			// Move the File in different volume
			virtual BOOL Move(String strSrcFilePath, String strDestFilePath);

			// Rename the File 
			virtual BOOL Rename(String strSrcFileName, String strDestFileName);

			// Copy the File and no access to cover exist one
			virtual BOOL Copy(String strSrcFilePath, String strDestFilePath);

			// Get the File Attribute(hidden,directory,normal ,system etc.)
			virtual FileAttribute GetAttributes(String strFileName);

			// Set the position of the File Pointer 
			virtual Offset Seek(SeekOrigin SeekType, Offset iOffset);

			// Flush the file and cause the buffer data written to the file
			virtual BOOL Flush();

		private:
			// File is opened 
			BOOL IsOpen();

			// Create the File
			BOOL _CreateFile(String strFilePath, FileMode OpenMode, FileAccess OperateAccess, FileAttrEnum AttributeEnum);

		private:
			// Initialize the File
			Empty Initialize();

			// Destory the File
			Empty Destory();

		private:
			// Get the Handle
			inline FileHandle GetFileHandle() const
			{
				return m_FileHandle;
			}

			// Set the Handle
			inline Empty SetFileHandle(FileHandle hFileHandle)
			{
				this->m_FileHandle = hFileHandle;
			}

			// Get the FileName
			inline String GetFileName() const
			{
				return m_FileName;
			}

			// Set the FileName
			inline Empty SetFileName(String strFileName)
			{
				this->m_FileName = strFileName;
			}

			// Get the Disposed
			inline BOOL GetDisposed() const
			{
				return m_Disposed;
			}

			// Set the Disposed
			inline Empty SetDisposed(BOOL bDisposed)
			{
				this->m_Disposed = bDisposed;
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

#endif // !FILE_H_