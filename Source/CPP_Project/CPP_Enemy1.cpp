// Fill out your copyright notice in the Description page of Project Settings.
#include "CPP_Enemy1.h"

ACPP_Enemy1::ACPP_Enemy1()
{
	PrimaryActorTick.bCanEverTick = false;
}

void ACPP_Enemy1::TakeExplosionDmg_Implementation(float dmgAmount)
{
	health -= dmgAmount;
	UE_LOG(LogTemp, Warning, TEXT("Target: %s took %f damage. Current health: %f"), *GetName(), dmgAmount, health)
}

void ACPP_Enemy1::ApplyPosion()
{
	m_isPosioned = true;
	UE_LOG(LogTemp, Error, TEXT("Target: %s is now poisoned!"), *GetName())
}
