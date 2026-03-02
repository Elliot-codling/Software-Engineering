#pragma once

#include "../../Engine/System/GameState/GameState.h"

class BaseWeapon;
#include "../GameObjects/Player/Player.h"
#include "../GameObjects/UI/Crosshair.h"

class GameplayState : public GameState
{
public:

	GameplayState(int windowWidth, int windowHeight);
	~GameplayState() override = default;

public:
	// Public Functions
	void Initialise() override;
	void Update() override;
	void FixedUpdate() override;

	GameObject* GetPlayer() override { return nullptr; }

private:
	// Private Functions
private:
	// Private members
	int m_windowWidth;
	int m_windowHeight;

	// Objects
	Player m_playerCharacter;
	Crosshair m_crosshair;

	std::vector<BaseWeapon*> m_weapons;

};

