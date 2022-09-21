// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/WeaponMagazine.h"
#include "Utilities/Global.h"

UWeaponMagazine::UWeaponMagazine()
{
    NO_COLLISION(this);
    NO_OVERLAPEVENTS(this);
    NO_STEPUPON(this);
}
