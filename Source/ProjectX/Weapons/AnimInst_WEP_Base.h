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
	
public:
    UAnimInst_WEP_Base();

    void NativeBeginPlay() override;
    void NativeUpdateAnimation(float DeltaSeconds) override;

private:
    class AWeaponBase* Weapon;
    class IIWeapon* WeaponItf;

private:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Projx | Weapon", meta = (AllowPrivateAccess = true))
	bool bRunning;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Projx | Weapon", meta = (AllowPrivateAccess = true))
	bool bAiming;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Projx | Weapon", meta = (AllowPrivateAccess = true))
	float BlendTimeRunIn;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Projx | Weapon", meta = (AllowPrivateAccess = true))
	float BlendTimeRunOut;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Projx | Weapon", meta = (AllowPrivateAccess = true))
	bool bEmpty;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Projx | Weapon", meta = (AllowPrivateAccess = true))
	UAnimSequenceBase* EmptyAmmoPose;
};
