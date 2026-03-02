#include "AmmoCollectible.h"
#include "../../DebugHandler.hpp"
#include "../Player/Player.h"

AmmoCollectible::AmmoCollectible()
{
	LOG("Ammo collectible created.")
}

AmmoCollectible::~AmmoCollectible()
{
	
}

void AmmoCollectible::Initialise(Player* player)
{
	m_player = player;

	m_value = m_player->GetMaxAmmo();
	m_Sprite.Initialise("sprites/Collectibles/spr_pickup_ammo_0.png", sf::Color::White, 1);
	
	m_collectibleSize = { 25, 1 };
	m_collisionRect = {0, 0, m_collectibleSize.x, m_collectibleSize.y};

	m_Sprite.AddToRenderQueue();
}

void AmmoCollectible::CheckCollisions()
{
	m_collided = CollidesWith(*m_player);

	if (m_collided)
	{
		m_player->IncreaseAmmo(m_value);
		m_collected = true;
	}
}
