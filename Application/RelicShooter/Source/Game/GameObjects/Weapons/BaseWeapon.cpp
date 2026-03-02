#include "BaseWeapon.h"

#include "../../DebugHandler.hpp"
#include "../../Input/InputWrapper.h"
#include "../../../Engine/Renderer/WindowManager.h"
#include "../../../Engine/System/GameState/GameState.h"
#include "../../../Engine/System/GameState/GameStateManager.h"
#include "../../../Engine/System/Context/SysContextProvider.h"

constexpr float RAD_TO_DEG = 180.f / 3.141592f;
constexpr float DEG_TO_RAD = 3.141592f / 180.f;
void BaseWeapon::Initialise()
{
	GameObjectWithAnimatedSprite::Initialise();

	const sf::Window& window = C_SysContext::Get<WindowManager>()->GetWindow();
	m_windowWidth = window.getSize().x;
	m_windowHeight = window.getSize().y;
	m_aspectRatio = static_cast<float>(m_windowWidth) / static_cast<float>(m_windowHeight);
}

void BaseWeapon::Update()
{
	GameObjectWithAnimatedSprite::Update();
}

void BaseWeapon::Fire()
{
	if (m_ammoInClip <= 0 || m_isReloading)
	{
		// Return if not enough ammo or is reloading
		return;
	}

	std::chrono::duration<float> duration = std::chrono::system_clock::now() - m_timeSinceLastFire;
	if (duration.count() >= 1.f / static_cast<float>(m_fireRate))
	{
		// Spawn new bullet
		CreateNewBullet();
		m_ammoInClip--;
		m_timeSinceLastFire = std::chrono::system_clock::now();
	}
}

void BaseWeapon::DefineEnemies(std::vector<Enemy*>* enemyVector)
{
	m_enemies = enemyVector;
}

void BaseWeapon::DefineCollisionTilemap(TileMap* tilemap)
{
	m_collisionTilemap = tilemap;
}

void BaseWeapon::SetAngle(float angle)
{
	// Flip the weapon direction in the y-axis depending on the right stick
	if (angle > 90 || angle < -90)
	{
		FlipY(true);
	}
	else
	{
		FlipY(false);
	}
	GameObjectWithAnimatedSprite::SetAngle(angle);
}

void BaseWeapon::InitaliseReload()
{
	if (m_ammoInClip >= m_maxClipSize || m_isReloading)
	{
		return;
	}
	m_timeSinceLastReload = std::chrono::system_clock::now();
	m_isReloading = true;
}

void BaseWeapon::StopReload()
{
	m_isReloading = false;
}

void BaseWeapon::Reload(int& playerAmmo)
{
	if (!m_isReloading)
	{
		return;
	}

	std::chrono::duration<float> duration = std::chrono::system_clock::now() - m_timeSinceLastReload;
	// If the reload is not finished, return
	if (duration.count() < m_reloadTime)
	{
		return;
	}

	// Calculate how much ammo to reload
	const int reductAmmo = m_maxClipSize - m_ammoInClip;
	if (playerAmmo - reductAmmo >= 0)
	{
		// Enough ammo to fully reload
		m_ammoInClip += reductAmmo;
		playerAmmo -= reductAmmo;
	}
	else
	{
		// Not enough ammo to fully reload
		m_ammoInClip += playerAmmo;
		playerAmmo = 0;
	}
	m_isReloading = false;

}

float BaseWeapon::GetReloadTime() const
{
	return m_reloadTime;
}

bool BaseWeapon::IsWeaponReloading() const
{
	return m_isReloading;
}

void BaseWeapon::SetBeingHeld(bool isBeingHeld)
{
	m_isBeingHeld = isBeingHeld;
}

void BaseWeapon::SetBeingHighlighted(bool isHighlighted)
{
	if (isHighlighted && !m_isBeingHeld)
	{
		SetCurrentAnimation(Selected);
		return;
	}
	SetCurrentAnimation(Normal);
}

void BaseWeapon::Direction(sf::Vector2f weaponOffset)
{
	if (!m_isBeingHeld)
	{
		return;
	}

	m_weaponOffset = weaponOffset;
	const float rightStickX = GetAnalogueInput(E_AnalogueInput_ThumbRX)->GetValue();
	const float rightStickY = GetAnalogueInput(E_AnalogueInput_ThumbRY)->GetValue();

	// Rotate the weapon to point towards the right stick
	const float angle = atan2f(rightStickY, rightStickX * m_aspectRatio);
	SetAngle(angle * RAD_TO_DEG);
}

void BaseWeapon::CreateNewBullet()
{
	Bullet* bullet = new Bullet();
	bullet->Initialise(m_bulletType, m_enemies, m_collisionTilemap);

	const float angle = CalculateBulletAngle(); 
	
	// Set the position of the bullet at the edge of a circle that is x distance from the weapon position
	const sf::Vector2f bulletOffset = { cos(angle) * m_weaponLength, (sin(angle) * m_weaponLength) };
	bullet->SetPosition(GetPosition() + bulletOffset);

	// Now set the angle of the bullet
	bullet->SetAngle(angle * RAD_TO_DEG);
	bullet->SetBulletDirectionVector();

	// Add the bullet the game scene
	C_SysContext::Get<GameStateManager>()->GetCurrentGameState()->AddGameObject(bullet);
	
}

float BaseWeapon::CalculateBulletAngle()
{
	const float rightStickX = GetAnalogueInput(E_AnalogueInput_ThumbRX)->GetValue();
	const float rightStickY = GetAnalogueInput(E_AnalogueInput_ThumbRY)->GetValue();
	
	// Calculate angle of right stick
	float angle = atan2f(rightStickY, rightStickX * m_aspectRatio);
	// If weapon is flipped, rotate bullet 180 degrees
	if (IsFlippedX())
	{
		angle -= 180.f * DEG_TO_RAD;
	}
	return angle;
}

const char* BaseWeapon::GetWeaponName() const {
	return m_weaponName;
}