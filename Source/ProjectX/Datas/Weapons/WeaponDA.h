// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "WeaponsEnum.h"
#include "WeaponDA.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTX_API UWeaponDA: public UPrimaryDataAsset
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Projx | Weapon", meta=(AllowPrivateAccess=true))
	EWeaponTypes WeaponType;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Projx | Mesh", meta=(AllowPrivateAccess=true))
    class USkeletalMesh* WeaponBody;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Projx | Mesh", meta=(AllowPrivateAccess=true))
    class UStaticMesh* WeaponMagazine;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Projx | Mesh", meta = (AllowPrivateAccess = true))
    class UStaticMesh* WeaponIronSight;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Projx | Animation", meta = (AllowPrivateAccess = true))
    TSubclassOf<class UAnimInstance> WeaponABP;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Projx | Animation", meta = (AllowPrivateAccess = true))
    class UAnimMontage* MontageReload;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Projx | Animation", meta = (AllowPrivateAccess = true))
    class UAnimMontage* MontageReloadEmpty;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Projx | Animation", meta = (AllowPrivateAccess = true))
    class UAnimMontage* MontageFire;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Projx | Animation", meta = (AllowPrivateAccess = true))
    class UAnimSequenceBase* EmptyAmmoPose;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Projx | Weapon", meta = (AllowPrivateAccess = true))
    TSubclassOf<class ACasingBase> CaseClass;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Projx | Weapon", meta = (AllowPrivateAccess = true))
    float CasingImpulseStrength;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Projx | Weapon", meta = (AllowPrivateAccess = true))
    TSubclassOf<class ABulletBase> BulletClass;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Projx | Weapon", meta = (AllowPrivateAccess = true))
    class UParticleSystem* Flame;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Projx | Pose", meta = (AllowPrivateAccess = true))
    class UWeaponPoseDA* PosesDA;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Projx | Pose", meta = (AllowPrivateAccess = true))
    FTransform AimOffset;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Projx | Weapon", meta = (AllowPrivateAccess = true))
    uint8 MaxAmmo;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Projx | Weapon", meta = (AllowPrivateAccess = true))
    uint8 CurAmmo;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Projx | Weapon", meta = (AllowPrivateAccess = true))
    TArray<EFireType> SupportFireType;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Projx | Weapon", meta = (AllowPrivateAccess = true))
    float FireInterval = 1.f;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Projx | Weapon", meta = (AllowPrivateAccess = true))
    class USoundCue* FireSound;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Projx | Weapon", meta = (AllowPrivateAccess = true))
    class USoundCue* ReloadSound;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Projx | Weapon", meta = (AllowPrivateAccess = true))
    class USoundCue* ReloadEmptySound;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Projx | Weapon", meta = (AllowPrivateAccess = true))
    class UTexture2D* WeaponBodyImage;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Projx | Weapon", meta = (AllowPrivateAccess = true))
    float FireIntensity = 25000.f;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Projx | Weapon", meta = (AllowPrivateAccess = true))
    FVector2D RecoilIntensity = FVector2D(0.05f, 0.05f);

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Projx | Weapon", meta = (AllowPrivateAccess = true))
    float BulletPower = 1.f;
};
