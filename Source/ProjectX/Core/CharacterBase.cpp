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

    HalfHeight = FVector(0.f, 0.f,GetCapsuleComponent()->GetScaledCapsuleHalfHeight());
    SkeletalMeshArms->AddRelativeLocation(-HalfHeight);
    SpringArm->TargetArmLength = 0.f;
    SpringArm->bDoCollisionTest = false;

    TSubclassOf<UAnimInstance> armsAnimInst;
    Helpers::GetClass(&armsAnimInst, TEXT("AnimBlueprint'/Game/ProjectX/Characters/ABP_CharacterBase.ABP_CharacterBase_C'"));
    SkeletalMeshArms->SetAnimClass(armsAnimInst);
    SkeletalMeshArms->SetBoundsScale(6.f);
}

// Called when the game starts or when spawned
void ACharacterBase::BeginPlay()
{
	Super::BeginPlay();
	
    if (!EquippedWeapon && TestWeapon)
    {
        EquippedWeapon = GetWorld()->SpawnActor<AWeaponBase>(TestWeapon, GetActorTransform());
    }
}

// Called every frame
void ACharacterBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

    Helpers::DrawGizmo(GetWorld(), GetActorLocation() + GetActorForwardVector() * 250.f, FQuat(GetController()->GetControlRotation()));

    SpringArm->SetRelativeRotation(FRotator(GetControlRotation().Pitch, 0.f, 0.f));
    SetActorRelativeRotation(FRotator(0.f, GetControlRotation().Yaw, 0.f));
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

    PlayerInputComponent->BindAxis("Forward", this, &ACharacterBase::MoveForward);
    PlayerInputComponent->BindAxis("Back", this, &ACharacterBase::MoveForward);
    PlayerInputComponent->BindAxis("Left", this, &ACharacterBase::MoveRight);
    PlayerInputComponent->BindAxis("Right", this, &ACharacterBase::MoveRight);

    PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
    PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);

    GetWorld()->GetFirstPlayerController()->PlayerInput->AddAxisMapping(forwardKey);
    GetWorld()->GetFirstPlayerController()->PlayerInput->AddAxisMapping(backKey);
    GetWorld()->GetFirstPlayerController()->PlayerInput->AddAxisMapping(rightKey);
    GetWorld()->GetFirstPlayerController()->PlayerInput->AddAxisMapping(leftKey);

    GetWorld()->GetFirstPlayerController()->PlayerInput->AddAxisMapping(lookUpKey);
    GetWorld()->GetFirstPlayerController()->PlayerInput->AddAxisMapping(turnKey);
}

void ACharacterBase::MoveForward(float AxisValue)
{
    AddMovementInput(GetActorForwardVector(), AxisValue);
}

void ACharacterBase::MoveRight(float AxisValue)
{
    AddMovementInput(GetActorRightVector(), AxisValue);
}

class AWeaponBase* ACharacterBase::GetEquippedWeapon()
{
    return EquippedWeapon;
}
