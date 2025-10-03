#ifndef _AUDIO_MANAGER_H
#define _AUDIO_MANAGER_H

#include <vector>

class SoundEffect;
class StreamedAudio;

class AudioManager
{
public:
	AudioManager();
	~AudioManager();

	void PlaySoundFX(const char* filename);
	void PlayMusic(const char* filename);

	void Update();

	void RemoveAllAudioObjects();

private:

	std::vector<SoundEffect*> m_SoundEffects;
	std::vector<StreamedAudio*> m_StreamedAudio;

	int m_NumAudioObjects;
};

#endif
