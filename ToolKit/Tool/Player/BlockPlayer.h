///************************************************************************
/// <copyrigth>2018-2019 Corporation.All Rights Reserved</copyrigth>
/// <author>tangyingzhong</author>
/// <contact>tangyz114987@outlook.com</contact>
/// <version>V1.0.0</version>
/// <describe>
/// Play piece of pcm file
///</describe>
/// <date>2019/3/6</date>
///***********************************************************************
#ifndef BLOCKPLAYER_H
#define BLOCKPLAYER_H

#include <mmsystem.h>
#include "AudioType.h"
#include "Tool\Thread\Mutex.h"
#include "Tool\Buffer\Array.h"

using namespace System::Buffer;
using namespace System::Thread;

namespace System
{
	namespace MultiMedia
	{
		///*********************************************************
		/// <class>BlockPlayer</class>
		/// <summary>
		///  play block data of pcm file
		/// </summary>
		/// <version>V1.0.0 </version>
		/// <goup> C++</group>
		/// <author>tangyingzhong</author>
		/// <contact>tangyingzhong@szangell.com</contact>
		///*********************************************************
		class BlockPlayer
		{
		public:
			typedef System::Empty Empty;
			typedef System::Boolean BOOL;
			typedef System::Int32 Count;
			typedef System::Int32 BlockSize;
			typedef System::Int32 Index;
			typedef System::Int32 Size;
			typedef System::Int32 ArraySize;
			typedef System::UInt32 Command;		
			typedef System::UInt64 Paramenter;
			typedef System::SByte SByte;
			typedef System::SByteArray SByteArray;
			typedef DWORD_PTR CallBack;
			typedef Mutex* Lock;
			typedef WAVEFORMATEX ConfigPara;
			typedef HWAVEOUT WaveOutHandle;

		public:
			// Construct the BlockPlayer
			BlockPlayer(CodingFormat eCodingFormat, Channel eChannel, BitWidth eBitWidth, SampleFreq eSampleFreq);

			// Detructe the BlockPlayer
			~BlockPlayer();

		private:
			// Copy BlockPlayer
			BlockPlayer(const BlockPlayer& other) {	}

			// Asigment of BlockPlayer
			BlockPlayer& operator=(const BlockPlayer& other) {	}

		public:
			// Open the player,it is suitable to the play piece data
			virtual Empty Open();

			// Start the player with piece data,but you have to open the device with format and channel, etc.
			virtual Empty Play(SByteArray pBlockArray, ArraySize iBlockSize);

			// Pause the player
			virtual Empty Pause();

			// Continue the playing
			virtual Empty Continue();

			// Stop the player
			virtual Empty Stop();

		private:
			// The call back of audio play finish
			static Empty CALLBACK AudioCallBack(WaveOutHandle hWaveoutHandle, Command uMsg, CallBack pObjectState, Paramenter dwParam1, Paramenter dwParam2);

		private:
			// Close the player
			Empty Close();

			// Init the audio device
			Empty Initialize();

			// Destory the audio device
			Empty Destory();

			// Create the cache blocks
			Empty CreateBlocks(BlockSize iBlockSize);

			// Destory the cache blocks
			Empty DestoryBlocks();

			// Destory the lock
			Empty DestoryMutex();

			// Install the cache
			Empty InstallCache();

			// Uninstall the cache
			Empty UnInstallCache();

			// Fill the config para
			ConfigPara FillConfigurePara(CodingFormat eCodingFormat, Channel eChannel, BitWidth eBitWidth, SampleFreq eSampleFreq);

			// WaveOut open the device
			Empty OpenDevice(CodingFormat eCodingFormat, Channel eChannel, BitWidth eBitWidth, SampleFreq eSampleFreq);

		private:
			// Get the audio format
			inline CodingFormat GetAudioFormat() const
			{
				return m_AudioFormat;
			}

			// Set the audio format
			inline Empty SetAudioFormat(CodingFormat eAudioFormat)
			{
				this->m_AudioFormat = eAudioFormat;
			}

			// Get the sample channel
			inline Channel GetSampleChannel() const
			{
				return m_SampleChannel;
			}

			// Set the sample channel
			inline Empty SetSampleChannel(Channel eSampleChannel)
			{
				this->m_SampleChannel = eSampleChannel;
			}

			// Get the sample point's bitwidth
			inline BitWidth GetSamplePointBitWidth() const
			{
				return m_SamplePointBitWidth;
			}

			// Set the sample point's bitwidth
			inline Empty SetSamplePointBitWidth(BitWidth eSamplePointBitWidth)
			{
				this->m_SamplePointBitWidth = eSamplePointBitWidth;
			}

			// Get the sample frequency
			inline SampleFreq GetSampleFreq() const
			{
				return m_SampleFreq;
			}

			// Set the sample frequency
			inline Empty SetSampleFreq(SampleFreq eSampleFreq)
			{
				this->m_SampleFreq = eSampleFreq;
			}

			// Get the wave out handle
			inline WaveOutHandle GetWaveoutHandle() const
			{
				return m_WaveOutHandle;
			}

			// Set the wave out handle
			inline Empty SetWaveoutHandle(WaveOutHandle hWaveOutHandle)
			{
				this->m_WaveOutHandle = hWaveOutHandle;
			}

			// Get the available block count
			inline Count GetAvailableBlockCount() const
			{
				return m_AvailableBlockCount;
			}

			// Set the available block count
			inline Empty SetAvailableBlockCount(Count iAvailableBlockCount)
			{
				this->m_AvailableBlockCount = iAvailableBlockCount;
			}

			// Get the current block index
			inline Index GetCurrentBlockIndex() const
			{
				return m_CurrentBlockIndex;
			}

			// Set the current block index
			inline Empty SetCurrentBlockIndex(Index iCurrentBlockIndex)
			{
				this->m_CurrentBlockIndex = iCurrentBlockIndex;
			}

			// Get the disposed status
			inline BOOL GetDisposed() const
			{
				return m_Disposed;
			}

			// Set the disposed status
			inline Empty SetDisposed(BOOL bDisposed)
			{
				this->m_Disposed = bDisposed;
			}

		private:
			// The lock of thread
			static Lock m_Mutex;

			// Audio coding format
			CodingFormat m_AudioFormat;

			// Sample channel
			Channel m_SampleChannel;

			// Sample point's bitwidth
			BitWidth m_SamplePointBitWidth;

			// Sample frequency
			SampleFreq m_SampleFreq;

			// Wave out device's handle
			WaveOutHandle m_WaveOutHandle;

			// Block head array
			Array<BlockHead> m_BlockHeadArray;

			// Available block count
			Count m_AvailableBlockCount;

			// Current block index
			Index m_CurrentBlockIndex;

			// Disposed status
			BOOL m_Disposed;

		};
	}
}

#endif //BLOCKPLAYER_H_