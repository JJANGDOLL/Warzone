// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Interfaces/ICharacter.h"
#include "CharacterBase.generated.h"

class USkeletalMeshComponent;
class USpringArmComponent;
class UCameraComponent;
class AWeaponBase;

UCLASS()
class PROJECTX_API ACharacterBase : public ACharacter, public IICharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ACharacterBase();

protected:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Projx | Character", meta = (AllowPrivateAccess = true))
	USpringArmComponent* SpringArm;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Projx | Character", meta = (AllowPrivateAccess = true))
    USkeletalMeshComponent* SkeletalMeshArms;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Projx | Character", meta = (AllowPrivateAccess = true))
	UCameraComponent* Camera;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void MoveForward(float AxisValue);
	void MoveRight(float AxisValue);

private:
	FVector HalfHeight;

public:
	class AWeaponBase* GetEquippedWeapon() override;

private:
	AWeaponBase* EquippedWeapon;

private:
	// Test, Debug
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Projx | Character", meta = (AllowPrivateAccess = true))
	TSubclassOf<AWeaponBase> TestWeapon;
};
