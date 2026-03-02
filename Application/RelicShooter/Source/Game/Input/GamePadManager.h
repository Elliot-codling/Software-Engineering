#pragma once

class GamePadManager
{
public:
	// Create singleton
	GamePadManager(const GamePadManager&) = delete;

	static GamePadManager& Get()
	{
		return s_instance;
	}

	GamePad* GetGamePad(int controllerID)
	{
		return &m_gamepadControllers[controllerID];
	}

private:
	GamePadManager() {}

	static GamePadManager s_instance;

	GamePad m_gamepadControllers[1];
	
};

