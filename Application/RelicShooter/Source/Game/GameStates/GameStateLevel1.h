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

class GameStateLevel1 : public GameState
{
public:
	GameStateLevel1() = default;
	~GameStateLevel1() override;

	GameObject* GetPlayer() override;
	void Initialise() override;
	void Update() override;
	void FixedUpdate() override;

	void DeleteEnemy(Enemy* enemy);
	void DeleteCollectible(Item* item);

	int SpawnWave(EnemyWave* wave, int* waveMap);
	void Wave1Start();
	void Wave2Start();
	void Wave3Start();

private:
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
	TileMap m_bulletCollisionTileMap;
	UIManager m_UIManager;
	Crosshair m_crosshair;
	GameEndHandler m_gameEndHandler;

	ItemFactory* m_itemGenerator;
	Item* m_collectible;
	std::vector<Item*> m_itemList;

	// Waves
	int* m_waveMap1 = nullptr;
	int* m_waveMap2 = nullptr;
	int* m_waveMap3 = nullptr;

	int m_numberOfEnemiesWave1;
	int m_numberOfEnemiesWave2;
	int m_numberOfEnemiesWave3;

	std::vector<Enemy*> m_enemyQueue;

	std::chrono::time_point<std::chrono::system_clock> m_waveDelay;
	bool m_initialiseWaveRespawn = false;
};
