// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "AnimNotify_Holster.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTX_API UAnimNotify_Holster : public UAnimNotify
{
	GENERATED_BODY()
	
public:
    FString GetNotifyName_Implementation() const override;
    void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) override;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Projx", meta = (AllowPrivateAccess = true))
    bool bUnholster;
};
