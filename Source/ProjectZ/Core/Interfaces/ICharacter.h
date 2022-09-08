// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Core/Defines/Structs.h"
#include "ICharacter.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI, meta = (CannotImplementInterfaceInBlueprint))
class UICharacter : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class PROJECTZ_API IICharacter
{
	GENERATED_BODY()

		// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	virtual void OnPickUp() = 0;
	virtual bool TryStartAbility(FSGameAbility Ability) = 0;

	UFUNCTION(BlueprintCallable, Category = "Projz | Intf")
		virtual class AActor* GetEquippedItem() = 0;

	virtual int32 GetFieldOfView() = 0;
	virtual int32 GetFieldOfViewRunning() = 0;

	virtual bool IsAiming() = 0;
	virtual bool IsRunning() = 0;
	virtual float GetAimDuration() = 0;
	virtual float GetAimSpeedMultiplier() = 0;
	virtual FVector2D GetInputLook() = 0;
	virtual class UCameraComponent* GetCameraComponent() = 0;
	virtual FVector2D GetInputMovement() = 0;
};