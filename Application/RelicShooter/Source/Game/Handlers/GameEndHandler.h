#ifndef GAMEENDHANDLER_H
#define GAMEENDHANDLER_H

class GameState;
class Player;
class UIManager;

class GameEndHandler {
public:
    GameEndHandler() = default;
    ~GameEndHandler() = default;

public:
    void Initialise(Player& player, UIManager& uiManager);
    void Update(bool wasGameWon);

    bool CheckWin() const;
    bool CheckLoss();

    inline void PerformWin();
    inline void PerformLoss();

    void SetCurrentGameState(GameState& currentGState) {
        m_currentGameState = &currentGState;
    }
    void SetNextGameState(GameState& nextGState) {
        m_nextGameState = &nextGState;
    }

private:
    /* Pointers to player and UI manager */
    Player* m_player;
    UIManager* m_uiManager;

    GameState* m_currentGameState;
    /* Next State for Button */
    GameState* m_nextGameState;

    /* Need to stop multiple updates */
    bool m_hasGameEnded = false;
};

#endif