#pragma once
#include "Enemy.h"


class TileMap;
class EnemyBaseWeapon;

class Shooter :
    public Enemy
{
public:
    Shooter() = default;
    ~Shooter() override = default;

    // ### GameObject override functions ###
    void Initialise(Player* player, TileMap* tileMap);
    void Update() override;
    sf::Vector2f GetPosition() override;

    // Unique shooter functions
    void UpdateGun();

private:
    int weaponSelect;
    EnemyBaseWeapon* m_weapon = nullptr;
    
};

