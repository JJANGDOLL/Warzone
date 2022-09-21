// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Core/CharacterBase.h"
#include "TestCharacter.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTX_API ATestCharacter : public ACharacterBase
{
    GENERATED_BODY()

public:
    ATestCharacter();


    void Tick(float DeltaTime) override;

private:
    typedef void (ATestCharacter::*TestActFunc)(void);
    TMap<FName, TestActFunc> TestActs;

private:
    UPROPERTY(VisibleInstanceOnly, Category = "Projx | Act | Test", meta = (AllowPrivateAccess = true))
    TArray<FName> TestActFeatures;

    UPROPERTY(EditInstanceOnly, Category = "Projx | Act | Test", meta = (AllowPrivateAccess = true))
    FName TestAct;

    TestActFunc TestActFeature;
    TestActFunc TestActFeatureCore;

    UPROPERTY(EditInstanceOnly, Category = "Projx | Act | Test", meta = (AllowPrivateAccess = true))
    float TestActTerm = 2.0f;

private:
    void WalkAct();
    void MoveFeature();

private:
    void RunAct();

private:
    void AimAct();

private:
    void DoNothingAct();

protected:
    void BeginPlay() override;

protected:
    FTimerHandle TestActTimerHandle;

private:
    void ResetPosition();

private:
    FTransform startPos;
    bool isSetted = false;
};
