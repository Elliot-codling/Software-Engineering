#ifndef _AUDIO_H
#define _AUDIO_H

class Audio
{
public:
	Audio();
	virtual ~Audio();

	virtual void Initialise(const char* filename, bool loop = false) = 0;
	virtual void Play() = 0;
	virtual void Pause() = 0;
	virtual void Stop() = 0;
	virtual void SetPlayingOffset(float seconds) = 0;
	virtual void SetVolume(float volume) = 0;//0.0f to 100.0f
	virtual bool HasFinished() = 0;

	bool m_Initialised;
};

#endif
