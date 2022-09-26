// Fill out your copyright notice in the Description page of Project Settings.


#include "Bullet/SniperBullet.h"
#include "Utilities/Global.h"

ASniperBullet::ASniperBullet()
{
    UStaticMesh* mesh;
    Helpers::GetAsset(&mesh, TEXT("StaticMesh'/Game/InfimaGames/LowPolyShooterPack/Art/Effects/Models/SM_Projectile_Bullet.SM_Projectile_Bullet'"));
    ProjectileMesh->SetStaticMesh(mesh);
}
