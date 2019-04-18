///************************************************************************
/// <copyrigth>2018-2019 Corporation.All Rights Reserved</copyrigth>
/// <author>tangyingzhong</author>
/// <contact>tangyz114987@outlook.com</contact>
/// <version>V1.0.0</version>
/// <describe>
/// Directory operations
///</describe>
/// <date>2019/3/6</date>
///***********************************************************************
#ifndef DIRECTORY_H
#define DIRECTORY_H

#include "Tool\BaseType\String.h"

using namespace System::BasicType;

namespace System
{
	namespace IO
	{
		///*********************************************************
		/// <class> Directory </class>
		/// <summary>
		/// Directory operations on window
		/// </summary>
		/// <version>V1.0.0 </version>
		/// <goup> C++ </group>
		/// <author>tangyingzhong</author>
		/// <contact>tangyz114987@outlook.com</contact>
		///**********************************************************/
		class Directory
		{
		public:
			typedef System::Boolean BOOL;
			typedef System::Empty Empty;
			typedef System::FileAttribute FileAttribute;
			typedef System::FileAttrEnum FileAttrEnum;
			typedef System::Object DirectoryHandle;
			typedef std::vector<String> DirectoryTable;
			typedef DirectoryTable FileTable;
			typedef WIN32_FIND_DATA FileData;

		public:
			// Construct the Directory
			Directory() {	}

			// Destrcut the directory
			~Directory() {	}

			// Allow the object copying
			Directory(const Directory& other) {	}

			// Allow the obejct assignment
			Directory& operator=(Directory& other) {	}

		public:
			// Create a new directory
			static BOOL Create(String strDirPath);

			// Delete the empty directory
			static BOOL Delete(String strDirPath);

			// Is the directory existed or not
			static BOOL Exists(String strDirPath);

			// Is directoy empty or not
			static BOOL IsEmpty(String strRootDirPath);

			// Get the directory attribute
			static FileAttribute GetDirAttribute(String strDirPath);

			// Set the Attributer of directory
			static Empty SetDirAttribute(String strDirPath, FileAttrEnum eFileAttribute);

			// Remove the attribute of the directory
			static Empty RemoveDirAttribute(String strDirPath, FileAttrEnum eFileAttribute);

			// Get current directory of current process
			static String GetCurDirectory();

			// Contains the specail file under the direcoty
			static BOOL Contains(String strRootDir, String strFileName);

			// Get directorys under this root directory
			static BOOL GetAllSubDir(String strRootDir, DirectoryTable& vDirectoryTable);

			// List all files under the directory
			static BOOL GetAllFiles(String strCurrentDir, FileTable& vFileTable);

		private:
			// Look up the sub directory
			static BOOL LookUpSubDirectory(String strDirPath, DirectoryTable& vDirectoryTable);

			// Look up the sub files
			static BOOL LookUpSubFiles(String strCurrentDir, FileTable& vFileTable);
		};
	}
}

#endif //!DIRECTORY_H_