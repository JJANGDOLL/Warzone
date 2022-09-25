// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/AC_Inventory.h"
#include "WeaponBase.h"
#include "Weapons/Assault_Rifle_01.h"
#include "Weapons/Handgun_01.h"
#include "Weapons/Assault_Rifle_02.h"
#include "Weapons/Sniper_02.h"

// Sets default values for this component's properties
UAC_Inventory::UAC_Inventory()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}


// Called when the game starts
void UAC_Inventory::BeginPlay()
{
	Super::BeginPlay();

	Inventory.Init(nullptr, 5);

	if (!Inventory[0])
	{
		AWeaponBase* weapon = GetWorld()->SpawnActor<AWeaponBase>(AAssault_Rifle_01::StaticClass(), GetOwner()->GetActorTransform());
		weapon->SetOwner(GetOwner());
		Inventory[0] = Cast<IIItem>(weapon);
	}

    if (!Inventory[1])
    {
        AWeaponBase* weapon = GetWorld()->SpawnActor<AWeaponBase>(ASniper_02::StaticClass(), GetOwner()->GetActorTransform());
        weapon->SetOwner(GetOwner());
        weapon->SetActorHiddenInGame(true);
        Inventory[1] = Cast<IIItem>(weapon);
    }

    if (!Inventory[2])
    {
        AWeaponBase* weapon = GetWorld()->SpawnActor<AWeaponBase>(AHandgun_01::StaticClass(), GetOwner()->GetActorTransform());
        weapon->SetOwner(GetOwner());
		weapon->SetActorHiddenInGame(true);
        Inventory[2] = Cast<IIItem>(weapon);
    }
}

IIItem* UAC_Inventory::GetLastItem()
{
	if (!LastItem)
		LastItem = Inventory[0];
	return LastItem;
}

IIItem* UAC_Inventory::GetSelectedItem(uint8 Idx)
{
	return Inventory[Idx];
}

void UAC_Inventory::PutItem(IIItem* InItem)
{
	LastItem = Cast<IIItem>(InItem);
}

