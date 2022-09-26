// Fill out your copyright notice in the Description page of Project Settings.


#include "Objects/Target_Hanged.h"
#include "Utilities/Global.h"

// Sets default values
ATarget_Hanged::ATarget_Hanged()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Helpers::CreateComponent(this, &Target, TEXT("Target"));
	UStaticMesh* mesh;

	Helpers::GetAsset(&mesh, TEXT("StaticMesh'/Game/ShootingRange/Meshes/SM_Target_1.SM_Target_1'"));
	Target->SetStaticMesh(mesh);

    Target->SetCollisionProfileName(TEXT("Body"));
    Target->SetGenerateOverlapEvents(true);
}

void ATarget_Hanged::Hitted(UPrimitiveComponent* Comp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	PrintLine();
}

// Called when the game starts or when spawned
void ATarget_Hanged::BeginPlay()
{


	Super::BeginPlay();
	
}

// Called every frame
void ATarget_Hanged::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ATarget_Hanged::PostInitializeComponents()
{
    Super::PostInitializeComponents();

    Target->OnComponentBeginOverlap.AddDynamic(this, &ATarget_Hanged::Hitted);

}

