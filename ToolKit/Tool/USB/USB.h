///************************************************************************
/// <copyrigth>2018-2019 Corporation.All Rights Reserved</copyrigth>
/// <author>tangyingzhong</author>
/// <contact>tangyz114987@outlook.com</contact>
/// <version>V1.0.0</version>
/// <describe>
/// Window USB operation supported here
///</describe>
/// <date>2019/3/6</date>
///***********************************************************************
#ifndef USB_H
#define USB_H

#include <SetupAPI.h>
#include "USBType.h"
#include "Tool\BaseType\String.h"

using namespace System::BasicType;

namespace System
{
	namespace IO
	{
		///*********************************************************
		/// <class>USB</class>
		/// <summary>
		/// Open ,Close ,Read,Write,etc.
		/// </summary>
		/// <version>V1.0.0 </version>
		/// <goup> C++</group>
		/// <author>tangyingzhong</author>
		/// <contact>tangyingzhong@szangell.com</contact>
		///*********************************************************
		class USB
		{
		public:
			typedef System::Int32 Value;
			typedef System::Int32 Index;
			typedef System::Int32 RequestCode;
			typedef System::Empty Empty;
			typedef System::Boolean BOOL;
			typedef System::USB::Target Target;
			typedef System::USB::Direction Direction;
			typedef System::USB::RequestType RequestType;
			typedef System::USB::USBTimeOut USBTimeOut;
			typedef System::USB::EndPoint EndPoint;
			typedef System::USB::UsbCommand UsbCommand;
			typedef System::USB::DeviceConfiguration DeviceConfiguration;
			typedef System::Int32 USBSize;
			typedef System::Int32 ArraySize;
			typedef System::Int32 Offset;
			typedef System::Int32 Length;
			typedef System::Int32 Command;
			typedef System::UInt64 Size;
			typedef System::ByteArray ByteArray;
			typedef System::Object UsbHandle;
			typedef System::FileAttrEnum FileAttrEnum;
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
			USB(String strVid = _T("0547"), String strPid = _T("1005"), const DeviceID iDeviceID = { 0xAE18AA60, 0x7F6A, 0x11D4, 0x97, 0xDD, 0x00, 0x01, 0x02, 0x29, 0xb9, 0x59 });

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
			virtual BOOL Configure(Target eTarget, Direction eDirection, RequestType eReqType, RequestCode iCode, Value iValue, Index iIndex);

			// Read the usb
			virtual Size Read(ByteArray pReadArray, Offset iOffset, ArraySize iReadSize);

			// Write to the usb
			virtual Size Write(ByteArray pWriteArray, Offset iOffset, ArraySize iWriteSize);

			// Close the usb
			virtual Empty Close();

		private:
			// Init the usb
			Empty Initialize();

			// Destory the usb
			Empty Destory();

			// Search for the usb device path
			String AcquireDevicePath();

			// Create the File
			BOOL _CreateFile(String strUsbName, FileAttrEnum eFileAttribute);

			// Create a package that contains head and transfering array
			ByteArray CreateOnePackage(ArraySize iPackageSize);

			// Destory the package
			Empty DestoryPakcage(ByteArray pPackage);

			// Setup the package head
			PHeadPackage SetupHeadPackage(ByteArray pPackage, EndPoint cEndPoint, Length iIsoPackageLength, Offset iHeadOffset, ArraySize iTransferSize);

			// Set the package with transferring array
			Empty SetupTransPackage(ByteArray pPackage, PHeadPackage pHead, ByteArray pTransferBuffer, ArraySize iTransferSize);

			// Read data from the usb through read in endpoint
			Size _ReadWriteEndPoint(Command iUSbCommd, ByteArray pPackage, ArraySize pPackageSize);

			// Filtrate the usb path
			String Filtrate(UsbPathTable& vUsbPathTable);

			// Enum all devices by the sepecail GUID
			Device EnumDevices(DeviceID iDeviceID);

			// Create device interface detail
			PInterfaceDetailInfo CreateInterfaceDetail(USBSize iSize);

			// Destory the interface detail
			Empty DestoryInterfaceDetail(PInterfaceDetailInfo interfaceDetail);

			// Set the timeout of the device
			BOOL SetTimeOut(USBSize iTotalTimeout);

			// Rebuild the vedor ID and product ID
			Empty CreateVidPid(String strVid, String strPid, PVIDTable& vPVIDTable);

		private:
			// Get the UsbHandle
			inline UsbHandle GetUsbHandle() const
			{
				return m_UsbHandle;
			}

			// Set the UsbHandle
			inline Empty SetUsbHandle(UsbHandle hUsbHandle)
			{
				this->m_UsbHandle = hUsbHandle;
			}

			// Get the Path
			inline String GetDevicePath() const
			{
				return m_DevicePath;
			}

			// Set the Path
			inline Empty SetDevicePath(String strDevicePath)
			{
				this->m_DevicePath = strDevicePath;
			}

			// Get the DeviceID
			inline DeviceID GetDeviceID() const
			{
				return m_DeviceID;
			}

			// Set the DeviceID
			inline Empty SetDeviceID(DeviceID iDeviceID)
			{
				this->m_DeviceID = iDeviceID;
			}

			// Get the Vid
			inline String GetVid() const
			{
				return m_UsbVid;
			}

			// Set the Vid
			inline Empty SetVid(String strUsbVid)
			{
				this->m_UsbVid = strUsbVid;
			}

			// Get the Pid
			inline String GetPid() const
			{
				return m_UsbPid;
			}

			// Set the Pid
			inline Empty SetPid(String strUsbPid)
			{
				this->m_UsbPid = strUsbPid;
			}

			// Get the Disposed
			inline BOOL GetDisposed() const
			{
				return m_Disposed;
			}

			// Set the Disposed
			inline Empty SetDisposed(BOOL bDisposed)
			{
				this->m_Disposed = bDisposed;
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
#endif // !USB_H