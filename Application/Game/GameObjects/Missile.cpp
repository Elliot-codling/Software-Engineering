#include "Missile.h"
#include "../../Core/Renderer/ConsoleColours.h"


CHAR_INFO MissileSprite[] =
{
	{ ' ' , BACKGROUND_WHITE },
	{ ' ', BACKGROUND_WHITE },
	{ ' ', BACKGROUND_WHITE },
};

CHAR_INFO EnemyMissileSprite[] =
{
	{ ' ', BACKGROUND_YELLOW },
	{ ' ', BACKGROUND_YELLOW },
	{ ' ', BACKGROUND_YELLOW },
};

Missile::Missile()
:m_bInitialised(false)
, m_Active(true)
{

}

Missile::~Missile()
{

}

void Missile::Initialise(Vector2& position, Vector2& velocity)
{
	m_Velocity = velocity;

	Sprite::Initialise(m_Velocity.y < 0.0f ? MissileSprite : EnemyMissileSprite, Vector2(1, 3));

	Vector2 startPosition(position.x - (Sprite::GetSize().x / 2), position.y - (Sprite::GetSize().y / 2));
	SetPosition(startPosition);

	m_bInitialised = true;
}

void Missile::Update()
{
	if (!m_bInitialised || !m_Active)
		return;

	SetPosition(Vector2(GetPosition().x + m_Velocity.x, GetPosition().y + m_Velocity.y));

}

void Missile::Render(ASCIIRenderer* pRenderer)
{
	if (!m_bInitialised || !m_Active)
		return;

	Sprite::Render(pRenderer);
}

void Missile::Explode()
{
	m_Active = false;
}