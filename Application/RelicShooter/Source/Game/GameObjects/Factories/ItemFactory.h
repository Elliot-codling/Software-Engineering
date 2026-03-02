#pragma once
#include <type_traits>
#include "../Collectables/Item.h"

enum Collectables
{
	AMMO,
	HEALTH,
	SPEED
};

class ItemFactory : public Item
{
public:
	Item* MakeItem(int type, Player* player);
	Item* CreateAmmo(Player* player);
	Item* CreateHealth(Player* player);
	Item* CreateSpeed(Player* player);
};

