// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Core/Interfaces/IMainWeapon.h"
#include "Core/WeaponBoltActionBase.h"
#include "Sniper_01.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTX_API ASniper_01 : public AWeaponBoltActionBase, public IIMainWeapon
{
	GENERATED_BODY()
	
public:
	ASniper_01();
    virtual void SetWeaponName() override;

	EAmmoType GetWeaponAmmoType() override;

};
