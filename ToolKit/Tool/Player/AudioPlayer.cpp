#include "Application\PreCompile.h"
#include "AudioPlayer.h"
#include "Tool\Buffer\Array.h"

using namespace System::IO;
using namespace System::Buffer;
using namespace System::MultiMedia;

AudioPlayer::Lock AudioPlayer::m_Mutex = new Mutex();

///************************************************************************
/// <summary>
/// Construct the AudioPlayer
/// </summary>
/// <returns></returns>
/// <remarks>
/// none
/// </remarks>
///***********************************************************************
AudioPlayer::AudioPlayer() :m_MusicFileName(_T("")),
m_BlockPlayer(NULL),
m_WinFile(NULL),
m_PlayStatus(PlayStatus::PLAYER_NOT_START),
m_Disposed(false)
{
	Initialize();
}


///************************************************************************
/// <summary>
/// Detructe the AudioPlayer
/// </summary>
/// <returns></returns>
/// <remarks>
/// none
/// </remarks>
///***********************************************************************
AudioPlayer::~AudioPlayer()
{
	Destory();
}



///************************************************************************
/// <summary>
/// Init the audio player
/// </summary>
/// <returns></returns>
/// <remarks>
/// none
/// </remarks>
///***********************************************************************
AudioPlayer::Empty AudioPlayer::Initialize()
{
	// Create a windows file
	CreateWinFile();
}


///************************************************************************
/// <summary>
/// Destory the palyer
/// </summary>
/// <returns></returns>
/// <remarks>
/// none
/// </remarks>
///***********************************************************************
AudioPlayer::Empty AudioPlayer::Destory()
{
	if (GetDisposed() == false)
	{
		SetDisposed(true);

		// Destory the block player
		DestoryBlockPlayer();

		// Destory the windows file
		DestoryWinFile();

		// Destory the lock
		DestoryMutex();
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
AudioPlayer::Empty AudioPlayer::DestoryMutex()
{
	if (AudioPlayer::m_Mutex)
	{
		delete AudioPlayer::m_Mutex;
		AudioPlayer::m_Mutex = NULL;
	}
}


///************************************************************************
/// <summary>
/// Create a block player
/// </summary>
/// <returns></returns>
/// <remarks>
/// none
/// </remarks>
///***********************************************************************
AudioPlayer::Empty AudioPlayer::CreateBlockPlayer(CodingFormat eCodingFormat, Channel eChannel, BitWidth eBitWidth, SampleFreq eSampleFreq)
{
	this->SetBlockPlayer(new BlockPlayer(eCodingFormat, eChannel, eBitWidth, eSampleFreq));
}


///************************************************************************
/// <summary>
/// Destory the block player
/// </summary>
/// <returns></returns>
/// <remarks>
/// none
/// </remarks>
///***********************************************************************
AudioPlayer::Empty AudioPlayer::DestoryBlockPlayer()
{
	if (this->GetBlockPlayer())
	{
		delete this->GetBlockPlayer();
		this->SetBlockPlayer(NULL);
	}
}


///************************************************************************
/// <summary>
/// Create a windows file object
/// </summary>
/// <returns></returns>
/// <remarks>
/// none
/// </remarks>
///***********************************************************************
AudioPlayer::Empty AudioPlayer::CreateWinFile()
{
	this->SetFile(new File());
}


///************************************************************************
/// <summary>
/// Destory the windows file
/// </summary>
/// <returns></returns>
/// <remarks>
/// none
/// </remarks>
///***********************************************************************
AudioPlayer::Empty AudioPlayer::DestoryWinFile()
{
	if (this->GetFile())
	{
		delete this->GetFile();
		this->SetFile(NULL);
	}
}


///************************************************************************
/// <summary>
/// Parse the file for the audio head info
/// </summary>
/// <param name=fileName>audio file name</param>
/// <returns>the special pcm head</returns>
/// <remarks>
/// none
/// </remarks>
///***********************************************************************
AudioPlayer::AudioHeader AudioPlayer::GetHeadInfo(String strFileName)
{
	// Read 44 bytes from the file
	this->GetFile()->Open(strFileName, FileMode::OPEN, FileAccess::READ);

	Array<SByte> HeadArray(AudioEnum::AUDIO_HEAD_SIZE);

	this->GetFile()->Read(HeadArray, 0, AudioEnum::AUDIO_HEAD_SIZE);

	// Set the audio header
	AudioHeader header;
	SByteArray p = HeadArray;

	// It must be "RIFF"
	header.head[0] = p[0];
	header.head[1] = p[1];
	header.head[2] = p[2];
	header.head[3] = p[3];
	p = p + 4;

	// The size of audio data+44 -8
	header.structSize = *((Int32*)p);
	p = p + 4;

	// It must be "WAVE"
	SByte* t1 = (SByte*)p;
	header.waveType[0] = t1[0];
	header.waveType[1] = t1[1];
	header.waveType[2] = t1[2];
	header.waveType[3] = t1[3];
	p = p + 4;

	// It must be "fmt "
	header.formatString[0] = p[0];
	header.formatString[1] = p[1];
	header.formatString[2] = p[2];
	header.formatString[3] = p[3];
	p = p + 4;

	// Included head size
	header.size1 = *((Int32*)p);
	p = p + 4;

	// The coding format of audio
	header.codingFormat = *((Int16*)p);
	p = p + 2;

	// The channel of audio
	header.channel = *((Int16*)p);
	p = p + 2;

	// The sample frequency of audio
	header.sampleRate = *((Int32*)p);
	p = p + 4;

	// The total bytes of one second 
	header.avgByteRate = *((Int32*)p);
	p = p + 4;

	// The total bytes of one sample, the value can be got by (channel*bitPerSample)/8
	header.blockAlign = *((Int16*)p);
	p = p + 2;

	// The total bits of one sample,8,16.
	header.bitPerSample = *((Int16*)p);
	p = p + 2;

	// Constant string "data"
	header.flag[0] = p[0];
	header.flag[1] = p[1];
	header.flag[2] = p[2];
	header.flag[3] = p[3];
	p = p + 4;

	// It is not including the head size of the file
	header.size2 = *((Int32*)p);

	return header;
}


///************************************************************************
/// <summary>
/// Open the player with the file
/// </summary>
/// <param name=fileName>audio file path</param>
/// <returns></returns>
/// <remarks>
/// none
/// </remarks>
///***********************************************************************
AudioPlayer::Empty AudioPlayer::Open(String strMusicFileName)
{
	// Set the file name
	this->SetMusicFileName(strMusicFileName);

	// Parse the file Notice that: you have to open the file here so that you can test playing succesfully
	AudioHeader AudioHead = this->GetHeadInfo(strMusicFileName);

	// Create the block player
	if (this->GetBlockPlayer() == NULL)
	{
		this->CreateBlockPlayer((CodingFormat)AudioHead.codingFormat, (Channel)AudioHead.channel, (BitWidth)AudioHead.bitPerSample, (SampleFreq)AudioHead.sampleRate);
	}

	// Open the block player
	this->GetBlockPlayer()->Open();
}


///************************************************************************
/// <summary>
/// Start the player
/// </summary>
/// <returns></returns>
/// <remarks>
/// none
/// </remarks>
///***********************************************************************
AudioPlayer::Empty AudioPlayer::Play(String fileName)
{
	// Open the audio device
	this->Open(fileName);

	// Get the total size of file
	Size totalSize = (this->GetFile()->GetSize()) - AudioEnum::AUDIO_HEAD_SIZE;
	Size leftSize = totalSize;
	Size readSize = 0;
	Size incrementSize = 0;
	Size runSize = AUDIOFILE_BLOCK_SIZE;

	// New a space for the file piece data
	Array<SByte> readBlockArray(runSize);
	Array<SByte>::Clear(readBlockArray, 0, runSize);

	// Loop playing the piece data
	while (1)
	{
		if (this->GetBlockPlayer() == NULL)
		{
			break;
		}

		if (GetPlayStatus() == PlayStatus::PLAYER_STOP)
		{
			this->GetBlockPlayer()->Stop();
			break;
		}
		else if (GetPlayStatus() == PlayStatus::PLAYER_PAUSE)
		{
			this->GetBlockPlayer()->Pause();
			continue;
		}
		else if (GetPlayStatus() == PlayStatus::PLAYER_CONTINUE)
		{
			this->GetBlockPlayer()->Continue();
		}
		// Read a piece of data
		readSize = this->GetFile()->Read(readBlockArray, 0, runSize);

		// Play the piece data
		this->GetBlockPlayer()->Play(readBlockArray, readSize);

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
	this->GetFile()->Close();
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
AudioPlayer::Empty AudioPlayer::Pause()
{
	if (this->GetBlockPlayer())
	{
		m_Mutex->Lock();
		{
			SetPlayStatus(PlayStatus::PLAYER_PAUSE);
		}
		m_Mutex->Unlock();
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
AudioPlayer::Empty AudioPlayer::Continue()
{
	if (this->GetBlockPlayer())
	{
		m_Mutex->Lock();
		{
			SetPlayStatus(PlayStatus::PLAYER_CONTINUE);
		}
		m_Mutex->Unlock();
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
AudioPlayer::Empty AudioPlayer::Stop()
{
	if (this->GetBlockPlayer())
	{
		m_Mutex->Lock();
		{
			SetPlayStatus(PlayStatus::PLAYER_STOP);
		}
		m_Mutex->Unlock();
	}
}