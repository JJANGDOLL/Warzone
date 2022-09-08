// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Defines/Enums.h"
#include "Defines/Structs.h"
#include "Engine/EngineTypes.h"
#include "Interfaces/ICharacter.h"
#include "Components/TimelineComponent.h"
#include "CharacterBase.generated.h"

class USpringArmComponent;
class USceneComponent;
class USkeletalMeshComponent;
class UStaticMeshComponent;
class UCameraComponent;
class USC_Inventory;
class UTimelineComponent;

UCLASS()
class PROJECTZ_API ACharacterBase : public ACharacter, public IICharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ACharacterBase();



	int32 GetFieldOfView() override;


	bool IsAiming() override;


	bool IsRunning() override;


	class UCameraComponent* GetCameraComponent() override;


	FVector2D GetInputLook() override;


	FVector2D GetInputMovement() override;

public:
	void OnPickUp() override;

public:
	FHitResult HitResultInteractionTrace;


public:
	bool TryStartAbility(FSGameAbility Ability) override;
	bool TryStartGameAbility(FSGameAbility Ability, FGameplayTagContainer Container);
	bool CanStartGameAbility(FSGameAbility Ability, FGameplayTagContainer Container, UWorld* World);
	void StartGameAbility(FSGameAbility Ability, FGameplayTagContainer Container, UWorld* World);
	void RemoveGameplayTagContainer(FGameplayTagContainer Ability, FGameplayTagContainer Container, UWorld* World);

public:
	FGameplayTagContainer AbilityTags;

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
	UStaticMeshComponent* SMeshHelmet;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Projz | Comp", meta = (AllowPrivateAccess = true))
	UStaticMeshComponent* SMeshHeadset;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Projz | Comp", meta = (AllowPrivateAccess = true))
	UCameraComponent* Camera;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Projz | Comp", meta = (AllowPrivateAccess = true))
	USC_Inventory* Inventory;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Projz | Comp", meta = (AllowPrivateAccess = true))
	USkeletalMeshComponent* ReplicatedCharacter;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Projz | Comp", meta = (AllowPrivateAccess = true))
	USceneComponent* ReplicatedHeadSocket;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Projz | Comp", meta = (AllowPrivateAccess = true))
	UStaticMeshComponent* Helmet;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Projz | Comp", meta = (AllowPrivateAccess = true))
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

    UPROPERTY(BlueprintReadWrite, Category = "Projz | Comp", meta = (AllowPrivateAccess = true))
	UTimelineComponent* TLineResetCamera;

    UPROPERTY(BlueprintReadWrite, Category = "Projz | Comp", meta = (AllowPrivateAccess = true))
    UTimelineComponent* TLineViewmodelJump;

    UPROPERTY(BlueprintReadWrite, Category = "Projz | Comp", meta = (AllowPrivateAccess = true))
    UTimelineComponent* TLineViewmodelLand;

    UPROPERTY(BlueprintReadWrite, Category = "Projz | Comp", meta = (AllowPrivateAccess = true))
    UTimelineComponent* TLineViewmodelFall;

    UPROPERTY(BlueprintReadWrite, Category = "Projz | Comp", meta = (AllowPrivateAccess = true))
    UTimelineComponent* TLineCameraJump;

    UPROPERTY(BlueprintReadWrite, Category = "Projz | Comp", meta = (AllowPrivateAccess = true))
    UTimelineComponent* TLineCameraLand;

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
	void UpdateHeadgearVisibility();

public:
	FVector FirstPersonViewOffset = FVector(0.f, 0.f, -25.f);
	bool bShowHelmet;
	bool bShowHeadset;
	bool bShowGoggles;

	class UMaterialInstanceConstant* CharacterMaterial;
	bool bLeftHandMode;

	//begin play
public:
	void TrySetFieldOfViewAlph(float Alpha);
	void SetUpMappingContext();
	void SetUpAllTimelineCurves();
	void SetUpCurveFloat(class UTimelineComponent* TimelineComponent, FSCurveFloat Curve);
	void SetUpCurveVector(class UTimelineComponent* TImelineComponent, FSCurveVector Curve);
	void CalculatePlayRates();
	void CacheGInstance();
	void AddWidgetstoViewport();

public:
	float FreeLookFlySpeed;
	float ControlRotationInterpSpeed;
	float CurrentControlRotationInterpSpeed;
	TMap<EAmmoType, int32> AmmunitionPoolStarting;
    TMap<EAmmoType, int32> AmmunitionPoolCurrent;

	FSFreeLook SettingsCameraUnlocking;
	FSCurveVector ViewmodelJumpLocationCurve;
	FSCurveVector ViewmodelJumpRotationCurve;

	FSCurveVector ViewmodelLandLocationCurve;
	FSCurveVector ViewmodelLandRotationCurve;

	FSCurveVector ViewmodelFallLocationCurve;
	FSCurveVector ViewmodelFallRotationCurve;

	FSCurveVector CameraJumpRotationCurve;
	FSCurveVector CameraLandRotationJump;

    FVector2D MontagePlayRateRangeMeleeAttack;
	FVector2D MontagePlayRateRangeGrenadeThrow;
	FVector2D MontagePlayRateRangeFire;
	
	float MontagePlayRateMeleeAttak;
	float MontagePlayRateGrenadeThrow;
	float MontagePlayRateFire;

	class UGameInstanceBase* GameInstance;

	TSubclassOf<UUserWidget> WidgetClassInterface;

	FOnTimelineFloat ResetCameraFunc;

    FOnTimelineVector TLineViewmodelFallFunc;
	FOnTimelineVector TLineViewmodelLandFunc;
	FOnTimelineVector TLineViewmodelJumpFunc;
	FOnTimelineVector TLineCameraJumpFunc;
	FOnTimelineVector TLineCameraLandFunc;

public:
	UFUNCTION(BlueprintCallable)
	virtual AActor* GetEquippedItem() override;

public:
	float FieldOfViewDefault;

public:
	virtual int32 GetFieldOfViewRunning() override;

public:
	float FieldOfViewMultiplierRunning;

	bool bAiming;
	bool bRunning;


	virtual float GetAimDuration() override;

	virtual float GetAimSpeedMultiplier() override;

	FSScope WeaponSettingsScope;

    FVector2D Look;
    FVector2D Movement;
};
