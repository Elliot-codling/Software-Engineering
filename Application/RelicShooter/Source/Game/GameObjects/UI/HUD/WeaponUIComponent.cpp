#include "WeaponUIComponent.h"

#include "../../../../Engine/Renderer/Sprite.h"
#include "../../../../Engine/UI/Text.h"
#include "../../Weapons/BaseWeapon.h"
#include "../../Weapons/Rifle.h"

void WeaponUIComponent::Initialise() {
	/* Add drawables to the UI renderer */
	C_SysContext::Get<RenderManager>()->AddUIRenderObject(&m_equippedSprite);
	C_SysContext::Get<RenderManager>()->AddUIRenderObject(&m_stashedSprite);

	/* Initialise ammo text */
	m_ammoText.Initialise("fonts/BoldPixels.ttf", "", sf::Color::White, 75, true);
	m_ammoText.setPosition(m_equippedSprite.getPosition().x + m_equippedSprite.getGlobalBounds().width + 25.0f, m_equippedSprite.getPosition().y);
}


// ---------------------- WEAPONS ----------------------
void WeaponUIComponent::UpdateWeapon(BaseWeapon* equippedWeapon, BaseWeapon* stashedWeapon) {
	CheckEquippedWeaponSlot(equippedWeapon);
	CheckStashedWeaponSlot(stashedWeapon);
}

void WeaponUIComponent::CheckEquippedWeaponSlot(BaseWeapon* equippedWeapon) {
	/* Check whether the equipped weapon exists */
	if (equippedWeapon == nullptr) {

		if (!m_clearedEquippedWeapon)
		{
			ClearEquippedWeaponSlot();
		}
		return;
	}
	m_clearedEquippedWeapon = false;

	/* Don't do unnecessary updates if the weapon is the same as last update */
	if (equippedWeapon->GetWeaponName() == m_equippedWeaponName) {
		return;
	}

	/* If the weapon is not the same and is valid, set the sprite */
	m_equippedWeaponName = equippedWeapon->GetWeaponName();
	m_equippedSprite = *equippedWeapon->GetSprite(2, 0);
	m_equippedSprite.setOrigin(0, 0);
	m_equippedSprite.setScale(m_equippedSpriteScale, m_equippedSpriteScale);
	m_equippedSprite.setPosition(0, 1080.0f - (m_equippedSprite.getGlobalBounds().height * 2));
}

void WeaponUIComponent::CheckStashedWeaponSlot(BaseWeapon* stashedWeapon) {
	/* Check whether the stashed weapon exists */
	if (stashedWeapon == nullptr) {

		if (!m_clearedStashedWeapon)
		{
			ClearStashedWeaponSlot();
		}
		return;
	}
	m_clearedStashedWeapon = false;

	/* Don't do unnecessary updates if the weapon is the same as last update */
	if (stashedWeapon->GetWeaponName() == m_stashedWeaponName) {
		return;
	}

	/* If the weapon is not the same and is valid, set the sprite */
	m_stashedWeaponName = stashedWeapon->GetWeaponName();
	m_stashedSprite = *stashedWeapon->GetSprite(2, 0);
	m_stashedSprite.setOrigin(0, 0);
	m_stashedSprite.setScale(m_stashedSpriteScale, m_stashedSpriteScale);
	m_stashedSprite.setPosition(0, 1080.0f - m_stashedSprite.getGlobalBounds().height);
}

void WeaponUIComponent::ClearEquippedWeaponSlot() {
	m_equippedWeaponName = "";
	m_equippedSprite = Sprite();
	m_clearedEquippedWeapon = true;
}

void WeaponUIComponent::ClearStashedWeaponSlot() {
	m_stashedWeaponName = "";
	m_stashedSprite = Sprite();
	m_clearedStashedWeapon = true;
}

// ---------------------- AMMO ----------------------
void WeaponUIComponent::UpdateAmmo(const BaseWeapon* currentWeapon) {
	if (currentWeapon == nullptr) {
		if (m_lastUpdateAmmoCount != -1) {
		    m_ammoText.setString("");
		    m_lastUpdateAmmoCount = -1;
		}
		return;
	}
    if (currentWeapon->GetAmmoCount() == m_lastUpdateAmmoCount) {
        return;
    }

	m_lastUpdateAmmoCount = currentWeapon->GetAmmoCount();
	m_ammoText.setString(std::to_string(currentWeapon->GetAmmoCount()));
	m_ammoText.setPosition(m_equippedSprite.getPosition().x + m_equippedSprite.getGlobalBounds().width + 25.0f, 
		                    m_equippedSprite.getGlobalBounds().top - m_ammoText.getLocalBounds().top + (m_ammoText.getGlobalBounds().height));
}

