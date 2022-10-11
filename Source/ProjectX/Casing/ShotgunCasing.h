// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Core/CasingBase.h"
#include "ShotgunCasing.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTX_API AShotgunCasing : public ACasingBase
{
	GENERATED_BODY()
	
public:
	AShotgunCasing();

	void ApplyImpulse(FVector Direction, const FVector Strength) override;
};
