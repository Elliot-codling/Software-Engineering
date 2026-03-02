#ifndef WEAPONUICOMPONENT_H
#define WEAPONUICOMPONENT_H

#include "UIElement.h"
#include "../../BaseGameObjects/GameObjectWithAnimatedSprite.h"
#include "../../../../Engine/UI/Text.h"
#include "../../../../Engine/Renderer/Sprite.h"
#include "../../../../Engine/System/Context/SysContextProvider.h"
#include "../../../../Engine/Renderer/RenderManager.h"

class Player;
class BaseWeapon;

class WeaponUIComponent : public UIElement {
public:
    WeaponUIComponent() = default;
    ~WeaponUIComponent() {
        C_SysContext::Get<RenderManager>()->RemoveUIRenderObject(&m_equippedSprite);
        C_SysContext::Get<RenderManager>()->RemoveUIRenderObject(&m_stashedSprite);
    };

public:
    void Initialise();
    void Update(const Player& player);

    void UpdateWeapon(BaseWeapon* equippedWeapon, BaseWeapon* stashedWeapon);
    void UpdateAmmo(const BaseWeapon* currentWeapon);

    void CheckEquippedWeaponSlot(BaseWeapon* equippedWeapon);
    void CheckStashedWeaponSlot(BaseWeapon* stashedWeapon);

    void ClearEquippedWeaponSlot();
    void ClearStashedWeaponSlot();

private:
    /* Sprite vars */
    //Held Weapon
    int m_lastUpdateAmmoCount = 0;
    const float m_equippedSpriteScale = 3.5f;
    const sf::Color m_shadowColour = sf::Color(20.0f, 20.0f, 20.0f, static_cast<sf::Uint8>(127.5f));
    //Stashed Weapon
    const float m_stashedSpriteScale = 2.75f;

    /* Weapons */
    sf::Sprite m_equippedSprite;
    sf::Sprite m_stashedSprite;
    const char* m_equippedWeaponName;
    const char* m_stashedWeaponName;
    bool m_clearedEquippedWeapon = false;
    bool m_clearedStashedWeapon = false;

    Text m_ammoText;
};

#endif