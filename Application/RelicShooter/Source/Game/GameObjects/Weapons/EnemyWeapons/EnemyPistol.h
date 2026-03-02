#pragma once
#include "EnemyBaseWeapon.h"

class EnemyPistol : public EnemyBaseWeapon
{
public:
	EnemyPistol() = default;
	~EnemyPistol() = default;

public:
	void Initialise() override;
};

