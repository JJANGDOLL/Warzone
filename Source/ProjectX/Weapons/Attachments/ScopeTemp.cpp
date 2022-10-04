// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapons/Attachments/ScopeTemp.h"
#include "Utilities/Global.h"
#include "Engine/DataTable.h"
#include "Datas/Weapons/WeaponsStructs.h"
#include "Datas/Weapons/WeaponScopeDA.h"
#include "Components/SceneCaptureComponent2D.h"
#include "Engine/TextureRenderTarget2D.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Character.h"
// #include "GameFramework/Actor.h"

UScopeTemp::UScopeTemp()
{
    UStaticMesh* scopeMesh;
    Helpers::GetAsset(&scopeMesh, TEXT("StaticMesh'/Game/InfimaGames/AnimatedLowPolyWeapons/Art/Weapons/_Common/Attachments/Models/SM_ATT_Scope_01.SM_ATT_Scope_01'"));

    SetStaticMesh(scopeMesh);

    ScopeType = SetScopeType();
    ScopeName = SetScopeName();

    Helpers::GetAsset(&TextureRender, TEXT("TextureRenderTarget2D'/Game/InfimaGames/AnimatedLowPolyWeapons/Art/Weapons/_Common/Attachments/Textures/RT_ATT_Scope_01.RT_ATT_Scope_01'"));

}

void UScopeTemp::BeginPlay()
{
    Super::BeginPlay();


}

EScopeType UScopeTemp::SetScopeType()
{
    return EScopeType::SCOPE_01;
}

FName UScopeTemp::SetScopeName()
{
    return TEXT("Scope-01");
}

void UScopeTemp::GetFOV(UDataTable* ScopeDT)
{
    FWeaponScopeDARef* findDA = ScopeDT->FindRow<FWeaponScopeDARef>(ScopeName, "");
    if (!findDA)
        return;

    ScopeDA = Cast<UWeaponScopeDA>(findDA->DataRef);

    if (!ScopeDA)
        return;

    if (!SceneCaptureScope)
        return;

    ScopeFOV = ScopeDA->ScopeMultiplier;
}

bool UScopeTemp::FindScopeDataInDataTable()
{
    static UDataTable* scopeRefDT = nullptr;
    if (!scopeRefDT)
        Helpers::GetAsset(&scopeRefDT, TEXT("DataTable'/Game/Datas/WeaponScope/AR_01/AR_01_Scope_DT.AR_01_Scope_DT'"));

    FWeaponScopeDARef* findDA = scopeRefDT->FindRow<FWeaponScopeDARef>(ScopeName, "");
    if (!findDA)
        return false;

    ScopeDA = Cast<UWeaponScopeDA>(findDA->DataRef);
    return true;
}

FTransform UScopeTemp::GetScopeOffset(UDataTable* ScopeDT)
{
    return ScopeAimOffset;
}

void UScopeTemp::EnableScope(UDataTable* ScopeDT)
{
    FWeaponScopeDARef* findDA = ScopeDT->FindRow<FWeaponScopeDARef>(ScopeName, "");
    if (!findDA)
        return;

    ScopeDA = Cast<UWeaponScopeDA>(findDA->DataRef);

    if (!SceneCaptureScope && ScopeDA->TextureRender || true)
    {
        SceneCaptureScope = NewObject<USceneCaptureComponent2D>(this, TEXT("ScopeSceneCapture"));
        SceneCaptureScope->RegisterComponent();
        SceneCaptureScope->AddRelativeRotation(FRotator(0.f, 90.f, 0.f));
        SceneCaptureScope->AttachToComponent(this, FAttachmentTransformRules(EAttachmentRule::SnapToTarget, EAttachmentRule::KeepRelative, EAttachmentRule::SnapToTarget, false), TEXT("SOCKET_Render"));
        SceneCaptureScope->TextureTarget = ScopeDA->TextureRender;
        SceneCaptureScope->bCaptureOnMovement = true;
        SceneCaptureScope->SetComponentTickEnabled(true);
        SceneCaptureScope->SetVisibility(true);
        SceneCaptureScope->FOVAngle = ScopeDA->ScopeMultiplier;
        SceneCaptureScope->HiddenActors.AddUnique(GetOwner());
        SceneCaptureScope->HiddenActors.AddUnique(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
    }

    ScopeAimOffset = ScopeDA->AimOffset;
}

