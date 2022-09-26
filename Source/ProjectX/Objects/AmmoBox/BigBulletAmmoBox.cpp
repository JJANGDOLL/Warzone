// Fill out your copyright notice in the Description page of Project Settings.


#include "Objects/AmmoBox/BigBulletAmmoBox.h"

void ABigBulletAmmoBox::SetAmmoType()
{
    AmmoType = EAmmoType::Big;
}

void ABigBulletAmmoBox::SetDescriptionText()
{
    DescriptionText = FText::FromString(TEXT("Fill BigBullet Ammo"));
}
