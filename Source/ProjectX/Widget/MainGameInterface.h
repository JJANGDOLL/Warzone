// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MainGameInterface.generated.h"

class UWeaponWidget;
class UWeaponTexture;

UCLASS()
class PROJECTX_API UMainGameInterface : public UUserWidget
{
	GENERATED_BODY()
	
public:
    UPROPERTY(EditAnywhere, meta = (BindWidget))
	UWeaponWidget* WeaponWidget;

	UWeaponWidget* GetWeaponWidget();

    UPROPERTY(EditAnywhere, meta = (BindWidget))
    UWeaponTexture* WeaponImage;

	UWeaponTexture* GetWeaponImage();
};
