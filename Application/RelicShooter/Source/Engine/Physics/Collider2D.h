#ifndef _COLLIDER_2D_H
#define _COLLIDER_2D_H

class BoxCollider2D;
class CircleCollider2D;

class Collider2D
{
public:
	Collider2D() = default;
	Collider2D(const Collider2D&) = delete;
	virtual ~Collider2D() = default;

	virtual bool CollidesWith(Collider2D& pCollider2D) = 0;
	virtual bool CollidesWith(BoxCollider2D& pBoxCollider2D) = 0;
	virtual bool CollidesWith(CircleCollider2D& pCircleCollider2D) = 0;

protected:
	static bool CircleCircleCollision(CircleCollider2D& pCircleA, CircleCollider2D& pCircleB);
	static bool RectangleRectangleCollision(BoxCollider2D& pBoxA, BoxCollider2D& pBoxB);
	static bool RectangleCircleCollision(BoxCollider2D& box, CircleCollider2D& circle);

};

#endif
