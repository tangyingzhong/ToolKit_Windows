#include "GeneralPlayer.h"

#pragma comment(lib, "strmiids.lib")

using namespace System::MultiMedia;

// Construct the GeneralPlayer
GeneralPlayer::GeneralPlayer() :m_pGraphBuilder(NULL),
m_pMediaController(NULL),
m_pMediaEvent(NULL),
m_pMediaSeeking(NULL),
m_pBasicAudio(NULL),
m_iAudioDuration(0),
m_bDisposed(false)
{
	Initialize();
}

// Detructe the GeneralPlayer
GeneralPlayer::~GeneralPlayer()
{
	Destory();
}

// Initialize the GeneralPlayer
None GeneralPlayer::Initialize()
{
	::CoInitialize(NULL);
}

// Destory the GeneralPlayer
None GeneralPlayer::Destory()
{
	if (!GetDisposed())
	{
		SetDisposed(true);

		Stop();

		CleanupAudio();

		::CoUninitialize();
	}
}

// Cleanup the audio
None GeneralPlayer::CleanupAudio()
{
	if (GetGraphBuilder())
	{
		GetGraphBuilder()->Release();

		SetGraphBuilder(NULL);
	}

	if (GetMediaController())
	{
		GetMediaController()->Release();

		SetMediaController(NULL);
	}

	if (GetMediaEvent())
	{
		GetMediaEvent()->Release();

		SetMediaEvent(NULL);
	}

	if (GetMediaSeeking())
	{
		GetMediaSeeking()->Release();

		SetMediaSeeking(NULL);
	}

	if (GetBasicAudio())
	{
		GetBasicAudio()->Release();

		SetBasicAudio(NULL);
	}
}

// Load the audio file
Boolean GeneralPlayer::Load(String strAudioFilePath)
{
	if (strAudioFilePath.IsEmpty())
	{
		return false;
	}

	// Cleanup the audio
	CleanupAudio();

	HRESULT hResult = CoCreateInstance(CLSID_FilterGraph,
		NULL,
		CLSCTX_INPROC_SERVER,
		IID_IGraphBuilder,
		(void **)&m_pGraphBuilder);
	if (FAILED(hResult))
	{
		::SetLastError(hResult);

		return false;
	}

	m_pGraphBuilder->QueryInterface(IID_IMediaControl, (void **)&m_pMediaController);
	m_pGraphBuilder->QueryInterface(IID_IMediaEventEx, (void **)&m_pMediaEvent);
	m_pGraphBuilder->QueryInterface(IID_IBasicAudio, (void**)&m_pBasicAudio);
	m_pGraphBuilder->QueryInterface(IID_IMediaSeeking, (void**)&m_pMediaSeeking);

	hResult = m_pGraphBuilder->RenderFile(strAudioFilePath.ToUTF16Data().c_str(), NULL);
	if (FAILED(hResult))
	{
		::SetLastError(hResult);

		return false;
	}

	if (GetMediaSeeking())
	{
		GetMediaSeeking()->SetTimeFormat(&TIME_FORMAT_MEDIA_TIME);

		// 10,000,000 = 1s
		GetMediaSeeking()->GetDuration(&m_iAudioDuration);
	}

	return true;
}

// Play the audio
Boolean GeneralPlayer::Play()
{
	if (GetMediaController()==NULL)
	{
		return false;
	}

	HRESULT hResult = GetMediaController()->Run();
	if (FAILED(hResult))
	{
		::SetLastError(hResult);

		return false;
	}

	return true;
}

// Pause the audio
Boolean GeneralPlayer::Pause()
{
	if (GetMediaController() == NULL)
	{
		return false;
	}

	HRESULT hResult = GetMediaController()->Pause();
	if (SUCCEEDED(hResult))
	{
		return true;
	}

	::SetLastError(hResult);

	return false;
}

// Resume the audio
Boolean GeneralPlayer::Resume()
{
	return Play();
}

// Stop the audio
Boolean GeneralPlayer::Stop()
{
	if (GetMediaController() == NULL)
	{
		return false;
	}

	HRESULT hResult = GetMediaController()->Stop();
	if (SUCCEEDED(hResult))
	{
		return true;
	}

	::SetLastError(hResult);

	return false;
}

// Wait for completion(iTimeoutMs==0, return immediately or playing finished)
Boolean GeneralPlayer::WaitForCompletion(FixedInt32 iTimeoutMs, FixedInt32* plEvCode)
{
	if (iTimeoutMs<0)
	{
		return false;
	}

	if (GetMediaEvent()==NULL)
	{
		return false;
	}

	GetMediaEvent()->WaitForCompletion(iTimeoutMs, plEvCode);
	
	return *plEvCode > 0;
}

// Get the current volume
FixedInt32 GeneralPlayer::GetCurrentVolume()
{
	if (GetBasicAudio()==NULL)
	{
		return -1;
	}

	FixedInt32 iVolume = -1;

	HRESULT hResult= GetBasicAudio()->get_Volume(&iVolume);
	if (FAILED(hResult))
	{
		::SetLastError(hResult);

		return -1;
	}

	return iVolume+1000;
}

// Set the volume (0-1000)
Boolean GeneralPlayer::SetVolume(FixedInt32 iValue)
{
	if (iValue<0)
	{
		return false;
	}

	FixedInt32 iVolume = iValue - 1000;

	if (GetBasicAudio() == NULL)
	{
		return false;
	}

	HRESULT hResult = GetBasicAudio()->put_Volume(iVolume);
	if (FAILED(hResult))
	{
		::SetLastError(hResult);

		return false;
	}

	return true;
}

// Get audio total duration
Int64 GeneralPlayer::GetAudioTotalDuration()
{
	return GetAudioDuration();
}

// Get current audio playing position
Int64 GeneralPlayer::GetCurPlayPos()
{
	if (GetMediaSeeking() == NULL)
	{
		return -1;
	}

	Int64 iCurPos = -1;

	HRESULT hResult = GetMediaSeeking()->GetCurrentPosition(&iCurPos);
	if (FAILED(hResult))
	{
		::SetLastError(hResult);
	}

	return iCurPos;
}

// Set the audio playing position
Boolean GeneralPlayer::SetPlayPos(Int64* pICurPos, Int64* pIStopPos, Boolean bIsAbsolutionPos)
{
	if (pICurPos==NULL)
	{
		return false;
	}

	if (pIStopPos==NULL)
	{
		return false;
	}

	if (GetMediaSeeking() == NULL)
	{
		return false;
	}

	DWORD dwFlag = 0;

	if (bIsAbsolutionPos)
	{
		dwFlag = AM_SEEKING_AbsolutePositioning | AM_SEEKING_SeekToKeyFrame;
	}
	else
	{
		dwFlag = AM_SEEKING_RelativePositioning | AM_SEEKING_SeekToKeyFrame;
	}

	HRESULT hResult = GetMediaSeeking()->SetPositions(pICurPos,dwFlag,pIStopPos,dwFlag);
	if (FAILED(hResult))
	{
		::SetLastError(hResult);

		return false;
	}

	return true;
}