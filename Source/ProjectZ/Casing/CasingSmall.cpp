// Fill out your copyright notice in the Description page of Project Settings.


#include "Casing/CasingSmall.h"
#include "Engine/StaticMesh.h"
#include "Utilities/Global.h"

ACasingSmall::ACasingSmall()
{
    UStaticMesh* caseMesh;
    Helpers::GetAsset(&caseMesh, TEXT("StaticMesh'/Game/InfimaGames/AnimatedLowPolyWeapons/Art/Weapons/_Common/Casings/SM_Bullet_Small_Empty.SM_Bullet_Small_Empty'"));

    Mesh->SetStaticMesh(caseMesh);
}