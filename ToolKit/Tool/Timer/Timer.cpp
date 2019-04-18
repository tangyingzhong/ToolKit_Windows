#include "Application\PreCompile.h"
#include "Timer.h"

using namespace System::Clock;

///************************************************************************
/// <summary>
/// Construct the Timer
/// </summary>
/// <param name=timerID></param>
/// <param name=time></param>
/// <param name=func></param>
/// <returns></returns>
/// <remarks>
/// none
/// </remarks>
///***********************************************************************
Timer::Timer(DelayMs DelayTime, CallBackFunc Func, Object Paramenter) :m_TimerId(0),
m_TimerDelayTime(DelayTime),
m_CallbackFunc(Func),
m_Closed(true),
m_Disposed(false)
{

}


///************************************************************************
/// <summary>
/// Detructe the Timer
/// </summary>
/// <returns></returns>
/// <remarks>
/// none
/// </remarks>
///***********************************************************************
Timer::~Timer()
{
	if (!GetDisposed())
	{
		SetDisposed(true);

		//Close the timer
		this->Close();
	}
}


///************************************************************************
/// <summary>
/// Open the timer
/// </summary>
/// <returns></returns>
/// <remarks>
/// none
/// </remarks>
///***********************************************************************
Timer::Empty Timer::Open()
{
	if (this->GetClosed() == true)
	{
		this->SetClosed(false);

		// Delay's resolution is 1 ms
		this->SetTimerId(::timeSetEvent(this->GetTimerDelayTime(), 1, this->GetCallbackFunc(), (DWORD_PTR)this->GetTimerPara(), TIME_PERIODIC));
	}
}


///************************************************************************
/// <summary>
/// Close the timer
/// </summary>
/// <returns></returns>
/// <remarks>
/// none
/// </remarks>
///***********************************************************************
Timer::Empty Timer::Close()
{
	if (this->GetClosed() == false)
	{
		::timeKillEvent(this->GetTimerId());

		this->SetClosed(true);
	}
}