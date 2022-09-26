// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Core/CasingBase.h"
#include "SniperCasing.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTX_API ASniperCasing : public ACasingBase
{
	GENERATED_BODY()
	
public:
	ASniperCasing();
	void ApplyImpulse(FVector Direction, const FVector Strength) override;
};
