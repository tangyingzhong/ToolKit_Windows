///************************************************************************
/// <copyrigth>emperor electric technology of ShenZhen</copyrigth>
/// <author>tangyingzhong</author>
/// <contact>tangyz114987@outlook.com</contact>
/// <version>v1.0.0</version>
/// <describe>
/// Offer the common interfaces of players
/// </describe>
/// <date>2018/1/17</date>
///***********************************************************************
#ifndef IBLOCKPLAYER_H
#define IBLOCKPLAYER_H

#include "AudioType.h"
#include "Tool/BaseType/String.h"

using namespace System;
using namespace System::BasicType;

namespace System
{
	namespace MultiMedia
	{
		class IBlockPlayer
		{
		public:
			// Detructe the IPlayer
			virtual ~IBlockPlayer(){		}

		public:
			// Open the player,it is suitable to the play piece data
			virtual Boolean Open() = 0;

			// Start the player with piece data,but you have to open the device with format and channel, etc.
			virtual Boolean Play(SByteArray pBlock, Int32 iBlockSize) = 0;

			// Pause the player
			virtual Boolean Pause() = 0;

			// Continue the playing
			virtual Boolean Continue() = 0;

			// Stop the player
			virtual Boolean Stop() = 0;

		};
	}
}

#endif // IBLOCKPLAYER_H