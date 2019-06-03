///************************************************************************
/// <copyrigth>2018-2019 Corporation.All Rights Reserved</copyrigth>
/// <author>tangyingzhong</author>
/// <contact>tangyz114987@outlook.com</contact>
/// <version>V1.0.0</version>
/// <describe>
/// USB paramenters needing 
///</describe>
/// <date>2019/3/7</date>
///***********************************************************************
#ifndef USBTYPE_H
#define USBTYPE_H

#include "cyioctl.h"
#include "Tool\Common\SystemType.h"

namespace System
{
	namespace USB
	{
		// Time out of the usb
		typedef enum _USBTimeOut
		{
			TIMEOUT = 10														// The time out of the USB
		}USBTimeOut;

		// USB device's configuration
		typedef enum _DeviceConfiguration
		{
			USB_MAXDEVICE = 127,												// Supported max devices' number
			USB_ENP0_TRANSFER_SIZE = 64											// Transfer size of the endpoint 0
		}DeviceConfiguration;

		// USB endpoint address
		typedef enum _EndPoint
		{
			USB_CONTRL = 0x00,													// Endpoint address of the endpoint 0
			USB_INPOINT = 0x81,													// Endpoint address of the input endpoint
			USB_OUTPOINT = 0x01													// Endpoint address of the output endpoint
		}EndPoint;

		// USB target
		typedef enum _Target
		{
			USB_DEVICE = 0,														// USB device
			USB_INTERFACE,														// USB interfaces of the windows enumeration
			USB_ENDPOINT,														// USB endpoints
			OTHER																// Others
		}Target;

		// USB request type
		typedef enum _RequestType
		{
			STANDARD = 0,														// Standart request
			CLASS,																// Class request
			VENDOR																// Vendor request
		}RequestType;

		//USB transfer direction
		typedef enum _Direction
		{
			TO_DEVICE = 0,														// Host to device
			FROM_DEVICE															// Device to host
		}Direction;

		typedef enum
		{
			SENDRECEIVE_EP0 = IOCTL_ADAPT_SEND_EP0_CONTROL_TRANSFER,			// Send to endpoint 0 or receive from it
			SENDRECEIVE_NONE_ENP0 = IOCTL_ADAPT_SEND_NON_EP0_TRANSFER,			// Send to the other endpoint(not endpoint 0)  or receive from it
			SENDRECEIVE_NONE_ENP0_DIRECT = IOCTL_ADAPT_SEND_NON_EP0_DIRECT,		// Send to the other endpoint(not endpoint 0)  or receive from it  <there is no send or receive cache >
			GET_DRIVER_VERSION = IOCTL_ADAPT_GET_DRIVER_VERSION,				// Get device version
			GET_INTERFACE_SETTING = IOCTL_ADAPT_GET_ALT_INTERFACE_SETTING,		// Get interface's information
			GET_DEVICE_ADDR = IOCTL_ADAPT_GET_ADDRESS,							// Get device address
			GET_ENP_COUNT = IOCTL_ADAPT_GET_NUMBER_ENDPOINTS,					// Get the count of endpoint
			GET_POWER_STATE = IOCTL_ADAPT_GET_DEVICE_POWER_STATE,				// Get the power state of usb
			SET_POWER_STATE = IOCTL_ADAPT_SET_DEVICE_POWER_STATE,				// Set the power state of usb
			TEST_CONNECT = IOCTL_ADAPT_CYCLE_PORT,								// Test the usb's connection or disconnection
			RESET_PIPE = IOCTL_ADAPT_RESET_PIPE,								// Reset the pipe
			RESET_DEVICE = IOCTL_ADAPT_RESET_PARENT_PORT,						// Reset the device 
			GET_ENP_SIZE = IOCTL_ADAPT_GET_TRANSFER_SIZE,						// Get the endpoint's transfer size
			SET_ENP_SIZE = IOCTL_ADAPT_SET_TRANSFER_SIZE,						// Set the endpoint's transfer size
			GET_DEVICE_NAME = IOCTL_ADAPT_GET_DEVICE_NAME,						// Get the name of device
			GET_FRIENDLY_NAME = IOCTL_ADAPT_GET_FRIENDLY_NAME,					// Get the device's friendly name
			ABORT_PIPE = IOCTL_ADAPT_ABORT_PIPE,								// Abort the running pipe
			GET_DEVICE_SPEED = IOCTL_ADAPT_GET_DEVICE_SPEED,					// Get the device speed
			GET_CURRENT_FRAME = IOCTL_ADAPT_GET_CURRENT_FRAME,					// Get the device current frame
		}UsbCommand;

		// One transferring paras
		typedef struct
		{
			Int32 iCommond;														// The command of USB operation
			Byte cEndPointAddress;												// The address of one point
			ByteArray pTransferArray;											// The array of transfer to the USB
			Int32 iArraySize;													// The size of transfer array
			Int32 iPackageHeadOffset;											// The offfset of the array head
			Int32 iOutSize;														// Output size
		}SingleTranfer;

		// USB device descriptor
		typedef struct
		{
			Byte cLength;														// The length of the descriptor(0x12)
			Byte cDescriptorType;												// The type of the decriptor(0x01)
			UInt16 iBcdUsb;														// Usb version(BCD code)£¬version 2.0 £º0200
			Byte cDeviceClass;													// Class code(1-0xFE). for example,0x03£ºHID device  0x0£ºusb interfaces are independent ,they are belong to different devices    0xFF£ºself define by product
			Byte cDeviceSubClass;												// Sub class code(if deviceClass=0x04£¬then 0x01£ºCRT display, 0x02£ºplat display 0x03:3D display)
			Byte cDeviceProtocol;												// Protocol code(0x0£ºnot use any protocol  0xFF£ºproductor prividing)
			Byte cMaxPacketSize;												// The max package size(byte) supported by endpoint 0£¨low£º8  full£º8,16,32,64 high£º64£©
			UInt16 iVid;														// Provider id
			UInt16 iPid;														// Productor id
			UInt16 iBcdDevice;													// Set by productor
			Byte cStringDescriptorIndex;										// The indx of string decriptor(you can find the string descriptor by this index)
			Byte cProductIndex;													// Product descriptor index in string descriptor
			Byte cSerialNumberIndex;											// Serial number in the string descriptor 's index
			Byte cNumConfigurations;											// The number of supporting configuration	
			Byte cReserve;														// Not use£¨0x00£©
		}UsbDeviceDescriptor;

		// USB configuration descriptor
		typedef struct
		{
			Byte cLength;														// The length of the descriptor(0x09) 
			Byte cDescriptorType;												// The type of the decriptor(0x02)
			UInt16 iTotalLength;												// The total size of all descriptor
			Byte cNumInterfaces;												// The number of support interface
			Byte cConfigValue;													// Value of configuration
			Byte cConfiguration;												// String descriptor's index(if none,set to 0)
			Byte cAttributes;													// It has different meanings of every bit(0-4£ºset to 0  5£ºsupport wake up  6£ºbus power 7£ºset to 1)
			Byte cMaxPower;														// The max power electric(value£º2-500 mA), you should set it to 1-250,,because of it unit is 2 mA
		}UsbConfigurationDescriptor;

		// USB interface descriptor
		typedef struct
		{
			Byte cLength;														// The length of the descriptor(0x09) 
			Byte cDescriptorType;												// The type of the decriptor(0x04)
			Byte cInterfaceNum;													// The no. of the interface
			Byte cAlternateSetting;												// Standby interface descriptor id
			Byte cNumEndpoints;													// The number of endpoint ,not include the endpoint 0
			Byte cInterfaceClass;												// Class code
			Byte cInterfaceSubClass;											// Sub class code
			Byte cInterfaceProtocol;											// Protocol code
			Byte cStringDescriptorIndex;										// String descriptor's index
		}UsbInterfaceDescriptor;

		// USB endpoint descriptor
		typedef struct
		{
			Byte cLength;														// The length of the descriptor(0x07)
			Byte cDescriptorType;												// The type of the decriptor(0x05)
			Byte cEndpointAddress;												// The address of endpoint
			Byte cAttributes;													// The attribute of endpoint(the 0 adn 1 bit represent the type of transferring. 00£ºcontrol   01£ºsynchronous  10£ºbulk  11£ºinterrupt)
			UInt16 iMaxPacketSize;												// The max package size of endpoint's transferring(0-10£ºthe size of transferring  11-12£ºmin frame's max transfer num, 13-15£ºset to 0)
			Byte cInterval;														// The interval of access the endpoint(ms)
		}UsbEndpointDescriptor;

		// USB string descriptor
		typedef struct
		{
			Byte cLength;														// The length of the descriptor
			Byte cDescriptorType;												// The type of the decriptor(0x03)
			Byte cStr[1];														// Unicode string
		}UsbStringDescriptor;

		// USB common descriptor
		typedef struct
		{
			Byte cLength;														// The length of the descriptor 
			Byte cDescriptorType;												// The type of the decriptor(0x03)
		}UsbCommonDescriptor;
	}
}

#endif // USBTYPE_H