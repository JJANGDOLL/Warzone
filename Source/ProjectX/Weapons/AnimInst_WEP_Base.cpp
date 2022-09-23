// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapons/AnimInst_WEP_Base.h"
#include "Core/Interfaces/IWeapon.h"
#include "Core/WeaponBase.h"

UAnimInst_WEP_Base::UAnimInst_WEP_Base()
{

}

void UAnimInst_WEP_Base::NativeBeginPlay()
{
    Super::NativeBeginPlay();

    Weapon = Cast<AWeaponBase>(GetOwningActor());
    WeaponItf = Cast<IIWeapon>(Weapon);
    verifyf(WeaponItf, L"Invalid weapon interface");
    EmptyAmmoPose = WeaponItf->GetEmptyPose();
}

void UAnimInst_WEP_Base::NativeUpdateAnimation(float DeltaSeconds)
{
    Super::NativeUpdateAnimation(DeltaSeconds);

    if (!WeaponItf)
        return;

    bEmpty = WeaponItf->IsEmpty() && !WeaponItf->IsReloading();
}
