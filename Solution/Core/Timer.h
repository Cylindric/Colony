#pragma once

#include <Windows.h>

class Timer
{
public:
	Timer(void);
	~Timer(void);

	void Start(void);
	void Stop(void);

	double GetElapsedTimeSeconds(void);

private:
	double m_StartTimeMicros;
	double m_EndTimeMicros;
	bool m_Stopped;
	LARGE_INTEGER m_Frequency;
	LARGE_INTEGER m_StartCount;
	LARGE_INTEGER m_EndCount;

};

