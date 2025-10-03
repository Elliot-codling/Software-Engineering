#include "Game.h"

#include <windows.h>
#include <iostream>
#include <string>

#include "../Engine/Utils/Utils.h"
#include "../Engine/System/Context/SysContextProvider.h"
#include "../Engine/Input/InputDevice.h"
#include "GameStates/GameStateTest.h"

const int WINDOW_WIDTH = 1600;
const int WINDOW_HEIGHT = 900;
const std::string WINDOW_NAME = "SEG - Relic Shooter";

Game::Game()
	:m_bExit(false)
	,m_pInputDevice(nullptr)
{
}

Game::~Game()
{
	SAFE_DELETE_PTR(m_pInputDevice);
}

void Game::Initialise()
{
	C_SysContext::Initialise();

	//setup the game data manager
	m_GameDataManager.Initialise();
	C_SysContext::Set<GameDataManager>(&m_GameDataManager);

	//setup the frame timer
	C_SysContext::Set<FrameTimer>(&m_FrameTimer);

	//setup the window manager
	C_SysContext::Set<WindowManager>(&m_WindowManager);

	//setup the asset manager
	C_SysContext::Set<AssetManager>(&m_AssetManager);

	//setup the renderer
	m_RenderManager.Initialise(WINDOW_WIDTH, WINDOW_HEIGHT,WINDOW_NAME.c_str());
	C_SysContext::Set<RenderManager>(&m_RenderManager);

	//setup the audio manager
	C_SysContext::Set<AudioManager>(&m_AudioManager);

	//setup the input manager
	m_InputManager.Initialise();
	C_SysContext::Set<InputManager>(&m_InputManager);

	//setup the game state manager
	m_GameStateManager.Initialise();
	C_SysContext::Set<GameStateManager>(&m_GameStateManager);

	//add a default game state
	GameStateTest* tgamestate = new GameStateTest();
	m_GameStateManager.QueueGameState(tgamestate);


}

void Game::Run()
{
	m_FrameTimer.Initialise();

	while (!m_bExit)
	{
		//start of game frame
		m_FrameTimer.StartFrame();
		
		//update Player Input First
		m_InputManager.Update();

		//update the game state
		m_GameStateManager.Update();

		//update the audio manager
		m_AudioManager.Update();

		//render
		m_RenderManager.Render();

		//end of game frame
		m_FrameTimer.EndFrame();	
	}
}
