// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapons/Attachments/ScopeTemp.h"
#include "Utilities/Global.h"
#include "Engine/DataTable.h"
#include "Datas/Weapons/WeaponsStructs.h"
#include "Datas/Weapons/WeaponScopeDA.h"
#include "Components/SceneCaptureComponent2D.h"
#include "Engine/TextureRenderTarget2D.h"

UScopeTemp::UScopeTemp()
{
    UStaticMesh* scopeMesh;
    Helpers::GetAsset(&scopeMesh, TEXT("StaticMesh'/Game/InfimaGames/AnimatedLowPolyWeapons/Art/Weapons/_Common/Attachments/Models/SM_ATT_Scope_01.SM_ATT_Scope_01'"));

    SetStaticMesh(scopeMesh);

    ScopeType = SetScopeType();
    ScopeName = SetScopeName();


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
    FWeaponScopeDARef* findDA = ScopeDT->FindRow<FWeaponScopeDARef>(ScopeName, "");
    if (!findDA)
        return FTransform::FTransform();

    ScopeDA = Cast<UWeaponScopeDA>(findDA->DataRef);

    if (!ScopeDA)
        return FTransform::FTransform();

    return ScopeDA->AimOffset;
}

