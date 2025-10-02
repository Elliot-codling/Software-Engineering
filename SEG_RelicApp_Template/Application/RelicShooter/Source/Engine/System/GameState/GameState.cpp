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
	for (auto& m_GameObject : m_GameObjects)
	{
		SAFE_DELETE_PTR(m_GameObject)
	}

	auto* pAudioManager = C_SysContext::Get<AudioManager>();
	pAudioManager->RemoveAllAudioObjects();
}

void GameState::Update()
{
	//Update each Game Object
	UpdateGameObjects();
	//Process Collisions
	UpdateCollisions();
	//Spawn new and cleanup retired game objects
	AddAndRemoveGameObjects();
	//Spawn new and cleanup retired collision objects
	AddAndRemoveColliders();
}

void GameState::UpdateGameObjects()
{
	for (const auto& m_GameObject : m_GameObjects)
	{
		m_GameObject->Update();
	}	
}

void GameState::AddAndRemoveGameObjects()
{
	for (auto& gameObjectAddQueueIter : m_GameObjectsAddQueue)
	{
		m_GameObjects.push_back(gameObjectAddQueueIter);
	}
	m_GameObjectsAddQueue.clear();


	for (auto& gameObjectRemoveQueueIter : m_GameObjectsRemoveQueue)
	{
		std::vector<GameObject*>::iterator gameObjectListIter;
		for (gameObjectListIter = m_GameObjects.begin(); gameObjectListIter != m_GameObjects.end(); )
		{
			if (*gameObjectListIter == gameObjectRemoveQueueIter)
			{
				const GameObject* pGameObject = *gameObjectListIter;
				gameObjectListIter = m_GameObjects.erase(gameObjectListIter);
				SAFE_DELETE_PTR(pGameObject)
			}
			else
			{
				++gameObjectListIter;
			}
		}
	}
	m_GameObjectsRemoveQueue.clear();
}

void GameState::UpdateCollisions()
{
	//update game objects
	for (size_t i = 0; i < m_2DColliders.size(); i++)
	{
		for (size_t j = i + 1; j < m_2DColliders.size(); j++)
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
	for (auto& collider2DAddQueueIter : m_2DCollidersAddQueue)
	{
		m_2DColliders.push_back(collider2DAddQueueIter);
	}
	m_2DCollidersAddQueue.clear();


	for (const auto& collider2DRemoveQueueIter : m_2DCollidersRemoveQueue)
	{
		std::vector<Collider2D*>::iterator collider2DListIter;
		for (collider2DListIter = m_2DColliders.begin(); collider2DListIter != m_2DColliders.end(); )
		{
			if (*collider2DListIter == collider2DRemoveQueueIter)
			{
				
				collider2DListIter = m_2DColliders.erase(collider2DListIter);
			}
			else
			{
				++collider2DListIter;
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

