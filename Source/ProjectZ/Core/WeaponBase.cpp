// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/WeaponBase.h"
#include "Utilities/Global.h"

#include "Core/WeaponAttachmentBase.h"
#include "Core/WeaponBodyBase.h"
#include "Engine/SkeletalMesh.h"
#include "Components/MeshComponent.h"
#include "Kismet/DataTableFunctionLibrary.h"

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
	FSMagazine* findMag = WeaponMagazineRowHandle.GetRow<FSMagazine>("");
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
	WeaponMagazineRowHandle.DataTable = weaponMagazineDT;
	WeaponMagazineRowHandle.RowName = weaponMagazineDT->GetRowNames()[0];

	TryUpdateAttachmentMagazine();
}

void AWeaponBase::TryUpdateAttachmentIronsights()
{
	ShowAttachmentIronsights = (WeaponIronsightRowHandle.RowName != TEXT("Hidden"));

	FSIronsights* findIron = WeaponIronsightRowHandle.GetRow<FSIronsights>("");
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
	WeaponIronsightRowHandle.DataTable = weaponIronsightDT;
	WeaponIronsightRowHandle.RowName = weaponIronsightDT->GetRowNames()[0];

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
// 	if (TryUpdateAttachmentScope(WeaponPresetOverride))
// 		return;

	if (TryUpdateAttachmentScope(WeaponPreset))
		return;

	GetIronsightsScopeSettings();
}

void AWeaponBase::UpdateAttachmentScopeLoadAssetConstruct()
{
	ScopeSettingsRowHandle.DataTable = WeaponInformation.SettingsAttachments.DataTableSettingsScope;
	ScopeSettingsRowHandle.RowName = WeaponPreset.Attachments.RowHandleMeshScope.RowName;

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
		Logger::Log(Preset.Attachments.RowHandleMeshScope.RowName.ToString());
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

