#ifndef _FRAME_TIMER_H
#define _FRAME_TIMER_H

#include <Windows.h>

class FrameTimer
{
public:

	FrameTimer();
	~FrameTimer();

	void Initialise();
	void StartFrame();
	void EndFrame();

	float DeltaTime() { return static_cast<float>(m_ElapsedTime);  }
	float FPS() { return m_CurrentFPS; }
	
private:
	LARGE_INTEGER frequency{};        // ticks per second
	LARGE_INTEGER currentTime{};		// ticks
	LARGE_INTEGER lastTime{};			// ticks
	double m_ElapsedTime{};
	float m_CurrentFPS{};
	
};

#endif
