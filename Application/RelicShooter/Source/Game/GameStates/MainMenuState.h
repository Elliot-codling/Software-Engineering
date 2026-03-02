#ifndef MAINMENUSTATE_H
#define MAINMENUSTATE_H

#include "../../Engine/System/GameState/GameState.h"
#include "../../Engine/Core/GameObject.h"
#include "../GameObjects/UI/HUD/UIManager.h"
#include "../GameObjects/UI/Crosshair.h"

#include <array>
#include <functional>
#include <memory>
#include <SFML/Graphics/View.hpp>

#include "../DebugHandler.hpp"


class GameObjectWithSprite;
class Button;
class GameObjectWithAnimatedSprite;

/**
 *  basis for the main menu game state which will handle all main menu actions
 *  and transitioning to the next game state (gameplay)
**/

using GameObjectFactory = std::function<std::unique_ptr<GameObject>()>;

/* Templates */
struct LayerTemplate {
    LayerTemplate() = default;
    ~LayerTemplate() {
        goFactories.clear();
    }
    std::vector<GameObjectFactory> goFactories;
};
struct ScreenTemplate {
    ScreenTemplate() = default;
    ~ScreenTemplate() {
        layerStack.clear();
    }

    void PushLayer(LayerTemplate&& layer) {
        layerStack.emplace_back(std::move(layer));
    }

    std::vector<LayerTemplate> layerStack;
};
/* Runtime */
struct Layer {
    std::vector<std::unique_ptr<GameObject>> gameObjects;
};
struct Screen {
    Screen() = default;
    Screen(Screen&&) = default;
    Screen& operator=(Screen&&) = default;

    ~Screen() {
        LOG("Deleted Screen")
        layerStack.clear();
    }

    std::vector<Layer> layerStack;
    bool isInitialised = false;
};

struct ScreenFactory {
    static Screen CreateScreen(const ScreenTemplate& screenTemplate) {
        Screen screen;
        screen.layerStack.reserve(screenTemplate.layerStack.size());
        Layer layer;
        layer.gameObjects.reserve(screenTemplate.layerStack.size());

        for (const auto& layerTemplate : screenTemplate.layerStack) {
            layer.gameObjects.clear();

            for (const auto& go : layerTemplate.goFactories) {
                layer.gameObjects.emplace_back(std::move(go()));
            }

            screen.layerStack.emplace_back(std::move(layer));
        }

        return screen;
    }
};


class MainMenuState : public GameState 
{
    // Key State
    enum KeyState {
        Inactive,
    	Active
        
    };
    // Keys
    enum KeyIndex {
        W_Key,
        A_Key,
        S_Key,
        D_Key,
        KEY_MAX
    };
    // Layers
    enum ScreenIndex {
        MAIN_SCREEN,
        CONTROLS_SCREEN,
        CREDITS_SCREEN,
        SCREEN_MAX
    };

    // Declared reverse order due to initialising in reverse order
    enum ButtonBehaviour {
        QUIT,
        CREDITS,
        CONTROLS,
        PLAY,
        BUTTON_MAX
    };

public:
    MainMenuState(int windowWidth, int windowHeight);
    ~MainMenuState() override = default;

public:
    /* Not required function  */
    GameObject* GetPlayer() override { return nullptr; }

    void Initialise() override;
    void Update() override;
    void FixedUpdate() override;

    void PlayButtonClicked();
    void QuitButtonClicked();

    void CreateMainMenuScreen();
    void CreateControlsScreen();
    void CreateCreditsScreen();

    void SwitchScreen(ScreenIndex screenToSwitchTo);

    void AddCurrentLayers();
    void RemoveCurrentLayers();
private:
    void UpdateInputSprites();
    inline void SetSprite(KeyIndex keyIndex, const char* file);

    void PerformScreenSwitch();

private:
    const int m_windowWidth;
    const int m_windowHeight;
    sf::View m_cameraView;

    /* Button */
    const int m_buttonTextXOffset = 50;
    bool wasPressed0 = false;
    bool wasPressed1 = false;

    bool m_shouldSceneSwitch = false;
    ScreenIndex m_sceneToSwitchTo;
    int m_framesToWait = 0;
    bool m_waitUntilEndOfFrame = false;

    // Title sprite
    GameObjectWithAnimatedSprite* m_titleSprite;

    // Input sprites that change state once interacted with
    GameObjectWithSprite* m_inputSprites[KEY_MAX] = {};


    // Store the input states of each key
    KeyState m_inputKeyStates[KEY_MAX] = {};

    // Screens
    std::vector<ScreenTemplate> m_screenTemplates;
    Screen m_currentScreen;

    std::array<Button*, BUTTON_MAX> m_buttons;

    /* Cursor */
    Crosshair m_crosshair;

    GameState* m_nextGameState;
};

#endif