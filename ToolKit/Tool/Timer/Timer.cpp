#include <Windows.h>
#include <mmsystem.h>
#include "Timer.h"

#pragma comment(lib,"Winmm.lib")

using namespace System::Clock;

// Construct the Timer
Timer::Timer(DelayMs DelayTime, CallBackFunc Func, Object Paramenter) :m_TimerId(0),
m_TimerDelayTime(DelayTime),
m_CallbackFunc(Func),
m_Closed(true),
m_Disposed(false)
{

}

// Detructe the Timer
Timer::~Timer()
{
	if (!GetDisposed())
	{
		SetDisposed(true);

		Close();
	}
}

// Open the timer
Timer::None Timer::Open()
{
	if (GetClosed() == true)
	{
		SetClosed(false);

		// Delay's resolution is 1 ms
		SetTimerId(::timeSetEvent(GetTimerDelayTime(), 
			1, 
			GetCallbackFunc(), 
			(DWORD_PTR)GetTimerPara(), 
			TIME_PERIODIC));
	}
}

// Close the timer
Timer::None Timer::Close()
{
	if (GetClosed() == false)
	{
		::timeKillEvent(GetTimerId());

		SetClosed(true);
	}
}