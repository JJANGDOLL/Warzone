// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "WeaponsEnum.h"
#include "WeaponPoseDA.generated.h"

/**
 * 
 */
class UAnimSequence;

UCLASS()
class PROJECTX_API UWeaponPoseDA : public UPrimaryDataAsset
{
	GENERATED_BODY()
	
public:
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Projx | Weapon", meta = (AllowPrivateAccess = true));
    EWeaponTypes WeaponType;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Projx | Weapon", meta = (AllowPrivateAccess = true));
    UAnimSequence* Idle;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Projx | Weapon", meta = (AllowPrivateAccess = true));
    UAnimSequence* Aim;
};
