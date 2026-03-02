#include "EnemyBaseWeapon.h"

#include "EnemyBullet.h"
#include "../../../DebugHandler.hpp"
#include "../../../../Engine/System/Context/SysContextProvider.h"
#include "../../../../Engine/System/GameState/GameStateManager.h"
#include "../../../../Engine/System/GameState/GameState.h"

constexpr float RAD_TO_DEG = 180.f / 3.141592f;
constexpr float DEG_TO_RAD = 3.141592f / 180.f;
void EnemyBaseWeapon::DefinePlayer(Player* player)
{
	m_player = player;
}

void EnemyBaseWeapon::Fire()
{
	std::chrono::duration<float> duration = std::chrono::system_clock::now() - m_timeSinceLastFire;
	if (duration.count() >= 1.f / static_cast<float>(m_fireRate))
	{
		// Spawn new bullet
		CreateNewBullet();
		m_timeSinceLastFire = std::chrono::system_clock::now();
	}
}

void EnemyBaseWeapon::CreateNewBullet()
{
	EnemyBullet* bullet = new EnemyBullet();
	bullet->Initialise(m_bulletType, m_player, m_collisionTilemap);

	const float angle = GetAngle() * DEG_TO_RAD;

	// Set the position of the bullet at the edge of a circle that is x distance from the weapon position
	const sf::Vector2f bulletOffset = { cos(angle) * m_weaponLength, (sin(angle) * m_weaponLength) };
	bullet->SetPosition(GetPosition() + bulletOffset);

	// Now set the angle of the bullet
	bullet->SetAngle(angle * RAD_TO_DEG);
	bullet->SetBulletDirectionVector();

	// Add the bullet the game scene
	C_SysContext::Get<GameStateManager>()->GetCurrentGameState()->AddGameObject(bullet);
}
