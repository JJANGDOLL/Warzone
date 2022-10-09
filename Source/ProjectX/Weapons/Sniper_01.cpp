// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapons/Sniper_01.h"

ASniper_01::ASniper_01()
{
    WeaponType = EWeaponTypes::SNIPER_01;

    MakeWeapon();
}

void ASniper_01::SetWeaponName()
{
    WeaponName = TEXT("Sniper-01");
}

EAmmoType ASniper_01::GetWeaponAmmoType()
{
    return EAmmoType::Big;
}
