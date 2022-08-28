// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/ProjectileBase.h"
#include "GameFramework/SpringArmComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SceneComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "Components/AudioComponent.h"
#include "Components/ChildActorComponent.h"
#include "Components/BoxComponent.h"
#include "Utilities/Global.h"
#include "Components/ArrowComponent.h"
#include "Components/WidgetComponent.h"
#include "Camera/CameraComponent.h"

// Sets default values
AProjectileBase::AProjectileBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Helpers::CreateComponent(this, &CollisionBox, TEXT("Collision Box"));
	Helpers::CreateComponent(this, &UtilityRoot, TEXT("Utility Root"), CollisionBox);
	Helpers::CreateComponent(this, &UtilityWidgetComponent, TEXT("Utility Widget Component"), UtilityRoot);
	Helpers::CreateComponent(this, &UtilityArrowComponent, TEXT("Utility Arrow Component"), UtilityRoot);
	Helpers::CreateComponent(this, &UtilityExplisionComponent, TEXT("Utility Explosion Component"), UtilityRoot);
	Helpers::CreateComponent(this, &ProjectileMesh, TEXT("Projectile Mesh"), CollisionBox);
	Helpers::CreateComponent(this, &CameraSpring, TEXT("Camera Spring"), ProjectileMesh);
	Helpers::CreateComponent(this, &CameraActor, TEXT("Camera Actor"), CameraSpring);
	Helpers::CreateComponent(this, &AudioRoot, TEXT("Audio Root"), CollisionBox);
	Helpers::CreateComponent(this, &AudioInit, TEXT("Audio Loop"), AudioRoot);
	Helpers::CreateComponent(this, &ParticlesRoot, TEXT("Particles Root"), CollisionBox);
	Helpers::CreateComponent(this, &ParticlesTrail, TEXT("Particles Trail"), ParticlesRoot);

	CollisionBox->SetBoxExtent(FVector(2.f, 2.f, 2.f));
	CollisionBox->CanCharacterStepUpOn = ECB_No;

	UtilityWidgetComponent->SetRelativeScale3D(FVector(0.15f, 0.15f, 0.15f));
	UtilityWidgetComponent->SetWidgetSpace(EWidgetSpace::Screen);
	UtilityWidgetComponent->SetGenerateOverlapEvents(false);
	UtilityWidgetComponent->CanCharacterStepUpOn = ECB_No;
	UtilityWidgetComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	UtilityArrowComponent->SetArrowColor(FLinearColor(FColor::Blue));
	UtilityArrowComponent->ArrowSize = 0.2f;
	UtilityArrowComponent->bIsEditorOnly = true;

	ProjectileMesh->SetGenerateOverlapEvents(false);
	ProjectileMesh->CanCharacterStepUpOn = ECB_No;
	ProjectileMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	CameraSpring->bEnableCameraLag = true;
	CameraSpring->bEnableCameraRotationLag = true;
	CameraSpring->CameraLagSpeed = 25.f;
	CameraSpring->CameraRotationLagSpeed = 5.f;

	CameraActor->SetChildActorClass(UCameraComponent::StaticClass());
	CameraActor->CreateChildActor();
}

void AProjectileBase::OnConstruction(const FTransform& Transform)
{
    Super::OnConstruction(Transform);

	ParticlesTrail->SetVisibility(false);
	UtilityRoot->SetWorldRotation(FRotator(0.f, 0.f, 0.f));
}

// Called when the game starts or when spawned
void AProjectileBase::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AProjectileBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);


}

