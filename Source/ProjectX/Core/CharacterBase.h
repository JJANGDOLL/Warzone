// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Interfaces/ICharacter.h"
#include "Datas/Characters/CharactersEnum.h"
#include "Datas/Weapons/WeaponsEnum.h"
#include "CharacterBase.generated.h"

class USkeletalMeshComponent;
class USpringArmComponent;
class UCameraComponent;
class AWeaponBase;
class UAnimMontage;

UCLASS()
class PROJECTX_API ACharacterBase : public ACharacter, public IICharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ACharacterBase();


	void OnConstruction(const FTransform& Transform) override;

protected:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Projx | Components", meta = (AllowPrivateAccess = true))
	USpringArmComponent* SpringArm;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Projx | Components", meta = (AllowPrivateAccess = true))
    USkeletalMeshComponent* SkeletalMeshArms;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Projx | Components", meta = (AllowPrivateAccess = true))
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
	FVector GetViewLocation();
	FVector ViewOffset;

public:
	AWeaponBase* GetEquippedWeapon() override;
	void DoNothing();
	bool IsAiming() override;
    void Aiming() override;
	void Fire() override;
	void Reload() override;
	void ReloadEmpty() override;
	bool IsRunning() override;
	void Running() override;
    bool IsFalling() override;
    bool IsCrouching() override;
    void Crouching() override;

private:
	AWeaponBase* EquippedWeapon;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Projx | State", meta = (AllowPrivateAccess = true))
	bool bAiming;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Projx | State", meta = (AllowPrivateAccess = true))
    bool bRunning;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Projx | State", meta = (AllowPrivateAccess = true))
    bool bCrouching;

protected:
	// Test, Debug
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Projx | Character | Test", meta = (AllowPrivateAccess = true))
    TSubclassOf<AWeaponBase> TestWeapon;

protected:
    FTimerHandle TestTimerHandle;


private:
    typedef void (ACharacterBase::* TestFunc)(void);
    TMap<ECharacterFeature, TestFunc> TestMethods;

    UPROPERTY(EditInstanceOnly, Category = "Projx | Character | Test", meta = (AllowPrivateAccess = true))
	ECharacterFeature TestFeature;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Projx | Charcter | Test", meta = (AllowPrivateAccess = true))
    float TestTerm = 5.f;

public:
    TestFunc OnTestFeature = nullptr;
};
