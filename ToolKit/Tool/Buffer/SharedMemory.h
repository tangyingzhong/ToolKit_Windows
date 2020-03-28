///************************************************************************
/// <copyrigth>2018-2019 Corporation.All Rights Reserved</copyrigth>
/// <author>tangyingzhong</author>
/// <contact>tangyz114987@outlook.com</contact>
/// <version>v1.0.0</version>
/// <describe>
/// Common memory for all the process in one computer
///</describe>
/// <date>2019/7/16</date>
///***********************************************************************
#ifndef SHAREDMEMORY_H
#define SHAREDMEMORY_H

#include "Tool/BaseType/String.h"

using namespace System::BasicType;

namespace System
{
	namespace Buffer
	{
		class SharedMemory
		{
		public:
			typedef System::None None;
			typedef System::Object Object;
			typedef System::Boolean BOOL;
			typedef System::Byte Byte;
			typedef System::ByteArray ByteArray;
			typedef System::Object MapFileHandle;
			typedef System::UInt64 ViewSize;
			typedef System::Int32 Length;
			typedef Length MapFileSize;
			typedef Length Offset;
			typedef String MapFileName;

			// This is the system size of file mapping view(alligment to the system)
			typedef enum _SystemAllign
			{
				MAPVIEWSIZE = 64 * 1024,
			}SystemAllign;

		public:
			// Construct the SharedMemory
			SharedMemory(const MapFileName strMapFileName, const MapFileSize iMapFileSize);

			// Detructe the SharedMemory
			~SharedMemory();

		private:
			// Forbid the object copying
			SharedMemory(const SharedMemory& other) {	}

			// Forbid the object copying
			SharedMemory& operator=(const SharedMemory& other) {	}

		public:
			// Read the common memory. 
			BOOL Read(ByteArray buffer, Length offset, Length len);

			// Write to the common memory
			BOOL Write(ByteArray buffer, Length offset, Length len);

		private:
			// Initialize the shared memory
			None Initialize();

			// Destory the shared memory
			None Destory();

			// Open the map file
			None Open();

			// Close the map file
			None Close();

			// Is the shared memory opened or not
			BOOL IsOpen();

		private:
			// Get the Mapfile
			inline MapFileHandle GetMapfileHandle() const
			{
				return m_MapfileHandle;
			}

			// Set the Mapfile
			inline None SetMapfileHandle(MapFileHandle hMapFile)
			{
				m_MapfileHandle = hMapFile;
			}

			// Get the Name
			inline MapFileName GetMapFileName() const
			{
				return m_MapFileName;
			}

			// Set the Name
			inline None SetMapFileName(MapFileName strMapFileName)
			{
				m_MapFileName = strMapFileName;
			}

			// Get the SharedSize
			inline MapFileSize GetSharedSize() const
			{
				return m_SharedSize;
			}

			// Set the SharedSize
			inline None SetSharedSize(MapFileSize iMapSize)
			{
				m_SharedSize = iMapSize;
			}

			// Get the disposed
			inline BOOL GetDisposed() const
			{
				return m_Disposed;
			}

			// Set the disposed	
			inline None SetDisposed(BOOL bDisposed)
			{
				m_Disposed = bDisposed;
			}

		private:
			// The handle of the map file
			MapFileHandle m_MapfileHandle;

			// The size of the sheared memory
			MapFileSize m_SharedSize;

			// The name of the map file
			MapFileName m_MapFileName;

			// Disposed status
			BOOL m_Disposed;

		};
	}
}

#endif // SHAREDMEMORY_H