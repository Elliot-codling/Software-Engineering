#include "WaveUIComponent.h"

#include "../../../../Engine/Renderer/RenderManager.h"
#include "../../../../Engine/System/Context/SysContextProvider.h"
#include "../../../DebugHandler.hpp"
#include "../../Enemies/Enemy.h"

void WaveUIComponent::Initialise(const int enemyCount) {
    /* Create shadow colour */
    sf::Color shadowColour = sf::Color(20.0f, 20.0f, 20.0f, static_cast<sf::Uint8>(127.5f));

    /* Create the health bar and shadow */
    m_waveBar = new Sprite();
    m_waveBar->setOrigin(0, 0);
    m_waveBar->Initialise("ui/HUD/spr_hud_bar_0.png", m_waveBarColour, m_waveBarScale, true);
    m_waveBar->setPosition((1920.0f - m_waveBar->getGlobalBounds().width) - 150.0f, 75.0f);
    m_waveBarShadow = new Sprite();
    m_waveBarShadow->Initialise("ui/HUD/spr_hud_bar_0.png", shadowColour, m_waveBarScale, true);
    m_waveBarShadow->setPosition(
        m_waveBar->getPosition().x + m_waveBarShadowOffset,
        m_waveBar->getPosition().y + m_waveBarShadowOffset);

    /* Add the health bar and shadow to renderer in the correct order */
    m_waveBarShadow->AddToRenderQueue();
    m_waveBar->AddToRenderQueue();

    m_waveText.Initialise("fonts/8-BIT WONDER.TTF", "Wave", sf::Color::White, 25, true);
    m_waveText.setOrigin(0, 0);
    m_waveText.setPosition(
        sf::Vector2f(m_waveBar->getGlobalBounds().left + m_waveText.getLocalBounds().left, m_waveBar->getGlobalBounds().top - m_waveText.getLocalBounds().top) +
        sf::Vector2f(m_waveBar->getGlobalBounds().width + 10.0f, m_waveBarShadowOffset)
    );

    m_waveNumberText.Initialise("fonts/8-BIT WONDER.TTF", "0", sf::Color::White, 35, true);
    m_waveNumberText.setOrigin(0, 0);
    m_waveNumberText.setPosition(
        sf::Vector2f(m_waveText.getGlobalBounds().left, m_waveText.getGlobalBounds().top) +
        sf::Vector2f((m_waveText.getLocalBounds().width / 2) - (m_waveNumberText.getLocalBounds().width / 2) - m_waveNumberText.getLocalBounds().left, m_waveText.getLocalBounds().height + m_waveNumberText.getLocalBounds().top)
        //(sf::Vector2f(m_waveBar->getGlobalBounds().width, 0))
    );

    /* DEBUG */
    rect.setFillColor(sf::Color(0, 0, 0, 0));
    rect.setOutlineColor(sf::Color::Red);
    rect.setOutlineThickness(5);
    rect.setSize({ m_waveText.getGlobalBounds().width / 2, m_waveText.getGlobalBounds().height});
    rect.setPosition(m_waveText.getGlobalBounds().left, m_waveText.getGlobalBounds().top);

    rect2.setFillColor(sf::Color(0, 0, 0, 0));
    rect2.setOutlineColor(sf::Color::Green);
    rect2.setOutlineThickness(5);
    rect2.setSize({ m_waveNumberText.getGlobalBounds().width / 2, m_waveNumberText.getGlobalBounds().height });
    rect2.setPosition(m_waveNumberText.getGlobalBounds().left, m_waveNumberText.getGlobalBounds().top);

    m_maxEnemies = enemyCount;
    m_previousEnemyCount = enemyCount;
    //C_SysContext::Get<RenderManager>()->AddUIRenderObject(&rect);
    //C_SysContext::Get<RenderManager>()->AddUIRenderObject(&rect2);
}

void WaveUIComponent::Update(const int enemiesRemaining, const int enemiesInWave) {
    UpdateWaveBar(enemiesRemaining, enemiesInWave);
}

void WaveUIComponent::UpdateWaveBar(const int enemiesRemaining, const int enemiesInWave) {
    if (m_previousEnemyCount == enemiesRemaining)
    {
        m_updateText = false;
	    return;
    }

    m_updateText = true;
    m_previousEnemyCount = enemiesRemaining;

	const float percentage = static_cast<float>(enemiesRemaining) / m_maxEnemies;

    LOG(percentage);

    /* Make sure the scale won't be negative */
    if (percentage >= 0) {
        /* Update health bar */
        m_waveBar->setScale(m_waveBarScale * percentage, m_waveBarScale);
    }
    else {
        m_waveBar->setScale(0, m_waveBarScale);
    }
}

void WaveUIComponent::UpdateWaveText(const int currentWave) {
    /* Update Text */
    m_waveNumberText.setString(std::to_string(currentWave));
    m_waveNumberText.setPosition(
        sf::Vector2f(m_waveText.getGlobalBounds().left, m_waveText.getGlobalBounds().top) +
        sf::Vector2f((m_waveText.getLocalBounds().width / 2) - (m_waveNumberText.getLocalBounds().width / 2) - m_waveNumberText.getLocalBounds().left, m_waveText.getLocalBounds().height + m_waveNumberText.getLocalBounds().top)
    );
}

void WaveUIComponent::StartNewWave(const int waveNum, int maxEnemies) {
    m_maxEnemies = maxEnemies;
    //m_previousEnemyCount = maxEnemies;

    LOG(waveNum)
    UpdateWaveText(waveNum);
}
