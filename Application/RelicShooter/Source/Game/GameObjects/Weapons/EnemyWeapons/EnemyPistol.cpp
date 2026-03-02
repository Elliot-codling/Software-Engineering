#include "EnemyPistol.h"

void EnemyPistol::Initialise()
{
	BaseWeapon::Initialise();

	AddSpriteSheet("sprites/weapons/spr_pistol.xml");
	AddAnimation(Normal, "spr_pistol_normal", 1, false);
	SetCurrentAnimation(Normal);

	const float scale = 1.2f;
	SetScale({ scale, scale });

	// Customisable variables
	m_weaponLength = 60.f;	// Determines how far the bullet will appear from the weapon

	// Ammo variables
	m_ammoInClip = 15;	// Ammo current in clip
	m_maxClipSize = 15;		// Max ammo in clip

	// Fire rate
	m_fireRate = 3;		//3 In bullets per second

	m_bulletType = BulletTypes::Red;
}
