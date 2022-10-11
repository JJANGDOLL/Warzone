// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Core/WeaponBase.h"
#include "SMG_05.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTX_API ASMG_05 : public AWeaponBase, public IIMainWeapon
{
	GENERATED_BODY()

public:
	ASMG_05();

	WeaponInheritance(TEXT("SMG-05"), EAmmoType::Small);
};
