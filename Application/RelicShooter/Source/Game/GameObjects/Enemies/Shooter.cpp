#include "Shooter.h"
#include "../../../Engine/System/Context/SysContextProvider.h"
#include "../../../Engine/Renderer/WindowManager.h"
#include "../../../Engine/System/GameState/GameState.h"
#include "../../../Engine/System/GameState/GameStateManager.h"
#include "../Weapons/EnemyWeapons/EnemyPistol.h"
#include "../Weapons/EnemyWeapons/EnemyShotgun.h"

constexpr float RAD_TO_DEG = 180.f / 3.141592f;
constexpr float DEG_TO_RAD = 3.141592f / 180.f;

void Shooter::Initialise(Player* player, TileMap* tileMap)
{
	GameObjectWithAnimatedSprite::Initialise();
	m_player = player;

	const sf::Window& window = C_SysContext::Get<WindowManager>()->GetWindow();
	m_windowWidth = window.getSize().x;
	m_windowHeight = window.getSize().y;

	m_moveSpeed = 2;
	m_detectionRadius = 960.0f;
	m_damage = 10;
	m_health = 30;
	
	m_damagedPoints = 15;
	m_killedPoints = 75;

	srand(time(nullptr));
	weaponSelect = rand() % 2;

	if (weaponSelect == 0)
	{
		m_weapon = new EnemyShotgun();
	}
	else
	{
		m_weapon = new EnemyPistol();
	}

	m_weapon->Initialise();
	m_weapon->DefinePlayer(m_player);
	m_weapon->DefineCollisionTilemap(tileMap);

	C_SysContext::Get<GameStateManager>()->GetCurrentGameState()->AddGameObject(m_weapon);

	// Load sprite sheet
	AddSpriteSheet("sprites/characters/spr_zombieTurtle.xml");

	// Add animations
	AddAnimation(IDLE, "spr_zombieTurtle_idle", 10, true);
	AddAnimation(WALK, "spr_zombieTurtle_walk", 10, true);
	AddAnimation(HIT, "spr_zombieTurtle_hit", 10, false);
	AddAnimation(DEATHDAMAGE, "spr_zombieTurtle_death", 10, false);

	//Set current animation
	SetCurrentAnimation(IDLE);

	SetScaleInPixels({ 128, 128 });

	m_enemySize = sf::Vector2f(56, 56);

	m_collisionRect = { 0, 0, m_enemySize.x, m_enemySize.y };

}

void Shooter::Update()
{
	GameObjectWithAnimatedSprite::Update();

	Chase();
	UpdateGun();
	CheckCollisions();
}

void Shooter::UpdateGun()
{

	sf::Vector2f currentPosition = GameObjectWithAnimatedSprite::GetPosition();
	sf::Vector2f faceDirection = m_targetLocation - currentPosition;
	float angle = atan2(faceDirection.y, faceDirection.x);

	if (m_health > 0)
	{
		m_weapon->setPosition(GetPosition());
		m_weapon->SetAngle(angle * RAD_TO_DEG);
		m_weapon->Fire();
	}

}

sf::Vector2f Shooter::GetPosition()
{
	sf::Vector2f offset = sf::Vector2f(0, 32);
	return GameObjectWithAnimatedSprite::GetPosition() + offset;
}