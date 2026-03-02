#include "EnemyBullet.h"

#include "../../../DebugHandler.hpp"
#include "../../../../Engine/Renderer/RenderManager.h"
#include "../../../../Engine/System/Context/SysContextProvider.h"
#include "../../../../Engine/Renderer/WindowManager.h"
#include "../../Player/Player.h"

void EnemyBullet::Initialise(BulletTypes::Type bulletType, Player* player, TileMap* collisionMap)
{
	GameObjectWithAnimatedSprite::Initialise();
	m_collisionTilemap = collisionMap;
	m_player = player;
	m_bulletType = bulletType;

	const sf::Window& window = C_SysContext::Get<WindowManager>()->GetWindow();
	m_windowWidth = window.getSize().x;
	m_windowHeight = window.getSize().y;
	m_aspectRatio = static_cast<float>(m_windowWidth) / static_cast<float>(m_windowHeight);

	m_bulletSpeed = 12.f;
	CalculateAnimationFPS();

	AddSpriteSheet(m_bulletFilenames[m_bulletType]);
	AddAnimation(0, "spr_bullet", static_cast<int>(m_bulletFPS), false);
	SetCurrentAnimation(0);

	m_radius = 20.f;
}

void EnemyBullet::Update()
{
	GameObjectWithAnimatedSprite::Update();
	Movement();
	UpdateCollisionMovement();

	CheckOutOfBounds();
	CheckPlayerCollisions();
	CheckWorldCollisions();
}

void EnemyBullet::CheckPlayerCollisions()
{
	if (m_player->CollidesWith(*this))
	{
		m_player->DoDamage(m_damageValue[m_bulletType]);
		C_SysContext::Get<RenderManager>()->RemoveRenderObject(this);
	}
}
