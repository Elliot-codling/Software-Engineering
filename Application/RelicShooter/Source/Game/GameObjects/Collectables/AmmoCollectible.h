#pragma once
#include "Item.h"
class AmmoCollectible :
    public Item
{
public:
    AmmoCollectible();
    ~AmmoCollectible();
#
    void Initialise(Player* player);

    void CheckCollisions() override;
};

