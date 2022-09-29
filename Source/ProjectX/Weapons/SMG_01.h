// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Core/WeaponBase.h"
#include "Core/Interfaces/IMainWeapon.h"
#include "SMG_01.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTX_API ASMG_01 : public AWeaponBase, public IIMainWeapon
{
	GENERATED_BODY()
	
public:
	ASMG_01();

	EAmmoType GetWeaponAmmoType() override;

protected:
	void SetWeaponName() override;

};
