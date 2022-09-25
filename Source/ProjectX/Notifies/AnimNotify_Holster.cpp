// Fill out your copyright notice in the Description page of Project Settings.


#include "Notifies/AnimNotify_Holster.h"
#include "Core/CharacterBase.h"
#include "Utilities/Global.h"

FString UAnimNotify_Holster::GetNotifyName_Implementation() const
{
    return TEXT("Holster End");
}

void UAnimNotify_Holster::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
    CheckNull(MeshComp);
    CheckNull(MeshComp->GetOwner());

    ACharacterBase* character = Cast<ACharacterBase>(MeshComp->GetOwner());
    CheckNull(character);

    character->EndHolstering();
}
