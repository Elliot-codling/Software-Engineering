#include "GameStateTest.h"
#include "../GameObjects/GameObjectWithText.h"
#include "../GameObjects/GameObjectWithSprite.h"
#include "../GameObjects/GameObjectWithAnimatedSprite.h"

GameStateTest::GameStateTest() = default;

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
	//Add a Text Object
	GameObjectWithText* tText = new GameObjectWithText();
	//Add it to the Renderer
	tText->Initialise();

	//Add it to the Game Objects
	this->m_GameObjects.push_back(tText);

	//Add a Text Object
	GameObjectWithText* tText2 = new GameObjectWithText();
	tText2->SetCharSize(50);
	tText2->SetDisplayText("Generic Text");
	tText2->SetColour(sf::Color::Blue);
	tText2->SetFontFile("fonts/wendy.ttf");
	tText2->SetPosition(sf::Vector2f(100.f,100.f));

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



	GameObjectWithAnimatedSprite* object = new GameObjectWithAnimatedSprite();
	object->SetPosition({400, 400});
	object->Initialise();
	
	m_GameObjects.push_back(object);
	
}

/**
 * \brief Update the Game State Once per Frame
 */
void GameStateTest::Update()
{
	GameState::Update();
}
