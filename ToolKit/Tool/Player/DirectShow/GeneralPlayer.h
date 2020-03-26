///************************************************************************
/// <copyrigth>Voice AI Technology Of ShenZhen</copyrigth>
/// <author>tangyingzhong</author>
/// <contact>yingzhong@voiceaitech.com</contact>
/// <version>v1.0.0</version>
/// <describe>
/// It is a general player using direct show
///</describe>
/// <date>2019/11/25</date>
///***********************************************************************
#ifndef GENERALPLAYER_H
#define GENERALPLAYER_H

#include <strmif.h>
#include <control.h>
#include <uuids.h>
#include "Common/SystemType.h"
#include "BaseType/String.h"

using namespace System;
using namespace System::BasicType;

namespace System
{
	namespace MultiMedia
	{
		class GeneralPlayer
		{
		public:
			typedef IGraphBuilder* GraphBuilder;
			typedef IMediaControl* MediaCntrl;
			typedef IMediaEventEx* MediaEvent;
			typedef IMediaSeeking* MediaSeeking;
			typedef IBasicAudio* BasicAudio;

		public:
			// Construct the GeneralPlayer
			GeneralPlayer();

			// Detructe the GeneralPlayer
			~GeneralPlayer();

		private:
			// Forbid the copy GeneralPlayer
			GeneralPlayer(const GeneralPlayer& other){	}

			// Forbid the assigment of GeneralPlayer
			GeneralPlayer& operator=(const GeneralPlayer& other){	}

		public:
			// Load the audio file
			Boolean Load(String strAudioFilePath);

			// Play the audio
			Boolean Play();

			// Pause the audio
			Boolean Pause();

			// Resume the audio
			Boolean Resume();

			// Stop the audio
			Boolean Stop();

			// Wait for completion(iTimeoutMs==0, return immediately or playing finished)
			Boolean WaitForCompletion(FixedInt32 iTimeoutMs, FixedInt32* plEvCode);

			// Get the current volume
			FixedInt32 GetCurrentVolume();

			// Set the volume
			Boolean SetVolume(FixedInt32 iValue);

			// Get audio total duration
			Int64 GetAudioTotalDuration();

			// Get current audio playing position
			Int64 GetCurPlayPos();

			// Set the audio playing position
			Boolean SetPlayPos(Int64* pICurPos,Int64* pIStopPos,Boolean bIsAbsolutionPos);

		private:
			// Initialize the GeneralPlayer
			Empty Initialize();

			// Destory the GeneralPlayer
			Empty Destory();

			// Cleanup the audio
			Empty CleanupAudio();

		private:
			// Get the GraphBuilder
			inline GraphBuilder GetGraphBuilder() const
			{
				return m_pGraphBuilder;
			}

			// Set the GraphBuilder
			inline Empty SetGraphBuilder(GraphBuilder pGraphBuilder)
			{
				m_pGraphBuilder = pGraphBuilder;
			}

			// Get the MediaController
			inline MediaCntrl GetMediaController() const
			{
				return m_pMediaController;
			}

			// Set the MediaController
			inline Empty SetMediaController(MediaCntrl pMediaController)
			{
				m_pMediaController = pMediaController;
			}

			// Get the MediaEvent
			inline MediaEvent GetMediaEvent() const
			{
				return m_pMediaEvent;
			}

			// Set the MediaEvent
			inline Empty SetMediaEvent(MediaEvent pMediaEvent)
			{
				m_pMediaEvent = pMediaEvent;
			}

			// Get the MediaSeeking
			inline MediaSeeking GetMediaSeeking() const
			{
				return m_pMediaSeeking;
			}

			// Set the MediaSeeking
			inline Empty SetMediaSeeking(MediaSeeking pMediaSeeking)
			{
				m_pMediaSeeking = pMediaSeeking;
			}

			// Get the BasicAudio
			inline BasicAudio GetBasicAudio() const
			{
				return m_pBasicAudio;
			}

			// Set the BasicAudio
			inline Empty SetBasicAudio(BasicAudio pBasicAudio)
			{
				m_pBasicAudio = pBasicAudio;
			}

			// Get the AudioDuration
			inline Int64 GetAudioDuration() const
			{
				return m_iAudioDuration;
			}

			// Set the AudioDuration
			inline Empty SetAudioDuration(Int64 iAudioDuration)
			{
				m_iAudioDuration = iAudioDuration;
			}

			// Get the disposed status
			inline Boolean GetDisposed() const
			{
				return m_bDisposed;
			}

			// Set the disposed status
			inline Empty SetDisposed(Boolean bDisposed)
			{
				m_bDisposed = bDisposed;
			}

		private:
			// GraphBuilder
			GraphBuilder m_pGraphBuilder;

			// Media controller
			MediaCntrl m_pMediaController;

			// Media event
			MediaEvent m_pMediaEvent;

			// Media seeking
			MediaSeeking m_pMediaSeeking;

			// Basic audio
			BasicAudio m_pBasicAudio;

			// Duration
			Int64 m_iAudioDuration;

			// Disposed status
			Boolean m_bDisposed;
		};
	}
}

#endif // GENERALPLAYER_H