// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "IWeapon.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UIWeapon : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class PROJECTR_API IIWeapon
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	virtual void OnFire() = 0;
	virtual void OnReload() = 0;
	virtual bool IsAutomatic() = 0;
	virtual uint8 GetAmmunitionCurrent() = 0;
	virtual uint8 GetAmmunitionTotal() = 0;
	virtual float GetRateOfFire() = 0;
	virtual bool IsEmpty() = 0;

	virtual UTexture* GetTextureWeaponBody() = 0;
	virtual UTexture* GetTextureWeaponMagazine() = 0;
    virtual UTexture* GetTextureWeaopnIronsight() = 0;

    virtual class UAnimMontage* GetFPMontageCharacterFire() = 0;
};
