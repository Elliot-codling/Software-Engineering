#pragma once
#include "BaseWeapon.h"

class Rifle : public BaseWeapon
{
public:
	Rifle() = default;
	~Rifle() override = default;

public:
	void Initialise() override;
};

