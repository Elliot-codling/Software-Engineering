#include "Kamikaze.h"
#include "../../../Engine/System/Context/SysContextProvider.h"
#include "../../../Engine/Renderer/WindowManager.h"
#include "../../../Engine/System/GameState/GameState.h"
#include "../Player/Player.h"
#include "../../../Engine/System/GameState/GameStateManager.h"

void Kamikaze::Initialise(Player* player)
{
	GameObjectWithAnimatedSprite::Initialise();
	m_player = player;

	const sf::Window& window = C_SysContext::Get<WindowManager>()->GetWindow();
	m_windowWidth = window.getSize().x;
	m_windowHeight = window.getSize().y;

	m_moveSpeed = 5;
	m_detectionRadius = 10000.0f;
	m_damage = 30;
	m_health = 60;

	m_damagedPoints = 20;
	m_killedPoints = 100;

	// Load sprite sheet
	AddSpriteSheet("sprites/characters/spr_kamikaze.xml");

	// Add animations
	AddAnimation(IDLE, "spr_kamikaze_idle", 10, true);
	AddAnimation(WALK, "spr_kamikaze_walk", 10, true);
	AddAnimation(HIT, "spr_kamikaze_hit", 10, false);
	AddAnimation(DEATHDAMAGE, "spr_kamikaze_death", 10, false);
	AddAnimation(DEATHEXPLODE, "spr_kamikaze_death3", 10, false);

	//Set current animation
	SetCurrentAnimation(WALK);

	SetScaleInPixels({ 128, 128 });

	m_enemySize = sf::Vector2f(64, 64);

	m_collisionRect = { 0, 0, m_enemySize.x, m_enemySize.y };

}

void Kamikaze::Update()
{
	Chase();
	CheckCollisions();
	GameObjectWithAnimatedSprite::Update();
}

sf::Vector2f Kamikaze::GetPosition()
{
	sf::Vector2f offset = sf::Vector2f(0, 30);
	return this->getPosition() + offset;
}

void Kamikaze::CheckCollisions()
{
	m_collided = CollidesWith(*m_player);

	if (m_collided && m_health > 0)
	{
		m_player->DoDamage(m_damage);
		this->m_health = 0;
		SetCurrentAnimation(DEATHEXPLODE);
	}
}
