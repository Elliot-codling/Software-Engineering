#ifndef _BOX_COLLIDER_2D
#define _BOX_COLLIDER_2D

#include "Collider2D.h"
#include <SFML/Graphics.hpp>

class BoxCollider2D : public Collider2D
{
public:
	BoxCollider2D();
	~BoxCollider2D() override;

	bool CollidesWith(Collider2D* pCollider2D) override;
	bool CollidesWith(BoxCollider2D* pBoxCollider2D) override;
	bool CollidesWith(CircleCollider2D* pCircleCollider2D) override;

//protected:

	sf::FloatRect m_CollisionRect;
};

#endif

