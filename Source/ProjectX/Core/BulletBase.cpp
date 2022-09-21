// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/BulletBase.h"
#include "Utilities/Global.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "Components/SceneComponent.h"

// Sets default values
ABulletBase::ABulletBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Helpers::CreateComponent(this, &CollisionBox, TEXT("Collision Box"));
	Helpers::CreateComponent(this, &ProjectileMesh, TEXT("Projectile Mesh"), CollisionBox);
	Helpers::CreateComponent(this, &ParticlesRoot, TEXT("Particles Root"), CollisionBox);
	Helpers::CreateComponent(this, &ParticlesTrail, TEXT("Particles Trail"), ParticlesRoot);

	Helpers::CreateActorComponent(this, &Projectile, TEXT("Projectile (Movement)"));

// 	ProjectileMesh->AddRelativeRotation(FRotator(0.f, -90.f, 0.f));

	CollisionBox->SetBoxExtent(FVector(1.f, 1.f, 1.f));
}

// Called when the game starts or when spawned
void ABulletBase::BeginPlay()
{
	Super::BeginPlay();
	SetLifeSpan(5.f);
}

// Called every frame
void ABulletBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

// 	Helpers::DrawGizmo(CollisionBox);
}

void ABulletBase::OnLaunch(bool bCinematic, FVector Velocity)
{
	Projectile->SetVelocityInLocalSpace(Velocity);
}

