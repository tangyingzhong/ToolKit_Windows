#include "Application\PreCompile.h"
#include "BlockPlayer.h"

#pragma comment(lib,"winmm.lib")

using namespace System::MultiMedia;

BlockPlayer::Lock BlockPlayer::m_Mutex = new Mutex();

///************************************************************************
/// <summary>
/// Construct the BlockPlayer
/// </summary>
/// <returns></returns>
/// <remarks>
/// none
/// </remarks>
///***********************************************************************
BlockPlayer::BlockPlayer(CodingFormat eCodingFormat, Channel eChannel, BitWidth eBitWidth, SampleFreq eSampleFreq) :m_AudioFormat(eCodingFormat),
m_SampleChannel(eChannel),
m_SamplePointBitWidth(eBitWidth),
m_SampleFreq(eSampleFreq),
m_WaveOutHandle(NULL),
m_AvailableBlockCount(AudioEnum::BLOCK_NUM),
m_CurrentBlockIndex(0),
m_Disposed(false)
{
	Initialize();
}


///************************************************************************
/// <summary>
/// Detructe the BlockPlayer
/// </summary>
/// <returns></returns>
/// <remarks>
/// none
/// </remarks>
///***********************************************************************
BlockPlayer::~BlockPlayer()
{
	Destory();
}


///************************************************************************
/// <summary>
/// Init the audio device
/// </summary>
/// <returns></returns>
/// <remarks>
/// none
/// </remarks>
///***********************************************************************
BlockPlayer::Empty BlockPlayer::Initialize()
{
	// Create the cache blocks
	CreateBlocks(BLOCK_SIZE);
}


///************************************************************************
/// <summary>
/// Destory the audio device
/// </summary>
/// <returns></returns>
/// <remarks>
/// none
/// </remarks>
///***********************************************************************
BlockPlayer::Empty BlockPlayer::Destory()
{
	if (GetDisposed() == false)
	{
		SetDisposed(true);

		// Close the audio device
		this->Close();

		// Destory the blocks
		this->DestoryBlocks();
	}
}


///************************************************************************
/// <summary>
/// Create the cache blocks
/// </summary>
/// <param name=size>the size of block</param>
/// <returns></returns>
/// <remarks>
/// none
/// </remarks>
///***********************************************************************
BlockPlayer::Empty BlockPlayer::CreateBlocks(BlockSize iBlockSize)
{
	Array<BlockHead> TempBlocks(BLOCK_NUM);

	for (Index iIndex = 0; iIndex < TempBlocks.Size();iIndex++)
	{
		TempBlocks[iIndex].lpData = new SByte[iBlockSize];

		Array<SByte>::Clear(TempBlocks[iIndex].lpData, 0, iBlockSize);
	}

	this->m_BlockHeadArray = TempBlocks;
}


///************************************************************************
/// <summary>
/// Destory the cache blocks
/// </summary>
/// <returns></returns>
/// <remarks>
/// none
/// </remarks>
///***********************************************************************
BlockPlayer::Empty BlockPlayer::DestoryBlocks()
{
	for (Index iIndex = 0; iIndex < this->m_BlockHeadArray.Size();iIndex++)
	{
		if (this->m_BlockHeadArray[iIndex].lpData != NULL)
		{
			delete[](this->m_BlockHeadArray[iIndex].lpData);

			this->m_BlockHeadArray[iIndex].lpData = NULL;
		}
	}
}


///************************************************************************
/// <summary>
/// Destory the lock
/// </summary>
/// <returns></returns>
/// <remarks>
/// none
/// </remarks>
///***********************************************************************
BlockPlayer::Empty BlockPlayer::DestoryMutex()
{
	if (BlockPlayer::m_Mutex)
	{
		delete BlockPlayer::m_Mutex;
		BlockPlayer::m_Mutex = NULL;
	}
}


///************************************************************************
/// <summary>
/// Install the cache
/// </summary>
/// <returns></returns>
/// <remarks>
/// none
/// </remarks>
///***********************************************************************
BlockPlayer::Empty BlockPlayer::InstallCache()
{
	for (Index iIndex = 0; iIndex < this->m_BlockHeadArray.Size();iIndex++)
	{
		this->m_BlockHeadArray[iIndex].dwBufferLength = AudioEnum::BLOCK_SIZE;
		this->m_BlockHeadArray[iIndex].dwFlags = WHDR_PREPARED;
		this->m_BlockHeadArray[iIndex].dwLoops = 0;

		::waveOutPrepareHeader(this->GetWaveoutHandle(), &(this->m_BlockHeadArray[iIndex]), sizeof(BlockHead));
	}
}


///************************************************************************
/// <summary>
/// Uninstall the cache
/// </summary>
/// <returns></returns>
/// <remarks>
/// none
/// </remarks>
///***********************************************************************
BlockPlayer::Empty BlockPlayer::UnInstallCache()
{
	for (Index iIndex = 0; iIndex < this->m_BlockHeadArray.Size();iIndex++)
	{
		if (this->m_BlockHeadArray[iIndex].dwFlags & WHDR_PREPARED)
		{
			waveOutUnprepareHeader(this->GetWaveoutHandle(), &(this->m_BlockHeadArray[iIndex]), sizeof(BlockHead));
		}
	}
}


///************************************************************************
/// <summary>
/// Fill the config para
/// </summary>
/// <param name=format>the coding format of audio</param>
/// <param name=channel>the channel of audio</param>
/// <param name=bitWidth>the bitwidth of sample</param>
/// <param name=freq>the frequency of sample</param>
/// <returns>the config paramenter of audio</returns>
/// <remarks>
/// you must set up the config para before your openning file
/// </remarks>
///***********************************************************************
BlockPlayer::ConfigPara BlockPlayer::FillConfigurePara(CodingFormat eCodingFormat, Channel eChannel, BitWidth eBitWidth, SampleFreq eSampleFreq)
{
	ConfigPara ConfigureParamenter;

	ConfigureParamenter.wFormatTag = eCodingFormat;
	ConfigureParamenter.cbSize = 0;
	ConfigureParamenter.nChannels = eChannel;
	ConfigureParamenter.wBitsPerSample = eBitWidth;
	ConfigureParamenter.nSamplesPerSec = eSampleFreq;
	ConfigureParamenter.nBlockAlign = (ConfigureParamenter.wBitsPerSample*ConfigureParamenter.nChannels) >> 3;
	ConfigureParamenter.nAvgBytesPerSec = ConfigureParamenter.nBlockAlign*ConfigureParamenter.nSamplesPerSec;

	return ConfigureParamenter;
}


///************************************************************************
/// <summary>
/// WaveOut open the device
/// </summary>
/// <param name=format></param>
/// <param name=channel></param>
/// <param name=bitWidth></param>
/// <param name=freq></param>
/// <returns></returns>
/// <remarks>
/// none
/// </remarks>
///***********************************************************************
BlockPlayer::Empty BlockPlayer::OpenDevice(CodingFormat eCodingFormat, Channel eChannel, BitWidth eBitWidth, SampleFreq eSampleFreq)
{
	// Fill the configPara
	ConfigPara ConfigurePara = FillConfigurePara(eCodingFormat, eChannel, eBitWidth, eSampleFreq);

	// Open the waveout device
	if (waveOutOpen(&(this->m_WaveOutHandle), WAVE_MAPPER, &ConfigurePara, (DWORD_PTR)AudioCallBack, (DWORD_PTR)this, CALLBACK_FUNCTION) != MMSYSERR_NOERROR)
	{
		MessageBox(NULL, _T("Open the device failed"), _T("Audio Error"), 0);

		return;
	}

	// Install the cache of the audio device
	InstallCache();
}


///************************************************************************
/// <summary>
/// The call back of audio play finish
/// </summary>
/// <param name=handle>the handle of wave out</param>
/// <param name=uMsg>the command of waveout</param>
/// <param name=objectState>the instance of self</param>
/// <param name=dwParam1>extra para</param>
/// <param name=dwParam2>extra para</param>
/// <returns></returns>
/// <remarks>
/// this function is called by OS when the waveout sending the msg
/// </remarks>
///***********************************************************************
BlockPlayer::Empty CALLBACK BlockPlayer::AudioCallBack(WaveOutHandle hWaveoutHandle, Command uMsg, CallBack pObjectState, Paramenter dwParam1, Paramenter dwParam2)
{
	BlockPlayer* player = (BlockPlayer*)pObjectState;

	switch (uMsg)
	{
	case WOM_DONE:
		m_Mutex->Lock();
		{
			player->SetAvailableBlockCount(player->GetAvailableBlockCount() + 1);
		}
		m_Mutex->Unlock();
		break;

	case WOM_OPEN:
		break;
	case WOM_CLOSE:
		break;

	default:
		break;
	}

}


///************************************************************************
/// <summary>
/// Open the player,it is suitable to the play piece data
/// </summary>
/// <param name=format>the coding of audio</param>
/// <param name=channel>the channel of audio</param>
/// <param name=bitWidth>the width of sample</param>
/// <param name=freq>sample frequency</param>
/// <returns></returns>
/// <remarks>
/// this is for the palying piece data not an audio file
/// </remarks>
///***********************************************************************
BlockPlayer::Empty BlockPlayer::Open()
{
	this->OpenDevice(this->GetAudioFormat(), this->GetSampleChannel(), this->GetSamplePointBitWidth(), this->GetSampleFreq());
}


///************************************************************************
/// <summary>
/// Start the player with piece data,but you have to open the device with format and channel, etc.
/// </summary>
/// <param name=block>the block data</param>
/// <param name=blockSize>the size of block</param>
/// <returns></returns>
/// <remarks>
/// it must be called after the open with specail coding ,etc.
/// </remarks>
///***********************************************************************
BlockPlayer::Empty BlockPlayer::Play(SByteArray pBlockArray, ArraySize iBlockSize)
{
	assert(pBlockArray != NULL);
	assert(iBlockSize > 0);

	if (pBlockArray == NULL || iBlockSize <= 0)
	{
		return;
	}

	// Get the block can work now
	CacheBlock pCurrentBlock = &(this->m_BlockHeadArray[this->GetCurrentBlockIndex()]);

	// Loop the work for stroring data and playing
	while (iBlockSize > 0)
	{
		// Make the current block unprepared so that we can use it
		if (pCurrentBlock->dwFlags & WHDR_PREPARED)
		{
			waveOutUnprepareHeader(this->GetWaveoutHandle(), pCurrentBlock, sizeof(BlockHead));
		}

		// If the block size is lower than the default block size
		if (iBlockSize < (ArraySize)(BLOCK_SIZE - (pCurrentBlock->dwUser)))
		{
			// We can store it at first and return the function
			Array<SByte>::Copy(pBlockArray, iBlockSize, pCurrentBlock->lpData + pCurrentBlock->dwUser, iBlockSize);

			// Update the record bytes
			pCurrentBlock->dwUser += iBlockSize;

			break;
		}

		// If the block size is larger than the default one
		{
			// We need to prepared the current block with the enough data
			Size iBlockLeftSize = BLOCK_SIZE - (Size)(pCurrentBlock->dwUser);

			// Copy the user data to the current block's left space
			Array<SByte>::Copy(pBlockArray, iBlockLeftSize, pCurrentBlock->lpData + pCurrentBlock->dwUser, iBlockLeftSize);

			// Change the position of the input block
			pBlockArray = pBlockArray + iBlockLeftSize;
			iBlockSize = iBlockSize - iBlockLeftSize;

			// Write the block to the audio driver
			pCurrentBlock->dwBufferLength = BLOCK_SIZE;
			waveOutPrepareHeader(this->GetWaveoutHandle(), pCurrentBlock, sizeof(BlockHead));
			waveOutWrite(this->GetWaveoutHandle(), pCurrentBlock, sizeof(BlockHead));

			// Update the available blocks at this time
			m_Mutex->Lock();
			{
				SetAvailableBlockCount(GetAvailableBlockCount() - 1);
			}
			m_Mutex->Unlock();

			// If the available block is 0
			while (GetAvailableBlockCount() == 0)
			{
				// We have to wait for available blocks here
				Sleep(10);
			}

			// We get the available blocks
			// Update the current blocks Index
			SetCurrentBlockIndex(GetCurrentBlockIndex() + 1);
			SetCurrentBlockIndex(GetCurrentBlockIndex() % BLOCK_NUM);

			// Get the correct block can working now
			pCurrentBlock = &(this->m_BlockHeadArray[this->GetCurrentBlockIndex()]);
			pCurrentBlock->dwUser = 0;
		}
	}
}


///************************************************************************
/// <summary>
/// Pause the player
/// </summary>
/// <returns></returns>
/// <remarks>
/// none
/// </remarks>
///***********************************************************************
BlockPlayer::Empty BlockPlayer::Pause()
{
	if (this->GetWaveoutHandle())
	{
		waveOutPause(this->GetWaveoutHandle());
	}
}


///************************************************************************
/// <summary>
/// Continue the playing
/// </summary>
/// <returns></returns>
/// <remarks>
/// none
/// </remarks>
///***********************************************************************
BlockPlayer::Empty BlockPlayer::Continue()
{
	if (this->GetWaveoutHandle())
	{
		waveOutRestart(this->GetWaveoutHandle());
	}
}


///************************************************************************
/// <summary>
/// Stop the player
/// </summary>
/// <returns></returns>
/// <remarks>
/// none
/// </remarks>
///***********************************************************************
BlockPlayer::Empty BlockPlayer::Stop()
{
	if (this->GetWaveoutHandle())
	{
		waveOutReset(this->GetWaveoutHandle());
	}
}


///************************************************************************
/// <summary>
/// Close the player
/// </summary>
/// <returns></returns>
/// <remarks>
/// none
/// </remarks>
///***********************************************************************
BlockPlayer::Empty BlockPlayer::Close()
{
	// Wait for all blocks handled
	while (this->GetAvailableBlockCount() < BLOCK_NUM)
	{
		Sleep(10);
	}

	// Unprepared any cache that is prepared
	this->UnInstallCache();

	// Destory the mutex
	DestoryMutex();

	// Reset the device
	if (waveOutReset(this->GetWaveoutHandle()) != MMSYSERR_NOERROR)
	{
		MessageBox(NULL, _T("Reset the device failed"), _T("Audio error"), 0);
	}

	// Close the device
	waveOutClose(this->GetWaveoutHandle());
}