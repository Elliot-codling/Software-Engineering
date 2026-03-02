#include "ReloadCharacter.h"

#include "../Weapons/BaseWeapon.h"

void ReloadCharacter::Initialise()
{
	GameObjectWithAnimatedSprite::Initialise();

	AddSpriteSheet("ui/spr_reload.xml");
	AddAnimation(Normal, m_animationImageName[Normal], 1, false);
	AddAnimation(Reloading, m_animationImageName[Reloading], 10, false);
	SetCurrentAnimation(Normal);
}

void ReloadCharacter::Update()
{
	GameObjectWithAnimatedSprite::Update();
}

void ReloadCharacter::UpdateReloadState(const BaseWeapon* weapon)
{
	if (weapon == nullptr)
	{
		if (GetCurrentAnimation() == Reloading)
		{
			SetCurrentAnimation(Normal);
		}
		return;
	}

	const bool weaponIsReloading = weapon->IsWeaponReloading();
	if (weaponIsReloading && GetCurrentAnimation() != Reloading)
	{
		// Set the animation to start
		SetCurrentAnimation(Reloading);

		const float numberOfFrames = static_cast<float>(GetNumberOfFrames());
		const float reloadTime = weapon->GetReloadTime();
		SetFPS(numberOfFrames / reloadTime);
		return;
	}
	if (!weaponIsReloading)
	{
		SetCurrentAnimation(Normal);
	}
}
