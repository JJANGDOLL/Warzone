// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/WeaponBase.h"
#include "Utilities/Global.h"

#include "Core/WeaponAttachmentBase.h"
#include "Core/WeaponBodyBase.h"
#include "Engine/SkeletalMesh.h"
#include "Components/MeshComponent.h"
#include "Kismet/DataTableFunctionLibrary.h"
#include "Components/PointLightComponent.h"

// Sets default values
AWeaponBase::AWeaponBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Helpers::CreateComponent(this, &Weapon, TEXT("Weapon"));

	Helpers::CreateComponent(this, &SocketDefault, TEXT("SOCKET_Default"), Weapon, TEXT("SOCKET_Default"));
	Helpers::CreateComponent(this, &SocketMagazine, TEXT("SOCKET_Magazine"), Weapon, TEXT("SOCKET_Magazine"));
	Helpers::CreateComponent(this, &SocketLaser, TEXT("SOCKET_Laser"), Weapon);
	Helpers::CreateComponent(this, &SocketGrip, TEXT("SOCKET_Grip"), Weapon);
	Helpers::CreateComponent(this, &SocketMuzzle, TEXT("SOCKET_Muzzle"), Weapon);
	Helpers::CreateComponent(this, &PivotScope, TEXT("Pivot_Scope"), Weapon);
	Helpers::CreateComponent(this, &SocketScope, TEXT("SOCKET_Scope"), PivotScope);

	Helpers::CreateComponent(this, &SMeshIronsight, TEXT("SMesh_Ironsights"), SocketDefault);
	Helpers::CreateComponent(this, &SMeshMagazine, TEXT("SMesh_Magazine"), SocketMagazine);
	Helpers::CreateComponent(this, &SMeshLaser, TEXT("SMesh_Laser"), SocketLaser);
	Helpers::CreateComponent(this, &SMeshGrip, TEXT("SMesh_Grip"), SocketGrip);
	Helpers::CreateComponent(this, &SMeshMuzzle, TEXT("SMesh_Muzzle"), SocketMuzzle);
	Helpers::CreateComponent(this, &SMeshScope, TEXT("SMesh_Scope"), SocketScope);

	// Base Actor Sample Mesh init
	USkeletalMesh* weaponMesh;
	Helpers::GetAsset(&weaponMesh, TEXT("SkeletalMesh'/Game/InfimaGames/AnimatedLowPolyWeapons/Art/Weapons/ARs/SK_AR_01.SK_AR_01'"));
	Weapon->SetSkeletalMesh(weaponMesh);

	// OnConstruction load asset
	CacheWeaponPresetLoadAssetConstruct();
	CacheWeaponInformationLoadAssetConstruct();
	TryUpdateAttachmentMagazineLoadAssetConstruct();
	TryUpdateAttachmentIronsightsLoadAssetConstruct();
	SettingsAnimationLoadAssetConstruct();
	UpdateAttachmentScopeLoadAssetConstruct();
    UpdateAttachmentMazzuleLoadAssetConstruct();
	UpdateAttachmentLaserLoadAssetConstruct();
	UpdateAttachmentGripLoadAssetConstruct();
	UpdateSkinLoadAssetConstruct();
}


// Called when the game starts or when spawned
void AWeaponBase::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AWeaponBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AWeaponBase::OnConstruction(const FTransform& Transform)
{
    Super::OnConstruction(Transform);

	GetComponents(ComponentsAttachments);

	UpdateSocketAttachments();
	CacheWeaponPreset();
	CacheWeaponInformation();
	TryUpdateAttachmentMagazine();
	TryUpdateAttachmentIronsights();
	SettingsAnimation();
	UpdateAttachmentScope();
	UpdateAttachmentMazzule();
	UpdateAttachmentLaser();
	UpdateAttachmentGrip();
	UpdateSkin();
}

void AWeaponBase::PostEditChangeProperty(struct FPropertyChangedEvent& PropertyChangedEvent)
{
    Super::PostEditChangeProperty(PropertyChangedEvent);

	OnConstruction(this->GetTransform());
}

void AWeaponBase::UpdateSocketAttachments()
{
	SocketScope->AttachToComponent(GetScopeParent(), FAttachmentTransformRules::SnapToTargetIncludingScale, SocketNameScope);
	SocketGrip->AttachToComponent(GetGripParent(), FAttachmentTransformRules::SnapToTargetIncludingScale, SocketNameGrip);
	SocketLaser->AttachToComponent(GetGripParent(), FAttachmentTransformRules::SnapToTargetIncludingScale, SocketNameLaser);
	SocketMuzzle->AttachToComponent(GetMuzzleParent(), FAttachmentTransformRules::SnapToTargetIncludingScale, SocketNameMuzzle);
	SMeshIronsight->AttachToComponent(Weapon, FAttachmentTransformRules::SnapToTargetIncludingScale, SocketNameIronsights);
}

UMeshComponent* AWeaponBase::GetScopeParent()
{
	return Weapon;
}

UMeshComponent* AWeaponBase::GetGripParent()
{
	return Weapon;
}

UMeshComponent* AWeaponBase::GetMuzzleParent()
{
	return Weapon;
}

void AWeaponBase::CacheWeaponPreset()
{
	FSPreset* findPreset = WeaponPresetRowHandle.GetRow<FSPreset>("");
	if (!findPreset)
		return;
	WeaponPreset = *findPreset;
	WeaponPresetOverride.RowHandleSkin.DataTable = findPreset->RowHandleSkin.DataTable;
	WeaponPresetOverride.Attachments.RowHandleMeshScope.DataTable = findPreset->Attachments.RowHandleMeshScope.DataTable;
    WeaponPresetOverride.Attachments.RowHandleMeshMuzzle.DataTable = findPreset->Attachments.RowHandleMeshMuzzle.DataTable;
    WeaponPresetOverride.Attachments.RowHandleMeshGrip.DataTable = findPreset->Attachments.RowHandleMeshGrip.DataTable;
    WeaponPresetOverride.Attachments.RowHandleMeshLaser.DataTable = findPreset->Attachments.RowHandleMeshLaser.DataTable;
}

void AWeaponBase::CacheWeaponPresetLoadAssetConstruct()
{
    UDataTable* weaponPresetDT;
	Helpers::GetAsset(&weaponPresetDT, TEXT("DataTable'/Game/Projz/DataTables/DT_WEP_CPP_Presets.DT_WEP_CPP_Presets'"));
	verifyf(weaponPresetDT, L"WeaopnPresetDT invalid asset");
	WeaponPresetRowHandle.DataTable = weaponPresetDT;
 	WeaponPresetRowHandle.RowName = weaponPresetDT->GetRowNames()[0];

	CacheWeaponPreset();
}

void AWeaponBase::CacheWeaponInformation()
{
	FSInformation* findInfo = WeaponInfoRowHandle.GetRow<FSInformation>("");
	if (!findInfo)
		return;
	WeaponInformation = *findInfo;
	ScopeSettingsRowHandle.DataTable = WeaponInformation.SettingsAttachments.DataTableSettingsScope;
	MuzzleSettingsRowHandle.DataTable = WeaponInformation.SettingsAttachments.DataTableSettingsMuzzle;
	LaserSettingsRowHandle.DataTable = WeaponInformation.SettingsAttachments.DataTableSettingsLaser;
	GripSettingsRowHandle.DataTable = WeaponInformation.SettingsAttachments.DataTableSettingsGrip;
}

void AWeaponBase::CacheWeaponInformationLoadAssetConstruct()
{
    UDataTable* weaponInfoDT;
    Helpers::GetAsset(&weaponInfoDT, TEXT("DataTable'/Game/Projz/DataTables/DT_WEP_CPP_Information.DT_WEP_CPP_Information'"));
    verifyf(weaponInfoDT, L"WeaponInfoDT invalid asset");
	WeaponInfoRowHandle.DataTable = weaponInfoDT;
	WeaponInfoRowHandle.RowName = weaponInfoDT->GetRowNames()[0];

	CacheWeaponInformation();
}

void AWeaponBase::TryUpdateAttachmentMagazine()
{
	FSMagazine* findMag = MagazineSettingRowHandle.GetRow<FSMagazine>("");
	if (!findMag)
		return;
	MagazineSettings = *findMag;
	SMeshMagazine->SetStaticMesh(MagazineSettings.Mesh);
}

void AWeaponBase::TryUpdateAttachmentMagazineLoadAssetConstruct()
{
    UDataTable* weaponMagazineDT;
    Helpers::GetAsset(&weaponMagazineDT, TEXT("DataTable'/Game/Projz/DataTables/DT_WEP_CPP_Magazines.DT_WEP_CPP_Magazines'"));
	verifyf(weaponMagazineDT, L"WeaponMagDT invalid asset");
	MagazineSettingRowHandle.DataTable = weaponMagazineDT;
	MagazineSettingRowHandle.RowName = TEXT("Hidden");

	TryUpdateAttachmentMagazine();
}

void AWeaponBase::TryUpdateAttachmentIronsights()
{
	if (!IronsightSettingsRowHandle.DataTable)
		return;

	ShowAttachmentIronsights = !(IronsightSettingsRowHandle.RowName == TEXT("Hidden"));

	FSIronsights* findIron = IronsightSettingsRowHandle.GetRow<FSIronsights>("");
	if (!findIron)
		return;
	IronsightSettings = *findIron;
	SMeshIronsight->SetStaticMesh(IronsightSettings.Mesh);
}

void AWeaponBase::TryUpdateAttachmentIronsightsLoadAssetConstruct()
{
    UDataTable* weaponIronsightDT;
    Helpers::GetAsset(&weaponIronsightDT, TEXT("DataTable'/Game/Projz/DataTables/DT_WEP_CPP_Ironsights.DT_WEP_CPP_Ironsights'"));
    verifyf(weaponIronsightDT, L"WeaponIronDT invalid asset");
	IronsightSettingsRowHandle.DataTable = weaponIronsightDT;
	IronsightSettingsRowHandle.RowName = weaponIronsightDT->GetRowNames()[1];

	TryUpdateAttachmentIronsights();
}

void AWeaponBase::SettingsAnimation()
{
	if (!WeaponInformation.SettingsAnimationBlueprint.RowHandleSettingsAnimation.DataTable)
		return;
	FName rowName = WeaponInformation.SettingsAnimationBlueprint.RowHandleSettingsAnimation.RowName;
	FSAnimationSettings* findSetAnimation = WeaponInformation.SettingsAnimationBlueprint.RowHandleSettingsAnimation.DataTable->FindRow<FSAnimationSettings>(rowName, "");
	if (!findSetAnimation)
		return;
	AnimationSettings = *findSetAnimation;
}

void AWeaponBase::SettingsAnimationLoadAssetConstruct()
{
	SettingsAnimation();
}

void AWeaponBase::UpdateAttachmentScope()
{
	if (bOverridePreset && TryUpdateAttachmentScope(WeaponPresetOverride))
		return;

	if (TryUpdateAttachmentScope(WeaponPreset))
		return;

	GetIronsightsScopeSettings();
}

void AWeaponBase::UpdateAttachmentScopeLoadAssetConstruct()
{
// 	ScopeSettingsRowHandle.DataTable = WeaponInformation.SettingsAttachments.DataTableSettingsScope;
// 	ScopeSettingsRowHandle.RowName = WeaponPreset.Attachments.RowHandleMeshScope.RowName;

	UpdateAttachmentScope();
}

bool AWeaponBase::TryUpdateAttachmentScope(FSPreset& Preset)
{
	if (!WeaponInformation.SettingsAttachments.DataTableSettingsScope)
	{
		return false;
	}

	FDataTableRowHandle rowHandleSettings;
	rowHandleSettings.DataTable = WeaponInformation.SettingsAttachments.DataTableSettingsScope;
	rowHandleSettings.RowName = Preset.Attachments.RowHandleMeshScope.RowName;

	FSScope* findScope = rowHandleSettings.GetRow<FSScope>("");
	if (!findScope)
	{
		if (Preset.Attachments.RowHandleMeshScope.RowName != TEXT("Hidden"))
			return false;

		GetIronsightsScopeSettings();
		rowHandleSettings = ScopeSettingsRowHandle;
	}

	FSMesh* findScopeMesh = Preset.Attachments.RowHandleMeshScope.GetRow<FSMesh>("");
	if (!findScopeMesh)
		return false;

	FDataTableRowHandle rowHandleMesh;
	rowHandleMesh = Preset.Attachments.RowHandleMeshScope;

	OnSwapAttachmentScope(rowHandleMesh, rowHandleSettings);

	return true;
}

void AWeaponBase::GetIronsightsScopeSettings()
{
	if (!IronsightSettings.RowHandleSettingsScope.DataTable)
		return;

	FSScope* findScope = IronsightSettings.RowHandleSettingsScope.GetRow<FSScope>("");
	if (!findScope)
		return;

	ScopeSettings = *findScope;
	ScopeSettingsRowHandle = IronsightSettings.RowHandleSettingsScope;
}

void AWeaponBase::OnSwapAttachmentScope(FDataTableRowHandle Mesh, FDataTableRowHandle Settings)
{
	SetScopeMeshRowHandle(Mesh);
	SetScopeSettingsRowHandle(Settings);
}

void AWeaponBase::SetScopeMeshRowHandle(FDataTableRowHandle Mesh)
{
	ScopeMeshRowHandle = Mesh;
	if (!ScopeMeshRowHandle.DataTable)
		return;

	SMeshScope->SetStaticMesh(ScopeMeshRowHandle.GetRow<FSMesh>("")->Mesh);
	ShowAttachmentIronsights = (ScopeMeshRowHandle.RowName != TEXT("Hidden"));
}

void AWeaponBase::SetScopeSettingsRowHandle(FDataTableRowHandle Settings)
{
	ScopeSettingsRowHandle = Settings;
	if (!ScopeSettingsRowHandle.DataTable)
		return;

	FSScope* findScopeSet = ScopeSettingsRowHandle.GetRow<FSScope>("");
	if (!findScopeSet)
		return;

	ScopeSettings = *findScopeSet;
}

void AWeaponBase::UpdateAttachmentMazzule()
{
	if (bOverridePreset && TryUpdateAttachmentMuzzle(WeaponPresetOverride))
		return;

	if (TryUpdateAttachmentMuzzle(WeaponPreset))
		return;
}

void AWeaponBase::UpdateAttachmentMazzuleLoadAssetConstruct()
{
	UpdateAttachmentMazzule();
}

bool AWeaponBase::TryUpdateAttachmentMuzzle(FSPreset& Preset)
{
	if (!WeaponInformation.SettingsAttachments.DataTableSettingsMuzzle)
		return false;

	FSMuzzle* findMuzzle = WeaponInformation.SettingsAttachments.DataTableSettingsMuzzle->FindRow<FSMuzzle>(Preset.Attachments.RowHandleMeshMuzzle.RowName, "");
	if (!findMuzzle)
	{
		MuzzleSettingsRowHandle = FDataTableRowHandle();
		MuzzleMeshRowHandle = FDataTableRowHandle();
		MuzzleSettings = FSMuzzle();
		return false;
	}
	
	FDataTableRowHandle rowHandleSettings;
	rowHandleSettings.DataTable = WeaponInformation.SettingsAttachments.DataTableSettingsMuzzle;
	rowHandleSettings.RowName = Preset.Attachments.RowHandleMeshMuzzle.RowName;

	FDataTableRowHandle rowHandleMesh;
	rowHandleMesh = Preset.Attachments.RowHandleMeshMuzzle;

	OnSwapAttachmentMuzzle(rowHandleMesh, rowHandleSettings);

	return true;
}

void AWeaponBase::OnSwapAttachmentMuzzle(FDataTableRowHandle Mesh, FDataTableRowHandle Settings)
{
	SetMuzzleMeshRowHandle(Mesh);
	SetMuzzleSettingsRowHandle(Settings);
}

void AWeaponBase::SetMuzzleMeshRowHandle(FDataTableRowHandle Mesh)
{
	MuzzleMeshRowHandle = Mesh;
	if (!MuzzleMeshRowHandle.DataTable)
		return;

	SMeshMuzzle->SetStaticMesh(MuzzleMeshRowHandle.GetRow<FSMesh>("")->Mesh);
}

void AWeaponBase::SetMuzzleSettingsRowHandle(FDataTableRowHandle Settings)
{
	MuzzleSettingsRowHandle = Settings;
	if (!MuzzleSettingsRowHandle.DataTable)
		return;

	FSMuzzle* findMuzzleSet = MuzzleSettingsRowHandle.GetRow<FSMuzzle>("");
	if (!findMuzzleSet)
		return;

	MuzzleSettings = *findMuzzleSet;
}

void AWeaponBase::UpdateAttachmentLaser()
{
	if (bOverridePreset && TryUpdateAttachmentLaser(WeaponPresetOverride))
		return;

	if (TryUpdateAttachmentLaser(WeaponPreset))
		return;
}

void AWeaponBase::UpdateAttachmentLaserLoadAssetConstruct()
{
	UpdateAttachmentLaser();
}

bool AWeaponBase::TryUpdateAttachmentLaser(FSPreset& Preset)
{
	if (!WeaponInformation.SettingsAttachments.DataTableSettingsLaser)
		return false;

	FDataTableRowHandle rowHandleSettings;
	rowHandleSettings.DataTable = WeaponInformation.SettingsAttachments.DataTableSettingsLaser;
	rowHandleSettings.RowName = Preset.Attachments.RowHandleMeshLaser.RowName;

	if (rowHandleSettings.GetRow<FSLaser>("") == nullptr)
	{ 
		if (Preset.Attachments.RowHandleMeshLaser.RowName != TEXT("Hidden"))
			return false;
	}

	if (!Preset.Attachments.RowHandleMeshLaser.DataTable)
		return false;

	if (Preset.Attachments.RowHandleMeshLaser.GetRow<FSMesh>("") == nullptr)
		return false;

	FDataTableRowHandle rowHandleMesh;
	rowHandleMesh = Preset.Attachments.RowHandleMeshLaser;

	OnSwapAttachmentLaser(rowHandleMesh, rowHandleSettings);

	return true;
}

void AWeaponBase::OnSwapAttachmentLaser(FDataTableRowHandle Mesh, FDataTableRowHandle Settings)
{
	SetLaserMeshRowHandle(Mesh);
	SetLaserSettingsRowHandle(Settings);
}

void AWeaponBase::SetLaserSettingsRowHandle(FDataTableRowHandle Settings)
{
	LaserSettingsRowHandle = Settings;

	if (!LaserSettingsRowHandle.DataTable)
		return;

	FSLaser* findLaser = LaserSettingsRowHandle.GetRow<FSLaser>("");
	if (!findLaser)
		return;

	LaserSettings = *findLaser;
}

void AWeaponBase::SetLaserMeshRowHandle(FDataTableRowHandle Mesh)
{
	LaserMeshRowHandle = Mesh;
	if (!LaserMeshRowHandle.DataTable)
		return;

	SMeshLaser->SetStaticMesh(LaserMeshRowHandle.GetRow<FSMesh>("")->Mesh);
}

void AWeaponBase::UpdateAttachmentGrip()
{
	if (bOverridePreset && TryUpdateAttachmentGrip(WeaponPresetOverride))
		return;

	if (TryUpdateAttachmentGrip(WeaponPreset))
		return;
}

void AWeaponBase::UpdateAttachmentGripLoadAssetConstruct()
{
	UpdateAttachmentGrip();
}

bool AWeaponBase::TryUpdateAttachmentGrip(FSPreset& Preset)
{
	if (!WeaponInformation.SettingsAttachments.DataTableSettingsGrip)
		return false;

	FDataTableRowHandle rowHandleSettings;
	rowHandleSettings.DataTable = WeaponInformation.SettingsAttachments.DataTableSettingsGrip;
	rowHandleSettings.RowName = Preset.Attachments.RowHandleMeshGrip.RowName;


	if (rowHandleSettings.GetRow<FSGrip>("") == nullptr)
	{
		if (Preset.Attachments.RowHandleMeshGrip.RowName != TEXT("Hidden"))
			return false;
	}

	if (!Preset.Attachments.RowHandleMeshGrip.DataTable)
		return false;

	if (Preset.Attachments.RowHandleMeshGrip.GetRow<FSMesh>("") == nullptr)
		return false;

	FDataTableRowHandle rowHandleMesh;
	rowHandleMesh = Preset.Attachments.RowHandleMeshGrip;

	OnSwapattachmentGrip(rowHandleMesh, rowHandleSettings);

	return true;
}

void AWeaponBase::OnSwapattachmentGrip(FDataTableRowHandle Mesh, FDataTableRowHandle Settings)
{
	SetGripSettingsRowHandle(Settings);
	SetGripMeshRowHandle(Mesh);
}

void AWeaponBase::SetGripSettingsRowHandle(FDataTableRowHandle Settings)
{
	GripSettingsRowHandle = Settings;
	if (!GripSettingsRowHandle.DataTable)
		return;

	FSGrip* findGrip = GripSettingsRowHandle.GetRow<FSGrip>("");
	if (!findGrip)
		return;

	GripSettings = *findGrip;
}

void AWeaponBase::SetGripMeshRowHandle(FDataTableRowHandle Mesh)
{
	GripMeshRowHandle = Mesh;
	if (!GripMeshRowHandle.DataTable)
		return;

	SMeshGrip->SetStaticMesh(GripMeshRowHandle.GetRow<FSMesh>("")->Mesh);
}

void AWeaponBase::UpdateSkin()
{
	if (bOverridePreset && TryUpdateSkin(WeaponPresetOverride))
		return;

	if (TryUpdateSkin(WeaponPreset))
		return;
}

void AWeaponBase::UpdateSkinLoadAssetConstruct()
{
	UpdateSkin();
}

bool AWeaponBase::TryUpdateSkin(FSPreset& Preset)
{
	if (!Preset.RowHandleSkin.DataTable)
		return false;

	if (Preset.RowHandleSkin.GetRow<FSSkin>("") == nullptr)
		return false;

	FDataTableRowHandle rowHandle;
	rowHandle = Preset.RowHandleSkin;

	SetSkinRowHandle(rowHandle);

	return true;
}

void AWeaponBase::SetSkinRowHandle(FDataTableRowHandle Skin)
{
	SkinRowHandle = Skin;

	FSSkin* findSkin = SkinRowHandle.GetRow<FSSkin>("");
	if (!findSkin)
		return;

	SkinSettings = *findSkin;

	UpdateMaterialFromSkin();
}

void AWeaponBase::UpdateMaterialFromSkin()
{
	CacheNewVisualLaserSettings();

	MapMaterialtoComponent(SMeshMagazine, SkinSettings.MaterialMapMagazine);
    MapMaterialtoComponent(SMeshLaser, SkinSettings.MaterialMapLaser);
    MapMaterialtoComponent(SMeshIronsight, SkinSettings.MaterialMapIronsights);
    MapMaterialtoComponent(SMeshGrip, SkinSettings.MaterialMapGrip);
    MapMaterialtoComponent(SMeshScope, SkinSettings.MaterialMapScope);
    MapMaterialtoComponent(SMeshMuzzle, SkinSettings.MaterialMapMuzzle);
    MapMaterialtoComponent(Weapon, SkinSettings.MaterialMapBody);
}

void AWeaponBase::CacheNewVisualLaserSettings()
{
	if (!SkinSettings.RowHandleSettingsLasersight.DataTable)
		return;

	FSLasersight* findLasersights = SkinSettings.RowHandleSettingsLasersight.GetRow<FSLasersight>("");
	if (!findLasersights)
		return;

	LaserSightsSettings = *findLasersights;

	if (!SkinSettings.RowHandleSettingsFlashlight.DataTable)
		return;

	FSFlashlight* findFlashlight = SkinSettings.RowHandleSettingsFlashlight.GetRow<FSFlashlight>("");
	if (!findFlashlight)
		return;

	FlashlightSettings = *findFlashlight;
}

void AWeaponBase::MapMaterialtoComponent(UPrimitiveComponent* Component, TMap<FName, UMaterialInstanceConstant*> MaterialMap)
{
	for (auto& Elem : MaterialMap)
	{
		Component->SetMaterialByName(Elem.Key, Elem.Value);
	}
}

void AWeaponBase::DebugAllComponents()
{
	if (!bDebugComponents)
		return;



}

void AWeaponBase::OnSpawnAttachmentComponents()
{
	TrySpawnComponentMuzzleFlash();
}

void AWeaponBase::TrySpawnComponentMuzzleFlash()
{
	if (!MuzzleSettings.FlashLight)
		return;

	if (!LightPointMuzzleFlash)
	{
		AddComponent<UPointLightComponent>(TEXT("Sample"), false, FTransform::FTransform());
	}
}

