#include "Application\PreCompile.h"
#include "Counter.h"

using namespace System::Clock;

///************************************************************************
/// <summary>
/// Construct the Counter
/// </summary>
/// <returns></returns>
/// <remarks>
/// none
/// </remarks>
///***********************************************************************
Counter::Counter() :m_Disposed(false)
{
	Initialize();
}


///************************************************************************
/// <summary>
/// Detructe the Counter
/// </summary>
/// <returns></returns>
/// <remarks>
/// none
/// </remarks>
///***********************************************************************
Counter::~Counter()
{
	Destory();
}


///************************************************************************
/// <summary>
/// Init the Counter 
/// </summary>
/// <returns></returns>
/// <remarks>
/// none
/// </remarks>
///***********************************************************************
Counter::Empty Counter::Initialize()
{
	// Zero the paras
	ZeroMemory(&m_PreviousTime, sizeof(LargeTime));
	ZeroMemory(&m_CurTime, sizeof(LargeTime));
	ZeroMemory(&m_CpuFreq, sizeof(LargeTime));

	// Get the cpu freq
	QueryPerformanceFrequency(&m_CpuFreq);
}


///************************************************************************
/// <summary>
/// Dispose the Counter
/// </summary>
/// <returns></returns>
/// <remarks>
/// none
/// </remarks>
///***********************************************************************
Counter::Empty Counter::Destory()
{
	if (!GetDisposed())
	{
		SetDisposed(true);

	}
}


///************************************************************************
/// <summary>
/// Start the counter
/// </summary>
/// <returns></returns>
/// <remarks>
/// none
/// </remarks>
///***********************************************************************
Counter::Empty Counter::Start()
{
	QueryPerformanceCounter(&m_PreviousTime);
}


///************************************************************************
/// <summary>
/// Stop the counter
/// </summary>
/// <returns></returns>
/// <remarks>
/// none
/// </remarks>
///***********************************************************************
Counter::Empty Counter::Stop()
{
	QueryPerformanceCounter(&m_CurTime);
}


///************************************************************************
/// <summary>
/// Get the total time (s)
/// </summary>
/// <param name=t></param>
/// <returns></returns>
/// <remarks>
/// none
/// </remarks>
///***********************************************************************
Counter::TimeS Counter::GetCountTimeS()
{
	TimeS TimeSecond;

	TimeSecond = (m_CurTime.QuadPart - m_PreviousTime.QuadPart)*1.0 / m_CpuFreq.QuadPart;

	return TimeSecond;
}


///************************************************************************
/// <summary>
/// Get the total time (ms)
/// </summary>
/// <param name=t></param>
/// <returns></returns>
/// <remarks>
/// none
/// </remarks>
///***********************************************************************
Counter::TimeMs Counter::GetCountTimeMs()
{
	TimeS TimeSecond;
	TimeSecond = this->GetCountTimeS();

	TimeMs TimeMsecond;
	TimeMsecond = TimeSecond * 1000;

	return TimeMsecond;
}


///************************************************************************
/// <summary>
/// Get the total time (us)
/// </summary>
/// <param name=t></param>
/// <returns></returns>
/// <remarks>
/// none
/// </remarks>
///***********************************************************************
Counter::TimeUs Counter::GetCountTimeUs()
{
	TimeMs TimeMsecond;
	TimeMsecond = this->GetCountTimeMs();

	TimeUs TimeUsecond;
	TimeUsecond = TimeMsecond * 1000;

	return TimeUsecond;
}