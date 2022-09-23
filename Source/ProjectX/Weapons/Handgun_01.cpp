// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapons/Handgun_01.h"

AHandgun_01::AHandgun_01()
{
    WeaponType = EWeaponTypes::HANDGUN_01;

    MakeWeapon();
}

void AHandgun_01::SetWeaponName()
{
    WeaponName = TEXT("Handgun-01");

}
