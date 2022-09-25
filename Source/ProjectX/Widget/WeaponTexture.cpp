// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/WeaponTexture.h"
#include "Core/Interfaces/IWeapon.h"
#include "Components/Image.h"

void UWeaponTexture::SetWeaponBodyImage(IIWeapon* Weapon)
{
    WeaponBody->SetBrushFromTexture(Weapon->GetWeaponBodyImage());
    WeaponMagazine->SetBrushFromTexture(Weapon->GetWeaponBodyImage());
}
