// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapons/Handgun_04.h"

AHandgun_04::AHandgun_04()
{
    WeaponType = EWeaponTypes::HANDGUN_04;

    MakeWeapon();
}

void AHandgun_04::SetWeaponName()
{
    WeaponName = TEXT("Handgun-04");
}

EAmmoType AHandgun_04::GetWeaponAmmoType()
{
    return EAmmoType::Small;
}
