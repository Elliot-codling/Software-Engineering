// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerHUDWidget.h"
#include "Components/ProgressBar.h"

void UPlayerHUDWidget::UpdateHealth(float CurrentHealth, float MaxHealth)
{
	if (HealthProgressBar) {
		float HealthPercent = (MaxHealth > 0) ? (CurrentHealth / MaxHealth) : 0.f;
		HealthProgressBar->SetPercent(HealthPercent);
	}
}
