#include "Bullet.h"

#include "../../DebugHandler.hpp"
#include "../../../Engine/System/GameState/GameStateManager.h"
#include "../../../Engine/Renderer/RenderManager.h"
#include "../../../Engine/Renderer/WindowManager.h"
#include "../../../Engine/System/GameState/GameState.h"
#include "../../../Engine/System/Context/SysContextProvider.h"
#include "../Enemies/Enemy.h"
#include "../../GameData/TileMap.h"

constexpr float DEG_TO_RAD = 3.141592f / 180.f;

void Bullet::Initialise(BulletTypes::Type bulletType, std::vector<Enemy*>* enemyVector, TileMap* collisionMap)
{
	GameObjectWithAnimatedSprite::Initialise();
	
	m_enemies = enemyVector;
	m_collisionTilemap = collisionMap;
	m_bulletType = bulletType;
	
	const sf::Window& window = C_SysContext::Get<WindowManager>()->GetWindow();
	m_windowWidth = window.getSize().x;
	m_windowHeight = window.getSize().y;
	m_aspectRatio = static_cast<float>(m_windowWidth) / static_cast<float>(m_windowHeight);

	m_bulletSpeed = 20.f;
	CalculateAnimationFPS();

	AddSpriteSheet(m_bulletFilenames[m_bulletType]);
	AddAnimation(0, "spr_bullet", static_cast<int>(m_bulletFPS), false);
	SetCurrentAnimation(0);
	
	m_radius = 20.f;
}
void Bullet::Update()
{
	GameObjectWithAnimatedSprite::Update();
	Movement();
	UpdateCollisionMovement();
	
	CheckOutOfBounds();
	CheckEnemyCollisions();
	CheckWorldCollisions();
}

void Bullet::SetBulletDirectionVector()
{
	// Convert bullet angle into directional vector
	const float angle = GetAngle() * DEG_TO_RAD;

	m_directionVector = {
		cosf(angle),
		sinf(angle)
	};
}

void Bullet::CalculateAnimationFPS()
{
	m_bulletFPS = 10.f * (m_bulletSpeed / 2.f);
}

void Bullet::Movement()
{
	IncrementPosition({ m_directionVector.x * m_bulletSpeed, m_directionVector.y * m_bulletSpeed });
}

void Bullet::UpdateCollisionMovement()
{
	m_centrePosition = GameObjectWithAnimatedSprite::GetPosition();
}

void Bullet::CheckWorldCollisions()
{
	if (m_collisionTilemap == nullptr)
	{
		return;
	}

	size_t bulletPosition = m_collisionTilemap->TileIndexAtPosition(GameObjectWithAnimatedSprite::GetPosition());
	std::map<size_t, BoxCollider2D>& worldCollisions = m_collisionTilemap->GetWorldCollisions();
	if (worldCollisions.find(bulletPosition) != worldCollisions.end())
	{
		BoxCollider2D& rect = worldCollisions.at(bulletPosition);
		
		if (rect.CollidesWith(*this))
		{
			// Bullet colliders with wall
			C_SysContext::Get<GameStateManager>()->GetCurrentGameState()->RemoveGameObject(this);
		}
	}
}

void Bullet::CheckOutOfBounds()
{
	sf::View viewPort = C_SysContext::Get<RenderManager>()->GetGameRenderView();
	const sf::Vector2i viewPosition = static_cast<sf::Vector2i>(viewPort.getCenter());

	// Get screen bounds
	sf::IntRect screenPositions(viewPosition.x - (m_windowWidth / 2.f),
		viewPosition.y - (m_windowHeight / 2.f),
		viewPosition.x + (m_windowWidth / 2.f),
		viewPosition.y + (m_windowHeight / 2.f)
	);

	// Remove bullet out of screen bounds
	if (GameObjectWithAnimatedSprite::GetPosition().x > screenPositions.width ||
		GameObjectWithAnimatedSprite::GetPosition().x + GetFrameSize().x < screenPositions.left ||
		GameObjectWithAnimatedSprite::GetPosition().y > screenPositions.height ||
		GameObjectWithAnimatedSprite::GetPosition().y + GetFrameSize().y < screenPositions.top)
	{
		C_SysContext::Get<GameStateManager>()->GetCurrentGameState()->RemoveGameObject(this);
	}
}

void Bullet::CheckEnemyCollisions()
{
	if (m_enemies == nullptr)
	{
		return;
	}
	
	for (Enemy* enemy : (*m_enemies))
	{
		if (enemy->GetHealth() <= 0)
		{
			continue;
		}
		if (!enemy->CollidesWith(*this))
		{
			continue;
		}

		const int damage = m_damageValue[m_bulletType];
		enemy->TakeDamage(damage);
		C_SysContext::Get<GameStateManager>()->GetCurrentGameState()->RemoveGameObject(this);
		return;
	}
}
