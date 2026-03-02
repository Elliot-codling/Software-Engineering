#pragma once
#include <chrono>
#include <SFML/Graphics/Sprite.hpp>

#include "HUD/UIElement.h"

class Player;

class DamageOverlay : public UIElement
{
public:
	DamageOverlay() = default;
	~DamageOverlay();

public:
	void Initialise(Player* player);
	void Update(Player* player);

private:
	inline void ChangeFadeValue();
	inline void CheckFadeBounds();
	bool StartFadeProcess(Player* player);

	// --- Apply fade to overlay ---
	inline void FadeOverlay();

private:
	// Window context
	size_t m_windowWidth;
	size_t m_windowHeight;

	// Sprite
	sf::Sprite m_overlaySprite;

	// Previous player stats
	int m_previousHealth;
	int m_previousSpeed;

	// Fade controls
	std::chrono::time_point<std::chrono::system_clock> m_fadeInFinishTime;
	const float m_fadeInSpeed = 0.1f;			// Measured in seconds
	const float m_fadeOutSpeed = 2.5f;			// Measured in seconds
	const float m_maxFadeValue = 0.6f;			// Will not go above this opacity level
	float m_opacityValue = 0.0f;					// 0 = transparent, 1 = opaque

	enum FadeState
	{
		NotFading,
		FadingIn,
		FadingOut
	};
	FadeState m_currentState = NotFading;

	enum FadeType
	{
		None = 0,
		Damage,
		Speed,
		Heal,
		MAXFADETYPES
	};

	sf::Color m_colorTypes[MAXFADETYPES] = 
	{
		{255, 255, 255},
		{ 255, 0, 0 },
		{ 0, 0, 255 },
		{0, 255, 0}
	};
	FadeType m_currentFadeType = None;
};

