// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Objects/TurretBase.h"
#include "Core/Interfaces/IDamageable.h"
#include "SampleTurret.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTX_API ASampleTurret : public ATurretBase, public IIDamageable
{
	GENERATED_BODY()
	
public:
	ASampleTurret();


	float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;


	void Tick(float DeltaTime) override;


	void Hitted(float Damage, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, class AActor* DamageCauser) override;

	void Attack();
    void SpawnBullet();

	FTimerHandle AttackHandler;
	FTimerHandle SpawnHandler;

public:
	UStaticMeshComponent* BaseMesh;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Projx | Comp", meta = (AllowPrivateAccess = true))
    class UWidgetComponent* StatusWidgetComp;

    class UEnemyStatus* StatusWidget;

protected:
	void BeginPlay() override;

private:
    class ACharacter* PlayerCharacter;

	float MaxHealth = 100;
	float CurrentHealth = 100;

	class UParticleSystem* ExplodeParticle;

	uint8 bulletCount = 0;
};
