// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/WeaponBase.h"
#include "Utilities/Global.h"
#include "Engine/DataTable.h"
#include "Misc/EnumRange.h"
#include "Datas/Weapons/WeaponDA.h"
#include "Datas/Weapons/WeaponsStructs.h"
#include "WeaponBody.h"
#include "WeaponMagazine.h"
#include "WeaponAttachment.h"
#include "CasingBase.h"
#include "Math/UnrealMathUtility.h"
#include "BulletBase.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AWeaponBase::AWeaponBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Helpers::CreateComponent(this, &Weapon, TEXT("Weapon"));
	Helpers::CreateComponent(this, &SocketMagazine, TEXT("Socket_Magazine"), Weapon, TEXT("SOCKET_Magazine"));
	Helpers::CreateComponent(this, &Magazine, TEXT("Magazine"), SocketMagazine);
    Helpers::CreateComponent(this, &SocketIronSight, TEXT("Socket_IronSight"), Weapon, TEXT("SOCKET_Default"));
    Helpers::CreateComponent(this, &IronSight, TEXT("Ironsight"), SocketIronSight);

	TestMethods.Add(EWeaponFeature::None, &AWeaponBase::DoNothing);
	TestMethods.Add(EWeaponFeature::Reload, &AWeaponBase::Reload);
	TestMethods.Add(EWeaponFeature::Fire, &AWeaponBase::Fire);
    TestMethods.Add(EWeaponFeature::EjectingCasing, &AWeaponBase::EjectCasing);
    TestMethods.Add(EWeaponFeature::SpawnBullet, &AWeaponBase::SpawnBullet);
    TestMethods.Add(EWeaponFeature::SpawnFlame, &AWeaponBase::SpawnFlame);

	TestFeature = EWeaponFeature::None;
}

// Called when the game starts or when spawned
void AWeaponBase::BeginPlay()
{
	Super::BeginPlay();

	Logger::Log(static_cast<int32>(TestFeature));
	
    OnTestFeature = TestMethods[TestFeature];

	GetWorldTimerManager().SetTimer(TestTimerHandle, this, OnTestFeature, TestTerm, true, 2.0f);
}

// Called every frame
void AWeaponBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

    OnTestFeature = TestMethods[TestFeature];
}

void AWeaponBase::MakeWeapon()
{
    GetWeaponNameByWeaponType();
	if (!FindWeaponDataInDataTable())
	{
		return;
	}

	if (!WeaponDA)
		return;

    GetWeaponBody();
    GetWeaponMagazine();
	GetWeaponIronsight();
	GetCasingInfo();
	GetBulletInfo();
	GetFlame();
	GetPoses();
}

void AWeaponBase::GetWeaponNameByWeaponType()
{
	WeaponName = TEXT("Invalid Weapon Type");

	switch (WeaponType)
	{
		case EWeaponTypes::None:
			break;
		case EWeaponTypes::ASSAULT_RIFLE_01:
			WeaponName = TEXT("Assault-Rifle-01");
			break;
		case EWeaponTypes::ASSAULT_RIFLE_02:
			WeaponName = TEXT("Assault-Rifle-02");
			break;
		case EWeaponTypes::Count:
			break;
		case EWeaponTypes::HANDGUN_01:
			WeaponName = TEXT("Handgun-01");
			break;
        case EWeaponTypes::HANDGUN_02:
            WeaponName = TEXT("Handgun-02");
            break;
		default:
			break;
	}
}

bool AWeaponBase::FindWeaponDataInDataTable()
{
	static UDataTable* weaponRefDT;
	if(!weaponRefDT)
		Helpers::GetAsset(&weaponRefDT, TEXT("DataTable'/Game/Datas/Weapon/WeaponRefDT.WeaponRefDT'"));

	FWeaponDARef* findDA = weaponRefDT->FindRow<FWeaponDARef>(WeaponName, "");
	if (!findDA)
		return false;

	WeaponDA = Cast<UWeaponDA>(findDA->DataRef);
	return true;
}

void AWeaponBase::GetWeaponBody()
{
	Weapon->SetSkeletalMesh(WeaponDA->WeaponBody);
	Weapon->SetAnimInstanceClass(WeaponDA->WeaponABP);
}

void AWeaponBase::GetWeaponMagazine()
{
	Magazine->SetStaticMesh(WeaponDA->WeaponMagazine);
}

void AWeaponBase::GetWeaponIronsight()
{
	IronSight->SetStaticMesh(WeaponDA->WeaponIronSight);
}

void AWeaponBase::GetCasingInfo()
{
	CasingClass = WeaponDA->CaseClass;
	EjectImpulse = WeaponDA->CasingImpulseStrength;
}

void AWeaponBase::GetBulletInfo()
{
	BulletClass = WeaponDA->BulletClass;
}

void AWeaponBase::GetFlame()
{
	Flame = WeaponDA->Flame;
}

void AWeaponBase::GetPoses()
{
	PosesDA = WeaponDA->PosesDA;
}

void AWeaponBase::EjectCasing()
{
	FTransform casingEjectTransform = Weapon->GetSocketTransform(TEXT("SOCKET_Eject"), RTS_World);

	casingEjectTransform.SetScale3D(GetActorScale());
	ACasingBase* casing = GetWorld()->SpawnActor<ACasingBase>(CasingClass, casingEjectTransform);
	float impulseStrength = 1.f;
	casing->ApplyImpulse(casingEjectTransform.GetRotation().GetForwardVector(), FVector(FMath::FRandRange(EjectImpulse * 0.9f, EjectImpulse * 1.1f)));
}

void AWeaponBase::SpawnBullet()
{
    FTransform muzzleTransform = Weapon->GetSocketTransform(TEXT("SOCKET_Bullet"), RTS_World);

	muzzleTransform.SetScale3D(GetActorScale());
	ABulletBase* bullet = GetWorld()->SpawnActor<ABulletBase>(BulletClass, muzzleTransform);
	bullet->OnLaunch(false, bullet->GetActorRightVector() * 33000.f * -1.f);
}

void AWeaponBase::SpawnFlame()
{
	UGameplayStatics::SpawnEmitterAttached(Flame, Weapon, TEXT("SOCKET_Flame"));
}

FVector AWeaponBase::GetWeaponForward()
{
	return GetActorRightVector();
}

UWeaponPoseDA* AWeaponBase::GetPosesDA()
{
	return PosesDA;
}

void AWeaponBase::DoNothing()
{
	Helpers::DrawGizmo(Weapon);
	Helpers::DrawGizmo(GetWorld(), Weapon->GetSocketTransform(TEXT("SOCKET_Muzzle"), RTS_World));
    Helpers::DrawGizmo(GetWorld(), Weapon->GetSocketTransform(TEXT("SOCKET_Eject"), RTS_World));
    Helpers::DrawGizmo(GetWorld(), Weapon->GetSocketTransform(TEXT("SOCKET_Bullet"), RTS_World));
}

void AWeaponBase::Reload()
{
	Weapon->GetAnimInstance()->Montage_Play(WeaponDA->MontageReload);
}

void AWeaponBase::Fire()
{
	Weapon->GetAnimInstance()->Montage_Play(WeaponDA->MontageFire);
}

USkeletalMeshComponent* AWeaponBase::GetWeaponBodyMesh()
{
	return Weapon;
}

UStaticMeshComponent* AWeaponBase::GetWeaponMagazineMesh()
{
	return Magazine;
}

UStaticMeshComponent* AWeaponBase::GetWeaponIronSightMesh()
{
	return IronSight;
}

