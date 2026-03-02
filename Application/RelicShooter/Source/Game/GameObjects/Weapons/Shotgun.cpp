#include "Shotgun.h"

#include "../../../Engine/System/Context/SysContextProvider.h"
#include "../../../Engine/System/GameState/GameStateManager.h"
#include "../../Input/InputWrapper.h"
#include "../../../Engine/System/GameState/GameState.h"
#include "../../../Engine/Renderer/WindowManager.h"

constexpr float RAD_TO_DEG = 180.f / 3.141592f;
constexpr float DEG_TO_RAD = 3.141592f / 180.f;
void Shotgun::Initialise()
{
	BaseWeapon::Initialise();
	AddSpriteSheet("sprites/weapons/spr_shotgun.xml");
	AddAnimation(Normal, "spr_shotgun_normal", 1, false);
	AddAnimation(Selected, "spr_shotgun_highlight", 1, false);
	SetCurrentAnimation(Normal);

	/* UI */
	m_weaponName = "Shotgun";
	AddAnimation(2, "spr_shotgun_white", 1, false);

	const float scale = 1.2f;
	SetScale({ scale, scale });

	// Customisable variables
	m_weaponLength = 60.f;	// Determines how far the bullet will appear from the weapon

	// Ammo variables
	m_ammoInClip = 4;	// Ammo current in clip
	m_maxClipSize = 4;		// Max ammo in clip

	// Reloading times
	m_reloadTime = 2.5f;	// In seconds

	// Fire rate
	m_fireRate = 1;		// In bullets per second

	m_bulletType = BulletTypes::Blue;
}

void Shotgun::CreateNewBullet()
{
	// Calculate angle of right stick
	float angle = CalculateBulletAngle();
	
	// Create bullets clockwise
	if (m_bulletsPerRound % 2 == 0)
	{
		// Even number of bullets
		const float offSetAngle = (static_cast<float>(m_bulletsPerRound) / 2.f) - 0.5f;
		angle -= offSetAngle * (m_bulletSpread * DEG_TO_RAD);
	}
	else
	{
		// Odd number of bullets
		const float offSetAngle = floor(static_cast<float>(m_bulletsPerRound) / 2.f);
		angle -= offSetAngle * (m_bulletSpread * DEG_TO_RAD);
		
	}
	
	// Create x number of bullets
	for (size_t index = 0; index < m_bulletsPerRound; index++)
	{
		Bullet* bullet = new Bullet();
		bullet->Initialise(m_bulletType, m_enemies, m_collisionTilemap);

		// Set the position of the bullet at the edge of a circle that is x distance from the weapon position
		const sf::Vector2f bulletOffset = { cos(angle) * m_weaponLength, (sin(angle) * m_weaponLength) };
		bullet->SetPosition(GetPosition() + bulletOffset);

		// Now set the angle of the bullet
		bullet->SetAngle(angle * RAD_TO_DEG);
		bullet->SetBulletDirectionVector();

		// Add the bullet the game scene
		C_SysContext::Get<GameStateManager>()->GetCurrentGameState()->AddGameObject(bullet);
		
		angle += m_bulletSpread * DEG_TO_RAD;
	}
}

