// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/TestCharacter.h"
#include "AIController.h"
#include "Utilities/Global.h"

#define AddFeat(Feature, Name, Method) \
FName Feature = FName(Name); \
TestActs.Add(Feature, &Method); \
TestActFeatures.Add(Name); \


ATestCharacter::ATestCharacter()
{
    FName idleFeat = TEXT("Idle");
    TestActs.Add(idleFeat , &ATestCharacter::DoNothingAct);
    TestActFeatures.Add(idleFeat);

    AddFeat(Walk, "Walk", ATestCharacter::WalkAct);
    AddFeat(Run, "Run", ATestCharacter::RunAct);
    AddFeat(Aim, "Aim", ATestCharacter::AimAct);

//     FName walkFeat = TEXT("Walk");
//     TestActs.Add(walkFeat, &ATestCharacter::WalkAct);
//     TestActFeatures.Add(walkFeat);
}

void ATestCharacter::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    if (TestActFeatureCore)
        (this->*(TestActFeatureCore))();
}

void ATestCharacter::WalkAct()
{
    if(!TestActFeatureCore)
        TestActFeatureCore = &ATestCharacter::MoveFeature;

    ResetPosition();
}

void ATestCharacter::MoveFeature()
{
    MoveForward(1.f);
}

void ATestCharacter::RunAct()
{
    if (!TestActFeatureCore)
    {
        Running();
        TestActFeatureCore = &ATestCharacter::MoveFeature;
    }

    ResetPosition();
}

void ATestCharacter::AimAct()
{
    if (!TestActFeatureCore)
    {
        Aiming();
        TestActFeatureCore = &ATestCharacter::MoveFeature;
    }

    ResetPosition();
}

void ATestCharacter::DoNothingAct()
{
}

void ATestCharacter::BeginPlay()
{
    Super::BeginPlay();

    AAIController* controller = GetWorld()->SpawnActor<AAIController>(AAIController::StaticClass(), GetActorTransform());

    PossessedBy(controller);

    if(TestActs.Contains(TestAct))
        TestActFeature = TestActs[TestAct];

    if (TestActFeature)
        GetWorldTimerManager().SetTimer(TestActTimerHandle, this, TestActFeature, TestActTerm, true, 2.0f);
}

void ATestCharacter::ResetPosition()
{
    if (!isSetted)
    {
        startPos = GetActorTransform();
        isSetted = true;
    }

    SetActorTransform(startPos);
}
