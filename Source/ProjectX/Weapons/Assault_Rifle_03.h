// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Core/WeaponBase.h"
#include "Core/Interfaces/IMainWeapon.h"
#include "Assault_Rifle_03.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTX_API AAssault_Rifle_03 : public AWeaponBase, public IIMainWeapon
{
	GENERATED_BODY()

	
public:
	AAssault_Rifle_03();
	EAmmoType GetWeaponAmmoType() override;

protected:
	void SetWeaponName() override;

};
