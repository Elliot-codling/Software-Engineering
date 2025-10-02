#ifndef _SOUND_EFFECT_H
#define _SOUND_EFFECT_H

#include "Audio.h"
#include "SFML/Audio.hpp"

class SoundEffect : public Audio
{
public:

	SoundEffect();
	~SoundEffect() override;

	void Initialise(const char* filename, bool loop = false) override;
	void Play() override;
	void Pause() override;
	void Stop() override;
	void SetPlayingOffset(float seconds) override;
	void SetVolume(float volume) override;//0.0f to 100.0f
	bool HasFinished() override;

private:

	sf::Sound m_Sound;

};

#endif
