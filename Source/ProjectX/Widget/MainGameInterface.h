// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Crosshair.h"
#include "MainGameInterface.generated.h"

class UWeaponWidget;
class UWeaponTexture;
class UInteractTextWidget;
class UPlayerStatus;

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

    UPROPERTY(EditAnywhere, meta = (BindWidget))
	UInteractTextWidget* InteractText;

	UInteractTextWidget* GetInteractText();

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UCrosshair* CrosshairWidget;

	UCrosshair* GetCrosshairWidget();
	void SetCrosshairClass(TSubclassOf<UCrosshair> CrosshairClass);

    UPROPERTY(EditAnywhere, meta = (BindWidget))
    UPlayerStatus* StatusWidget;

	UPlayerStatus* GetPlayerStatus();
};
