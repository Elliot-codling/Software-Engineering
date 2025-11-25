// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CPP_TargetBase.generated.h"

UCLASS()
class CPP_PROJECT_API ACPP_TargetBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACPP_TargetBase();

	UFUNCTION(BlueprintNativeEvent, Category="Combat")
	void TakeExplosionDmg(float dmgAmount);

	virtual void TakeExplosionDmg_Implementation(float dmgAmount);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnyWhere, BlueprintReadOnly, Category="Combat")
	float health = 100.f;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	

};
