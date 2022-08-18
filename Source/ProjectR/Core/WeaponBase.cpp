// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/WeaponBase.h"
#include "Utilities/Global.h"

#include <Components/SkeletalMeshComponent.h>

// Sets default values
AWeaponBase::AWeaponBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

void AWeaponBase::OnFire()
{
    UAnimMontage* const fireMontage = MontageFire;
    verifyf(fireMontage, L"Fire Montage Null");

    UAnimInstance* const animInst = MeshWeapon->GetAnimInstance();
    animInst->Montage_Play(fireMontage);

    AmmunitionCurrent = FMath::Clamp(AmmunitionCurrent - 1, 0, AmmunitionMax);

    verifyf(ParticleMuzzleFlash, L"Muzzle Flash Null");
    UGameplayStatics::SpawnEmitterAttached(ParticleMuzzleFlash, MeshWeapon, TEXT("SOCKET_Muzzle"), FVector::ZeroVector, FRotator::ZeroRotator, FVector::OneVector, EAttachLocation::KeepRelativeOffset, true, EPSCPoolMethod::None, true);
}

void AWeaponBase::OnReload()
{
    UAnimMontage* const reloadMontage = IsEmpty() ? MontageReloadEmpty : MontageReload;
    verifyf(reloadMontage, L"Reload Montage Null");

    UAnimInstance* const animInst = MeshWeapon->GetAnimInstance();
    animInst->Montage_Play(reloadMontage);
}

bool AWeaponBase::IsAutomatic()
{
    return bAutomatic;
}

uint8 AWeaponBase::GetAmmunitionCurrent()
{
    return AmmunitionCurrent;
}

uint8 AWeaponBase::GetAmmunitionTotal()
{
    return AmmunitionMax;
}

float AWeaponBase::GetRateOfFire()
{
    return RateOfFire;
}

bool AWeaponBase::IsEmpty()
{
    return AmmunitionCurrent == 0;
}

UTexture* AWeaponBase::GetTextureWeaponBody()
{
    return TextureWeaponBody;
}

UTexture* AWeaponBase::GetTextureWeaponMagazine()
{
    return TextureWeaponMagazine;
}

UTexture* AWeaponBase::GetTextureWeaopnIronsight()
{
    return TextureWeaponIronsights;
}
