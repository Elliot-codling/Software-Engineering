#include "GameStateTest.h"



void GameStateTest::Initialise()
{
	GameObjectWithText* object = new GameObjectWithText();
	object->Initialise();

	object->SetFont("fonts/8-BIT WONDER.ttf");
	object->SetText("Among us");
	object->SetColor({ 255, 255, 255 });
	object->SetFontSize(60);
	object->SetPosition(600.0f, 400.0f);

	m_GameObjects.push_back(object);

}

void GameStateTest::Update()
{

	GameState::Update();
}
