#ifndef _GAME_STATE_H
#define _GAME_STATE_H

#include <vector>

class GameObject;
class Collider2D;

class GameState
{
public:
	GameState();
	virtual ~GameState();

	virtual void Initialise() = 0;
	virtual void Update();
	virtual GameObject* GetPlayer() = 0;

	bool SwallowRender() { return m_bSwallowRender; }
	bool SwallowUpdate() { return m_bSwallowUpdate; }

	void AddGameObject(GameObject* pGameObject);
	void RemoveGameObject(GameObject* pGameObject);

	void AddCollider(Collider2D* pCollider);
	void RemoveCollider(Collider2D* pCollider);

protected:

	void UpdateGameObjects();
	void AddAndRemoveGameObjects();

	void UpdateCollisions();
	void AddAndRemoveColliders();

	std::vector<GameObject*> m_GameObjects;
	std::vector<GameObject*> m_GameObjectsAddQueue;
	std::vector<GameObject*> m_GameObjectsRemoveQueue;


	std::vector<Collider2D* > m_2DColliders;
	std::vector<Collider2D* > m_2DCollidersAddQueue;
	std::vector<Collider2D* > m_2DCollidersRemoveQueue;


	bool m_bSwallowRender;
	bool m_bSwallowUpdate;
};

#endif
