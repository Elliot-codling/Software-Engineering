#include "CircleCollider2D.h"

#include <math.h>
#include "../Core/MathHelpers.h"

CircleCollider2D::CircleCollider2D()
{

}

CircleCollider2D::~CircleCollider2D()
{

}

bool CircleCollider2D::CollidesWith(Collider2D* pCollider2D)
{
	return pCollider2D->CollidesWith(this);
}

bool CircleCollider2D::CollidesWith(BoxCollider2D* pBoxCollider2D)
{
	return Collider2D::RctangleCircleCollision(pBoxCollider2D, this);
}

bool CircleCollider2D::CollidesWith(CircleCollider2D* pCircleCollider2D)
{
	if (!pCircleCollider2D)
		return false;

	return Collider2D::CircleCircleCollision(this, pCircleCollider2D);
}
