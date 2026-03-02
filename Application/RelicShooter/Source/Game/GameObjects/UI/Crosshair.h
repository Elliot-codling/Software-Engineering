#pragma once
#include "../BaseGameObjects/GameObjectWithAnimatedSprite.h"

class BaseWeapon;

class Crosshair : public GameObjectWithAnimatedSprite
{
public:
	Crosshair() = default;
	~Crosshair() override = default;

public:
	void Initialise() override;
	void Update() override;
	void ReloadCrosshair(const BaseWeapon* weapon);

private:
	inline void MoveCrosshair();

private:
	// Window context
	size_t m_windowWidth;
	size_t m_windowHeight;

	// Animation setup
	enum CrosshairStates
	{
		Normal,
		Reloading,
		STATE_MAX
	};

	const char* m_animationImageName[STATE_MAX] =
	{
		"spr_crosshair",
		"spr_crosshair_reload"
	};
};

