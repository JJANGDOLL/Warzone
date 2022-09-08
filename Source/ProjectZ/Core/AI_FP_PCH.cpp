// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/AI_FP_PCH.h"
#include "GameFramework/Character.h"
#include "Kismet/KismetMathLibrary.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Math/UnrealMathUtility.h"
#include "Camera/CameraComponent.h"
#include "Components/SceneComponent.h"

void UAI_FP_PCH::NativeBeginPlay()
{
    Super::NativeBeginPlay();

    Character = Cast<ACharacter>(TryGetPawnOwner());

    if (!Character)
        return;

    CharItf = Cast<IICharacter>(Character);

//     WeaponItf = Cast<IIWeapon>();
}

void UAI_FP_PCH::NativeUpdateAnimation(float DeltaSeconds)
{
    Super::NativeUpdateAnimation(DeltaSeconds);
    if (!Character)
        return;

    if (!CharItf)
        return;

    Equipped_Item = CharItf->GetEquippedItem();

    FieldOfView();

    WeaponItf = Cast<IIWeapon>(Equipped_Item);

    UpdateValues();
    CalculateMappedSpeed();
    GetInputLook();
    UpdateValuesPitch();
    GetInputMovement();
}

void UAI_FP_PCH::FieldOfView()
{
    FieldOfViewStanding = CharItf->GetFieldOfView();

    FieldOfViewAiming = SettingsScope.MultiplierFieldOfView * FieldOfViewStanding;

    FieldOfViewRunning = CharItf->GetFieldOfViewRunning();
}

void UAI_FP_PCH::UpdateValues()
{
    FVector invVec = UKismetMathLibrary::InverseTransformDirection(Character->GetTransform(), Character->GetCharacterMovement()->Velocity);
    FVector invRVec = FVector(invVec.X, invVec.Y, 0.f);

    Velocity = invRVec;

    bAiming = CharItf->IsAiming() && !bAiming;

    bCrouching = Character->GetCharacterMovement()->IsCrouching();

    bRunning = CharItf->IsRunning();

    bFalling = Character->GetCharacterMovement()->IsFalling();

    SettingsAnimation = WeaponItf->GetSettingsAnimation();

    StaticMeshWeaponBody = WeaponItf->GetStaticMeshBody();

    DataTableAnimationPoses = WeaponItf->GetCharacterAnimationPoses();

    SettingsScope = WeaponItf->GetSettingsScope();

    SettingsMovement = WeaponItf->GetCharacterSettingsMovement();
    
    AimBlendTime = GetAimBlendTime();

    AlphaWalking = GetAlphaWalking();

    PlayRateWalkingAiming = GetPlayRateWalkingAiming();

    AlphaLagMovement = GetAlphaLagMovement();

    AlphaTurning = GetAlphaTurning();

    AlphaWalkingLean = GetAlphaWalkingLean();

    PlayRateWalking = GetPlayRateWalking();

    PlayRateWalkingCrouching = GetPlayRateWalkingCrouching();

    PlayRateBrathing = GetPlayRateBreathing();

    AlphaBreathing = GetAlphaBreathing();

    PlayRateAim = GetAimPlayRate();

    PlayRateRunning = GetPlayRateRunning();
}

float UAI_FP_PCH::GetAimBlendTime()
{
    if (CharItf)
        return CharItf->GetAimDuration();
    return 0.25f;
}

float UAI_FP_PCH::GetAlphaWalking()
{
    float retVal;
    GetCurveValue(TEXT("Alpha Walking"), retVal);

    return retVal * MappedSpeed;
}

float UAI_FP_PCH::GetPlayRateWalkingAiming()
{
    float tval = bCrouching ? (SettingsMovement.Speeds.SpeedCrouch.MaxSpeed / 300.f) : (SettingsMovement.Speeds.SpeedAim.MaxSpeed / 350.f);
    return (MappedSpeed - bFalling) * tval;
}

float UAI_FP_PCH::GetAlphaLagMovement()
{
    return 1 - bFalling;
}

float UAI_FP_PCH::GetAlphaTurning()
{
    float tval;
    GetCurveValue(TEXT("Alpha Turning"), tval);
    return TurnRate * tval * AlphaLagLook;
}

float UAI_FP_PCH::GetAlphaWalkingLean()
{
    float tval;

    GetCurveValue(TEXT("Alpha Walking Lean"), tval);
    return MappedSpeed * tval;
}

float UAI_FP_PCH::GetPlayRateWalking()
{
    return (MappedSpeed - bFalling) * (SettingsMovement.Speeds.SpeedWalk.MaxSpeed / 400.f);
}

float UAI_FP_PCH::GetPlayRateWalkingCrouching()
{
    return (MappedSpeed - bFalling) * (SettingsMovement.Speeds.SpeedCrouch.MaxSpeed / 300.f);
}

float UAI_FP_PCH::GetPlayRateBreathing()
{
    return (1.f - TurnRate) * SettingsAnimation.PlayRateBreathing;
}

float UAI_FP_PCH::GetAlphaBreathing()
{
    float tval;
    GetCurveValue(TEXT("Alpha Breathing"), tval);

    return tval - MappedSpeed;
}

float UAI_FP_PCH::GetAimPlayRate()
{
    if (CharItf)
        return CharItf->GetAimSpeedMultiplier();
    return 1.0f;
}

float UAI_FP_PCH::GetPlayRateRunning()
{
    return (MappedSpeed - bFalling) * (SettingsMovement.Speeds.SpeedRun.MaxSpeed / 700.f);
}

void UAI_FP_PCH::CalculateMappedSpeed()
{
    FVector2D tvec2d;
    tvec2d.X = Character->GetCharacterMovement()->Velocity.X;
    tvec2d.Y = Character->GetCharacterMovement()->Velocity.Y;

    MappedSpeed = FMath::Clamp<float>(tvec2d.Size() / Character->GetCharacterMovement()->GetMaxSpeed(), 0.f, 1.f);
}

void UAI_FP_PCH::GetInputLook()
{
    if (!CharItf)
        return;

    CharacterInputLook = CharItf->GetInputLook();

    TurnRate = FMath::Abs(CharacterInputLook.X) - MappedSpeed;
}

void UAI_FP_PCH::UpdateValuesPitch()
{
    if (CharItf)
        return;
    FRotator trotval;
    trotval = CharItf->GetCameraComponent()->GetComponentRotation();

    CameraPitchAcceleration = FMath::Clamp(PreviousPitch - trotval.Pitch, 0.f, 1.f);

    PreviousPitch = trotval.Pitch;

    FRotator rot = UKismetMathLibrary::NormalizedDeltaRotator(Character->GetControlRotation(), Character->GetActorRotation());
    Pitch = rot.Pitch * -0.1f;
}

void UAI_FP_PCH::GetInputMovement()
{
    CharacterInputMovement = CharItf->GetInputMovement();

    CharacterInputMovementSmooth = UKismetMathLibrary::Vector2DInterpTo(CharacterInputMovementSmooth, CharacterInputMovement, GetWorld()->GetDeltaSeconds(), SettingsAnimation.LagMovementInterpSpeed);


}

void UAI_FP_PCH::CalculateLagValues()
{
    ClampedYawInput = FMath::Clamp(CharacterInputLook.X, -1.f, 1.f);

    ClampedMovementInuptHorizontal = FMath::Clamp(CharacterInputMovementSmooth.X, -1.f, 1.f);

    ClampedMovementInputVertical = FMath::Clamp(CharacterInputMovementSmooth.Y, -1.f, 1.f);

    UpdateAimingLocationLag();
}

void UAI_FP_PCH::UpdateAimingLocationLag()
{
    FVector scopeHorzVec = SettingsScope.MultiplierLagValues.Look.Location.Horizontal;
    FVector scopeVertVec = SettingsScope.MultiplierLagValues.Look.Location.Vertical;
    FVector setanimHorzVec = SettingsAnimation.AimingLag.Look.Location.Horizontal;
    FVector setanimVertVec = SettingsAnimation.AimingLag.Look.Location.Vertical;

    AimingLocationLag = CustomVectorSpringInterp(AimingLocationLag, setanimVertVec* scopeVertVec* CameraPitchAcceleration + scopeHorzVec * setanimHorzVec * ClampedYawInput, GetWorld()->GetDeltaSeconds(), SettingsAnimation.AimingLag.SpringInterpolation, SpringStateAimingLagLocation);
}

FVector UAI_FP_PCH::CustomVectorSpringInterp(FVector Current, FVector Target, float DeltaTime, FSSPringInterpVector Data, FVectorSpringState SpringState)
{
    FSSPringInterpVector LocalData = Data;

    return UKismetMathLibrary::VectorSpringInterp(Current, Target, SpringState, LocalData.Stiffness, LocalData.CriticalDampingFactor, DeltaTime, LocalData.Mass);
}
