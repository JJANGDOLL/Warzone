// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapons/Sniper_02.h"

ASniper_02::ASniper_02()
{
    WeaponType = EWeaponTypes::SNIPER_02;

    MakeWeapon();
}

EAmmoType ASniper_02::GetWeaponAmmoType()
{
    return EAmmoType::Big;
}

void ASniper_02::SetWeaponName()
{
    WeaponName = TEXT("Sniper-02");
}
