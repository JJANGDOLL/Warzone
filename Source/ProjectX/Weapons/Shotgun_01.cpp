// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapons/Shotgun_01.h"

AShotgun_01::AShotgun_01()
{
    WeaponType = EWeaponTypes::SHOTGUN_01;

    MakeWeapon();
}

void AShotgun_01::SetWeaponName()
{
    WeaponName = TEXT("Shotgun-01");

}
