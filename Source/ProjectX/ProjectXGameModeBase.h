// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "ProjectXGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTX_API AProjectXGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	AProjectXGameModeBase();

protected:
	void BeginPlay() override;
};
