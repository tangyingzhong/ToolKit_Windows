///************************************************************************
/// <copyrigth>2018-2019 Corporation.All Rights Reserved</copyrigth>
/// <author>tangyingzhong</author>
/// <contact>tangyz114987@outlook.com</contact>
/// <version>v1.0.0</version>
/// <describe>
/// It contains some types for the  player
///</describe>
/// <date>2019/7/16</date>
///***********************************************************************
#ifndef AUDIOTYPE_H
#define AUDIOTYPE_H

#include <Windows.h>
#include "Tool/Common/SystemType.h"

namespace System
{
	namespace MultiMedia
	{
		// Audio coding format
		enum CODING_FORMAT_ENUM
		{
			// Audio's coding format is PCM 
			PLAYER_WAVE_FORMAT_PCM_F = WAVE_FORMAT_PCM						
		};

		// Audio channels
		enum CHANNEL_ENUM
		{
			// Sample channel is single
			PLAYER_SINGLE = 1,							

			// Sample channel is double
			PLAYER_DOUBLE = 2																		
		};

		// Audio sample point's width
		enum BITWIDTH_ENUM
		{
			// Sample point's bit width : 8
			PLAYER_EIGHT = 8,							

			// Sample point's bit width : 16
			PLAYER_SIXTEE = 16																				
		};

		// Audio sample frequency
		enum SAMPLE_FREQ_ENUM
		{
			// Low sample frequency
			PLAYER_LOW = 11025,				

			// Middle sample frequency
			PLAYER_MIDDLE = 22050,						

			// High sample frequency
			PLAYER_HIGH = 44100,					

			// Super sample frequency
			PLAYER_SUPER = 48000																		
		};

		// The head of audio file (total 44 bytes)
		struct AudioHeader
		{
			// It must be "RIFF"----- (4 bytes)
			Byte head[4];						

			// The size of this struct=44 -8 -----(4 bytes)
			UInt32 structSize;			

			// It must be "WAVE" -----(4 bytes)
			Byte waveType[4];		

			// It must be "fmt "----- (4 bytes)
			Byte formatString[4];				

			// Size1=16 -----(4 bytes)
			UInt32 size1;												

			// The coding format of audio=1 -----(2 bytes)
			UInt16 codingFormat;			

			// The channel of audio -----(2 bytes)
			UInt16 channel;							

			// The sample frequency of audio -----(4 bytes)
			UInt32 sampleRate;				

			// The total bytes of one second -----(4 bytes)
			UInt32 avgByteRate;		

			// The total bytes of one sample, the value can be got by (channel*bitPerSample)/8  ------(2 bytes)
			UInt16 blockAlign;								

			// The total bits of one sample,8,16.----- (2 bytes)	
			UInt16 bitPerSample;

			// Constant string "data" -----(4 bytes)
			Byte flag[4];				

			// It is not including the head size of the file -----(4 bytes)
			UInt32 size2;																							
		};

		// Audio's enum
		enum AUDIO_ENUM
		{
			// The total count of cache
			BLOCK_NUM = 20,														

			// The size of a block
			BLOCK_SIZE = 500,		

			// The head size of audio file ,which contains audio config info.
			AUDIO_HEAD_SIZE = 44,											

			// The file block size of every reading
			AUDIOFILE_BLOCK_SIZE = 600,																
		};

		// Audio play status
		enum PLAY_STATE_ENUM
		{
			// Not start to play
			PLAYER_NOT_START = 0,			

			// Stop the current playing
			PLAYER_STOP,					

			// Pause the play but can play again here
			PLAYER_PAUSE,					

			// continue palying at the position
			PLAYER_CONTINUE																				
		};
		
		typedef WAVEHDR BlockHead;

		typedef BlockHead* CacheBlock;

		// Audio's head
		struct AudioHeadBlock
		{
			// This is the head blocks of device
			CacheBlock block[BLOCK_NUM];	

			// This is a head block's user data section
			ByteArray userBlock[BLOCK_NUM];														
		};
	}
}

#endif// AUDIOTYPE_H