#pragma once
#include <SFML/System/Vector2.hpp>

#include "../../../Engine/Physics/BoxCollider2D.h"
#include "../BaseGameObjects/GameObjectWithSprite.h"

class Player;

class Item : public GameObjectWithSprite, public BoxCollider2D
{
public:
	Item() {}
	~Item() {}

	// Function to correctly position the item's hitbox
	void FixHitboxPosition(sf::Vector2f position);

	virtual void CheckCollisions();
	bool IsCollected();

protected:

	// A reference of the player, for collisions
	Player* m_player;

	bool		  m_collided;
	bool		  m_collected = false;

	sf::Vector2f  m_position;
	int			  m_value;
	sf::Vector2f  m_collectibleSize;
};

