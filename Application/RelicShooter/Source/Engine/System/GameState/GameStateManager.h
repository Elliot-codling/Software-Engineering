#ifndef _GAME_STATE_MANAGER_H
#define _GAME_STATE_MANAGER_H

#include <vector>


class GameState;

class GameStateManager
{
public:
	GameStateManager();
	~GameStateManager();

	static void Initialise();
	void Update();

	void QueueGameState(GameState* pGameState);
	void QueuePop();
	
	GameState* GetCurrentGameState() { return m_GameStates.back(); }

private:
	
	void PushGameState(GameState* pGameState);
	void PopGameState();

	std::vector<GameState*> m_GameStates;

	std::vector<GameState*> m_GameStateQueue;

	bool m_bPopGameState;
};

#endif
