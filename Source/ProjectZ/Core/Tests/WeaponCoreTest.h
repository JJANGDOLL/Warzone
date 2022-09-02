// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Core/WeaponBase.h"
#include "Engine/EngineTypes.h"
#include "WeaponCoreTest.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTZ_API AWeaponCoreTest : public AWeaponBase
{
	GENERATED_BODY()
	


protected:
	void BeginPlay() override;

public:
	UFUNCTION(BlueprintImplementableEvent, Category = "Projz | BPImpl", meta = (AllowPrivateAccess=true))
	void TestAction();

	UFUNCTION()
	void Test();

public:
	FTimerHandle TestActionHandle;
};
