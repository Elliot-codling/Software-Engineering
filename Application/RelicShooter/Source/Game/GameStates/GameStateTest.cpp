#include "GameStateTest.h"

#include "../GameObjects/GameObjectWithSprite.h"
#include "../GameObjects/GameObjectWithText.h"

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
	GameObjectWithSprite* pSprite = new GameObjectWithSprite();
	
	//tText->SetCharSize(50);
	//tText->SetDisplayText("Generic Text");
	//tText->SetColour(sf::Color::Blue);
	//tText->SetFontFile("fonts/wendy.ttf");
	//tText->SetPosition(sf::Vector2f(100.f,100.f));

	//Add it to the Renderer
	tText->Initialise();
	pSprite->Initialise();

	
	pSprite->SetPosition(400, 400);

	//Add it to the Game Objects
	this->m_GameObjects.push_back(tText);
	this->m_GameObjects.push_back(pSprite);
	pSprite->ReplaceTexture("sprites/spr_pistol_jimmy_0.png");
	
}

/**
 * \brief Update the Game State Once per Frame
 */
void GameStateTest::Update()
{
	GameState::Update();
}
