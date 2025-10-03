#pragma once

#include "../../Engine/System/GameState/GameState.h"

class GameStateTest : public GameState
{
public:
	GameStateTest();
	~GameStateTest() override;

public: 
	GameObject* GetPlayer() override;
	void Initialise() override;
	void Update() override;
};

