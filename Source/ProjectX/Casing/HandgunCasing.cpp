// Fill out your copyright notice in the Description page of Project Settings.


#include "Casing/HandgunCasing.h"
#include "Utilities/Global.h"
#include "GameFramework/ProjectileMovementComponent.h"

AHandgunCasing::AHandgunCasing()
{
    UStaticMesh* mesh;
    Helpers::GetAsset(&mesh, TEXT("StaticMesh'/Game/InfimaGames/AnimatedLowPolyWeapons/Art/Weapons/_Common/Casings/SM_Bullet_Small_Empty.SM_Bullet_Small_Empty'"));
    Mesh->SetStaticMesh(mesh);
}

void AHandgunCasing::ApplyImpulse(FVector Direction, const FVector Strength)
{
    ProjectileMovement->Velocity = Direction * Strength;
}