///************************************************************************
/// <copyrigth>2018-2019 Corporation.All Rights Reserved</copyrigth>
/// <author>tangyingzhong</author>
/// <contact>tangyz114987@outlook.com</contact>
/// <version>v1.0.0</version>
/// <describe>
/// Window USB operation supported here
///</describe>
/// <date>2019/7/16</date>
///***********************************************************************
#ifndef USB_H
#define USB_H

#include <SetupAPI.h>
#include "USBType.h"
#include "Tool/BaseType/String.h"

using namespace System::BasicType;

namespace System
{
	namespace IO
	{
		class USB
		{
		public:
			typedef System::Int32 Value;
			typedef System::Int32 Index;
			typedef System::Int32 RequestCode;
			typedef System::None None;
			typedef System::Boolean BOOL;
			typedef TARGET_ENUM Target;
			typedef DIRECTION_ENUM Direction;
			typedef REQUEST_TYPE_ENUM RequestType;
			typedef USB_TIMEOUT_ENUM USBTimeOut;
			typedef END_POINT_ENUM EndPoint;
			typedef USB_CMD_ENUM UsbCommand;
			typedef DEVICE_CONFIG_ENUM DeviceConfiguration;
			typedef System::Int32 USBSize;
			typedef System::Int32 ArraySize;
			typedef System::Int32 Offset;
			typedef System::Int32 Length;
			typedef System::Int32 Command;
			typedef System::FixedUInt32 Size;
			typedef System::ByteArray ByteArray;
			typedef System::Object UsbHandle;
			typedef System::FILE_MODE_ENUM FileMode;
			typedef System::FILE_ACCESS_ENUM FileAccess;
			typedef System::FILE_SHARE_ENUM FileShare;
			typedef System::SEEK_ORIGIN_ENUM SeekOrigin;
			typedef System::FILE_ATTRIBUTE_ENUM FileAttrEnum;
			typedef System::FileAttribute FileAttribute;
			typedef std::vector<String> PVIDTable;
			typedef std::vector<String> UsbPathTable;
			typedef GUID DeviceID;
			typedef HDEVINFO Device;
			typedef SINGLE_TRANSFER HeadPackage;
			typedef PSINGLE_TRANSFER PHeadPackage;
			typedef SP_DEVICE_INTERFACE_DATA InterfaceInfo;
			typedef SP_DEVICE_INTERFACE_DETAIL_DATA InterfaceDetailInfo;
			typedef PSP_DEVICE_INTERFACE_DETAIL_DATA PInterfaceDetailInfo;

		public:
			// Construct the usb with the Guid
			USB(String strVid = _T("0547"),
				String strPid = _T("1005"),
				const DeviceID DeviceID = { 0xAE18AA60, 0x7F6A, 0x11D4, 0x97, 0xDD, 0x00, 0x01, 0x02, 0x29, 0xb9, 0x59 }
			);

			// Destruct the usb
			~USB();

		private:
			// Copy the usb
			USB(const USB& other) {	}

			// Assginment of usb
			USB& operator=(const USB& other) {	}

		public:
			// Is usb opened
			virtual BOOL IsOpen();

			// Open the usb
			virtual BOOL Open();

			// Init the usb config
			virtual BOOL Configure(Target eTarget,
				Direction eDirection,
				RequestType eReqType,
				RequestCode iCode,
				Value iValue,
				Index iIndex);

			// Read the usb
			virtual Size Read(ByteArray pReadArray, Offset iOffset, ArraySize iReadSize);

			// Write to the usb
			virtual Size Write(ByteArray pWriteArray, Offset iOffset, ArraySize iWriteSize);

			// Close the usb
			virtual None Close();

		private:
			// Init the usb
			None Initialize();

			// Destory the usb
			None Destory();

			// Search for the usb device path
			String AcquireDevicePath();

			// Create the File
			BOOL _CreateFile(String strUsbName, FileAttrEnum eFileAttribute);

			// Create a package that contains head and transfering array
			ByteArray CreateOnePackage(ArraySize iPackageSize);

			// Destory the package
			None DestoryPakcage(ByteArray pPackage);

			// Setup the package head
			PHeadPackage SetupHeadPackage(ByteArray pPackage,
				EndPoint cEndPoint,
				Length iIsoPackageLength,
				Offset iHeadOffset,
				ArraySize iTransferSize);

			// Set the package with transferring array
			None SetupTransPackage(ByteArray pPackage,
				PHeadPackage pHead,
				ByteArray pTransferBuffer,
				ArraySize iTransferSize);

			// Read data from the usb through read in endpoint
			Size _ReadWriteEndPoint(Command iUSbCommd, ByteArray pPackage, ArraySize pPackageSize);

			// Filtrate the usb path
			String Filtrate(UsbPathTable& vUsbPathTable);

			// Enum all devices by the sepecail GUID
			Device EnumDevices(DeviceID iDeviceID);

			// Create device interface detail
			PInterfaceDetailInfo CreateInterfaceDetail(USBSize iSize);

			// Destory the interface detail
			None DestoryInterfaceDetail(PInterfaceDetailInfo interfaceDetail);

			// Set the timeout of the device
			BOOL SetTimeOut(USBSize iTotalTimeout);

			// Rebuild the vedor ID and product ID
			None CreateVidPid(String strVid, String strPid, PVIDTable& vPVIDTable);

		private:
			// Get the UsbHandle
			inline UsbHandle GetUsbHandle() const
			{
				return m_UsbHandle;
			}

			// Set the UsbHandle
			inline None SetUsbHandle(UsbHandle hUsbHandle)
			{
				m_UsbHandle = hUsbHandle;
			}

			// Get the Path
			inline String GetDevicePath() const
			{
				return m_DevicePath;
			}

			// Set the Path
			inline None SetDevicePath(String strDevicePath)
			{
				m_DevicePath = strDevicePath;
			}

			// Get the DeviceID
			inline DeviceID GetDeviceID() const
			{
				return m_DeviceID;
			}

			// Set the DeviceID
			inline None SetDeviceID(DeviceID iDeviceID)
			{
				m_DeviceID = iDeviceID;
			}

			// Get the Vid
			inline String GetVid() const
			{
				return m_UsbVid;
			}

			// Set the Vid
			inline None SetVid(String strUsbVid)
			{
				m_UsbVid = strUsbVid;
			}

			// Get the Pid
			inline String GetPid() const
			{
				return m_UsbPid;
			}

			// Set the Pid
			inline None SetPid(String strUsbPid)
			{
				m_UsbPid = strUsbPid;
			}

			// Get the Disposed
			inline BOOL GetDisposed() const
			{
				return m_Disposed;
			}

			// Set the Disposed
			inline None SetDisposed(BOOL bDisposed)
			{
				m_Disposed = bDisposed;
			}

		private:
			// The handle of usb
			UsbHandle m_UsbHandle;

			// The path of the device
			String m_DevicePath;

			// The id of device
			DeviceID m_DeviceID;

			// Vendor ID 
			String m_UsbVid;

			// Product ID
			String m_UsbPid;

			// Dispose status 
			BOOL m_Disposed;

		};
	}
}
#endif // USB_H