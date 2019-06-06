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
#ifndef SYSTEMTYPE_H
#define SYSTEMTYPE_H

#include <assert.h>
#include <Windows.h>
#include <tchar.h>
#include <cstring>
#include <string>
#include <sstream>
#include <vector>
#include <queue>

using namespace std;

namespace System
{
	// True or False
	typedef bool Boolean;			

	// Nothing
	typedef void Empty;

	// Universal pointer : any type pointer or NULL (4 bytes in memory)
	typedef Empty* Object;				

	// One byte: 0-255
	typedef unsigned char Byte;		

	// Byte pointer : 4 bytes in memory	
	typedef Byte* ByteArray;	

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

	// Long integer : -2 ^ 64 / 2 - 2 ^ 64 / 2 - 1
	typedef long Int64;						

	// Long integer : 0 - 2 ^ 64 - 1
	typedef unsigned long UInt64;	

	// Single real: 4 bytes in memory
	typedef float Single;				

	// Double real: 8 bytes in memory
	typedef double Double;	

	// Function that called back by a thread	
	typedef UInt64(WINAPI *ThreadRountine)(Object obj);							

	// The way to open the file
	typedef enum _Filemode
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
	}FileMode;

	// The way to operate the file
	typedef enum _FileAccess
	{
		// Read allowed only
		READ = GENERIC_READ,			

		// Write allowed only
		WRITE = GENERIC_WRITE,								

		// Read and Write allowed
		READWRITE = GENERIC_READ | GENERIC_WRITE						
	}FileAccess;

	// The way of allowing the file to be shared with others
	typedef enum _FileShare
	{
		// Sharing reading the same file with other thread or process 
		SREAD = FILE_SHARE_READ,				

		// Sharing writing the same file with other thread or process 
		SWRITE = FILE_SHARE_WRITE,								

		// Sharing reading and writing the same file with other thread or process 
		SREADWRITE = FILE_SHARE_READ | FILE_SHARE_WRITE				
	}FileShare;

	// Operate the file's data in which position
	typedef enum _SeekOrigin
	{
		// Seek from the beginning 
		BEGIN = 0,			

		// Seek from the current position
		CURRENT = 1,		

		// Seek from the end position
		END = 2																				
	}SeekOrigin;

	// File's attributes enum
	typedef enum _FileAttribute
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

		// Integrity Support(sacnner)
		INTEGRITYSTREAM = FILE_ATTRIBUTE_INTEGRITY_STREAM,		

		// This is a standard file
		NORMAL = FILE_ATTRIBUTE_NORMAL,							

		// This file's data cannot be scanned by the background
		NOSCRUBDATA = FILE_ATTRIBUTE_NO_SCRUB_DATA,				

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
		TEMPORARY = FILE_ATTRIBUTE_TEMPORARY							
	}FileAttrEnum;

	// File's flag
	typedef enum _FileFlag
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

		// The file or device is being opened with session awareness
		SessionAware = FILE_FLAG_SESSION_AWARE,							

		// Access is intended to be sequential from beginning to end
		SequentialScan = FILE_FLAG_SEQUENTIAL_SCAN,		

		// Write operations will not go through any intermediate cache, they will go directly to disk.
		DirectWrite = FILE_FLAG_WRITE_THROUGH								
	}FileFlag;

	// Encode type of the string
	typedef enum _EncodeType
	{
		// ASCII type string
		E_ASCII = 0,						

		// UTF8 type string
		E_UTF8,					

		// UNICODE type string
		E_UNICODE																				
	}EncodeType;

	// The baund rate of the port
	typedef enum _BoundRate
	{
		// Port's transferring speed: Low
		PORT_LOW_SPEED = 9600,							

		// Port's transferring speed: High
		PORT_HIGH_SPEED = 14400,												

		// Port's transferring speed: Super
		PORT_SUPER_SPEED = 115200													
	}BoundRate;

	// Bits of one data of the port 
	typedef enum _DataBits
	{
		// Port's transferring length of one character: 8
		PORT_EIGHT = 8,						

		// Port's transferring length of one character: 16
		PORT_SIXTEEN = 16																	
	}DataBits;

	// Check bits of the port
	typedef enum _Parity
	{
		// Port's parity checking,No
		PORT_NO = 0,							

		// Port's odd parity checking
		PORT_ODD = 1,							

		// Port's even parity checking		
		PORT_EVEN = 2																		
	}Parity;

	// Stop bits of the port
	typedef enum _StopBits
	{
		// Port's transferring ending bits width:0
		PORT_ONE = 0,					

		// Port's transferring ending bits width:1
		PORT_HALF = 1,						

		// Port's transferring ending bits width:2
		PORT_TWO = 2																			
	}StopBits;

	// Timeout of the port
	typedef enum _PortTimeOut
	{
		// Reading interval between two characters
		PORT_READ_INTERVAL = 1000,									

		// Scal factor number
		PORT_READ_MULTIPLE = 1000,					

		// Constant read time
		PORT_READ_CONSTANT = 1000,								

		// Scal factor number
		PORT_WRITE_MULTIPLE = 1000,									

		// Constant write time
		PORT_WRITE_CONSTANT = 1000												
	}PortTimeOut;

	// Cache for the port transferring
	typedef enum _PortCache
	{
		// Input cache for the port
		PORT_INPUT_CACHE_SIZE = 1024,									

		// Output cache for the port
		PORT_OUTPUT_CACHE_SIZE = 1024											
	}PortCache;

	// Port's cache status
	typedef enum
	{
		// Abort the tx
		ABORTTX = PURGE_TXABORT,					

		// Abort the rx
		ABORTRX = PURGE_RXABORT,				

		// Clear the tx cache
		CLEARTX = PURGE_TXCLEAR,						

		// Clear the rx cache
		CLEARRX = PURGE_RXCLEAR													
	}CacheStatus;

	// File's attributes structure
	typedef struct
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

		// Integrity Support(sacnner)
		UInt64 dwIntegrityStream;	

		// This is a standard file
		UInt64 dwNormal;				

		// This file's data cannot be scanned by the background
		UInt64 dwNoScrubData;											

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

		// Is empty or not
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

#endif // SYSTEMTYPE_H