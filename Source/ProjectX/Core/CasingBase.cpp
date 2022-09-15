// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/CasingBase.h"
#include "Utilities/Global.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/SceneComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Engine/StaticMesh.h"

// Sets default values
ACasingBase::ACasingBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Helpers::CreateComponent(this, &Pivot, TEXT("Pivot"));
	Helpers::CreateComponent(this, &Mesh, TEXT("Mesh"), Pivot);
	Helpers::CreateActorComponent(this, &ProjectileMovement, TEXT("Projectile Movement"));

	NO_OVERLAPEVENTS(Mesh);
	NO_STEPUPON(Mesh);
	NO_COLLISION(Mesh);

	Mesh->AddRelativeRotation(FRotator(0.f, 0.f, -180.f));

	ProjectileMovement->bUpdateOnlyIfRendered = true;

}

// Called when the game starts or when spawned
void ACasingBase::BeginPlay()
{
	Super::BeginPlay();

	RotationSpeedCurr = FMath::FRandRange(RotationSpeed, RotationSpeed * 2.f);
}

// Called every frame
void ACasingBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

    const float Rotation = DeltaTime * RotationSpeedCurr;
    Mesh->AddLocalRotation(FRotator(Rotation, Rotation, 0));

// 	Helpers::DrawGizmo(Pivot);

	if (GetGameTimeSinceCreation() >= LifeTime)
	{
		Destroy();
	}
}

void ACasingBase::ApplyImpulse(FVector Direction, const FVector Strength)
{
    Mesh->AddImpulse(Direction.Normalize() * Strength);
}

