// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ProjectileBase.generated.h"

UCLASS()
class PROJECTZ_API AProjectileBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AProjectileBase();

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Proj | Default", meta=(AllowPrivateAccess = true))
	class UBoxComponent* CollisionBox;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Proj | Default", meta = (AllowPrivateAccess = true))
	class USceneComponent* UtilityRoot;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Proj | Default", meta = (AllowPrivateAccess = true))
    class UWidgetComponent* UtilityWidgetComponent;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Proj | Default", meta = (AllowPrivateAccess = true))
    class UArrowComponent* UtilityArrowComponent;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Proj | Default", meta = (AllowPrivateAccess = true))
    class USceneComponent* UtilityExplisionComponent;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Proj | Projectile", meta = (AllowPrivateAccess = true))
	class UStaticMeshComponent* ProjectileMesh;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Proj | Projectile", meta = (AllowPrivateAccess = true))
	class USpringArmComponent* CameraSpring;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Proj | Projectile", meta = (AllowPrivateAccess = true))
	class UChildActorComponent* CameraActor;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Proj | Audio", meta = (AllowPrivateAccess = true))
	class USceneComponent* AudioRoot;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Proj | Audio", meta = (AllowPrivateAccess = true))
	class UAudioComponent* AudioInit;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Proj | Audio", meta = (AllowPrivateAccess = true))
	class UAudioComponent* AudioLoop;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Proj | Particle", meta = (AllowPrivateAccess = true))
	class USceneComponent* ParticlesRoot;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Proj | Particle", meta = (AllowPrivateAccess = true))
	class UParticleSystemComponent* ParticlesTrail;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Proj | Particle", meta = (AllowPrivateAccess = true))
	class UProjectileMovementComponent* Projectile;


	void OnConstruction(const FTransform& Transform) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
