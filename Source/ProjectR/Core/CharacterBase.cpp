// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/CharacterBase.h"
#include "Utilities/Global.h"

#include "LevelSequence.h"
#include "MovieSceneSequencePlayer.h"
#include "LevelSequenceActor.h"
#include "LevelSequencePlayer.h"
#include "GameFramework/PlayerInput.h"
#include "GameFramework/Character.h"

#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Engine/LatentActionManager.h"

#include "Sound/SoundBase.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/CapsuleComponent.h"
#include "Engine/SkeletalMesh.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Animation/AnimInstance.h"
#include "Core/WeaponBase.h"
#include "Weapons/Handgun.h"

// Sets default values
ACharacterBase::ACharacterBase()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

    GetCapsuleComponent()->InitCapsuleSize(35.f, 92.f);
    GetCapsuleComponent()->SetAllMassScale(100.f);

    Helpers::GetAsset(&jumpSoundQue, "SoundCue'/Game/Audio/SC_Jump_Start.SC_Jump_Start'");

    UCharacterMovementComponent* const movementComp = GetCharacterMovement();
    movementComp->GravityScale = 1.5f;
    movementComp->MaxAcceleration = 3000.f;
    movementComp->BrakingFrictionFactor = 2.0f;
    movementComp->BrakingFriction = 1.0f;
    movementComp->CrouchedHalfHeight = 54.0f;
    movementComp->bUseSeparateBrakingFriction = true;
    movementComp->Mass = 400.0f;

    movementComp->MaxStepHeight = 25.0f;
    movementComp->SetWalkableFloorAngle(45.0f);
    movementComp->GroundFriction = 10.0f;
    movementComp->MaxWalkSpeed = 400.0f;
    movementComp->bCanWalkOffLedgesWhenCrouching = true;

    movementComp->JumpZVelocity = 300.f;
    movementComp->AirControl = 0.35f;

    movementComp->GetNavAgentPropertiesRef().bCanCrouch = true;

    movementComp->StandingDownwardForceScale = 0.f;

    JumpMaxHoldTime = 0.15f;


    // ----------------------------------------

    Helpers::CreateComponent(this, &SpringArm, TEXT("SpringArm"), GetMesh());
    SpringArm->TargetArmLength = 0.f;
    SpringArm->bDoCollisionTest = false;

    Helpers::CreateComponent(this, &CameraComp, TEXT("MainCamera"), SpringArm);
    CameraComp->bUsePawnControlRotation = true;
    CameraComp->SetFieldOfView(90.f);

    Helpers::CreateComponent(this, &MeshArms, TEXT("Mesh Arms"), CameraComp);
    MeshArms->SetRelativeLocation(FVector(0.f, 0.f, -165.f));
    MeshArms->AddRelativeRotation(FRotator(0.f ,-90.f, 0.f));

    USkeletalMesh* skelArmMesh;
    Helpers::GetAsset(&skelArmMesh, TEXT("SkeletalMesh'/Game/AnimatedLowPolyWeapons/Demo/Art/Characters/Mannequin/SK_Mannequin_Arms.SK_Mannequin_Arms'"));
    MeshArms->SetSkeletalMesh(skelArmMesh);

    //---------------------------------------

    TSubclassOf<UAnimInstance> animInst;
    Helpers::GetClass(&animInst, TEXT("AnimBlueprint'/Game/Animation/ABP_FP_Arms.ABP_FP_Arms_C'"));
    MeshArms->SetAnimInstanceClass(animInst);

    // --------------------------------------------

    Helpers::GetAsset(&MontageFire, TEXT("AnimMontage'/Game/AnimatedLowPolyWeapons/Art/Characters/Animations/Handguns/AM_FP_PCH_Handgun_Fire.AM_FP_PCH_Handgun_Fire'"));

}

bool ACharacterBase::IsAiming()
{
    return bAiming;
}

bool ACharacterBase::IsRunning()
{
    return bRunning;
}

bool ACharacterBase::CanAim()
{
    return true;
}

bool ACharacterBase::CanFire()
{
    return true;
}

void ACharacterBase::OnConstruction(const FTransform& Transform)
{
    SpringArm->SetRelativeLocation(GetViewLocation());
}

void ACharacterBase::Jump()
{
    if(!GetCharacterMovement()->IsFalling())
    {
        if (GetCharacterMovement()->IsCrouching())
        {
            UnCrouch();
        }
        else
        {
            Super::Jump();

            bJumping = false;
            UGameplayStatics::SpawnSound2D(GetWorld(), jumpSoundQue);
        }
    }
}

void ACharacterBase::StopJumping()
{
    Super::StopJumping();
}

// Called when the game starts or when spawned
void ACharacterBase::BeginPlay()
{
	Super::BeginPlay();
	
	ULevelSequence* fadeInSeq;
	Helpers::GetAssetDynamic<ULevelSequence>(&fadeInSeq, "LevelSequence'/Game/Sequences/FadeIn_Level.FadeIn_Level'");
	FMovieSceneSequencePlaybackSettings fmovieSeqSet;
	ALevelSequenceActor* outActor;
	ULevelSequencePlayer* levelSeqPlayer = ULevelSequencePlayer::CreateLevelSequencePlayer(GetWorld(), fadeInSeq, FMovieSceneSequencePlaybackSettings::FMovieSceneSequencePlaybackSettings(), outActor);
	levelSeqPlayer->Play();

    verifyf(CameraComp, L"Camera component null")

    Logger::Log(CameraComp);
}

// Called every frame
void ACharacterBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

    SpringArm->SetRelativeLocation(FMath::VInterpTo(SpringArm->GetRelativeLocation(), GetViewLocation(), GetWorld()->GetDeltaSeconds(), 15.0f));

    CameraComp->SetFieldOfView(MeshArms->GetAnimInstance()->GetCurveValue(TEXT("Field Of View")));



    // Run
    if (bHoldingKeyRun && CanRun())
    {
        if (!bRunning)
        {
            bRunning = true;
            GetCharacterMovement()->MaxWalkSpeed = SpeedRunning;
        }
    }
    else
    {
        if (bRunning)
        {
            bRunning = false;
            GetCharacterMovement()->MaxWalkSpeed = SpeedWalking;
        }
    }

    if (bDebug)
    {
        Logger::Log(bHoldingKeyFire);
        Logger::Log(WeaponActor);
    }

    if(bHoldingKeyFire && WeaponActor && WeaponActor->IsAutomatic())
    {
        if(CanFire())
        {
            PlayFireMontage();


        }
    }
    else if(bHoldingKeyFire && WeaponActor && !WeaponActor->IsAutomatic())
    {
        if(CanFire())
        {
            if(GetGameTimeSinceCreation() - LastFireTime > 60.0 / WeaponActor->GetRateOfFire())
            {
                PlayFireMontage();
                LastFireTime = GetGameTimeSinceCreation();
            }
        }
    }
}


void ACharacterBase::MoveForward(float AxisValue)
{
    AddMovementInput(GetActorForwardVector(), AxisValue);
}

void ACharacterBase::MoveRight(float AxisValue)
{
    AddMovementInput(GetActorRightVector(), AxisValue);
}


void ACharacterBase::PressRun()
{
    bHoldingKeyRun = true;

//     if (bHoldingKeyRun)
//     {
//         if (CanRun())
//         {
//             if (!bRunning)
//             {
//                 bRunning = true;
// 
// //                 GetCharacterMovement()->MaxWalkSpeed = SpeedRunning;
//             }
//         }
//         else
//         {
//             if (bRunning)
//             {
//                 bRunning = false;
// 
//                 GetCharacterMovement()->MaxWalkSpeed = SpeedWalking;
//             }
//         }
// 
// 
//         PrintLine();
//     }
}

void ACharacterBase::ReleaseRun()
{
    bHoldingKeyRun = false;

    if(bRunning)
    {
        bRunning = false;

    }

//     if (bRunning)
//     {
//         bRunning = false;
// 
//         GetCharacterMovement()->MaxWalkSpeed = SpeedWalking;
//     }
}

// Called to bind functionality to input
void ACharacterBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

    PlayerInputComponent->BindAxis("Forward", this, &ACharacterBase::MoveForward);
    PlayerInputComponent->BindAxis("Back", this, &ACharacterBase::MoveForward);
    PlayerInputComponent->BindAxis("Left", this, &ACharacterBase::MoveRight);
    PlayerInputComponent->BindAxis("Right", this, &ACharacterBase::MoveRight);

    PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacterBase::Jump);
    PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacterBase::StopJumping);

    PlayerInputComponent->BindAction("Run", IE_Pressed, this, &ACharacterBase::PressRun);
//     PlayerInputComponent->BindAction("Run", IE_Repeat, this, &ACharacterBase::DoRun);
    PlayerInputComponent->BindAction("Run", IE_Released, this, &ACharacterBase::ReleaseRun);

    PlayerInputComponent->BindAction("Crouch", IE_Pressed, this, &ACharacterBase::ToggleCrouch);
    PlayerInputComponent->BindAction("Crouch", IE_Released, this, &ACharacterBase::ToggleCrouch);

    PlayerInputComponent->BindAction("Aim", IE_Pressed, this, &ACharacterBase::ToggleAim);
    PlayerInputComponent->BindAction("Aim", IE_Released, this, &ACharacterBase::ToggleAim);
    
    PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &ACharacterBase::PressFire);
    PlayerInputComponent->BindAction("Fire", IE_Released, this, &ACharacterBase::ReleaseFire);


    PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
    PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);



    FInputAxisKeyMapping forwardKey("Forward", EKeys::W, 1.f);
    FInputAxisKeyMapping backKey("Back", EKeys::S, -1.f);
    FInputAxisKeyMapping rightKey("Right", EKeys::D, 1.f);
    FInputAxisKeyMapping leftKey("Left", EKeys::A, -1.f);

    FInputAxisKeyMapping lookUpKey("LookUp", EKeys::MouseY, -1.f);
    FInputAxisKeyMapping turnKey("Turn", EKeys::MouseX, 1.f);

    FInputActionKeyMapping jumpKey("Jump", EKeys::SpaceBar, 0, 0, 0, 0);
    FInputActionKeyMapping runKey("Run", EKeys::LeftShift, 0, 0, 0, 0);
    FInputActionKeyMapping crouchKey("Crouch", EKeys::LeftControl, 0, 0, 0, 0);
    FInputActionKeyMapping aimKey("Aim", EKeys::RightMouseButton, 0, 0, 0, 0);
    FInputActionKeyMapping fireKey("Fire", EKeys::LeftMouseButton, 0, 0, 0, 0);

    GetWorld()->GetFirstPlayerController()->PlayerInput->AddAxisMapping(forwardKey);
    GetWorld()->GetFirstPlayerController()->PlayerInput->AddAxisMapping(backKey);
    GetWorld()->GetFirstPlayerController()->PlayerInput->AddAxisMapping(rightKey);
    GetWorld()->GetFirstPlayerController()->PlayerInput->AddAxisMapping(leftKey);

    GetWorld()->GetFirstPlayerController()->PlayerInput->AddAxisMapping(lookUpKey);
    GetWorld()->GetFirstPlayerController()->PlayerInput->AddAxisMapping(turnKey);

    GetWorld()->GetFirstPlayerController()->PlayerInput->AddActionMapping(jumpKey);
    GetWorld()->GetFirstPlayerController()->PlayerInput->AddActionMapping(runKey);
    GetWorld()->GetFirstPlayerController()->PlayerInput->AddActionMapping(crouchKey);
    GetWorld()->GetFirstPlayerController()->PlayerInput->AddActionMapping(aimKey);
    GetWorld()->GetFirstPlayerController()->PlayerInput->AddActionMapping(fireKey);
}

bool ACharacterBase::CanRun()
{
    return (!GetCharacterMovement()->IsCrouching() && !bAiming && !bPlayingMontageReloading && !bPlayingMontageInspecting);
}

void ACharacterBase::ToggleCrouch()
{
    if(GetCharacterMovement()->IsCrouching())
    {
        UnCrouch();
    }
    else
    {
        Crouch();
    }
}

FVector ACharacterBase::GetViewLocation()
{
    return FVector(ViewOffset.X, ViewOffset.Y, ViewOffset.Z + GetCapsuleComponent()->GetScaledCapsuleHalfHeight());
}

AWeaponBase* ACharacterBase::GetCurrentWeapon()
{
    return WeaponActor;
}

void ACharacterBase::ToggleAim()
{
    if(!IsAiming())
    {
        if (CanAim())
        {
            StartAiming();
        }
    }
    else
    {
        bAiming = false;
        // Soune Queue

        if(!GetCharacterMovement()->IsCrouching())
        {
            GetCharacterMovement()->MaxWalkSpeed = SpeedWalking;
        }
    }
}

void ACharacterBase::StartAiming()
{
   if(!GetCharacterMovement()->IsCrouching())
   {
       GetCharacterMovement()->MaxWalkSpeed = SpeedAiming;
   }
   bAiming = true;

   // Sound Que
}

void ACharacterBase::DoRun()
{
//     if(CanRun())
//     {
//         if(!bRunning)
//         {
//             bRunning = true;
// 
//             GetCharacterMovement()->MaxWalkSpeed = SpeedRunning;
//         }
//     }
//     else
//     {
//         if(bRunning)
//         {
//             bRunning = false;
// 
//             GetCharacterMovement()->MaxWalkSpeed = SpeedWalking;
//         }
//     }
// //     bHoldingKeyRun = true;
// //     if(bHoldingKeyRun)
// //     {
// // //         UKismetSystemLibrary::RetriggerableDelay(GetWorld(), 0.1f, FLatentActionInfo::FLatentActionInfo());
// //     }
}

void ACharacterBase::PressFire()
{
    bHoldingKeyFire = true;
}

void ACharacterBase::ReleaseFire()
{
    bHoldingKeyFire = false;
}

void ACharacterBase::PlayFireMontage()
{
    verifyf(MontageFire, L"FireMontage is null");

    MeshArms->GetAnimInstance()->Montage_Play(MontageFire);
    if(WeaponActor)
    {
        WeaponActor->OnFire();
    }
}

void ACharacterBase::NewWeapon()
{
    WeaponActor = GetWorld()->SpawnActor<AWeaponBase>(AHandgun::StaticClass(), FTransform::FTransform());
    WeaponActor->SetOwner(this);
    WeaponActor->SetInstigator(this);
    WeaponActor->AttachToComponent(MeshArms, FAttachmentTransformRules(EAttachmentRule::SnapToTarget, EAttachmentRule::SnapToTarget, EAttachmentRule::SnapToTarget, true), TEXT("SOCKET_Weapon"));
}

