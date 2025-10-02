#include "FrameTimer.h"

constexpr double TARGET_FRAMETIME = 1.0 / 60.0;

FrameTimer::FrameTimer()
= default;

FrameTimer::~FrameTimer()
= default;

void FrameTimer::Initialise()
{
	m_ElapsedTime = 0.0;

	QueryPerformanceFrequency(&frequency);

	//start the timer
	QueryPerformanceCounter(&lastTime);
}

void FrameTimer::StartFrame()
{
	QueryPerformanceCounter(&currentTime);
}

void FrameTimer::EndFrame()
{
	do
	{ 
		QueryPerformanceCounter(&currentTime);
		m_ElapsedTime = (currentTime.QuadPart - lastTime.QuadPart) * 1.0 / frequency.QuadPart;

	} while (m_ElapsedTime < TARGET_FRAMETIME);

	m_CurrentFPS = static_cast<float>(1.0 / m_ElapsedTime);

	lastTime = currentTime;
}
