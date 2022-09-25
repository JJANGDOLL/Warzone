// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "AnimInst_CharacterBase.generated.h"

/**
 * 
 */
class UAnimSequenceBase;

UCLASS()
class PROJECTX_API UAnimInst_CharacterBase : public UAnimInstance
{
	GENERATED_BODY()

	
public:

	UAnimInst_CharacterBase();

	void NativeBeginPlay() override;
	void NativeUpdateAnimation(float DeltaSeconds) override;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Projx | AnimSeq", meta = (AllowPrivateAccess = true))
	UAnimSequenceBase* PoseIdle;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Projx | AnimSeq", meta = (AllowPrivateAccess = true))
    UAnimSequenceBase* PoseAim;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Projx | State", meta = (AllowPrivateAccess = true))
    bool bAiming;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Projx | Weapon", meta = (AllowPrivateAccess = true))
    FTransform AimOffset;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Projx | State", meta = (AllowPrivateAccess = true))
    bool bRunning;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Projx | AnimSeq", meta = (AllowPrivateAccess = true))
    UAnimSequenceBase* PoseRun;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Projx | State", meta = (AllowPrivateAccess = true))
    bool bFalling;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Projx | State", meta = (AllowPrivateAccess = true))
    float Vertical;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Projx | State", meta = (AllowPrivateAccess = true))
    float Horizontal;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Projx | State", meta = (AllowPrivateAccess = true))
    bool bBreath;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Projx | State", meta = (AllowPrivateAccess = true))
    bool bHolster;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Projx | AnimSeq", meta = (AllowPrivateAccess = true))
    UAnimSequenceBase* PoseHolster;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Projx | AnimSeq", meta = (AllowPrivateAccess = true))
    UAnimSequenceBase* PoseUnholster;

private:
	class ACharacter* Character;
	class IICharacter* CharItf;
	class IIWeapon* WeaponItf;
};
