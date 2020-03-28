#include <Windows.h>
#include <mmsystem.h>
#include "BlockPlayer.h"

#pragma comment(lib,"winmm.lib")

using namespace System::MultiMedia;

Mutex* BlockPlayer::m_pLock = new Mutex();

// Construct the BlockPlayer
BlockPlayer::BlockPlayer(CODING_FORMAT_ENUM eCodeFormat,
	CHANNEL_ENUM eChannel,
	BITWIDTH_ENUM eBitWidth,
	SAMPLE_FREQ_ENUM eSampleFreq) :m_eCodeFormat(eCodeFormat),
	m_eChannel(eChannel),
	m_eBitWidth(eBitWidth),
	m_eSampleFreq(eSampleFreq),
	m_hHandle(NULL),
	m_iAvailableBlockCount(BLOCK_NUM),
	m_iCurrentBlockIndex(0),
	m_bDisposed(false)
{
	Initialize();
}

// Detructe the BlockPlayer
BlockPlayer::~BlockPlayer()
{
	Destory();
}

// Init the audio device
None BlockPlayer::Initialize()
{
	// Create the cache blocks
	CreateBlocks(BLOCK_SIZE);
}

// Destory the audio device
None BlockPlayer::Destory()
{
	if (!GetDisposed())
	{
		SetDisposed(true);		
	
		Close();

		DestoryBlocks();
	}
}

// Create the cache blocks
None BlockPlayer::CreateBlocks(Int32 iSize)
{
	Array<BlockHead> TempBlocks(BLOCK_NUM);

	for (Int32 iIndex = 0; iIndex < BLOCK_NUM; ++iIndex)
	{
		TempBlocks[iIndex].lpData = new SByte[iSize];

		Array<SByte>::Clear(TempBlocks[iIndex].lpData, 0, iSize);
	}

	m_HeadBlockArray = TempBlocks;
}

// Destory the cache blocks
None BlockPlayer::DestoryBlocks()
{
	for (Int32 iIndex = 0; iIndex < BLOCK_NUM; ++iIndex)
	{
		if (m_HeadBlockArray[iIndex].lpData != NULL)
		{
			delete[](m_HeadBlockArray[iIndex].lpData);

			m_HeadBlockArray[iIndex].lpData = NULL;
		}
	}
}

// Install the cache
None BlockPlayer::InstallCache()
{
	for (Int32 iIndex = 0; iIndex < BLOCK_NUM; ++iIndex)
	{
		m_HeadBlockArray[iIndex].dwBufferLength = BLOCK_SIZE;

		m_HeadBlockArray[iIndex].dwFlags = WHDR_PREPARED;

		m_HeadBlockArray[iIndex].dwLoops = 0;

		// Make the current one to be prepared
		::waveOutPrepareHeader(GetHandle(), &(m_HeadBlockArray[iIndex]), sizeof(BlockHead));
	}
}

// Uninstall the cache
None BlockPlayer::UnInstallCache()
{
	for (Int32 iIndex = 0; iIndex < BLOCK_NUM; ++iIndex)
	{
		if (m_HeadBlockArray[iIndex].dwFlags & WHDR_PREPARED)
		{
			waveOutUnprepareHeader(GetHandle(), &(m_HeadBlockArray[iIndex]), sizeof(BlockHead));
		}
	}
}

// Fill the config para
BlockPlayer::ConfigPara BlockPlayer::FillConfigPara(CODING_FORMAT_ENUM eCodeFormat,
	CHANNEL_ENUM eChannel,
	BITWIDTH_ENUM eBitWidth,
	SAMPLE_FREQ_ENUM eSampleFreq)
{
	ConfigPara para;

	para.wFormatTag = eCodeFormat;

	para.cbSize = 0;

	para.nChannels = eChannel;

	para.wBitsPerSample = eBitWidth;

	para.nSamplesPerSec = eSampleFreq;

	para.nBlockAlign = (para.wBitsPerSample*para.nChannels) >> 3;

	para.nAvgBytesPerSec = para.nBlockAlign*para.nSamplesPerSec;

	return para;
}

// WaveOut open the device
Boolean BlockPlayer::OpenDevice(CODING_FORMAT_ENUM eCodeFormat,
	CHANNEL_ENUM eChannel,
	BITWIDTH_ENUM eBitWidth,
	SAMPLE_FREQ_ENUM eSampleFreq)
{
	// Fill the configPara
	ConfigPara ConfigParamenter = FillConfigPara(eCodeFormat, eChannel, eBitWidth, eSampleFreq);

	// Open the waveout device
	if (waveOutOpen(&m_hHandle,		
		WAVE_MAPPER, 
		&ConfigParamenter, 
		(DWORD_PTR)AudioCallBack,
		(DWORD_PTR)this, 
		CALLBACK_FUNCTION) != MMSYSERR_NOERROR)
	{
		return false;
	}

	// Install the cache of the audio device
	InstallCache();

	return true;
}

// The call back of audio play finish
None CALLBACK BlockPlayer::AudioCallBack(WaveOutHandle hHandle,
	Command uMsg,
	Caller pObjectState,
	Paramenter dwParam1,
	Paramenter dwParam2)
{
	BlockPlayer* pThis = (BlockPlayer*)pObjectState;

	switch (uMsg)
	{
	case WOM_DONE:
	{
		MutexLocker Locker(m_pLock);

		pThis->SetAvailableBlockCount(pThis->GetAvailableBlockCount() + 1);
	}
		break;

	case WOM_OPEN:
		break;
	case WOM_CLOSE:
		break;

	default:
		break;
	}
}

// Open the player,it is suitable to the play piece data
Boolean BlockPlayer::Open()
{
	return OpenDevice(GetFormat(),
		GetChannel(),
		GetBitWidth(),
		GetSampleFreq());
}

// Start the player with piece data,but you have to open the device with format and channel, etc.
Boolean BlockPlayer::Play(SByteArray pBlock, Int32 iBlockSize)
{
	if (pBlock==NULL)
	{
		return false;
	}

	if (iBlockSize<0)
	{
		return false;
	}

	// Get the block can work now
	CacheBlock currentBlock = &(m_HeadBlockArray[GetCurrentBlockIndex()]);

	// Loop the work for stroring data and playing
	while (iBlockSize > 0)
	{
		// Make the current block unprepared so that we can use it
		if (currentBlock->dwFlags & WHDR_PREPARED)
		{
			Int32 iRetCode0 =waveOutUnprepareHeader(GetHandle(), currentBlock, sizeof(BlockHead));
			if (iRetCode0!=MMSYSERR_NOERROR)
			{
				return false;
			}
		}

		// If the block size is lower than the default block size
		if (iBlockSize<(BLOCK_SIZE - (Int32)currentBlock->dwUser))
		{
			// We can store it at first and return the function
			Array<SByte>::Copy(pBlock, 
				iBlockSize, 
				currentBlock->lpData + currentBlock->dwUser, 	
				iBlockSize);

			// Update the record bytes
			currentBlock->dwUser += iBlockSize;

			break;
		}

		// If the block size is larger than the default one
		{
			// We need to prepared the current block with the enough data
			Int32 blockLeftSize = BLOCK_SIZE - static_cast<Int32>(currentBlock->dwUser);

			// Copy the user data to the current block's left space
			Array<SByte>::Copy(pBlock,
				blockLeftSize, 
				currentBlock->lpData+currentBlock->dwUser, 
				blockLeftSize);

			// Change the position of the input block
			pBlock = pBlock + blockLeftSize;

			iBlockSize = iBlockSize - blockLeftSize;

			// Write the block to the audio driver
			currentBlock->dwBufferLength = BLOCK_SIZE;

			Int32 iRetCode1 = waveOutPrepareHeader(GetHandle(), currentBlock, sizeof(BlockHead));
			if (iRetCode1 != MMSYSERR_NOERROR)
			{
				return false;
			}

			Int32 iRetCode = waveOutWrite(GetHandle(), currentBlock, sizeof(BlockHead));
			if (iRetCode != MMSYSERR_NOERROR)
			{
				return false;
			}

			// Update the available blocks at this time
			{
				MutexLocker Locker(m_pLock);

				SetAvailableBlockCount(GetAvailableBlockCount() - 1);
			}

			// If the available block is 0
			while (GetAvailableBlockCount()==0)
			{
				// We have to wait for available blocks here
				Sleep(10);
			}

			// We get the available blocks and Update the current blocks Index
			SetCurrentBlockIndex(GetCurrentBlockIndex() + 1);

			SetCurrentBlockIndex(GetCurrentBlockIndex() % BLOCK_NUM);

			// Get the correct block can working now
			currentBlock = &(m_HeadBlockArray[GetCurrentBlockIndex()]);

			currentBlock->dwUser = 0;
		}
	}

	return true;
}

// Pause the player
Boolean BlockPlayer::Pause()
{
	if (GetHandle() == NULL)
	{
		return false;
	}

	Int32 iRetCode = waveOutPause(GetHandle());
	if (iRetCode != MMSYSERR_NOERROR)
	{
		return false;
	}

	return true;
}

// Continue the playing
Boolean BlockPlayer::Continue()
{
	if (GetHandle() == NULL)
	{
		return false;
	}

	Int32 iRetCode = waveOutRestart(GetHandle());
	if (iRetCode != MMSYSERR_NOERROR)
	{
		return false;
	}

	return true;
}

// Stop the player
Boolean BlockPlayer::Stop()
{
	if (GetHandle() == NULL)
	{
		return false;
	}

	Int32 iRetCode = waveOutReset(GetHandle());
	if (iRetCode != MMSYSERR_NOERROR)
	{
		return false;
	}

	return true;
}

// Close the player
Boolean BlockPlayer::Close()
{
	// Wait for all blocks handled
	while (GetAvailableBlockCount() < BLOCK_NUM)
	{
		Sleep(10);
	}

	// Unprepared any cache that is prepared
	for (Int32 iIndex = 0; iIndex < BLOCK_NUM; ++iIndex)
	{
		if (m_HeadBlockArray[iIndex].dwFlags & WHDR_PREPARED)
		{
			waveOutUnprepareHeader(GetHandle(), &(m_HeadBlockArray[iIndex]), sizeof(BlockHead));
		}
	}

	// Reset the device
	Int32 iRetCode = waveOutReset(GetHandle());
	if (iRetCode != MMSYSERR_NOERROR)
	{
		return false;
	}

	// Close the device
	Int32 iRetCode1 = waveOutClose(GetHandle());
	if (iRetCode1 != MMSYSERR_NOERROR)
	{
		return false;
	}

	return true;
}