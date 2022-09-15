// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/AnimInst_CharacterBase.h"
#include "Core/Interfaces/ICharacter.h"
#include "Core/Interfaces/IWeapon.h"
#include "Datas/Weapons/WeaponPoseDA.h"
#include "GameFramework/Character.h"
#include "Utilities/Global.h"
#include "Core/WeaponBase.h"

void UAnimInst_CharacterBase::NativeBeginPlay()
{
    Super::NativeBeginPlay();

    Character = Cast<ACharacter>(TryGetPawnOwner());

    if (!Character)
        return;

    CharItf = Cast<IICharacter>(Character);
}

void UAnimInst_CharacterBase::NativeUpdateAnimation(float DeltaSeconds)
{
    Super::NativeUpdateAnimation(DeltaSeconds);

    if (CharItf && CharItf->GetEquippedWeapon())
    {
        WeaponItf = Cast<IIWeapon>(CharItf->GetEquippedWeapon());
    }

    if (WeaponItf)
    {
        UWeaponPoseDA* posesDA = WeaponItf->GetPosesDA();
        if (posesDA)
        {
            PoseIdle = posesDA->Idle;
            PoseAim = posesDA->Aim;
        }
    }
}
