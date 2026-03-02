#include "Game.h"

#include <iostream>
#include <string>


#include "../Engine/Utils/Utils.h"
#include "../Engine/System/Context/SysContextProvider.h"
#include "../Engine/Input/InputDevice.h"
#include "GameStates/GameplayState.h"
#include "GameStates/GameStateTest.h"
#include "GameStates/MainMenuState.h"
#include "Input/ControllerInputDevice.h"
#include "Input/KeyboardAndMouseInputDevice.h"


#include "DebugHandler.hpp"
#include "Input/GamePadManager.h"

const int WINDOW_WIDTH = 1920;
const int WINDOW_HEIGHT = 1080;
const char* WINDOW_NAME = "SEG - Relic Shooter";

GamePadManager GamePadManager::s_instance;

Game::Game()
	:m_bExit(false), m_mainMenuState(WINDOW_WIDTH, WINDOW_HEIGHT)
{
}

Game::~Game()
{
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
	m_RenderManager.Initialise(WINDOW_WIDTH, WINDOW_HEIGHT,WINDOW_NAME);
	C_SysContext::Set<RenderManager>(&m_RenderManager);

	//setup the audio manager
	C_SysContext::Set<AudioManager>(&m_AudioManager);

	//setup the input manager
	C_SysContext::Set<InputManager>(&m_InputManager);

	//setup the game state manager
	m_GameStateManager.Initialise();
	C_SysContext::Set<GameStateManager>(&m_GameStateManager);
	
	bool joystickConnected = GamePadManager::Get().GetGamePad(0)->CheckConnection();
	if (joystickConnected)
	{
		LOG("Controller detected, switching to controller input.")
		auto inputDevice = std::make_unique<ControllerInputDevice>();
		inputDevice->Initalise();
		m_InputManager.SetInputDevice(std::move(inputDevice));
	}
	else
	{
		LOG("No controller detected, defaulting to keyboard and mouse input.")
		auto inputDevice = std::make_unique<KeyboardAndMouseInputDevice>();
		inputDevice->Initalise();
		m_InputManager.SetInputDevice(std::move(inputDevice));
	}
	
	// Create Main Menu State
	m_GameStateManager.QueueGameState(&m_mainMenuState);
	
}

void Game::Run()
{
	m_FrameTimer.Initialise();

	while (!m_bExit)
	{
	    if (!m_WindowManager.GetWindow().isOpen()) {
			m_bExit = true;
	    }

		//start of game frame
		m_FrameTimer.StartFrame();

		UpdateGame();

		//render
		m_RenderManager.Render();

		//update Player Input First
		m_InputManager.Update();

		//end of game frame
		m_FrameTimer.EndFrame();	
	}
}

void Game::UpdateGame()
{
	if (!m_WindowManager.GetWindow().hasFocus())
	{
		m_WindowManager.GetWindow().setFramerateLimit(m_idleFramerate);
		return;
	}
	m_WindowManager.GetWindow().setFramerateLimit(m_framerate);

	while (m_FrameTimer.FixedUpdate())
	{
		m_GameStateManager.FixedUpdate();
	}
	//update the game state
	m_GameStateManager.Update();

	//update the audio manager
	m_AudioManager.Update();

	
}
