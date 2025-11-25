// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PlayerHUDWidget.generated.h"

/**
 * 
 */
class UProgressBar;

UCLASS()
class MYPROJECT_API UPlayerHUDWidget : public UUserWidget
{
	GENERATED_BODY()
	
	public:
		UFUNCTION()
		void UpdateHealth(float CurrentHealth, float MaxHealth);

    protected:
		UPROPERTY(meta = (BindWidget))
		UProgressBar* HealthProgressBar;
};
