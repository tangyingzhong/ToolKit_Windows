///************************************************************************
/// <copyrigth>2018-2019 Corporation.All Rights Reserved</copyrigth>
/// <author>tangyingzhong</author>
/// <contact>tangyz114987@outlook.com</contact>
/// <version>v1.0.0</version>
/// <describe>
/// Directory operations
///</describe>
/// <date>2019/7/16</date>
///***********************************************************************
#ifndef DIRECTORY_H
#define DIRECTORY_H

#include "Tool/Common/SystemType.h"
#include "Tool/BaseType/String.h"

using namespace System::BasicType;

namespace System
{
	namespace IO
	{
		class Directory
		{
		public:
			typedef System::Boolean BOOL;
			typedef System::None None;
			typedef System::FileAttribute FileAttribute;
			typedef System::FILE_ATTRIBUTE_ENUM FileAttrEnum;
			typedef System::Object DirectoryHandle;
			typedef std::vector<String> DirectoryTable;
			typedef DirectoryTable FileTable;
			typedef WIN32_FIND_DATA FileData;

		public:
			// Construct the Directory
			Directory(){	}

			// Destrcut the directory
			~Directory() {	}

			// Allow the object copying
			Directory(const Directory& other) {	}

			// Allow the obejct assignment
			Directory& operator=(Directory& other) {	}

		public:
			// Create new directory recursively
			static BOOL Create(String strDirPath, BOOL bRecursive);

			// Copy the directory recursively
			static BOOL Copy(String strSrcDirPath, String strDestDirPath,BOOL bCover);

			// Delete the directory recursively
			static BOOL Delete(String strDirPath, BOOL bRecursive);

			// Trim path ending without "\\"
			static String TrimEnding(String strPath);

			// Add path ending with "\\"
			static String AddEnding(String strPath);

			// Is the directory existed or not
			static BOOL IsExisted(String strDirPath);

			// Is directoy None or not
			static BOOL IsEmpty(String strRootDirPath);

			// Is directory
			static BOOL IsDirectory(String strPath);

			// Is the drive letter valid
			static BOOL IsDriveLetterValid(String strDriveLetter);

			// Get the directory attribute
			static FileAttribute GetDirAttribute(String strDirPath);

			// Set the Attributer of directory
			static None SetDirAttribute(String strDirPath, FileAttrEnum eFileAttribute);

			// Remove the attribute of the directory
			static None RemoveDirAttribute(String strDirPath, FileAttrEnum eFileAttribute);

			// Get current directory of main project
			static String GetCurDirectory();

			// Get exe file path
			static String GetExcutableDirectory();

			// Contains the specail file under the direcoty
			static BOOL Contains(String strRootDir, String strFileName);

			// Get directorys under this root directory
			static BOOL GetAllSubDir(String strRootDir, DirectoryTable& vDirectoryTable);

			// List all files under the directory
			static BOOL GetAllFiles(String strCurrentDir, FileTable& vFileTable);

		private:
			// Create the whole directory on the dest directory
			static BOOL CreateSrcDirOnDest(String strSrcDirPath, String strNewDestDirPath);

			// Copy source directory files to dest one
			static BOOL CopySrcFilesToDest(String strSrcDirPath, String strNewDestDirPath);

			// Copy source directory files to dest one when no cover
			static BOOL CopySrcFilesToDest_NotCover(String strSrcDirPath, String strNewDestDirPath);

			// Create a new directory
			static BOOL Create(String strDirPath);

			// Delete the None directory
			static BOOL Delete(String strDirPath);

			// Build the new root directory
			static String BuildNewRoot(String strSrcPath, String strDestPath, String strCurPath);

			// Build new directory or file path
			static String Build(String strSrcPath, String strDestPath);

			// Is dest diretory name equal the src one
			static BOOL IsEqual(String strSrcDirPath, String strDestDirPath);

			// Is valid drive root directory
			static BOOL IsValidRootDriveDirectory(String strDirPath);

			// Extract the directory
			static String Extract(String strDirPath);

			// Look up the sub directory
			static BOOL LookUpSubDirectory(String strDirPath, DirectoryTable& vDirectoryTable);

			// Look up the sub files
			static BOOL LookUpSubFiles(String strCurrentDir, FileTable& vFileTable);
		};
	}
}

#endif // DIRECTORY_H