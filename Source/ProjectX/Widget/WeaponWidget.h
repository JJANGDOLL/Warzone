// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "WeaponWidget.generated.h"

class IIWeapon;
class UTextBlock;

UCLASS()
class PROJECTX_API UWeaponWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	void SetMaxAmmo(int8 Weapon);
	void SetCurAmmo(IIWeapon* Weapon);
	void SetFireType(IIWeapon* Weapon);

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UTextBlock* MaxAmmo;

    UPROPERTY(EditAnywhere, meta = (BindWidget))
    UTextBlock* CurAmmo;

    UPROPERTY(EditAnywhere, meta = (BindWidget))
    UTextBlock* FireType;
};
