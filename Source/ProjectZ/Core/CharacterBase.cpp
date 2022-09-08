// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/CharacterBase.h"
#include "GameFramework/SpringArmComponent.h"

#include "Utilities/Global.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/SceneComponent.h"
#include "Camera/CameraComponent.h"
#include "Animation/AnimInstance.h"
#include "Components/CapsuleComponent.h"
#include "Engine/StaticMesh.h"
#include "Components/SC_Inventory.h"
#include "Materials/MaterialInstanceConstant.h"
#include "MovieSceneSequencePlayer.h"
#include "LevelSequence.h"
#include "LevelSequenceActor.h"
#include "LevelSequencePlayer.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/TimelineComponent.h"
#include "Blueprint/UserWidget.h"
#include "GameInstanceBase.h"
#include "BlueprintGameplayTagLibrary.h"
#include "Curves/CurveVector.h"
#include "Curves/CurveFloat.h"
#include "Components/Widget.h"

// Sets default values
ACharacterBase::ACharacterBase()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Helpers::CreateComponent(this, &SpringArm, TEXT("Spring Arm"), GetMesh());
	Helpers::CreateComponent(this, &SkeletalMeshArms, TEXT("Skeletal Mesh Arms"), SpringArm);
	Helpers::CreateComponent(this, &SocketHandLeft, TEXT("Socket Hand Left"), SkeletalMeshArms, TEXT("SOCKET_Weapon_L"));
	Helpers::CreateComponent(this, &SMeshKnife, TEXT("SMesh Knife"), SocketHandLeft);
	Helpers::CreateComponent(this, &SocketHandRight, TEXT("SOCKET Hand Right"), SkeletalMeshArms, TEXT("SOCKET_Weapon_R"));
	Helpers::CreateComponent(this, &RootCosmetics, TEXT("Root Cosmetics"), SkeletalMeshArms);
	Helpers::CreateComponent(this, &SMeshGoggles, TEXT("SMesh Goggles"), RootCosmetics);
	Helpers::CreateComponent(this, &SMeshHelmet, TEXT("SMesh Helmet"), RootCosmetics);
	Helpers::CreateComponent(this, &SMeshHeadset, TEXT("SMesh Headset"), RootCosmetics);
	Helpers::CreateComponent(this, &Camera, TEXT("Camera"), SkeletalMeshArms, TEXT("SOCKET_Camera"));
	Helpers::CreateComponent(this, &Inventory, TEXT("Inventory"), SkeletalMeshArms, TEXT("SOCKET_Weapon"));
	Helpers::CreateComponent(this, &ReplicatedCharacter, TEXT("Replicated Character"), GetMesh());
	Helpers::CreateComponent(this, &ReplicatedHeadSocket, TEXT("Replicated Head Socket"), ReplicatedCharacter, TEXT("SOCKET_Head"));
	Helpers::CreateComponent(this, &Helmet, TEXT("Helmet"), ReplicatedHeadSocket);
	Helpers::CreateComponent(this, &Headset, TEXT("Headset"), Helmet);
	Helpers::CreateComponent(this, &Googles, TEXT("Googgles"), Helmet);
	Helpers::CreateComponent(this, &BackpackSocket, TEXT("Backpack Socket"), ReplicatedCharacter, TEXT("SOCKET_Back"));
	Helpers::CreateComponent(this, &BackpackMesh, TEXT("Backpack Mesh"), BackpackSocket);
	Helpers::CreateComponent(this, &BackpackMeshRocket01, TEXT("Backpack Mesh Rocket 01"), BackpackMesh);
	Helpers::CreateComponent(this, &BackpackmeshRocket02, TEXT("Backpack Mesh Rocket 02"), BackpackMesh);

	// init

	SpringArm->TargetArmLength = 0;
	SpringArm->bDoCollisionTest = false;

	SkeletalMeshArms->AddRelativeLocation(FVector(0.f, 0.f, -165.51f));
	SkeletalMeshArms->AddRelativeRotation(FRotator(0.f, -90.f, 0.f));

	USkeletalMesh* meshArm;
	Helpers::GetAsset(&meshArm, TEXT("SkeletalMesh'/Game/InfimaGames/LowPolyShooterPack/Art/Characters/Default/SK_FP_CH_Default.SK_FP_CH_Default'"));
	SkeletalMeshArms->SetSkeletalMesh(meshArm);

	TSubclassOf<UAnimInstance> animInst;
	Helpers::GetClass(&animInst, TEXT("AnimBlueprint'/Game/InfimaGames/LowPolyShooterPack/Core/Characters/ABP_LPSP_FP_PCH.ABP_LPSP_FP_PCH_C'"));
	SkeletalMeshArms->SetAnimInstanceClass(animInst);

	UStaticMesh* meshKnife;
	Helpers::GetAsset(&meshKnife, TEXT("StaticMesh'/Game/InfimaGames/AnimatedLowPolyWeapons/Art/Weapons/Melee/SM_Knife_01.SM_Knife_01'"));
	SMeshKnife->SetStaticMesh(meshKnife);

	NO_OVERLAPEVENTS(SMeshKnife);
	NO_STEPUPON(SMeshKnife);
	NO_COLLISION(SMeshKnife);

	UStaticMesh* meshGoggle;
	Helpers::GetAsset(&meshGoggle, TEXT("StaticMesh'/Game/InfimaGames/LowPolyShooterPack/Art/Characters/Default/SM_FP_CH_Goggles.SM_FP_CH_Goggles'"));
	SMeshGoggles->SetStaticMesh(meshGoggle);
	SMeshGoggles->AddRelativeLocation(FVector(-23.7f, 0, -5.2f));
	SMeshGoggles->AddRelativeRotation(FRotator(0.f, -90.f, 0));

	NO_OVERLAPEVENTS(SMeshGoggles);
	NO_STEPUPON(SMeshGoggles);
	NO_COLLISION(SMeshGoggles);

	UStaticMesh* meshHelmet;
	Helpers::GetAsset(&meshHelmet, TEXT("StaticMesh'/Game/InfimaGames/LowPolyShooterPack/Art/Characters/Default/SM_CH_Helmet.SM_CH_Helmet'"));
	SMeshHelmet->SetStaticMesh(meshHelmet);
	SMeshHelmet->AddRelativeLocation(FVector(-23.4f, 0.f, 0.26f));
	SMeshHelmet->AddRelativeRotation(FRotator(0.f, -90.f, -8.f));

	NO_OVERLAPEVENTS(SMeshHelmet);
	NO_STEPUPON(SMeshHelmet);
	NO_COLLISION(SMeshHelmet);

	UStaticMesh* meshHeadset;
	Helpers::GetAsset(&meshHeadset, TEXT("StaticMesh'/Game/InfimaGames/LowPolyShooterPack/Art/Characters/Default/SM_CH_Headset.SM_CH_Headset'"));
	SMeshHeadset->SetStaticMesh(meshHeadset);
	SMeshHeadset->AddRelativeLocation(FVector(-23.6f, 0.3f, 3.1f));
	SMeshHeadset->AddRelativeRotation(FRotator(15.1f, -90.f, -16.f));

	NO_OVERLAPEVENTS(SMeshHeadset);
	NO_STEPUPON(SMeshHeadset);
	NO_COLLISION(SMeshHeadset);

	USkeletalMesh* replicatedMesh;
	Helpers::GetAsset(&replicatedMesh, TEXT("SkeletalMesh'/Game/InfimaGames/LowPolyShooterPack/Art/Characters/Default/SK_TP_CH_Default.SK_TP_CH_Default'"));
	ReplicatedCharacter->SetSkeletalMesh(replicatedMesh);
	ReplicatedCharacter->AddRelativeLocation(FVector(0.f, 0.f, -95.f));
	ReplicatedCharacter->AddRelativeRotation(FRotator(0.f, -90.f, 0.f));

    TSubclassOf<UAnimInstance> repliAnimInst;
    Helpers::GetClass(&repliAnimInst, TEXT("AnimBlueprint'/Game/InfimaGames/LowPolyShooterPack/Core/Characters/ABP_LPSP_TP_PCH.ABP_LPSP_TP_PCH_C'"));
	ReplicatedCharacter->SetAnimInstanceClass(repliAnimInst);

	Helmet->SetStaticMesh(meshHelmet);
	NO_OVERLAPEVENTS(Helmet);
	NO_STEPUPON(Helmet);
	NO_COLLISION(Helmet);

	Headset->SetStaticMesh(meshHeadset);
	NO_OVERLAPEVENTS(Headset);
	NO_STEPUPON(Headset);
	NO_COLLISION(Headset);

	Googles->SetStaticMesh(meshGoggle);
    NO_OVERLAPEVENTS(Googles);
    NO_STEPUPON(Googles);
    NO_COLLISION(Googles);

	UStaticMesh* meshBackpack;
	Helpers::GetAsset(&meshBackpack, TEXT("StaticMesh'/Game/InfimaGames/LowPolyShooterPack/Art/Characters/Default/SM_TP_Backpack.SM_TP_Backpack'"));
	BackpackMesh->SetStaticMesh(meshBackpack);
    NO_OVERLAPEVENTS(BackpackMesh);
    NO_STEPUPON(BackpackMesh);
    NO_COLLISION(BackpackMesh);

	UStaticMesh* meshRL;
	Helpers::GetAsset(&meshRL, TEXT("StaticMesh'/Game/InfimaGames/AnimatedLowPolyWeapons/Art/Weapons/Launchers/SM_RL_01_Projectile_Default.SM_RL_01_Projectile_Default'"));
	BackpackMeshRocket01->SetStaticMesh(meshRL);
	BackpackMeshRocket01->AddRelativeLocation(FVector(6.3f, -17.f, 22.3f));
	BackpackMeshRocket01->AddRelativeRotation(FRotator(-15.6f, 7.07f, -134.7f));
    NO_OVERLAPEVENTS(BackpackMeshRocket01);
    NO_STEPUPON(BackpackMeshRocket01);
    NO_COLLISION(BackpackMeshRocket01);

	BackpackmeshRocket02->SetStaticMesh(meshRL);
	BackpackmeshRocket02->AddRelativeLocation(FVector(1.43f, -10.3f, 18.64f));
	BackpackmeshRocket02->AddRelativeRotation(FRotator(2.99f, -13.06f, -130.4f));
    NO_OVERLAPEVENTS(BackpackmeshRocket02);
    NO_STEPUPON(BackpackmeshRocket02);
    NO_COLLISION(BackpackmeshRocket02);

	// 
	Helpers::GetAsset(&CharacterMaterial, TEXT("MaterialInstanceConstant'/Game/InfimaGames/LowPolyShooterPack/Art/Characters/Default/Skins/Materials/MI_CH_Camo_Digital_011_001.MI_CH_Camo_Digital_011_001'"));

    Helpers::CreateActorComponent(this, &TLineViewmodelFall, TEXT("TLine Viewmodel Fall"));
    Helpers::CreateActorComponent(this, &TLineViewmodelLand, TEXT("TLine Viewmodel Land"));
    Helpers::CreateActorComponent(this, &TLineCameraJump, TEXT("TLine Camera Jump"));
    Helpers::CreateActorComponent(this, &TLineCameraLand, TEXT("TLine Camera Land"));
    Helpers::CreateActorComponent(this, &TLineViewmodelJump, TEXT("TLine Viewmodel Jump"));
    Helpers::CreateActorComponent(this, &TLineResetCamera, TEXT("TLine Reset Camera"));

	UCurveFloat* cameraResetCurve;
	Helpers::GetAsset(&cameraResetCurve, TEXT("CurveFloat'/Game/InfimaGames/LowPolyShooterPack/Data/Curves/FC_LPSP_Camera_Reset.FC_LPSP_Camera_Reset'"));
	TLineResetCamera->AddInterpFloat(cameraResetCurve, ResetCameraFunc, NAME_None, TEXT("Alpha"));

	SettingsCameraUnlocking.Enabled = true;
	SettingsCameraUnlocking.DisableWeaponLagLooking = true;
	SettingsCameraUnlocking.CameraInterpolationSpeed = 25.f;
	SettingsCameraUnlocking.CameraClamps.ClampsYaw = FVector2D(-60.f, 60.f);
	SettingsCameraUnlocking.CameraClamps.ClampsPitch = FVector2D(-20.f, 85.f);
	SettingsCameraUnlocking.CameraResetTimeline.FloatTrackName = TEXT("Alpha");
	Helpers::GetAsset(&SettingsCameraUnlocking.CameraResetTimeline.FloatCurve, TEXT("CurveFloat'/Game/InfimaGames/LowPolyShooterPack/Data/Curves/FC_LPSP_Camera_Reset.FC_LPSP_Camera_Reset'"));


	ViewmodelJumpLocationCurve.VectorTrackName = TEXT("Location");
	Helpers::GetAsset(&ViewmodelJumpLocationCurve.VectorCurve, TEXT("CurveVector'/Game/InfimaGames/LowPolyShooterPack/Data/Curves/Animation/VC_LPSP_FP_PCH_Jump_Location.VC_LPSP_FP_PCH_Jump_Location'"));

	ViewmodelJumpRotationCurve.VectorTrackName = TEXT("Rotation");
    Helpers::GetAsset(&ViewmodelJumpRotationCurve.VectorCurve, TEXT("CurveVector'/Game/InfimaGames/LowPolyShooterPack/Data/Curves/Animation/VC_LPSP_FP_PCH_Jump_Rotation.VC_LPSP_FP_PCH_Jump_Rotation'"));

	ViewmodelLandLocationCurve.VectorTrackName = TEXT("Location");
    Helpers::GetAsset(&ViewmodelLandLocationCurve.VectorCurve, TEXT("CurveVector'/Game/InfimaGames/LowPolyShooterPack/Data/Curves/Animation/VC_LPSP_FP_PCH_Land_Location.VC_LPSP_FP_PCH_Land_Location'"));

	ViewmodelLandRotationCurve.VectorTrackName = TEXT("Rotation");
    Helpers::GetAsset(&ViewmodelLandRotationCurve.VectorCurve, TEXT("CurveVector'/Game/InfimaGames/LowPolyShooterPack/Data/Curves/Animation/VC_LPSP_FP_PCH_Land_Rotation.VC_LPSP_FP_PCH_Land_Rotation'"));

	ViewmodelFallLocationCurve.VectorTrackName = TEXT("Location");
    Helpers::GetAsset(&ViewmodelFallLocationCurve.VectorCurve, TEXT("CurveVector'/Game/InfimaGames/LowPolyShooterPack/Data/Curves/Animation/VC_LPSP_FP_PCH_Fall_Location.VC_LPSP_FP_PCH_Fall_Location'"));

	ViewmodelFallRotationCurve.VectorTrackName = TEXT("Rotation");
    Helpers::GetAsset(&ViewmodelFallRotationCurve.VectorCurve, TEXT("CurveVector'/Game/InfimaGames/LowPolyShooterPack/Data/Curves/Animation/VC_LPSP_FP_PCH_Fall_Rotation.VC_LPSP_FP_PCH_Fall_Rotation'"));

	CameraJumpRotationCurve.VectorTrackName = TEXT("Rotation");
    Helpers::GetAsset(&CameraJumpRotationCurve.VectorCurve, TEXT("CurveVector'/Game/InfimaGames/LowPolyShooterPack/Data/Curves/Animation/VC_LPSP_FP_PCH_Jump_Rotation_Camera.VC_LPSP_FP_PCH_Jump_Rotation_Camera'"));

	CameraLandRotationJump.VectorTrackName = TEXT("Rotation");
    Helpers::GetAsset(&CameraLandRotationJump.VectorCurve, TEXT("CurveVector'/Game/InfimaGames/LowPolyShooterPack/Data/Curves/Animation/VC_LPSP_FP_PCH_Land_Rotation_Camera.VC_LPSP_FP_PCH_Land_Rotation_Camera'"));


    UCurveVector* initVectorCurve;
    Helpers::GetAsset(&initVectorCurve, TEXT("CurveVector'/Game/Projz/Curve/InitVector.InitVector'"));
	TLineViewmodelFall->AddInterpVector(initVectorCurve, TLineViewmodelFallFunc, NAME_None, TEXT("Location"));
    TLineViewmodelFall->AddInterpVector(initVectorCurve, TLineViewmodelFallFunc, NAME_None, TEXT("Rotation"));
	TLineViewmodelLand->AddInterpVector(initVectorCurve, TLineViewmodelLandFunc, NAME_None, TEXT("Location"));
    TLineViewmodelLand->AddInterpVector(initVectorCurve, TLineViewmodelLandFunc, NAME_None, TEXT("Rotation"));
    TLineViewmodelJump->AddInterpVector(initVectorCurve, TLineViewmodelJumpFunc, NAME_None, TEXT("Location"));
	TLineViewmodelJump->AddInterpVector(initVectorCurve, TLineViewmodelJumpFunc, NAME_None, TEXT("Rotation"));
	TLineCameraJump->AddInterpVector(initVectorCurve, TLineCameraJumpFunc, NAME_None, TEXT("Rotation"));
    TLineCameraLand->AddInterpVector(initVectorCurve, TLineCameraLandFunc, NAME_None, TEXT("Rotation"));

	
	Helpers::GetClass(&WidgetClassInterface, TEXT("WidgetBlueprint'/Game/InfimaGames/LowPolyShooterPack/Core/Widgets/WBP_LPSP_Interface.WBP_LPSP_Interface_C'"));

	ReplicatedCharacter->SetVisibility(false, true);

	SMeshGoggles->SetVisibility(false);
	SMeshHelmet->SetVisibility(false);
	SMeshHeadset->SetVisibility(false);

	Helmet->SetVisibility(false);
	Headset->SetVisibility(false);
	Googles->SetVisibility(false);

	BackpackMesh->SetVisibility(false);

	FieldOfViewDefault = 120.f;
	FieldOfViewMultiplierRunning = 1.06f;
}

int32 ACharacterBase::GetFieldOfView()
{
// 	if (GameInstance)
// 	{
// 
// 	}

	return FieldOfViewDefault;
}

bool ACharacterBase::IsAiming()
{
	return bAiming;
}

bool ACharacterBase::IsRunning()
{
	return bRunning;
}

class UCameraComponent* ACharacterBase::GetCameraComponent()
{
	return Camera != nullptr ? Camera : nullptr;
}

FVector2D ACharacterBase::GetInputLook()
{
	return Look;
}

FVector2D ACharacterBase::GetInputMovement()
{
	return Movement;
}

void ACharacterBase::OnPickUp()
{
	if (!HitResultInteractionTrace.GetActor())
		return;

	Inventory->EventServerTryPickupItem(HitResultInteractionTrace.GetActor());
}

bool ACharacterBase::TryStartAbility(FSGameAbility Ability)
{
	return TryStartGameAbility(Ability, AbilityTags);
}

bool ACharacterBase::TryStartGameAbility(FSGameAbility Ability, FGameplayTagContainer Container)
{
	if (CanStartGameAbility(Ability, Container, GetWorld()))
	{
		StartGameAbility(Ability, Container, GetWorld());

		return true;
	}

	return false;
}

bool ACharacterBase::CanStartGameAbility(FSGameAbility Ability, FGameplayTagContainer Container, UWorld* World)
{
	if (UBlueprintGameplayTagLibrary::HasAllTags(Container, Ability.TagsRequired, true) == false)
	{
		return false;
	}
	if (UBlueprintGameplayTagLibrary::HasAnyTags(Container, Ability.TagsRequired, true) == false)
	{
		return true;
	}

	return false;
}

void ACharacterBase::StartGameAbility(FSGameAbility Ability, FGameplayTagContainer Container, UWorld* World)
{
	UBlueprintGameplayTagLibrary::AppendGameplayTagContainers(Container, Ability.TagsAdded);
	RemoveGameplayTagContainer(Container, Ability.TagsRemoved, GetWorld());
}

void ACharacterBase::RemoveGameplayTagContainer(FGameplayTagContainer A, FGameplayTagContainer B, UWorld* World)
{
	TArray<FGameplayTag> tagIter;
	UBlueprintGameplayTagLibrary::BreakGameplayTagContainer(B, tagIter);
	for (auto& elem : tagIter)
	{
		UBlueprintGameplayTagLibrary::RemoveGameplayTag(A, elem);
	}
}

// Called when the game starts or when spawned
void ACharacterBase::BeginPlay()
{
	Super::BeginPlay();
	
	ULevelSequence* fadeInSeq;
    Helpers::GetAssetDynamic<ULevelSequence>(&fadeInSeq, TEXT("LevelSequence'/Game/InfimaGames/LowPolyShooterPack/Data/Sequences/LS_Fade_Level.LS_Fade_Level'"));
    FMovieSceneSequencePlaybackSettings fmovieSeqSet;
    ALevelSequenceActor* outActor;
    ULevelSequencePlayer* levelSeqPlayer = ULevelSequencePlayer::CreateLevelSequencePlayer(GetWorld(), fadeInSeq, FMovieSceneSequencePlaybackSettings::FMovieSceneSequencePlaybackSettings(), outActor);
    levelSeqPlayer->Play();

	GetCharacterMovement()->MaxFlySpeed = FreeLookFlySpeed;

	CurrentControlRotationInterpSpeed = ControlRotationInterpSpeed;

	TrySetFieldOfViewAlph(1.f);

	SetUpMappingContext();
	Inventory->AttachToComponent(SkeletalMeshArms, FAttachmentTransformRules::SnapToTargetIncludingScale, TEXT("SOCKET_Weapon"));

	AmmunitionPoolCurrent = AmmunitionPoolStarting;
	
	SetUpAllTimelineCurves();

	CalculatePlayRates();

	CacheGInstance();

	AddWidgetstoViewport();
}

// Called every frame
void ACharacterBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ACharacterBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ACharacterBase::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);

	SpringArm->SetRelativeLocation(GetViewLocation());

	UpdateHeadgearVisibility();

	SkeletalMeshArms->SetMaterial(0, CharacterMaterial);

	SocketHandLeft->SetVisibility(false, true);

	FRotator camRot = SkeletalMeshArms->GetSocketRotation(TEXT("SOCKET_Camera"));
	RootCosmetics->SetWorldRotation(FRotator(camRot.Yaw - 90.0f, camRot.Roll, camRot.Pitch));
	RootCosmetics->SetWorldLocation(SkeletalMeshArms->GetSocketLocation(TEXT("SOCKET_Camera")));

	if (bLeftHandMode)
		SkeletalMeshArms->SetWorldScale3D(FVector(-1.f, 1.f, 1.f));
}

FVector ACharacterBase::GetViewLocation()
{
	return FirstPersonViewOffset + FVector(0.f, 0.f, GetCapsuleComponent()->GetScaledCapsuleHalfHeight());
}

void ACharacterBase::UpdateHeadgearVisibility()
{
	SMeshHelmet->SetVisibility(bShowHelmet, true);
	SMeshHeadset->SetVisibility(bShowHeadset, true);
	SMeshGoggles->SetVisibility(bShowGoggles, true);
}

void ACharacterBase::TrySetFieldOfViewAlph(float Alpha)
{
	//Check Local

	SkeletalMeshArms->SetScalarParameterValueOnMaterials(TEXT("Field Of View Alpha"), Alpha);
	SMeshKnife->SetScalarParameterValueOnMaterials(TEXT("Field Of View Alpha"), Alpha);
}

void ACharacterBase::SetUpMappingContext()
{
	// Enhanced Input
// 	UGameplayStatics::GetPlayerController(GetWorld(), 0);
}

void ACharacterBase::SetUpAllTimelineCurves()
{
	PrintLine();

	SetUpCurveFloat(TLineResetCamera, SettingsCameraUnlocking.CameraResetTimeline);

	SetUpCurveVector(TLineViewmodelJump, ViewmodelJumpLocationCurve);
	SetUpCurveVector(TLineViewmodelJump, ViewmodelJumpRotationCurve);
	SetUpCurveVector(TLineViewmodelLand, ViewmodelLandLocationCurve);
	SetUpCurveVector(TLineViewmodelLand, ViewmodelLandRotationCurve);
	SetUpCurveVector(TLineViewmodelFall, ViewmodelFallLocationCurve);
	SetUpCurveVector(TLineViewmodelFall, ViewmodelFallRotationCurve);
	SetUpCurveVector(TLineCameraJump, CameraJumpRotationCurve);
	SetUpCurveVector(TLineCameraLand, CameraLandRotationJump);

    PrintLine();

}

void ACharacterBase::SetUpCurveFloat(UTimelineComponent* TimelineComponent, FSCurveFloat Curve)
{
	TimelineComponent->SetFloatCurve(Curve.FloatCurve, Curve.FloatTrackName);
	TimelineComponent->SetTimelineLengthMode(TL_LastKeyFrame);
}

void ACharacterBase::SetUpCurveVector(class UTimelineComponent* TimelineComponent, FSCurveVector Curve)
{
	TimelineComponent->SetVectorCurve(Curve.VectorCurve, Curve.VectorTrackName);
    TimelineComponent->SetTimelineLengthMode(TL_LastKeyFrame);
}

void ACharacterBase::CalculatePlayRates()
{
	MontagePlayRateMeleeAttak = FMath::FRandRange(MontagePlayRateRangeMeleeAttack.X, MontagePlayRateRangeMeleeAttack.Y);
	MontagePlayRateGrenadeThrow = FMath::FRandRange(MontagePlayRateRangeGrenadeThrow.X, MontagePlayRateRangeGrenadeThrow.Y);
	MontagePlayRateFire = FMath::FRandRange(MontagePlayRateRangeFire.X, MontagePlayRateRangeFire.Y);
}

void ACharacterBase::CacheGInstance()
{
	GameInstance = Cast<UGameInstanceBase>(UGameplayStatics::GetGameInstance(GetWorld()));
}

void ACharacterBase::AddWidgetstoViewport()
{
	UUserWidget* widget = CreateWidget(UGameplayStatics::GetPlayerController(GetWorld(), 0), WidgetClassInterface);

	if (widget)
		widget->AddToViewport();
}

AActor* ACharacterBase::GetEquippedItem()
{
	PrintLine();

	Logger::Log(Inventory->GetEquipped());

	return Inventory->GetEquipped();
}

int32 ACharacterBase::GetFieldOfViewRunning()
{
	return GetFieldOfView() * FieldOfViewMultiplierRunning;
}

float ACharacterBase::GetAimDuration()
{
	return GetAimSpeedMultiplier();
}

float ACharacterBase::GetAimSpeedMultiplier()
{
	return WeaponSettingsScope.MultiplierAimingSpeed;
}

