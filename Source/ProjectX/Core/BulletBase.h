// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BulletBase.generated.h"

class UBoxComponent;
class UStaticMeshComponent;
class UProjectileMovementComponent;
class USceneComponent;
class UParticleSystemComponent;

UCLASS()
class PROJECTX_API ABulletBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABulletBase();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Projx | Comp", meta = (AllowPrivateAccess = true))
	UBoxComponent* CollisionBox;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Projx | Comp", meta = (AllowPrivateAccess = true))
	UStaticMeshComponent* ProjectileMesh;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Projx | Comp", meta = (AllowPrivateAccess = true))
	USceneComponent* ParticlesRoot;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Projx | Comp", meta = (AllowPrivateAccess = true))
	UParticleSystemComponent* ParticlesTrail;

protected:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Projx | Comp", meta = (AllowPrivateAccess = true))
	UProjectileMovementComponent* Projectile;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
	void OnLaunch(bool bCinematic, FVector Velocity);

	UFUNCTION(BlueprintNativeEvent, Category = "Collision")
	void HitCheck(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	void PostInitializeComponents() override;

	TSubclassOf<AActor> DamageTextClass;
	class UMaterialInstanceConstant* WallDecalMaterial;
};
