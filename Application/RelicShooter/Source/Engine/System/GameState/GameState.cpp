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
	for (std::vector<GameObject*>::iterator iter = m_GameObjects.begin(); iter != m_GameObjects.end(); iter++)
	{
		SAFE_DELETE_PTR(*iter);
	}
	
	AudioManager* pAudioManager = C_SysContext::Get<AudioManager>();
	pAudioManager->RemoveAllAudioObjects();
}

void GameState::Update()
{
	UpdateGameObjects();

	UpdateCollisions();

	AddAndRemoveGameObjects();

	AddAndRemoveColliders();
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
		m_GameObjects.push_back(*gameObjectAddQueueIter);
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

void GameState::UpdateCollisions()
{
	//update game objects
	for (unsigned int i = 0; i < m_2DColliders.size(); i++)
	{
		for (unsigned int j = i + 1; j < m_2DColliders.size(); j++)
		{
			if (m_2DColliders[i]->CollidesWith(m_2DColliders[j]))
			{
				m_2DColliders[i]->OnCollision(m_2DColliders[j]);
				m_2DColliders[j]->OnCollision(m_2DColliders[i]);
			}
		}
	}	
}

void GameState::AddAndRemoveColliders()
{
	//add any colliders from the add queue
	std::vector<Collider2D*>::iterator collider2DAddQueueIter;
	for (collider2DAddQueueIter = m_2DCollidersAddQueue.begin(); collider2DAddQueueIter != m_2DCollidersAddQueue.end(); collider2DAddQueueIter++)
	{
		m_2DColliders.push_back(*collider2DAddQueueIter);
	}
	m_2DCollidersAddQueue.clear();


	//remove colliders from the remove queue
	std::vector<Collider2D*>::iterator collider2DRemoveQueueIter;
	for (collider2DRemoveQueueIter = m_2DCollidersRemoveQueue.begin(); collider2DRemoveQueueIter != m_2DCollidersRemoveQueue.end(); collider2DRemoveQueueIter++)
	{
		std::vector<Collider2D*>::iterator collider2DListIter;
		for (collider2DListIter = m_2DColliders.begin(); collider2DListIter != m_2DColliders.end(); )
		{
			if ((*collider2DListIter) == (*collider2DRemoveQueueIter))
			{
				Collider2D* pCollider2d = *collider2DListIter;
				collider2DListIter = m_2DColliders.erase(collider2DListIter);
			}
			else
			{
				collider2DListIter++;
			}
		}
	}
	m_2DCollidersRemoveQueue.clear();
}


void GameState::AddGameObject(GameObject* pGameObject)
{
	m_GameObjectsAddQueue.push_back(pGameObject);
}

void GameState::RemoveGameObject(GameObject* pGameObject)
{
	m_GameObjectsRemoveQueue.push_back(pGameObject);
}

void GameState::AddCollider(Collider2D* pCollider)
{
	m_2DCollidersAddQueue.push_back(pCollider);
}

void GameState::RemoveCollider(Collider2D* pCollider)
{
	m_2DCollidersRemoveQueue.push_back(pCollider);
}

