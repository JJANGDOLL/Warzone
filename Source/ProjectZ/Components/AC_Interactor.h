// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Core/Interfaces/IInteractor.h"
#include "Engine/EngineTypes.h"
#include "AC_Interactor.generated.h"


UCLASS(Blueprintable, ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class PROJECTZ_API UAC_Interactor : public UActorComponent, public IIInteractor
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UAC_Interactor();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

public:
	void ResetType();
	void TryAssignType();
		
public:
	FHitResult GetHitResult() override;
	EInteractionType GetType() override;

public:
	void Trace();

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Projz | Interactor", meta = (AllowPrivateAccess = true))
	bool bEnabled;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Projz | Interactor", meta = (AllowPrivateAccess = true))
	float Distance;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Projz | Interactor", meta = (AllowPrivateAccess = true))
	float Radius;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Projz | Interactor", meta = (AllowPrivateAccess = true))
	TArray<TEnumAsByte<EObjectTypeQuery>> ObjectTypesBelow;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Projz | Interactor", meta = (AllowPrivateAccess = true))
	TArray<TEnumAsByte<EObjectTypeQuery>> ObjectTypesForward;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Projz | Data", meta = (AllowPrivateAccess = true))
	class AActor* Owner;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Projz | Data", meta = (AllowPrivateAccess = true))
	FHitResult HitResult;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Projz | Data", meta = (AllowPrivateAccess = true))
	FVector Location;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Projz | Data", meta = (AllowPrivateAccess = true))
	FVector Forward;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Projz | Data", meta = (AllowPrivateAccess = true))
	EInteractionType Type;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Projz | Data", meta = (AllowPrivateAccess = true))
	class ACharacter* Character;
};
