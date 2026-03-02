#pragma once
#include "EnemyBaseWeapon.h"

class EnemyShotgun : public EnemyBaseWeapon
{
public:
	EnemyShotgun() = default;
	~EnemyShotgun() = default;

public:
	void Initialise() override;

protected:
	void CreateNewBullet() override;

private:
	const size_t m_bulletsPerRound = 3;
	const float m_bulletSpread = 15.f;		// In degrees
};

