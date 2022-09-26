// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Core/WeaponBase.h"
#include "Assault_Rifle_02.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTX_API AAssault_Rifle_02 : public AWeaponBase
{
	GENERATED_BODY()
	
public:
	AAssault_Rifle_02();

	virtual void SetWeaponName() override;

	EAmmoType GetWeaponAmmoType() override;

};
