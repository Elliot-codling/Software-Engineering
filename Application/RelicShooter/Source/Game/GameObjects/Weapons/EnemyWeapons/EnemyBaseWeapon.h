#pragma once
#include "../BaseWeapon.h"


class Player;

class EnemyBaseWeapon : public BaseWeapon
{
public:
	EnemyBaseWeapon() = default;
	~EnemyBaseWeapon() = default;

public:
	void DefinePlayer(Player* player);
	void Fire() override;

protected:
	Player* m_player = nullptr;

private:
	void CreateNewBullet() override;

private:
	std::chrono::time_point<std::chrono::system_clock> m_timeSinceLastFire;

};

