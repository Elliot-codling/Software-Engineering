#pragma once
#include "Item.h"
class SpeedCollectible :
    public Item
{
public:
    SpeedCollectible();
    ~SpeedCollectible();

    void Initialise(Player* player);

    void CheckCollisions() override;
};

