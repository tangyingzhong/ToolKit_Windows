#include "AudioPlayer.h"
#include "BlockPlayer.h"
#include "Tool/File/File.h"

using namespace System::IO;
using namespace System::MultiMedia;

Mutex* AudioPlayer::m_pLock = new Mutex();

// Construct the AudioPlayer
AudioPlayer::AudioPlayer() :m_strFileName(_T("")),
m_pBlockPlayer(NULL),
m_ePlayStatus(PLAYER_NOT_START),
m_bDisposed(false)
{
	Initialize();
}

// Detructe the AudioPlayer
AudioPlayer::~AudioPlayer()
{
	Destory();
}

// Init the audio player
None AudioPlayer::Initialize()
{

}

// Destory the palyer
None AudioPlayer::Destory()
{
	if (GetDisposed() == false)
	{
		SetDisposed(true);

		// Destory the block player
		DestoryBlockPlayer();
	}
}

// Create a block player
None AudioPlayer::CreateBlockPlayer(CODING_FORMAT_ENUM eCodeFormat,
	CHANNEL_ENUM eChannel,
	BITWIDTH_ENUM eBitWidth,
	SAMPLE_FREQ_ENUM eSampleFreq)
{
	SetBlockPlayer(new BlockPlayer(eCodeFormat, eChannel, eBitWidth, eSampleFreq));
}

// Destory the block player
None AudioPlayer::DestoryBlockPlayer()
{
	if (GetBlockPlayer())
	{
		delete GetBlockPlayer();

		SetBlockPlayer(NULL);
	}
}

// Parse the file for the audio head info
Boolean AudioPlayer::ParseFile(String strFileName, AudioHeader& HeadInfo)
{
	if (strFileName.IsEmpty())
	{
		return false;
	}

	// Read 44 bytes from the file
	File FileHelper;

	if (!FileHelper.Open(strFileName,File::FileMode::OPEN,File::FileAccess::READ))
	{
		return false;
	}

	Array<SByte> headArray(AUDIO_HEAD_SIZE);

	FileHelper.Read(headArray.Data(), 0, headArray.Size());

	FileHelper.Close();

	// Set the audio header
	SByte* p = headArray.Data();

	// It must be "RIFF"
	HeadInfo.head[0] = p[0];
	HeadInfo.head[1] = p[1];
	HeadInfo.head[2] = p[2];
	HeadInfo.head[3] = p[3];
	p = p + 4;
	// The size of audio data+44 -8
	HeadInfo.structSize = *((Int32*)p);
	p = p + 4;
	// It must be "WAVE"
	Byte* t1 = (Byte*)p;
	HeadInfo.waveType[0] = t1[0];
	HeadInfo.waveType[1] = t1[1];
	HeadInfo.waveType[2] = t1[2];
	HeadInfo.waveType[3] = t1[3];
	p = p + 4;
	// It must be "fmt "
	HeadInfo.formatString[0] = p[0];
	HeadInfo.formatString[1] = p[1];
	HeadInfo.formatString[2] = p[2];
	HeadInfo.formatString[3] = p[3];
	p = p + 4;
	// Included head size
	HeadInfo.size1 = *((Int32*)p);
	p = p + 4;
	// The coding format of audio
	HeadInfo.codingFormat = *((Int16*)p);
	p = p + 2;
	// The channel of audio
	HeadInfo.channel = *((Int16*)p);
	p = p + 2;
	// The sample frequency of audio
	HeadInfo.sampleRate = *((Int32*)p);
	p = p + 4;
	// The total bytes of one second 
	HeadInfo.avgByteRate = *((Int32*)p);
	p = p + 4;
	// The total bytes of one sample, the value can be got by (channel*bitPerSample)/8
	HeadInfo.blockAlign = *((Int16*)p);
	p = p + 2;
	// The total bits of one sample,8,16.
	HeadInfo.bitPerSample = *((Int16*)p);
	p = p + 2;
	// Constant string "data"
	HeadInfo.flag[0] = p[0];
	HeadInfo.flag[1] = p[1];
	HeadInfo.flag[2] = p[2];
	HeadInfo.flag[3] = p[3];
	p = p + 4;
	// It is not including the head size of the file
	HeadInfo.size2 = *((Int32*)p);

	return true;
}

// Open the player with the file
Boolean AudioPlayer::Open(String strFileName)
{
	if (strFileName.IsEmpty())
	{
		return false;
	}

	// Set the file name
	SetFileName(strFileName);

	// Parse the file Notice that: you have to open the file here so that you can test playing succesfully
	AudioHeader HeadInfo;
	if (!ParseFile(strFileName, HeadInfo))
	{
		return false;
	}

	// Create the block player
	if (GetBlockPlayer()==NULL)
	{
		CreateBlockPlayer((CODING_FORMAT_ENUM)HeadInfo.codingFormat,
			(CHANNEL_ENUM)HeadInfo.channel,
			(BITWIDTH_ENUM)HeadInfo.bitPerSample,
			(SAMPLE_FREQ_ENUM)HeadInfo.sampleRate);
	}

	return GetBlockPlayer()->Open();
}

// Start the player
Boolean AudioPlayer::Play(String fileName)
{
	// Open the audio device
	if (!Open(fileName))
	{
		return false;
	}

	// Get the total size of file
	File FileHelper;

	if (!FileHelper.Open(fileName,File::FileMode::OPEN,File::FileAccess::READ))
	{
		return false;
	}

	Int32 iSize = (Int32)FileHelper.GetSize();

	Int32 totalSize = iSize - AUDIO_HEAD_SIZE;

	Int32 leftSize = totalSize;

	Int32 readSize = 0;

	Int32 incrementSize = 0;

	Int32 runSize = AUDIOFILE_BLOCK_SIZE;

	FileHelper.Seek(File::SeekOrigin::BEGIN, 0);

	// New a space for the file piece data
	Array<SByte> readBlock(runSize);

	// Loop playing the piece data
	while (1)
	{
		if (GetBlockPlayer() == NULL)
		{
			return false;
		}

		if (GetPlayStatus() == PLAYER_STOP)
		{
			if(!GetBlockPlayer()->Stop())
			{
				return false;
			}

			break;
		}
		else if (GetPlayStatus() == PLAYER_PAUSE)
		{
			if (!GetBlockPlayer()->Pause())
			{
				return false;
			}

			continue;
		}
		else if (GetPlayStatus() == PLAYER_CONTINUE)
		{
			if (!GetBlockPlayer()->Continue())
			{
				return false;
			}
		}

		// Read a piece of data
		readSize = FileHelper.Read(readBlock.Data(), 0, runSize);

		// Play the piece data
		if (!GetBlockPlayer()->Play(readBlock.Data(), readSize))
		{
			return false;
		}

		// Update the left size of file
		incrementSize = incrementSize + readSize;

		// Get the left size
		leftSize = totalSize - incrementSize;
		if (leftSize == 0)
		{
			break;
		}
		else if (leftSize < runSize)
		{
			runSize = leftSize;
		}
	}

	// Close the file
	FileHelper.Close();

	return true;
}

// Pause the playe
Boolean AudioPlayer::Pause()
{
	if (GetBlockPlayer()==NULL)
	{
		return false;
	}

	MutexLocker Locker(m_pLock);

	SetPlayStatus(PLAYER_PAUSE);

	return true;
}

// Continue the playing
Boolean AudioPlayer::Continue()
{
	if (GetBlockPlayer() == NULL)
	{
		return false;
	}

	MutexLocker Locker(m_pLock);

	SetPlayStatus(PLAYER_CONTINUE);

	return true;
}

// Stop the player
Boolean AudioPlayer::Stop()
{
	if (GetBlockPlayer() == NULL)
	{
		return false;
	}

	MutexLocker Locker(m_pLock);

	SetPlayStatus(PLAYER_STOP);

	return true;
}