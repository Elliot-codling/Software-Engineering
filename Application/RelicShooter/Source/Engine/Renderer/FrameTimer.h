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
	bool FixedUpdate();

	void EndFrame();

	float DeltaTime() const
	{
		if (m_elapsedTime >= (1.f / 60.f))
		{
			return 1.f / 60.f;
		}
		return m_elapsedTime;
	}
	float FPS() const { return m_currentFPS; }
	
private:


	LARGE_INTEGER frequency;        // ticks per second
	LARGE_INTEGER currentTime;		// ticks
	LARGE_INTEGER lastTime;			// ticks
	double m_elapsedTime;
	double m_timeSinceLastUpdate;
	float m_currentFPS;
	
};

#endif
