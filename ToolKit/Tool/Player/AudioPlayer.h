///************************************************************************
/// <copyrigth>2018-2019 Corporation.All Rights Reserved</copyrigth>
/// <author>tangyingzhong</author>
/// <contact>tangyz114987@outlook.com</contact>
/// <version>V1.0.0</version>
/// <describe>
/// Audio player
///</describe>
/// <date>2019/3/6</date>
///***********************************************************************
#ifndef AUDIOPLAYER_H
#define AUDIOPLAYER_H

#include "BlockPlayer.h"
#include "Tool\File\File.h"
#include "Tool\BaseType\String.h"

using namespace System::BasicType;
using namespace System::IO;

namespace System
{
	namespace MultiMedia
	{
		///*********************************************************
		/// <class>AudioPlayer</class>
		/// <summary>
		/// play pcm file
		/// </summary>
		/// <version>V1.0.0 </version>
		/// <goup> C++</group>
		/// <author>tangyingzhong</author>
		/// <contact>tangyingzhong@szangell.com</contact>
		///*********************************************************
		class AudioPlayer
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
			typedef System::UInt64 Caller;
			typedef System::UInt64 Paramenter;
			typedef System::SByte SByte;
			typedef System::SByteArray SByteArray;
			typedef AudioHeader AudioHeader;
			typedef BlockPlayer* Player;
			typedef File* WinFile;
			typedef DWORD_PTR CallBack;
			typedef Mutex* Lock;
			typedef WAVEFORMATEX ConfigPara;
			typedef HWAVEOUT WaveOutHandle;

		public:
			// Construct the AudioPlayer
			AudioPlayer();

			// Detructe the AudioPlayer
			~AudioPlayer();

		private:
			// Copy AudioPlayer
			AudioPlayer(const AudioPlayer& other) {	}

			// Asigment of AudioPlayer
			AudioPlayer& operator=(const AudioPlayer& other) {	}

		public:
			// Start the player
			virtual Empty Play(String strMusicFileName);

			// Pause the player
			virtual Empty Pause();

			// Continue the playing
			virtual Empty Continue();

			// Stop the player
			virtual Empty Stop();

		private:
			// Open the player with the file
			Empty Open(String strMusicFileName);

			// Init the audio player
			Empty Initialize();

			// Destory the palyer
			Empty Destory();

			// Destory the lock
			Empty DestoryMutex();

			// Create a block player
			Empty CreateBlockPlayer(CodingFormat eCodingFormat, Channel eChannel, BitWidth eBitWidth, SampleFreq eSampleFreq);

			// Destory the block player
			Empty DestoryBlockPlayer();

			// Create a windows file object
			Empty CreateWinFile();

			// Destory the windows file
			Empty DestoryWinFile();

			// Parse the file for the audio head info
			AudioHeader GetHeadInfo(String strFileName);

		private:
			// Get the music file name 
			inline String GetMusicFileName() const
			{
				return m_MusicFileName;
			}

			// Set the music file name 
			inline Empty SetMusicFileName(String strMusicFileName)
			{
				this->m_MusicFileName = strMusicFileName;
			}

			// Get the block player
			inline Player GetBlockPlayer() const
			{
				return m_BlockPlayer;
			}

			// Set the block player
			inline Empty SetBlockPlayer(Player pBlockPlayer)
			{
				this->m_BlockPlayer = pBlockPlayer;
			}

			// Get the file 
			inline WinFile GetFile() const
			{
				return m_WinFile;
			}

			// Set the file
			inline Empty SetFile(WinFile pWinFile)
			{
				this->m_WinFile = pWinFile;
			}

			// Get the play status
			inline PlayStatus GetPlayStatus() const
			{
				return m_PlayStatus;
			}

			// Set the play status
			inline Empty SetPlayStatus(PlayStatus ePlayStatus)
			{
				this->m_PlayStatus = ePlayStatus;
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
			// Thread lock
			static Lock m_Mutex;

			// Music file name
			String m_MusicFileName;

			// Block player
			Player m_BlockPlayer;

			// WinFile object
			WinFile m_WinFile;

			// Play status
			PlayStatus m_PlayStatus;

			// Disposed status
			BOOL m_Disposed;

		};
	}
}

#endif //AUDIOPLAYER_H_