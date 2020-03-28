#include <iostream>
#include "Delay.h"

using namespace System::Clock;

// Construct the Delay
Delay::Delay() :m_Disposed(false)
{
	Initialize();
}

// Detructe the Delay
Delay::~Delay()
{
	Destory();
}

// Init the delay 
Delay::None Delay::Initialize()
{

}

// Destory the delay
Delay::None Delay::Destory()
{
	if (!GetDisposed())
	{
		SetDisposed(true);
	}
}

// Delay for us
Delay::None Delay::DelayUs(TimeUs iTimeUs)
{
	LARGE_INTEGER dwStart;
	LARGE_INTEGER dwCurrent;
	LARGE_INTEGER dwFreq;
	LONGLONG iCounter;

	// Check the current OS is supporting such delay or not
	if (!QueryPerformanceFrequency(&dwFreq))
	{
		std::cerr << "OS do not support such delay" << std::endl;

		return;
	}

	QueryPerformanceCounter(&dwStart);

	iCounter = dwFreq.QuadPart*iTimeUs / 1000 / 1000;

	dwCurrent = dwStart;

	while ((dwCurrent.QuadPart - dwStart.QuadPart) < iCounter)
	{
		QueryPerformanceCounter(&dwCurrent);
	}
}