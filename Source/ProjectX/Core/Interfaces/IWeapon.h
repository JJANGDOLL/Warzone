// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Datas/Weapons/WeaponsEnum.h"
#include "IWeapon.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UIWeapon : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class PROJECTX_API IIWeapon
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	virtual class USkeletalMeshComponent* GetWeaponBodyMesh() = 0;
	virtual class UStaticMeshComponent* GetWeaponMagazineMesh() = 0;
	virtual class UStaticMeshComponent* GetWeaponIronSightMesh() = 0;

	virtual void Reload() = 0;
	virtual void Fire() = 0;
	virtual void EjectCasing() = 0;
	virtual void SpawnBullet() = 0;
	virtual void SpawnFlame() = 0;

	virtual FVector GetWeaponForward() = 0;

	virtual class UWeaponPoseDA* GetPosesDA() = 0;
    virtual FTransform GetAimOffset() = 0;

	virtual UAnimSequenceBase* GetEmptyPose() = 0;
	virtual bool IsEmpty() = 0;

	virtual int8 GetMaxAmmo() = 0;
    virtual int8 GetCurAmmo() = 0;
	virtual EFireType GetFireType() = 0;
	virtual float GetFireInterval() = 0;
	virtual bool IsReloading() = 0;
	virtual FVector2D GetRecoilIntensity() = 0;

	virtual class UTexture2D* GetWeaponBodyImage() = 0;
    virtual class UTexture2D* GetWeaponMagazineImage() = 0;
    virtual class UTexture2D* GetWeaponScopeImage() = 0;

	virtual EAmmoType GetWeaponAmmoType() = 0;

	virtual TSubclassOf<class UCrosshair> GetCrosshairClass() = 0;

	virtual bool IsBoltAction() = 0;
	virtual void BoltActionReload() = 0;
	virtual void AddOneAmmo() = 0;
};
