#ifndef _STREAMED_AUDIO_H
#define _STREAMED_AUDIO_H

#include "Audio.h"
#include "SFML/Audio.hpp"

class StreamedAudio : public Audio
{
public:
	StreamedAudio();
	virtual ~StreamedAudio();
	
	virtual void Initialise(const char* filename, bool loop = false);
	virtual void Play();
	virtual void Pause();
	virtual void Stop();
	virtual void SetPlayingOffset(const float seconds);
	virtual void SetVolume(const float volume); //0.0f to 100.0f.
	virtual bool HasFinished();

private:

	sf::Music m_StreamedAudio;
};

#endif
