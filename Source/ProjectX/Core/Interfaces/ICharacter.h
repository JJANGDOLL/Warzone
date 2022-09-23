// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "ICharacter.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UICharacter : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class PROJECTX_API IICharacter
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	virtual class AWeaponBase* GetEquippedWeapon() = 0;
	virtual bool IsAiming() = 0;
	virtual void Aiming() = 0;
	virtual void Fire() = 0;
	virtual void Reload() = 0;
	virtual void ReloadEmpty() = 0;
	virtual bool IsRunning() = 0;
    virtual void Running() = 0;
	virtual void StopRunning() = 0;
	virtual bool IsFalling() = 0;
	virtual bool IsCrouching() = 0;
	virtual void Crouching() = 0;
	virtual bool IsBreath() = 0;
	virtual void Breath() = 0;
};
