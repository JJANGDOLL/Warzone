// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "WeaponTexture.generated.h"

class UImage;

UCLASS()
class PROJECTX_API UWeaponTexture : public UUserWidget
{
	GENERATED_BODY()

public:
	void SetWeaponBodyImage(class IIWeapon* Weapon);

    UPROPERTY(EditAnywhere, meta = (BindWidget))
	UImage* WeaponBody;
};
