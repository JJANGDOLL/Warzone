// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Core/Interfaces/ICharacter.h"
#include "CharacterBase.generated.h"

class AWeaponBase;

UCLASS()
class PROJECTR_API ACharacterBase : public ACharacter, public IICharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ACharacterBase();


	bool IsAiming() override;


	bool IsRunning() override;


	bool CanAim() override;


	bool CanFire() override;


	bool CanReload() override;


	bool CanInspect() override;


	void PossessedBy(AController* NewController) override;


	bool CanHolster() override;


	bool IsHolstered() override;

public:
	virtual void OnConstruction(const FTransform& Transform) override;

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
    class USpringArmComponent* SpringArm;

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
    class UCameraComponent* CameraComp;

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	class USkeletalMeshComponent* MeshArms;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void Jump() override;

	void StopJumping() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
	void MoveForward(float AxisValue);

    UFUNCTION(BlueprintCallable)
	void MoveRight(float AxisValue);

	UFUNCTION(BlueprintCallable)
	void PressRun();

    UFUNCTION(BlueprintCallable)
	void ReleaseRun();

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	bool bHoldingKeyRun = false;
	bool CanRun();

	bool bAiming = false;
	bool bPlayingMontageReloading = false;
	bool bPlayingMontageInspecting = false;
	bool bRunning = false;
	float SpeedRunning = 700.f;
    float SpeedWalking = 400.f;
	float SpeedAiming = 350.f;

	bool bJumping = false;

private:
	class USoundBase* jumpSoundQue;

public:
	UFUNCTION(BlueprintCallable)	
	void ToggleCrouch();

private:
    FVector ViewOffset = FVector(0.0f, 0.0f, -35.0f);
	FVector GetViewLocation();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Test | Weapon")
	TSubclassOf<AWeaponBase> WeaponClass;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Test | Weapon")//, meta=(AllowPrivateAccess = "true"))
	AWeaponBase* WeaponActor;

public:
	UFUNCTION(BlueprintCallable)
	AWeaponBase* GetCurrentWeapon();


private:
	float RateOfFire;

private:
	UPROPERTY(EditInstanceOnly, Category = "Test")
	bool bDebug;
	
public:
	UFUNCTION(BlueprintCallable)
	void ToggleAim();
	
	void PressAim();
	void ReleaseAim();

	void StartAiming();

	bool bHoldingKeyAim;

private:
	void DoRun();

public:
	void PressFire();
	void ReleaseFire();

	UFUNCTION(BlueprintCallable)
	void PlayFireMontage();

	bool bHoldingKeyFire;

public:
	UFUNCTION(BlueprintCallable, CallInEditor, Category = "Test | Weapon")
	void NewWeapon();

	UAnimMontage* MontageFire;
	float LastFireTime;

	bool bHolstered = false;

public:
	UFUNCTION(BlueprintCallable)
	void Reload();

	bool bWeaponEmpty;
	UAnimMontage* MontageReload;
	UAnimMontage* MontageReloadEmpty;

	void OnReloadBlendOut(UAnimMontage* animMOntage, bool bInterrupted);

public:
	UFUNCTION(BlueprintCallable)
	void Inspect();

	UAnimMontage* MontageInspect;
    void OnInspectBlendOut(UAnimMontage* animMOntage, bool bInterrupted);

public:
	UFUNCTION(BlueprintCallable)
	void ToggleHolster();

	void Holster();
	void Unholster();

	UAnimMontage* MontageHolster;
    UAnimMontage* MontageUnholster;
	bool bPlayingMontageHolstering;

    void OnHolsterBlendOut(UAnimMontage* animMOntage, bool bInterrupted);
    void OnUnholsterBlendOut(UAnimMontage* animMOntage, bool bInterrupted);
};
