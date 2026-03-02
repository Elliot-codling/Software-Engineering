#ifndef HEALTHUICOMPONENT_H
#define HEALTHUICOMPONENT_H

#include "UIElement.h"

#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Drawable.hpp>

class Sprite;
class Text;

class HealthUIComponent : public UIElement {
public:
    HealthUIComponent() = default;
    ~HealthUIComponent() = default;

public:
    void Initialise(int health);

    void UpdateHealth(int currentHealth, int maxHealth);
    void UpdateFaceSprite(const int currentHealth) const;
private:
    /* Sprites and text */
    Sprite* m_healthRectangle;
    Sprite* m_healthRectangleShadow;
    Sprite* m_healthFace;
    Sprite* m_healthIcon;
    Text* m_healthText;

    /* Health bar settings */
    const float m_healthShadowOffset = 5.0f;
    const float m_healthBarScale = 3.5f;
    const sf::Color m_healthColour = sf::Color(255.0f, 71.0f, 77.0f, static_cast<sf::Uint8>(255.0f));
    const sf::Color m_shadowColour = sf::Color(20.0f, 20.0f, 20.0f, static_cast<sf::Uint8>(127.5f));
    float m_textLocalWidth = 0.0f;

    int m_previousHealth;

    /* Face sprites */
    const char* m_faceSpriteFileNames[3] = {
        "ui/HUD/jimmy/spr_hud_face_jimmy_0.png",
        "ui/HUD/jimmy/spr_hud_face_jimmy_1.png",
        "ui/HUD/jimmy/spr_hud_face_jimmy_2.png"
    };
    int m_faceChangeThresholds[2]{
        60,
        25
    };
};

#endif