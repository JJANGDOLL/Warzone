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
#include "Sound/SoundCue.h"
#include "CharacterBase.h"
#include "AC_Inventory.h"
#include "Weapons/Attachments/ScopeTemp.h"
#include "Components/SceneCaptureComponent2D.h"
#include "Engine/TextureRenderTarget2D.h"

#define LOCTEXT_NAMESPACE "MyNamespace"

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
	Helpers::CreateComponent(this, &SocketScope, TEXT("Socket_Scope"), Weapon, TEXT("SOCKET_Scope"));
	Helpers::CreateComponent(this, &Scope, TEXT("Scope"), SocketScope);
	Helpers::CreateComponent(this, &SceneCaptureScope, TEXT("SceneCapture"), Scope, TEXT("SOCKET_Render"));

	TestMethods.Add(EWeaponFeature::None, &AWeaponBase::DoNothing);
	TestMethods.Add(EWeaponFeature::Reload, &AWeaponBase::Reload);
	TestMethods.Add(EWeaponFeature::Fire, &AWeaponBase::Fire);
    TestMethods.Add(EWeaponFeature::EjectingCasing, &AWeaponBase::EjectCasing);
    TestMethods.Add(EWeaponFeature::SpawnBullet, &AWeaponBase::SpawnBullet);
    TestMethods.Add(EWeaponFeature::SpawnFlame, &AWeaponBase::SpawnFlame);

	TestFeature = EWeaponFeature::None;

	Weapon->SetGenerateOverlapEvents(true);
	Weapon->SetCollisionProfileName(TEXT("InteractObject"));

    Helpers::GetAsset(&TextureRender, TEXT("TextureRenderTarget2D'/Game/InfimaGames/AnimatedLowPolyWeapons/Art/Weapons/_Common/Attachments/Textures/RT_ATT_Scope_01.RT_ATT_Scope_01'"));
}

// Called when the game starts or when spawned
void AWeaponBase::BeginPlay()
{
	Super::BeginPlay();

	Logger::Log(static_cast<int32>(TestFeature));
	
    OnTestFeature = TestMethods[TestFeature];

	Logger::Log(Scope);

	GetWorldTimerManager().SetTimer(TestTimerHandle, this, OnTestFeature, TestTerm, true, 2.0f);

	if (TestScope)
	{
//         SceneCaptureScope = NewObject<USceneCaptureComponent2D>();
        SceneCaptureScope->AddRelativeRotation(FRotator(0.f, 90.f, 0.f));
        SceneCaptureScope->AttachToComponent(Scope, FAttachmentTransformRules(EAttachmentRule::SnapToTarget, EAttachmentRule::KeepRelative, EAttachmentRule::SnapToTarget, false), TEXT("SOCKET_Render"));
        SceneCaptureScope->TextureTarget = TextureRender;
        SceneCaptureScope->bCaptureOnMovement = true;
        SceneCaptureScope->SetVisibility(true);
        SceneCaptureScope->SetComponentTickEnabled(true);
		SceneCaptureScope->FOVAngle = 6.5f;
		SceneCaptureScope->HiddenActors.AddUnique(this);
		SceneCaptureScope->HiddenActors.AddUnique(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	}
	else
	{
		Scope->DestroyComponent();

	}
}

// Called every frame
void AWeaponBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

    OnTestFeature = TestMethods[TestFeature];

// 	Helpers::DrawGizmo(GetWorld(), Weapon->GetSocketTransform(TEXT("SOCKET_Bullet")));
}

void AWeaponBase::MakeWeapon()
{
    SetWeaponName();
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
	GetEmptyPose();
	GetWeaponInfo();
	GetSounds();
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
		case EWeaponTypes::SHOTGUN_01:
			WeaponName = TEXT("Shotgun-01");
			break;
		default:
			break;
	}
}

bool AWeaponBase::FindWeaponDataInDataTable()
{
	static UDataTable* weaponRefDT = nullptr;
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

void AWeaponBase::GetWeaponInfo()
{
	MaxAmmo = WeaponDA->MaxAmmo;
}

void AWeaponBase::GetSounds()
{
	FireSound = WeaponDA->FireSound;
	ReloadSound = WeaponDA->ReloadSound;
	ReloadEmptySound = WeaponDA->ReloadEmptySound;
}

void AWeaponBase::SetWeaponName()
{

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
    FTransform bulletTransform = Weapon->GetSocketTransform(TEXT("SOCKET_Bullet"), RTS_World);

	ACharacterBase* ownerChar = Cast<ACharacterBase>(GetOwner());
	if (!ownerChar)
		return;
	
	FVector location;
	FVector direction;

	if (ownerChar->IsAiming() && ownerChar->GetController()->IsPlayerController())
	{
		PrintLine();

		int32 sizeX;
		int32 sizeY;
		UGameplayStatics::GetPlayerController(GetWorld(), 0)->GetViewportSize(sizeX, sizeY);
		UGameplayStatics::DeprojectScreenToWorld(UGameplayStatics::GetPlayerController(GetWorld(), 0), FVector2D(sizeX / 2, sizeY / 2), location, direction);

		bulletTransform.SetLocation(location);
		bulletTransform.SetRotation(FQuat(direction.Rotation()));

// 		DrawDebugDirectionalArrow(GetWorld(), location, location + direction * 100.f, 10, FColor::Red, false, 20.f, 0.f, 1.f);
	}

	bulletTransform.SetScale3D(GetActorScale());
	ABulletBase* bullet = GetWorld()->SpawnActor<ABulletBase>(BulletClass, bulletTransform);
	if (bullet)
	{
		bullet->SetPower(WeaponDA->BulletPower);
		bullet->OnLaunch(false, bulletTransform.GetRotation().GetForwardVector() * WeaponDA->FireIntensity);
	}
}

void AWeaponBase::SpawnFlame()
{
	UGameplayStatics::SpawnEmitterAttached(Flame, Weapon, TEXT("SOCKET_Flame"), FVector::ZeroVector, FRotator::ZeroRotator, FVector(0.25f,  0.25f, 0.25f));
}

UAnimSequenceBase* AWeaponBase::GetEmptyPose()
{
	return WeaponDA->EmptyAmmoPose;
}

bool AWeaponBase::IsEmpty()
{
	return CurrentAmmo == 0;
}

FVector AWeaponBase::GetWeaponForward()
{
	return GetActorRightVector();
}

UWeaponPoseDA* AWeaponBase::GetPosesDA()
{
	return PosesDA;
}

FTransform AWeaponBase::GetAimOffset()
{
	FTransform offset = WeaponDA->AimOffset;
	if (Scope && WeaponDA->ScopeDA && TestScope)
	{
		offset += Scope->GetScopeOffset(WeaponDA->ScopeDA);
	}

	return offset;
}

int8 AWeaponBase::GetMaxAmmo()
{
	return MaxAmmo;
}

int8 AWeaponBase::GetCurAmmo()
{
    return CurrentAmmo;
}

EFireType AWeaponBase::GetFireType()
{
	return WeaponDA->SupportFireType[FireTypeIdx];
}

float AWeaponBase::GetFireInterval()
{
	return WeaponDA->FireInterval;
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
	bReloading = true;
	if (CurrentAmmo > 0)
	{
		Weapon->GetAnimInstance()->Montage_Play(WeaponDA->MontageReload);
        FOnMontageEnded BlendOutDele;
        BlendOutDele.BindUObject(this, &AWeaponBase::OnReloadBlendOut);
        Weapon->GetAnimInstance()->Montage_SetBlendingOutDelegate(BlendOutDele, WeaponDA->MontageReload);
		if (ReloadSound)
			UGameplayStatics::PlaySoundAtLocation(GetWorld(), ReloadSound, GetActorLocation(), 2.f);
	}
	else
	{
        Weapon->GetAnimInstance()->Montage_Play(WeaponDA->MontageReloadEmpty);
		FOnMontageEnded BlendOutDele;
		BlendOutDele.BindUObject(this, &AWeaponBase::OnReloadBlendOut);
		Weapon->GetAnimInstance()->Montage_SetBlendingOutDelegate(BlendOutDele, WeaponDA->MontageReloadEmpty);
        if (ReloadEmptySound)
            UGameplayStatics::PlaySoundAtLocation(GetWorld(), ReloadEmptySound, GetActorLocation());
	}

}

void AWeaponBase::Fire()
{
	Weapon->GetAnimInstance()->Montage_Play(WeaponDA->MontageFire);
	if(FireSound)
		UGameplayStatics::PlaySoundAtLocation(GetWorld(), FireSound, GetActorLocation());
	CurrentAmmo--;

	OnWeaponFire.ExecuteIfBound();
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

void AWeaponBase::SetAmmo(int8 InAmmo)
{
	CurrentAmmo = InAmmo;
}

void AWeaponBase::ChangeFireType()
{
	FireTypeIdx++;
	if (FireTypeIdx == WeaponDA->SupportFireType.Num())
	{
		FireTypeIdx = 0;
	}

	OnWeaponFiretypeChanged.ExecuteIfBound();
}

void AWeaponBase::OnReloadBlendOut(UAnimMontage* AnimMontage, bool bInterrupted)
{
	bReloading = false;
    OnWeaponReload.ExecuteIfBound();
}

void AWeaponBase::Action()
{
	ACharacterBase* playerChar = Cast<ACharacterBase>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	SetOwner(playerChar );
	UAC_Inventory* inventory = Helpers::GetComponent<UAC_Inventory>(playerChar);
	inventory->PickupItem(GetItem());

// 	AttachToComponent(playerChar->GetMeshArms(), FAttachmentTransformRules::SnapToTargetIncludingScale, TEXT("SOCKET_Weapon"));
}

FText AWeaponBase::Description()
{
	return FText::Format(LOCTEXT("WeaponDetail", "Equip {0}"), FText::FromName(WeaponName));
}

IIItem* AWeaponBase::GetItem()
{
	return this;
}

class UTexture2D* AWeaponBase::GetWeaponScopeImage()
{
	return WeaponDA->WeaponIronsightImage;
}

bool AWeaponBase::IsReloading()
{
	return bReloading;
}

UTexture2D* AWeaponBase::GetWeaponBodyImage()
{
	return WeaponDA->WeaponBodyImage;
}

UTexture2D* AWeaponBase::GetWeaponMagazineImage()
{
    return WeaponDA->WeaponMagazineImage;
}

FVector2D AWeaponBase::GetRecoilIntensity()
{
	return WeaponDA->RecoilIntensity;
}

EAmmoType AWeaponBase::GetWeaponAmmoType()
{
	return EAmmoType::Big;
}

#undef LOCTEXT_NAMESPACE