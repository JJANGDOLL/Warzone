// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/EnemyStatus.h"
#include "Components/ProgressBar.h"
#include "Utilities/Global.h"

void UEnemyStatus::SetHealth(float MaxHealth, float CurHealth)
{
    if (HealthBar)
    {
        HealthBar->SetPercent(CurHealth / MaxHealth);
    }
}
