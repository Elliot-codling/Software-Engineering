#include "GameState.h"
#include "../../Core/GameObject.h"
#include "../../Utils/Utils.h"

#include "../Context/SysContextProvider.h"
#include "../../Audio/AudioManager.h"

#include "../../Physics/Collider2D.h"

#include <SFML/Graphics.hpp>

GameState::GameState()
	:m_bSwallowRender(true)
	,m_bSwallowUpdate(true)
{
}

GameState::~GameState()
{
	m_GameObjects.clear();
	
	AudioManager* pAudioManager = C_SysContext::Get<AudioManager>();
	pAudioManager->RemoveAllAudioObjects();
}

void GameState::Update()
{
	AddAndRemoveGameObjects();
}

void GameState::FixedUpdate()
{
	UpdateGameObjects();	
}

void GameState::UpdateGameObjects()
{
	//update game objects
	std::vector<GameObject*>::iterator iter;
	for (iter = m_GameObjects.begin(); iter != m_GameObjects.end(); iter++)
	{
		(*iter)->Update();
	}	
}

void GameState::AddAndRemoveGameObjects()
{
	//add any game objects from the add queue
	std::vector<GameObject*>::iterator gameObjectAddQueueIter;
	for (gameObjectAddQueueIter = m_GameObjectsAddQueue.begin(); gameObjectAddQueueIter != m_GameObjectsAddQueue.end(); gameObjectAddQueueIter++)
	{
		m_GameObjects.emplace_back(*gameObjectAddQueueIter);
	}
	m_GameObjectsAddQueue.clear();


	//remove game objects from the remove queue
	std::vector<GameObject*>::iterator gameObjectRemoveQueueIter;
	for (gameObjectRemoveQueueIter = m_GameObjectsRemoveQueue.begin(); gameObjectRemoveQueueIter != m_GameObjectsRemoveQueue.end(); gameObjectRemoveQueueIter++)
	{
		std::vector<GameObject*>::iterator gameObjectListIter;
		for (gameObjectListIter = m_GameObjects.begin(); gameObjectListIter != m_GameObjects.end(); )
		{
			if ((*gameObjectListIter) == (*gameObjectRemoveQueueIter))
			{
				GameObject* pGameObject = *gameObjectListIter;
				gameObjectListIter = m_GameObjects.erase(gameObjectListIter);
				SAFE_DELETE_PTR(pGameObject);
			}
			else
			{
				gameObjectListIter++;
			}
		}
	}
	m_GameObjectsRemoveQueue.clear();
}

void GameState::AddGameObject(GameObject* pGameObject)
{
	m_GameObjectsAddQueue.emplace_back(pGameObject);
}

void GameState::RemoveGameObject(GameObject* pGameObject)
{
	m_GameObjectsRemoveQueue.emplace_back(pGameObject);
}