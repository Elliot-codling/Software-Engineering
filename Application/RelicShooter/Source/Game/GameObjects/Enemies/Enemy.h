#pragma once
#include "../BaseGameObjects/GameObjectWithAnimatedSprite.h"
#include "../../../Engine/Physics/BoxCollider2D.h"

class Player;

class Enemy :
    public GameObjectWithAnimatedSprite, public BoxCollider2D
{
public:
    // Default constructor and destructor
    Enemy() = default;
    ~Enemy() = default;

    // Chasing the player
    void Chase();

    // Set and Get functions
	int GetDamage();
    int GetHealth();
    void SetHealth(int health);

    // Collisions
    void CheckCollisions();
    void CheckWorldCollisions(size_t tile, std::map<size_t, BoxCollider2D>& collisionLayer);
    void DefineHitObjects(int collidedTile);
    inline bool CheckCollisionWithTile(size_t tile, std::map<size_t, BoxCollider2D>& collisionLayer);
    inline void ClampDirection(sf::Vector2f& directionVector) const;
    void TakeDamage(int damageTaken);
    bool IsDead();

protected:

    // A reference of the player
    Player* m_player;

    // Window context
    size_t m_windowWidth = 0;
    size_t m_windowHeight = 0;

    // Movement
   // --------------------------LEFT--------RIGHT--------UP--------DOWN
    sf::IntRect     m_hitObject = { 0, 0, 0, 0 };
    sf::Vector2f	m_targetLocation;
    float			m_moveSpeed;
    float           m_detectionRadius;

    // Animations
    enum AnimStates
    {
        IDLE,
        WALK,
        HIT,
        DEATHDAMAGE
    };

    // Variables for damaging the player
    int             m_damage;

    // Collisions
    sf::Vector2f    m_enemySize;
    bool            m_collided;

    // Variables to check if the enemy is alive
    int             m_health;
    bool			m_isAlive;

    // Variables for rewarding good gameplay
    int             m_damagedPoints;
    int             m_killedPoints;
};

