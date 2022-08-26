// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/FPAnimInst.h"

#include "Utilities/Global.h"
#include "Core/CharacterBase.h"
#include "Core/WeaponBase.h"
#include "GameFramework/CharacterMovementComponent.h"

void UFPAnimInst::NativeUpdateAnimation(float DeltaSeconds)
{
    Super::NativeUpdateAnimation(DeltaSeconds);

    CheckNull(characterBase);

    // Status

    bAiming = characterBase->IsAiming();

    bCrouching = characterBase->GetCharacterMovement()->IsCrouching();

    bRunning = characterBase->IsRunning();

    FVector invVec = UKismetMathLibrary::InverseTransformDirection(characterBase->GetTransform(), characterBase->GetCharacterMovement()->Velocity);
    FVector invRVec = FVector(invVec.X, invVec.Y, 0.f);

    velocity = invRVec;

    grounded = 1.f - (characterBase->GetCharacterMovement()->IsFalling() ? 1.f : 0.f);

    playRateRunning = FMath::FInterpTo(playRateRunning, grounded * playRateMultiplierRunning, GetWorld()->GetDeltaSeconds(), 10.0f);
    playRateIdle = FMath::FInterpTo(playRateIdle, grounded * playRateMultiplierIdle, GetWorld()->GetDeltaSeconds(), 10.0f);

    // Wepaon 

    if(weaponBase == nullptr)
        weaponBase = characterBase->GetCurrentWeapon();

    CheckNull(weaponBase);

    bHolstered = characterBase->IsHolstered();
}

void UFPAnimInst::NativeBeginPlay()
{
    Super::NativeBeginPlay();

    grounded = 0.f;
    playRateRunning = 0.f;
    playRateMultiplierRunning = 1.0f;
    playRateIdle = 0.f;
    playRateMultiplierIdle = 1.0f;


    characterBase = Cast<ACharacterBase>(TryGetPawnOwner());
    CheckNull(characterBase);
    Logger::Log(characterBase->GetName());
}
