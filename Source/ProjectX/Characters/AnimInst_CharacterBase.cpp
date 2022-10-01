// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/AnimInst_CharacterBase.h"
#include "Core/Interfaces/ICharacter.h"
#include "Core/Interfaces/IWeapon.h"
#include "Datas/Weapons/WeaponPoseDA.h"
#include "GameFramework/Character.h"
#include "Utilities/Global.h"
#include "Core/WeaponBase.h"
#include "Animation/AnimSequenceBase.h"

UAnimInst_CharacterBase::UAnimInst_CharacterBase()
{
    Helpers::GetAsset(&PoseIdle, TEXT("AnimSequence'/Game/InfimaGames/AnimatedLowPolyWeapons/Art/Characters/Animations/ARs/A_FP_PCH_AR_01_Idle_Pose.A_FP_PCH_AR_01_Idle_Pose'"));
    Helpers::GetAsset(&PoseAim, TEXT("AnimSequence'/Game/InfimaGames/AnimatedLowPolyWeapons/Art/Characters/Animations/ARs/A_FP_PCH_AR_01_Aim_Pose.A_FP_PCH_AR_01_Aim_Pose'"));
    Helpers::GetAsset(&PoseRun, TEXT("AnimSequence'/Game/InfimaGames/AnimatedLowPolyWeapons/Art/Characters/Animations/_Common/A_FP_PCH_Run_01.A_FP_PCH_Run_01'"));
    Helpers::GetAsset(&PoseHolster, TEXT("AnimSequence'/Game/InfimaGames/AnimatedLowPolyWeapons/Art/Characters/Animations/ARs/A_FP_PCH_AR_01_Holster.A_FP_PCH_AR_01_Holster'"));
    Helpers::GetAsset(&PoseUnholster, TEXT("AnimSequence'/Game/InfimaGames/AnimatedLowPolyWeapons/Art/Characters/Animations/ARs/A_FP_PCH_AR_01_Unholster.A_FP_PCH_AR_01_Unholster'"));
}

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

    if (CharItf)
    {
        bAiming = CharItf->IsAiming();
        bRunning = CharItf->IsRunning();
        bFalling = CharItf->IsFalling();
        bBreath = CharItf->IsBreath();
        bHolster = CharItf->IsHolster();
        Horizontal = FMath::Clamp(Character ->GetVelocity().Y / 100.f, -1.f, 1.f);
        Vertical = FMath::Clamp(Character ->GetVelocity().X / 100.f , -1.f, 1.f);;

        if (CharItf->GetEquippedWeapon())
        {
            WeaponItf = Cast<IIWeapon>(CharItf->GetEquippedWeapon());
        }
    }

    if (WeaponItf)
    {
        UWeaponPoseDA* posesDA = WeaponItf->GetPosesDA();
        if (posesDA)
        {
            PoseIdle = posesDA->Idle;
            PoseAim = posesDA->Aim;
            PoseRun = posesDA->Running;
        }
        AimOffset = WeaponItf->GetAimOffset();
    }
}

