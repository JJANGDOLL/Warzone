// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "WeaponScopeDA.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTX_API UWeaponScopeDA : public UPrimaryDataAsset
{
	GENERATED_BODY()
	
public:
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Projx | Scope", meta = (AllowPrivateAccess = true))
	FTransform AimOffset;
};
