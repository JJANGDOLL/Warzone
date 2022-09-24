// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Core/ObjectBase.h"
#include "Core/Interfaces/IDamageable.h"
#include "Target.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTX_API ATarget : public AObjectBase
{
	GENERATED_BODY()
	
public:
	ATarget();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Projx | Comp", meta = (AllowPrivateAccess = true))
	USkeletalMeshComponent* SkelComp;

	UFUNCTION()
	void Hitted(UPrimitiveComponent* Comp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	void PostInitializeComponents() override;

	FTimerHandle RecoverHandle;
	bool bDown = true;

	void Recover();

	void Tick(float DeltaTime) override;

protected:
	void BeginPlay() override;

};
