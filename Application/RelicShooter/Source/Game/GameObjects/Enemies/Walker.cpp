#include "Walker.h"
#include "../../../Engine/System/Context/SysContextProvider.h"
#include "../../../Engine/Renderer/WindowManager.h"

void Walker::Initialise(Player* player)
{
	GameObjectWithAnimatedSprite::Initialise();
	m_player = player;

	const sf::Window& window = C_SysContext::Get<WindowManager>()->GetWindow();
	m_windowWidth = window.getSize().x;
	m_windowHeight = window.getSize().y;

	m_moveSpeed = 3;
	m_detectionRadius = 960.0f;
	m_damage = 20;
	m_health = 180;

	m_damagedPoints = 10;
	m_killedPoints = 50;

	// Load sprite sheet
	AddSpriteSheet("sprites/characters/spr_rider.xml");

	// Add animations
	AddAnimation(IDLE, "spr_rider_idle", 10, true);
	AddAnimation(WALK, "spr_rider_walk", 10, true);
	AddAnimation(HIT, "spr_rider_hit", 10, false);
	AddAnimation(DEATHDAMAGE, "spr_rider_death", 10, false);

	//Set current animation
	SetCurrentAnimation(WALK);

	SetScaleInPixels({ 128, 128 });

	m_enemySize = sf::Vector2f(64, 64);

	m_collisionRect = { 0, 0, m_enemySize.x, m_enemySize.y };

}

void Walker::Update()
{
	Chase();
	CheckCollisions();
	GameObjectWithAnimatedSprite::Update();
}

sf::Vector2f Walker::GetPosition()
{
	sf::Vector2f offset = sf::Vector2f(0, 30);
	return this->getPosition() + offset;
}
