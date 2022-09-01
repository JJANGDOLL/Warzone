// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "Loadout.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTZ_API ULoadout : public USaveGame
{
	GENERATED_BODY()
	
public:
	FName NameScope;
	FName NameMuzzle;
	FName NameLaser;
	FName NameGrip;
};
