// Fill out your copyright notice in the Description page of Project Settings.


#include "Bullet/ShotgunBullet.h"
#include "Utilities/Global.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "ShotgunBulletCore.h"


void AShotgunBullet::OnLaunch(bool bCinematic, FVector Velocity)
{
//     Projectile->Velocity = Velocity;

    for (uint8 i = 0; i < 7; i++)
    {
        AShotgunBulletCore* coreBullet = GetWorld()->SpawnActorDeferred<AShotgunBulletCore>(AShotgunBulletCore::StaticClass(), GetTransform(), this);
        coreBullet->SetPower(Power);
        coreBullet->FinishSpawning(GetTransform());
        coreBullet->OnLaunch(false,  Velocity);
    }
}
