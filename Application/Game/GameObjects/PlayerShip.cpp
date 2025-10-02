#include "PlayerShip.h"
#include "../../Core/Maths/Vector2.h"
#include "../../Core/Renderer/ConsoleColours.h"
#include <Windows.h>

const int MOVEMENT_SPEED = 2;

CHAR_INFO ShipSprite[]=
{
	{ 0 ,BACKGROUND_BLACK },{ 0 ,BACKGROUND_BLACK },{ 0 ,BACKGROUND_BLACK },{ 0 ,BACKGROUND_BLACK },{ 0 ,BACKGROUND_BLACK },{ 0 ,BACKGROUND_WHITE },{ 0 ,BACKGROUND_WHITE },{ 0 ,BACKGROUND_BLACK },{ 0 ,BACKGROUND_BLACK },{ 0 ,BACKGROUND_BLACK },{ 0 ,BACKGROUND_BLACK },{ 0 ,BACKGROUND_BLACK },
	{ 0 ,BACKGROUND_BLACK },{ 0 ,BACKGROUND_BLACK },{ 0 ,BACKGROUND_BLACK },{ 0 ,BACKGROUND_BLACK },{ 0 ,BACKGROUND_BLACK },{ 0 ,BACKGROUND_WHITE },{ 0 ,BACKGROUND_WHITE },{ 0 ,BACKGROUND_BLACK },{ 0 ,BACKGROUND_BLACK },{ 0 ,BACKGROUND_BLACK },{ 0 ,BACKGROUND_BLACK },{ 0 ,BACKGROUND_BLACK },
	{ 0 ,BACKGROUND_BLACK },{ 0 ,BACKGROUND_BLACK },{ 0 ,BACKGROUND_BLACK },{ 0 ,BACKGROUND_BLACK },{ 0 ,BACKGROUND_WHITE },{ 0 ,BACKGROUND_WHITE },{ 0 ,BACKGROUND_WHITE },{ 0 ,BACKGROUND_WHITE },{ 0 ,BACKGROUND_BLACK },{ 0 ,BACKGROUND_BLACK },{ 0 ,BACKGROUND_BLACK },{ 0 ,BACKGROUND_BLACK },
	{ 0 ,BACKGROUND_BLACK },{ 0 ,BACKGROUND_BLACK },{ 0 ,BACKGROUND_BLACK },{ 0 ,BACKGROUND_BLACK },{ 0 ,BACKGROUND_WHITE },{ 0 ,BACKGROUND_WHITE },{ 0 ,BACKGROUND_WHITE },{ 0 ,BACKGROUND_WHITE },{ 0 ,BACKGROUND_BLACK },{ 0 ,BACKGROUND_BLACK },{ 0 ,BACKGROUND_BLACK },{ 0 ,BACKGROUND_BLACK },
	{ 0 ,BACKGROUND_BLACK },{ 0 ,BACKGROUND_WHITE },{ 0 ,BACKGROUND_WHITE },{ 0 ,BACKGROUND_WHITE },{ 0 ,BACKGROUND_WHITE },{ 0 ,BACKGROUND_WHITE },{ 0 ,BACKGROUND_WHITE },{ 0 ,BACKGROUND_WHITE },{ 0 ,BACKGROUND_WHITE },{ 0 ,BACKGROUND_WHITE },{ 0 ,BACKGROUND_WHITE },{ 0 ,BACKGROUND_BLACK },
	{ 0 ,BACKGROUND_WHITE },{ 0 ,BACKGROUND_WHITE },{ 0 ,BACKGROUND_WHITE },{ 0 ,BACKGROUND_WHITE },{ 0 ,BACKGROUND_WHITE },{ 0 ,BACKGROUND_WHITE },{ 0 ,BACKGROUND_WHITE },{ 0 ,BACKGROUND_WHITE },{ 0 ,BACKGROUND_WHITE },{ 0 ,BACKGROUND_WHITE },{ 0 ,BACKGROUND_WHITE },{ 0 ,BACKGROUND_WHITE },
	{ 0 ,BACKGROUND_WHITE },{ 0 ,BACKGROUND_WHITE },{ 0 ,BACKGROUND_WHITE },{ 0 ,BACKGROUND_WHITE },{ 0 ,BACKGROUND_WHITE },{ 0 ,BACKGROUND_WHITE },{ 0 ,BACKGROUND_WHITE },{ 0 ,BACKGROUND_WHITE },{ 0 ,BACKGROUND_WHITE },{ 0 ,BACKGROUND_WHITE },{ 0 ,BACKGROUND_WHITE },{ 0 ,BACKGROUND_WHITE },
	{ 0 ,BACKGROUND_WHITE },{ 0 ,BACKGROUND_WHITE },{ 0 ,BACKGROUND_WHITE },{ 0 ,BACKGROUND_WHITE },{ 0 ,BACKGROUND_WHITE },{ 0 ,BACKGROUND_WHITE },{ 0 ,BACKGROUND_WHITE },{ 0 ,BACKGROUND_WHITE },{ 0 ,BACKGROUND_WHITE },{ 0 ,BACKGROUND_WHITE },{ 0 ,BACKGROUND_WHITE },{ 0 ,BACKGROUND_WHITE },
};

PlayerShip::PlayerShip()
:m_LeftKey(0)
,m_RightKey(0)
, m_bInitialised(false)
{
}

PlayerShip::~PlayerShip()
{
}

void PlayerShip::Initialise(Vector2& position, int leftKey, int rightKey)
{
	m_LeftKey = leftKey;
	m_RightKey = rightKey;

	Sprite::Initialise(ShipSprite, Vector2(12, 8));

	Vector2 startPosition(position.x - (Sprite::GetSize().x / 2), position.y - (Sprite::GetSize().y / 2));
	SetPosition(startPosition);

	m_bInitialised = true;
}

void PlayerShip::Update()
{
	if (!m_bInitialised)
		return;

}

void PlayerShip::Render(ASCIIRenderer* pRenderer)
{
	if (!m_bInitialised)
		return;

	Sprite::Render(pRenderer);
}

void PlayerShip::MoveLeft()
{
	SetPosition(Vector2(GetPosition().x - MOVEMENT_SPEED, GetPosition().y));

	if (GetPosition().x < 0)
	{
		MoveRight();
	}
}

void PlayerShip::MoveRight()
{
	SetPosition(Vector2(GetPosition().x + MOVEMENT_SPEED, GetPosition().y));

	if (GetPosition().x + GetSize().x > SCREEN_WIDTH)
	{
		MoveLeft();
	}
}

bool PlayerShip::LeftKeyPressed()
{
	return (GetKeyState(m_LeftKey) < 0);
}

bool PlayerShip::RightKeyPressed()
{
	return (GetKeyState(m_RightKey) < 0);
}
