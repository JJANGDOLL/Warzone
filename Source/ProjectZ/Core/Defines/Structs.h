#pragma once

#include "Math/Float32.h"
#include "Engine/DataTable.h"
#include "Materials/MaterialInstance.h"
#include "Materials/MaterialInstanceConstant.h"
#include "Core/Defines/Enums.h"
#include "Structs.generated.h"

USTRUCT(BlueprintType)
struct FWeaponSettings
{
    GENERATED_BODY()

public:
    float FireMode;
    float FireRate;
};



USTRUCT(BlueprintType)
struct FSSpeed
{
    GENERATED_BODY()

public:

    FSSpeed()
    {

    }

    FSSpeed(float InMaxSpeed, float InFootstepDistance)
        : MaxSpeed(InMaxSpeed), FootstepDistance(InFootstepDistance)
    {

    }

    float MaxSpeed;
    float FootstepDistance;
};

USTRUCT(BlueprintType)
struct FSSpeeds
{
    GENERATED_BODY()

public:
    FSSpeeds()
        : SpeedWalk(440.f, 150.f)
        , SpeedAim(350.f, 100.f)
        , SpeedRun(700.f, 200.f)
        , SpeedCrouch(300.f, 100.f)
        , SpeedMultiplierShooting(0.7f, 0.7f)
    {

    }

    FSSpeed SpeedWalk;
    FSSpeed SpeedAim;
    FSSpeed SpeedRun;
    FSSpeed SpeedCrouch;
    FSSpeed SpeedMultiplierShooting;
};

USTRUCT(BlueprintType)
struct FSMovement
{
    GENERATED_BODY()

public:
    FSSpeeds Speeds;
    float AirControl = 0.35;
    float JumpForce = 600.f;
    float JumpMaxHoldTime = 0.15f;
    float SpeedMultiplierFiringRevertAddedDelay = 0.05;
};

USTRUCT(BlueprintType)
struct FSViewmodelAnimatedOffset
{
    GENERATED_BODY()

public:
    FVector JumpingLocation;
    FVector JumpingRotation;
    FVector FallingLocation;
    FVector FallingRotation;
    FVector LandingLocation;
    FVector LandingRotation;
};

USTRUCT(BlueprintType)
struct FSAttachmentMeshes
{
    GENERATED_BODY()


public:
    FSAttachmentMeshes()
    {
        RowHandleMeshScope.RowName = TEXT("Hidden");
        RowHandleMeshLaser.RowName = TEXT("Hidden");
        RowHandleMeshMuzzle.RowName = TEXT("Hidden");
        RowHandleMeshGrip.RowName = TEXT("Hidden");
    }

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
        FDataTableRowHandle RowHandleMeshScope;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
        FDataTableRowHandle RowHandleMeshLaser;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
        FDataTableRowHandle RowHandleMeshMuzzle;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
        FDataTableRowHandle RowHandleMeshGrip;
};

USTRUCT(BlueprintType)
struct FSPreset : public FTableRowBase
{
    GENERATED_BODY()

public:
    FSPreset()
    {
        RowHandleSkin.RowName = TEXT("Default-Assault-Rifle-01");
    }

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
        FDataTableRowHandle RowHandleSkin;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
        FSAttachmentMeshes Attachments;
};

USTRUCT(BlueprintType)
struct FSSkins : public FTableRowBase
{
    GENERATED_BODY()

public:
    FSSkins()
    {
        RowHandleSettingsLasersight.RowName = TEXT("Normal");
        RowHandleSettingsFlashlight.RowName = TEXT("Normal");
    }

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
        TMap<FName, UMaterialInstanceConstant*> MaterialMapBody;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
        TMap<FName, UMaterialInstanceConstant*> MaterialMapIronsights;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
        TMap<FName, UMaterialInstanceConstant*> MaterialMapMagazine;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
        TMap<FName, UMaterialInstanceConstant*> MaterialMapMuzzle;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
        TMap<FName, UMaterialInstanceConstant*> MaterialMapScope;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
        TMap<FName, UMaterialInstanceConstant*> MaterialMapLaser;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
        TMap<FName, UMaterialInstanceConstant*> MaterialMapGrip;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
        FDataTableRowHandle RowHandleSettingsLasersight;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
        FDataTableRowHandle RowHandleSettingsFlashlight;
};

USTRUCT(BlueprintType)
struct FSLasersight : public FTableRowBase
{
    GENERATED_BODY()

public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
        float LasersightBeamThickness;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
        FLinearColor LasersightBeamColor;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
        UMaterialInstance* LasersightBeamMaterial;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
        float LasersightDotSizeBase;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
        float LasersightDotSizeMultiplier;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
        FLinearColor LasersightDotColor;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
        UMaterialInstance* LasersightDotMaterial;
};

USTRUCT(BlueprintType)
struct FSFlashlight : public FTableRowBase
{
    GENERATED_BODY()

public:

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
        float Intensity;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
        float AttenuationRadius;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
        float InnerConeAngle;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
        float OuterConeAngle;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
        FLinearColor Color;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
        UMaterialInstance* LightFunctionMaterial;
};

USTRUCT(BlueprintType)
struct FSAttachmentSettings
{
    GENERATED_BODY()

public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    class UDataTable* DataTableSettingsScope;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    class UDataTable* DataTableSettingsLaser;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    class UDataTable* DataTableSettingsMuzzle;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    class UDataTable* DataTableSettingsGrip;
};

USTRUCT(BlueprintType)
struct FSAnimBlueprintSettings
{
    GENERATED_BODY()

public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FDataTableRowHandle RowHandleSettingsAnimation;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    class UDataTable* DataTablePosesCharacter;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    class UDataTable* DataTableMontagesCharacter;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    class UDataTable* DataTableMontagesWeapon;
};

USTRUCT(BlueprintType)
struct FSInformation : public FTableRowBase
{
    GENERATED_BODY()

public:

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FText WeaponName;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TSubclassOf<class UUserWidget> WidgetClassCrosshair;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FSAttachmentSettings SettingsAttachments;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FSAnimBlueprintSettings SettingsAnimationBlueprint;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FDataTableRowHandle RowHandleSettingsWeapon;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FDataTableRowHandle RowHandleSettingsCharacterAbilities;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FDataTableRowHandle RowHandleSettingsCharacterMovement;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    class UDataTable* DataTableIcons;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    class UDataTable* DataTableSoundCues;
};

USTRUCT(BlueprintType)
struct FSTexture
{
    GENERATED_BODY()

public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    class UTexture2D* Texture;
};

USTRUCT(BlueprintType)
struct FSMagazine : public FTableRowBase
{
    GENERATED_BODY()

public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    class UStaticMesh* Mesh;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FSTexture Texture;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    EAmmoType AmmunitionType;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 AmmunitionTotal;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TSubclassOf<class ACasingBase> CasingType;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FVector2D CasingImpulseRange;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float CasingOffset;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TSubclassOf<class AProjectileBase> ProjectileType;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FVector2D ProjectileVelocityRange;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FVector2D ProjectilePelletRange;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    bool AmmunitionVisualUpdate;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 AmmunitionVisualStartingIndex;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    class UMaterialInstanceConstant* AmmunitionVisualHiddenMaterial;
};

USTRUCT(BlueprintType)
struct FSIronsights : public FTableRowBase
{
    GENERATED_BODY()

public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    class UStaticMesh* Mesh;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FSTexture Icon;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FDataTableRowHandle RowHandleSettingsScope;
};

USTRUCT(BlueprintType)
struct FSBlend
{
    GENERATED_BODY()

public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float BlendIn;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float BlendOut;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float TimedValue;
};

USTRUCT(BlueprintType)
struct FSDirectionVector
{
    GENERATED_BODY()

public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FVector Horizontal;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FVector Vertical;
};

USTRUCT(BlueprintType)
struct FSDirectionTransform
{
    GENERATED_BODY()

public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FSDirectionVector Location;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FSDirectionVector Rotation;
};

USTRUCT(BlueprintType)
struct FSSPringInterpVector
{
    GENERATED_BODY()

public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float Stiffness;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float CriticalDampingFactor;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float Mass;
};

USTRUCT(BlueprintType)
struct FSLagValues
{
    GENERATED_BODY()

public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FSDirectionTransform Movement;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FSDirectionTransform Look;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FSSPringInterpVector SpringInterpolation;
};

USTRUCT(BlueprintType)
struct FSLowered
{
    GENERATED_BODY()

public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FSBlend SettingsBlend;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FTransform AdditionalOffset;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    bool RemoveStandingOffset;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    bool RunningAnimationUsed;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float RunningAnimationExplicitTime;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    bool RunningAnimationOffsetUsed;
};

USTRUCT(BlueprintType)
struct FSLean
{
    GENERATED_BODY()

public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    class UCurveVector* CurveLocation;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    class UCurveVector* CurveRotation;
};

USTRUCT(BlueprintType)
struct FSAnimationSettings : public FTableRowBase
{
    GENERATED_BODY()

public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
        FSBlend RunningBlend;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
        float PlayRateBreathing;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
        float PlayRateWalking;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
        float PlayRateRunning;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
        float PlayRateTurning;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
        float LagMovementInterpSpeed;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
        FVector LookOffsetMultiplierLocation;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
        FVector LookOffsetMultiplierRotation;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
        FTransform StandingOffset;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
        FSLagValues StandingLag;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
        float StandingLagLocationControllerMultiplier;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
        FTransform AimingOffset;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
        FSLagValues AimingLag;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
        FTransform RunningOffset;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
        FTransform CrouchingOffset;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
        FTransform MontageOffset;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
        FSLowered LoweredSettings;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
        class UDataTable* DataTableSequences;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
        class UDataTable* DataTableBlendspaces;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
        FSLean Leaning;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
        FSBlend AimingSyncTime;
};

USTRUCT(BlueprintType)
struct FSMesh : public FTableRowBase
{
    GENERATED_BODY()

public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    class UStaticMesh* Mesh;
};

USTRUCT(BlueprintType)
struct FSScope : public FTableRowBase
{
    GENERATED_BODY()

public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
        bool RenderTargetRequired = false;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
        float RenderTargetFieldOfView;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
        class UTextureRenderTarget2D* RenderTargetTexture;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
        FName RenderMaterialSlotName;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
        class UMaterialInstanceConstant* RenderMaterialReplacement;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
        FTransform OffsetStanding = FTransform::Identity;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
        FTransform OffsetAiming = FTransform::Identity;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
        FSLagValues MultiplierLagValues;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float MultiplierFieldOfView;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float MultiplierAimingSpeed;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float MultiplierSensitivityYaw;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float MultiplierSensitivityPitch;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    class UMaterialInstanceConstant* RenderMaterial;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float AimedFieldOfViewViewmodel;
};