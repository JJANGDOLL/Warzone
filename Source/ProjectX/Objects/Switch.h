// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Core/Interfaces/IInteractable.h"
#include "Switch.generated.h"

UCLASS()
class PROJECTX_API ASwitch : public AActor, public IIInteractable
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASwitch();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Projx | Comp", meta = (AllowPrivateAccess = true))
	UStaticMeshComponent* Base;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Projx | Comp", meta = (AllowPrivateAccess = true))
    UStaticMeshComponent* Button;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Projx | Comp", meta = (AllowPrivateAccess = true))
	AActor* Target;

public:
	void Action() override;

    FVector Forward;
	FVector Backward;
	bool bDir;

	void PostInitializeComponents() override;


	void Tick(float DeltaSeconds) override;


	FText Description() override;

};
