// Fill out your copyright notice in the Description page of Project Settings.


#include "Notifies/AnimNotify_SpawnCasing.h"
#include "Utilities/Global.h"
#include "Core/Interfaces/IWeapon.h"

FString UAnimNotify_SpawnCasing::GetNotifyName_Implementation() const
{
    Super::GetNotifyName_Implementation();
    
    return "Spawn Casing";
}

void UAnimNotify_SpawnCasing::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
    Super::Notify(MeshComp, Animation);

    CheckNull(MeshComp);
    CheckNull(MeshComp->GetOwner());

    IIWeapon* weapon = Cast<IIWeapon>(MeshComp->GetOwner());
    CheckNull(weapon);

    weapon->EjectCasing();
}
