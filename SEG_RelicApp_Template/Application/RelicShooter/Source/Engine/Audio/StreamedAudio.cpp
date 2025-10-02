#include "StreamedAudio.h"

StreamedAudio::StreamedAudio()
= default;

StreamedAudio::~StreamedAudio()
= default;

void StreamedAudio::Initialise(const char* filename, const bool loop)
{
	if (m_StreamedAudio.openFromFile(filename))
	{
		m_StreamedAudio.setLoop(loop);
		m_Initialised = true;
	}
}

void StreamedAudio::Play()
{
	if (m_Initialised)
	{
		m_StreamedAudio.play();
	}
}

void StreamedAudio::Pause()
{
	if (m_Initialised)
	{
		m_StreamedAudio.pause();
	}
}

void StreamedAudio::Stop()
{
	if (m_Initialised)
	{
		m_StreamedAudio.stop();
	}
}

void StreamedAudio::SetPlayingOffset(const float seconds)
{
	if (m_Initialised)
	{
		m_StreamedAudio.setPlayingOffset(sf::seconds(seconds));
	}
}

void StreamedAudio::SetVolume(const float volume)
{
	if (m_Initialised)
	{
		m_StreamedAudio.setVolume(volume);
	}
}

bool StreamedAudio::HasFinished()
{
	if (m_Initialised)
	{
		if (m_StreamedAudio.getStatus() == sf::SoundSource::Status::Stopped)
		{
			return true;
		}

		return false;
	}

	return true;
}
