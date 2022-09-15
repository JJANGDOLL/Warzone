// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CasingBase.generated.h"

class USceneComponent;
class UStaticMeshComponent;
class UProjectileMovementComponent;

UCLASS()
class PROJECTX_API ACasingBase : public AActor
{
	GENERATED_BODY()
	
public:	
	ACasingBase();

protected:
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Low Poly Shooter Pack")
    USceneComponent* Pivot;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Low Poly Shooter Pack")
    UStaticMeshComponent* Mesh;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Low Poly Shooter Pack")
	UProjectileMovementComponent* ProjectileMovement;

protected:
    float RotationSpeed = 2500.0f;
	float RotationSpeedCurr;
	float LifeTime = 0.5f;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
	virtual void ApplyImpulse(FVector Direction, const FVector Strength);
};
