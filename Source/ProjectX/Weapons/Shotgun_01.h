// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Core/Interfaces/IMainWeapon.h"
#include "Core/WeaponBoltActionBase.h"
#include "Shotgun_01.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTX_API AShotgun_01 : public AWeaponBoltActionBase, public IIMainWeapon
{
	GENERATED_BODY()
	
public:
	AShotgun_01();


	void SetWeaponName() override;
	EAmmoType GetWeaponAmmoType();

	void SpawnBullet() override;

};
