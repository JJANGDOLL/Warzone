// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/WeaponBase.h"
#include "Utilities/Global.h"

#include <Components/SkeletalMeshComponent.h>
#include "Animation/AnimMontage.h"

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
    for(const auto& n : MeshWeapon->GetAllSocketNames())
    {
        Logger::Log(n.ToString());
    }
//     UGameplayStatics::SpawnEmitterAttached(ParticleMuzzleFlash, MeshWeapon, TEXT("SOCKET_Muzzle"), FVector::ZeroVector);
    UGameplayStatics::SpawnEmitterAttached(ParticleMuzzleFlash, MeshWeapon, TEXT("SOCKET_Muzzle"), FVector::ZeroVector, FRotator(0.f, 90.f, 0.f));
//     UGameplayStatics::SpawnEmitterAttached(ParticleMuzzleFlash, MeshWeapon, "");
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

UAnimMontage* AWeaponBase::GetFPMontageCharacterFire()
{
    verifyf(MontageFire, L"Fire Montage Null")
    return MontageFire;
}
