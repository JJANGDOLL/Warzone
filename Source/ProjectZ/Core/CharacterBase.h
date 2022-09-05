// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "CharacterBase.generated.h"

class USpringArmComponent;
class USceneComponent;
class USkeletalMeshComponent;
class UStaticMeshComponent;
class UCameraComponent;

UCLASS()
class PROJECTZ_API ACharacterBase : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ACharacterBase();

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Projz | Comp", meta = (AllowPrivateAccess = true))
	USpringArmComponent* SpringArm;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Projz | Comp", meta = (AllowPrivateAccess = true))
	USkeletalMeshComponent* SkeletalMeshArms;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Projz | Comp", meta = (AllowPrivateAccess = true))
	USceneComponent* SocketHandLeft;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Projz | Comp", meta = (AllowPrivateAccess = true))
	UStaticMeshComponent* SMeshKnife;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Projz | Comp", meta = (AllowPrivateAccess = true))
	USceneComponent* SocketHandRight;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Projz | Comp", meta = (AllowPrivateAccess = true))
	USceneComponent* RootCosmetics;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Projz | Comp", meta = (AllowPrivateAccess = true))
	UStaticMeshComponent* SMeshGoggles;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Projz | Comp", meta = (AllowPrivateAccess = true))
	UStaticMeshComponent* SMeshHelment;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Projz | Comp", meta = (AllowPrivateAccess = true))
	UStaticMeshComponent* SMeshHeadset;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Projz | Comp", meta = (AllowPrivateAccess = true))
	UCameraComponent* Camera;

	// Inventory
	//..
	//..

    UPROPERTY(BlueprintReadWrite, Category = "Projz | Comp", meta = (AllowPrivateAccess = true))
	USkeletalMeshComponent* ReplicatedCharacter;

    UPROPERTY(BlueprintReadWrite, Category = "Projz | Comp", meta = (AllowPrivateAccess = true))
	USceneComponent* ReplicatedHeadSocket;

    UPROPERTY(BlueprintReadWrite, Category = "Projz | Comp", meta = (AllowPrivateAccess = true))
	UStaticMeshComponent* Helmet;

    UPROPERTY(BlueprintReadWrite, Category = "Projz | Comp", meta = (AllowPrivateAccess = true))
	UStaticMeshComponent* Headset;

    UPROPERTY(BlueprintReadWrite, Category = "Projz | Comp", meta = (AllowPrivateAccess = true))
	UStaticMeshComponent* Googles;

    UPROPERTY(BlueprintReadWrite, Category = "Projz | Comp", meta = (AllowPrivateAccess = true))
	USceneComponent* BackpackSocket;

    UPROPERTY(BlueprintReadWrite, Category = "Projz | Comp", meta = (AllowPrivateAccess = true))
	UStaticMeshComponent* BackpackMesh;

    UPROPERTY(BlueprintReadWrite, Category = "Projz | Comp", meta = (AllowPrivateAccess = true))
	UStaticMeshComponent* BackpackMeshRocket01;

    UPROPERTY(BlueprintReadWrite, Category = "Projz | Comp", meta = (AllowPrivateAccess = true))
	UStaticMeshComponent* BackpackmeshRocket02;


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
    void OnConstruction(const FTransform& Transform) override;

public:
	FVector GetViewLocation();

public:
	FVector FirstPersonViewOffset = FVector(0.f, 0.f, -25.f);
};
