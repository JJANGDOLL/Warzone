// Fill out your copyright notice in the Description page of Project Settings.


#include "Bullet/ARBullet.h"
#include "Utilities/Global.h"
#include "Particles/ParticleSystem.h"
#include "Particles/ParticleSystemComponent.h"

AARBullet::AARBullet()
{
    UStaticMesh* mesh;
    Helpers::GetAsset(&mesh, TEXT("StaticMesh'/Game/InfimaGames/LowPolyShooterPack/Art/Effects/Models/SM_Projectile_Bullet.SM_Projectile_Bullet'"));
    ProjectileMesh->SetStaticMesh(mesh);

    UParticleSystem* trailParticle;
    Helpers::GetAsset(&trailParticle, TEXT("ParticleSystem'/Game/InfimaGames/LowPolyShooterPack/Art/Effects/Particles/PS_Trail_Bullet.PS_Trail_Bullet'"));
    ParticlesTrail->SetTemplate(trailParticle);

    
}
