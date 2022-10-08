// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/MainGameInterface.h"
#include "Kismet/GameplayStatics.h"

UWeaponWidget* UMainGameInterface::GetWeaponWidget()
{
    return WeaponWidget;
}

UWeaponTexture* UMainGameInterface::GetWeaponImage()
{
    return WeaponImage;
}

UInteractTextWidget* UMainGameInterface::GetInteractText()
{
    return InteractText;
}

UCrosshair* UMainGameInterface::GetCrosshairWidget()
{
    return CrosshairWidget;
}

void UMainGameInterface::SetCrosshairClass(TSubclassOf<UCrosshair> CrosshairClass)
{
    if (!CrosshairClass)
        return;

    if (CrosshairWidget)
    {
        CrosshairWidget->RemoveFromParent();
    }
    CrosshairWidget = CreateWidget<UCrosshair>(UGameplayStatics::GetPlayerController(GetWorld(), 0), CrosshairClass, TEXT("Crosshair"));
    CrosshairWidget->AddToViewport();
}
