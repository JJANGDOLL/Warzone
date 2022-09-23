// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapons/Assault_Rifle_01.h"

#include "Utilities/Global.h"

// Sets default values
AAssault_Rifle_01::AAssault_Rifle_01()
{
    WeaponType = EWeaponTypes::ASSAULT_RIFLE_01;

    MakeWeapon();
}

void AAssault_Rifle_01::SetWeaponName()
{
    WeaponName = TEXT("Assault-Rifle-01");
}
