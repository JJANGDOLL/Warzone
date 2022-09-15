// Fill out your copyright notice in the Description page of Project Settings.


#include "Casing/ARCasing.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Utilities/Global.h"

AARCasing::AARCasing()
{
    UStaticMesh* mesh;
    Helpers::GetAsset(&mesh, TEXT("StaticMesh'/Game/InfimaGames/AnimatedLowPolyWeapons/Art/Weapons/_Common/Casings/SM_Bullet_Big_Empty.SM_Bullet_Big_Empty'"));
    Mesh->SetStaticMesh(mesh);
}

void AARCasing::ApplyImpulse(FVector Direction, const FVector Strength)
{
    ProjectileMovement->Velocity = Direction * Strength;
}