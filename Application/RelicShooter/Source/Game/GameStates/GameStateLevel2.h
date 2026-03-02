#pragma once

#include "../../Engine/System/GameState/GameState.h"
#include "../GameObjects/Player/Player.h"
#include "../GameObjects/Enemies/Walker.h"
#include "../GameData/TileMap.h"
#include "../GameData/EnemyWave.h"
#include "../GameObjects/Enemies/Kamikaze.h"
#include "../GameObjects/Enemies/Shooter.h"
#include "../GameObjects/UI/Crosshair.h"
#include "../GameObjects/UI/HUD/UIManager.h"
#include "../GameObjects/Weapons/Rifle.h"
#include "../GameObjects/Weapons/Shotgun.h"
#include "../GameObjects/Factories/ItemFactory.h"
#include "../Handlers/GameEndHandler.h"

class GameStateLevel2 : public GameState
{
public:
	GameStateLevel2() = default;
	~GameStateLevel2() override;

	GameObject* GetPlayer() override;
	void Initialise() override;
	void Update() override;
	void FixedUpdate() override;

	void DeleteEnemy(Enemy* enemy);
	void DeleteCollectible(Item* item);

	void SpawnWave(EnemyWave* wave, int* waveMap);
	void Wave1Start();
	void Wave2Start();
	void Wave3Start();

private:
	GameObjectWithSprite* newObject = new GameObjectWithSprite();
	std::vector<Enemy*> m_enemies;
	std::vector<BaseWeapon*> m_weapons;
	bool m_gotWeapon = false;

	Shotgun* m_shotgun = nullptr;
	Rifle* m_rifle = nullptr;
	Walker* m_walker = nullptr;
	Kamikaze* m_kamikaze = nullptr;
	Shooter* m_shooter = nullptr;

	EnemyWave* m_wave1;
	EnemyWave* m_wave2;
	EnemyWave* m_wave3;
	int m_currentWave = 0;
	bool m_waveUpdate = true;
	bool m_levelComplete = false;

	Player m_playerCharacter;
	TileMap m_backgroundTilemap;
	TileMap m_collisionTileMap;
	TileMap m_bulletCollisionTilemap;
	UIManager m_UIManager;
	Crosshair m_crosshair;
	GameEndHandler m_gameEndHandler;

	ItemFactory* m_itemGenerator;
	Item* m_collectible;
	std::vector<Item*> m_itemList;

	std::chrono::time_point<std::chrono::system_clock> m_waveDelay;
	bool m_initialiseWaveRespawn = false;
};

