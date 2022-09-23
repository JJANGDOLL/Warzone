// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Core/WeaponBase.h"
#include "Assault_Rifle_01.generated.h"

UCLASS()
class PROJECTX_API AAssault_Rifle_01 : public AWeaponBase
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AAssault_Rifle_01();

    void SetWeaponName() override;

};
