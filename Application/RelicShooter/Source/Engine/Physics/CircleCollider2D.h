#ifndef _CIRCLE_COLLIDER_2D_H
#define _CIRCLE_COLLIDER_2D_H

#include "Collider2D.h"
#include <SFML/Graphics.hpp>

class CircleCollider2D : public Collider2D
{
public:
	CircleCollider2D() = default;
	virtual ~CircleCollider2D() = default;

	bool CollidesWith(Collider2D& pCollider2D) override;
	bool CollidesWith(BoxCollider2D& pBoxCollider2D) override;
	bool CollidesWith(CircleCollider2D& pCircleCollider2D) override;

	sf::Vector2f GetPosition();
	float GetRadius();

protected:
	sf::Vector2f m_centrePosition;
	float m_radius;
};

#endif
