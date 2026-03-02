#pragma once

#include "../../Engine/System/GameState/GameState.h"
#include "../GameObjects/Player/Player.h"
#include "../GameObjects/Enemies/Walker.h"
#include "../GameData/TileMap.h"
#include "../GameObjects/Enemies/Kamikaze.h"
#include "../GameObjects/Enemies/Shooter.h"
#include "../GameObjects/UI/Crosshair.h"
#include "../GameObjects/UI/HUD/UIManager.h"
#include "../GameObjects/Weapons/Rifle.h"
#include "../GameObjects/Weapons/Shotgun.h"
#include "../GameObjects/Factories/ItemFactory.h"
#include "../Handlers/GameEndHandler.h"
#include "../GameObjects/Player/RayCastLine.h"

class GameStateTest : public GameState
{
public:
	GameStateTest() = default;
	~GameStateTest() override;

	GameObject* GetPlayer() override;
	void Initialise() override;
	void Update() override;
	void FixedUpdate() override;

	void DeleteEnemy(Enemy* enemy);
	void DeleteCollectible(Item* item);

private:
	GameObjectWithSprite* newObject = new GameObjectWithSprite();
	std::vector<Enemy*> m_enemies;
	std::vector<BaseWeapon*> m_weapons;

	Shotgun* m_shotgun = nullptr;
	Rifle* m_rifle = nullptr;
	Walker* m_walker = nullptr;
	Kamikaze* m_kamikaze = nullptr;
	Shooter* m_shooter = nullptr;
	
	Player object;
	RayCastLine m_raycastLine;
	TileMap backgroundTilemap;
	TileMap collisionTileMap;
	UIManager m_UIManager;
	GameEndHandler m_gameEndHandler;
	Crosshair m_crosshair;

	ItemFactory* m_itemGenerator;
	Item* m_collectible;
	std::vector<Item*> m_itemList;

	bool wasPPressed = false;
};
