// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapons/Assault_Rifle_02.h"

AAssault_Rifle_02::AAssault_Rifle_02()
{
    WeaponType = EWeaponTypes::ASSAULT_RIFLE_02;

    MakeWeapon();
}

void AAssault_Rifle_02::SetWeaponName()
{
    WeaponName = TEXT("Assault-Rifle-02");
}
