// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Core/WeaponBase.h"
#include "Handgun.generated.h"

/**
 * 
 */
class USceneComponent;

UCLASS()
class PROJECTR_API AHandgun final : public AWeaponBase
{
	GENERATED_BODY()
	
private:
	AHandgun();

	void BeginPlay() override;

};
