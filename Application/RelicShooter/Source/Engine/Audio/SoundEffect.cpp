#include "SoundEffect.h"
#include "../System/Context/SysContextProvider.h"
#include "../System/Assets/AssetManager.h"


SoundEffect::SoundEffect()
= default;

SoundEffect::~SoundEffect()
= default;

void SoundEffect::Initialise(const char* filename, bool loop)
{
	auto* pAssetManager = C_SysContext::Get<AssetManager>();
	m_Sound.setBuffer(pAssetManager->GetSoundBuffer(filename));
	m_Sound.setLoop(loop);
	m_Initialised = true;
}

void SoundEffect::Play()
{
	if (m_Initialised)
	{
		m_Sound.play();
	}
}

void SoundEffect::Pause()
{
	if (m_Initialised)
	{
		m_Sound.pause();
	}
}

void SoundEffect::Stop()
{
	if (m_Initialised)
	{
		m_Sound.stop();
	}
}

void SoundEffect::SetPlayingOffset(const float seconds)
{
	if (m_Initialised)
	{
		m_Sound.setPlayingOffset(sf::seconds(seconds));
	}
}

void SoundEffect::SetVolume(const float volume)
{
	if (m_Initialised)
	{
		m_Sound.setVolume(volume);
	}
}

bool SoundEffect::HasFinished()
{
	if (m_Initialised)
	{
		if (m_Sound.getStatus() == sf::SoundSource::Status::Stopped)
		{
			return true;
		}

		return false;
	}

	return true;
}
