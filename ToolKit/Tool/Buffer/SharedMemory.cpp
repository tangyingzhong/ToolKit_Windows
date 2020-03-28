#include "Array.h"
#include "SharedMemory.h"

using namespace System::Buffer;

// Construct the shared memory with a fixed size and name
SharedMemory::SharedMemory(const MapFileName strMapFileName, const MapFileSize iMapFileSize) :m_MapfileHandle(NULL),
m_MapFileName(strMapFileName),
m_SharedSize(iMapFileSize),
m_Disposed(false)
{
	Initialize();
}

// Detructe the SharedMemory
SharedMemory::~SharedMemory()
{
	Destory();
}

// Initialize the shared memory
SharedMemory::None SharedMemory::Initialize()
{

}

// Dispose the shared memory
SharedMemory::None SharedMemory::Destory()
{
	if (!GetDisposed())
	{
		SetDisposed(true);

		Close();
	}
}

// Is the shared memory opened or not
SharedMemory::BOOL SharedMemory::IsOpen()
{
	if (GetMapfileHandle() == NULL)
	{
		return false;
	}

	return true;
}

// Open the map file
SharedMemory::None SharedMemory::Open()
{
	MapFileHandle hMapFileHandle = ::OpenFileMapping(FILE_MAP_ALL_ACCESS, 
		NULL, 
		GetMapFileName().CStr());
	if (hMapFileHandle == NULL)
	{
		SetMapfileHandle(::CreateFileMapping(INVALID_HANDLE_VALUE, 
			NULL, 
			PAGE_READWRITE, 
			0, 
			GetSharedSize(), 
			GetMapFileName().CStr()));
	}
	else
	{
		SetMapfileHandle(hMapFileHandle);
	}
}

// Read the common memory.(Len must be one of 64K ,2*64K,4*64KIt can be called one-level cache,two-level cache and four -level cache)
SharedMemory::BOOL SharedMemory::Read(ByteArray buffer, Length offset, Length len)
{
	BOOL bSuccess = false;

	// Check the legal of the input paras
	if (buffer == NULL || len > GetSharedSize())
	{
		return bSuccess;
	}

	// Check the share is opend or not
	if (IsOpen() == false)
	{
		Open();
	}

	// Get the view of the share memory
	Object pShared = ::MapViewOfFile(GetMapfileHandle(), FILE_MAP_ALL_ACCESS, 0, 0, 0);
	if (pShared == NULL)
	{
		return bSuccess;
	}

	// Copy the data from the map file
	Array<Byte>::Copy((ByteArray)pShared, len, buffer + offset, len);

	// UnMap to the view
	::UnmapViewOfFile(pShared);

	bSuccess = true;

	return bSuccess;
}

// Write the map file
SharedMemory::BOOL SharedMemory::Write(ByteArray buffer, Length offset, Length len)
{
	BOOL bSuccess = false;

	// Check the legal of the input paras
	if (buffer == NULL || len > GetSharedSize())
	{
		return bSuccess;
	}

	// Check the share is opend or not
	if (IsOpen() == false)
	{
		Open();
	}

	// Map to a view
	Object pShared = ::MapViewOfFile(GetMapfileHandle(), FILE_MAP_ALL_ACCESS, 0, 0, 0);
	if (pShared == NULL)
	{
		return bSuccess;
	}
	// Copy the data from the map file
	Array<Byte>::Copy(buffer + offset, len, (ByteArray)pShared, len);

	// UnMap to the view
	::UnmapViewOfFile(pShared);

	bSuccess = true;

	return bSuccess;
}

// Close the map file
SharedMemory::None SharedMemory::Close()
{
	if (GetMapfileHandle())
	{
		::CloseHandle(GetMapfileHandle());

		SetMapfileHandle(NULL);
	}
}