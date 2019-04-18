#include "Application\PreCompile.h"
#include "Delay.h"

using namespace System::Clock;

///************************************************************************
/// <summary>
/// Construct the Delay
/// </summary>
/// <returns></returns>
/// <remarks>
/// none
/// </remarks>
///***********************************************************************
Delay::Delay() :m_Disposed(false)
{
	Initialize();
}


///************************************************************************
/// <summary>
/// Detructe the Delay
/// </summary>
/// <returns></returns>
/// <remarks>
/// none
/// </remarks>
///***********************************************************************
Delay::~Delay()
{
	Destory();
}


///************************************************************************
/// <summary>
/// Init the delay 
/// </summary>
/// <returns></returns>
/// <remarks>
/// none
/// </remarks>
///***********************************************************************
Delay::Empty Delay::Initialize()
{

}


///************************************************************************
/// <summary>
/// Destory the delay
/// </summary>
/// <returns></returns>
/// <remarks>
/// none
/// </remarks>
///***********************************************************************
Delay::Empty Delay::Destory()
{
	if (!GetDisposed())
	{
		SetDisposed(true);

	}
}


///************************************************************************
/// <summary>
/// delay for us
/// </summary>
/// <param name=us></param>
/// <returns></returns>
/// <remarks>
/// none
/// </remarks>
///***********************************************************************
Delay::Empty Delay::DelayUs(TimeUs iTimeUs)
{
	LARGE_INTEGER dwStart;
	LARGE_INTEGER dwCurrent;
	LARGE_INTEGER dwFreq;
	LONGLONG iCounter;

	// Check the current OS is supporting such delay or not
	if (!QueryPerformanceFrequency(&dwFreq))
	{
		MessageBox(NULL, _T("Delay Not OK"), _T("OS do not support such delay"), 0);
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