#include "Ball.h"
#include "../../Core/Renderer/ConsoleColours.h"
#include "../../Core/Renderer/ASCIIRenderer.h"

int BallSprite[]=
{
	BACKGROUND_RED,
};

Ball::Ball()
{
}

Ball::~Ball()
{
}

void Ball::Initialise(Vector2& courtSize)
{
	m_CourtSize = courtSize;

	Sprite::Initialise(BallSprite, Vector2(1, 1));

	m_MovementDirecteion.x = 1;
	m_MovementDirecteion.y = 1;
}

void Ball::Update()
{
	m_PreviousPosition = GetPosition();
	SetPosition(GetPosition().x + m_MovementDirecteion.x, GetPosition().y + m_MovementDirecteion.y);

	if (CollideWithVerticalWalls())
	{
		SetPosition(m_PreviousPosition);
		m_MovementDirecteion.x = -m_MovementDirecteion.x;
		SetPosition(GetPosition().x + m_MovementDirecteion.x, GetPosition().y + m_MovementDirecteion.y);
	}
	else if (CollideWithHorizontalWalls())
	{
		SetPosition(m_PreviousPosition);
		m_MovementDirecteion.y = -m_MovementDirecteion.y;
		SetPosition(GetPosition().x + m_MovementDirecteion.x, GetPosition().y + m_MovementDirecteion.y);
	}
}

void Ball::BounceOffPaddle()
{
	SetPosition(m_PreviousPosition);
	m_MovementDirecteion.x = -m_MovementDirecteion.x;
	SetPosition(GetPosition().x + m_MovementDirecteion.x, GetPosition().y + m_MovementDirecteion.y);
}

void Ball::Render(ASCIIRenderer* pRenderer)
{
	Sprite::Render(pRenderer);
}

bool Ball::CollideWithVerticalWalls()
{
	if (GetPosition().x < 0 || GetPosition().x >= m_CourtSize.x)
	{
		return true;
	}

	return false;
}

bool Ball::CollideWithHorizontalWalls()
{
	if (GetPosition().y < 0 || GetPosition().y >= m_CourtSize.y)
	{
		return true;
	}

	return false;
}

