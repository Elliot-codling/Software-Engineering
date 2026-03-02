#include "GameStateTest.h"

#include "MainMenuState.h"
#include "../DebugHandler.hpp"
#include "../../Engine/Renderer/FrameTimer.h"
#include "../../Engine/Renderer/RenderManager.h"
#include "../../Engine/Renderer/WindowManager.h"
#include "../Layers/Layer.h"
#include "../../Engine/System/Context/SysContextProvider.h"
#include "../../Engine/Utils/Utils.h"
#include "../GameObjects/BaseGameObjects/GameObjectWithText.h"
#include "../Input/InputWrapper.h"

GameStateTest::~GameStateTest()
{
}

GameObject* GameStateTest::GetPlayer()
{
	//TODO:  We don't have a Player Object yet to use!
	return nullptr;
}

/**
 * \brief Called when the State is first loaded.
 * Sets up the Initial State of the Screen.
 */
void GameStateTest::Initialise()
{

	//GameDataManager* pGameDataManager = C_SysContext::Get<GameDataManager>();
	//SpritesheetDef* pSSDef = pGameDataManager->GetSpritesheetDef("backgrounds/bg_desert_edit.xml");

	backgroundTilemap.Initialise();
	backgroundTilemap.LoadFromFile("backgrounds/tilemaps/desertlevel0.txt", "backgrounds/bg_desert_edit.xml");

	m_GameObjects.push_back(&backgroundTilemap);

	collisionTileMap.Initialise();
	collisionTileMap.LoadFromFile("backgrounds/tilemaps/desertlevelplayercollision.txt", "backgrounds/bg_desert_edit.xml");

	m_GameObjects.push_back(&collisionTileMap);

	//Add a Text Object
	GameObjectWithText* tText = new GameObjectWithText();
	//Add it to the Renderer
	tText->SetDisplayText("test level");
	tText->SetPosition(50.f, 0.f);
	tText->Initialise();

	//Add it to the Game Objects
	this->m_GameObjects.push_back(tText);

	//Add a Text Object
	GameObjectWithText* tText2 = new GameObjectWithText();
	tText2->SetCharSize(50);
	tText2->SetDisplayText("let me be clear");
	tText2->SetColour(sf::Color::Blue);
	tText2->SetFontFile("fonts/wendy.ttf");
	tText2->SetPosition(sf::Vector2f(200.f,100.f));

	//Add it to the Renderer
	tText2->Initialise();

	//Add it to the Game Objects
	this->m_GameObjects.push_back(tText2);

	GameObjectWithSprite* tSprite = new GameObjectWithSprite();
	tSprite->SetPosition(sf::Vector2f(300,300));
	tSprite->Initialise();
	this->m_GameObjects.push_back(tSprite);

	GameObjectWithSprite* tSprite2 = new GameObjectWithSprite();
	tSprite2->SetSpriteFile("sprites/spr_pistol_jimmy_0.png");
	tSprite2->SetColour(sf::Color::Blue);
	tSprite2->SetScale(2.0f);
	tSprite2->Initialise();
	tSprite2->SetPosition(sf::Vector2f(500,500));
	this->m_GameObjects.push_back(tSprite2);

	object.SetPosition({1920, 1120});
	object.Initialise();
	
	m_GameObjects.push_back(&object);

	m_walker = new Walker();
	m_walker->Initialise(&object);
	m_walker->SetPosition(192, 192);
	m_enemies.push_back(m_walker);
	AddGameObject(m_walker);

	m_kamikaze = new Kamikaze();
	m_kamikaze->Initialise(&object);
	m_kamikaze->SetPosition(192, 192);
	m_enemies.push_back(m_kamikaze);
	AddGameObject(m_kamikaze);

	m_shooter = new Shooter();
	m_shooter->Initialise(&object, &collisionTileMap);
	m_shooter->SetPosition(192, 192);
	m_enemies.push_back(m_shooter);
	AddGameObject(m_shooter);
	
	newObject->SetSpriteFile("Obama/obama.jpg");
	newObject->SetScale(0.1);
	newObject->SetColour({ 255, 255, 255, 255 });
	newObject->Initialise();
	
	m_GameObjects.push_back(newObject);
	
	C_SysContext::Get<WindowManager>()->SetWindowColor({ 199,128,76 });

	m_UIManager.Initialise(object, m_enemies);
	
	
	m_shotgun = new Shotgun();
	m_shotgun->Initialise();
	m_shotgun->DefineEnemies(&m_enemies);
	m_shotgun->DefineCollisionTilemap(&collisionTileMap);
	
	m_shotgun->setPosition({1920, 600});
	m_weapons.emplace_back(m_shotgun);
	AddGameObject(m_shotgun);
	
	m_rifle = new Rifle();
	m_rifle->Initialise();
	m_rifle->DefineEnemies(&m_enemies);
	m_rifle->DefineCollisionTilemap(&collisionTileMap);
	
	m_rifle->setPosition({1920, 400});
	m_weapons.emplace_back(m_rifle);
	AddGameObject(m_rifle);
	
	m_crosshair.Initialise();

	m_gameEndHandler.Initialise(object, m_UIManager);
	m_gameEndHandler.SetNextGameState(*(new MainMenuState(1920, 1080)));

	srand(time(nullptr));

	// Define a raycast line
	m_raycastLine.Initialise();
	m_raycastLine.SetLength(250);

}

/**
 * \brief Update the Game State Once per Frame
 */
void GameStateTest::Update()
{
	// Update every frame
	GameState::Update();

	m_crosshair.Update();
	object.CameraMovement();

	m_raycastLine.Update(&object);
	m_raycastLine.SetPosition(object.GetPosition());
	object.UpdateRaycast(&m_raycastLine);

	/* Use to kill player */
	if (!wasPPressed && sf::Keyboard::isKeyPressed(sf::Keyboard::P)) {
		object.DoDamage(100);
	}
	wasPPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::P);

	//m_gameEndHandler.Update();
}

void GameStateTest::FixedUpdate()
{
	// Update at 60fps
	GameState::FixedUpdate();
	m_crosshair.ReloadCrosshair(object.GetCurrentWeapon());

	/* Update UI */
	m_UIManager.Update();

	sf::Uint8 currentPercent = newObject->GetColour().a - 1;
	newObject->SetColour({ 255, 255, 255, currentPercent });

	size_t playerTile = collisionTileMap.TileIndexAtPosition(object.GetPosition());
	object.CheckWorldCollisions(playerTile, collisionTileMap.GetWorldCollisions());

	// Update enemies collision
	for (Enemy* enemy : m_enemies)
	{
		size_t enemyTile = collisionTileMap.TileIndexAtPosition(enemy->GetPosition());
		enemy->CheckWorldCollisions(enemyTile, collisionTileMap.GetWorldCollisions());

		if (enemy->IsDead())
		{
			int randNum = rand() % 9;

			if (randNum < 3)
			{
				m_collectible = m_itemGenerator->MakeItem(randNum, &object);
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
		const sf::Vector2f distanceToWeapon = object.GetPosition() - weapon->GetPosition();
		float distance = sqrt((distanceToWeapon.x * distanceToWeapon.x) + (distanceToWeapon.y * distanceToWeapon.y));

		weapon->SetBeingHighlighted(false);
		if (distance > 120.f)
		{
			continue;
		}
		// Less than distance 120
		weapon->SetBeingHighlighted(true);
		DigitalInput* xInput = GetDigitalInput(E_DigitalInput_X);

		if (xInput->GetHoldTime() > 1.f && xInput->IsDown())
		{
			object.PickupWeapon(weapon);
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
}

void GameStateTest::DeleteEnemy(Enemy* enemy)
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

void GameStateTest::DeleteCollectible(Item* item)
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
