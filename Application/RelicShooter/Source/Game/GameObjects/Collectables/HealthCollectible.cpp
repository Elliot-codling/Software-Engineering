#include "HealthCollectible.h"
#include "../../DebugHandler.hpp"
#include "../Player/Player.h"

HealthCollectible::HealthCollectible()
{
	LOG("Health collectible created.")
}

HealthCollectible::~HealthCollectible()
{
	
}

void HealthCollectible::Initialise(Player* player)
{
	m_player = player;

	m_value = 20;
	m_Sprite.Initialise("sprites/Collectibles/spr_pickup_health_0.png", sf::Color::White, 1);

	m_collectibleSize = { 50, 50 };
	m_collisionRect = { 0, 0, m_collectibleSize.x, m_collectibleSize.y };

	m_Sprite.AddToRenderQueue();
}

void HealthCollectible::CheckCollisions()
{
	m_collided = CollidesWith(*m_player);

	if (m_collided && m_player->GetHealth() < m_player->GetMaxHealth())
	{
		m_player->IncreaseHealth(m_value);
		m_collected = true;
	}
}
