///************************************************************************
/// <copyrigth>emperor electric technology of ShenZhen</copyrigth>
/// <author>tangyingzhong</author>
/// <contact>tangyz114987@outlook.com</contact>
/// <version>v1.0.0</version>
/// <describe>
/// Play music file(.wav)
/// </describe>
/// <date>2018/1/18</date>
///***********************************************************************
#ifndef AUDIOPLAYER_H
#define AUDIOPLAYER_H

#include "IAudioPlayer.h"
#include "IBlockPlayer.h"
#include "Tool/Buffer/Array.h"
#include "Tool/Thread/MutexLocker.h"

using namespace System::Buffer;
using namespace System::Thread;

namespace System
{
	namespace MultiMedia
	{
		class AudioPlayer :public IAudioPlayer
		{
		public:
			typedef WAVEFORMATEX ConfigPara;
			typedef IBlockPlayer* Player;

		public:
			// Construct the AudioPlayer
			AudioPlayer();

			// Detructe the AudioPlayer
			~AudioPlayer();

		private:
			// Copy AudioPlayer
			AudioPlayer(const AudioPlayer& other){	}

			// Asigment of AudioPlayer
			AudioPlayer& operator=(const AudioPlayer& other){	}

		public:
			// Start the player
			virtual Boolean Play(String strFileName);

			// Pause the player
			virtual Boolean Pause();

			// Continue the playing
			virtual Boolean Continue();

			// Stop the player
			virtual Boolean Stop();

		private:
			// Open the player with the file
			Boolean Open(String strFileName);

			// Init the audio player
			None Initialize();

			// Destory the palyer
			None Destory();

			// Create a block player
			None CreateBlockPlayer(CODING_FORMAT_ENUM eCodeFormat,
				CHANNEL_ENUM eChannel,
				BITWIDTH_ENUM eBitWidth,
				SAMPLE_FREQ_ENUM eSampleFreq);

			// Destory the block player
			None DestoryBlockPlayer();

			// Parse the file for the audio head info
			Boolean ParseFile(String strFileName, AudioHeader& HeadInfo);

		private:
			// Get the FileName
			inline String GetFileName() const
			{
				return m_strFileName;
			}

			// Set the FileName
			inline None SetFileName(String strFileName)
			{
				m_strFileName = strFileName;
			}

			// Get the BlockPlayer
			inline Player GetBlockPlayer() const
			{
				return m_pBlockPlayer;
			}

			// Set the BlockPlayer
			inline None SetBlockPlayer(Player pBlockPlayer)
			{
				m_pBlockPlayer = pBlockPlayer;
			}

			// Get the PlayStatus
			inline PLAY_STATE_ENUM GetPlayStatus() const
			{
				return m_ePlayStatus;
			}

			// Set the PlayStatus
			inline None SetPlayStatus(PLAY_STATE_ENUM ePlayStatus)
			{
				m_ePlayStatus = ePlayStatus;
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

		private:
			// File's lock
			static Mutex* m_pLock;

			// The audio file name
			String m_strFileName;

			// The block player
			Player m_pBlockPlayer;

			// Play status
			PLAY_STATE_ENUM m_ePlayStatus;

			// Disposed status
			BOOL m_bDisposed;
		};
	}
}

#endif // AUDIOPLAYER_H