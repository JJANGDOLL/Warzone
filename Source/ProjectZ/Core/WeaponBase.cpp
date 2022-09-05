// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/WeaponBase.h"
#include "Utilities/Global.h"

#include "Core/WeaponAttachmentBase.h"
#include "Core/WeaponBodyBase.h"
#include "Engine/SkeletalMesh.h"
#include "Components/MeshComponent.h"
#include "Kismet/DataTableFunctionLibrary.h"
#include "Components/PointLightComponent.h"
#include "Components/SpotLightComponent.h"
#include "Components/DecalComponent.h"
#include "Kismet/KismetMaterialLibrary.h"
#include "Materials/MaterialInstanceDynamic.h"
#include "Components/SceneCaptureComponent2D.h"
#include "GameFramework/Character.h"
#include "Engine/DataTable.h"
#include "Engine/EngineTypes.h"
#include "Kismet/KismetMathLibrary.h"
#include "Save/Loadout.h"
#include "Kismet/GameplayStatics.h"
#include "Components/TimelineComponent.h"
#include "Kismet/KismetArrayLibrary.h"
#include "Defines/Structs.h"
#include "Interfaces/ICharacter.h"
#include "Animation/AnimSequenceBase.h"
#include "Animation/AnimMontage.h"
#include "Sound/SoundCue.h"
#include "Utilities/ViewmodelHelper.h"
#include "Curves/CurveFloat.h"
#include "Defines/Enums.h"
#include "Components/AudioComponent.h"

#define MAKEDATATABLEROWHANDLE(Out, Table, Name) \
Out.DataTable = Table; \
Out.RowName = Name; 


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

	Helpers::CreateActorComponent(this, &ViewmodelHelper, TEXT("Viewmodel Helper"));

	Helpers::CreateActorComponent(this, &TLineScaleAttachmentsUp, TEXT("TLine Scale Attachments Up"));
	Helpers::CreateActorComponent(this, &TLineScaleAttachmentsDown, TEXT("TLine Scale Attachments Down"));

	// Base Actor Sample Mesh init
	USkeletalMesh* weaponMesh;
	Helpers::GetAsset(&weaponMesh, TEXT("SkeletalMesh'/Game/InfimaGames/AnimatedLowPolyWeapons/Art/Weapons/ARs/SK_AR_01.SK_AR_01'"));
	Weapon->SetSkeletalMesh(weaponMesh);



    AttachmentsUpFunction.BindUFunction(this, FName("SetAttachmentsScale"));
    AttachmentsDownFunction.BindUFunction(this, FName("SetAttachmentsScale"));


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
	DebugAllComponentsLoadAssetConstruct();
	UpdateAllPhysicalSettingsLoadAssetConstruct();
}


// Called when the game starts or when spawned
void AWeaponBase::BeginPlay()
{
	Super::BeginPlay();
	
	AmmunitionCurrent = MagazineSettings.AmmunitionTotal;

    FTimerHandle TimerHandle;
    GetWorld()->GetTimerManager().SetTimer(TimerHandle, [&]()
    {
    }, 0.01, false);

	OnSpawnAttachmentComponents();

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
	DebugAllComponents();
	UpdateAllPhysicalSettings();
    CacheWeaponSettings();
	CacheCharacterAbilities();

	Logger::Log(L"Objects");
	Logger::Log(LightPointMuzzleFlash);
    Logger::Log(LightSpotFlashlight);
    Logger::Log(StaticMeshLasersightBeam);
    Logger::Log(Decal);
    Logger::Log(SceneCaptureScope);
}

void AWeaponBase::PostEditChangeProperty(struct FPropertyChangedEvent& PropertyChangedEvent)
{
    Super::PostEditChangeProperty(PropertyChangedEvent);

// 	OnConstruction(this->GetTransform());
}

void AWeaponBase::OnChangeSettingsPhysical(FDataTableRowHandle RowHandle)
{
	OnChangeSettingsPhysicalBody(RowHandle);
	OnChangeSettingsPhysicalAttachments(RowHandle);
}

FSAbilities AWeaponBase::GetCharacterAbilities()
{
	return PlayerCharacterAbilities;
}

UDataTable* AWeaponBase::GetCharacterAnimationMontages()
{
	return WeaponInformation.SettingsAnimationBlueprint.DataTableMontagesCharacter;
}

void AWeaponBase::OnMontageStopAll(float BlendTime)
{
	Weapon->GetAnimInstance()->Montage_Stop(BlendTime);
}

void AWeaponBase::OnStopAudioPlaying()
{
	if (AudioComponentPlaying)
		AudioComponentPlaying->Stop();
}

bool AWeaponBase::CanInteract()
{
	return bCanBePickedUp;
}

EInteractionType AWeaponBase::GetIteractionType()
{
	return EInteractionType::WeaponPickup;
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

	FSMesh* findMesh = GripMeshRowHandle.GetRow<FSMesh>("");
	if(findMesh)
		SMeshGrip->SetStaticMesh(findMesh->Mesh);
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
	{
		return;
	}

	OnSpawnAttachmentComponents();
	if (LightPointMuzzleFlash)
		LightPointMuzzleFlash->SetVisibility(true);

	if (LightSpotFlashlight)
		LightSpotFlashlight->SetVisibility(true);

	if (StaticMeshLasersightBeam)
	{
		StaticMeshLasersightBeam->SetVisibility(true);
		StaticMeshLasersightBeam->SetWorldScale3D(FVector(20.f, 1.f, 1.f));
	}
}

void AWeaponBase::DebugAllComponentsLoadAssetConstruct()
{
// 	Helpers::CreateActorComponent(this, &LightPointMuzzleFlash, TEXT("LightPointMuzzleFlash"));
}

void AWeaponBase::OnSpawnAttachmentComponents()
{
	if (!bDebugComponents)
		return;

    TrySpawnComponentMuzzleFlash();
	TrySpawnComponentFlashlight();
	TrySpawnComponentsLasersight();
	TrySpawnScopeRenderTarget();
}

void AWeaponBase::TrySpawnComponentMuzzleFlash()
{
	if (!MuzzleSettings.FlashLight)
		return;

	if (!LightPointMuzzleFlash)
	{
        LightPointMuzzleFlash = NewObject<UPointLightComponent>(this, UPointLightComponent::StaticClass());
		LightPointMuzzleFlash->AttachToComponent(SMeshMuzzle, FAttachmentTransformRules::SnapToTargetIncludingScale, TEXT("SOCKET_Emitter"));
		LightPointMuzzleFlash->Intensity = 250.f;
		LightPointMuzzleFlash->SetLightColor(FLinearColor(1.0f, 0.610496f, 0.018164f));
		LightPointMuzzleFlash->SetAttenuationRadius(1100.f);
		LightPointMuzzleFlash->SetTemperature(3800.f);
		LightPointMuzzleFlash->bUseTemperature = true;



		Logger::Log("Create LightPointMuzzleFlash");
	}

	LightPointMuzzleFlash->SetRelativeLocation(MuzzleSettings.FlashLightRelativeLocation);
}

void AWeaponBase::TrySpawnComponentFlashlight()
{
	if (!LightSpotFlashlight)
	{
		if (LaserSettings.Flashlight)
		{
			LightSpotFlashlight = NewObject<USpotLightComponent>(this, USpotLightComponent::StaticClass());
			LightSpotFlashlight->Intensity = 80.0f;
			LightSpotFlashlight->SetAttenuationRadius(2500.f);
			LightSpotFlashlight->InnerConeAngle = 8.f;
			LightSpotFlashlight->OuterConeAngle = 20.f;
			LightSpotFlashlight->SetVisibility(false);

			LightSpotFlashlight->SetRelativeLocation(LaserSettings.RelativeLocation);
			SetLightSpotFlashLight();
		}
	}
	else
	{
		if (!LaserSettings.Flashlight)
		{
			LightSpotFlashlight->SetVisibility(false);
		}
	}
}

void AWeaponBase::SetLightSpotFlashLight()
{
	if (LightSpotFlashlight)
		LightSpotFlashlight->AttachToComponent(SMeshLaser, FAttachmentTransformRules::SnapToTargetIncludingScale, TEXT("SOCKET_Laser"));
}

void AWeaponBase::TrySpawnComponentsLasersight()
{
	if (!LaserSettings.Lasersight)
	{
		if (StaticMeshLasersightBeam)
		{
			StaticMeshLasersightBeam->SetVisibility(false);
		}
		if (Decal)
		{
			Decal->SetVisibility(false);
		}
	}
	else
	{
        PrintLine();

		if (!StaticMeshLasersightBeam)
		{
			PrintLine();
            StaticMeshLasersightBeam = NewObject<UStaticMeshComponent>(this, UStaticMeshComponent::StaticClass());

			UStaticMesh* lasersightMesh;
			Helpers::GetAssetDynamic(&lasersightMesh, TEXT("StaticMesh'/Game/InfimaGames/LowPolyShooterPack/Art/Effects/Models/SM_Laser_Beam.SM_Laser_Beam'"));

			UMaterialInstanceConstant* lasersightMaterial;
			Helpers::GetAssetDynamic(&lasersightMaterial, TEXT("MaterialInstanceConstant'/Game/InfimaGames/LowPolyShooterPack/Art/Effects/Materials/MI_Laser_Beam.MI_Laser_Beam'"));
			lasersightMesh->SetMaterial(0, lasersightMaterial);

			StaticMeshLasersightBeam->SetStaticMesh(lasersightMesh);

			StaticMeshLasersightBeam->SetRelativeLocation(LaserSettings.RelativeLocation);
			StaticMeshLasersightBeam->AttachToComponent(SMeshLaser, FAttachmentTransformRules::SnapToTargetIncludingScale, TEXT("SOCKET_Laser"));
		}

		StaticMeshLasersightBeam->CreateDynamicMaterialInstance(0, LaserSightsSettings.LasersightBeamMaterial)->SetVectorParameterValue(TEXT("Beam Color"), LaserSightsSettings.LasersightBeamColor);
		
		DotMaterialDynamic = UKismetMaterialLibrary::CreateDynamicMaterialInstance(GetWorld(), LaserSightsSettings.LasersightDotMaterial, TEXT("Laser Dot"));

		if (DotMaterialDynamic)
		{
			DotMaterialDynamic->SetVectorParameterValue(TEXT("Dot Color"), LaserSightsSettings.LasersightDotColor);
			if (Decal)
			{
				Decal->SetDecalMaterial(DotMaterialDynamic);
			}
		}
	}
}

void AWeaponBase::TrySpawnScopeRenderTarget()
{
	if (!ScopeSettings.RenderTargetRequired)
	{
		if (SceneCaptureScope)
		{
			SceneCaptureScope->DestroyComponent();
		}
		return;
	}

	if (!SceneCaptureScope)
	{
		SceneCaptureScope = NewObject<USceneCaptureComponent2D>(this, USceneCaptureComponent2D::StaticClass());
		SceneCaptureScope->PrimitiveRenderMode = ESceneCapturePrimitiveRenderMode::PRM_RenderScenePrimitives;
		SceneCaptureScope->bCaptureEveryFrame = false;
		SceneCaptureScope->bCaptureOnMovement = false;
		SceneCaptureScope->bAlwaysPersistRenderingState = true;
		SceneCaptureScope->SetVisibility(false);

		SceneCaptureScope->AttachToComponent(SMeshScope, FAttachmentTransformRules::SnapToTargetIncludingScale, TEXT("SOCKET_Render"));
		SceneCaptureScope->SetRelativeRotation(FRotator(0.f, 90.f, 0.f));

		SceneCaptureScope->TextureTarget = ScopeSettings.RenderTargetTexture;
		SceneCaptureScope->FOVAngle = ScopeSettings.RenderTargetFieldOfView;
		SceneCaptureScope->HiddenActors.AddUnique(this);
		SceneCaptureScope->HiddenActors.AddUnique(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	}
	else
	{
        SceneCaptureScope->TextureTarget = ScopeSettings.RenderTargetTexture;
        SceneCaptureScope->FOVAngle = ScopeSettings.RenderTargetFieldOfView;
	}
}

void AWeaponBase::UpdateAllPhysicalSettings()
{
	PrintLine();
    Logger::Log(RowHandlePhysicalAttachments.DataTable);

	OnChangeSettingsPhysicalAttachments(RowHandlePhysicalAttachments);
	OnChangeSettingsPhysicalBody(RowHandlePhysicalWeapon);
}

void AWeaponBase::UpdateAllPhysicalSettingsLoadAssetConstruct()
{
	UDataTable* physicsSettingsDT;

	Helpers::GetAsset(&physicsSettingsDT, TEXT("DataTable'/Game/Projz/DataTables/DT_WEP_CPP_Physical.DT_WEP_CPP_Physical'"));
	verifyf(physicsSettingsDT, L"Physics Settings DT invalid asset");

    RowHandlePhysicalWeapon.DataTable = physicsSettingsDT;
    RowHandlePhysicalWeapon.RowName = TEXT("Viewmodel");

    RowHandlePhysicalAttachments.DataTable = physicsSettingsDT;
    RowHandlePhysicalAttachments.RowName = TEXT("Viewmodel");
}

void AWeaponBase::OnChangeSettingsPhysicalAttachments(FDataTableRowHandle Value)
{
    Logger::Log(Value.DataTable);

	SetRowHandlePhysicalAttachments(Value);
}

void AWeaponBase::OnChangeSettingsPhysicalBody(FDataTableRowHandle Value)
{
	SetRowHandlePhysicalWeapon(Value);
}



void AWeaponBase::SetRowHandlePhysicalAttachments(FDataTableRowHandle Value)
{
	Logger::Log(Value.DataTable);

	RowHandlePhysicalAttachments = Value;

	FSPhysical findPhysical = GetSettingsPhysical(RowHandlePhysicalAttachments);

	for (auto& elem : ComponentsAttachments)
	{
		UpdateComponentPhysicalSettings(elem, findPhysical);
	}
}

void AWeaponBase::SetRowHandlePhysicalWeapon(FDataTableRowHandle Value)
{
    Logger::Log(Value.DataTable);

	RowHandlePhysicalWeapon = Value;

    FSPhysical findPhysical = GetSettingsPhysical(RowHandlePhysicalWeapon);
	UpdateComponentPhysicalSettings(Weapon, findPhysical);
}

FSPhysical AWeaponBase::GetSettingsPhysical(FDataTableRowHandle RowHandle)
{
	if (!RowHandle.DataTable)
		return FSPhysical();

	FSPhysical* findPhysical = RowHandle.GetRow<FSPhysical>("");
	if (!findPhysical)
		return FSPhysical();

	return *findPhysical;
}

void AWeaponBase::UpdateComponentPhysicalSettings(UPrimitiveComponent* Component, FSPhysical Settings)
{
	Component->SetSimulatePhysics(Settings.SimulatePhysics);
	Component->SetCastShadow(Settings.CastShadow);
	Component->SetCollisionProfileName(Settings.CollisionProfileName.Name, true);
	Component->SetVisibility(Settings.Visible, false);
	Component->SetHiddenInGame(Settings.HiddenInGame, false);
	Component->SetReceivesDecals(Settings.ReceivesDecals);
	Component->SetRenderCustomDepth(Settings.RenderCustomDepth);
}

void AWeaponBase::CacheWeaponSettings()
{
	if (!WeaponInformation.RowHandleSettingsWeapon.DataTable)
		return;

	FSWeaponSettings* findWeaponSettings = WeaponInformation.RowHandleSettingsWeapon.GetRow<FSWeaponSettings>("");
	if (!findWeaponSettings)
		return;

	WeaponSettings = *findWeaponSettings;
}

void AWeaponBase::CacheCharacterAbilities()
{
	if (!WeaponInformation.RowHandleSettingsCharacterAbilities.DataTable)
		return;

	FSAbilities* findAbilities = WeaponInformation.RowHandleSettingsCharacterAbilities.GetRow<FSAbilities>("");
	if (!findAbilities)
		return;

	PlayerCharacterAbilities = *findAbilities;

	for (auto& elem : PlayerCharacterAbilities.AbilityKnife.TagsRequired)
	{
		Logger::Log(elem.ToString());
	}
}

void AWeaponBase::OnAimingStop()
{
	if (!SMeshScope)
		return;

	SMeshScope->SetMaterialByName(ScopeSettings.RenderMaterialSlotName, ScopeSettings.RenderMaterialReplacement);
	ScopeRenderTargetDisable();
}

void AWeaponBase::ScopeRenderTargetDisable()
{
	if (!SceneCaptureScope)
		return;

	SceneCaptureScope->bCaptureOnMovement = false;
	SceneCaptureScope->SetVisibility(false);
}

void AWeaponBase::TryCacheMagazineMaterials()
{
	if (!SMeshMagazine)
		return;

	
	MaterialsDefaultMagazine = SMeshMagazine->GetMaterials();
}

void AWeaponBase::OnUpdate()
{
	UpdateSpread();
	OnUpdateLaser();
}

void AWeaponBase::UpdateSpread()
{
	if (WeaponSettings.FireMode == EFireMode::Semi)
	{
		SpreadMultiplier = (bAiming ?  WeaponSettings.SpreadAimingMultiplier * ShotCount : ShotCount * MovementSpread);
	}
	else
	{
		if (!WeaponSettings.SpreadCurve)
			return;

		float tempF1 = 1.f;
		if (bAiming)
			tempF1 = WeaponSettings.SpreadAimingMultiplier;

		float tempF2 = tempF1 * WeaponSettings.SpreadCurve->GetFloatValue(FMath::Clamp<float>(ShotCount / MagazineSettings.AmmunitionTotal, 0.f, 1.f));

		if (!bAiming)
			tempF2 += MovementSpread;

		SpreadMultiplier = tempF2;
	}
}

void AWeaponBase::OnUpdateLaser()
{
	if (!bLaserOn)
	{
		Disablelaser();
	}
	else
	{
		UpdateLaserSight();
		UpdateFlashlight();
	}
}

void AWeaponBase::Disablelaser()
{
	bLaserOn = false;

	if (!LaserSettings.Flashlight)
		return;

	if (LightSpotFlashlight)
		LightSpotFlashlight->SetVisibility(false);

	if (!LaserSettings.Lasersight)
		return;

	if (StaticMeshLasersightBeam)
		StaticMeshLasersightBeam->SetWorldScale3D(FVector(0.f, 0.f, 0.f));

	if (Decal)
		Decal->SetVisibility(false);
}

void AWeaponBase::UpdateLaserSight()
{
	if (!LaserSettings.Lasersight)
		return;

	EventServerSpawnLasersight();
	
	if (!StaticMeshLasersightBeam)
		return;

	StaticMeshLasersightBeam->SetVisibility(true);
	UpdateLasersightProperties();
}

void AWeaponBase::UpdateFlashlight()
{
	if (!LaserSettings.Flashlight)
		return;

	if (LightSpotFlashlight)
		LightSpotFlashlight->SetVisibility(true);
}

void AWeaponBase::EventServerSpawnLasersight()
{
	if (Decal)
		return;

	if (!DotMaterialDynamic)
		return;

	Decal = UGameplayStatics::SpawnDecalAtLocation(GetWorld(), DotMaterialDynamic, FVector(1.f, 1.f, 1.f), FVector(0.f, 0.f, 0.f), FRotator(0.f, 90.f, 0.f));
	Decal->SetFadeScreenSize(0.f);
}

void AWeaponBase::UpdateLasersightProperties()
{
	if (!Decal)
		return;

	GetWorld()->LineTraceSingleByChannel(
		Result,
		SMeshLaser->GetSocketTransform(TEXT("SOCKET_Laser"), RTS_World).GetLocation(),
		SMeshLaser->GetSocketTransform(TEXT("SOCKET_Laser"), RTS_World).GetLocation() + SMeshLaser->GetSocketTransform(TEXT("SOCKET_Laser"), RTS_World).GetRotation().GetForwardVector() * 10000.f,
		ECollisionChannel::ECC_GameTraceChannel1
	);

	Decal->SetVisibility(Result.bBlockingHit);
	if (!Result.bBlockingHit)
	{
		StaticMeshLasersightBeam->SetWorldScale3D(FVector(10000.f, 0.f, LaserSightsSettings.LasersightBeamThickness));
	}
	else
	{
		StaticMeshLasersightBeam->SetWorldScale3D(FVector(Result.Distance / 20.f, LaserSightsSettings.LasersightBeamThickness, LaserSightsSettings.LasersightBeamThickness));
		Decal->SetWorldRotation(UKismetMathLibrary::MakeRotFromX(Result.Normal));
		Decal->SetRelativeScale3D(FVector(Result.Distance * LaserSightsSettings.LasersightDotSizeMultiplier + LaserSightsSettings.LasersightDotSizeBase));

	}    
}

void AWeaponBase::OnEquipped()
{
	EventEquipped();
}

void AWeaponBase::EventEquipped()
{
	TryHideMagazine(bHiddenMagazine);
}

void AWeaponBase::TryHideMagazine(bool Hide)
{
	static UDataTable* physicalWEPDT;
	if (!physicalWEPDT)
		Helpers::GetAssetDynamic(&physicalWEPDT, TEXT("DataTable'/Game/Projz/DataTables/DT_WEP_CPP_Physical.DT_WEP_CPP_Physical'"));

	if (Hide)
	{
		FDataTableRowHandle param;
		param.DataTable = physicalWEPDT;
		param.RowName = TEXT("Hidden");

		FSPhysical findPhysical = GetSettingsPhysical(param);
		UpdateComponentPhysicalSettings(SMeshMagazine, findPhysical);
	}
	else
	{
		UpdateComponentPhysicalSettings(SMeshMagazine, GetSettingsPhysical(RowHandlePhysicalAttachments));
	}

}

void AWeaponBase::OnUnequipped()
{
	Disablelaser();
	OnAimingStop();
}

void AWeaponBase::OnUpdateAmmunition(bool Fill, int32 Amount)
{
	UpdateAmmunitionCurrent(Fill, Amount);
}

void AWeaponBase::UpdateAmmunitionCurrent(bool Fill, int32 Amount)
{
	if (Fill)
	{
		AmmunitionCurrent = GetAmmunitionTotal();
	}
	else
	{
		AmmunitionCurrent = FMath::Clamp<int32>(AmmunitionCurrent + Amount, 0, GetAmmunitionTotal());
		bSlideRackedVisually = IsOutOfAmmunition();
		bSlideRacked = bSlideRackedVisually;
	}


}

int32 AWeaponBase::GetAmmunitionTotal()
{
	return MagazineSettings.AmmunitionTotal;
}

bool AWeaponBase::IsOutOfAmmunition()
{
	return AmmunitionCurrent == 0;
}

void AWeaponBase::TryUpdateAmmunitionVisual()
{
	if (!MagazineSettings.AmmunitionVisualUpdate)
		return;

	UpdateCalculation();
	UpdateBulletMaterials();
}

void AWeaponBase::UpdateCalculation()
{
	if (AmmunitionCurrent == 0)
	{
		Calculation = 0;
		return;
	}
	
	int32 matAmmuSI = SMeshMagazine->GetNumMaterials() - MagazineSettings.AmmunitionVisualStartingIndex;

	Calculation = matAmmuSI - UKismetMathLibrary::FCeil(matAmmuSI * (AmmunitionCurrent / MagazineSettings.AmmunitionTotal)) + MagazineSettings.AmmunitionVisualStartingIndex;
}

void AWeaponBase::UpdateBulletMaterials()
{
	for (int i = MagazineSettings.AmmunitionVisualStartingIndex; i < SMeshMagazine->GetNumMaterials() - 1; i++)
	{
		if (i < Calculation)
		{
			SMeshMagazine->SetMaterial(i, MagazineSettings.AmmunitionVisualHiddenMaterial);
		}
		else
		{
			SMeshMagazine->SetMaterial(i, MaterialsDefaultMagazine[i]);
		}
	}
}

void AWeaponBase::OnSaveLoadout()
{
	SaveLoadout();
}

void AWeaponBase::SaveLoadout()
{
	TSubclassOf<ULoadout> loadout;
	SaveObject = Cast<ULoadout>(UGameplayStatics::CreateSaveGameObject(loadout));

	SaveObject->NameGrip = GripMeshRowHandle.RowName;
	SaveObject->NameLaser = LaserMeshRowHandle.RowName;
	SaveObject->NameMuzzle = MuzzleMeshRowHandle.RowName;
	SaveObject->NameScope = ScopeMeshRowHandle.RowName;

	UGameplayStatics::SaveGameToSlot(SaveObject, TEXT("Weapon_Loadout"), 0);
}

void AWeaponBase::OnWeaponDrop(FVector ThrowImpulse, FVector AngularImpulse)
{
	WeaponDrop(ThrowImpulse, AngularImpulse);
}

void AWeaponBase::WeaponDrop(FVector Impulse, FVector AngularImpulse)
{
	DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
	OnSetCanInteract(true);

	static UDataTable* physicsDT;
	if(!physicsDT)
		Helpers::GetAssetDynamic(&physicsDT, TEXT("DataTable'/Game/Projz/DataTables/DT_WEP_CPP_Physical.DT_WEP_CPP_Physical'"));

	FDataTableRowHandle param;
	param.DataTable = physicsDT;
	param.RowName = TEXT("Physics");

	OnChangeSettingsPhysicalBody(param);
	OnChangeSettingsPhysicalAttachments(param);

	Weapon->AddImpulse(Impulse * Weapon->GetMass());

	Weapon->AddAngularImpulse(AngularImpulse);
}

void AWeaponBase::OnSetCanInteract(bool Value)
{
	bCanBePickedUp = Value;
}

void AWeaponBase::OnEquipSavedLoadout()
{
// 	if (!TLineScaleAttachmentsDown)
// 		TLineScaleAttachmentsDown = NewObject<UTimelineComponent>();
		
	TLineScaleAttachmentsDown->PlayFromStart();

	UKismetSystemLibrary::RetriggerableDelay(GetWorld(), TLineScaleAttachmentsDown->GetTimelineLength(), FLatentActionInfo());

	TryLoadLoadout();
}

void AWeaponBase::TryLoadLoadout()
{
	ULoadout* loadout = Cast<ULoadout>(UGameplayStatics::LoadGameFromSlot(TEXT("Weapon_Loadout"), 0));
	if (!loadout)
		return;

	SaveObject = loadout;

	FDataTableRowHandle presetMuzzle;
	presetMuzzle.DataTable = WeaponPresetOverride.Attachments.RowHandleMeshMuzzle.DataTable;
	presetMuzzle.RowName = SaveObject->NameMuzzle;

	FDataTableRowHandle infoMuzzle;
	infoMuzzle.DataTable = WeaponInformation.SettingsAttachments.DataTableSettingsMuzzle;
	infoMuzzle.RowName = SaveObject->NameMuzzle;

	OnSwapAttachmentMuzzle(presetMuzzle, infoMuzzle);

	UpdateScopefromName(SaveObject->NameScope);

	FDataTableRowHandle q;
	FDataTableRowHandle w;

	MAKEDATATABLEROWHANDLE(q, WeaponPresetOverride.Attachments.RowHandleMeshGrip.DataTable, SaveObject->NameGrip);
	MAKEDATATABLEROWHANDLE(w, WeaponInformation.SettingsAttachments.DataTableSettingsGrip, SaveObject->NameGrip);

	OnSwapattachmentGrip(q, w);

    MAKEDATATABLEROWHANDLE(q, WeaponPresetOverride.Attachments.RowHandleMeshLaser.DataTable, SaveObject->NameLaser);
	MAKEDATATABLEROWHANDLE(w, WeaponInformation.SettingsAttachments.DataTableSettingsLaser, SaveObject->NameLaser);

	OnSwapAttachmentLaser(q, w);

}

void AWeaponBase::UpdateScopefromName(FName Name)
{
	if (Name == TEXT("Hidden"))
	{
		FDataTableRowHandle t;
		MAKEDATATABLEROWHANDLE(t, WeaponPresetOverride.Attachments.RowHandleMeshScope.DataTable, TEXT("Hidden"));
		OnSwapAttachmentScope(t, IronsightSettings.RowHandleSettingsScope);
		return;
	}

    FDataTableRowHandle q;
    MAKEDATATABLEROWHANDLE(q, WeaponPresetOverride.Attachments.RowHandleMeshScope.DataTable, Name);
	FDataTableRowHandle w;
    MAKEDATATABLEROWHANDLE(w, WeaponInformation.SettingsAttachments.DataTableSettingsScope, Name);

    OnSwapAttachmentScope(q, w);

	FinalizeAttachmentChange();
}

void AWeaponBase::FinalizeAttachmentChange()
{
	OnSpawnAttachmentComponents();
	EquipSkinRandomPreset();
	TLineScaleAttachmentsUp->PlayFromStart();

	MaterialsDefaultMagazine = SMeshMagazine->GetMaterials();

	OnAimingStop();
}

void AWeaponBase::EquipSkinRandomPreset()
{
	TArray<FName> presetNames;
	presetNames = WeaponPresetRowHandle.DataTable->GetRowNames();
	

	WeaponPresetRowHandle.RowName = presetNames[FMath::RandRange(0, presetNames.Num()-1)];

	FSPreset preset;

	preset = *(WeaponPresetRowHandle.GetRow<FSPreset>(""));

	if (preset.RowHandleSkin.DataTable)
		SetSkinRowHandle(preset.RowHandleSkin);
}

void AWeaponBase::TimelineSetting()
{
    UCurveFloat* attachmentDownScale;
    Helpers::GetAssetDynamic(&attachmentDownScale, TEXT("CurveFloat'/Game/Projz/Curve/AttachmentDown.AttachmentDown'"));
	TLineScaleAttachmentsDown->AddInterpFloat(attachmentDownScale, AttachmentsDownFunction);
	TLineScaleAttachmentsDown->SetLooping(false);

    UCurveFloat* attachmentUpScale;
    Helpers::GetAsset(&attachmentUpScale, TEXT("CurveFloat'/Game/Projz/Curve/AttachmentUp.AttachmentUp'"));
    TLineScaleAttachmentsUp->AddInterpFloat(attachmentUpScale, AttachmentsUpFunction);
	TLineScaleAttachmentsUp->SetLooping(false);
}

void AWeaponBase::SetAttachmentsScale(float Scale)
{
	FVector ScaleVector;
	ScaleVector = FVector(Scale);

	SMeshScope->SetRelativeScale3D(ScaleVector);
	SMeshLaser->SetRelativeScale3D(ScaleVector);
	SMeshGrip->SetRelativeScale3D(ScaleVector);
	SMeshMuzzle->SetRelativeScale3D(ScaleVector);
}

void AWeaponBase::OnInteracted(IICharacter* InteractionOwner)
{
	InteractionOwner->OnPickUp();
}

void AWeaponBase::OnRandomizePreset()
{
	OnRandomizePresetCore();
}

void AWeaponBase::OnRandomizePresetCore()
{
	TLineScaleAttachmentsDown->PlayFromStart();
	UKismetSystemLibrary::RetriggerableDelay(GetWorld(), TLineScaleAttachmentsDown->GetTimelineLength(), FLatentActionInfo());
	EquipRandomScope();
	EquipRandomMuzzle();
	EquipRandomGrip();
	EquipRandomLaser();

	OnRandomizeAttachments();

	FinalizeAttachmentChange();
}

void AWeaponBase::EquipRandomScope()
{
	TArray<FName> rowNames = WeaponPresetOverride.Attachments.RowHandleMeshScope.DataTable->GetRowNames();
	UpdateScopefromName(rowNames[FMath::RandRange(0, rowNames.Num()-1)]);
}

void AWeaponBase::EquipRandomMuzzle()
{
    TArray<FName> rowNames = WeaponPresetOverride.Attachments.RowHandleMeshMuzzle.DataTable->GetRowNames();
	int32 randNum = FMath::RandRange(0, rowNames.Num()-1);
	FDataTableRowHandle q;
	MAKEDATATABLEROWHANDLE(q, WeaponPresetOverride.Attachments.RowHandleMeshMuzzle.DataTable, rowNames[randNum]);
    FDataTableRowHandle w;
	MAKEDATATABLEROWHANDLE(w, WeaponInformation.SettingsAttachments.DataTableSettingsMuzzle, rowNames[randNum]);

	OnSwapAttachmentMuzzle(q, w);
}

void AWeaponBase::EquipRandomGrip()
{
    TArray<FName> rowNames = WeaponPresetOverride.Attachments.RowHandleMeshMuzzle.DataTable->GetRowNames();
	int32 randNum = FMath::RandRange(0, rowNames.Num()-1);

	FDataTableRowHandle q;
	MAKEDATATABLEROWHANDLE(q, WeaponPresetOverride.Attachments.RowHandleMeshGrip.DataTable, rowNames[randNum]);
	FDataTableRowHandle w;
	MAKEDATATABLEROWHANDLE(w, WeaponInformation.SettingsAttachments.DataTableSettingsGrip, rowNames[randNum]);

	OnSwapattachmentGrip(q, w);
}

void AWeaponBase::EquipRandomLaser()
{
    TArray<FName> rowNames = WeaponPresetOverride.Attachments.RowHandleMeshLaser.DataTable->GetRowNames();
    int32 randNum = FMath::RandRange(0, rowNames.Num()-1);

	FDataTableRowHandle q;
	MAKEDATATABLEROWHANDLE(q, WeaponPresetOverride.Attachments.RowHandleMeshLaser.DataTable, rowNames[randNum]);
	FDataTableRowHandle w;
	MAKEDATATABLEROWHANDLE(w, WeaponInformation.SettingsAttachments.DataTableSettingsLaser, rowNames[randNum]);

	OnSwapAttachmentLaser(q, w);
}

void AWeaponBase::OnRandomizeAttachments()
{

}

void AWeaponBase::OnMontagePlay(FName Name, bool FirstPerson)
{
	FSAnimation* findAnim = WeaponInformation.SettingsAnimationBlueprint.DataTableMontagesWeapon->FindRow<FSAnimation>(Name, "");
	if (findAnim)
	{
		UAnimMontage* montage = (FirstPerson ? findAnim->SequenceBaseFirstPerson : findAnim->SequenceBaseThirdPerson);

		Weapon->GetAnimInstance()->Montage_Play(montage);
	}


	FSSound* findSound = WeaponInformation.DataTableSoundCues->FindRow<FSSound>(Name, "");
	if (findSound)
	{
		UKismetSystemLibrary::Delay(GetWorld(), findSound->Delay, FLatentActionInfo());
		AudioComponentPlaying = UGameplayStatics::SpawnSound2D(GetWorld(), findSound->SoundCue);
	}
}

