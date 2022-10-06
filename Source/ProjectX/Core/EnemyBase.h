// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Interfaces/IDamageable.h"
#include "EnemyBase.generated.h"

class UEnemyStatus;
class UWidgetComponent;

UCLASS()
class PROJECTX_API AEnemyBase : public ACharacter, public IIDamageable
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AEnemyBase();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Projx | Comp", meta = (AllowPrivateAccess = true))
	UWidgetComponent* StatusWidgetComp;

	UEnemyStatus* StatusWidget;

	UPROPERTY(EditAnywhere, Category = "Projx | Behavior")
	class UBehaviorTree* EnemyBehaviorTree;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	float TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;
	void Hitted(float Damage, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

	UFUNCTION(BlueprintCallable)
	void EnableRun();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
	float MaxHealth = 200.f;
	float CurrentHealth = 200.f;

	ACharacter* PlayerCharacter;

// public:
// 	UFUNCTION(BlueprintCallable)
// 	float GetVelocity();
};
