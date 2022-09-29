// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/AC_Inventory.h"
#include "WeaponBase.h"
#include "Weapons/Assault_Rifle_01.h"
#include "Weapons/Handgun_01.h"
#include "Weapons/Assault_Rifle_02.h"
#include "Weapons/Sniper_02.h"
#include "Utilities/Global.h"
#include "CharacterBase.h"

// Sets default values for this component's properties
UAC_Inventory::UAC_Inventory()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UAC_Inventory::BeginPlay()
{
	Super::BeginPlay();

	Inventory.Init(nullptr, 2);

// 	AWeaponBase* weapon;
// 	if (!Inventory[0])
// 	{
// 		weapon = GetWorld()->SpawnActor<AWeaponBase>(AAssault_Rifle_01::StaticClass(), GetOwner()->GetActorTransform());
// 		weapon->SetOwner(GetOwner());
// 		Inventory[0] = Cast<IIItem>(weapon);
// 		CurrentItem = &(Inventory[0]);
// 	}
// 
//     if (!Inventory[1])
//     {
// 		weapon = GetWorld()->SpawnActor<AWeaponBase>(ASniper_02::StaticClass(), GetOwner()->GetActorTransform());
//         weapon->SetOwner(GetOwner());
//         weapon->SetActorHiddenInGame(true);
//         Inventory[1] = Cast<IIItem>(weapon);
//     }

//     if (!Inventory[2])
//     {
// 		weapon = GetWorld()->SpawnActor<AWeaponBase>(AAssault_Rifle_01::StaticClass(), GetOwner()->GetActorTransform());
// 		weapon->SetOwner(GetOwner());
// 		weapon->SetActorHiddenInGame(true);
//         Inventory[2] = Cast<IIItem>(weapon);
//     }

//     if (!Inventory[3])
//     {
//         AWeaponBase* weapon = GetWorld()->SpawnActor<AWeaponBase>(AAssault_Rifle_02::StaticClass(), GetOwner()->GetActorTransform());
//         weapon->SetOwner(GetOwner());
//         weapon->SetActorHiddenInGame(true);
//         Inventory[3] = Cast<IIItem>(weapon);
//     }
// 	PrintLine();
// 	PrintLine();
}



IIItem* UAC_Inventory::GetLastItem()
{
	if (!LastItem)
		LastItem = Inventory[0];
	return LastItem;
}

IIItem* UAC_Inventory::GetSelectedItem(uint8 Idx)
{
	if (!Inventory[Idx])
		return nullptr;
	CurrentItem = &Inventory[Idx];
	return Inventory[Idx];
}

void UAC_Inventory::PutItem(IIItem* InItem)
{
	LastItem = Cast<IIItem>(InItem);
}

uint32 UAC_Inventory::GetRemainAmmo(EAmmoType AmmoType)
{
	uint32 remain = 0;
	switch (AmmoType)
	{
		case EAmmoType::None:
			break;
		case EAmmoType::Big:
			remain = BigBullet;
			break;
		case EAmmoType::Small:
			remain = SmallBullet;
			break;
		case EAmmoType::Count:
			break;
		default:
			break;
	}
	return remain;
}

void UAC_Inventory::SetRemainAmmo(EAmmoType AmmoType, uint32 UseAmmo)
{
    switch (AmmoType)
    {
        case EAmmoType::None:
            break;
        case EAmmoType::Big:
			BigBullet -= UseAmmo;
            break;
        case EAmmoType::Small:
			SmallBullet -= UseAmmo;
            break;
        case EAmmoType::Count:
            break;
        default:
            break;
    }
}

void UAC_Inventory::SetMaxAmmo(EAmmoType AmmoType)
{
	switch (AmmoType)
	{
		case EAmmoType::None:
			break;
		case EAmmoType::Big:
			BigBullet = 200;
			break;
		case EAmmoType::Small:
			SmallBullet = 100;
			break;
		case EAmmoType::Count:
			break;
		default:
			break;

	}
}

void UAC_Inventory::DropItem()
{
	Logger::Log(Cast<AActor>(*CurrentItem));

	if (!*CurrentItem)
		return;

	AWeaponBase* weapon = Cast<AWeaponBase>(*CurrentItem);
	weapon->SetOwner(nullptr);
	weapon->DetachFromActor(FDetachmentTransformRules::KeepRelativeTransform);
	weapon->GetWeaponBodyMesh()->SetSimulatePhysics(true);
	weapon->GetWeaponBodyMesh()->AddImpulse(FVector(GetOwner()->GetActorForwardVector())* 40000.f);
	*CurrentItem = nullptr;
}

void UAC_Inventory::PickupItem(IIItem* PickupItem)
{
	IIItem** prevItem = CurrentItem;

    if (!Inventory[0])
    {
        Inventory[0] = PickupItem;
        CurrentItem = &Inventory[0];
    }

    else if (!Inventory[1])
    {
        Inventory[1] = PickupItem;
        CurrentItem = &Inventory[1];
    }

	else if (*CurrentItem)
	{
		DropItem();
		*CurrentItem = PickupItem;
	}

	OnWeaponChanged.Broadcast();
	PrintLine();
}

void UAC_Inventory::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
// 	Logger::Log(Cast<AActor>(*CurrentItem));
}

IIItem* UAC_Inventory::GetCurrentItem()
{
	if (!CurrentItem)
		return nullptr;

// 	Logger::Log(Cast<AActor>(CurrentItem));
//     Logger::Log(Cast<AActor>(*CurrentItem));

	return *CurrentItem;
}

bool UAC_Inventory::IsWeaponChanged()
{
	return false;
}

