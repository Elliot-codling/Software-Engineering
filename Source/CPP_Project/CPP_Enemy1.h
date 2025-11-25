// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CPP_TargetBase.h"
#include "CPP_Enemy1.generated.h"

/**
 * 
 */
UCLASS()
class CPP_PROJECT_API ACPP_Enemy1 : public ACPP_TargetBase
{
	GENERATED_BODY()
public:
	ACPP_Enemy1();

	virtual void TakeExplosionDmg_Implementation(float dmgAmount) override;

	void ApplyPosion();

protected:
	UPROPERTY(VisibleAnywhere, Category = "Combat")
	bool m_isPosioned = false;
};
