// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/WeaponAttachment.h"
#include "Utilities/Global.h"

UWeaponAttachment::UWeaponAttachment()
{
    NO_COLLISION(this);
    NO_OVERLAPEVENTS(this);
    NO_STEPUPON(this);
}
