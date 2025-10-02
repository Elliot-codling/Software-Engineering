#ifndef _STREAMED_AUDIO_H
#define _STREAMED_AUDIO_H

#include "Audio.h"
#include "SFML/Audio.hpp"

class StreamedAudio : public Audio
{
public:
	StreamedAudio();
	~StreamedAudio() override;

	void Initialise(const char* filename, bool loop = false) override;
	void Play() override;
	void Pause() override;
	void Stop() override;
	void SetPlayingOffset(float seconds) override;
	void SetVolume(float volume) override; //0.0f to 100.0f.
	bool HasFinished() override;

private:

	sf::Music m_StreamedAudio;
};

#endif
