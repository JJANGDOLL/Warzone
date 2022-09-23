// Fill out your copyright notice in the Description page of Project Settings.


#include "System/CharacterTest.h"
#include "Core/CharacterBase.h"
#include "Core/PlayerControllerBase.h"

ACharacterTest::ACharacterTest()
{
    DefaultPawnClass = ACharacterBase::StaticClass();
    PlayerControllerClass = APlayerControllerBase::StaticClass();
}
