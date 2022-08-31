// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interfaces/IWeapon.h"
#include "Core/Defines/Structs.h"
#include "WeaponBase.generated.h"

class UWeaponAttachmentBase;
class UWeaponBodyBase;
class USceneComponent;
class UMeshComponent;
class UDataTable;

UCLASS(Abstract)
class PROJECTZ_API AWeaponBase : public AActor, public IIWeapon
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AWeaponBase();

private:
	UPROPERTY(BlueprintReadWrite, Category = "Projz | Comp", meta = (AllowPrivateAccess = true))
	UWeaponBodyBase* Weapon;

    UPROPERTY(BlueprintReadWrite, Category = "Projz | Comp", meta = (AllowPrivateAccess = true))
	USceneComponent* SocketDefault;

    UPROPERTY(BlueprintReadWrite, Category = "Projz | Comp", meta = (AllowPrivateAccess = true))
	UWeaponAttachmentBase* SMeshIronsight;

    UPROPERTY(BlueprintReadWrite, Category = "Projz | Comp", meta = (AllowPrivateAccess = true))
    USceneComponent* SocketMagazine;

    UPROPERTY(BlueprintReadWrite, Category = "Projz | Comp", meta = (AllowPrivateAccess = true))
	UWeaponAttachmentBase* SMeshMagazine;

    UPROPERTY(BlueprintReadWrite, Category = "Projz | Comp", meta = (AllowPrivateAccess = true))
	USceneComponent* SocketLaser;

    UPROPERTY(BlueprintReadWrite, Category = "Projz | Comp", meta = (AllowPrivateAccess = true))
	UWeaponAttachmentBase* SMeshLaser;

    UPROPERTY(BlueprintReadWrite, Category = "Projz | Comp", meta = (AllowPrivateAccess = true))
	USceneComponent* SocketGrip;

    UPROPERTY(BlueprintReadWrite, Category = "Projz | Comp", meta = (AllowPrivateAccess = true))
	UWeaponAttachmentBase* SMeshGrip;

    UPROPERTY(BlueprintReadWrite, Category = "Projz | Comp", meta = (AllowPrivateAccess = true))
	USceneComponent* SocketMuzzle;
        
	UPROPERTY(BlueprintReadWrite, Category = "Projz | Comp", meta = (AllowPrivateAccess = true))
	UWeaponAttachmentBase* SMeshMuzzle;

    UPROPERTY(BlueprintReadWrite, Category = "Projz | Comp", meta = (AllowPrivateAccess = true))
	USceneComponent* PivotScope;

    UPROPERTY(BlueprintReadWrite, Category = "Projz | Comp", meta = (AllowPrivateAccess = true))
	USceneComponent* SocketScope;

    UPROPERTY(BlueprintReadWrite, Category = "Projz | Comp", meta = (AllowPrivateAccess = true))
	UWeaponAttachmentBase* SMeshScope;


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
	void OnConstruction(const FTransform& Transform) override;


	void PostEditChangeProperty(struct FPropertyChangedEvent& PropertyChangedEvent) override;

	// OnConstruction
public:
	void UpdateSocketAttachments();

public:
	TArray<UWeaponAttachmentBase*> ComponentsAttachments;

	UMeshComponent* GetScopeParent();
	UMeshComponent* GetGripParent();
	UMeshComponent* GetMuzzleParent();

public:
	FName SocketNameScope = TEXT("SOCKET_Scope");
	FName SocketNameGrip = TEXT("SOCKET_Grip");
	FName SocketNameLaser = TEXT("SOCKET_Laser");
	FName SocketNameMuzzle = TEXT("SOCKET_Muzzle");
	FName SocketNameIronsights = TEXT("SOCKET_Default");

public:
	void CacheWeaponPreset();
	void CacheWeaponPresetLoadAssetConstruct();

public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Projz | Settings", meta = (AllowPrivateAccess = true))
	FDataTableRowHandle WeaponPresetRowHandle;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Projz | Preview", meta = (AllowPrivateAccess = true))
	FSPreset WeaponPreset;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Projz | Custom", meta = (AllowPrivateAccess = true))
	FSPreset WeaponPresetOverride;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Projz | Custom", meta = (AllowPrivateAccess = true))
	bool bOverridePreset = false;

public:
	void CacheWeaponInformation();
	void CacheWeaponInformationLoadAssetConstruct();

public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Projz | Settings", meta = (AllowPrivateAccess = true))
	FDataTableRowHandle WeaponInfoRowHandle;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Projz | Preview", meta = (AllowPrivateAccess = true))
	FSInformation WeaponInformation;

public:
	void TryUpdateAttachmentMagazine();
	void TryUpdateAttachmentMagazineLoadAssetConstruct();

public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Projz | Settings", meta = (AllowPrivateAccess = true))
    FDataTableRowHandle MagazineSettingRowHandle;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Projz | Preview", meta = (AllowPrivateAccess = true))
	FSMagazine MagazineSettings;

public:
	void TryUpdateAttachmentIronsights();
	void TryUpdateAttachmentIronsightsLoadAssetConstruct();

public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Projz | Settings", meta = (AllowPrivateAccess = true))
	FDataTableRowHandle IronsightSettingsRowHandle;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Projz | Preview", meta = (AllowPrivateAccess = true))
	FSIronsights IronsightSettings;
	bool ShowAttachmentIronsights;

public:
	void SettingsAnimation();
    void SettingsAnimationLoadAssetConstruct();

public:
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Projz | Preview", meta = (AllowPrivateAccess = true))
	FSAnimationSettings AnimationSettings;

public:
	void UpdateAttachmentScope();
    void UpdateAttachmentScopeLoadAssetConstruct();
	bool TryUpdateAttachmentScope(FSPreset& Preset);
	void GetIronsightsScopeSettings();
	void OnSwapAttachmentScope(FDataTableRowHandle Mesh, FDataTableRowHandle Settings);
	void SetScopeMeshRowHandle(FDataTableRowHandle Mesh);
    void SetScopeSettingsRowHandle(FDataTableRowHandle Settings);

public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Projz | Settings", meta = (AllowPrivateAccess = true))
	FDataTableRowHandle ScopeSettingsRowHandle;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Projz | Preview", meta = (AllowPrivateAccess = true))
	FSScope ScopeSettings;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Projz | Preview", meta = (AllowPrivateAccess = true))
	FDataTableRowHandle ScopeMeshRowHandle;

public:
	void UpdateAttachmentMazzule();
	void UpdateAttachmentMazzuleLoadAssetConstruct();
	bool TryUpdateAttachmentMuzzle(FSPreset& Preset);
	void OnSwapAttachmentMuzzle(FDataTableRowHandle Mesh, FDataTableRowHandle Settings);
	void SetMuzzleMeshRowHandle(FDataTableRowHandle Mesh);
	void SetMuzzleSettingsRowHandle(FDataTableRowHandle Settings);

public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Projz | Settings", meta = (AllowPrivateAccess = true))
	FDataTableRowHandle MuzzleSettingsRowHandle;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Projz | Preview", meta = (AllowPrivateAccess = true))
	FSMuzzle MuzzleSettings;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Projz | Preview", meta = (AllowPrivateAccess = true))
	FDataTableRowHandle MuzzleMeshRowHandle;

public:
	void UpdateAttachmentLaser();
	void UpdateAttachmentLaserLoadAssetConstruct();
	bool TryUpdateAttachmentLaser(FSPreset& Preset);
	void OnSwapAttachmentLaser(FDataTableRowHandle Mesh, FDataTableRowHandle Settings);
	void SetLaserSettingsRowHandle(FDataTableRowHandle Settings);
	void SetLaserMeshRowHandle(FDataTableRowHandle Mesh);

public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Projz | Settings", meta = (AllowPrivateAccess = true))
	FDataTableRowHandle LaserSettingsRowHandle;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Projz | Preview", meta = (AllowPrivateAccess = true))
	FSLaser LaserSettings;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Projz | Preview", meta = (AllowPrivateAccess = true))
	FDataTableRowHandle LaserMeshRowHandle;

public:
	void UpdateAttachmentGrip();
	void UpdateAttachmentGripLoadAssetConstruct();
	bool TryUpdateAttachmentGrip(FSPreset& Preset);
	void OnSwapattachmentGrip(FDataTableRowHandle Mesh, FDataTableRowHandle Settings);
	void SetGripSettingsRowHandle(FDataTableRowHandle Settings);
	void SetGripMeshRowHandle(FDataTableRowHandle Mesh);

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Projz | Settings", meta = (AllowPrivateAccess = true))
	FDataTableRowHandle GripSettingsRowHandle;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Projz | Preview", meta = (AllowPrivateAccess = true))
	FSGrip GripSettings;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Projz | Preview", meta = (AllowPrivateAccess = true))
	FDataTableRowHandle GripMeshRowHandle;

public:
	void UpdateSkin();
	void UpdateSkinLoadAssetConstruct();
	bool TryUpdateSkin(FSPreset& Preset);
	void SetSkinRowHandle(FDataTableRowHandle Skin);
	void UpdateMaterialFromSkin();
	void CacheNewVisualLaserSettings();
	void MapMaterialtoComponent(class UPrimitiveComponent* Component, TMap<FName, class UMaterialInstanceConstant*> MaterialMap);

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Projz | Settings", meta = (AllowPrivateAccess = true))
	FDataTableRowHandle SkinRowHandle;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Projz | Preview", meta = (AllowPrivateAccess = true))
	FSSkin SkinSettings;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Projz | Preview", meta = (AllowPrivateAccess = true))
	FSLasersight LaserSightsSettings;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Projz | Preview", meta = (AllowPrivateAccess = true))
	FSFlashlight FlashlightSettings;

public:
	void DebugAllComponents();
	void DebugAllComponentsLoadAssetConstruct();
	virtual void OnSpawnAttachmentComponents() override;
	void TrySpawnComponentMuzzleFlash();
	void TrySpawnComponentFlashlight();
	void SetLightSpotFlashLight();
	void TrySpawnComponentsLasersight();
	void TrySpawnScopeRenderTarget();

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Projz | Debug", meta = (AllowPrivateAccess = true))
	bool bDebugComponents;

	class UPointLightComponent* LightPointMuzzleFlash;
	class USpotLightComponent* LightSpotFlashlight;
	class UStaticMeshComponent* StaticMeshLasersightBeam;
	class UDecalComponent* Decal;
	class USceneCaptureComponent2D* SceneCaptureScope;

public:
	void UpdateAllPhysicalSettings();
    void UpdateAllPhysicalSettingsLoadAssetConstruct();
    virtual void OnChangeSettingsPhysicalAttachments(FDataTableRowHandle Value) override;
    virtual void OnChangeSettingsPhysicalBody(FDataTableRowHandle Value) override;
	void SetRowHandlePhysicalAttachments(FDataTableRowHandle Value);
	void SetRowHandlePhysicalWeapon(FDataTableRowHandle Value);
	FSPhysical GetSettingsPhysical(FDataTableRowHandle RowHandle);
	void UpdateComponentPhysicalSettings(UPrimitiveComponent* Component, FSPhysical Settings);

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Projz | Preview", meta = (AllowPrivateAccess = true))
	FDataTableRowHandle RowHandlePhysicalAttachments;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Projz | Preview", meta = (AllowPrivateAccess = true))
	FDataTableRowHandle RowHandlePhysicalWeapon;

public:
    void CacheWeaponSettings();

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Projz | Preview", meta = (AllowPrivateAccess = true))
	FSWeaponSettings WeaponSettings;

public:
	void CacheCharacterAbilities();

public:
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Projz | Preview", meta = (AllowPrivateAccess = true))
	FSAbilities PlayerCharacterAbilities;

};

