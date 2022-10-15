// Fill out your copyright notice in the Description page of Project Settings.


#include "Objects/SampleTurret.h"
#include "Utilities/Global.h"
#include "Components/WidgetComponent.h"
#include "GameFramework/Character.h"
#include "Components/CapsuleComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Widget/EnemyStatus.h"
#include "Particles/ParticleSystem.h"
#include "Bullet/TurretBullet.h"
#include "Camera/PlayerCameraManager.h"
#include "ExplosionShake.h"
#include "ExplodeCameraShake.h"

ASampleTurret::ASampleTurret()
{
    Helpers::CreateComponent(this, &BaseMesh, TEXT("Body"));

    UStaticMesh* mesh;
    Helpers::GetAsset(&mesh, TEXT("StaticMesh'/Game/Objects/Cone.Cone'"));
    Helpers::CreateComponent(this, &StatusWidgetComp, TEXT("StatusWidget"), BaseMesh, TEXT("SOCKET_Widget"));

    BaseMesh->SetStaticMesh(mesh);

    BaseMesh->SetGenerateOverlapEvents(true);
    BaseMesh->SetCollisionProfileName(TEXT("Body"));

    TSubclassOf<UUserWidget> statusWidgetClass;
    Helpers::GetClass(&statusWidgetClass, TEXT("WidgetBlueprint'/Game/ProjectX/Widgets/WBP_EnemyStatus.WBP_EnemyStatus_C'"));

    StatusWidgetComp->SetWidgetClass(statusWidgetClass);
    StatusWidgetComp->AddRelativeLocation(FVector(0.f, 0.f, 15.f));
    StatusWidgetComp->SetWidgetSpace(EWidgetSpace::World);
    StatusWidgetComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);

    Helpers::GetAsset(&ExplodeParticle, TEXT("ParticleSystem'/Game/InfimaGames/LowPolyShooterPack/Art/Effects/Particles/PS_EXP_Spherical_Small_Air.PS_EXP_Spherical_Small_Air'"));

    MyShake = UExplodeCameraShake::StaticClass();
}

float ASampleTurret::TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser)
{
    PrintLine();

    float damage = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);

    CurrentHealth = FMath::Clamp<float>(CurrentHealth - damage, 0, MaxHealth);
    StatusWidget->SetHealth(MaxHealth, CurrentHealth);

    return damage;
}

void ASampleTurret::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

//     FQuat(GetController()->GetControlRotation())

    if (PlayerCharacter)
    {
        FRotator widgetRot = FQuat(PlayerCharacter->GetControlRotation()).GetForwardVector().Rotation() * -1;
        FVector dirChar = GetActorLocation() - PlayerCharacter->GetActorLocation();

        dirChar.Normalize();
        if (FVector::DotProduct(FQuat(PlayerCharacter->GetControlRotation()).GetForwardVector(), dirChar) > 0.98f)
        {
            StatusWidgetComp->SetVisibility(true);
            StatusWidgetComp->SetRelativeRotation(FRotator(0.f, 180.f, 0.f) - GetActorRotation());
            StatusWidgetComp->AddRelativeRotation(FRotator(0.f, widgetRot.Yaw * -1.f, 0.f));
        }
        else
        {
            StatusWidgetComp->SetVisibility(false);
        }
    }

    if (CurrentHealth <= 0)
    {
        UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ExplodeParticle, GetTransform());

        if (MyShake)
        {
            PrintLine();
            GetWorld()->GetFirstPlayerController()->PlayerCameraManager->StartCameraShake(MyShake, 1.0f);
        }

        Destroy();
    }
}

void ASampleTurret::Hitted(float Damage, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, class AActor* DamageCauser)
{
    TakeDamage(Damage, DamageEvent, EventInstigator, DamageCauser);

    PrintLine();
}

void ASampleTurret::Attack()
{
    ACharacter* character = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);

    PrintLine();

    bulletCount = 3;

    GetWorldTimerManager().UnPauseTimer(SpawnHandler);
}

void ASampleTurret::SpawnBullet()
{
    if (!PlayerCharacter)
        return;

    if (bulletCount == 0)
    {
        GetWorldTimerManager().PauseTimer(SpawnHandler);
        return;
    }

    FTransform bulletTransform = BaseMesh->GetSocketTransform(TEXT("SOCKET_Bullet"));

    ATurretBullet* bullet = GetWorld()->SpawnActor<ATurretBullet>(ATurretBullet::StaticClass(), bulletTransform);
    bullet->SetPower(10.f);
    bulletCount--;
}

void ASampleTurret::BeginPlay()
{
    Super::BeginPlay();
    
    StatusWidget = Cast<UEnemyStatus>(StatusWidgetComp->GetWidget());

    PlayerCharacter = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);

    GetWorldTimerManager().SetTimer(AttackHandler, this, &ASampleTurret::Attack, 5.f, true, 0.f);
    GetWorldTimerManager().SetTimer(SpawnHandler, this, &ASampleTurret::SpawnBullet, 0.3f, true, 0.f);
    GetWorldTimerManager().PauseTimer(SpawnHandler);

}
