// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "Interfaces/ICharacter.h"
#include "Defines/Structs.h"
#include "Interfaces/IWeapon.h"
#include "Kismet/KismetMathLibrary.h"
#include "AI_FP_PCH.generated.h"

/**
 * 
 */

class UAnimSequenceBase;

#define TRY_SEQUENCE_TEMPLATE(funcName, rowName, varName) \
UAnimSequenceBase*  varName; \
void funcName() \
{ \
    FSAnimation *findAnim = SettingsAnimation.DataTableSequences->FindRow<FSAnimation>(rowName, ""); \
    varName = Cast<UAnimSequenceBase>(findAnim->SequenceBaseFirstPerson); \
};

UCLASS()
class PROJECTZ_API UAI_FP_PCH : public UAnimInstance
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Projz | Prop", meta = (AllowPrivateAccess = true))
	ACharacter* Character;

	IICharacter* CharItf;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Projz | Prop", meta = (AllowPrivateAccess = true, DisplayName="Equipped Item"))
	AActor* Equipped_Item;

	IIWeapon* WeaponItf;

	float FieldOfViewDefault;
	
public:
	void NativeBeginPlay() override;
	void NativeUpdateAnimation(float DeltaSeconds) override;

public:
	void FieldOfView();

public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Projz | Prop", meta = (AllowPrivateAccess = true))
	float FieldOfViewStanding;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Projz | Prop", meta = (AllowPrivateAccess = true))
	float FieldOfViewAiming;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Projz | Prop", meta = (AllowPrivateAccess = true))
	float FieldOfViewRunning;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Projz | Prop", meta = (AllowPrivateAccess = true))
	FSScope SettingsScope;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Projz | Prop", meta = (AllowPrivateAccess = true))
	FVector Velocity;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Projz | Prop", meta = (AllowPrivateAccess = true))
	bool bAiming;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Projz | Prop", meta = (AllowPrivateAccess = true))
    bool bCrouching;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Projz | Prop", meta = (AllowPrivateAccess = true))
    bool bRunning;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Projz | Prop", meta = (AllowPrivateAccess = true))
    bool bFalling;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Projz | Prop", meta = (AllowPrivateAccess = true))
	FSAnimationSettings SettingsAnimation;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Projz | Prop", meta = (AllowPrivateAccess = true))
	USkeletalMeshComponent* StaticMeshWeaponBody;


public:
	void UpdateValues();

public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Projz | Prop", meta = (AllowPrivateAccess = true))
	FSSPringInterpVector SpringDataLookOffsetLocation;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Projz | Prop", meta = (AllowPrivateAccess = true))
    FSSPringInterpVector SpringDataLookOffsetRotation;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Projz | Prop", meta = (AllowPrivateAccess = true))
	UDataTable* DataTableAnimationPoses;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Projz | Prop", meta = (AllowPrivateAccess = true))
	FSGrip SettingsGrip;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Projz | Prop", meta = (AllowPrivateAccess = true))
	FSMovement SettingsMovement;

	float AimBlendTime;
	float MappedSpeed;
	float AlphaWalking;

	float PlayRateWalkingAiming;
	float AlphaLagMovement;
	float AlphaTurning;
	float AlphaLagLook;
	float TurnRate;
	float AlphaWalkingLean;
	float PlayRateWalking;
	float PlayRateWalkingCrouching;
	float PlayRateBrathing;
	float AlphaBreathing;
	float PlayRateAim;
	float PlayRateRunning;

public:
	float GetAimBlendTime();

	float GetAlphaWalking();

	float GetPlayRateWalkingAiming();

	float GetAlphaLagMovement();
	float GetAlphaTurning();
	float GetAlphaWalkingLean();
	float GetPlayRateWalking();
	float GetPlayRateWalkingCrouching();
	float GetPlayRateBreathing();
	float GetAlphaBreathing();
	float GetAimPlayRate();
	float GetPlayRateRunning();

public:
	void CalculateMappedSpeed();

public:
	void GetInputLook();

public:
	FVector2D CharacterInputLook;

public:
	void UpdateValuesPitch();

public:
	float PreviousPitch;
	float CameraPitchAcceleration;
	float Pitch;

public:
	void GetInputMovement();

public:
	FVector2D CharacterInputMovement;
	FVector2D CharacterInputMovementSmooth;

public:
	void CalculateLagValues();
	FVector CustomVectorSpringInterp(FVector Current, FVector Target, float DeltaTime, FSSPringInterpVector Data, FVectorSpringState SpringState);

	void UpdateAimingLocationLag();
	void UpdateAimingRotationLag();

	void UpdateAimingMovementLocationLag();
	void UpdateAimingMovementRotationLag();

	void UpdateStandingLocationLag();
	void UpdateStandingRotationLag();

	void UpdateStandingMovementLocationLag();
	void UpdateStandingMovementRotationLag();

public:
    float ClampedYawInput;
    float ClampedMovementInuputHorizontal;
    float ClampedMovementInputVertical;
	FVector AimingLocationLag;
	FVectorSpringState SpringStateAimingLagLocation;

	FVector AimingRotationLag;
	FRotator AimingRotationLagRotator;
    FVectorSpringState SpringStateAimingLagRotation;

	FVector AimingMovementLocationLag;
	FVectorSpringState SpringStateMovementLagLocation;

	FVector AimingMovementRotationLag;
	FRotator AimingMovementRotationLagRotator;

	FVector StandingLocationLag;
	FVectorSpringState SpringStateStandingLagLocation;
	FVector CurrentLookOffsetLocation;
	FVectorSpringState SpringStateLookOffsetLocation;

	FVector StandingRotationLag;
	FVectorSpringState SpringStateStandingLagRotation;
	FRotator StandingRotationLagRotator;
	FVector StandingRotationLagLookOffset;
	FVectorSpringState SpringStateLagLookOffset;

	FVector StandingMovementLocationLag;
	FVectorSpringState SpringStateStandingMovementLagLocation;

	FVector StandingMovementRotationLag;
	FVectorSpringState SpringStateStandingMovementLagRotation;
	FRotator StandingMovementRotationLagRotator;

public:
	void CalculateOffsetAiming();

public:
	FTransform OffsetAiming;

public:
	TRY_SEQUENCE_TEMPLATE(GetSequenceAimingBreathing, TEXT("Aiming-Breathing"), SequenceBreathingAiming);
    TRY_SEQUENCE_TEMPLATE(GetSequenceAimingWalking, TEXT("Aiming-Walking"), SequenceWalkingAiming);
    TRY_SEQUENCE_TEMPLATE(GetSequenceStandingBreathing, TEXT("Standing-Breathing"), SequenceBreathingStanding);
    TRY_SEQUENCE_TEMPLATE(GetSequenceTurning, TEXT("Turning"), SequenceTurning);
    TRY_SEQUENCE_TEMPLATE(GetSequenceRunning, TEXT("Sprint"), SequenceRunning);

// 	void SetSequenceViaSequencesTable(FName RowName, UAnimSequenceBase* PassedSequence, UAnimSequenceBase* DefaultSequence);

	void TryGetSequence()
	{
		if (!SettingsAnimation.DataTableSequences)
			return;

		GetSequenceAimingBreathing();
		GetSequenceAimingWalking();
		GetSequenceStandingBreathing();
		GetSequenceTurning();
		GetSequenceRunning();
	};
};
