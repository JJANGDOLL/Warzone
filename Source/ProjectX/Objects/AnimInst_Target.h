// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "AnimInst_Target.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTX_API UAnimInst_Target : public UAnimInstance
{
	GENERATED_BODY()
	
public:
	UAnimInst_Target();

	class ATarget* Target;

	void NativeBeginPlay() override;
	void NativeUpdateAnimation(float DeltaSeconds) override;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Projx | Target", meta = (AllowPrivateAccess = true))
	bool bDown;
};
