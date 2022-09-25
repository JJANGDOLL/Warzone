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
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Projx | Weapon", meta = (AllowPrivateAccess = true))
    EWeaponTypes WeaponType;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Projx | Weapon", meta = (AllowPrivateAccess = true))
    UAnimSequenceBase* Idle;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Projx | Weapon", meta = (AllowPrivateAccess = true))
    UAnimSequenceBase* Aim;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Projx | Weapon", meta = (AllowPrivateAccess = true))
    UAnimSequenceBase* Fire;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Projx | Weapon", meta = (AllowPrivateAccess = true))
    UAnimSequenceBase* AimFire;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Projx | Weapon", meta = (AllowPrivateAccess = true))
    UAnimSequenceBase* Reload;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Projx | Weapon", meta = (AllowPrivateAccess = true))
    UAnimSequenceBase* ReloadEmpty;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Projx | Weapon", meta = (AllowPrivateAccess = true))
    UAnimSequenceBase* AimReload;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Projx | Weapon", meta = (AllowPrivateAccess = true))
    UAnimSequenceBase* AimReloadEmpty;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Projx | Weapon", meta = (AllowPrivateAccess = true))
    UAnimSequenceBase* Running;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Projx | Weapon", meta = (AllowPrivateAccess = true))
    UAnimSequenceBase* Holster;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Projx | Weapon", meta = (AllowPrivateAccess = true))
    UAnimSequenceBase* Unholster;
};
