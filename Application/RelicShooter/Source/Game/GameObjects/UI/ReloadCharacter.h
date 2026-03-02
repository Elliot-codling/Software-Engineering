#pragma once
#include "../BaseGameObjects/GameObjectWithAnimatedSprite.h"

class BaseWeapon;

class ReloadCharacter : public GameObjectWithAnimatedSprite
{
public:
	ReloadCharacter() = default;
	~ReloadCharacter() override = default;

public:
	void Initialise() override;
	void Update() override;
	void UpdateReloadState(const BaseWeapon* weapon);

private:
	// Animation setup
	enum ReloadStates
	{
		Normal,
		Reloading,
		STATE_MAX
	};

	const char* m_animationImageName[STATE_MAX] =
	{
		"spr_reload_blank",
		"spr_reload_char"
	};
};

