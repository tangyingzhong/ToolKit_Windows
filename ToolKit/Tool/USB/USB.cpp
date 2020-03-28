#include "Tool/Buffer/Array.h"
#include "USB.h"

#pragma comment(lib, "setupapi")

using namespace System::IO;
using namespace System::Buffer;

// Construct the usb with the Guid
USB::USB(String strVid, String strPid, const DeviceID iDeviceID) :m_UsbHandle(NULL),
m_DevicePath(_T("")),
m_DeviceID(iDeviceID),
m_UsbVid(strVid),
m_UsbPid(strPid),
m_Disposed(false)
{
	Initialize();
}

// Destruct the usb
USB::~USB()
{
	Destory();
}

// initialize the usb
USB::None USB::Initialize()
{

}

// release all the resource using by usb
USB::None USB::Destory()
{
	if (!GetDisposed())
	{
		SetDisposed(true);

		Close();
	}
}

// Set the timeout of the device
USB::BOOL USB::SetTimeOut(USBSize iTotalTimeout)
{
	COMMTIMEOUTS UsbTimeout;

	UsbTimeout.ReadIntervalTimeout = 0;
	UsbTimeout.ReadTotalTimeoutMultiplier = 0;
	UsbTimeout.ReadTotalTimeoutConstant = iTotalTimeout;

	UsbTimeout.WriteTotalTimeoutMultiplier = 0;
	UsbTimeout.WriteTotalTimeoutConstant = 0;

	if (::SetCommTimeouts(GetUsbHandle(), &UsbTimeout) == FALSE)
	{
		return false;
	}

	return true;
}

// Rebuild the vedor ID and product ID
USB::None USB::CreateVidPid(String strVid, String strPid, PVIDTable& vPVIDTable)
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


// Filtrate the current usb path by its' vid and pid
// After the enumerating,there is many usb path,so we need to find the correct one
String USB::Filtrate(UsbPathTable& vUsbPathTable)
{
	String strUsbPath = _T("");

	if (vUsbPathTable.empty())
	{
		return strUsbPath;
	}

	// Get the correct VID,PID
	PVIDTable vVidPidTable;
	CreateVidPid(GetVid(), GetPid(), vVidPidTable);

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

// Enum all the usb devices
USB::Device USB::EnumDevices(DeviceID iDeviceID)
{
	Device device = ::SetupDiGetClassDevs(&iDeviceID, 
		NULL, 
		NULL, 
		DIGCF_PRESENT | DIGCF_DEVICEINTERFACE);
	if (device == INVALID_HANDLE_VALUE)
	{
		return NULL;
	}

	return device;
}

// create the interface detail struct to have the info of interface
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

// Destory the applyed interface detail struct
USB::None USB::DestoryInterfaceDetail(PInterfaceDetailInfo interfaceDetail)
{
	::GlobalFree(interfaceDetail);
}

// Get the correct usb path that you want to operate
// This path is specail one on OS,it can symbol the usb you want to operate
String USB::AcquireDevicePath()
{
	// Enum the device
	Device device = EnumDevices(GetDeviceID());
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
		UInt32 nCount = 0;
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

// create the usb path(open the usb)
USB::BOOL USB::_CreateFile(String strUsbName, FileAttrEnum eFileAttribute)
{
	BOOL bSuccess = false;

	if (IsOpen())
	{
		bSuccess = true;

		return bSuccess;
	}

	SetUsbHandle(CreateFile(strUsbName.CStr(),
		FileAccess::READWRITE, 
		FileShare::SREADWRITE, 
		NULL, FileMode::OPEN, 
		eFileAttribute, NULL));
	if (GetUsbHandle() == INVALID_HANDLE_VALUE)
	{
		// Close the usb
		Close();

		return bSuccess;
	}

	bSuccess = true;

	return bSuccess;
}

// read write the endpoint of usb
USB::Size USB::_ReadWriteEndPoint(Command iUSbCommd, ByteArray pPackage, ArraySize pPackageSize)
{
	if (!IsOpen())
	{
		return 0;
	}

	Size dwBytes = 0;

	if (DeviceIoControl(GetUsbHandle(), 
		iUSbCommd, 
		pPackage, 
		pPackageSize, 
		pPackage, 
		pPackageSize,
		&dwBytes, 
		NULL) == FALSE)
	{
		return 0;
	}

	return dwBytes;
}

// Create a package buffer(please do remember to destory the memory if it is not used)
USB::ByteArray USB::CreateOnePackage(ArraySize iPackageSize)
{
	ByteArray pPack = new Byte[iPackageSize];

	memset(pPack, 0, iPackageSize);

	return pPack;
}

// Destory the buffer 
USB::None USB::DestoryPakcage(ByteArray pPackage)
{
	if (pPackage)
	{
		delete[] pPackage;

		pPackage = NULL;
	}
}

// setup the transfer buffer's head(this step is neccesory for any transfering to usb)
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

// Setup the transfering buffer's data section(we need to create a new package with correct head and user buffer data)
USB::None USB::SetupTransPackage(ByteArray pPackage,
	PHeadPackage pHead,
	ByteArray pTransferBuffer,
	ArraySize iTransferSize)
{
	// Refer to the transfer buffer position
	ByteArray pBuffer = pPackage + pHead->BufferOffset;

	// Fill the buffer section
	Array<Byte>::Copy(pTransferBuffer, iTransferSize, pBuffer, iTransferSize);
}

// Is usb opened
USB::BOOL USB::IsOpen()
{
	if (GetUsbHandle())
	{
		return true;
	}

	return false;
}

// Open the usb
USB::BOOL USB::Open()
{
	// Get the usb path
	String strUsbPath = AcquireDevicePath();
	if (strUsbPath == _T(""))
	{
		return false;
	}

	// Create the usb file
	if (!_CreateFile(strUsbPath, FileAttrEnum::NORMAL))
	{
		return false;
	}

	// Set the usb time out 50ms
	if (!SetTimeOut(USBTimeOut::TIMEOUT))
	{
		return false;
	}

	return true;
}

// Config the usb so that usb can communicate with the client
USB::BOOL USB::Configure(Target eTarget,
	Direction eDirection,
	RequestType eReqType,
	RequestCode iCode,
	Value iValue,
	Index iIndex)
{
	if (!IsOpen())
	{
		return false;
	}

	// Get buffer size(buffer data size of the endpoint 0 is 64)
	Int32 iBufferSize = sizeof(HeadPackage) + DeviceConfiguration::USB_ENP0_TRANSFER_SIZE;

	Array<Byte> Buffer(iBufferSize);

	// Fill the buffer's head
	ByteArray pBuffer = Buffer.Data();
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
	FixedUInt32 dwBytes = 0;
	if (DeviceIoControl(GetUsbHandle(),
		UsbCommand::SENDRECEIVE_EP0,
		Buffer.Data(),
		iBufferSize,
		Buffer.Data(),
		iBufferSize,
		&dwBytes,
		NULL) == TRUE)
	{
		return true;
	}

	return false;
}

// Read the usb
USB::Size USB::Read(ByteArray pReadArray, Offset iOffset, ArraySize iReadSize)
{
	if (pReadArray == NULL || iOffset < 0 || iReadSize <= 0)
	{
		return 0;
	}

	if (!IsOpen())
	{
		return 0;
	}

	// Create a package that contains head and transfering array
	ArraySize iPackageSize = sizeof(HeadPackage) + iReadSize;

	Array<Byte> PacketBuffer(iPackageSize);

	// Setup the package head
	PHeadPackage head = SetupHeadPackage(PacketBuffer.Data(), EndPoint::USB_INPOINT, 0, sizeof(HeadPackage), iReadSize);

	// Set the package with transferring array
	SetupTransPackage(PacketBuffer.Data(), head, pReadArray, iReadSize);

	// Read data from the usb through read in endpoint
	Size dwReadSize = _ReadWriteEndPoint(UsbCommand::SENDRECEIVE_NONE_ENP0, PacketBuffer.Data(), PacketBuffer.Size());
	if (dwReadSize == 0)
	{
		return dwReadSize;
	}

	// Get the data section size
	dwReadSize = dwReadSize - sizeof(HeadPackage);

	// Copy the return data to the outside
	Array<Byte>::Copy(PacketBuffer.Data() + sizeof(HeadPackage), dwReadSize, pReadArray + iOffset, dwReadSize);

	return dwReadSize;
}

// Write to the usb 
USB::Size USB::Write(ByteArray pWriteArray, Offset iOffset, ArraySize iWriteSize)
{
	if (pWriteArray == NULL || iOffset < 0 || iWriteSize <= 0)
	{
		return 0;
	}

	if (!IsOpen())
	{
		return 0;
	}

	// Create a package that contains head and transfering array
	ArraySize iPackageSize = sizeof(HeadPackage) + iWriteSize;

	Array<Byte> PacketBuffer(iPackageSize);

	// Setup the package head
	PHeadPackage PacketHead = SetupHeadPackage(PacketBuffer.Data(), EndPoint::USB_OUTPOINT, 0, sizeof(HeadPackage), iWriteSize);

	// Set the package with transferring array
	SetupTransPackage(PacketBuffer.Data(), PacketHead, pWriteArray, iWriteSize);

	// Write data to the usb through out endpoint
	Size dwWriteSize = _ReadWriteEndPoint(UsbCommand::SENDRECEIVE_NONE_ENP0, PacketBuffer.Data(), PacketBuffer.Size());

	return dwWriteSize;
}

// Close the usb
USB::None USB::Close()
{
	if (GetUsbHandle())
	{
		::CloseHandle(GetUsbHandle());

		SetUsbHandle(NULL);
	}
}