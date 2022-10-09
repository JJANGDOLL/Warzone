 // Fill out your copyright notice in the Description page of Project Settings.


#include "Core/WeaponBoltActionBase.h"
#include "Kismet/GameplayStatics.h"
#include "Datas/Weapons/WeaponDA.h"
#include "WeaponBody.h"
#include "Sound/SoundCue.h"
#include "Utilities/Global.h"
#include "Datas/Weapons/WeaponPoseDA.h"

void AWeaponBoltActionBase::Reload()
{
    PrintLine();

    bPlayingBoltActionReloading = true;

    if (CurrentAmmo == MaxAmmo)
        return;

    if (!WeaponDA->ReloadBoltaction)
        return;

    Weapon->GetAnimInstance()->Montage_Play(WeaponDA->ReloadBoltaction);
//     Weapon->GetAnimInstance()->Montage_SetNextSection("Default", "Insert", WeaponDA->ReloadBoltaction);
//     Weapon->GetAnimInstance()->Montage_JumpToSection("Default", WeaponDA->ReloadBoltaction);
//     Logger::Log(Weapon->GetAnimInstance()->Montage_GetCurrentSection(WeaponDA->ReloadBoltaction).ToString());

//     PrintLine();
//     FOnMontageEnded BlendOutDele;
//     BlendOutDele.BindUObject(this, &AWeaponBase::OnReloadBlendOut);
//     Weapon->GetAnimInstance()->Montage_SetBlendingOutDelegate(BlendOutDele, WeaponDA->MontageReload);
//     if (ReloadSound)
//         UGameplayStatics::PlaySoundAtLocation(GetWorld(), ReloadSound, GetActorLocation(), 2.f);
}

void AWeaponBoltActionBase::OnFireBlendOut(UAnimMontage* AnimMontage, bool bInterrupted)
{

}

void AWeaponBoltActionBase::Fire()
{
    PrintLine();


//     Weapon->GetAnimInstance()->Montage_Play(WeaponDA->MontageFire);
//     FOnMontageEnded BlendOutDele;
//     BlendOutDele.BindUObject(this, &AWeaponBoltActionBase::OnFireBlendOut);
//     Weapon->GetAnimInstance()->Montage_SetBlendingOutDelegate(BlendOutDele, WeaponDA->MontageFire);


    if (FireSound)
    {
        UGameplayStatics::PlaySoundAtLocation(GetWorld(), FireSound, GetActorLocation());
    }

    CurrentAmmo--;

    OnWeaponFire.ExecuteIfBound();
    OnWeaponRecoil.ExecuteIfBound();

//     GetWorldTimerManager().SetTimer(BoltActionTimer, this, &AWeaponBoltActionBase::BoltAction, 1.f, false, 1.f);
}

void AWeaponBoltActionBase::BoltAction()
{
    Weapon->GetAnimInstance()->Montage_Play(WeaponDA->MontageReload);
    FOnMontageEnded BlendOutDele;
    BlendOutDele.BindUObject(this, &AWeaponBase::OnReloadBlendOut);
    Weapon->GetAnimInstance()->Montage_SetBlendingOutDelegate(BlendOutDele, WeaponDA->MontageReload);
    if (ReloadSound)
        UGameplayStatics::PlaySoundAtLocation(GetWorld(), ReloadSound, GetActorLocation(), 2.f);
}

void AWeaponBoltActionBase::OnReloadBlendOut(UAnimMontage* AnimMontage, bool bInterrupted)
{
}

void AWeaponBoltActionBase::OnAmmoInsertBlendOut(UAnimMontage* AnimMontage, bool bInterrupted)
{
    PrintLine();
}

void AWeaponBoltActionBase::InsertBoltActionAmmo()
{
    Weapon->GetAnimInstance()->Montage_SetNextSection("Insert", "Insert", WeaponDA->ReloadBoltaction);

}

void AWeaponBoltActionBase::AddOneAmmo()
{
    Super::AddOneAmmo();
    if (CurrentAmmo == MaxAmmo)
        Weapon->GetAnimInstance()->Montage_JumpToSection("Close", WeaponDA->ReloadBoltaction);
}
