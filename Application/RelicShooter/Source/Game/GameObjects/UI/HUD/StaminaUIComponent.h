#ifndef STAMINAUICOMPONENT_H
#define STAMINAUICOMPONENT_H

#include "UIElement.h"

#include <vector>
#include <SFML/Graphics/Color.hpp>
#include <SFML/System/Vector2.hpp>

class Sprite;

class StaminaUIComponent : public UIElement {
public:
    StaminaUIComponent() = default;
    ~StaminaUIComponent() = default;

public:
    void Initialise(const float maxStamina, const float dashStaminaCost);
    void CreateStaminaBars(const float maxStamina, const float dashStaminaCost);

    void UpdateStaminaBar(const float currentStamina, const float maxStamina);

private:
    std::vector<Sprite> m_staminaBarSprites;
    std::vector<Sprite> m_staminaBarBackgroundSprites;

    sf::Color m_backgroundColour = sf::Color(79.0f, 79.0f, 79.0f, 127.5f);
    sf::Vector2f m_initialBarPosition = sf::Vector2f(155.0f, 145.0f);
    const char* m_barSpriteFileName = "ui/HUD/spr_hud_bar_0.png";

    int m_amountOfBars = 0;
    const float m_barSeparatorSize = 5.0f;
    const float m_totalWidth = 283.5f;
    float m_currentBarScaleX;

};

// 150.0f, 75.0f health bar position

// 150.0f, 145.0f possible stamina bar position

#endif