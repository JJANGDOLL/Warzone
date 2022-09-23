// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Core/WeaponBase.h"
#include "Shotgun_01.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTX_API AShotgun_01 : public AWeaponBase
{
	GENERATED_BODY()
	
public:
	AShotgun_01();
    virtual void SetWeaponName() override;

};
