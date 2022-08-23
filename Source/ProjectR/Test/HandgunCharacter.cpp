// Fill out your copyright notice in the Description page of Project Settings.


#include "Test/HandgunCharacter.h"

#include "Weapons/Handgun.h"
#include "AIController.h"
#include "Components/CapsuleComponent.h"

AHandgunCharacter::AHandgunCharacter()
    : ACharacterBase()
{
    TestWeaponClass = AHandgun::StaticClass();
}

void AHandgunCharacter::BeginPlay()
{
    Super::BeginPlay();

    GetCapsuleComponent()->SetHiddenInGame(false);

    WeaponActor = GetWorld()->SpawnActor<AWeaponBase>(TestWeaponClass, FTransform::FTransform());
    WeaponActor->SetOwner(this);
    WeaponActor->SetInstigator(this);
    WeaponActor->AttachToComponent(MeshArms, FAttachmentTransformRules(EAttachmentRule::SnapToTarget, EAttachmentRule::SnapToTarget, EAttachmentRule::SnapToTarget, true),TEXT("SOCKET_Weapon"));
    

    AAIController* aiController = GetWorld()->SpawnActor<AAIController>(AAIController::StaticClass(), FTransform::FTransform());
    aiController->Possess(this);
}
