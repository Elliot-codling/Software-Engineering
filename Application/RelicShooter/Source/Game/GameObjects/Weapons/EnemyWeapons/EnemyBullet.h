#pragma once
#include "../Bullet.h"

class Player;
class EnemyBullet : public Bullet
{
public:
	EnemyBullet() = default;
	~EnemyBullet() override = default;

public:
	void Initialise(BulletTypes::Type bulletType, Player* player, TileMap* collisionMap);
	void Update() override;

private:
	void CheckPlayerCollisions();

private:
	Player* m_player = nullptr;

	// Damage value based on the bullet type
	int m_damageValue[BulletTypes::TYPE_MAX] =
	{
		15,			// Blue
		10			// Red
	};
};

