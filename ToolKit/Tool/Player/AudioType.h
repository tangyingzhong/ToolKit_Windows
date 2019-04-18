///************************************************************************
/// <copyrigth>2018-2019 Corporation.All Rights Reserved</copyrigth>
/// <author>tangyingzhong</author>
/// <contact>tangyz114987@outlook.com</contact>
/// <version>V1.0.0</version>
/// <describe>
/// It contains some types for the  player
///</describe>
/// <date>2019/3/6</date>
///***********************************************************************
#ifndef AUDIOTYPE_H
#define AUDIOTYPE_H

#include "Tool\Common\SystemType.h"

namespace System
{
	namespace MultiMedia
	{
		// Audio coding format
		typedef enum _CodingFormat
		{
			PLAYER_WAVE_FORMAT_PCM_F = WAVE_FORMAT_PCM						// Audio's coding format is PCM 
		}CodingFormat;

		// Audio channels
		typedef enum _Channel
		{
			PLAYER_SINGLE = 1,												// Sample channel is single 
			PLAYER_DOUBLE = 2												// Sample channel is double
		}Channel;

		// Audio sample point's width
		typedef enum _BitWidth
		{
			PLAYER_EIGHT = 8,												// Sample point's bit width : 8
			PLAYER_SIXTEE = 16												// Sample point's bit width : 16
		}BitWidth;

		// Audio sample frequency
		typedef enum _SampleFreq
		{
			PLAYER_LOW = 11025,												// Low sample frequency
			PLAYER_MIDDLE = 22050,											// Middle sample frequency
			PLAYER_HIGH = 44100,											// High sample frequency
			PLAYER_SUPER = 48000											// Super sample frequency
		}SampleFreq;

		// The head of audio file (total 44 bytes)
		typedef struct _AudioHeader
		{
			Byte head[4];													// It must be "RIFF"----- (4 bytes)
			UInt32 structSize;												// The size of this struct=44 -8 -----(4 bytes)
			Byte waveType[4];												// It must be "WAVE" -----(4 bytes)
			Byte formatString[4];											// It must be "fmt "----- (4 bytes)
			UInt32 size1;													// Size1=16 -----(4 bytes)
			UInt16 codingFormat;											// The coding format of audio=1 -----(2 bytes)
			UInt16 channel;													// The channel of audio -----(2 bytes)
			UInt32 sampleRate;												// The sample frequency of audio -----(4 bytes)
			UInt32 avgByteRate;												// The total bytes of one second -----(4 bytes)
			UInt16 blockAlign;												// The total bytes of one sample, the value can be got by (channel*bitPerSample)/8  ------(2 bytes)
			UInt16 bitPerSample;											// The total bits of one sample,8,16.----- (2 bytes)	
			Byte flag[4];													// Constant string "data" -----(4 bytes)
			UInt32 size2;													// It is not including the head size of the file -----(4 bytes)
		}AudioHeader;

		// Audio's enum
		typedef enum _AudioEnum
		{
			BLOCK_NUM = 20,													// The total count of cache
			BLOCK_SIZE = 500,												// The size of a block
			AUDIO_HEAD_SIZE = 44,											// The head size of audio file ,which contains audio config info.
			AUDIOFILE_BLOCK_SIZE = 600,										// The file block size of every reading
		}AudioEnum;

		// Audio play status
		typedef enum _PlayStatus
		{
			PLAYER_NOT_START = 0,											// Not start to play
			PLAYER_STOP,													// Stop the current playing
			PLAYER_PAUSE,													// Pause the play but can play again here
			PLAYER_CONTINUE													// continue palying at the position
		}PlayStatus;

		typedef WAVEHDR* CacheBlock;
		typedef WAVEHDR BlockHead;

		// Audio's head
		typedef struct _AudioHeadBlock
		{
			CacheBlock block[BLOCK_NUM];									// This is the head blocks of device
			ByteArray userBlock[BLOCK_NUM];									// This is a head block's user data section
		}AudioHeadBlock;
	}
}

#endif//!AUDIOTYPE_H_