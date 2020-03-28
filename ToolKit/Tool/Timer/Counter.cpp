#include "Counter.h"

using namespace System::Clock;

// Construct the Counter
Counter::Counter() :m_Disposed(false)
{
	Initialize();
}

// Detructe the Counter
Counter::~Counter()
{
	Destory();
}

// Init the Counter 
Counter::None Counter::Initialize()
{
	// Zero the paras
	ZeroMemory(&m_PreviousTime, sizeof(LargeTime));

	ZeroMemory(&m_CurTime, sizeof(LargeTime));

	ZeroMemory(&m_CpuFreq, sizeof(LargeTime));

	// Get the cpu freq
	QueryPerformanceFrequency(&m_CpuFreq);
}

// Dispose the Counter
Counter::None Counter::Destory()
{
	if (!GetDisposed())
	{
		SetDisposed(true);
	}
}

// Start the counter
Counter::None Counter::Start()
{
	QueryPerformanceCounter(&m_PreviousTime);
}

// Stop the counter
Counter::None Counter::Stop()
{
	QueryPerformanceCounter(&m_CurTime);
}

// Get the total time (s)
Counter::TimeS Counter::GetCountTimeS()
{
	TimeS TimeSecond;

	TimeSecond = (m_CurTime.QuadPart - m_PreviousTime.QuadPart)*1.0 / m_CpuFreq.QuadPart;

	return TimeSecond;
}

// Get the total time (ms)
Counter::TimeMs Counter::GetCountTimeMs()
{
	TimeS TimeSecond;
	TimeSecond = GetCountTimeS();

	TimeMs TimeMsecond;
	TimeMsecond = TimeSecond * 1000;

	return TimeMsecond;
}

// Get the total time (us)
Counter::TimeUs Counter::GetCountTimeUs()
{
	TimeMs TimeMsecond;
	TimeMsecond = GetCountTimeMs();

	TimeUs TimeUsecond;
	TimeUsecond = TimeMsecond * 1000;

	return TimeUsecond;
}