// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Core/WeaponBase.h"
#include "Sniper_03.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTX_API ASniper_03 : public AWeaponBase, public IIMainWeapon
{
	GENERATED_BODY()

public:
	ASniper_03();


	EAmmoType GetWeaponAmmoType() override;

protected:
	void SetWeaponName() override;

};
