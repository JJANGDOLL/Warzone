// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/WeaponWidget.h"
#include "Components/TextBlock.h"
#include "Core/Interfaces/IWeapon.h"
#include "Utilities/Global.h"

void UWeaponWidget::SetMaxAmmo(uint8 RemainAmmo)
{
//     int8 maxAmmo = Weapon->GetMaxAmmo();
    MaxAmmo->SetText(FText::AsNumber(RemainAmmo));
}

void UWeaponWidget::SetCurAmmo(IIWeapon* Weapon)
{
    int8 curAmmo = Weapon->GetCurAmmo();
    CurAmmo->SetText(FText::AsNumber(curAmmo));
}

void UWeaponWidget::SetFireType(IIWeapon* Weapon)
{
    switch (Weapon->GetFireType())
    {
        case EFireType::Single:
            FireType->SetText(FText::FromString(FString(L"Single")));
            break;
        case EFireType::Brust:
            FireType->SetText(FText::FromString(FString(L"Brust")));
            break;
        case EFireType::Auto:
            FireType->SetText(FText::FromString(FString(L"Auto")));
            break;
    }
}
