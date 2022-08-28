// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/CasingBase.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "Runtime/Engine/Classes/Kismet/KismetMathLibrary.h"
#include "GameFramework/Character.h"
#include "GameFramework/ProjectileMovementComponent.h"

// Sets default values
ACasingBase::ACasingBase()
{
    // Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = true;
    //Simple root creation.
    Pivot = CreateDefaultSubobject<USceneComponent>(TEXT("Pivot"));
    RootComponent = Pivot;

    //Create casing mesh component.
    Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
    Mesh->SetupAttachment(Pivot);
    Mesh->AddRelativeRotation(FRotator(-90.f, 0.f, 0.f));

    ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovement"));
}


void ACasingBase::OnSpawn_Implementation()
{
    //We calculate the delay on spawn so that it works properly, as Begin Play is not getting called.
    DestroyDelay = UKismetMathLibrary::RandomFloatInRange(DestroyDelayRange.X, DestroyDelayRange.Y);
}

void ACasingBase::ApplyImpulse_Implementation(FVector Direction, const FVector Strength) const
{
    //Add impulse.
    Mesh->AddImpulse(Direction.Normalize() * Strength);
}

void ACasingBase::ApplyImpulse(FVector Direction, const FVector Strength)
{
    ProjectileMovement->Velocity = Direction * Strength;
}

void ACasingBase::BeginPlay()
{
    Super::BeginPlay();

    AttachToActor(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0), FAttachmentTransformRules::KeepWorldTransform);
    Mesh->SetScalarParameterValueOnMaterials(TEXT("Field Of View Alpha"), 1.0f);
    if (ShouldUpdateScale())
    {
        FTimerHandle waitHandle;
        float waitTime = 0.01f;
        GetWorld()->GetTimerManager().SetTimer(waitHandle, FTimerDelegate::CreateLambda([&]()
        {
            UKismetMathLibrary::VEase(FVector(1.f, 1.f, 1.f), FVector(0.f, 0.f, 0.f), GetGameTimeSinceCreation() / GetDestroyDelay(), EEasingFunc::Linear);
        }), waitTime, false);
    }
}

// Called every frame
void ACasingBase::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    //Rotate constantly.
    const float Rotation = DeltaTime * RotationSpeed;
    Mesh->AddLocalRotation(FRotator(Rotation, Rotation, 0));

    //Destroy.
    if (GetGameTimeSinceCreation() >= DestroyDelay)
    {
        //Play sound.
        UGameplayStatics::PlaySoundAtLocation(GetWorld(), Sound, GetActorLocation());

        //Destroy this actor.
        Destroy();
    }
}

