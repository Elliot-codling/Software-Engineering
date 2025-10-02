#pragma once
#include "../../Engine/System/GameState/GameState.h"
#include "../GameObjects/GameObjectWithText.h"

class GameStateTest : public GameState
{
public:
	GameStateTest() {};
	~GameStateTest() override {};

	void Initialise() override;
	void Update() override;
	GameObject* GetPlayer() override { return nullptr; }
};

