// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Core/AmmoBoxCore.h"
#include "SmallBulletAmmoBox.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTX_API ASmallBulletAmmoBox : public AAmmoBoxCore
{
	GENERATED_BODY()

protected:
	void SetAmmoType() override;
	void SetDescriptionText() override;

};
