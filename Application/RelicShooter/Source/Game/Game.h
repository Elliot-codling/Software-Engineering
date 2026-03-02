#ifndef _GAME_H
#define _GAME_H

#include "../Engine/Renderer/RenderManager.h"
#include "../Engine/System/Assets/AssetManager.h"
#include "../Engine/Renderer/FrameTimer.h"
#include "../Engine/System/GameState/GameStateManager.h"
#include "../Engine/Audio/AudioManager.h"
#include "../Engine/Input/InputManager.h"
#include "../Engine/Renderer/WindowManager.h"
#include "GameData/GameDataManager.h"
#include "GameStates/MainMenuState.h"

class InputDevice;

class Game
{
public:

	Game();
	~Game();

	void Initialise();
	void Run();

private:
	void UpdateGame();
private:
	MainMenuState m_mainMenuState;
	const int m_framerate = 120;
	const int m_idleFramerate = 10;
	bool m_bExit;

	GameDataManager m_GameDataManager;
	WindowManager m_WindowManager;	
	FrameTimer m_FrameTimer;
	RenderManager m_RenderManager;
	AssetManager m_AssetManager;
	GameStateManager m_GameStateManager;
	AudioManager m_AudioManager;
	InputManager m_InputManager;
};

#endif
