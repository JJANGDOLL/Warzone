// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/InteractTextWidget.h"
#include "Components/EditableText.h"

void UInteractTextWidget::SetInteractText(FText InText)
{
    InteractText->SetText(InText);
}
