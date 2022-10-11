// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapons/Handgun_03.h"

AHandgun_03::AHandgun_03()
{
    WeaponType = EWeaponTypes::HANDGUN_03;

    MakeWeapon();
}

void AHandgun_03::SetWeaponName()
{
    WeaponName = TEXT("Handgun-03");
}

EAmmoType AHandgun_03::GetWeaponAmmoType()
{
    return EAmmoType::Small;
}
