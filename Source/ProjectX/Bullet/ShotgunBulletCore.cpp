// Fill out your copyright notice in the Description page of Project Settings.


#include "Bullet/ShotgunBulletCore.h"
#include "GameFramework/ProjectileMovementComponent.h"


void AShotgunBulletCore::OnLaunch(bool bCinematic, FVector Velocity)
{
    FVector randomVector = FVector(FMath::FRandRange(-0.05f, 0.05f), FMath::FRandRange(-0.05f, 0.05f), FMath::FRandRange(-0.05f, 0.05f)) + GetActorForwardVector();
    randomVector.Normalize();

    Projectile->Velocity = randomVector * Velocity.Size();
}
