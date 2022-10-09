// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "AnimNotify_AddAmmoBoltAction.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTX_API UAnimNotify_AddAmmoBoltAction : public UAnimNotify
{
	GENERATED_BODY()
	
	
private:
	FString GetNotifyName_Implementation() const;
	void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) override;

};
