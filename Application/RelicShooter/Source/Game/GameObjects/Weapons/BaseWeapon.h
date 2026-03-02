#pragma once

#include <chrono>
#include "Bullet.h"
#include "../BaseGameObjects//GameObjectWithAnimatedSprite.h"


class Enemy;

class BaseWeapon : public GameObjectWithAnimatedSprite
{
public:
	BaseWeapon() = default;
	~BaseWeapon() override = default;

public:
	void Initialise() override;
	void Update() override;
	virtual void Fire();
	
	void DefineEnemies(std::vector<Enemy*>* enemyVector);
	void DefineCollisionTilemap(TileMap* tilemap);

	// --- Transformations
	// Rotations
	void SetAngle(float angle);

	// --- Weapon Reload ---
	void InitaliseReload();
	void StopReload();
	void Reload(int& playerAmmo);
	float GetReloadTime() const;
	bool IsWeaponReloading() const;

	// --- Set weapon states ---
	void SetBeingHeld(bool isBeingHeld);
	void SetBeingHighlighted(bool isHighlighted);

	// --- Weapon direction ---
	void Direction(sf::Vector2f weaponOffset);

	// --- Weapon identifier ---
	const char* GetWeaponName() const;

	// --- Ammo ---
	int GetAmmoCount() const { return m_ammoInClip; };

protected:
	virtual void CreateNewBullet();
	float CalculateBulletAngle();

protected:
	// Animation states
	enum WeaponState
	{
		Normal,
		Selected
	};

	// Customisable variables
	float m_weaponLength;	// Determines how far the bullet will appear from the weapon

	const char* m_weaponName; // Weapon identifier

	// Ammo variables
	int m_ammoInClip;	// Ammo current in clip
	int m_maxClipSize;		// Max ammo in clip
	BulletTypes::Type m_bulletType;

	// Reloading times
	float m_reloadTime;	// In seconds

	// Fire rate
	int m_fireRate;		// In bullets per second
	
	// Weapon offset from player
	sf::Vector2f m_weaponOffset = { 0, 0 };
	
	// Enemy and world collisions to pass to bullets
	std::vector<Enemy*>* m_enemies = nullptr;
	TileMap* m_collisionTilemap = nullptr;

private:
	// Window information
	size_t m_windowWidth;
	size_t m_windowHeight;
	float m_aspectRatio;

	bool m_isBeingHeld = false;
	bool m_isReloading = false;
	std::chrono::time_point<std::chrono::system_clock> m_timeSinceLastReload;
	std::chrono::time_point<std::chrono::system_clock> m_timeSinceLastFire;
	
};
