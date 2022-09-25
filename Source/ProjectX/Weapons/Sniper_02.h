// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Core/WeaponBase.h"
#include "Sniper_02.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTX_API ASniper_02 : public AWeaponBase
{
	GENERATED_BODY()
	
public:
	ASniper_02();


protected:
	void SetWeaponName() override;

};
