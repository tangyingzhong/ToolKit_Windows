///************************************************************************
/// <copyrigth>2018-2019 Corporation.All Rights Reserved</copyrigth>
/// <author>tangyingzhong</author>
/// <contact>tangyz114987@outlook.com</contact>
/// <version>v1.0.0</version>
/// <describe>
/// USB paramenters needing 
///</describe>
/// <date>2019/7/16</date>
///***********************************************************************
#ifndef USBTYPE_H
#define USBTYPE_H

#include "cyioctl.h"
#include "Tool/Common/SystemType.h"

namespace System
{
	namespace IO
	{
		// Time out of the usb
		enum USB_TIMEOUT_ENUM
		{
			// The time out of the USB
			TIMEOUT = 10																
		};

		// USB device's configuration
		enum DEVICE_CONFIG_ENUM
		{
			// Supported max devices' number
			USB_MAXDEVICE = 127,	

			// Transfer size of the endpoint 0
			USB_ENP0_TRANSFER_SIZE = 64									
		};

		// USB endpoint address
		enum END_POINT_ENUM
		{
			// Endpoint address of the endpoint 0
			USB_CONTRL = 0x00,													

			// Endpoint address of the input endpoint
			USB_INPOINT = 0x81,													

			// Endpoint address of the output endpoint
			USB_OUTPOINT = 0x01													
		};

		// USB target
		enum TARGET_ENUM
		{
			// USB device
			USB_DEVICE = 0,															

			// USB interfaces of the windows enumeration
			USB_INTERFACE,															

			// USB endpoints
			USB_ENDPOINT,															

			// Others
			OTHER																			
		};

		// USB request type
		enum REQUEST_TYPE_ENUM
		{
			// Standart request
			STANDARD = 0,														

			// Class request
			CLASS,																			

			// Vendor request
			VENDOR																		
		};

		//USB transfer direction
		enum DIRECTION_ENUM
		{
			// Host to device
			TO_DEVICE = 0,															

			// Device to host
			FROM_DEVICE																
		};

		enum USB_CMD_ENUM
		{
			// Send to endpoint 0 or receive from it
			SENDRECEIVE_EP0 = IOCTL_ADAPT_SEND_EP0_CONTROL_TRANSFER,					

			// Send to the other endpoint(not endpoint 0)  or receive from it
			SENDRECEIVE_NONE_ENP0 = IOCTL_ADAPT_SEND_NON_EP0_TRANSFER,	

			// Send to the other endpoint(not endpoint 0)  or receive from it  <there is no send or receive cache >
			SENDRECEIVE_NONE_ENP0_DIRECT = IOCTL_ADAPT_SEND_NON_EP0_DIRECT,		

			// Get device version
			GET_DRIVER_VERSION = IOCTL_ADAPT_GET_DRIVER_VERSION,							

			// Get interface's information
			GET_INTERFACE_SETTING = IOCTL_ADAPT_GET_ALT_INTERFACE_SETTING,			

			// Get device address
			GET_DEVICE_ADDR = IOCTL_ADAPT_GET_ADDRESS,												

			// Get the count of endpoint
			GET_ENP_COUNT = IOCTL_ADAPT_GET_NUMBER_ENDPOINTS,							

			// Get the power state of usb
			GET_POWER_STATE = IOCTL_ADAPT_GET_DEVICE_POWER_STATE,						

			// Set the power state of usb
			SET_POWER_STATE = IOCTL_ADAPT_SET_DEVICE_POWER_STATE,							

			// Test the usb's connection or disconnection
			TEST_CONNECT = IOCTL_ADAPT_CYCLE_PORT,														

			// Reset the pipe
			RESET_PIPE = IOCTL_ADAPT_RESET_PIPE,																

			// Reset the device 
			RESET_DEVICE = IOCTL_ADAPT_RESET_PARENT_PORT,											

			// Get the endpoint's transfer size
			GET_ENP_SIZE = IOCTL_ADAPT_GET_TRANSFER_SIZE,											

			// Set the endpoint's transfer size
			SET_ENP_SIZE = IOCTL_ADAPT_SET_TRANSFER_SIZE,	

			// Get the name of device
			GET_DEVICE_NAME = IOCTL_ADAPT_GET_DEVICE_NAME,										

			// Get the device's friendly name
			GET_FRIENDLY_NAME = IOCTL_ADAPT_GET_FRIENDLY_NAME,								

			// Abort the running pipe
			ABORT_PIPE = IOCTL_ADAPT_ABORT_PIPE,															

			// Get the device speed
			GET_DEVICE_SPEED = IOCTL_ADAPT_GET_DEVICE_SPEED,										

			// Get the device current frame
			GET_CURRENT_FRAME = IOCTL_ADAPT_GET_CURRENT_FRAME,							
		};

		// One transferring paras
		struct SingleTranfer
		{
			// The command of USB operation
			Int32 iCommond;																									

			// The address of one point
			Byte cEndPointAddress;																							

			// The array of transfer to the USB
			ByteArray pTransferArray;																						

			// The size of transfer array
			Int32 iArraySize;																									

			// The offfset of the array head
			Int32 iPackageHeadOffset;																				

			// Output size
			Int32 iOutSize;																									
		};

		// USB device descriptor
		struct UsbDeviceDescriptor
		{
			// The length of the descriptor(0x12)
			Byte cLength;																										

			// The type of the decriptor(0x01)
			Byte cDescriptorType;																							

			// Usb version(BCD code)£¬version 2.0 £º0200
			UInt16 iBcdUsb;	

			// Class code(1-0xFE). for example,0x03£ºHID device  0x0£ºusb interfaces are independent ,they are belong to different devices    0xFF£ºself define by product
			Byte cDeviceClass;							

			// Sub class code(if deviceClass=0x04£¬then 0x01£ºCRT display, 0x02£ºplat display 0x03:3D display)
			Byte cDeviceSubClass;																							

			// Protocol code(0x0£ºnot use any protocol  0xFF£ºproductor prividing)
			Byte cDeviceProtocol;							

			// The max package size(byte) supported by endpoint 0£¨low£º8  full£º8,16,32,64 high£º64£©
			Byte cMaxPacketSize;											

			// Provider id
			UInt16 iVid;				

			// Productor id
			UInt16 iPid;		

			// Set by productor
			UInt16 iBcdDevice;								
			
			// The indx of string decriptor(you can find the string descriptor by this index)
			Byte cStringDescriptorIndex;							

			// Product descriptor index in string descriptor
			Byte cProductIndex;																								

			// Serial number in the string descriptor 's index
			Byte cSerialNumberIndex;					

			// The number of supporting configuration
			Byte cNumConfigurations;

			// Not use£¨0x00£©
			Byte cReserve;																										
		};

		// USB configuration descriptor
		struct UsbConfigurationDescriptor
		{
			// The length of the descriptor(0x09) 
			Byte cLength;																										

			// The type of the decriptor(0x02)
			Byte cDescriptorType;																							

			// The total size of all descriptor
			UInt16 iTotalLength;		

			// The number of support interface
			Byte cNumInterfaces;																						

			// Value of configuration
			Byte cConfigValue;																								

			// String descriptor's index(if none,set to 0)
			Byte cConfiguration;							

			// It has different meanings of every bit(0-4£ºset to 0  5£ºsupport wake up  6£ºbus power 7£ºset to 1)
			Byte cAttributes;																

			// The max power electric(value£º2-500 mA), you should set it to 1-250,,because of it unit is 2 mA
			Byte cMaxPower;																									
		};

		// USB interface descriptor
		struct UsbInterfaceDescriptor
		{
			// The length of the descriptor(0x09) 
			Byte cLength;																									

			// The type of the decriptor(0x04)
			Byte cDescriptorType;																						

			// The no. of the interface
			Byte cInterfaceNum;																								

			// Standby interface descriptor id
			Byte cAlternateSetting;																			

			// The number of endpoint ,not include the endpoint 0
			Byte cNumEndpoints;																							

			// Class code
			Byte cInterfaceClass;																								

			// Sub class code
			Byte cInterfaceSubClass;																						

			// Protocol code
			Byte cInterfaceProtocol;																					

			// String descriptor's index
			Byte cStringDescriptorIndex;																				
		};

		// USB endpoint descriptor
		struct UsbEndpointDescriptor
		{
			// The length of the descriptor(0x07)
			Byte cLength;																										

			// The type of the decriptor(0x05)
			Byte cDescriptorType;																							

			// The address of endpoint
			Byte cEndpointAddress;		

			// The attribute of endpoint(the 0 adn 1 bit represent the type of transferring. 00£ºcontrol   01£ºsynchronous  10£ºbulk  11£ºinterrupt)
			Byte cAttributes;			

			// The max package size of endpoint's transferring(0-10£ºthe size of transferring  11-12£ºmin frame's max transfer num, 13-15£ºset to 0)
			UInt16 iMaxPacketSize;		

			// The interval of access the endpoint(ms)
			Byte cInterval;																									
		};

		// USB string descriptor
		struct UsbStringDescriptor
		{
			// The length of the descriptor
			Byte cLength;																									

			// The type of the decriptor(0x03)
			Byte cDescriptorType;					

			// Unicode string
			Byte cStr[1];																											
		};

		// USB common descriptor
		struct UsbCommonDescriptor
		{
			// The length of the descriptor 
			Byte cLength;																									

			// The type of the decriptor(0x03)
			Byte cDescriptorType;																						
		};
	}
}

#endif // USBTYPE_H