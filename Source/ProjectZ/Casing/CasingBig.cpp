// Fill out your copyright notice in the Description page of Project Settings.


#include "Casing/CasingBig.h"
#include "Engine/StaticMesh.h"
#include "Utilities/Global.h"

ACasingBig::ACasingBig()
{
    UStaticMesh* caseMesh;
    Helpers::GetAsset(&caseMesh, TEXT("StaticMesh'/Game/InfimaGames/AnimatedLowPolyWeapons/Art/Weapons/_Common/Casings/SM_Bullet_Big_Empty.SM_Bullet_Big_Empty'"));

    Mesh->SetStaticMesh(caseMesh);
}
