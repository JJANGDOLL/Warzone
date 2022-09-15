// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "AnimInst_WEP_Base.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTX_API UAnimInst_WEP_Base : public UAnimInstance
{
	GENERATED_BODY()
	
private:
	UPROPERTY(BlueprintReadOnly, Category = "Projx | Weapon", meta = (AllowPrivateAccess = true))
	bool bRunning;

	UPROPERTY(BlueprintReadOnly, Category = "Projx | Weapon", meta = (AllowPrivateAccess = true))
	bool bAiming;

	UPROPERTY(BlueprintReadOnly, Category = "Projx | Weapon", meta = (AllowPrivateAccess = true))
	float BlendTimeRunIn;

	UPROPERTY(BlueprintReadOnly, Category = "Projx | Weapon", meta = (AllowPrivateAccess = true))
	float BlendTimeRunOut;

	UPROPERTY(BlueprintReadOnly, Category = "Projx | Weapon", meta = (AllowPrivateAccess = true))
	bool bEmpty;

	UPROPERTY(BlueprintReadOnly, Category = "Projx | Weapon", meta = (AllowPrivateAccess = true))
	UAnimSequenceBase* EmptyAmmoPose;
};
