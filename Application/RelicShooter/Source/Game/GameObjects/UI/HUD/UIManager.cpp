#include "UIManager.h"

#include "../../Player/Player.h"

void UIManager::Initialise(Player& player, std::vector<Enemy*>& enemies) {
    m_player = &player;
    m_enemies = &enemies;

	m_effectOverlay.Initialise(m_player);
    if (m_player != nullptr) {
        m_healthUIComponent.Initialise(m_player->GetHealth());
        m_staminaUIComponent.Initialise(m_player->GetMaxStamina(), m_player->GetDashStaminaCost());
    }

    m_weaponUIComponent.Initialise();
    m_waveUIComponent.Initialise(static_cast<int>(m_enemies->size()));
    m_pointsUIComponent.Initialise();
}

void UIManager::Update() {
    if (m_player == nullptr) {
        return;
    }

    if (!m_isGameEnded) {
        /* Update UI Components */
        m_healthUIComponent.UpdateHealth(m_player->GetHealth(), m_player->GetMaxHealth());
        m_staminaUIComponent.UpdateStaminaBar(m_player->GetStamina(), m_player->GetMaxStamina());

        m_weaponUIComponent.UpdateWeapon(m_player->GetCurrentWeapon(), m_player->GetStashedWeapon());
        m_weaponUIComponent.UpdateAmmo(m_player->GetCurrentWeapon());

        m_waveUIComponent.Update(static_cast<int>(m_enemies->size()), 0);

        m_pointsUIComponent.Update(m_player->GetScore());

        m_effectOverlay.Update(m_player);
    }
    else {
        // Update Game End Screen
    }
}

void UIManager::StartNewWave(int wave, int maxEnemies) {
    m_waveUIComponent.StartNewWave(wave, maxEnemies);
}

void UIManager::StartEndGameUI(bool wasGameWon, GameState* nextGameState, GameState* currentGameState) {
    m_gameEndScreenUIComponent.Initialise(wasGameWon, nextGameState, currentGameState, m_player->GetScore());
}
