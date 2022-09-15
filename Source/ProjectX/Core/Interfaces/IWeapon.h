// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
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
};