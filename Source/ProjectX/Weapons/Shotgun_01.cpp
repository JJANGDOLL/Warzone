// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapons/Shotgun_01.h"
#include "Core/WeaponBody.h"
#include "Core/CharacterBase.h"
#include "Utilities/Global.h"
#include "Kismet/GameplayStatics.h"
#include "Core/BulletBase.h"
#include "Datas/Weapons/WeaponDA.h"

AShotgun_01::AShotgun_01()
{
    WeaponType = EWeaponTypes::SHOTGUN_01;

    MakeWeapon();
}

void AShotgun_01::SetWeaponName()
{
    WeaponName = TEXT("Shotgun-01");
}

EAmmoType AShotgun_01::GetWeaponAmmoType()
{
    return EAmmoType::Big;
}

void AShotgun_01::SpawnBullet()
{
    FTransform bulletTransform = Weapon->GetSocketTransform(TEXT("SOCKET_Bullet"), RTS_World);

    ACharacterBase* ownerChar = Cast<ACharacterBase>(GetOwner());
    if (!ownerChar)
        return;

    FVector location;
    FVector direction;

    if (ownerChar->IsAiming() && ownerChar->GetController()->IsPlayerController())
    {
        PrintLine();

        int32 sizeX;
        int32 sizeY;
        UGameplayStatics::GetPlayerController(GetWorld(), 0)->GetViewportSize(sizeX, sizeY);
        UGameplayStatics::DeprojectScreenToWorld(UGameplayStatics::GetPlayerController(GetWorld(), 0), FVector2D(sizeX / 2, sizeY / 2), location, direction);

        bulletTransform.SetLocation(location);
        bulletTransform.SetRotation(direction.ToOrientationQuat());

        // 		DrawDebugDirectionalArrow(GetWorld(), location, location + direction * 3000.f, 10, FColor::Red, false, 20.f, 0.f, 1.f);
    }

    bulletTransform.SetScale3D(GetActorScale());
    ABulletBase* bullet = GetWorld()->SpawnActor<ABulletBase>(BulletClass, bulletTransform);
    if (bullet)
    {
        bullet->SetPower(WeaponDA->BulletPower);
        bullet->OnLaunch(false, bulletTransform.GetRotation().GetForwardVector() * WeaponDA->FireIntensity);
    }

    OnWeaponRecoil.ExecuteIfBound();
}
