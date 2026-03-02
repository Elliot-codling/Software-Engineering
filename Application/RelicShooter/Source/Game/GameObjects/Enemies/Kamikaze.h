#pragma once
#include "Enemy.h"

class Kamikaze :
    public Enemy
{
public:
    Kamikaze() = default;
    virtual ~Kamikaze() = default;

    // ### GameObject override functions ###
    void Initialise(Player* player);
    void Update() override;
    sf::Vector2f GetPosition() override;

    // Enemy override functions
    void CheckCollisions();

private:

    enum AnimStates
    {
        IDLE,
	    WALK,
        HIT,
        DEATHEDAMAGE,
        DEATHEXPLODE
    };
};

