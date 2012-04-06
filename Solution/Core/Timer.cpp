#include "Timer.h"

Timer::Timer()
{
	QueryPerformanceFrequency(&m_Frequency);
	m_StartCount.QuadPart = 0;
	m_EndCount.QuadPart = 0;
	
	m_Stopped = true;
	m_StartTimeMicros = 0;
	m_EndTimeMicros = 0;
}


Timer::~Timer()
{
}


void Timer::Start()
{
	m_Stopped = false;
	QueryPerformanceCounter(&m_StartCount);
}


void Timer::Stop()
{
	m_Stopped = true;
	QueryPerformanceCounter(&m_EndCount);
}


double Timer::GetElapsedTimeSeconds()
{
	if(!m_Stopped)
	{
		QueryPerformanceCounter(&m_EndCount);
	}

	return (double)(m_EndCount.QuadPart - m_StartCount.QuadPart) / m_Frequency.QuadPart;
}
