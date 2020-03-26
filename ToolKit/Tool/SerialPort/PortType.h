///************************************************************************
/// <copyrigth>Voice AI Technology Of ShenZhen</copyrigth>
/// <author>tangyingzhong</author>
/// <contact>yingzhong@voiceaitech.com</contact>
/// <version>v1.0.0</version>
/// <describe>
/// Serial port's type
///</describe>
/// <date>2019/7/16</date>
///***********************************************************************
#ifndef PORT_TYPE_H
#define PORT_TYPE_H

#include "Tool/Common/SystemType.h"

namespace System
{
	namespace IO
	{
		// The baund rate of the port
		enum BOUNDRATE_ENUM
		{
			// Port's transferring speed: Low
			PORT_LOW_SPEED = 9600,

			// Port's transferring speed: High
			PORT_HIGH_SPEED = 14400,

			// Port's transferring speed: Super
			PORT_SUPER_SPEED = 115200
		};

		// Bits of one data of the port 
		enum DATABIT_ENUM
		{
			// Port's transferring length of one character: 8
			PORT_EIGHT = 8,

			// Port's transferring length of one character: 16
			PORT_SIXTEEN = 16
		};

		// Check bits of the port
		enum PARITY_ENUM
		{
			// Port's parity checking,No
			PORT_NO = 0,

			// Port's odd parity checking
			PORT_ODD = 1,

			// Port's even parity checking		
			PORT_EVEN = 2
		};

		// Stop bits of the port
		enum STOPBIT_ENUM
		{
			// Port's transferring ending bits width:0
			PORT_ONE = 0,

			// Port's transferring ending bits width:1
			PORT_HALF = 1,

			// Port's transferring ending bits width:2
			PORT_TWO = 2
		};

		// Timeout of the port
		enum PORT_TIMEOUT_ENUM
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
		};

		// Cache for the port transferring
		enum PORT_CACHE_ENUM
		{
			// Input cache for the port
			PORT_INPUT_CACHE_SIZE = 1024,

			// Output cache for the port
			PORT_OUTPUT_CACHE_SIZE = 1024
		};

		// Port's cache status
		enum PORT_CACHE_STATE_ENUM
		{
			// Abort the tx
			ABORTTX = PURGE_TXABORT,

			// Abort the rx
			ABORTRX = PURGE_RXABORT,

			// Clear the tx cache
			CLEARTX = PURGE_TXCLEAR,

			// Clear the rx cache
			CLEARRX = PURGE_RXCLEAR
		};
	}
}

#endif // PORT_TYPE_H