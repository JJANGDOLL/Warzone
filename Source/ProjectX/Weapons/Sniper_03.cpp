// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapons/Sniper_03.h"

ASniper_03::ASniper_03()
{
    WeaponType = EWeaponTypes::SNIPER_03;

    MakeWeapon();
}

EAmmoType ASniper_03::GetWeaponAmmoType()
{
    return EAmmoType::Big;
}

void ASniper_03::SetWeaponName()
{
    WeaponName = TEXT("Sniper-03");
}
