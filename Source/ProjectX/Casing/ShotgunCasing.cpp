// Fill out your copyright notice in the Description page of Project Settings.


#include "Casing/ShotgunCasing.h"
#include "Utilities/Global.h"
#include "GameFramework/ProjectileMovementComponent.h"

AShotgunCasing::AShotgunCasing()
{
    UStaticMesh* mesh;
    Helpers::GetAsset(&mesh, TEXT("StaticMesh'/Game/InfimaGames/AnimatedLowPolyWeapons/Art/Weapons/Shotguns/SM_Shotgun_01_Magazine_Default.SM_Shotgun_01_Magazine_Default'"));

    Mesh->SetStaticMesh(mesh);
    Mesh->AddRelativeRotation(FRotator(0.f, -90.f, 0.f));
}

void AShotgunCasing::ApplyImpulse(FVector Direction, const FVector Strength)
{
    ProjectileMovement->Velocity = Direction * Strength;
}
