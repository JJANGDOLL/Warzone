// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/WeaponAttachmentBase.h"

UWeaponAttachmentBase::UWeaponAttachmentBase()
{
    PrimaryComponentTick.bCanEverTick = false;

    SetCollisionEnabled(ECollisionEnabled::NoCollision);

    CanCharacterStepUpOn = ECB_No;
    bAutoActivate = false;
}
