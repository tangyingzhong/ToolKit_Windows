///************************************************************************
/// <copyrigth>emperor electric technology of ShenZhen</copyrigth>
/// <author>tangyingzhong</author>
/// <contact>tangyz114987@outlook.com</contact>
/// <version>v1.0.0</version>
/// <describe>
/// Play the wave with piece data 
/// </describe>
/// <date>2018/1/17</date>
///***********************************************************************
#ifndef BLOCKPLAYER_H
#define BLOCKPLAYER_H

#include "IBlockPlayer.h"
#include <mmsystem.h>
#include "Tool/Buffer/Array.h"
#include "Tool/Thread/MutexLocker.h"

using namespace System::Buffer;
using namespace System::Thread;

namespace System
{
	namespace MultiMedia
	{
		class BlockPlayer :public IBlockPlayer
		{
		public:
			typedef WAVEFORMATEX ConfigPara;
			typedef HWAVEOUT WaveOutHandle;
			typedef UINT Command;
			typedef DWORD_PTR CallBack;
			typedef DWORD Caller;
			typedef DWORD Paramenter;

		public:
			// Construct the BlockPlayer
			BlockPlayer(CODING_FORMAT_ENUM eCodeFormat, 
				CHANNEL_ENUM eChannel, 
				BITWIDTH_ENUM eBitWidth,
				SAMPLE_FREQ_ENUM eSampleFreq);

			// Detructe the BlockPlayer
			~BlockPlayer();

		private:
			// Copy BlockPlayer
			BlockPlayer(const BlockPlayer& other){	}

			// Asigment of BlockPlayer
			BlockPlayer& operator=(const BlockPlayer& other){	}

		private:
			// The call back of audio play finish
			static None CALLBACK AudioCallBack(WaveOutHandle hHandle, 	
				Command uMsg,
				Caller pObjectState, 
				Paramenter dwParam1, 
				Paramenter dwParam2);

		public:
			// Open the player,it is suitable to the play piece data
			virtual Boolean Open();

			// Start the player with piece data,but you have to open the device with format and channel, etc.
			virtual Boolean Play(SByteArray pBlock, Int32 iBlockSize);

			// Pause the player
			virtual Boolean Pause();

			// Continue the playing
			virtual Boolean Continue();

			// Stop the player
			virtual Boolean Stop();

		private:
			// Close the player
			Boolean Close();

			// Init the audio device
			None Initialize();

			// Destory the audio device
			None Destory();

			// Create the cache blocks
			None CreateBlocks(Int32 iSize);

			// Destory the cache blocks
			None DestoryBlocks();

			// Install the cache
			None InstallCache();

			// Uninstall the cache
			None UnInstallCache();

		private:
			// Fill the config para
			ConfigPara FillConfigPara(CODING_FORMAT_ENUM eCodeFormat,
				CHANNEL_ENUM eChannel,
				BITWIDTH_ENUM eBitWidth,
				SAMPLE_FREQ_ENUM eSampleFreq);

			// WaveOut open the device
			Boolean OpenDevice(CODING_FORMAT_ENUM eCodeFormat,
				CHANNEL_ENUM eChannel,
				BITWIDTH_ENUM eBitWidth,
				SAMPLE_FREQ_ENUM eSampleFreq);

		private:
			// Get the Handle
			inline WaveOutHandle GetHandle() const
			{
				return m_hHandle;
			}

			// Set the Handle
			inline None SetHandle(WaveOutHandle hHandle)
			{
				m_hHandle = hHandle;
			}

			// Get the AvailableBlockCount
			inline Int32 GetAvailableBlockCount() const
			{
				return m_iAvailableBlockCount;
			}

			// Set the AvailableBlockCount
			inline None SetAvailableBlockCount(Int32 iBlockCount)
			{
				m_iAvailableBlockCount = iBlockCount;
			}

			// Get the CurrentBlockIndex
			inline Int32 GetCurrentBlockIndex() const
			{
				return m_iCurrentBlockIndex;
			}

			// Set the CurrentBlockIndex
			inline None SetCurrentBlockIndex(Int32 iIndex)
			{
				m_iCurrentBlockIndex = iIndex;
			}

			// Get the Disposed
			inline BOOL GetDisposed() const
			{
				return m_bDisposed;
			}

			// Set the Disposed
			inline None SetDisposed(BOOL bDisposed)
			{
				m_bDisposed = bDisposed;
			}

			// Get the Format
			inline CODING_FORMAT_ENUM GetFormat() const
			{
				return m_eCodeFormat;
			}

			// Set the Format
			inline None SetFormat(CODING_FORMAT_ENUM eFormat)
			{
				m_eCodeFormat = eFormat;
			}

			// Get the Channel
			inline CHANNEL_ENUM GetChannel() const
			{
				return m_eChannel;
			}

			// Set the Channel
			inline None SetChannel(CHANNEL_ENUM eChannel)
			{
				m_eChannel = eChannel;
			}

			// Get the BitWidth
			inline BITWIDTH_ENUM GetBitWidth() const
			{
				return m_eBitWidth;
			}

			// Set the BitWidth
			inline None SetBitWidth(BITWIDTH_ENUM eBitWidth)
			{
				m_eBitWidth = eBitWidth;
			}

			// Get the Freq
			inline SAMPLE_FREQ_ENUM GetSampleFreq() const
			{
				return m_eSampleFreq;
			}

			// Set the Freq
			inline None SetSampleFreq(SAMPLE_FREQ_ENUM eFreq)
			{
				m_eSampleFreq = eFreq;
			}

		private:
			// The lock of thread
			static Mutex* m_pLock;

			// Coding format
			CODING_FORMAT_ENUM m_eCodeFormat;

			// Channel
			CHANNEL_ENUM m_eChannel;

			// Bitwidth
			BITWIDTH_ENUM m_eBitWidth;

			// Sample frequency
			SAMPLE_FREQ_ENUM m_eSampleFreq;

			// The handle of the wave out device
			WaveOutHandle m_hHandle;

			// Audio head block
			Array<BlockHead> m_HeadBlockArray;

			// The available block count
			Int32 m_iAvailableBlockCount;

			// The index of current block
			Int32 m_iCurrentBlockIndex;

			// The dispose status
			BOOL m_bDisposed;
		};
	}
}

#endif // BLOCKPLAYER_H