///************************************************************************
/// <copyrigth>emperor electric technology of ShenZhen</copyrigth>
/// <author>tangyingzhong</author>
/// <contact>tangyz114987@outlook.com</contact>
/// <version>v1.0.0</version>
/// <describe>
/// Play the wave file
/// </describe>
/// <date>2018/1/18</date>
///***********************************************************************
#ifndef IAUDIOPLAYER_H
#define IAUDIOPLAYER_H

#include "AudioType.h"
#include "Tool/BaseType/String.h"

using namespace System;
using namespace System::BasicType;

namespace System
{
	namespace MultiMedia
	{
		class IAudioPlayer
		{
		public:
			// Detructe the IAudioPlayer
			virtual ~IAudioPlayer(){		}

		public:
			// Start the player
			virtual Boolean Play(String strFileName) = 0;

			// Pause the player
			virtual Boolean Pause() = 0;

			// Continue the playing
			virtual Boolean Continue() = 0;

			// Stop the player
			virtual Boolean Stop() = 0;
		};
	}
}

#endif // IAUDIOPLAYER_H