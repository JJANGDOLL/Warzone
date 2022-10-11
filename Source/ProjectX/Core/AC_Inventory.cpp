// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/AC_Inventory.h"
#include "WeaponBase.h"
#include "Weapons/Assault_Rifle_01.h"
#include "Weapons/Handgun_01.h"
#include "Weapons/Assault_Rifle_02.h"
#include "Weapons/Sniper_02.h"
#include "Utilities/Global.h"
#include "CharacterBase.h"
#include "Interfaces/ISubWeapon.h"
#include "Weapons/Sniper_01.h"
#include "Weapons/Shotgun_01.h"

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

	Inventory.Init(nullptr, 3);

// 	AddWeapon(AShotgun_01::StaticClass(), 0);
//     AddWeapon(AAssault_Rifle_02::StaticClass(), 1);
//     AddWeapon(AHandgun_01::StaticClass(), 2);
// 	CurrentItem = &(Inventory[0]);

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

void UAC_Inventory::AddWeapon(TSubclassOf<AWeaponBase> WeaponClass, uint8 Idx)
{
    AWeaponBase* weapon;

    weapon = GetWorld()->SpawnActor<AWeaponBase>(WeaponClass, GetOwner()->GetActorTransform());
    weapon->SetOwner(GetOwner());
	Inventory[Idx] = weapon;
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
// 	CurrentItem = &Inventory[Idx];
	return Inventory[Idx];
}

void UAC_Inventory::SetSelectedItem(uint8 Idx)
{
	CurrentItem = &Inventory[Idx];

	OnWidgetUpdate.ExecuteIfBound();
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

    OnWidgetUpdate.ExecuteIfBound();
}

void UAC_Inventory::DropItem(bool bNextWeapon)
{
	if (!CurrentItem)
		return;

	if (!*CurrentItem)
		return;

	AWeaponBase* weapon = Cast<AWeaponBase>(*CurrentItem);
	weapon->SetOwner(nullptr);
	weapon->SetActorHiddenInGame(false);
    weapon->GetWeaponBodyMesh()->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	weapon->DetachFromActor(FDetachmentTransformRules::KeepRelativeTransform);
	weapon->GetWeaponBodyMesh()->SetSimulatePhysics(true);
	weapon->GetWeaponBodyMesh()->AddImpulse(FVector(GetOwner()->GetActorForwardVector()) * 25000.f + FVector(GetOwner()->GetActorUpVector()) * 15000.f + FVector(GetOwner()->GetActorRightVector()) * 1.f);

	*CurrentItem = nullptr;
	if (bNextWeapon)
	{
        if (Inventory[0] != nullptr)
            CurrentItem = &Inventory[0];
        else if (Inventory[1] != nullptr)
            CurrentItem = &Inventory[1];
        else if (Inventory[2] != nullptr)
            CurrentItem = &Inventory[2];
	}


    OnWeaponChanged.ExecuteIfBound();
}

void UAC_Inventory::PickupItem(IIItem* PickupItem)
{
	Logger::Log(Cast<AWeaponBase>(PickupItem));

	Cast<AWeaponBase>(PickupItem)->GetWeaponBodyMesh()->SetSimulatePhysics(false);
	Cast<AWeaponBase>(PickupItem)->GetWeaponBodyMesh()->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	if (Cast<IIMainWeapon>(PickupItem))
	{
        if (!Inventory[0])
        {
            if (CurrentItem && *CurrentItem)
            {
                Cast<AWeaponBase>(*CurrentItem)->SetActorHiddenInGame(true);
            }
            Inventory[0] = PickupItem;
            CurrentItem = &Inventory[0];
        }

        else if (!Inventory[1])
        {
            if (CurrentItem && *CurrentItem)
                Cast<AWeaponBase>(*CurrentItem)->SetActorHiddenInGame(true);
            Inventory[1] = PickupItem;
            CurrentItem = &Inventory[1];
        }

        else if (CurrentItem && *CurrentItem)
        {

            DropItem(false);
            *CurrentItem = PickupItem;
        }
	}
	else if (Cast<IISubWeapon>(PickupItem))
	{
        if (CurrentItem && *CurrentItem)
            Cast<AWeaponBase>(*CurrentItem)->SetActorHiddenInGame(true);

		CurrentItem = &Inventory[2];
		if (CurrentItem && *CurrentItem)
		{
			DropItem(false);
		}
		*CurrentItem = PickupItem;
	}




	OnWeaponChanged.ExecuteIfBound();
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

