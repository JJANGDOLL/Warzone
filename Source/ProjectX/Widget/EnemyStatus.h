// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "EnemyStatus.generated.h"

class UProgressBar;

UCLASS()
class PROJECTX_API UEnemyStatus : public UUserWidget
{
	GENERATED_BODY()
	
public:
	void SetHealth(float MaxHealth, float CurHealth);

    UPROPERTY(EditAnywhere, meta = (BindWidget))
	UProgressBar* HealthBar;
};
