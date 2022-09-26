// Fill out your copyright notice in the Description page of Project Settings.


#include "Objects/AmmoBox/SmallBulletAmmoBox.h"

void ASmallBulletAmmoBox::SetAmmoType()
{
    AmmoType = EAmmoType::Small;
}

void ASmallBulletAmmoBox::SetDescriptionText()
{
    DescriptionText = FText::FromString(TEXT("Fill SmallBullet Ammo"));
}
