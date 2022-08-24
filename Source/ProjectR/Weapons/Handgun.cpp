// Fill out your copyright notice in the Description page of Project Settings. 


#include "Weapons/Handgun.h"

#include "Utilities/Global.h"

#include <Components/SceneComponent.h>
#include <Components/SkeletalMeshComponent.h>
#include <Components/StaticMeshComponent.h>
#include <Engine/StaticMesh.h>
#include <Engine/SkeletalMesh.h>
#include <Animation/AnimMontage.h>
#include <Animation/AnimInstance.h>
#include <Particles/ParticleSystem.h>

AHandgun::AHandgun()
{
    // component
    Helpers::CreateComponent<USkeletalMeshComponent>(this, &MeshWeapon, TEXT("Mesh Weapon"));
    USkeletalMesh* meshWeapon;
    Helpers::GetAsset(&meshWeapon, TEXT("SkeletalMesh'/Game/AnimatedLowPolyWeapons/Art/Weapons/Handguns/SK_Handgun_03.SK_Handgun_03'"));
    MeshWeapon->SetSkeletalMesh(meshWeapon);

    Helpers::CreateComponent<USceneComponent>(this, &SocketDefault, TEXT("Socket Default"), MeshWeapon, TEXT("SOCKET_Default"));
    Helpers::CreateComponent<UStaticMeshComponent>(this, &MeshIronsight, TEXT("Mesh Ironsight"), SocketDefault);
    UStaticMesh* meshIronsight;
    Helpers::GetAsset(&meshIronsight, TEXT("StaticMesh'/Game/AnimatedLowPolyWeapons/Art/Weapons/Handguns/SM_Handgun_03_Scope_Default.SM_Handgun_03_Scope_Default'"));
    MeshIronsight->SetStaticMesh(meshIronsight);
    MeshIronsight->SetCollisionEnabled(ECollisionEnabled::NoCollision);

    Helpers::CreateComponent<USceneComponent>(this, &SocketMagazine, TEXT("Socket Magazine"), MeshWeapon, TEXT("SOCKET_Magazine"));
    Helpers::CreateComponent<UStaticMeshComponent>(this, &MeshMagazine, TEXT("Mesh Magazine"), SocketMagazine);
    UStaticMesh* meshMagazine;
    Helpers::GetAsset(&meshMagazine, TEXT("StaticMesh'/Game/AnimatedLowPolyWeapons/Art/Weapons/Handguns/SM_Handgun_03_Magazine_Default.SM_Handgun_03_Magazine_Default'"));
    MeshMagazine->SetStaticMesh(meshMagazine);
    MeshMagazine->SetCollisionEnabled(ECollisionEnabled::NoCollision);

    // set inheritanced value
    bAutomatic = false;
    RateOfFire = 550.f;
    AmmunitionMax = 9;

    Helpers::GetAsset<UAnimMontage>(&MontageFire, "AnimMontage'/Game/AnimatedLowPolyWeapons/Art/Weapons/Handguns/Animations/AM_TP_WEP_Handgun_03_Fire.AM_TP_WEP_Handgun_03_Fire'");
    Helpers::GetAsset<UAnimMontage>(&MontageReload, "AnimMontage'/Game/AnimatedLowPolyWeapons/Art/Weapons/Handguns/Animations/AM_TP_WEP_Handgun_03_Reload.AM_TP_WEP_Handgun_03_Reload'");
    Helpers::GetAsset<UAnimMontage>(&MontageReloadEmpty, "AnimMontage'/Game/AnimatedLowPolyWeapons/Art/Weapons/Handguns/Animations/AM_TP_WEP_Handgun_03_Reload_Empty.AM_TP_WEP_Handgun_03_Reload_Empty'");

    Helpers::GetAsset<UTexture>(&TextureWeaponBody, "Texture2D'/Game/AnimatedLowPolyWeapons/Art/Icons/Weapons/Handguns/T_HUD_Handgun_03_D.T_HUD_Handgun_03_D'");
    Helpers::GetAsset<UTexture>(&TextureWeaponMagazine, "Texture2D'/Game/AnimatedLowPolyWeapons/Art/Icons/Weapons/Handguns/T_HUD_Handgun_03_Magazine_Default_D.T_HUD_Handgun_03_Magazine_Default_D'");
    Helpers::GetAsset<UTexture>(&TextureWeaponIronsights, "Texture2D'/Game/AnimatedLowPolyWeapons/Art/Icons/Weapons/Handguns/T_HUD_Handgun_03_Scope_Default_D.T_HUD_Handgun_03_Scope_Default_D'");

    TSubclassOf<UAnimInstance> animInst;
    Helpers::GetClass<UAnimInstance>(&animInst, "AnimBlueprint'/Game/AnimatedLowPolyWeapons/Demo/Useable/Animation/ABP_ALPW_WEP_Handgun_03.ABP_ALPW_WEP_Handgun_03_C'");
    MeshWeapon->SetAnimInstanceClass(animInst);

    Helpers::GetAsset<UParticleSystem>(&ParticleMuzzleFlash, "ParticleSystem'/Game/InfimaGames/LowPolyShooterPack/Art/Effects/Particles/PS_Muzzle_Flash.PS_Muzzle_Flash'");

    AmmunitionCurrent = AmmunitionMax;
}

void AHandgun::BeginPlay()
{
    Super::BeginPlay();
}
