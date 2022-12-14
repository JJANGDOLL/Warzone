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
#include "Widget/MainGameInterface.h"
#include "Blueprint/UserWidget.h"
#include "Core/PlayerControllerBase.h"
#include "Widget/WeaponWidget.h"
#include "Widget/WeaponTexture.h"
#include "Weapons/Sniper_01.h"
#include "AC_Inventory.h"
#include "Kismet/GameplayStatics.h"
#include "Interfaces/IInteractable.h"
#include "Widget/InteractTextWidget.h"
#include "Widget/Crosshair.h"
#include "Widget/PlayerStatus.h"

#define SET_MAX_WALK_SPEED(p) GetCharacterMovement()->MaxWalkSpeed = p;
#define RET_IS_UNARMED if(!GetEquippedWeapon()) return;
#define IS_UNARMED GetEquippedWeapon() == nullptr

// Sets default values
ACharacterBase::ACharacterBase()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

    Helpers::CreateComponent(this, &SpringArm, TEXT("Spring Arm"), GetMesh());
    Helpers::CreateComponent(this, &SkeletalMeshArms, TEXT("Skeletal Mesh Arms"), SpringArm);
    Helpers::CreateComponent(this, &Camera, TEXT("Camera"), SkeletalMeshArms, TEXT("SOCKET_Camera"));

    Helpers::CreateActorComponent(this, &Inventory, TEXT("Inventory"));

    USkeletalMesh* meshArms;
    Helpers::GetAsset(&meshArms, TEXT("SkeletalMesh'/Game/InfimaGames/LowPolyShooterPack/Art/Characters/Default/SK_FP_CH_Default.SK_FP_CH_Default'"));

    SkeletalMeshArms->SetSkeletalMesh(meshArms);

    SkeletalMeshArms->AddRelativeRotation(FRotator(0.f, -90.f, 0.f));
    SkeletalMeshArms->SetCollisionEnabled(ECollisionEnabled::NoCollision);

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
    TestWeapon = AAssault_Rifle_02::StaticClass();
    TestWeapon = AHandgun_01::StaticClass();
    TestWeapon = ASniper_01::StaticClass();

    UCharacterMovementComponent* const movementComp = GetCharacterMovement();
    movementComp->CrouchedHalfHeight = 54.f;

    movementComp->GetNavAgentPropertiesRef().bCanCrouch = true;
    movementComp->MaxWalkSpeed = 300.f;

//     GetCapsuleComponent()->SetVisibility(true);
//     GetCapsuleComponent()->bHiddenInGame = false;

    ViewOffset = FVector(0.f, 0.f, -25.f);

    PlayerHUD = nullptr;
    Helpers::GetClass<UMainGameInterface>(&PlayerHUDClass, TEXT("WidgetBlueprint'/Game/ProjectX/Widgets/Main_Game_Interface.Main_Game_Interface_C'"));

    PauseWidgetClass = nullptr;
    Helpers::GetClass<UUserWidget>(&PauseWidgetClass, TEXT("WidgetBlueprint'/Game/ProjectX/Widgets/WBP_Pause.WBP_Pause_C'"));

    CrosshairClass = nullptr;
    Helpers::GetClass<UCrosshair>(&CrosshairClass, TEXT("WidgetBlueprint'/Game/ProjectX/Widgets/Crosshair/WBP_CrosshairDefault.WBP_CrosshairDefault_C'"));

    GetCapsuleComponent()->SetCollisionProfileName(TEXT("PlayerBody"));
}

void ACharacterBase::OnConstruction(const FTransform& Transform)
{
    Super::OnConstruction(Transform);

    SpringArm->SetRelativeLocation(GetViewLocation());
}

void ACharacterBase::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
    if (PlayerHUD)
    {
        PlayerHUD->RemoveFromParent();
        PlayerHUD = nullptr;
    }

    Super::EndPlay(EndPlayReason);
}

float ACharacterBase::TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
    CurHealth -= Damage;

    UpdateStatusWidget();
    
    return Super::TakeDamage(Damage, DamageEvent, EventInstigator, DamageCauser);
}

void ACharacterBase::Hitted(float Damage, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, class AActor* DamageCauser)
{
    TakeDamage(Damage, DamageEvent, EventInstigator, DamageCauser);
}

USkeletalMeshComponent* ACharacterBase::GetMeshArms()
{
    return SkeletalMeshArms;
}

// Called when the game starts or when spawned
void ACharacterBase::BeginPlay()
{
	Super::BeginPlay();

    Inventory->OnWeaponChanged.BindUObject(this, &ACharacterBase::NewWeapon);
    Inventory->OnWidgetUpdate.BindUObject(this, &ACharacterBase::UpdateWeaponWidget);

    CurHealth = MaxHealth;
    CurEnergy = MaxEnergy;

//     if (IsWeaponEquipped())
//         GetEquippedWeapon()->AttachToComponent(SkeletalMeshArms, FAttachmentTransformRules::SnapToTargetIncludingScale, TEXT("SOCKET_Weapon"));
//     else
//         bHolster = true;

    SpringArm->SetRelativeLocation(GetViewLocation());
//     SkeletalMeshArms->AddRelativeLocation(-FVector(0.f, 0.f, GetCapsuleComponent()->GetScaledCapsuleHalfHeight()));

    OnTestFeature = TestMethods[TestFeature];

    if(OnTestFeature)
        GetWorldTimerManager().SetTimer(TestTimerHandle, this, OnTestFeature, TestTerm, true, 2.0f);

    if (IsLocallyControlled() && PlayerHUDClass)
    {
//         PrintLine();
        APlayerControllerBase* FPC = GetController<APlayerControllerBase>();
        if (!FPC)
        {
            return;
        }
        PlayerHUD = CreateWidget<UMainGameInterface>(FPC, PlayerHUDClass);
        verifyf(PlayerHUD, L"Invalid HUD");
        PlayerHUD->AddToPlayerScreen();
        PlayerHUD->SetCrosshairClass(CrosshairClass);
        PlayerHUD->GetPlayerStatus()->SetHealth(MaxHealth, CurHealth);
        PlayerHUD->GetPlayerStatus()->SetHealth(MaxEnergy, CurEnergy);
    }

    if (IS_UNARMED)
    {
        bHolster = true;
        PlayerHUD->GetWeaponImage()->SetVisibility(ESlateVisibility::Hidden);
        PlayerHUD->GetWeaponWidget()->SetVisibility(ESlateVisibility::Hidden);
        SkeletalMeshArms->SetVisibility(false);
    }
}

// Called every frame
void ACharacterBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

//     Helpers::DrawGizmo(GetWorld(), GetActorLocation() + GetActorForwardVector() * 250.f, FQuat(GetController()->GetControlRotation()));

    SpringArm->SetRelativeRotation(FRotator(GetControlRotation().Pitch, 0.f, 0.f));
    SetActorRelativeRotation(FRotator(0.f, GetControlRotation().Yaw, 0.f));

    SpringArm->SetRelativeLocation(FMath::VInterpTo(SpringArm->GetRelativeLocation(), GetViewLocation(), GetWorld()->GetDeltaSeconds(), 15.0f));
    Camera->SetFieldOfView(FMath::FInterpTo(Camera->FieldOfView, SkeletalMeshArms->GetAnimInstance()->GetCurveValue(TEXT("Field Of View")), GetWorld()->GetDeltaSeconds(), 10.f));

    if (GetController()->IsPlayerController())
    {
        FVector location;
        FVector direction;

        int32 sizeX;
        int32 sizeY;
        UGameplayStatics::GetPlayerController(GetWorld(), 0)->GetViewportSize(sizeX, sizeY);
        UGameplayStatics::DeprojectScreenToWorld(UGameplayStatics::GetPlayerController(GetWorld(), 0), FVector2D(sizeX / 2, sizeY / 2), location, direction);

        FHitResult hitResult;

        if (GetWorld()->LineTraceSingleByChannel(hitResult, location, location + direction * 200.f, ECollisionChannel::ECC_GameTraceChannel4))
        {
            IIInteractable* interact;
            interact = Cast<IIInteractable>(hitResult.GetActor());
            if (!interact)
                return;
            InteractTarget = interact;
        }
        else
        {
            InteractTarget = nullptr;
        }
        UpdateWidget();
    }

    if (bRunning || !bBreath)
    {
        EnergyRecoverDilation = 0.f;
        CurEnergy -= DeltaTime * 20;

        if (CurEnergy <= 0.f)
        {
            if (bRunning)
                bRunning = false;

            if (!bBreath)
                bBreath = true;
        }

    }
    else
    {
        EnergyRecoverDilation += DeltaTime;
        EnergyRecoverDilation = FMath::Clamp(EnergyRecoverDilation, 0.f, 2.f);
    }

    if (EnergyRecoverDilation >= 1)
    {
        CurEnergy += DeltaTime * 20;
        CurEnergy = FMath::Clamp(CurEnergy, 0.f, MaxEnergy);
    }
    UpdateStatusWidget();
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
    FInputActionKeyMapping crouchKey("Crouching", EKeys::C, 0, 0, 0, 0);
    FInputActionKeyMapping breathKey("Breath", EKeys::CapsLock, 0, 0, 0, 0);
    FInputActionKeyMapping firetypeKey("FireType", EKeys::B, 0, 0, 0, 0);
//     FInputActionKeyMapping holsterKey("Holstering", EKeys::G, 0, 0, 0, 0);

    FInputActionKeyMapping item1Key("Item1Key", EKeys::One, 0, 0, 0, 0);
    FInputActionKeyMapping item2Key("Item2Key", EKeys::Two, 0, 0, 0, 0);
    FInputActionKeyMapping item3Key("Item3Key", EKeys::Three, 0, 0, 0, 0);

    FInputActionKeyMapping interactKey("Interact", EKeys::E, 0, 0, 0, 0);
    FInputActionKeyMapping dropKey("Drop", EKeys::H, 0, 0, 0, 0);
    FInputActionKeyMapping pauseKey("Pause", EKeys::P, 0, 0, 0, 0);

    PlayerInputComponent->BindAxis("Forward", this, &ACharacterBase::MoveForward);
    PlayerInputComponent->BindAxis("Back", this, &ACharacterBase::MoveForward);
    PlayerInputComponent->BindAxis("Left", this, &ACharacterBase::MoveRight);
    PlayerInputComponent->BindAxis("Right", this, &ACharacterBase::MoveRight);

    PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
    PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);

    PlayerInputComponent->BindAction("Aim", IE_Pressed, this, &ACharacterBase::StartAiming);
    PlayerInputComponent->BindAction("Aim", IE_Released, this, &ACharacterBase::StopAiming);
    PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &ACharacterBase::Fire);
    PlayerInputComponent->BindAction("Fire", IE_Released, this, &ACharacterBase::StopFire);
    PlayerInputComponent->BindAction("Reload", IE_Pressed, this, &ACharacterBase::Reload);
    PlayerInputComponent->BindAction("Running", IE_Pressed, this, &ACharacterBase::Running);
    PlayerInputComponent->BindAction("Running", IE_Released, this, &ACharacterBase::StopRunning);
    PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
    PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);
    PlayerInputComponent->BindAction("Crouching", IE_Pressed, this, &ACharacterBase::StartCrouch);
    PlayerInputComponent->BindAction("Crouching", IE_Released, this, &ACharacterBase::StopCrouch);
    PlayerInputComponent->BindAction("Breath", IE_Pressed, this, &ACharacterBase::StartBreath);
    PlayerInputComponent->BindAction("Breath", IE_Released, this, &ACharacterBase::StopBreath);
    PlayerInputComponent->BindAction("FireType", IE_Pressed, this, &ACharacterBase::ChangeFireType);
//     PlayerInputComponent->BindAction("Holstering", IE_Pressed, this, &ACharacterBase::Holstering);
    PlayerInputComponent->BindAction("Item1Key", IE_Pressed, this, &ACharacterBase::GetItemOne);
    PlayerInputComponent->BindAction("Item2Key", IE_Pressed, this, &ACharacterBase::GetItemTwo);
    PlayerInputComponent->BindAction("Item3Key", IE_Pressed, this, &ACharacterBase::GetItemThree);
    PlayerInputComponent->BindAction("Interact", IE_Pressed, this, &ACharacterBase::Interact);
    PlayerInputComponent->BindAction("Drop", IE_Pressed, this, &ACharacterBase::DropItem);
    PlayerInputComponent->BindAction("Pause", IE_Pressed, this, &ACharacterBase::Pause).bExecuteWhenPaused = true;


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
    GetWorld()->GetFirstPlayerController()->PlayerInput->AddActionMapping(breathKey);
    GetWorld()->GetFirstPlayerController()->PlayerInput->AddActionMapping(firetypeKey);
//     GetWorld()->GetFirstPlayerController()->PlayerInput->AddActionMapping(holsterKey);

    GetWorld()->GetFirstPlayerController()->PlayerInput->AddActionMapping(item1Key);
    GetWorld()->GetFirstPlayerController()->PlayerInput->AddActionMapping(item2Key);
    GetWorld()->GetFirstPlayerController()->PlayerInput->AddActionMapping(item3Key);

    GetWorld()->GetFirstPlayerController()->PlayerInput->AddActionMapping(interactKey);
    GetWorld()->GetFirstPlayerController()->PlayerInput->AddActionMapping(dropKey);
    GetWorld()->GetFirstPlayerController()->PlayerInput->AddActionMapping(pauseKey);
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

AWeaponBase* ACharacterBase::GetEquippedWeapon()
{
//     PrintLine();
//     Logger::Log(Inventory->GetCurrentItem());
    return Cast<AWeaponBase>(Inventory->GetCurrentItem());
}

void ACharacterBase::UpdateEquippedWeapon()
{
    if (!Inventory)
        return;

    *EquippedWeapon = Cast<AWeaponBase>(Inventory->GetCurrentItem());
}

void ACharacterBase::UpdateStatusWidget()
{
    if (!PlayerHUD)
        return;

    PlayerHUD->GetPlayerStatus()->SetHealth(MaxHealth, CurHealth);
    PlayerHUD->GetPlayerStatus()->SetEnergy(MaxEnergy, CurEnergy);
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
    if (!EquippedWeapon)
    {
        Logger::Log(TEXT("No Weapon"));
        return;
    }

    StopRunning();

    bAiming = !bAiming;

    SET_MAX_WALK_SPEED(250.f);
}

void ACharacterBase::Fire()
{
    RET_IS_UNARMED;

    if (GetEquippedWeapon()->IsBoltAction() && bPlayingMontageReloading && !bBoltActionReloadStop)
    {
        bBoltActionReloadStop = true;
        return;
    }

    if (!bCanFire)
        return;

    if (bPlayingMontageReloading)
        return;

    if (bPlayingMontageUnholstering)
        return;

    if (GetEquippedWeapon()->GetCurAmmo() <= 0)
    {
        return;
    }

    if (bRunning)
    {
        StopRunning();
        return;
    }

    if (GetEquippedWeapon()->GetFireType() == EFireType::Brust && bHoldingFire)
    {
        return;
    }

    UWeaponPoseDA* poses = GetEquippedWeapon()->GetPosesDA();

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
    montage->SetPreviewMesh(SkeletalMeshArms->SkeletalMesh);

    FireDelegate = FTimerDelegate::CreateUObject(this, &ACharacterBase::FireCore, montage);

    switch (GetEquippedWeapon()->GetFireType())
    {

        case EFireType::Single:
            FireCore(montage);
            break;
        case EFireType::Brust:
            BrustFireCount = 0;
            bHoldingFire = true;
            GetWorldTimerManager().SetTimer(FireHandle, FireDelegate, GetEquippedWeapon()->GetFireInterval() * 0.8f, true, 0.0f);
            break;
        case EFireType::Auto:
            bHoldingFire = true;
            GetWorldTimerManager().SetTimer(FireHandle, FireDelegate, GetEquippedWeapon()->GetFireInterval(), true, 0.0f);
            break;
    }
}


void ACharacterBase::Reload()
{
    if (bPlayingMontageReloading)
        return;

    if (!bCanReload)
        return;

    if (!GetEquippedWeapon())
        return;

    if (bPlayingMontageUnholstering)
        return;

    if (Inventory->GetRemainAmmo(GetEquippedWeapon()->GetWeaponAmmoType()) <= 0)
        return;

    bPlayingMontageReloading = true;
    StopRunning();

    if (GetEquippedWeapon()->IsBoltAction())
    {
        ReloadBoltActionAmmo();
        return;
    }

    if (GetEquippedWeapon()->GetCurAmmo() == 0 && GetEquippedWeapon()->GetPosesDA()->ReloadEmpty)
    {
        ReloadEmpty();
        return;
    }

    UWeaponPoseDA* poses = GetEquippedWeapon()->GetPosesDA();

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
        StopAiming();
        newSegment.AnimReference = poses->Reload;
        newSegment.AnimEndTime = poses->Reload->SequenceLength;
    }
    newSegment.AnimStartTime = 0.f;
    newSegment.AnimPlayRate = 1.f;
    newSegment.StartPos = 0.f;
    newSegment.LoopingCount = 1;
    slotAim.AnimTrack.AnimSegments.Add(newSegment);

    SkeletalMeshArms->GetAnimInstance()->Montage_Play(montage);


    FOnMontageEnded BlendOutDele;
    BlendOutDele.BindUObject(this, &ACharacterBase::OnReloadBlendOut);
    SkeletalMeshArms->GetAnimInstance()->Montage_SetBlendingOutDelegate(BlendOutDele, montage);

    GetEquippedWeapon()->Reload();
}

void ACharacterBase::ReloadEmpty()
{
    if (!GetEquippedWeapon())
        return;

    UWeaponPoseDA* poses = GetEquippedWeapon()->GetPosesDA();

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
        StopAiming();
        newSegment.AnimReference = poses->ReloadEmpty;
        newSegment.AnimEndTime = poses->ReloadEmpty->SequenceLength;
    }
    newSegment.AnimStartTime = 0.f;
    newSegment.AnimPlayRate = 1.f;
    newSegment.StartPos = 0.f;
    newSegment.LoopingCount = 1;
    slotAim.AnimTrack.AnimSegments.Add(newSegment);

    SkeletalMeshArms->GetAnimInstance()->Montage_Play(montage);

    FOnMontageEnded BlendOutDele;
    BlendOutDele.BindUObject(this, &ACharacterBase::OnReloadBlendOut);
    SkeletalMeshArms->GetAnimInstance()->Montage_SetBlendingOutDelegate(BlendOutDele, montage);

    GetEquippedWeapon()->Reload();
}

bool ACharacterBase::IsRunning()
{
    return bRunning;
}

void ACharacterBase::Running()
{
    if (CurEnergy < 20.f)
        return;

    if (bPlayingMontageReloading)
        return;

    if (bCrouching)
        return;

    bRunning = true;



    SET_MAX_WALK_SPEED(450.f);
}

void ACharacterBase::StopRunning()
{
    bRunning = false;

    SET_MAX_WALK_SPEED(300.f);
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
    if (bRunning)
        return;

    bCrouching = !bCrouching;

    if (bCrouching)
    {
        StopRunning();
        Crouch();
    }
    else
    {
        UnCrouch();
    }
}

bool ACharacterBase::IsBreath()
{
    return bBreath;
}

void ACharacterBase::Breath()
{
    if (CurEnergy <= 20.f)
        return;

    bBreath = !bBreath;
}

void ACharacterBase::StartBreath()
{
    if (!bAiming)
        return;

    if (CurEnergy <= 20.f)
        return;

    bBreath = false;
}

void ACharacterBase::StopBreath()
{
    bBreath = true;

}

bool ACharacterBase::IsHolster()
{
    return bHolster;
}

void ACharacterBase::Holstering()
{
    RET_IS_UNARMED;

    if (bHoldingFire)
        return;

    if (bPlayingMontageReloading)
        return;
}

void ACharacterBase::Unholstering()
{
    if (bPlayingMontageUnholstering)
        return;

    bPlayingMontageUnholstering = true;

    GetEquippedWeapon()->SetActorHiddenInGame(false);

    UWeaponPoseDA* poses = GetEquippedWeapon()->GetPosesDA();

    UAnimMontage* montage = UAnimMontage::CreateSlotAnimationAsDynamicMontage(poses->Unholster, TEXT("Overlay Standing"), 0.f, 0.f, 1.f);

    FSlotAnimationTrack& slotAim = montage->AddSlot(TEXT("Overlay Aiming"));

    FAnimSegment newSegment;
    newSegment.AnimReference = poses->Unholster;
    newSegment.AnimEndTime = poses->Unholster->SequenceLength;
    newSegment.AnimStartTime = 0.f;
    newSegment.AnimPlayRate = 1.f;
    newSegment.StartPos = 0.f;
    newSegment.LoopingCount = 1;
    slotAim.AnimTrack.AnimSegments.Add(newSegment);

    SkeletalMeshArms->SetVisibility(true);

    SkeletalMeshArms->GetAnimInstance()->Montage_Play(montage);

    FOnMontageEnded BlendOutDele;
    BlendOutDele.BindUObject(this, &ACharacterBase::OnUnholsterBlendOut);
    SkeletalMeshArms->GetAnimInstance()->Montage_SetBlendingOutDelegate(BlendOutDele, montage);
}

void ACharacterBase::StopFire()
{
    RET_IS_UNARMED;
    
    if(GetEquippedWeapon()->GetFireType() == EFireType::Auto)
        bHoldingFire = false;
}

void ACharacterBase::ChangeFireType()
{
    if (!GetEquippedWeapon())
        return;

    if (bPlayingMontageReloading)
        return;

    if (bHoldingFire)
        return;

    GetEquippedWeapon()->ChangeFireType();
}

void ACharacterBase::FireCore(UAnimMontage* Montage)
{
    RET_IS_UNARMED;

    if (GetEquippedWeapon()->GetFireType() == EFireType::Auto && GetEquippedWeapon()->GetCurAmmo() <= 0)
    {
        bHoldingFire = false;
        GetWorldTimerManager().ClearTimer(FireHandle);
        return;
    }

    if (GetEquippedWeapon()->GetFireType() == EFireType::Auto && !bHoldingFire)
    {
        bHoldingFire = false;
        GetWorldTimerManager().ClearTimer(FireHandle);
        return;
    }

    if (GetEquippedWeapon()->GetFireType() == EFireType::Brust && GetEquippedWeapon()->GetCurAmmo() <= 0)
    {
        bHoldingFire = false;
        GetWorldTimerManager().ClearTimer(FireHandle);
        return;
    }

    if (GetEquippedWeapon()->GetFireType() == EFireType::Brust && BrustFireCount >= 3)
    {
        bHoldingFire = false;
        GetWorldTimerManager().ClearTimer(FireHandle);
        return;
    }


    SkeletalMeshArms->GetAnimInstance()->Montage_Play(Montage);
    if (GetEquippedWeapon()->IsBoltAction())
    {
        bCanFire = false;
        bCanReload = false;
    }
    FOnMontageEnded BlendOutDele;
    BlendOutDele.BindUObject(this, &ACharacterBase::OnFireBlendOut);
    SkeletalMeshArms->GetAnimInstance()->Montage_SetBlendingOutDelegate(BlendOutDele, Montage);

    GetEquippedWeapon()->Fire();

    BrustFireCount++;
}

bool ACharacterBase::IsWeaponEquipped()
{
    if (!EquippedWeapon)
        return false;
    return (*EquippedWeapon) != nullptr;
}

// AWeaponBase* ACharacterBase::GetEquippedWeapon()
// {
//     return *EquippedWeapon;
// }

void ACharacterBase::UpdateWidget()
{
    if (InteractTarget)
    {
        PlayerHUD->GetInteractText()->SetInteractText(InteractTarget->Description());
    }
    else
    {
        PlayerHUD->GetInteractText()->SetInteractText(FText::FromString(TEXT("")));
    }
}

void ACharacterBase::OnReloadBlendOut(UAnimMontage* AnimMontage, bool bInterrupted)
{
    uint8 needAmmo = GetEquippedWeapon()->GetMaxAmmo() - GetEquippedWeapon()->GetCurAmmo();

    uint8 ammotoEquip = (Inventory->GetRemainAmmo(GetEquippedWeapon()->GetWeaponAmmoType()) > needAmmo  ? needAmmo  : Inventory->GetRemainAmmo(GetEquippedWeapon()->GetWeaponAmmoType()));

    Inventory->SetRemainAmmo(GetEquippedWeapon()->GetWeaponAmmoType(), ammotoEquip);
    GetEquippedWeapon()->SetAmmo(ammotoEquip + GetEquippedWeapon()->GetCurAmmo());

    bPlayingMontageReloading = false;
}

void ACharacterBase::OnUnholsterBlendOut(UAnimMontage* AnimMontage, bool bInterrupted)
{
    PrintLine();

    bPlayingMontageReloading = false;
    bCanFire = true;
    bPlayingMontageUnholstering = false;
}

void ACharacterBase::OnFireBlendOut(UAnimMontage* AnimMontage, bool bInterrupted)
{
    PrintLine();

    if (!GetEquippedWeapon()->IsBoltAction())
        return;

    BoltActionReload();
}

void ACharacterBase::OnBoltActionReloadBlendOut(UAnimMontage* AnimMontage, bool bInterrupted)
{
    bCanFire = true;
    bCanReload = true;
}

void ACharacterBase::StartCrouch()
{
    if (bRunning)
        return;

    bCrouching = true;

    StopRunning();
    Crouch();
}

void ACharacterBase::StopCrouch()
{
    bCrouching = false;
    UnCrouch();
}

void ACharacterBase::StartAiming()
{
    if (!GetEquippedWeapon())
        return;

    if (bPlayingMontageReloading)
        return;

    StopRunning();

    bAiming = true;

    PlayerHUD->GetCrosshairWidget()->SetVisibility(ESlateVisibility::Hidden);

    SET_MAX_WALK_SPEED(250.f);
}

void ACharacterBase::StopAiming()
{
    if (!bAiming)
        return;

    bAiming = false;

    PlayerHUD->GetCrosshairWidget()->SetVisibility(ESlateVisibility::Visible);

    SET_MAX_WALK_SPEED(300.f);
}

void ACharacterBase::GetItemOne()
{
    if (bPlayingMontageUnholstering)
        return;

    if (bPlayingMontageReloading)
        return;

    if (bHoldingFire)
        return;

    AWeaponBase* weapon = Cast<AWeaponBase>(Inventory->GetSelectedItem(0));
    if (!weapon)
        return;


    if (GetEquippedWeapon())
    {
        if (weapon == GetEquippedWeapon())
            return;

        GetEquippedWeapon()->SetActorHiddenInGame(true);
    }

    if (weapon == GetEquippedWeapon())
    {
        return;
    }

    Inventory->SetSelectedItem(0);

    GetEquippedWeapon()->SetActorHiddenInGame(false);
    Unholstering();
}

void ACharacterBase::GetItemTwo()
{
    if (bPlayingMontageUnholstering)
        return;

    if (bPlayingMontageReloading)
        return;

    if (bHoldingFire)
        return;

    AWeaponBase* weapon = Cast<AWeaponBase>(Inventory->GetSelectedItem(1));
    if (!weapon)
        return;

    if (weapon == GetEquippedWeapon())
    {
        return;
    }

    GetEquippedWeapon()->SetActorHiddenInGame(true);
    Inventory->SetSelectedItem(1);

    GetEquippedWeapon()->SetActorHiddenInGame(false);
    Unholstering();
}

void ACharacterBase::GetItemThree()
{
    if (bPlayingMontageUnholstering)
        return;

    if (bPlayingMontageReloading)
        return;

    if (bHoldingFire)
        return;

    AWeaponBase* weapon = Cast<AWeaponBase>(Inventory->GetSelectedItem(2));
    if (!weapon)
        return;

    if (weapon == GetEquippedWeapon())
    {
        return;
    }

    GetEquippedWeapon()->SetActorHiddenInGame(true);
    Inventory->SetSelectedItem(2);

    GetEquippedWeapon()->SetActorHiddenInGame(false);
    Unholstering();
}

void ACharacterBase::EndHolstering()
{
    RET_IS_UNARMED;

    AWeaponBase* weapon = Cast<AWeaponBase>(Inventory->GetCurrentItem());
    weapon->SetActorHiddenInGame(true);

    bHolster = true;
    bPlayingMontageUnholstering = false;
}

void ACharacterBase::EndUnholstering()
{
    return;

    RET_IS_UNARMED;

    bPlayingMontageUnholstering = false;
    bHolster = false;
}

void ACharacterBase::Interact()
{
    if (!InteractTarget)
        return;

    if (bPlayingMontageReloading)
        return;

    if (bPlayingMontageUnholstering)
        return;

    if (bHoldingFire)
        return;

    InteractTarget->Action();
}

void ACharacterBase::DropItem()
{
    RET_IS_UNARMED;

    if (bPlayingMontageReloading)
        return;

    if (bHoldingFire)
        return;

    if (bPlayingMontageUnholstering)
        return;

    Inventory->DropItem();
}

void ACharacterBase::NewWeapon()
{
    UpdateWeaponWidget();

    RET_IS_UNARMED;

    GetEquippedWeapon()->AttachToComponent(SkeletalMeshArms, FAttachmentTransformRules::SnapToTargetIncludingScale, TEXT("SOCKET_Weapon"));
    GetEquippedWeapon()->Equipped();

    Unholstering();

    GetEquippedWeapon()->OnWeaponFire.BindUObject(this, &ACharacterBase::UpdateWeaponWidget);
    GetEquippedWeapon()->OnWeaponRecoil.BindUObject(this, &ACharacterBase::WeaponRecoil);
    GetEquippedWeapon()->OnWeaponFiretypeChanged.BindUObject(this, &ACharacterBase::UpdateWeaponWidget);
    GetEquippedWeapon()->OnWeaponReload.BindUObject(this, &ACharacterBase::UpdateWeaponWidget);

//     PlayerHUD->SetCrosshairClass(GetEquippedWeapon()->GetCrosshairClass());
}

UAC_Inventory* ACharacterBase::GetInventory()
{
    return Inventory;
}

void ACharacterBase::UpdateWeaponWidget()
{
    if (IS_UNARMED)
    {
        PlayerHUD->GetWeaponImage()->SetVisibility(ESlateVisibility::Hidden);
        PlayerHUD->GetWeaponWidget()->SetVisibility(ESlateVisibility::Hidden);
    }

    if (!PlayerHUD)
    {
        return;
    }

    PlayerHUD->GetWeaponImage()->SetVisibility(ESlateVisibility::Visible);
    PlayerHUD->GetWeaponWidget()->SetVisibility(ESlateVisibility::Visible);

    if (Inventory->GetCurrentItem())
    {
        PlayerHUD->GetWeaponWidget()->SetMaxAmmo(Inventory->GetRemainAmmo(GetEquippedWeapon()->GetWeaponAmmoType()));
        PlayerHUD->GetWeaponWidget()->SetCurAmmo(GetEquippedWeapon());
        PlayerHUD->GetWeaponWidget()->SetFireType(GetEquippedWeapon());
        PlayerHUD->GetWeaponImage()->SetWeaponBodyImage(GetEquippedWeapon());
    }
}

void ACharacterBase::WeaponRecoil()
{
    FVector2D recoilIntensity = GetEquippedWeapon()->GetRecoilIntensity();

    float recoilUp = FMath::FRandRange(recoilIntensity.X * 0.1f, recoilIntensity.X);
    float recoilRight = FMath::FRandRange(recoilIntensity.Y * 0.1f, recoilIntensity.Y);

    if (bAiming)
    {
        recoilUp *= 0.8f;
        recoilRight *= 0.8f;
    }
    else
    {
        recoilUp *= 1.2f;
        recoilRight *= 1.2f;
    }

    if (bCrouching)
    {
        recoilUp *= 0.6;
        recoilRight *= 0.6f;
    }

    GetController()->SetControlRotation(FRotator(recoilUp, recoilRight, 0.f) + GetControlRotation());
}

void ACharacterBase::Pause()
{
    if (!PauseWidget)
    {
        PauseWidget = CreateWidget<UUserWidget>(GetWorld(), PauseWidgetClass, TEXT("PauseWidget"));
    }

    PauseWidget->AddToViewport();
}

void ACharacterBase::BoltActionReload()
{
    if (bPlayingMontageReloading)
        return;

    if (!GetEquippedWeapon())
        return;

    if (bPlayingMontageUnholstering)
        return;

    if (Inventory->GetRemainAmmo(GetEquippedWeapon()->GetWeaponAmmoType()) <= 0)
        return;

    UWeaponPoseDA* poses = GetEquippedWeapon()->GetPosesDA();

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
        StopAiming();
        newSegment.AnimReference = poses->Reload;
        newSegment.AnimEndTime = poses->Reload->SequenceLength;
    }
    newSegment.AnimStartTime = 0.f;
    newSegment.AnimPlayRate = 1.f;
    newSegment.StartPos = 0.f;
    newSegment.LoopingCount = 1;
    slotAim.AnimTrack.AnimSegments.Add(newSegment);

    SkeletalMeshArms->GetAnimInstance()->Montage_Play(montage);
    FOnMontageEnded BlendOutDele;
    BlendOutDele.BindUObject(this, &ACharacterBase::OnBoltActionReloadBlendOut);
    SkeletalMeshArms->GetAnimInstance()->Montage_SetBlendingOutDelegate(BlendOutDele, montage);

    GetEquippedWeapon()->BoltActionReload();
}

void ACharacterBase::ReloadBoltActionAmmo()
{
    if (GetEquippedWeapon()->GetCurAmmo() == GetEquippedWeapon()->GetMaxAmmo())
    {
        bPlayingMontageReloading = false;
        return;
    }

    UWeaponPoseDA* poses = GetEquippedWeapon()->GetPosesDA();

    UAnimMontage* montage = UAnimMontage::CreateSlotAnimationAsDynamicMontage(poses->BoltActionOpenPose, TEXT("Overlay Standing"), 0.f, 0.f, 1.f);

    FSlotAnimationTrack& slotAim = montage->AddSlot(TEXT("Overlay Aiming"));

    FAnimSegment newSegment;

    StopAiming();
    newSegment.AnimReference = poses->BoltActionOpenPose;
    newSegment.AnimEndTime = poses->BoltActionOpenPose->SequenceLength;
    newSegment.AnimStartTime = 0.f;
    newSegment.AnimPlayRate = 1.f;
    newSegment.StartPos = 0.f;
    newSegment.LoopingCount = 1;
    slotAim.AnimTrack.AnimSegments.Add(newSegment);

    SkeletalMeshArms->GetAnimInstance()->Montage_Play(montage);

    FOnMontageEnded BlendOutDele;
    BlendOutDele.BindUObject(this, &ACharacterBase::OnBoltActionOpenBlendOut);
    SkeletalMeshArms->GetAnimInstance()->Montage_SetBlendingOutDelegate(BlendOutDele, montage);

    GetEquippedWeapon()->Reload();
}

void ACharacterBase::OnBoltActionOpenBlendOut(UAnimMontage* AnimMontage, bool bInterrupted)
{
    UWeaponPoseDA* poses = GetEquippedWeapon()->GetPosesDA();

    UAnimMontage* montage = UAnimMontage::CreateSlotAnimationAsDynamicMontage(poses->BoltActionInsertPose, TEXT("Overlay Standing"), 0.f, 0.f, 1.f);

    FSlotAnimationTrack& slotAim = montage->AddSlot(TEXT("Overlay Aiming"));

    FAnimSegment newSegment;

    StopAiming();
    newSegment.AnimReference = poses->BoltActionInsertPose;
    newSegment.AnimEndTime = poses->BoltActionInsertPose->SequenceLength;
    newSegment.AnimStartTime = 0.f;
    newSegment.AnimPlayRate = 1.f;
    newSegment.StartPos = 0.f;
    newSegment.LoopingCount = 1;
    slotAim.AnimTrack.AnimSegments.Add(newSegment);

    SkeletalMeshArms->GetAnimInstance()->Montage_Play(montage);

    if (GetEquippedWeapon()->GetCurAmmo() != GetEquippedWeapon()->GetMaxAmmo() && !bBoltActionReloadStop)
    {
        FOnMontageEnded BlendOutDele;
        BlendOutDele.BindUObject(this, &ACharacterBase::OnBoltActionOpenBlendOut);
        SkeletalMeshArms->GetAnimInstance()->Montage_SetBlendingOutDelegate(BlendOutDele, montage);

        GetEquippedWeapon()->InsertBoltActionAmmo();
    }
    else
    {
        UWeaponPoseDA* poses2 = GetEquippedWeapon()->GetPosesDA();

        UAnimMontage* montage2 = UAnimMontage::CreateSlotAnimationAsDynamicMontage(poses->BoltActionClosePose, TEXT("Overlay Standing"), 0.f, 0.f, 1.f);

        FSlotAnimationTrack& slotAim2 = montage->AddSlot(TEXT("Overlay Aiming"));

        FAnimSegment newSegment2;

        StopAiming();
        newSegment2.AnimReference = poses2->BoltActionClosePose;
        newSegment2.AnimEndTime = poses2->BoltActionClosePose->SequenceLength;
        newSegment2.AnimStartTime = 0.f;
        newSegment2.AnimPlayRate = 1.f;
        newSegment2.StartPos = 0.f;
        newSegment2.LoopingCount = 1;
        slotAim2.AnimTrack.AnimSegments.Add(newSegment2);

        SkeletalMeshArms->GetAnimInstance()->Montage_Play(montage2);

        FOnMontageEnded BlendOutDele2;
        BlendOutDele2.BindUObject(this, &ACharacterBase::OnBoltActionCloseBlendOut);
        SkeletalMeshArms->GetAnimInstance()->Montage_SetBlendingOutDelegate(BlendOutDele2, montage2);
    }

}

void ACharacterBase::OnBoltActionCloseBlendOut(UAnimMontage* AnimMontage, bool bInterrupted)
{
    bPlayingMontageReloading = false;
    bBoltActionReloadStop = false;
}

bool ACharacterBase::IsBoltActionReloadStop()
{
    return bBoltActionReloadStop;
}
