#ifndef GAMEENDSCREEN_H
#define GAMEENDSCREEN_H

#include "UIElement.h"
#include "../Button.h"
#include "../../../../Engine/Renderer/Sprite.h"
#include "../../../../Engine/UI/Text.h"

class GameState;

class GameEndScreenUIComponent : public UIElement {
public:
    GameEndScreenUIComponent() = default;
    ~GameEndScreenUIComponent() = default;

public:
    void Initialise(bool wasGameWon, GameState* nextGameState, GameState* currentGameState, int points);

    inline void CreateWinScreen();
    inline void CreateLossScreen();

    inline void CreateBackground(sf::Color colour);
    inline void CreateScreenBackground();
    inline void CreateTitleText(std::string text);

    inline void CreateLeftAlignedButton(std::string text, GameState* nextGameState);
    inline void CreateRightAlignedButton(std::string text, GameState* nextGameState);

    inline void CreatePointsText();
    inline void CreateCentralMenuButton();

private:
    GameState* m_currentGameState;
    GameState* m_nextGameState;
    int m_points;

    Sprite m_backgroundSprite;
    const float m_backgroundOpacity = 0.75f;
    const sf::Color m_winBackgroundColour = sf::Color(0.0f, 255.0f, 0.0f, 100.0f);
    const sf::Color m_lossBackgroundColour = sf::Color(255.0f, 0.0f, 0.0f, 100.0f);

    Sprite m_screenSprite;
    const sf::Color m_screenColour = sf::Color(255, 191, 0, 255.0f);

    Text m_titleText;
    Text m_pointsText;

    Button m_mainMenuButton;
    /* This is only in the win state */
    Button m_nextGameStateButton;
};

#endif