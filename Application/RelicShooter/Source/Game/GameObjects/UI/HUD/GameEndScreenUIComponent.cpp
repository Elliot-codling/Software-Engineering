#include "GameEndScreenUIComponent.h"

#include "../../../DebugHandler.hpp"
#include "../../../../Engine/System/Context/SysContextProvider.h"
#include "../../../../Engine/System/GameState/GameStateManager.h"
#include "../../../GameStates/MainMenuState.h"
#include "../../../Input/ControllerInputDevice.h"
#include "../../BaseGameObjects/GameObjectWithText.h"

void GameEndScreenUIComponent::Initialise(bool wasGameWon, GameState* nextGameState, GameState* currentGameState, int points) {
    if (nextGameState != nullptr) {
        m_nextGameState = nextGameState;
    }
    if (currentGameState != nullptr) {
        m_currentGameState = currentGameState;
    }
    m_points = points;

    if (wasGameWon) {
        CreateWinScreen();
    } else {
        CreateLossScreen();
    }

    LOG("GameEndScreen Created")
}

void GameEndScreenUIComponent::CreateWinScreen() {
    CreateBackground(m_winBackgroundColour);

    /* Screen */
    CreateScreenBackground();

    /* Title Text */
    CreateTitleText("Game Won");

    /* Points Text */
    CreatePointsText();

    if (m_nextGameState == nullptr) {
        CreateCentralMenuButton();
        return;
    }


    /* --- Next Level Button --- */
    CreateLeftAlignedButton("Next Level", m_nextGameState);

    /* --- Next Level Button --- */
    CreateRightAlignedButton("Main Menu", new MainMenuState(1920, 1080));
}



void GameEndScreenUIComponent::CreateLossScreen() {
    CreateBackground(m_lossBackgroundColour);

    LOG("Loss Screen Created")

    /* Screen */
    CreateScreenBackground();

    /* Title Text */
    CreateTitleText("Game Lost");

    /* Points Text */
    CreatePointsText();

    /* Create Button */
    CreateLeftAlignedButton("Restart Level", m_currentGameState);

    CreateRightAlignedButton("Main Menu", new MainMenuState(1920, 1080));
}

void GameEndScreenUIComponent::CreateBackground(sf::Color colour) {
    m_backgroundSprite.Initialise("ui/HUD/spr_hud_bar_0.png", colour, 1, true);
    m_backgroundSprite.setTextureRect({ 0, 0, 1920, 1080 });
    m_backgroundSprite.AddToRenderQueue();
}

void GameEndScreenUIComponent::CreateScreenBackground() {
    m_screenSprite.Initialise("ui/HUD/spr_hud_bar_0.png", m_screenColour, 1, true);
    m_screenSprite.setTextureRect({ 0, 0, 1920 / 2, 1080 / 2 });
    m_screenSprite.setPosition(1920 / 4, 1080 / 4);
    m_screenSprite.AddToRenderQueue();
}

void GameEndScreenUIComponent::CreateTitleText(std::string text) {
    m_titleText.Initialise("fonts/8-BIT WONDER.TTF", text.c_str(), sf::Color::Black, 75, true);
    m_titleText.setPosition(m_screenSprite.getPosition() +
        sf::Vector2f((m_screenSprite.getTextureRect().width / 2) - (m_titleText.getGlobalBounds().width / 2) - m_titleText.getLocalBounds().left,
            (m_screenSprite.getTextureRect().height / 2) - (m_titleText.getGlobalBounds().height / 2) - m_titleText.getLocalBounds().top) -
        sf::Vector2f(0, 200.0f));
}

void GameEndScreenUIComponent::CreateLeftAlignedButton(std::string text, GameState* nextGameState) {
    /* --- Next Level Button --- */
    m_nextGameStateButton = Button("ui/HUD/spr_menu_button_0.png", sf::Vector2f(0, 0), 1.5f);
    m_nextGameStateButton.CreateButton(true);
    m_nextGameStateButton.SetHoveredSpriteFile("ui/HUD/spr_menu_button_1.png");
    auto NewStateButton = [nextGameState]() {
        C_SysContext::Get<GameStateManager>()->QueuePop();
        C_SysContext::Get<GameStateManager>()->QueueGameState(nextGameState);

    };
    m_nextGameStateButton.AddClickEventFunction(NewStateButton);
    C_SysContext::Get<GameStateManager>()->GetCurrentGameState()->AddGameObject(&m_nextGameStateButton);
    m_nextGameStateButton.CreateAndSetButtonText(sf::Vector2f(0, 0), text.c_str(), sf::Color::Black, 30, "fonts/BoldPixels.TTF");
    m_nextGameStateButton.Initialise();
    /* Set position of button and text */
    m_nextGameStateButton.SetPosition((1920 / 2) - (m_nextGameStateButton.GetSpriteRect().width / 2) - 150.0f, 1080 / 2 + 150.0f);
    sf::FloatRect localBounds1 = m_nextGameStateButton.GetTextObject()->GetLocalBounds();
    sf::FloatRect globalBounds1 = m_nextGameStateButton.GetTextObject()->GetGlobalBounds();
    m_nextGameStateButton.GetTextObject()->SetPosition(m_nextGameStateButton.GetPosition() +
        sf::Vector2f((m_nextGameStateButton.GetSpriteRect().width / 2) - (globalBounds1.width / 2) + localBounds1.left, (m_nextGameStateButton.GetSpriteRect().height / 2) - (localBounds1.height / 2) - localBounds1.top)
    );
}

void GameEndScreenUIComponent::CreateRightAlignedButton(std::string text, GameState* nextGameState) {
    m_mainMenuButton = Button("ui/HUD/spr_menu_button_0.png", sf::Vector2f(0, 0), 1.5f);
    m_mainMenuButton.CreateButton(true);
    m_mainMenuButton.SetHoveredSpriteFile("ui/HUD/spr_menu_button_1.png");
    auto NextStateButton = []() {
        C_SysContext::Get<GameStateManager>()->QueuePop();
        C_SysContext::Get<GameStateManager>()->QueueGameState(new MainMenuState(1920, 1080));

        };
    m_mainMenuButton.AddClickEventFunction(NextStateButton);
    C_SysContext::Get<GameStateManager>()->GetCurrentGameState()->AddGameObject(&m_mainMenuButton);
    m_mainMenuButton.CreateAndSetButtonText(sf::Vector2f(0, 0), text.c_str(), sf::Color::Black, 30, "fonts/BoldPixels.TTF");
    m_mainMenuButton.Initialise();
    /* Set position of button and text */
    m_mainMenuButton.SetPosition((1920 / 2) - (m_mainMenuButton.GetSpriteRect().width / 2) + 150.0f, 1080 / 2 + 150.0f);
    sf::FloatRect localBounds = m_mainMenuButton.GetTextObject()->GetLocalBounds();
    sf::FloatRect globalBounds = m_mainMenuButton.GetTextObject()->GetGlobalBounds();
    m_mainMenuButton.GetTextObject()->SetPosition(m_mainMenuButton.GetPosition() +
        sf::Vector2f((m_mainMenuButton.GetSpriteRect().width / 2) - (globalBounds.width / 2) + localBounds.left, (m_mainMenuButton.GetSpriteRect().height / 2) - (localBounds.height / 2) - localBounds.top)
    );
}

void GameEndScreenUIComponent::CreatePointsText() {
    std::string pointsText = "Points     " + std::to_string(m_points);
    m_pointsText.Initialise("fonts/8-BIT WONDER.TTF", pointsText.c_str(), sf::Color::Black, 50, true);
    m_pointsText.setPosition(m_screenSprite.getPosition() +
                             sf::Vector2f((m_screenSprite.getTextureRect().width / 2) - (m_titleText.getGlobalBounds().width / 2) - m_titleText.getLocalBounds().left,
                                          (m_screenSprite.getTextureRect().height / 2) - (m_titleText.getGlobalBounds().height / 2) - m_titleText.getLocalBounds().top) -
                             sf::Vector2f(0, 0));
}


void GameEndScreenUIComponent::CreateCentralMenuButton() {
    /* Menu */
    m_mainMenuButton = Button("ui/HUD/spr_menu_button_0.png", sf::Vector2f(0, 0), 1.5f);
    m_mainMenuButton.CreateButton(true);
    m_mainMenuButton.SetHoveredSpriteFile("ui/HUD/spr_menu_button_1.png");
    auto MainMenuButton = []() {
        C_SysContext::Get<GameStateManager>()->QueuePop();
        C_SysContext::Get<GameStateManager>()->QueueGameState(new MainMenuState(1920, 1080));

        };
    m_mainMenuButton.AddClickEventFunction(MainMenuButton);
    C_SysContext::Get<GameStateManager>()->GetCurrentGameState()->AddGameObject(&m_mainMenuButton);
    m_mainMenuButton.CreateAndSetButtonText(sf::Vector2f(0, 0), "Menu", sf::Color::Black, 30, "fonts/BoldPixels.TTF");
    m_mainMenuButton.Initialise();
    /* Set position of button and text */
    m_mainMenuButton.SetPosition((1920 / 2) - (m_mainMenuButton.GetSpriteRect().width / 2), 1080 / 2 + 150.0f);
    sf::FloatRect localBounds = m_mainMenuButton.GetTextObject()->GetLocalBounds();
    sf::FloatRect globalBounds = m_mainMenuButton.GetTextObject()->GetGlobalBounds();
    m_mainMenuButton.GetTextObject()->SetPosition(m_mainMenuButton.GetPosition() +
        sf::Vector2f((m_mainMenuButton.GetSpriteRect().width / 2) - (globalBounds.width / 2) + localBounds.left, (m_mainMenuButton.GetSpriteRect().height / 2) - localBounds.top)
    );
}
