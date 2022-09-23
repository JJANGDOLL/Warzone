// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/MainGameInterface.h"

UWeaponWidget* UMainGameInterface::GetWeaponWidget()
{
    return WeaponWidget;
}

UWeaponTexture* UMainGameInterface::GetWeaponImage()
{
    return WeaponImage;
}
