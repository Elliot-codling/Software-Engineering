#pragma once
#include "Enemy.h"

class Walker : public Enemy
{

public:
    Walker() = default;
    virtual ~Walker() = default;

    // ### GameObject override functions ###
    void Initialise(Player* player);
    void Update() override;
    sf::Vector2f GetPosition() override;
};

