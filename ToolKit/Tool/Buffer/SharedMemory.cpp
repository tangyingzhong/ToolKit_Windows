#include "Application\PreCompile.h"
#include "Array.h"
#include "SharedMemory.h"

using namespace System::Buffer;

///************************************************************************
/// <summary>
/// Construct the shared memory with a fixed size and name
/// </summary>
/// <param name=name>Share momery name</param>
/// <param name=size>Share momery size</param>
/// <returns></returns>
/// <remarks>
/// none
/// </remarks>
///***********************************************************************
SharedMemory::SharedMemory(const MapFileName strMapFileName, const MapFileSize iMapFileSize) :m_MapfileHandle(NULL),
m_MapFileName(strMapFileName),
m_SharedSize(iMapFileSize),
m_Disposed(false)
{
	Initialize();
}


///************************************************************************
/// <summary>
/// Detructe the SharedMemory
/// </summary>
/// <returns></returns>
/// <remarks>
/// none
/// </remarks>
///***********************************************************************
SharedMemory::~SharedMemory()
{
	Destory();
}


///************************************************************************
/// <summary>
/// Initialize the shared memory
/// </summary>
/// <returns></returns>
/// <remarks>
/// none
/// </remarks>
///***********************************************************************
SharedMemory::Empty SharedMemory::Initialize()
{

}


///************************************************************************
/// <summary>
/// Dispose the shared memory
/// </summary>
/// <returns></returns>
/// <remarks>
/// none
/// </remarks>
///***********************************************************************
SharedMemory::Empty SharedMemory::Destory()
{
	if (!GetDisposed())
	{
		SetDisposed(true);

		// Close the shared memory
		this->Close();
	}
}


///************************************************************************
/// <summary>
/// Is the shared memory opened or not
/// </summary>
/// <returns></returns>
/// <remarks>
/// none
/// </remarks>
///************************************************************************
SharedMemory::BOOL SharedMemory::IsOpen()
{
	if (this->GetMapfileHandle() == NULL)
	{
		return false;
	}

	return true;
}


///************************************************************************
/// <summary>
/// Open the map file
/// </summary>
/// <returns></returns>
/// <remarks>
/// none
/// </remarks>
///***********************************************************************
SharedMemory::Empty SharedMemory::Open()
{
	MapFileHandle hMapFileHandle = ::OpenFileMapping(FILE_MAP_ALL_ACCESS, NULL, this->GetMapFileName());
	if (hMapFileHandle == NULL)
	{
		this->SetMapfileHandle(::CreateFileMapping(INVALID_HANDLE_VALUE, NULL, PAGE_READWRITE, 0, this->GetSharedSize(), this->GetMapFileName()));
	}
	else
	{
		this->SetMapfileHandle(hMapFileHandle);
	}
}


///************************************************************************
/// <summary>
/// Read the common memory.  
/// </summary>
/// <param name=buffer></param>
/// <param name=offset></param>
/// <param name=len></param>
/// <returns></returns>
/// <remarks>
/// Notice: len must be one of 64K ,2*64K,4*64KIt can be called one-level cache,two-level cache and four -level cache
/// </remarks>
///***********************************************************************
SharedMemory::BOOL SharedMemory::Read(ByteArray buffer, Length offset, Length len)
{
	BOOL bSuccess = false;

	// Check the legal of the input paras
	assert(buffer != NULL);
	assert(len <= GetSharedSize());

	if (buffer == NULL || len > this->GetSharedSize())
	{
		return bSuccess;
	}

	// Check the share is opend or not
	if (this->IsOpen() == false)
	{
		this->Open();
	}

	// Get the view of the share memory
	Object pShared = ::MapViewOfFile(this->GetMapfileHandle(), FILE_MAP_ALL_ACCESS, 0, 0, 0);
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


///************************************************************************
/// <summary>
/// Write the map file
/// </summary>
/// <param name=buffer></param>
/// <param name=offset></param>
/// <param name=len></param>
/// <returns></returns>
/// <remarks>
/// Notice: len must be one of 64K ,2*64K,4*64K It can be called one-level cache,two-level cache and four -level cache
/// </remarks>
///***********************************************************************
SharedMemory::BOOL SharedMemory::Write(ByteArray buffer, Length offset, Length len)
{
	BOOL bSuccess = false;

	// Check the legal of the input paras
	assert(buffer != NULL);
	assert(len <= GetSharedSize());

	if (buffer == NULL || len > this->GetSharedSize())
	{
		return bSuccess;
	}

	// Check the share is opend or not
	if (this->IsOpen() == false)
	{
		this->Open();
	}

	//Map to a view
	Object pShared = ::MapViewOfFile(this->GetMapfileHandle(), FILE_MAP_ALL_ACCESS, 0, 0, 0);
	if (pShared == NULL)
	{
		return bSuccess;
	}
	//Copy the data from the map file
	Array<Byte>::Copy(buffer + offset, len, (ByteArray)pShared, len);

	//UnMap to the view
	::UnmapViewOfFile(pShared);

	bSuccess = true;

	return bSuccess;
}


///************************************************************************
/// <summary>
/// Close the map file
/// </summary>
/// <returns></returns>
/// <remarks>
/// none
/// </remarks>
///***********************************************************************
SharedMemory::Empty SharedMemory::Close()
{
	if (this->GetMapfileHandle())
	{
		::CloseHandle(GetMapfileHandle());
		this->SetMapfileHandle(NULL);
	}
}