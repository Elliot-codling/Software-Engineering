#include "MainMenuState.h"

#include "GameStateLevel1.h"
#include "GameStateTest.h"
#include "../../Engine/System/GameState/GameStateManager.h"
#include "../GameObjects/UI/ScrollableBackground.h"
#include "../GameStates/GameplayState.h"
#include "../../Engine/Renderer/WindowManager.h"
#include "../../Engine/System/Context/SysContextProvider.h"
#include "../../Engine/Renderer/RenderManager.h"
#include "../GameObjects/UI/Button.h"
#include "../GameObjects/BaseGameObjects/GameObjectWithSprite.h"
#include "../GameObjects/BaseGameObjects/GameObjectWithAnimatedSprite.h"

#include <sstream>
#include <iostream>
#include <fstream>

#include "../GameObjects/BaseGameObjects/GameObjectWithText.h"


MainMenuState::MainMenuState(const int windowWidth, const int windowHeight) :
    m_windowWidth(windowWidth),
    m_windowHeight(windowHeight)
{
  
}

void MainMenuState::Initialise() {
    // Reset the camera position
	//m_cameraView = sf::View(sf::FloatRect(0, 0, static_cast<float>(m_windowWidth), static_cast<float>(m_windowHeight)));
    //C_SysContext::Get<WindowManager>()->GetWindow()->setView(m_cameraView);
    C_SysContext::Get<RenderManager>()->RemoveGameRenderView();

    m_nextGameState = new GameStateLevel1();

    /* Create all screen templates */
    CreateMainMenuScreen();
    CreateControlsScreen();
    CreateCreditsScreen();

    /* Set the initial screen to be the main screen */
    m_currentScreen = ScreenFactory::CreateScreen(m_screenTemplates[MAIN_SCREEN]);
    m_currentScreen.isInitialised = true;

    AddCurrentLayers();

    m_crosshair.Initialise();
}

void MainMenuState::Update() {
    /* Perform screen switch if flagged last frame */
    if (m_shouldSceneSwitch && !wasPressed0) {
        RemoveCurrentLayers();

        /* Perform update loop to remove all objects from m_GameObjects */
        GameState::Update();

        PerformScreenSwitch();
        m_currentScreen.isInitialised = true;
    }

    if (m_currentScreen.isInitialised) {
        GameState::Update();
        m_crosshair.Update();
        return;
    }
}

void MainMenuState::FixedUpdate() {
	GameState::FixedUpdate();
}

void MainMenuState::PlayButtonClicked() {
    LOG("Play Clicked");
    C_SysContext::Get<GameStateManager>()->QueueGameState(m_nextGameState);
}

void MainMenuState::QuitButtonClicked() {
    C_SysContext::Get<WindowManager>()->GetWindow().close();
}


void MainMenuState::CreateMainMenuScreen() {
    ScreenTemplate mainScreenTemplate;

    LayerTemplate backgroundLayer;
    LayerTemplate foregroundLayer;

    /* First button */
    foregroundLayer.goFactories.emplace_back([this]() -> std::unique_ptr<GameObject> {
        auto button = std::make_unique<Button>("sprites/MenuSprites/spr_menu_button.png", sf::Vector2f(0, 0), 1.5f);
        button->CreateButton();
        button->SetPosition(0, m_windowHeight - ((PLAY + 2) * (button->GetSpriteRect().height + 10)));
        button->SetHoveredSpriteFile("sprites/MenuSprites/spr_menu_button_hovered.png");
        button->SetClickedSpriteFile("sprites/MenuSprites/spr_menu_button_clicked.png");

        /* Play button */
        auto PlayClickEvent = [this]() {
            PlayButtonClicked(); };
        button->AddClickEventFunction(PlayClickEvent);
        button->CreateAndSetButtonText(sf::Vector2f(button->GetPosition().x + m_buttonTextXOffset, button->GetPosition().y - 9), "PLAY", sf::Color::Black, 60, "fonts/BoldPixels.TTF");

        return button;
    });

    /* Second Button (Options) */
    foregroundLayer.goFactories.emplace_back([this]() -> std::unique_ptr<GameObject> {
        auto button = std::make_unique<Button>("sprites/MenuSprites/spr_menu_button.png", sf::Vector2f(0, 0), 1.5f);
        button->CreateButton();
        button->SetPosition(0, m_windowHeight - ((CONTROLS + 2) * (button->GetSpriteRect().height + 10)));
        button->SetHoveredSpriteFile("sprites/MenuSprites/spr_menu_button_hovered.png");
        button->SetClickedSpriteFile("sprites/MenuSprites/spr_menu_button_clicked.png");

        /* Options button */
        auto OptionsClickEvent = [this]() {
            LOG("Options Button Clicked")
            SwitchScreen(CONTROLS_SCREEN);
        };
        button->AddClickEventFunction(OptionsClickEvent);
        button->CreateAndSetButtonText(sf::Vector2f(button->GetPosition().x + m_buttonTextXOffset, button->GetPosition().y - 9), "CONTROLS", sf::Color::Black, 60, "fonts/BoldPixels.TTF");

        return button;
    });

    /* Third Button (Credits) */
    foregroundLayer.goFactories.emplace_back([this]() -> std::unique_ptr<GameObject> {
        auto button = std::make_unique<Button>("sprites/MenuSprites/spr_menu_button.png", sf::Vector2f(0, 0), 1.5f);
        button->CreateButton();
        button->SetPosition(0, m_windowHeight - ((CREDITS + 2) * (button->GetSpriteRect().height + 10)));
        button->SetHoveredSpriteFile("sprites/MenuSprites/spr_menu_button_hovered.png");
        button->SetClickedSpriteFile("sprites/MenuSprites/spr_menu_button_clicked.png");

        /* Setup Credits Button */
        auto OptionsClickEvent = [this]() {
            LOG("Credits Button Clicked")
                SwitchScreen(CREDITS_SCREEN);
        };
        button->AddClickEventFunction(OptionsClickEvent);
        button->CreateAndSetButtonText(sf::Vector2f(button->GetPosition().x + m_buttonTextXOffset, button->GetPosition().y - 9), "CREDITS", sf::Color::Black, 60, "fonts/BoldPixels.TTF");
    
        return button;
    });

    /* Fourth Button (Quit) */
    foregroundLayer.goFactories.emplace_back([this]() -> std::unique_ptr<GameObject> {
        auto button = std::make_unique<Button>("sprites/MenuSprites/spr_menu_button.png", sf::Vector2f(0, 0), 1.5f);
        button->CreateButton();
        button->SetPosition(0, m_windowHeight - ((QUIT + 2) * (button->GetSpriteRect().height + 10)));
        button->SetHoveredSpriteFile("sprites/MenuSprites/spr_menu_button_hovered.png");
        button->SetClickedSpriteFile("sprites/MenuSprites/spr_menu_button_clicked.png");

        /* Setup Quit Button */
        auto QuitClickEvent = [this]() { QuitButtonClicked(); };
        button->AddClickEventFunction(QuitClickEvent);
        button->CreateAndSetButtonText(sf::Vector2f(button->GetPosition().x + m_buttonTextXOffset, button->GetPosition().y - 9), "QUIT", sf::Color::Black, 60, "fonts/BoldPixels.TTF");

        return button;
    });

    /* Create background image */
    backgroundLayer.goFactories.emplace_back([this]() -> std::unique_ptr<GameObject> {
        auto backgroundSprite = std::make_unique<GameObjectWithSprite>("sprites/MenuSprites/bg_menu_main.png", sf::Vector2f(0, 0), 1.f);
        backgroundSprite->CreateSprite();
        backgroundSprite->SetScaleInPixels({ m_windowWidth, m_windowHeight });

        return backgroundSprite;
    });
    /* Create scrollable stars background */
    backgroundLayer.goFactories.emplace_back([this]() -> std::unique_ptr<GameObject> {
        auto scrollableBackground = std::make_unique<ScrollableBackground>();
        scrollableBackground->Create("sprites/MenuSprites/spr_menu_bg_stars.png");

        return scrollableBackground;
    });


    /* Initialise all input sprites */
    for (int i = 0; i < std::size(m_inputSprites); i++) {
        /* Creates a new factory for every input sprite */
        foregroundLayer.goFactories.emplace_back([this, i]() -> std::unique_ptr<GameObject> {
            auto inputSprite = std::make_unique<GameObjectWithSprite>();

            switch (i) {
            case W_Key:
                inputSprite->SetSpriteFile("sprites/input-sprites/kenney/keyboard_w_outline.png");
                break;
            case A_Key:
                inputSprite->SetSpriteFile("sprites/input-sprites/kenney/keyboard_a_outline.png");
                break;
            case S_Key:
                inputSprite->SetSpriteFile("sprites/input-sprites/kenney/keyboard_s_outline.png");
                break;
            case D_Key:
                inputSprite->SetSpriteFile("sprites/input-sprites/kenney/keyboard_d_outline.png");
                break;
            }

            inputSprite->SetScale(1.0f);
            inputSprite->SetPosition(
                sf::Vector2f(static_cast<float>(m_windowWidth) - 100,
                    (static_cast<float>(m_windowHeight) - (64 * 4)) + (i * 64 - 36))
            );

            inputSprite->CreateSprite();

            return inputSprite;
        });
    }

    /* Create animated title sprite */
    foregroundLayer.goFactories.emplace_back([this]() -> std::unique_ptr<GameObject> {
        sf::Vector2i distanceFromBorder = { -150, 25 };
        float titleScale = 1.5f;

        auto titleSprite = std::make_unique<GameObjectWithAnimatedSprite>();
        titleSprite->AddSpriteSheet("sprites/MenuSprites/Title/spr_intro.xml");
        titleSprite->AddAnimation(0, "spr_logo", 12, false);
        titleSprite->SetScale(sf::Vector2f(titleScale, titleScale));
        titleSprite->SetCurrentAnimation(0);
        sf::Vector2i titleSize = titleSprite->GetFrameSize();

        titleSprite->SetPosition(sf::Vector2f(((titleSize.x * titleSprite->GetScale().x) / 2) + distanceFromBorder.x,
                                              ((titleSize.y * titleSprite->GetScale().y) / 2) + distanceFromBorder.y));

        return titleSprite;
    });

    /* Push layers in order < back -> front > */
    mainScreenTemplate.PushLayer(std::move(backgroundLayer));
    mainScreenTemplate.PushLayer(std::move(foregroundLayer));

    m_screenTemplates.emplace_back(mainScreenTemplate);
}

void MainMenuState::CreateControlsScreen() {
    ScreenTemplate controlsScreenTemplate;
    
    LayerTemplate backgroundLayer;
    LayerTemplate foregroundLayer;
    
    /* Back button */
    foregroundLayer.goFactories.emplace_back([this]() -> std::unique_ptr<GameObject> {
        auto button = std::make_unique<Button>("sprites/MenuSprites/spr_menu_button.png", sf::Vector2f(0, 0), 1.5f);
        button->CreateButton();
        button->SetPosition(-300, 0 + ((PLAY + 2) * (button->GetSpriteRect().height + 10)));
        button->SetHoveredSpriteFile("sprites/MenuSprites/spr_menu_button_hovered.png");
        button->SetClickedSpriteFile("sprites/MenuSprites/spr_menu_button_clicked.png");
    
        /* Back button */
        auto BackClickEvent = [this]() {
            SwitchScreen(MAIN_SCREEN);
        };
        button->AddClickEventFunction(BackClickEvent);
        button->CreateAndSetButtonText(sf::Vector2f(button->GetPosition().x + 350, button->GetPosition().y - 9), "BACK", sf::Color::Black, 60, "fonts/BoldPixels.TTF");
    
        return button;
    });

    /* Create background image */
    backgroundLayer.goFactories.emplace_back([this]() -> std::unique_ptr<GameObject> {
        auto backgroundSprite = std::make_unique<GameObjectWithSprite>("sprites/MenuSprites/bg_menu_settings.png", sf::Vector2f(0, 0), 1.5f);
        backgroundSprite->CreateSprite();
        backgroundSprite->SetScaleInPixels({ m_windowWidth, m_windowHeight });

        return backgroundSprite;
    });
    /* Create scrollable stars background */
    backgroundLayer.goFactories.emplace_back([this]() -> std::unique_ptr<GameObject> {
        auto scrollableBackground = std::make_unique<ScrollableBackground>();
        scrollableBackground->Create("sprites/MenuSprites/spr_menu_bg_stars.png");

        return scrollableBackground;
    });


    /* Controls Text Background */
    foregroundLayer.goFactories.emplace_back([this]() -> std::unique_ptr<GameObject> {
        auto backgroundSprite = std::make_unique<GameObjectWithSprite>("ui/HUD/spr_hud_bar_0.png", sf::Vector2f(0, 0));
        backgroundSprite->CreateSprite();
        backgroundSprite->SetScaleInPixels(sf::Vector2i(1080, 645));
        backgroundSprite->SetPosition(800.0f - 25, 242.5f - 25.0f);
        backgroundSprite->SetColour(sf::Color(250, 250, 250, 175.0f));

        return backgroundSprite;
    });


    /* Controls Text */
    std::ifstream file("MenuInfo/controls.txt");
    std::stringstream buffer;
    buffer << file.rdbuf();
    std::string line;

    int amountOfLines = 0;

    if (!file.is_open()) {
        LOG("Could not find controls.txt")
        file.close();
    } else {
        LOG("Found controls.txt")
    }

    /* Get amount of lines */
    while (true) {
        if (std::getline(buffer, line)) {
            amountOfLines++;
        }
        else {
            break;
        }
    }

    buffer.clear();
    buffer.seekg(0, std::ios::beg);

    for (int i = 0; i < amountOfLines; i++) {
        std::getline(buffer, line);

        foregroundLayer.goFactories.emplace_back([this, line, i]() -> std::unique_ptr<GameObject> {
            auto textLine = std::make_unique<GameObjectWithText>();
            textLine->Initialise();
            textLine->SetFontFile("fonts/PixelCode-Black.ttf");
            textLine->SetDisplayText(line);
            textLine->SetColour(sf::Color(238, 75, 43));
            textLine->SetCharSize(35);
            textLine->SetCharSpacing(1.25f);
            textLine->SetPosition(800.0f, 242.5f  + (i * 35.0f));

            return textLine;
        });
    }

    /* Push layers in order < back -> front > */
    controlsScreenTemplate.PushLayer(std::move(backgroundLayer));
    controlsScreenTemplate.PushLayer(std::move(foregroundLayer));
    
    m_screenTemplates.emplace_back(controlsScreenTemplate);
}

void MainMenuState::CreateCreditsScreen() {
    ScreenTemplate creditsScreenTemplate;

    LayerTemplate backgroundLayer;
    LayerTemplate foregroundLayer;

    /* Back button */
    foregroundLayer.goFactories.emplace_back([this]() -> std::unique_ptr<GameObject> {
        auto button = std::make_unique<Button>("sprites/MenuSprites/spr_menu_button.png", sf::Vector2f(0, 0), 1.5f);
        button->CreateButton();
        button->SetPosition(-300, 0 + ((PLAY + 2) * (button->GetSpriteRect().height + 10)));
        LOG(m_windowHeight)
            button->SetHoveredSpriteFile("sprites/MenuSprites/spr_menu_button_hovered.png");
        button->SetClickedSpriteFile("sprites/MenuSprites/spr_menu_button_clicked.png");

        /* Back button */
        auto BackClickEvent = [this]() {
            SwitchScreen(MAIN_SCREEN);
            };
        button->AddClickEventFunction(BackClickEvent);
        button->CreateAndSetButtonText(sf::Vector2f(button->GetPosition().x + 350.0f, button->GetPosition().y - 9), "BACK", sf::Color::Black, 60, "fonts/BoldPixels.TTF");

        return button;
        });

    /* Create background image */
    backgroundLayer.goFactories.emplace_back([this]() -> std::unique_ptr<GameObject> {
        auto backgroundSprite = std::make_unique<GameObjectWithSprite>("sprites/MenuSprites/bg_menu_nested.png", sf::Vector2f(0, 0), 1.5f);
        backgroundSprite->CreateSprite();
        backgroundSprite->SetScaleInPixels({ m_windowWidth, m_windowHeight });

        return backgroundSprite;
        });
    /* Create scrollable stars background */
    backgroundLayer.goFactories.emplace_back([this]() -> std::unique_ptr<GameObject> {
        auto scrollableBackground = std::make_unique<ScrollableBackground>();
        scrollableBackground->Create("sprites/MenuSprites/spr_menu_bg_stars.png");

        return scrollableBackground;
        });


    /* Credits Text Background */
    foregroundLayer.goFactories.emplace_back([this]() -> std::unique_ptr<GameObject> {
        auto backgroundSprite = std::make_unique<GameObjectWithSprite>("ui/HUD/spr_hud_bar_0.png", sf::Vector2f(0, 0));
        backgroundSprite->CreateSprite();
        backgroundSprite->SetScaleInPixels(sf::Vector2i(1015, 645));
        backgroundSprite->SetPosition(800.0f - 25, 242.5f - 25.0f);
        backgroundSprite->SetColour(sf::Color(250, 250, 250, 175.0f));

        return backgroundSprite;
        });


    /* Credits Text */
    std::ifstream file("MenuInfo/credits.txt");
    std::stringstream buffer;
    buffer << file.rdbuf();
    std::string line;

    int amountOfLines = 0;

    if (!file.is_open()) {
        LOG("Could not find credits.txt")
            file.close();
    }
    else {
        LOG("Found credits.txt")
    }

    /* Get amount of lines */
    while (true) {
        if (std::getline(buffer, line)) {
            amountOfLines++;
        }
        else {
            break;
        }
    }

    buffer.clear();
    buffer.seekg(0, std::ios::beg);

    for (int i = 0; i < amountOfLines; i++) {
        std::getline(buffer, line);

        foregroundLayer.goFactories.emplace_back([this, line, i]() -> std::unique_ptr<GameObject> {
            auto textLine = std::make_unique<GameObjectWithText>();
            textLine->Initialise();
            textLine->SetFontFile("fonts/PixelCode-Black.ttf");
            textLine->SetDisplayText(line);
            textLine->SetColour(sf::Color(238, 75, 43));
            textLine->SetCharSize(35);
            textLine->SetCharSpacing(1.25f);
            textLine->SetPosition(800, 242.5f + (i * 35.0f));

            return textLine;
            });
    }

    /* Push layers in order < back -> front > */
    creditsScreenTemplate.PushLayer(std::move(backgroundLayer));
    creditsScreenTemplate.PushLayer(std::move(foregroundLayer));

    m_screenTemplates.emplace_back(creditsScreenTemplate);
}

/* Maybe move this to a transition/screen manager? */
void MainMenuState::SwitchScreen(ScreenIndex screenToSwitchTo) {
    m_shouldSceneSwitch = true;
    m_sceneToSwitchTo = screenToSwitchTo;
}

void MainMenuState::AddCurrentLayers() {
    /* Add all game objects to be updated and rendered in layer order */
    for (const auto& layer : m_currentScreen.layerStack) {
        for (auto& obj : layer.gameObjects) {
            AddGameObject(obj.get());
            obj->Initialise();
        }
    }
}

void MainMenuState::RemoveCurrentLayers() {
    /* Remove all game objects from update and rendering */
    for (auto& layer : m_currentScreen.layerStack) {
        for (auto& obj : layer.gameObjects) {
            RemoveGameObject(obj.get());
        }
        /* Clear gameobjects inside of layer */
        layer.gameObjects.clear();
    }

    /* Clear game objects in the states gameobject pool */
    m_GameObjects.clear();
}

/* Only for visuals for now */
/* Updates the sprites in the menu whenever their corresponding key is pressed */
void MainMenuState::UpdateInputSprites() {
    // Store key states as of last update 
    KeyState lastUpdateKeyStates[KEY_MAX] = {};
    for (int i = 0; i < std::size(m_inputKeyStates); i++) {
        lastUpdateKeyStates[i] = m_inputKeyStates[i];
    }

    /* Update key states */
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
        m_inputKeyStates[W_Key] = Active;
    }  else {
        m_inputKeyStates[W_Key] = Inactive;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
        m_inputKeyStates[A_Key] = Active;
    }  else {
        m_inputKeyStates[A_Key] = Inactive;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
        m_inputKeyStates[S_Key] = Active;
    }  else {
        m_inputKeyStates[S_Key] = Inactive;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
        m_inputKeyStates[D_Key] = Active;
    }  else {
        m_inputKeyStates[D_Key] = Inactive;
    }

    /* Change sprites */
    /* Desc: checks current key states against last update key state so that we do not repeat changes every update tick */
    if (m_inputKeyStates[W_Key] == Active && lastUpdateKeyStates[W_Key] == Inactive) { /* W */
        SetSprite(W_Key, "sprites/input-sprites/kenney/keyboard_w.png");
    }  else if (m_inputKeyStates[W_Key] == Inactive && lastUpdateKeyStates[W_Key] == Active) {
        SetSprite(W_Key, "sprites/input-sprites/kenney/keyboard_w_outline.png");
    }

    if (m_inputKeyStates[A_Key] == Active && lastUpdateKeyStates[A_Key] == Inactive) { /* A */
        SetSprite(A_Key, "sprites/input-sprites/kenney/keyboard_a.png");
    }  else if (m_inputKeyStates[A_Key] == Inactive && lastUpdateKeyStates[A_Key] == Active) {
        SetSprite(A_Key, "sprites/input-sprites/kenney/keyboard_a_outline.png");
    }

    if (m_inputKeyStates[S_Key] == Active && lastUpdateKeyStates[S_Key] == Inactive) { /* S */
        SetSprite(S_Key, "sprites/input-sprites/kenney/keyboard_s.png");
    }  else if (m_inputKeyStates[S_Key] == Inactive && lastUpdateKeyStates[S_Key] == Active) {
        SetSprite(S_Key, "sprites/input-sprites/kenney/keyboard_s_outline.png");
    }

    if (m_inputKeyStates[D_Key] == Active && lastUpdateKeyStates[D_Key] == Inactive) { /* D */
        SetSprite(D_Key, "sprites/input-sprites/kenney/keyboard_d.png");
    }  else if (m_inputKeyStates[D_Key] == Inactive && lastUpdateKeyStates[D_Key] == Active) {
        SetSprite(D_Key, "sprites/input-sprites/kenney/keyboard_d_outline.png");
    }
}

void MainMenuState::SetSprite(KeyIndex keyIndex, const char* file) {
    m_inputSprites[keyIndex]->SetSprite(file);
}

void MainMenuState::PerformScreenSwitch() {
    m_currentScreen = ScreenFactory::CreateScreen(m_screenTemplates[m_sceneToSwitchTo]);
    AddCurrentLayers();
    m_shouldSceneSwitch = false;
}
