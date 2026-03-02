#include "HealthUIComponent.h"

#include "../../../DebugHandler.hpp"
#include "../../../../Engine/Renderer/Sprite.h"
#include "../../../../Engine/UI/Text.h"

void HealthUIComponent::Initialise(int health) {
    m_previousHealth = health;

	/* Create shadow colour */
    sf::Color shadowColour = sf::Color(20.0f, 20.0f, 20.0f, static_cast<sf::Uint8>(127.5f));

    /* Create the health bar and shadow */
    m_healthRectangle = new Sprite();
    m_healthRectangle->Initialise("ui/HUD/spr_hud_bar_0.png", m_healthColour, m_healthBarScale, true);
    m_healthRectangle->setPosition(150, 75);
    m_healthRectangleShadow = new Sprite();
    m_healthRectangleShadow->Initialise("ui/HUD/spr_hud_bar_0.png", m_shadowColour, m_healthBarScale, true);
    m_healthRectangleShadow->setPosition(
        m_healthRectangle->getPosition().x + m_healthShadowOffset, 
        m_healthRectangle->getPosition().y + m_healthShadowOffset);

    /* Add the health bar and shadow to renderer in the correct order */
    m_healthRectangleShadow->AddToRenderQueue();
    m_healthRectangle->AddToRenderQueue();

    m_healthIcon = new Sprite();
    m_healthIcon->Initialise("ui/HUD/spr_icon_health_0.png", sf::Color::White, 1.5f, true);
    m_healthIcon->setOrigin(m_healthIcon->getLocalBounds().width / 2.0f, m_healthIcon->getLocalBounds().height / 2.0f);
    /* This is contending for the worst line of code I have ever written, please help me */
    m_healthIcon->setPosition(m_healthRectangle->getPosition() + 
                             (sf::Vector2f(m_healthRectangle->getLocalBounds().width * m_healthBarScale, m_healthRectangle->getLocalBounds().height * m_healthBarScale)/ 2.0f) - 
                              sf::Vector2f((m_healthRectangle->getLocalBounds().width * m_healthBarScale) / 2.0f - (m_healthIcon->getLocalBounds().width / 2 + 30.0f), 0.0f));
    m_healthIcon->AddToRenderQueue();


    /* Create the face */
    m_healthFace = new Sprite();
    m_healthFace->Initialise(m_faceSpriteFileNames[0], sf::Color::White, 1.5f, true);
    m_healthFace->setPosition(25, 50);
    m_healthFace->AddToRenderQueue();

    /* Create the text */
    m_healthText = new Text();
    m_healthText->Initialise("fonts/8-BIT WONDER.TTF", "100", sf::Color::White, 40, true);
    m_healthText->setPosition(m_healthRectangle->getPosition() + (sf::Vector2f(m_healthRectangle->getLocalBounds().width, m_healthRectangle->getLocalBounds().height)/ 2.0f) + sf::Vector2f(130.0f, 0.0f));

    /* Set the original width for proper positioning of the text */
    m_textLocalWidth = m_healthText->getLocalBounds().width;
}

void HealthUIComponent::UpdateHealth(int currentHealth, int maxHealth) {
    // Do not update the health has not changed
    if (abs(m_previousHealth - currentHealth) <= 0)
    {
        return;
    }

    m_previousHealth = currentHealth;
	const float percentage = static_cast<float>(currentHealth) / static_cast<float>(maxHealth);
    /* Make sure the scale won't be negative */
    if (percentage >= 0) {
        /* Update health bar */
        m_healthRectangle->setScale(m_healthBarScale * percentage, m_healthBarScale);

        /* Update Text */
        m_healthText->setString(std::to_string(currentHealth));
        m_healthText->setPosition(m_healthText->getPosition().x + (m_textLocalWidth - m_healthText->getLocalBounds().width), m_healthText->getPosition().y);

        /* Update local width so that the position will only change once */
        m_textLocalWidth = m_healthText->getLocalBounds().width;
    }
    else {
        m_healthRectangle->setScale(0, m_healthBarScale);
        m_healthText->setString("0");
    }

    UpdateFaceSprite(currentHealth);
}

/* Check what threshold health is at, change face sprite depending on it */
void HealthUIComponent::UpdateFaceSprite (const int currentHealth) const {
    if (currentHealth > m_faceChangeThresholds[0]) {
        m_healthFace->SetTexture(m_faceSpriteFileNames[0]);
        return;
    }
    if (currentHealth > m_faceChangeThresholds[1]) {

        m_healthFace->SetTexture(m_faceSpriteFileNames[1]);
        return;
    }
    if(currentHealth <= m_faceChangeThresholds[1]){
        m_healthFace->SetTexture(m_faceSpriteFileNames[2]);
        return;
    }
} 
