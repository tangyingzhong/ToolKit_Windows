#include "Application\PreCompile.h"
#include "Tool\Buffer\Array.h"
#include "USB.h"

#pragma comment(lib, "setupapi")

using namespace System::IO;
using namespace System::Buffer;

///************************************************************************
/// <summary>
/// Construct the usb with the Guid
/// </summary>
/// <param name=id>usb class guid</param>
/// <returns></returns>
/// <remarks>
/// none
/// </remarks>
///***********************************************************************
USB::USB(String strVid, String strPid, const DeviceID iDeviceID) :m_UsbHandle(NULL),
m_DevicePath(_T("")),
m_DeviceID(iDeviceID),
m_UsbVid(strVid),
m_UsbPid(strPid),
m_Disposed(false)
{
	Initialize();
}


///************************************************************************
/// <summary>
/// Destruct the usb
/// </summary>
/// <returns></returns>
/// <remarks>
/// none
/// </remarks>
///***********************************************************************
USB::~USB()
{
	Destory();
}


///************************************************************************
/// <summary>
/// initialize the usb
/// </summary>
/// <param name=usbId>usb class guid</param>
/// <returns></returns>
/// <remarks>
/// the class guid found in inf file
/// </remarks>
///***********************************************************************
USB::Empty USB::Initialize()
{

}


///************************************************************************
/// <summary>
/// release all the resource using by usb
/// </summary>
/// <returns></returns>
/// <remarks>
/// none
/// </remarks>
///***********************************************************************
USB::Empty USB::Destory()
{
	if (!GetDisposed())
	{
		SetDisposed(true);

		// Close the usb
		this->Close();
	}
}


///************************************************************************
/// <summary>
/// Set the timeout of the device
/// </summary>
/// <param name=totalTimeout></param>
/// <returns></returns>
/// <remarks>
/// none
/// </remarks>
///***********************************************************************
USB::BOOL USB::SetTimeOut(USBSize iTotalTimeout)
{
	BOOL bSuccess = false;

	COMMTIMEOUTS UsbTimeout;

	UsbTimeout.ReadIntervalTimeout = 0;
	UsbTimeout.ReadTotalTimeoutMultiplier = 0;
	UsbTimeout.ReadTotalTimeoutConstant = iTotalTimeout;

	UsbTimeout.WriteTotalTimeoutMultiplier = 0;
	UsbTimeout.WriteTotalTimeoutConstant = 0;

	if (::SetCommTimeouts(this->GetUsbHandle(), &UsbTimeout) == FALSE)
	{
		return bSuccess;
	}

	bSuccess = true;

	return bSuccess;
}


///************************************************************************
/// <summary>
/// Rebuild the vedor ID and product ID
/// </summary>
/// <param name=vid></param>
/// <param name=pid></param>
/// <returns></returns>
/// <remarks>
/// none
/// </remarks>
///***********************************************************************
USB::Empty USB::CreateVidPid(String strVid, String strPid, PVIDTable& vPVIDTable)
{
	// Rebuild the vid and pid
	String strVidHead = _T("vid_");
	String sVID = strVidHead + strVid + _T("&pid_") + strPid;

	// Push the string to the vector
	vPVIDTable.push_back(sVID);

	// Rebuild the vid and pid
	String strVidHead1 = _T("VID_");
	String sVID1 = strVidHead1 + strVid + _T("&PID_") + strPid;

	// Push the string to the vector
	vPVIDTable.push_back(sVID1);
}


///************************************************************************
/// <summary>
/// filtrate the current usb path by its' vid and pid
/// </summary>
/// <param name=usbPath>all the enumerated usb path in it</param>
/// <param name=pathCount>the total count of usb path </param>
/// <returns>the current usb path</returns>
/// <remarks>
/// after the enumerating,there is many usb path,so we need to find the correct one
/// </remarks>
///***********************************************************************
String USB::Filtrate(UsbPathTable& vUsbPathTable)
{
	String strUsbPath = _T("");

	if (vUsbPathTable.empty())
	{
		return strUsbPath;
	}

	// Get the correct VID,PID
	PVIDTable vVidPidTable;
	this->CreateVidPid(this->GetVid(), this->GetPid(), vVidPidTable);

	// Choose one fixed device's interface(device path)
	for (Index iInterfaceIndex = 0; iInterfaceIndex < (Index)vUsbPathTable.size(); iInterfaceIndex++)
	{
		// Split the path
		UsbPathTable vPathTable;
		BOOL bSuccess = vUsbPathTable[iInterfaceIndex].Split(_T("#"), vPathTable);
		if (!bSuccess)
		{
			return strUsbPath;
		}

		// Compare the split string with vid ,pid of the usb
		const Int32 VIDPID_POSITION = 1;
		if (vPathTable[VIDPID_POSITION] == vVidPidTable[0] || vPathTable[VIDPID_POSITION] == vVidPidTable[1])
		{
			strUsbPath = vUsbPathTable[iInterfaceIndex];

			return strUsbPath;
		}
	}

	return strUsbPath;
}


///************************************************************************
/// <summary>
/// enum all the usb devices
/// </summary>
/// <param name=deviceId>the kind of device's guid</param>
/// <returns>the list of device</returns>
/// <remarks>
/// we can enum all devices with the guid
/// </remarks>
///***********************************************************************
USB::Device USB::EnumDevices(DeviceID iDeviceID)
{
	Device device = ::SetupDiGetClassDevs(&iDeviceID, NULL, NULL, DIGCF_PRESENT | DIGCF_DEVICEINTERFACE);
	if (device == INVALID_HANDLE_VALUE)
	{
		return NULL;
	}

	return device;
}


///************************************************************************
/// <summary>
/// create the interface detail struct to have the info of interface
/// </summary>
/// <param name=size>the size of applying</param>
/// <returns>interface info struct</returns>
/// <remarks>
/// none
/// </remarks>
///***********************************************************************
USB::PInterfaceDetailInfo USB::CreateInterfaceDetail(USBSize iSize)
{
	PInterfaceDetailInfo pDetail = (PInterfaceDetailInfo)::GlobalAlloc(LMEM_ZEROINIT, iSize);
	if (pDetail == NULL)
	{
		return NULL;
	}

	pDetail->cbSize = sizeof(InterfaceDetailInfo);

	return pDetail;
}


///************************************************************************
/// <summary>
/// destory the applyed interface detail struct
/// </summary>
/// <param name=interfaceDetail>the interface detail struct</param>
/// <returns></returns>
/// <remarks>
/// none
/// </remarks>
///***********************************************************************
USB::Empty USB::DestoryInterfaceDetail(PInterfaceDetailInfo interfaceDetail)
{
	::GlobalFree(interfaceDetail);
}


///************************************************************************
/// <summary>
/// Get the correct usb path that you want to operate
/// </summary>
/// <returns>the usb path</returns>
/// <remarks>
/// This path is specail one on OS,it can symbol the usb you want to operate
/// </remarks>
///***********************************************************************
String USB::AcquireDevicePath()
{
	// Enum the device
	Device device = EnumDevices(this->GetDeviceID());
	if (device == NULL)
	{
		return _T("");
	}

	// Create the interface detail
	const System::Int64 INTERFACE_DETAIL_SIZE = 1024;
	PInterfaceDetailInfo pDetail = CreateInterfaceDetail(INTERFACE_DETAIL_SIZE);
	if (pDetail == NULL)
	{
		// Clear the device info
		SetupDiDestroyDeviceInfoList(device);

		return _T("");
	}

	// Store the devices' path
	UsbPathTable DevicePathTable;

	// The interface info of device
	InterfaceInfo deviceInterfaceData;

	// The index of device in Device info
	Int32 bResult = TRUE;

	// Enum all interfaces of the device
	while (bResult)
	{
		deviceInterfaceData.cbSize = sizeof(deviceInterfaceData);

		// Enum device interface owing the GUID
		UInt64 nCount = 0;
		bResult = ::SetupDiEnumDeviceInterfaces(device, NULL, &GetDeviceID(), nCount, &deviceInterfaceData);
		if (bResult)
		{
			// Get the interface detail info of the device(Get device instance path)
			bResult = SetupDiGetInterfaceDeviceDetail(device, &deviceInterfaceData, pDetail, INTERFACE_DETAIL_SIZE, NULL, NULL);
			if (bResult)
			{
				DevicePathTable.push_back(pDetail->DevicePath);
			}
		}
	}

	// Filtrate the fixed usb path
	String strUsbPath = Filtrate(DevicePathTable);
	if (strUsbPath == _T(""))
	{
		return _T("");
	}

	// Clear the device info
	SetupDiDestroyDeviceInfoList(device);

	// Destory the interface detail
	DestoryInterfaceDetail(pDetail);

	return strUsbPath;
}


///************************************************************************
/// <summary>
/// create the usb path(open the usb)
/// </summary>
/// <param name=usbName>usb path</param>
/// <param name=attr>open usb with the attribute</param>
/// <returns>FAILED or SUCCESS</returns>
/// <remarks>
/// none
/// </remarks>
///***********************************************************************
USB::BOOL USB::_CreateFile(String strUsbName, FileAttrEnum eFileAttribute)
{
	BOOL bSuccess = false;

	if (this->IsOpen())
	{
		bSuccess = true;

		return bSuccess;
	}

	this->SetUsbHandle(CreateFile(strUsbName, FileAccess::READWRITE, FileShare::SREADWRITE, NULL, FileMode::OPEN, eFileAttribute, NULL));
	if (this->GetUsbHandle() == INVALID_HANDLE_VALUE)
	{
		// Close the usb
		this->Close();

		return bSuccess;
	}

	bSuccess = true;

	return bSuccess;
}


///************************************************************************
/// <summary>
/// read write the endpoint of usb
/// </summary>
/// <param name=cmd>the command of operating to usb</param>
/// <param name=package>the buffer having transfering data in</param>
/// <param name=packageSize>buffer size</param>
/// <returns></returns>
/// <remarks>
/// none
/// </remarks>
///***********************************************************************
USB::Size USB::_ReadWriteEndPoint(Command iUSbCommd, ByteArray pPackage, ArraySize pPackageSize)
{
	Size dwBytes = 0;

	if (!IsOpen())
	{
		return dwBytes;
	}

	DeviceIoControl(this->GetUsbHandle(), iUSbCommd, pPackage, pPackageSize, pPackage, pPackageSize, &dwBytes, NULL);

	return dwBytes;
}


///************************************************************************
/// <summary>
/// create a package buffer
/// </summary>
/// <param name=packageSize>buffer size</param>
/// <returns>the pointer of buffer</returns>
/// <remarks>
/// please do remember to destory the memory if it is not used
/// </remarks>
///***********************************************************************
USB::ByteArray USB::CreateOnePackage(ArraySize iPackageSize)
{
	ByteArray pPack = new Byte[iPackageSize];

	memset(pPack, 0, iPackageSize);

	return pPack;
}


///************************************************************************
/// <summary>
/// destory the buffer 
/// </summary>
/// <param name=package>the pointer of buffer</param>
/// <returns></returns>
/// <remarks>
/// release the memory of applyed
/// </remarks>
///***********************************************************************
USB::Empty USB::DestoryPakcage(ByteArray pPackage)
{
	if (pPackage)
	{
		delete[] pPackage;
		pPackage = NULL;
	}
}


///************************************************************************
/// <summary>
/// setup the transfer buffer's head
/// </summary>
/// <param name=package>transfering buffer</param>
/// <param name=enp>the endpoint of usb</param>
/// <param name=isoPackageLength>the length of iso transfering</param>
/// <param name=headOffset>the offset size of head in the buffer</param>
/// <param name=transferSize>transfering buffer size</param>
/// <returns>the head pointer</returns>
/// <remarks>
/// this step is neccesory for any transfering to usb
/// </remarks>
///***********************************************************************
USB::PHeadPackage USB::SetupHeadPackage(ByteArray pPackage,
	EndPoint cEndPoint,
	Length iIsoPackageLength,
	Offset iHeadOffset,
	ArraySize iTransferSize)
{
	PHeadPackage pHead = (PHeadPackage)pPackage;

	pHead->ucEndpointAddress = cEndPoint;
	pHead->IsoPacketLength = iIsoPackageLength;
	pHead->BufferOffset = iHeadOffset;
	pHead->BufferLength = iTransferSize;

	return pHead;
}


///************************************************************************
/// <summary>
/// Setup the transfering buffer's data section
/// </summary>
/// <param name=package>transfering buffer</param>
/// <param name=head>the pointer of head of the transfering buffer</param>
/// <param name=transferBuffer>user's transfering buffer</param>
/// <param name=transferSize>user's transfering buffer size</param>
/// <returns></returns>
/// <remarks>
/// we need to create a new package with correct head and user buffer data
/// </remarks>
///***********************************************************************
USB::Empty USB::SetupTransPackage(ByteArray pPackage,
	PHeadPackage pHead,
	ByteArray pTransferBuffer,
	ArraySize iTransferSize)
{
	// Refer to the transfer buffer position
	ByteArray pBuffer = pPackage + pHead->BufferOffset;

	// Fill the buffer section
	Array<Byte>::Copy(pTransferBuffer, iTransferSize, pBuffer, iTransferSize);
}


///************************************************************************
/// <summary>
/// Is usb opened
/// </summary>
/// <returns></returns>
/// <remarks>
/// none
/// </remarks>
///***********************************************************************
USB::BOOL USB::IsOpen()
{
	if (this->GetUsbHandle())
	{
		return true;
	}

	return false;
}



///************************************************************************
/// <summary>
/// open the usb
/// </summary>
/// <returns></returns>
/// <remarks>
/// any usb operation must follow the open of usb
/// </remarks>
///***********************************************************************
USB::BOOL USB::Open()
{
	BOOL bSuccess = false;

	// Get the usb path
	String strUsbPath = AcquireDevicePath();
	if (strUsbPath == _T(""))
	{
		return bSuccess;
	}

	// Create the usb file
	bSuccess = _CreateFile(strUsbPath, FileAttrEnum::NORMAL);
	if (!bSuccess)
	{
		return bSuccess;
	}

	// Set the usb time out 50ms
	bSuccess = this->SetTimeOut(USBTimeOut::TIMEOUT);
	if (!bSuccess)
	{
		return bSuccess;
	}

	return bSuccess;
}


///************************************************************************
/// <summary>
/// config the usb so that usb can communicate with the client
/// </summary>
/// <param name=target>config target</param>
/// <param name=direction>config the direction of config endpoint</param>
/// <param name=reqType>config the requst type</param>
/// <param name=code>config the request code</param>
/// <param name=value>config the value</param>
/// <param name=indexconfig the index></param>
/// <returns>0£ºconfig failed other£ºconfig ok</returns>
/// <remarks>
/// none
/// </remarks>
///***********************************************************************
USB::BOOL USB::Configure(Target eTarget,
	Direction eDirection,
	RequestType eReqType,
	RequestCode iCode,
	Value iValue,
	Index iIndex)
{
	BOOL bSuccess = false;

	if (!this->IsOpen())
	{
		return bSuccess;
	}

	// Get buffer size(buffer data size of the endpoint 0 is 64)
	Int32 iBufferSize = sizeof(HeadPackage) + DeviceConfiguration::USB_ENP0_TRANSFER_SIZE;

	Array<Byte> Buffer(iBufferSize);

	// Fill the buffer's head
	ByteArray pBuffer = Buffer;
	PHeadPackage pSingleTransfer = (PHeadPackage)pBuffer;
	pSingleTransfer->SetupPacket.bmReqType.Recipient = eTarget;
	pSingleTransfer->SetupPacket.bmReqType.Type = eReqType;
	pSingleTransfer->SetupPacket.bmReqType.Direction = eDirection;
	pSingleTransfer->SetupPacket.bRequest = iCode;
	pSingleTransfer->SetupPacket.wValue = iValue;
	pSingleTransfer->SetupPacket.wIndex = iIndex;
	pSingleTransfer->SetupPacket.wLength = DeviceConfiguration::USB_ENP0_TRANSFER_SIZE;
	pSingleTransfer->SetupPacket.ulTimeOut = 1000 / 1000;

	pSingleTransfer->ucEndpointAddress = EndPoint::USB_CONTRL;
	pSingleTransfer->IsoPacketLength = 0;
	pSingleTransfer->BufferOffset = sizeof(HeadPackage);
	pSingleTransfer->BufferLength = DeviceConfiguration::USB_ENP0_TRANSFER_SIZE;

	// Set the usb device by endpoint 0
	UInt64 dwBytes = 0;
	if (DeviceIoControl(this->GetUsbHandle(),
		UsbCommand::SENDRECEIVE_EP0,
		Buffer,
		iBufferSize,
		Buffer,
		iBufferSize,
		&dwBytes,
		NULL) == TRUE)
	{
		bSuccess = true;
	}

	return bSuccess;
}


///************************************************************************
/// <summary>
/// read the usb
/// </summary>
/// <param name=arr>read buffer</param>
/// <param name=offset>buffer offset</param>
/// <param name=readSize>buffer size</param>
/// <returns>the real size of reading</returns>
/// <remarks>
/// you need to do the timeout here
/// </remarks>
///***********************************************************************
USB::Size USB::Read(ByteArray pReadArray, Offset iOffset, ArraySize iReadSize)
{
	Size dwReadSize = 0;

	assert(pReadArray != NULL);
	assert(iOffset >= 0);
	assert(iReadSize > 0);

	if (pReadArray == NULL || iOffset < 0 || iReadSize <= 0)
	{
		return dwReadSize;
	}

	if (!this->IsOpen())
	{
		return dwReadSize;
	}

	// Create a package that contains head and transfering array
	ArraySize iPackageSize = sizeof(HeadPackage) + iReadSize;

	Array<Byte> PacketBuffer(iPackageSize);

	// Setup the package head
	PHeadPackage head = SetupHeadPackage(PacketBuffer, EndPoint::USB_INPOINT, 0, sizeof(HeadPackage), iReadSize);

	// Set the package with transferring array
	SetupTransPackage(PacketBuffer, head, pReadArray, iReadSize);

	// Read data from the usb through read in endpoint
	dwReadSize = _ReadWriteEndPoint(UsbCommand::SENDRECEIVE_NONE_ENP0, PacketBuffer, PacketBuffer.Size());
	if (dwReadSize == 0)
	{
		return dwReadSize;
	}

	// Get the data section size
	dwReadSize = dwReadSize - sizeof(HeadPackage);

	// Copy the return data to the outside
	Array<Byte>::Copy(PacketBuffer + sizeof(HeadPackage), dwReadSize, pReadArray + iOffset, dwReadSize);

	return dwReadSize;
}


///************************************************************************
/// <summary>
/// write to the usb 
/// </summary>
/// <param name=arr>write buffer</param>
/// <param name=offset>the buffe offset</param>
/// <param name=writeSize>buffe size</param>
/// <returns>the real write size</returns>
/// <remarks>
/// you need to do the timeout here
/// </remarks>
///***********************************************************************
USB::Size USB::Write(ByteArray pWriteArray, Offset iOffset, ArraySize iWriteSize)
{
	Size dwWriteSize = 0;

	assert(pWriteArray != NULL);
	assert(iOffset >= 0);
	assert(iWriteSize > 0);

	if (pWriteArray == NULL || iOffset < 0 || iWriteSize <= 0)
	{
		return dwWriteSize;
	}

	if (!this->IsOpen())
	{
		return dwWriteSize;
	}

	// Create a package that contains head and transfering array
	ArraySize iPackageSize = sizeof(HeadPackage) + iWriteSize;

	Array<Byte> PacketBuffer(iPackageSize);

	// Setup the package head
	PHeadPackage PacketHead = SetupHeadPackage(PacketBuffer, EndPoint::USB_OUTPOINT, 0, sizeof(HeadPackage), iWriteSize);

	// Set the package with transferring array
	SetupTransPackage(PacketBuffer, PacketHead, pWriteArray, iWriteSize);

	// Write data to the usb through out endpoint
	dwWriteSize = _ReadWriteEndPoint(UsbCommand::SENDRECEIVE_NONE_ENP0, PacketBuffer, PacketBuffer.Size());

	return dwWriteSize;
}


///************************************************************************
/// <summary>
/// close the usb
/// </summary>
/// <returns></returns>
/// <remarks>
/// none
/// </remarks>
///***********************************************************************
USB::Empty USB::Close()
{
	if (this->GetUsbHandle())
	{
		::CloseHandle(this->GetUsbHandle());

		this->SetUsbHandle(NULL);
	}
}