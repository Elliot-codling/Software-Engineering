#pragma once
#include "Item.h"
class HealthCollectible :
    public Item
{
public:
    HealthCollectible();
    ~HealthCollectible();

    void Initialise(Player* player);

    void CheckCollisions() override;
};

