// Fill out your copyright notice in the Description page of Project Settings.


#include "Notifies/AnimNotify_SpawnBullet.h"
#include "Core/Interfaces/IWeapon.h"
#include "Utilities/Global.h"

FString UAnimNotify_SpawnBullet::GetNotifyName_Implementation() const
{
    return "Spawn Bullet";
}

void UAnimNotify_SpawnBullet::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
    Super::Notify(MeshComp, Animation);

    CheckNull(MeshComp);
    CheckNull(MeshComp->GetOwner());

    IIWeapon* weapon = Cast<IIWeapon>(MeshComp->GetOwner());
    CheckNull(weapon);

    weapon->SpawnBullet();
}
