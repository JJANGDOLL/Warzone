// Fill out your copyright notice in the Description page of Project Settings.


#include "Objects/DamageText.h"
#include "Engine/TextRenderActor.h"
#include "Components/TextRenderComponent.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Character.h"
#include "Components/CapsuleComponent.h"

ADamageText::ADamageText()
{
    GetTextRender()->SetHorizontalAlignment(EHorizTextAligment::EHTA_Center);
    GetTextRender()->SetVerticalAlignment(EVerticalTextAligment::EVRTA_TextCenter);
    GetTextRender()->SetWorldSize(12.f);
}

void ADamageText::BeginPlay()
{
    Super::BeginPlay();

    ACharacter* playerCharacter = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);

    FRotator rot = playerCharacter->GetCapsuleComponent()->GetForwardVector().Rotation();

    GetTextRender()->SetRelativeRotation(FRotator(0.f, rot.Yaw + 180.f, 0.f));
    SetLifeSpan(0.3f);
}

void ADamageText::SetText(FText Value, bool bCrit)
{
    if (bCrit)
        GetTextRender()->SetTextRenderColor(FColor::Yellow);
    GetTextRender()->SetText(Value);
}

