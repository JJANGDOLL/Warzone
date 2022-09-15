// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "AnimInst_CharacterBase.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTX_API UAnimInst_CharacterBase : public UAnimInstance
{
	GENERATED_BODY()
	
public:
	void NativeBeginPlay() override;
	void NativeUpdateAnimation(float DeltaSeconds) override;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Projx | AnimSeq", meta = (AllowPrivateAccess = true))
	UAnimSequence* PoseIdle;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Projx | AnimSeq", meta = (AllowPrivateAccess = true))
    UAnimSequence* PoseAim;

private:
	class ACharacter* Character;
	class IICharacter* CharItf;
	class IIWeapon* WeaponItf;
};
