// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Core/CharacterBase.h"
#include "HandgunCharacter.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTR_API AHandgunCharacter : public ACharacterBase
{
	GENERATED_BODY()

	AHandgunCharacter();
	
public:
    TSubclassOf<class AWeaponBase> TestWeaponClass;

protected:
	void BeginPlay() override;
};
