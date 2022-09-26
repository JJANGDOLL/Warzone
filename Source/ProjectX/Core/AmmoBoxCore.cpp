// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/AmmoBoxCore.h"
#include "Utilities/Global.h"
#include "Engine/StaticMesh.h"
#include "Components/StaticMeshComponent.h"
#include "AC_Inventory.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Character.h"

// Sets default values
AAmmoBoxCore::AAmmoBoxCore()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Helpers::CreateComponent(this, &Bottom, TEXT("Box"));
	Helpers::CreateComponent(this, &Top, TEXT("Top"), Bottom);

	UStaticMesh* bottomMesh;
	Helpers::GetAsset(&bottomMesh, TEXT("StaticMesh'/Game/InfimaGames/LowPolyShooterPack/Art/Environment/Objects/Misc/SM_Box_Ammo.SM_Box_Ammo'"));
	Bottom->SetStaticMesh(bottomMesh);
	Bottom->SetGenerateOverlapEvents(true);
	Bottom->SetCollisionProfileName(TEXT("InteractObject"));

    UStaticMesh* topMesh;
    Helpers::GetAsset(&topMesh, TEXT("StaticMesh'/Game/InfimaGames/LowPolyShooterPack/Art/Environment/Objects/Misc/SM_Box_Ammo_Lid.SM_Box_Ammo_Lid'"));
	Top->SetStaticMesh(topMesh);
	Top->AddRelativeLocation(FVector(0.f, 0.f, 15.f));
	Top->SetGenerateOverlapEvents(true);
	Top->SetCollisionProfileName(TEXT("InteractObject"));
}

// Called when the game starts or when spawned
void AAmmoBoxCore::BeginPlay()
{
	Super::BeginPlay();

	SetAmmoType();
	SetDescriptionText();
}

// Called every frame
void AAmmoBoxCore::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AAmmoBoxCore::Action()
{
    UAC_Inventory* inventory = Helpers::GetComponent<UAC_Inventory>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
    inventory->SetMaxAmmo(AmmoType);
}

FText AAmmoBoxCore::Description()
{
	return DescriptionText;
}

