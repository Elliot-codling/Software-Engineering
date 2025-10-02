#include "CircleCollider2D.h"

CircleCollider2D::CircleCollider2D() = default;

CircleCollider2D::~CircleCollider2D() = default;


bool CircleCollider2D::CollidesWith(Collider2D* pCollider2D)
{
	return pCollider2D->CollidesWith(this);
}

bool CircleCollider2D::CollidesWith(BoxCollider2D* pBoxCollider2D)
{
	return RctangleCircleCollision(pBoxCollider2D, this);
}

bool CircleCollider2D::CollidesWith(CircleCollider2D* pCircleCollider2D)
{
	if (!pCircleCollider2D)
		return false;

	return CircleCircleCollision(this, pCircleCollider2D);
}
