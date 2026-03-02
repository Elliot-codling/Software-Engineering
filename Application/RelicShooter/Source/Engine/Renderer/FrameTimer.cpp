#include "FrameTimer.h"
#include <iostream>

const double TARGET_FRAMETIME = 1.0 / 60.0;

FrameTimer::FrameTimer()
{

}

FrameTimer::~FrameTimer()
{

}

void FrameTimer::Initialise()
{
	m_elapsedTime = 0.f;
	m_timeSinceLastUpdate = 0.f;

	QueryPerformanceFrequency(&frequency);

	//start the timer
	QueryPerformanceCounter(&lastTime);
}

void FrameTimer::StartFrame()
{
	QueryPerformanceCounter(&currentTime);
}

bool FrameTimer::FixedUpdate()
{
	if (m_timeSinceLastUpdate >= TARGET_FRAMETIME)
	{
		m_timeSinceLastUpdate -= TARGET_FRAMETIME;
		return true;
	}
	return false;
}

void FrameTimer::EndFrame()
{
	QueryPerformanceCounter(&currentTime);
	m_elapsedTime = ((currentTime.QuadPart - lastTime.QuadPart) * 1.0) / frequency.QuadPart;

	m_timeSinceLastUpdate += m_elapsedTime;

	m_currentFPS = (1.0 / m_elapsedTime);

	lastTime = currentTime;
}
