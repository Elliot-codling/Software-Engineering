#include "GameStateManager.h"

#include "GameState.h"
#include "../../Utils/Utils.h"
#include "../Context/SysContextProvider.h"
#include "../../Renderer/RenderManager.h"

GameStateManager::GameStateManager()
	:m_bPopGameState(false)
{

}

GameStateManager::~GameStateManager()
{
	m_GameStateQueue.clear();
}

void GameStateManager::Initialise()
{

}

void GameStateManager::Update()
{
	for (std::vector<GameState*>::reverse_iterator iter = m_GameStates.rbegin(); iter != m_GameStates.rend(); ++iter)
	{
		(*iter)->Update();

		if ((*iter)->SwallowUpdate())
			break;
	}

	if (m_bPopGameState)
	{
		PopGameState();
	}

	//process the queued game states
	for (std::vector<GameState*>::iterator iter = m_GameStateQueue.begin(); iter != m_GameStateQueue.end(); ++iter)
	{
		PushGameState(*iter);
	}
	m_GameStateQueue.clear();
}

void GameStateManager::PushGameState(GameState* pGameState)
{
	if (!pGameState)
		return;

	RenderManager* pRenderManager = C_SysContext::Get<RenderManager>();
	pRenderManager->PushRenderGroup();

	m_GameStates.push_back(pGameState);
	m_GameStates.back()->Initialise();
}

void GameStateManager::PopGameState()
{
	RenderManager* pRenderManager = C_SysContext::Get<RenderManager>();
	pRenderManager->PopRenderGroup();

	if (m_GameStates.size() > 0)
	{
		SAFE_DELETE_PTR(m_GameStates.back());
		m_GameStates.pop_back();
	}

	m_bPopGameState = false;
}

void GameStateManager::QueueGameState(GameState* pGameState)
{
	if (!pGameState)
		return;

	if (m_GameStates.size() == 0)
	{
		PushGameState(pGameState);
	}
	else
	{
		m_GameStateQueue.push_back(pGameState);
	}
}

void GameStateManager::QueuePop()
{
	m_bPopGameState = true;
}
