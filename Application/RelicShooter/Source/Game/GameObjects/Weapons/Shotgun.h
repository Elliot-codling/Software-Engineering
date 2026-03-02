#pragma once
#include "BaseWeapon.h"

class Shotgun : public BaseWeapon
{
public:
	Shotgun() = default;
	~Shotgun() override = default;

public:
	void Initialise() override;
	
protected:
	void CreateNewBullet() override;
	
private:
	const size_t m_bulletsPerRound = 3;
	const float m_bulletSpread = 15.f;		// In degrees
};

