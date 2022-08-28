// Fill out your copyright notice in the Description page of Project Settings.


#include "Casing/CasingShell.h"
#include "Engine/StaticMesh.h"
#include "Utilities/Global.h"

ACasingShell::ACasingShell()
{
    UStaticMesh* caseMesh;
    Helpers::GetAsset(&caseMesh, TEXT("StaticMesh'/Game/InfimaGames/AnimatedLowPolyWeapons/Art/Weapons/_Common/Casings/SM_Shell_Empty.SM_Shell_Empty'"));

    Mesh->SetStaticMesh(caseMesh);
}