// Fill out your copyright notice in the Description page of Project Settings.


#include "Notifies/AnimNotify_AddAmmoBoltAction.h"
#include "Core/Interfaces/IWeapon.h"
#include "Utilities/Global.h"

FString UAnimNotify_AddAmmoBoltAction::GetNotifyName_Implementation() const
{
    Super::GetNotifyName_Implementation();

    return "AddAmmo BoltAction";
}

void UAnimNotify_AddAmmoBoltAction::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
    Super::Notify(MeshComp, Animation);

    CheckNull(MeshComp);
    CheckNull(MeshComp->GetOwner());

    IIWeapon* weapon = Cast<IIWeapon>(MeshComp->GetOwner());
    CheckNull(weapon);

    weapon->AddOneAmmo();
}
