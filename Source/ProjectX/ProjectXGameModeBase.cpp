// Copyright Epic Games, Inc. All Rights Reserved.


#include "ProjectXGameModeBase.h"

#include "Utilities/Global.h"

AProjectXGameModeBase::AProjectXGameModeBase()
{

}

void AProjectXGameModeBase::BeginPlay()
{
    Super::BeginPlay();
    PrintLine();
}
