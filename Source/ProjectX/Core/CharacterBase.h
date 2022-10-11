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
class UUSerWidget;
class UMainGameInterface;
class UAC_Inventory;
class IIInteractable;

UCLASS()
class PROJECTX_API ACharacterBase : public ACharacter, public IICharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ACharacterBase();


	void OnConstruction(const FTransform& Transform) override;


	void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

protected:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Projx | Components", meta = (AllowPrivateAccess = true))
	USpringArmComponent* SpringArm;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Projx | Components", meta = (AllowPrivateAccess = true))
    USkeletalMeshComponent* SkeletalMeshArms;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Projx | Components", meta = (AllowPrivateAccess = true))
	UCameraComponent* Camera;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Projx | Components", meta = (AllowPrivateAccess = true))
	UAC_Inventory* Inventory;

public:
	USkeletalMeshComponent* GetMeshArms();

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
	void StopRunning() override;
    bool IsFalling() override;
    bool IsCrouching() override;
    void Crouching() override;
    bool IsBreath() override;
    void Breath() override;
	bool IsHolster() override;
    void Holstering() override;
    void Unholstering() override;
	
	void StopFire();

	void ChangeFireType();
	void FireCore(UAnimMontage* Montage);

	bool IsWeaponEquipped();
// 	AWeaponBase* GetEquippedWeapon();
	void UpdateEquippedWeapon();

private:
    AWeaponBase** EquippedWeapon;
//     AWeaponBase* NextWeapon;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Projx | State", meta = (AllowPrivateAccess = true))
	bool bAiming;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Projx | State", meta = (AllowPrivateAccess = true))
    bool bRunning;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Projx | State", meta = (AllowPrivateAccess = true))
    bool bCrouching;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Projx | State", meta = (AllowPrivateAccess = true))
    bool bBreath = true;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Projx | State", meta = (AllowPrivateAccess = true))
    bool bHolster = false;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Projx | State", meta = (AllowPrivateAccess = true))
    bool bPlayingMontageUnholstering = false;

protected:
	// Test, Debug
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Projx | Character | Test", meta = (AllowPrivateAccess = true))
    TSubclassOf<AWeaponBase> TestWeapon;

protected:
    FTimerHandle TestTimerHandle;

    FTimerHandle FireHandle;
	FTimerDelegate FireDelegate;

private:
    typedef void (ACharacterBase::* TestFunc)(void);
    TMap<ECharacterFeature, TestFunc> TestMethods;

    UPROPERTY(EditInstanceOnly, Category = "Projx | Character | Test", meta = (AllowPrivateAccess = true))
	ECharacterFeature TestFeature;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Projx | Charcter | Test", meta = (AllowPrivateAccess = true))
    float TestTerm = 5.f;

public:
    TestFunc OnTestFeature = nullptr;

	//HUD
public:
	UPROPERTY(EditInstanceOnly, Category = "Projx | Widget ", meta = (AllowPrivateAccess = true))
    TSubclassOf<UMainGameInterface> PlayerHUDClass;

	UPROPERTY()
	UMainGameInterface* PlayerHUD;

private:
	void UpdateWidget();

private:
	void OnReloadBlendOut(UAnimMontage* AnimMontage, bool bInterrupted);
    void OnUnholsterBlendOut(UAnimMontage* AnimMontage, bool bInterrupted);
    void OnFireBlendOut(UAnimMontage* AnimMontage, bool bInterrupted);
    void OnBoltActionReloadBlendOut(UAnimMontage* AnimMontage, bool bInterrupted);


	bool bPlayingMontageReloading = false;

	bool bHoldingFire = false;

	uint8 BrustFireCount = 0;

	void StartCrouch();
	void StopCrouch();
	void StartAiming();
    void StopAiming();

	void GetItemOne();
    void GetItemTwo();
    void GetItemThree();

public:
	void EndHolstering();
	void EndUnholstering();

private:
	IIInteractable* InteractTarget;
	void Interact();

private:
	void DropItem();
	void NewWeapon();

public:
	UAC_Inventory* GetInventory();

public:
	void UpdateWeaponWidget();
	
	void WeaponRecoil();

private:
	void Pause();

	TSubclassOf<UUserWidget> PauseWidgetClass;
    UUserWidget* PauseWidget;
    bool bShowPause;

	TSubclassOf<class UCrosshair> CrosshairClass;

private:
	void BoltActionReload();

protected:
	bool bCanFire = true;
	bool bCanReload = true;
	bool bBoltActionReloadStop = false;

private:
	void ReloadBoltActionAmmo();
    void OnBoltActionOpenBlendOut(UAnimMontage* AnimMontage, bool bInterrupted);
	void BoltActionReloadAmmoCore();
    void OnBoltActionCloseBlendOut(UAnimMontage* AnimMontage, bool bInterrupted);

public:
	bool IsBoltActionReloadStop();
};

