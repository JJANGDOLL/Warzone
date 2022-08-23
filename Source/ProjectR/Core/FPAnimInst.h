// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "FPAnimInst.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTR_API UFPAnimInst : public UAnimInstance
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "CProp | Status")
	bool bAiming;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "CProp | Status")
	bool bCrouching;

    UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "CProp | Status")
    bool bRunning;

	UPROPERTY(BlueprintReadOnly, VisibleDefaultsOnly, Category = "CProp | Weapon")
	class AWeaponBase* weaponBase;

	UPROPERTY(BlueprintReadOnly, VisibleDefaultsOnly, Category = "CProp | Character")
	class ACharacterBase* characterBase;

    UPROPERTY(BlueprintReadOnly, VisibleDefaultsOnly, Category = "CProp | Character")
	FVector velocity;

    UPROPERTY(BlueprintReadOnly, VisibleDefaultsOnly, Category = "CProp | Character")
	float grounded;

    UPROPERTY(BlueprintReadOnly, VisibleDefaultsOnly, Category = "CProp | Character")
	float playRateRunning;

    UPROPERTY(BlueprintReadOnly, VisibleDefaultsOnly, Category = "CProp | Character")
    float playRateMultiplierRunning;

    UPROPERTY(BlueprintReadOnly, VisibleDefaultsOnly, Category = "CProp | Character")
    float playRateIdle;

    UPROPERTY(BlueprintReadOnly, VisibleDefaultsOnly, Category = "CProp | Character")
    float playRateMultiplierIdle;

public:
	void NativeUpdateAnimation(float DeltaSeconds) override;
	void NativeBeginPlay() override;
};
