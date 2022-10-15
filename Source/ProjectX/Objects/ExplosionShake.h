// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Camera/CameraShakeBase.h"
#include "ExplosionShake.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTX_API UExplosionShake : public UCameraShakeBase
{
	GENERATED_BODY()

public:
    UExplosionShake(const FObjectInitializer& ObjectInitializer);
};
