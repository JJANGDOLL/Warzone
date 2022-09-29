// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapons/Assault_Rifle_03.h"
#include "Datas/Weapons/WeaponsEnum.h"

AAssault_Rifle_03::AAssault_Rifle_03()
{
    WeaponType = EWeaponTypes::ASSAULT_RIFLE_03;

    MakeWeapon();
}

EAmmoType AAssault_Rifle_03::GetWeaponAmmoType()
{
    return EAmmoType::Big;
}

void AAssault_Rifle_03::SetWeaponName()
{
    WeaponName = TEXT("Assault-Rifle-03");
}
