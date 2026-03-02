#ifndef WAVEUICOMPONENT_H
#define WAVEUICOMPONENT_H

#include "UIElement.h"
#include "../../../../Engine/Renderer/Sprite.h"
#include "../../../../Engine/UI/Text.h"

class WaveUIComponent : public UIElement {
public:
    WaveUIComponent() = default;
    ~WaveUIComponent() = default;

public:
    void Initialise(const int enemyCount);
    void Update(const int enemiesRemaining, const int enemiesInWave);

    void StartNewWave(const int waveNum, int maxEnemies);
private:
    void UpdateWaveBar(const int enemiesRemaining, const int enemiesInWave);
    void UpdateWaveText(const int currentWave);
    void UpdateEnemyCount();


private:
    Sprite* m_waveBar;
    Sprite* m_waveBarShadow;

    Text m_waveText;
    Text m_waveNumberText;

    const float m_waveBarScale = 3.5f;
    const float m_waveBarShadowOffset = 5.0f;

    const sf::Color m_waveBarColour = sf::Color(77, 208, 247, 255.0f);

    int m_previousEnemyCount;
    int m_maxEnemies = 0;
    bool m_updateText = false;

    sf::RectangleShape rect;
    sf::RectangleShape rect2;
};

#endif