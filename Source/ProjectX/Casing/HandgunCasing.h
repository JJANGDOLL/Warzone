// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Core/CasingBase.h"
#include "HandgunCasing.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTX_API AHandgunCasing : public ACasingBase
{
	GENERATED_BODY()
	
public:
	AHandgunCasing();
	void ApplyImpulse(FVector Direction, const FVector Strength) override;
};
