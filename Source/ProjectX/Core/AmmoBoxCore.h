// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interfaces/IInteractable.h"
#include "Datas/Weapons/WeaponsEnum.h"
#include "AmmoBoxCore.generated.h"

UCLASS(Abstract)
class PROJECTX_API AAmmoBoxCore : public AActor, public IIInteractable
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AAmmoBoxCore();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Projx | Comp", meta = (AllowPrivateAccess = true))
	UStaticMeshComponent* Bottom;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Projx | Comp", meta = (AllowPrivateAccess = true))
	UStaticMeshComponent* Top;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	EAmmoType AmmoType;
	FText DescriptionText;

protected:
	virtual void SetAmmoType() PURE_VIRTUAL(AAmmoBoxCore::SetAmmoType, ;);
	virtual void SetDescriptionText() PURE_VIRTUAL(AAmmoBoxCore::SetDescriptionText, ;);

public:
	void Action() override;
	FText Description() override;
};
