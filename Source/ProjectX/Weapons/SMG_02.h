// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Core/WeaponBase.h"
#include "Core/Interfaces/IMainWeapon.h"
#include "SMG_02.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTX_API ASMG_02 : public AWeaponBase, public IIMainWeapon
{
	GENERATED_BODY()
	
public:
	ASMG_02();

	WeaponInheritance(TEXT("SMG-02"), EAmmoType::Small);
};
