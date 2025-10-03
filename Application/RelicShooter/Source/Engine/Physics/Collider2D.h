#ifndef _COLLIDER_2D_H
#define _COLLIDER_2D_H

class BoxCollider2D;
class CircleCollider2D;

class Collider2D
{
public:
	Collider2D();
	virtual ~Collider2D();

	virtual bool CollidesWith(Collider2D* pCollider2D) = 0;
	virtual bool CollidesWith(BoxCollider2D* pBoxCollider2D) = 0;
	virtual bool CollidesWith(CircleCollider2D* pCircleCollider2D) = 0;

	virtual void OnCollision(Collider2D* pCollider2D) = 0;

	static bool CircleCircleCollision(CircleCollider2D* pCircleA, CircleCollider2D* pCircleB);
	static bool RectangleRectangleCollision(BoxCollider2D* pBoxA, BoxCollider2D* pBoxB);
	static bool RctangleCircleCollision(BoxCollider2D* pBoxA, CircleCollider2D* pCircleA);

private:	

};

#endif
