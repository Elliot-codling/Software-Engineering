#ifndef UIMANAGER_H
#define UIMANAGER_H

#include "HealthUIComponent.h"
#include "PointsUIComponent.h"
#include "StaminaUIComponent.h"
#include "WaveUIComponent.h"
#include "WeaponUIComponent.h"
#include "GameEndScreenUIComponent.h"
#include "../EffectOverlay.h"

class Player;
class Enemy;

class UIManager {
public:
    UIManager() = default;
    ~UIManager() = default;

public:
    void Initialise(Player& player, std::vector<Enemy*>& enemies);
    void Update();

    void StartNewWave(int wave, int maxEnemies);
    void StartEndGameUI(bool wasGameWon, GameState* nextGameState, GameState* currentGameState);

private:
    /* Pointer to the current player in the scene */
    Player* m_player;

    /* Pointer to the current enemies in the scene */
    std::vector<Enemy*>* m_enemies;

    /* UI Components */
    HealthUIComponent m_healthUIComponent;
    StaminaUIComponent m_staminaUIComponent;
    WeaponUIComponent m_weaponUIComponent;
    WaveUIComponent m_waveUIComponent;
    PointsUIComponent m_pointsUIComponent;
    GameEndScreenUIComponent m_gameEndScreenUIComponent;
    EffectOverlay m_effectOverlay;

    bool m_isGameEnded = false;
};

#endif