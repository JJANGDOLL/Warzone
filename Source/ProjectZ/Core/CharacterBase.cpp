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
	Helpers::CreateComponent(this, &SMeshHelment, TEXT("SMesh Helmet"), RootCosmetics);
	Helpers::CreateComponent(this, &SMeshHeadset, TEXT("SMesh Headset"), RootCosmetics);
	Helpers::CreateComponent(this, &Camera, TEXT("Camera"), SkeletalMeshArms, TEXT("SOCKET_Camera"));
	// Inventory;
	Helpers::CreateComponent(this, &ReplicatedCharacter, TEXT("Replicated Character"), GetMesh());
	Helpers::CreateComponent(this, &ReplicatedHeadSocket, TEXT("Replicated Head Socket"), ReplicatedCharacter, TEXT("SOCKET_Head"));
	Helpers::CreateComponent(this, &Helmet, TEXT("Helmet"), ReplicatedHeadSocket);
	Helpers::CreateComponent(this, &Headset, TEXT("Headset"), Helmet);
	Helpers::CreateComponent(this, &Googles, TEXT("Googgles"), Helmet);
	Helpers::CreateComponent(this, &BackpackSocket, TEXT("Backpack Socket"), ReplicatedCharacter, TEXT("SOCKET_Back"));
	Helpers::CreateComponent(this, &BackpackMesh, TEXT("Backpack Mesh"), BackpackSocket);
	Helpers::CreateComponent(this, &BackpackMeshRocket01, TEXT("Backpack Mesh Rocket 01"));
	Helpers::CreateComponent(this, &BackpackmeshRocket02, TEXT("Backpack Mesh Rocket 02"));

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

	NO_OVERLAPEVENTS(SMeshGoggles);
	NO_STEPUPON(SMeshGoggles);
	NO_COLLISION(SMeshGoggles);

	UStaticMesh* meshHelmet;
	Helpers::GetAsset(&meshHelmet, TEXT("StaticMesh'/Game/InfimaGames/LowPolyShooterPack/Art/Characters/Default/SM_CH_Helmet.SM_CH_Helmet'"));
	SMeshHelment->SetStaticMesh(meshHelmet);

	NO_OVERLAPEVENTS(SMeshHelment);
	NO_STEPUPON(SMeshHelment);
	NO_COLLISION(SMeshHelment);

	UStaticMesh* meshHeadset;
	Helpers::GetAsset(&meshHeadset, TEXT("StaticMesh'/Game/InfimaGames/LowPolyShooterPack/Art/Characters/Default/SM_CH_Headset.SM_CH_Headset'"));
	SMeshHeadset->SetStaticMesh(meshHeadset);

	NO_OVERLAPEVENTS(SMeshHeadset);
	NO_STEPUPON(SMeshHeadset);
	NO_COLLISION(SMeshHeadset);


}

// Called when the game starts or when spawned
void ACharacterBase::BeginPlay()
{
	Super::BeginPlay();
	
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
	SpringArm->SetRelativeLocation(GetViewLocation());
}

FVector ACharacterBase::GetViewLocation()
{
	return FirstPersonViewOffset + FVector(0.f, 0.f, GetCapsuleComponent()->GetScaledCapsuleHalfHeight());
}


