// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Core/WeaponBase.h"
#include "WeaponBoltActionBase.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTX_API AWeaponBoltActionBase : public AWeaponBase
{
	GENERATED_BODY()
	
public:
	void Reload() override;


	void OnFireBlendOut(UAnimMontage* AnimMontage, bool bInterrupted) override;


	void Fire() override;

	void BoltAction();


	void OnReloadBlendOut(UAnimMontage* AnimMontage, bool bInterrupted) override;

	virtual bool IsBoltAction() override {
		return true;
	}

	void OnAmmoInsertBlendOut(UAnimMontage* AnimMontage, bool bInterrupted);


	void InsertBoltActionAmmo() override;


	void AddOneAmmo() override;

protected:
    FTimerHandle BoltActionTimer;

	bool bPlayingBoltActionReloading;
};
