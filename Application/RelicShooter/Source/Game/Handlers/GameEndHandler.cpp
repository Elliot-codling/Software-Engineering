#include "GameEndHandler.h"

#include "../GameObjects/Player/Player.h"
#include "../DebugHandler.hpp"
#include "../../Engine/System/Context/SysContextProvider.h"
#include "../../Engine/System/GameState/GameStateManager.h"
#include "../GameObjects/UI/HUD/UIManager.h"

void GameEndHandler::Initialise(Player& player, UIManager& uiManager) {
    m_player = &player;
    m_uiManager = &uiManager;
}

void GameEndHandler::Update(bool wasGameWon) {
    if (m_player == nullptr || m_uiManager == nullptr) {
        return;
    }

    if (m_hasGameEnded) {
        return;
    }


    /* If player has won this level */
    if (wasGameWon) {
        m_hasGameEnded = true;
        m_uiManager->StartEndGameUI(true, m_nextGameState, m_currentGameState);
        return;
    }
    /* If player has lost on this level */
    if (CheckLoss()) {
        m_hasGameEnded = true;
        LOG("Game End")

        m_uiManager->StartEndGameUI(false, m_nextGameState, m_currentGameState);
        return;
        
    }
}

/* If player has beat all waves */
bool GameEndHandler::CheckWin() const {
    return false;
}

/* If player is dead */
bool GameEndHandler::CheckLoss() {
    /* This should be replaced by m_player->IsDead() so we do not skip the player death animation */
    if (m_player->IsDead()) {
        m_hasGameEnded = true;
        return true;
    }

    return false;
}