#include "CircleCollider2D.h"

#include <math.h>
#include "../Core/MathHelpers.h"


bool CircleCollider2D::CollidesWith(Collider2D& pCollider2D)
{
	return pCollider2D.CollidesWith(*this);
}

bool CircleCollider2D::CollidesWith(BoxCollider2D& pBoxCollider2D)
{
	return Collider2D::RectangleCircleCollision(pBoxCollider2D, *this);
}

bool CircleCollider2D::CollidesWith(CircleCollider2D& pCircleCollider2D)
{
	return Collider2D::CircleCircleCollision(*this, pCircleCollider2D);
}

sf::Vector2f CircleCollider2D::GetPosition()
{
	return m_centrePosition;
}

float CircleCollider2D::GetRadius()
{
	return m_radius;
}
