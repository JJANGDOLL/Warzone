// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "IInventoryTarget.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UIInventoryTarget : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class PROJECTZ_API IIInventoryTarget
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	virtual class USkeletalMeshComponent* GetViewmodelArms() = 0;
};
