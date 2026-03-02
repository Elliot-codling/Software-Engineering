#include "ItemFactory.h"

#include "../Collectables/AmmoCollectible.h"
#include "../Collectables/HealthCollectible.h"
#include "../Collectables/SpeedCollectible.h"

Item* ItemFactory::MakeItem(int type, Player* player)
{
	Item* newItem = new Item();

	 switch (type)
	{
	 case AMMO:
		 newItem = CreateAmmo(player);
		break;
	 case HEALTH:
		 newItem = CreateHealth(player);
		break;
	 case SPEED:
		 newItem = CreateSpeed(player);
		break;
	 default:
		 break;
	}

	 return newItem;
}

Item* ItemFactory::CreateAmmo(Player* player)
{
	AmmoCollectible* ammo = new AmmoCollectible();
	ammo->Initialise(player);
	return ammo;
}

Item* ItemFactory::CreateHealth(Player* player)
{
	HealthCollectible* health = new HealthCollectible();
	health->Initialise(player);
	return health;
}

Item* ItemFactory::CreateSpeed(Player* player)
{
	SpeedCollectible* speed = new SpeedCollectible();
	speed->Initialise(player);
	return speed;
}
