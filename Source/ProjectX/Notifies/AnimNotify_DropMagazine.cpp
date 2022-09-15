// Fill out your copyright notice in the Description page of Project Settings.


#include "Notifies/AnimNotify_DropMagazine.h"
#include "Utilities/Global.h"
#include "Core/Interfaces/IWeapon.h"
#include "Components/StaticMeshComponent.h"

FString UAnimNotify_DropMagazine::GetNotifyName_Implementation() const
{
    Super::GetNotifyName_Implementation();

    return "Drop Magazine";
}

void UAnimNotify_DropMagazine::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
    Super::Notify(MeshComp, Animation);

    CheckNull(MeshComp);
    CheckNull(MeshComp->GetOwner());

    IIWeapon* weapon = Cast<IIWeapon>(MeshComp->GetOwner());
    CheckNull(weapon);

    UStaticMeshComponent* magazineMesh = weapon->GetWeaponMagazineMesh();

    if (!magazineMesh)
        return;

    if (!bDrop)
    {
        magazineMesh->SetVisibility(true);
    }
    else
    {
        magazineMesh->SetVisibility(false);
    }
}
