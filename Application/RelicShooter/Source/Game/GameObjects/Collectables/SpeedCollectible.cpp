#include "SpeedCollectible.h"
#include "../../DebugHandler.hpp"
#include "../Player/Player.h"

SpeedCollectible::SpeedCollectible()
{
	LOG("Speed collectible created.")
}

SpeedCollectible::~SpeedCollectible()
{
	
}

void SpeedCollectible::Initialise(Player* player)
{
	m_player = player;

	m_Sprite.Initialise("sprites/Collectibles/spr_candyLarge1_0.png", sf::Color::White, 1);

	m_collectibleSize = { 25, 20 };
	m_collisionRect = { 0, 0, m_collectibleSize.x, m_collectibleSize.y };

	m_Sprite.AddToRenderQueue();
}

void SpeedCollectible::CheckCollisions()
{
	m_collided = CollidesWith(*m_player);

	if (m_collided)
	{
		m_player->IncreaseMovementSpeed();
		m_collected = true;
	}
}