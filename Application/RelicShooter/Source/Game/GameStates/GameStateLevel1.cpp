#include "GameStateLevel1.h"

#include "../DebugHandler.hpp"
#include "../../Engine/Renderer/FrameTimer.h"
#include "../../Engine/Renderer/RenderManager.h"
#include "../../Engine/Renderer/WindowManager.h"
#include "../Layers/Layer.h"
#include "../../Engine/System/Context/SysContextProvider.h"
#include "../../Engine/Utils/Utils.h"
#include "../GameObjects/BaseGameObjects/GameObjectWithText.h"
#include "../Input/InputWrapper.h"
#include <fstream>
#include <sstream>
#include <string>

#include "GameStateLevel2.h"

GameStateLevel1::~GameStateLevel1()
{
}

GameObject* GameStateLevel1::GetPlayer()
{
	//TODO:  We don't have a Player Object yet to use!
	return nullptr;
}

/**
 * \brief Called when the State is first loaded.
 * Sets up the Initial State of the Screen.
 */
void GameStateLevel1::Initialise()
{
	C_SysContext::Get<WindowManager>()->SetWindowColor({ 199,128,76 });

	m_backgroundTilemap.Initialise();
	m_backgroundTilemap.LoadFromFile("backgrounds/tilemaps/level1bg.txt", "backgrounds/bg_desert_edit.xml");

	m_GameObjects.push_back(&m_backgroundTilemap);

	m_collisionTileMap.Initialise();
	m_collisionTileMap.LoadFromFile("backgrounds/tilemaps/level1playercollision.txt", "backgrounds/bg_desert_edit.xml");

	m_GameObjects.push_back(&m_collisionTileMap);

	m_bulletCollisionTileMap.Initialise();
	m_bulletCollisionTileMap.LoadFromFile("backgrounds/tilemaps/level1bulletcollision.txt", "backgrounds/bg_desert_edit.xml");

	m_GameObjects.push_back(&m_bulletCollisionTileMap);

	/* Initialise player */
	m_playerCharacter.SetPosition({1920, 1120});
	m_playerCharacter.Initialise();
	m_GameObjects.push_back(&m_playerCharacter);
	
	/* UI Manager */
	m_UIManager.Initialise(m_playerCharacter, m_enemies);
	
	/* Initialise weapons */
	m_shotgun = new Shotgun();
	m_shotgun->Initialise();
	m_shotgun->DefineEnemies(&m_enemies);
	m_shotgun->DefineCollisionTilemap(&m_bulletCollisionTileMap);
	
	m_shotgun->setPosition({1620, 1160 });
	m_weapons.emplace_back(m_shotgun);
	AddGameObject(m_shotgun);
	
	m_rifle = new Rifle();
	m_rifle->Initialise();
	m_rifle->DefineEnemies(&m_enemies);
	m_rifle->DefineCollisionTilemap(&m_bulletCollisionTileMap);
	
	m_rifle->setPosition({2200, 1160 });
	m_weapons.emplace_back(m_rifle);
	AddGameObject(m_rifle);
	/* ------------------------------------------------------ */

	m_gameEndHandler.Initialise(m_playerCharacter, m_UIManager);
	m_gameEndHandler.SetNextGameState(*(new GameStateLevel2()));
	m_gameEndHandler.SetCurrentGameState(*(new GameStateLevel1()));
	m_crosshair.Initialise();

	srand(time(nullptr));

	m_wave1 = new EnemyWave();
	m_wave2 = new EnemyWave();
	m_wave3 = new EnemyWave();

	m_waveMap1 = m_wave1->LoadEnemyWaveFromFile("LevelData/Level1/wave1.txt");
	m_waveMap2 = m_wave2->LoadEnemyWaveFromFile("LevelData/Level1/wave2.txt");
	m_waveMap3 = m_wave3->LoadEnemyWaveFromFile("LevelData/Level1/wave3.txt");

	m_numberOfEnemiesWave1 = SpawnWave(m_wave1, m_waveMap1);
	m_numberOfEnemiesWave2 = SpawnWave(m_wave2, m_waveMap2);
	m_numberOfEnemiesWave3 = SpawnWave(m_wave3, m_waveMap3);
}

/**
 * \brief Update the Game State Once per Frame
 */
void GameStateLevel1::Update()
{
	// Update every frame
	GameState::Update();

	m_crosshair.Update();
	m_playerCharacter.CameraMovement();
}

void GameStateLevel1::FixedUpdate()
{
	// Update at 60fps
	GameState::FixedUpdate();
	m_crosshair.ReloadCrosshair(m_playerCharacter.GetCurrentWeapon());

	/* Update UI */
	m_UIManager.Update();

	size_t playerTile = m_collisionTileMap.TileIndexAtPosition(m_playerCharacter.GetPosition());
	m_playerCharacter.CheckWorldCollisions(playerTile, m_collisionTileMap.GetWorldCollisions());

	// Update enemies collision
	for (Enemy* enemy : m_enemies)
	{
		size_t enemyTile = m_collisionTileMap.TileIndexAtPosition(enemy->GetPosition());
		enemy->CheckWorldCollisions(enemyTile, m_collisionTileMap.GetWorldCollisions());

		if (enemy->IsDead())
		{
			int randNum = rand() % 9;

			if (randNum < 3)
			{
				m_collectible = m_itemGenerator->MakeItem(randNum, &m_playerCharacter);
				m_collectible->SetPosition(enemy->GetPosition());
				m_collectible->SetScale(1.5f);
				m_collectible->FixHitboxPosition(enemy->GetPosition());
				AddGameObject(m_collectible);
				m_itemList.push_back(m_collectible);
			}

			DeleteEnemy(enemy);
		}
	}
	

	// Picking up weapons and highlighting weapons within a given distance
	for (BaseWeapon* weapon : m_weapons)
	{
		const sf::Vector2f distanceToWeapon = m_playerCharacter.GetPosition() - weapon->GetPosition();
		float distance = sqrt((distanceToWeapon.x * distanceToWeapon.x) + (distanceToWeapon.y * distanceToWeapon.y));

		weapon->SetBeingHighlighted(false);
		if (distance > 120.f)
		{
			continue;
		}
		// Less than distance 120
		weapon->SetBeingHighlighted(true);
		DigitalInput* xInput = GetDigitalInput(E_DigitalInput_X);

		if (xInput->HasCompletedCycle())
		{
			m_playerCharacter.PickupWeapon(weapon);
			m_gotWeapon = true;
		}
	}

	// Update the collectible items
	for (Item* item : m_itemList)
	{
		item->CheckCollisions();

		if (item->IsCollected())
		{
			DeleteCollectible(item);
		}
	}

	/* Do not perform wave logic when level is completed */
	if (m_levelComplete) {
		return;
	}

	if (m_enemies.size() == 0)
	{
		m_waveUpdate = true;
		if (!m_initialiseWaveRespawn)
		{
			m_initialiseWaveRespawn = true;
			m_playerCharacter.SetPosition({ 1920, 1120 });
			m_waveDelay = std::chrono::system_clock::now();

		}
	}
		

	std::chrono::duration<float> duration = std::chrono::system_clock::now() - m_waveDelay;
	if (m_gotWeapon && m_waveUpdate && duration.count() >= 3)
	{
		m_initialiseWaveRespawn = false;
		m_currentWave += 1;
		switch (m_currentWave)
		{
		case(1):
			Wave1Start();
			m_UIManager.StartNewWave(m_currentWave, static_cast<int>(m_enemies.size()));
			break;
		case(2):
			Wave2Start();
			m_UIManager.StartNewWave(m_currentWave, static_cast<int>(m_enemies.size()));
			break;
		case(3):
			Wave3Start();
			m_UIManager.StartNewWave(m_currentWave, static_cast<int>(m_enemies.size()));
			break;
		default:
			/* Do win logic here */
			LOG("Level Won")

			m_levelComplete = true;
			m_waveUpdate = false;
			m_playerCharacter.StopCameraMovement();
			break;
		}
	}
	m_gameEndHandler.Update(m_levelComplete);
	if (m_levelComplete || m_playerCharacter.IsDead()) {
		m_levelComplete = true;
		C_SysContext::Get<RenderManager>()->RemoveUIRenderObject(&m_crosshair);
		C_SysContext::Get<RenderManager>()->AddUIRenderObject(&m_crosshair);
	}
}

void GameStateLevel1::DeleteEnemy(Enemy* enemy)
{

	// Example of removing an enemy from the vector and the game
	/// Remove enemy from vector
	std::vector<Enemy*>::iterator it;
	for (it = m_enemies.begin(); it != m_enemies.end(); ++it)
	{
		if (*it == enemy)
		{
			m_enemies.erase(it);
			break;
		}
	}
	// Then remove enemy from the game
	RemoveGameObject(enemy);
}

void GameStateLevel1::DeleteCollectible(Item* item)
{

	// Example of removing an enemy from the vector and the game
	/// Remove enemy from vector
	std::vector<Item*>::iterator it;
	for (it = m_itemList.begin(); it != m_itemList.end(); ++it)
	{
		if (*it == item)
		{
			m_itemList.erase(it);
			break;
		}
	}
	// Then remove enemy from the game
	RemoveGameObject(item);
}

int GameStateLevel1::SpawnWave(EnemyWave* wave, int* waveMap)
{
	int numberOfEnemies = 0;
	sf::Vector2f pos;
	for (int i = 0; i < wave->GetAmountOfTiles(); i++)
	{
		switch (waveMap[i])
		{
		case(2):
			pos = sf::Vector2f((i % 60) * 64, (i / 60) * 64);
			//LOG("Spawned Kamikaze at position { " + std::to_string(pos.x) + ", " + std::to_string(pos.y) + " }")

			m_kamikaze = new Kamikaze();
			m_kamikaze->Initialise(&m_playerCharacter);
			m_kamikaze->SetVisible(false);
			m_kamikaze->SetPosition(pos);
			//m_enemies.push_back(m_kamikaze);
			//AddGameObject(m_kamikaze);
			m_enemyQueue.emplace_back(m_kamikaze);
			numberOfEnemies++;
			break;

		case(3):
			pos = sf::Vector2f((i % 60) * 64, (i / 60) * 64);
			//LOG("Spawned Walker at position { " + std::to_string(pos.x) + ", " + std::to_string(pos.y) + " }")

			m_walker = new Walker();
			m_walker->Initialise(&m_playerCharacter);
			m_walker->SetVisible(false);
			m_walker->SetPosition(pos);
			//m_enemies.push_back(m_walker);
			//AddGameObject(m_walker);
			m_enemyQueue.emplace_back(m_walker);
			numberOfEnemies++;
			break;

		case(4):
			pos = sf::Vector2f((i % 60) * 64, (i / 60) * 64);
			//LOG("Spawned Shooter at position { " + std::to_string(pos.x) + ", " + std::to_string(pos.y) + " }")

			m_shooter = new Shooter();
			m_shooter->Initialise(&m_playerCharacter, &m_bulletCollisionTileMap);
			m_shooter->SetVisible(false);
			m_shooter->SetPosition(pos);
			//m_enemies.push_back(m_shooter);
			//AddGameObject(m_shooter);
			m_enemyQueue.emplace_back(m_shooter);
			numberOfEnemies++;
			break;
		default:
			break;
		}
	}
	return numberOfEnemies;
}

void GameStateLevel1::Wave1Start()
{
	LOG("Wave 1")
	m_waveUpdate = false;
	//SpawnWave(m_wave1, m_waveMap1);
	for (int index = 0; index < m_numberOfEnemiesWave1; index++)
	{
		m_enemies.emplace_back(m_enemyQueue[index]);
		AddGameObject(m_enemies.back());
		m_enemies.back()->SetVisible(true);
	}
}

void GameStateLevel1::Wave2Start()
{
	LOG("Wave 2")
	m_waveUpdate = false;
	//SpawnWave(m_wave2, m_waveMap2);
	for (int index = 0; index < m_numberOfEnemiesWave2; index++)
	{
		m_enemies.emplace_back(m_enemyQueue[index + m_numberOfEnemiesWave1]);
		AddGameObject(m_enemies.back());
		m_enemies.back()->SetVisible(true);
	}
}

void GameStateLevel1::Wave3Start()
{
	LOG("Wave 3")
	m_waveUpdate = false;
	//SpawnWave(m_wave3, m_waveMap3);
	for (int index = 0; index < m_numberOfEnemiesWave3; index++)
	{
		m_enemies.emplace_back(m_enemyQueue[index + m_numberOfEnemiesWave1 + m_numberOfEnemiesWave2]);
		AddGameObject(m_enemies.back());
		m_enemies.back()->SetVisible(true);
	}
}
