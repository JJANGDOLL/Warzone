// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Core/WeaponBase.h"
#include "Core/Interfaces/ISubWeapon.h"
#include "Handgun_02.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTX_API AHandgun_02 : public AWeaponBase, public IISubWeapon
{
	GENERATED_BODY()
	
public:
	AHandgun_02();
    virtual void SetWeaponName() override;

	EAmmoType GetWeaponAmmoType() override;

};
