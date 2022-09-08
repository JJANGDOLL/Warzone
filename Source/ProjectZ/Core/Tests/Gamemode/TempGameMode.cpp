// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/Tests/Gamemode/TempGameMode.h"
#include "Utilities/Global.h"
#include "Core/CharacterBase.h"

ATempGameMode::ATempGameMode()
{
    DefaultPawnClass = ACharacterBase::StaticClass();
}