// Fill out your copyright notice in the Description page of Project Settings.


#include "CPP_TargetBase.h"

// Sets default values
ACPP_TargetBase::ACPP_TargetBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}



void ACPP_TargetBase::TakeExplosionDmg_Implementation(float dmgAmount)
{
	health -= dmgAmount;
	UE_LOG(LogTemp, Warning, TEXT("Target: %s took %f damage. Current health: %f"),*GetName(), dmgAmount,health)
}

// Called when the game starts or when spawned
void ACPP_TargetBase::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACPP_TargetBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

