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
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Projz | Datas", meta = (AllowPrivateAccess = true))
	FDataTableRowHandle WeaponPresetRowHandle;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Projz | Preview", meta = (AllowPrivateAccess = true))
	FSPreset WeaponPreset;

public:
	void CacheWeaponInformation();
	void CacheWeaponInformationLoadAssetConstruct();

public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Projz | Datas", meta = (AllowPrivateAccess = true))
	FDataTableRowHandle WeaponInfoRowHandle;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Projz | Preview", meta = (AllowPrivateAccess = true))
	FSInformation WeaponInformation;

public:
	void TryUpdateAttachmentMagazine();
	void TryUpdateAttachmentMagazineLoadAssetConstruct();

public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Projz | Datas", meta = (AllowPrivateAccess = true))
    FDataTableRowHandle WeaponMagazineRowHandle;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Projz | Preview", meta = (AllowPrivateAccess = true))
	FSMagazine MagazineSettings;

public:
	void TryUpdateAttachmentIronsights();
	void TryUpdateAttachmentIronsightsLoadAssetConstruct();

public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Projz | Datas", meta = (AllowPrivateAccess = true))
	FDataTableRowHandle WeaponIronsightRowHandle;

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

public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Projz | Datas", meta = (AllowPrivateAccess = true))
	FDataTableRowHandle ScopeSettingsRowHandle;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Projz | Preview", meta = (AllowPrivateAccess = true))
	FSScope ScopeSettings;

	FSPreset WeaponPresetOverride;
};
