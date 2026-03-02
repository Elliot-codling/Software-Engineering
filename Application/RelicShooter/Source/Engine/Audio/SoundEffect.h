#ifndef _SOUND_EFFECT_H
#define _SOUND_EFFECT_H

#include "Audio.h"
#include "SFML\Audio.hpp"

class SoundEffect : public Audio
{
public:

	SoundEffect();
	virtual ~SoundEffect();

	virtual void Initialise(const char* filename, bool loop = false);
	virtual void Play();
	virtual void Pause();
	virtual void Stop();
	virtual void SetPlayingOffset(const float seconds);
	virtual void SetVolume(const float volume);//0.0f to 100.0f
	virtual bool HasFinished();

private:

	sf::Sound m_Sound;

};

#endif
