// Fill out your copyright notice in the Description page of Project Settings.


#include "Bullet/TurretBullet.h"
#include "Utilities/Global.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Character.h"

ATurretBullet::ATurretBullet()
{
    UStaticMesh* mesh;
    
    Helpers::GetAsset(&mesh, TEXT("StaticMesh'/Game/Objects/Sphere.Sphere'"));

    ProjectileMesh->SetWorldScale3D(FVector(0.1f, 0.1f, 0.1f));
    ProjectileMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
    ProjectileMesh->SetStaticMesh(mesh);

    CollisionBox->SetCollisionProfileName(TEXT("EnemyBullet"));

    LifeSpanTime = 20.f;

    Projectile->ProjectileGravityScale = 0.f;

    bShowText = false;


}

void ATurretBullet::BeginPlay()
{
    Super::BeginPlay();

    PlayerCharacter = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
    if (!PlayerCharacter)
        return;

    SetActorTransform(FTransform(   (PlayerCharacter->GetActorLocation() - GetActorLocation()).Rotation() , GetActorLocation()));

    Projectile->Velocity = GetActorForwardVector() * 500.f;
}

