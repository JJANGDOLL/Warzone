// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Core/CasingBase.h"
#include "ARCasing.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTX_API AARCasing : public ACasingBase
{
	GENERATED_BODY()
	
public:
	AARCasing();

    void ApplyImpulse(FVector Direction, const FVector Strength) override;
};
