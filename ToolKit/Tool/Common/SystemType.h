///************************************************************************
/// <copyrigth>2018-2019 Corporation.All Rights Reserved</copyrigth>
/// <author>tangyingzhong</author>
/// <contact>tangyz114987@outlook.com</contact>
/// <version>V1.0.0</version>
/// <describe>
/// Basic type of the system on windows
///</describe>
/// <date>2019/3/2</date>
///***********************************************************************
#ifndef SYSTEMTYPE_H_
#define SYSTEMTYPE_H_

#include <assert.h>
#include <tchar.h>
#include <Windows.h>
#include <string>
#include <sstream>
#include <vector>
#include <queue>

using namespace std;

namespace System
{
	typedef bool Boolean;												// True or False
	typedef void Empty;													// Nothing
	typedef Empty* Object;												// Universal pointer : any type pointer or NULL (4 bytes in memory)
	typedef unsigned char Byte;											// One byte: 0-255
	typedef Byte* ByteArray;											// Byte pointer : 4 bytes in memory	
	typedef char SByte;													// Signed byte with the range from -127-128
	typedef SByte* SByteArray;											// Signed byte array which is 4 bytes in memory
	typedef wchar_t WByte;												// Wide byte that can contain the unicode string
	typedef WByte* WByteArray;											// Wide byte array which is 4 bytes in memory
#ifdef UNICODE
	typedef WByte Character;											// An character that accepts all character type including unicode
	typedef Character* CharArray;										// Characters' array
	typedef std::wstring StdString;										// String of the STL
	typedef std::wstringstream StringStream;							// Convert string to other type data or other type data transfers to be string
#else
	typedef SByte Character;												// An character that is ranged from -128 - 127
	typedef Character* CharArray;										// Characters' array
	typedef std::string StdString;										// String of the STL
	typedef std::stringstream StringStream;								// Convert string to other type data or other type data transfers to be string
#endif
	typedef short Int16;												// Short integer : -2 ^ 16 / 2 - 2 ^ 16 / 2 - 1
	typedef unsigned short UInt16;										// Short integer : 0 - 2 ^ 16 - 1
	typedef int Int32;													// Integer : -2 ^ 32 / 2 - 2 ^ 32 / 2 - 1
	typedef unsigned int UInt32;										// Integer : 0 - 2 ^ 32 - 1
	typedef long Int64;													// Long integer : -2 ^ 64 / 2 - 2 ^ 64 / 2 - 1
	typedef unsigned long UInt64;										// Long integer : 0 - 2 ^ 64 - 1
	typedef float Single;												// Single real: 4 bytes in memory
	typedef double Double;												// Double real: 8 bytes in memory
	typedef UInt64(WINAPI *ThreadRountine)(Object obj);					// Function that called back by a thread			

	// The way to open the file
	typedef enum _Filemode
	{
		APPEND = OPEN_ALWAYS,											// File exist and open it or create it and write at the end
		CREATE = CREATE_ALWAYS,											// Create a file whatever it is existed or not."w" "w+"
		CREATENEW = CREATE_NEW,											// File must be not exist and it can create file or error happends 
		OPEN = OPEN_EXISTING,											// File must be exist or error happends . "r"  "r+"
		OPENORCREATE = OPEN_ALWAYS,										// File exist and open it or create it.
		TRUNC = TRUNCATE_EXISTING,										// Make current file's length to be 0
	}FileMode;

	// The way to operate the file
	typedef enum _FileAccess
	{
		READ = GENERIC_READ,											// Read allowed only
		WRITE = GENERIC_WRITE,											// Write allowed only
		READWRITE = GENERIC_READ | GENERIC_WRITE						// Read and Write allowed
	}FileAccess;

	// The way of allowing the file to be shared with others
	typedef enum _FileShare
	{
		SREAD = FILE_SHARE_READ,										// Sharing reading the same file with other thread or process 
		SWRITE = FILE_SHARE_WRITE,										// Sharing writing the same file with other thread or process 
		SREADWRITE = FILE_SHARE_READ | FILE_SHARE_WRITE					// Sharing reading and writing the same file with other thread or process 
	}FileShare;

	// Operate the file's data in which position
	typedef enum _SeekOrigin
	{
		BEGIN = 0,														// Seek from the beginning 
		CURRENT = 1,													// Seek from the current position
		END = 2															// Seek from the end position
	}SeekOrigin;

	// File's attributes enum
	typedef enum _FileAttribute
	{
		ARCHIVE = FILE_ATTRIBUTE_ARCHIVE,								// This file is a backup or delete one
		COMPRESSED = FILE_ATTRIBUTE_COMPRESSED,							// This is Compressed file
		DEVICE = FILE_ATTRIBUTE_DEVICE,									// Reversed
		DIRECTORY = FILE_ATTRIBUTE_DIRECTORY,							// This is a directory
		ENCRYPTED = FILE_ATTRIBUTE_ENCRYPTED,							// Encrypted the File or Directory
		HIDDEN = FILE_ATTRIBUTE_HIDDEN,									// This file is not seen
		INTEGRITYSTREAM = FILE_ATTRIBUTE_INTEGRITY_STREAM,				// Integrity Support(sacnner)
		NORMAL = FILE_ATTRIBUTE_NORMAL,									// This is a standard file
		NOSCRUBDATA = FILE_ATTRIBUTE_NO_SCRUB_DATA,						// This file's data cannot be scanned by the background
		NOTCONTENTINDEXED = FILE_ATTRIBUTE_NOT_CONTENT_INDEXED,			// This is file cannot be indexed 
		OFFLINE = FILE_ATTRIBUTE_OFFLINE,								// This file is on offline,its' data can not be used at time
		READONLY = FILE_ATTRIBUTE_READONLY,								// This file is read only
		REPARSEPOINT = FILE_ATTRIBUTE_REPARSE_POINT,					// The file includes reparse point which produced by user
		SPARSEFILE = FILE_ATTRIBUTE_SPARSE_FILE,						// This file is sparse file with large data
		SYSTEM = FILE_ATTRIBUTE_SYSTEM,									// This is a system file which used by OS only
		TEMPORARY = FILE_ATTRIBUTE_TEMPORARY							// This is a temporary file when used.
	}FileAttrEnum;

	// File's flag
	typedef enum _FileFlag
	{
		BackupSemantics = FILE_FLAG_BACKUP_SEMANTICS,					// This file is opened or created for a backup or restore operation
		DeleteOnClose = FILE_FLAG_DELETE_ON_CLOSE,						// The file is to be deleted immediately after the file handle closed
		NoBuffer = FILE_FLAG_NO_BUFFERING,								// The file is opened without system caching for data reads or writes
		OpenNoRecall = FILE_FLAG_OPEN_NO_RECALL,						// The file data is requested by remote system and stored in the remote
		OpenReparsePoint = FILE_FLAG_OPEN_REPARSE_POINT,				// CreateFile attempt to open the reparse point. it cannot be used with CREATE_ALWALYS
		OverLapped = FILE_FLAG_OVERLAPPED,								// This file is openning for asyncChronous I/O.
		PosixSemantics = FILE_FLAG_POSIX_SEMANTICS,						// Access will occur according to POSIX rules
		RandomAccess = FILE_FLAG_RANDOM_ACCESS,							// Access is intended to be random
		SessionAware = FILE_FLAG_SESSION_AWARE,							// The file or device is being opened with session awareness
		SequentialScan = FILE_FLAG_SEQUENTIAL_SCAN,						// Access is intended to be sequential from beginning to end
		DirectWrite = FILE_FLAG_WRITE_THROUGH							// Write operations will not go through any intermediate cache, they will go directly to disk.
	}FileFlag;

	// Encode type of the string
	typedef enum _EncodeType
	{
		E_ASCII = 0,													// ASCII type string
		E_UTF8,															// UTF8 type string
		E_UNICODE														// UNICODE type string
	}EncodeType;

	// The baund rate of the port
	typedef enum _BoundRate
	{
		PORT_LOW_SPEED = 9600,											// Port's transferring speed: Low
		PORT_HIGH_SPEED = 14400,										// Port's transferring speed: High
		PORT_SUPER_SPEED = 115200										// Port's transferring speed: Super
	}BoundRate;

	// Bits of one data of the port 
	typedef enum _DataBits
	{
		PORT_EIGHT = 8,													// Port's transferring length of one character: 8
		PORT_SIXTEEN = 16												// Port's transferring length of one character: 16
	}DataBits;

	// Check bits of the port
	typedef enum _Parity
	{
		PORT_NO = 0,													// Port's parity checking,No
		PORT_ODD = 1,													// Port's odd parity checking
		PORT_EVEN = 2													// Port's even parity checking		
	}Parity;

	// Stop bits of the port
	typedef enum _StopBits
	{
		PORT_ONE = 0,													// Port's transferring ending bits width:0
		PORT_HALF = 1,													// Port's transferring ending bits width:1
		PORT_TWO = 2													// Port's transferring ending bits width:2
	}StopBits;

	// Timeout of the port
	typedef enum _PortTimeOut
	{
		PORT_READ_INTERVAL = 1000,										// Reading interval between two characters
		PORT_READ_MULTIPLE = 1000,										// Scal factor number
		PORT_READ_CONSTANT = 1000,										// Constant read time
		PORT_WRITE_MULTIPLE = 1000,										// Scal factor number
		PORT_WRITE_CONSTANT = 1000										// Constant write time
	}PortTimeOut;

	// Cache for the port transferring
	typedef enum _PortCache
	{
		PORT_INPUT_CACHE_SIZE = 1024,									// Input cache for the port
		PORT_OUTPUT_CACHE_SIZE = 1024									// Output cache for the port
	}PortCache;

	// Port's cache status
	typedef enum
	{
		ABORTTX = PURGE_TXABORT,										// Abort the tx
		ABORTRX = PURGE_RXABORT,										// Abort the rx
		CLEARTX = PURGE_TXCLEAR,										// Clear the tx cache
		CLEARRX = PURGE_RXCLEAR											// Clear the rx cache
	}CacheStatus;

	// File's attributes structure
	typedef struct
	{
		UInt64 dwArchive;												// This file is a backup or delete one
		UInt64 dwCompressed;											// This is Compressed file
		UInt64 dwDevice;												// Reversed
		UInt64 dwDirectory;												// This is a directory
		UInt64 dwEncrypted;												// Encrypted the File or Directory
		UInt64 dwHidden;												// This file is not seen
		UInt64 dwIntegrityStream;										// Integrity Support(sacnner)
		UInt64 dwNormal;												// This is a standard file
		UInt64 dwNoScrubData;											// This file's data cannot be scanned by the background
		UInt64 dwNotContentIndexed;										// This is file cannot be indexed 
		UInt64 dwOffline;												// This file is on offline,its' data can not be used at time
		UInt64 dwReadOnly;												// This file is read only
		UInt64 dwReparsePoint;											// The file includes reparse point which produced by user
		UInt64 dwSparseFile;											// This file is sparse file with large data
		UInt64 dwSystem;												// This is a system file which used by OS only
		UInt64 dwTemporary;												// This is a temporary file when used.

		Boolean IsEmpty()
		{
			return (dwArchive == 0
				&& dwCompressed == 0
				&& dwDevice == 0
				&& dwDirectory == 0
				&& dwEncrypted == 0
				&& dwHidden == 0
				&& dwIntegrityStream == 0
				&& dwNormal == 0
				&& dwNoScrubData == 0
				&& dwNotContentIndexed == 0
				&& dwOffline == 0
				&& dwReadOnly == 0
				&& dwReparsePoint == 0
				&& dwSparseFile == 0
				&& dwSystem == 0
				&& dwTemporary == 0);
		}

	}FileAttribute;
}

#endif // !SYSTEMTYPE_H_