#include "Collider2D.h"
#include "BoxCollider2D.h"
#include "CircleCollider2D.h"

#include "../../Engine/System/Context/SysContextProvider.h"
#include "../../Engine/System/GameState/GameStateManager.h"
#include "../../Engine/System/GameState/GameState.h"

#include <math.h>

#include "../../Game/DebugHandler.hpp"
#include "../Core/MathHelpers.h"

bool Collider2D::CircleCircleCollision(CircleCollider2D& pCircleA, CircleCollider2D& pCircleB)
{
	sf::Vector2f difference = pCircleB.GetPosition() - pCircleA.GetPosition();

	float distanceSquared = fabsf(MathHelpers::LengthSquared(difference));
	float radiusSquared = (pCircleA.GetRadius() + pCircleB.GetRadius());
	radiusSquared *= radiusSquared;

	if (distanceSquared < radiusSquared)
	{
		return true;
	}

	return false;
}

bool Collider2D::RectangleRectangleCollision(BoxCollider2D& pBoxA, BoxCollider2D& pBoxB)
{
	const sf::FloatRect boxA = pBoxA.GetCollisionRect();
	const sf::FloatRect boxB = pBoxB.GetCollisionRect();

	if (boxA.intersects(boxB))
	{
		return true;
	}

	return false;
}

bool Collider2D::RectangleCircleCollision(BoxCollider2D& box, CircleCollider2D& circle)
{
	const sf::Vector2f circlePosition = circle.GetPosition();
	const sf::FloatRect testRect = box.GetCollisionRect();
	
	float calcX = circlePosition.x;
	float calcY = circlePosition.y;
	
	if (circlePosition.x < testRect.left)
	{
		calcX = testRect.left;
	}
	else if (circlePosition.x > testRect.left + testRect.width)
	{
		calcX = testRect.left + testRect.width;
	}	
	
	if (circlePosition.y < testRect.top)
	{
		calcY = testRect.top;
	}
	else if (circlePosition.y > testRect.top + testRect.height)
	{
		calcY = testRect.top + testRect.height;
	}
	
	const float distX = circlePosition.x - calcX;
	const float distY = circlePosition.y - calcY;
	const float distance = sqrt((distX * distX) + (distY * distY));
	
	if (distance <= circle.GetRadius())
	{
		return true;
	}
	return false;
	
	
}
