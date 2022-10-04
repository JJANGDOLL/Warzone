// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapons/Attachments/ScopeBase.h"
#include "Datas/Weapons/WeaponsStructs.h"
#include "Components/SceneCaptureComponent2D.h"
#include "Engine/DataTable.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Character.h"

UScopeBase::UScopeBase()
{
    SetScopeName();
    SetScopeType();
}

void UScopeBase::SetScopeName()
{
    ScopeName = TEXT("Invalid");
}

void UScopeBase::SetScopeType()
{
    ScopeType = EScopeType::None;
}

void UScopeBase::EnableScope(UDataTable* ScopeDT)
{
    FWeaponScopeDARef* findDA = ScopeDT->FindRow<FWeaponScopeDARef>(ScopeName, "");
    if (!findDA)
        return;

    ScopeDA = Cast<UWeaponScopeDA>(findDA->DataRef);

    if (!ScopeSceneCapture && ScopeDA->TextureRender || true)
    {
        ScopeSceneCapture = NewObject<USceneCaptureComponent2D>(this, TEXT("ScopeSceneCapture"));
        ScopeSceneCapture->RegisterComponent();
        ScopeSceneCapture->AddRelativeRotation(FRotator(0.f, 90.f, 0.f));
        ScopeSceneCapture->AttachToComponent(this, FAttachmentTransformRules(EAttachmentRule::SnapToTarget, EAttachmentRule::KeepRelative, EAttachmentRule::SnapToTarget, false), TEXT("SOCKET_Render"));
        ScopeSceneCapture->TextureTarget = ScopeDA->TextureRender;
        ScopeSceneCapture->bCaptureOnMovement = true;
        ScopeSceneCapture->SetComponentTickEnabled(true);
        ScopeSceneCapture->SetVisibility(true);
        ScopeSceneCapture->FOVAngle = ScopeDA->ScopeMultiplier;
        ScopeSceneCapture->HiddenActors.AddUnique(GetOwner());
        ScopeSceneCapture->HiddenActors.AddUnique(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
    }
    SetStaticMesh(ScopeDA->ScopeMesh);

    ScopeAimOffset = ScopeDA->AimOffset;
}

FTransform UScopeBase::GetScopeOffset()
{
    return ScopeDA->AimOffset;
}

UStaticMesh* UScopeBase::GetScopeMesh()
{
    return ScopeMesh;
}
