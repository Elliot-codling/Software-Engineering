// Fill out your copyright notice in the Description page of Project Settings.


#include "CPP_Granade.h"
#include "CPP_TargetBase.h"
#include "Kismet/GameplayStatics.h"
// Sets default values
ACPP_Granade::ACPP_Granade()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ACPP_Granade::BeginPlay()
{
	Super::BeginPlay();

	TArray<AActor*> hitActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ACPP_TargetBase::StaticClass(), hitActors);
	
	for (AActor* object : hitActors) 
	{
		ACPP_TargetBase* targetBaseRef = Cast<ACPP_TargetBase>(object);
		if (targetBaseRef) 
		{
			targetBaseRef->TakeExplosionDmg(10.f);
		}
	}
}

// Called every frame
void ACPP_Granade::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

