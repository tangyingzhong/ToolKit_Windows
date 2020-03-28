///************************************************************************
/// <copyrigth>2018-2019 Corporation.All Rights Reserved</copyrigth>
/// <author>tangyingzhong</author>
/// <contact>tangyz114987@outlook.com</contact>
/// <version>v1.0.0</version>
/// <describe>
/// Basic type of the system on windows
///</describe>
/// <date>2019/7/16</date>
///***********************************************************************
#ifndef SYSTEMTYPE_H
#define SYSTEMTYPE_H

// Close the warning of c4312 which is a smaller size changed to be a bigger one
#pragma warning(disable:4312)

// Close the c4996 warning which is tip you that you should use a safe function not an old one
#pragma warning(disable:4996)

#ifdef UNICODE
#define _T(x) L ## x
#else
#define _T(x) x
#endif

// Exclude rarely-used stuff from Windows headers
#define WIN32_LEAN_AND_MEAN 
#include <windows.h>
#include <sstream>
#include <string>

namespace System
{
	// True or False
	typedef bool Boolean;			

	// Nothing
	typedef void None;

	// Universal pointer : any type pointer or NULL (4 bytes in memory)
	typedef None* Object;

	// One byte: 0-255
	typedef unsigned char Byte;		

	// Byte pointer : 4 bytes in memory	
	typedef unsigned char* ByteArray;

	// Signed byte with the range from -127-128
	typedef char SByte;					

	// Signed byte array which is 4 bytes in memory
	typedef SByte* SByteArray;			

	// Wide byte that can contain the unicode string
	typedef wchar_t WByte;				

	// Wide byte array which is 4 bytes in memory
	typedef WByte* WByteArray;															
#ifdef UNICODE
	// An character that accepts all character type including unicode
	typedef WByte Character;									

	// Characters' array
	typedef Character* CharArray;	

	// String of the STL
	typedef std::wstring StdString;		

	// Convert string to other type data or other type data transfers to be string
	typedef std::wstringstream StringStream;										
#else
	// An character that is ranged from -128 - 127
	typedef SByte Character;					

	// Characters' array
	typedef Character* CharArray;		

	// String of the STL
	typedef std::string StdString;			

	// Convert string to other type data or other type data transfers to be string
	typedef std::stringstream StringStream;											
#endif
	// Short integer : -2 ^ 16 / 2 - 2 ^ 16 / 2 - 1
	typedef short Int16;							

	// Short integer : 0 - 2 ^ 16 - 1
	typedef unsigned short UInt16;		

	// Integer : -2 ^ 32 / 2 - 2 ^ 32 / 2 - 1
	typedef int Int32;					

	// Integer : 0 - 2 ^ 32 - 1
	typedef unsigned int UInt32;					

	// Long integer :  -2 ^ 32 / 2 - 2 ^ 32 / 2 - 1
	typedef long FixedInt32;

	// Long integer :0 - 2 ^ 32 - 1
	typedef unsigned long FixedUInt32;

	// Long integer : -2 ^ 64 / 2 - 2 ^ 64 / 2 - 1
	typedef long long Int64;						

	// Long integer : 0 - 2 ^ 64 - 1
	typedef unsigned long long UInt64;	

	// Single real: 4 bytes in memory
	typedef float Single;				

	// Double real: 8 bytes in memory
	typedef double Real;	

	// Function that called back by a thread	
	typedef FixedUInt32(__stdcall *ThreadRountine)(Object obj);

	// The way to open the file
	enum FILE_MODE_ENUM
	{
		// File exist and open it or create it and write at the end
		APPEND = OPEN_ALWAYS,						

		// Create a file whatever it is existed or not."w" "w+"
		CREATE = CREATE_ALWAYS,				

		// File must be not exist and it can create file or error happends 
		CREATENEW = CREATE_NEW,					

		// File must be exist or error happends . "r"  "r+"
		OPEN = OPEN_EXISTING,					

		// File exist and open it or create it.
		OPENORCREATE = OPEN_ALWAYS,										

		// Make current file's length to be 0
		TRUNC = TRUNCATE_EXISTING,											
	};

	// The way to operate the file
	enum FILE_ACCESS_ENUM
	{
		// Read allowed only
		READ = GENERIC_READ,			

		// Write allowed only
		WRITE = GENERIC_WRITE,								

		// Read and Write allowed
		READWRITE = GENERIC_READ | GENERIC_WRITE						
	};

	// The way of allowing the file to be shared with others
	enum FILE_SHARE_ENUM
	{
		// Sharing reading the same file with other thread or process 
		SREAD = FILE_SHARE_READ,				

		// Sharing writing the same file with other thread or process 
		SWRITE = FILE_SHARE_WRITE,								

		// Sharing reading and writing the same file with other thread or process 
		SREADWRITE = FILE_SHARE_READ | FILE_SHARE_WRITE				
	};

	// Operate the file's data in which position
	enum SEEK_ORIGIN_ENUM
	{
		// Seek from the beginning 
		BEGIN = 0,			

		// Seek from the current position
		CURRENT = 1,		

		// Seek from the end position
		END = 2																				
	};

	// File's attributes enum
	enum FILE_ATTRIBUTE_ENUM
	{
		// This file is a backup or delete one
		ARCHIVE = FILE_ATTRIBUTE_ARCHIVE,			

		// This is Compressed file
		COMPRESSED = FILE_ATTRIBUTE_COMPRESSED,	

		// Reversed
		DEVICE = FILE_ATTRIBUTE_DEVICE,									

		// This is a directory
		DIRECTORY = FILE_ATTRIBUTE_DIRECTORY,			

		// Encrypted the File or Directory
		ENCRYPTED = FILE_ATTRIBUTE_ENCRYPTED,		

		// This file is not seen
		HIDDEN = FILE_ATTRIBUTE_HIDDEN,			

		// This is a standard file
		NORMAL = FILE_ATTRIBUTE_NORMAL,							

		// This is file cannot be indexed
		NOTCONTENTINDEXED = FILE_ATTRIBUTE_NOT_CONTENT_INDEXED,			 

		// This file is on offline,its' data can not be used at time
		OFFLINE = FILE_ATTRIBUTE_OFFLINE,		

		// This file is read only
		READONLY = FILE_ATTRIBUTE_READONLY,			

		// The file includes reparse point which produced by user
		REPARSEPOINT = FILE_ATTRIBUTE_REPARSE_POINT,					

		// This file is sparse file with large data
		SPARSEFILE = FILE_ATTRIBUTE_SPARSE_FILE,		

		// This is a system file which used by OS only
		SYSTEM = FILE_ATTRIBUTE_SYSTEM,											

		// This is a temporary file when used.
		TEMPORARY = FILE_ATTRIBUTE_TEMPORARY,

		// This is a system file
		VIRTUAL = FILE_ATTRIBUTE_VIRTUAL
	};

	// File's flag
	enum FILE_FLAG_ENUM
	{
		// This file is opened or created for a backup or restore operation
		BackupSemantics = FILE_FLAG_BACKUP_SEMANTICS,			

		// The file is to be deleted immediately after the file handle closed
		DeleteOnClose = FILE_FLAG_DELETE_ON_CLOSE,						

		// The file is opened without system caching for data reads or writes
		NoBuffer = FILE_FLAG_NO_BUFFERING,			

		// The file data is requested by remote system and stored in the remote
		OpenNoRecall = FILE_FLAG_OPEN_NO_RECALL,						

		// CreateFile attempt to open the reparse point. it cannot be used with CREATE_ALWALYS
		OpenReparsePoint = FILE_FLAG_OPEN_REPARSE_POINT,			

		// This file is openning for asyncChronous I/O.
		OverLapped = FILE_FLAG_OVERLAPPED,		

		// Access will occur according to POSIX rules
		PosixSemantics = FILE_FLAG_POSIX_SEMANTICS,						

		// Access is intended to be random
		RandomAccess = FILE_FLAG_RANDOM_ACCESS,			

		// Access is intended to be sequential from beginning to end
		SequentialScan = FILE_FLAG_SEQUENTIAL_SCAN,		

		// Write operations will not go through any intermediate cache, they will go directly to disk.
		DirectWrite = FILE_FLAG_WRITE_THROUGH								
	};

	// File's attributes structure
	struct FileAttribute
	{
		// This file is a backup or delete one
		UInt64 dwArchive;										

		// This is Compressed file
		UInt64 dwCompressed;				

		// Reversed
		UInt64 dwDevice;				

		// This is a directory
		UInt64 dwDirectory;					

		// Encrypted the File or Directory
		UInt64 dwEncrypted;			

		// This file is not seen
		UInt64 dwHidden;					

		// This is a standard file
		UInt64 dwNormal;				

		// This is file cannot be indexed
		UInt64 dwNotContentIndexed;		

		// This file is on offline,its' data can not be used at time
		UInt64 dwOffline;								

		// This file is read only
		UInt64 dwReadOnly;												

		// The file includes reparse point which produced by user
		UInt64 dwReparsePoint;								

		// This file is sparse file with large data
		UInt64 dwSparseFile;							

		// This is a system file which used by OS only
		UInt64 dwSystem;	

		// This is a temporary file when used.
		UInt64 dwTemporary;															

		// This is a system file
		UInt64 dwVirtual;

		// Is None or not
		Boolean IsEmpty()
		{
			return (dwArchive == 0
				&& dwCompressed == 0
				&& dwDevice == 0
				&& dwDirectory == 0
				&& dwEncrypted == 0
				&& dwHidden == 0
				&& dwNormal == 0
				&& dwNotContentIndexed == 0
				&& dwOffline == 0
				&& dwReadOnly == 0
				&& dwReparsePoint == 0
				&& dwSparseFile == 0
				&& dwSystem == 0
				&& dwTemporary == 0
				&& dwVirtual==0);
		}
	};
}

#endif // SYSTEMTYPE_H