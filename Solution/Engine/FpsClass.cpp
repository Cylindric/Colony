///////////////////////////////////////////////////////////////////////////////
// Filename: FpsClass.cpp
///////////////////////////////////////////////////////////////////////////////
#include "FpsClass.h"


//////////////
// INCLUDES //
//////////////
#include <Windows.h>
#include <MMSystem.h>


////////////////////////////////////////////////////////////////////////////////
// Class name: FpsClass
////////////////////////////////////////////////////////////////////////////////
FpsClass::FpsClass()
{
}


FpsClass::FpsClass(const FpsClass& other)
{
}


FpsClass::~FpsClass()
{
}

void FpsClass::Initialise()
{
	m_fps = 0;
	m_count = 0;
	m_startTime = timeGetTime();
	return;
}

void FpsClass::Frame()
{
	m_count++;

	if(timeGetTime() >= (m_startTime + 1000))
	{
		m_fps = m_count;
		m_count = 0;
		
		m_startTime = timeGetTime();
	}
}

int FpsClass::GetFps()
{
	return m_fps;
}
