#include "StaminaUIComponent.h"

#include "../../../../Engine/Renderer/Sprite.h"

void StaminaUIComponent::Initialise(const float maxStamina, const float dashStaminaCost) {
    CreateStaminaBars(maxStamina, dashStaminaCost);
}


void StaminaUIComponent::CreateStaminaBars(const float maxStamina, const float dashStaminaCost) {
    sf::Vector2f barScale = sf::Vector2f(3.5f, 0.5f);

    /* Make sure that the bar stays within the maximum width */
    m_amountOfBars = static_cast<int>(floor(maxStamina / dashStaminaCost));
    const float barSize = (m_totalWidth - (m_barSeparatorSize * (m_amountOfBars - 1))) / m_amountOfBars;
    m_currentBarScaleX = barScale.x / (m_totalWidth / barSize);

    for (int i = 0; i < m_amountOfBars; i++) {
        /* Reserve space for each bar */
        m_staminaBarSprites.reserve(m_amountOfBars);
        m_staminaBarBackgroundSprites.reserve(m_amountOfBars);

        /* Create bar */
        Sprite barSprite;
        barSprite.Initialise(m_barSpriteFileName, sf::Color::White, 1.0f, true);
        barSprite.setScale(m_currentBarScaleX, barScale.y);
        m_staminaBarSprites.emplace_back(barSprite);

        /* Create bar background */
        Sprite barBackgroundSprite;
        barBackgroundSprite.Initialise(m_barSpriteFileName, m_backgroundColour, 1.0f, true);
        barBackgroundSprite.setScale(m_currentBarScaleX, barScale.y);
        m_staminaBarBackgroundSprites.emplace_back(barBackgroundSprite);

        /* Get this bar's X position in the bar */
        const float barPosX = m_initialBarPosition.x + (barSize * i) + (m_barSeparatorSize * i);

        /* Set position of sprites */
        m_staminaBarBackgroundSprites[m_staminaBarBackgroundSprites.size() - 1].setPosition(barPosX, m_initialBarPosition.y);
        m_staminaBarSprites[m_staminaBarSprites.size() - 1].setPosition(barPosX, m_initialBarPosition.y);

        /* Add sprites to render queue */
        m_staminaBarBackgroundSprites[m_staminaBarBackgroundSprites.size() - 1].AddToRenderQueue();
        m_staminaBarSprites[m_staminaBarSprites.size() - 1].AddToRenderQueue();
    }
}

void StaminaUIComponent::UpdateStaminaBar(const float currentStamina, const float maxStamina) {
    /* Return if we are at max stamina or less than or equal to 0 */
    if (currentStamina >= maxStamina || currentStamina <= 0) {
        return;
    }

    /* Find the stamina per bar, then find the current health bar and the amount left in that bar */
    const float perBarStamina = maxStamina / m_amountOfBars;
    const int currentHealthBar = static_cast<int>(floor(currentStamina / perBarStamina));

    const float amountOfStamLeft = std::fmod(currentStamina, perBarStamina); // float
    //float amountOfStamLeft = static_cast<int>(currentStamina) % static_cast<int>(perBarStamina); // int

    /* Calculate the percentage left in the current bar */
    const float percentage = amountOfStamLeft / perBarStamina;

    /* Set the X scale of the current stamina bar */
    m_staminaBarSprites[currentHealthBar].setScale(m_currentBarScaleX * percentage, 0.5f);

    /* Set all stamina bars after to be 0 */
    for (int i = currentHealthBar + 1; i < m_amountOfBars; i++) {
        m_staminaBarSprites[i].setScale(0, 0.5f);
    }
    /* Set all stamina bars before to be full */
    for (int i = currentHealthBar - 1; i >= 0; i--) {
        m_staminaBarSprites[i].setScale(m_currentBarScaleX, 0.5f);
    }
}