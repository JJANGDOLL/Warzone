// Fill out your copyright notice in the Description page of Project Settings.


#include "Casing/CasingGL.h"
#include "Engine/StaticMesh.h"
#include "Utilities/Global.h"

ACasingGL::ACasingGL()
{
    UStaticMesh* caseMesh;
    Helpers::GetAsset(&caseMesh, TEXT("StaticMesh'/Game/InfimaGames/AnimatedLowPolyWeapons/Art/Weapons/_Common/Casings/SM_Shell_Grenade_Empty.SM_Shell_Grenade_Empty'"));

    Mesh->SetStaticMesh(caseMesh);
}