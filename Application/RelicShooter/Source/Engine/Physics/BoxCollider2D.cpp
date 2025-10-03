#include "BoxCollider2D.h"
#include "CircleCollider2D.h"

BoxCollider2D::BoxCollider2D()
{

}

BoxCollider2D::~BoxCollider2D()
{
	
}

bool BoxCollider2D::CollidesWith(Collider2D* pCollider2D)
{
	return pCollider2D->CollidesWith(this);
}

bool BoxCollider2D::CollidesWith(BoxCollider2D* pBoxCollider2D)
{
	if (!pBoxCollider2D)
		return false;
	
	return Collider2D::RectangleRectangleCollision(this, pBoxCollider2D);

}

bool BoxCollider2D::CollidesWith(CircleCollider2D* pCircleCollider2D)
{
	return Collider2D::RctangleCircleCollision(this, pCircleCollider2D);
}
