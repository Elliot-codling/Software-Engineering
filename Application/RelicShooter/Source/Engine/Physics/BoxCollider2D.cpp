#include "BoxCollider2D.h"
#include "CircleCollider2D.h"

bool BoxCollider2D::CollidesWith(Collider2D& pCollider2D)
{
	return pCollider2D.CollidesWith(*this);
}

bool BoxCollider2D::CollidesWith(BoxCollider2D& pBoxCollider2D)
{
	return Collider2D::RectangleRectangleCollision(*this, pBoxCollider2D);
}

bool BoxCollider2D::CollidesWith(CircleCollider2D& pCircleCollider2D)
{
	return Collider2D::RectangleCircleCollision(*this, pCircleCollider2D);
}

sf::FloatRect BoxCollider2D::GetCollisionRect()
{
	return m_collisionRect;
}
