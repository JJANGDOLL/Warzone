// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/CharacterBase.h"
#include "GameFramework/PlayerInput.h"
#include "Utilities/Global.h"
#include "Components/SkeletalMeshComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Engine/SkeletalMesh.h"
#include "Components/CapsuleComponent.h"
#include "Animation/AnimInstance.h"
#include "WeaponBase.h"
#include "Weapons/Assault_Rifle_01.h"
#include "Weapons/Handgun_01.h"
#include "Weapons/Assault_Rifle_02.h"
#include "Datas/Weapons/WeaponPoseDA.h"
#include "Animation/AnimSequenceBase.h"
#include "Animation/AnimMontage.h"
#include "Animation/AnimCompositeBase.h"
#include "GameFramework/CharacterMovementComponent.h"

#define SET_MAX_WALK_SPEED(p) GetCharacterMovement()->MaxWalkSpeed = p;

// Sets default values
ACharacterBase::ACharacterBase()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

    Helpers::CreateComponent(this, &SpringArm, TEXT("Spring Arm"), GetMesh());
    Helpers::CreateComponent(this, &SkeletalMeshArms, TEXT("Skeletal Mesh Arms"), SpringArm);
    Helpers::CreateComponent(this, &Camera, TEXT("Camera"), SkeletalMeshArms, TEXT("SOCKET_Camera"));

    USkeletalMesh* meshArms;
    Helpers::GetAsset(&meshArms, TEXT("SkeletalMesh'/Game/InfimaGames/LowPolyShooterPack/Art/Characters/Default/SK_FP_CH_Default.SK_FP_CH_Default'"));

    SkeletalMeshArms->SetSkeletalMesh(meshArms);

    SkeletalMeshArms->AddRelativeRotation(FRotator(0.f, -90.f, 0.f));

    SkeletalMeshArms->SetRelativeLocation(FVector(0.f, 0.f, -165.f));
    SpringArm->TargetArmLength = 0.f;
    SpringArm->bDoCollisionTest = false;

    TSubclassOf<UAnimInstance> armsAnimInst;
    Helpers::GetClass(&armsAnimInst, TEXT("AnimBlueprint'/Game/ProjectX/Characters/ABP_CharacterBase.ABP_CharacterBase_C'"));
    SkeletalMeshArms->SetAnimClass(armsAnimInst);
    SkeletalMeshArms->SetBoundsScale(6.f);

    TestMethods.Add(ECharacterFeature::None, &ACharacterBase::DoNothing);
    TestMethods.Add(ECharacterFeature::Aiming, &ACharacterBase::Aiming);
    TestMethods.Add(ECharacterFeature::Fire, &ACharacterBase::Fire);
    TestMethods.Add(ECharacterFeature::Reload, &ACharacterBase::Reload);
    TestMethods.Add(ECharacterFeature::ReloadEmpty, &ACharacterBase::ReloadEmpty);
    TestMethods.Add(ECharacterFeature::Running, &ACharacterBase::Running);

    TestFeature = ECharacterFeature::None;

    TestWeapon = AAssault_Rifle_01::StaticClass();

    UCharacterMovementComponent* const movementComp = GetCharacterMovement();
    movementComp->CrouchedHalfHeight = 54.f;

    movementComp->GetNavAgentPropertiesRef().bCanCrouch = true;
    movementComp->MaxWalkSpeed = 300.f;

    GetCapsuleComponent()->SetVisibility(true);
    GetCapsuleComponent()->bHiddenInGame = false;

    ViewOffset = FVector(0.f, 0.f, -25.f);
}

void ACharacterBase::OnConstruction(const FTransform& Transform)
{
    Super::OnConstruction(Transform);

    SpringArm->SetRelativeLocation(GetViewLocation());
}

// Called when the game starts or when spawned
void ACharacterBase::BeginPlay()
{
	Super::BeginPlay();
	
    if (!EquippedWeapon && TestWeapon)
    {
        EquippedWeapon = GetWorld()->SpawnActor<AWeaponBase>(TestWeapon, GetActorTransform());
        EquippedWeapon->AttachToComponent(SkeletalMeshArms, FAttachmentTransformRules::SnapToTargetIncludingScale, TEXT("SOCKET_Weapon"));
    }

    SpringArm->SetRelativeLocation(GetViewLocation());
//     SkeletalMeshArms->AddRelativeLocation(-FVector(0.f, 0.f, GetCapsuleComponent()->GetScaledCapsuleHalfHeight()));

    OnTestFeature = TestMethods[TestFeature];

    if(OnTestFeature)
        GetWorldTimerManager().SetTimer(TestTimerHandle, this, OnTestFeature, TestTerm, true, 2.0f);
}

// Called every frame
void ACharacterBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

    Helpers::DrawGizmo(GetWorld(), GetActorLocation() + GetActorForwardVector() * 250.f, FQuat(GetController()->GetControlRotation()));

    SpringArm->SetRelativeRotation(FRotator(GetControlRotation().Pitch, 0.f, 0.f));
    SetActorRelativeRotation(FRotator(0.f, GetControlRotation().Yaw, 0.f));

    SpringArm->SetRelativeLocation(FMath::VInterpTo(SpringArm->GetRelativeLocation(), GetViewLocation(), GetWorld()->GetDeltaSeconds(), 15.0f));

    Camera->SetFieldOfView(FMath::FInterpTo(Camera->FieldOfView, SkeletalMeshArms->GetAnimInstance()->GetCurveValue(TEXT("Field Of View")), GetWorld()->GetDeltaSeconds(), 10.f));
}

// Called to bind functionality to input
void ACharacterBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

    FInputAxisKeyMapping forwardKey("Forward", EKeys::W, 1.f);
    FInputAxisKeyMapping backKey("Back", EKeys::S, -1.f);
    FInputAxisKeyMapping rightKey("Right", EKeys::D, 1.f);
    FInputAxisKeyMapping leftKey("Left", EKeys::A, -1.f);

    FInputAxisKeyMapping lookUpKey("LookUp", EKeys::MouseY, -1.f);
    FInputAxisKeyMapping turnKey("Turn", EKeys::MouseX, 1.f);

    FInputActionKeyMapping aimKey("Aim", EKeys::RightMouseButton, 0, 0, 0, 0);
    FInputActionKeyMapping fireKey("Fire", EKeys::LeftMouseButton, 0, 0, 0, 0);
    FInputActionKeyMapping reloadKey("Reload", EKeys::R, 0, 0, 0, 0);
    FInputActionKeyMapping runningKey("Running", EKeys::LeftShift, 0, 0, 0, 0);
    FInputActionKeyMapping jumpKey("Jump", EKeys::SpaceBar, 0, 0, 0, 0);
    FInputActionKeyMapping crouchKey("Crouching", EKeys::LeftControl, 0, 0, 0, 0);

    PlayerInputComponent->BindAxis("Forward", this, &ACharacterBase::MoveForward);
    PlayerInputComponent->BindAxis("Back", this, &ACharacterBase::MoveForward);
    PlayerInputComponent->BindAxis("Left", this, &ACharacterBase::MoveRight);
    PlayerInputComponent->BindAxis("Right", this, &ACharacterBase::MoveRight);

    PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
    PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);

    PlayerInputComponent->BindAction("Aim", IE_Pressed, this, &ACharacterBase::Aiming);
    PlayerInputComponent->BindAction("Aim", IE_Released, this, &ACharacterBase::Aiming);
    PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &ACharacterBase::Fire);
    PlayerInputComponent->BindAction("Reload", IE_Pressed, this, &ACharacterBase::Reload);
    PlayerInputComponent->BindAction("Running", IE_Pressed, this, &ACharacterBase::Running);
    PlayerInputComponent->BindAction("Running", IE_Released, this, &ACharacterBase::Running);
    PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
    PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);
    PlayerInputComponent->BindAction("Crouching", IE_Pressed, this, &ACharacterBase::Crouching);


    GetWorld()->GetFirstPlayerController()->PlayerInput->AddAxisMapping(forwardKey);
    GetWorld()->GetFirstPlayerController()->PlayerInput->AddAxisMapping(backKey);
    GetWorld()->GetFirstPlayerController()->PlayerInput->AddAxisMapping(rightKey);
    GetWorld()->GetFirstPlayerController()->PlayerInput->AddAxisMapping(leftKey);

    GetWorld()->GetFirstPlayerController()->PlayerInput->AddAxisMapping(lookUpKey);
    GetWorld()->GetFirstPlayerController()->PlayerInput->AddAxisMapping(turnKey);

    GetWorld()->GetFirstPlayerController()->PlayerInput->AddActionMapping(aimKey);
    GetWorld()->GetFirstPlayerController()->PlayerInput->AddActionMapping(fireKey);
    GetWorld()->GetFirstPlayerController()->PlayerInput->AddActionMapping(reloadKey);
    GetWorld()->GetFirstPlayerController()->PlayerInput->AddActionMapping(runningKey);
    GetWorld()->GetFirstPlayerController()->PlayerInput->AddActionMapping(jumpKey);
    GetWorld()->GetFirstPlayerController()->PlayerInput->AddActionMapping(crouchKey);
}

void ACharacterBase::MoveForward(float AxisValue)
{
    AddMovementInput(GetActorForwardVector(), AxisValue);
}

void ACharacterBase::MoveRight(float AxisValue)
{
    AddMovementInput(GetActorRightVector(), AxisValue);
}

FVector ACharacterBase::GetViewLocation()
{
    return ViewOffset + FVector(0.f, 0.f, GetCapsuleComponent()->GetScaledCapsuleHalfHeight());
}

class AWeaponBase* ACharacterBase::GetEquippedWeapon()
{
    return EquippedWeapon;
}

void ACharacterBase::DoNothing()
{

}

bool ACharacterBase::IsAiming()
{
    return bAiming;
}

void ACharacterBase::Aiming()
{
    bAiming = !bAiming;

    SET_MAX_WALK_SPEED(250.f);
}

void ACharacterBase::Fire()
{
    if (!EquippedWeapon)
        return;

    UWeaponPoseDA* poses = EquippedWeapon->GetPosesDA();

    UAnimMontage* montage = UAnimMontage::CreateSlotAnimationAsDynamicMontage(poses->Fire, TEXT("Overlay Standing"), 0.f, 0.f, 1.f);

    FSlotAnimationTrack& slotAim = montage->AddSlot(TEXT("Overlay Aiming"));

    FAnimSegment newSegment;
    newSegment.AnimReference = poses->AimFire;
    newSegment.AnimStartTime = 0.f;
    newSegment.AnimEndTime = poses->AimFire->SequenceLength;
    newSegment.AnimPlayRate = 1.f;
    newSegment.StartPos = 0.f;
    newSegment.LoopingCount = 1;
    slotAim.AnimTrack.AnimSegments.Add(newSegment);

//     // add new track
//     FSlotAnimationTrack& NewTrack = NewMontage->SlotAnimTracks[0];
//     NewTrack.SlotName = SlotNodeName;
//     FAnimSegment NewSegment;
//     NewSegment.AnimReference = Asset;
//     NewSegment.AnimStartTime = 0.f;
//     NewSegment.AnimEndTime = Asset->SequenceLength;
//     NewSegment.AnimPlayRate = 1.f;
//     NewSegment.StartPos = 0.f;
//     NewSegment.LoopingCount = LoopCount;
//     NewMontage->SequenceLength = NewSegment.GetLength();
//     NewTrack.AnimTrack.AnimSegments.Add(NewSegment);
// 
//     FCompositeSection NewSection;
//     NewSection.SectionName = TEXT("Default");
//     NewSection.LinkSequence(Asset, Asset->SequenceLength);
//     NewSection.SetTime(0.0f);
// 
//     montage->AddSlot(TEXT("Overlay Running"));
//     montage->AddSlot(TEXT("Overlay Lowered"));


    montage->SetPreviewMesh(SkeletalMeshArms->SkeletalMesh);

//     Logger::Log(montage);

    SkeletalMeshArms->GetAnimInstance()->Montage_Play(montage);
    EquippedWeapon->Fire();
}

void ACharacterBase::Reload()
{
    if (!EquippedWeapon)
        return;

    UWeaponPoseDA* poses = EquippedWeapon->GetPosesDA();

    UAnimMontage* montage = UAnimMontage::CreateSlotAnimationAsDynamicMontage(poses->Reload, TEXT("Overlay Standing"), 0.f, 0.f, 1.f);

    FSlotAnimationTrack& slotAim = montage->AddSlot(TEXT("Overlay Aiming"));

    FAnimSegment newSegment;
    if (poses->AimReload)
    {
        newSegment.AnimReference = poses->AimReload;
        newSegment.AnimEndTime = poses->AimReload->SequenceLength;
    }
    else
    {
        newSegment.AnimReference = poses->Reload;
        newSegment.AnimEndTime = poses->Reload->SequenceLength;
    }
    newSegment.AnimStartTime = 0.f;
    newSegment.AnimPlayRate = 1.f;
    newSegment.StartPos = 0.f;
    newSegment.LoopingCount = 1;
    slotAim.AnimTrack.AnimSegments.Add(newSegment);

    SkeletalMeshArms->GetAnimInstance()->Montage_Play(montage);

    EquippedWeapon->Reload();
}

void ACharacterBase::ReloadEmpty()
{
    if (!EquippedWeapon)
        return;

    UWeaponPoseDA* poses = EquippedWeapon->GetPosesDA();

    UAnimMontage* montage = UAnimMontage::CreateSlotAnimationAsDynamicMontage(poses->ReloadEmpty, TEXT("Overlay Standing"), 0.f, 0.f, 1.f);

    FSlotAnimationTrack& slotAim = montage->AddSlot(TEXT("Overlay Aiming"));

    FAnimSegment newSegment;
    if (poses->AimReloadEmpty)
    {
        newSegment.AnimReference = poses->AimReloadEmpty;
        newSegment.AnimEndTime = poses->AimReloadEmpty->SequenceLength;
    }
    else
    {
        newSegment.AnimReference = poses->ReloadEmpty;
        newSegment.AnimEndTime = poses->ReloadEmpty->SequenceLength;
    }
    newSegment.AnimStartTime = 0.f;
    newSegment.AnimPlayRate = 1.f;
    newSegment.StartPos = 0.f;
    newSegment.LoopingCount = 1;
    slotAim.AnimTrack.AnimSegments.Add(newSegment);

    SkeletalMeshArms->GetAnimInstance()->Montage_Play(montage);

    EquippedWeapon->Reload();
}

bool ACharacterBase::IsRunning()
{
    return bRunning;
}

void ACharacterBase::Running()
{
    bRunning = !bRunning;

    SET_MAX_WALK_SPEED(450.f);
}

bool ACharacterBase::IsFalling()
{
    return GetCharacterMovement()->IsFalling();
}

bool ACharacterBase::IsCrouching()
{
    return bCrouching;
}

void ACharacterBase::Crouching()
{
    bCrouching = !bCrouching;

    if (bCrouching)
    {
        Crouch();
    }
    else
    {
        UnCrouch();
    }
}
