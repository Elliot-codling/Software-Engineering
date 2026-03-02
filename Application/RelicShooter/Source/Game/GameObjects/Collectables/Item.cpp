#include "Item.h"
#include "../Player/Player.h"

void Item::FixHitboxPosition(sf::Vector2f position)
{
    // Update the collision box's location.
    m_collisionRect.left = position.x - (m_collectibleSize.x / 2.f);
    m_collisionRect.top = position.y - (m_collectibleSize.y / 2.f);
}

void Item::CheckCollisions()
{
	m_collided = CollidesWith(*m_player);

	if (m_collided)
	{
		m_collected = true;
	}
}

bool Item::IsCollected()
{
	return m_collected;
}
