#include "Rifle.h"

void Rifle::Initialise()
{
	BaseWeapon::Initialise();

	AddSpriteSheet("sprites/weapons/spr_blitz.xml");
	AddAnimation(Normal, "spr_blitz_normal", 1, false);
	AddAnimation(Selected, "spr_blitz_highlight", 1, false);
	SetCurrentAnimation(Normal);

	/* UI */
	m_weaponName = "Rifle";
	AddAnimation(2, "spr_blitz_white", 1, false);

	const float scale = 1.2f;
	SetScale({ scale, scale });

	// Customisable variables
	m_weaponLength = 70.f;	// Determines how far the bullet will appear from the weapon

	// Ammo variables
	m_ammoInClip = 30;	// Ammo current in clip
	m_maxClipSize = 30;		// Max ammo in clip

	// Reloading times
	m_reloadTime = 1.0f;	// In seconds

	// Fire rate
	m_fireRate = 6;		// In bullets per second

	m_bulletType = BulletTypes::Red;
}
