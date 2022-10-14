// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/PlayerStatus.h"
#include "Components/ProgressBar.h"

void UPlayerStatus::SetHealth(float MaxHealth, float CurHealth)
{
    HealthBar->SetPercent(CurHealth / MaxHealth);
}

void UPlayerStatus::SetEnergy(float MaxEnergy, float CurEnergy)
{
    EnergyBar->SetPercent(CurEnergy / MaxEnergy);
}
