// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapons/SMG_01.h"
#include "Datas/Weapons/WeaponsEnum.h"

ASMG_01::ASMG_01()
{
    WeaponType = EWeaponTypes::SMG_01;

    MakeWeapon();
}

EAmmoType ASMG_01::GetWeaponAmmoType()
{
    return EAmmoType::Small;
}

void ASMG_01::SetWeaponName()
{
    WeaponName = TEXT("SMG-01");
}
